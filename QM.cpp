//
//  QM.cpp
//  Project 1
//
//  Created by Jumanah Moussa on 08/11/2025.
//
#include "QM.h"
#include <sstream>
#include <cmath>



QM::QM(int s,string v1,string v2){
    size=s;
    string m;
    m=v1.substr(0,1);
    stringstream line1(v1),line2(v2);//I am using stringstream so I can use getline
    string value;
    
    if(m=="m"){//if it is minterm
        while(getline(line1,value,','))
        {  value.erase(remove(value.begin(), value.end(), ' '), value.end()); // remove all spaces in minterms
            convert_num_to_binary(value.substr(1),false);} //pushes the numbers themselves
    }
    else{//if it is maxterm
        convert_max_to_min(v1);}
    
    while(getline(line2,value,','))
    {  value.erase(remove(value.begin(), value.end(), ' '), value.end()); // remove all spaces in do not cares
        convert_num_to_binary(value.substr(1),true);
    }
}


QM::~QM(){
    for(string s:minterms) //this is just to ensure that the number in the vector are right
        cout<<"Minterms:"<<s<<endl;
    for(int s:doNotCares) //this is just to ensure that the number in the vector are right
        cout<<"Do not cares:"<<s<<endl;
    for(string s:EPI) //this is just to ensure that the number in the vector are right
        cout<<"EPI:"<<s<<endl;

    
    minterms.clear();
}

void QM::convert_num_to_binary(string n,bool DNC){
    if(DNC){
        doNotCares.push_back(stoi(n));//if do not care add it to the do not care vector
        return;
    }
    
    vector <int> rem;//this will store the remainders
    int number=stoi(n);
    
    if(number == 0) {
           string zero_string(size, '0');
        minterms.push_back(zero_string);
           return;
       }
    
    while(number>0){
        rem.push_back(number%2);//converts the number into binary and stores it in reminder but in the wrong order
        number/=2;
    }//maybe instead of the two function just use a stack???
    
    string value;
    while(rem.size()>0){//this takes the numbers from the vector in the opposite order of the division
        value+=to_string(*(rem.end()-1));
        rem.pop_back();
    }
    
    while(value.length() < size) {//this part is to ensure to add remaining zeros at the beginning of the number
           value = "0" + value;
       }
    
    minterms.push_back(value);
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
        auto it1 =find(max.begin(), max.end(), i);//checks the location of the number in max
        auto it2 =find(doNotCares.begin(), doNotCares.end(), i);//checks the location of the number in do not care
       
        if(it1==max.end() && it2==doNotCares.end()) //if the number does not exist in maxterm or do not care then it is a minterm
        {convert_num_to_binary(to_string(i),false);}
    }
}

vector <string> QM::find_EPI(){
    vector<vector<string>> chart (PI.size(),vector<string>(minterms.size(),"0"));
    for(int i=0;i<PI.size();i++){
        chart[i][0]=PI[i];//we created the rows of the coverage chart
        
        for(int j=0;j<minterms.size();j++){
            string s=minterms[j];
            auto it2 =find(doNotCares.begin(), doNotCares.end(), stoi(s));
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
    
    return EPI;
}
