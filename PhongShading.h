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
    static float* materialProperties;   // Ka, Kd, Ks, alpha
    float dot(float a[], float b[], int vectorSize = 3);
    float dot(int a[], int b[], int vectorSize = 3);
    float* normalize(float* vector);
    float* normalize(int* vector);
    // ambient absorption coefficient (Ka)
    // diffuse absorption coefficient (Kd)
    // specular absorption coefficient (Ks)
    // shininess coefficient (alpha)
    // light source ambient (Ia)
    // light source diffuse (Id)
    // light source specular (Is)
    // normal vector (N)
    // light vector (L)
    // view vector (V)
    // reflection vector (R)
    // Ip = Ka * Ia + Kd * (^L dot ^N) * Id + Ks * (^R dot ^V)^alpha * Is

    public:
    PhongShading();
    ~PhongShading();
    void setCamera(int* cameraPosition);
    void setLight(int* lightSourceColor, float* lightSourcePosition);
    void setObject(int* objectColor, float* materialProperties);
    float* getShade(float* pixelLocation, float* surfaceNormal);
}