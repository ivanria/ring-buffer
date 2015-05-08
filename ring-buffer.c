#include "ring-buffer.h"

RBRetCod_t RBufInit(size_t size)
{
	size_t i;
	if ((RBufP = malloc(sizeof(RBuf_t))) == NULL) {
		perror("cannot allocate Ring Buffer:");
		return RBERR;
	}
	if (size < 4 || size > 256) {
		fprintf(stderr, "size of buffer may be > 4 or < 256, you size is: %zu\n", size);
		free(RBufP);
		return RBERR;
	}
	for (i = 1; i < size; i *= 2);
	rbufp->size = i - 1;
	rbufp->head = rbufp->tail = 0;
	if ((rbufp->rbufdat = malloc(sizeof(unsigned char) * i)) == NULL) {
		perror("cannot allocate Ring Buffer:");
		free(rbufp);
		return RBERR;
	}
	return RBSUCC;
}

RBRetCod_t RBufPull(unsigned char *dat)
{
	return RBSUCC;
}

RBRetCod_t RBufDelN(int n)
{

}

RBRetCod_t RBufPush(unsigned char dat)
{
	return RBSUCC;
}

int RBufNum(void)
{

	int i;
	for (i = 0; rbufp[i] != NULL; i++);
	return i;
}
