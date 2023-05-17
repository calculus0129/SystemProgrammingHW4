CFLAGS += -Wall -g -O5
pgm:	test.o heap-allocator.o
	$(CC) -o $@ $^
.phony:	clean
clean:
	rm (*.o) pgm
