#ifndef RSHPOST_H
#define RSHPOST_H

#include <QString>

class RshPost
{
public:
    RshPost();
    void setTitle(QString);
    void setContent(QString);
    void setAuthorAndDate(QString);
    QString getTitle();
    QString getContent();
    QString getAuthorAndDate();

private:
    QString title;
    QString content;
    QString authorAndDate;

};

#endif // RSHPOST_H
