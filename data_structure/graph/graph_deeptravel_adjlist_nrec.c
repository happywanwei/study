/* 用邻接表表示的图的深度优先周游的非递归算法*/


#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 20

typedef struct EdgeNode EdgeNode;
typedef struct EdgeNode * PEdgeNode;
typedef struct EdgeNode * EdgeList;
struct EdgeNode {
    int endvex;			/* 相邻顶点字段 */
    PEdgeNode nextedge;	/* 链字段 */
};  					/* 边表中的结点 */

typedef struct {
    /*VexType vertex;*/		/* 顶点信息 */
    EdgeList edgelist;		/* 边表头指针 */
} VexNode;				/* 顶点表中的结点 */

typedef struct {
    int n;				/* 图的顶点个数 */
    VexNode vexs[MAXVEX];
} GraphList;

/* 边的插入算法*/
void insert(GraphList* p,int a,int b) {
    EdgeList pp;
    PEdgeNode temp;
    temp = (PEdgeNode)malloc(sizeof(EdgeNode));
    temp->endvex = b;
    temp->nextedge = NULL;
    pp = p->vexs[a].edgelist;
    if (pp == NULL)
        p->vexs[a].edgelist = temp;
    else {
        while (pp->nextedge != NULL)
            pp = pp->nextedge;
        pp->nextedge = temp;
    }
}
	
/* 实例邻接表的构造 */
GraphList* makeList() {
    GraphList* p;
    int i;
    p = (GraphList*)malloc(sizeof(GraphList));
    p->n = 8;
    for (i = 0; i < p->n; i++)
        p->vexs[i].edgelist = NULL;
    insert(p,0,1);
    insert(p,0,2);
    insert(p,1,3);
    insert(p,1,4);
    insert(p,2,5);
    insert(p,2,6);
    insert(p,3,7);
    insert(p,4,7);
    insert(p,5,6);
    return p;
}

#define NON  -1

int firstVertex(GraphList* pgraph) {
    if(pgraph->n == 0)
        return NON;
    else return 0;
}

int  nextVertex(GraphList* pgraph,int n) {    
    if (n == pgraph->n - 1)
        return NON;
    else return n+1;
}

int firstAdjacent(GraphList* pgraph, int i) {
    if(pgraph->vexs[i].edgelist != NULL)
        return pgraph->vexs[i].edgelist->endvex;
    else return NON; 
}  

int nextAdjacent(GraphList* pgraph, int i, int j) {
    PEdgeNode p;
    for(p = pgraph->vexs[i].edgelist; p != NULL; p = p->nextedge)
        if(p->endvex==j) {
            if(p->nextedge!=NULL)
                return p->nextedge->endvex;
            else 
                return NON;
        }
    return NON; 
}

typedef int Vertex;
#define TRUE 1
#define FALSE 0

typedef struct {
    Vertex v;
    Vertex k;
} DataType;

#define MAXNUM 20   /* 栈中最大元素个数 */
struct  SeqStack {	/* 顺序栈类型定义 */
    int  t; 		/* 指示栈顶位置 */
    DataType  s[MAXNUM];
};

typedef  struct SeqStack  *PSeqStack;	/* 顺序栈类型的指针类型 */ 

/*创建一个空栈;为栈结构申请空间，并将栈顶变量赋值为-1*/
PSeqStack  createEmptyStack_seq( void ) {
    PSeqStack pastack;
    pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack == NULL)
        printf("Out of space!\n");
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
    return (pastack->s[pastack->t]);
}


int visited[MAXVEX];

void dfs ( GraphList* g , Vertex v );

void dft ( GraphList* g ) {
    Vertex v ;
    for ( v = firstVertex ( g ) ; v != NON ; v = nextVertex ( g , v ) )
        if ( visited[v] == FALSE ) dfs ( g , v ) ;
}

void dfs ( GraphList* g , Vertex v ) {
    DataType element;
    Vertex v1, v2;
    PSeqStack s ;       
    s = createEmptyStack_seq ( ) ;
    element.v = v;
    element.k = firstAdjacent(g, v);
    push_seq(s ,element) ;
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
                push_seq (s, element);
                visited[v2] = TRUE ;
                printf("%d ", v2);
                v1 = v2;
                v2 = firstAdjacent(g, v1);
            }
            else 
                v2 = nextAdjacent(g , v1 , v2) ;
        }
    }
}

int main(){
    GraphList* p = makeList();
    dft(p);
    return 0;
}
