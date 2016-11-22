void reader_function(void);
void writer_function(void);


 char buffer;
int buffer_has_item = 0;
pthread_mutex_t mutex;
struct timespec delay;


main()
{
    pthread_t reader;


    delay.tv_sec = 2;
    delay.tv_nsec = 0;


    pthread_mutex_init(&mutex, pthread_mutexattr_default);
    pthread_create( &reader, pthread_attr_default, (void*)&reader_function,
           NULL);
    writer_function();
}
void writer_function(void)
{
    while(1)
    {
     pthread_mutex_lock( &mutex );
     if ( buffer_has_item == 0 )
     {
        buffer = make_new_item();
        buffer_has_item = 1;
     }
     pthread_mutex_unlock( &mutex );
     pthread_delay_np( &delay );
    }
}


void reader_function(void)
{
    while(1)
    {
     pthread_mutex_lock( &mutex );
     if ( buffer_has_item == 1)
     {
        consume_item( buffer );
        buffer_has_item = 0;
     }
     pthread_mutex_unlock( &mutex );
     pthread_delay_np( &delay );
    }
}


