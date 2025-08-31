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
#include<arpa/inet.h>
#include<unistd.h>

int main(){
    //create socket
    int sock = socket(AF_INET,SOCK_DGRAM,0);
    if(sock<0){
        std::cerr<<"socket creation failed"<<std::endl;
        return -1;
    }

    //define server address
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9291);
    inet_pton(AF_INET,"192.168.64.100",&server_addr.sin_addr);

    //Send data
    const char* message = "Hello from UDP client!";
    sendto(sock,message,strlen(message),0,(struct sockaddr*)&server_addr,sizeof(server_addr));

    //Receive data
    char buffer[1024] = {0};
    socklen_t server_addr_len = sizeof(server_addr);
    recvfrom(sock,buffer,1024,0,(struct sockaddr*)&server_addr,&server_addr_len);
    std::cout<<"Server replied: "<<buffer<<std::endl;

    //Close socket
    close(sock);
    return 0;
}