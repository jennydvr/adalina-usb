//
//  neuron.h
//  adalina-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#ifndef __adalina_usb__neuron__
#define __adalina_usb__neuron__

#include <vector>
#include <math.h>
#include <random>
#include <stdlib.h>
#include <fstream>
#include "StringHelper.h"
using namespace std;

class Neuron {

protected:
    
    //Output de la neurona
    float _output;
    
    //Error delta de la neurona
    float _deltaError;
    
    //Peso asignado a la neurona
    vector<float> _weights;
    
    //Opcional, guarda el cambio en el peso de  un frame anterior
    vector<float> _previousWeights;
    
    //Calcula la norma del vector de pesos
    float getNorm();
    
public:
    
    //Inicializa una neurona
    //  numW - numero de pesos
    //  randimizeW - activar pesos aleatorios
    Neuron(int numW, bool randomizeW);
    
    Neuron(ifstream &file);
    //Actualiza el delta de la neurona, el value depende de cada tipo de capa
    void setDelta(float value);
    
    //Actualiza los pesos
    void setWeight(float tr, float mr, std::vector<float> input);
    
    //Actualiza los pesos (inicializacion de Nguyen-Widrow)
    void NguyenWidrowInitialization(float beta);
    
    //Obtiene el delta
    float getDelta();
    
    //Obtiene el output
    float getOutput();
    
    //Reemplaza el output
    void setOutput(float output);

    // Obtiene la suma delta x pesos
    float getSumDeltaWeight();
    
    //Obtiene la sumatoria de los pesos multiplicado por el delta error
    float getSumWeightWithVector(vector<float> output);
    
    //Obtiene un peso dado
    float getWeight(int pos);
    
    void toFile(ostream &os);

};

#endif /* defined(__adalina_usb__neuron__) */
