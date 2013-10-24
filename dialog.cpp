#include "dialog.h"
#include "ui_dialog.h"



#include <QtGui>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->ip_text->hide();
    ui->ip1->hide();
    ui->ip2->hide();
    ui->ip3->hide();
    ui->ip4->hide();
    ui->port_text->hide();
    ui->port->hide();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_loginBtn_clicked()
{
    int mode = ui->mode->currentIndex();

    int chessboradsize = ui->size->value();

    //QString string1 = ui->IPaddress->text();
    //QString string2 = ui->port->text();
    //int n1 = string1.toInt();
    //int n2 = string2.toInt();

    int ip1 = ui->ip1->value();
    int ip2 = ui->ip2->value();
    int ip3 = ui->ip3->value();
    int ip4 = ui->ip4->value();
    int port = ui->port->value();

    qDebug() << "SendVariable mode: " << mode << " size: " << chessboradsize << " IP: " << ip1 << "." << ip2 << "." << ip3 <<"." <<ip4 << " port: "<<port;

    accept();

//    if(mode == 3){
//        network.server(1234);
//    }else if(mode == 4){
//        network.client("localhost", 1234);
//    }

    emit sendVariable(mode, chessboradsize, ip1, ip2, ip3, ip4, port);


    //if(ui->usrLineEdit->text()==tr("group01")&&ui->pwdLineEdit->text()==tr("123")){
    //}else{
        //QMessageBox::warning(this,tr("Warning"),tr("user name or password error!"),QMessageBox::Yes);
    //}
}

void Dialog::on_exitBtn_clicked()
{
    exit(0);
}

void Dialog::on_mode_currentIndexChanged(int index)
{
    if(index == 4){
        ui->size_text->hide();
        ui->size->hide();
        ui->ip_text->show();
        ui->ip1->show();
        ui->ip2->show();
        ui->ip3->show();
        ui->ip4->show();
        ui->port_text->show();
        ui->port->show();
    }else if(index == 3){
        ui->size_text->show();
        ui->size->show();
        ui->ip_text->hide();
        ui->ip1->hide();
        ui->ip2->hide();
        ui->ip3->hide();
        ui->ip4->hide();
        ui->port_text->show();
        ui->port->show();
    }else{
        ui->size_text->show();
        ui->size->show();
        ui->ip_text->hide();
        ui->ip1->hide();
        ui->ip2->hide();
        ui->ip3->hide();
        ui->ip4->hide();
        ui->port_text->hide();
        ui->port->hide();
    }
}
