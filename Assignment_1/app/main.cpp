#include <iostream>
#include <fstream>
#include "../code/fundamentals.hpp"
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

    string inputfile = argv[1];
    ifstream infile;
    infile.open(inputfile);

    int linesInFile = 0;
    stockInfo stocks[5];
    string company_name;
    double stock_prices_arr[5];
    int index = 0;
    string line;

    while (getline(infile, line)) {

        string temp;
        stringstream str(line);
        linesInFile++;

        getline(str, company_name, ',');

        for (int i = 0; i < 5; i++) {
            getline(str, temp, ',');
            stock_prices_arr[i] = stod(temp);
        }

        insertStockInfo(stocks, company_name, stock_prices_arr, index);
        index++;
    }

    string outfile = argv[2];
    ofstream outputfile;
    outputfile.open(outfile);

    for (int i = 0; i < linesInFile; i++) {
        displaySortedStocks(stocks[i], outputfile);
    }
    return 0;
}