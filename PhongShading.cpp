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

}

void PhongShading::setLight(int* light, float* lightSourcePosition) {

}

void PhongShading::setObject(int* objectColor, float* materialProperties) {

}

int* PhongShading::getShade(int* pixelLocation, int* surfaceNormal) {

}