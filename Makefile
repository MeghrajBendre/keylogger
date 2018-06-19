keylogger: keylogger.o
	gcc -o keylogger -g -Wall keylogger.o

keylogger.o: keylogger.c keylogger.h
	gcc -g -c -Wall keylogger.c
	
clean:
	rm -f *.o keylogger
