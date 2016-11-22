/* 顺序栈表示：函数定义 */

#include <stdio.h>
#include <stdlib.h>

#include "sstack.h"

/*创建一个空栈;为栈结构申请空间，并将栈顶变量赋值为-1*/
PSeqStack  createEmptyStack_seq( void ) {  
    PSeqStack pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack==NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return pastack;
}

/*判断pastack所指的栈是否为空栈，当pastack所指的栈为空栈时，则返回1，否则返回0*/
int  isEmptyStack_seq( PSeqStack pastack ) {
    return pastack->t == -1;
}

/* 在栈中压入一元素x */
void  push_seq( PSeqStack pastack, DataType x ) {  
    if( pastack->t >= MAXNUM - 1  )
        printf( "Stack Overflow! \n" );
    else {  
        pastack->t++;
        pastack->s[pastack->t] = x;
    }
}

/* 删除栈顶元素 */
void  pop_seq( PSeqStack pastack ) {  	
    if (pastack->t == -1 )
        printf( "Underflow!\n" );
    else
        pastack->t--;
}

/* 当pastack所指的栈不为空栈时，求栈顶元素的值 */
DataType top_seq( PSeqStack pastack ) {
    return pastack->s[pastack->t];
}

