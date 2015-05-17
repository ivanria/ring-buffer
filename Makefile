CFLAGS := -Wall -g -DDEBUG
TEST := test
LIB_NAME := librbuf.so
MAKE_FILE := Makefile

ifneq (,$(findstring DEBUG, $(CFLAGS)))
	LDFLAGS := -Wl,--no-as-needed,-lefence
else
	LDFLAGS := 
endif

ring-buffer.o: ring-buffer.c ring-buffer.h $(MAKE_FILE)
	gcc $(CFLAGS) -c -fPIC -o ring-buffer.o ring-buffer.c

$(LIB_NAME): ring-buffer.o $(MAKE_FILE)
	gcc -shared -o $(LIB_NAME) ring-buffer.o

test.o: test.c $(MAKE_FILE)
	gcc $(CFLAGS) -c test.c

$(TEST): test.o $(MAKE_FILE)
	gcc -L. -lrbuf test.o -o $(TEST)


.PHONY: clean all

clean:
	rm -f *.o $(TEST) $(LIB_NAME)

all: $(LIB_NAME) $(TEST) $(MAKE_FILE)


