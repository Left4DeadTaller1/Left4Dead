# UX/Jugabilidad (2/5)
* (P1) Las definición de los elementos no se condice con lo que se muestra gráficamente, hay paredes invisibles que te impiden mover que pareciera se debe a cráteres

# Instalación (2/5)
* (P4) No hay instalación
* (P1) Hay paths a assets hardcodeados, debería ser variable en función de si estás ejecutandoló en modo desarrollo (paths locales)
o si estás en producción (`/usr/bin/` para los ejecutables, `/var/left4dead/` para las configuraciones)


## Animaciones (P0)
* El disparo no está animado
* Los zombies están animados de una forma rara, pasan sus frames muy rapidos respecto al movimiento que hacen. O deberían moverse mas rapido o la animación de caminar debería tardar mas tiempo en terminar. Esto debería corregirse mediante archivo de configuración para modificarlo rapido sin recompilar.

## Configuraciones (P0)
* El cliente no tiene archivo de configuración. Esto hubiera venido bien para ajustar el tiempo que debe transcurrir entre un cambio de frame y otro en los distintos zombies para que la animación se condiga con el movimiento que realmente hacen.

queda:
- sacar musica de qt y poner la de sdl con evento para apagar
- mejorar menu qt, mandar tipo de arma
- ver porque me llega una vez dead, si es asi hacer un contador en las clases y manejar los frames de dead 
- ver de dargar los datos con el .yaml
- tests
- (P3) La implementación de hilos del dipa que están usando ya tiene los bloques try-catch de forma que no se silencie ningún error, no es necesario que hagas bloques try-catch en los hilos sender, receiver y eventManager (que silencian errores). VER SI EL TRY CATCH DE LA COLA SAFA O MEJOR CERRARLOS DESDE EL HILO MAIN
- (P0) Faltaría definir las dimensiones del camino, el jugador puede "flotar" en el aire, por las dudas ajustarlas tamb del lado del cliente
- (P0) Falta mostrar información del juego (balas restantes, tiempo de partida)
- (P4) La disposición de los botones es incómoda, y genera a veces tocar la tecla 's', matando al server con un segmentation fault.
- (P3) Si mantengo apretado la tecla a la derecha, y luego aprieto arriba (manteniendo la tecla derecha presionada) esperaría poder moverme en diagonal hacia arriba y derecha, pero el juego mueve al personaje a arriba. Cuando suelto una tecla debería poder moverme en la dirección restante. (ya esta, pero ver si se puede hacer que gire con cierto angulo)
- (P0) El cliente puede enviar mensajes de JOIN, CREATE y START después de haber empezado la partida. Si se manda un mensaje de START luego de que la partida arrancó, el server muere con un segmentation fault. Agregar protecciones para que el cliente no pueda enviar estos mensajes una vez arrancó la partida, y también validar de que el server si le llegan estos mensajes, los ignore si la partida arrancó.
- (P0) Si abro un cliente en un socket incorrecto, el cliente termina con un segmentation fault

* No se pudo correr valgrind en el cliente porque no se puede cerrar ordenadamente debido a los hilos no joineados. Una vez corregido eso, correr valgrind usando un archivo de supresión. Para generar el archivo de supresión se puede usar el ejemplo del [ejecutable sdlpp-events de este branch](https://github.com/Taller-de-Programacion/clases/tree/valgrind_supp_file_example/bibliotecas-gui/sdlpp). Para hacer un archivo de supresión, se debe correr el programa de SDL con valgrind, con los flags `--gen-suppressions=all --log-file=supp.txt` además de los clásicos `--leak-check=full --leak-resolution=high --show-leak-kinds=all --show-reachable=yes --track-fds=yes --track-origins=yes`


creo que estan:

Una solución, es enviar un evento `Quit` a la cola `qEventsToRender`, y que el hilo main cierre todos los hilos.

* (P0) El gameloop llama a funciones **bloqueantes** como Queue::pop. Ya se habia hablado de que el gameloop no se puede bloquear **salvo** en el sleep (que no tiene).
* (P0) El gameloop no está atendiendo eventos que le lleguen del eventManager directamente (`qEventsToRender`)
* (P1) El gameloop debería poder procesar N eventos a renderizar que vengan de `qEventsToRender`
* (P2) El método run del cliente silencia todas las excepciones que se puedan lanzar
* (P4) Falta encapsulamiento, la barra de vida, los jugadores, el zombie podrían haber sido clases que encapsulen la lógica de la vista.
* (P2) `client_main.cpp` llama a funciones que pueden lanzar y no hay ningún bloque try catch (está en la clase client pero SDL puede lanzar. El bloque try catch debe estar en este main y no en el run de la clase client)
* (P1) El hilo receiver no hace nada si recibe un comando Exit, ¿no debería irse del loop en este caso?
* (P0) ¿Cómo detecta el hilo receiver que el hilo fue cerrado?
* (P0) El booleano `wasClosed` está compartido entre hilos, y no es un objeto que sea atómico ==> Race Condition
* El Cliente no hace un cierre natural del programa, se queda colgado y tenés que hacer un pkill para matarlo. Seguro faltan joinear hilos en el medio (ver sección Codigo del cliente que se encontró la causa).
* Cuando se muere el server, el cliente no lo podés cerrar, queda en un deadlock porque debe haber algún hilo que no se puede joinear
* (P1) Los clientes consumen 100% de CPU, en una computadora con un i7 y una placa de video potente... Ojo con los busy waits (es el hilo del event handler que hace un pollEvent)
* (P1) Si dejo el juego corriendo un tiempo largo (10 min), el cliente consume 200% de CPU y el server 50% de CPU 
(probablemente debido a muchos zombies en el mapa spawneados que tarda mucho en actualizarlos).
Se podría limitar la cantidad de zombies spawneados y corregir el problema de las colisiones en los crateres.
EDIT: después de revisar el código, se puede concluir que los 200% de CPU en el cliente se debe al hilo eventHandler (hace busy wait) + el hilo render que intenta renderizar un mapa con cientos de zombies y jugadores. 