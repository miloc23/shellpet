#include "helpers.h"

int main()
{
    struct sockaddr_storage client;
    
    time_t cur_time = time(NULL);
    time_t next_time;

    int listen_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    int sockaddr_len;
    struct sockaddr_un *addr = pet__abstract_socket(SOCK, 4, &sockaddr_len);
    
    int ret = bind(listen_socket, (struct sockaddr*)addr, sockaddr_len);
    
    int data_socket;
    int addr_size = sizeof(client); 

    struct pet *pet = calloc(1, sizeof(struct pet));

    short init = 0;

    enum pet_cmd cmd;
    char buf[BUFSIZE];
    for (;;) {
        ret = listen(listen_socket, 20);
        data_socket = accept(listen_socket, (struct sockaddr*)&client, &addr_size);
        
        next_time = time(NULL);
        pet->age += ((float)(next_time - cur_time) / 60.0); 
        cur_time = next_time;
        char buf[1024];
        recv(data_socket, &cmd, 1, 0);
        switch(cmd) {
            case INIT:
                recv(data_socket, buf, 1024, 0);
                if (!init)
                    strncpy(pet->name, buf, 32);
                break;
            case GET:
                send(data_socket, pet, sizeof(struct pet), 0);
                break;
            case EXIT:
                send(data_socket, "bye", 4, 0);
                goto cleanup;
            default:
                send(data_socket, "unknown", 7, 0);
                break;
        }
    }
    
cleanup:
    shutdown(data_socket, SHUT_RDWR);
    shutdown(listen_socket, SHUT_RDWR);
    close(data_socket);
    close(listen_socket);
    return 0;
}
