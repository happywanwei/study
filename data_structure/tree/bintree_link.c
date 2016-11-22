/* �����������ӱ�ʾ*/

#include<stdlib.h>
#include<stdio.h>

typedef int DataType;

struct BinTreeNode;	                        /* �������н�� */
typedef  struct BinTreeNode	 *PBinTreeNode;	/* ����ָ������ */

struct BinTreeNode { 
    DataType  info;	                        /* ������ */
    PBinTreeNode llink;                     /* ָ������Ů */
    PBinTreeNode rlink;                     /* ָ������Ů */
};

typedef  struct BinTreeNode  *BinTree;

typedef  BinTree  *PBinTree;

PBinTreeNode root_btree(PBinTree t) {
    return *t;
}

PBinTreeNode leftChild_btree (PBinTreeNode p) {
    return p->llink;
}

PBinTreeNode rightChild_btree (PBinTreeNode p) {
    return p->rlink;
}

/*�����㷨�����Ƚ�����������Ϊ����Ķ�������
Ȼ���ȸ��������ε�˳�����������Ϣ,
����һ��˫���洢�Ķ������Ĺ���*/

/* �ݹ鴴���Ӹ���ʼ�Ķ����� */
PBinTreeNode createRest_BTree() { 
    PBinTreeNode  pbnode;
    char ch;
    scanf("%c", &ch);
    if(ch == '@') pbnode = NULL;
    else { 
        pbnode = (PBinTreeNode )malloc(sizeof(struct BinTreeNode));
        if( pbnode == NULL )         {
            printf("Out of space!\n");
            return pbnode;
        }
        pbnode->info = ch;
        pbnode->llink = createRest_BTree();	/* ���������� */
        pbnode->rlink = createRest_BTree();	/* ���������� */
    }
    return pbnode;
}


/* ���������Ķ����� */
PBinTree  create_BTree( void ) { 
    PBinTree pbtree;
    pbtree = (PBinTree)malloc(sizeof(BinTree));
    if (pbtree != NULL)
        *pbtree = createRest_BTree( );  /* �ݹ鴴���Ӹ���ʼ�Ķ����� */
    return pbtree; 
}


int main(){
	return 0;
}
