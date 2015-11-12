#include <stdlib.h>
#include <stdio.h>

#include "resultados.h"


void resultadoNew(struct resultado *r){
  r->n = 0;
  r->allocLen = 4;
  r->posiciones = (int*)malloc(r->allocLen * sizeof(int));

  if(r->posiciones == NULL){
    printf("no hay mas memoria disponible\n");
  }
  r->comparaciones = 0;
  //printf("new resultado\n");
}

void resultadoAdd(struct resultado *r, int result){
  if (r->n == r->allocLen){
    r->posiciones = (int*)realloc(r->posiciones, 2*r->allocLen*sizeof(int));
    if(r->posiciones == NULL){
      fprintf(stderr, "no hay mas memoria disponible. :(\n");
      exit(-1);
    }
    r->allocLen = 2*r->allocLen;
  }

  r->posiciones[r->n] = result;
  r->n++;
}

void resultadoFree(struct resultado *r){
  if(r->posiciones != NULL){
    free(r->posiciones);
  }
  //printf("bye resultado\n");
}

void estadisticaNew(struct estadistica_comparaciones *ec){
  ec->valores = (unsigned long long *)malloc(ESTADISTICA_PREALLOC*sizeof(unsigned long long));
  if(ec->valores==NULL) exit(-1);
  ec->n=0;
  ec->allocLen = ESTADISTICA_PREALLOC;
}

void estadisticaAdd(struct estadistica_comparaciones *ec, unsigned long long valor){
  if(ec->n==ec->allocLen){
    ec->valores = (unsigned long long *)realloc(ec->valores,2*ec->allocLen*sizeof(unsigned long long));
    if(ec->valores==NULL) exit(-1);
    ec->allocLen = 2*ec->allocLen;
  }
  ec->valores[ec->n] = valor;
  ec->n++;
}


void estadisticaFree(struct estadistica_comparaciones *ec){
  free(ec->valores);
}
