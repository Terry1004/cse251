scheduler: scheduler.o io.o file.o
	gcc -o scheduler scheduler.o io.o file.o

scheduler.o: scheduler.c scheduler.h types.h
	gcc -c scheduler.c

io.o: io.c io.h types.h
	gcc -c io.c

file.o: file.c io.h types.h
	gcc -c file.c

clean:
	rm -f *.o scheduler
