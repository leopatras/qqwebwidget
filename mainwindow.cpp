#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qqwebwidget.h"
#include <QNetworkReply>
#include <QAuthenticator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
  m_ui->setupUi( this );

  m_web = new QQWebWidget();
  m_web->setURLStr( "https://www.google.com" );
  QObject::connect( m_web, SIGNAL(pageLoaded(const QString&)),
                    this, SLOT(pageLoaded(const QString&)) );
  QObject::connect( m_web, SIGNAL(jsResult(const QString&)),
                    this, SLOT(jsResult(const QString&)) );
  QObject::connect( m_ui->prev, SIGNAL(clicked()),
                    m_web, SLOT(goBack()) );
  QObject::connect( m_ui->next, SIGNAL(clicked()),
                    m_web, SLOT(goForward()) );
  QObject::connect( m_web,
                    SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
                    this, SLOT(authenticationRequired(QNetworkReply*,QAuthenticator*)) );
  m_ui->verticalLayout->addWidget( m_web );
  m_web->setFocus();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::pageLoaded(const QString& urlStr)
{
  qDebug() << "pageLoaded:" << urlStr;
  m_web->evalJS("a=3;");
}

void MainWindow::jsResult(const QString& result)
{
  qDebug() << "jsResult:" << result;
}

void MainWindow::authenticationRequired(QNetworkReply* reply,QAuthenticator* auth)
{
  qDebug() << "authenticationRequired:" << reply->url();
}
