#include <stdio.h>
#include <pthread.h>
#include <sys/shm.h>
#include "semaphor.h"

void print_message_function( void *ptr );


Semaphore child_counter;
Semaphore worlds_turn;


main()
{
      pthread_t thread1, thread2;
      char *message1 = "Hello";
      char *message2 = "World";


      semaphore_init( &child_counter );
      semaphore_init( &worlds_turn );


      semaphore_down( &worlds_turn ); /* world goes second */
      semaphore_decrement( &child_counter ); /* value now 0 */
      semaphore_decrement( &child_counter ); /* value now -1 */
      /* 
       * child_counter now must be up-ed 2 times for a thread blocked on it
       * to be released 
       *
       */


      pthread_create( &thread1, NULL, 
            (void *) &print_message_function, (void *) message1);


      semaphore_down( &worlds_turn );


      pthread_create(&thread2, NULL, 
            (void *) &print_message_function, (void *) message2);


      semaphore_down( &child_counter );


      /* not really necessary to destroy since we are exiting anyway */
      semaphore_destroy ( &child_counter );
      semaphore_destroy ( &worlds_turn );
      exit(0);
}


void print_message_function( void *ptr )
{
      char *message;
      message = (char *) ptr;
      printf("%s ", message);
      fflush(stdout); 
      semaphore_up( &worlds_turn );
      semaphore_up( &child_counter );
      pthread_exit(0);
}


