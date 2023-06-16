# Código (2/5)
## Cliente
* (P0) En el eventManager, como es un hilo dedicado SOLO a escuchar eventos de SDL, hay que usar `SDL_WaitEvent` para no hacer un busy wait que consuma 100% de CPU

```cpp
  while (true) {
            SDL_Event event;
            while (SDL_WaitEvent(&event)) {
            	// ...
            }
  }
```

* (P0) El event manager hace un return sin avisar a los demás hilos que el juego debe cerrarse. Esto genera que el cliente no se cierre debidamente porque hay hilos que piensan que deben seguir corriendo
```cpp
 if (event.type == SDL_QUIT) {
    return;
}
```
Una solución, es enviar un evento `Quit` a la cola `qEventsToRender`, y que el hilo main cierre todos los hilos.

* (P0) El gameloop llama a funciones **bloqueantes** como Queue::pop. Ya se habia hablado de que el gameloop no se puede bloquear **salvo** en el sleep (que no tiene).
* (P0) El gameloop no está atendiendo eventos que le lleguen del eventManager directamente (`qEventsToRender`)
* (P1) El gameloop debería poder procesar N eventos a renderizar que vengan de `qEventsToRender`
* (P2) El método run del cliente silencia todas las excepciones que se puedan lanzar
* (P4) Falta encapsulamiento, la barra de vida, los jugadores, el zombie podrían haber sido clases que encapsulen la lógica de la vista.
* (P2) `client_main.cpp` llama a funciones que pueden lanzar y no hay ningún bloque try catch (está en la clase client pero SDL puede lanzar. El bloque try catch debe estar en este main y no en el run de la clase client)
* (P3) La implementación de hilos del dipa que están usando ya tiene los bloques try-catch de forma que no se silencie ningún error, no es necesario que hagas bloques try-catch en los hilos sender, receiver y eventManager (que silencian errores).
* (P1) El hilo receiver no hace nada si recibe un comando Exit, ¿no debería irse del loop en este caso?
* (P0) ¿Cómo detecta el hilo receiver que el hilo fue cerrado?
* (P0) El booleano `wasClosed` está compartido entre hilos, y no es un objeto que sea atómico ==> Race Condition

## Server
* (P2) No hay un manejo de errores debido en el hilo main del server
* (P2) El shutdown de la clase socket del dipa puede lanzar excepcion. Al no hacer tu clase Server RAII, si se lanza excepción, jamás vas a joinear el hilo. El join del hilo debe hacerse en el destructor para asegurarte de que se intente joinear el hilo para no leakear memoria.
* (P0) La clase game no termina nunca. Una vez cerrados los dos clientes, el game permanece activo. Falta lógica que detecte cuando no hay mas clientes en la partida.


# Documentación (1/5)
(P1) Falta Documentación técnica y de proyecto. El manual de usuario debería estar unificado tanto para cliente y servidor, y podrían agregarle imagenes para hacerlo mas amigable para el usuario

# UX/Jugabilidad (2/5)
* (P0) Faltaría definir las dimensiones del camino, el jugador puede "flotar" en el aire
* (P1) Las definición de los elementos no se condice con lo que se muestra gráficamente, hay paredes invisibles que te impiden mover que pareciera se debe a cráteres
* (P0) Falta mostrar información del juego (balas restantes, tiempo de partida)
* (P4) La disposición de los botones es incómoda, y genera a veces tocar la tecla 's', matando al server con un segmentation fault.
* (P3) Si mantengo apretado la tecla a la derecha, y luego aprieto arriba (manteniendo la tecla derecha presionada) esperaría poder moverme en diagonal hacia arriba y derecha, pero el juego mueve al personaje a arriba. Cuando suelto una tecla debería poder moverme en la dirección restante.

