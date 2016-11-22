/* ���Ա��˳���ʾ������ʵ��*/

#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

PSeqList createNullList_seq( void )
{
  PSeqList palist = (PSeqList)malloc(sizeof(struct SeqList));
  if (palist!=NULL)
    palist->n = 0;		/*�ձ���Ϊ0 */
  else
    printf("Out of space!\n");    	/*�洢����ʧ��*/
  return palist;
}

/*��palist��ָ˳������±�Ϊp��Ԫ��֮ǰ����Ԫ��x*/
int insert_seq(PSeqList palist, int p, DataType x)
{
  int q;
  if ( palist->n == MAXNUM ) { 			/* ��� */
    printf("Seq-list overflow!\n");
    return FALSE;
  }
  if (  p < 0  ||  p > palist->n  ) { 	/* �������±�Ϊp��Ԫ�� */
    printf("Index of seq-list is out of range! \n");
    return FALSE;
  }

  for(q = palist->n - 1; q >= p; q--)  	/* ����λ�ü�֮���Ԫ�ؾ�����һ��λ�� */
    palist->element[q+1] = palist->element[q];

  palist->element[p] = x;				/* ����Ԫ��x */
  palist->n++;			/* Ԫ�ظ�����1 */
  return TRUE;
}

/*��palist��ָ˳�����ɾ���±�Ϊ���Ԫ��*/
int delete_seq( PSeqList palist, int p )
{
  int q;
  if (p < 0 || p > palist->n-1 ) { 	/* �������±�Ϊp��Ԫ�� */
    printf("Index of seq-list is out of range!\n ");
    return FALSE;
  }

  for(q = p; q < palist->n-1; q++) 	/* ��ɾ��Ԫ��֮���Ԫ�ؾ�ǰ��һ��λ�� */
    palist->element[q] = palist->element[q+1];

  palist->n--;			/* Ԫ�ظ�����1 */
  return TRUE;
}

/*��x��palist��ָ˳����е��±�*/
int locate_seq(PSeqList palist, DataType x)
{
  int q;
  for ( q = 0; q<palist->n; q++ )
    if (palist->element[q] == x)
      return q;
  return  SPECIAL;
}

/* ��palist��ָ˳������±�Ϊp��Ԫ��ֵ */
DataType  retrieve_seq( PSeqList palist, int p )
{
  if ( p >= 0 && p < palist->n )	/* �����±�Ϊp��Ԫ�� */
    return palist->element[p];

  printf("Index of seq-list is out of range.\n ");
  return SPECIAL;                 /* ����һ��˳�����û�е�����ֵ */
}

int isNullList_seq( PSeqList palist )
{
  return palist->n == 0;
}
