#include <stdio.h>

struct buf {
	unsigned int mask;
	int head, tail;
	int *data;
};

int push(struct buf *buf, int val)
{
	unsigned int head = buf->head;
	print_buf(buf, "befor push");
	if ((head + 1) & buf->mask == buf->tail) {
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
	i--;
	if ((buf->data = malloc(sizeof(int) * size)) == NULL) {
		perror("cannot allocate buffer memory");
		free(buf);
		return NULL;
	}
	buf->mask = i;
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
	return 0;
}
