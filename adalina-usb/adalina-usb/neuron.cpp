//
//  neuron.cpp
//  adalina-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include "neuron.h"

Neuron::Neuron() {
    // Inicializa el vector de pesos
    weights = vector<float>(numInputs + 1, 0.05f);
    
    // Inicializa la tasa de aprendizaje
    trainingRate = 0.1;
}

float Neuron::calculateOutput(vector<float> input) {
    // Output : if  Sumatoria(w[i] * x[i]) > 0  then  1  else  -1
    return inner_product(input.begin(), input.end(), weights.begin(), 0) > 0 ? 1 : -1;
}

void Neuron::update(vector<float> input, float output, float real) {
    for (int i = 0; i != weights.size(); ++i)
        weights[i] += trainingRate * (real - output) * input[i];
}

float Neuron::analize(vector<float> input, float real) {
    // Calcula el valor de salida
    float output = calculateOutput(input);
    
    // Si la neurona esta siendo entrenada, actualiza pesos
    if (training & (real != numeric_limits<double>::infinity()))
        update(input, output, real);
    
    return output;
}

float Neuron::calculateError() {
    // Error : Sumatoria((t[i] - o[i]) * (t[i] - o[i])) / 2
    float error = 0;
    
    for (int i = 0; i != testCases.size(); ++i) {
        float aux = testResults[i] - calculateOutput(testCases[i]);
        error += aux * aux;
    }
    
    return error / 2;
}
