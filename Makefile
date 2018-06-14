keylogger: keylogger.o
	gcc -o keylogger -g keylogger.o

keylogger.o: keylogger.c
	gcc -g -c -Wall keylogger.c

clean:
	rm -f *.o keylogger
