#include "rshpost.h"

RshPost::RshPost()
{

}

void RshPost::setTitle(QString value)
{
    this->title = value;
}

void RshPost::setContent(QString value)
{
    this->content = value;
}

void RshPost::setAuthorAndDate(QString value)
{
    this->authorAndDate = value;
}

QString RshPost::getTitle()
{
    return this->title;
}

QString RshPost::getContent()
{
    return this->content;
}

QString RshPost::getAuthorAndDate()
{
    return this->authorAndDate;
}
