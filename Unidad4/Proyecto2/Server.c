#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 6666
#define BUF_SIZE 128

struct client_t{
    int socket;
    int rxState;
    int num;
};

int cont=0;
struct client_t *client;
int sillas[10];

void * readThread(void *arg){
    struct client_t *clientact = ((struct client_t *)arg);
    // printf("Punteros %p %p\n", activos[cont-1], clientact);
    ssize_t numOfBytes;
    char buf[BUF_SIZE];
    int status;
    int idName = 0;
    char name[10];

    while(1){
        numOfBytes = read(clientact->socket, buf, BUF_SIZE);
        // printf("Socket %d, %d num\n", clientact->socket, clientact->num);
        if(0 == numOfBytes){
            printf("client closed the socket end\n");
            break;
        }
        else if(-1 == numOfBytes){
            perror("ReadThread read() fails: ");
            break;
        }
        else{
            //printf("Cliente %d: %s\n",clientact->num,buf);
            if(idName==0){
                idName=1;
                memcpy(name, buf, 8);
            }
            else{
                for (int i = 1; i <= 10; i++)
                {
                    if(clientact->num != client[i-1].num && sillas[i-1]!=0){
                        // printf("%d\n", clientact->num);
                        status = write(client[i-1].socket, buf, strlen(buf)+1);
                        if(-1 == status){
                            perror("Server write to client fails: ");
                            break;
                        }
                    }
                }
            }       
        }
    }
    printf("%s se desconecto\n", name);
    idName=0;
    clientact->rxState = 0;
    sillas[clientact->num-1] = 0;
    close(clientact->socket);
    cont--;
    return NULL;
}

int main(int argc, char *argv[]){
    int status;
    int enable = 1;
    int server_sd;
    int client_sd;
    pthread_t *rxThreadId = malloc(sizeof(pthread_t)*10);
    client = malloc(sizeof(struct client_t)*10);

    // 1. Ignore SIGPIPE
    signal(SIGPIPE, SIG_IGN);

    // 2. Create socket
    server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd == -1) {
        perror("Socket creation fails\n");
        exit(EXIT_FAILURE);
    }
    printf("Socket created\n");

    // 3. turn off bind address checking
    status = setsockopt(server_sd, SOL_SOCKET, SO_REUSEADDR,(int *) &enable, sizeof(enable));
    if (-1 == status){
        perror("setsockopt error: ");
    }

    //4. BIND the socket to an address
    // Prepare the address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    status = bind(server_sd, (struct sockaddr*)&addr, sizeof(addr));
    if (-1 == status) {
        perror("Bind fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }
    printf("Socket binded\n");

    // 5. Set backlog

    status = listen(server_sd, 1);

    if (-1 == status) {
        perror("Listen fails: ");
        close(server_sd);
        exit(EXIT_FAILURE);
    }

    printf("Server escuchando, se puede conectar\n");
    while(1)
    {
        int silla=0;
        //Esperando por un cliente
        client_sd = accept(server_sd, NULL, NULL);
        cont++;
        printf("Cliente %d conectado\n", cont);
        if(-1 == client_sd){
            perror("Accept fails: ");
            close(server_sd);
            exit(EXIT_FAILURE);
        }

        for (int i = 1; i <= 10; i++)
        {
            if(sillas[i-1]==0){
                sillas[i-1]=1;
                silla=i;
                break;
            }
        }
        
        printf("%d\n", silla);
        client[silla-1].socket = client_sd;
        client[silla-1].rxState = 1;
        client[silla-1].num = silla;

        status = pthread_create(&(rxThreadId[silla-1]),NULL,&readThread,&(client[silla-1]));
        if(-1 == status){
            perror("Pthread read fails: ");
            close(server_sd);
            exit(EXIT_FAILURE);
        }
    }
    
}