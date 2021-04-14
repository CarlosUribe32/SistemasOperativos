#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int cont = 0;
struct stat stat_str;

void unix_error(char *msg) 
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}
void analizarDirectorio(char dir[30]){
    stat(dir, &stat_str);
    return 0;
}

void imprimirRegistros(char dir[30]){
    char subdir[30];
    cont++;
    DIR *streamp; 
    struct dirent *dep;
    streamp = opendir(dir);
    errno = 0;
    while ((dep = readdir(streamp)) != NULL) {
        if(strcmp(dep->d_name, ".")!=0 && strcmp(dep->d_name, "..")!=0){
            strcpy(subdir, dir);
            strcat(subdir, dep->d_name);
            //printf("%s\n", subdir);
            for (int i = 2; i <= cont; i++)
                printf("  ");
            analizarDirectorio(subdir);
            if (S_ISDIR(stat_str.st_mode)){
                printf("Directorio %s\n", dep->d_name);
                strcat(subdir, "/");
                imprimirRegistros(subdir);
            }
            else
                printf("Archivos %s\n", dep->d_name);
        } 
    } 
    if (errno != 0)
        unix_error("readdir error");
    closedir(streamp);
    cont--;
    return 0;
}


int main(int argc, char **argv){

    if (argc != 2) {
        fprintf(stderr, "Para compilar usa el comando: %s <NombreDirectorio>\n", argv[0]);
        exit(0);
    }

    analizarDirectorio(argv[1]);

    if (S_ISREG(stat_str.st_mode))
	    printf("Esto es un archivo, no un directorio\n");
    else if (S_ISDIR(stat_str.st_mode))
	    imprimirRegistros(argv[1]);
    else 
	    printf("Este directorio no existe\n");

    return 0;
}