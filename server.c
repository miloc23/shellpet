#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int listen_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    
    struct sockaddr_storage client;
    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;
    char path[108] = "/home/milo/.pet/sock\0";
    strcpy(addr.sun_path, path);

    int ret = bind(listen_socket, (struct sockaddr*)&addr, sizeof(struct sockaddr_un));
    
    ret = listen(listen_socket, 20);
    int addr_size = sizeof(client); 
    int data_socket = accept(listen_socket, (struct sockaddr*)&client, &addr_size);
    
    char *msg = "Hello World";    
    int length = strlen(msg);

    send(data_socket, msg, length, 0);
    close(data_socket);
    close(listen_socket);
    return 0;
}
