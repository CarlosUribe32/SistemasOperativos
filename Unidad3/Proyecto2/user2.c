#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>

#define PERMS 0644
struct my_msgbuf {
   long mtype;
   char mtext[200];
};

struct my_msgbuf buf1, buf2;
int msqid1, msqid2;
int toend1;
key_t key1, key2;

void *lectura(){
    //Conectamos con la cola 1
    while ((msqid1 = msgget(key1, PERMS)) == -1) {
        sleep(1);
        // perror("msgget lectura");
        // exit(1);
    }
    while(1){
        //Leemos el mensaje
        while (msgrcv(msqid1, &buf1, sizeof(buf1.mtext), 0, 0) == -1) {
            sleep(1);
            msqid1 = msgget(key1, PERMS);//Volviendo a conectar...
            // perror("msgrcv");
            // exit(1);
        }
        printf("Usuario 1: \"%s\"\n", buf1.mtext);
    }
    return 0;
}

int main(void){
    pthread_t hilo1, hilo2;
    system("touch msgq1-2.txt");
    system("touch msgq2-1.txt");

    //Creamos ambas llaves
    if ((key1 = ftok("msgq1-2.txt", 'B')) == -1 || (key2 = ftok("msgq2-1.txt", 'B')) == -1) {
      perror("ftok");
      exit(1);
    }
    pthread_create(&hilo1, NULL, &lectura, NULL);
    
    pthread_join (hilo1, NULL);
}