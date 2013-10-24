/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created: Tue Apr 9 19:22:47 2013
**      by: Qt User Interface Compiler version 4.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *loginBtn;
    QLabel *ip_text;
    QLabel *port_text;
    QPushButton *exitBtn;
    QLabel *label_4;
    QComboBox *mode;
    QLabel *size_text;
    QSpinBox *size;
    QHBoxLayout *horizontalLayout;
    QSpinBox *ip1;
    QSpinBox *ip2;
    QSpinBox *ip3;
    QSpinBox *ip4;
    QSpinBox *port;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(416, 282);
        gridLayoutWidget = new QWidget(Dialog);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 60, 361, 191));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        loginBtn = new QPushButton(gridLayoutWidget);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));

        gridLayout->addWidget(loginBtn, 6, 1, 1, 1);

        ip_text = new QLabel(gridLayoutWidget);
        ip_text->setObjectName(QString::fromUtf8("ip_text"));

        gridLayout->addWidget(ip_text, 2, 1, 1, 1);

        port_text = new QLabel(gridLayoutWidget);
        port_text->setObjectName(QString::fromUtf8("port_text"));

        gridLayout->addWidget(port_text, 3, 1, 1, 1);

        exitBtn = new QPushButton(gridLayoutWidget);
        exitBtn->setObjectName(QString::fromUtf8("exitBtn"));

        gridLayout->addWidget(exitBtn, 6, 2, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 1, 1, 1);

        mode = new QComboBox(gridLayoutWidget);
        mode->setObjectName(QString::fromUtf8("mode"));

        gridLayout->addWidget(mode, 0, 2, 1, 1);

        size_text = new QLabel(gridLayoutWidget);
        size_text->setObjectName(QString::fromUtf8("size_text"));

        gridLayout->addWidget(size_text, 1, 1, 1, 1);

        size = new QSpinBox(gridLayoutWidget);
        size->setObjectName(QString::fromUtf8("size"));
        size->setMinimum(10);
        size->setMaximum(20);
        size->setValue(15);

        gridLayout->addWidget(size, 1, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        ip1 = new QSpinBox(gridLayoutWidget);
        ip1->setObjectName(QString::fromUtf8("ip1"));
        ip1->setReadOnly(false);
        ip1->setMinimum(0);
        ip1->setMaximum(255);
        ip1->setValue(127);

        horizontalLayout->addWidget(ip1);

        ip2 = new QSpinBox(gridLayoutWidget);
        ip2->setObjectName(QString::fromUtf8("ip2"));
        ip2->setMinimum(0);
        ip2->setMaximum(255);
        ip2->setValue(0);

        horizontalLayout->addWidget(ip2);

        ip3 = new QSpinBox(gridLayoutWidget);
        ip3->setObjectName(QString::fromUtf8("ip3"));
        ip3->setMinimum(0);
        ip3->setMaximum(255);
        ip3->setValue(0);

        horizontalLayout->addWidget(ip3);

        ip4 = new QSpinBox(gridLayoutWidget);
        ip4->setObjectName(QString::fromUtf8("ip4"));
        ip4->setMinimum(0);
        ip4->setMaximum(255);
        ip4->setValue(1);

        horizontalLayout->addWidget(ip4);


        gridLayout->addLayout(horizontalLayout, 2, 2, 1, 1);

        port = new QSpinBox(gridLayoutWidget);
        port->setObjectName(QString::fromUtf8("port"));
        port->setMinimum(0);
        port->setMaximum(65535);
        port->setValue(1234);

        gridLayout->addWidget(port, 3, 2, 1, 1);

        horizontalLayoutWidget_2 = new QWidget(Dialog);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(30, 10, 361, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QFont font;
        font.setPointSize(15);
        label_5->setFont(font);

        horizontalLayout_2->addWidget(label_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", 0, QApplication::UnicodeUTF8));
        loginBtn->setText(QApplication::translate("Dialog", "Login", 0, QApplication::UnicodeUTF8));
        ip_text->setText(QApplication::translate("Dialog", "IP address:", 0, QApplication::UnicodeUTF8));
        port_text->setText(QApplication::translate("Dialog", "Port:", 0, QApplication::UnicodeUTF8));
        exitBtn->setText(QApplication::translate("Dialog", "Exit", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Dialog", "Mode:", 0, QApplication::UnicodeUTF8));
        mode->clear();
        mode->insertItems(0, QStringList()
         << QApplication::translate("Dialog", "Local Battle", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "VS Battle - Greedy Algorithm", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "VS Battle - Game Tree Algorithm", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "Online Battle - Server", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "Online Battle - Client", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Dialog", "VS Demo - Greedy : Game Tree", 0, QApplication::UnicodeUTF8)
        );
        size_text->setText(QApplication::translate("Dialog", "Size(10-20):", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Dialog", "Gobang Game", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
