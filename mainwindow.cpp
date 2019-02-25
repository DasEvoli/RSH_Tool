#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Actions in menubar
    menubarDeleteAction = ui->menubarDeleteAction;
    connect(menubarDeleteAction, SIGNAL(triggered(bool)), this, SLOT(deletePostsAction()));
    menubarCloseAction = ui->menubarCloseAction;
    connect(menubarCloseAction, SIGNAL(triggered(bool)), this, SLOT(closeAppAction()));
    menubarSaveAction = ui->menubarSaveAction;
    connect(menubarSaveAction, SIGNAL(triggered(bool)), this, SLOT(savePostsAction()));

    //Spinboxes for pages
    firstPageSpinBox = ui->firstPageSpinBox;
    connect(firstPageSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setFirstPageValue(int)));
    lastPageSpinBox = ui->lastPageSpinBox;
    connect(lastPageSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setLastPageValue(int)));

    //Button for getting posts
    getPostsActionButton = ui->getPostsActionButton;
    connect(getPostsActionButton, SIGNAL(released()), this, SLOT(getPostsAction()));

    //Gif (Eevee)
    eeveeGif = new QMovie(":/resources/resources/eevee.gif");
    ui->eeveeMovie->setMovie(eeveeGif);
    QSize size;
    size.scale(180,180, Qt::KeepAspectRatioByExpanding);
    eeveeGif->setScaledSize(size);
    eeveeGif->start();

    // List to display all posts and the belonging item model
    postsListView = ui->postsListView;
    postsListView->setModel(itemModel);

        // StyleSheet for this List
        this->setStyleSheet("QListView::item {"
                        "padding: 10 0 10 0;"
                        "border-bottom: 1px solid rgb(40,40,40);"
                        "}");

    // Checkbox to only load one page
    onlyOnePageCheckBox = ui->onlyOnePageCheckBox;
    connect(onlyOnePageCheckBox,SIGNAL(stateChanged(int)), this, SLOT(disableSpinBoxes(int)));

    // Login widgets
    usernameLineEdit = ui->usernameLineEdit;
    passwordLineEdit = ui->passwordLineEdit;
    loginActionButton = ui->loginActionButton;
    usernameLineEdit->setPlaceholderText("Nutzername");
    passwordLineEdit->setPlaceholderText("Passwort");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    connect(loginActionButton, SIGNAL(clicked(bool)), this, SLOT(loginAction()));
    loginStatusLabel = ui->loginStatusLabel;
    loginStatusLabel->setText("Nicht eingeloggt");

    // Progressbar when loading posts
    postLoadProgressBar = ui->postLoadProgressBar;
    connect(this, SIGNAL(progressValueChanged(int)), postLoadProgressBar, SLOT(setValue(int)));

    // Load page so we can login with javascript
    rshWEController->rshWebEnginePage->load(QUrl("https://rollenspielhimmel.de/login.do"));
    connect(rshWEController->rshWebEnginePage, &QWebEnginePage::loadFinished, [=](){this->loginActionButton->setEnabled(true);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getPostsAction(){

    deletePostsAction(); // Delete all posts before we add new ones. (deletes just by clicking the button)
    basisUrl = ui->inputUrlLineEdit->text();

    bool pageIsValid;
    if(!Validation::rshUrl(basisUrl)){
        QMessageBox error;
        error.critical(this, "Error", "Url stimmt nicht");
        error.setFixedSize(400, 200);
        return;
    }
    if(onlyOnePageCheckBox->isChecked()){
        // pages are valid because we only load one page
        pageIsValid = true;
    }
    else pageIsValid = Validation::pageNumbers(firstPage, lastPage, this->layout()->widget());

    if(pageIsValid){
        RshParser *rshParser = new RshParser();
        // If the user want only one page
        if(onlyOnePageCheckBox->isChecked()){
            postLoadProgressBar->setMinimum(0);
            postLoadProgressBar->setMaximum(1);

            if(!rshWEController->loadRsh(basisUrl)){
                QMessageBox error;
                error.critical(this, "Error", rshWEController->getLastError());
                error.setFixedSize(400, 200);
                return;
            }
            rshParser->loadJQuery(rshWEController->rshWebEnginePage);

            int postsCount = rshParser->getPostsCount(rshWEController->rshWebEnginePage);
            // Iterate through every post on the page
            for(int i = 0; i < postsCount; i++){
                RshPost* newRshPost = new RshPost();
                newRshPost->setTitle(rshParser->getPostTitle(rshWEController->rshWebEnginePage, i));
                newRshPost->setAuthorAndDate(rshParser->getPostAuthorAndDate(rshWEController->rshWebEnginePage, i));
                newRshPost->setContent(rshParser->getPostContent(rshWEController->rshWebEnginePage, i));
                rshPostCollection.append(newRshPost);
            }
            delete rshParser;
            emit progressValueChanged(1);
        }
        else{
            QString newUrl; // to append the number of the page
            postLoadProgressBar->setMinimum(firstPage);
            postLoadProgressBar->setMaximum(lastPage);

            for(int i = firstPage; i <= lastPage; i++){
                newUrl = basisUrl + QString::number(i);
                if(!rshWEController->loadRsh(newUrl)){
                    QMessageBox error;
                    error.critical(this, "Error", rshWEController->getLastError());
                    error.setFixedSize(400, 200);
                    return;
                }
                rshParser->loadJQuery(rshWEController->rshWebEnginePage);

                int postsCount = rshParser->getPostsCount(rshWEController->rshWebEnginePage);
                for(int i = 0; i < postsCount; i++){
                    RshPost* newRshPost = new RshPost();
                    newRshPost->setTitle(rshParser->getPostTitle(rshWEController->rshWebEnginePage, i));
                    newRshPost->setAuthorAndDate(rshParser->getPostAuthorAndDate(rshWEController->rshWebEnginePage, i));
                    newRshPost->setContent(rshParser->getPostContent(rshWEController->rshWebEnginePage, i));
                    rshPostCollection.append(newRshPost);
                }

                emit progressValueChanged(i);
            }
            delete rshParser;
        }
        printRshPostCollectionToScreen();
    }
}

void MainWindow::printRshPostCollectionToScreen(){

    foreach(RshPost *el, rshPostCollection){
        QStandardItem *SI = new QStandardItem(el->getTitle() + "\n" + el->getAuthorAndDate() + "\n" + el->getContent());
        SIlist.append(SI);
    }
    foreach(QStandardItem *el, SIlist){
        itemModel->appendRow(el);
    }
}

void MainWindow::disableSpinBoxes(int stage){

    if(stage){
        firstPageSpinBox->setDisabled(true);
        lastPageSpinBox->setDisabled(true);
    }
    else {
        firstPageSpinBox->setDisabled(false);
        lastPageSpinBox->setDisabled(false);
    }
}

void MainWindow::setFirstPageValue(int value){

    firstPage = value;
}

void MainWindow::setLastPageValue(int value){

    lastPage = value;
}

void MainWindow::deletePostsAction(){

    qDeleteAll(SIlist.begin(), SIlist.end());
    SIlist.clear();

    itemModel->clear();

    qDeleteAll(rshPostCollection.begin(), rshPostCollection.end());
    rshPostCollection.clear();
}

void MainWindow::closeAppAction(){

    // More features added later probably
    QCoreApplication::quit();
}

void MainWindow::savePostsAction(){

    FileManager::savePostsAsTextFile(this->layout()->widget(), &rshPostCollection);
}

void MainWindow::loginAction(){

    loginController->setLoginUsername(usernameLineEdit->text());
    loginController->setLoginPassword(passwordLineEdit->text());

    loginStatusLabel->setText("Einloggen...");

    if(loginController->loginToRsh()){
        loginStatusLabel->setText("Erfolgreich eingeloggt. Hallo " + loginController->getLoginUsername() + "!");
    }
    else{
        loginStatusLabel->setText("Login erfolglos");
    }
}
