all: writer.o story.o
	gcc -o story story.o
	gcc -o writer writer.o

story.o: story.c
	gcc -c story.c

writer.o: writer.c
	gcc -c writer.c
