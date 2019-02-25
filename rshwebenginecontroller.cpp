#include "rshwebenginecontroller.h"

RshWebEngineController::RshWebEngineController(QObject *parent) : QObject(parent)
{

}

bool RshWebEngineController::loadRsh(QUrl url)
{
    rshWebEnginePage->load(url);
    QEventLoop loop;
    connect(rshWebEnginePage, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));
    loop.exec();
    // We get redirected to the login page if this forum is private
    if(rshWebEnginePage->title() == "Login - Rollenspielhimmel"){
        lastError = "Rollenspiel scheint privat zu sein. Du musst dich einloggen, um private Rollenspiele lesen zu können";
        return false;
    }
    return true;
}

QString RshWebEngineController::getLastError()
{
    return lastError;
}
