/* 队列的顺序表示：函数定义 */

#include <stdio.h>
#include <stdlib.h>

#include "squeue.h"

/*创建一个空队列*/
PSeqQueue  createEmptyQueue_seq( void ) {  
    PSeqQueue paqu = (PSeqQueue)malloc(sizeof(struct SeqQueue));
    if (paqu==NULL)
        printf("Out of space!! \n");
    else
        paqu->f = paqu->r = 0;
    return paqu;
}

/*判队列是否为空队列*/
int  isEmptyQueue_seq( PSeqQueue paqu ) {
    return paqu->f == paqu->r;
}

/* 在队列中插入一元素x */
void  enQueue_seq( PSeqQueue paqu, DataType x ) {
    if( (paqu->r + 1) % MAXNUM == paqu->f  )
        printf( "Full queue.\n" );
    else 	{
        paqu->q[paqu->r] = x;
        paqu->r = (paqu->r + 1) % MAXNUM;
    }
}

/* 删除队列头部元素 */
void  deQueue_seq( PSeqQueue paqu ) {
    if( paqu->f == paqu->r )
        printf( "Empty Queue.\n" );
    else
        paqu->f = (paqu->f + 1) % MAXNUM;
}

/* 对非空队列,求队列头部元素 */
DataType  frontQueue_seq( PSeqQueue paqu ) {
    return paqu->q[paqu->f];
}

