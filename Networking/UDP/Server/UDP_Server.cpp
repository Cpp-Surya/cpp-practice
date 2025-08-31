/*
UDP: User Datagram Protocol is a connection-less protocol that allows for the transmission of data without establishing a connection between the sender and receiver. This means that data can be sent quickly and efficiently, but there is no guarantee that it will arrive at its destination or that it will arrive in the correct order.
Key Features of UDP:
1. Connectionless: No need to establish a connection before sending data.
2. Unreliable: No guarantee of delivery, order, or error checking.
3. Lightweight: Minimal protocol overhead, making it faster for certain applications.
4. Suitable for real-time applications: Ideal for streaming audio/video where speed is crucial.
Key Socket Functions:
1. socket(): Create a UDP socket.
2. bind(): Bind the socket to a specific IP address and port.
3. sendto(): Send data to a specific address.
4. recvfrom(): Receive data from a specific address.
*/

#include<iostream>
#include<cstring>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>

int main(){
    //Create socket
    int server_socket = socket(AF_INET,SOCK_DGRAM,0);
    if(server_socket<0){
        std::cerr<<"Socket creation failed"<<std::endl;
        return -1;
    }

    //Bind server to socket
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(9291);
    int bind_status = bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(bind_status<0){
        std::cerr<<"Bind failed"<<std::endl;
        close(server_socket);
        return -1;
    }

    std::cout<<"UDP listening on port 9291..."<<std::endl;

    //Receive data and get client address
    char buffer[1024] = {0};
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    recvfrom(server_socket,buffer,1024,0,(struct sockaddr*)&client_addr,&client_addr_len);
    std::cout<<"client says: "<<buffer<<std::endl;

    //Send a reply back to the client
    const char* message = "Hello from UDP server!";
    sendto(server_socket,message,strlen(message),0,(struct sockaddr*)&client_addr,client_addr_len);

    //Close socket
    close(server_socket);

    return 0;
}