// Header file for PhongShading class

// Packages for debugging
#include <iostream>
#include <stdlib.h>

class PhongShading {
    private:
    static float* cameraPosition;
    static int* lightSourceColor;
    static float* lightSourcePosition;
    static int* objectColor;
    static float* materialProperties;

    public:
    PhongShading();
    ~PhongShading();
    void setCamera(int* cameraPosition);
    void setLight(int* light, float* lightSourcePosition);
    void setObject(int* objectColor, float* lightSourcePosition);
    int* getShade(int* pixelLocation, int* surfaceNormal);
}