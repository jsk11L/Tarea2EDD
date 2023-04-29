# Tarea2EDD

- Crear perfil de jugador/a (nombre) ✔
- Mostrar perfil de jugador/a (nombre) ✔
- Agregar item a jugador/a (nombre, item) ✔
- Eliminar item de jugador/a (nombre, item) ✔
- Agregar puntos de habilidad a el/la jugador/a (nombre, puntos) ✔
- Mostrar jugador@s con item específico (item) ✔
- Deshacer última acción de jugador/a (nombre) ✔
- Exportar datos de jugadores a archivo de texto (nombre_archivo) ✔
- Cargar datos de jugadores desde un archivo de texto (nombre_archivo) ✔

===== 1 - COMO COMPILAR Y EJECUTAR LA TAREA =====

Al nosotros no tener compilador interno de C, para compilarlo y ejecutarlo luego de descargarlo lo que hicimos fue crear un nuevo replit, y abrir los 3 puntos al lado de Files para seleccionar la opción **Show hidden files**, con la opción activada, borramos los archivos **main.c** y **main**. Ahora apretamos los mismos 3 puntos de antes y ponemos **Upload folder**, seleccionamos la carpeta de Tarea-2-EDD, y cuando se suba, abrimos la carpeta y apretamos el archivo **main**, cuando cargue, basta con apretar el botón verde de **Run** de arriba y el código ya se ejecuta. 


===== 2 - LO QUE FUNCIONA Y LO QUE NO =====
  
Todo funciona correctamente, como es esperado, si se necesita un bitácora podría comentar que se necesito un cambio a grandes rasgos de los TDA's a la hora de crear al función deshacer, a pesar de la dificultad, no hubieron inconvenientes :).

PD: Se nos olvido hacer commits pero deberiamos tener minimo 7 cada uno, principalmente porque la implentación a GitHub fue posterior a la creación del replit, así que la versión actual es una copia, cuando 5/9 funciones ya estaban creadas y funcionando. 

===== 3 - HERRAMIENTAS UTILIZADAS =====

Las herramientas usadas en esencia fueron:

