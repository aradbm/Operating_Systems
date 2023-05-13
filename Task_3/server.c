
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <poll.h>
#include <stdlib.h>

#define SIZE 1024
#define MAX_CLIENTS 10

int creat_socket(int port, const char *server_ip)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_aton(server_ip, &addr.sin_addr) == 0)
    {
        perror("inet_aton");
    }

    int bindResult = bind(server_socket, (struct sockaddr *)&addr, sizeof(addr));
    if (bindResult == -1)
    {
        perror("bindResult");
    }

    int listenResult = listen(server_socket, 5);
    if (listenResult == -1)
    {
        perror("listenResult");
    }

    printf("server start\n");
    return server_socket;
}

int wait_client(int server_socket)
{
    struct pollfd pollfds[MAX_CLIENTS + 1];
    pollfds[0].fd = server_socket;
    pollfds[0].events = POLLIN | POLLPRI;
    int useClient = 0;

    while (1)
    {
        int pollResult = poll(pollfds, useClient + 1, 5000);
        if (pollResult > 0)
        {
            if (pollfds[0].revents & POLLIN)
            {
                struct sockaddr_in cliaddr;
                socklen_t addrlen = sizeof(cliaddr);
                int client_socket = accept(server_socket, (struct sockaddr *)&cliaddr, &addrlen);
                printf("accept success %s\n", inet_ntoa(cliaddr.sin_addr));
                for (int i = 1; i < MAX_CLIENTS; i++)
                {
                    if (pollfds[i].fd == 0)
                    {

                        pollfds[i].fd = client_socket;
                        pollfds[i].events = POLLIN | POLLPRI;
                        useClient++;
                        break;
                    }
                }
            }
            for (int i = 1; i < MAX_CLIENTS; i++)
            {
                if (pollfds[i].fd > 0 && pollfds[i].revents & POLLIN)
                {
                    char buf[SIZE];
                    int bufSize = read(pollfds[i].fd, buf, SIZE - 1);
                    if (bufSize == -1)
                    {
                        pollfds[i].fd = 0;
                        pollfds[i].events = 0;
                        pollfds[i].revents = 0;
                        useClient--;
                    }
                    else if (bufSize == 0)
                    {
                        pollfds[i].fd = 0;
                        pollfds[i].events = 0;
                        pollfds[i].revents = 0;
                        useClient--;
                    }
                    else
                    {
                        buf[bufSize] = '\0';
                        printf("From client: %s\n", buf);

                        // Relay the message to all connected clients
                        for (int j = 1; j < MAX_CLIENTS; j++)
                        {
                            if (pollfds[j].fd > 0 && pollfds[j].fd != pollfds[i].fd)
                            {
                                ssize_t num_bytes_sent = write(pollfds[j].fd, buf, strlen(buf));
                                if (num_bytes_sent == -1)
                                {
                                    perror("write");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <server_ip> <port>\n", argv[0]);
        exit(1);
    }
    const char *server_ip = argv[1];
    int port = atoi(argv[2]);
    int server_socket = creat_socket(port, server_ip);
    int client_socket = wait_client(server_socket);
    close(client_socket);
    close(server_socket);
    return 0;
}