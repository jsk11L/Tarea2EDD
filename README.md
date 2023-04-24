# Tarea2EDD
hola jajaja

void mostrarJugadoresEspecifico(Map* mapa) {
  getchar();
  char item[32];
  printf("Ingrese el nombre del item a buscar\n");
  scanf("%30[^\n]s",item);
  getchar();
  printf("%s\n", item);
  int foundItem = 0;

  Jugador * aux = firstMap(mapa);
  while (aux != NULL) {
    void* aux2 = firstList(aux->items);
    while(aux2 != NULL) {
      if (strcmp(aux2,item) == 0) {
        foundItem++;
        printf("\n === PERFIL DEL JUGADOR === \n");
        printf("Nombre: %s\n", aux->nombre);
        printf("Item: %s\n", item);
        
      }
      aux2 = nextList(aux->items);
    }
    aux = nextMap(mapa);
  }
  
  if (!foundItem) {
    printf("Ningún jugador tiene el item '%s'\n", item);
  }
  
} Funcion hecha si items es una lista.