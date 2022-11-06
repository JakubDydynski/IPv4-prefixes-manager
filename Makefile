# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -Wextra

# the build target executable:
main: main.o api.o
	$(CC) $(CFLAGS) -o main api.o main.o 

api.o: api.c api.h
	$(CC) $(CFLAGS) -c api.c

main.o: main.c api.h
	$(CC) $(CFLAGS) -c main.c


clean: 
	$(RM) main *.o *~