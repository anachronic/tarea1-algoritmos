#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>

#include "experimentos.h"
#include "alfabetos.h"
#include "resultados.h"
#include "algoritmos.h"

void alfabeto_binario_exp(char *nombre, FILE* fbf, FILE* fkmp, FILE* fbmh){
  struct timeval inicio, fin;
  struct resultado *r;
  FILE *thefile;

  int k = 1, i=0;
  int algoritmo=ALGORITMO_FB;

  double suma = 0.0;
  double sumacuadrados = 0.0;
  double estetiempo;
  long double promedio, stdev, mu_stdev;
  long double error;

  unsigned long long sumac = 0;
  unsigned long long sumacuadradosc = 0;
  long estascomparaciones;
  long double promedioc, stdevc, mu_stdevc;
  long double errorc;

  char *alfabin = alfabeto_rand(binario_rand);
  char *patron = NULL;

  char infoalgoritmo[100];

  int largopatron2 = 2; // en POTENCIAS DE 2

  printf("Iniciando Experimento: %s\n", nombre);

  while(algoritmo < CANT_ALGORITMOS){ //por cada algoritmo
    if(algoritmo == ALGORITMO_FB) sprintf(infoalgoritmo, "Fuerza Bruta");
    else if(algoritmo == ALGORITMO_KMP) sprintf(infoalgoritmo, "Knuth Morris Pratt");
    else if(algoritmo == ALGORITMO_BMH) sprintf(infoalgoritmo, "Boyer Moore Horspool");

    printf("Iniciando iteracion para Algoritmo %s...\n", infoalgoritmo);
    while(1){ // por cada largo del patron
      suma = 0.0;
      sumac = 0;
      promedio = 0.0;
      promedioc = 0;
      sumacuadrados = 0.0;
      sumacuadradosc = 0;
      stdev = stdevc = 0.0;
      mu_stdev = mu_stdevc = 0.0;
      k=0; 
      struct estadistica_comparaciones ec;
      estadisticaNew(&ec);
      while (1){ // calcular el promedio de tiempo de ejecucion con error menor a 5% de la media
	         // con 95% de confianza
	patron = patron_rand(largopatron2, binario_rand);
	r = (struct resultado *)malloc(sizeof(struct resultado));

	if(algoritmo==ALGORITMO_FB){
	  gettimeofday(&inicio, NULL);
	  fzabruta(patron,alfabin,r);
	  gettimeofday(&fin, NULL);
	} else if (algoritmo==ALGORITMO_KMP){
	  gettimeofday(&inicio, NULL);
	  kmp(patron,alfabin,UNMEGAENCHARS,r);
	  gettimeofday(&fin, NULL);
	} else if (algoritmo==ALGORITMO_BMH){
	  gettimeofday(&inicio, NULL);
	  bmh(patron,alfabin,UNMEGAENCHARS,r);
	  gettimeofday(&fin, NULL);
	}
	estetiempo = elapsed_time(&fin, &inicio);
	estascomparaciones = r->comparaciones;

	estadisticaAdd(&ec, estascomparaciones);
	
	suma += estetiempo;
	sumac += estascomparaciones;
	k++;
	
	promedio = suma/k;
	promedioc = sumac/k;
	if(k<2){
	  resultadoFree(r);
	  free(r);
	  free(patron);
	  continue;
	}
	sumacuadrados += estetiempo*estetiempo;
	sumacuadradosc += estascomparaciones*estascomparaciones;
	
	stdev = sqrtl((sumacuadrados - k*promedio*promedio)/((double)(k -1))); //stdev de los tiempos
	
	stdevc = 0.0;
	for(i=0;i<ec.n;i++){
	  long double dif = (ec.valores[i] - promedioc);
	  stdevc += dif*dif/(k-1);
	}
	stdevc = sqrtl(stdevc);
	mu_stdev = stdev/sqrtl(k*1.0); //stdev del PROMEDIO de tiempos
	mu_stdevc = stdevc/sqrtl(k*1.0);
	
	error = 2.0*mu_stdev;
	errorc = 2.0*mu_stdevc;
	
	resultadoFree(r);
	free(r);
	free(patron);

	if(k>MIN_ITERACIONES && error < 0.05*promedio && errorc < 0.05*promedioc){
	  printf("Patron de largo %i\tlisto: promedio %.8Lf\titeraciones: %i\tmu_comparaciones: %.3Lf\n", 1<<largopatron2, promedio, k, promedioc);
	  largopatron2++;
	  break;
	}
      }

      if(algoritmo==ALGORITMO_FB) thefile = fbf;
      else if(algoritmo==ALGORITMO_KMP) thefile = fkmp;
      else if(algoritmo==ALGORITMO_BMH) thefile = fbmh;

      fprintf(thefile, "%i\t%.8Lf\t%.8Lf\n", largopatron2-1, promedio, error);

      estadisticaFree(&ec);

      if (largopatron2 > 7){
	algoritmo++;
	largopatron2 = 2;
	break;
      }
    }
  }

  free(alfabin);
}


