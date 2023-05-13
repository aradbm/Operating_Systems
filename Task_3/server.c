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

void handle_client(int client_socket);
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s PORT\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = atoi(argv[1]);

    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 10) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", port);

    while (1)
    {
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("Connection established with client %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        handle_client(client_socket);

        close(client_socket);
    }

    close(server_socket);
    return 0;
}

void handle_client(int client_socket)
{
    char recv_buffer[BUFFER_SIZE];
    char send_buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    fd_set readfds;
    int max_fd;

    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(client_socket, &readfds);
        max_fd = client_socket + 1;

        if (select(max_fd, &readfds, NULL, NULL, NULL) < 0)
        {
            perror("select");
            break;
        }

        if (FD_ISSET(client_socket, &readfds))
        {
            memset(recv_buffer, 0, BUFFER_SIZE);
            bytes_received = recv(client_socket, recv_buffer, BUFFER_SIZE - 1, 0);
            if (bytes_received <= 0)
            {
                if (bytes_received == 0)
                {
                    printf("Client disconnected.\n");
                }
                else
                {
                    perror("recv");
                }
                break;
            }

            printf("Client: %s", recv_buffer);
        }

        if (FD_ISSET(STDIN_FILENO, &readfds))
        {
            fgets(send_buffer, BUFFER_SIZE, stdin);
            if (send(client_socket, send_buffer, strlen(send_buffer), 0) < 0)
            {
                perror("send");
                break;
            }
        }
    }
}
