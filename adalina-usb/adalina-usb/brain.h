//
//  brain.h
//  adalina-usb
//
//  Created by Luis Alejandro Vieira on 06/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#ifndef __adalina_usb__brain__
#define __adalina_usb__brain__

#include <sstream>
#include <iostream>
#include <fstream>
#include "adaline.h"
#include "Training.h"

enum Type_Neuron { NEURON, BATCH_ADALINE , INCREMENTAL_ADALINE};
class Brain{
    
protected:
    Neuron * neurons;
    static Brain * instance;
    int minimo;
    int maximo;
    //This value not be here
    std::stringstream ss;

    /*
        Read casesFile and get the testCases and testResults
     */
    void readInputs(const char * casesFile, int percent);
    /*
        Split a string by delim, and return a vector of string.
     ARREGLAR REDACCION
     */
    std::vector<std::string> split(std::string work,char delim, int rep);
    
    /*
     Inicialize one nueron by the Type_Neuron
     */
    void initNeuron(Type_Neuron type, float _trainingRate);
  
    FILE * initFile(const char * name);
    
    void closeFile(FILE * archivo);
    
    void writeFile( FILE * archivo,int iter, float error);
    
    /*
     Remove the 100 - percent of data
     */
    void takeData(int percent);
    
public:

    static Brain * Instance();
    
    /*
     FirstTrain the brain and her neurons, by number of neurons, parser casesFile, minimun error and
     maximun of iterator. Percent take only a part of input data.
     */
    void FirstTrain( const char * casesFile, int percent, float _trainingRate,float _minError,Type_Neuron type, int maxIter,float (*uTR)(float,int));
    
    void TestData(const char * casesFile);
    


};
#endif /* defined(__adalina_usb__brain__) */
