//
//  QM.cpp
//  Project 1
//
//  Created by Jumanah Moussa on 08/11/2025.
//
#include "QM.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>
#include <string>
//#include "generatePI.h"
using namespace std;

QM::QM(int s,string v1,string v2):size(s),minterms(),doNotCares(),PI(),EPI(),solutions(){
    string m;
    m=v1.substr(0,1);
    stringstream line1(v1),line2(v2);//I am using stringstream so I can use getline
    string value;
        
    while(getline(line2,value,','))
    {
        value.erase(remove(value.begin(), value.end(), ' '), value.end()); // remove all spaces in do not cares
        int num = stoi(value.substr(1));  // get the numeric value
               if (num < 0 || num >= (1 << size)) {
                   throw std::out_of_range("DoNotCare value " + to_string(num) + " is out of range for " + to_string(size) + " variables.");
               }//checks for if the number read is not in the range
        value = bitset<20>(stoi(value.substr(1))).to_string().substr(20 - size); // convert to binary with leading zeros
        doNotCares.push_back(value);
    }

    if(m=="m"){//if it is minterm
        while(getline(line1,value,','))
        {
            value.erase(remove(value.begin(), value.end(), ' '), value.end()); // remove all spaces in minterms
            int num = stoi(value.substr(1));
                        if (num < 0 || num >= (1 << size)) {
                            throw std::out_of_range("Minterm value " + to_string(num) + " is out of range for " + to_string(size) + " variables.");
                        }//checks for if the number read is not in the range
            value = bitset<20>(stoi(value.substr(1))).to_string().substr(20 - size); // convert to binary with leading zeros
            minterms.push_back(value);
        }
    }
    else if(m=="M"){//if it is maxterm
        convert_max_to_min(v1);
    }
    else{
        throw std::runtime_error("Unknown if numbers are minterms or maxterms.");
    }
}


QM::~QM(){
    minterms.clear();
}

void QM::convert_max_to_min(string line){
    stringstream s(line);
    vector <int> max; //vectors that stores the numbers that are maxterms
    string value;
    
    while(getline(s,value,',')){
        value.erase(remove(value.begin(), value.end(), ' '), value.end());
        max.push_back(stoi(value.substr(1)));//gets the number of the maxterms
    }
    
    for(int i=0;i<pow(2,size);i++){
        string binary_i = bitset<20>(i).to_string().substr(20 - size);//this converts the number to binary so that I can compare it with the numbers in do not care
        
        auto it1 =find(max.begin(), max.end(), i);//checks the location of the number in max
        auto it2 = find(doNotCares.begin(), doNotCares.end(), binary_i); //checks the location of the number in doNotCares

        if(it1==max.end() && it2==doNotCares.end()){ //if the number does not exist in maxterm or do not care then it is a minterm{convert_num_to_binary(to_string(i),false);
            minterms.push_back(binary_i);
        }
    }
}

