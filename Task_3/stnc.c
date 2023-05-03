
#include "stnc.h"
void checksum(char *buff, long long *sum, int bufflen)
{
    for (int i = 0; i < bufflen + 1; i++)
    {
        if (isalpha(buff[i]))
        {
            *sum += buff[i];
        }
        else if (buff[i] == '0')
        {
            break;
        }
        else if (buff[i] == '\0')
        {
            break;
        }
    }
}
void TCPserver(char *filename, int port)
{

    int sockfd, newsockfd, portno;
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("error\n");
        perror("ERROR opening socket");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(port);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("error\n");
        perror("ERROR on binding");
    }
    listen(sockfd, 5);

    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        printf("error\n");
        error("ERROR on accept");
    }

    int fdest = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00700);

    int stop = 0;
    char buffer[1000000];
    while (stop == 0)
    {
        bzero(buffer, sizeof(buffer));
        memset(buffer, '\0', strlen(buffer));
        n = read(newsockfd, buffer, sizeof(buffer));
        if (n < 0)
        {
            printf("error\n");
            error("ERROR reading from socket");
        }
        write(fdest, buffer, strlen(buffer));
        if (strstr(buffer, "0") > 0)
        {
            stop = 1;
        }
        if (strlen(buffer) == 0)
        {
            stop = 1;
        }
    }
    close(newsockfd);
    close(sockfd);
}
void TCPclient(char *filename, int port)
{
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    portno = atoi(port);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("error\n");
        error("ERROR opening socket");
    }
    server = gethostbyname("localhost");
    if (server == NULL)
    {
        printf("error\n");
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("error\n");
        error("ERROR connecting");
    }

    int fd = open(filename, O_RDONLY);
    int nread;
    char buff[1000000];

    while (nread = read(fd, buff, sizeof buff), nread > 0)
    {
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
    }

    close(sockfd);
}

void UDStcpServer(char *filename)
{

    int sockfd, newsockfd, servlen, n;
    socklen_t clilen;
    struct sockaddr_un cli_addr, serv_addr;

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        error("creating socket");
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, PORTUDS1);
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, servlen) < 0)
    {
        error("binding socket");
    }

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0)
    {
        error("accepting");
    }

    int fdest = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00700);
    int stop = 0;
    char buffer[1000000];

    while (stop == 0)
    {
        bzero(buffer, sizeof(buffer));
        memset(buffer, '\0', strlen(buffer));
        n = read(newsockfd, buffer, sizeof(buffer));
        if (n < 0)
        {
            error("ERROR reading from socket");
        }
        write(fdest, buffer, strlen(buffer));
        if (strstr(buffer, "0") > 0)
        {
            stop = 1;
        }
        if (strlen(buffer) == 0)
        {
            stop = 1;
        }
    }

    close(newsockfd);
    close(sockfd);
    unlink(PORTUDS1);
}

