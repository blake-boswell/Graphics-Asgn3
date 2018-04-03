#include "PhongShading.h"

PhongShading::PhongShading() {
    this->cameraPosition = NULL;
    this->lightSourceColor = NULL;
    this->lightSourcePosition = NULL;
    this->objectColor = NULL;
    this->materialProperties = NULL;
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

int* PhongShading::getShade(int* pixelLocation, int* surfaceNormal) {

}