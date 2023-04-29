#include "Map.h"
#include "list.h"
#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

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

/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }

    return NULL;
}



void crearPerfil(Map* mapa) {
  //Se inicializan las variables del nuevoJugador junto a la reservación de memoria.
  Jugador* nuevoJugador = NULL;
  nuevoJugador = (Jugador *) malloc(sizeof(Jugador));
  nuevoJugador->puntosH = 0;
  nuevoJugador->items = createMap(is_equal_string);
  nuevoJugador->contadorItems = 0;
  char nombre[32];
  
  getchar();
  printf("Ingrese el nombre del Jugador:\n");
  scanf("%30[^\n]s", nombre);
  getchar();

  //Se copia el nombre ingresado al nombre del nuevoJugador.
  strcpy(nuevoJugador->nombre,nombre);
  //Se inserta el nuevoJugador con sus variables inicializadas dentro del mapa.
  insertMap(mapa, nuevoJugador->nombre, nuevoJugador);
  
  printf("Se ha creado correctamente el perfil del jugador %s\n\n",nuevoJugador->nombre);
}

void mostrarPerfil(Map* mapa) {
  getchar();
  char buscado[32];
  //Se le pregunta al usuario el nombre del perfil a buscar.
  printf("Ingrese nombre del perfil a buscar\n");
  scanf("%30[^\n]s",buscado);
  getchar();

  /*El jugador ingresado se busca dentro del mapa, en caso de encontrarlo se hará impresión
  de todos los datos que contiene el jugador, caso contrario de no encontrarlo se retorna NULL y     
  termina la función. */
  Jugador * jugadorBuscado = searchMap(mapa, buscado);
  if (jugadorBuscado == NULL) {
    printf("El jugador indicado no existe\n"); 
    return;
  } else {
    printf("\n === PERFIL DEL JUGADOR === \n");
    printf("Nombre: %s\n", jugadorBuscado->nombre);
    printf("Puntos de Habilidad: %d\n", jugadorBuscado->puntosH);
    printf("Cantidad de items: %d\n", jugadorBuscado->contadorItems);
    
    int contador = 1;
    
    //Un auxiliar que irá recorriendo el mapa.
    char* aux = firstMap(jugadorBuscado->items);
    
    while(aux != NULL) {
      printf("  %i-%s\n",contador,aux);
      aux = nextMap(jugadorBuscado->items);
      contador++;
     }
    if (contador == 1) {
      printf("El jugador no ha conseguido items hasta el momento\n\n");
    }
  }
}

void agregarItem(Map* mapa, Stack* stack) {
  getchar();
  char buscado[32];
  //Se pregunta al usuario el nombre del jugador al que se deea agregar un item.
  printf("Ingrese nombre del jugador al que desea agregar un item:\n");
  scanf("%30[^\n]s",buscado);
  getchar();

  /*El jugador ingresado por el usuario se ingresa a searchMap para verificar si el jugador se 
  encuentra dentro del mapa, si se retorna NULL el jugador no existe y termina la función, caso 
  contrario se pregunta el nombre del item a agregar. */
  Jugador * jugadorBuscado = searchMap(mapa, buscado);
  if (jugadorBuscado == NULL) {
    printf("El jugador indicado no existe!\n"); 
    return;
  } else {
    char item[32];
    printf("Ingrese el nombre del item a agregar:\n");
    scanf("%30[^\n]s",item);
    getchar();
    jugadorBuscado->contadorItems++;

    /*Se guarda dentro de la pila "stack" los datos copiados a la variable registro de tipo     
    Pila, indicando el tipo de acción que se está realizando. */
    Pila* registro = (Pila *) malloc(sizeof(Pila));
    strcpy(registro->nombre, buscado);
    registro->accion = AGREGAR_ITEM;
    strcpy(registro->item, strdup(item));
    
    
    insertMap(jugadorBuscado->items, strdup(item), strdup(item));
    stack_push(stack, registro);
    
    printf("Se ha agregado el item '%s' al inventario del jugador '%s'\n\n", item, jugadorBuscado->nombre);
  }
}

