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
- conncet(): Connect to server's ip address and port
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

struct ComplexData{
    int x;
    float y;
    bool z;
    ComplexData(const int& i,const float& j,const bool& k):x(i),y(j),z(k){}
};

int main(){
    // create a socket
    int server_socket = socket(AF_INET,SOCK_STREAM,0);
    if(server_socket<0){
        std::cerr<<"socket creation failed"<<std::endl;
        return -1;
    }

    // bind socket to an IP and port
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; //use any available network interface
    server_addr.sin_port = htons(9191);
    //inet_pton(AF_INET, "192.168.64.100",&server_addr.sin_addr);

    int bind_status = bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(bind_status < 0){
        std::cerr<<"bind failed"<<std::endl;
        close(server_socket);
        return -1;
    }

    // listen for incoming connections
    int listen_status = listen(server_socket, 3);
    if(listen_status < 0){
        std::cerr<<"listen failed"<<std::endl;
        close(server_socket);
        return -1;
    }

    std::cout<<"Server listening on port 9191..."<<std::endl;

    // Accept a client connection
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_socket = accept(server_socket,(struct sockaddr*)&client_addr,&client_addr_len);
    if(client_socket < 0){
        std::cerr<<"accept failed"<<std::endl;
        return -1;
    }

    std::cout<<"Client connected: "<<inet_ntoa(client_addr.sin_addr)<<std::endl;

    // Receive and send data
    char buffer[1024] = {0};
    recv(client_socket,buffer,1024,0);
    std::cout<<"Client says: "<<buffer<<std::endl;
    const char* message = "Hello from server!";
    send(client_socket,message,strlen(message),0);

    //Sending and receiving standard datatypes
    int receive_value{0};
    recv(client_socket,&receive_value,sizeof(int),0);
    std::cout<<"Server Received: "<<receive_value<<std::endl;
    float sent_value{99.65};
    send(client_socket,&sent_value,sizeof(float),0);
    
    //Sending and receiving User defined datatypes
    ComplexData d1{0,0,false};
    recv(client_socket,&d1,sizeof(ComplexData),0);
    std::cout<<"Server Received: x-> "<<d1.x<<", y-> "<<d1.y<<", z-> "<<d1.z<<std::endl;
    ComplexData d2{123,87.7,true};
    send(client_socket,&d2,sizeof(ComplexData),0);

    // Close the sockets
    close(client_socket);
    close(server_socket);

    return 0;
}