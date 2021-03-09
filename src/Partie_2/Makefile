CFLAGS = -Wall -g
CC = gcc
PROGS = mainHach 

all : $(PROGS)

# --------------------------------------------


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


# --------------------------------------------

clean :
	rm -rf $(PROGS) *.o