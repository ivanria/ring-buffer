#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

#include <stdbool.h>
#include <stdlib.h>

typedef enum {
	RBSUCC = 0,
	RBEMPT = -1,
	RBFULL = -2,
	RBERR  = -3
} RBRetCod_t;

typedef unsigned char* RBufDat_t; /* pointer to data */
typedef unsigned int RBufPoint_t; /* head and tail pointers */
typedef size_t RBufSiz_t; /* size of buffer */
typedef struct {
	RBufSiz_t size; /*size and mask*/
	RBufDat_t rbufdat; /*pointer to buffer*/
	RBufPoint_t head, tail; /*head and tail pointers*/
} RBuf_t;

RBRetCod_t RBufInit(size_t size, RBuf_t *rbufp);
RBRetCod_t RBufDeInit(void);
int RBufNum(void);
RBRetCod_t RBufDelN(int n)
RBRetCod_t RBufPush(unsigned char dat);
RBRetCod_t RBufPull(unsigned char *dat);

#endif /*_RING_BUFFER_H*/
