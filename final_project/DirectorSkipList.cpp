#include<iostream>
#include <vector>
#include "DirectorSkipList.hpp"
using namespace std;


/** 
 * DirectorSkipList - Constructor for DirectorSkipList with default capacity and levels
 */
DirectorSkipList::DirectorSkipList() {
    DirectorSLNode* tmp = new DirectorSLNode("", DEFAULT_LEVELS);
    head = tmp;

    capacity = DEFAULT_CAPACITY;
    levels = DEFAULT_LEVELS - 1;
    size = 0;
}


/**
 * DirectorSkipList - Constructor for DirectorSkipList with given capacity and levels
 * 
 * @param _cap
 * @param _levels
 */
DirectorSkipList::DirectorSkipList(int _cap, int _levels) {
    DirectorSLNode* tmp = new DirectorSLNode("", _levels + 1);
    head = tmp;

    capacity = _cap;
    levels = _levels - 1;
    size = 0;
}


/**
 * ~DirectorSkipList - Destructor for DirectorSkipList that deletes all nodes in the skip list (but not the MovieNodes, which are shared with other data structures)
 */
DirectorSkipList::~DirectorSkipList() {
    DirectorSLNode* curr = head;
    DirectorSLNode* prev = nullptr;
    while (curr) {
        prev = curr;
        curr = curr->next[0];
        delete prev;
    }
}


/**
 * insert - Inserts a movie node into the skip list with the specified director
 * 
 * @param director
 * @param _movie
 */
void DirectorSkipList::insert(string director, MovieNode* _movie) {
    DirectorSLNode* tmp = search(director);
    DirectorSLNode* curr = head;

    // Checks if there is a node already in the list that has the same director value, if so adds the movie to the node's movie vector
    if (tmp != nullptr) {
        tmp->addMovie(_movie);
        return;
    } 

    // Calculates the number of levels the new node will exist on by flipping a coin
    int n_levels = 0;
    while (n_levels <= levels && rand() % 2 == 0) {
        n_levels++;
    }

    // Creates the new node
    DirectorSLNode* tmpNode = new DirectorSLNode(director, n_levels + 1);
    DirectorSLNode* newNode = tmpNode;
    newNode->addMovie(_movie);
    
    // If the next vector of head has no pointers the list is empty, so we insert the new node into the next vector of head
    if (head->next[0] == nullptr) { 
        for (int i = 0; i <= n_levels; i++) {
            head->next[i] = newNode;
        }
    } else { // The next vector of head is not empty and we must insert the new node into the list
        DirectorSLNode* prev;
        DirectorSLNode* curr;

        // Loops through the directors list starting from the lowest value
        for (int i = 0; i <= levels; i++) {
            curr = head->next[i];
            prev = head;

            // Loops through directorList and continues inserting at every level as long as the new node is to exist at that height
            while(i <= n_levels) {

                // If the next vector of head has no pointers at that level the new node is inserted into the vector of head at that level
                if (curr == nullptr) {
                    head->next[i] = newNode;
                    break;
                }
                
                // If the new node's director is higher in alphebetical order that the current node's director, insert infront of the current node
                if (curr->director > newNode->director) {
                        newNode->next[i] = prev->next[i];
                        prev->next[i] = newNode;
                        break;
            
                }

                // If the end of the list is reached insert the new node at the end of the list 
                if (curr->next[i] == nullptr) {
                        curr->next[i] = newNode;
                        break;
                }

                // Progress down the list
                prev = curr;
                curr = curr->next[i];
            }
        }
    }
}


/**
 * search - Searches for a node in the skip list with the specified director
 * 
 * @param director
 * 
 * @return DirectorSLNode
 */
DirectorSLNode *DirectorSkipList::search(string director) {
    DirectorSLNode* curr = head;
    // Starts seaching from the highest level
    for (int i = levels; i >= 0; i--) {
        // Loops until the end of the list is reached or a director of lesser alphebetical value is found
        while (curr->next[i] != nullptr && curr->next[i]->director < director) {
            curr = curr->next[i];

            // Checks that the current node exists and is the has the desired director, if so returns node
            if (curr->next[0] && curr->next[0]->director == director) {
                return curr->next[0];
            }
        }
    }
    return nullptr;
}


/**
 * prettyPrint - Pretty-prints the skip list
 */
void DirectorSkipList::prettyPrint() {
    DirectorSLNode* curr;
    int numL;
    cout << endl;
    // Starts looping from the highest level
    for (int i = levels; i >= 0; i--) {
        curr = head;
        cout << "[" << i << "]" << " -> ";
        
        // Loops through every nodes next vector at a level and prints its director
        while (curr->next[i]) {
            numL = curr->next.size() - 1;
            curr = curr->next[i];
            cout << curr->director << " -> ";
        }
        cout << "NULL" << endl;
    }
}

