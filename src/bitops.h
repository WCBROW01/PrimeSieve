#ifndef BITOPS_H
#define BITOPS_H

#define INT_WIDTH ( sizeof(int) * 8 )

#define SetBit(A,k)   ( A[k/INT_WIDTH] |=  (1 << (k%INT_WIDTH)) )
#define ClearBit(A,k) ( A[k/INT_WIDTH] &= ~(1 << (k%INT_WIDTH)) )
#define CheckBit(A,k) ( A[k/INT_WIDTH] &   (1 << (k%INT_WIDTH)) )

#endif
