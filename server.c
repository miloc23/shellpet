#include "helpers.h"

int main()
{
    struct sockaddr_storage client;
    
    time_t cur_time = time(NULL);
    time_t next_time;

    int listen_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    int sockaddr_len;
    struct sockaddr_un *addr = pet__abstract_socket("test", 4, &sockaddr_len);
    
    int ret = bind(listen_socket, (struct sockaddr*)addr, sockaddr_len);
    
    int data_socket;
    int addr_size = sizeof(client); 

    struct pet *pet = calloc(1, sizeof(struct pet));

    short init = 0;
    //strncpy(pet->name, "Charles", 8);
    
    //pet->age = 1;
    char buf[BUFSIZE];
    for (;;) {
        ret = listen(listen_socket, 20);
        data_socket = accept(listen_socket, (struct sockaddr*)&client, &addr_size);
        
        next_time = time(NULL);
        pet->age += ((float)(next_time - cur_time) / 60.0); 
        cur_time = next_time;
        //char buf[1024];
        recv(data_socket, buf, BUFSIZE, 0);
        
        if (!strcmp(buf, "info")) {
            send(data_socket, "hi", 3, 0);
        } else if (!strcmp(buf, "init")) {
            recv(data_socket, buf, 1024, 0);
            if (!init)
                strncpy(pet->name, buf, 32);
        } else if (!strcmp(buf, "exit")) {
            send(data_socket, "bye", 4, 0);
            break;
        } else if (!strcmp(buf, "pet")) {
            send(data_socket, pet, sizeof(struct pet), 0);
//            pet->age++;
        } else {
            send(data_socket, "unknown", 7, 0);
        }
    }
    


    shutdown(data_socket, SHUT_RDWR);
    shutdown(listen_socket, SHUT_RDWR);
    close(data_socket);
    close(listen_socket);
    return 0;
}