void eliminarItem(Map* mapa, Stack* stack) {
  getchar();
  
  char buscado[32];
  //Se pregunta al usuario el nombre del jugador al que se desea eliminar el item.
  printf("Ingrese nombre del jugador al que desea eliminar un item:\n");
  scanf("%30[^\n]s",buscado);
  getchar();

  //En caso de que el jugador no exista 
  Jugador * jugadorBuscado = searchMap(mapa, buscado);
  if (jugadorBuscado == NULL) {
    printf("El jugador indicado no existe!\n"); 
    return;
  } else {
    
    char item[32];
    //Se ingresa el nombre del item a eliminar.
    printf("Ingrese el nombre del item a eliminar:\n");
    scanf("%30[^\n]s",item);
    getchar();

    //Se utiliza un aux que recorrerá el mapa.
    void* aux = firstMap(jugadorBuscado->items);

    while(aux != NULL) {
      /*En caso de que el item ingresado lo tenga el jugador en su inventario se procederá a la eliminación del 
      item señalado y se terminará la iteración.*/
      if (strcmp(aux,item) == 0) {
        eraseMap(jugadorBuscado->items, item);
        break;
      }
      aux = nextMap(jugadorBuscado->items);
    }
    //Si aux salió de la iteración como NULL el item no existía en el inventario del jugador.
    if(aux == NULL) {
      printf("El item indicado no existe en el inventario del Jugador %s\n",jugadorBuscado->nombre);
      return;
    } else {
      /*Se guarda la información guardada en registro para luego guardarla en la pila stack, donde lo importante 
      es la acción que se está realizando. */
      Pila* registro = (Pila*) malloc(sizeof(Pila));
      strcpy(registro->nombre, buscado);
      registro->accion = ELIMINAR_ITEM; 
      strcpy(registro->item, item);
      
      stack_push(stack, registro);
      jugadorBuscado->contadorItems--;
      printf("Item '%s' eliminado con exito!\n\n", item);
    }
  }
}
void agregarPuntos(Map* mapa, Stack* stack) {
  getchar();
  char buscado[32];
  //Se pide al usuario ingresar el nombre del jugador que se desea agregar puntos.
  printf("Ingrese nombre del jugador al que desea agregarle los puntos:\n");
  scanf("%30[^\n]s",buscado);
  getchar();
  //Se busca si el jugador existe dentro del mapa. En caso de no existir la función termina.
  Jugador * jugadorBuscado = searchMap(mapa, buscado);
  if (jugadorBuscado == NULL) {
    printf("El jugador indicado no existe!\n"); 
    return;
  } else {
    //Caso contrario se pedirá ingresar el puntaje al jugador.
    int puntaje = 0;
    printf("Ingrese el puntaje a agregar:\n");
    scanf("%i", &puntaje);
    jugadorBuscado->puntosH = puntaje;
    
    /*Se guardan los datos en la variable registro de tipo Pila para luego guardar todos los datos en la pila 
    stack que guardará primordialmente la acción que se está realizando. */
    Pila* registro = (Pila*) malloc(sizeof(Pila));
    strcpy(registro->nombre, buscado);
    registro->accion = AUMENTAR_PH; 
    registro->puntosH = puntaje;
     
    stack_push(stack, registro);
    printf("Se ha agregado el puntaje '%i' al jugador '%s'\n\n", puntaje, jugadorBuscado->nombre);
  }
  
}

void mostrarJugadoresEspecifico(Map* mapa) {
  getchar();
  char item[32];
  //Se le pide al usuario ingresar el item para buscar en todos los jugadores.
  printf("Ingrese el nombre del item a buscar\n");
  scanf("%30[^\n]s",item);
  getchar();
  
  int encontrarItem = 0;
  printf("\n === Perfil de los jugadores con el item %s === \n", item);
  //Se utilizará un auxMapa que comienza en el firstMap, este irá recorriendo el mapa dentro de la iteración.
  Jugador* auxMapa = firstMap(mapa);
  while (auxMapa != NULL) {
    //auxItems se encargará de ir recorriendo el mapa de items que tiene el jugador.
    char* auxItems = firstMap(auxMapa->items);
    while(auxItems != NULL) {
      //En caso de que algún item del inventario del jugador coincida con el ingresado se imprimirá su información.
      if (strcmp(auxItems,item) == 0) {
        encontrarItem++;
        printf("Nombre: %s\n", auxMapa->nombre);
        printf("Item: %s\n", item);
        printf("\n");
      }
      auxItems = nextMap(auxMapa->items);
    }
    auxMapa = nextMap(mapa);
  }
  
  if (encontrarItem == 0) {
    printf("Ningún jugador tiene el item '%s'\n", item);
  } 
}

