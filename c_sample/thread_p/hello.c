#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>

void print_message_function( void *ptr ); 

main()
{
    pthread_t thread1, thread2;
    char *message1 = "Hello";
    char *message2 = "World";

    int i=pthread_create( &thread1, NULL,
           (void*)&print_message_function, (void*) message1);
    i=pthread_create(&thread2, NULL, 
           (void*)&print_message_function, (void*) message2);
    while(1);


   // exit(0);
}


void print_message_function( void *ptr )
{
    char *message;
    message = (char *) ptr;
    printf("%s \n", message);
}

