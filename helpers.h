#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 1024

struct sockaddr_un *pet__abstract_socket(const char *name, int len, int *addr_len);