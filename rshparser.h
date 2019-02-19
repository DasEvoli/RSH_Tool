#ifndef RSHPARSER_H
#define RSHPARSER_H

#include <QWebView>
#include <QWebElementCollection>
#include <QWebPage>
#include <QWebFrame>
#include <QEventLoop>
#include <QWebElement>
#include <QDebug>
#include "rshpost.h"


class RshParser : public QObject
{
    Q_OBJECT
public:
    RshParser();
    void static postsfromWebViewToCollection(QWebView*, QList<RshPost*>*);

signals:
};

#endif // RSHPARSER_H
