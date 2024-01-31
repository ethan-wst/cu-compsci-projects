#include<iostream>
#include <vector>
#include <cmath>
#include "MovieHashTable.hpp"
using namespace std;


/**
 * MovieHashTable - Constructor for MovieHashTable with default size.
 */ 
MovieHashTable::MovieHashTable() {
    table_size = DEFAULT_HTABLE_CAPACITY;
    MovieNode **newtable = new MovieNode*[table_size];
    for (int i = 0; i < table_size; i++) {
        newtable[i] = nullptr;
    }
    table = newtable;
    n_collisions = 0;
}


/**
 * MovieHashTable - Constructor for MovieHashTable with given size.
 * 
 * @param s
 */ 
MovieHashTable::MovieHashTable(int s) {
    table_size = s;
    MovieNode **newtable = new MovieNode*[table_size];
    for (int i = 0; i < table_size; i++) {
        newtable[i] = nullptr;
    }
    table = newtable;
    n_collisions = 0;
}


/**
 * ~MovieHashTable - Destructer for MovieHashtable that deletes all nodes in the hash table and the table itself.
 */
MovieHashTable::~MovieHashTable() {
    for (int i = 0; i < table_size; i++) {
        delete table[i];
    }
    delete[] table;
}


/**
 * hash - Hash function for MovieHashTable that returns an index in the hash table for a given movie title. 
 * 
 * @param title
 * @return int
*/
int MovieHashTable::hash(string title) {
    double ASCII_Val = 0;
    string IdentiKey = "etwe3371";
    double Factor = .7741; // .7741 = .437 + .3371, 437 is the combined ASCII Values of etwe
    int index = 0;

    // Loops through every letter of the given movie title
    for (int i = 0; i < title.length(); i++) {
        // Combines ASCII values of each individual letter in the movie title
        ASCII_Val = ASCII_Val + title[i];
    }

    // Multiplies the ASCII value of the title by factor, takes the decimal of that number and multiplies it by the table size, then rounds down to an integer
    index = floor(table_size*(fmod((ASCII_Val*Factor),1)));
    return index;
}


/**
 * insert - Inserts a movie node into hash table with specific title and uses quadratic probing to handle collisions.
 * 
 * @param title
 * @param movie
 */
void MovieHashTable::insert(string title, MovieNode* movie) {
    int index = hash(title); // Hashes the given title

    // Checks if the hashed index is empty and inserts the movieNode if it is
    if (table[index] == nullptr) {
        table[index] = movie;
        return;
    } else {
        // Hash Collisions (quadratic probing), if the hashed index is not empty the collision is resolved by testing indexes with quadratic probing
        setCollisions();
        for (int i = 0; i < table_size; i ++) {
            int NewIndex = (((index + (i * i)) % table_size));
            if (table[NewIndex] == nullptr) {
                table[NewIndex] = movie;
                return;
            }
        }
    }
}


/**
 * Search - Searches for a node in the hash table with the specified title.
 * 
 * @param title
 * 
 * @return MovieNode*
 */ 
MovieNode* MovieHashTable::search(string title) {
    int index = hash(title); // Hashes the given title

    // Checks if hashed index is empty, if so then the movie is not in the table
    if (table[index] == nullptr) {
        return nullptr;
    }

    MovieNode* curr = table[index];

    // Loops until the current movieNode's title matches the desired title, searches using quadratic probing to make search more effiecient
    while (curr != nullptr) {
         for (int i = 0; i < table_size; i ++) {
            int NewIndex = ((index + (i * i) % table_size));
            curr = table[NewIndex];
            
            if (curr->title.compare(title) == 0) {
                return curr;
            }
        }
    }
    return nullptr;
}


/**
 * GetCollisions - Returns the number of collisions that have occurred during insertion into the hash table. 
 * 
 * @return int
 */
int MovieHashTable::getCollisions() {
    return n_collisions;
}


/** 
 * SetCollision - Increments the number of collisions that have occurred during insertion into the hash table.
 */
void MovieHashTable::setCollisions() {
    n_collisions++;
}
