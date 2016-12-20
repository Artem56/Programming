#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

int main(int argc, char ** argv){
    char* str;
    char* endptr;
    int i, status;
    long int n;
    pid_t p;

    if (argc < 2){
        printf("Wrong number of arguments\n");
        return 0;
    }
    str = argv[1];
    n = strtol(str, &endptr,10);
    if ( ((*endptr != '\0')) || (errno == ERANGE)){
        printf("Wrong input");
        return 0;
    }

    printf("pid of the original process %d\n",getpid());

    for (i=0; i<n; i++){
        p = fork();
        if(p == -1){
            printf("%s", strerror(errno));
        }
        if (p>0) {
            waitpid(p, &status, 0);
        }
        if (p==0) {
            printf("pid = %d, ppid = %d, number = %d \n", getpid(), getppid(), i);
            return 0;
        }
    }
    return 0;
}
