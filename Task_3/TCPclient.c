//https://www.linuxhowtos.org/data/6/client.c
//https://www.linuxhowtos.org/C_C++/socket.htm


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>  
#include <ctype.h>  
#include <fcntl.h>
#include <resolv.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h> // inet_addr()
#include <strings.h> // bzero()
#include <unistd.h> // read(), write(), close()
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <errno.h>
#include <sys/time.h> // gettimeofday()
#include <resolv.h>
#include <time.h>
#include <net/ethernet.h>



void checksum(char * buff, long long * sum, int bufflen){
    // printf ("size of buffer is %ld checksum b4 = %lld   ....",strlen(buff),*sum);
    for (int i=0; i< bufflen+1;i++){
        if (isalpha(buff[i])){
            *sum += buff[i];
        }  
    }
    // printf("checksum atfter is %lld\n",*sum);
    
}

void error(const char *msg){
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]){
    
    // printf("start\n");
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR connecting");
    }


    clock_t start, stop;
    long long c=0;
    long long *csum =&c;
    long long c1=0;
    long long *csum1=&c1;
    int fd= open("file.txt",O_RDONLY);
    int nread;
    char buff[1000000];
    
    start = clock();
	while (nread = read(fd, buff, sizeof buff), nread > 0){
		// printf("nread = %d\n",nread);
        checksum(buff,csum,nread);
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		} 
    stop= clock();
    printf("start time: %ld  end time: %ld\n",start,stop);
    printf("diff = %ld\n", stop-start);
    printf("check sum %lld\n",c);

    close(sockfd);
    return 0;
}
