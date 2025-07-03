"Simple TCP Client-Server Application"
This repository contains a basic implementation of a TCP client-server application written in C.
The server accepts connections from clients, receives messages, and responds with a confirmation. 
The client connects to the server, sends a message, and displays the server's response.
Features

Server: Listens for incoming connections on port 6666, accepts client messages, and responds with "Message received!".
Client: Connects to the server at localhost:6666, sends a user-provided message, and displays the server's response.
Single-threaded server that handles one client at a time.
Error handling for socket creation, binding, connection, and data transfer.

"Prerequisites"

A C compiler (e.g., gcc)
POSIX-compliant system (e.g., Linux, macOS, or WSL on Windows)
Standard C libraries (stdio.h, stdlib.h, string.h, errno.h, unistd.h, sys/socket.h, netinet/in.h, netdb.h)

"Files"

server.c: Implements the TCP server that listens for and processes client connections.
client.c: Implements the TCP client that connects to the server and sends/receives messages.

Compilation
To compile the server and client, use the following commands:
gcc -o server server.c
gcc -o client client.c

Usage

Start the server:Run the server in a terminal window:
./server

The server will listen for connections on localhost:6666.

Run the client:In another terminal window, run the client:
./client

The client will prompt you to enter a message, send it to the server, and display the server's response.

Example Interaction:

Server output (upon receiving a client message):Received from client: Hello, server!


Client output (after sending a message):Enter message: Hello, server!
Server replied: Message received!

Notes

The server runs indefinitely, handling one client at a time. To stop the server, use Ctrl+C.
The client sends a single message and exits after receiving the server's response.
The server binds to INADDR_ANY, allowing connections from any IP address on port 6666.
The client connects to localhost. To connect to a different server, modify the host variable in client.c.

Limitations

The server is single-threaded and processes one client at a time. For concurrent clients, consider using threads or a fork-based approach.
No advanced error recovery or timeout mechanisms are implemented.
The buffer size is fixed at 1024 bytes; larger messages may be truncated.
