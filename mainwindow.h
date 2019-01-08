#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_FORWARD_DECLARE_CLASS(QQWebWidget)
QT_FORWARD_DECLARE_CLASS(QAuthenticator)
QT_FORWARD_DECLARE_CLASS(QNetworkReply)

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:

  explicit MainWindow( QWidget* parent = 0 );
  ~MainWindow();

private slots:

  void pageLoaded( const QString &urlStr );
  void jsResult( const QString &result );
  void authenticationRequired( QNetworkReply* reply, QAuthenticator* auth );

private:

  Ui::MainWindow* m_ui;
  QQWebWidget* m_web;
};

#endif // MAINWINDOW_H
