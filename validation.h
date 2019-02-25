#ifndef VALIDATION_H
#define VALIDATION_H

#include <QMessageBox>
#include <QUrl>

class Validation
{
public:
    bool static pageNumbers(int, int, QWidget*);
    bool static rshUrl(QString url);
};

#endif // VALIDATION_H
