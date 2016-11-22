#include <stdio.h>
#include <signal.h>


#define TRUE 1
#define FALSE 0
#define BELLS "\007\007\007"

int alarm_flag=FALSE;

/* SIGALRM handle fucntion*/
setflag()
{
      alarm_flag=TRUE;
}


main(int argc,char* argv[])
{
      int nsecs;
      int i;


      if (argc<2)
      {
           fprintf(stderr,"Usage:tml #minutes message\n");
           exit(1);
      }
      if ((nsecs=atoi(argv[1])*60)<=0)
      {
           fprintf(stderr,"Invalid time\n");
           exit(2);
      }

      /*  set the action associated with SIGALRM  */ 
             signal(SIGALRM,setflag);
      /*      set timer      */
      alarm(nsecs);

      /*  use pause()  to call the waiting signal  */
      pause();

      if (alarm_flag)
      {
           printf(BELLS);
           for (i=2;i<argc;i++)
           {
                 printf("%s\n",argv[i]);
           }
      }
      exit(0);
}


