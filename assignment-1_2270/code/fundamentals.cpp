#include "fundamentals.hpp"

void insertStockInfo(stockInfo stocks[], string company_name, double stock_prices_arr[], int index) {
    
    stocks[index].company_name = company_name;

    for (int i = 0; i < 5; i++){
        stocks[index].stock_prices_arr[i] = stock_prices_arr[i];
    }

    double sum = 0;
    for (int i = 0; i < 5; i++){
        sum = stock_prices_arr[i] + sum;
    }

    stocks[index].average = sum/5;

    return;
}

void displaySortedStocks(stockInfo stock, ofstream& file){
        file << stock.company_name;
        cout << stock.company_name;
        file << "," << stock.average;
        cout << "," << stock.average;
        int count = 0;
        int num = 0;
            for (int k = 0; k < 5; k++) {   

                double low = stock.stock_prices_arr[count];
                num = count;

                for (int i = count + 1; i < 5 ; i++){
                    if (stock.stock_prices_arr[i] < low) {
                        low = stock.stock_prices_arr[i];
                        num = i;
                    }
                }

                double tmp = stock.stock_prices_arr[count];
                stock.stock_prices_arr[count] = low;
                stock.stock_prices_arr[num] = tmp;
                
                file << "," << low;
                cout << "," << low;
                count++;

            }
        file << "\n";
        cout << "\n";
    return;
}