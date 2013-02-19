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
#include "draftsman.h"
#include "randomGenerator.h"
#include "StringHelper.h"

using namespace std;

int numVariables;
vector<vector<float>> testCases;
vector<vector<float>> testResults;

vector<vector<float>> controlCases;
vector<vector<float>> controlResults;
vector<vector<float>> controlOutputs;

float minVal = numeric_limits<float>::max();
float maxVal = numeric_limits<float>::min();

void normalize(vector<vector<float>> &result)
{
    float n = maxVal - minVal;
    
    // Solo normalizar la primera (y unica) variable
    for (int i = 0; i != result.size(); ++i)
        result[i][0] = (result[i][0] - minVal) / n;
}

void readInputs(const char * casesFile,const char  separator,vector<vector<float>> &cases, vector<vector<float>> &result)
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
        
        strs = split(line,separator,1);
        vector<float> testValues;
        vector<float> resultValues;
        for (size_t n = 0; n != strs.size()-1; ++n)
        {
            testValues.push_back((float)atof(strs[n].c_str()));
            
        }
        
        cases.push_back(testValues);
        
        resultValues.push_back((float)atof(strs[strs.size()-1].c_str()));
        
        if (resultValues[0] < minVal)
            minVal = resultValues[0];
        if (resultValues[0] > maxVal)
            maxVal = resultValues[0];
        
        result.push_back(resultValues);
        

    }
    myfile.close();
    if ((int)cases.size() < 1)
    {
        perror("Error with input file and percent of the data" );
        exit(1);
    }
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
    
    readInputs(argv[1],' ',testCases, testResults);
    
    
    if (argv[2] != NULL) {
        readInputs(argv[2],' ',controlCases, controlResults);
    }
    else{

        takeDataPercent(100);
    }
    
    normalize(testResults);
    normalize(controlResults);
    
    numVariables = (int)testCases[0].size();
    float threshold = 0.01;
    float traiRate = 0.3;
    float momentRate = 0.05;
    int numNeuHid = 7;
    int MAX_ITER = 10000;
    
    //---------------
    int numLayers = 3;
    int nNeuronas[3] = {numVariables, numNeuHid, 1};
    int nPesos[3] = {1, numVariables+1, numNeuHid+1};

    vector<int> weightInput = vector<int>(nNeuronas, nNeuronas + 3);
    vector<int> neuronInput = vector<int>(nPesos, nPesos + 3);
   // if (argv[3] != NULL) {
     //   Brain::Instance()->Initiliaze(argv[3], neuronInput[0], weightInput[0], traiRate, momentRate);
    //}
    //else{
        Brain::Instance()->Initiliaze(numLayers,
                                      weightInput,
                                      neuronInput,
                                      traiRate, momentRate );
    //}
 
    
    int sizeTestCases = (int)testCases.size();
    int epoch;
    
    for (epoch = 0; epoch != MAX_ITER; ++epoch) {
        
        float mse = 0.0;
        
        for (int c = 0; c != sizeTestCases; ++c) {
            Brain::Instance()->BackPropagation(testCases[c], testResults[c]);
            mse += Brain::Instance()->calculateMSE(testResults[c]);
        }
        
        mse /= sizeTestCases;
        
        cout << epoch + 1 << ";" << mse << endl;
        
        if (mse < threshold)
            break;
    }
    
    //feedforward con los datos y luego pedir el output
    
    Brain::Instance()->toFile("pesos.txt");
    if (controlCases.size() > 0) {
        
        for (int i = 0; i != (int)controlCases.size(); i++) {
            
            Brain::Instance()->FeedForward(controlCases[i]);
            controlOutputs.push_back( Brain::Instance()->Out());
            
        }
        createBitmap(controlCases, controlOutputs);
    }
    
    
    
    return 0;
}
