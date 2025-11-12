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
    vector<string> minterms;//vector that stores the numbers in the columns as binary as string for easier comparison
    vector<string> doNotCares;//vectors that stores the do not cares
    vector<string> PI;//vectors that stores the prime Implicants
    vector<string> EPI;//vectors that stores the essential prime Implicants
    vector<vector<string>> solutions;//vectors that stores the solution
    const int size;//amount of input variables
    void createFirstColumn(vector<vector<string>>& groups);
    bool generateEPI();//function that finds EPI and returns them in as strings
    bool columnDominance();
    bool rowDominance();
    void convert_max_to_min(string line);//function that converts maxterms into minterms
    bool isCovered(const string& minterm, const string& pi);
    vector<string> combineMinterms(string term1, string term2);
    void generateVerilog(vector <string> v) const;//function that generates verilog code

public:
    QM(int s,string v1,string v2);//constructor that takes the number of inputs, minterms, and do not cares and converts them into binary
    ~QM();//destructor
    vector<string> generatePI();//function that generates the PI
    void generateSolutions();//function that finds all the solutions and stores them as strings
    void displayPI() const;//displays Prime Implicants
    void displayEPI() const;//displays Essential Prime Implicants
    void displaySolutions() const;//displays final solution
    
    
};
#endif
