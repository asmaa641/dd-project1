#include "coveragechart.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

CoverageChart::CoverageChart(const int &s, const vector<string> &pi, const vector<string> &minterms)
    : size(s), PI(pi), minterms(minterms)
{
    generateEPI();
    generateSolutions();
}

void CoverageChart::generateEPI()
{
    
}

void CoverageChart::generateSolutions()
{
    if (minterms.size() == 0)
    {
        solutions.push_back(EPI);
        return;
    }
    vector<int> coverage(PI.size(), 0);
    for (int i = 0; i < PI.size(); i++)
    {
        for (int j = 0; j < minterms.size(); j++)
        {
            if (isCovered(minterms[j], PI[i]))
                coverage[i] |= (1 << j);
        }
    }
    vector<int> solutionBits;
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
         { return __builtin_popcount(a) < __builtin_popcount(b); });
    int min = __builtin_popcount(solutionBits[0]);
    for (int i = 0; i < solutionBits.size(); i++)
    {
        if (__builtin_popcount(solutionBits[i]) == min)
        {
            solutions.push_back(EPI);
            for (int j = 0; j < PI.size(); j++)
            {
                if (solutionBits[i] & (1 << j))
                    solutions[i].push_back(PI[j]);
            }
        }
        else
            break;
    }
}

void CoverageChart::displayEPI() const
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

void CoverageChart::displaySolutions() const
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

bool CoverageChart::isCovered(const string &minterm, const string &pi)
{
    for (int i = 0; i < size; i++)
    {
        if (pi[i] != '-' && pi[i] != minterm[i])
            return 0;
    }
    return 1;
}