void deshacerAccion(Map* mapa, Stack* stack) {
  getchar();
  char buscado[32];
  //Se pide ingresar el nombre del jugador que se desea deshacer la úlltima acción.
  printf("Ingrese nombre del jugador al que desea deshacer la última accion:\n");
  scanf("%30[^\n]s",buscado);
  getchar();

  //Se busca el jugador en el mapa, en caso de que retorne NULL la función searchMap finalizará la función.
  Jugador * jugadorBuscado = searchMap(mapa, buscado);
  if (jugadorBuscado == NULL) {
    printf("El jugador indicado no existe!\n"); 
    return;
  }
  int encontrado = 0;
  //Se define "aux" como una variable de tipo Pila para recorrer la pila.
  Pila* aux;
  
  while(stack_top(stack) != NULL) {
    /* Se irá recorriendo la pila y asignandole a aux lo que retorna stack_pop (popFront). De esta forma no se 
    perderán los datos almacenados en la lista disfrazada de pila. */
    aux = stack_pop(stack);
    /* En caso de que el jugador buscado coincida con el del aux se buscará su última acción realizada. */
    if (strcmp(aux->nombre,buscado) == 0) {
      encontrado++;
      //Según que acción sea, se efectuará la eliminación o recuperación del item o la resta de puntos.
      switch(aux->accion) {
        case AGREGAR_ITEM:
          if(searchMap(jugadorBuscado->items,aux->item) != NULL) {
            eraseMap(jugadorBuscado->items, aux->item);
            return;
          }

        case ELIMINAR_ITEM:
          if(searchMap(jugadorBuscado->items, aux->item) == NULL) {
            insertMap(jugadorBuscado->items, strdup(aux->item), strdup(aux->item));
            return;
          }

        case AUMENTAR_PH:
          jugadorBuscado->puntosH -= aux->puntosH;
          return;
      }
    } 
  }
  if (encontrado > 0) {
    printf("Se ha deshecho correctamente la última acción del jugador %s\n\n", jugadorBuscado->nombre);
  } else printf("El jugador no registró ninguna última acción\n\n");
  
  
}

void exportarArchivo(Map* mapa) {
  //Se crea el archivo a exportar.
  FILE* archExportar;
  char nombreArchivo[100];
  //Se pregunta el nombre del archivo al cuál se exportará.
  printf("Ingrese el nombre del archivo al cual se exportará en formato .csv\n");
  scanf("%s", nombreArchivo);

  //Se abre el archivo mediante fopen para la adición de los datos.
  archExportar = fopen(nombreArchivo, "a");
  printf("Se han exportado los datos al archivo %s\n",nombreArchivo);

  if (!archExportar) {
    printf("Error: no se pudo abrir el archivo\n");
    return;
  }
  //Aux mapa se utilizará para ir recorriendo el mapa
  Jugador* auxMapa = firstMap(mapa);
 
  while(auxMapa != NULL) {
    //Aux item se utilizará para recorrer los items del jugador.
    char* auxItem = firstMap(auxMapa->items);
    //Se empieza a escribir dentro del archivo los datos en el formato ".csv".
    fprintf(archExportar, "%s,", auxMapa->nombre);
    fprintf(archExportar, "%d,", auxMapa->puntosH);
    fprintf(archExportar, "%d", auxMapa->contadorItems);
    while(auxItem != NULL) {
      fprintf(archExportar, ",%s", auxItem);
      
      auxItem = nextMap(auxMapa->items);
    }
    fprintf(archExportar, "\n");
    auxMapa = nextMap(mapa);
  }
  fclose(archExportar);
}