# Robustez / Valgrind (todo tiene prioridad P0) (1/5)
* El server se muere al iniciar una partida por querer buscar un archivo en un path fijo. Debería fallar antes al inicializar el server para asegurarse de que todo se inicializó debidamente.
* El Cliente no hace un cierre natural del programa, se queda colgado y tenés que hacer un pkill para matarlo. Seguro faltan joinear hilos en el medio (ver sección Codigo del cliente que se encontró la causa).
* Cuando se muere el server, el cliente no lo podés cerrar, queda en un deadlock porque debe haber algún hilo que no se puede joinear
* El cliente puede enviar mensajes de JOIN, CREATE y START después de haber empezado la partida. Si se manda un mensaje de START luego de que la partida arrancó, el server muere con un segmentation fault. Agregar protecciones para que el cliente no pueda enviar estos mensajes una vez arrancó la partida, y también validar de que el server si le llegan estos mensajes, los ignore si la partida arrancó.
* Luego de cerrar los clientes, si quiero cerrar el server de forma ordenada, el programa termina con un segmentation fault. (probablemente debido a los hilos del gameloop que nunca se terminan debidamente)
* Si abro un cliente en un socket incorrecto, el cliente termina con un segmentation fault

* No se pudo correr valgrind en el cliente porque no se puede cerrar ordenadamente debido a los hilos no joineados. Una vez corregido eso, correr valgrind usando un archivo de supresión. Para generar el archivo de supresión se puede usar el ejemplo del [ejecutable sdlpp-events de este branch](https://github.com/Taller-de-Programacion/clases/tree/valgrind_supp_file_example/bibliotecas-gui/sdlpp). Para hacer un archivo de supresión, se debe correr el programa de SDL con valgrind, con los flags `--gen-suppressions=all --log-file=supp.txt` además de los clásicos `--leak-check=full --leak-resolution=high --show-leak-kinds=all --show-reachable=yes --track-fds=yes --track-origins=yes`

Una vez armado el archivo de supresión, queda eliminarle el ruido, para eso correr este script 

```python
#!/usr/bin/python3

# quick&dirty script para sacar los pids del log de valgrind
# para generar un file de supresiones

import sys
import re
import fileinput

try:
    if len(sys.argv) != 2:
        raise ValueError(f"Usage: {sys.argv[0]} <Filepath>")

    filename = sys.argv[1]
    for line in fileinput.input(filename, inplace = True):
       if not re.search('==[0-9]+==.*', line):
          print(line, end="")
except Exception as e:
    print(f"Error: {e}")
    print("Input a valid valgrind log file")
```
Es **importantisimo** que el archivo de supresión se genere usando un programa que sabés no leakea, ya que sino vas a silenciar leaks verdaderos. Por eso recomiendo que uses el ejecutable del branch mencionado, que renderiza texto, reproduce música y carga texturas).

* Se adjuntan trazas de valgrind del servidor para los casos:
	* Corrida normal: se jugó un juego normal sin querer romper nada, luego de que se cierran los clientes, se intentó cerrar el server con la 'q' y se observa la traza mostrada
	* Corrida para explotar el server: se levantaron dos clientes, se starteó la partida, y luego se le dio a start de nuevo

# Performance (2/5)
* (P1) Los clientes consumen 100% de CPU, en una computadora con un i7 y una placa de video potente... Ojo con los busy waits (es el hilo del event handler que hace un pollEvent)
* (P1) Si dejo el juego corriendo un tiempo largo (10 min), el cliente consume 200% de CPU y el server 50% de CPU 
(probablemente debido a muchos zombies en el mapa spawneados que tarda mucho en actualizarlos).
Se podría limitar la cantidad de zombies spawneados y corregir el problema de las colisiones en los crateres.
EDIT: después de revisar el código, se puede concluir que los 200% de CPU en el cliente se debe al hilo eventHandler (hace busy wait) + el hilo render que intenta renderizar un mapa con cientos de zombies y jugadores. 

