#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netdb.h>

void stream_client_loop(int conn_sd)
{
    char buffer[1024];
    printf("Enter message: ");
    fgets(buffer, sizeof(buffer), stdin);
    send(conn_sd, buffer, strlen(buffer), 0);

    int bytes_received = recv(conn_sd, buffer, sizeof(buffer), 0);
    if (bytes_received > 0)
    {
        buffer[bytes_received] = '\0';
        printf("Server replied: %s\n", buffer);
    }
}

int main(int argc, char **argv)
{

    // ----------- 1. Create socket object ------------------

    int conn_sd = socket(AF_INET, SOCK_STREAM, 0);
    if (conn_sd == -1)
    {
        fprintf(stderr, "Could not create socket: %s\n",
                strerror(errno));
        exit(1);
    }

    // ------------ 2. Connect to server-- ------------------

    // Find the IP address behind the hostname
    char host[] = "localhost";
    struct hostent *host_entry;
    host_entry = gethostbyname(host);
    if (!host_entry)
    {
        fprintf(stderr, "Could not resolve the host '%s'\n", host);
        exit(1);
    }

    // Prepare the address
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr = *((struct in_addr *)host_entry->h_addr);
    ;
    addr.sin_port = htons(6666);

    int result = connect(conn_sd,
                         (struct sockaddr *)&addr, sizeof(addr));
    if (result == -1)
    {
        close(conn_sd);
        fprintf(stderr, "Could no connect: %s\n", strerror(errno));
        exit(1);
    }

    stream_client_loop(conn_sd);

    return 0;
}