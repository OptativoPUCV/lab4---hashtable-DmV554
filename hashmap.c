#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long pos = hash(key, map->capacity);
    Pair ** buckets = map->buckets;
    int i = 0;
    // Buscamos una casilla disponible
    while (buckets[pos] != NULL && buckets[pos]->key != NULL && strcmp(buckets[pos]->key, key) != 0 && i < map->capacity) {
        pos = (pos + 1) % map->capacity;
        i++;
    }
    // Si la casilla ya existe, actualizamos su valor
    if (buckets[pos] != NULL && strcmp(buckets[pos]->key, key) == 0) {
        buckets[pos]->value = value;
    } else {
        // Si encontramos una casilla disponible, insertamos el nuevo par
        if (buckets[pos] == NULL || buckets[pos]->key == NULL) {
            buckets[pos] = malloc(sizeof(Pair));
            buckets[pos]->key = key;
            map->size++;
        } else { // Si llegamos al límite de resolución de colisiones sin encontrar una casilla disponible, redimensionamos la tabla
            resize(map);
            insertMap(map, key, value);
            return;
        }
        // Actualizamos el valor del par
        buckets[pos]->value = value;
        // Actualizamos el índice current
        map->current = pos;
    }
}


void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
  HashMap *mapa = malloc(sizeof(HashMap));
  mapa->buckets = calloc(capacity, sizeof(Pair*));
  mapa->capacity = capacity;
  mapa->size = 0;
  mapa->current = -1;
    return mapa;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   


    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
