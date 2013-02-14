//
//  neuron.cpp
//  adalina-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include "neuron.h"
#include <math.h>
Neuron::Neuron() {
    
    /*
    // Inicializa el vector de pesos
    weights = vector<float>(numVariables , 0.05f);
    min = 0;
    max = 1;
    // Inicializa la tasa de aprendizaje
    trainingRate = 0.1f;*/
}

Neuron::Neuron(int numW, bool randomizeW)
{
    //Ver si quito esto
    srand((unsigned)(time(NULL)));
   
    float w;
    for (int i = 0; i<numW; i++) {
        
        w = 0;
        
        if (rand) {
            w = (float)(rand())/(RAND_MAX/2) - 1;
        }
        _weights.push_back(w);
        _previousWeights.push_back(0.0);
    }
}
void Neuron::setDelta(float value)
{
    _deltaError = _output * ( 1 - _output ) * ( value );
}

void Neuron::setWeight(float tr,std::vector<float> output)
{
    int size = (int)output.size();
    for (int k = 0; k < size; k++) {
        _previousWeights[k] = tr * _deltaError * output[k];
        _weights[k] +=  _previousWeights[k] ;
    }
    
    _previousWeights[size] = tr * _deltaError ;
    _weights[size] +=  _previousWeights[size] ;
    
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
    float sum=0.0;
    for(int k=0;k < (int)_weights.size();k++){
        sum+= _deltaError * _weights[k];
    }
    
    return sum;
}

float Neuron::getWeight(int pos)
{
    return _weights[pos];
}
//Obtiene la sumatoria de los pesos multiplicado por el delta error
float Neuron::getSumWeightWithVector(std::vector<float> output)
{
    float sum=0.0;
    for(int k=0;k < (int)output.size();k++){
        sum+= output[k] * _weights[k];
    }
    //bias
    //sum+= _weights[(int)output.size()];

    return sum;
}

void Neuron::setOutput(float output)
{
    _output = output;
}
/*
Neuron::Neuron(float trainingRate) {
    // Inicializa el vector de pesos
    weights = vector<float>(numVariables , 0.05f);
    
    // Inicializa la tasa de aprendizaje
    this->trainingRate = trainingRate;
}

float Neuron::calculateOutput(vector<float> input) {
    // Output : if  Sumatoria(w[i] * x[i]) > 0  then  1  else  -1
    return inner_product(input.begin(), input.end(), weights.begin(), 0) > 0 ? max : min;
}

void Neuron::update(vector<float> input, float output, float real) {
    for (int i = 0; i != weights.size(); ++i)
        weights[i] += trainingRate * (real - output) * input[i];
}

float Neuron::analize(vector<float> input, float real) {
    // Calcula el valor de salida
    float output = calculateOutput(input);
    
    // Si la neurona esta siendo entrenada, actualiza pesos
    if (isTraining & (real != numeric_limits<double>::infinity()))
        update(input, output, real);
    
    return output;
}

float Neuron::calculateError(std::vector < std::vector <float> > cases, std::vector <float> result) {
    // Error Cuadratico Medio : Sumatoria((t[i] - o[i]) * (t[i] - o[i])) / n
    float error = 0;
    
    int numCases = (int) cases.size();
    
    for (int i = 0; i != numCases ; ++i) {
        float aux = result[i] - calculateOutput(cases[i]);
        error += aux * aux;
    }
    
    return (error / (float) numCases);
}
*/