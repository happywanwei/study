/* 直接插入排序的算法源程序*/

#include<stdio.h>

#define MAXNUM 100

typedef int KeyType;
typedef int DataType;
typedef struct {
    KeyType key;       /* 排序码字段 */
    /*DataType info;           记录的其它字段 */
} RecordNode;

typedef struct {
    int n;               /* n为文件中的记录个数，n<MAXNUM */
    RecordNode record[MAXNUM];
} SortObject;

void InsertSort(SortObject * pvector) { /* 按递增序进行直接插入排序 */
    int i, j;
    RecordNode temp;
    RecordNode *data = pvector->record;

    for( i = 1; i < pvector->n; i++ ) { /* 依次插入记录R1, R2…Rn-1 */
        temp = data[i]; 
        for ( j = i-1; j >= 0 && temp.key < data[j].key; j-- )
            /* 由后向前找插入位置 将排序码大于ki的记录后移 */
            data[j+1] = data[j];
        if( j != i-1 ) data[j+1] = temp;
    }
}

SortObject vector = {10, 
    49, 38, 65, 97, 76, 13, 27, 49, 50, 101};

int main(){
    int i;
    InsertSort(&vector);
    for(i = 0; i < vector.n; i++)
        printf("%d ", vector.record[i]);
    getchar();
    return 0;
}

/**
void InsertSort(int* data, int size)
{
    int i = 0, j = 0;
    int temp = 0;
 
    for (i = 1; i < size; i++)
    {
        temp = data[i];
 
        for (j = i; j > 0 && data[j - 1] > temp; j--)
            data[j] = data[j - 1];
 
        if (j != i) data[j] = temp;
    }
}
/**/