El aumento de consumo de CPU del server se debe a que hay muchos (cientos de) zombies, a los cuales querés updatear. El hilo del gameloop se la pasa casi todo el tiempo procesando updatear los zombies y te consume mucho cpu. 

Se puede limitar la cantidad de zombies en el mapa a un número máximo.

* (P1) Arranco una partida, cierro los clientes y el server empieza a subir su consumo de CPU hasta llegar al 100% (debido a que el hilo game no se cierra y se spawnean zombies)

# Instalación (2/5)
* (P4) No hay instalación
* (P1) Hay paths a assets hardcodeados, debería ser variable en función de si estás ejecutandoló en modo desarrollo (paths locales)
o si estás en producción (`/usr/bin/` para los ejecutables, `/var/left4dead/` para las configuraciones)

# Features (1/5)

## Zombies
### Infectados (P0)
#### Caminan o permanecen quietos si no son molestados
No se pudo probar

#### Cuando el jugador esté en el rango de vision los persigue
No se puede probar

#### golpe con mordidas o golpes
No se puede probar

### Jumper (P0)
#### Salta sobre sus victimas
No se pudo apreciar

#### produce daño cuando cae sobre las victimas
No hay daños

#### salto tiene animación previa de aviso
No hay animación previa al salto

### Witch (P1)
No está el feature
#### ocasionalmente grita para atraer infectados

### Spear (P0)
No está el feature
#### usan armas como lanzas

### Venom (P3)
No está el feature
#### ataque a distancia
#### daña a todo jugador que esté en contacto con el ataque

## Jugador (P0)
### Munición infinita
Faltaría mostrar en pantalla las balas por rafaga restantes pero está el feature

### Tiempo de recarga
* Pareciera no haber, si apreto recargar y luego disparar al instante, la animación indica que se puede.
* Si no me muevo, apreto recargar, la animación parece durar tiempo infinito

### Todos salvo P90 pueden lanzar granadas explosivas y de humo
No se pudo probar

### IDF
#### rafaga de 20 balas 
Pareciera tener rafagas infinitas

#### daño a corta distancia alto
No se puede probar. Faltaría un indicador de la vida del zombie para corroborarlo

#### daño menor a larga distancia
No se pudo probar

#### recarga cada 50 rafagas
Por mas que mantenga presionado disparar por mucho tiempo, nunca se pasa a un estado "recargar" cuando llega a tener cero balas

### P90

#### rafagas de 10 balas
No se pudo probar.

#### daño no reducido a largas distancias
No se pudo probar
#### recarga cada 30 rafagas
No se pudo probar

### Scout
#### Rifle de 1 bala
No se pudo probar
#### Atraviesa infectados
No se pudo probar

#### Daño se reduce por cada impacto entre infectados
No se pudo probar

#### recarga cada 20 bbalas
No se pudo probar

## Granadas
No aplica, al ser grupo de 2
### Son infinitas
### hay un tiempo de espera entre lanzamientos
### explosiva: daña enemigos en la zona. Daña a jugadores aliados también
### humo: no producen daño. Los infectados quedan aturdidos y dejan de correr y saltar, siguen caminando

## Bombardeo aereo
No aplica, al ser grupo de 2
### Solo P90 puede invocarlo
### caen granadas por todo el escenario salvo la zona cercana al jugador
### tiempo de espera entre bombardeos mayor

## Vida
### Los jugadores y zombies tienen vida. Cuando llega a cero son derribados (P0)
* Se ve la vida de los jugadores, pero no de los zombies.
* Los zombies parecieran no atacar, ya que no se puede ver que se reduzca la vida de los jugadores
* No se pudo probar el derribo

### Los jugadores derribados pueden recibir asistencia por otro jugador y seguir jugando (P3)
No se pudo probar

### el jugador recuperado se levanta con mitad de vida (P3)
No se pudo probar

### a los 3 derribos muere inmediatamente. (P3)
No se pudo probar

### Si jugador derribado no es asistido, muere (P3)
No se pudo probar

