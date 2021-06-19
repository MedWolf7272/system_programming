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
    int socket_to_connect, port, recv_len;
    int buffsize = 1024;
    char buffer[buffsize];
    struct sockaddr_in sever_addr, cli_addr;    
    socklen_t size_leng;
    int socket_leng = sizeof(cli_addr);
    if (argc < 2) 
    {
        fprintf(stderr,"ERROR, no port provided\n");          
        exit(1);      
    }
    socket_to_connect = socket(AF_INET, SOCK_DGRAM, 0);
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
    printf("Binded good\n");
    size_leng = sizeof(cli_addr);
    printf("Waiting for data...");
    if ((recv_len = recvfrom(socket_to_connect, buffer, buffsize, 0, (struct sockaddr *)&cli_addr, &size_leng)) == -1)
    {
        printf("ERROR. Fail to recieve message...\n");
        exit(1);
    }
    printf ("Recieved data: %s\n", buffer);
    printf ("Write the reply for client:\n");
    cin >> buffer;
    if (sendto(socket_to_connect, buffer, buffsize, 0, (struct sockaddr*)&cli_addr, socket_leng) ==-1)
    {
        printf("ERROR. Fail to send message...\n");
        exit(1);
    }
    
    close (socket_to_connect);
    return 0;
}