#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <malloc.h>


int main() {

    int i = 1;
    char** strs;
    int fd = open("/home/artem/ClionProjects/useless/test.txt", O_RDONLY);
    if (fd == -1) {
        printf("%s\n", strerror(errno));
        return 1;
    }
    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char *buf = (char *) malloc(size);

    int tmp = read(fd, buf, size);
    if (tmp == -1) {
        printf("%s\n", strerror(errno));
        return 1;
    }

    char* separ = " ";
    strs[0] = strtok(buf,separ);

    /*while (strs[i] != NULL) {

        // Выделение очередной части строки
        strs[i] = strtok (NULL,separ);
        i++;
    }*/
    i == 0;
    //while(strs[i] != NULL)
    printf("%s \n", strs[i]);


    //execvp(argv[1], &argv[1]);


    return 0;
}