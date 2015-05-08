CFLAGS := -Wall -g -DDEBUG
TEST := test
LIB_NAME := librbuf.so

ring-buffer.o: ring-buffer.c ring-buffer.h
	gcc $(CFLAGS) -c -fPIC -o ring-buffer.o ring-buffer.c

$(LIB_NAME): ring-buffer.o
	gcc -shared -o $(LIB_NAME) ring-buffer.o

test.o: test.c
	gcc $(CFLAGS) -c test.c

$(TEST): test.o
	gcc -L. -lrbuf test.o -o $(TEST)


.PHONY: clean all

clean:
	rm -f *.o $(TEST) $(LIB_NAME)

all: $(LIB_NAME) $(TEST)


