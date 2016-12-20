//
// Created by artem on 06.12.16.
//

#include <zconf.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

pthread_mutex_t mutex;

int main(){
    int err = pthread_mutex_init (&mutex, NULL);
    if(err != 0){
        printf("%s", strerror(errno));
        return -1;
    }
    int arg[4];    //counter
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    if(pthread_create(&thread1, NULL, thread1_inc, (void *)arg) != 0 || pthread_join(thread1, NULL) != 0){
        printf("%s", strerror(errno));
        return -1;
    }
    if(pthread_create(&thread2, NULL, thread2_inc, (void *)arg) != 0 || pthread_join(thread2, NULL) != 0){
        printf("%s", strerror(errno));
        return -1;
    }
    if(pthread_create(&thread3, NULL, thread3_inc, (void *)arg) != 0 || pthread_join(thread3, NULL) != 0){
        printf("%s", strerror(errno));
        return -1;
    }

    printf("%d\n", arg[0]);
    printf("%d\n", arg[1]);
    printf("%d\n", arg[2]);
    printf("%d\n", arg[3]);

    err = pthread_mutex_destroy(&mutex);
    if(err != 0){
        printf("%s", strerror(errno));
        return -1;
    }
    return 0;
}

void *thread1_inc(void* arg) {
    int i;
    for (i = 0; i < 1000; i++){
        pthread_mutex_lock(&mutex);
        ((int*)arg)[0]++;
        ((int*)arg)[1]++;
        pthread_mutex_unlock(&mutex);
    }
}
void *thread2_inc(void* arg) {
    int i;
    for (i = 0; i < 1000; i++){
        pthread_mutex_lock(&mutex);
        ((int*)arg)[0]++;
        ((int*)arg)[1]++;
        pthread_mutex_unlock(&mutex);
    }
}
void *thread3_inc(void* arg) {
    int i;
    for (i = 0; i < 1000; i++){
        pthread_mutex_lock(&mutex);
        ((int*)arg)[0]++;
        ((int*)arg)[1]++;
        pthread_mutex_unlock(&mutex);
    }
}