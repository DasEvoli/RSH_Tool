#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QListWidget>
#include <QSpinBox>
#include <QCheckBox>
#include <QFileDialog>
#include <QDialog>
#include <QErrorMessage>
#include <QMovie>
#include <QMessageBox>
#include <QList>
#include <QProgressBar>
#include <QtAlgorithms>
#include "validation.h"
#include "filemanager.h"
#include "rshwebenginecontroller.h"
#include "rshpost.h"
#include "rshparser.h"
#include "logincontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    // ui objects
    Ui::MainWindow *ui;
    QLineEdit *inputUrlLineEdit;
    QSpinBox *firstPageSpinBox;
    QSpinBox *lastPageSpinBox;
    QCheckBox *onlyOnePageCheckBox;
    QPushButton *getPostsActionButton;
    QListView *postsListView;
    QAction *menubarDeleteAction;
    QAction *menubarCloseAction;
    QAction *menubarSaveAction;
    QAction *menubarLoginAction;
    QMovie *eeveeGif;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginActionButton;
    QLabel *loginStatusLabel;
    QProgressBar *postLoadProgressBar;

    // Posts get stored in this list
    // We could make a class for this collection to add some functions to it like delete, edit etc...
    QList<RshPost*> rshPostCollection;

    // To Display posts on screen
    QStandardItemModel *itemModel = new QStandardItemModel();
    QList<QStandardItem*> SIlist;

    // Variables we need
    QString basisUrl = "";
    int firstPage = 1;
    int lastPage = 2;

    // Other class instances
    // Holds the webengine and all cookies with it to stay logged in
    RshWebEngineController *rshWEController = new RshWebEngineController(this);
    // to login to rollenspielhimmel.de (webenginepage needs to be argument so it can set the responsed cookies)
    LoginController *loginController = new LoginController(rshWEController->rshWebEnginePage);

    // Private methods
    // prints all posts in the rshPostCollection to the SIlist and from that to the itemModel
    void printRshPostCollectionToScreen();

signals:
    void progressValueChanged(int);

private slots:
    void getPostsAction();
    void disableSpinBoxes(int);
    void setFirstPageValue(int);
    void setLastPageValue(int);
    void deletePostsAction();
    void closeAppAction();
    void savePostsAction();
    void loginAction();
};

#endif // MAINWINDOW_H
