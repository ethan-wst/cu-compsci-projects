/*************************************************************/
/*                BrowserHistory Definition                  */
/*************************************************************/
/* TODO: Implement the member functions of BrowserHistory    */
/*     This class uses a linked-list of WebPage structs to   */
/*     represent the schedule of web pages                   */
/*************************************************************/

#include "browserHistory.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
BrowserHistory::BrowserHistory() {
    /*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
    head = nullptr;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool BrowserHistory::isEmpty() {
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: prints the current list of pages 
 * in the given format.
 * [ID::1]-(URL::url1) -> ... -> NULL
 * @param none
 * @return none
 */
void BrowserHistory::displayHistory() {
    cout << "== CURRENT BROWSER HISTORY ==" << endl;
    if (head == nullptr) {
        cout << "Empty History" << endl;
        cout << "NULL" << endl;
        cout << "===" << endl;
        return;

    } else {
        WebPage* curr = head;
        cout << "[ID:: " << head->id << "]-(URL::" << head->url << ") -> ";
        while((curr->next) != nullptr) {            
            curr = curr->next;
            cout << "[ID:: " << curr->id << "]-(URL::" << curr->url << ") -> ";
        }
    }
    cout << "NULL" << endl;

    cout << "===" << endl;


}

/*
 * Purpose: Add a new webpage to the browser history LL
 *   between the previous and the page that follows it in the list.
 * @param previousPage, the show that comes before the new page
 * @param newPage, the webpage to be added. 
 * @return none
 */
void BrowserHistory::addWebPage(WebPage* previousPage, WebPage* newPage) {
    if (previousPage == nullptr) {
        WebPage* temp = head;
        head = newPage;
        head->next = temp;

        cout  <<  "adding: "  <<  "["  <<  newPage->id  <<  "]-"  <<  newPage->url  <<  " (HEAD)\n";
    
    } else {
        WebPage* temp = previousPage->next;
        previousPage->next = newPage;
        newPage->next = temp;

        cout  <<  "adding: "  <<  "["  <<  newPage->id  <<  "]-"  <<  newPage->url  <<  " (prev: "  <<  "["  <<  previousPage->id  <<  "])\n";

    }
    
    

}

/*
 * Purpose: populates the BrowserHistory with the predetermined pages
 * @param none
 * @return none
 */
void BrowserHistory::buildBrowserHistory() {
    WebPage* webList = new WebPage[5];

    webList[0].url = "https://www.colorado.edu/";
    webList[0].id = 10;

    webList[1].url = "https://www.wikipedia.org/";
    webList[1].id = 11;

    webList[2].url = "https://brilliant.org/";
    webList[2].id = 12;

    webList[3].url = "https://www.khanacademy.org/";
    webList[3].id = 13;

    webList[4].url = "https://www.numberphile.com/";
    webList[4].id = 14;

    addWebPage(nullptr, &webList[0]);
    addWebPage(&webList[0], &webList[1]);
    addWebPage(&webList[1], &webList[2]);
    addWebPage(&webList[2], &webList[3]);
    addWebPage(&webList[3], &webList[4]);

    webList = nullptr;
    

}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by ID and return a pointer to that node.
 * @param int id - ID of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByID(int id) {
    WebPage* curr = head;

    while (curr != nullptr){
        if (curr->id == id) { 
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by the URL and return a pointer to that node.
 * @param string url - url of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByURL(std::string url) {
    WebPage* curr = head;

    while (curr != 0){
        if (curr->url == url) { 
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

/*
 * Purpose: Give an owner to a web page.
 * @param receiver - name of the show that is receiving the rating
 * @param rating - the rating that is being given to a show
 * @return none
 */
void BrowserHistory::addOwner(std::string url, string owner) {
    WebPage* temp = searchPageByURL(url);
    if (temp == nullptr) {
        cout  <<  "Page not found\n";
    } else {
        temp->owner = owner;
        cout  <<  "The owner ("  <<  owner  <<  ") has been added for the ID - "<<  temp->id  <<  "\n";
    }
    
}

void BrowserHistory::updateViews(string url) {
    WebPage* temp = searchPageByURL(url);
    temp->views = temp->views + 1;
    
   
}
