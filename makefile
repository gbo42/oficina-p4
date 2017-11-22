CFLAGS = -Wall
objects = celulas.o csv_lib.o prints.o formulas.o comandos.o

all: myxcel

myxcel: myxcel.o $(objects)
	gcc myxcel.o $(objects) -o myxcel $(CFLAGS) -lncurses

myxcel.o: myxcel.c
	gcc -c myxcel.c $(CFLAGS) -lncurses

celulas.o: celulas.c celulas.h
	gcc -c celulas.c $(CFLAGS)

csv_lib.o: csv_lib.c csv_lib.h
	gcc -c csv_lib.c $(CFLAGS)

prints.o: prints.c prints.h
	gcc -c prints.c $(CFLAGS) -lncurses

formulas.o: formulas.c formulas.h
	gcc -c formulas.c $(CFLAGS)

comandos.o: comandos.c comandos.h
	gcc -c comandos.c $(CFLAGS)
clean:
	-rm -f *.o

purge: clean
	-rm -f myxcel
