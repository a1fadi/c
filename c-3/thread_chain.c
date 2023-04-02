#include <pthread.h>
#include "thread_chain.h"
#include <stdio.h>

void *my_thread(void *data) {
    int *data1 = (int*)data;
    if (*data1 <= 50) {
        //int *number = (int*)data;
        pthread_t thread_handle;
        //Increments the pointers value from 'the source' i.e data
        ++*(data1++);
        //Because we need to make sure the data being passed into the function 
        //Is correctly incremented we pass on data after its been incremented
        thread_hello();
        pthread_create(&thread_handle, NULL, my_thread, data);
        pthread_join(thread_handle, NULL);
    }
    return NULL;
}

void my_main(void) {
    pthread_t thread_handle;
    int thr_number = 1;

    pthread_create(&thread_handle, NULL, my_thread, &thr_number);

    pthread_join(thread_handle, NULL);
}

// void thread_hello() {
//     printf("hello");
// }