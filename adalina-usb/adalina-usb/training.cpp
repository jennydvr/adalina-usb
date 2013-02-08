//
//  training.cpp
//  adalina-usb
//
//  Created by Luis Alejandro Vieira on 07/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#include "training.h"
int numVariables = -1;
float minError = std::numeric_limits<float>::min();
bool isTraining = false;
std::vector < std::vector <float> > testCases;
std::vector <float> testResults;
std::vector < std::vector <float> > controlCases;
std::vector <float> controlResults;
