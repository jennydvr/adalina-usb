//
//  randomGenerator.cpp
//  adalina-usb
//
//  Created by Jenny Valdez on 15/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#include "randomGenerator.h"

using namespace std;

struct point {
    float x;
    float y;
    
    point(float mx, float my) : x(mx), y(my) {}
    
    int isInCircle() {
        return (x - 10) * (x - 10) + (y - 10) * (y - 10) <= 36 ? -1 : 1;
    }
};

vector<point> generateRandomNumbers(float min, float max, int size) {
    unsigned int seed = (unsigned int)chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(min, max);
    
    vector<point> numbers;
    
    for (int i = 0; i != size; ++i)
        numbers.push_back(point(distribution(generator), distribution(generator)));

    return numbers;
}

void generateTestCase(int size) {
    // Creo los datos
    vector<point> numbers;
    
    if (size == 10000) {
        for (int i = 0; i != 100; ++i)
            for (int j = 0; j != 100; ++j)
                numbers.push_back(point(float(i) * 0.2, float(j) * 0.2));
    } else
        numbers = generateRandomNumbers(0.0, 20.0, size);
    
    // Escribo en el archivo
    stringstream ss;
    ss << "caso_prueba_" << size << ".input";
    
    ofstream testfile;
    testfile.open(ss.str());
    
    for (int i = 0; i != size; ++i)
        testfile << numbers[i].x << " " << numbers[i].y << " " << numbers[i].isInCircle() << endl;
    
    testfile.close();
}
