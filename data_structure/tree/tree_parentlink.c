/* ���ĸ�ָ���ʾ��*/

#define MAXNUM 20

typedef int DataType;

struct ParTreeNode {
    DataType info;		/* ����е�Ԫ�� */
    int     parent;	/* ���ĸ����λ�� */
};

struct  ParTree { 
    int n;                 	/* ���н��ĸ��� */
    struct ParTreeNode nodelist[MAXNUM];  	/* ������еĽ�� */
};

typedef struct ParTree *PParTree;		/* �����͵�ָ������ */

int rightSibling_partree(PParTree t, int p) {
    int i;
    if (p >= 0 && p < t->n) {
        for (i = p+1; i <= t->n; i++)
            if (t->nodelist[i].parent == t->nodelist[p].parent)
                return i;
    }
    return -1;
}


/* ���ȸ����д洢ʱ,�������ӽ�������ɼ�����*/
int leftChild_partree(PParTree t, int p) {     
    if (t->nodelist[p+1].parent == p)
        return p+1;
    else
        return -1;
}

int main(){
    return 0;
}
