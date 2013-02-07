//
//  main.cpp
//  adalina-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include <iostream>
#include "brain.h"

using namespace std;

int main(int argc, const char * argv[])
{
    int type =  atoi(argv[5]);
    Type_Neuron tipe = NEURON;
    switch (type) {
        case 1:
            tipe = BATCH_ADALINE;
            break;
        case 2:
            tipe = INCREMENTAL_ADALINE;
        default:
            break;
    }
    Brain::Instance()->Train(atoi(argv[1]), argv[2], (float)atof(argv[3]), atoi(argv[4]),tipe);
    // Creacion de inputs - version chimba
    /*
    for (int i = 0; i != 4; ++i) {
        testCases.push_back(vector<float>(inputValues[i], inputValues[i] + 2));
        testCases[i].push_back(1);
        
        testResults.push_back(andResults[i]);
    }
    
    // Inicializacion de parametros
    Neuron neuron;
    int it = 0;
    float error = 1;
    
    while (error > 0.1 & it < 1000 * testCases.size()) {
        
        // Analisis del caso
        int numCase = it % testCases.size();
        neuron.analize(testCases[numCase], testResults[numCase]);
        
        cout << "    " << it++ << " : ";
        printf("%1.2f\n", (error = neuron.calculateError()));
    }
    
    cout << "\nResults:\n";
    cout << "   Iterations per case: " << it / testCases.size() << endl;*/
    
    return 0;
}

