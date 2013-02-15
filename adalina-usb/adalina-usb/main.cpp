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

int numVariables;
vector<vector<float>> testCases;
vector<vector<float>> testResults;

vector<vector<float>> controlCases;
vector<vector<float>> controlResults;


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

void readInputs(const char * casesFile)
{
    string line;
    vector<string> strs;
    
    ifstream myfile(casesFile);
    
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
        vector<float> resultValues;
        for (size_t n = 0; n != strs.size()-1; ++n)
        {
            testValues.push_back((float)atof(strs[n].c_str()));
            
        }
        
        testCases.push_back(testValues);
        
        resultValues.push_back((float)atof(strs[strs.size()-1].c_str()));
        testResults.push_back(resultValues);
        

    }
    myfile.close();
    if ((int)testCases.size() < 1)
    {
        perror("Error with input file and percent of the data" );
        exit(1);
    }
    numVariables = (int)testCases[0].size();
}

void takeDataPercent(int percent)
{
    if (percent > 100)
    {
        percent = 100;
    } else if (percent < 0)
    {
        percent = 0;
    }
    
    int awayData = ((100 - percent) * (int)testCases.size() ) / 100;
    for (int i = 0; i < awayData; i++)
    {
        controlResults.push_back(testResults.back());
        testResults.pop_back();
        controlCases.push_back(testCases.back());
        testCases.pop_back();
    }
    if ((int)testCases.size() < 1)
    {
        perror("Error with input file and percent of the data" );
        exit(1);
    }
}

int main(int argc, const char * argv[])
{
    srand((unsigned)(time(NULL)));
    
    readInputs(argv[1]);
    
    takeDataPercent(100);
    
    float threshold = 0.1;
    float traiRate = 0.1;
    float momentRate = 0.1;
    int numNeuHid = 2;
    int MAX_ITER = 10000;
    
    //---------------
    int numLayers = 3;
    int nNeuronas[3] = {numVariables, numNeuHid, 1};
    int nPesos[3] = {1, numVariables+1, numNeuHid+1};

    Brain::Instance()->Initiliaze(numLayers,
                                  vector<int>(nNeuronas, nNeuronas + 3),
                                  vector<int>(nPesos, nPesos + 3),
                                  traiRate, momentRate );
    
    int sizeTestCases = (int)testCases.size();
    for (int iter  = 0; iter < MAX_ITER; iter++) {
        int pos = iter%sizeTestCases;
        Brain::Instance()->BackPropagation(testCases[pos], testResults[pos]);
        
        if(  Brain::Instance()->calculateMSError(testResults[pos]) < threshold)
        {
            break;
        }
        
    }
    
    //feedforward con los datos y luego pedir el output
    
    //cout << Brain::Instance()->calculateMSError(results[iter%sizeTestCases]) << endl;
    
    return 0;
}

