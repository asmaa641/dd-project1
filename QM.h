//
//  QM.h
//  Project 1
//
//  Created by Jumanah Moussa on 08/11/2025.
//

#ifndef QM_h
#define QM_h
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class QM{
private:
    vector<string> minterms;//vector that stores the numbers in the columns as binary and as string for easier comparison
    vector<string> doNotCares;//vectors that stores the numbers of the do not cares as decimal
    vector<string> PI;
    vector<string> EPI;
    vector<vector<string>> solutions;
    const int size;//amount of input variables
    void generateEPI();//function that finds EPI and returns them in as strings
    void generateSolutions();//function that finds all the solutions and stores them as strings
    void convert_max_to_min(string line);//function that converts maxterms into minterms
    bool isCovered(const string& minterm, const string& pi);

public:
    QM(int s,string v1,string v2);//constructor that takes the number of inputs, minterms, and do not cares calls function to convert the numbers to binary
    ~QM();//destructor
    void displayEPI() const;
    void displaySolutions() const;
};
#endif
