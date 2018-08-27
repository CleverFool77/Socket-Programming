#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h> 

int main(){

    int newsocket;
    char buffer[1024];
    socklen_t client;

    newsocket=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(4455);
    serverAddr.sin_addr.s_addr =INADDR_ANY;

    struct sockaddr_in clientAddr;
    client = sizeof(clientAddr);

    if(bind(newsocket,(struct sockaddr *)&serverAddr,sizeof(serverAddr))== -1)
    {
        printf("Error in bind");
        exit(1);
    }
    if(listen(newsocket,5)== -1)
    {
        printf("Error in listening");
        exit(1);
    }
    int clientsocket;
    clientsocket = accept(newsocket,(struct sockaddr *)&clientAddr,&client);
        if(clientsocket == -1)
        {
            printf("Error in accepting");
            exit(1);
        }

        while(1){
            if(recv(clientsocket,buffer,sizeof(buffer),0)== -1)
            {
                printf("Error in recv from cleint");
            }
            printf("Data from Client : %s ",buffer);
            printf("Server :");

            fgets(buffer, sizeof(buffer), stdin);

              if (strncmp(buffer, "bye", 3) == 0)
              {
                    break;
              }

              if(send(clientsocket,buffer,sizeof(buffer),0) == -1)
              {
                  printf("Error in sending");
                  exit(1);
              }
        }

}