//
//  training.h
//  adalina-usb
//
//  Created by Luis Alejandro Vieira on 07/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#ifndef __adalina_usb__training__
#define __adalina_usb__training__

#include <iostream>
#include <vector>
//------- Training ------//
extern int numVariables;
extern float minError;
extern bool isTraining;
extern std::vector < std::vector <float> > testCases;
extern std::vector <float> testResults;
//------

#endif /* defined(__adalina_usb__training__) */
