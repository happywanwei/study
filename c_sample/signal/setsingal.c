#include <stdlib.h>
#include <stdio.h>
#include <signal.h>


int main(void)
{
        signal(SIGINT,SIG_IGN); /*notify process to ignor SIGINT */
         printf("xixi\n");
        sleep(10); /* system call sleep() notify process to sleep 10seconds. */
          printf("end\n");
        return;
}

