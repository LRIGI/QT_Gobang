#include "function.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <iostream>

using namespace std;

// A simple Internet server application.
// It listens to the port written in command line (default 1234),
// accepts a connection, and sends the "Hello!\r\n" message
// to a client. Then it receives the answer from a client and terminates.
//
// Usage:
//      server [port_to_listen]
// Default is the port 1234.
//



//void Function::judge(void){
//	qDebug() << "test!";
//}

//void Function::server(int x, int y){
 
//}

Function::Function(){

    listenPort = 1234;
    peerHost = "localhost";
    peerPort = 1234;

}

Function::~Function(){
    close(server_client);
}

void Function::intToString(int x, char string[30]){
    int i = 0;
    char temp[30];
    int length = 0;

    //get num one by one
    do{
        //cout << char(x%10 + '0') << endl;
        temp[i++] = char(x%10 + '0');
        x = x/10;
    }while(x != 0);
    temp[i] = '\0';

    //reverse
    length = strlen(temp);
    for(i = 0; i < length; i++){
        string[i] = temp[length-i-1];
    }
    string[i] = '\0';

    //cout << "x: " << x << " string: " << string << endl;
}

void Function::stringToInt(char temp[30]){
    int length = strlen(temp);
    bool flag = false;

    int x_index = 0;
    int y_index = 0;

    for(int i = 0; i < length; i++){
        if(temp[i] != ' ' && flag == false){
            //cout << temp[i] - '0' << endl;
            x_index = x_index*10 + temp[i]-'0';
            //cout << x_index << endl;
        }else if(temp[i] != ' ' && flag == true){
            y_index = y_index*10 + temp[i]-'0';
        }else{
            flag = true;
        }
    }

    coordinate[0] = x_index;
    coordinate[1] = y_index;
    //cout << x_index << " " << y_index << endl;
}

void Function::send(int x, int y){
    char x_temp[30];
    char y_temp[30];
    //char temp[30];
    intToString(x, x_temp);
    intToString(y, y_temp);
    strcat(x_temp, " ");
    strcat(x_temp, y_temp);
    write(server_client, x_temp, 100);

    cout << "Send: " << x_temp << endl;
}

int * Function::receive(){
    char buffer[1024];
    res = read(server_client, buffer, 1023);

    //cout << "Receive..." << endl;

    if (res < 0) {
        perror("Read error"); exit(1);
        //res = read(server_client, buffer, 1023);
    }
    buffer[res] = 0;

    stringToInt(buffer);

    return coordinate;
    //printf("Received %d bytes:\n%s\n", res, buffer);
}

void Function::server(int port){
    listenPort = port;

    // Create a socket
    server0 = socket(AF_INET, SOCK_STREAM, 0);
    if (server0 < 0) {
        perror("Cannot create a socket"); exit(1);
    }

    // Fill in the address structure containing self address
    struct sockaddr_in myaddr;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(listenPort);        // Port to listen
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind a socket to the address
    res = bind(server0, (struct sockaddr*) &myaddr, sizeof(myaddr));
    if (res < 0) {
        perror("Cannot bind a socket"); exit(1);
    }

    // Set the "LINGER" timeout to zero, to close the listen socket
    // immediately at program termination.
    struct linger linger_opt = { 1, 0 }; // Linger active, timeout 0
    setsockopt(server0, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));

    // Now, listen for a connection
    res = listen(server0, 1);    // "1" is the maximal length of the queue
    if (res < 0) {
        perror("Cannot listen"); exit(1);
    }

    // Accept a connection (the "accept" command waits for a connection with
    // no timeout limit...)
    cout << "Waiting for connection..." << endl;

    struct sockaddr_in peeraddr;
    socklen_t peeraddr_len = sizeof(peeraddr);
    server_client = accept(server0, (struct sockaddr*) &peeraddr, &peeraddr_len);
    if (server_client < 0) {
        perror("Cannot accept"); exit(1);
    }

    // A connection is accepted. The new socket "s1" is created
    // for data input/output. The peeraddr structure is filled in with
    // the address of connected entity, print it.
    printf(
        "Connection from IP %d.%d.%d.%d, port %d\n",
        (ntohl(peeraddr.sin_addr.s_addr) >> 24) & 0xff, // High byte of address
        (ntohl(peeraddr.sin_addr.s_addr) >> 16) & 0xff, // . . .
        (ntohl(peeraddr.sin_addr.s_addr) >> 8) & 0xff,  // . . .
        ntohl(peeraddr.sin_addr.s_addr) & 0xff,         // Low byte of addr
        ntohs(peeraddr.sin_port)
    );

    res = close(server0);    // Close the listen socket

    //send & receive
//    for(int i = 0; i < 10; i++){
//        send(server1, i*20, i*20+1);
//        receive(server1, res);
//    }
    //send(1,2);

    // Close the data socket
    //close(server1);
}



void Function::client(char addr[30], int port) {
    // Create a socket
    server_client = socket(AF_INET, SOCK_STREAM, 0);
    if (server_client < 0) {
        perror("Cannot create a socket"); exit(1);
    }

    // Fill in the address of server
    struct sockaddr_in peeraddr;
    memset(&peeraddr, 0, sizeof(peeraddr));

    //const char* peerHost = "localhost";

//    if (argc > 1)
    //peerHost = argv[1];
    peerHost = addr;


    // Resolve the server address (convert from symbolic name to IP number)
    struct hostent *host = gethostbyname(peerHost);
    if (host == NULL) {
        perror("Cannot define host address"); exit(1);
    }
    peeraddr.sin_family = AF_INET;

    peerPort = port;

    peeraddr.sin_port = htons(peerPort);

    // Print a resolved address of server (the first IP of the host)
    printf(
        "peer addr = %d.%d.%d.%d, port %d\n",
        host->h_addr_list[0][0] & 0xff,
        host->h_addr_list[0][1] & 0xff,
        host->h_addr_list[0][2] & 0xff,
        host->h_addr_list[0][3] & 0xff,
        (int) peerPort
    );

    // Write resolved IP address of a server to the address structure
    memmove(&(peeraddr.sin_addr.s_addr), host->h_addr_list[0], 4);

    // Connect to a remote server
    res = connect(server_client, (struct sockaddr*) &peeraddr, sizeof(peeraddr));
    if (res < 0) {
        perror("Cannot connect"); exit(1);
    }
    printf("Connected. Reading a server message.\n");


    //receive & send
//    for(int i = 0; i < 10; i++){
//        receive(client0, res);
//        send(client0, i*10, i*10+1);
//    }


    // Close the data socket
    //close(client0);

}


void Function::usage() {
    printf(
        "A simple Internet server application.\n"
        "It listens to the port written in command line (default 1234),\n"
        "accepts a connection, and sends the \"Hello!\" message to a client.\n"
        "Then it receives the answer from a client and terminates.\n\n"
        "Usage:\n"
        "     server [port_to_listen]\n"
        "Default is the port 1234.\n"
    );
}


