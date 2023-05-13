#ifndef STNC
#define STNC
#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h> // read(), write(), close()
#include <time.h>
#include <fcntl.h>
#include <strings.h> // bzero()
#include <resolv.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h> // inet_addr()
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <errno.h>
#include <sys/time.h> // gettimeofday()
#include <net/ethernet.h>
#include <ctype.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/shm.h> // shared memory
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>

#define PORT "77777"
#define PORTUDS1 "12347"
#define SHAREDFILENAME "mysharedfile.txt"
#define BUFFER_SIZE_PIPE 1024

#define CLIENT_SOCK_FILE "csocket"
#define SERVER_SOCK_FILE "ssocket"

#define SIZESM 5000000

void TCPserver(char *filename);
void TCPclient(char *filename);
void UDStcpServer(char *filename);
void UDStcpClient(char *filename);
void UDSdgramServer(char *filename);
void UDSdgramClient(char *filename);
void UDPserver(char *filename);
void UDPclient(char *filename);
void run_server_and_client(int);

#endif