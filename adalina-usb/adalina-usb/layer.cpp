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

Layer::Layer(Type_Layer type, int numW, int numN)
{
    _type = type;
    
    if (type == INPUT_LAYER) {
        for (int i = 0; i != numN; ++i) {
            _neurons.push_back(Neuron(numW, false));
            _outp.push_back(0);
        }
    }
    else
    {
        for (int i = 0; i != numN; ++i) {
            _neurons.push_back(Neuron(numW, true));
            _outp.push_back(0);
        }
    }
}

Layer::Layer(ifstream &file)
{
    string line;
    getline (file,line);
    int numNeu = (int) atoi(line.c_str());
 //   cout << "Numero de Neuronas: "<<numNeu <<endl;

    for (int i = 0; i != numNeu; ++i) {
        _neurons.push_back(Neuron(file));
        _outp.push_back(0);
    }
}

void Layer::NguyenWidrowInitialization(int i) {
    float beta = 0.7 * pow(float(_neurons.size()), 1/float(i));
    
    for (int k = 0; k != _neurons.size(); ++k)
        _neurons[k].NguyenWidrowInitialization(beta);
}

float Layer::getSumWeightNeurons(int pos)
{
    float sum = 0;
    
    for (int k = 0; k != (int)_neurons.size(); ++k) {
        sum += _neurons[k].getDelta() * _neurons[k].getWeight(pos);
    }
    
    return sum;
}

void Layer::setDeltas(std::vector<float> expectedResult)
{
    for (int i = 0; i != (int)_neurons.size(); ++i) {
        _neurons[i].setDelta(expectedResult[i] - _neurons[i].getOutput());
    }
}

void Layer::setDeltas( Layer capaSig)
{
    for (int j = 0; j != (int)_neurons.size(); ++j) {
        _neurons[j].setDelta(capaSig.getSumWeightNeurons(j));
    }

}

void Layer::updateOutput(std::vector<float> outputs,float (* activationF)(float))
{
    if (activationF != NULL) {
        for (int i = 0; i != (int)_neurons.size(); ++i) {
            _neurons[i].setOutput(activationF(_neurons[i].getSumWeightWithVector(outputs)));
            _outp[i] = _neurons[i].getOutput();
        }
    }
    else
    {
        for (int i = 0; i != (int)_neurons.size(); ++i) {
            _neurons[i].setOutput(outputs[i]);
            _outp[i]= _neurons[i].getOutput();
        }
    }
}

void Layer::updateWeight(float tr, float mr, std::vector<float> outputs)
{
    for (int j = 0; j != (int)_neurons.size(); ++j)
        _neurons[j].setWeight(tr, mr, outputs);
}

std::vector<float> Layer::getOutputs()
{
    return _outp;
}

float Layer::getDifference(std::vector<float> expectedOut)
{
    float sum = 0;
    
    for (int i = 0; i != (int)_outp.size(); ++i) {
        //std::cout <<"Expec: "<< expectedOut[i]<<"      Out: "<<_outp[i] <<endl;
        float aux = _outp[i] - expectedOut[i];
        sum += aux * aux;
    }
    
    return sum;
}

void Layer::toFile( ostream &os)
{
    os << _neurons.size() << endl;
    for (int i =0; i != (int)_neurons.size(); ++i) {
        
        _neurons[i].toFile(os);
    }
    
    
}