void QM::createFirstColumn(vector<vector<string>>& groups){
        
    if (minterms.empty() && doNotCares.empty()) return; //nothing there

    int inputSize = !minterms.empty() ? minterms[0].size() : doNotCares[0].size();
    //get input size by checking the size of the first element

    vector<string> allTerms = minterms; // create a vector of all terms to put minterms and dont cares together
    allTerms.insert(allTerms.end(), doNotCares.begin(), doNotCares.end());

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

vector<string> QM::combineMinterms(string term1, string term2) { //combine minterms that only differ by 1 bit (coloumn 2)
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



vector<string> QM::generatePI() {
   
    // int inputSize = minterms.empty() ? 0 : minterms[0].size(); // get input size

    vector<vector<string>> groups(size + 1);
    vector<string> primeImplicants;

    createFirstColumn(groups);

    // flatten all groups into a vector (single list) instead of a vector of vectors so we can
    // process them easier in the while loop
    // vector<string> current;
    // for (int i = 0; i < groups.size(); i++) {
    //     for (int j = 0; j < groups[i].size(); j++) {
    //         current.push_back(groups[i][j]);
    //     }
    // }

    // loop until no more combinations possible to get unused terms (pis)
    while (true) {
        vector<vector<string>> newGroups(size + 1);
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

        // anything not used this round os a prime implicant
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

    // before returning lets check for duplicate terms
    
    for (int i = 0; i < primeImplicants.size(); ++i) {
    bool exists = false;
        for (int j = 0; j < PI.size(); ++j) {
            if (PI[j] == primeImplicants[i]) {
                exists = true;
            }
    }
    if (!exists) PI.push_back(primeImplicants[i]);
}
return PI;
    
}

bool QM::generateEPI(){
    bool returnValue = false;

       // Create coverage chart with an extra row and column for headers
       vector<vector<string>> chart(PI.size() + 1, vector<string>(minterms.size() + 1, "0"));

       // Fill first row (minterm headers) and first column (PI headers)
       for (int i = 0; i < PI.size(); i++)
       {
           chart[i + 1][0] = PI[i]; // row header
       }
       for (int j = 0; j < minterms.size(); j++)
       {
           string s = minterms[j];
           auto it2 = find(doNotCares.begin(), doNotCares.end(), s);
           if (it2 == doNotCares.end())
           {
               chart[0][j + 1] = s; // column header
           }
       }//full coverage chart is created and all is initialized to zero

       for (int i = 1; i < chart.size(); i++)
       {
           for (int j = 1; j < chart[0].size(); j++)
           {
               string m = chart[0][j];  // minterm
               string p = chart[i][0];  // PI

               if (isCovered(m, p))
               {
                   chart[i][j] = "1";
               }
           }
       }// Mark cells whose minterm is covered by the PI with 1


       vector<bool> essential(PI.size(), false);  // Vector identical to PI to see which ones are EPI

       for (int j = 1; j < chart[0].size(); j++)
       {
           int coverCount = 0;
           int first = -1;//to make sure it is out of the array index at first

           for (int i = 1; i < chart.size(); i++)
           {
               if (chart[i][j] == "1")
               {
                   coverCount++;
                   if (coverCount == 1)
                       first = i;
               }
           }//find first minterm that covers the PI

           if (coverCount == 1 && first != -1)
           {
               essential[first - 1] = true;//adjusting index since the chart rows start at 1 and 0 like the vectors
               returnValue = true;
           }
       }//If the minterms is covered exactly once then it is a EPI

       for (int i = 0; i < PI.size(); i++)
       {
           if (essential[i])
           {
               string essentialPI = PI[i];

               for (int j = 0; j < minterms.size(); j++)
               {
                   if (isCovered(minterms[j], essentialPI))
                   {
                       minterms.erase(minterms.begin() + j);
                       j--; // adjust index after erase
                   }
               }//this will remove the minterms that already covered

               EPI.push_back(essentialPI); // Move this PI to EPI vector


               PI.erase(PI.begin() + i); // remove it from PI vector

               essential.erase(essential.begin() + i);
               i--; // adjust index after erase because the vector size changed
           }
       }
       return returnValue;
   }
   


bool QM::columnDominance()
{
    bool returnValue = 0;
    vector<bitset<1050000>> coverage(minterms.size(), 0);
    for (int i = 0; i < minterms.size(); i++)
    {
        for (int j = 0; j < PI.size(); j++)
        {
            if (isCovered(minterms[i], PI[j])) coverage[i] |= (1 << j);
        }
    }
    for (int i = 0; i < minterms.size(); i++)
    {
        for (int j = i + 1; j < minterms.size(); j++)
        {
            if ((coverage[j] | ~coverage[i]).all())
            {
                returnValue = 1;
                minterms.erase(minterms.begin() + j);
                coverage.erase(coverage.begin() + j);
                j--;
            }
            else if ((coverage[i] | ~coverage[j]).all())
            {
                returnValue = 1;
                minterms.erase(minterms.begin() + i);
                coverage.erase(coverage.begin() + i);
                i--;
                break;
            }
        }
    }
    return returnValue;
}

bool QM::rowDominance()
{
    bool returnValue = 0;
    vector<bitset<1050000>> coverage(PI.size(), 0);
    for (int i = 0; i < PI.size(); i++)
    {
        for (int j = 0; j < minterms.size(); j++)
        {
            if (isCovered(minterms[j], PI[i])) coverage[i] |= (1 << j);
        }
    }
    for (int i = 0; i < PI.size(); i++)
    {
        for (int j = i + 1; j < PI.size(); j++)
        {
            if ((coverage[j] | ~coverage[i]).all())
            {
                returnValue = 1;
                PI.erase(PI.begin() + i);
                coverage.erase(coverage.begin() + i);
                i--;
                break;
            }
            else if ((coverage[i] | ~coverage[j]).all())
            {
                returnValue = 1;
                PI.erase(PI.begin() + j);
                coverage.erase(coverage.begin() + j);
                j--;
            }
        }
    }
    return returnValue;
}

void QM::generateSolutions()
{
    while(true){
        bool b1 = generateEPI();
        bool b2 = columnDominance();
        bool b3 = rowDominance();
        if(!b1 && !b2 && !b3) break;
    }
    if (minterms.size() == 0)
    {
        solutions.push_back(EPI);
        return;
    }
    vector<bitset<1050000>> coverage(PI.size(), 0);
    for (int i = 0; i < PI.size(); i++)
    {
        for (int j = 0; j < minterms.size(); j++)
        {
            if (isCovered(minterms[j], PI[i]))
                coverage[i] |= (1 << j);
        }
    }
    vector<bitset<1050000>> solutionBits;
    bitset<1050000> covered;
    for (int i = 0; i < pow(2, PI.size()); i++)
    {
        covered = 0;
        for (int j = 0; j < PI.size(); j++)
        {
            if (i & (1 << j))
                covered |= coverage[j];
            if (covered == pow(2, minterms.size()) - 1)
            {
                solutionBits.push_back(i);
                break;
            }
        }
    }
    sort(solutionBits.begin(), solutionBits.end(), [](bitset<1050000> a, bitset<1050000> b)
         { return a.count() < b.count(); });
    int min = solutionBits[0].count();
    for (int i = 0; i < solutionBits.size(); i++)
    {
        if (solutionBits[i].count() == min)
        {
            solutions.push_back(EPI);
            for (int j = 0; j < PI.size(); j++)
            {
                if (solutionBits[i][j])
                    solutions[i].push_back(PI[j]);
            }
        }
        else
            break;
    }
}

void QM::displayPI() const
{
    if(!PI.size()){cout<<"No prime implicants"<<endl;}
    cout << "Prime Implicants: ";
    for (int i = 0; i < PI.size(); i++)
    {
        if (i > 0) cout << ", ";
        char c = 'A';
        for (int j = 0; j < size; j++)
        {
            if (PI[i][j] == '1') cout<<c;
            else if (PI[i][j] == '0') cout << c << "'";
            c++;
        }
    }
    cout << endl;
}

void QM::displayEPI() const
{
    if(!EPI.size()){cout<<"No essential prime implicants"<<endl;}
    cout << "Essential Implicants: ";
    for (int i = 0; i < EPI.size(); i++)
    {
        if (i > 0) cout << ", ";
        char c = 'A';
        for (int j = 0; j < size; j++)
        {
            if (EPI[i][j] == '1') cout<<c;
            else if (EPI[i][j] == '0') cout << c << "'";
            c++;
        }
    }
    cout << endl;
}

void QM::displaySolutions() const
{
    cout << "Solutions:\n";
    for (int i = 0; i < solutions.size(); i++)
    {
        cout<<"F= ";
        for (int j = 0; j < solutions[i].size(); j++)
        {
            if (j > 0)
                cout << " + ";
            char c = 'A';
            for (int k = 0; k < size; k++)
            {
                if (solutions[i][j][k] == '1')
                    cout << c;
                else if (solutions[i][j][k] == '0')
                    cout << c << "'";
                c++;
            }
        }
        cout << endl;
    }
}

bool QM::isCovered(const string &minterm, const string &pi)
{
    for (int i = 0; i < size; i++)
    {
        if (pi[i] != '-' && pi[i] != minterm[i])
            return 0;
    }
    return 1;
}
