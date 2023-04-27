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


/*
  función para comparar claves de tipo string
  retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

/*
  función para comparar claves de tipo string
  retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
    if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

void crearPerfil(Map* mapa) {
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

  strcpy(nuevoJugador->nombre,nombre);
  insertMap(mapa, nuevoJugador->nombre, nuevoJugador);
  
  printf("Se ha creado correctamente el perfil del jugador %s\n\n",nuevoJugador->nombre);
}

void mostrarPerfil(Map* mapa) {
  getchar();
  
  char buscado[32];
  printf("Ingrese nombre del perfil a buscar\n");
  scanf("%30[^\n]s",buscado);
  getchar();
  
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
    
    char* aux = firstMap(jugadorBuscado->items);
    
    while(aux != NULL) {
      printf("  %i-%s\n",contador,aux);
      
      aux = nextMap(jugadorBuscado->items);
      contador++;
     }
    if (contador  == 1) {
      printf("El jugador no ha conseguido items hasta el momento\n\n");
    }
  }
}

void agregarItem(Map* mapa, Stack* stack) {
  getchar();
  char buscado[32];
  printf("Ingrese nombre del jugador al que desea agregar un item:\n");
  scanf("%30[^\n]s",buscado);
  getchar();
  
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
  printf("Ingrese nombre del jugador al que desea eliminar un item:\n");
  scanf("%30[^\n]s",buscado);
  getchar();
  
  Jugador * jugadorBuscado = searchMap(mapa, buscado);
  if (jugadorBuscado == NULL) {
    printf("El jugador indicado no existe!\n"); 
    return;
  }
  
  char item[32];
  printf("Ingrese el nombre del item a eliminar:\n");
  scanf("%30[^\n]s",item);
  getchar();

  void* aux = firstMap(jugadorBuscado->items);

  while(aux != NULL) {
    if (strcmp(aux,item) == 0) {
      eraseMap(jugadorBuscado->items, item);
      break;
    }
    aux = nextMap(jugadorBuscado->items);
  }
  if(aux == NULL) {
    printf("El item indicado no existe en el inventario del Jugador %s\n",jugadorBuscado->nombre);
    return;
  } else {
    Pila* registro = (Pila*) malloc(sizeof(Pila));
    strcpy(registro->nombre, buscado);
    registro->accion = ELIMINAR_ITEM; 
    strcpy(registro->item, item);
    
    stack_push(stack, registro);
    jugadorBuscado->contadorItems--;
    printf("Item '%s' eliminado con exito!\n\n", item);
  }
  
}
void agregarPuntos(Map* mapa, Stack* stack) {
  getchar();
  char buscado[32];
  printf("Ingrese nombre del jugador al que desea agregarle los puntos:\n");
  scanf("%30[^\n]s",buscado);
  getchar();
  Jugador * jugadorBuscado = searchMap(mapa, buscado);
  if (jugadorBuscado == NULL) {
    printf("El jugador indicado no existe!\n"); 
    return;
  }

  int puntaje = 0;
  printf("Ingrese el puntaje a agregar:\n");
  scanf("%i", &puntaje);
  jugadorBuscado->puntosH = puntaje;

  Pila* registro = (Pila*) malloc(sizeof(Pila));
  strcpy(registro->nombre, buscado);
  registro->accion = AUMENTAR_PH; 
  registro->puntosH = puntaje;
  
  stack_push(stack, registro);
  printf("Se ha agregado el puntaje '%i' al jugador '%s'\n\n", puntaje, jugadorBuscado->nombre);
}

void mostrarJugadoresEspecifico(Map* mapa) {
  getchar();
  char item[32];
  printf("Ingrese el nombre del item a buscar\n");
  scanf("%30[^\n]s",item);
  getchar();
  
  int encontrarItem = 0;
  printf("\n === Perfil de los jugadores con el item %s === \n", item);
  Jugador * aux = firstMap(mapa);
  while (aux != NULL) {
    char* aux2 = firstMap(aux->items);
    while(aux2 != NULL) {
      if (strcmp(aux2,item) == 0) {
        encontrarItem++;
        printf("Nombre: %s\n", aux->nombre);
        printf("Item: %s\n", item);
        printf("\n");
      }
      aux2 = nextMap(aux->items);
    }
    aux = nextMap(mapa);
  }
  
  if (encontrarItem == 0) {
    printf("Ningún jugador tiene el item '%s'\n", item);
  } 
}

void deshacerAccion(Map* mapa, Stack* stack) {
  getchar();
  char buscado[32];
  printf("Ingrese nombre del jugador al que desea deshacer la última accion:\n");
  scanf("%30[^\n]s",buscado);
  getchar();

  Jugador * jugadorBuscado = searchMap(mapa, buscado);
  if (jugadorBuscado == NULL) {
    printf("El jugador indicado no existe!\n"); 
    return;
  }
  int encontrado = 0;
  Pila* aux;
  
  while(stack_top(stack) != NULL) {
    aux = stack_pop(stack);
    if (strcmp(aux->nombre,buscado) == 0) {
      encontrado++;
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
  FILE* archExportar;
  char nombreArchivo[100];
  printf("Ingrese el nombre del archivo al cual se exportará en formato .csv\n");
  scanf("%s", nombreArchivo);
  
  archExportar = fopen(nombreArchivo, "a");
  printf("Se han exportado los datos al archivo %s\n",nombreArchivo);

  if (!archExportar) {
    printf("Error: no se pudo abrir el archivo\n");
    return;
  }
  Jugador* auxMapa = firstMap(mapa);
 
  while(auxMapa != NULL) {
    char* auxItem = firstMap(auxMapa->items);
    fprintf(archExportar, "%s,", auxMapa->nombre);
    fprintf(archExportar, "%d", auxMapa->puntosH);
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
  FILE* archImportar;
  char nombreArchivo[100];
  printf("Ingrese el nombre del archivo del cual desea importar jugadores en formato .csv\n");
  scanf("%s", nombreArchivo);
  
  archImportar = fopen(nombreArchivo, "r");
  printf("Se han importado los datos al archivo %s\n",nombreArchivo);
  if (!archImportar) {
    printf("Error: no se pudo abrir el archivo\n");
    return;
  }

  char linea[1024];
  fgets(linea,1024,archImportar);
  
  while (fgets(linea,1024,archImportar)){
    Jugador* jugador = NULL;
    jugador = (Jugador*) malloc(sizeof(Jugador));
    //strcpy(jugador->nombre, nombre);
    jugador->puntosH = 0;
    jugador->items = createMap(is_equal_string);
    

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