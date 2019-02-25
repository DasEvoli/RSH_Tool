#include "logincontroller.h"

LoginController::LoginController(QWebEnginePage* webEnginePage, QObject *parent) : QObject(parent)
{
    page = webEnginePage;
}

QString LoginController::getLoginUsername() const
{
    return loginUsername;
}

void LoginController::setLoginUsername(const QString &value)
{
    loginUsername = value;
}

QString LoginController::getLoginPassword() const
{
    return loginPassword;
}

void LoginController::setLoginPassword(const QString &value)
{
    loginPassword = value;
}

bool LoginController::loginToRsh()
{
    page->runJavaScript("var http = new XMLHttpRequest();\
                                var url = 'https://rollenspielhimmel.de/login.do';\
                                var params = 'username=" + this->getLoginUsername() + "&password=" + this->getLoginPassword() + "';\
                                http.open('POST', url, true);\
                                http.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');\
                                http.send(params);",
                                [this](const QVariant &temp){
                                    QVariant voidTemp = temp;
                                    emit loginFinished();
    });
    QEventLoop loop;
    connect(this, SIGNAL(loginFinished()), &loop, SLOT(quit()));
    loop.exec();

    // If rsh redirects us to Login - Rollenspielhimmel then login was not successful
    page->load(QUrl("https://rollenspielhimmel.de/profile/Nora.html"));
    QEventLoop loopTwo;
    connect(page, SIGNAL(loadFinished(bool)), &loopTwo, SLOT(quit()));
    loopTwo.exec();
    return page->title() != "Login - Rollenspielhimmel";
}
