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

