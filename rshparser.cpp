#include "rshparser.h"

RshParser::RshParser()
{
    // Prepare jQuery
    QFile file;
    file.setFileName(":/resources/jquery-3.3.1.slim.js");
    file.open(QIODevice::ReadOnly);
    jQuery = file.readAll();
    jQuery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    file.close();
}

void RshParser::loadJQuery(QWebEnginePage* page){

    page->runJavaScript(jQuery, [this](QVariant tmp){
        QVariant voidTmp = tmp; // I don't know what to do with it.
        emit runJavaScriptFinished();
    });
    QEventLoop loop;
    connect(this, SIGNAL(runJavaScriptFinished()), &loop, SLOT(quit()));
    loop.exec();
}

int RshParser::getPostsCount(QWebEnginePage* page){

    int size = 0;
    page->runJavaScript("document.getElementsByClassName(\"forum_postbody_content\").length", [this,&size](const QVariant &count) mutable {
        size = count.toInt();
        emit runJavaScriptFinished();
    });
    QEventLoop loop;
    connect(this, SIGNAL(runJavaScriptFinished()), &loop, SLOT(quit()));
    loop.exec();
    return size;
}

QString RshParser::getPostTitle(QWebEnginePage* page, int index)
{
    QString titleValue;
    page->runJavaScript("qt.jQuery(\".forum_postbody_content:eq(" + QString::number(index) + ")\").find(\"H2\").text()", [this, &titleValue](const QVariant &value) mutable {
        titleValue = value.toString().simplified();
        emit runJavaScriptFinished();
    });
    QEventLoop loop;
    connect(this, SIGNAL(runJavaScriptFinished()), &loop, SLOT(quit()));
    loop.exec();
    return titleValue;
}

QString RshParser::getPostAuthorAndDate(QWebEnginePage* page, int index)
{
    QString authorValue;
    page->runJavaScript("qt.jQuery(\".forum_postbody_content:eq(" + QString::number(index) + ")\").find(\".forum_postbody_small\").text()", [this, &authorValue](const QVariant &value) mutable {
        authorValue = value.toString().simplified();
        emit runJavaScriptFinished();
    });
    QEventLoop loop;
    connect(this, SIGNAL(runJavaScriptFinished()), &loop, SLOT(quit()));
    loop.exec();
    return authorValue;
}

QString RshParser::getPostContent(QWebEnginePage* page, int index)
{
    QString contentValue;

    // FOR ALL P TAGS
    page->runJavaScript("qt.jQuery(\".forum_postbody_content:eq(" + QString::number(index) + ")\").find(\"p\").text()", [this, &contentValue](const QVariant &value) mutable {
        contentValue = value.toString().simplified();
        emit runJavaScriptFinished();
    });
    QEventLoop loopP;
    connect(this, SIGNAL(runJavaScriptFinished()), &loopP, SLOT(quit()));
    loopP.exec();

    // FOR ALL DIV CONTAINERS
    page->runJavaScript("qt.jQuery(\".forum_postbody_content:eq(" + QString::number(index) + ")\").find(\"div\").text()", [this, &contentValue](const QVariant &value) mutable {
        contentValue += value.toString().simplified();
        emit runJavaScriptFinished();
    });
    QEventLoop loopDiv;
    connect(this, SIGNAL(runJavaScriptFinished()), &loopDiv, SLOT(quit()));
    loopDiv.exec();

    // FOR ALL CENTER TAGS (yea this site generates a center outsite of a p tag)
    page->runJavaScript("qt.jQuery(\".forum_postbody_content:eq(" + QString::number(index) + ")\").find(\"center\").text()", [this, &contentValue](const QVariant &value) mutable {
        contentValue += value.toString().simplified();
        emit runJavaScriptFinished();
    });
    QEventLoop loopCenter;
    connect(this, SIGNAL(runJavaScriptFinished()), &loopCenter, SLOT(quit()));
    loopCenter.exec();

    return contentValue;
}
