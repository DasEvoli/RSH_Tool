#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QWebView>
#include <QtWebKit>
#include <QtWebKitWidgets/QWebFrame>
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
#include "rshpost.h"
#include "rshparser.h"
#include "rshnetworkmanager.h"


// TODO: Änder alles in die collection. Löschen, speichern usw.

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
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
    QList<RshPost*> rshPostCollection;

    // To Display posts on screen
    QStandardItemModel *itemModel = new QStandardItemModel();
    QList<QStandardItem*> SIlist;

    // Variables we need
    QString basisUrl = "";
    int firstPage = 1;
    int lastPage = 2;

    // Other class instances
    RshNetworkManager *rshNetworkManager = new RshNetworkManager(this);

    // Private methods
    void printRshPostCollectionToScreen();
    bool checkUrl(QString);

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
