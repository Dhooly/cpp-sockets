#include <iostream>
#include <cstring>          // for memset()
#include <netinet/in.h>     // for sockaddr_in
#include <sys/socket.h>     // for socket(), bind(), listen(), accept()
#include <unistd.h>         // for close()

int main(void)
{
  // 1. Create a TCP socket (IPv4, stream-oriented)
  int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0)
  {
    std::cerr << "Error: cannot create socket\n";
    return 1;
  }

  // 2. Prepare a sockaddr_in struct to describe this server’s address
  sockaddr_in serverAddress;
  std::memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;           // IPv4
  serverAddress.sin_port   = htons(8080);       // Port 8080, network byte order
  serverAddress.sin_addr.s_addr = INADDR_ANY;   // Listen on all available interfaces

  // 3. Bind the socket to our specified IP/port
  if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0)
  {
    std::cerr << "Error: bind failed\n";
    close(serverSocket);
    return 1;
  }

  // 4. Mark the socket as passive to accept connections
  //    backlog = 5: max number of pending connections
  if (listen(serverSocket, 5) < 0)
  {
    std::cerr << "Error: listen failed\n";
    close(serverSocket);
    return 1;
  }

  std::cout << "Server is listening on port 8080...\n";

  // 5. Wait for a client to connect; returns a new socket for the client
  int clientSocket = accept(serverSocket, nullptr, nullptr);

  if (clientSocket < 0)
  {
    std::cerr << "Error: accept failed\n";
    close(serverSocket);
    return 1;
  }

  std::cout << "Client connected!\n";

  // 6. Read data sent by the client
  char buffer[1024] = {0};
  ssize_t bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
  if (bytesReceived < 0)
  {
    std::cerr << "Error: recv failed\n";
  }
  else
  {
    buffer[bytesReceived] = '\0';  // ensure null-terminated
    std::cout << "Message from client: " << buffer << "\n";
  }

  // 7. Close both sockets before exiting
  close(clientSocket);
  close(serverSocket);

  return 0;
}
