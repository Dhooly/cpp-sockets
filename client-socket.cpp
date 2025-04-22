#include <iostream>
#include <cstring>          // for strlen()
#include <netinet/in.h>     // for sockaddr_in
#include <sys/socket.h>     // for socket(), connect(), send()
#include <unistd.h>         // for close()

int main(void)
{
  // 1. Create a TCP socket (IPv4, stream-oriented)
  int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket < 0)
  {
    std::cerr << "Error: cannot create socket\n";
    return 1;
  }

  // 2. Define the server’s address to connect to
  sockaddr_in serverAddress;
  std::memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;           // IPv4
  serverAddress.sin_port   = htons(8080);       // Port 8080, network byte order
  serverAddress.sin_addr.s_addr = INADDR_ANY;   // Server on localhost (0.0.0.0)

  // 3. Establish a connection to the server
  if (connect(clientSocket,
        reinterpret_cast<sockaddr*>(&serverAddress),
        sizeof(serverAddress)) < 0) {
    std::cerr << "Error: connect failed\n";
    close(clientSocket);
    return 1;
  }
  std::cout << "Connected to server on port 8080.\n";

  // 4. Send a message to the server
  const char* message = "Hello server!";
  ssize_t bytesSent = send(clientSocket, message, std::strlen(message), 0);
  if (bytesSent < 0)
  {
    std::cerr << "Error: send failed\n";
  }
  else
  {
    std::cout << "Sent message: " << message << "\n";
  }

  // 5. Close the socket
  close(clientSocket);

  return 0;
}
