CFLAGS = -Wall -g
CC = gcc
PROGS = compare_recherche_lc compare_recherche_h

all : $(PROGS)

compare_recherche_lc : compare_recherche_lc.o biblioLC.o entreeSortieLC.o
	$(CC) $(CFLAGS) -o $@ $^

compare_recherche_lc.o : compare_recherche_lc.c ../commun.h  ../Partie_1/biblioLC.h ../Partie_1/entreeSortieLC.h 
	$(CC) $(CFLAGS) -o $@ -c $<

biblioLC.o : ../Partie_1/biblioLC.c ../Partie_1/biblioLC.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

entreeSortieLC.o : ../Partie_1/entreeSortieLC.c ../Partie_1/entreeSortieLC.h  ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<


biblioH.o : ../Partie_2/biblioH.c ../Partie_2/biblioH.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

entreeSortieHach.o : ../Partie_2/entreeSortieHach.c ../Partie_2/entreeSortieHach.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<


compare_recherche_h : compare_recherche_h.o biblioH.o entreeSortieHach.o
	$(CC) $(CFLAGS) -o $@  $^

compare_recherche_h.o : compare_recherche_h.c ../commun.h ../Partie_2/biblioH.h  ../Partie_2/entreeSortieHach.h
	$(CC) $(CFLAGS) -o $@ -c $<


clean :
	rm -f *.o $(PROGS)
