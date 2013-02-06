//
//  neuron.cpp
//  adalina-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include "neuron.h"

Neuron::Neuron() {
    weights = vector<float>(numInputs + 1, 0.05f);
    trainingRate = 0.1;
}

int Neuron::calculateOutput(vector<float> input) {
    // Sum(w[i] * x[i])
    return inner_product(input.begin(), input.end(), weights.begin(), 0) > 0 ? 1 : -1;
}

void Neuron::update(vector<float> input, int output, int real) {
    // Perceptron method
    for (int i = 0; i != weights.size(); ++i)
        weights[i] += trainingRate * (real - output) * input[i];
}

int Neuron::analize(vector<float> input, int real) {
    cout << "    Weights: ";
    for (int i = 0; i != weights.size(); ++i)
        cout << weights[i] << " "; 
    cout << endl;
    
    int output = calculateOutput(input);
    
    if (training && real != numeric_limits<double>::infinity())
        update(input, output, real);
    
    cout << (output == real ? "    OK" : "    :(\n") << endl;
    
    return output;
}
