#ifndef RSHWEBENGINECONTROLLER_H
#define RSHWEBENGINECONTROLLER_H

#include <QObject>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QEventLoop>
#include <QWebEngineSettings>

class RshWebEngineController : public QObject
{
    Q_OBJECT
public:
    explicit RshWebEngineController(QObject *parent = nullptr);
    QWebEnginePage* rshWebEnginePage = new QWebEnginePage();

    // To load a page from rollenspielhimmel.de
    bool loadRsh(QUrl);
    QString lastError = "";
    QString getLastError();

signals:


public slots:

};

#endif // RSHWEBENGINECONTROLLER_H
