/* 字符串的链接表示 */

#include<stdio.h>
#include<stdlib.h>

struct StrNode;						/* 链串的结点 */
typedef struct StrNode *PStrNode;	/* 结点指针类型 */

struct StrNode {  					/* 链串的结点结构 */
    char      c;
    PStrNode  link;
};

typedef  struct  StrNode  *LinkString;  	/* 链串的类型 */

/*创建带头结点的空链串*/
LinkString  createNullStr_link( void ) {   
    LinkString pst = (LinkString)malloc( sizeof(struct StrNode) );
    if (pst != NULL) pst->link = NULL;
    return (pst);
}

/*判断带头结点的串s是否为空串，若为空串，则返回1，否则返回0*/
int IsNullStr (LinkString s) {
    return (s->link==NULL);
}

/*返回串s的长度*/
int length (LinkString s) {
    int len = -1;
    LinkString p = s;
    for ( p=s; p!=NULL; p=p->link ) len++;
    return len;
}

/*返回将串s1和s2拼接在一起构成一个新串*/
LinkString concat (LinkString s1, LinkString s2 ) {
    LinkString pst, p1, p2, temp;
    pst = createNullStr_link();
    if (pst != NULL) 	{
        p1 = pst->link;
        for (p2=s1->link;p2!=NULL;p2=p2->link) {
            temp = (LinkString)malloc(sizeof(struct StrNode));  /* !! 需要检查分配情况 */
            temp->c = p2->c;
            temp->link = NULL;
            p1->link = temp;
        }
        p1 = p1->link;
        for ( p2 = s2->link; p2 != NULL; p2 = p2->link) {
            temp = (LinkString)malloc(sizeof(struct StrNode));  /* !! 需要检查分配情况 */
            temp->c = p2->c;
            temp->link = NULL;
            p1->link = temp;
        }
    }
    return pst;
}

/* 求从s所指的带头结点的链串中第i(i>0)个字符开始连续取j个字符所构成的子串 */
LinkString subStr_link(LinkString s,int i,int j) {
    PStrNode p,q,t;
    int k;
    LinkString s1 = createNullStr_link( );  /* 创建空链串 */
    if( s1 == NULL ) {	
        printf( "Out of space!\n" );
        return NULL;
    }
    if (i<1 || j<1 ) return(s1);	/* i,j值不合适，返回空串 */

    for (p = s, k = 1; k <= i; k++)  		/*找第i个结点*/
        if ( p != NULL) p = p->link;
        else return s1;
        
    if (p == NULL) return s1;

    for (t = s1, k=1; k<=j; k++) 		 /*连续取j个字符*/
        if (p != NULL) { 
            q = (PStrNode)malloc(sizeof(struct StrNode));
            if (q == NULL) { 
                printf( "Out of space!\n" );
                return(s1);
            }
            q->c = p->c;
            q->link = NULL;
            t->link = q;			/* 结点放入子链串中 */
            t = q;
            p = p->link;
        }
       
    return s1;
}

