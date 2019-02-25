#include "rshnetworkmanager.h"

RshNetworkManager::RshNetworkManager(QObject *parent) : QObject(parent)
{
    NAM->setCookieJar(cookieJar);
}

void RshNetworkManager::setUsername(QString value)
{
    this->username = value;
}

void RshNetworkManager::setPassword(QString value)
{
    this->password = value;
}

bool RshNetworkManager::loginToRsh()
{
    QNetworkRequest request(QUrl("https://rollenspielhimmel.de/login.do"));
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery loginParams;
    loginParams.addQueryItem("username", this->username);
    loginParams.addQueryItem("password", this->password);

    QEventLoop loop;
    connect(this, SIGNAL(loginFinished()), &loop, SLOT(quit()));
    reply = NAM->post(request, loginParams.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(redirected(QUrl)), this, SLOT(redirectedUrlLogin(QUrl)));
    connect(reply, SIGNAL(finished()), this, SLOT(replyFinishedLogin()));
    loop.exec();
    return loggedIn;
}
/*
void RshNetworkManager::loadRshWebview(QUrl url, QWebView* webView)
{
    webView->page()->setNetworkAccessManager(this->NAM); // TODO maybe we should call that when we create the webview

    QEventLoop loop;
    webView->load(url);
    connect(webView, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));
    loop.exec();
}
*/
void RshNetworkManager::managerFinishedLogin(QNetworkReply* replyFromManager){
     qDebug() << "managerFinishedLogin() got called";
     // TODO: add functionality to it
}

void RshNetworkManager::replyFinishedLogin(){
    qDebug() << "replayFinishedLogin() got called";

    // If we don't get redirected then it means login was not successfull
    this->setLoggedIn(false);
    emit loginFinished();
}

void RshNetworkManager::redirectedUrlLogin(QUrl newUrl){
    // We got redirected, that means login was successfull (still check if url is right)
    qDebug() << "Redirected to " << newUrl.toDisplayString();
    if(newUrl.toDisplayString() == "https://rollenspielhimmel.de/home.html"){
        this->setLoggedIn(true);
    }
    else this->setLoggedIn(false);
    emit loginFinished();
}

void RshNetworkManager::setLoggedIn(bool value){
    this->loggedIn = value;
}

QString RshNetworkManager::getUsername(){
    return this->username;
}

int RshNetworkManager::getHttpStatus()
{
    return this->reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}
