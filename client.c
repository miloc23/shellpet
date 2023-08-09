#include "helpers.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Need a command\n");
    }
    int data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    int sockaddr_len = 0; 
    struct sockaddr_un *addr = pet__abstract_socket("test", 4, &sockaddr_len); 
    //addr.sun_family = AF_UNIX;
    //strcpy(addr.sun_path+1, "test\0");
    //addr.sun_path[0] = '\0';    

    connect(data_socket, (struct sockaddr *)addr, sockaddr_len);

    char send_buf[BUFSIZE];
    char recv_buf[BUFSIZE];

    // remove \n char

    //send(data_socket, send_buf, strlen(send_buf) + 1, 0); 
    
    send(data_socket, argv[1], strlen(argv[1]) + 1, 0);

    if (!strcmp(argv[1], "pet")) {
        struct pet *pet = calloc(1, sizeof(struct pet));
        recv(data_socket, pet, sizeof(struct pet), 0);
        printf("Pet name: %s\nPet age %d\n", pet->name, pet->age);
    } else if (!strcmp(argv[1], "init")) {
        printf("Name: ");
        fgets(send_buf, 32, stdin);
        send_buf[strlen(send_buf) - 1] = '\0';
        send(data_socket, send_buf, 32, 0); 
    } else { 
        recv(data_socket, recv_buf, BUFSIZE, 0);
        printf("Got %s from server\n", recv_buf);
    }
    close(data_socket);
    return 0;
}