void adn_real_exp(char *nombre, FILE* fbf, FILE* fkmp, FILE* fbmh, char *filename){
  struct timeval inicio, fin;
  struct resultado *r;
  FILE* thefile;

  int k = 1, i=0;
  int algoritmo=ALGORITMO_FB;

  double suma = 0.0;
  double sumacuadrados = 0.0;
  double estetiempo;
  long double promedio, stdev, mu_stdev;
  long double error;

  unsigned long long sumac = 0;
  unsigned long long sumacuadradosc = 0;
  long estascomparaciones;
  long double promedioc, stdevc, mu_stdevc;
  long double errorc;

  char *alfaadn = alfabeto_file(filename, UNMEGAENCHARS, onlyATGC, 0);
  char *patron = NULL;

  char infoalgoritmo[100];

  int largopatron2 = 2; // en POTENCIAS DE 2

  printf("Iniciando Experimento: %s\n", nombre);

  while(algoritmo < CANT_ALGORITMOS){ //por cada algoritmo
    if(algoritmo == ALGORITMO_FB) sprintf(infoalgoritmo, "Fuerza Bruta");
    else if(algoritmo == ALGORITMO_KMP) sprintf(infoalgoritmo, "Knuth Morris Pratt");
    else if(algoritmo == ALGORITMO_BMH) sprintf(infoalgoritmo, "Boyer Moore Horspool");

    printf("Iniciando iteracion para Algoritmo %s...\n", infoalgoritmo);
    while(1){ // por cada largo del patron
      suma = 0.0;
      sumac = 0;
      promedio = 0.0;
      promedioc = 0;
      sumacuadrados = 0.0;
      sumacuadradosc = 0;
      stdev = stdevc = 0.0;
      mu_stdev = mu_stdevc = 0.0;
      k=0; 
      struct estadistica_comparaciones ec;
      estadisticaNew(&ec);
      while (1){ // calcular el promedio de tiempo de ejecucion con error menor a 5% de la media
	         // con 95% de confianza
	patron = patron_text(largopatron2, alfaadn, UNMEGAENCHARS);
	r = (struct resultado *)malloc(sizeof(struct resultado));

	if(algoritmo==ALGORITMO_FB){
	  gettimeofday(&inicio, NULL);
	  fzabruta(patron,alfaadn,r);
	  gettimeofday(&fin, NULL);
	} else if (algoritmo==ALGORITMO_KMP){
	  gettimeofday(&inicio, NULL);
	  kmp(patron,alfaadn,UNMEGAENCHARS,r);
	  gettimeofday(&fin, NULL);
	} else if (algoritmo==ALGORITMO_BMH){
	  gettimeofday(&inicio, NULL);
	  bmh(patron,alfaadn,UNMEGAENCHARS,r);
	  gettimeofday(&fin, NULL);
	}
	estetiempo = elapsed_time(&fin, &inicio);
	estascomparaciones = r->comparaciones;

	estadisticaAdd(&ec, estascomparaciones);
	
	suma += estetiempo;
	sumac += estascomparaciones;
	k++;
	
	promedio = suma/k;
	promedioc = sumac/k;
	if(k<2){
	  resultadoFree(r);
	  free(r);
	  free(patron);
	  continue;
	}
	sumacuadrados += estetiempo*estetiempo;
	sumacuadradosc += estascomparaciones*estascomparaciones;
	
	stdev = sqrtl((sumacuadrados - k*promedio*promedio)/((double)(k -1))); //stdev de los tiempos
	
	stdevc = 0.0;
	for(i=0;i<ec.n;i++){
	  long double dif = (ec.valores[i] - promedioc);
	  stdevc += dif*dif/(k-1);
	}
	stdevc = sqrtl(stdevc);
	mu_stdev = stdev/sqrtl(k*1.0); //stdev del PROMEDIO de tiempos
	mu_stdevc = stdevc/sqrtl(k*1.0);
	
	error = 2.0*mu_stdev;
	errorc = 2.0*mu_stdevc;
	
	resultadoFree(r);
	free(r);
	free(patron);
	
	if(k>MIN_ITERACIONES && error < 0.05*promedio){
	  printf("Patron de largo %i listo: promedio %.8Lf\titeraciones: %i\n", 1<<largopatron2, promedio, k);
	  largopatron2++;
	  break;
	}
      }

      if(algoritmo==ALGORITMO_FB) thefile = fbf;
      else if(algoritmo==ALGORITMO_KMP) thefile = fkmp;
      else if(algoritmo==ALGORITMO_BMH) thefile = fbmh;

      fprintf(thefile, "%i\t%.8Lf\t%.8Lf\n", largopatron2-1, promedio, error);

      estadisticaFree(&ec);

      if (largopatron2 > 7){
	algoritmo++;
	largopatron2 = 2;
	break;
      }
    }
  }

  free(alfaadn);
}

