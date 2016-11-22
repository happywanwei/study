/* ֱ�Ӳ���������㷨Դ����*/

#include<stdio.h>

#define MAXNUM 100

typedef int KeyType;
typedef int DataType;
typedef struct {
    KeyType key;       /* �������ֶ� */
    /*DataType info;           ��¼�������ֶ� */
} RecordNode;

typedef struct {
    int n;               /* nΪ�ļ��еļ�¼������n<MAXNUM */
    RecordNode record[MAXNUM];
} SortObject;

void InsertSort(SortObject * pvector) { /* �����������ֱ�Ӳ������� */
    int i, j;
    RecordNode temp;
    RecordNode *data = pvector->record;

    for( i = 1; i < pvector->n; i++ ) { /* ���β����¼R1, R2��Rn-1 */
        temp = data[i]; 
        for ( j = i-1; j >= 0 && temp.key < data[j].key; j-- )
            /* �ɺ���ǰ�Ҳ���λ�� �����������ki�ļ�¼���� */
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
