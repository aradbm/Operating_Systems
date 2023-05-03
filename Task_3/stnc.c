
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
int createRandomfile()
{
    int fd;
    char buf[] = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n"};
    fd = open("myrandomfile.txt", O_WRONLY | O_CREAT | O_TRUNC, 00700);
    for (int i = 0; i < 250000; i++)
    {
        write(fd, buf, strlen(buf));
    }
    for (int i = 0; i < 5; i++)
    {
        write(fd, "0", 1);
    }
    return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(1);
}
// Main function
void stnc(int argc, char *argv[])
{
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
            comm_type = optarg;        // ipv4,ipv6,mmap,pipe,uds this is the type of the communication
            comm_param = argv[optind]; // udp/tcp or dgram/stream or file name, depending on the type
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
                // TCPclient("myrandomfile.txt");
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
            if (strcmp(comm_type, "tcp") == 0)
            {
                run_server_and_client(1);
            }
            else if (strcmp(comm_type, "udp") == 0)
            {
                run_server_and_client(2);
            }
            else if (strcmp(comm_type, "mmap") == 0)
            {
                run_server_and_client(3);
            }
            else if (strcmp(comm_type, "pipe") == 0)
            {
                run_server_and_client(4);
            }
            else if (strcmp(comm_type, "uds") == 0 && strcmp(comm_param, "dgram") == 0)
            {
                run_server_and_client(5);
            }
            else if (strcmp(comm_type, "uds") == 0 && strcmp(comm_param, "stream") == 0)
            {
                run_server_and_client(6);
            }
            else
            {
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
void run_server_and_client(int x)
{
    createRandomfile();
    // printf("created random file\n");
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
    // switch case.
    // 1. tcp
    // 2. udp
    // 3. mmap
    // 4. pipe
    // 5. uds dgram
    // 6. uds stream

    switch (x)
    {
    case 1:
        // TCP server and client
        {
            // printf("~~~ START TCP ~~~\n");
            clock_t start, end;
            start = clock();
            int forktcp = fork();
            if (forktcp < 0)
            {
                printf("error\n");
            }
            if (forktcp == 0)
            {
                // printf("childfork\n");
                sleep(5);
                // tcp client
                TCPclient("myrandomfile.txt");
                exit(0);
            }
            else
            {
                // tcp server
                //  printf("parentfork\n");
                TCPserver("newfile.txt");
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
                printf("it took TCP %f seconds to run\n", cpu_time_used);
            }
            else
            {
                printf("TCP %d\n", -1);
            }
            // printf("~~~ END TCP ~~~\n\n");
        }
        break;
    case 2:
        // Udp server and client
        {
            // printf("~~~ START UDP ~~~\n");
            clock_t start, end;
            start = clock();
            int forkudp = fork();
            if (forkudp < 0)
            {
                printf("error\n");
            }
            if (forkudp == 0)
            {
                sleep(5);
                // udp client
                UDPclient("myrandomfile.txt");
                exit(0);
            }
            else
            {
                // udp server
                UDPserver("newfile.txt");
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
                printf("it took UDP %f seconds to run\n", cpu_time_used);
            }
            else
            {
                printf("UDP %d\n", -1);
            }
            // printf("~~~ END UDP ~~~\n\n");
        }
        break;
    case 3:
        // mmap:
        {
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
        break;
    case 4:
        // pipes:
        {
            // printf("~~~ START PIPE ~~~\n");
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
        break;
    case 5:
        // uds tcp
        {
            // printf("~~~~ START UDS-TCP ~~~\n");
            clock_t start, end;
            start = clock();
            int forkudstcp = fork();

            if (forkudstcp < 0)
            {
                printf("error\n");
            }
            if (forkudstcp == 0)
            {
                // udstcp server
                UDStcpServer("newfile.txt");
                exit(0);
            }
            else
            {
                sleep(2);
                // udstcp client
                UDStcpClient("myrandomfile.txt");
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
                printf("it took UDS-TCP %f seconds to run\n", cpu_time_used);
            }
            else
            {
                printf("UDS-TCP %d\n", -1);
            }
            // printf("~~~ END UDS-TCP ~~~\n\n");
        }
        break;
    case 6:
        // uds udp
        {
            // printf("~~~ START UDS-UDP ~~~\n");
            clock_t start, end;
            start = clock();
            int forkudsudp = fork();

            if (forkudsudp < 0)
            {
                printf("error\n");
            }
            if (forkudsudp == 0)
            {
                UDSdgramServer("newfile.txt");
                exit(0);
            }
            else
            {
                sleep(5);
                UDSdgramClient("myrandomfile.txt");
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
                printf("it took UDS-UDP %f seconds to run\n", cpu_time_used);
            }
            else
            {
                printf("UDS-UDP %d\n", -1);
            }

            unlink(CLIENT_SOCK_FILE);
            unlink(SERVER_SOCK_FILE);
            // printf("~~~ END UDS-UDP ~~~\n\n");
        }
        break;
    case 7:
        break;
    case 8:
        break;
    default:
        printf("error\n");
        exit(0);
        break;
    }
}

//////// functions for clients and servers
void TCPserver(char *filename)
{

    int sockfd, newsockfd, portno;
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    int n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("error\n");
        error("ERROR opening socket");
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(PORT);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("error\n");
        error("ERROR on binding");
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

void TCPclient(char *filename)
{
    int sockfd, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    portno = atoi(PORT);
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

void UDSdgramServer(char *filename)
{
    int fd;
    struct sockaddr_un addr;
    char buff[8192];
    struct sockaddr_un from;
    int ok = 1;
    int len;
    socklen_t fromlen = sizeof(from);
    int fs = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00700);

    if ((fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        ok = 0;
    }

    if (ok)
    {
        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path, SERVER_SOCK_FILE);
        unlink(SERVER_SOCK_FILE);
        if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("bind");
            ok = 0;
        }
    }

    while ((len = recvfrom(fd, buff, sizeof(buff), 0, (struct sockaddr *)&from, &fromlen)) > 0)
    {
        write(fs, buff, len);
        if (strstr(buff, "0") != NULL)
        {
            break;
        }
        bzero(buff, sizeof(buff));
    }
    close(fs);

    if (fd >= 0)
    {
        close(fd);
    }
}

void UDSdgramClient(char *filename)
{
    int fd, w;
    struct sockaddr_un addr;
    char buff[1024];
    int ok = 1;
    int fs = open(filename, O_RDONLY);

    if ((fd = socket(PF_UNIX, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket");
        ok = 0;
    }

    if (ok)
    {
        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path, CLIENT_SOCK_FILE);
        unlink(CLIENT_SOCK_FILE);
        if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        {
            perror("bind");
            ok = 0;
        }
    }

    if (ok)
    {
        memset(&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path, SERVER_SOCK_FILE);
        if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1)
        {
            perror("connect");
            ok = 0;
        }
    }

    bzero(buff, sizeof(buff));

    while ((w = read(fs, buff, sizeof(buff))) > 0)
    {
        if (send(fd, buff, w, 0) == -1)
        {
            perror("send");
            break;
        }
    }
    close(fs);

    if (fd >= 0)
    {
        close(fd);
    }

    unlink(CLIENT_SOCK_FILE);
}

void UDPserver(char *filename)
{

    int stop = 0;

    char buffer[256];
    int fdest = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00700);
    memset(buffer, '\0', strlen(buffer));

    while (stop == 0)
    {
        memset(buffer, '\0', strlen(buffer));
        int sock;
        int status;
        struct sockaddr_in6 sin6;
        socklen_t sin6len;

        sock = socket(PF_INET6, SOCK_DGRAM, 0);
        sin6len = sizeof(struct sockaddr_in6);
        memset(&sin6, 0, sin6len);

        /* just use the first address returned in the structure */

        sin6.sin6_port = htons(atoi(PORT));
        sin6.sin6_family = AF_INET6;
        sin6.sin6_addr = in6addr_any;

        status = bind(sock, (struct sockaddr *)&sin6, sin6len);
        if (-1 == status)
        {
            perror("bind"), exit(1);
        }

        status = getsockname(sock, (struct sockaddr *)&sin6, &sin6len);
        status = recvfrom(sock, buffer, 1024, 0, (struct sockaddr *)&sin6, &sin6len);

        write(fdest, buffer, status);
        if (strstr(buffer, "0") > 0)
        {
            stop = 1;
        }
        bzero(buffer, sizeof(buffer));
        memset(buffer, '\0', strlen(buffer));
        shutdown(sock, 2);
        close(sock);
    }
}

void UDPclient(char *filename)
{

    int fd1 = open(filename, O_RDONLY);
    int nread;
    char buffer[256];
    while (nread = read(fd1, buffer, sizeof buffer), nread > 0)
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
        status = sendto(sock, buffer, nread, 0, (struct sockaddr *)psinfo->ai_addr, sin6len);

        bzero(buffer, sizeof(buffer));
        memset(buffer, '\0', strlen(buffer));
        freeaddrinfo(psinfo);
        psinfo = NULL;
        shutdown(sock, 2);
        close(sock);
    }
}
