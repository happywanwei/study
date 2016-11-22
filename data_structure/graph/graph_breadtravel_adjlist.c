/* ���ڽӱ��ʾ��ͼ�Ĺ�����������㷨*/

#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 20

typedef struct EdgeNode EdgeNode;
typedef struct EdgeNode * PEdgeNode;
typedef struct EdgeNode * EdgeList;
struct EdgeNode {
    int endvex;			/* ���ڶ����ֶ� */
    PEdgeNode nextedge;	/* ���ֶ� */
};						/* �߱��еĽ�� */
typedef struct {
    /*VexType vertex;*/		/* ������Ϣ */
    EdgeList edgelist;		/* �߱�ͷָ�� */
} VexNode;				/* ������еĽ�� */

typedef struct {
    int n;				/* ͼ�Ķ������ */
    VexNode vexs[MAXVEX];
} GraphList;

/* �ߵĲ����㷨*/
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
        while(pp->nextedge != NULL)
            pp = pp->nextedge;
        pp->nextedge = temp;
    }
}
	
/* ʵ���ڽӱ�Ĺ��� */
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


#define  MAXNUM   20/* ���������Ԫ�ظ��� */
typedef int DataType;
struct SeqQueue {		/* ˳��������Ͷ��� */
    int  f, r;
    DataType  q[MAXNUM];
};

typedef  struct SeqQueue  *PSeqQueue;	/* ˳��������͵�ָ������ */

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

/* �ڶ����в���һԪ��x */
void  enQueue_seq( PSeqQueue paqu, DataType x ) {
    if( (paqu->r + 1) % MAXNUM == paqu->f  )
        printf( "Full queue.\n" );
    else {
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
    return (paqu->q[paqu->f]);
}


#define NON -1

int  firstVertex(GraphList* pgraph) {    
    if (pgraph->n == 0)
        return NON;
    else return 0;
}

int  nextVertex(GraphList* pgraph,int n) {    
    if (n == pgraph->n - 1)
        return NON;
    else return n+1;
}

int  firstAdjacent(GraphList* pgraph, int i) {
    if (pgraph->vexs[i].edgelist != NULL)
        return pgraph->vexs[i].edgelist->endvex;
    else return NON; 
}  

int nextAdjacent(GraphList* pgraph, int i, int j) {
    PEdgeNode p;
    for (p = pgraph->vexs[i].edgelist; p != NULL; p = p->nextedge)
        if (p->endvex == j) {
            if (p->nextedge != NULL)
                return p->nextedge->endvex;
            else 
                return NON;
        }
    return NON; 
}   

typedef int Vertex;
#define TRUE 1
#define FALSE 0

int visited[MAXVEX];

void bfs ( GraphList* g , Vertex v );
void bft ( GraphList* g ) {
    Vertex v ;
    for ( v = firstVertex ( g ) ; v != NON ; v = nextVertex ( g , v ) )
        if ( visited[v] == FALSE ) bfs ( g , v ) ;
} 

void bfs ( GraphList* g , Vertex v ) {
    Vertex v1 , v2;
    PSeqQueue q  = createEmptyQueue_seq ( ) ;   /* ����Ԫ�ص�����ΪVertex* */

    enQueue_seq ( q ,v ) ;
    printf("%d ",v);
    visited[v] = TRUE ;

    while ( !isEmptyQueue_seq(q) ) {
        v1 = frontQueue_seq ( q ) ;
        deQueue_seq ( q );
        v2 = firstAdjacent ( g ,v1 );

        while ( v2 != NON ) {
            if ( visited[v2] == FALSE ) {
                enQueue_seq ( q,  v2 );
                visited[v2] = TRUE ;
                printf("%d ",v2);
            }
            v2 = nextAdjacent ( g , v1 , v2 ) ;
        }
    }
}

int main(){
    GraphList* p = makeList();
    bft(p);
    return 0;
}
