// Author: Blake Boswell
// Header file for Scene class

// Packages for debugging
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

class Scene {
    private:
    static float* cameraPosition;
    static int* lightSourceColor;
    static float* lightSourcePosition;  
    static int* objectColor;
    static float* materialProperties;   // Ka, Kd, Ks, alpha
    float dot(float a[], float b[], int vectorSize = 3);
    float dot(int a[], int b[], int vectorSize = 3);
    float* normalize(float* vector, int vectorSize = 3);
    float* normalize(int* vector, int vectorSize = 3);
    float magnitude(float* vector, int vectorSize = 3);
    float magnitude(int* vector, int vectorSize = 3);
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
    Scene();
    ~Scene();
    static void setCamera(float* cameraPosition);
    static void setLight(int* lightSourceColor, float* lightSourcePosition);
    static void setObject(int* objectColor, float* materialProperties);
    float* getShade(float* pixelLocation, float* surfaceNormal);
};