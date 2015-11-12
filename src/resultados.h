

#ifndef __RESULTADOS__H__
#define __RESULTADOS__H__

struct resultado {
  int *posiciones;
  int allocLen;
  int n; //indica el tamano de posiciones
  unsigned long long comparaciones;
};

#define ESTADISTICA_PREALLOC 200

struct estadistica_comparaciones {
  unsigned long long *valores;
  int n;
  int allocLen;
};

void resultadoNew(struct resultado *r);
void resultadoAdd(struct resultado *r, int result);
void resultadoFree(struct resultado *r);

void estadisticaNew(struct estadistica_comparaciones *ec);
void estadisticaAdd(struct estadistica_comparaciones *ec, unsigned long long valor);
void estadisticaFree(struct estadistica_comparaciones *ec);

#endif
