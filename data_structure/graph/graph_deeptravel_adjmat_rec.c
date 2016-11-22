/* 用邻接矩阵表示的图的深度优先周游的递归算法*/


#include<stdio.h>
#define MAXVEX 6
#define MAX 0
#define NON -1

typedef char VexType;
typedef float AdjType;

typedef struct {
    int n;                                           /* 图的顶点个数 */
    /*VexType vexs[MAXVEX];                   顶点信息 */
    AdjType arcs[MAXVEX][MAXVEX];           /* 边信息 */
} GraphMatrix;


int  firstVertex(GraphMatrix* pgraph) {    
    if (pgraph->n == 0)
        return NON;
    else return 0;
}

int  nextVertex(GraphMatrix* pgraph,int n) {    
    if (n == pgraph->n-1)
        return NON;
    else return n+1;
}

int  firstAdjacent(GraphMatrix* pgraph, int i) {
    int k;
    for (k = 0; k < pgraph->n; k++)
        if (pgraph->arcs[i][k] != 0) return k;
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

int visited[MAXVEX];
void dfs ( GraphMatrix* g , Vertex v );

void dft ( GraphMatrix* g ) {
    Vertex v ;
    for ( v =firstVertex ( g ) ; v != NON ; v = nextVertex ( g , v ) )
        if ( visited[v] == FALSE ) dfs ( g , v ) ;
}

void dfs ( GraphMatrix* g , Vertex v ) {
    Vertex v1;
    visited[v] = TRUE ;
    printf("%d ",v);
    for ( v1 = firstAdjacent(g , v); v1 != NON ; v1=nextAdjacent(g ,v, v1) )
        if(visited[v1]==FALSE) dfs ( g ,v1 );
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
