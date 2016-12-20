//
// Created by artem on 11.10.16.
//
/*
#include <pthread.h>
#include <thread_db.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 2
#define NITER 10
int arr[3];
struct sthread {
    int thread_num;
};

void* funk(void* arr);

int main() {


    thread_t my_thread1;

    int pth = pthread_create(&my_thread1, NULL, &funk, 0);
    if(pth != 0){
        printf("Error in pthread_create()");
    }

    struct sthread* ts;
    ts = calloc(2, sizeof(struct thread_info));

    int err = pthread_join(my_thread1, NULL);
    if(err != 0){
        printf("Error in pthread_join()");
    }

    return 0;
}

void* funk(void* arr){
    int* array = arr;
    array[1]++;
    //arr[N]++;
    return NULL;
}*/


#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>

#define NUM_THREADS 2
#define NUM_ITER 100

int arr[3];
struct thread_info {    /* Used as argument to thread_start() */
    pthread_t thread_id;        /* ID returned by pthread_create() */
    int       thread_num;       /* Application-defined thread # */
};

void *thread_start(void *arg) {
    struct thread_info *tinfo = arg;
    int i;

    for (i = 0; i < NUM_ITER; i++){
        arr[0]++;
        arr[tinfo->thread_num]++;
    }
    return NULL;
}

int main() {
    int s, tnum, opt;
    struct thread_info *tinfo;

    tinfo = calloc(NUM_THREADS, sizeof(struct thread_info));/* Allocate memory for pthread_create() arguments */
    for (tnum = 0; tnum < NUM_THREADS; tnum++) {/* Create one thread for each command-line argument */
        s = pthread_create(&tinfo[tnum].thread_id, NULL,&thread_start, &tinfo[tnum]);/* The pthread_create() call stores the
                                                                           thread ID into corresponding element of tinfo[] */
        for (tnum = 0; tnum < NUM_THREADS; tnum++) {/* Now join with each thread, and display its returned value */
            s = pthread_join(tinfo[tnum].thread_id, NULL);
        }
        free(tinfo);
    }
    printf("%d  %d   %d\n", arr[0], arr[1], tinfo->thread_num);
}

