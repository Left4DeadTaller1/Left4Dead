# Left4Dead
Left4Dead is a imitation of the game Left 4 Dead made by students from the University of Buenos Aires for the subject Taller de Programacion 1.

## Documentacion

## Acciones del juego

**Moverse**: Utiliza las flechas del teclado para mover al personaje en las siguientes direcciones:
```
`↑`: Mover hacia arriba.

`↓`: Mover hacia abajo.

`←`: Mover hacia la izquierda.

`→`: Mover hacia la derecha.
```

**Correr**: Para correr, mantén presionada la flecha correspondiente a la dirección en la que deseas moverte y presiona la tecla `Shift` al mismo tiempo.
*Ejemplo*: `↑` + `Shift` para correr hacia arriba.

**Disparar**: Presiona la tecla `f` para disparar. El personaje realizará una acción de disparo al presionar esta tecla.

**Recargar**: Para recargar el arma, presiona la tecla `r`. El personaje realizará una acción de recarga al presionar esta tecla.

**Revivir**: Presiona la tecla `g` para revivir. Esta acción se utiliza para revivir a un personaje en el juego.

**Silenciar**: Para silenciar o activar el sonido del juego, presiona la tecla `m`.

## Menu Del Juego

**Campos obligatorios**

![Rojo](https://via.placeholder.com/15/FF0000/000000?text=+)  Campos obligatorios para crear una partida.

![Naranja](https://via.placeholder.com/15/FFA500/000000?text=+)   Campos obligatorios para unirse a una partida.

![Captura desde 2023-07-01 07-42-49](https://github.com/Left4DeadTaller1/Left4Dead/assets/83927746/788ddfe1-7da9-4040-b38e-daaa2eb62f8e)

**Cuando los jugadores se unan a la partida, se mostrarán en pantalla junto con su nombre de usuario y el arma que estén utilizando.**

![Captura desde 2023-07-01 07-33-22](https://github.com/Left4DeadTaller1/Left4Dead/assets/83927746/72e8016e-3e3c-49de-a75a-70288ff35fd9)

## Juego
![Captura desde 2023-07-01 07-58-17](https://github.com/Left4DeadTaller1/Left4Dead/assets/83927746/1067cb7c-10d4-4e88-b0e6-8516d1adcc50)

![Captura desde 2023-07-01 08-03-31](https://github.com/Left4DeadTaller1/Left4Dead/assets/83927746/13512fd5-827a-4c62-848a-1a5db7505050)

## Implementacion

Se utilizo como lenguaje C++, y para la parte grafica del juego, utilizamos QT y SDL2pp.

Con QT, diseñamos el menú de juego. Y con SDL2pp renderizamos los elementos visuales del juego, como los jugadores, los zombies y el fondo.

**Menu QT:**

![menuQT drawio](https://github.com/Left4DeadTaller1/Left4Dead/assets/83927746/1c408d65-3534-4b87-adc4-c4c0f8aee069)


![tallerDiagrama2 drawio (1)](https://github.com/Left4DeadTaller1/Left4Dead/assets/83927746/f50e9fe6-539f-4bb8-9fd5-7e1a4c47a9dd)


![Copia de tallerDiagramaJoinMane drawio](https://github.com/Left4DeadTaller1/Left4Dead/assets/83927746/62a0a16d-ab4a-405e-8e26-570af0e94d87)

Si el codigo de retorno del menu de QT es cero significa que el juego debe arranacar, el programa crea una instancia de la clase Client que sera la que lanzara los hilos:

*EventManager*

*ClientSender*

*ClientReceiver*

![esqueleto drawio](https://github.com/Left4DeadTaller1/Left4Dead/assets/83927746/55d3a2cb-e63b-4f5a-9155-58f05bb4e418)

diagrama de clases con loopRenderer()