#ifndef RSHPARSER_H
#define RSHPARSER_H

#include <QWebEnginePage>
#include <QEventLoop>
#include <QFile>
#include <QDebug>

class RshParser : public QObject
{
    Q_OBJECT
public:
    RshParser();
    // Contains a whole jQuery file to add jQuery to every page
    QString jQuery;

    // these functions get the content of one page on rollenspielhimmel (forum)
    int getPostsCount(QWebEnginePage*);
    QString getPostTitle(QWebEnginePage*, int);
    QString getPostAuthorAndDate(QWebEnginePage*, int);
    QString getPostContent(QWebEnginePage*, int);

    // to get the content of this website we need jQuery. So we add it manually to the website
    void loadJQuery(QWebEnginePage*);

signals:
    void runJavaScriptFinished();
public slots:
};

#endif // RSHPARSER_H
