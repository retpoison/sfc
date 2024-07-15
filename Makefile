cc=gcc

sfc: main.o sfc.o number.o
	$(cc) main.o sfc.o number.o -o sfc -lm

main.o: main.c
	$(cc) -c main.c

sfc.o: sfc.c sfc.h
	$(cc) -c sfc.c

number.o: number.c number.h
	$(cc) -c number.c 

clean:
	rm sfc *.o

