#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "ipc.h"
#include <unistd.h>

#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_NAME "/tmp/fdexample"

#define DATA "The sea is calm tonight, the tide is full . . ."

// int main(int argc, char** argv)
// {
// 	int exit_code = EXIT_FAILURE;
// 	int ret;
	

// 	// Open up our file. Change the permissions to just O_RDONLY and observe
// 	// that the client will not be able modify the file in question
// 	int file_fd = open("aa.txt", O_RDWR | O_APPEND);
// 	if (file_fd < 0) {
// 		perror("open()");
// 		goto out;
// 	}

// 	// Unix domain sockets will persist in the file system even after
// 	// closing them, so make sure to delete them
// 	unlink(SOCKET_NAME);

// 	// Open up a Unix domain socket...
// 	int sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
// 	if (sock_fd < 0) {
// 		perror("socket()");
// 		goto out2;
// 	}

// 	// ...and then bind it to a specific filesystem path
// 	struct sockaddr_un addr = {
// 		.sun_family = AF_UNIX,
// 		.sun_path = SOCKET_NAME,
// 	};
// 	 clock_t start, stop;
// 	 start = clock();
// 	ret = bind(sock_fd, (const struct sockaddr*) &addr, sizeof(addr));
// 	if (ret < 0) {
// 		perror("bind()");
// 		goto out3;
// 	}

// 	// Listen for incoming client processes
// 	// ret = listen(sock_fd, 2);
// 	// if (ret < 0) {
// 	// 	perror("listen()");
// 	// 	goto out3;
// 	// }

// 	// Only service 2 clients so that the example server terminates
// 	for (int count = 0; count < 2; count++) {
// 		// Accept an incoming connection
// 		int client_fd = accept(sock_fd, NULL, NULL);
// 		if (client_fd < 0) {
// 			perror("accept()");
// 			continue;
// 		}

// 		// Now we will send the client our file descriptor. We can't just send
// 		// zero bytes of data along with our file descriptors, so just send one
// 		// byte of data.
// 		struct iovec iov = {
// 			.iov_base = "\0",
// 			.iov_len = 1,
// 		};

// 		// Set up the ancillary message header the kernel will use to pass
// 		// the file descriptor to the client.
// 		char cmsgbuf[CMSG_SPACE(sizeof(file_fd))] = {0};
// 		struct msghdr msg = {
// 			.msg_name = NULL,
// 			.msg_namelen = 0,
// 			.msg_iov = &iov,
// 			.msg_iovlen = 1,
// 			.msg_control = cmsgbuf,
// 			.msg_controllen = sizeof(cmsgbuf),
// 			.msg_flags = 0,
// 		};
// 		struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
// 		cmsg->cmsg_len = CMSG_LEN(sizeof(file_fd));
// 		cmsg->cmsg_level = SOL_SOCKET;
// 		cmsg->cmsg_type = SCM_RIGHTS;
// 		// Write the file descriptor we want to pass...
// 		memcpy(CMSG_DATA(cmsg), &file_fd, sizeof(file_fd));

// 		// ...and now send it along
// 		ret = sendmsg(client_fd, &msg, 0);
// 		if (ret < 0) {
// 			perror("sendmsg()");
// 		}

// 		// Close the connextion
// 		close(client_fd);
// 	}
// 	stop= clock();
//     printf("start time: %ld  end time: %ld\n",start,stop);
//     printf("diff = %ld\n", stop-start);
// 	exit_code = EXIT_SUCCESS;

// out3:
// 	close(sock_fd);
// 	// Unix domain sockets will persist in the file system even after
// 	// closing them, so make sure to delete them
// 	unlink(SOCKET_NAME);
// out2:
// 	close(file_fd);
// out:
// 	return exit_code;
// }
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
// int main(int argc, char *argv[])
//    /* int argc;
//     char *argv[];*/
// {
//     int sock;
//     struct sockaddr_un name;


//     /* Create socket on which to send. */
//     sock = socket(AF_UNIX, SOCK_DGRAM, 0);
//     if (sock < 0) {
//         perror("opening datagram socket");
//         exit(1);
//     }
//     /* Construct name of socket to send to. */
//     name.sun_family = AF_UNIX;
//     strcpy(name.sun_path, SOCKET_NAME);
//     /* Send message. */
//     if (sendto(sock, DATA, sizeof(DATA), 0,
        
// 		&name, sizeof(struct sockaddr_un)) < 0) {
//         perror("sending datagram message");
//     }
// 	clock_t start, end;
// 	 long long c;
//     long long *csum= &c;
//     start = clock();
//     int stop=0,n,w;
// 	int fd= open("bb.txt",O_WRONLY | O_CREAT);
//     char buffer[1024];
//     while (stop ==0) {
//         bzero(buffer,sizeof(buffer));
//         memset(buffer,'\0',strlen(buffer));
//         if ((n=read(sock, buffer, 1024)) < 0)
//        { perror("receiving datagram packet");
//         // printf("we read %d chars into the buffer\n",n);
// 		stop=1;
// 	   }
//         checksum(buffer,csum,n);
//         if (strstr(buffer,"0")>0){
//             stop=1;
//         }
//         if(strlen(buffer)==0){
//             stop=1;
//         }
//         if (n < 0) error("ERROR reading from socket");
// 		if((w=write(fd,buffer,sizeof(buffer)))<0)
// 		     {error("ERROR write from socket");
// 			 stop=1;
// 			 }
		
//     }
// 	close(fd);

//     end= clock();
//     printf("start time : %ld  end time %ld \n",start,end);
//     printf("diff = %ld\n", end-start);
//     printf("check sum %lld \n",c);


//     close(sock);
// }
// void error(const char *msg){
//     perror(msg);
//     exit(0);
// }

int main() {
	int fd;
	struct sockaddr_un addr;
	int ret,n;
	char buff[8192];
	struct sockaddr_un from;
	int ok = 1;
	int len;
	socklen_t fromlen = sizeof(from);
    int fs= open("bb.txt",O_WRONLY | O_CREAT |O_TRUNC,00700);

	if ((fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		ok = 0;
	}

	if (ok) {
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		strcpy(addr.sun_path, SERVER_SOCK_FILE);
		unlink(SERVER_SOCK_FILE);
		if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
			perror("bind");
			ok = 0;
		}
	}

	while ((len = recvfrom(fd, buff, sizeof(buff), 0, (struct sockaddr *)&from, &fromlen)) > 0) {
		printf ("recvfrom: %s\n", buff);
		//strcpy (buff, "transmit good!");
		ret = write(fs,buff,strlen(buff));
        if(strstr(buff,"0") != NULL){
            break;
        }
        bzero(buff,sizeof(buff));
		
	}
    // while (n=read(fs,buff,sizeof(buff))>0)
    // {
    //     ret = sendto(fd, buff, strlen(buff)+1, 0, (struct sockaddr *)&from, fromlen);
	// 	if (ret < 0) {
	// 		perror("sendto");
	// 		return 1;
	// 	}
    // }
    close(fs);

	

	if (fd >= 0) {
		close(fd);
	}

	return 0;
}
