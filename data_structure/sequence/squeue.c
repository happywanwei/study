/* ���е�˳���ʾ���������� */

#include <stdio.h>
#include <stdlib.h>

#include "squeue.h"

/*����һ���ն���*/
PSeqQueue  createEmptyQueue_seq( void ) {  
    PSeqQueue paqu = (PSeqQueue)malloc(sizeof(struct SeqQueue));
    if (paqu==NULL)
        printf("Out of space!! \n");
    else
        paqu->f = paqu->r = 0;
    return paqu;
}

/*�ж����Ƿ�Ϊ�ն���*/
int  isEmptyQueue_seq( PSeqQueue paqu ) {
    return paqu->f == paqu->r;
}

/* �ڶ����в���һԪ��x */
void  enQueue_seq( PSeqQueue paqu, DataType x ) {
    if( (paqu->r + 1) % MAXNUM == paqu->f  )
        printf( "Full queue.\n" );
    else 	{
        paqu->q[paqu->r] = x;
        paqu->r = (paqu->r + 1) % MAXNUM;
    }
}

/* ɾ������ͷ��Ԫ�� */
void  deQueue_seq( PSeqQueue paqu ) {
    if( paqu->f == paqu->r )
        printf( "Empty Queue.\n" );
    else
        paqu->f = (paqu->f + 1) % MAXNUM;
}

/* �Էǿն���,�����ͷ��Ԫ�� */
DataType  frontQueue_seq( PSeqQueue paqu ) {
    return paqu->q[paqu->f];
}

