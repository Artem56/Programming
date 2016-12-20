#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define FIFO "fifo"

int main(int argc, char* argv[]) {
    int fd1, fd2;
    int arg;

    if(argc == 2) {
        arg = atoi(argv[1]);
    }else{
        printf("Wrong number of args\n");
        return 1;
    }
    char buf[100];

    mkfifo(FIFO, 0666);

    if(arg == 0) { //writer
        printf("writer\n");
        while (1) {
            fd2 =  open(FIFO, O_WRONLY);
            if(fd2 == -1){
                printf("%s", strerror(errno));
            }
            fgets(buf, 100 * sizeof(char), stdin);
            write(fd2, buf, strlen(buf) + 1);
            strcpy(buf, "");
        }
    }else if(arg == 1){ //reader
        printf("reader\n");
        while (1) {
            fd1 = open(FIFO, O_RDONLY);
            if(fd1 == -1){
                printf("%s", strerror(errno));
            }
            read(fd1, buf, strlen(buf) + 1);
            printf("%s", buf);
            fflush(stdout);
            strcpy(buf, "");
        }
    }else {
        printf("Wrong value of the argument\n");
        return 1;
    }
}