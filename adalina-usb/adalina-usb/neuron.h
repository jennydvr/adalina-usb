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
//#include "globals.h"
#include "brain.h"

using namespace std;

class Neuron {
    
protected:
    
    // Vector de pesos
    vector<float> weights;
    
    // Tasa de aprendizaje
    float trainingRate;
    
    // Calcula la salidad de acuerdo a la entrada y los pesos de la neurona
    float calculateOutput(vector<float> input);
    
    // Actualiza los pesos
    void update(vector<float> input, float output, float real);
    
public:
    
    // Inicializa una neurona
    Neuron();
    
    // Analiza un input, y compara el output con el valor real (en caso de entrenamiento)
    float analize(vector<float> input, float real = numeric_limits<float>::max());
    
    // Calcula el error cuadratico medio
    float calculateError();
    
};

#endif /* defined(__adalina_usb__neuron__) */