void adn_sintetico_exp(char *nombre, FILE* fbf, FILE* fkmp, FILE* fbmh){
  struct timeval inicio, fin;
  struct resultado *r;
  FILE *thefile;

  int k = 1,i=0;
  int algoritmo=ALGORITMO_FB;

  double suma = 0.0;
  double sumacuadrados = 0.0;
  double estetiempo;
  long double promedio, stdev, mu_stdev;
  long double error;

  unsigned long long sumac = 0;
  unsigned long long sumacuadradosc = 0;
  long estascomparaciones;
  long double promedioc, stdevc, mu_stdevc;
  long double errorc;

  char *alfaadn = alfabeto_rand(adnsintetico_rand);
  char *patron = NULL;

  char infoalgoritmo[100];

  int largopatron2 = 2; // en POTENCIAS DE 2

  printf("Iniciando Experimento: %s\n", nombre);

  while(algoritmo < CANT_ALGORITMOS){ //por cada algoritmo
    if(algoritmo == ALGORITMO_FB) sprintf(infoalgoritmo, "Fuerza Bruta");
    else if(algoritmo == ALGORITMO_KMP) sprintf(infoalgoritmo, "Knuth Morris Pratt");
    else if(algoritmo == ALGORITMO_BMH) sprintf(infoalgoritmo, "Boyer Moore Horspool");

    printf("Iniciando iteracion para Algoritmo %s...\n", infoalgoritmo);
    while(1){ // por cada largo del patron
      suma = 0.0;
      sumac = 0;
      promedio = 0.0;
      promedioc = 0;
      sumacuadrados = 0.0;
      sumacuadradosc = 0;
      stdev = stdevc = 0.0;
      mu_stdev = mu_stdevc = 0.0;
      k=0; 
      struct estadistica_comparaciones ec;
      estadisticaNew(&ec);
      while (1){ // calcular el promedio de tiempo de ejecucion con error menor a 5% de la media
	         // con 95% de confianza
	patron = patron_text(largopatron2, alfaadn, UNMEGAENCHARS);
	r = (struct resultado *)malloc(sizeof(struct resultado));

	if(algoritmo==ALGORITMO_FB){
	  gettimeofday(&inicio, NULL);
	  fzabruta(patron,alfaadn,r);
	  gettimeofday(&fin, NULL);
	} else if (algoritmo==ALGORITMO_KMP){
	  gettimeofday(&inicio, NULL);
	  kmp(patron,alfaadn,UNMEGAENCHARS,r);
	  gettimeofday(&fin, NULL);
	} else if (algoritmo==ALGORITMO_BMH){
	  gettimeofday(&inicio, NULL);
	  bmh(patron,alfaadn,UNMEGAENCHARS,r);
	  gettimeofday(&fin, NULL);
	}
	estetiempo = elapsed_time(&fin, &inicio);
	estascomparaciones = r->comparaciones;

	estadisticaAdd(&ec, estascomparaciones);
	
	suma += estetiempo;
	sumac += estascomparaciones;
	k++;
	
	promedio = suma/k;
	promedioc = sumac/k;
	if(k<2){
	  resultadoFree(r);
	  free(r);
	  free(patron);
	  continue;
	}
	sumacuadrados += estetiempo*estetiempo;
	sumacuadradosc += estascomparaciones*estascomparaciones;
	
	stdev = sqrtl((sumacuadrados - k*promedio*promedio)/((double)(k -1))); //stdev de los tiempos
	
	stdevc = 0.0;
	for(i=0;i<ec.n;i++){
	  long double dif = (ec.valores[i] - promedioc);
	  stdevc += dif*dif/(k-1);
	}
	stdevc = sqrtl(stdevc);
	mu_stdev = stdev/sqrtl(k*1.0); //stdev del PROMEDIO de tiempos
	mu_stdevc = stdevc/sqrtl(k*1.0);
	
	error = 2.0*mu_stdev;
	errorc = 2.0*mu_stdevc;
	
	resultadoFree(r);
	free(r);
	free(patron);
	
	if(k>MIN_ITERACIONES && error < 0.05*promedio){
	  printf("Patron de largo %i listo: promedio %.8Lf\titeraciones: %i\n", 1<<largopatron2, promedio, k);
	  largopatron2++;
	  break;
	}
      }

      if(algoritmo==ALGORITMO_FB) thefile = fbf;
      else if(algoritmo==ALGORITMO_KMP) thefile = fkmp;
      else if(algoritmo==ALGORITMO_BMH) thefile = fbmh;

      fprintf(thefile, "%i\t%.8Lf\t%.8Lf\n", largopatron2-1, promedio, error);

      estadisticaFree(&ec);

      if (largopatron2 > 7){
	algoritmo++;
	largopatron2 = 2;
	break;
      }
    }
  }

  free(alfaadn);
}


