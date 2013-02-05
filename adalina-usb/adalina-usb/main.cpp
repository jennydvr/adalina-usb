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
    
    for (int i = 0; i != 4; ++i) {
        int real = results[i];
        
        vector<float> input = vector<float>(inputValues[i], inputValues[i] + 2);
        input.push_back(1);
        
        neuron.analize(input, real);
    }
    
    return 0;
}

