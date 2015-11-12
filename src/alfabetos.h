#ifndef __ALFABETOS__H__
#define __ALFABETOS__H__

#define SEPARADOR ' '

char binario_rand();
char adnsintetico_rand();
char lengsintetico_rand();
char *alfabeto_rand(char (*randomcharfunction)(void));
char *alfabeto_file(char *fileloc, long nbytes, int (*allowchar)(char), int separar);
char *patron_rand(int potenciade2, char (*randomcharfunction)(void));
char *patron_text(int potenciade2, char *texto, int txtlen);

long intrand(long max); /* genera un random en [0, max) */

double elapsed_time(struct timeval *a, struct timeval *b);

/* estas funciones son BOOLEANAS */
int onlyATGC(char c);
int onlyEnglish(char c);


#endif
