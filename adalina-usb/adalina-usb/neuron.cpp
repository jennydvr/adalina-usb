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
    if (!randomizeW)
    {
        for (int i = 0; i != numW; ++i) {
            _weights.push_back(0);
            _previousWeights.push_back(0);
        }
    }
    else
    {
        unsigned int seed = (unsigned int)std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_real_distribution<double> distribution(-1, 1);
        
        for (int i = 0; i != numW; ++i) {
            _weights.push_back(distribution(generator));
            _previousWeights.push_back(0);
        }
    }
}

void Neuron::setDelta(float value)
{

    _deltaError = 0.5 * (1 - _output * _output) * value;
}

void Neuron::setWeight(float tr, float mr, std::vector<float> output)
{
    int size = (int)output.size();
    
    for (int k = 0; k != size; ++k) {
        _previousWeights[k] = tr * _deltaError * output[k] + mr * _previousWeights[k];
        _weights[k] += _previousWeights[k];
    }
    
    _previousWeights[size] = tr * _deltaError + mr * _previousWeights[size];
    _weights[size] +=  _previousWeights[size];
}

void Neuron::NguyenWidrowInitialization(float beta)
{
    float norm = getNorm();
    for (int k = 0; k != _weights.size(); ++k)
        _weights[k] = beta * _weights[k] / norm;
}

float Neuron::getNorm() {
    float sum = 0;
    
    for (int i = 0; i != _weights.size(); ++i)
        sum += _weights[i] * _weights[i];
    
    return sqrt(sum);
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