## Ataque y colisiones
### soldados y zombies pueden colisionar
Esto está funcionando, pareciera que las dimensiones de la caja de cada personaje es muy pequeña y en el cliente
se ve como que casi se estuvieran superponiendo, pero se puede ver que se detectan las colisiones.

### hay un hitbox para detectar zombies en el eje y
* La caja que determina la posición del jugador no coincide con el sprite (intentar caminar hacia arriba con un jugador en el limite izquierdo del otro jugador y luego repetir con el costado derecho del jugador)

## Escenario
### los crateres son zona por la que no podés caminar (P3)
La zona donde está modelado el crater en el servidor no coincide con el sprite, pareciera haber zonas con una pared invisible que pareciera ser un crater cercano.

### hay una camara que sigue al jugador 
No aplica, grupo 2 personas

### Pantalla lateral scrolleable
No aplica.

### Hay una ilusion de paralaje
No aplica.

## Modos de juego
### Clear the zone
No aplica
#### cantidad fija de zombies. Jugador gana cuando elimina a todos

### Survival
#### Cantidad infinita de zombies.
Los zombies parecieran ir spawneando constantemente a los costados, pero se chocan con un crater y se quedan trabados.

#### cada vez se hacen mas fuertes, resistentes y veloces (P3)
No se puede probar

#### termina cuando jugadores mueren (P0)
No se puede probar

## Fin de partida (P0)
No se pudo ver este feature
### se muestra estadisticas de juego (cantidad de eliminados, balas disparadas, tiempo de partida) (P4)
### En modo survival las estadisticas se guardan y se muestra un ranking historico (1 ranking por cada estadistica) que se muestra al final del modo (P4)

## Interfaz gráfica
### Se muestra la vida de cada soldado (P0)
La barra de vida está, pero no se ve que se reduzca ante daños

### Se muestra las rafagas restantes antes de recargar (P1)
No se muestra en pantalla esto

### Se muestra tiempo restante para lanzar granada
No aplica

### Se muestra balas disparadas
No se puede ver

### Se muestra infectados eliminados (P2)
No se puede ver

### Se muestra tiempo transcurrido (P1)
No se muestra

## Controles
### se controla via teclado
La disposición de teclas genera que varias veces mate al server con un segmentation fault queriendo hacer una recarga que en realidad envia un comando START

### Recarga automatica y manual (mediante botón de recarga) (P1)
No se pudo ver este feature

### distancia de lanzado de granada depende de cuanto tiempo se mantiene presionado la tecla
No aplica
### Si mantenés mucho tiempo presionado la tecla de lanzar granada, explota en la mano
No aplica

## sonidos (P0)
No hay sonidos
### cuando hay disparo
### cuando hay expĺosion

## Musica (P0)
No hay

## Animaciones (P0)
* El disparo no está animado
* Los zombies están animados de una forma rara, pasan sus frames muy rapidos respecto al movimiento que hacen. O deberían moverse mas rapido o la animación de caminar debería tardar mas tiempo en terminar. Esto debería corregirse mediante archivo de configuración para modificarlo rapido sin recompilar.

## Configuraciones (P0)
* El cliente no tiene archivo de configuración. Esto hubiera venido bien para ajustar el tiempo que debe transcurrir entre un cambio de frame y otro en los distintos zombies para que la animación se condiga con el movimiento que realmente hacen.

## Cheat (P5)
No aplica
## Tests (P2)
Hay 3 tests rotos
* ServerProtocolTest.TestEncodeServerMessage (Failed)
* ServerProtocolTest.TestEncodeJoinMessage (Failed)
* ZombieSpawnerTest.CheckZombieSpawn (Failed)

# Cliente - Servidor (P0) (2/5)
* No puedo crear multiples partidas
* No hay un debido manejo de hilos en el cliente y el servidor para cerrar las aplicaciones ordenadamente

# Extras
No hay