void lenguaje_real_exp(char *nombre, FILE* fbf, FILE* fkmp, FILE* fbmh, char *filename){
  struct timeval inicio, fin;
  struct resultado *r;
  FILE *thefile;

  int k = 1,i=0;
  int algoritmo=ALGORITMO_FB;

  double suma = 0.0;
  double sumacuadrados = 0.0;
  double estetiempo;
  long double promedio, stdev, mu_stdev;
  long double error;

  unsigned long long sumac = 0;
  unsigned long long sumacuadradosc = 0;
  long estascomparaciones;
  long double promedioc, stdevc, mu_stdevc;
  long double errorc;

  char *alfaleng = alfabeto_file(filename, UNMEGAENCHARS, onlyEnglish, 1);
  char *patron = NULL;

  char infoalgoritmo[100];

  int largopatron2 = 2; // en POTENCIAS DE 2

  printf("Iniciando Experimento: %s\n", nombre);

  while(algoritmo < CANT_ALGORITMOS){ //por cada algoritmo
    if(algoritmo == ALGORITMO_FB) sprintf(infoalgoritmo, "Fuerza Bruta");
    else if(algoritmo == ALGORITMO_KMP) sprintf(infoalgoritmo, "Knuth Morris Pratt");
    else if(algoritmo == ALGORITMO_BMH) sprintf(infoalgoritmo, "Boyer Moore Horspool");

    printf("Iniciando iteracion para Algoritmo %s...\n", infoalgoritmo);
    while(1){ // por cada largo del patron
      suma = 0.0;
      sumac = 0;
      promedio = 0.0;
      promedioc = 0;
      sumacuadrados = 0.0;
      sumacuadradosc = 0;
      stdev = stdevc = 0.0;
      mu_stdev = mu_stdevc = 0.0;
      k=0; 
      struct estadistica_comparaciones ec;
      estadisticaNew(&ec);
      while (1){ // calcular el promedio de tiempo de ejecucion con error menor a 5% de la media
	         // con 95% de confianza
	patron = patron_text(largopatron2, alfaleng, UNMEGAENCHARS);
	r = (struct resultado *)malloc(sizeof(struct resultado));

	if(algoritmo==ALGORITMO_FB){
	  gettimeofday(&inicio, NULL);
	  fzabruta(patron,alfaleng,r);
	  gettimeofday(&fin, NULL);
	} else if (algoritmo==ALGORITMO_KMP){
	  gettimeofday(&inicio, NULL);
	  kmp(patron,alfaleng,UNMEGAENCHARS,r);
	  gettimeofday(&fin, NULL);
	} else if (algoritmo==ALGORITMO_BMH){
	  gettimeofday(&inicio, NULL);
	  bmh(patron,alfaleng,UNMEGAENCHARS,r);
	  gettimeofday(&fin, NULL);
	}
	estetiempo = elapsed_time(&fin, &inicio);
	estascomparaciones = r->comparaciones;

	estadisticaAdd(&ec, estascomparaciones);
	
	suma += estetiempo;
	sumac += estascomparaciones;
	k++;
	
	promedio = suma/k;
	promedioc = sumac/k;
	if(k<2){
	  resultadoFree(r);
	  free(r);
	  free(patron);
	  continue;
	}
	sumacuadrados += estetiempo*estetiempo;
	sumacuadradosc += estascomparaciones*estascomparaciones;
	
	stdev = sqrtl((sumacuadrados - k*promedio*promedio)/((double)(k -1))); //stdev de los tiempos
	
	stdevc = 0.0;
	for(i=0;i<ec.n;i++){
	  long double dif = (ec.valores[i] - promedioc);
	  stdevc += dif*dif/(k-1);
	}
	stdevc = sqrtl(stdevc);
	mu_stdev = stdev/sqrtl(k*1.0); //stdev del PROMEDIO de tiempos
	mu_stdevc = stdevc/sqrtl(k*1.0);
	
	error = 2.0*mu_stdev;
	errorc = 2.0*mu_stdevc;
	
	resultadoFree(r);
	free(r);
	free(patron);
	
	if(k>MIN_ITERACIONES && error < 0.05*promedio){
	  printf("Patron de largo %i listo: promedio %.8Lf\titeraciones: %i\n", 1<<largopatron2, promedio, k);
	  largopatron2++;
	  break;
	}
      }

      if(algoritmo==ALGORITMO_FB) thefile = fbf;
      else if(algoritmo==ALGORITMO_KMP) thefile = fkmp;
      else if(algoritmo==ALGORITMO_BMH) thefile = fbmh;
      
      fprintf(thefile, "%i\t%.8Lf\t%.8Lf\n", largopatron2-1, promedio, error);

      estadisticaFree(&ec);

      if (largopatron2 > 7){
	algoritmo++;
	largopatron2 = 2;
	break;
      }
    }
  }

  free(alfaleng);
}

