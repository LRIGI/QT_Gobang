#ifndef FUNCTION_H
#define FUNCTION_H

#include <QtGui>
#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QtDebug>

#include <vector>

//server

//server

using namespace std;

class Function{
public:
    Function();
    ~Function();

    void server(int port);
    void client(char addr[30], int port);

    void send(int x, int y);
    int * receive();

private:
    void intToString(int x, char string[30]);
    void stringToInt(char temp[30]);

    void usage();

    int coordinate[2];
    int server0;
    int server_client;
    int res;
    int listenPort;

    char * peerHost;
    int peerPort;

};

#endif
