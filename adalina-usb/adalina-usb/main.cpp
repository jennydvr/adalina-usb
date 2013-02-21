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
vector<vector<float>> normalizedTestCases;
vector<vector<float>> testCases;
vector<vector<float>> testResults;

vector<vector<float>> normalizedControlCases;
vector<vector<float>> controlCases;
vector<vector<float>> controlResults;
vector<vector<float>> controlOutputs;

vector<float> minVal;
vector<float> maxVal;

void normalizeCases(vector<vector<float>> &cases, vector<vector<float>> &normcases)
{
    int nvar = (int)cases[0].size();
    int ncases = (int)cases.size();
    
    
    for (int i = 0; i != nvar; ++i) {
        float n = maxVal[i] - minVal[i];
        
        for (int j = 0; j != ncases; ++j)
            normcases[j][i] = (cases[j][i] - minVal[i]) / n;
    }
}

void normalizeResults(vector<vector<float>> &results)
{
    float n = maxVal[maxVal.size() - 1] - minVal[minVal.size() - 1];
    
    for (int i = 0; i != results.size(); ++i)
        results[i][0] = (results[i][0] - minVal[minVal.size() - 1]) / n;
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
        
        if (minVal.size() == 0)
            minVal = vector<float>(strs.size(), numeric_limits<float>::max());
        
        if (maxVal.size() == 0)
            maxVal = vector<float>(strs.size(), numeric_limits<float>::min());
        
        for (int i = 0; i != testValues.size(); ++i) {
            if (testValues[i] < minVal[i])
                minVal[i] = testValues[i];
            if (testValues[i] > maxVal[i])
                maxVal[i] = testValues[i];
        }

        
        cases.push_back(testValues);
        
        resultValues.push_back((float)atof(strs[strs.size()-1].c_str()));
        
        if (resultValues[0] < minVal[minVal.size() - 1])
            minVal[minVal.size() - 1] = resultValues[0];
        if (resultValues[0] > maxVal[maxVal.size() - 1])
            maxVal[maxVal.size() - 1] = resultValues[0];
        
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

void fillPlotDataError(int valorX, float valorY, float valorY1)
{
    mp.x.push_back(valorX);
    mp.y.push_back(valorY);
    mp.x1.push_back(valorX);
    mp.y1.push_back(valorY1);
}
void fillPlotDataCircle(){
    for (int i = 0; i != (int)controlCases.size(); ++i) {
        if (controlOutputs[i][0]  < 0.5) {
            mp.x2.push_back(controlCases[i][0]);
            mp.y2.push_back(controlCases[i][1]);
        }
        else
        {
            mp.x3.push_back(controlCases[i][0]);
            mp.y3.push_back(controlCases[i][1]);
        }
    }
    
}
int main(int argc,  char * argv[])
{
    srand((unsigned)(time(NULL)));
    
    readInputs(argv[1],' ',testCases, testResults);
    
   // normalizedTestCases = testCases;
   // normalizeCases(testCases, normalizedTestCases);
    normalizeResults(testResults);
    
    minVal.clear();
    maxVal.clear();
    
    
    if (argv[2] != NULL) {
        readInputs(argv[2],' ',controlCases, controlResults);
    }
    else{

        takeDataPercent(100);
    }
    
   // normalizedControlCases = controlCases;
   // normalizeCases(controlCases, normalizedControlCases);
    normalizeResults(controlResults);
    
    numVariables = (int)testCases[0].size();
    float threshold = 0.01;
    float traiRate = 0.1;
    float momentRate = 0.001;
    int numNeuHid = 10;
    int MAX_ITER = 5000;
    
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
    
    int numPlotEpoch = 20;
    int auxPlot = 0;
    
    for (epoch = 0; epoch != MAX_ITER; ++epoch) {
        
        // Entrenar
        
        for (int c = 0; c != sizeTestCases; ++c) {
            Brain::Instance()->BackPropagation(testCases[c], testResults[c]);
        }
        
        float mse = 0.0;
        for (int c = 0; c != sizeTestCases; ++c) {
            Brain::Instance()->FeedForward(testCases[c]);
            mse += Brain::Instance()->calculateMSE(testResults[c]);
        }
        mse /= sizeTestCases;
        
        
        // Probar
        /*
        for (int c = 0; c != controlCases.size(); ++c) {
            Brain::Instance()->FeedForward(controlCases[c]);
        }
        */
        float pmse = 0.0;
        for (int c = 0; c != controlCases.size(); ++c) {
            Brain::Instance()->FeedForward(controlCases[c]);

            pmse += Brain::Instance()->calculateMSE(controlResults[c]);
        }
        pmse /= controlCases.size();
        
        
        cout << epoch + 1 << "  " << mse << "  " << pmse << endl;
     
        
        
        if (auxPlot > numPlotEpoch) {
         
            fillPlotDataError(epoch+1, pmse, mse);
            auxPlot = -1;
        }
        auxPlot++;

        
        if (pmse < threshold)
            break;
    }
    
    //feedforward con los datos y luego pedir el output
    
    Brain::Instance()->toFile("pesos.txt");
    
    if (controlCases.size() > 0) {
        
        for (int i = 0; i != (int)controlCases.size(); ++i) {
            Brain::Instance()->FeedForward(controlCases[i]);
            controlOutputs.push_back( Brain::Instance()->Out());
        }
        
        fillPlotDataCircle();
        Plotear(argc, argv);
    }
    
    return 0;
}
