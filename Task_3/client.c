#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void handle_server(int server_socket);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s IP PORT\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int server_socket;
    struct sockaddr_in server_addr;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0)
    {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server %s:%d\n", ip, port);

    handle_server(server_socket);

    close(server_socket);
    return 0;
}
void handle_server(int server_socket)
{
    char send_buffer[BUFFER_SIZE];
    char recv_buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    fd_set readfds;
    int max_fd;

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(server_socket, &readfds);
        max_fd = server_socket + 1;

        if (select(max_fd, &readfds, NULL, NULL, NULL) < 0)
        {
            perror("select");
            break;
        }

        if (FD_ISSET(server_socket, &readfds))
        {
            memset(recv_buffer, 0, BUFFER_SIZE);
            bytes_received = recv(server_socket, recv_buffer, BUFFER_SIZE - 1, 0);
            if (bytes_received <= 0)
            {
                if (bytes_received == 0)
                {
                    printf("Server disconnected.\n");
                }
                else
                {
                    perror("recv");
                }
                break;
            }

            printf("Server: %s", recv_buffer);
        }

        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            printf("You: ");
            fgets(send_buffer, BUFFER_SIZE, stdin);
            if (send(server_socket, send_buffer, strlen(send_buffer), 0) < 0)
            {
                perror("send");
                break;
            }
        }
    }
}
