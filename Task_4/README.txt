

OS - Task 4
This program implements a server-client communication using a reactor design pattern. The server listens for incoming client connections and handles their messages. Multiple clients can connect to the server simultaneously.

Prerequisites
Before running the program, ensure that you have the following dependencies installed:

gcc (GNU Compiler Collection)

Installation:
Clone the repository or download the source code files.

Open a terminal and navigate to the directory where the program files are located.

Compile the program by running the following command:

make all

Usage:

In the terminal, start the server by running the following command:

./react_server
Open another terminal to connect to the server using the Telnet client. Use the following command:

telnet localhost 9034
Start sending messages from the Telnet client to the server. You can send multiple messages from different Telnet clients simultaneously.

The server will receive and display the messages from the connected clients.

Example:

$ ./react_server

react_server: new connection from 127.0.0.1 on socket 4
Received message: Hello, world!

react_server: new connection from 127.0.0.1 on socket 5
Received message: How are you?

react_server: new connection from 127.0.0.1 on socket 6
Received message: Greetings from another client!

$ telnet localhost 9034
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
Hello, world!
How are you?

$ telnet localhost 9034
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
Greetings from another client!


Troubleshooting:
If you encounter any issues connecting to the server, make sure that you have followed the installation steps correctly and that the necessary dependencies are installed.

Note: The Void WaitFor(void * this) function mentioned in the code was not implemented in this version due to some complications that arose when connecting to the server.