#include <cstring>
#include <unistd.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
using namespace std;

#define PORT 8000
#define BUFFER_SIZE 1024
#define MESSAGE_SIZE 1024

void handle_client(int client_socket){
  char message [MESSAGE_SIZE];
  
  while(true){
	  memset(message, 0, MESSAGE_SIZE);
	  ssize_t bytes_received = recv(client_socket, message, MESSAGE_SIZE, 0);
       if (bytes_received <= 0){
	       cout << "Client disconnected"<<endl;
	       break;
       }
       if(strncmp("end", message, 3) == 0){
	       cout << "Client exited"<< endl;
	       cout << "Server is exsiting..."<< endl;
	       break;
       }

       cout<< "Data received from client: "<< message << endl;

      memset(message, 0, MESSAGE_SIZE);
     cout<< "Enter the message to client: "<< endl;
      cin.getline(message, MESSAGE_SIZE);

      ssize_t bytes_sent = send(client_socket, message, strlen(message), 0);
     if (bytes_sent >= 0) {
     cout << "Data successfully sent to client" << endl;
     } 
} 
 close (client_socket);
}

int main() {
   int server_socket, client_socket;
   struct sockaddr_in server_addr, client_addr;
   socklen_t client_len = sizeof(client_addr);

   if((server_socket = socket(AF_INET, SOCK_STREAM, 0))== -1) {
     cout << "Socket creation failed"<< endl;
     exit(EXIT_FAILURE);
}

   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(PORT); 

if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
  cout<< "Bind failed" << endl; 
  close(server_socket);
  exit(EXIT_FAILURE);
}

if (listen(server_socket, 5) == -1) {
   cout << "Listen failed" << endl;
   close(server_socket);
   exit(EXIT_FAILURE);
}

cout << "Server is listening on port " << PORT << endl;

while (true) {
     if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) == -1) {
cout << "Accept failed" << endl;
close(server_socket);
exit(EXIT_FAILURE);
}

cout << "Client connected"<< endl;

handle_client(client_socket);
}
close(server_socket);
return 0;
}

