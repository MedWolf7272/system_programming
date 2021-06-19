#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <netdb.h> 
#include <iostream>
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <errno.h>
#include <arpa/inet.h>
using namespace std;
int main (int argc, char *argv[])
{
    int socket_to_connect, port;
    int buffsize = 1024;
    char buffer[buffsize];
    struct  sockaddr_in server_add, client;
    struct hostent *server;
    socklen_t size_leng;
    int socket_leng = sizeof(server_add);
    if (argc < 3) 
    {        
        fprintf(stderr,"usage %s hostname port\n", argv[0]);        
        exit(0);     
    }     
    port = atoi(argv[2]);     
    socket_to_connect = socket(AF_INET, SOCK_DGRAM, 0);

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

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;  
    short clinet_port = port-1;
    client.sin_port = htons(50524);
    size_leng = sizeof(server_add);
    if ((bind(socket_to_connect, (struct sockaddr*)&client,sizeof(client))) < 0) 
    {
        printf("ERROR. Fail to bind connection, the socket has already been established...\n");
        exit(1);
    }

    printf("Write your messege:");
    bzero(buffer,buffsize);
    scanf("%s", buffer);

    int n = sendto(socket_to_connect, buffer, strlen(buffer), 0, 
    (const struct sockaddr* )&server_add, size_leng);
    if (n<0)
    {
        
        printf("ERROR. Fail to send messsage :(%d - %d\n", n, errno);
        exit(0); 
    }
    n = recvfrom(socket_to_connect, (char*)buffer, buffsize, 0, 
    (struct sockaddr *) &server_add, &size_leng);
    if (n<0)
    {
        printf("ERROR. Fail to recieved messsage :(\n");
        exit(0); 
    }
    printf ("Data from server: %s\n", buffer);
    close (socket_to_connect);
    return 0;
}