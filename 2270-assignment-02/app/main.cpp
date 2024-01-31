#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;

int main(int argc, char* argv[]) {

    string infile = argv[1];
    ifstream inputfile;
    inputfile.open(infile);

    string queryParams[4];
    for (int i = 0; i < 4; i ++) {
        queryParams[i] = argv[i + 2];
    }

    int recordCount = 0;
    int doubleCount = 0;

    int arraySize = 10;
    CovidCase* cases = new CovidCase[arraySize];

    parseFile(inputfile, queryParams, cases, arraySize, recordCount, doubleCount);
    sortCases(cases, recordCount);

    cout << "Array doubled: " << doubleCount << endl;
    cout << "Total number of cases returned after the query: " << recordCount << endl;
    
    printQueriedCases(cases, recordCount);

    //resizeArr(*&cases, &arraySize);

    return 0;
}