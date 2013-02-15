//
//  randomGenerator.cpp
//  adalina-usb
//
//  Created by Jenny Valdez on 15/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#include "randomGenerator.h"

float randomNumberBetween(float min, float max) {
    return (float)rand()/((float)RAND_MAX/(max - min)) - min
}

