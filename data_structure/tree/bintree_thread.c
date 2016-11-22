/* �����������Ķ���,�����㷨���и������㷨*/

#include<stdio.h>
#include<stdlib.h>
typedef int DataType;
struct ThrTreeNode;                         /* �������еĽ�� */
typedef struct ThrTreeNode  *PThrTreeNode;	/* ָ����������ָ������ */

struct ThrTreeNode {                        /* ��������ÿ�����Ľṹ */
    DataType      info;
    PThrTreeNode  llink, rlink;
    int           ltag, rtag;
};

typedef struct ThrTreeNode  *ThrTree;       /* ���������͵Ķ��� */
typedef ThrTree  *PThrTree;                 /* ���������͵�ָ������ */

#define  MAXNUM  100            /* ջ�����Ԫ�ظ��� */
struct  SeqStack {              /* ˳��ջ���Ͷ��� */
    int          t; 
    PThrTreeNode s[MAXNUM];
};
typedef struct SeqStack *PSeqStack;		/* ջ���͵�ָ������ */

/*����һ����ջ;Ϊջ�ṹ����ռ䣬����ջ��������ֵΪ-1*/
PSeqStack  createEmptyStack_seq( void ) {
    PSeqStack pastack;
    pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack == NULL)
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
void  push_seq( PSeqStack pastack, PThrTreeNode x ) {
    if( pastack->t >= MAXNUM - 1  )
        printf( "Overflow! \n" );
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
PThrTreeNode  top_seq( PSeqStack pastack ) {
    return pastack->s[pastack->t];
}

void thread(PThrTree t) {
    PSeqStack  st;				  	
    PThrTreeNode  p;                    /*ָ��ǰ���ڷ��ʵĽ��*/
    PThrTreeNode  pr;                   /*ָ��p�ĶԳ����ǰ�����*/ 
     
    if (t == NULL || *t == NULL) return ;
    st = createEmptyStack_seq();        /* ������ջ */
    p = *t;
    pr = NULL;
    do {
        while (p != NULL) {             /* �����������ջ��,Ȼ������������ */
            push_seq(st,p);
            p = p->llink;
        }
        /* ������������,��ջ���г���㲢���� */
        while ( p == NULL && !isEmptyStack_seq(st) ) { 
            p = top_seq(st);
            pop_seq(st);
            if (pr != NULL) {
                if (pr->rlink == NULL) {/* ���ǰ��������ָ�� */
                    pr->rlink = p;
                    pr->rtag = 1;
                }
                if (p->llink == NULL) { /* ���ý�����ָ�� */
                    p->llink = pr;
                    p->ltag = 1;
                }
            }
            pr = p;
            p = p->rlink;               /* ���������� */
        }
    } while ( !isEmptyStack_seq(st) || p != NULL );
    free(st);                           /* �ͷ�ջ�ռ� */
}

void visit(PThrTreeNode  p) { printf("%d ", p->info); }

/* ���Գ������ζԳ�������*/
void nInOrder( PThrTree t ) {
    PThrTreeNode  p;
    if (t == NULL || *t == NULL) return ;
    p = *t;
    while ( p->llink != NULL && p->ltag == 0 )      /* ˳������һֱ���� */
        p = p->llink;
    while (p != NULL) { 
        visit(p);
        if( p->rlink != NULL && p->rtag == 0 ) {    /* ��������������ʱ */
            p = p->rlink;
            while( p->llink != NULL && p->ltag == 0 )/* ˳��������������һֱ���� */
                p = p->llink;
        } 
        else
            p = p->rlink;                           /* ˳�������� */
    }
}  

int main(){
    return 0;
}
