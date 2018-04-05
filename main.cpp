// Author: Blake Boswell
// Synopsis: This file is used to test out the Phong Shading class

#include <iostream>
#include <stdlib.h>
#include "PhongShading.h"

using namespace std;

int main() {
    PhongShading* p = new PhongShading();
    float* cameraPosition = new float[3]{0.0, 0.0, -300.0};
    int* lightSourceColor = new int[3]{100, 100, 100};
    float* lightSourcePosition = new float[3]{.5, .5, -.7};
    int* objectColor = new int[3]{255, 255, 0};
    float* materialProperties = new float[4]{0.0, 0.2, 0.4, 2.0};
    p->setCamera(cameraPosition);
    p->setLight(lightSourceColor, lightSourcePosition);
    p->setObject(objectColor, materialProperties);

    float* pixelLocation = new float[3]{100.0, 100.0, 200.0};
    float* surfaceNormal = new float[3]{0.398925, 0.598388, -0.453324};
    p->getShade(pixelLocation, surfaceNormal);

    return 0;
}