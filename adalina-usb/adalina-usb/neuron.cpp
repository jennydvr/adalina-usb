//
//  neuron.cpp
//  adalina-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include "neuron.h"

Neuron::Neuron() {
    weights = vector<float>(0.05f, numInputs + 1);
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
    int output = calculateOutput(input);
    
    if (training && real != numeric_limits<double>::infinity())
        update(input, output, real);
    
    return output;
}
