FLAGS = -g -Wall

kshell: prompt.o utils.o shell.o
	gcc -o kshell $(FLAGS) prompt.o utils.o shell.o

clean:
	rm -f *.o kshell

prompt.o: prompt.c prompt.h
	gcc $(FLAGS) -c prompt.c

utils.o: utils.c utils.h
	gcc $(FLAGS) -c utils.c