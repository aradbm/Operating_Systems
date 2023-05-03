
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
#include <sys/mman.h> 





void checksum(char * buff, long long * sum, int bufflen){
    // printf ("size of buffer is %ld checksum b4 = %lld   ....",strlen(buff),*sum);
    for (int i=0; i< bufflen+1;i++){
        if (isalpha(buff[i])){
            *sum += buff[i];
        }
        
    }
    // printf("checksum after is %lld\n",*sum);
}



// https://stackoverflow.com/questions/26582920/mmap-memcpy-to-copy-file-from-a-to-b


int main(int argc, char **argv){

    int sfd, dfd;
    char *src, *dest;
    size_t filesize;

    clock_t start, stop; 
    start = clock();

    /* SOURCE */
    sfd = open("f1.txt", O_RDONLY);
    filesize = lseek(sfd, 0, SEEK_END);
    lseek(sfd,0,0);

    src = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, sfd, 0);


    /* DESTINATION */
    dfd = open("dest.txt", O_RDWR | O_CREAT, 0666);

    ftruncate(dfd, filesize); //make new fie hav the same size as originall file

    dest = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);

    /* COPY */

    memcpy(dest, src, filesize);

    munmap(src, filesize);
    munmap(dest, filesize);


    long long c1=0;
    long long c2=0;
    long long *sumc1=&c1;
    long long *sumc2=&c2;
    
    int nread;
    char buff[1000000];
    
    printf("%d %d\n",sfd,dfd);
	while (nread = read(sfd, buff, sizeof buff), nread > 0){
		printf("nread = %d\n",nread);
        checksum(buff,sumc1,nread);
		bzero(buff, sizeof(buff));
	}

    while (nread = read(dfd, buff, sizeof buff), nread > 0){
		// printf("nread = %d\n",nread);
        checksum(buff,sumc2,nread);
		bzero(buff, sizeof(buff));
	}  

    stop= clock();
    printf("start time: %ld  end time: %ld\n",start,stop);
    printf("diff = %ld\n", stop-start);
    printf("check sum src %lld ,check sum dest %lld\n",c1 ,c2);

    close(sfd);
    close(dfd);

    return 0;
}