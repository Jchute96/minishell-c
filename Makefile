all: newshell numbers userinput letters firstname

newshell:	newshell.o
	gcc newshell.o -o newshell

newshell.o:	newshell.c
	gcc -c newshell.c -o newshell.o

numbers:	numbers.o
	gcc numbers.o -o numbers

numbers.o:	numbers.c
	gcc -c numbers.c -o numbers.o

userinput:	userinput.o
	gcc userinput.o -o userinput

userinput.o:	userinput.c
	gcc -c userinput.c -o userinput.o

letters:	letters.o
	gcc letters.o -o letters

letters.o:	letters.c
	gcc -c letters.c -o letters.o

firstname:	firstname.o
	gcc firstname.o -o firstname

firstname.o:	firstname.c
	gcc -c firstname.c -o firstname.o

clean:
	rm -f *.o core *~ newshell numbers userinput letters firstname