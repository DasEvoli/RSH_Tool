#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QEventLoop>
#include <QTimer>

class LoginController : public QObject
{
    Q_OBJECT
public:
    explicit LoginController(QWebEnginePage*,QObject *parent = nullptr);

    QString getLoginUsername() const;
    QString getLoginPassword() const;
    QWebEnginePage* page;

    void setLoginUsername(const QString &value);
    void setLoginPassword(const QString &value);

    // Logs in to rollenspielhimmel.de by sending a post request with javascript
    bool loginToRsh();

private:
    QString loginUsername;
    QString loginPassword;

signals:
    void loginFinished();

public slots:
};

#endif // LOGINCONTROLLER_H
