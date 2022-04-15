objects = hello-main.o hello-funct1.o hello-funct2.o
CC = gcc
CFLAGS = -c -Wall -pg

debug-objects = hello-main-d.o hello-funct1-d.o hello-funct2-d.o
DEBUG = -g

all: hello

hello: $(objects)
	$(CC) -o hello $(objects) -lpthread

hello-main.o : hello-main.c
	$(CC) $(CFLAGS) hello-main.c

hello-funct1.o : hello-funct1.c
	$(CC) $(CFLAGS) hello-funct1.c

hello-funct2.o : hello-funct2.c
	$(CC) $(CFLAGS) hello-funct2.c


debug: hello-d

hello-d: $(debug-objects)
	$(CC) -o hello-d $(debug-objects)

hello-main-d.o: hello-main.c
	$(CC) $(CFLAGS) $(DEBUG) -o hello-main-d.o hello-main.c

hello-funct1-d.o: hello-funct1.c
	$(CC) $(CFLAGS) $(DEBUG) -o hello-funct1-d.o hello-funct1.c

hello-funct2-d.o: hello-funct2.c
	$(CC) $(CFLAGS) $(DEBUG) -o hello-funct2-d.o hello-funct2.c

clean:
	rm -f $(objects) $(debug-objects) hello hello-d