void lenguaje_sintetico_exp(char *nombre, FILE* fbf, FILE* fkmp, FILE* fbmh){
  struct timeval inicio, fin;
  struct resultado *r;
  FILE *thefile;

  int k = 1,i=0;
  int algoritmo=ALGORITMO_FB;

  double suma = 0.0;
  double sumacuadrados = 0.0;
  double estetiempo;
  long double promedio, stdev, mu_stdev;
  long double error;

  unsigned long long sumac = 0;
  unsigned long long sumacuadradosc = 0;
  long estascomparaciones;
  long double promedioc, stdevc, mu_stdevc;
  long double errorc;

  char *alfaleng = alfabeto_rand(lengsintetico_rand);
  char *patron = NULL;

  char infoalgoritmo[100];

  int largopatron2 = 2; // en POTENCIAS DE 2

  printf("Iniciando Experimento: %s\n", nombre);

  while(algoritmo < CANT_ALGORITMOS){ //por cada algoritmo
    if(algoritmo == ALGORITMO_FB) sprintf(infoalgoritmo, "Fuerza Bruta");
    else if(algoritmo == ALGORITMO_KMP) sprintf(infoalgoritmo, "Knuth Morris Pratt");
    else if(algoritmo == ALGORITMO_BMH) sprintf(infoalgoritmo, "Boyer Moore Horspool");

    printf("Iniciando iteracion para Algoritmo %s...\n", infoalgoritmo);
    while(1){ // por cada largo del patron
      suma = 0.0;
      sumac = 0;
      promedio = 0.0;
      promedioc = 0;
      sumacuadrados = 0.0;
      sumacuadradosc = 0;
      stdev = stdevc = 0.0;
      mu_stdev = mu_stdevc = 0.0;
      k=0; 
      struct estadistica_comparaciones ec;
      estadisticaNew(&ec);
      while (1){ // calcular el promedio de tiempo de ejecucion con error menor a 5% de la media
	         // con 95% de confianza
	patron = patron_text(largopatron2, alfaleng, UNMEGAENCHARS);
	r = (struct resultado *)malloc(sizeof(struct resultado));

	if(algoritmo==ALGORITMO_FB){
	  gettimeofday(&inicio, NULL);
	  fzabruta(patron,alfaleng,r);
	  gettimeofday(&fin, NULL);
	} else if (algoritmo==ALGORITMO_KMP){
	  gettimeofday(&inicio, NULL);
	  kmp(patron,alfaleng,UNMEGAENCHARS,r);
	  gettimeofday(&fin, NULL);
	} else if (algoritmo==ALGORITMO_BMH){
	  gettimeofday(&inicio, NULL);
	  bmh(patron,alfaleng,UNMEGAENCHARS,r);
	  gettimeofday(&fin, NULL);
	}
	estetiempo = elapsed_time(&fin, &inicio);
	estascomparaciones = r->comparaciones;

	estadisticaAdd(&ec, estascomparaciones);
	
	suma += estetiempo;
	sumac += estascomparaciones;
	k++;
	
	promedio = suma/k;
	promedioc = sumac/k;
	if(k<2){
	  resultadoFree(r);
	  free(r);
	  free(patron);
	  continue;
	}
	sumacuadrados += estetiempo*estetiempo;
	sumacuadradosc += estascomparaciones*estascomparaciones;
	
	stdev = sqrtl((sumacuadrados - k*promedio*promedio)/((double)(k -1))); //stdev de los tiempos
	
	stdevc = 0.0;
	for(i=0;i<ec.n;i++){
	  long double dif = (ec.valores[i] - promedioc);
	  stdevc += dif*dif/(k-1);
	}
	stdevc = sqrtl(stdevc);
	mu_stdev = stdev/sqrtl(k*1.0); //stdev del PROMEDIO de tiempos
	mu_stdevc = stdevc/sqrtl(k*1.0);
	
	error = 2.0*mu_stdev;
	errorc = 2.0*mu_stdevc;
	
	resultadoFree(r);
	free(r);
	free(patron);
	
	if(k>MIN_ITERACIONES && error < 0.05*promedio){
	  printf("Patron de largo %i listo: promedio %.8Lf\titeraciones: %i\n", 1<<largopatron2, promedio, k);
	  largopatron2++;
	  break;
	}
      }

      if(algoritmo==ALGORITMO_FB) thefile = fbf;
      else if(algoritmo==ALGORITMO_KMP) thefile = fkmp;
      else if(algoritmo==ALGORITMO_BMH) thefile = fbmh;
      
      fprintf(thefile, "%i\t%.8Lf\t%.8Lf\n", largopatron2-1, promedio, error);

      estadisticaFree(&ec);

      if (largopatron2 > 7){
	algoritmo++;
	largopatron2 = 2;
	break;
      }
    }
  }

  free(alfaleng);
}
