//
//  main.cpp
//  DD_proj1
//
//  Created by Jumanah Moussa on 04/11/2025.
//

#include <iostream>
#include <fstream>
#include "PI.h"
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
    return 0;
}
