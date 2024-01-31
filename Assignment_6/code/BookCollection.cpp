#include "BookCollection.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

BookCollection::BookCollection() {
    root = nullptr;
}

BookCollection::~BookCollection() {
    _destruct(root);
}

void BookCollection::_destruct(Book* &book) {
    if (book == nullptr) {
        return;
    } else {
        _destruct(book->left);
        _destruct(book->right);
        delete book;
    }
}

void BookCollection::addBook(string bookName, string author, double rating) {
    _addBook(root, bookName, author, rating);
}

void BookCollection::_addBook(Book* &book, string bookName, string author, double rating) {
    if (book == nullptr) {
        book = new Book(bookName, author, rating);
        return;
    } else {
        if (bookName < book->bookName) {
            _addBook(book->left, bookName, author, rating);
        } else {
            _addBook(book->right, bookName, author, rating);
        }
    }
}

void BookCollection::showBookCollection() {
    if (root == nullptr) {
        cout << "Collection is empty." << endl;
        return;
    } else {
        _showBookCollection(root);
    }
}

void BookCollection::_showBookCollection(Book* book) {
    if (book == nullptr) {
        return;
    } else {
        _showBookCollection(book->left);
        cout << "BOOK: " << book->bookName << " BY: " << book->author << " RATING: " << book->rating << endl;
        _showBookCollection(book->right);
    }
}

void BookCollection::showBook(string bookName) {
    _showBook(root, bookName);
}

void BookCollection::_showBook(Book* book, string bookName) {
    if (book == nullptr) {
        cout << "Book not found." << endl;
    } else {
        if (book->bookName == bookName) {
            cout << "Book:" << endl;
            cout << "==================" << endl;
            cout << "Name :" << book->bookName << endl;
            cout << "Author :" << book->author << endl;
            cout << "Rating :" << book->rating << endl;
        } else if (book->bookName < bookName) {
            _showBook(book->right, bookName);
        } else {
            _showBook(book->left, bookName);
        }
    }
}

void BookCollection::showBooksByAuthor(string author) {
        cout << "Books By: " << author << endl;
        _showBooksByAuthor(root, author);
}

void BookCollection::_showBooksByAuthor(Book* book, string author) {
    if (book == nullptr ){
        return;
    }
    _showBooksByAuthor(book->left, author);     
    if (book->author.compare(author) == 0) {
        cout << book->bookName << " RATING: " << book->rating << endl;
    }
    _showBooksByAuthor(book->right, author);
}

void BookCollection::showHighestRatedBooks() {
    if (_findHighestRatedBooks(root) == -1) {
        cout << "Collection is empty." << endl;
        return;
    } else {
        double high = _findHighestRatedBooks(root);
        cout << "Highest Rating: " << high << endl;
        _showHighestRatedBooks(root);
    }
}

double BookCollection::_findHighestRatedBooks(Book* book) {

    if (book == nullptr) {
        return -1;
    } 

    _findHighestRatedBooks(book->right);

    if ((book->rating) > highRating) {
        highRating = book->rating;
    }
    _findHighestRatedBooks(book->left);

    return highRating;
    
}

void BookCollection::_showHighestRatedBooks(Book* book) {

    if (book == nullptr) {
        return;
    }

    _showHighestRatedBooks(book->left);

    if (book->rating == highRating) {
        cout << book->bookName << " BY: " << book->author << endl;    
    }
    _showHighestRatedBooks(book->right);
}

int BookCollection::getHeightOfBookCollection() {
    return _getHeightOfBookCollection(root);
}

int BookCollection::_getHeightOfBookCollection(Book* book) {
    if (book == nullptr) {
        return 0;
    } else {
        int leftSide;
        int rightSide;

        leftSide = _getHeightOfBookCollection(book->left);
        rightSide = _getHeightOfBookCollection(book->right);

        if (leftSide > rightSide) {
            return (leftSide + 1);
        } else {
            return (rightSide + 1);
        }
    }

    return 0;
    }


