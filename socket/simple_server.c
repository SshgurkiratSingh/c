// Include necessary headers
#include <stdio.h>      // For standard input and output functions
#include <stdlib.h>     // For standard library functions such as exit()
#include <string.h>     // For string handling functions
#include <unistd.h>     // For close() function
#include <sys/socket.h> // For socket functions
#include <arpa/inet.h>  // For inet_addr structures and functions
#include <netinet/in.h> // For sockaddr_in structure
#include <signal.h>     // For signal() function
#include <asm-generic/socket.h>
// Define constants
#define PORT 8080         // Port number on which the server will listen
#define BUFFER_SIZE 1024  // Size of the buffer to store received data
int server_fd, client_fd; // File descriptors for server and client
void handler(int sig)
{
    // Close the sockets and exit the program
    printf("Closing server...\n");
    close(server_fd);
    close(client_fd);
    exit(0);
}

// Main function
int main()
{

    struct sockaddr_in address;     // Structure to hold server address information
    int addrlen = sizeof(address);  // Size of the address structure
    char buffer[BUFFER_SIZE] = {0}; // Buffer to store incoming data
    int opt = 1;                    // Option for setsockopt
    signal(SIGINT, handler);        // Handle SIGINT (Ctrl+C)

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attach socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Define the server address
    address.sin_family = AF_INET;         // Address family (IPv4)
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
    address.sin_port = htons(PORT);       // Port number (converted to network byte order)

    // Bind the socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d\n", PORT);
    while (1)
    {

        // Accept an incoming connection
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Read data from the client
        int valread = read(client_fd, buffer, BUFFER_SIZE);
        printf("Received: %s\n", buffer);

        // Echo the received data back to the client
        send(client_fd, buffer, valread, 0);

        // Close the sockets
        
    }
    close(server_fd);

    return 0;
}
