#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <bits/stdc++.h>
#include "MovieHashTable.hpp"
#include "DirectorSkipList.hpp"

using namespace std;

// Function prototypes
MovieNode* parseMovieLine(string line);
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList);
void display_menu();
void handleUserInput(MovieHashTable &movieTable, DirectorSkipList &directorList);


/**
 * main - Main function, takes in user arguments, declares objects, and calls readMovieCSV and handleUserInputs.
 */
int main(int argc, char* argv[]) {

    // Outputs error message if user arguments are incorrect
    if (argc != 4) {
        cerr << "Invalid number of arguments." << endl;
        cerr << "Usage: ./<program name> <csv file> <hashTable size> <skipList size>" << endl;
    }

    // Constructs the movieTable and directorList objects with user inputs
    MovieHashTable movieTable(atoi(argv[2]));
    DirectorSkipList directorList(atoi(argv[3]), (int)log2(atoi(argv[3])));
    
    readMovieCSV(argv[1], movieTable, directorList);
    handleUserInput(movieTable, directorList);

    return 0;
}


/** 
 * parseMovieLine - Function to parse a CSV line into a MovieNode object
 * 
 * @param line
 */
MovieNode* parseMovieLine(string line) {
    stringstream ss(line);
    vector<string> fields;
    string field;

    // Loop through the characters in the line
    bool in_quotes = false;
    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];
        if (c == '\"') {
            in_quotes = !in_quotes;
        } else if (c == ',' && !in_quotes) {
            // add field to vector and reset for next field
            fields.push_back(field);
            field.clear();
        } else {
            field += c;
            // handle double quotes inside a quoted field
            if (in_quotes && c == '\"' && i < line.length() - 1 && line[i+1] == '\"') {
                field += '\"'; // add the second double quote and skip it
                ++i;
            }
        }
    }
    fields.push_back(field);

    if (fields.size() != 12) {
        cerr << "Error: Invalid movie line format" << line << endl;
        return nullptr;
    }

    int rank = stoi(fields[0]);
    string title = fields[1];
    string genre = fields[2];
    string description = fields[3];
    string director = fields[4];
    string actors = fields[5];
    int year = stoi(fields[6]);
    int runtime = stoi(fields[7]);
    float rating = stof(fields[8]);
    int votes = stoi(fields[9]);
    float revenue = stof(fields[10]);
    int metascore = stoi(fields[11]);

    // Create a new MovieNode object with the parsed fields
    MovieNode* movie = new MovieNode(rank, title, genre, description, director, actors, year, runtime, rating, votes, revenue, metascore);
    return movie;
}


/**
 * ReadMovieCSV - Function to read a CSV file into a vector of MovieNode objects
 * 
 * @param filename
 * @param movieTable
 * @param directorList
 */
void readMovieCSV(string filename,  MovieHashTable &movieTable, DirectorSkipList &directorList) {
    ifstream file(filename);
    string line;
    file.ignore(10000, '\n'); // Handles first line of CSV

    // Loops through every line in the CSV 
    while(getline(file, line)) {
        MovieNode* tmp = parseMovieLine(line); // Creates Movie Node objects from each line of the CSV
        movieTable.insert(tmp->title, tmp); // Inserts the MovieNode objects into the movieTable
        directorList.insert(tmp->director, tmp); // Inserts the MovieNode objects into the directorList        
    }

}


/**
 * HandleUserInput - Funciton that handles displaying the options menu and user inputs
 * 
 * @param filename
 * @param movieTable
 * @param directorList
 */
void handleUserInput(MovieHashTable &movieTable, DirectorSkipList &directorList) {
    int choice;
    bool quit = false;
    bool MenuLoop = true;

    while (!quit) {
        // Displays options menu
        cout << "\nNumber of collisions: " << movieTable.getCollisions() << endl;
        display_menu();

        // Loop to ensure valid input
        while (MenuLoop) {
            cout << "Enter an Option: ";
            cin >> choice;

            // Checks if input is a valid integer, loops if not
            if (!cin && choice < 1 || choice > 5) {
                cout << "Please enter a valid choice." << endl;
                cout << "Try again." << endl;
                cin.clear();
                cin.ignore(100, '\n');
                continue;
            } else {
                MenuLoop = false;
                cin.clear();
                cin.ignore(100, '\n');
            }
        }
        
        // User Input Switch
        switch (choice) {
            case 1: { // Find the director of a movie
                while (true) {
                    cout << "Enter movie name: ";
                    string movieName; 
                    getline(cin, movieName);
                    MovieNode* movie = movieTable.search(movieName);

                        if (movie != nullptr) {
                            cout << "\n" << movie->title << " was directed by " << movie->director << endl;
                            break;
                        } else {
                            cout << "\nMovie was not found. Try again." << endl;
                        }
                    }
                break;

            } case 2: { // Find the number of movies by a director
                while (true) {
                    cout << "Enter director name: ";
                    string directorName; 
                    getline(cin, directorName);
                    DirectorSLNode* directorNode = directorList.search(directorName);

                        if (directorNode != nullptr) {
                            if (directorNode->movies.size() == 1) {
                                cout << "\n" << directorNode->director << " directed " << directorNode->movies.size() << " movie" << endl;
                                break;
                            } else {
                                cout << "\n" << directorNode->director << " directed " << directorNode->movies.size() << " movies" << endl;
                                break;
                            }
                        } else {
                            cout << "\nDirector was not found. Try again." << endl;
                        }
                    }
                break;

            } case 3: { // Find the description of a movie
                while (true) {
                    cout << "Enter movie name: ";
                    string movieName;
                    getline(cin, movieName);
                    MovieNode* movie = movieTable.search(movieName);

                        if (movie != nullptr) {
                            cout << "\nSummary: " << movie->title << " is a " << movie->year << " ("<< movie->genre << ") film featuring " << "\"" << movie->actors << ".\"" <<endl;
                            cout << "Plot: " << "\"" << movie->description << "\"" << endl;
                            break;
                        } else {
                            cout << "\nMovie was not found. Try again." << endl;
                        }
                    }
                break;

            } case 4: { // List the movies by a director
                while (true) {
                    cout << "Enter director name: ";
                    string directorName; 
                    getline(cin, directorName);
                    DirectorSLNode* directorNode = directorList.search(directorName);

                        if (directorNode != nullptr) {
                            cout << "\n" << directorNode->director << " directed the following movies:" << endl;
                            for (int i = 0; i < directorNode->movies.size(); i++) {
                                cout << i+1 << ": " << directorNode->movies[i]->title << endl;
                            }
                            break;
                        } else {
                            cout << "\nDirector was not found. Try again." << endl;
                        }
                    }
                break;
            
            } case 5: { // Quit
                cout << "Quitting...Goodbye!\n";
                quit = true;
                break;
            }
        }
        MenuLoop = true;
    }
}



/**
 * Display_menu - Function to display the menu options
 */
void display_menu() {
    cout << "Please select a numerical option:" << endl;
    cout << " 1. Find the director of a movie" << endl;
    cout << " 2. Find the number of movies by a director" << endl;
    cout << " 3. Find the description of a movie " << endl;
    cout << " 4. List the movies by a director" << endl;
    cout << " 5. Quit" << endl;
    cout << endl;
}
