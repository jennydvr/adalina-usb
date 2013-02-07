//
//  adaline.cpp
//  adalina-usb
//
//  Created by Jenny Valdez on 06/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#include "adaline.h"

void BatchAdaline::update(vector<float> input, float output, float real) {
    for (int i = 0; i != weights.size(); ++i) {
        int aux = 0;
        
        for (int j = 0; j != Brain::Instance()->getTestCases().size(); ++j)
            aux += (Brain::Instance()->getTestResult()[j] - calculateOutput(Brain::Instance()->getTestCases()[j])) * Brain::Instance()->getTestCases()[j][i];
        
        weights[i] += trainingRate * aux / 2;
    }
}

void IncrementalAdaline::update(vector<float> input, float output, float real) {
    for (int i = 0; i != weights.size(); ++i)
        weights[i] += trainingRate * (real - output) * input[i] / 2;
}
