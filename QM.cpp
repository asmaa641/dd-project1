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

using namespace std;

QM::QM(int s,string v1,string v2):size(s),minterms(),doNotCares(),PI(),EPI(),solutions(){
    string m;
    m=v1.substr(0,1);
    stringstream line1(v1),line2(v2);//I am using stringstream so I can use getline
    string value;
    
    while(getline(line2,value,','))
    {  
        value.erase(remove(value.begin(), value.end(), ' '), value.end()); // remove all spaces in do not cares
        value = bitset<20>(stoi(value.substr(1))).to_string().substr(20 - size); // convert to binary with leading zeros
        doNotCares.push_back(value);
    }

    if(m=="m"){//if it is minterm
        while(getline(line1,value,','))
        {  
            value.erase(remove(value.begin(), value.end(), ' '), value.end()); // remove all spaces in minterms
            value = bitset<20>(stoi(value.substr(1))).to_string().substr(20 - size); // convert to binary with leading zeros
            minterms.push_back(value);
        }
    }
    else{//if it is maxterm
        convert_max_to_min(v1);
    }
    
}


QM::~QM(){
    for(string s:minterms) //this is just to ensure that the number in the vector are right
        cout<<"Minterms:"<<s<<endl;
    for(string s:doNotCares) //this is just to ensure that the number in the vector are right
        cout<<"Do not cares:"<<s<<endl;
    for(string s:EPI) //this is just to ensure that the number in the vector are right
        cout<<"EPI:"<<s<<endl;

    
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
        string binary_i = bitset<20>(stoi(value.substr(1))).to_string().substr(20 - size);//this converts the number to binary so that I can compare it with the numbers in do not care
        
        auto it1 =find(max.begin(), max.end(), i);//checks the location of the number in max
        auto it2 = find(doNotCares.begin(), doNotCares.end(), binary_i); //checks the location of the number in doNotCares

        if(it1==max.end() && it2==doNotCares.end()){ //if the number does not exist in maxterm or do not care then it is a minterm{convert_num_to_binary(to_string(i),false);
            minterms.push_back(binary_i);
        }
    }
}

void QM::generateEPI(){
    vector<vector<string>> chart (PI.size(),vector<string>(minterms.size(),"0"));
    for(int i=0;i<PI.size();i++){
        chart[i][0]=PI[i];//we created the rows of the coverage chart
        
        for(int j=0;j<minterms.size();j++){
            string s=minterms[j];
            auto it2 =find(doNotCares.begin(), doNotCares.end(), s);
            if(it2==doNotCares.end()){
                chart[0][j]=s;
            }
        } //we created the columns as well
    }//full coverage chart created and initialized to zero
    
    for(int i=1;i<chart.size();i++){
        int comp=0;
        for(int j=1;j<chart[0].size();j++){
            for(int k=0;k<4;k++){
                if(chart[0][j].substr(k,k+1)==chart[i][0].substr(k,k+1)){
                    comp++;
                }
            }
            if(comp==2){
                chart[i][j]="1";
            }
        }
    }//this part marks the minterms covered with 1
    
    for(int i=1;i<chart.size();i++){
        int count=0;
        for(int j=1;j<chart[0].size();j++){
            if(chart[i][j]=="1"){
                count++;}
        }
        if(count==1){
            EPI.push_back(chart[i][0]);}
    }//this tries to find the EPI which is a minterm is covered exactly once
}

void QM::generateSolutions()
{
    if (minterms.size() == 0) //If there are no minterms, the only solution is the set of essential prime implicants
    {
        solutions.push_back(EPI);
        return;
    }
    vector<int> coverage(PI.size(), 0); //Vector to store coverage of each prime implicant
    for (int i = 0; i < PI.size(); i++)
    {
        for (int j = 0; j < minterms.size(); j++)
        {
            if (isCovered(minterms[j], PI[i]))
                coverage[i] |= (1 << j);
        }
    }
    vector<int> solutionBits; //Vector to store bit representations of solutions
    int covered;
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
    sort(solutionBits.begin(), solutionBits.end(), [](int a, int b) 
         { return __builtin_popcount(a) < __builtin_popcount(b); }); //Sort the solution bits based on the number of prime implicants
    int min = __builtin_popcount(solutionBits[0]);
    for (int i = 0; i < solutionBits.size(); i++)
    {
        if (__builtin_popcount(solutionBits[i]) == min)
        {
            solutions.push_back(EPI);
            for (int j = 0; j < PI.size(); j++)
            {
                if (solutionBits[i] & (1 << j))
                    solutions[i].push_back(PI[j]); //Add the selected prime implicants to the solution
            }
        }
        else
            break;
    }
}

void QM::displayEPI() const
{
    cout << "Essential Implicants: ";
    for (int i = 0; i < EPI.size(); i++)
    {
        if (i > 0)
            cout << ", ";
        char c = 'A';
        for (int j = 0; j < size; j++)
        {
            if (EPI[i][j] == '1')
                cout << c;
            else if (EPI[i][j] == '0')
                cout << c << "'";
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
