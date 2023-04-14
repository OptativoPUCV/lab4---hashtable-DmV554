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

   if (map == NULL || key == NULL) {
        return; // Verificar que la tabla y la clave no sean nulas
    }
    if (map->size == map->capacity) {
        return; // Verificar que la tabla no esté llena
    }

    long index = hash(key) % map->capacity; // Calcular la posición del par en la tabla hash
    int i = 0;
    while (i < map->capacity) {
        Pair * bucket = map->buckets[index];
        if (bucket == NULL || bucket->key == NULL) { // Encontrar un bucket vacío
            break;
        } else if (strcmp(bucket->key, key) == 0) { // Verificar que la clave no se repita
            return;
        } else { // Resolver colisión linealmente
            index = (index + 1) % map->capacity;
            i++;
        }
    }

    // Insertar el nuevo par en la posición encontrada
    Pair * newPair = malloc(sizeof(Pair));
    newPair->key = key;
    newPair->value = value;
    map->buckets[index] = newPair;
    map->size++;
    map->current = index;

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
