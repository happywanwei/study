/* 用邻接矩阵表示的图的深度优先周游的非递归算法*/

#include<stdio.h>
#include<stdlib.h>

#define MAXVEX 6
#define MAX 0
#define  NON  -1

typedef char VexType;
typedef float AdjType;

typedef struct {
    int n;                                           /* 图的顶点个数 */
    /*VexType vexs[MAXVEX];                   顶点信息 */
    AdjType arcs[MAXVEX][MAXVEX];           /* 边信息 */
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

#define MAXNUM 20     /* 栈中最大元素个数 */
struct  SeqStack {	  /* 顺序栈类型定义 */
	int  t; 			/* 指示栈顶位置 */
	DataType  s[MAXNUM];
};

typedef  struct SeqStack  *PSeqStack;	/* 顺序栈类型的指针类型 */

/*创建一个空栈;为栈结构申请空间，并将栈顶变量赋值为-1*/
PSeqStack  createEmptyStack_seq( void ) {
    PSeqStack pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack == NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return  (pastack);
}

/*判断pastack所指的栈是否为空栈，当pastack所指的栈为空栈时，则返回1，否则返回0*/
int  isEmptyStack_seq( PSeqStack pastack ) {
    return pastack->t == -1;
}

/* 在栈中压入一元素x */
void  push_seq( PSeqStack pastack, DataType x ) {
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
