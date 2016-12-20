#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <errno.h>


int main() {
    int pipefd[2], x = 0, tmp = 1;
    int t = pipe2(pipefd, O_NONBLOCK);
    if(t == -1){
        printf("%s", strerror(errno));
        return 1;
    }
    while(tmp > 0) {
        tmp = write(pipefd[1], "0", 1);
        x++;
    }
    printf("Можно записать в PIPE сразу %d байтов\n", x - 1);

    return 0;
}

