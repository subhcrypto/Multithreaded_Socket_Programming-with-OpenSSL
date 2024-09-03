

# Multithreaded Server-Client Socket Programming Without SSL.

This file demonstrates a basic server-client communication using sockets in C without SSL encryption.

## Files

- servermt.c :The server side program
- client.c : The client side program

## Compilation on Bash

- Server: gcc -o servermt servermt.c -pthread
- Client: gcc -o client client.c

## Runnging Server-Client program

1.Running the server: After compilation both server and client side program on bash correctly, write the command-

```bash
./servermt
```

2.Running Client: Open another bash and write the command 
```bash
./client
```

## Functionality

- The server accepts multiple client connections using threads.
- The client sends messages to the server and receives responses.
- The communication continues until either the client or server sends the message "exit".


