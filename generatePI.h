#ifndef GENERATEPI_H
#define GENERATEPI_H

#include <string>
#include <vector>
using namespace std;

class generatePI{


    public:
  
    void createFirstColumn(vector<string>& minterms, vector<string>& dontcares,
    vector<vector<string>>& groups);
    vector<string> combineMinterms(string term1, string term2);
    // void combineMintermsAcrossGroups(vector<vector<string>>& groups, vector<string>& primeImplicants);
    vector<string> generatePrimeImplicants(vector<string>& minterms, vector<string>& dontcares);
};


#endif