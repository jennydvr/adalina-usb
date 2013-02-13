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
void Neuron::setDelta(float value)
{
    _deltaError = _output * ( 1 - _output ) * ( value );
}

float Neuron::getOutput()
{
    return _output;
}

//Obtiene la sumatoria de los pesos multiplicado por el delta error
float Neuron::getSumDeltaWeight()
{
    float sum=0.0;
    for(int k=0;k < (int)_weights.size();k++){
        sum+= _deltaError * _weights[k];
    }
    
    return sum;
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