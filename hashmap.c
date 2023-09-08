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
  long i = hash(key, map->capacity);

  Pair* aux = map->buckets[i];
  while(1){
    if ((aux == NULL) || (aux->key==NULL)){
      Pair* Dato = createPair(key, value);
      map->buckets[i]= Dato;
      map->current= i;
      map->size++;
      return;
    }
    
    i=(i+1) % map->capacity;
    
    aux = map->buckets[i];
    
  }
  

  /*if (map->buckets[i] == NULL){
    Pair * newPair = createPair(key, value);
    map->buckets[i] = newPair;
  }
  else{
    map->buckets[i]->value = value;
  }*/

  
  map->current = i;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)
    Pair ** old_buckets = map->buckets;
    map->capacity *=2;
    map->buckets= (Pair **) malloc (sizeof(Pair *) * map->capacity);

}


HashMap * createMap(long capacity) {
  HashMap * Mapa = (HashMap*) malloc (sizeof(HashMap));
  Mapa ->buckets = (Pair**) malloc (sizeof(Pair*)*capacity);

  Mapa->size = 0;
  Mapa->capacity = capacity;
  Mapa->current = -1;

  for(long i=0; i<capacity; i++){
    Mapa->buckets[i] = NULL;
  }

    return Mapa;
}

void eraseMap(HashMap * map,  char * key) { 
  long i = hash(key, map->capacity);
  long contador = 0;

  while( contador < map->capacity){
    if (map->buckets[i] != NULL && is_equal(map->buckets[i]->key, key)){
      map->buckets[i]->key=NULL;

      map->size--;
      return;
    }
    i=(i+1) % map->capacity;
    contador++;
  }


}

Pair * searchMap(HashMap * map,  char * key) { 
  long i = hash(key, map->capacity);
  long contador=0;
   
  while( contador < map->capacity){
    if (map->buckets[i] != NULL && is_equal(map->buckets[i]->key, key)){
      map->current= i;
      return map->buckets[i];
      
    }
    i= (i+1) % map->capacity;
    contador++;
  }


    return NULL;
}

Pair * firstMap(HashMap * map) {
  for (long i =0; i < map->capacity; i++){
    if (map->buckets[i] != NULL && map->buckets[i]->key != NULL){
      
      map->current=i;
      return map->buckets[i];
    }
  }
  

    return NULL;
}

Pair * nextMap(HashMap * map) {
  
  for(long i = map->current +1; i<map->capacity; i++){
    if(map->buckets[i] != NULL && map->buckets[i]->key != NULL){
      
      map->current=i;
      return map->buckets[i];
    }
  }
  

    return NULL;
}
