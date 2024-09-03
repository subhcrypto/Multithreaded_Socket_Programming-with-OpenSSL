#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVERPORT 8990
#define BUFSIZE 4096

int main(int argc, char **argv)
{
    int client_socket;
    struct sockaddr_in server_addr;
    char buff[BUFSIZE];
    int n;

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("Failed to create socket");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVERPORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Failed to connect to server");
        close(client_socket);
        exit(1);
    }

    printf("Connected to server.\n");

    // Communication loop
    for (;;)
    {
        bzero(buff, BUFSIZE);
        printf("Enter message: ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;

        // Send message to server
        write(client_socket, buff, strlen(buff));

        // Exit if the message is "exit"
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Client Exit...\n");
            break;
        }

        bzero(buff, BUFSIZE);

        // Read response from server
        int bytes_read = read(client_socket, buff, sizeof(buff) - 1);
        if (bytes_read < 0)
        {
            perror("Failed to read from server");
            break;
        }

        printf("From server: %s", buff);
    }

    // Close the socket
    close(client_socket);

    return 0;
}
