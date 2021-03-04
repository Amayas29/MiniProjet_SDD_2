CFLAGS = -Wall -g
CC = gcc
PROGS = mainHach

all : $(PROGS)

# --------------------------------------------

mainHach : biblioH.o mainHach.o
	$(CC) $(CFLAGS) -o $@ $^

biblioH.o : biblioH.c biblioH.h commun.h
	$(CC) $(CFLAGS) -o $@ -c $<

mainHach.o : mainHach.c
	$(CC) $(CFLAGS) -o $@ -c $<

# --------------------------------------------

clean :
	rm -rf $(PROGS) *.o