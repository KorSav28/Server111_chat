#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

using namespace std;

#define PORT 8000
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
   int client_socket, bytes_sent, bytes_received; 
   struct sockaddr_in server_addr;
   char buffer[BUFFER_SIZE];
   if (argc != 2){
     cout << "Usage: " << argv[0] << "<server_ip>" << endl; 
     exit (EXIT_FAILURE);
   }

   if (client_socket = socket(AF_INET, SOCK_STREAM, 0)== -1) {
     cout << "Socket creation failed"<< endl;
     exit(EXIT_FAILURE);
}

   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(PORT);
  if(inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0){
   cout << "Invalid address" << endl;
   close(client_socket);
   exit(EXIT_FAILURE); 
  } 

if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
  cout<< "Connection failed" << endl; 
  close(client_socket);
  exit(EXIT_FAILURE);
}

cout << "Connected to server"<<endl;

while (true) {
	cout << "Enter message: ";
	cin.getline(buffer, BUFFER_SIZE);

	bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
	if(bytes_sent == -1) {
		cout << "Send failed" << endl;
		close(client_socket);
		exit(EXIT_FAILURE);
	}

	bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
	if (bytes_received == -1) {
	cout << "Receive failed" << endl;
	close(client_socket);
	exit(EXIT_FAILURE);
	}

	buffer[bytes_received]= '\0';
	cout << "Received from server: " << buffer << endl;
}
close(client_socket);
return 0;
}

