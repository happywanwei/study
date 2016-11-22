/* ���Ա�ĵ������ʾ������ʵ��*/

#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

/* ����һ����ͷ���Ŀ����� */
LinkList  createNullList_link( void ) {   
    LinkList llist;
    llist = (LinkList)malloc( sizeof( struct Node ) );	/* �����ͷ���ռ� */
    if( llist != NULL ) llist->link = NULL;
    return llist;
}

/* ��llist��ͷ���ĵ��������±�Ϊi��(��i+1��)���ǰ����Ԫ��x */
int insert_link(LinkList llist, int i, DataType x) { 
    PNode p = llist, q;
    int j;
    for (j = 0 ; p != NULL && j < i; j++)		/* ���±�Ϊi-1��(��i��)��� */
        p = p->link;
 	  
    if (j != i) {								/* i<1���ߴ��ڱ� */
        printf("Index of link-list is out of range.\n",i);
  	 	return 0;
    }
 	  
    q = (PNode)malloc( sizeof( struct Node ) );	/* �����½�� */
    if( q == NULL ) { 
        printf( "Out of space!\n" );
        return 0;
    }
    									/* ���������� */
    q->info = x;
    q->link = p->link;
    p->link = q;						/* ע��þ�������Ͼ��ִ�� */
    return 1 ;
}

/* ��llist����ͷ���ĵ�������ɾ����һ��ֵΪx�Ľ�� */
/* ��ʱҪ�� DataType ������ != �Ƚ� */
int delete_link( LinkList llist, DataType x ) { 
    PNode p = llist, q;      	
    /*��ֵΪx�Ľ���ǰ�����Ĵ洢λ�� */
    while( p->link != NULL && p->link->info != x )
        p = p->link;
       	
    if( p->link == NULL ) {  	/* û�ҵ�ֵΪx�Ľ�� */
        printf("Datum does not exist!\n ");
        return 0;
    }
    
    q = p->link;	  			/* �ҵ�ֵΪx�Ľ�� */
    p->link = p->link->link;  	/* ɾ���ý�� */
    free( q );      
    return 1; 
}

/* ��llist����ͷ���ĵ��������ҵ�һ��ֵΪx�Ľ��洢λ�� */
/* �Ҳ���ʱ���ؿ�ָ�� */
PNode locate_link( LinkList llist, DataType x ) { 
    PNode p;
    if (llist == NULL)  return NULL;
    
    for ( p = llist->link; p != NULL && p->info != x; )
        p = p->link;
    return p;
}

/* �ڴ���ͷ���ĵ�����llist���±�Ϊi��(��i+1��)���Ĵ洢λ�� */
/* ���������±�Ϊi��(��i+1��)Ԫ��ʱ������ֵΪNULL */
PNode find_link( LinkList llist, int i ) { 
    PNode p;
    int j;
    if (i < 0) {					/* ���i��ֵ */
        printf("Index of link-list is out of range.\n",i);
        return NULL;
    }
	  
    for ( p = llist->link, j = 0; p != NULL && j < i; j++) 
        p = p->link;

    if (p == NULL) 
        printf("Index of link-list is out of range.\n", i);

    return p;
}

/* �ж�llist����ͷ���ĵ������Ƿ��ǿ����� */
int  isNullList_link( LinkList llist) {     
    return llist == NULL || llist->link == NULL;
}

