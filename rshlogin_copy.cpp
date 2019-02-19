#include "rshloginWindow.h"


RshLoginWindow::RshLoginWindow(QWidget* parent) : QWidget(parent)
{
    this->setWindowTitle("Einloggen bei Rollenspielhimmel");
    this->setMinimumSize(400,100);

    // MainLayout
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    // Layout for input and button
    QHBoxLayout *hBoxLayout = new QHBoxLayout();
    hBoxLayout->setMargin(5);
    layout->addLayout(hBoxLayout);

    // Input
    usernameLineEdit = new QLineEdit();
    usernameLineEdit->setPlaceholderText("Username");
    hBoxLayout->addWidget(usernameLineEdit);
    passwordLineEdit = new QLineEdit();
    passwordLineEdit->setPlaceholderText("Password");
    hBoxLayout->addWidget(passwordLineEdit);

    // Button for login
    QPushButton *loginButton = new QPushButton("Einloggen");
    hBoxLayout->addWidget(loginButton);

    // Spacer to have login layout top and status bottom
    QSpacerItem *spacer = new QSpacerItem(0,50, QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    layout->addSpacerItem(spacer);

    // Status for login
    loginStatus = new QLabel("Status: ");
    loginStatus ->setMargin(5);
    layout->addWidget(loginStatus);

    // CONNECTS
    connect(loginButton, SIGNAL(clicked(bool)), this, SLOT(loginAction()));

}

void RshLoginWindow::setUserName(QString value)
{
    this->username = value;
}

void RshLoginWindow::setPassword(QString value)
{
    this->password = value;
}

void RshLoginWindow::loginAction(){
    this->setUserName(RshLoginWindow::usernameLineEdit->text());
    this->setPassword(RshLoginWindow::passwordLineEdit->text());


    QNetworkRequest request(QUrl("https://rollenspielhimmel.de/login.do"));
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    QUrlQuery params;
    params.addQueryItem("username", "nora");
    params.addQueryItem("password", "Zeichnerin.22");

    manager->setCookieJar(cookieJar);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(managerFinished(QNetworkReply*)));
    reply = manager->post(request, params.toString(QUrl::FullyEncoded).toUtf8());
    connect(reply, SIGNAL(redirected(QUrl)), this, SLOT(redirectedUrl(QUrl)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(replyError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(finished()), this, SLOT(replyFinished()));

}

void RshLoginWindow::managerFinished(QNetworkReply* replyFromManager){
     qDebug() << replyFromManager->errorString();
}

void RshLoginWindow::replyError(QNetworkReply::NetworkError error){
    qDebug() << "Error: " << error;
}

void RshLoginWindow::replyFinished(){
    qDebug() << "Starts reading";
    qDebug() << reply->readAll();
    qDebug() << reply->errorString();
    qDebug() << reply->size();

    QByteArray bytes = reply->readAll();
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statuscode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Statuscode: " << statuscode;
}

void RshLoginWindow::redirectedUrl(QUrl newUrl){
    qDebug() << "Redirected";
    qDebug() << newUrl.toString();

    reply = manager->get(QNetworkRequest(QUrl("https://rollenspielhimmel.de/profile/Nora.html?from=myaccount")));
    QEventLoop event;
    connect(reply,SIGNAL(finished()),&event,SLOT(quit()));
    event.exec();
    QString html = reply->readAll();
    qDebug() << html;


}
