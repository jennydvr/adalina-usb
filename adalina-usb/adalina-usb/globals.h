//
//  globals.h
//  adalina-usb
//
//  Created by Jenny Valdez on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#ifndef __adalina_usb__globals__
#define __adalina_usb__globals__

#include <iostream>
#include <vector>

extern bool training;
extern int numInputs;

extern int inputValues[4][2];
extern int andResults[4];

// Vector que contiene todos los casos de prueba
extern std::vector<std::vector<float>> testCases;

// Vector que contiene el valor resultante de cada caso
extern std::vector<float> testResults;

#endif /* defined(__adalina_usb__globals__) */
