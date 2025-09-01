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
    
    // inet_pton(AF_INET, "192.168.64.100",&server_addr.sin_addr);//server ip
    inet_pton(AF_INET, "127.0.0.1",&server_addr.sin_addr);//server ip

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

    //sending and receiving standard datatypes
    int send_value = 976;
    void* data = &send_value;
    send(client_socket,data,sizeof(int),0);
    float receive_value{0};
    recv(client_socket,&receive_value,sizeof(float),0);
    std::cout<<"Client Received: "<<receive_value<<std::endl;

    //Sending and receving user defined datatypes
    ComplexData d1{981,54.267,true};
    void* data1 = &d1;
    send(client_socket,data1,sizeof(ComplexData),0);
    ComplexData d2{0,0,false};
    recv(client_socket,&d2,sizeof(ComplexData),0);
    std::cout<<"Client Received: x-> "<<d2.x<<", y-> "<<d2.y<<", z-> "<<d2.z<<std::endl;
    // close socket
    close(client_socket);

    return 0;
}