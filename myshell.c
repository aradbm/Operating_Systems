#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <getopt.h>
#include <limits.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <signal.h>
#include <wait.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void signal_handler(int signum)
{
    return;
}

void signal_handler2(int signum)
{
    exit(0);
}

// void mydir(){
//     DIR * d;
//     struct dirent *dp;
//     for (d=opendir("."), dp=readdir(d); dp!=NULL; dp =readdir(d)){
//         printf("%s\n",dp->d_name);
//     }
//     printf("\n");
// }

// int copyfile(const char *to, const char *from, int flag);

int main(int argc, char *argv[])
{

    while (1)
    {
        char *buffer;
        size_t bufsize = 1024;
        // size_t characters;

        buffer = (char *)malloc(bufsize * sizeof(char));
        if (buffer == NULL)
        {
            perror("Unable to allocate buffmystrings[i]er");
            exit(1);
        }

        char *mystrings[1024];
        bzero(mystrings, sizeof(mystrings));
        int stringnum = 0;
        // printf("Type something: ");
        getline(&buffer, &bufsize, stdin);
        buffer[strlen(buffer) - 1] = 0;
        if (strcmp(buffer, "exit") == 0)
            return 0;

        char mybuffcopy[1024] = {0};

        strcpy(mybuffcopy, buffer);

        char *token = strtok(mybuffcopy, " ");
        // loop through the string to extract all other tokens
        while (token != NULL)
        {
            mystrings[stringnum] = token;
            stringnum++;
            token = strtok(NULL, " ");
        }

        int seenpipe = 0;
        // int spotpipe=-1;
        int seenbigger1 = 0;
        // int spotbigger1=-1;
        int seendoublebigger = 0;
        int seensomthing = 0;

        for (int i = 0; i < stringnum; i++)
        {

            if (strstr(mystrings[i], "|") != NULL)
            {
                seenpipe++;
                seensomthing++;
                // spotpipe=i;
            }
            if (strstr(mystrings[i], ">>") != NULL)
            {
                seendoublebigger = 1;
                seensomthing++;
                // spotsmaller1=i;
            }
            if (strstr(mystrings[i], ">") != NULL)
            {
                seenbigger1 = 1;
                seensomthing++;
                // spotbigger1=i;
            }
        }

        if (seensomthing == 0)
        {

            int other_fork_id = fork();
            if (other_fork_id == -1)
            {
                printf("error\n");
            }
            else if (other_fork_id == 0)
            {
                execl("/bin/sh", "sh", "-c", buffer, (char *)NULL);
            }
            else
            {
                wait(NULL);
            }
            // }
        }

        else
        {

            if (seenpipe > 0)
            {
                char *piped[2] = {0};
                char mybuffcopypipe[1024];
                memset(mybuffcopypipe, '\0', strlen(mybuffcopypipe));
                bzero(piped, sizeof(piped));
                strcpy(mybuffcopypipe, buffer);
                char *token = strtok(mybuffcopypipe, "|");
                int idx = 0;
                // loop through the string to extract all other tokens
                while (token != NULL)
                {
                    piped[idx] = token;
                    idx++;
                    token = strtok(NULL, "|");
                }

                int fd1[2];
                if (pipe(fd1) == -1)
                {
                    printf("Pipe Failed\n");
                    return 1;
                }

                int pipefork = fork();
                if (pipefork == -1)
                {
                    printf("error\n");
                }
                if (pipefork == 0)
                {

                    dup2(fd1[1], 1);
                    close(fd1[0]);
                    close(fd1[1]);
                    execl("/bin/sh", "sh", "-c", piped[0], (char *)NULL);
                }
                else
                {

                    int pid = fork();

                    if (pid == 0)
                    {
                        dup2(fd1[0], 0);
                        close(fd1[1]);
                        close(fd1[0]);
                        execl("/bin/sh", "sh", "-c", piped[1], (char *)NULL);
                    }
                    else
                    {
                        int status;
                        close(fd1[0]);
                        close(fd1[1]);
                        waitpid(pid, &status, 0);
                    }
                }
            }

            else if (seenbigger1 > 0)
            {
                char *bigger1[2] = {0};
                char mybuffcopybigger1[1024];
                memset(mybuffcopybigger1, '\0', strlen(mybuffcopybigger1));
                bzero(bigger1, sizeof(bigger1));
                strcpy(mybuffcopybigger1, buffer);
                char *token = strtok(mybuffcopybigger1, ">");
                int idx = 0;
                // loop through the string to extract all other tokens
                while (token != NULL)
                {
                    bigger1[idx] = token;
                    idx++;
                    token = strtok(NULL, "|");
                }
                int fd = open(bigger1[1], O_WRONLY | O_CREAT, 00700);

                int bigfork1 = fork();
                if (bigfork1 == -1)
                {
                    printf("error\n");
                }
                if (bigfork1 == 0)
                {
                    dup2(fd, 1);
                    execl("/bin/sh", "sh", "-c", buffer, (char *)NULL);
                }
                else
                {
                    wait(NULL);
                }
            }

            else if (seendoublebigger > 0)
            {
                char *bigger1[2] = {0};
                char mybuffcopybigger1[1024];
                memset(mybuffcopybigger1, '\0', strlen(mybuffcopybigger1));
                bzero(bigger1, sizeof(bigger1));
                strcpy(mybuffcopybigger1, buffer);
                char *token = strtok(mybuffcopybigger1, ">");
                int idx = 0;
                // loop through the string to extract all other tokens
                while (token != NULL)
                {
                    bigger1[idx] = token;
                    idx++;
                    token = strtok(NULL, "|");
                }
                int fd = open(bigger1[1], O_WRONLY | O_CREAT | O_APPEND, 00700);

                int bigfork1 = fork();
                if (bigfork1 == -1)
                {
                    printf("error\n");
                }
                if (bigfork1 == 0)
                {
                    dup2(fd, 1);
                    execl("/bin/sh", "sh", "-c", buffer, (char *)NULL);
                }
                else
                {
                    wait(NULL);
                }
            }
        }
        signal(SIGINT, signal_handler);
    }
    return 0;
}
