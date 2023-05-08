#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>

#define PORT 8081
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

    int server_socket = connect(client_socket, (struct sockaddr *)&addr, sizeof(addr)); // 连接服务器

    if (server_socket == -1)
    {
        perror("connect");
        exit(1);
    }

    printf("Connect result ==> %d\n", server_socket);

    char buf[SIZE] = {0};

    while (1)
    {
        printf("Send to server：");
        scanf("%s", buf);
        ssize_t num_bytes_sent = write(client_socket, buf, strlen(buf));

        if (num_bytes_sent == -1)
        {
            perror("write");
        }

        printf("\n");
        if (strncmp(buf, "end", 3) == 0)
        {
            break;
        }
    }
    close(server_socket);

    return 0;
}
