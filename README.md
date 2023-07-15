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
>¿Cuál es el mejor momento para leer el pulsador, luego de un ciclo completo de la secuencia o después de encender y apagar un led? ¿Qué diferencia hay entre estas alternativas?>

El mejor momento es antes del ciclo, ya que en caso de detectarse el cambio de estado, el tiempo de ejecucion siguiente nos favorece para evitar rebotes.
>¿Cambiaría las respuestas a las preguntas anteriores si el tiempo de encendido de cada led fuera sensiblemente más grande, 1 segundo por ejemplo? ¿Y si fuera  sensiblemente más chico, 50 ms por ejemplo?

Si, ya que esta relacionado con el efecto que queremos disminuir.







### Practica 2

La carpeta Practica 2 contiene el proyecto finalizado correspondiente.  Debido a que la placa nucleo con la que se realizo el trabajo no posee mas de 1 led para uso del usuario, para esta practica se utilizaron los pines pb10,pb4 y pb5 como gpio output para colocar 3 leds (LED1,LED2 y LED3 respectivamente).

>¿Se pueden cambiar los tiempos de encendido de cada led fácilmente en un solo lugar del código o éstos están hardcodeados?

Como la idea es que el tiempo siempre sea el mismo en todo momento de ejecucion, su valor va a quedar almacenado en una constante. Si yo debo utilizar muchas veces esa constante, lo mejor es crear una variable con la directiva DEFINE, para asi si el dia de mañana deseo cambiar el tiempo, solo tengo que editarlo en un solo lado.

>¿Qué bibliotecas estándar se debieron agregar para que el código compile? Si las funcionalidades crecieran, habría que pensar cuál sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usan en el ejercicio.

La libreria agregada es la stdbool.h. Cada vez que se agregan .h se debe ser precavido para evitar colocarlos mas de una vez en el codigo final, ya que eso da error.

>¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos?

Esto lo hemos discutido la clase pasada, y llegamos a la conclucion de que cada vez que uno realiza un driver o una aplicacion,siempre se debe proteger contra los usos herroneos de la misma

### Practica 3

La carpeta Practica 3ccontiene el proyecto finalizado correspondiente.  Debido a que la placa nucleo con la que se realizo el trabajo no posee mas de 1 led para uso del usuario, para esta practica se utilizaron los pines pb10,pb4 y pb5 como gpio output para colocar 3 leds (LED1,LED2 y LED3 respectivamente).

>¿Se pueden cambiar los tiempos de encendido de cada led fácilmente en un solo lugar del código o éstos están hardcodeados?

Como la idea es que el tiempo siempre sea el mismo en todo momento de ejecucion, su valor va a quedar almacenado en una constante. Si yo debo utilizar muchas veces esa constante, lo mejor es crear una variable con la directiva DEFINE, para asi si el dia de mañana deseo cambiar el tiempo, solo tengo que editarlo en un solo lado.

>¿Qué bibliotecas estándar se debieron agregar para que el código compile? Si las funcionalidades crecieran, habría que pensar cuál sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usan en el ejercicio.

La libreria agregada es la stdbool.h. Cada vez que se agregan .h se debe ser precavido para evitar colocarlos mas de una vez en el codigo final, ya que eso da error.

>¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos?

Esto lo hemos discutido la clase pasada, y llegamos a la conclucion de que cada vez que uno realiza un driver o una aplicacion,siempre se debe proteger contra los usos herroneos de la misma


### Practica 4
La practica 4 esta dividida en dos proyectos. Si bien el comportamiento en ambos es el mismo, el ejercico 2 es mucho mas prolijo en terminos de codigo.
El segundo ejercicio se realizo con interrupciones por flanco del boton de la placa. Sumado a esto, se reacomodo el driver del timer systic de forma tal que sea posible inicializar el timer y controlar si se cumplio desde dos funciones distintas.

>¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos? 

>¿Se nota una mejora en la detección de las pulsaciones respecto a la práctica 0? ¿Se pierden pulsaciones? ¿Hay falsos positivos?

