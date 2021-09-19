FLAGS = -g -Wall

kshell: prompt.o utils.o command_cd.o command_pwd.o shell.o
	gcc -o kshell $(FLAGS) prompt.o utils.o command_cd.o command_pwd.o shell.o

clean:
	rm -f *.o kshell

prompt.o: prompt.c prompt.h
	gcc $(FLAGS) -c prompt.c

utils.o: utils.c utils.h
	gcc $(FLAGS) -c utils.c

command_cd.o: command_cd.c command_cd.h
	gcc $(FLAGS) -c command_cd.c

command_pwd.o: command_pwd.c command_pwd.h
	gcc $(FLAGS) -c command_pwd.c