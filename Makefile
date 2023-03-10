CC=gcc
LIBRARY=-L.
LIBS=-lstructs
HEADERS=-Iheaders
OPTIONS=-g

main: library
	$(CC) $(OPTIONS) -o main main.c $(HEADERS) $(LIBRARY) $(LIBS)


library: priority_queue.o rbtree.o
	gcc -shared -o libstructs.so $^

%.o: src/%.c
	$(CC) $(OPTIONS) -c $< $(HEADERS)

clean:
	find . -name "*.o" -o -name "*.so" -o -name "main" | xargs rm