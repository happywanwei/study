/* �ַ��������ӱ�ʾ */

#include<stdio.h>
#include<stdlib.h>

struct StrNode;						/* �����Ľ�� */
typedef struct StrNode *PStrNode;	/* ���ָ������ */

struct StrNode {  					/* �����Ľ��ṹ */
    char      c;
    PStrNode  link;
};

typedef  struct  StrNode  *LinkString;  	/* ���������� */

/*������ͷ���Ŀ�����*/
LinkString  createNullStr_link( void ) {   
    LinkString pst = (LinkString)malloc( sizeof(struct StrNode) );
    if (pst != NULL) pst->link = NULL;
    return (pst);
}

/*�жϴ�ͷ���Ĵ�s�Ƿ�Ϊ�մ�����Ϊ�մ����򷵻�1�����򷵻�0*/
int IsNullStr (LinkString s) {
    return (s->link==NULL);
}

/*���ش�s�ĳ���*/
int length (LinkString s) {
    int len = -1;
    LinkString p = s;
    for ( p=s; p!=NULL; p=p->link ) len++;
    return len;
}

/*���ؽ���s1��s2ƴ����һ�𹹳�һ���´�*/
LinkString concat (LinkString s1, LinkString s2 ) {
    LinkString pst, p1, p2, temp;
    pst = createNullStr_link();
    if (pst != NULL) 	{
        p1 = pst->link;
        for (p2=s1->link;p2!=NULL;p2=p2->link) {
            temp = (LinkString)malloc(sizeof(struct StrNode));  /* !! ��Ҫ��������� */
            temp->c = p2->c;
            temp->link = NULL;
            p1->link = temp;
        }
        p1 = p1->link;
        for ( p2 = s2->link; p2 != NULL; p2 = p2->link) {
            temp = (LinkString)malloc(sizeof(struct StrNode));  /* !! ��Ҫ��������� */
            temp->c = p2->c;
            temp->link = NULL;
            p1->link = temp;
        }
    }
    return pst;
}

/* ���s��ָ�Ĵ�ͷ���������е�i(i>0)���ַ���ʼ����ȡj���ַ������ɵ��Ӵ� */
LinkString subStr_link(LinkString s,int i,int j) {
    PStrNode p,q,t;
    int k;
    LinkString s1 = createNullStr_link( );  /* ���������� */
    if( s1 == NULL ) {	
        printf( "Out of space!\n" );
        return NULL;
    }
    if (i<1 || j<1 ) return(s1);	/* i,jֵ�����ʣ����ؿմ� */

    for (p = s, k = 1; k <= i; k++)  		/*�ҵ�i�����*/
        if ( p != NULL) p = p->link;
        else return s1;
        
    if (p == NULL) return s1;

    for (t = s1, k=1; k<=j; k++) 		 /*����ȡj���ַ�*/
        if (p != NULL) { 
            q = (PStrNode)malloc(sizeof(struct StrNode));
            if (q == NULL) { 
                printf( "Out of space!\n" );
                return(s1);
            }
            q->c = p->c;
            q->link = NULL;
            t->link = q;			/* �������������� */
            t = q;
            p = p->link;
        }
       
    return s1;
}

