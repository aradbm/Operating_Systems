/// https://www.linuxhowtos.org/data/6/U_server.c



/* a server in the unix domain.  The pathname of 
   the socket address is passed as an argument */
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <stdio.h>
#include <ctype.h> 
#include <time.h>


void checksum(char * buff, long long * sum, int bufflen){
    // printf ("size of buffer is %ld checksum b4 = %lld   ....",strlen(buff),*sum);
    for (int i=0; i< bufflen+1;i++){
        if (isalpha(buff[i])){
            *sum += buff[i];
        }
        
    }
    // printf("checksum after is %lld\n",*sum);
}


void error(const char *);


int main(int argc, char *argv[]){

    int sockfd, newsockfd, servlen, n;
    socklen_t clilen;
    struct sockaddr_un  cli_addr, serv_addr;
    // char buf[100000];

    if ((sockfd = socket(AF_UNIX,SOCK_STREAM,0)) < 0){
        error("creating socket");
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, argv[1]);
    servlen=strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);
    if(bind(sockfd,(struct sockaddr *)&serv_addr,servlen)<0){
        error("binding socket"); 
    }

    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
    if (newsockfd < 0){ 
        error("accepting");
    }

    clock_t start, end;
    long long c;
    long long *csum= &c;
    start = clock();
    int stop=0;
    char buffer[1000000];
    while (stop ==0) {
        bzero(buffer,sizeof(buffer));
        memset(buffer,'\0',strlen(buffer));
        n = read(newsockfd,buffer,sizeof(buffer));
        if (n < 0){
         error("ERROR reading from socket");
        }
        // printf("we read %d chars into the buffer\n",n);
        checksum(buffer,csum,n);
        if (strstr(buffer,"0")>0){
            stop=1;
        }
        if(strlen(buffer)==0){
            stop=1;
        }
        if (n < 0) error("ERROR reading from socket");
    }

    end= clock();
    printf("start time : %ld  end time %ld \n",start,end);
    printf("diff = %ld\n", end-start);
    printf("check sum %lld \n",c);
    
    // n=read(newsockfd,buf,80);
    // printf("A connection has been established\n");
    // write(1,buf,n);
    // write(newsockfd,"I got your message\n",19);
    close(newsockfd);
    close(sockfd);
    return 0;
}

void error(const char *msg){
    perror(msg);
    exit(0);
}


















