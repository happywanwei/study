/* 线索二叉树的定义,构造算法和中根周游算法*/

#include<stdio.h>
#include<stdlib.h>
typedef int DataType;
struct ThrTreeNode;                         /* 穿线树中的结点 */
typedef struct ThrTreeNode  *PThrTreeNode;	/* 指向穿线树结点的指针类型 */

struct ThrTreeNode {                        /* 穿线树中每个结点的结构 */
    DataType      info;
    PThrTreeNode  llink, rlink;
    int           ltag, rtag;
};

typedef struct ThrTreeNode  *ThrTree;       /* 穿线树类型的定义 */
typedef ThrTree  *PThrTree;                 /* 穿线树类型的指针类型 */

#define  MAXNUM  100            /* 栈中最大元素个数 */
struct  SeqStack {              /* 顺序栈类型定义 */
    int          t; 
    PThrTreeNode s[MAXNUM];
};
typedef struct SeqStack *PSeqStack;		/* 栈类型的指针类型 */

/*创建一个空栈;为栈结构申请空间，并将栈顶变量赋值为-1*/
PSeqStack  createEmptyStack_seq( void ) {
    PSeqStack pastack;
    pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack == NULL)
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
void  push_seq( PSeqStack pastack, PThrTreeNode x ) {
    if( pastack->t >= MAXNUM - 1  )
        printf( "Overflow! \n" );
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
PThrTreeNode  top_seq( PSeqStack pastack ) {
    return pastack->s[pastack->t];
}

void thread(PThrTree t) {
    PSeqStack  st;				  	
    PThrTreeNode  p;                    /*指向当前正在访问的结点*/
    PThrTreeNode  pr;                   /*指向p的对称序的前驱结点*/ 
     
    if (t == NULL || *t == NULL) return ;
    st = createEmptyStack_seq();        /* 创建空栈 */
    p = *t;
    pr = NULL;
    do {
        while (p != NULL) {             /* 遇到结点推入栈中,然后处理其左子树 */
            push_seq(st,p);
            p = p->llink;
        }
        /* 左子树处理完,从栈顶托出结点并访问 */
        while ( p == NULL && !isEmptyStack_seq(st) ) { 
            p = top_seq(st);
            pop_seq(st);
            if (pr != NULL) {
                if (pr->rlink == NULL) {/* 检查前驱结点的右指针 */
                    pr->rlink = p;
                    pr->rtag = 1;
                }
                if (p->llink == NULL) { /* 检查该结点的左指针 */
                    p->llink = pr;
                    p->ltag = 1;
                }
            }
            pr = p;
            p = p->rlink;               /* 处理右子树 */
        }
    } while ( !isEmptyStack_seq(st) || p != NULL );
    free(st);                           /* 释放栈空间 */
}

void visit(PThrTreeNode  p) { printf("%d ", p->info); }

/* 按对称序周游对称序穿线树*/
void nInOrder( PThrTree t ) {
    PThrTreeNode  p;
    if (t == NULL || *t == NULL) return ;
    p = *t;
    while ( p->llink != NULL && p->ltag == 0 )      /* 顺左子树一直向下 */
        p = p->llink;
    while (p != NULL) { 
        visit(p);
        if( p->rlink != NULL && p->rtag == 0 ) {    /* 右子树不是线索时 */
            p = p->rlink;
            while( p->llink != NULL && p->ltag == 0 )/* 顺右子树的左子树一直向下 */
                p = p->llink;
        } 
        else
            p = p->rlink;                           /* 顺线索向下 */
    }
}  

int main(){
    return 0;
}
