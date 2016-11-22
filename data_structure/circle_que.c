typedef struct
{
	int head;
	int tail;
	int size;
	void **q;
}mmq_ww;

int create_que(mmq_ww *q, int size)
{
    q->q=malloc(sizeof(viod *)*size);
   if(!q)return -1;
   q->head=q->tail=0;
   q->size=size;
   return 1;
}

int add_que(mmq_ww *q)
{
	if(!q)return -1;//que is NULL
		int pos=q->tail+1;
		//judge two boundary
		if(pos>=p->size)pos=0;//get the end of loop
			if (pos==p->head)return -1;//full
				
		q->q[q->tail]=p;
		q->tail=pos;
		return 1;
}
void * del_que(mmq_ww *q)
{
	void * m=0;
			if(!q)return m;//que is NULL
			if (p->tail==p->head)return m;//empty
		m=q->q[q->head];
		int pos=q->head+1;
		if(pos>=p->size)pos=0;//get the begin of loop
			q->q[q->head]=0;
		q->head=pos;
		return m;
}
void * peek_que(mmq_ww *q)
{
		void * m=0;
			if(!q)return m;//que is NULL
			if (p->tail==p->head)return m;//empty
		m=q->q[q->head];
		return m;
}
