//
//  main.cpp
//  adalina-usb
//
//  Created by Jenny Valdez & Luis Vieira on 05/02/13.
//  Copyright (c) 2013 Jenny Valdez & Luis Vieira. All rights reserved.
//

#include <iostream>
#include "brain.h"

using namespace std;

float updateTrainingRate(float value, int iter)
{
    return value/(float)iter;
}

int main(int argc, const char * argv[])
{
    
    int type =  atoi(argv[4]);
    Type_Neuron tipe = NEURON;
    switch (type) {
        case 1:
            tipe = BATCH_ADALINE;
            break;
        case 2:
            tipe = INCREMENTAL_ADALINE;
        default:
            break;
    }
    int percent = 100;
    if (argv[7]) {
      percent  = atoi(argv[7]);
    }
    
    
    
    if (atoi(argv[6])==1) {
        clock_t t_ini, t_fin;
        t_ini = clock();
        Brain::Instance()->FirstTrain(argv[1], percent,(float)atof(argv[2]),(float)atof(argv[3]),tipe,atoi(argv[5]),updateTrainingRate);
        t_fin = clock();
        float TiempoTotal = (float)(t_fin - t_ini) / CLOCKS_PER_SEC;
        std::cout << "Time " << tipe << " TR= "<< (float)atof(argv[2])<<" Decay : " << TiempoTotal<<std::endl;
    }
    else{
        clock_t t_ini, t_fin;
        t_ini = clock();
        Brain::Instance()->FirstTrain(argv[1], percent,(float)atof(argv[2]),(float)atof(argv[3]),tipe,atoi(argv[5]),NULL);
        t_fin = clock();
        float TiempoTotal = (float)(t_fin - t_ini) / CLOCKS_PER_SEC;
        std::cout << "Time " << tipe << " TR= "<< (float)atof(argv[2])<<" : " << TiempoTotal<<std::endl;
    }

    if (percent < 100 && percent > 0) {
        Brain::Instance()->TestData(NULL);
    }
    
    return 0;
}

