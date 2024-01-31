#include "array_double.hpp"
#include <sstream>

void parseFile(ifstream& input,string queryParams[], CovidCase *&cases, int &arrCapacity,  int &recordIdx, int &doublingCounter){

    string databaseLine;
    
    while (getline(input, databaseLine)) {

        stringstream str(databaseLine);
        CovidCase covidCase;
        string age;

        getline(str, covidCase.name, ',');
        getline(str, covidCase.variant, ',');
        getline(str, covidCase.location, ',');
        getline(str, age, ',');
        covidCase.age = stoi(age);

        if (isCaseQueried(covidCase, queryParams[0], queryParams[1], stoi(queryParams[2]), stoi(queryParams[3]))) {
            addCase(cases, covidCase, arrCapacity, recordIdx, doublingCounter);
        }   
    }
}

bool isCaseQueried(CovidCase covidCase, string queryLocation, string queryVariant, int startAge, int endAge) {
    if (covidCase.location == queryLocation ) {
        if (covidCase.variant == queryVariant ) {
            if (covidCase.age <= endAge && covidCase.age >= startAge) {
                return true;

          }
        }
    }  
    return false;
}

void resizeArr(CovidCase *&cases, int *arraySize) {

    CovidCase* newCases = new CovidCase[*arraySize * 2];

    for (int i = 0; i < *arraySize; i++) {
        newCases[i] = cases[i];
    }

    *arraySize = 2*(*arraySize);

    delete[] cases;
    cases = newCases;
    newCases = nullptr;

    
}
    

void addCase(CovidCase *&cases, CovidCase covidCase, int &arrCapacity, int &recordIdx, int &doublingCounter) {
    if (recordIdx + 1 > arrCapacity) {
        resizeArr(cases, &arrCapacity);
        doublingCounter++;
    }
    cases[recordIdx] = covidCase;
    recordIdx++;
}

void sortCases(CovidCase* cases, int length) {

    int minIndex, i, j;


        for (i = 0; i < (length - 1); i++) {   
            minIndex = i;
            
            for (j = (i + 1); j < length ; j++){
                if (cases[j].age < cases[minIndex].age || (cases[j].name < cases[minIndex].name && cases[j].age == cases[minIndex].age) ) {
                    minIndex = j;
                }
            }

            if (minIndex != i) {
                CovidCase tmp = cases[minIndex];
                cases[minIndex] = cases[i];
                cases[i] = tmp;
            }

        }
}

void printQueriedCases(CovidCase* cases, int numOfRecords) {
    
    cout << "Queried Cases\n---------------------------------------" << endl;

    for(int i = 0; i < numOfRecords; i++){
        cout << cases[i].name << " " << cases[i].age << endl;

    }

}