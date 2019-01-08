#include <QtWebView>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlProperty>
#include <QNetworkReply>
#include <QAuthenticator>
#include "qqwebwidget.h"

QQWebWidget::QQWebWidget(QWidget *parent):QQuickWidget(parent)
,m_qmlWebView(NULL)
{
  static bool initialized = false;

  if( !initialized )
  {
    initialized = true;
    QtWebView::initialize();
  }

  /* cannot work:
     QNetworkAccessManager* qnam = engine()->networkAccessManager();
     QObject::connect( qnam,
                    SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
                    this, SLOT(authenticationRequiredInt(QNetworkReply*,QAuthenticator*)) );
   */
  //setVisible(true); //prevent ASSERT in native mode
  setResizeMode( QQuickWidget::SizeRootObjectToView );
  setSource( QUrl::fromLocalFile( QLatin1String( ":/qqwebwidget.qml" ) ) );
  m_qmlWebView = rootObject();

  QObject::connect( m_qmlWebView, SIGNAL(pageLoaded(QString)),
                    this, SLOT(pageLoadedInt(const QString&)) );
  QObject::connect( m_qmlWebView, SIGNAL(jsResult(QString)),
                    this, SLOT(jsResultInt(const QString&)) );
}

QQWebWidget::~QQWebWidget()
{
}

void QQWebWidget::setURLStr( const QString& urlStr)
{
  QQmlProperty::write( m_qmlWebView, "url", urlStr );
}

void QQWebWidget::pageLoadedInt( const QString& urlStr)
{
  emit pageLoaded( urlStr );
}

void QQWebWidget::jsResultInt( const QString& result)
{
  emit jsResult( result );
}

void QQWebWidget::evalJS( const QString& js )
{
  QVariant returnedValue;
  QMetaObject::invokeMethod( m_qmlWebView, "evalJS",
                             Q_RETURN_ARG( QVariant, returnedValue ),
                             Q_ARG( QVariant, js ) );
}

void QQWebWidget::goForward()
{
  QMetaObject::invokeMethod( m_qmlWebView, "forward" );
}

void QQWebWidget::goBack()
{
  QMetaObject::invokeMethod( m_qmlWebView, "back" );
}

void QQWebWidget::authenticationRequiredInt(QNetworkReply* reply,QAuthenticator* auth)
{
  qDebug()<< "authenticationRequiredInt:"<< reply->url();
  emit authenticationRequired(reply,auth);
}
