/* 本程序是用开地址法解决碰撞的散列表示方法,
提供了字典的一些基本操作*/

#include<stdio.h>

#define null -1                 /* null为空结点标记 */
#define TRUE 1
#define FALSE 0

#define REGION_LEN 13

typedef int KeyType;
typedef int DataType;

typedef struct {
    KeyType key;                /* 字典元素的关键码字段     */
    DataType value;             /* 字典元素的属性字段    */
} DicElement;

typedef struct {
    int m;                      /* m=REGION_LEN，为基本区域长度 */
    DicElement element[REGION_LEN];
} HashDictionary;

int h(KeyType key){
    return key % REGION_LEN;
}

int linearSearch(HashDictionary * phash, KeyType key, int *position) {
    int inc, d = h(key);                    /* d为散列地址，散列函数为h(key) */
    for (inc = 0; inc < phash->m; inc++) {
        if (phash->element[d].key == key) { /* 检索成功 */
            *position = d;                
            return TRUE;
        }
        else if (phash->element[d].key == null) {/* 检索失败，找到插入位置 */
            *position = d;                              
            return FALSE;
        }
        d = (d+1) % phash->m;
    }

    *position = -1;                         /* 散列表溢出 */

    return FALSE;
}

int linearInsert(HashDictionary *phash, KeyType key) {
    int position;
    if(linearSearch(phash, key, &position) == TRUE )/* 散列表中已有关键码为key 的结点*/
        printf("Find\n");
    else if(position != -1)    
        phash->element[position].key = key;     /* 插入结点，忽略对value字段的赋值 */
    else return FALSE;                          /* 散列表溢出 */
    return TRUE;
}


int main(){
    return 0;
}
			
