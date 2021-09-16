FLAGS = -g -Wall

kshell: prompt.o shell.o
	gcc -o kshell $(FLAGS) prompt.o shell.o

clean:
	rm -f *.o kshell

prompt.o: prompt.c prompt.h
	gcc $(FLAGS) -c prompt.c