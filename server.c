#include "helpers.h"

int main()
{
    /* Code for using regular socket */
    //int listen_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    //
    //struct sockaddr_storage client;
    //struct sockaddr_un addr;
    //addr.sun_family = AF_UNIX;
    //char path[108] = "/home/milo/.pet/sock\0";
    //strcpy(addr.sun_path, path);

    //unlink(addr.sun_path);
    //int ret = bind(listen_socket, (struct sockaddr*)&addr, sizeof(struct sockaddr_un));
    //
    //ret = listen(listen_socket, 20);
    //int addr_size = sizeof(client); 
    //int data_socket = accept(listen_socket, (struct sockaddr*)&client, &addr_size);
    
    //char *msg = "Hello World";    
    //int length = strlen(msg);
    
    //send(data_socket, msg, length, 0);

    struct sockaddr_storage client;

    int listen_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    int sockaddr_len;
    struct sockaddr_un *addr = pet__abstract_socket("test", 4, &sockaddr_len);
    //addr.sun_family = AF_UNIX;
    //char path[108] = "\0test\0";
    //addr.sun_path[0] = '\0';
    //strncpy(addr.sun_path+1, path+1, 5);
    
    int ret = bind(listen_socket, (struct sockaddr*)addr, sockaddr_len);
    
    ret = listen(listen_socket, 20);
    int addr_size = sizeof(client); 
    int data_socket = accept(listen_socket, (struct sockaddr*)&client, &addr_size);
    
    char *msg = "Hello World";    
    int length = strlen(msg);
    
    //send(data_socket, msg, length, 0);

    char buf[1024];
    recv(data_socket, buf, 1024, 0);
    if (!strcmp(buf, "info")) {
        send(data_socket, "hi\0", 3, 0);
    }

    shutdown(data_socket, SHUT_RDWR);
    shutdown(listen_socket, SHUT_RDWR);
    close(data_socket);
    close(listen_socket);
    return 0;
}
