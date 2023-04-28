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
#include <strings.h> // bzero()
#include <unistd.h> // read(), write(), close()
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


void checksum(char * buff, long long * sum, int bufflen){
    // printf ("size of buffer is %ld checksum b4 = %lld   ....",strlen(buff),*sum);
    for (int i=0; i< bufflen+1;i++){
        if (isalpha(buff[i])){
            *sum += buff[i];
        }
        
    }
    // printf("checksum after is %lld\n",*sum);
}

int main(int argc, char *argv[]){

   
    
    long long c=0;
    long long *csum=&c;
    int stop=0;
    clock_t start, end;	


    char buffer[MAXBUF];
    int fdest=open("newfile.txt",O_WRONLY| O_CREAT  |O_TRUNC,00700);
    memset(buffer,'\0',strlen(buffer));

    start = clock();    
    while(stop==0){
        memset(buffer,'\0',strlen(buffer));
        int sock;
        int status;
        struct sockaddr_in6 sin6;
        socklen_t sin6len;
       

        sock = socket(PF_INET6, SOCK_DGRAM,0);
        sin6len = sizeof(struct sockaddr_in6);
        memset(&sin6, 0, sin6len);

        /* just use the first address returned in the structure */

        sin6.sin6_port = htons(atoi(PORT));
        sin6.sin6_family = AF_INET6;
        sin6.sin6_addr = in6addr_any;
  
        status = bind(sock, (struct sockaddr *)&sin6, sin6len);
        if(-1 == status){
            perror("bind"), exit(1);
        }
    
        status = getsockname(sock, (struct sockaddr *)&sin6, &sin6len);
        status = recvfrom(sock, buffer, MAXBUF, 0, (struct sockaddr *)&sin6, &sin6len);
        write(fdest,buffer,strlen(buffer));
        if (strstr(buffer,"0")>0){
			stop=1;
		}
		bzero(buffer, sizeof(buffer));
        memset(buffer,'\0',strlen(buffer));
        shutdown(sock, 2);
        close(sock);
    }

    end = clock();
    int nread;
    int fd2= open("newfile.txt",O_RDONLY);
    while (nread = read(fd2, buffer, sizeof buffer), nread > 0){
        checksum(buffer,csum,strlen(buffer));
    }
    printf("checksum = %lld\n",c);
	printf("start time : %ld  end time %ld \n",start,end);
	printf("diff = %ld\n", end-start);
    
    return 0;
}


