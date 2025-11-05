#include <iostream>
#include <string>
#include <vector>
using namespace std;


bool isGreyCode(string x, string y){
    int numberOfDifferentBits = 0;
    for(int i  = 0; i < x.length(); i++){
        if(x[i] != y[i]) numberOfDifferentBits++;
    }
    if (numberOfDifferentBits == 1) return true;
    else return false;
}

void createFirstColumn(vector<string> minterms, vector<string> dontcares){
    
    int onesCount = 0;
    vector<vector<string>>& groups;
    for(int i = 0; i < minterms.size(); i++){
        string str = minterms[i];
        for (int j = 0; j < inputSize; j++){
            if(str[i] == 1) onesCount++;
        }
        groups[onesCount].push_back(minterms[i]);
        
    }
}

vector<string> combineMinterms(string term1, string term2) {
    string combinedTerm = "";
    int diffCount = 0;
    
    for (int i = 0; i < term1.length(); i++) {
        if (term1[i] != term2[i]) {
            diffCount++;
            combinedTerm += '-';  
        } else {
            combinedTerm += term1[i];
        }
    }

    if (diffCount == 1) {
        return {combinedTerm}; 
    }

    return {};
}

void combineMintermsAcrossGroups(vector<vector<string>>& groups, vector<string>& primeImplicants) {
    vector<vector<bool>> used(groups.size(), vector<bool>(100, false)); 
    for (int i = 0; i < groups.size() - 1; i++) {
        for (int j = 0; j < groups[i].size(); j++) {
            for (int k = 0; k < groups[i + 1].size(); k++) {
                vector<string> combined = combineMinterms(groups[i][j], groups[i + 1][k]);
                if (!combined.empty()) {
                    primeImplicants.push_back(combined[0]);
                    used[i][j] = true;  
                    used[i + 1][k] = true;
                }
            }
        }
    }

    for (int i = 0; i < groups.size(); i++) {
        for (int j = 0; j < groups[i].size(); j++) {
            if (!used[i][j]) {
                primeImplicants.push_back(groups[i][j]);
            }
        }
    }
}

vector<string> generatePrimeImplicants(vector<string>& minterms) {
    vector<vector<string>> groups(minterms[0].length() + 1);  
    vector<string> primeImplicants;

    createFirstColumn(minterms, groups);

    combineMintermsAcrossGroups(groups, primeImplicants);

    return primeImplicants;
}