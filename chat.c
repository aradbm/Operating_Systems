#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

// https://codereview.stackexchange.com/questions/13461/two-way-communication-in-tcp-server-client-implementation

#define MAXSIZE 1024
#define BACKLOG 10

int nc_client(char *s, char *port)
{
    int p = atoi(port);
    struct sockaddr_in server_info;
    struct hostent;
    int socket_fd;

    char sendbuff[1024];
    char recvbuff[1024];
    memset(sendbuff, '\0', sizeof(sendbuff));
    memset(recvbuff, '\0', sizeof(recvbuff));

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "Socket Failure!!\n");
        exit(1);
    }

    memset(&server_info, 0, sizeof(server_info));
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(p);
    server_info.sin_addr.s_addr = inet_addr(s);
    if (connect(socket_fd, (struct sockaddr *)&server_info, sizeof(struct sockaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    while (1)
    {
        fgets(sendbuff, MAXSIZE - 1, stdin);
        if ((send(socket_fd, sendbuff, strlen(sendbuff), 0)) == -1)
        {
            fprintf(stderr, "Failure Sending Message\n");
            close(socket_fd);
            exit(1);
        }

        memset(sendbuff, '\0', sizeof(sendbuff));
        memset(recvbuff, '\0', sizeof(recvbuff));
    }
    close(socket_fd);
}

int nc_server(char *port)
{
    int p = atoi(port);
    struct sockaddr_in server;
    struct sockaddr_in dest;
    int socket_fd, client_fd, num;
    socklen_t size;
    int yes = 1;

    char sendbuff[1024];
    char recvbuff[1024];
    memset(sendbuff, '\0', sizeof(sendbuff));
    memset(recvbuff, '\0', sizeof(recvbuff));

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "Socket failure!!\n");
        exit(1);
    }

    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    memset(&server, 0, sizeof(server));
    memset(&dest, 0, sizeof(dest));
    server.sin_family = AF_INET;
    server.sin_port = htons(p);
    server.sin_addr.s_addr = INADDR_ANY;

    if ((bind(socket_fd, (struct sockaddr *)&server, sizeof(struct sockaddr))) == -1)
    {
        fprintf(stderr, "Binding Failure\n");
        exit(1);
    }

    if ((listen(socket_fd, BACKLOG)) == -1)
    {
        fprintf(stderr, "Listening Failure\n");
        exit(1);
    }

    while (1)
    {

        size = sizeof(struct sockaddr_in);

        if ((client_fd = accept(socket_fd, (struct sockaddr *)&dest, &size)) == -1)
        {
            perror("accept");
            exit(1);
        }

        while (1)
        {
            if ((num = recv(client_fd, recvbuff, sizeof(recvbuff), 0)) == -1)
            {
                perror("recv");
                exit(1);
            }
            else if (num == 0)
            {

                break;
            }
            recvbuff[num] = '\0';
            printf("OBJECT: %s", recvbuff);

            memset(sendbuff, '\0', sizeof(sendbuff));
            memset(recvbuff, '\0', sizeof(recvbuff));
        }
        // Close Connection Socket
        close(client_fd);
    }

    return 0;
}

int main(int argc, char *argv[])
{

    if (argc == 3)
    {
        if (strcmp(argv[1], "-l") == 0)
        {
            // printf("server\n");
            nc_server(argv[2]);
        }
        else
        {
            // printf("client\n");
            nc_client(argv[1], argv[2]);
        }
    }
    else
    {
        printf("too many or not enough args\n");
        return -1;
    }
    return 0;
}