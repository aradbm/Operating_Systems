#ifndef REACT_SERVER_H
#define REACT_SERVER_H

#define PORT "9034" // Port we're listening on

void setup_server();
void accept_connection(int listener);
void echo_response(int client_fd);

#endif
