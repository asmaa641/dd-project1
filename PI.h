//
//  PI.h
//  DD_proj1
//
//  Created by Jumanah Moussa on 04/11/2025.
//

#ifndef PI_h
#define PI_h
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class PI{
    vector <string> num;//vector that stores the numbers in the columns as binary and as string for easier comparison
    vector <int> doNotCares;//vectors that stores the numbers of the do not cares as decimal
    vector <string> EPI;
    int size;//amount of input
    void convert_num_to_binary(string n,bool isDNC);//function that converts the number into binary and stores them as strings and if do not care saves it also in do not cares vector

public:
    PI(int s,string v1,string v2);//constructor that takes the number of inputs, minterms, and do not cares calls function to convert the numbers to binary
    void convert_max_to_min(string line);//function that converts the maxterms into minterms
    vector <string> find_EPI(vector <string> primeImplicants);//function that finds EPI and returns them in as strings
    ~PI();//destructor
};
#endif
