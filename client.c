#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

int main()
{
    int data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path+1, "test\0");
    addr.sun_path[0] = '\0';    

    connect(data_socket, (struct sockaddr *)&addr, sizeof(addr.sun_family) + 6);

    printf("What is the command: ");
    char send_buf[BUFSIZE];
    char recv_buf[BUFSIZE];
    fgets(send_buf, BUFSIZE, stdin);

    send(data_socket, "info\0", 5, 0); 


    recv(data_socket, recv_buf, BUFSIZE, 0);
    
    printf("Got %s from server\n", recv_buf);
    close(data_socket);
    return 0;
}
