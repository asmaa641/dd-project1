//
//  PI.cpp
//  DD_proj1
//
//  Created by Jumanah Moussa on 04/11/2025.
//

#include "PI.h"
#include <sstream>
#include <cmath>


PI::PI(int s,string v1,string v2){
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


PI::~PI(){
  //  for(string s:num) //this is just to ensure that the number in the vector are right
    //    cout<<s<<endl;
    num.clear();
}

void PI::convert_num_to_binary(string n,bool DNC){
    if(DNC){
        doNotCares.push_back(stoi(n));//if do not care add it to the do not care vector
    }
    
    vector <int> rem;//this will store the remainders
    int number=stoi(n);
    
    if(number == 0) {
           string zero_string(size, '0');
           num.push_back(zero_string);
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
    
    num.push_back(value);
}

void PI::convert_max_to_min(string line){
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
