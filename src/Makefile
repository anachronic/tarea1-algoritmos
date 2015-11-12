CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lm
PROGNAME=tarea1

default : $(PROGNAME)

tarea1 : tarea1.o algoritmos.o resultados.o experimentos.o alfabetos.o
	$(CC) $(CFLAGS) tarea1.o algoritmos.o resultados.o experimentos.o alfabetos.o -o $(PROGNAME) $(LDFLAGS)

tarea1.o :
	$(CC) $(CFLAGS) tarea1.c -o tarea1.o -c

algoritmos.o :
	$(CC) $(CFLAGS) algoritmos.c -o algoritmos.o -c

resultados.o :
	$(CC) $(CFLAGS) resultados.c -o resultados.o -c

alfabetos.o :
	$(CC) $(CFLAGS) alfabetos.c -o alfabetos.o -c

experimentos.o :
	$(CC) $(CFLAGS) experimentos.c -o experimentos.o -c

clean:
	rm -rf *.o *.dat *~ $(PROGNAME)

debug:
	make clean && make
