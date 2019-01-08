#ifndef __QQWEBVIEW_H
#define __QQWEBVIEW_H
#include <QQuickWidget>
#include <QString>
class QAuthenticator;
class QNetworkReply;
class QQWebWidget : public QQuickWidget
{
  Q_OBJECT

public:

  QQWebWidget( QWidget * parent = 0 );
  ~QQWebWidget();
  void evalJS( const QString &js ); //signals async jsResult
  void setURLStr( const QString &url );

signals:

  void pageLoaded( const QString &pageLoaded );
  void jsResult( const QString &result );
  void authenticationRequired(QNetworkReply* reply,QAuthenticator* auth);

public slots:
  void goForward();
  void goBack();

private slots:

  void pageLoadedInt( const QString &pageLoaded );
  void jsResultInt( const QString &result );
  void authenticationRequiredInt(QNetworkReply* reply,QAuthenticator* auth);

private:

  QObject* m_qmlWebView;
};
#endif
