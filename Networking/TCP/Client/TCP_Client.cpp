/*
TCP: Transmission Control Protocol is a connection-oriented protocol that guarantees:
- Reliable data transfer - No data loss
- Ordered data transfer - Data arrives in sequence
- Error checking - Built-in error detection and correction
- Flow control - Manages data flow to prevent congestion
Key Socket Functions:
- socket(): Create a new socket endpoint
- bind(): Associate the socket with a specific IP address and port
- listen(): Set the socket to listen for incoming connections
- accept(): Accept an incoming connection request
- recv(): Receive data from a connected socket
- send(): Send data to a connected socket
- close(): Close the socket connection
*/

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(){
    // create socket
    int client_socket = socket(AF_INET,SOCK_STREAM,0);
    if(client_socket<0){
        std::cerr<<"socket creation failed"<<std::endl;
        return -1;
    }

    // connect to server
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9191);
    
    inet_pton(AF_INET, "192.168.64.100",&server_addr.sin_addr);//server ip

    int connection_status = connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(connection_status < 0){
        std::cerr<<"Connection failed"<<std::endl;
        return -1;
    }
    std::cout<<"Connected to server: "<<inet_ntoa(server_addr.sin_addr)<<std::endl;

    const char* message = "Hello from client!";
    send(client_socket,message,strlen(message),0);
    char buffer[1024] = {0};
    recv(client_socket,buffer,1024,0);
    std::cout<<"Server replied: "<<buffer<<std::endl;

    // close socket
    close(client_socket);

    return 0;
}