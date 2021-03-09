CFLAGS = -Wall -g
CC = gcc
PROGS = comparer

all : $(PROGS)


biblioLC.o : ../Partie_1/biblioLC.c ../Partie_1/biblioLC.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

entreeSortieLC.o : ../Partie_1/entreeSortieLC.c ../Partie_1/entreeSortieLC.h  ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

biblioH.o : ../Partie_2/biblioH.c ../Partie_2/biblioH.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

entreeSortieHach.o : ../Partie_2/entreeSortieHach.c ../Partie_2/entreeSortieHach.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

comparer : comparer.o biblioLC.o entreeSortieLC.o biblioH.o entreeSortieHach.o
	$(CC) $(CFLAGS) -o $@  $^

comparer.o : comparer.c ../commun.h ../Partie_1/biblioLC.h ../Partie_1/entreeSortieLC.h ../Partie_2/biblioH.h  ../Partie_2/entreeSortieHach.h
	$(CC) $(CFLAGS) -o $@ -c $<

plot_numeros:
	gnuplot -p < commande_plot_numeros.txt

plot_titres:
	gnuplot -p < commande_plot_titres.txt

plot_auteurs:
	gnuplot -p < commande_plot_auteurs.txt

clean :
	rm -f *.o $(PROGS) *.ps