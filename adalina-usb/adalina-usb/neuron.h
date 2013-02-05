//
//  neuron.h
//  adalina-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#ifndef __adalina_usb__neuron__
#define __adalina_usb__neuron__

#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include "globals.h"

using namespace std;

class Neuron {
    
protected:
    
    vector<float> weights;
    
    float trainingRate;
    
    int calculateOutput(vector<float> input);
    
    void update(vector<float> input, int output, int real);
    
public:
    
    Neuron();
    
    int analize(vector<float> input, int real = numeric_limits<int>::max());
    
};

#endif /* defined(__adalina_usb__neuron__) */
