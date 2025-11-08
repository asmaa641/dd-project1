//
//  main.cpp
//  DD_proj1
//
//  Created by Jumanah Moussa on 04/11/2025.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "PI.h"
#include "generatePI.h"
using namespace std;

int main(int argc, const char * argv[]) {
    ifstream file;
    file.open("/Users/jojo/Downloads/4_input_somePI_are_EPI.txt");
    
    if (!file.is_open()) { //to ensure the file opens
            cout << "Error: Unable to open file!" << endl;
            return 1;
        }
    
    string line1; //to get the size from the file and initialize it to the PI
    
    if(!getline(file, line1)){
        cout<<"Missing first line"<<endl;
        return 1;
    }
    string line2;
    if(!getline(file, line2)){
        cout<<"Missing second line"<<endl;
        return 1;
    }
    string line3;
    if(!getline(file, line3)){
        cout<<"Missing third line"<<endl;
        return 1;
    }//these three conditions ensure that the file is written in the right format
    
         PI colum1(stoi(line1),line2,line3);
    file.close();

      vector<string> minterms  = {"0100", "0101", "0110","1000","1001","1101"};
    vector<string> dontcares = {"0000", "0111","1111"};  // checking if generate pi works

    generatePI gen;
    vector<string> PIs = gen.generatePrimeImplicants(minterms, dontcares);

    cout << "Prime Implicants (" << PIs.size() << "):\n";
    for (size_t i = 0; i < PIs.size(); ++i) {
        cout << "  " << PIs[i] << '\n';
    }


    return 0;
}
