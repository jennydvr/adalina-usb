//
//  main.cpp
//  adalina-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include <iostream>
#include "neuron.h"

using namespace std;

int main(int argc, const char * argv[])
{
    cout << "Hello!\nTraining for: ";
    cout << "AND\n";
    
    Neuron neuron;
    
    // Inputs - version chimba
    vector<vector<float> > input;
    
    for (int i = 0; i != 4; ++i) {
        input.push_back(vector<float>(inputValues[i], inputValues[i] + 2));
        input[i].push_back(1);
    }
    
    for (int e = 0; e != 20; ++e) {
        
        cout << e << endl;
        for (int i = 0; i != input.size(); ++i) {
            neuron.analize(input[i], results[i]);
            cout << endl;
        }
    }
    
    return 0;
}

