// https://www.linuxhowtos.org/data/6/server.c
// https://www.linuxhowtos.org/C_C++/socket.htm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <ctype.h>

void checksum(char *buff, long long *sum, int bufflen)
{
    // printf ("size of buffer is %ld checksum b4 = %lld   ....",strlen(buff),*sum);
    for (int i = 0; i < bufflen + 1; i++)
    {
        if (isalpha(buff[i]))
        {
            *sum += buff[i];
        }
    }
    // printf("checksum after is %lld\n",*sum);
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{

    int sockfd, newsockfd, portno;
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("ERROR on binding");
    }
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        error("ERROR on accept");
    }

    clock_t start, end;
    long long c;
    long long *csum = &c;
    start = clock();
    int stop = 0;
    char buffer[1000000];
    while (stop == 0)
    {
        bzero(buffer, sizeof(buffer));
        memset(buffer, '\0', strlen(buffer));
        n = read(newsockfd, buffer, sizeof(buffer));
        if (n < 0)
        {
            error("ERROR reading from socket");
        }
        // printf("we read %d chars into the buffer\n",n);
        checksum(buffer, csum, n);
        if (strstr(buffer, "0") > 0)
        {
            stop = 1;
        }
        if (strlen(buffer) == 0)
        {
            stop = 1;
        }
    }

    end = clock();
    printf("start time : %ld  end time %ld \n", start, end);
    printf("diff = %ld\n", end - start);
    printf("check sum %lld \n", c);

    close(newsockfd);
    close(sockfd);
    return 0;
}
