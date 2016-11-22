/* ˳��ջ��ʾ���������� */

#include <stdio.h>
#include <stdlib.h>

#include "sstack.h"

/*����һ����ջ;Ϊջ�ṹ����ռ䣬����ջ��������ֵΪ-1*/
PSeqStack  createEmptyStack_seq( void ) {  
    PSeqStack pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack==NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return pastack;
}

/*�ж�pastack��ָ��ջ�Ƿ�Ϊ��ջ����pastack��ָ��ջΪ��ջʱ���򷵻�1�����򷵻�0*/
int  isEmptyStack_seq( PSeqStack pastack ) {
    return pastack->t == -1;
}

/* ��ջ��ѹ��һԪ��x */
void  push_seq( PSeqStack pastack, DataType x ) {  
    if( pastack->t >= MAXNUM - 1  )
        printf( "Stack Overflow! \n" );
    else {  
        pastack->t++;
        pastack->s[pastack->t] = x;
    }
}

/* ɾ��ջ��Ԫ�� */
void  pop_seq( PSeqStack pastack ) {  	
    if (pastack->t == -1 )
        printf( "Underflow!\n" );
    else
        pastack->t--;
}

/* ��pastack��ָ��ջ��Ϊ��ջʱ����ջ��Ԫ�ص�ֵ */
DataType top_seq( PSeqStack pastack ) {
    return pastack->s[pastack->t];
}

