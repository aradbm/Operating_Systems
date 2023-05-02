#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/un.h>
#include <time.h>
#include <errno.h>
#include <sys/time.h>

// Helper functions (you will need to implement these)
int create_tcp_socket(int family);
int create_udp_socket(int family);
void bind_and_listen(int sockfd, int port, int family);
int connect_to_server(int sockfd, const char *ip, int port, int family);
void send_data(int sockfd, const void *data, size_t size, int type);
void recv_data(int sockfd, void *data, size_t size, int type);
void create_mmap_file(const char *filename, size_t size);
void read_mmap_file(const char *filename, size_t size);
void create_named_pipe(const char *filename);
void read_named_pipe(const char *filename);

// Main function
void stnc(int argc, char *argv[])
{
    int opt;
    int client_mode = 0;
    int server_mode = 0;
    int perform_test = 0;
    int quiet_mode = 0;
    char *ip = NULL;
    int port = 0;
    char *comm_type = NULL;
    char *comm_param = NULL;
    // Parse command line arguments
    while ((opt = getopt(argc, argv, "c:s:p:q")) != -1)
    {
        switch (opt)
        {
        case 'c':
            client_mode = 1;
            // optarg: pointer to the start of the option argument
            ip = optarg;
            // optind: index of the next element to be processed in argv
            port = atoi(argv[optind]);
            break;
        case 's':
            server_mode = 1;
            port = atoi(optarg);
            break;
        case 'p':
            perform_test = 1;
            comm_type = optarg;
            comm_param = argv[optind];
            break;
        case 'q':
            quiet_mode = 1;
            break;
        default:
            fprintf(stderr, "Usage: %s [-c IP PORT] [-s PORT] [-p <type> <param>] [-q]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    // Validate arguments and perform the corresponding actions
    if (client_mode)
    {
        // Client-side logic
        // We have now args: ip, port
    }
    else if (server_mode)
    {
        // Server-side logic
        // We have now args: port
        // command to start server on ivp4 with port given.
        // run file ....
    }
    else
    {
        fprintf(stderr, "Error: Either client or server mode must be specified\n");
        exit(EXIT_FAILURE);
    }

    if (perform_test)
    {
        // Performance test logic
        // ...
    }
    else
    {
        // Chat tool logic
        // ...
    }
}

int main(int argc, char *argv[])
{
    stnc(argc, argv);
    return 0;
}
