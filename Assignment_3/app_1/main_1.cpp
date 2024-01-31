#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "../code_1/browserHistory.hpp"

using namespace std;

void displayMenu();

int main(int argc, char* argv[]) {

    // DO NOT MODIFY THIS.
    if(argc>1) 
    {
        freopen(argv[1],"r",stdin);
    }
    // DO NOT MODIFY ABOVE.
    
    BrowserHistory LL;
    
    int input = 0;

    while (input != 6) {

        displayMenu();
        cin >> input;

        switch (input) {
            case 1:
            {
                LL.buildBrowserHistory();
                LL.displayHistory();
                break;
            }

            case 2:
            {
                LL.displayHistory();
                break;
            }

            case 3: 
            {

                string newURL = "";
                int newID = 0;
                string prevURL = "";
                WebPage* newPage = new WebPage;
                
                cout << "Enter the new web page's url:" << endl;
                cin >> newURL;
                newPage->url = newURL;


                cout << "Enter the new web page's id:" << endl;
                cin >> newID;
                newPage->id = newID;
                while (LL.searchPageByID(newID) != nullptr) {
                    cout << "This ID already exists. Try again." << endl;
                    cout << "Enter the new web page's id:" << endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> newID;
                }
                newPage->id = newID;

                cout << "Enter the previous page's url (or First):" << endl;
                cin >> prevURL;

                while(true) {
                    if (prevURL == "First") {
                        LL.addWebPage(nullptr, newPage);
                        break;
                    } else if (LL.searchPageByURL(prevURL) != nullptr ) {
                        LL.addWebPage(LL.searchPageByURL(prevURL), newPage);
                        LL.updateViews(newURL);
                        break;
                    } else {
                        cin.clear();
                        cin.ignore(256,'\n');
                        cout << "INVALID(previous page url)... Please enter a VALID previous page url!" << endl;
                        cout << "Enter the previous page's url (or First):" << endl;
                        cin >> prevURL;
                    }
                }
                break;
            }

            case 4: 
            {
                string url;
                string owner;

                cout << "Enter url of the web page to add the owner:" << endl;
                cin >> url;
                while (LL.searchPageByURL(url) == nullptr) {
                    cout << "Page not found. Try again." << endl;
                    cout << "Enter url of the web page to add the owner:" << endl;
                    cin >> url;
                }

                cin.ignore(256, '\n');

                cout << "Enter the owner:";
                getline(cin, owner);
                LL.addOwner(url, owner);
                break;
            }

            case 5: 
            {
                string url;
                WebPage* temp;
                cout << "Enter url of the web page to check the view count: " << endl;
                cin >> url;
                temp = LL.searchPageByURL(url);
                while (temp == nullptr) {
                        cout << "Page not found. Try again." << endl;
                        cout << "Enter url of the web page to check the view count: " << endl;
                        cin >> url;
                        temp = LL.searchPageByURL(url);   
                    }
                if (temp != nullptr) {
                    cout << "View count for URL - " << url << " is " << temp->views << endl;
                }
                
                break;
            }

            default:
            {
                cin.clear();
                cin.ignore(256,'\n');
            }
        }
    }

    if (input == 6) {
        cout << "Quitting...Goodbye!\n";
    }
    return 0;
}




/************************************************
           Definitions for main_1.cpp
************************************************/
void displayMenu()
{
    // COMPLETE: You DO NOT need to edit this
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build history " << endl;
    cout << " 2. Display history " << endl;
    cout << " 3. Add web page " << endl;
    cout << " 4. Add owner" << endl;
    cout << " 5. View count for a web page" << endl;
    cout << " 6. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
