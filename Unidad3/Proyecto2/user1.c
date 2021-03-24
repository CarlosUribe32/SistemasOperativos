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

void *escritura(){
    int len;
    //Creamos la cola de mensajes 1
    if ((msqid1 = msgget(key1, PERMS | IPC_CREAT)) == -1) {
      perror("msgget escritura");
      exit(1);
    }
    buf1.mtype = 1;
    printf("Ingrese ^D si quiere salir del chat\n");
    while(fgets(buf1.mtext, sizeof buf1.mtext, stdin) != NULL){
        len = strlen(buf1.mtext);
        if (buf1.mtext[len-1] == '\n') 
            buf1.mtext[len-1] = '\0';
        //Enviamos el mensaje por la cola 1
        if (msgsnd(msqid1, &buf1, len+1, 0) == -1)
             perror("msgsnd escritura");
    }
    //Destruimos la cola 1
    if (msgctl(msqid1, IPC_RMID, NULL) == -1) {
        perror("msgctl escritura");
        exit(1);
    }
    system("rm msgq1-2.txt");
    return 0;
}
void *lectura(){
    //Conectamos con la cola 2
    while ((msqid2 = msgget(key2, PERMS)) == -1) {
        sleep(1);
        // perror("msgget lectura");
        // exit(1);
    }
    while(1){
        //Leemos el mensaje
        while (msgrcv(msqid2, &buf2, sizeof(buf2.mtext), 0, 0) == -1) {
            sleep(1);
            msqid2 = msgget(key2, PERMS);//Volviendo a conectar...
            // perror("msgrcv");
            // exit(1);
        }
        printf("Usuario 2: \"%s\"\n", buf2.mtext);
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
    pthread_create(&hilo1, NULL, &escritura, NULL);
    pthread_create(&hilo2, NULL, &lectura, NULL);
    
    //Esperamos solo el hilo de escritura
    pthread_join (hilo1, NULL);
}