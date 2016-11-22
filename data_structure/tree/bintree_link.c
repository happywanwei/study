/* 二叉树的链接表示*/

#include<stdlib.h>
#include<stdio.h>

typedef int DataType;

struct BinTreeNode;	                        /* 二叉树中结点 */
typedef  struct BinTreeNode	 *PBinTreeNode;	/* 结点的指针类型 */

struct BinTreeNode { 
    DataType  info;	                        /* 数据域 */
    PBinTreeNode llink;                     /* 指向左子女 */
    PBinTreeNode rlink;                     /* 指向右子女 */
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

/*以下算法就是先将二叉树扩充为扩充的二叉树，
然后按先根次序周游的顺序输入结点的信息,
生成一个双链存储的二叉树的过程*/

/* 递归创建从根开始的二叉树 */
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
        pbnode->llink = createRest_BTree();	/* 构造左子树 */
        pbnode->rlink = createRest_BTree();	/* 构造右子树 */
    }
    return pbnode;
}


/* 创建完整的二叉树 */
PBinTree  create_BTree( void ) { 
    PBinTree pbtree;
    pbtree = (PBinTree)malloc(sizeof(BinTree));
    if (pbtree != NULL)
        *pbtree = createRest_BTree( );  /* 递归创建从根开始的二叉树 */
    return pbtree; 
}


int main(){
	return 0;
}
