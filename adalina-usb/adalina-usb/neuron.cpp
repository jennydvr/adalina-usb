//
//  neuron.cpp
//  adalina-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include "neuron.h"

Neuron::Neuron(int numW, bool randomizeW)
{
    float w = 0;
    for (int i = 0; i != numW; ++i) {
        if (randomizeW)
            w = (float)(rand())/(RAND_MAX/2) - 1;
        
        _weights.push_back(w);
        _previousWeights.push_back(0);
    }
}

void Neuron::setDelta(float value)
{
    _deltaError = _output * ( 1 - _output ) * ( value );
}

void Neuron::setWeight(float tr, std::vector<float> output)
{
    int size = (int)output.size();
    
    for (int k = 0; k != size; ++k) {
        _previousWeights[k] = tr * _deltaError * output[k];
        _weights[k] += _previousWeights[k];
    }
    
    _previousWeights[size] = tr * _deltaError;
    _weights[size] +=  _previousWeights[size];
}

float Neuron::getDelta()
{
    return _deltaError;
}

float Neuron::getOutput()
{
    return _output;
}

float Neuron::getSumDeltaWeight()
{
    float sum = 0;
    for (int k = 0; k != (int)_weights.size(); ++k)
        sum+= _deltaError * _weights[k];
    
    return sum;
}

float Neuron::getWeight(int pos)
{
    return _weights[pos];
}

float Neuron::getSumWeightWithVector(std::vector<float> output)
{
    float sum = 0;
    for (int k = 0; k != (int)output.size(); ++k)
        sum+= output[k] * _weights[k];
    
    //Bias
    sum += _weights[(int)output.size()];

    return sum;
}

void Neuron::setOutput(float output)
{
    _output = output;
}
