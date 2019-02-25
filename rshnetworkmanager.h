#ifndef RSHLOGINMANAGER_H
#define RSHLOGINMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkConfigurationManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QNetworkCookieJar>
#include <QDebug>
#include <QEventLoop>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QMessageBox>
//#include <QWebView>

class RshNetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit RshNetworkManager(QObject *parent = nullptr);


    QString getUsername();
    int getHttpStatus();
    void setUsername(QString);
    void setPassword(QString);
    void setLoggedIn(bool);
    bool loginToRsh();

    //void loadRshWebview(QUrl, QWebView*);

private:
    QNetworkAccessManager *NAM = new QNetworkAccessManager(this);
    QNetworkCookieJar* cookieJar = new QNetworkCookieJar();
    QNetworkReply *reply;
    QString username;
    QString password;
    bool loggedIn = false;



signals:
    void loginFinished();

public slots:
    void managerFinishedLogin(QNetworkReply*);
    void replyFinishedLogin();
    void redirectedUrlLogin(QUrl);
};

#endif // RSHLOGINMANAGER_H
