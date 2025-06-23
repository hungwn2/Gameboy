#include "client.h"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

client::client(const std::string& server_address, int port): 
ip(server_ip), port(server_port), sockfd(-1){}

client::~client(){
    if (client_socket!=-1){
        close(client_socket);
    }
}

bool client::connectToServer(){
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd<0){
        perror("Socket creation fail");
        return false;
    }
    sockaddr_in server_addr{};
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(port);
    inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);
    if(connect(sockfd, (sockaddr*)&server_addr, sizeof(server_addr))<0){
        perr("Connection failed");
        return false;
    }
    std::cout<<"Connected to server \n";
    return true;
}

bool Client::sendMessage(const std::string& message){
    if (send(sockfd, message.c_str(), message.size(), 0)<0){
        perror("send failed");
        return false;
    }
    return true;
}

std::string client::receiveMessage(){
    char buffer[256];
    bzero(buffer, 256);
    ssize_t n=recv(sockfd, buffer, 255, 0);
    if (n<=0){
        return "Disconnected from server";
    }
    return std::string(buffer);
}

std::string client::hashPassword(const std::string& password){
    std::hash<std::string> hasher;
    size_t hash_value=hasher(password);
    std::ostringstream oss;
    oss<std::hex<<hash_value;
    return oss.str();
}

// void error(const char *msg){
//     perror(msg);
//     exit(0);
// }
// int main(){
//     int sockfd, portno, n;
//     struct sockaddr_in serv_addr;
//     struct hostent *server;
//     char buffer[256];
//     portno(atoi(C_PORTNO));
//     client_fd=socket(AF_INET, SOCK_STREAM, 0);
//     if (client_fd<0){
//         std::cerr << "Error opening socket" << std::endl;
//         return;
//     }
//     server-gethostbyname();
//     if (server == NULL){
//         std::cerr << "Error, no such host" << std::endl;
//         return;
//     }
//     bzero((char*)&serv_addr, sizeof(serv_addr));
//     serv_addr.sin_family = AF_INET;
//     bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr. server->h_length);
//     serv_addr.sin_port=htons(S_PORTNO);
//     if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
//         std::cerr << "Error connecting" << std::endl;
//         return;
//     }
//     bzero(buffer, 256);
//     fgets(buffer, 255, );
//     n=write(sockfd, buffer, strlen(buffer));
//     if (n<0) std::cerr<<"Error writing to socket"<<std::endl;
//     bzero(buffer, 256);
//     n=read(sockfd, buffer, 255);
//     if (n<0) std::cerr<<"Error reading from socket"<<std::endl;
//     printf("%s\n", buffer);
//     close(sockfd);
//     return 0;

// }