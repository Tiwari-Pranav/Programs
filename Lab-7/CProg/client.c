#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUF_SIZE 32

int main(int argc, char *argv[]) {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[BUF_SIZE];

    // create client socket
    if ((client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket creation failed");
        return EXIT_FAILURE;
    }

    // set server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    // connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connection failed");
        return EXIT_FAILURE;
    }

    // receive time from server
    memset(buffer, 0, BUF_SIZE);
    if (recv(client_socket, buffer, BUF_SIZE, 0) < 0) {
        perror("receive failed");
        return EXIT_FAILURE;
    }

    printf("Current time: %s", buffer);

    // close client socket
    close(client_socket);

    return EXIT_SUCCESS;
}

