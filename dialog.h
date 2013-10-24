#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtDebug>

#include "function.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    
private slots:
    void on_loginBtn_clicked();
    void on_exitBtn_clicked();

    void on_mode_currentIndexChanged(int index);

private:
    Ui::Dialog *ui;
    //Interface interface; //make a new example!
    //Function network;

signals:
    void sendVariable(int,int,int,int,int,int,int);
};

#endif // DIALOG_H
