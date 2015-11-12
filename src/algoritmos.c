#include <stdio.h>

#include "algoritmos.h"


void fzabruta(char *patron, char *texto, struct resultado *result){
  int found=0;
  int start=0;
  
  char *p, *t, *t2;

  resultadoNew(result);
  
  for(t=texto; *t != 0; t=t+1, ++start){
    t2=t;
    for(p=patron; *p != 0; p=p+1){
      result->comparaciones++;
      if(*p == *t2){
	t2=t2+1;
	if(*(p+1) == 0){
	  found = 1;
	  break;
	}
      } else break;
    }
    if(found){
      found=0;
      //      resultadoAdd(result, start);
    }
  }
}

static void preprocesarPatron(char* patron, int* next){
  int j, i;

  char *p=patron;
  j=1;
  next[0] = 0;

  while(*(p+1)){
    i = next[j-1];
    while(i>0 && patron[i]!=patron[j]) i=next[i-1];
    if(patron[i] == patron[j]) next[j]=i+1;
    else next[j] = 0;
    j++;
    p++;
  }
}


void kmp(char *patron, char *texto, int textoSize, struct resultado *result){
  int k=0;
  int j=0;
  int m=strlen(patron);
  int *fracaso;

  resultadoNew(result);

  fracaso = (int*)malloc(m*sizeof(int));
  preprocesarPatron(patron, fracaso);

  while (k<textoSize){
    while (j>0 && texto[k]!=patron[j]){
      j=fracaso[j-1];
      result->comparaciones++; // cada parte del ciclo
    }
    if(j>0)result->comparaciones++; // la ultima iteracion del ciclo tb compara
    result->comparaciones++; //cada if -> 1 comparacion
    if (texto[k]==patron[j]) j++;
    k++;
    if(j==m){
      //      resultadoAdd(result, k-j);
      j=fracaso[j-1];
    }
  }

  free(fracaso);
}



void bmh(char *patron, char *texto, int textoLen, struct resultado *result){
  int patronlen, k, j, indice;
  int salto[TAMANO_ALFABETO];

  patronlen = strlen(patron);

  /* calculamos la funcion de salto */
  for(k=0; k<TAMANO_ALFABETO; k++) salto[k]=0;
  for(k=0; k < patronlen - 1; k++) salto[(int)patron[k]] = k;

  resultadoNew(result);

  if(patron == NULL || *patron == 0){
    printf("patron es null\n");
    return;
  }
  
  /* en adelante k recorre el patron y j el texto */
  for(k=patronlen-1, j=patronlen-1; j<textoLen;){
    indice = j + k + 1 - patronlen;
    result->comparaciones++;
    if(texto[indice] == patron[k]) k--;
    else {
      j += patronlen - salto[(int)texto[j]] - 1;
      k = patronlen - 1;
    }
    if(k==0){
      //      resultadoAdd(result, j - patronlen + 1);
      j += patronlen - salto[(int)texto[j]] - 1;
      k = patronlen - 1;
      //      return;
    }
  }
}
