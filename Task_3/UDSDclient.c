#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>

// #define SOCKET_NAME "/tmp/fdexample"
// //https://github.com/octurion/unix-fd-passing/blob/master/LICENSE.txt
// void checksum(char * buff, long long * sum, int bufflen){
//     // printf ("size of buffer is %ld checksum b4 = %lld   ....",strlen(buff),*sum);
//     for (int i=0; i< bufflen+1;i++){
//         if (isalpha(buff[i])){
//             *sum += buff[i];
//         }
        
//     }
//     // printf("checksum after is %lld\n",*sum);
// }
// void error(const char *);

// // int main(void)
// // {
// // 	int exit_code = EXIT_FAILURE;
// // 	int ret;

// // 	// Open up a Unix domain socket...
// // 	int sock_fd = socket(AF_UNIX, SOCK_DGRAM, 0);
// // 	if (sock_fd < 0) {
// // 		perror("socket()");
// // 		goto out;
// // 	}

// // 	// ...and then connect to the server
// // 	struct sockaddr_un addr = {
// // 		.sun_family = AF_UNIX,
// // 		.sun_path = SOCKET_NAME,
// // 	};
// // 	clock_t start, stop;
// // 	 start = clock();
// // 	// ret = connect(sock_fd, (const struct sockaddr*) &addr, sizeof(addr));
// // 	// if (ret < 0) {
// // 	// 	perror("connect()");
// // 	// 	goto out2;
// // 	// }

// // 	// We have to receive that one byte the server sent
// // 	char tmp_msgbuf = '\0';
// // 	struct iovec iov = {
// // 		.iov_base = &tmp_msgbuf,
// // 		.iov_len = 1,
// // 	};

// // 	// Set up the ancillary message header the kernel will use to pass
// // 	// the file descriptor from the server
// // 	char cmsgbuf[CMSG_SPACE(sizeof(int))] = {0};
// // 	struct msghdr msg = {
// // 		.msg_name = NULL,
// // 		.msg_namelen = 0,
// // 		.msg_iov = &iov,
// // 		.msg_iovlen = 1,
// // 		.msg_control = cmsgbuf,
// // 		.msg_controllen = sizeof(cmsgbuf),
// // 		.msg_flags = 0,
// // 	};
// // 	ret = recvmsg(sock_fd, &msg, 0);
// // 	if (ret < 0) {
// // 		perror("recvmsg()");
// // 		goto out2;
// // 	}

// // 	// Now get the file descriptor from the server
// // 	struct cmsghdr* cmsg = CMSG_FIRSTHDR(&msg);
// // 	if (cmsg == NULL || cmsg->cmsg_type != SCM_RIGHTS) {
// // 		fprintf(stderr, "No file descriptor rights data\n");
// // 		goto out2;
// // 	}

// // 	int file_fd;
// // 	memcpy(&file_fd, CMSG_DATA(cmsg), sizeof(file_fd));

// // 	// Query the size of the file
// // 	struct stat st;
// // 	ret = fstat(file_fd, &st);
// // 	if (ret < 0) {
// // 		perror("fstat()");
// // 		goto out3;
// // 	}
// // 	printf("Size of file: %ju\n", (intmax_t) st.st_size);

// // 	// Try to write to the file. If the server opened the file with `O_RDONLY`,
// // 	// `write()` will fail. If the server opened the file with
// // 	// `O_RDWR | O_APPEND`, not only will `write()` succeed, but also our
// // 	// message will be appended to the end of the file.
// // 	ret = write(file_fd, "Hello\n", strlen("Hello\n"));
// // 	if (ret < 0) {
// // 		perror("write()");
// // 		fprintf(stderr, "As you can see, you cannot write to the file\n");
// // 	} else {
// // 		fprintf(stderr, "As you can see, you can write to the file\n");
// // 	}
// // 	stop= clock();
// //     printf("start time: %ld  end time: %ld\n",start,stop);
// //     printf("diff = %ld\n", stop-start);

// // 	exit_code = EXIT_SUCCESS;

// // out3:
// // 	close(file_fd);
// // out2:
// // 	close(sock_fd);
// // out:
// // 	return exit_code;
// // }

// int main(int argc, char* argv[])
// {
//     int sock, length;
//     struct sockaddr_un name;
//     char buf[1024];


//     /* Create socket from which to read. */
//     sock = socket(AF_UNIX, SOCK_DGRAM, 0);
//     if (sock < 0) {
//         perror("opening datagram socket");
//         exit(1);
//     }


//     /* Create name. */
//     name.sun_family = AF_UNIX;
//     strcpy(name.sun_path, SOCKET_NAME);


//     /* Bind the UNIX domain address to the created socket */
//     if (bind(sock, (struct sockaddr *) &name, sizeof(struct sockaddr_un))) {
//         perror("binding name to datagram socket");
//         exit(1);
//     }
//     printf("socket -->%s\n", argv[1]);


//     /* Read from the socket */
//     if (read(sock, buf, 1024) < 0)
//         perror("receiving datagram packet");
//     printf("-->%s\n", buf);
//    clock_t start, stop;
//     long long c=0;
//     long long *csum =&c;
//     int fd= open("aa.txt",O_RDONLY);
//     int nread;
//     char buff[1024];
// 	 start = clock();
// 	while (nread = read(fd, buff, sizeof buff), nread > 0){
// 		// printf("nread = %d\n",nread);
// 		 checksum(buff,csum,nread);
// 		  if (sendto(sock, buff, sizeof(buff), 0,
        
// 		&name, sizeof(struct sockaddr_un)) < 0) {
//         perror("sending datagram message");
//     }
// 		bzero(buff, sizeof(buff));
// 		} 
//     stop= clock();
//     printf("start time: %ld  end time: %ld\n",start,stop);
//     printf("diff = %ld\n", stop-start);
//     printf("check sum %lld\n",c);
//     close(sock);
//     unlink(SOCKET_NAME);
// }
// void error(const char *msg){
//     perror(msg);
//     exit(0);
// }
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "ipc.h"

int main() {
	int fd,w;
	struct sockaddr_un addr;
	int ret;
	char buff[1024];
    char buffer[1024];
	struct sockaddr_un from;
	int ok = 1;
	int len;
    int fs= open("aa.txt",O_RDONLY);

	if ((fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0) {
		perror("socket");
		ok = 0;
	}

	if (ok) {
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		strcpy(addr.sun_path, CLIENT_SOCK_FILE);
		unlink(CLIENT_SOCK_FILE);
		if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
			perror("bind");
			ok = 0;
		}
	}

	if (ok) {
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		strcpy(addr.sun_path, SERVER_SOCK_FILE);
		if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
			perror("connect");
			ok = 0;
		}
	}

	// if (ok) {
	// 	strcpy (buff, "iccExchangeAPDU");
	// 	if (send(fd, buff, strlen(buff)+1, 0) == -1) {
	// 		perror("send");
	// 		ok = 0;
	// 	}
	// 	printf ("sent iccExchangeAPDU\n");
	// }
    bzero(buff,sizeof(buff));

	 while (w=read(fs,buff,sizeof(buff))>0)
    {
        if (send(fd, buff, strlen(buff)+1, 0) == -1) {
			perror("send");
			break;
		}
    }
    close(fs);

	if (fd >= 0) {
		close(fd);
	}

	unlink (CLIENT_SOCK_FILE);
	return 0;
}
