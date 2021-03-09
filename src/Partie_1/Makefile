CFLAGS = -Wall -g
CC = gcc
PROGS = mainListe 

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

# --------------------------------------------

clean :
	rm -rf $(PROGS) *.o
