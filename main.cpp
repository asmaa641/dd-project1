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
    
    file.open(exePath / "4_input_somePI_are_EPI.txt");
    
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
    if(!getline(file, line2) || line2.substr(0, 1) == "d"){
        cout<<"Missing second line"<<endl;
        return 1;
    }
    string line3;
    if(!getline(file, line3)){
        cout<<"Missing third line"<<endl;
        return 1;
    }//these three conditions ensure that the file is written in the right format

    ifstream file2;
    file2.open(exePath / "10_input_somePI_are_EPI.txt");
    
    if (!file2.is_open()) { //to ensure the file opens
            cout << "Error: Unable to open file!" << endl;
            return 1;
        }
    
    string line11; //to get the size from the file and initialize it to the PI
    
    if(!getline(file2, line11)){
        cout<<"Missing first line"<<endl;
        return 1;
    }
    string line12;
    if(!getline(file2, line12) && (line12.substr(0,1)!="m" || line12.substr(0,1)!="M")){
        cout<<"Missing second line"<<endl;
        return 1;
    }
    string line13;
    if(!getline(file2, line13)){
        cout<<"Missing third line"<<endl;
        return 1;
    }

    ifstream file3;
    file3.open(exePath / "20_input_somePI_are_EPI");
    
    if (!file3.is_open()) { //to ensure the file opens
            cout << "Error: Unable to open file!" << endl;
            return 1;
        }
    
    string line21; //to get the size from the file and initialize it to the PI
    
    if(!getline(file3, line21)){
        cout<<"Missing first line"<<endl;
        return 1;
    }
    string line22;
    if(!getline(file3, line22) && (line22.substr(0,1)!="m" || line22.substr(0,1)!="M")){
        cout<<"Missing second line"<<endl;
        return 1;
    }
    string line23;
    if(!getline(file3, line23)){
        cout<<"Missing third line"<<endl;
        return 1;
    }
    
    cout << "This is the test case of 4 input some PI are EPI:" << endl;
    QM trial(stoi(line1),line2,line3);
    trial.generatePI();
    trial.displayPI();
    trial.generateSolutions();
    trial.displayEPI();
    trial.displaySolutions();

    file.close();

    cout << "This is the test case of 10 input some PI are EPI:" << endl;
    QM trial2(stoi(line11),line12,line13);
    trial2.generatePI();
    trial2.displayPI();
    trial2.generateSolutions();
    trial2.displayEPI();
    trial2.displaySolutions();

    file2.close();

    cout << "This is the test case of 20 input some PI are EPI:" << endl;
    QM trial3(stoi(line21),line22,line23);
    trial3.generatePI();
    trial3.displayPI();
    trial3.generateSolutions();
    trial3.displayEPI();
    trial3.displaySolutions();

    file3.close();
    return 0;
}
