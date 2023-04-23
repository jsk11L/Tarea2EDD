#include "Map.h"
#include "list.h"
#include "stack.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Jugador {
  char nombre[32];
  int puntosH;
  List* items;

} Jugador;

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
  nuevoJugador->items = createList();
  Stack* stack = stack_create();
  
  
  char nombre[32];

  getchar();

  printf("Ingrese el nombre del Jugador:\n");
  scanf("%30[^\n]s", nombre);
  getchar();

  strcpy(nuevoJugador->nombre,nombre);
  
  stack_push(stack,nuevoJugador);
  insertMap(mapa, nuevoJugador->nombre, nuevoJugador);

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
    
    void* aux = firstList(jugadorBuscado->items);
    
    while(aux != NULL) {
      printf("%i-%s\n",contador,(char*)aux);
        aux = nextList(jugadorBuscado->items);
        contador++;
    }
    
    if (aux == NULL) {
      printf("El jugador no ha conseguido items hasta el momento\n\n");
    }
  }
  
}

void agregarItem(Map* mapa) {
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
    pushBack(jugadorBuscado->items, strdup(item));
    
    printf("Se ha agregado el item '%s' al inventario del jugador '%s'\n", item, jugadorBuscado->nombre);
  }
}


void eliminarItem(Map* mapa) {
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

  void* aux = firstList(jugadorBuscado->items);

  
  
  
  
}

void agregarPuntos(Map* mapa) {
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
  printf("Ingrese el nombre del item a agregar:\n");
  scanf("%i", &puntaje);
  jugadorBuscado->puntosH = puntaje;
  printf("Se ha agregado el puntaje '%i' al jugador '%s'\n", puntaje, jugadorBuscado->nombre);
}

void mostrarJugadoresEspecifico(Map* mapa) {}

void deshacerAccion(Map* mapa) {}

void exportarArchivo(Map* mapa) {}

void importarArchivo(Map* mapa) {}


int main() {
  Map* mapaJugador = createMap(is_equal_string);
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
        agregarItem(mapaJugador);
        break;
      case 4:
        eliminarItem(mapaJugador);
        break;
      case 5:
        agregarPuntos(mapaJugador);
        break;
      case 6:
        //mostrarJugadoresEspecifico(mapaJugador);
        printf("Funcion no implementada, no vuelva nunca!\n");
        //break;
      case 7:
        //deshacerAccion(mapaJugador);
        printf("Funcion no implementada, no vuelva nunca!\n");
        //break;
      case 8:
        //exportarArchivo(mapaJugador);
        printf("Funcion no implementada, no vuelva nunca!\n");
        //break;
      case 9:
        //importarArchivo(mapaJugador);
        printf("Funcion no implementada, no vuelva nunca!\n");
        //break;
      case 10:
        printf("Cerrando el programa...\n");
        printf("hola");
      return 0;
        
    }

  }

  return 0;
}