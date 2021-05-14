#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <netdb.h> 
#include <iostream>
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/in.h> 
using namespace std;
int main (int argc, char *argv[])
{
    int socket_to_connect, port;
    bool room_closed = false;
    int buffsize = 1024;
    char buffer[buffsize];
    struct  sockaddr_in server_add;
    struct hostent *server;
    if (argc < 3) 
    {        
        fprintf(stderr,"usage %s hostname port\n", argv[0]);        
        exit(0);     
    }     
    port = atoi(argv[2]);     
    socket_to_connect = socket(AF_INET, SOCK_STREAM, 0);     
    if (socket_to_connect < 0)          
    {
        printf("ERROR. Fail to create socket :(\n");
    }  
     
    server = gethostbyname(argv[1]);     
    if (server == NULL) 
    {         
        fprintf(stderr,"ERROR, no such host\n");         
        exit(0);     
    }
    
    server_add.sin_family = AF_INET; 
    bcopy((char *)server->h_addr,           
    (char *)&server_add.sin_addr.s_addr,          
    server->h_length);   
    server_add.sin_port = htons(port);
    if (connect(socket_to_connect, (struct sockaddr *)&server_add, sizeof(server_add))==0)
    {
        printf("Welcome to the room.\n");
    }
    recv(socket_to_connect, buffer, buffsize, 0);
    printf("Server is ready to lisent to you. Good talk.\n");
    printf("Enter # to leave the room\n");

    while (!room_closed)
    {
        printf("----Client:");
        bzero(buffer,buffsize);
        cin >> buffer;
        send (socket_to_connect, buffer, buffsize, 0); 
        for (int i=0; i < buffsize; i++)
            {
                if (buffer[i] == '#') 
                {
                    i=buffsize;
                    room_closed = true;
                }
            }
        bzero(buffer,buffsize); 
        printf("Server:");
        recv (socket_to_connect, buffer, buffsize, 0);
            for (int i=0; i < buffsize; i++)
            {
                cout << buffer[i];
                if (buffer[i] == '#') 
                {
                    i=buffsize;
                    room_closed = true;
                }
            }
        printf("\n");
    }
    printf("Room closing. Bye!\n");
    close(socket_to_connect);
    return 0;
}