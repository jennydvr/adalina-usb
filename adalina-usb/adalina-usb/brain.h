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
    

    /*
        Read casesFile and get the testCases and testResults
     */
    void readInputs(const char * casesFile);
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
public:

    static Brain * Instance();
    
    /*
     Train the brain and her neurons, by number of neurons, parser casesFile, minimun error and
     maximun of iterator.
     */
    void Train(int numNeurons, const char * casesFile , float trainingRate,float minError, int maxIter,Type_Neuron type);

};
#endif /* defined(__adalina_usb__brain__) */
