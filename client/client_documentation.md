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

