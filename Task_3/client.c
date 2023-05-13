#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <poll.h>

#define SIZE 1024
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <host> <port>\n", argv[0]);
        exit(1);
    }

    char *hostArgv = argv[1];
    char *portArgv = argv[2];

    int port = atoi(portArgv);

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1)
    {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_aton(hostArgv, &(addr.sin_addr)) == 0)
    {
        perror("inet_aton");
        exit(1);
    }

    int connect_status = connect(client_socket, (struct sockaddr *)&addr, sizeof(addr));

    if (connect_status == -1)
    {
        perror("connect");
        exit(1);
    }

    printf("Connect status ==> %d\n", connect_status);

    struct pollfd pollfds[2];
    pollfds[0].fd = STDIN_FILENO;
    pollfds[0].events = POLLIN | POLLPRI;
    pollfds[1].fd = client_socket;
    pollfds[1].events = POLLIN | POLLPRI;

    while (1)
    {
        int pollResult = poll(pollfds, 2, -1);
        if (pollResult > 0)
        {
            if (pollfds[0].revents & POLLIN)
            {
                char buf_stdin[SIZE];
                ssize_t num_bytes_read = read(STDIN_FILENO, buf_stdin, SIZE - 1);
                if (num_bytes_read > 0)
                {
                    buf_stdin[num_bytes_read] = '\0';
                    ssize_t num_bytes_sent = write(client_socket, buf_stdin, strlen(buf_stdin));

                    if (num_bytes_sent == -1)
                    {
                        perror("write");
                    }

                    if (strncmp(buf_stdin, "end", 3) == 0)
                    {
                        break;
                    }
                }
            }

            if (pollfds[1].revents & POLLIN)
            {
                char buf_socket[SIZE];
                ssize_t num_bytes_received = read(client_socket, buf_socket, SIZE - 1);
                if (num_bytes_received > 0)
                {
                    buf_socket[num_bytes_received] = '\0';
                    printf("From server: %s\n", buf_socket);
                }
                else if (num_bytes_received == 0)
                {
                    printf("Server closed the connection\n");
                    break;
                }
                else
                {
                    perror("read");
                    break;
                }
            }
        }
    }

    close(client_socket);

    return 0;
}
