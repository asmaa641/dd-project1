#include <iostream>
#include <string>
#include <vector>
#include "generatePI.h"
using namespace std;

void generatePI::createFirstColumn(vector<string>& minterms, vector<string>& dontcares,
    vector<vector<string>>& groups){
        
    if (minterms.empty() && dontcares.empty()) return; //nothing there

    int inputSize = !minterms.empty() ? minterms[0].size() : dontcares[0].size(); 
    //get input size by checking the size of the first element 

    vector<string> allTerms = minterms; // create a vector of all terms to put minterms and dont cares together
    allTerms.insert(allTerms.end(), dontcares.begin(), dontcares.end());

    groups.clear();
    groups.resize(inputSize + 1); //making sure the groups vector is ready for use

    for(int i = 0; i < allTerms.size(); i++){ // iterate through each term in allTerms, then iterate through the 0s and 1s in each element
        int onesCount = 0;
        string str = allTerms[i];
        for (int j = 0; j < inputSize; j++){
            if(str[j] == '1') onesCount++;
        }
        if (onesCount >= 0) {
            groups[onesCount].push_back(allTerms[i]);
        }
        
        
    }
}

vector<string> generatePI::combineMinterms(string term1, string term2) { //combine minterms that only differ by 1 bit (coloumn 2)
    string combinedTerm = ""; // intial combine minterms
    int diffCount = 0;
    
    for (int i = 0; i < term1.length(); i++) {
        if (term1[i] != term2[i]) { // checking if theres a bit thats not equal
            diffCount++;
            combinedTerm += '-';  
        } else {
            combinedTerm += term1[i];
        }
    }

    if (diffCount == 1) { // we just want the ones that differ only by one bit
        return {combinedTerm}; 
    }

    return {};
}



vector<string> generatePI::generatePrimeImplicants(vector<string>& minterms, vector<string>& dontcares) {
   
    int inputSize = minterms.empty() ? 0 : minterms[0].size(); // get input size 

    vector<vector<string>> groups(inputSize + 1);
    vector<string> primeImplicants;

    createFirstColumn(minterms, dontcares, groups);

    // flatten all groups into a vector (single list) instead of a vector of vectors so we can 
    // process them easier in the while loop
    vector<string> current;
    for (int i = 0; i < groups.size(); i++) {
        for (int j = 0; j < groups[i].size(); j++) {
            current.push_back(groups[i][j]);
        }
    }

    // loop until no more combinations possible to get unused terms (pis)
    while (true) {
        vector<vector<string>> newGroups(inputSize + 1);
        vector<string> combinedTerms;
        vector<vector<bool>> used(groups.size());

        // resize used tracker to match each group
        for (int i = 0; i < groups.size(); i++) {
            used[i] = vector<bool>(groups[i].size(), false);
        }

        bool combinedAnything = false;

        // combine adjacent groups (groups with only one differing bit. keep track of unused terms
        // as this is the pis)
        for (int i = 0; i < groups.size() - 1; i++) {
            for (int j = 0; j < groups[i].size(); j++) {
                for (int k = 0; k < groups[i + 1].size(); k++) {
                    vector<string> combined = combineMinterms(groups[i][j], groups[i + 1][k]);
                    if (!combined.empty()) {
                        combinedAnything = true;
                        used[i][j] = true;
                        used[i + 1][k] = true;
                        combinedTerms.push_back(combined[0]);
                    }
                }
            }
        }

        // anything not used this round os prime implicant
        for (int i = 0; i < groups.size(); i++) {
            for (int j = 0; j < groups[i].size(); j++) {
                if (!used[i][j]) {
                    primeImplicants.push_back(groups[i][j]);
                }
            }
        }

        // stop if no more combinations
        if (!combinedAnything) break;

        // regroup new combined terms by number of ones
        for (int i = 0; i < combinedTerms.size(); i++) {
            int ones = 0;
            for (int b = 0; b < combinedTerms[i].size(); b++) {
                if (combinedTerms[i][b] == '1') ones++;
            }
            newGroups[ones].push_back(combinedTerms[i]);
        }

        // prepare for next round
        groups = newGroups;
    }

    return primeImplicants;
}
