//
//  main.cpp
//  Project 1
//
//  Created by Jumanah Moussa on 08/11/2025.
//
#include <fstream>
#include <iostream>
#include "QM.h"
#include <filesystem>
using namespace std;

int main(int argc, char* argv[]) {
    filesystem::path exePath = filesystem::absolute(argv[0]).parent_path();
    ifstream file;
    file.open(exePath / "4_input_allPI_are_EPI.txt");
    
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
    if(!getline(file, line2) && (line2.substr(0,1)!="m" || line2.substr(0,1)!="M")){
        cout<<"Missing second line"<<endl;
        return 1;
    }
    string line3;
    if(!getline(file, line3)){
        cout<<"Missing third line"<<endl;
        return 1;
    }//these three conditions ensure that the file is written in the right format
    
    QM trial(stoi(line1),line2,line3);
    trial.generatePI();
    trial.displayPI();
    trial.generateSolutions();
    trial.displayEPI();
    trial.displaySolutions();

    file.close();

    

    return 0;
}
