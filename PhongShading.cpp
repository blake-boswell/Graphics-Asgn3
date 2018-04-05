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
    float Ka = PhongShading::materialProperties[0];
    float Kd = PhongShading::materialProperties[1];
    float Ks = PhongShading::materialProperties[2];
    float alpha = PhongShading::materialProperties[3];
    int IaRed = PhongShading::objectColor[0];
    int IaGreen = PhongShading::objectColor[1];
    int IaBlue = PhongShading::objectColor[2];
    int IdRed = PhongShading::lightSourceColor[0] * (objectColor[0]/255.0);
    int IdGreen = PhongShading::lightSourceColor[1] * (objectColor[1]/255.0);
    int IdBlue = PhongShading::lightSourceColor[2] * (objectColor[2]/255.0);
    int IsRed = PhongShading::lightSourceColor[0];
    int IsGreen = PhongShading::lightSourceColor[1];
    int IsBlue = PhongShading::lightSourceColor[2];

    int ambientRed = 0;
    int ambientGreen = 0;
    int ambientBlue = 0;
    int diffuseRed = 0;
    int diffuseGreen = 0;
    int diffuseBlue = 0;
    int specularRed = 0;
    int specularGreen = 0;
    int specularBlue = 0;

    cout << "Camera " << PhongShading::cameraPosition[0] << " " << PhongShading::cameraPosition[1] << " " << PhongShading::cameraPosition[2] << endl;
    cout << "Light " << PhongShading::lightSourceColor[0] << " " << PhongShading::lightSourceColor[1] << " " << PhongShading::lightSourceColor[2] << " " << PhongShading::lightSourcePosition[0] << " " << PhongShading::lightSourcePosition[1] << " " << PhongShading::lightSourcePosition[2] << endl;
    cout << "Object " << PhongShading::objectColor[0] << " " << PhongShading::objectColor[1] << " " << PhongShading::objectColor[2] << " " << PhongShading::materialProperties[0] << " " << PhongShading::materialProperties[1] << " " << PhongShading::materialProperties[2] << " " << PhongShading::materialProperties[3] << endl;
    cout << endl;
    cout << "Point " << pixelLocation[0] << " " << pixelLocation[1] << " " << pixelLocation[2] << " " << surfaceNormal[0] << " " << surfaceNormal[1] << " " << surfaceNormal[2] << endl;
    float* shade = new float[3];

    // Calculate light ambient color
    // ambient absorption coefficient (Ka) * Color (R,G,B) = Ia vector
    ambientRed = Ka * IaRed;
    ambientGreen = Ka * IaGreen;
    ambientBlue = Ka * IaBlue;

    // Generate LdotN vector
    float* normalizedLightVector = new float[3];
    float* normalizedNormalVector = new float[3];

    normalizedLightVector = normalize(PhongShading::lightSourcePosition);

    float LdotN = dot(normalizedLightVector, surfaceNormal);

    for(int i = 0; i < 3; i++) {
        if(i == 0) cout << "X" << endl;
        else if (i == 1) cout << "Y" << endl;
        else cout << "Z" << endl;
        cout << "\tLight Vector: " << PhongShading::lightSourcePosition[i] << endl;
        cout << "\tLight Vector Magnitude: " << PhongShading::lightSourcePosition[i]/normalizedLightVector[i] << endl;
        cout << "\tNormalized Light Vector: " << normalizedLightVector[i] << endl;
        cout << "\tNormal Vector: " << surfaceNormal[i] << endl;
        cout << "\tNormal Vector Magnitude: " << surfaceNormal[i]/surfaceNormal[i] << endl;
        // cout << "\tNormalized Normal Vector: " << surfaceNormal[i] << endl;
    }
    cout << "L dot N: " << LdotN << endl;
    cout << "Normalized Light Vector Magnitude: " << magnitude(normalizedLightVector) << endl;
    cout << "Normalized Normal Vector Magnitude: " << magnitude(surfaceNormal) << endl;

    if(LdotN > 0.0) {
        cout << "LdotN" << endl;
        // Calculate diffuse value
        diffuseRed = Kd * LdotN * IdRed;
        diffuseGreen = Kd * LdotN * IdGreen;
        diffuseBlue = Kd * LdotN * IdBlue;

        cout << PhongShading::lightSourceColor[0] << " x (" << objectColor[0] << "/255) = " << IdRed << endl; 
        cout << "Id\nR: " << IdRed << "\nG: " << IdGreen << "\nB: " << IdBlue << endl;
        cout << "Diffuse\nR: " << diffuseRed << "\nG: " << diffuseGreen << "\nB: " << diffuseBlue << endl;
        cout << "Ambient\nR: " << ambientRed << "\nG: " << ambientGreen << "\nB: " << ambientBlue << endl;
        
        // Generate RdotV vector
        float* reflectionVector = new float[3];
        float* viewVector = new float[3];

        // Ideal reflector vector PPT 18
        for(int i = 0; i < 3; i++) {

            reflectionVector[i] = 2 * LdotN * pixelLocation[i] - PhongShading::lightSourcePosition[i];
        }
        reflectionVector = normalize(reflectionVector);
        viewVector = normalize(PhongShading::cameraPosition);

        
        float RdotV = dot(reflectionVector, viewVector);
        if(RdotV > 0.0) {
            cout << "RdotV" << endl;
            // Calculate light specular value
            float Ks = PhongShading::materialProperties[2];
            RdotV = pow(RdotV, PhongShading::materialProperties[3]);
            specularRed = Ks * RdotV * IsRed;
            specularGreen = Ks * RdotV * IsGreen;
            specularBlue = Ks * RdotV * IsBlue;
            
            

        }
    }

    shade[0] = ambientRed + diffuseRed + specularRed;
    shade[1] = ambientGreen + diffuseGreen + specularGreen;
    shade[2] = ambientBlue + diffuseBlue + specularBlue;

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