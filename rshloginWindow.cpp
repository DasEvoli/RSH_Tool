#include "rshloginWindow.h"


RshLoginWindow::RshLoginWindow(RshNetworkManager* networkManager, QWidget* parent) : QWidget(parent), networkManager(networkManager)
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

    networkManager->setUsername(username);
    networkManager->setPassword(password);

    networkManager->loginToRsh();
}

void RshLoginWindow::setStatus(QString value){
    loginStatus->setText("Status: " + value); // Das geht hübscher
}
