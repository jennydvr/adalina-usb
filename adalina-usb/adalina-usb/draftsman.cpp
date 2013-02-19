//
//  draftsman.cpp
//  adalina-usb
//
//  Created by Jenny Valdez on 15/02/13.
//  Copyright (c) 2013 Jenny Valdez. All rights reserved.
//

#include "draftsman.h"

int transformToPixel(float n, int maxIndex)
{
    float diff = 20 / float(maxIndex);
    int index;
    
    for (index = 0; index != maxIndex; ++index)
        if (n < diff * float(index))
            break;
    
    return index - 1;
}

void createBitmap(vector<vector<float>> points, vector<vector<float>> results)
{
    const unsigned int dim = points.size() == 10000 ? 500 : (int)points.size() / 2;
    bitmap_image image(dim, dim);
    
    // Creo los colores
    rgb_store blue, green;
    blue.blue = 255; blue.green = 255; blue.red = 0;
    green.green = 0; green.red = 255; green.blue = 0;
    
    for (int i = 0; i != (int)points.size(); ++i) {
        
        // Hallo la correspondencia punto - pixel
        int px = transformToPixel(points[i][0], dim);
        int py = transformToPixel(points[i][1], dim);
        rgb_store col;
        
        // Reviso si el pixel no esta coloreado ya
        image.get_pixel(px, py, col.red, col.green, col.blue);
        if (col.red + col.green + col.blue != 0) {
            cout << "Pixel ya coloreado: " << px << " " << py << endl;
            continue;
        }
        
        // Coloreo de acuerdo al resultado
        col = results[i][0] < 0.5f ? blue : green;
        image.set_pixel(px, py, col.red, col.green, col.blue);
        
    }
    
    // Salvo la imagen
    image.save_image("color_map_image.bmp");
}
MP mp;
void display(){

     mp.display();
 }
 void reshape(int w,int h){

     mp.reshape(w,h);
 }

 void Plotear(int argc,  char * argv[])
{
    
    glutInit(&argc, argv);
    glutCreateWindow(100,100,800,400);
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutMainLoop();
                  
}
