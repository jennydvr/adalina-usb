//
//  brain.cpp
//  adalina-usb
//
//  Created by Luis Alejandro Vieira on 06/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#include "brain.h"
#include "DecimalSeparator.h"
#include <math.h>

using namespace std;

Brain * Brain::instance = 0;
Brain * Brain::Instance()
{
	if(instance == 0)
	{
		instance = new Brain();
	}
	return instance;
}

void Brain::Initiliaze( int numL, vector<int> sizeXL ,vector<int> sizeWN, float TR, float MR )
{
    _trainingRate = TR;
    _momentumRate = MR;
    
    if (numL != sizeXL.size() || numL != sizeWN.size()) {
        perror("Dont match size of the layer with the input weigth and number of neurons.");
        exit(1);
    }
    
    _layers.push_back(Layer(INPUT_LAYER, sizeWN[0], sizeXL[0]));

    for (int i = 1; i < numL-1; ++i)
        _layers.push_back(Layer(HIDDEN_LAYER, sizeWN[i], sizeXL[i]));
    
    _layers.push_back(Layer(OUTPUT_LAYER,sizeWN[numL-1], sizeXL[numL-1]));
    
    //Nguyen-Widrow initialization
    for (int i = 1; i != numL; ++i)
        _layers[i].NguyenWidrowInitialization(sizeXL[0]);
}

void Brain::Initiliaze( const char * file,int numNeuInput,int sizeWeiInput ,float TR, float MR )
{
    _trainingRate = TR;
    _momentumRate = MR;
    
    string line;
    vector<string> strs;
    
    ifstream myfile(file);
    
    if (!myfile.is_open()) {
       perror( "Unable to open file." );
        exit(1);
    }
    
    getline (myfile,line);
    int numL = (int) atoi(line.c_str());
 //   cout << "Numero de Layers: "<<numL <<endl;
    _layers.push_back(Layer(INPUT_LAYER, sizeWeiInput, numNeuInput));    
    for (int i = 0; i !=numL; ++i) {
       
        _layers.push_back(Layer(myfile));
        
    }
    
    
    myfile.close();
    
}

float activationFunction(float sum)
{
    return 1.0 / (1.0 + exp(-sum));
}

void Brain::FeedForward(vector<float> input)
{
    _layers[0].updateOutput(input, NULL);
    
    for (int i = 1; i < (int)_layers.size() ; ++i) {
        vector<float> op = _layers[i-1].getOutputs();
        _layers[i].updateOutput(op, activationFunction);
    }
}

void Brain::updateDeltas(vector<float> expectedResult )
{
     _layers[_layers.size()-1].setDeltas(expectedResult);
   
    for (int i = (int) _layers.size() - 2; i > 0 ; --i)
        _layers[i].setDeltas(_layers[i+1]);
}

void Brain::updateWeight()
{
    for (int i = 1; i < (int) _layers.size(); ++i)
        _layers[i].updateWeight(_trainingRate, _momentumRate, _layers[i-1].getOutputs());
}


void Brain::BackPropagation(vector<float> input, vector<float>expectedResult)
{
    FeedForward(input);
    updateDeltas(expectedResult);
    updateWeight();
}


float Brain::calculateMSE(vector<float> expectedOut)
{
    return _layers[(int)_layers.size() - 1].getDifference(expectedOut);
}

vector<float> Brain::Out()
{
    return _layers.back().getOutputs();
}

void Brain::toFile (const char * name)
{
    filebuf fb;
    fb.open (name,ios::out);
    ostream os(&fb);
    os << _layers.size() -1<< endl;
    for (int i =1; i != (int)_layers.size(); ++i) {
        
        _layers[i].toFile(os);
    }
    
    fb.close();
}
