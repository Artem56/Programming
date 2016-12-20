#include <pthread.h>
#include <thread_db.h>
#include <stdio.h>

void* funk(void* a);

int main() {
    void* res;
    thread_t my_thread;

    int pth = pthread_create(&my_thread, NULL, &funk, 0);
    if(pth != 0){
        printf("Error in pthread_create()");
    }
    int err = pthread_join(my_thread, &res);
    if(err != 0){
        printf("Error in pthread_join()");
    }
    //printf("%d", res);
    return 0;
}

void* funk(void* a){
    int b = 5;
    thread_t number = pthread_self();
    printf("I'm a thread № %lu\n", number);
    return NULL;
}





