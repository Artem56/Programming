#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <errno.h>


#define SIZE 50

int main() {
    int pipefd[2];
    char buf[SIZE];
    int status;

    int tmp = pipe(pipefd);
    if(tmp == -1){
        printf("%s", strerror(errno));
        return 1;
    }

    int cpid = fork();
    if (cpid == -1) {
        printf("%s", strerror(errno));
        return 1;
    }
    if(cpid > 0){  //parent reads
        close(pipefd[1]);
        tmp = read(pipefd[0], buf, SIZE);
        if(tmp > 0){
            printf("I have read %d bytes : %s", tmp, buf);
        }else{
            printf("%s", strerror(errno));
            return 1;
        }
        close(pipefd[0]);
        return 0;
    }
    if(cpid == 0){   //child writes
        close(pipefd[0]);
        if(tmp = write(pipefd[1], "Hello world!", strlen("Hello world!")) != strlen("Hello world!")){
            printf("Failed to write in the pipe!");
            return 1;
        }
        close(pipefd[1]);
        waitpid(cpid, &status, 0);
        return 0;

    }

    close(pipefd[0]);
    close(pipefd[1]);

    return 0;
}