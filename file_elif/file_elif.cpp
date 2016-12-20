#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main() {
    int fdin = open("/home/artem/ClionProjects/file_elif/in.txt", O_RDONLY);   //CHANGE ADDRESS
    if (fdin == -1) {
        printf("%s\n", strerror(errno));
        return 1;
    }

    int fdout = open("/home/artem/ClionProjects/file_elif/out.txt", O_CREAT | O_RDWR | O_TRUNC);  ////CHANGE ADDRESS
    if (fdout == -1) {
        printf("%s\n", strerror(errno));
        return 1;
    }

    int size = lseek(fdin, 0, SEEK_END);
    lseek(fdin, 0, SEEK_SET);


    char *buf = (char *) malloc(size);

    int rcount = read(fdin, buf, size);
    if (rcount == -1) {
        printf("%s\n", strerror(errno));
        return 1;
    }

    char* str = (char*)malloc(rcount);
    int i, l = strlen(buf);
    for (i = 0; i < l; i++) {
        str[i] = buf[l - i - 1];
    }

    int wcount = write(fdout, str, rcount);

    close(fdin);
    close(fdout);
    return 0;
}