//
//  main.cpp
//  adalina-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include <iostream>
#include <limits>
#include "brain.h"

using namespace std;

int numVariables, minimo, maximo;
vector<vector<float>> testCases;
vector<float> testResults;


vector<string> split(string work, char delim, int rep)
{
    vector<string> output;
    
    string buf = "";
    int i = 0;
    while (i < work.length()) {
        if (work[i] != delim)
            buf += work[i];
        else if (rep == 1) {
            output.push_back(buf);
            buf = "";
        } else if (buf.length() > 0) {
            output.push_back(buf);
            buf = "";
        }
        ++i;
    }
    if (!buf.empty())
        output.push_back(buf);
    return output;
}

void readInputs(const char * casesFile,int percent)
{
    string line;
    vector<string> strs;
    
    ifstream myfile(casesFile);
    minimo = numeric_limits<int>::max();
    maximo = numeric_limits<int>::min();
    
    if (!myfile.is_open()) {
        cout << "Unable to open file." << endl;
        exit(1);
    }
    
    while (true)
    {
        getline (myfile,line);
        if (!myfile.good())
            break;
        
        strs = split(line,',',1);
        vector<float> testValues;
        for (size_t n = 0; n != strs.size()-1; ++n)
            testValues.push_back((float)atof(strs[n].c_str()));
        
        testCases.push_back(testValues);
        testResults.push_back((float)atof(strs[strs.size()-1].c_str()));
        
        if (minimo > testResults.back())
            minimo = testResults.back();
        
        if (maximo < testResults.back())
            maximo = testResults.back();
    }
    myfile.close();
    
    //takeData(percent);
    numVariables = (int)testCases[0].size();
}

int main(int argc, const char * argv[])
{
    srand((unsigned)(time(NULL)));
    
    /*
     * numL - numero de Layer
     * sizeXL[i] - numero de Neuronas por cada layer
     * sizeWN[i] - numero de pesos de las neuronas de cada Layer
     * TR - training rate
     * MR - momentun rate
     */
    
    readInputs(argv[1], 100);
    
    int numLayers = 3;
    int nNeuronas[3] = {2, 2, 1};
    int nPesos[3] = {1, 3, 3};
    
    vector<float> results;
    results.push_back(testResults[0]);
    
    Brain::Instance()->Initiliaze(numLayers,
                                  vector<int>(nNeuronas, nNeuronas + 3),
                                  vector<int>(nPesos, nPesos + 3),
                                  0.1, 0.1);
    
    Brain::Instance()->BackPropagation(testCases[0], results);
    
    cout << Brain::Instance()->calculateMSError(results) << endl;
    
    return 0;
}

