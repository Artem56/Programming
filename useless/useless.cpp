#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>

const char FILENAME[] = "test.txt";
const int MAXFILE = 256;

char * ReadToBuf (const char *, int *);
int fsize (int);
int Count (const char *, int);
int Divide (char **, const char *, int, int);
int cmp (const void *, const void *);
int strnum (const char *, const char *);
int Exec (char **, int);
char * GetPath (const char *);

int main() {
    int size = 0;
    char * buf = ReadToBuf ( FILENAME, &size );
    int nLines = Count( buf, size );
    char ** Strs = (char **)calloc(nLines, sizeof(char *));
    Divide (Strs, buf, nLines, size);
    qsort (Strs, nLines, sizeof(char *), cmp);
    Exec (Strs, nLines);
    free (buf);
    free (Strs);
    return 0;
}

char * ReadToBuf (const char * FileName, int * sz) {
    FILE * file = fopen(FileName, "r");
    int size = fsize (fileno(file));
    char * buf = (char *)calloc(size, sizeof(*buf));

    read (fileno (file), (char *) buf, size);
    fclose (file);
    *sz = size;
    return buf;
}

int fsize (int fd) {
    struct stat st;
    fstat (fd, &st);
    int size = st.st_size;
    return size;
}

int Count (const char * s, int len){
    //char EndOfStr = '\n';
    char * point;
    int count = 0;
    while((point = strrchr ((char*)s, '\n'))){
        *point = '\0';
        count++;
    }
    return count;
}

int Divide(char ** arr, const char * buf, int lines, int slen){
    bool assign = false;
    int ArrCount = 0, pos = 0;
    int i;
    for (i = 0; i < slen; i++){
        if (buf[i] == '\0'){
            assign = true;
        }
        if (assign){
            arr[ArrCount] = (char *)buf + pos;
            pos = i + 1;
            assign = false;
            ArrCount++;
        }
    }
    return 0;
}

int cmp (const void * a, const void * b){
    return strnum (*(char **)a, *(char ** )b);
}

int strnum (const char * s1, const char * s2){
    return atoi ( s1 ) - atoi ( s2 );
}


int Exec (char ** strs, int nLines){
    int SleepTime = 0; // in seconds
    int LastST = 0;
    char * path;
    int i;
    for (i = 0; i < nLines; i++){
        SleepTime = atoi (strs[i]);
        usleep ((SleepTime - LastST) * 1000000);
        LastST = SleepTime;
        path = GetPath (strs[i]);
        pid_t pid = fork ();
        assert (pid >= 0);

        if (pid > 0) {
            printf("Executing program: %s\n", path);
        }

        if (!pid){ // child process; exec another program
            execl (path, path, NULL);
            abort();
        }
    }
    return 0;
}

char * GetPath (const char * s){
    char * res = NULL;
    int i;
    for (i = 0; i < strlen (s); i++) {
        if (s[i] == ' ') {
            if (i + 1 < strlen(s))
                res = (char *) s + i + 1;
            else
                return NULL;
            break;
        }
    }
    return res;
}