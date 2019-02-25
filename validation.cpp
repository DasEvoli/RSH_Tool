#include "validation.h"

bool Validation::pageNumbers(int first, int last, QWidget *context){

    if(first > last){
        QMessageBox errorBox;
        errorBox.critical(context, "Error", "Erste Seitenzahl muss kleiner sein, als die letzte Seitenzahl");
        errorBox.setFixedSize(400, 200);
        return false;
    }
    else if(first == last){
        QMessageBox errorBox;
        errorBox.critical(context, "Error", "Erste Seitenzahl muss kleiner sein, als die letzte Seitenzahl. Wenn du nur eine Seite möchtest, aktiviere 'Nur eine Seite'");
        errorBox.setFixedSize(400, 200);
        return false;
    }
    return true;
}

bool Validation::rshUrl(QString url){

    QUrl qurl(url);
    return (qurl.isValid() && qurl.authority() == "rollenspielhimmel.de");
}
