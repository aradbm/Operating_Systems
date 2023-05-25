# OS - Task 4: Server-Client Communication Using Reactor Design Pattern

This project is a demonstration of server-client communication using a reactor design pattern. The server is set up to listen for and handle incoming client connections. It supports multiple simultaneous connections, facilitating concurrent message exchanges.

## Prerequisites

Before running the program, please make sure you have the following dependencies installed:

- `gcc` (GNU Compiler Collection)

## Installation

To install and run this project, follow these steps:

1. **Clone the repository or download the source code files.**

2. **Compile the Program**

    Open your terminal and navigate to the directory where the program files are located. Compile the program by running the following command:

    ```bash
    make all
    ```

## Usage

To use this server-client communication program, follow the steps outlined below:

1. **Start the Server**

    In your terminal, start the server by running the following command:

    ```bash
    ./react_server
    ```

2. **Connect to the Server**

    Open another terminal window and use the Telnet client to connect to the server. To do so, use the following command:

    ```bash
    telnet localhost 9034
    ```

3. **Start Sending Messages**

    You can now start sending messages from the Telnet client to the server. This server supports concurrent connections, allowing you to send multiple messages from different Telnet clients simultaneously.

    The server will receive and display the messages from the connected clients.

## Example

Server terminal:

```bash
$ ./react_server

react_server: new connection from 127.0.0.1 on socket 4
Received message: Hello, world!

react_server: new connection from 127.0.0.1 on socket 5
Received message: How are you?

react_server: new connection from 127.0.0.1 on socket 6
Received message: Greetings from another client!
```

Client terminal(s):
```bash
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
```
