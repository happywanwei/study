#include <stdio.h>
#include <stdlib.h>
#include <linux/ipc.h>
#include <linux/msg.h>

static struct mymsgbuf {
		long mtype;
		int request;
		double salary;
		} msg;

int open_queue(key_t keyval);
int send_message(int qid, struct mymsgbuf* qbuf);

main()
{
         int    qid;
         key_t  msgkey;
         /* Generate our IPC key value */
         msgkey = ftok(".", 'm');
         /* Open/create the queue */
         if(( qid = open_queue(msgkey)) == -1) {
         perror("open_queue");
         exit(1);
         }
         /* Load up the message with arbitrary test data */
         msg.mtype   = 1;        /* Message type must be a positive number! */   
         msg.request = 1;        /* Data element #1 */
         msg.salary  = 1000.00;  /* Data element #2 (my yearly salary!) */
         /* Bombs away! */
         if((send_message( qid, &msg )) == -1) {
         perror("send_message");
         exit(1);
         }
}

int open_queue(key_t keyval)
{
	int qid;
	if((qid=msgget(keyval, IPC_CREAT|0660))==-1)
	{
		return(-1);
	}
	return(qid);
}

int send_message(int qid, struct mymsgbuf* qbuf)
{
	int result, length;
	/*The length is essentially the size of the structure
	*minus sizeof(mtype)*/
	length=sizeof(struct mymsgbuf)-sizeof(long);
	if((result=msgsnd(qid, qbuf, length, 0))==-1)
	{
		return(-1);
	}
	return(result);
}





