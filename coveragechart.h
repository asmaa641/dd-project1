#include <iostream>
#include <vector>
using namespace std;

class CoverageChart{
private:
    int size;
    vector<string> PI;
    vector<string> minterms;
    vector<string> EPI;
    vector<vector<string>> solutions;
    void generateEPI();
    void generateSolutions();
    bool isCovered(const string& minterm, const string& pi);

public:
    CoverageChart(const int& s, const vector<string>& pi, const vector<string>& minterms);
    void displayEPI() const;
    void displaySolutions() const;
};