CFLAGS = -Wall -g
CC = gcc
PROGS = main

all : $(PROGS)

main : biblioLC.o entreeSortieLC.o UIfonctions.o main.o
	$(CC) $(CFLAGS) -o $@ $^

main.o : main.c entreeSortieLC.h commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

biblioLC.o : biblioLC.c biblioLC.h commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

entreeSortieLC.o : entreeSortieLC.c entreeSortieLC.h commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

UIfonctions.o : UIfonctions.c UIfonctions.h entreeSortieLC.h biblioLC.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -rf $(PROGS) *.o