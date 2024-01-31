
#include "BrowserHistory.hpp"

BrowserHistory::BrowserHistory()
{
    // No changes needed
}

BrowserHistory::~BrowserHistory()
{
    // No changes needed
}

/*
 * Purpose: Has to detect if a defect is present in the linkedlist pointed by head
 * @param none
 * @return integer length of defect if one exists. If defect not present return -1
 */
int BrowserHistory::findDefectLength(){

    // TODO START =============================================
    
    if (head == NULL) {
        return -1;
    } else {
        WebPage* fast = head;
        WebPage* slow = head;
        int count = 1;

        while (fast->next != nullptr && fast != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast) {
                fast = fast->next;
                while(slow != fast) {
                    fast = fast->next;
                    count ++;
                }
            return count;
            }
            
        }
        return -1;
    }

    // TODO END ==================================================
}

/*
 * Purpose: Has to remove all the WebPage nodes from [start, end] inclusive.
 * Has to print appropriate messages on cout like below if the linkedlist is empty
 * or if the values of start/ end are improper
 * follow the same order for couts in the writeup - check empty list first, then check wrong start/end values
 * @param integers start and end (1 based indexing not 0 based)
 * @return none
 */
void BrowserHistory::removeWebPages(int start, int end){

    // TODO START ===================================================
    int index = 1;
    WebPage* front = head;
    WebPage* temp = nullptr;
    WebPage* temp2 = nullptr;

    if (head == NULL) {
        cout << "Browsing history is Empty" << endl;
        return;

    } else if (start < 1 || start > end) {
        cout << "Invalid start or end values" << endl;
        return;

    } else {

        while (index < start - 1) {

            if (front != nullptr) {
                front = front->next;
                index++;
            }
        }
        temp = front;
        if (start == 1 && end == 1) {
            temp = front->next;
            head = temp;
            delete front;
            front = nullptr;
            return;

        } else if (start == end) {
            temp = front -> next;
            front->next = temp->next;
            delete temp;
            temp = nullptr;

        } else if (start == 1) {
            temp = front;
            for (int i = 0; i < end - index; i++) {
                if (temp != nullptr) {
                    temp2 = temp;
                    temp = temp->next;
                    front->next = temp;
                    delete temp2;
                    temp2 = nullptr;
                } else {
                    cout << "Invalid start or end values" << endl;
                    return;
                }
            }
            head = nullptr;
            return;

        } else {
            temp = front->next;
            for (int i = 0; i < end - index; i++) {
                if (temp != nullptr) {
                    temp2 = temp;
                    temp = temp->next;
                    front->next = temp;
                    delete temp2;
                    temp2 = nullptr;
                } else {
                    cout << "Invalid start or end values" << endl;
                    return;
                }
            }
            return;
        }
    }
}

    // TODO END ===================================================


/*
 * Purpose: Interweave the webpages alternatively into a new linkedlist 
 * starting with the first webpage in the list one
 * Assign the head of the new interweaved list to the head of this BrowserHistory
 * DO NOT create new nodes and copy the data, just use the same nodes from one and two and change pointers
 * If one of them runs out of length append the remaining of the other one at end
 * @param two linkedlist heads one and two
 * @return none
 */
void BrowserHistory::mergeTwoHistories(WebPage *headOne, WebPage * headTwo){

    // TODO START =============================================
    //First
    if (headOne == nullptr) {
        head = nullptr;
        return;

    } else if (headTwo == nullptr) { 
        head = headOne;
        return;

    }else {
        head = headOne;
        headOne = headOne->next;
        head->next = headTwo;
        headTwo = headTwo->next;
    }
    // Second
    if (headOne == nullptr) {
        head->next->next=headTwo;
        return;
    } else if (headTwo == nullptr) {
        head->next->next=headOne;
        return;
    } else {
        head->next->next = headOne;
        headOne = headOne->next;
        head->next->next->next = headTwo;
        headTwo = headTwo->next;
    }
    // Third
    if (headOne == nullptr) {
        head->next->next->next=headTwo;
        return;
    } else if (headTwo == nullptr) {
        head->next->next->next=headOne;
        return;
    } else {
        head->next->next->next->next = headOne;
        headOne = headOne->next;
        head->next->next->next->next->next = headTwo;
        headTwo = headTwo->next;
    }
    // Fourth
    if (headOne == nullptr) {
        head->next->next->next->next->next->next=headTwo;
        return;
    } else if (headTwo == nullptr) {
        head->next->next->next->next->next->next=headOne;
        return;
    } else {
        head->next->next->next->next->next->next = headOne;
        headOne = headOne->next;
        head->next->next->next->next->next->next->next = headTwo;
        headTwo = headTwo->next;
    }
    //Fifth
    if (headOne == nullptr) {
        head->next->next->next->next->next->next->next->next=headTwo;
        return;
    } else if (headTwo == nullptr) {
        head->next->next->next->next->next->next->next->next=headOne;
        return;
    } else {
        head->next->next->next->next->next->next->next->next = headOne;
        headOne = headOne->next;
        head->next->next->next->next->next->next->next->next->next = headTwo;
        headTwo = headTwo->next;
    }
    // TODO END ==================================================
}
