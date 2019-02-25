#include "filemanager.h"

void FileManager::savePostsAsTextFile(QWidget *context, QList<RshPost*>* postCollection){

    QString fileName = QFileDialog::getSaveFileName(context, "Speicher deine Posts", QDir::currentPath(), "text file(*.txt)");

    if(fileName.isEmpty()){
        QMessageBox::information(context, "Error", "Dateiname ist leer");
        return;
    }
    else{
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly)){
            QMessageBox::information(context, "Error", "Die Datei konnte nicht gespeichert werden");
            return;
        }
        QTextStream out(&file);
        for(int i = 0; i < postCollection->size(); i++){
           //QString buffer = postCollection->at(i)->getTitle() + '\n';
           //buffer.append(postCollection->at(i)->getAuthorAndDate() + '\n');
           //buffer.append(postCollection->at(i)->getContent());
           out << postCollection->at(i)->getTitle() << "\r\n";
           out << postCollection->at(i)->getAuthorAndDate() << "\r\n";
           out << postCollection->at(i)->getContent() << "\r\n";
           out << "\r\n";
        }
    }
}
