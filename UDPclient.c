// https://www.tack.ch/unix/network/sockets/udpv6.shtml

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <arpa/inet.h> // inet_addr()
#include <strings.h>   // bzero()
#include <unistd.h>    // read(), write(), close()
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <errno.h>
#include <sys/time.h> // gettimeofday()
#include <resolv.h>
#include <net/ethernet.h>
#include <time.h>
#include <ctype.h>

#define MAXBUF 1024

#define PORT "7777"

void checksum(char *buff, long long *sum, int bufflen)
{
    for (int i = 0; i < bufflen + 1; i++)
    {
        if (isalpha(buff[i]))
        {
            *sum += buff[i];
        }
    }
}

int main(int argc, char *argv[])
{

    clock_t start, stop;
    int fd1 = open("file.txt", O_RDONLY);
    int fd2 = open("file.txt", O_RDONLY);
    int nread;
    long long c = 0;
    long long *csum = &c;
    char buffer[MAXBUF];
    while (nread = read(fd1, buffer, sizeof buffer), nread > 0)
    {
        checksum(buffer, csum, strlen(buffer));
    }
    printf("checksum = %lld\n", c);
    start = clock();
    while (nread = read(fd2, buffer, sizeof buffer), nread > 0)
    {

        int sock;
        int status;
        struct addrinfo sainfo, *psinfo;
        struct sockaddr_in6 sin6;
        int sin6len;

        sin6len = sizeof(struct sockaddr_in6);
        sock = socket(PF_INET6, SOCK_DGRAM, 0);
        memset(&sin6, 0, sizeof(struct sockaddr_in6));
        sin6.sin6_port = htons(0);
        sin6.sin6_family = AF_INET6;
        sin6.sin6_addr = in6addr_any;

        status = bind(sock, (struct sockaddr *)&sin6, sin6len);

        if (-1 == status)
        {
            perror("bind"), exit(1);
        }

        memset(&sainfo, 0, sizeof(struct addrinfo));
        memset(&sin6, 0, sin6len);

        sainfo.ai_flags = 0;
        sainfo.ai_family = PF_INET6;
        sainfo.ai_socktype = SOCK_DGRAM;
        sainfo.ai_protocol = IPPROTO_UDP;
        status = getaddrinfo("ip6-localhost", PORT, &sainfo, &psinfo);
        status = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)psinfo->ai_addr, sin6len);

        bzero(buffer, sizeof(buffer));
        memset(buffer, '\0', strlen(buffer));
        freeaddrinfo(psinfo);
        psinfo = NULL;
        shutdown(sock, 2);
        close(sock);
    }
    stop = clock();
    printf("start time: %ld  end time: %ld\n", start, stop);
    printf("diff = %ld\n", stop - start);

    return 0;
}
