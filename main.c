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
  
  
  
  char nombre[32];

  getchar();

  printf("Ingrese el nombre del Jugador:\n");
  scanf("%30[^\n]s", nombre);
  getchar();

  strcpy(nuevoJugador->nombre,nombre);
  insertMap(mapa, nuevoJugador->nombre, nuevoJugador);
  
  printf("Se ha creado correctamente el perfil del jugador %s\n",nuevoJugador->nombre);
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

    int contador = 1;
    
    char* aux = firstMap(jugadorBuscado->items);
    
    while(aux != NULL) {
      printf("  %i-%s\n",contador,aux);
      
      aux = nextMap(jugadorBuscado->items);
      contador++;
     }
    if (contador  == 1) {
      printf("El jugador no ha conseguido items hasta el momento\n");
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
    
    Pila* registro = (Pila *) malloc(sizeof(Pila));
    strcpy(registro->nombre, buscado);
    registro->accion = AGREGAR_ITEM;
    strcpy(registro->item, strdup(item));
    
    
    insertMap(jugadorBuscado->items, strdup(item), strdup(item));
    stack_push(stack, registro);
    
    printf("Se ha agregado el item '%s' al inventario del jugador '%s'\n", item, jugadorBuscado->nombre);
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
  //freddy fasbear
  if(aux == NULL) {
    printf("El item indicado no existe en el inventario del Jugador %s\n",jugadorBuscado->nombre);
    return;
  } else {
    Pila* registro = (Pila*) malloc(sizeof(Pila));
    strcpy(registro->nombre, buscado);
    registro->accion = ELIMINAR_ITEM; 
    strcpy(registro->item, item);
    
    stack_push(stack, registro);
    printf("Item '%s' eliminado con exito!\n", item);
  }
  
}
//i dunno i was thinking
void agregarPuntos(Map* mapa, Stack* stack) {
  getchar();
  char buscado[32];
  printf("Ingrese nombre del jugador al que desea agregarle los puntos:\n");
  scanf("%30[^\n]s",buscado);
  getchar();
// leaving my child behind
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
  printf("Se ha agregado el puntaje '%i' al jugador '%s'\n", puntaje, jugadorBuscado->nombre);
}

void mostrarJugadoresEspecifico(Map* mapa) {
  getchar();
  char item[32];
  printf("Ingrese el nombre del item a buscar\n");
  scanf("%30[^\n]s",item);
  getchar();
  printf("%s\n", item);
  int encontrarItem = 0;

  Jugador * aux = firstMap(mapa);
  while (aux != NULL) {
    char* aux2 = firstMap(aux->items);
    while(aux2 != NULL) {
      if (strcmp(aux2,item) == 0) {
        encontrarItem++;
        printf("\n === PERFIL DEL JUGADOR === \n");
        printf("Nombre: %s\n", aux->nombre);
        printf("Item: %s\n", item);
      }
      aux2 = nextMap(aux->items);
    }
    aux = nextMap(mapa);
  }
  
  if (!encontrarItem) {
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

  Pila* aux;
  
  while(stack_top(stack) != NULL) {
    aux = stack_pop(stack);
    if (strcmp(aux->nombre,buscado) == 0) {
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
  printf("Se ha deshecho correctamente la última acción del jugador %s\n", jugadorBuscado->nombre);
  
}

void exportarArchivo(Map* mapa) {}

void importarArchivo(Map* mapa) {}


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
        //exportarArchivo(mapaJugador);
        printf("Funcion no implementada, comeback soon and come in!\n");
        //break;
      case 9:
        //importarArchivo(mapaJugador);
        printf("Funcion no implementada, comeback soon and come in!\n");
        //break;
      case 10:
        printf("Cerrando el programa...\n");
      return 0;
        
    }

  }

  return 0;
}