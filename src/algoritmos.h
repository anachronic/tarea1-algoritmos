#include <string.h>
#include <stdlib.h>

#ifndef __ALGORITMOS__H__
#define __ALGORITMOS__H__

#include "resultados.h"

#define NOT_FOUND -1;
#define TAMANO_ALFABETO 256

void fzabruta(char *patron, char *texto, struct resultado *result);
void kmp(char *patron, char *texto, int textoLen, struct resultado *result);
void bmh(char *patron, char *texto, int textoLen, struct resultado *result);


#endif
