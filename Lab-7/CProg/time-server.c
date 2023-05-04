#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_PENDING 5
#define BUF_SIZE 32

int main(int argc, char *argv[]) {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUF_SIZE];
    time_t current_time;

    // create server socket
    if ((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        perror("socket creation failed");
        return EXIT_FAILURE;
    }

    // set server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    // bind server socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        return EXIT_FAILURE;
    }

    // listen for incoming connections
    if (listen(server_socket, MAX_PENDING) < 0) {
        perror("listen failed");
        return EXIT_FAILURE;
    }

    printf("Server listening on port %d...\n", atoi(argv[1]));

    while (1) {
        socklen_t client_len = sizeof(client_addr);

        // accept incoming connection
        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) < 0) {
            perror("accept failed");
            return EXIT_FAILURE;
        }

        printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));

        // get current time and format as string
        current_time = time(NULL);
        snprintf(buffer, BUF_SIZE, "%.24s\n", ctime(&current_time));

        // send time to client
        if (send(client_socket, buffer, strlen(buffer), 0) != strlen(buffer)) {
            perror("send failed");
            return EXIT_FAILURE;
        }

        // close client socket
        close(client_socket);
    }

    // close server socket
    close(server_socket);

    return EXIT_SUCCESS;
}

