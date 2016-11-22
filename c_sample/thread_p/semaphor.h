#ifndef SEMAPHORES
#define SEMAPHORES

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>

typedef struct Semaphore
{
     int         v;
     pthread_mutex_t mutex;
     pthread_cond_t cond;
}Semaphore;



int          semaphore_down (Semaphore * s);
int         semaphore_decrement (Semaphore * s);
int         semaphore_up (Semaphore * s);
void        semaphore_destroy (Semaphore * s);
void        semaphore_init (Semaphore * s);
int          semaphore_value (Semaphore * s);
int         tw_pthread_cond_signal (pthread_cond_t * c);
int         tw_pthread_cond_wait (pthread_cond_t * c, pthread_mutex_t * m);
int         tw_pthread_mutex_unlock (pthread_mutex_t * m);
int         tw_pthread_mutex_lock (pthread_mutex_t * m);
void        do_error (char *msg);


#endif

