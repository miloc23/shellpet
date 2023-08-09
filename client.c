#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, "/home/milo/.pet/sock\0");
    
    connect(data_socket, (struct sockaddr *)&addr, sizeof(struct sockaddr_un));

    char buf[1024];

    recv(data_socket, buf, 1024, 0);
    
    printf("Got %s from server\n", buf);
    close(data_socket);
    return 0;
}
