#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

void accept_forever(int server_sd)
{
    struct sockaddr_in client_addr;
    socklen_t addr_size = sizeof(client_addr);
    int client_sd;

    while (1)
    {
        client_sd = accept(server_sd, (struct sockaddr *)&client_addr, &addr_size);
        if (client_sd == -1)
        {
            fprintf(stderr, "Failed to accept client: %s\n", strerror(errno));
            continue;
        }

        char buffer[1024];
        int bytes_received = recv(client_sd, buffer, sizeof(buffer), 0);
        if (bytes_received > 0)
        {
            buffer[bytes_received] = '\0';
            printf("Received from client: %s\n", buffer);
            send(client_sd, "Message received!", 17, 0);
        }
        close(client_sd);
    }
}

struct sockaddr *sockaddr_new()
{
    return malloc(sizeof(struct sockaddr_in));
}

socklen_t sockaddr_sizeof()
{
    return sizeof(struct sockaddr_in);
}

int main(int argc, char **argv)
{

    // ----------- 1. Create socket object ------------------
    int server_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sd == -1)
    {
        fprintf(stderr, "Could not create socket: %s\n",
                strerror(errno));
        exit(1);
    }

    // ----------- 2. Bind the socket file ------------------

    // Setup the address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(6666);

    int result = bind(server_sd,
                      (struct sockaddr *)&addr, sizeof(addr));
    if (result == -1)
    {
        close(server_sd);
        fprintf(stderr, "Could not bind the address: %s\n",
                strerror(errno));
        exit(1);
    }

    // ----------- 3. Prepare backlog ------------------
    result = listen(server_sd, 10);
    if (result == -1)
    {
        close(server_sd);
        fprintf(stderr, "Could not set the backlog: %s\n",
                strerror(errno));
        exit(1);
    }

    // ----------- 4. Start accepting clients ---------
    accept_forever(server_sd);

    return 0;
}
