# SBualo-CESE
STM32CubeIDE workspace  - CESE - FIUBA

Repo donde se van a ir subiendo la ejercitacion mediante diferentes carpetas


## Programacion de Microcontroladores

_Todos los proyectos se encuentran realizados para la placa Nucleo-F401RE_ 

### Practica 1

En la carpeta Test Project se encuentra el projecto finalizado de la practia 1.  Debido a que la placa nucleo con la que se realizo el trabajo no posee mas de 1 led para uso del usuario, se construyeron funcinoes con distintos parpadeos del led que hacen de funcion de LED1,LED2 y LED3.
Cada una posee una duracion de 1 segundo, y se las activa con 1 segundo de delay a cada una (en opocision a los 200 ms que proponia la consigna, ya que sino no se logra distinguir el cambio). 
A continuacion se contestan las preguntas relacionadas a la práctica:
>De qué serviría usar un array de “leds” con la secuencia en el programa? ¿Qué pasa con nuestro programa si nos piden agregar/sacar/cambiar un led de la secuencia? 
En caso de utilizar arrays, se hace mucho mas sencillo cualquier cambio que se le quiera hacer a la secuencia, ya que al diseñar la funcion para que el programa busque el led que tiene que prender en un array, evita que si lo cambio tenga que rehacer las funciones para los distintos leds.
>¿Cómo responde el programa a las pulsaciones, hay falsos positivos o pulsaciones no detectadas? ¿Se implementa alguna técnica de antirrebote de las pulsaciones?
Si bien la unica "tecnica" utilizada para evitar rebotes es la implementacion de un flag restrictivo + una demora en el tiempo de un resensado, siempre no es la solucion optima, ya que si el boton se mantiene pulsado por tiempo indefinido, se van a activar constantemente las funciones.
>¿Cuál es el mejor momento para leer el pulsador, luego de un ciclo completo de la secuencia o después de encender y apagar un led? ¿Qué diferencia hay entre estas alternativas?
El mejor momento es antes del ciclo, ya que en caso de detectarse el cambio de estado, el tiempo de ejecucion siguiente nos favorece para evitar rebotes.
>¿Cambiaría las respuestas a las preguntas anteriores si el tiempo de encendido de cada led fuera sensiblemente más grande, 1 segundo por ejemplo? ¿Y si fuera  sensiblemente más chico, 50 ms por ejemplo?
Si, ya que esta relacionado con el efecto que queremos disminuir.







