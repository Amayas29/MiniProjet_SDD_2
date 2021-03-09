CFLAGS = -Wall -g
CC = gcc
PROGS = mainListe compare_recherche_lc

all : $(PROGS)

# --------------------------------------------

mainListe : biblioLC.o entreeSortieLC.o UIfonctions.o mainListe.o
	$(CC) $(CFLAGS) -o $@ $^

mainListe.o : mainListe.c entreeSortieLC.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

biblioLC.o : biblioLC.c biblioLC.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

entreeSortieLC.o : entreeSortieLC.c entreeSortieLC.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

UIfonctions.o : UIfonctions.c UIfonctions.h entreeSortieLC.h biblioLC.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

compare_recherche_lc : compare_recherche_lc.o entreeSortieLC.o biblioLC.o 
	$(CC) $(CFLAGS) -o $@ $^

compare_recherche_lc.o : compare_recherche_lc.c ../commun.h  biblioLC.h entreeSortieLC.h 
	$(CC) $(CFLAGS) -o $@ $<

# --------------------------------------------

clean :
	rm -rf $(PROGS) *.o
