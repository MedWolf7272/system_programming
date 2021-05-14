#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <iostream>
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/in.h> 
using namespace std;
int main(int argc, char *argv[])
{
    int socket_to_connect, port, server;
    int buffsize = 1024;
    char buffer[buffsize];
    bool room__closed = false;
    struct sockaddr_in sever_addr, cli_addr;
    socklen_t size_leng;
    if (argc < 2) 
    {
        fprintf(stderr,"ERROR, no port provided\n");          
        exit(1);      
    }
    socket_to_connect = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_to_connect<0)
    {
        printf("ERROR. Fail to create socket :(\n");
        exit(1);
    }
    printf("Socket has been created...\n");    
    port = atoi(argv[1]);
    sever_addr.sin_family = AF_INET;      
    sever_addr.sin_addr.s_addr = INADDR_ANY;      
    sever_addr.sin_port = htons(port);
    if ((bind(socket_to_connect, (struct sockaddr*)&sever_addr,sizeof(sever_addr))) < 0) 
    {
        printf("ERROR. Fail to bind connection, the socket has already been established...\n");
        exit(1);
    }
    printf("Bindid good\n");
    size_leng = sizeof(cli_addr);
    printf("Server is started. Waiting for client...\n");

    listen(socket_to_connect, 1);
    printf("Start listeting\n");
    server = accept(socket_to_connect, (struct sockaddr *)&cli_addr, &size_leng);
    printf("Accept done\n");
    if (server<0)
    {
        printf("ERROR. Fail to do accept fuction\n");
    }
    //while (server >0)
    //{
        strcpy(buffer, "Server connected...\n");
        send(server, buffer, buffsize, 0);
        printf("Client has entered the room. Good talk.\n");
        printf("Enter # to end leave the room\n");
        
        cout << "Client: ";
        recv (server, buffer, buffsize, 0);
        for (int i=0; i < buffsize; i++)
        {
            cout << buffer[i];
            if (buffer[i] == '#') 
            {
                i=buffsize;
                room__closed = true;
            }
            if (buffer[i] == '*') 
            {
                i=buffsize;
            }
        }
        printf("\n");
        while (!room__closed)
        {
            printf("Server:");
            bzero(buffer,buffsize);
            cin >> buffer;
            send (server, buffer, buffsize, 0);
            for (int i=0; i < buffsize; i++)
            {
                if (buffer[i] == '#') 
                {
                    i=buffsize;
                    room__closed = true;
                }
            } 
            bzero(buffer,buffsize); 
            printf("---Client:");
            recv (server, buffer, buffsize, 0);
            for (int i=0; i < buffsize; i++)
            {
                cout << buffer[i];
                if (buffer[i] == '#') 
                {
                    room__closed = true;
                }
                if (buffer[i] == '*') 
                {
                    i=buffsize;
                }
            }
            printf("\n");
        } 
        printf("Room closing. Bye!\n");
        close(server);
    //}
    close(socket_to_connect);
    return 0;
}