#include <stdio.h> 
#include <string.h>
#include <pthread.h>
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>

typedef struct{
    char * myfifo;
}Parametros;

void *escritura(void * p1){
    int fd;
    Parametros *p = (Parametros *)p1;
    char arr[80]; 

    fd = open(p->myfifo, O_WRONLY);
    while(1){
        fgets(arr, 80, stdin);
        write(fd, arr, strlen(arr)+1); 
    }
    close(fd);
}
void *lectura(void *p2){
    int fd, status;
    Parametros *p = (Parametros *)p2;
    char arr[80];
    fd = open(p->myfifo, O_RDONLY);
    while(1){
        status = read(fd, arr, sizeof(arr));
        if(status!=0)
            printf("User1: %s\n", arr);
        else
            sleep(1); //Mimase un ratico mientras venga el otro
    }
    close(fd);
}

int main(){
    char * myfifo = "/tmp/myfifo";
    char * myfifo2 = "/tmp/myfifo2";
    mkfifo(myfifo, 0666);
    mkfifo(myfifo2, 0666);
    pthread_t id_hilo_1;
    pthread_t id_hilo_2;
    Parametros p1, p2;

    p1.myfifo = myfifo2;
    p2.myfifo = myfifo;
    pthread_create(&id_hilo_1, NULL, &escritura, &p1);
    pthread_create(&id_hilo_2, NULL, &lectura, &p2);
    pthread_join (id_hilo_1, NULL);
    pthread_join (id_hilo_2, NULL);
    return 0;
}