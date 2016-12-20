#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>

#define FILE "/home/artem/ClionProjects/shm/main.cpp"

int main() {
    int key = 0, id = 0;
    int * buf;
    key = ftok(FILE, 1);

    if(key == -1) {
        printf("Error 1 : ");
        printf("%s\n", strerror(errno));
        return 1;
    }

    id = shmget(key, 4 * sizeof(int), IPC_CREAT | IPC_EXCL | 0666);

    if(id == -1){
        if(errno != EEXIST) {
            printf("Error 2 : ");
            printf("%s\n", strerror(errno));
            return 1;
        }
        if(errno == EEXIST){
            id = shmget(key, 4 * sizeof(int), 0);
        }
    }

    buf = (int*)shmat(id, NULL, 0);
    if(buf == (void*)-1){
        printf("Error 3 : %s\n", strerror(errno));
    }

    printf("key: %d, id: %d \n", key, id);

    return 0;
}