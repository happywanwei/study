/* 用邻接矩阵表示的图的广度优先周游算法*/

#include<stdio.h>
#include<stdlib.h>

#define MAXVEX 6
#define MAX 0

typedef char VexType;
typedef float AdjType;

typedef struct {
    int n;                                           /* 图的顶点个数 */
    /*VexType vexs[MAXVEX];                   顶点信息 */
    AdjType arcs[MAXVEX][MAXVEX];           /* 边信息 */
} GraphMatrix;

#define  MAXNUM   8/* 队列中最大元素个数 */
typedef int DataType;
struct  SeqQueue {		/* 顺序队列类型定义 */
    int  f, r;
    DataType  q[MAXNUM];
};

typedef  struct SeqQueue  *PSeqQueue;	/* 顺序队列类型的指针类型 */

PSeqQueue  createEmptyQueue_seq( void ) {  
    PSeqQueue paqu;
    paqu = (PSeqQueue)malloc(sizeof(struct SeqQueue));
    if (paqu == NULL)
        printf("Out of space!! \n");
    else 
        paqu->f = paqu->r = 0;

    return paqu;
}

int isEmptyQueue_seq( PSeqQueue paqu ) {
    return paqu->f == paqu->r;
}

/* 在队列中插入一元素x */
void  enQueue_seq( PSeqQueue paqu, DataType x ) {
    if( (paqu->r + 1) % MAXNUM == paqu->f  )
        printf( "Full queue.\n" );
    else {
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
    return (paqu->q[paqu->f]);
}

#define NON  -1

int firstVertex(GraphMatrix* pgraph) {    
    if (pgraph->n == 0)
        return NON;
    else return 0;

}

int nextVertex(GraphMatrix* pgraph,int n) {    
    if (n == pgraph->n-1)
        return NON;
    else return n + 1;
}

int firstAdjacent(GraphMatrix* pgraph, int i) {
    int k;
    for (k = 0; k < pgraph->n; k++)
        if(pgraph->arcs[i][k] != 0) return k;
    return NON; 
}  


int nextAdjacent(GraphMatrix* pgraph, int i, int j) {
    int k;
    for (k = j+1; k < pgraph->n; k++)
        if (pgraph->arcs[i][k] != 0) return k;
    return NON; 
}   

typedef int Vertex;
#define TRUE 1
#define FALSE 0

int visited[MAXVEX];

void bfs ( GraphMatrix* g , Vertex v );
void bft ( GraphMatrix* g ) {
    Vertex v ;
    for ( v =firstVertex ( g ) ; v != NON ; v = nextVertex ( g , v ) )
        if ( visited[v] == FALSE ) bfs ( g , v ) ;
} 

void bfs ( GraphMatrix* g , Vertex v ) {
    Vertex v1 , v2;
    PSeqQueue q = createEmptyQueue_seq();       /* 队列元素的类型为Vertex* */

    enQueue_seq ( q, v ) ;
    printf("%d ", v);
    visited[v] = TRUE ;

    while ( !isEmptyQueue_seq(q) ) {
        v1 = frontQueue_seq ( q ) ;
        deQueue_seq ( q );
        v2 = firstAdjacent ( g, v1 );

        while ( v2!= NON ) {
            if ( visited[v2] == FALSE ) {
                enQueue_seq ( q,  v2 );
                visited[v2] = TRUE ;
                printf("%d ", v2);
            }
            v2 = nextAdjacent ( g, v1 , v2 ) ;
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
    bft(&graph);
    return 0;
}
