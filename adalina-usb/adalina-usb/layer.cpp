//
//  layer.cpp
//  adalina-usb
//
//  Created by Luis Alejandro Vieira on 12/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#include "layer.h"

Layer::Layer()
{
    
}

void Layer::setDeltas(std::vector<float> expectedResult)
{
    switch (_type) {
        case HIDDEN_LAYER:
            for (int i =0; i<(int)_neurons.size(); i++) {
                _neurons[i].setDelta(_neurons[i].getSumDeltaWeight());
            }
            break;
            
        case OUTPUT_LAYER:
            for (int i =0; i<(int)_neurons.size(); i++) {
                _neurons[i].setDelta(expectedResult[i] - _neurons[i].getOutput());
            }
            break;
            
        case INPUT_LAYER:
            
            break;
    }
}