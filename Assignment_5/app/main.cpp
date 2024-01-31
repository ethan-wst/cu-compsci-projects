#include<iostream>
#include <fstream>
#include<cmath>
#include<iomanip>
#include "../code/MessageDecoder.hpp"

using namespace std;


int main(int argc, char* argv[])
{
   if (argc < 2) {
        cout << "Usage: ./run_app <inputfilename>" << endl;
        return 0;
    } else {
      MessageDecoder decoder;

      string infile = argv[1];
      ifstream inputfile;
      inputfile.open(infile);

      string str;

      getline(inputfile, str);
      decoder.generate_operator_queue(str);

      string test = decoder.generate_postfix(str);
      cout << "Postfix Notation::" << test << endl;

      int final = decoder.evaluate_postfix(test);
      cout << "Final Answer::" << final << endl;

      return 0;
    }
    
  return 0;
}