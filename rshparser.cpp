#include "rshparser.h"

RshParser::RshParser()
{
}

void RshParser::postsfromWebViewToCollection(QWebView* webView, QList<RshPost*> *rshPostCollection)
{
    QWebElementCollection postbody = webView->page()->mainFrame()->findAllElements("div.forum_postbody_content");

    foreach(QWebElement el, postbody){
        RshPost* newRshPost = new RshPost();

        // Gets title of Post
        QString title;
        title = el.findFirst("h2").toPlainText();
        newRshPost->setTitle(title);

        // Gets author and time (with regex could it be splitted)
        QString authorAndTime;
        authorAndTime = el.findFirst("span.forum_postbody_small").toPlainText();
        newRshPost->setAuthorAndDate(authorAndTime);

        // Gets content of post with <p>
        QString stringForP;
        QWebElementCollection pCollection = el.findAll("p");
        foreach(QWebElement el, pCollection){
            stringForP.append(el.toPlainText());
        }
        stringForP = stringForP.simplified(); // Calling simplified so it doesnt apply format of user
        // Is empty for some user. Instead divs contain the content
        // TODO: Check what happens if they post something without writing something
        if(stringForP.isEmpty()){
            QString stringForDivs;
            QWebElementCollection divsCollection = el.findAll("div");
            for(int i = 0; i < divsCollection.count(); i++){
                if(i != (divsCollection.count() -1)) stringForDivs += divsCollection.at(i).toPlainText() + "\n";
                else stringForDivs += divsCollection.at(i).toPlainText();
            }
            newRshPost->setContent(stringForDivs.simplified());
        }
        else {
          newRshPost->setContent(stringForP);
        }
        // Important that it is still in the loop. Or else empty content could be added
        rshPostCollection->append(newRshPost);
    }
}
