//
//  draftsman.h
//  adalina-usb
//
//  Created by Jenny Valdez on 15/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#ifndef __adalina_usb__draftsman__
#define __adalina_usb__draftsman__

#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include "bitmap_image.hpp"

using namespace std;
#include "matplotpp.h"
class MP :public MatPlot{
   
    
    void DISPLAY(){
        //vector<double> x(100),y(100);
      /*  x.clear();
        y.clear();
        x2.clear();
        x3.clear();
        y2.clear();
        y3.clear();
        for(int i=0;i<100;++i){
            x.push_back(0.1*i);
            y.push_back(sin(x.back()));
            if (i < 50) {
                x2.push_back(0.1*i);
                y2.push_back(sin(x[i]));
            }else
            {
                x3.push_back(0.1*i);
                y3.push_back(sin(x[i]));
            }
        }*/
        
        subplot(1,2,1);
        plot(x,y);
        // To color lines
        subplot(1,2,2);
        plot(x2,y2);set("*");set("r");//red
        plot(x3,y3);set("*");set("b");//blue
    }
public:
    
    vector<double> x;
    vector<double> y;
    
    vector<double> x2;
    vector<double> y2;
    vector<double> x3;
    vector<double> y3;
};

extern void display();
extern void reshape(int w,int h);
extern MP mp;
extern void Plotear(int argc,  char * argv[]);
extern void createBitmap(vector<vector<float>> points, vector<vector<float>> results);

#endif /* defined(__adalina_usb__draftsman__) */
