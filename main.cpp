#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
  QApplication a( argc, argv );
  //remove the following comment and an assertion takes place
  //qputenv( "QT_WEBVIEW_PLUGIN", "native" );
  MainWindow w;
  w.show();
  return a.exec();
}
