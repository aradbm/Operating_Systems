/// https://www.linuxhowtos.org/data/6/U_client.c

/* a client in the unix domain */
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h> // read(), write(), close()
#include <time.h>
#include <fcntl.h>
#include <strings.h> // bzero()

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

void error(const char *);

int main(int argc, char *argv[])
{
    int sockfd, servlen, n;
    struct sockaddr_un serv_addr;
    // char buffer[100000];

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, argv[1]);
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        error("Creating socket");
    }
    if (connect(sockfd, (struct sockaddr *)&serv_addr, servlen) < 0)
    {
        error("Connecting");
    }

    clock_t start, stop;
    long long c = 0;
    long long *csum = &c;
    int fd = open("file.txt", O_RDONLY);
    int nread;
    char buff[1000000];

    start = clock();
    while (nread = read(fd, buff, sizeof buff), nread > 0)
    {
        // printf("nread = %d\n",nread);
        checksum(buff, csum, nread);
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
    }
    stop = clock();
    printf("start time: %ld  end time: %ld\n", start, stop);
    printf("diff = %ld\n", stop - start);
    printf("check sum %lld\n", c);

    close(sockfd);
    return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
