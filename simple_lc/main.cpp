#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define PATH "."

int main() {
    int err;
    DIR * ptr = opendir(PATH);
    if(ptr == NULL){
        printf("%s", strerror(errno));
    }

    struct stat st;
    while(dirent * stru = readdir(ptr)){
        stat(stru->d_name, &st);

        st.st_mode & S_IFDIR ? printf("d") : printf("-");  //права доступа
        st.st_mode & S_IRUSR ? printf("r") : printf("-");
        st.st_mode & S_IWUSR ? printf("w") : printf("-");
        st.st_mode & S_IXUSR ? printf("x") : printf("-");
        st.st_mode & S_IRGRP ? printf("r") : printf("-");
        st.st_mode & S_IWGRP ? printf("w") : printf("-");
        st.st_mode & S_IXGRP ? printf("x") : printf("-");
        st.st_mode & S_IROTH ? printf("r") : printf("-");
        st.st_mode & S_IWOTH ? printf("w") : printf("-");
        st.st_mode & S_IXOTH ? printf("x") : printf("-");

        printf(" %ld ", st.st_nlink);            //number of hard links
        printf("%d %d ", st.st_gid, st.st_uid);
        printf("%ld ", st.st_size);               //размер
        printf("%s ", ctime(&st.st_mtime));   //time
        printf("%s \n", stru->d_name);    //имя файла

    }

    err = closedir(ptr);
    if(err != 0){
        printf("%s", strerror(errno));
    }
    return 0;
}