//
//  brain.cpp
//  adalina-usb
//
//  Created by Luis Alejandro Vieira on 06/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#include "brain.h"
#include "DecimalSeparator.h"
Brain * Brain::instance = 0;
Brain * Brain::Instance()
{
	if(instance == 0)
	{
		instance = new Brain();
	}
	return instance;
}
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
}

void Brain::Train(int numNeurons,const char * casesFile , float _trainingRate ,float _minError, int maxIter, Type_Neuron type)
{
    //Set values for training
    isTraining = true;
    minError = _minError;
    
    cout << "Reading file: " << casesFile << endl;
    
    readInputs(casesFile);
    
    cout << "Done! Analizing..." << endl;
    
    initNeuron(type, _trainingRate);
    
    int it = 0;
    float error = std::numeric_limits<float>::max();
    

    std::stringstream ss;
    ss << casesFile<<"_"<<_trainingRate << ".csv";

    FILE * archivo = initFile((ss.str()).c_str());
    while (error > minError & it < maxIter * testCases.size())
    {
        // Analisis del caso
        int numCase = (int)(it % testCases.size());
        
        neurons->analize(testCases[numCase], testResults[numCase]);
        
        writeFile(archivo,it++,(error = neurons->calculateError()));

    }
    closeFile(archivo);
    cout << "\nResults:\n";
    printf("    Number of iterations: %d\n", it);
    printf("    Iterations per case: %1.2f\n", ((float)it / testCases.size()));
    printf("    Final error: %1.2f\n", error);
}

FILE * Brain::initFile(const char * name)
{
    FILE *archivo;
    archivo=fopen(name, "w");
    
    return archivo;
}

void Brain::closeFile(FILE * archivo)
{
     fclose(archivo);
}

void Brain::writeFile( FILE * archivo,int iter, float error)
{
    /*El manejador de archivo*/
   
    std::stringstream ss1;
    ss1.imbue(std::locale(ss1.getloc(), new DecimalSeparator<char>(',')));
    float number = error;
    ss1 << iter <<";"<<number<<"\n";
    
    fprintf(archivo, "%s",(ss1.str()).c_str());
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
