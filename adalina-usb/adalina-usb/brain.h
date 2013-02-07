//
//  brain.h
//  adalina-usb
//
//  Created by Luis Alejandro Vieira on 06/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#ifndef __adalina_usb__brain__
#define __adalina_usb__brain__

#include <iostream>
#include <fstream>
#include "neuron.h"
class Neuron;

class Brain{
    
protected:
    std::vector <Neuron> neurons;
    static Brain * instance;
    
    //------- Training ------//
    int numInputs;
    float minError;
    bool isTraining;
    std::vector < std::vector <float> > testCases;
    std::vector <float> testResults;
    //------
    
    /*
        Read casesFile and get the testCases and testResults
     */
    void readInputs(const char * casesFile);
    /*
        Split a string by delim, and return a vector of string.
     ARREGLAR REDACCION
     */
    std::vector<std::string> split(std::string work,char delim, int rep);
    
public:

    static Brain * Instance();
    
    /*
     Train the brain and her neurons, by number of neurons, parser casesFile, minimun error and
     maximun of iterator.
     */
    void Train(int numNeurons, const char * casesFile ,float minError, int maxIter);
    
    /*
     Get the number of input for TestCases.
     */
    int getNumberOfInputs()
    {
        return numInputs;
    }
    
    /*
     Get if the brain is training.
     */
    bool getIsTraning()
    {
        return isTraining;
    }

    /*
     Get the cases for test in the training.
     */
    std::vector < std::vector <float> > getTestCases()
    {
        return testCases;
    }
    
    /*
     Get the result for test in the training.
     */
    std::vector <float>  getTestResult()
    {
        return testResults;
    }

};
#endif /* defined(__adalina_usb__brain__) */
