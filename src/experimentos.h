#ifndef __EXPERIMENTOS__H__
#define __EXPERIMENTOS__H__

#define UNMEGAENCHARS 1000000
#define MIN_ITERACIONES 100
#define Z_INTERVALO 1.96 /* 1.96 para 95% de confianza y 2.575 para 99% */
#define MAX_ERROR 5.0 /*Z_INVTERVALO==1.96 => MAX_ERROR==5.0, Z_INTERVALO==2.575 => MAX_ERROR==1.0*/


#define ALGORITMO_FB  0
#define ALGORITMO_KMP 1
#define ALGORITMO_BMH 2

#define CANT_ALGORITMOS 3

void alfabeto_binario_exp(char *nombre, FILE* fbf, FILE* fkmp, FILE* fbmh);
void adn_real_exp(char *nombre, FILE* fbf, FILE* fkmp, FILE* fbmh, char *filename);
void adn_sintetico_exp(char *nombre, FILE* fbf, FILE* fkmp, FILE* fbmh);
void lenguaje_real_exp(char *nombre, FILE* fbf, FILE* fkmp, FILE* fbmh, char *filename);
void lenguaje_sintetico_exp(char *nombre, FILE* fbf, FILE* fkmp, FILE* fbmh);

#endif
