//
// Created by artem on 20.12.16.
//
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define FILE "/home/artem/ClionProjects/shm/main.cpp"

int main(int argc, char**argv){
    if(argc != 2){
        printf("Wrong number of arguments");
        return -1;
    }
    int n = strtol(argv[1], NULL, 10);
    int key = ftok(FILE, 1);
    int id = shmget(key, 4 * sizeof(int), 0);
    if(id == -1){
        printf("%s", strerror(errno));
    }
    int* buf = (int*)shmat(id, NULL, 0);


    for(int i = 0;i < 1000;i++) {
        buf[0]++;
        buf[n]++; //теперь на 1000 увеличить инкрементами
    }

    printf("%d %d %d %d", buf[0], buf[1], buf[2], buf[3]);
    return 0;
}

