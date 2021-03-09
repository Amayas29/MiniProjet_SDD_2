CFLAGS = -Wall -g
CC = gcc
PROGS = mainHach compare_recherche_h

all : $(PROGS)

# --------------------------------------------
compare_recherche_h : compare_recherche_h.o biblioH.o entreeSortieHach.o
	$(CC) $(CFLAGS) -o $@ $^

mainHach : biblioH.o entreeSortieHach.o UIfonctions.o mainHach.o
	$(CC) $(CFLAGS) -o $@ $^

biblioH.o : biblioH.c biblioH.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

entreeSortieHach.o : entreeSortieHach.c entreeSortieHach.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

UIfonctions.o : UIfonctions.c UIfonctions.h entreeSortieHach.h biblioH.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

mainHach.o : mainHach.c entreeSortieHach.h ../commun.h
	$(CC) $(CFLAGS) -o $@ -c $<


compare_recherche_h.o : compare_recherche_h.c  biblioH.h  entreeSortieHach.h ../commun.h
	$(CC) $(CFLAGS) -o $@ $<

# --------------------------------------------

clean :
	rm -rf $(PROGS) *.o