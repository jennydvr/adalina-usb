//
//  brain.cpp
//  adalina-usb
//
//  Created by Luis Alejandro Vieira on 06/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#include "brain.h"

Brain * Brain::instance = 0;
Brain * Brain::Instance()
{
	if(instance == 0)
	{
		instance = new Brain();
	}
	return instance;
}
void Brain::initNeuron(Type_Neuron type)
{
    switch (type) {
        case BATCH_ADALINE:
            neurons = new BatchAdaline();
            break;
        case INCREMENTAL_ADALINE:
            neurons = new IncrementalAdaline();
            break;
        default:
            neurons = new Neuron();
            break;
    }
}

void Brain::Train(int numNeurons,const char * casesFile ,float _minError, int maxIter, Type_Neuron type)
{
    //Set values for training
    isTraining = true;
    minError = _minError;
    
    cout << "Reading file: " << casesFile << endl;
    
    readInputs(casesFile);
    
    cout << "Done! Analizing..." << endl;
    
    initNeuron(type);
    
    int it = 0;
    float error = std::numeric_limits<float>::max();
    
    while (error > minError & it < maxIter * testCases.size())
    {
        // Analisis del caso
        int numCase = (int)(it % testCases.size());
        
        neurons->analize(testCases[numCase], testResults[numCase]);
        
        cout << it++ << ";";
        printf("%1.2f\n", (error = neurons->calculateError()));
    }
    
    cout << "\nResults:\n";
    printf("    Number of iterations: %d\n", it);
    printf("    Iterations per case: %1.2f\n", ((float)it / testCases.size()));
    printf("    Final error: %1.2f\n", error);
}

void Brain::readInputs(const char * casesFile)
{
    numVariables = -1;
    std::string line;
    std::vector<std::string> strs;

    ifstream myfile(casesFile);
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
            
        }
        myfile.close();
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
}
