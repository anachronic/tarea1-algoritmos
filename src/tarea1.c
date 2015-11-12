#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>

#include "algoritmos.h"
#include "resultados.h"
#include "alfabetos.h"
#include "experimentos.h"

int main(){
  srand48(getpid());

  FILE *fbf;
  FILE *fkmp;
  FILE *fbmh;

  fbf = fopen("fuerzabruta_bin.dat", "wt");
  fkmp = fopen("kmp_bin.dat", "wt");
  fbmh = fopen("bmh_bin.dat", "wt");

  printf("Tarea 1 CC4102\nEmpezando Iteraciones\n\n");

  alfabeto_binario_exp("Alfabeto Binario", fbf, fkmp,fbmh);

  fclose(fbf);
  fclose(fkmp);
  fclose(fbmh);

  fbf = fopen("fuerzabruta_adnreal.dat", "wt");
  fkmp = fopen("kmp_adnreal.dat", "wt");
  fbmh = fopen("bmh_adnreal.dat", "wt");

  adn_real_exp("ADN Real", fbf, fkmp, fbmh, "../texts/dna");

  fclose(fbf);
  fclose(fkmp);
  fclose(fbmh);

  fbf = fopen("fuerzabruta_adnsintetico.dat", "wt");
  fkmp = fopen("kmp_adnsintetico.dat", "wt");
  fbmh = fopen("bmh_adnsintetico.dat", "wt");

  adn_sintetico_exp("ADN Sintetico", fbf, fkmp, fbmh);

  fclose(fbf);
  fclose(fkmp);
  fclose(fbmh);

  fbf = fopen("fuerzabruta_lenguajereal.dat", "wt");
  fkmp = fopen("kmp_lenguajereal.dat", "wt");
  fbmh = fopen("bmh_lenguajereal.dat", "wt");

  lenguaje_real_exp("Lenguaje Real", fbf, fkmp, fbmh, "../texts/english");

  fclose(fbf);
  fclose(fkmp);
  fclose(fbmh);

  fbf = fopen("fuerzabruta_lenguajesint.dat", "wt");
  fkmp = fopen("kmp_lenguajesint.dat", "wt");
  fbmh = fopen("bmh_lenguajersint.dat", "wt");

  lenguaje_sintetico_exp("Lenguaje Sintetico", fbf, fkmp, fbmh);

  fclose(fbf);
  fclose(fkmp);
  fclose(fbmh);


  return 0;
}

