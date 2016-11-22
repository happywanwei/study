/* ���ڽӾ����ʾ��ͼ������������εķǵݹ��㷨*/

#include<stdio.h>
#include<stdlib.h>

#define MAXVEX 6
#define MAX 0
#define  NON  -1

typedef char VexType;
typedef float AdjType;

typedef struct {
    int n;                                           /* ͼ�Ķ������ */
    /*VexType vexs[MAXVEX];                   ������Ϣ */
    AdjType arcs[MAXVEX][MAXVEX];           /* ����Ϣ */
} GraphMatrix;


int  firstVertex(GraphMatrix* pgraph) {    
    if(pgraph->n == 0)
        return NON;
    else return 0;
}

int  nextVertex(GraphMatrix* pgraph,int n) {    
    if(n==pgraph->n-1)
        return NON;
    else return n+1;
}

int  firstAdjacent(GraphMatrix* pgraph, int i) {
    int k;
    for(k=0;k<pgraph->n;k++)
        if(pgraph->arcs[i][k]!=0) return k;
    return NON; 
}  

int  nextAdjacent(GraphMatrix* pgraph, int i, int j) {
    int k;
    for(k=j+1; k<pgraph->n; k++)
        if(pgraph->arcs[i][k]!=0) return k;
    return NON; 
}   

typedef int Vertex;
#define TRUE 1
#define FALSE 0

typedef struct {
    Vertex v;
    Vertex k;
} DataType;

#define MAXNUM 20     /* ջ�����Ԫ�ظ��� */
struct  SeqStack {	  /* ˳��ջ���Ͷ��� */
	int  t; 			/* ָʾջ��λ�� */
	DataType  s[MAXNUM];
};

typedef  struct SeqStack  *PSeqStack;	/* ˳��ջ���͵�ָ������ */

/*����һ����ջ;Ϊջ�ṹ����ռ䣬����ջ��������ֵΪ-1*/
PSeqStack  createEmptyStack_seq( void ) {
    PSeqStack pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack == NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return  (pastack);
}

/*�ж�pastack��ָ��ջ�Ƿ�Ϊ��ջ����pastack��ָ��ջΪ��ջʱ���򷵻�1�����򷵻�0*/
int  isEmptyStack_seq( PSeqStack pastack ) {
    return pastack->t == -1;
}

/* ��ջ��ѹ��һԪ��x */
void  push_seq( PSeqStack pastack, DataType x ) {
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
DataType  top_seq( PSeqStack pastack ) {
    return pastack->s[pastack->t];
}

int visited[MAXVEX];
void dfs ( GraphMatrix* g , Vertex v );

void dft ( GraphMatrix* g ) {
    Vertex v ;
    for ( v = firstVertex ( g ) ; v != NON ; v = nextVertex ( g , v ) )
        if ( visited[v] == FALSE ) dfs ( g , v ) ;
}

void dfs ( GraphMatrix* g , Vertex v ) {
    DataType element;
    Vertex v1,v2;
    PSeqStack s ;       
    s = createEmptyStack_seq ( ) ;
    element.v = v;
    element.k = firstAdjacent(g, v);
    push_seq ( s, element) ;
    printf("%d ", v);
    visited[v] = TRUE ;
    while ( !isEmptyStack_seq(s) ) {
        element = top_seq ( s ) ;
        pop_seq ( s );
        v1 = element.v;
        v2 = element.k;
        while (v2 != NON ) {
            if ( visited[v2] == FALSE ) {
                element.v = v1;
                element.k = v2;
                push_seq ( s,  element);
                visited[v2] = TRUE ;
                printf("%d ", v2);
                v1 = v2;
                v2 = firstAdjacent(g, v1);
            }
            else v2 = nextAdjacent(g , v1 , v2) ;
        }
    }
}

GraphMatrix graph = {
    6,
    {{0,10,MAX,MAX,19,21},
     {10,0,5,6,MAX,11},
     {MAX,5,0,6,MAX,MAX},
     {MAX,6,6,0,18,14},
     {19,MAX,MAX,18,0,33},
     {21,11,MAX,14,33,0}
    }
};

int main(){
    dft(&graph);
    return 0;
}
