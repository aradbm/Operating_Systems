#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <getopt.h>
#include <limits.h>
#include <sys/stat.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <signal.h>
#include <wait.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


void signal_handler(int signum){

}

void signal_handler2(int signum){
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



int main (int argc, char * argv[]){

      
        
    while(1){
        char *buffer;
        size_t bufsize = 1024;
        // size_t characters;

        buffer = (char *)malloc(bufsize * sizeof(char));
        if( buffer == NULL){
            perror("Unable to allocate buffmystrings[i]er");
            exit(1);
        }
        char* mystrings[1024];
        bzero(mystrings,sizeof(mystrings));
        int stringnum=0;
        // printf("Type something: ");
        getline(&buffer,&bufsize,stdin);
        buffer[strlen(buffer)-1]=0;
  

        char mybuffcopy[1024] = {0};

        strcpy(mybuffcopy, buffer);
        

        char * token = strtok(mybuffcopy, " ");
        // loop through the string to extract all other tokens
        while( token != NULL ) {
            mystrings[stringnum]=token;
            stringnum++;
            token = strtok(NULL, " ");
        }
        
        


        int seenpipe=0;
        // int spotpipe=-1;
        int seenbigger1=0;
        // int spotbigger1=-1;
        int seensmaller1=0;
        // int spotsmaller1=-1;
        int seenbigger2=0;
        // int spotbigger2=-1;
        int seensmaller2=0;
        // int spotsmaller2=-1;
        int seensomthing=0;

        for (int i =0; i<stringnum;i++){
          
            
            if (strstr(mystrings[i],"|")!=NULL){
                seenpipe=1;
                seensomthing++;
                // spotpipe=i;
            }
            if (strstr(mystrings[i],"<")!=NULL){
                seensmaller1=1;
                seensomthing++;
                // spotsmaller1=i;
            }
            if (strstr(mystrings[i],">")!=NULL){
                seenbigger1=1;
                seensomthing++;
                // spotbigger1=i;
            }
            if (strstr(mystrings[i],"}")!=NULL){
                seenbigger2=1;
                seensomthing++;
                // spotbigger2=i;
            }
            if (strstr(mystrings[i],"{")!=NULL){
                seensmaller2=1;
                seensomthing++;
                // spotsmaller2=i;
            }

        }

        
        if (seensomthing==0){

            

            // DIR
            // if (strcmp(mystrings[0],"DIR") == 0){
            //     int dir_fork_id =fork();
            //     if (dir_fork_id==-1){
            //         printf("error\n");
            //     }
            //     else if (dir_fork_id==0){
            //         mydir();
            //     }
            // }

            // COPY
            // else if (strcmp(mystrings[0],"COPY") ==0){
            //     int copy_fork_id =fork();
            //     if (copy_fork_id==-1){
            //         printf("error\n");
            //     }
            //     else if (copy_fork_id==0){
            //         copyfile(mystrings[2],mystrings[1],0);
            //     }
            // }
           
            // else{
                // printf("else\n");
                int other_fork_id =fork();
                if (other_fork_id==-1){
                    printf("error\n");
                }
                else if (other_fork_id==0){                    
                    execl("/bin/sh", "sh", "-c", buffer, (char *)NULL);
                }
                else{
                    wait(NULL);
                }
            // }
        }

        else{

            if (seenpipe>0){ 
                char* piped[2]={0};
                char mybuffcopypipe[1024];
                memset(mybuffcopypipe,'\0',strlen(mybuffcopypipe));
                bzero(piped, sizeof(piped));
                strcpy(mybuffcopypipe, buffer);
                char * token = strtok(mybuffcopypipe, "|");
                int idx=0;
                // loop through the string to extract all other tokens
                while( token != NULL ) {
                    piped[idx]=token;
                    idx++;
                    token = strtok(NULL, "|");
                }
                // int seenDIR=-1;
                // if (strstr(piped[0],"DIR")==0){
                //     seenDIR=0;
                // }
                // else{
                //     seenDIR=1;
                // }
                

            

                int fd1[2];
                if (pipe(fd1) == -1) {
                    printf( "Pipe Failed\n");
                    return 1;
                }
               
                                    
                int pipefork = fork();
                if (pipefork==-1){
                    printf("error\n");
                }
                if (pipefork==0){
                    
                    // if (seenDIR==0){
                        dup2(fd1[1],1);
                        close(fd1[0]);
                        close(fd1[1]);
                        execl("/bin/sh", "sh", "-c", piped[0], (char *)NULL);
                    // }
                    // else{
                    //     printf("DIR in |\n");
                    //     dup2(fd1[1],1);
                    //     close(fd1[0]);
                    //     close(fd1[1]);
                    //     mydir();
                    // }
                    
                
                }
                else{
                    
                    int pid=fork();

                    if(pid==0){
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

            else if (seenbigger1>0){
                char* bigger1[2]={0};
                char mybuffcopybigger1[1024];
                memset(mybuffcopybigger1,'\0',strlen(mybuffcopybigger1));
                bzero(bigger1, sizeof(bigger1));
                strcpy(mybuffcopybigger1, buffer);
                char * token = strtok(mybuffcopybigger1, ">");
                int idx=0;
                // loop through the string to extract all other tokens
                while( token != NULL ) {
                    bigger1[idx]=token;
                    idx++;
                    token = strtok(NULL, "|");
                }
                int fd=open(bigger1[1], O_WRONLY | O_CREAT | O_APPEND ,00700);

                int bigfork1 = fork();
                if (bigfork1==-1){
                    printf("error\n");
                }
                if (bigfork1==0){
                    dup2(fd,1);
                    execl("/bin/sh", "sh", "-c", buffer, (char *)NULL);
                   
                }
                else{
                    wait(NULL);                   
                }
                    
               
            }


            else if (seensmaller1>0){
                char* smaller1[2]={0};
                char mybuffcopysmaller1[1024];
                memset(mybuffcopysmaller1,'\0',strlen(mybuffcopysmaller1));
                bzero(smaller1, sizeof(smaller1));
                strcpy(mybuffcopysmaller1, buffer);
                char * token = strtok(mybuffcopysmaller1, ">");
                int idx=0;
                while( token != NULL ) {
                    smaller1[idx]=token;
                    idx++;
                    token = strtok(NULL, "|");
                }
                int fd=open(smaller1[1], O_RDONLY);

                int smallfork1 = fork();
                if (smallfork1==-1){
                    printf("error\n");
                }
                if (smallfork1==0){
                    dup2(0,fd);
                    execl("/bin/sh", "sh", "-c", buffer, (char *)NULL);
                }
                else{
                    wait(NULL);
                }
             
            }

            else if (seenbigger2>0){


                int size=strlen(buffer)+10;
                char mybuff[size];
                memset(mybuff,'\0',sizeof(mybuff));
                char c1[]={"nc"};
                // char c2[] ={"dir | nc"};
                char c3[]= {" | nc "};
                // if (strstr(buffer,"DIR")!=NULL){
                //         strcpy(mybuff,c2);
                // }
                // else{
                //     strcpy(mybuff, c1);
                // }
                // int num=strlen(mybuff);

                int spotbigger2=-1;
                for (int i=0; i<strlen(buffer);i++){
                    if (buffer[i]=='}' && spotbigger2<0){
                        spotbigger2=i;
                    }
                    else{
                        continue;
                    }
                }      
                
                int seen=0;
                for (int i=0; i<spotbigger2;i++){
                    if (isalpha (buffer[i])){
                        mybuff[i]=tolower(buffer[i]);
                        seen=1;
                    }
                    else{
                        mybuff[i]=buffer[i];
                    }
                }
                if (seen==1){
                    strcat(mybuff, c3);   
                }
                else{
                    strcat(mybuff, c1); 
                }
                int num=strlen(mybuff);

                for (int i=spotbigger2+1; i< strlen(buffer);i++){
                    if (buffer[i]==':'){
                        mybuff[num]=' ';
                    }
                    else{
                        mybuff[num]=buffer[i];
                    }
                    num++;
                }
                // printf("%s\n",mybuff);
                

                int bigfork2 = fork();
                if (bigfork2==-1){
                    printf("error\n");
                }
                if (bigfork2==0){
                    if (seen==1){
                         execl("/bin/sh", "sh", "-c", mybuff, (char *)NULL);
                    }
                    else{
                        execl("/bin/sh", "snc 0 5000 -lh", "-c", mybuff, (char *)NULL);
                    }
                    // execl("/bin/sh", "sh", "-c", mybuff, (char *)NULL);
                }
                else{
                    signal(SIGINT,signal_handler);
                    wait(NULL);
                    signal(SIGINT,signal_handler2);

                }   
               
            }


            else if (seensmaller2>0){
                char start[14]={"nc 0"};
                int size=strlen(buffer)+strlen(start)+5;
                char mybuff[size];
                memset(mybuff,'\0',sizeof(mybuff));
                
                strcpy(mybuff, start);
                int num=strlen(start);
                for (int i=1; i< strlen(buffer);i++){
                    mybuff[num]=buffer[i];
                    num++;
                }
                mybuff[num++]=' ';
                mybuff[num++]='-';
                mybuff[num++]='l';
                // printf("%s\n",mybuff);

                int smallfork2 = fork();
                if (smallfork2==-1){
                    printf("error\n");
                }
                if (smallfork2==0){
                    // execl("/bin/sh", "sh", "-c", mybuff, (char *)NULL);
                    execl("/bin/sh", "snc 0 5000 -lh", "-c", mybuff, (char *)NULL);
                }
                else{
                    signal(SIGINT,signal_handler);
                    wait(NULL);
                    signal(SIGINT,signal_handler2);
                }



            }
        }
    }
    return 0;
}





// https://stackoverflow.com/questions/2180079/how-can-i-copy-a-file-on-unix-using-c



// int copyfile(const char *to, const char *from, int flag){

//     int fd_to, fd_from;
//     char buf[1024];
//     ssize_t nread;
//     if (flag == 0){        
//         fd_from = open(from, O_RDONLY); // using flag read only
//         if (fd_from < 0){
//             // printf("failed opppening first file\n");
//             return -1;
//         }
       
//         fd_to = open(to, O_WRONLY | O_CREAT | O_APPEND ,00700); // using flags write only, if doesnt exist create, makes sure it creates the file,
//         if (fd_to < 0){
//             // printf("failed opppening second file\n");
//             return -1;
//         }
        
//         while (nread = read(fd_from, buf, sizeof buf), nread > 0){
//             char *out_ptr = buf;
//             ssize_t nwritten;
//             do {
//                 nwritten = write(fd_to, out_ptr, nread);
//                 if (nwritten >= 0){
//                     nread -= nwritten;
//                     out_ptr += nwritten;
//                 }
//                 else if (errno != EINTR){
//                     return -1;  
//                 }
//             } while (nread > 0);
//         }

//         if (nread == 0){
//             if (close(fd_to) < 0){
//                 fd_to = -1;
//                 return -1;
//             }
//             close(fd_from);
//             // printf("file is copied\n");
//             return 0;
//         }   
//     }

//     else if (flag == 1){
//         struct stat sl;
//         if (stat(from, &sl) == -1) {
//             copyfile (to,from,0);
//         }
//         else{ 
//             char linkbuf[PATH_MAX];
//             ssize_t checkLink = readlink(from, linkbuf, sizeof(linkbuf));
//             if (checkLink == -1){
//                 copyfile (to,from,0);
//             }
//             else{
//                 fd_to = open(to, O_WRONLY | O_CREAT | O_APPEND ,00700); // using flags write only, if doesnt exist create, makes sure it creates the file,
//                 if (fd_to < 0){
//                     return -1;
//                 }
//                 ssize_t nwritten;
//                 nwritten = write(fd_to, linkbuf, checkLink);
//                 if (nwritten >= 0){
//                     checkLink -= nwritten;
//                 }
//                 else if (errno != EINTR){
//                     return -1;  
//                 }
//                 if (close(fd_to) < 0){
//                     fd_to = -1;
//                     return -1;
//                 }
//                 // printf("file is copied\n");
//                 return 0;
//             }
//         }
//     }     
//     return 0;
// }

