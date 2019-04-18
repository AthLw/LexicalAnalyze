app: main.c lib.o analyzer.o
	gcc -ggdb main.c lib.o analyzer.o -I./include
lib.o: lib.c
	gcc -ggdb -o lib.o -c lib.c -I./include
analyzer.o: analyzer.c
	gcc -g -o analyzer.o -c analyzer.c -I./include
clean: 
	rm -rf *.o 
