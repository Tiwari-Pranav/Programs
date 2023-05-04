// Client side C program 
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
// #include <bits/stdc++.h>
#include<time.h>
#define PORT 8080
int main(int argc, char const* argv[])
{
	time_t t;
	time(&t);
	int sock = 0, valread, client_fd;
	struct sockaddr_in serv_addr;
    //string to store message to server
	char msg[100];
    //prompting user to enter message
    printf("Enter message for server:\n");
    fgets(msg, sizeof(msg), stdin);
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
		<= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if ((client_fd
		= connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr)))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
	send(sock, msg, strlen(msg), 0);
	printf("\n%s: !!Message Sent!!\n\n",ctime(&t));
	valread = read(sock, buffer, 1024);
	printf("\n%s: Response from server: \n%s\n",ctime(&t), buffer);

	// closing the connected socket
	close(client_fd);
	return 0;
}
