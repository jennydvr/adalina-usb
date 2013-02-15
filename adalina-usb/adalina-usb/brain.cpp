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
Brain * Brain::instance = 0;
Brain * Brain::Instance()
{
	if(instance == 0)
	{
		instance = new Brain();
	}
	return instance;
}

void Brain::Initiliaze( int numL, std::vector<int> sizeXL ,std::vector<int> sizeWN, float TR, float MR )
{
    _trainingRate = TR;
    _momentunRate = MR;
    
    if (numL != sizeXL.size() || numL != sizeWN.size()) {
        perror("Dont match size of the layer with the input weigth and number of neurons.");
        exit(1);
    }
    _layers.push_back(Layer(INPUT_LAYER, sizeWN[0], sizeXL[0]));

    for (int i = 1; i < numL-1; i++) {
        _layers.push_back(Layer(HIDDEN_LAYER, sizeWN[i], sizeXL[i]));
    }
    _layers.push_back(Layer(OUTPUT_LAYER,sizeWN[numL-1], sizeXL[numL-1]));
}

float activationFunction(float sum)
{
    return (1/(1+exp(-sum)));
}

void Brain::FeedForward(std::vector<float> input)
{
    _layers[0].updateOutput(input,NULL);
    
    for (int i = 1; i < (int)_layers.size(); i++) {
        
        _layers[i].updateOutput(_layers[i-1].getOutputs(),activationFunction);
    }
}

void Brain::updateDeltas(std::vector<float> expectedResult )
{
     _layers[_layers.size()-1].setDeltas(expectedResult);
   
    for (int i  = (int) _layers.size() - 2; i > 0 ; i--) {
        _layers[i].setDeltas( _layers[i+1]);
    }    
}

void Brain::updateWeight()
{
    for (int i  = 1; i < (int) _layers.size(); i++) {
        _layers[i].updateWeight(_trainingRate,_layers[i-1].getOutputs());
    }
}


void Brain::BackPropagation(std::vector<float> input, std::vector<float>expectedResult)
{
    
    FeedForward(input);
    
    updateDeltas(expectedResult );
    
    //aplicar momentums
    
    updateWeight();
}


float Brain::calculateMSError(std::vector<float> expectedResult)
{
    float mse =  _layers[(int)_layers.size()].getSquareError(expectedResult) ;

    return mse/2;
}

float Brain::Out(int pos)
{
    return _layers.back().getOutputs()[pos];;
}

