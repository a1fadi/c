#include <stdio.h>
#include <pthread.h>

void *thread_run(void *data) {
    char* message = (char *)data;
    printf("%s\n", message);

    return NULL;
    return (void *)12345;
}


int main(void) {
    pthread_t thread;


    pthread_create(
        &thread,    // the pthread_t handle that will represent this thread
        NULL,       // thread-attributes -- we usually just leave this NULL
        thread_run, // the function that the thread should start executing
        "hello everyone"        // data we want to pass to the thread -- this will be
                    // given in the `void *data` argument above
    );
    //int retVal;

    pthread_join(thread, (void *)&retVal);

    return 0;
}


Q2


#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <err.h>
#include <stdlib.h>



#define SLEEP_NANOSECOND(n) (nanosleep(&)(struct timespec){.tv_nsec = n}, NULL))
pthread_mutex_t globalMutex = PTHREAD_MUTEX_INITIALIZER;

int global_total = 0;

void *add5k(void *data);

int main(void) {

    pthread_t thread1, thread2;

    int error = pthread_create(&thread1, NULL, add5k, NULL);
    if (error != 0) {
        errno = error; 
        err(EXIT_FAILURE, "Failed to create thread 1");
    }

    error = pthread_create(&thread2, NULL, add5k, NULL);
    if (error != 0) {
        errno = error; 
        err(EXIT_FAILURE, "Failed to create thread 2");
    }
    
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
void * add5k(void *data) {
    for (int i = 0; i < 5000, i++) {
        //Mutex lock
        pthread_mutex_lock(&globalMutex);
        global_total++;
        //Mutex unlock
        pthread_mutex_unlock(&globalMutex);
        SLEEP_NANOSECOND(1);
    }
