#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SUCC 0
#define FULL -1
#define EMPT -2
#define FAIL -3

struct buf {
	unsigned int mask;
	int head, tail;
	int *data;
	bool full_fl, empt_fl;
};

void print_buf(struct buf *buf, char *str)
{
	unsigned int i, end;
	int *data;
	printf("\n====%s====\n", str);
	for (i = 0, end = buf->mask, data = buf->data; i < end; i++)
		printf("%d ", data[i]);
}
int push(struct buf *buf, int val)
{
	unsigned int head = buf->head;
	print_buf(buf, "befor push");
	if (((head + 1) & buf->mask) == buf->tail) {
		print_buf(buf, "buffer full");
		return FULL;
	}
	buf->data[head] = val;
	buf->head++;
	print_buf(buf, "after push");
	return SUCC;
}
int pop(struct buf *buf, int *val)
{
	unsigned int tail = buf->tail;
	print_buf(buf, "befor pop");
	if (tail == (buf->head)) {
		print_buf(buf, "buffer empty");
		return EMPT;
	}
	*val = buf->data[tail];
	buf->tail = (tail + 1) & buf->mask;
	print_buf(buf, "after pop");
	return SUCC;
}
struct buf *init(size_t size)
{
	unsigned int i;
	struct buf *buf;
	if (size > 255 || size < 3) {
		return NULL;
	}
	if ((buf = malloc(sizeof(struct buf))) == NULL) {
		perror("cannot allocate buffer struct");
		return NULL;
	}
	for (i = 2; i < size; i *= 2);
	if ((buf->data = malloc(sizeof(int) * i)) == NULL) {
		perror("cannot allocate buffer memory");
		free(buf);
		return NULL;
	}
	buf->mask = i - 1;
	buf->full_fl = false, buf->empt_fl = true;
	buf->head = buf->tail = 0;
	return buf;
}
int del(struct buf *buf)
{
	if (buf)
		if (buf->data)
			free(buf->data), free(buf);
		else
			free(buf);
	else
		return FAIL;
	return SUCC;
}

int main(void)
{
#ifdef DEBUG
	extern int EF_ALIGNMENT;
	EF_ALIGNMENT = 0;
#endif
	struct buf *buf = init(20);
	if (buf == NULL) {
		return 1;
	}
	if (del(buf) != SUCC) {
		fprintf(stderr, "cannot free buffer\n");
		return 1;
	}
	return 0;
}
