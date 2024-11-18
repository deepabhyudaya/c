#include <stdio.h>  // For input/output functions like printf()
#include <string.h> // For string manipulation functions like memset(), strlen()
#include <stdlib.h> // For standard library functions like exit()

#ifdef _WIN32                      // Include Windows-specific headers
#include <winsock2.h>              // Core Winsock functions
#include <ws2tcpip.h>              // For InetPton() and InetNtop()
#pragma comment(lib, "ws2_32.lib") // Link the Winsock library automatically
#else
#include <unistd.h>    // For close() and read() on UNIX systems
#include <arpa/inet.h> // For inet_pton() and inet_ntoa() on UNIX systems
#endif

#define PORT 8080        // The port number the server will listen on
#define BUFFER_SIZE 1024 // Size of the buffer for reading client requests

int main()
{
    // Windows-specific Winsock initialization
#ifdef _WIN32
    WSADATA wsaData; // Structure to store Winsock data
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        // If WSAStartup fails, print an error and exit
        perror("WSAStartup failed");
        exit(EXIT_FAILURE);
    }
#endif

    int server_fd;                  // File descriptor for the server socket
    int new_socket;                 // File descriptor for an accepted client connection
    struct sockaddr_in address;     // Structure to hold server's address information
    int addrlen = sizeof(address);  // Size of the address structure
    char buffer[BUFFER_SIZE] = {0}; // Buffer to store data from the client (initialized to 0)

    // 1. Create a socket
    // The socket() function creates an endpoint for communication.
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        // If socket() returns INVALID_SOCKET, it failed to create the socket.
        perror("Socket creation failed");
#ifdef _WIN32
        WSACleanup(); // Clean up Winsock resources on failure
#endif
        exit(EXIT_FAILURE);
    }

    // 2. Define server address
    // The sockaddr_in structure holds information about the address of the server.
    address.sin_family = AF_INET;         // Set address family to IPv4
    address.sin_addr.s_addr = INADDR_ANY; // Bind to any available network interface (0.0.0.0)
    address.sin_port = htons(PORT);       // Convert port number to network byte order

    // 3. Bind the socket to the address and port
    // The bind() function assigns the address and port to the server socket.
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) == SOCKET_ERROR)
    {
        // If bind() returns SOCKET_ERROR, it means the binding failed.
        perror("Bind failed");
#ifdef _WIN32
        closesocket(server_fd); // Close the socket on failure
        WSACleanup();           // Clean up Winsock resources
#else
        close(server_fd); // For UNIX-like systems
#endif
        exit(EXIT_FAILURE);
    }

    // 4. Start listening for incoming connections
    // The listen() function puts the server socket in passive mode, allowing it to accept connections.
    if (listen(server_fd, 3) < 0)
    {
        // If listen() returns a negative value, it means listening failed.
        perror("Listen failed");
#ifdef _WIN32
        closesocket(server_fd); // Close the socket on failure
        WSACleanup();           // Clean up Winsock resources
#else
        close(server_fd); // For UNIX-like systems
#endif
        exit(EXIT_FAILURE);
    }
    printf("Server is listening on port %d...\n", PORT); // Inform the user that the server is running

    while (1)
    { // Infinite loop to continuously accept client connections
        // 5. Accept a client connection
        // The accept() function waits for a connection request and creates a new socket for the client.
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) == INVALID_SOCKET)
        {
            // If accept() returns INVALID_SOCKET, it means the connection failed.
            perror("Accept failed");
#ifdef _WIN32
            closesocket(server_fd); // Close the server socket
            WSACleanup();           // Clean up Winsock resources
#else
            close(server_fd); // For UNIX-like systems
#endif
            exit(EXIT_FAILURE);
        }

        // 6. Read data sent by the client
        // The recv() function reads data from the client's socket into the buffer.
        recv(new_socket, buffer, BUFFER_SIZE, 0);
        printf("Received request:\n%s\n", buffer); // Print the client's request for debugging

        // 7. Prepare the HTTP response
        // This is a basic HTTP response with an HTML page.
        const char *response =
            "HTTP/1.1 200 OK\r\n"         // HTTP response status line
            "Content-Type: text/html\r\n" // HTTP header: content type is HTML
            "Connection: close\r\n\r\n"   // HTTP header: indicate the connection will close
            "<!DOCTYPE html>"             // Start of HTML document
            "<html>"
            "<head><title>Simple C Web Server</title></head>"        // Page title
            "<body><h1>Welcome to My Simple Web Server!</h1></body>" // Page content
            "</html>";

        // 8. Send the HTTP response to the client
        // The send() function writes data to the client's socket.
        send(new_socket, response, strlen(response), 0); // Send the HTTP response
        printf("Response sent\n");                       // Inform the user that the response was sent

        // 9. Close the client socket
        // After responding, the server closes the connection with the client.
#ifdef _WIN32
        closesocket(new_socket);
#else
        close(new_socket);
#endif
    }

    // 10. Close the server socket
    // This would only execute if the server exits the while loop, which it does not in this example.
#ifdef _WIN32
    closesocket(server_fd); // Close the server socket
    WSACleanup();           // Clean up Winsock resources
#else
    close(server_fd); // For UNIX-like systems
#endif

    return 0; // Exit the program successfully
}
