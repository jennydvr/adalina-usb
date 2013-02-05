//
//  globals.cpp
//  adalina-usb
//
//  Created by Jenny Valdez on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#include "globals.h"

// Reference values

int inputValues[4][2] = {{1, 1}, {1, 0}, {0, 1}, {0, 0}};

int andResults[4] = {1, 0, 0, 0};
int orResults[4] = {1, 1, 1, 0};
int xorResults[4] = {0, 1, 1, 0};


// Global variables

bool training = true;
int numInputs = 2;
std::vector<int> results = std::vector<int>(andResults, andResults + 4);