/*
void Brain::initNeuron(Type_Neuron type, float _trainingRate)
{
    switch (type) {
        case BATCH_ADALINE:
            neurons = new BatchAdaline(_trainingRate);
            break;
        case INCREMENTAL_ADALINE:
            neurons = new IncrementalAdaline(_trainingRate);
            break;
        default:
            neurons = new Neuron(_trainingRate);
            break;
    }
    
    neurons->setMax(maximo);
    neurons->setMin(minimo);
}

void Brain::FirstTrain(const char * casesFile,int percent,float _trainingRate,float _minError,Type_Neuron type,int maxIter, float (*uTR)(float,int)  )
{

    isTraining = true;
    
    int it = 0;
    float error = std::numeric_limits<float>::max();
    
    readInputs(casesFile, percent);
    
    initNeuron(type, _trainingRate);
    

    int typeNeuron;
    switch (type) {
        case BATCH_ADALINE:
            typeNeuron = 1;
            break;
        case INCREMENTAL_ADALINE:
            typeNeuron = 2;
            break;
        case NEURON:
            typeNeuron = 0;
            break;
    }
    
    if (uTR)
    {
        ss << casesFile<<"_"<<typeNeuron <<"_Decay_TR_" <<neurons->getTrainingRating()<<"_perCases_"<<percent << ".csv";
    }
    else
    {
        ss << casesFile<< "_"<< typeNeuron<<"_TR_"<<neurons->getTrainingRating()<<"_perCases_"<<percent << ".csv";
 
    }
    FILE * archivo = initFile((ss.str()).c_str());
    fprintf(archivo, "TrainingData;\n");
    //------
    
    
    while (error > minError & it < maxIter * testCases.size())
    {
        // Analisis del caso
        int numCase = (int)(it % testCases.size());
        
        neurons->analize(testCases[numCase], testResults[numCase]);
        
        writeFile(archivo,it++,(error = neurons->calculateError(testCases,testResults)));
        if (uTR)
        {
            std::cout << "Iteracion: "<<it<<" TrainingRAte : "<< uTR(_trainingRate,it) << std::endl;
             neurons->setTrainingRate(uTR(_trainingRate,it));
        }
       
    }
    closeFile(archivo);
    
    isTraining = false;
}

void Brain::TestData(const char * casesFile)
{
    
    if (casesFile) {
        
    }
    if ((int)controlCases.size() < 1 || (int) controlResults.size() < 1) {
        std::cout << "No cases for test" << std::endl;
        exit(1);
    }
    
    ss<< "_PRUEBA.csv";
      FILE * archivo = initFile((ss.str()).c_str());
      fprintf(archivo, "TestData;\n");
    
    writeFile(archivo,0, neurons->calculateError(controlCases,controlResults));

    closeFile(archivo);
}

FILE * Brain::initFile(const char * name)
{
    FILE *archivo;
    archivo=fopen(name, "w+");
    
    return archivo;
}

void Brain::closeFile(FILE * archivo)
{
     fclose(archivo);
}

void Brain::writeFile( FILE * archivo,int iter, float error)
{

   
    std::stringstream ss1;
    ss1.imbue(std::locale(ss1.getloc(), new DecimalSeparator<char>(',')));
    float number = error;
    ss1 << iter <<";"<<number<<"\n";
    
    fprintf(archivo, "%s",(ss1.str()).c_str());
}

void Brain::takeData(int percent)
{
    if (percent > 100)
    {
        percent = 100;
    } else if (percent < 0)
    {
        percent = 0;
    }
    int awayData = ((100 - percent) * (int)testCases.size() ) / 100;
    for (int i = 0; i < awayData; i++)
    {
        controlResults.push_back(testResults.back());
        testResults.pop_back();
        controlCases.push_back(testCases.back());
        testCases.pop_back();
    }
    if ((int)testCases.size() < 1)
    {
        std::cout << "Error with input file and percent of the data" << std::endl;
        exit(1);
    }
}

void Brain::readInputs(const char * casesFile,int percent)
{
    numVariables = -1;
    std::string line;
    std::vector<std::string> strs;

    ifstream myfile(casesFile);
    minimo = numeric_limits<int>::max();
     maximo = numeric_limits<int>::min();
    if (myfile.is_open())
    {
        while (true)
        {
            std::getline (myfile,line);
            if (!myfile.good()) {
                break;
            }
            
            strs = split(line,',',1);
            std::vector<float> firstValues;
            for (size_t n = 0; n < strs.size()-1; n++)
            {
                firstValues.push_back((float)atof(strs[n].c_str()));
            }
            firstValues.push_back(1);
            testCases.push_back(firstValues);
            testResults.push_back((float)atof(strs[strs.size()-1].c_str()));
            
            if (minimo > testResults.back()) {
                minimo = testResults.back();
            }
            if(maximo < testResults.back())
            {
                maximo = testResults.back();
                
            }
        }
        myfile.close();
        
        takeData(percent);
        
        
        if (numVariables == -1)
        {
            numVariables = (int) testCases[0].size();
        }
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
        exit(1);
    }
}

std::vector<std::string> Brain::split(std::string work,char delim, int rep)
{
    std::vector<std::string> output;
    
    string buf = "";
    int i = 0;
    while (i < work.length()) {
        if (work[i] != delim)
            buf += work[i];
        else if (rep == 1) {
            output.push_back(buf);
            buf = "";
        } else if (buf.length() > 0) {
            output.push_back(buf);
            buf = "";
        }
        i++;
    }
    if (!buf.empty())
        output.push_back(buf);
    return output;
}*/
