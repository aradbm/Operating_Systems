#include "react_server.h"
#include "reactor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "hashmap.h"
#include <string.h>
#include <pthread.h>

void *start_reactor_wrapper(void *reactor)
{
    startReactor(reactor);
    return NULL;
}

static reactor_t *reactor;

void setup_server()
{
    int listener;
    struct addrinfo hints, *ai, *p;
    int yes = 1;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    if (getaddrinfo(NULL, PORT, &hints, &ai) != 0)
    {
        fprintf(stderr, "react_server: failed to get address info\n");
        exit(1);
    }

    for (p = ai; p != NULL; p = p->ai_next)
    {
        listener = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (listener < 0)
        {
            continue;
        }

        setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

        if (bind(listener, p->ai_addr, p->ai_addrlen) < 0)
        {
            close(listener);
            continue;
        }

        break;
    }

    if (p == NULL)
    {
        fprintf(stderr, "react_server: failed to bind\n");
        exit(2);
    }

    freeaddrinfo(ai);

    if (listen(listener, 10) == -1)
    {
        perror("listen");
        exit(3);
    }

    // start reactor using WaitFd
    reactor = createReactor(); // Initialize the static reactor variable
    addFd(reactor, listener, accept_connection);
    pthread_t thread;

    stopReactor(reactor);
    reactor = NULL;
}

void accept_connection(int listener)
{
    struct sockaddr_storage remoteaddr;
    socklen_t addrlen = sizeof remoteaddr;
    char remoteIP[INET6_ADDRSTRLEN];

    int newfd = accept(listener, (struct sockaddr *)&remoteaddr, &addrlen);

    if (newfd == -1)
    {
        perror("accept");
    }
    else
    {
        printf("react_server: new connection from %s on socket %d\n",
               inet_ntop(remoteaddr.ss_family, &remoteaddr, remoteIP, INET6_ADDRSTRLEN),
               newfd);
        addFd(reactor, newfd, echo_response);
    }
}
void echo_response(int client_fd)
{
    char buf[256];
    int nbytes;

    if ((nbytes = recv(client_fd, buf, sizeof buf, 0)) <= 0)
    {
        if (nbytes == 0)
        {
            printf("react_server: socket %d hung up\n", client_fd);
        }
        else
        {
            perror("recv");
        }

        close(client_fd);
    }
    else
    {
        buf[nbytes] = '\0';                    // Null-terminate the string
        printf("Received message: %s\n", buf); // Print the received message
    }
}

int main(void)
{
    setup_server();
    return 0;
}