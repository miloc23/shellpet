#include "helpers.h"

struct sockaddr_un *pet__abstract_socket(const char *name, int len, int *addr_len)
{
    if (len > 107) {
        return NULL;
    }
    
    // len + 1 to account for leading '\0' char
    struct sockaddr_un *out = calloc(1, sizeof(sa_family_t) + len + 1);
    out->sun_family = AF_UNIX;
    strncpy(out->sun_path + 1, name, len);
    out->sun_path[0] = '\0';
    
    *addr_len = sizeof(sa_family_t) + len + 1;
    return out;
}
    
