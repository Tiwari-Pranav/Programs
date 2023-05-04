// Server side C/C++ program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>
#include <bits/stdc++.h>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
#define PORT 8080
int main(int argc, char const *argv[])
{
	time_t t;
	time(&t);
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	// string to store the response
	char msg[100];
	// ask user for response

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET,
				   SO_REUSEADDR | SO_REUSEPORT, &opt,
				   sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
			 sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
							 (socklen_t *)&addrlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	valread = read(new_socket, buffer, 1024);
	printf("\n%s: Message from client: \n%s\n", ctime(&t), buffer);
	// cout<<typeid(valread).name()<<endl;
	if (buffer[0] == '/')
	{
		string input = buffer;
		input = input.substr(1, input.size() - 2);
		size_t found = input.find(" ");
		string cmd = input.substr(0, found);
		string path = input.substr(found, input.size() - 1);
		string command = "";
		if (cmd == "list")
		{
			command = "ls " + path+" >file.txt";
		}
		else if (cmd == "show")
		{
			command = "cat " + path+" >file.txt";
		}
		// cout<<"Command request:"<< command<<endl;
		system(command.c_str());
		std::ifstream t("file.txt");
		std::stringstream buff;
		buff << t.rdbuf();
		strcpy(msg,buff.str().c_str());
	}
	else
	{
		printf("Enter response for client:\n");
		fgets(msg, sizeof(msg), stdin);
	}

	send(new_socket, msg, strlen(msg), 0);
	printf("\n!!Reply Sent!!\n\n");

	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}
