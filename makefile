FLAGS =-Wall -g
CC = gcc

all: stringProg

stringProg: main.o libclass.a 
	$(CC) $(FLAGS) -o stringProg main.o libclass.a


main.o: main.c my_func.h
	$(CC) $(FLAGS) -c main.c 

libclass.a: my_func.o
	ar -rcs libclass.a my_func.o


my_func.o: my_func.c my_func.h
	$(CC) $(FLAGS) -c my_func.c 	


.PHONY: clean
clean:
	rm -f stringProg *.o *.a *.so *.out