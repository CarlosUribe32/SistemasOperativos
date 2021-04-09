#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

void unix_error(char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

int main(int argc, char **argv)
{
    DIR *streamp; 
    struct dirent *dep; 

    if (argc != 2) {
        printf("usage: %s <pathname>\n", argv[0]);
        exit(1);
    }
    streamp = opendir(argv[1]);

    errno = 0;
    while ((dep = readdir(streamp)) != NULL) { 
        printf("Found file: %s\n", dep->d_name); 
    } 
    if (errno != 0)
        unix_error("readdir error");

    closedir(streamp); 
    exit(0);
}
