CFLAGS = -Wall -g
CC = gcc
PROGS = compare_recherche_lc compare_recherche_h

all : $(PROGS)

compare_recherche_lc : compare_recherche_lc.o
	$(CC) $(CFLAGS) -o $@ $^

compare_recherche_lc.o : compare_recherche_lc.c commun.h  ./Partie_1/biblioLC.h ./Partie_1/entreeSortieLC.h 
	$(CC) $(CFLAGS) -o $@ $<


compare_recherche_h : compare_recherche_h.o
	$(CC) $(CFLAGS) -o $@ $^

compare_recherche_h.o : compare_recherche_h.c commun.h ./Partie_2/biblioH.h  ./Partie_2/entreeSortieHach.h
	$(CC) $(CFLAGS) -o $@ $<


clean :
	rm -f *.o $(PROGS)