void importarArchivo(Map* mapa) {
  //Se crea una variable de tipo FILE para el archivo que se importará.
  FILE* archImportar;
  char nombreArchivo[100];
  //Se pregunta el nombre del archivo que se quiere importar.
  printf("Ingrese el nombre del archivo del cual desea importar jugadores en formato .csv\n");
  scanf("%s", nombreArchivo);

  //Se abre el archivo en modo de lectura.
  archImportar = fopen(nombreArchivo, "r");
  printf("Se han importado los datos al archivo %s\n",nombreArchivo);
  if (!archImportar) {
    printf("Error: no se pudo abrir el archivo\n");
    return;
  }

  char linea[1024];
  //Se consigue la linea para hacer un salto y no tomar en cuenta la primera linea.
  fgets(linea,1024,archImportar);
  
  while (fgets(linea,1024,archImportar)){
    //Mientras la linea contenga información se irá iterando y almacenando a los jugadores.
    Jugador* jugador = NULL;
    jugador = (Jugador*) malloc(sizeof(Jugador));
    jugador->puntosH = 0;
    jugador->items = createMap(is_equal_string);
    
    //Según que retorne la función get_csv_field se irán haciendo las asignaciones de los datos.
    for(int i = 0 ; i < 4 ; i++) {
      char* aux = get_csv_field(linea, i);
      switch(i) {
        case 0:
          strcpy(jugador->nombre, aux);
          break;

        case 1:
          jugador->puntosH = atoi(aux);
          break;

        case 2:
          jugador->contadorItems = atoi(aux);
          break;

        case 3:
          for(int j = 0 ; j < jugador->contadorItems ; j++) {
            char * item = get_csv_field(linea, j+3);
            insertMap(jugador->items, strdup(item), strdup(item));
          }
          break;
        
        default:
          break;
      }
    }
    insertMap(mapa, jugador->nombre, jugador);
  }
  fclose(archImportar);
}


int main() {
  //Se inicializa el mapa de los jugadores y la lista disfrazada de pila.
  Map* mapaJugador = createMap(is_equal_string);
  Stack* stack = stack_create();
  int opcion, titulo = 0;

  while(1) {
    if (titulo == 0) {
      printf("=========================================\n");
      printf(" === BIENVENIDO AL MENÚ DE JUGADORES === \n");
      titulo++;
    }

    printf("=========================================\n");
    printf("Escoja una opción: \n\n");
    printf("1. Crear perfil de jugador/a\n");
    printf("2. Mostrar perfil de jugador/a\n");
    printf("3. Agregar item a jugador/a\n");
    printf("4. Eliminar item de jugador/a\n");
    printf("5. Agregar puntos de habilidad a el/la jugador/a\n");
    printf("6. Mostrar jugador@s con item específico\n");
    printf("7. Deshacer última acción de jugador/a\n");
    printf("8. Exportar datos de jugadores a archivo de texto\n");
    printf("9. Cargar datos de jugadores desde un archivo de texto\n");
    printf("10. Salir del programa\n");
    
    scanf("%d",&opcion);
    while(opcion < 1 || opcion > 10) {
      scanf("%d",&opcion);
    }

    switch(opcion) {
      case 1:
        crearPerfil(mapaJugador);
        break;
      case 2:
        mostrarPerfil(mapaJugador);
        break;
      case 3:
        agregarItem(mapaJugador, stack);
        break;
      case 4:
        eliminarItem(mapaJugador, stack);
        break;
      case 5:
        agregarPuntos(mapaJugador, stack);
        break;
      case 6:
        mostrarJugadoresEspecifico(mapaJugador);
        break;
      case 7:
        deshacerAccion(mapaJugador, stack);
        break;
      case 8:
        exportarArchivo(mapaJugador);
        break;
      case 9:
        importarArchivo(mapaJugador);
        break;
      case 10:
        printf("Cerrando el programa...\n");
      return 0;
        
    }
  }
  return 0;
}