- Replit [https://replit.com/] : Se logró el trabajo en equipo mediante replit, donde pudimos analizar y cambiar grupalmente el código.
- GitHub [https://github.com] : Creamos el repositorio y lo vinculamos a replit, asi teniendo exitosamente un lugar para ver todos los commits y cambios realizados en todos los aspectos de la tarea, como el "main.c", "list_answer.c", "list.h", "map.c/h" y "stack.h", los ".csv" y el README.

===== 4 - COEVALUACIÓN DEL TRABAJO EN EQUIPO =====

Aspectos a mejorar: Mejorar los horarios de comunicación entre los integrantes, cada uno tubo su aporte esta vez, pero hubieron deficiencias en la comunicación del trabajo a la hora de avanzar.

Grupo = Clippers
  Participación activa y equitativa = 20
  Resolución de conflictos = 20
  Colaboración = 20
  Responsabilidad = 20
  Comunicación = 15
  Pje Total = 95
----------------------------------------
  
===== 5 - COEVALUACIÓN DEL APORTE INDIVIDUAL =====

Aspectos positivos: Organización, comunicación, disposición, se preocupa por la estabilidad de sus compañeros.

A mejorar: Manejo de conocimientos, mayor participación activa en los trabajos.

Estudiante: Francisca Abarca
  Participación = 15
  Responsabilidad = 20
  Comunicación = 20
  Calidad del Trabajo = 20
  Trabajo en Equipo = 20
  Pje Total = 95
------------------------------

Aspectos positivos: Cooperativo, escuchar a los demás y aceptar sus opiniones. Ayudar a explicar materia. 

A mejorar: Manejo de conocimientos, mayor concentración en las clases y ser mas participativo/comunicativo.

Estudiante: Vicente Arratia
  Participación = 20
  Responsabilidad = 20
  Comunicación = 20
  Calidad del Trabajo = 20
  Trabajo en Equipo = 20
  Pje Total = 100
------------------------------

Aspectos positivos: Preocupación en tanto a los trabajos grupales, bueno escuchando y comprendiendo las deficiencias en tanto al trabajo.

A mejorar: Ser mas participativo, prepararse mejor para las clases. Una comunicación más pausiva bajo estrés, para lograr una comunicación eficiente.

Estudiante: Vicente Mediano
  Participación = 15
  Responsabilidad = 20
  Comunicación = 20
  Calidad del Trabajo = 20
  Trabajo en Equipo = 20
  Pje Total = 95
------------------------------

Aspectos positivos: Buen lider, maneja bien los conocimientos y es atento con las inquitudes del equipo. Se dió a la oportunidad de la colaboración grupal.

A mejorar: Comprensión, comunicación bajo desafíos.

Estudiante: Javier Sepúlveda
  Participación = 20
  Responsabilidad = 20
  Comunicación = 15
  Calidad del Trabajo = 20
  Trabajo en Equipo = 20
  Pje Total = 95
------------------------------

===== 6 - ANALISIS DEL CÓDIGO =====
Usaremos la siguiente estructura

````c
typedef struct Jugador {
  char nombre[32];
  int puntosH;
  Map* items;
  int contadorItems;
} Jugador;

typedef enum Accion {
  AGREGAR_ITEM,
  ELIMINAR_ITEM,
  AUMENTAR_PH
} Accion;

typedef struct Pila {
  char nombre[32];
  Accion accion;
  char item[32];
  int puntosH;
} Pila;
````

Primordialmente para entender la funciones, es necesario entender el **main**, para ello se crea un mapa para todos los jugadores, que incluirá a cada jugador de manera independiente dentro del mapa con su struct correspondiente.
Luego de eso, presentamos el menú de bienvenida, para realizar cada opción que desee el usuario, usamos variables como 'opcion' y 'titulo' para saber las opciones a elegir del usuario, además de poseer sus restricciones correspondientes para no generar errores, implementamos cada función con un ciclo switch asignando así a cada caso su función correspondiente, y la ultima opcion termina el programa


En la primera función **crearPerfil** que recibe un mapa, se creara la variable para guardar un nuevo jugador tipo 'Jugador', y realizamos la reserva de memoria, para posteriormente inicalizar los puntos de cada jugador en 0 y crear otro mapa dentro de los item donde usamos la funcion 'is_equal_string' para comparar y que no se repitan estos, y luego inicializamos el contador de items en 0, luego se le solicita al usuario el nombre del jugador a ingresar, se copia el nombre ingresado al nombre del nuevoJugador y se inserta el nuevoJugador con sus variables inicializadas dentro del mapa. Finalmente se le hace saber al usuario que el jugador quedó registrado.


En la función **mostrarPerfil** que recibe un mapa, se le pregunta al usuario el nombre del perfil a buscar para posteriormente realizar dicha acción, en caso de encontrar al jugador se imprimirán los datos guardado de dicho jugador y se implementará un contador para recorrer el mapa de los items almacenados en dicho jugador, en caso contrario, se retorna 'NULL' y se  finalizará la ejecución de la función.


La función **agregarItem** que recibe el mapa y una pila, al principio se le solicita al usuario el nombre dle jugador al cual se le desea agregar el item, con la función 'searchMap' se verifica si el usuario efectivamente existe, si retorna 'NULL' se finaliza la función y se le hace saber al usuario, de encontrarlo se le solicita al usuario el nombre del item a agregar al jugador, se realiza una reserva de memoria a la pila y se guarda dentro de la pila "stack" los datos copiados a la variable registro de tipo pila, indicando el tipo de acción que se está realizando.


En la función **eliminarItem** recibe el mapa y la pila, se le pregunta al usuario el nombre del jugador al que se desea eliminar el item. En caso de que el jugador no existe retorna 'NULL', sino, se soicita el nombre de item a eliminar y se creará un auxiliar para recorrer el mapa de los items, en caso de que el item ingresado lo tenga el jugador en su inventario se procederá a la eliminación del item señalado y se terminará la iteración. Si aux salió de la iteración como NULL el item no existía en el inventario del jugador. Se guarda la información guardada en registro para luego guardarla en la pila, se hace reserva de memoria, donde lo importante es la acción que se está realizando y se le hace saber al usuario.

En la función **agregarPuntos**, que recibe el mapa y la pila, se le solicita al usuario el nombre del jugador al cual se le agregarán los puntos deseados, posteriormente se usa 'searchMap' para recorren el mapa, si el jugador buscado arroja 'NULL' se le hace saber al usuario que el jugador no existe, de lo contrario se usa una variable `int` conocida como 'puntaje' para ingresar la cantidad de puntaje y lo guardaremos, se usara un registro de la pila (almacenando memoria) donde buscara el nombre y con la acción `AUMENTAR_PH` se aumentará el puntaje y se le asigna dicho puntaje dentro de la pila y se le hace saber al usuario que le puntaje fue almacenado correctamente.

En la funcion **mostrarJugadoresEspecifico**, la cual recibe un mapa, se ingresa el nombre del item que deseamos encontrar en los inventarios de los jugadores, y recorremos el mapa buscando el item que ingreso el usuario, finalmente imprimiendo el item y todos los jugadores que lo tienen.


La funcion **deshacerAccion** la cual recibe un mapa y una pila, se ingresa el nombre del jugador al que se le desea deshacer la ultima accion, se busca al jugador en el mapa y si no se encuentra se entrega un mensaje y se termina la ejecucion de la funcion. Se recorre la pila y se revisa cual fue la ultima accion (la cual es una variable que se guardaba al final de cada funcion) y dependiendo del caso, se borra el mapa de los items, se inserta el item de nuevo en el mapa u se eliminan los puntos que se le añadieron al jugador.


La funcion void **exportarArchivo** exporta datos de una lista de jugadores en un archivo ".csv". Primero, se pide al usuario que ingrese el nombre del archivo al que se exportarán los datos, y luego se abre el archivo en modo de escritura, asignandole la variable "archExportar" y se imprime un mensaje para decirle al usuario que el archivo se ha exportado con exito. Se recorre el mapa, escribiendo el nombre del jugador, sus puntos de habilidad, la cantidad de items que tiene en su inventario y los items que estan en este y finalmente se termina la ejecucion de la funcion y se cierra el archivo.


La funcion void **importarArchivo** permite importar datos de un archivo ".csv" para guardarlos en el mapa. Para eso, solicita el nombre del archivo que se desea importar y lo abre en modo lectura, si no se puede abrir, la funcion mostrara un mensaje de error y terminara la ejecucion. A continuacion, la funcion creara a un Jugador reservando memoria e inicializando valores para luego ir copiando los que estan en el ".csv". Finalmente se termina la ejecucion de la funcion y se cierra el archivo.

De este modo el código a lo largo de la construcción e implementación de TDA's fue un proceso y ánalisis de cada ejecución que procesaba el Replit.