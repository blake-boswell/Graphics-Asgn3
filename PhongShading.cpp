#include "PhongShading.h"

float* PhongShading::cameraPosition = new float[3];
int* PhongShading::lightSourceColor = new int[3];
float* PhongShading::lightSourcePosition = new float[3];
int* PhongShading::objectColor = new int[3];
float* PhongShading::materialProperties = new float[4];

PhongShading::PhongShading() {
    
}

PhongShading::~PhongShading() {
    delete[] PhongShading::cameraPosition;
    delete[] PhongShading::lightSourceColor;
    delete[] PhongShading::lightSourcePosition;
    delete[] PhongShading::objectColor;
    delete[] PhongShading::materialProperties;
}

void PhongShading::setCamera(float* cameraPosition) {
    for(int i = 0; i < 3; i++) {
        PhongShading::cameraPosition[i] = cameraPosition[i];
    }
}

void PhongShading::setLight(int* lightSourceColor, float* lightSourcePosition) {
    for(int i = 0; i < 3; i++) {
        PhongShading::lightSourceColor[i] = lightSourceColor[i];
        PhongShading::lightSourcePosition[i] = lightSourcePosition[i];
    }
}

void PhongShading::setObject(int* objectColor, float* materialProperties) {
    for(int i = 0; i < 3; i++) {
        PhongShading::objectColor[i] = objectColor[i];
        PhongShading::materialProperties[i] = materialProperties[i];
    }
    PhongShading::materialProperties[3] = materialProperties[3];
}

float* PhongShading::getShade(float* pixelLocation, float* surfaceNormal) {
    float* shade = new float[3];

    // Calculate ambient color values
    // ambient absorption coefficient (Ka) * Color (R,G,B) = Ia vector
    // float R = PhongShading::materialProperties[0] * PhongShading::objectColor[0];
    // float G = PhongShading::materialProperties[0] * PhongShading::objectColor[1];
    // float B = PhongShading::materialProperties[0] * PhongShading::objectColor[2];

    // Generate LdotN vector
    float* normalizedLightVector = new float[3];
    float* normalizedNormalVector = new float[3];

    normalizedLightVector = normalize(PhongShading::lightSourcePosition);
    normalizedNormalVector = normalize(surfaceNormal);

    float LdotN = dot(normalizedLightVector, normalizedNormalVector);

    for(int i = 0; i < 3; i++) {
        if(i == 0) cout << "X" << endl;
        else if (i == 1) cout << "Y" << endl;
        else cout << "Z" << endl;
        cout << "\tLight Vector: " << PhongShading::lightSourcePosition[i] << endl;
        cout << "\tLight Vector Magnitude: " << PhongShading::lightSourcePosition[i]/normalizedLightVector[i] << endl;
        cout << "\tNormalized Light Vector: " << normalizedLightVector[i] << endl;
        cout << "\tNormal Vector: " << surfaceNormal[i] << endl;
        cout << "\tNormal Vector Magnitude: " << surfaceNormal[i]/normalizedNormalVector[i] << endl;
        cout << "\tNormalized Normal Vector: " << normalizedNormalVector[i] << endl;
    }
    cout << "L dot N: " << LdotN << endl;
    cout << "Normalized Light Vector Magnitude: " << magnitude(normalizedLightVector) << endl;
    cout << "Normalized Normal Vector Magnitude: " << magnitude(normalizedNormalVector) << endl;

    if(LdotN < 0.0) {
        LdotN = 0.0;
    }

    // Generate RdotV vector
    float* reflectionVector = new float[3];
    float* viewVector = new float[3];

    for(int i = 0; i < 3; i++) {
        reflectionVector[i] = 2 * LdotN * pixelLocation[i] - PhongShading::lightSourcePosition[i];
    }
    reflectionVector = normalize(reflectionVector);
    viewVector = normalize(PhongShading::cameraPosition);

    
    float RdotV = dot(reflectionVector, viewVector);
    if(RdotV < 0.0) {
        RdotV = 0.0;
    }

    return shade;

}

float PhongShading::dot(float a[], float b[], int vectorSize) {
    float dotResult = 0.0;
    for(int i = 0; i < vectorSize; i++) {
        dotResult += a[i] * b[i];
    }
    return dotResult;
}

float PhongShading::dot(int a[], int b[], int vectorSize) {
    float dotResult = 0.0;
    for(int i = 0; i < vectorSize; i++) {
        dotResult += a[i] * b[i];
    }
    return dotResult;
}

float* PhongShading::normalize(float* vector, int vectorSize) {
    float* normalizedVector = new float[vectorSize];
    float vectorMagnitude = magnitude(vector);
    for(int i = 0; i < vectorSize; i++) {
        normalizedVector[i] = vector[i] / vectorMagnitude;
    }
    return normalizedVector;


}

float* PhongShading::normalize(int* vector, int vectorSize) {
    float* normalizedVector = new float[vectorSize];
    float vectorMagnitude = magnitude(vector);
    for(int i = 0; i < vectorSize; i++) {
        normalizedVector[i] = (float)vector[i] / vectorMagnitude;
    }
    return normalizedVector;
}

float PhongShading::magnitude(float* vector, int vectorSize) {
    float squareSum = 0;
    for(int i = 0; i < vectorSize; i++) {
        squareSum += vector[i] * vector[i];
    }
    return sqrt(squareSum);
}

float PhongShading::magnitude(int* vector, int vectorSize) {
    float squareSum = 0;
    for(int i = 0; i < vectorSize; i++) {
        squareSum += vector[i] * vector[i];
    }
    return sqrt(squareSum);
}