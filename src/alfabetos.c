#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "alfabetos.h"
#include "experimentos.h"

char binario_rand(){
  return drand48() < 0.5 ? '0' : '1';
}

char adnsintetico_rand(){
  double r = drand48();

  if(r < 0.25) return 'A';
  else if (r < 0.5) return 'T';
  else if (r < 0.75) return 'G';
  else return 'C';
}

char lengsintetico_rand(){
  long largo = (long)('z'-'a'+1);
  long rand = intrand(2*largo + 2);

  if(rand < largo) return (char)rand + 'A';
  else if(rand < 2*largo) return (char)(rand % largo)  + 'a';
  
  return ' ';
}

/******************************/

char *alfabeto_rand(char (*randomcharfunction)(void)){
  const int tamano = UNMEGAENCHARS; /* 1 MB */
  int k;

  char *result = (char*)malloc((tamano + 1)*sizeof(char));

  for(k=0; k<tamano; k++)
    result[k] = randomcharfunction();

  result[k] = 0;
  return result;
}

char *patron_rand(int potenciade2, char (*randomcharfunction)(void)){
  int tamano, k;
  char *result;

  tamano = 2 << (potenciade2 - 1);
  result = (char*)malloc((tamano+1)*sizeof(char));

  for(k=0; k<tamano; k++)
    result[k] = randomcharfunction();

  result[k] = 0;
  return result;
}

char *patron_text(int potenciade2, char *texto, int txtlen){
  int tamano;
  int rnd;

  char *result;

  tamano = 2 << (potenciade2 -1);
  result = (char*)malloc((tamano+1)*sizeof(char));
  if(result==NULL){
    printf("no hay memoria..\n");
    exit(-1);
  }

  rnd = intrand(txtlen - tamano);
  memcpy(result, texto + rnd, tamano);
  result[tamano] = 0;

  return result;
}


char *alfabeto_file(char *fileloc, long nbytes, int (*allowchar)(char), int separar){
  FILE *f;
  char *result;
  char *buffer;
  int resultindex, bufferindex;
  long filesize, patronstart;
  int enespacio;

  // para preprocesamiento obtenemos un texto del doble pedido, lo preprocesamos
  // y finalmente lo cortamos a 1MB. Si no es suficiente, repetimos.
  
  f = fopen(fileloc, "rb");

  if(f==NULL){
    fprintf(stderr, "FILE %s not found\n", fileloc);
    exit(-1);
  }

  buffer = (char*)malloc((2*nbytes + 1)*sizeof(char));
  result = (char*)malloc((nbytes + 1)*sizeof(char));
  fseek(f, 0, SEEK_END);
  filesize = ftell(f);

  patronstart = intrand(filesize - 2*nbytes);
  fseek(f, patronstart, SEEK_SET);

  fread(buffer, sizeof(char), 2*nbytes, f);
  buffer[2*nbytes] = 0;
  fclose(f);

  resultindex = 0;
  enespacio=0;

  if(allowchar == NULL){
    free(result);
    return buffer;
  }

  for(bufferindex=0; buffer[bufferindex] != 0 && resultindex < nbytes; bufferindex++){
    if(allowchar(buffer[bufferindex])){
      result[resultindex] = buffer[bufferindex];
      enespacio=0;
      resultindex++;
    } else {
      if(separar){
	if(enespacio) continue;
	enespacio=1;
	result[resultindex] = SEPARADOR;
	resultindex++;
      }
    }
  }
  free(buffer);
  result[resultindex] = 0;
  
  return result;
}


/************************Funciones de postprocesamiento*/
int onlyATGC(char c){
  return c=='A' || c=='T' || c=='G' || c=='C';
}


int onlyEnglish(char c){
  return ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z');
}



/*************************/


long intrand(long max){
  return (long)(drand48() * max);
}


double elapsed_time(struct timeval *a, struct timeval *b){
    return
      (double)(a->tv_sec + (double)a->tv_usec/1000000) -
      (double)(b->tv_sec + (double)b->tv_usec/1000000);
}
