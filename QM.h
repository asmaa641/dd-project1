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
    vector<string> doNotCares;//vectors that stores the numbers of the do not cares as binary and as string for easier comparison
    vector<string> PI;
    vector<string> EPI;
    vector<vector<string>> solutions;
    const int size;//amount of input variables
    void createFirstColumn(vector<vector<string>>& groups);
    bool generateEPI();//function that finds EPI and returns them in as strings
    bool columnDominance();
    bool rowDominance();
    void convert_max_to_min(string line);//function that converts maxterms into minterms
    bool isCovered(const string& minterm, const string& pi);
    vector<string> combineMinterms(string term1, string term2);


public:
    QM(int s,string v1,string v2);//constructor that takes the number of inputs, minterms, and do not cares calls function to convert the numbers to binary
    ~QM();//destructor
    vector<string> generatePI();
    void generateSolutions();//function that finds all the solutions and stores them as strings
    void displayPI() const;
    void displayEPI() const;
    void displaySolutions() const;

    
};
#endif
