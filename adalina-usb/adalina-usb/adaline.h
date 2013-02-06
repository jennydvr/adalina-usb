//
//  adaline.h
//  adalina-usb
//
//  Created by Jenny Valdez on 06/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#ifndef __adalina_usb__adaline__
#define __adalina_usb__adaline__

#include <iostream>
#include "neuron.h"

class BatchAdaline : public Neuron {
    
protected:
    
    // Actualiza los pesos de acuerdo a la regla delta batch
    virtual void update(vector<float> input, float output, float real);
    
};

class IncrementalAdaline : public Neuron {
    
protected:
    
    // Actualiza los pesos de acuerdo a la regla delta incremental
    virtual void update(vector<float> input, float output, float real);
    
};

#endif /* defined(__adalina_usb__adaline__) */
