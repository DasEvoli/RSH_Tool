#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QStandardItemModel>
#include "rshpost.h"

class FileManager
{
public:
    void static savePostsAsTextFile(QWidget*, QList<RshPost*>*);
};

#endif // FILEMANAGER_H