void UDStcpClient(char *filename)
{

    int sockfd, servlen;
    struct sockaddr_un serv_addr;

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, PORTUDS1);
    servlen = strlen(serv_addr.sun_path) + sizeof(serv_addr.sun_family);

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    {
        error("Creating socket");
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, servlen) < 0)
    {
        error("Connecting");
    }
    // printf("client has cnnected\n");

    int fd = open(filename, O_RDONLY);
    int nread;
    char buff[1000000];

    while (nread = read(fd, buff, sizeof buff), nread > 0)
    {
        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
    }
    close(sockfd);
}
// Main function
void stnc(int argc, char *argv[])
{

    ////////////////////////////////
    int fd = open("myrandomfile.txt", O_RDONLY);
    long long checksum1 = 0;
    long long *check = &checksum1;
    char buffer[1000000];
    memset(buffer, '\0', strlen(buffer));
    int n;
    while (n = read(fd, buffer, sizeof buffer), n > 0)
    {
        checksum(buffer, check, n);
        memset(buffer, '\0', strlen(buffer));
    }
    // printf("checksum calc1 = %lld\n",checksum1);
    checksum1 = 0;
    int fd3 = open("myrandomfile.txt", O_RDONLY);
    memset(buffer, '\0', strlen(buffer));
    while (n = read(fd3, buffer, sizeof buffer), n > 0)
    {
        checksum(buffer, check, n);
        memset(buffer, '\0', strlen(buffer));
    }

    ///////////////////////////////
    int opt;
    int client_mode = 0;
    int perform_test = 0;
    int quiet_mode = 0;

    char *comm_type = NULL;
    char *comm_param = NULL;

    char *ip = NULL;
    int port = 0;

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
            client_mode = 0;
            port = atoi(optarg);
            break;
        case 'p':
            perform_test = 1;
            comm_type = optarg;        // ipv4,ipv6,mmap,pipe,uds
            comm_param = argv[optind]; // udp/tcp or dgram/stream or file name
            break;
        case 'q':
            quiet_mode = 1;
            break;
        default:
            fprintf(stderr, "Usage: %s [-c IP PORT] [-s PORT] [-p <type> <param>] [-q]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    // print 1 line sammary of the command line arguments
    if (quiet_mode == 0)
    {
        printf("client_mode = %d\n", client_mode);
        printf("perform_test = %d\n", perform_test);
        printf("comm_type = %s\n", comm_type);
        printf("comm_param = %s\n", comm_param);
        printf("ip = %s\n", ip);
        printf("port = %d\n", port);
    }

    if (client_mode == 1)
    {
        // we open the client side
        // 1. no performance, chat only
        // 2. performance test with mmap
        // 3. performance test with pipe
        // 4. performance test with uds
        // 5. performance test with udp 1 file for ipv4 and ipv6
        // 6. performance test with tcp 1 file for ipv4 and ipv6

        if (perform_test == 0)
        {
            // 1. chat only
        }
        else
        {
            // performance test
            if (strcmp(comm_type, "mmap") == 0)
            {
                // mmap
                // printf("~~~ START MMAP ~~~\n");
                int sfd, dfd;
                char *src, *dest;
                size_t filesize;
                clock_t start, end;

                // SOURCE
                sfd = open("myrandomfile.txt", O_RDONLY);
                filesize = lseek(sfd, 0, SEEK_END);
                lseek(sfd, 0, 0);

                src = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, sfd, 0);
                start = clock();
                int forkmmap = fork();
                if (forkmmap < 0)
                {
                    printf("error");
                }

                if (forkmmap == 0)
                {
                    // child process
                    dfd = open("newfile.txt", O_RDWR | O_CREAT, 0666);
                    ftruncate(dfd, filesize); // make new fie hav the same size as originall file
                    dest = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
                    // COPY
                    memcpy(dest, src, filesize);
                    munmap(src, filesize);
                    munmap(dest, filesize);
                    exit(0);
                }
                end = clock();

                int fd2 = open("newfile.txt", O_RDONLY);
                long long checksum2 = 0;
                long long *check2 = &checksum2;
                memset(buffer, '\0', strlen(buffer));
                while (n = read(fd2, buffer, sizeof buffer), n > 0)
                {
                    checksum(buffer, check2, strlen(buffer));
                    memset(buffer, '\0', strlen(buffer));
                }
                // printf("checksum2 = %lld\n",checksum2);
                // printf ("checksum before - checksum atfer = %lld \n",checksum1-checksum2);
                if (checksum1 - checksum2 == 0)
                {
                    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                    printf("it took MMAP %f seconds to run\n", cpu_time_used);
                }
                else
                {
                    printf("MMAP %d\n", -1);
                }
                // printf("~~~ END MMAP ~~~\n\n");
            }
            else if (strcmp(comm_type, "pipe") == 0)
            {
                // pipe
                int fdone[2];
                pid_t childid;
                char readBuff[BUFFER_SIZE_PIPE];
                clock_t start, end;
                start = clock();

                if (pipe(fdone) < 0)
                {
                    printf("ERROR: Opening pipe failed\n");
                    exit(1);
                }

                int fileOpen = open("myrandomfile.txt", 0);
                int targetFile = open("newfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 00700);

                if (fileOpen == -1 || targetFile == -1)
                {
                    printf("ERROR: Opening file failed\n");
                    exit(1);
                }
                start = clock();
                childid = fork();

                if (childid == 0)
                {
                    // inside the child prcocessmemset
                    close(fdone[1]);
                    int n;
                    while ((n = read(fdone[0], readBuff, sizeof(readBuff))) > 0)
                    {
                        // Writing to the target fileOpen
                        write(targetFile, readBuff, n);
                        memset(readBuff, '\0', BUFFER_SIZE_PIPE);
                    }

                    close(fdone[0]);
                    close(targetFile);
                    exit(0);
                }
                else
                {
                    // inside the parent process
                    close(fdone[0]);

                    // code to read from a text file
                    int n;
                    while ((n = read(fileOpen, readBuff, sizeof(readBuff))) > 0)
                    {
                        write(fdone[1], readBuff, n);
                        memset(readBuff, '\0', BUFFER_SIZE_PIPE);
                    }

                    close(fdone[1]);
                    close(fileOpen);
                    wait(NULL);
                }
                end = clock();
                int fd2 = open("newfile.txt", O_RDONLY);
                long long checksum2 = 0;
                long long *check2 = &checksum2;
                memset(buffer, '\0', strlen(buffer));
                while (n = read(fd2, buffer, sizeof buffer), n > 0)
                {
                    checksum(buffer, check2, strlen(buffer));
                    memset(buffer, '\0', strlen(buffer));
                }
                // printf("checksum2 = %lld\n",checksum2);
                if (checksum1 - checksum2 == 0)
                {
                    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
                    printf("it took PIPE %f seconds to run\n", cpu_time_used);
                }
                else
                {
                    printf("PIPE %d\n", -1);
                }
                // printf ("checksum before - checksum atfer = %lld \n",checksum1-checksum2);
                // printf("~~~ END PIPE ~~~\n\n");
            }
            else if (strcmp(comm_type, "uds") == 0)
            {
                // uds
            }
            else if (strcmp(comm_type, "udp") == 0)
            {
                // udp
            }
            else if (strcmp(comm_type, "tcp") == 0)
            {
                // tcp
                TCPclient("myrandomfile.txt", port);
            }
            else
            {
                // error
                printf("Error: unknown communication type\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        // we open the server side
        // 1. no performance, chat only
        // 2. performance test with mmap
        // 3. performance test with pipe
        // 4. performance test with uds
        // 5. performance test with udp 1 file for ipv4 and ipv6
        // 6. performance test with tcp 1 file for ipv4 and ipv6

        if (perform_test == 0)
        {
            // no performance, chat only
        }
        else
        {
            if (strcmp(comm_type, "mmap") == 0)
            {
                // mmap
            }
            else if (strcmp(comm_type, "pipe") == 0)
            {
                // pipe
            }
            else if (strcmp(comm_type, "uds") == 0)
            {
                // uds
            }
            else if (strcmp(comm_type, "udp") == 0)
            {
                // udp
            }
            else if (strcmp(comm_type, "tcp") == 0)
            {
                // tcp
                TCPserver("newfile.txt", port);
            }
            else
            {
                // error
                printf("Error: unknown communication type\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    stnc(argc, argv);
    return 0;
}
