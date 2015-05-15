#ifndef _RING_BUFFER_H
#define _RING_BUFFER_H

#include <stdlib.h>

typedef enum {
	RBSUCC = 0,
	RBEMPT = -1,
	RBFULL = -2,
	RBERR  = -3
} RBRetCod_t;

typedef int RBId_t;
typedef unsigned char RBDatUnit_t;
typedef unsigned char* RBScope_t; /* pointer to data */
typedef unsigned int RBPoint_t; /* head and tail pointers */
typedef size_t RBSiz_t; /* size of buffer */
typedef struct * {
	RBSiz_t size; /*size and mask*/
	RBScope_t bufdat; /*pointer to buffer*/
	RBPoint_t head, tail; /*head and tail pointers*/
} RB_t;

RBRetCod_t RBInit(RBSiz_t size, RBId_t *id);
RBRetCod_t RBDeInit(void);
RBRetCod_t RBPush(RBDatUnit dat);
RBRetCod_t RBPull(RBDatUnit *dat);

#endif /*_RING_BUFFER_H*/
