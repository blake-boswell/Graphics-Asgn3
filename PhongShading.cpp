#include "PhongShading.h"

PhongShading::PhongShading() {
    this->cameraPosition = new float[3]{0.0, 0.0, 0.0};
    this->lightSourceColor = new int[3]{0, 0, 0};
    this->lightSourcePosition = new float[3]{0.0, 0.0, 0.0};
    this->objectColor = new int[3]{0, 0, 0};
    this->materialProperties = new float[4]{0.0, 0.0, 0.0, 0.0};
}

PhongShading::~PhongShading() {
    delete[] this->cameraPosition;
    delete[] this->lightSourceColor;
    delete[] this->lightSourcePosition;
    delete[] this->objectColor;
    delete[] this->materialProperties;
}

void PhongShading::setCamera(int* cameraPosition) {
    for(int i = 0; i < 3; i++) {
        this->cameraPosition[i] = cameraPosition[i];
    }
}

void PhongShading::setLight(int* lightSourceColor, float* lightSourcePosition) {
    for(int i = 0; i < 3; i++) {
        this->lightSourceColor[i] = lightSourceColor[i];
        this->lightSourcePosition[i] = lightSourcePosition[i];
    }
}

void PhongShading::setObject(int* objectColor, float* materialProperties) {
    for(int i = 0; i < 3; i++) {
        this->objectColor[i] = objectColor[i];
        this->materialProperties[i] = materialProperties[i];
    }
    this->materialProperties[3] = materialProperties[3];
}

float* PhongShading::getShade(float* pixelLocation, float* surfaceNormal) {
    int* shade = new int[3];

    // Calculate ambient color values
    // ambient absorption coefficient (Ka) * Color (R,G,B) = Ia vector
    float R = this->materialProperties[0] * this->objectColor[0];
    float G = this->materialProperties[0] * this->objectColor[1];
    float B = this->materialProperties[0] * this->objectColor[2];

    // Generate LdotN vector
    float* lightVector = new float[3];
    float* normalVector = new float[3];

    lightVector = normalize(this->lightSourcePosition);
    normalVector = normalize(surfaceNormal);

    float LdotN = dot(lightVector, normalVector);
    if(LdotN < 0.0) {
        LdotN = 0.0;
    }

    // Generate RdotV vector
    float* reflectionVector = new float[3];
    float* viewVector = new float[3];

    for(int i = 0; i < 3; i++) {
        reflectionVector[i] = 2 * LdotN * pixelLocation[i] - this->lightSourcePosition[i];
    }
    reflectionVector = normalize(reflectionVector);
    viewVector = normalize(this->cameraPosition);

    
    float RdotV = dot(reflectionVector, viewVector);
    if(RdotV < 0.0) {
        RdotV = 0.0;
    }


}

float PhongShading::dot(float a[], float b[], int vectorSize = 3) {
    float dotResult = 0.0;
    for(int i = 0; i < vectorSize; i++) {
        dotResult += a[i] * b[i];
    }
    return dotResult;
}

float PhongShading::dot(int a[], int b[], int vectorSize = 3) {
    float dotResult = 0.0;
    for(int i = 0; i < vectorSize; i++) {
        dotResult += a[i] * b[i];
    }
    return dotResult;
}

float* PhongShading::normalize(float* vector) {

}

float* PhongShading::normalize(int* vector) {

}