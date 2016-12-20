#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void handler(int a);
int main() {
    printf("pid : %d group : %d session : %d \n", getpid(), getpgid(getpid()), getsid(getpid()));

    const sighandler_t p = signal(SIGINT, handler);

    while(true);
}

void handler(int a){
    static int tmp;
    if(tmp != 4)
        printf("  k\n");
    else
//        p = SIG_IGN;
    tmp++;
}