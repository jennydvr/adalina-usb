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


void Brain::Train(int numNeurons,const char * casesFile ,float minError, int maxIter)
{
    //Set values for training
    isTraining = true;
    this->minError = minError;
    
    readInputs(casesFile);
    
    neurons=std::vector <Neuron>(numNeurons);
    
    int it = 0;
    float error = std::numeric_limits<float>::max();
    
    while (error > this->minError & it < maxIter * testCases.size())
    {
        // Analisis del caso
        int numCase = it % testCases.size();
        
        neurons[0].analize(testCases[numCase], testResults[numCase]);
        
        cout << "    " << it++ << " : ";
        printf("%1.2f\n", (error = neurons[0].calculateError()));
    }
    
    cout << "\nResults:\n";
    cout << "   Iterations per case: " << it / testCases.size() << endl;
    
}
void Brain::readInputs(const char * casesFile)
{
    numInputs = -1;
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
            std::cout << "\nline: "<< line<< std::endl;
            strs = split(line,',',1);
            std::vector<float> firstValues;
            for (size_t n = 0; n < strs.size()-1; n++)
            {
                std::cout << "InputValue: "<< strs[n] << std::endl;
                firstValues.push_back((float)atof(strs[n].c_str()));
            }
            testCases.push_back(firstValues);
            testResults.push_back((float)atof(strs[strs.size()-1].c_str()));
              std::cout << "ResultValue: "<< testResults[testResults.size()-1] << std::endl;
            if (numInputs == -1)
            {
                numInputs = (int) testCases.size();
            }

        }
        myfile.close();
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