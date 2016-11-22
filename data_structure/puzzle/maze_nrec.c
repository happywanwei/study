/* 迷宫问题的非递归算法(栈实现)*/


#define MAXNUM        100/* 栈中最大元素个数 */
#define N 11 /*地图的第一维长度*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int  x;/* 行下标 */
    int  y;/* 列下标 */
    int  d;/* 运动方向 */
} DataType;

struct SeqStack {	  	/* 顺序栈类型定义 */
    int  t; 			/* 指示栈顶位置 */
    DataType  s[MAXNUM];
};

typedef  struct SeqStack  *PSeqStack;	/* 顺序栈类型的指针类型 */
PSeqStack  pastack;					/* pastack是指向顺序栈的一个指针变量 */

PSeqStack  createEmptyStack_seq( void ) {
    PSeqStack pastack;
    pastack = (PSeqStack)malloc(sizeof(struct SeqStack));
    if (pastack == NULL)
        printf("Out of space!! \n");
    else
        pastack->t = -1;
    return pastack;
}

int isEmptyStack_seq( PSeqStack pastack ) {
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

void pushtostack(PSeqStack st, int x, int y, int d) {
    DataType element;
    element.x = x;
    element.y = y;
    element.d = d;
    push_seq(st, element);
}

void printpath(PSeqStack st) {
    DataType element;
    printf("The revers path is:\n");     /* 打印路径上的每一点 */
    while(!isEmptyStack_seq(st)) {
        element = top_seq(st);
        pop_seq(st);
        printf("the node is: %d %d \n", element.x, element.y);
    }
}

/* 迷宫maze[M][N]中求从入口maze[x1][y1]到出口maze[x2][y2]的一条路径 */
/* 其中 1<=x1,x2<=M-2 , 1<=y1,y2<=N-2 */
void mazePath(int maze[][N], int direction[][2], int x1, int y1, int x2, int y2) {
    int i, j, k, g, h;
    PSeqStack st;
    DataType element;
    st = createEmptyStack_seq( );
    maze[x1][y1] = 2;                      /* 从入口开始进入,作标记 */                    
    pushtostack(st, x1, y1, -1);           /* 入口点进栈 */

    while ( !isEmptyStack_seq(st)) {       /* 走不通时,一步步回退 */
        element = top_seq(st);
        pop_seq(st);
        i = element.x; j = element.y; 
        for (k = element.d + 1; k <= 3; k++) {           /* 依次试探每个方向 */
            g = i + direction[k][0];h = j + direction[k][1];
            if (g == x2 && h == y2 && maze[g][h] == 0) { /* 走到出口点 */
                printpath(st);            /* 打印路径 */
                return;
            }
            if (maze[g][h] == 0) {        /* 走到没走过的点 */
                maze[g][h] = 2;           /* 作标记 */
                pushtostack(st, i, j, k); /* 进栈 */
                i = g; j = h; k = -1;     /* 下一点转换成当前点 */
            }
        }
    }
    printf("The path has not been found.\n");/* 栈退完未找到路径 */
}

int main(){
    int direction[][2]={0,1,1,0,0,-1,-1,0};
    int maze[][N] = {
        1,1,1,1,1,1,1,1,1,1,1,
        1,0,1,0,0,1,1,1,0,0,1,
        1,0,0,0,0,0,1,0,0,1,1,
        1,0,1,1,1,0,0,0,1,1,1,
        1,0,0,0,1,0,1,1,0,1,1,
        1,1,0,0,1,0,1,1,0,0,1,
        1,1,1,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1
    };
    mazePath(maze,direction,1,1,6,9);
    getchar();
    return 0;
}

		

