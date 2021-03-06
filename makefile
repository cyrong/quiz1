CC = gcc
OBJ = modifyqsort.o
%.o: %.c
	$(CC) -c -o $@ $<
modifyqsort: $(OBJ)
	$(CC) -o $@ $^
test:
	./modifyqsort
clean:
	rm -f modifyqsort *.o
