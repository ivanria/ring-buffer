#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define SUCC 0
#define FULL -1
#define EMPT -2
#define FAIL -3

struct buf {
	unsigned int mask;
	size_t size;
	int head, tail;
	int *data;
	bool full_fl, empt_fl;
};

int del(struct buf *buf)
{
	if (buf) {
		if (buf->data) {
			free(buf->data);
		       	free(buf);
		} else {
			free(buf);
			return FAIL;
		}
	} else {
		return FAIL;
	}
	return SUCC;
}
#ifdef DEBUG
void print_buf(struct buf *buf, char *str)
{
	unsigned int i, end;
	int *data;
	printf("\n====%s====\n", str);
	for (i = 0, end = buf->size, data = buf->data; i < end; i++)
		printf("%d ", data[i]);
	printf("\nhead %d, tail %d\n", buf->head, buf->tail);
}
#endif
int push(struct buf *buf, int val)
{
	unsigned int t_head = buf->head, t_tail = buf->tail;
#ifdef DEBUG
	if (buf->full_fl == true || buf->empt_fl == true) {
		if (t_head != t_tail) {
			del(buf);
			fprintf(stderr, "buffer %p is corrupt\n", buf);
			return FAIL;
		}
	}
	print_buf(buf, "befor push");
#endif
	if (buf->full_fl == true) {
		return FULL;
	}
	if (t_tail == t_head && buf->empt_fl != true) {
		buf->full_fl = true;
		return FULL;
	}
	buf->data[t_head] = val;
	t_head++;
	buf->head = t_head & buf->mask;
	buf->empt_fl = false;
#ifdef DEBUG
	print_buf(buf, "after push");
#endif
	return SUCC;
}
int pop(struct buf *buf, int *val)
{
	unsigned int t_head = buf->head, t_tail = buf->tail;
#ifdef DEBUG
	if (buf->full_fl == true || buf->empt_fl == true) {
		if (t_head != t_tail) {
			del(buf);
			fprintf(stderr, "buffer %p is corrupt\n", buf);
			return FAIL;
		}
	}
	print_buf(buf, "befor pop");
#endif
	if (buf->empt_fl == true) {
		return EMPT;
	}
	if (t_tail == t_head && buf->full_fl != true) { /*last value in the buf*/
		buf->empt_fl = true;
		return EMPT;
	}
	*val = buf->data[t_tail];
	buf->data[t_tail] = 0;
	t_tail++;
	buf->tail = t_tail & buf->mask;
	buf->full_fl = false;
#ifdef DEBUG
	print_buf(buf, "after pop");
#endif
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
	buf->size = i;
	buf->mask = i - 1;
#ifdef DEBUG
	printf("size of buffer is: %zu\n", size);
	printf("buf mask is: %d\n", size - 1);
#endif
	buf->full_fl = false, buf->empt_fl = true;
	buf->head = buf->tail = 0;
	return buf;
}

int main(void)
{
#ifdef DEBUG
	extern int EF_ALIGNMENT;
	EF_ALIGNMENT = 0;
#endif
	int i, val;
	struct buf *buf = init(4);
	if (buf == NULL) {
		return 1;
	}
	printf("\n===========\ntest 1: 5 push and wait for empty fl\n===========\n");
	for (i = 1; i <= 5; i++) {
		if (push(buf, i) == FULL) {
			printf("buffer full\n");
			break;
		}
	}
	printf("\n===========\ntest 2: 5 pop and wait for full fl\n===========\n");
	for (i = 1; i <= 5; i++) {
		if (pop(buf, &val) == EMPT) {
			printf("buffer empty\n");
			break;
		}
		printf("pop %d\n", val);
	}
	printf("\n===========\ntest 3: 100 push and pop\n===========\n");
	for (i = 0; i < 20; i++) {
		if (i % 5 == 0) {
			goto POP;
		}
PUSH:
		if (push(buf, i) != SUCC) {
			sleep(1);
			goto POP;
		}
	}
	goto END;
POP:
		if (pop(buf, &val) != SUCC) {
			sleep(1);
			goto PUSH;
		} else {
			printf("pop val = %d\n", val);
		}
		goto POP;
END:
	if (del(buf) != SUCC) {
		fprintf(stderr, "cannot free buffer\n");
		return 1;
	}
	return 0;
}
