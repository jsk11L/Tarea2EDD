#include "Map.h"
#include <stdlib.h>
#include <assert.h>

typedef struct Node Node;

struct Node {
    void * key;
    /*! Puntero al dato */
    void * data;

    /*! Puntero al siguiente nodo */
    Node * next;

    /*! Puntero al anterior nodo */
    Node * prev;
};

Node* _createNode(void * key, void * data) {
    Node  * new = (Node *)malloc(sizeof(Node));

    assert(new != NULL);

    new->key = key;
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

struct Map {
    /*! Puntero al incio (cabeza) de la lista */
    Node * head;

    /*! Puntero al final (cola) de la lista */
    Node * tail;

    /*! Punteor para poder recorrer la lista */
    Node * current;

    int (*is_equal)(void* key1, void* key2);
    int (*lower_than)(void* key1, void* key2);

};


Map * createMap(int (*is_equal)(void* key1, void* key2)) {
    Map * new = (Map *)malloc(sizeof(Map));
    assert(new != NULL); // No hay memoria para reservar la Mapa.
    new->head = new->tail = new->current = NULL;
    new->is_equal = is_equal;
    new->lower_than = NULL;
    return new;
}

void setSortFunction(Map* map, int (*lower_than)(void* key1, void* key2)){
    map->lower_than = lower_than;
}

void * firstMap(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;

    list->current = list->head;

    return (void *)list->current->data;
}

void * nextMap(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL || list->current == NULL || list->current->next == NULL) return NULL;

    list->current = list->current->next;

    return (void *)list->current->data;
}

void _pushFront(Map * list, void * key, void * value) {
    assert(list != NULL); // list no puede ser NULL.

    Node * new = _createNode(key, value);

    if (list->head == NULL) {
        list->tail = new;
    } else {
        new->next = list->head;
        list->head->prev = new;
    }

    list->head = new;
}


void insertMap(Map * list, void * key, void * value){

    assert(list != NULL); // list no puede ser NULL.

    Node* aux= list->head;

    //se revisa si el elemento existe
    while(aux){
        if(list->is_equal(aux->key,key)) return;
        aux=aux->next;
    }

    if(list->lower_than==NULL) {
        _pushFront (list, key, value);
        return;
    }

    aux= list->head;
    //the minimum element
    if (!aux || list->lower_than(key,aux->key)==1) {      
        _pushFront (list, key, value);
        return;
    }


    while(aux->next && list->lower_than(aux->next->key,key)==1)
        aux=aux->next;
    
    list->current = aux;

    Node* new = _createNode(key, value);

    new->next = list->current->next;
    new->prev = list->current;

    if (list->current->next != NULL) {
        list->current->next->prev = new;
    }

    list->current->next = new;

    if (list->current == list->tail) {
        list->tail = new;
    }

}

void * _popFront(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;

    Node * aux = list->head;

    void * data = (void *)aux->data;

    if (list->head == list->tail) {
        list->tail = list->head = NULL;
    } else {
        list->head = list->head->next;
        list->head->prev = NULL;
    }

    free(aux);


    return data;
}

void * _popBack(Map * list) {
    assert(list != NULL); // list no puede ser NULL.

    if (list->head == NULL) return NULL;

    Node * aux = list->tail;

    void * data = (void *)aux->data;

    if (list->tail == list->head) {
        list->tail = list->head = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    free(aux);


    return data;
}


void* searchMap(Map * list, void * key) {
    assert(list != NULL); // list no puede ser NULL.

    Node* aux= list->head;
    //the minimum element
    while (aux && list->is_equal(key,aux->key)==0) aux=aux->next;

    list->current=aux;
    if (list->head == NULL || list->current == NULL) return NULL;

    return (void *) aux->data;
}

void * eraseMap(Map * list, void * key) {
    assert(list != NULL); // list no puede ser NULL.

    Node* aux= list->head;
    while (aux && list->is_equal(key,aux->key)==0) aux=aux->next;

    list->current=aux;
    if (list->head == NULL || list->current == NULL) return NULL;

    if (list->current == list->head) {
        return _popFront(list);
    } else if (list->current == list->tail) {
        return _popBack(list);
    } else {
        if (aux->next != NULL) {
            aux->next->prev = aux->prev;
        }

        if (aux->prev != NULL) {
            aux->prev->next = aux->next;
        }
    }

    void * data = (void *)aux->data;

    list->current = aux->next;

    free(aux);

    return data;
}


