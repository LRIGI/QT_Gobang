#include "interface.h"
#include "dialog.h"

#include <QtGui>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);


  Dialog login;
  Interface window;
  QObject::connect(&login, SIGNAL(sendVariable(int, int, int, int, int, int, int)), &window, SLOT(getVariable(int, int, int, int, int, int, int)));

  ///--------------

////-----

  if(login.exec() == QDialog::Accepted){
      window.show();
      return app.exec();
  }else{
      return 0;
  }
}
