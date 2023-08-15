#include "helpers.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Need a command\n");
        exit(-1);
    }
    int data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    int sockaddr_len = 0; 
    struct sockaddr_un *addr = pet__abstract_socket(SOCK, 4, &sockaddr_len); 

    connect(data_socket, (struct sockaddr *)addr, sockaddr_len);

    char send_buf[BUFSIZE];
    char recv_buf[BUFSIZE];

    enum pet_cmd cmd;

    switch(argv[1][0]) {
        case 'i':
            cmd = INIT;
            break;
        case 'g':
            cmd = GET;
            break;
        case 's':
            cmd = SAVE;
            break;
        case 'l':
            cmd = LOAD;
            break;
        case 'e':
            cmd = EXIT;
            break;
    }

    send(data_socket, &cmd, 1, 0);
    
    switch(cmd) {
        case INIT: 
            printf("Name: ");
            fgets(send_buf, 32, stdin);
            send_buf[strlen(send_buf) - 1] = '\0';
            send(data_socket, send_buf, 32, 0); 
            break;
        case GET:
            struct pet *pet = calloc(1, sizeof(struct pet));
            recv(data_socket, pet, sizeof(struct pet), 0);
            printf("Pet name: %s\nPet age %f\n", pet->name, pet->age);
            printf("      ▄▀▄     ▄▀▄\n     ▄█░░▀▀▀▀▀░░█▄\n ▄▄  █░░░░░░░░░░░█  ▄▄\n█▄▄█ █░░▀░░┬░░▀░░█ █▄▄█\n");
            // This string may have usage issues. Credit goes to fsymbols
            break;
        default:
            recv(data_socket, recv_buf, BUFSIZE, 0);
            printf("Got %s from server\n", recv_buf);
            break;
    }

    close(data_socket);
    return 0;
}

//"──────▄▀▄─────▄▀▄\n─────▄█░░▀▀▀▀▀░░█▄\n─▄▄──█░░░░░░░░░░░█──▄▄\n█▄▄█─█░░▀░░┬░░▀░░█─█▄▄█\n"

