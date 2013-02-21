//
//  layer.h
//  adalina-usb
//
//  Created by Luis Alejandro Vieira on 12/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#ifndef __adalina_usb__layer__
#define __adalina_usb__layer__

#include "neuron.h"
#include <iostream>
#include <fstream>
//Este enum no es necesario, solo es prueba
enum Type_Layer {INPUT_LAYER, OUTPUT_LAYER, HIDDEN_LAYER};

class Layer
{
protected:
    
    std::vector <Neuron> _neurons;
    Type_Layer _type;
    std::vector<float> _outp;
    
public:
    
    void setDeltas(Layer capaSig);
    
    void setDeltas(std::vector<float> expectedResult);

    
    Layer();
    
    /*
     * numW - numero de pesos por neurona
     * numN - numero de Neuronas
     */
    Layer( Type_Layer type, int numW, int numN);
    
    Layer(ifstream &file);
    //Inicializa los pesos con el metodo de Nguyen-Widrow, siendo i el num de neuronas input
    void NguyenWidrowInitialization(int i);
    
    /*
     * outputs - valores asignados a cada neurona correspondiente
     */
    void updateOutput(std::vector<float> outputs, float (* activationF)(float));
    
    void updateWeight(float tr, float mr, std::vector<float> inputs);

    float getSumWeightNeurons(int pos);
    
    std::vector<float> getOutputs();
    
    // Obtiene la diferencia entre el valor esperado y el valor real (expectedOut)
    float getDifference(std::vector<float> expectedOut);
    
    void toFile( ostream &os);
    
};
#endif /* defined(__adalina_usb__layer__) */
