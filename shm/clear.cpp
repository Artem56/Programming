//
// Created by artem on 20.12.16.
//

#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdio>
#include <cstring>
#include <errno.h>

#define FILE "/home/artem/ClionProjects/shm/main.cpp"

int main(){
    int key = ftok(FILE, 1);
    int id = shmget(key, 4 * sizeof(int), 0);
    if(id == -1){
        printf("%s", strerror(errno));
    }
    int* buf = (int*)shmat(id, NULL, 0);
    int err = shmdt(buf);
    if(err == 0){
        printf("memory was successfully disconnected");
    }
    return 0;
}
