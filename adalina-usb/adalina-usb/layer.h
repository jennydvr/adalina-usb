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

//Este enum no es necesario, solo es prueba
enum Type_Layer {INPUT_LAYER, OUTPUT_LAYER, HIDDEN_LAYER};

class Layer
{
protected:
    
    std::vector <Neuron> _neurons;
    Type_Layer _type;
    
    
public:
    
    void setDeltas(std::vector<float> expectedResult);
    
    Layer();
    
};
#endif /* defined(__adalina_usb__layer__) */
