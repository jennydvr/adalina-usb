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

#include "Training.h"

using namespace std;
class Neuron {


protected:
    
    /*Cambios proyecto 2*/
    
    //Output de la neurona
    float _output;
    
    //Error delta de la neurona
    float _deltaError;
    
    //Peso asignado a la neurona
    vector<float> _weights;
    
    //Opcional, guarda el cambio en el peso de  un frame anterior
    vector<float> _previousWeights;
    

    //------
    
    /*
    int min;
    int max;
    // Vector de pesos
    vector<float> weights;
    
    // Tasa de aprendizaje
    float trainingRate;
    
    // Calcula la salida de acuerdo a la entrada y los pesos de la neurona
    virtual float calculateOutput(vector<float> input);
    
    // Actualiza los pesos de acuerdo al metodo de perceptrones
    virtual void update(vector<float> input, float output, float real);*/
    
public:
    /*Cambios proyecto 2*/
    
    //Actualiza el delta de la neurona, el value depende de cada tipo de capa
    void setDelta(float value);
    
    float getOutput();
    
    //Obtiene la sumatoria de los pesos multiplicado por el delta error
    float getSumDeltaWeight();
    //--------
    
    
    // Inicializa una neurona
    Neuron();
    /*
    Neuron(float trainingRate);
    
    float getTrainingRating()
    {
        return trainingRate;
    }
    
    void setTrainingRate(float newTR)
    {
        trainingRate = newTR;
    }
    
    void setMin(int min)
    {
        this->min = min;
    }
    void setMax(int max)
    {
        this->max = max;
    }
    
    
    // Analiza un input, y compara el output con el valor real (en caso de entrenamiento)
    float analize(vector<float> input, float real = numeric_limits<float>::max());
    
    // Calcula el error cuadratico medio
    float calculateError(std::vector < std::vector <float> > cases, std::vector <float> result);
    */
};

#endif /* defined(__adalina_usb__neuron__) */
