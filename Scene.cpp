#include "Scene.h"

float* Scene::cameraPosition = new float[3];
int* Scene::lightSourceColor = new int[3];
float* Scene::lightSourcePosition = new float[3];
int* Scene::objectColor = new int[3];
float* Scene::materialProperties = new float[4];

Scene::Scene() {
    
}

Scene::~Scene() {
    delete[] Scene::cameraPosition;
    delete[] Scene::lightSourceColor;
    delete[] Scene::lightSourcePosition;
    delete[] Scene::objectColor;
    delete[] Scene::materialProperties;
}

void Scene::setCamera(float* cameraPosition) {
    for(int i = 0; i < 3; i++) {
        Scene::cameraPosition[i] = cameraPosition[i];
    }
}

void Scene::setLight(int* lightSourceColor, float* lightSourcePosition) {
    for(int i = 0; i < 3; i++) {
        Scene::lightSourceColor[i] = lightSourceColor[i];
        Scene::lightSourcePosition[i] = lightSourcePosition[i];
    }
}

void Scene::setObject(int* objectColor, float* materialProperties) {
    for(int i = 0; i < 3; i++) {
        Scene::objectColor[i] = objectColor[i];
        Scene::materialProperties[i] = materialProperties[i];
    }
    Scene::materialProperties[3] = materialProperties[3];
}

float* Scene::getShade(float* pixelLocation, float* surfaceNormal) {
    float Ka = Scene::materialProperties[0];
    float Kd = Scene::materialProperties[1];
    float Ks = Scene::materialProperties[2];
    float alpha = Scene::materialProperties[3];
    float IaRed = (Scene::objectColor[0]) * (Scene::lightSourceColor[0])/255;
    float IaGreen = (Scene::objectColor[1]) * (Scene::lightSourceColor[1])/255;
    float IaBlue = (Scene::objectColor[2]) * (Scene::lightSourceColor[2])/255;
    float IdRed = (Scene::lightSourceColor[0]) * (objectColor[0]/255.0);
    float IdGreen = (Scene::lightSourceColor[1]) * (objectColor[1]/255.0);
    float IdBlue = (Scene::lightSourceColor[2]) * (objectColor[2]/255.0);
    float IsRed = Scene::lightSourceColor[0];
    float IsGreen = Scene::lightSourceColor[1];
    float IsBlue = Scene::lightSourceColor[2];

    int ambientRed = 0;
    int ambientGreen = 0;
    int ambientBlue = 0;
    int diffuseRed = 0;
    int diffuseGreen = 0;
    int diffuseBlue = 0;
    int specularRed = 0;
    int specularGreen = 0;
    int specularBlue = 0;

    // cout << "Camera " << Scene::cameraPosition[0] << " " << Scene::cameraPosition[1] << " " << Scene::cameraPosition[2] << endl;
    // cout << "Light " << Scene::lightSourceColor[0] << " " << Scene::lightSourceColor[1] << " " << Scene::lightSourceColor[2] << " " << Scene::lightSourcePosition[0] << " " << Scene::lightSourcePosition[1] << " " << Scene::lightSourcePosition[2] << endl;
    // cout << "Object " << Scene::objectColor[0] << " " << Scene::objectColor[1] << " " << Scene::objectColor[2] << " " << Scene::materialProperties[0] << " " << Scene::materialProperties[1] << " " << Scene::materialProperties[2] << " " << Scene::materialProperties[3] << endl;
    // cout << endl;
    // cout << "Point " << pixelLocation[0] << " " << pixelLocation[1] << " " << pixelLocation[2] << " " << surfaceNormal[0] << " " << surfaceNormal[1] << " " << surfaceNormal[2] << endl;
    float* shade = new float[3];

    // Calculate light ambient color
    // ambient absorption coefficient (Ka) * Color (R,G,B) = Ia vector
    ambientRed = Ka * IaRed;
    ambientGreen = Ka * IaGreen;
    ambientBlue = Ka * IaBlue;

    // Generate LdotN vector
    float* normalizedLightVector = new float[3];
    float* normalizedNormalVector = new float[3];

    normalizedNormalVector = normalize(surfaceNormal);
    normalizedLightVector = normalize(Scene::lightSourcePosition);
    //normalizedLightVector = Scene::lightSourcePosition;

    float LdotN = dot(normalizedLightVector, normalizedNormalVector);

    // for(int i = 0; i < 3; i++) {
    //     if(i == 0) cout << "X" << endl;
    //     else if (i == 1) cout << "Y" << endl;
    //     else cout << "Z" << endl;
    //     cout << "\tLight Vector: " << Scene::lightSourcePosition[i] << endl;
    //     cout << "\tLight Vector Magnitude: " << magnitude(Scene::lightSourcePosition) << endl;
    //     cout << "\tNormalized Light Vector: " << normalizedLightVector[i] << endl;
    //     cout << "\tNormal Vector: " << surfaceNormal[i] << endl;
    //     cout << "\tNormal Vector Magnitude: " << magnitude(surfaceNormal) << endl;
    //     cout << "\tNormalized Normal Vector: " << normalizedNormalVector[i] << endl;
    // }
    // cout << "L dot N: " << LdotN << endl;
    // cout << "Normalized Light Vector Magnitude: " << magnitude(normalizedLightVector) << endl;
    // cout << "Normalized Normal Vector Magnitude: " << magnitude(normalizedNormalVector) << endl;

    if(LdotN > 0.0) {
        // cout << "LdotN" << endl;
        // Calculate diffuse value
        diffuseRed = Kd * LdotN * IdRed;
        diffuseGreen = Kd * LdotN * IdGreen;
        diffuseBlue = Kd * LdotN * IdBlue;

        // cout << Scene::lightSourceColor[0] << " x (" << objectColor[0] << "/255) = " << IdRed << endl; 
        // cout << "Id\nR: " << IdRed << "\nG: " << IdGreen << "\nB: " << IdBlue << endl;
        // cout << "Diffuse\tR: " << diffuseRed << "\tG: " << diffuseGreen << "\tB: " << diffuseBlue << endl;
        // cout << "Ambient\tR: " << ambientRed << "\tG: " << ambientGreen << "\tB: " << ambientBlue << endl;
        
        // Generate RdotV vector
        float* reflectionVector = new float[3];
        float* viewVector = new float[3];

        // Ideal reflector vector PPT 18
        for(int i = 0; i < 3; i++) {

            reflectionVector[i] = 2 * LdotN * normalizedNormalVector[i] - normalizedLightVector[i];
        }
        reflectionVector = normalize(reflectionVector);
        for(int i = 0; i < 3; i++) {
            viewVector[i] = Scene::cameraPosition[i] - pixelLocation[i];
        }
        
        viewVector = normalize(viewVector);
        // cameraX - x
        // cameraY - y
        // cameraZ - z

        // cout << "Reflection vector: (" << reflectionVector[0] << ", " << reflectionVector[1] << ", " << reflectionVector[3] << ")\n\tMag: " << magnitude(reflectionVector) << endl;
        // cout << "View vector: (" << viewVector[0] << ", " << viewVector[1] << ", " << viewVector[2] << ")\n\tMag: " << magnitude(viewVector) << endl;

        
        float RdotV = dot(reflectionVector, viewVector);
        // cout << "R dot V: " << RdotV << endl;
        if(RdotV > 0.0) {
            //cout << "RdotV" << endl;
            // Calculate light specular value
            RdotV = pow(RdotV, alpha);
            specularRed = Ks * RdotV * IsRed;
            specularGreen = Ks * RdotV * IsGreen;
            specularBlue = Ks * RdotV * IsBlue;
            
            

        }
    }

    shade[0] = floor(ambientRed + diffuseRed + specularRed);
    shade[1] = floor(ambientGreen + diffuseGreen + specularGreen);
    shade[2] = floor(ambientBlue + diffuseBlue + specularBlue);

    return shade;

}

float Scene::dot(float a[], float b[], int vectorSize) {
    float dotResult = 0.0;
    for(int i = 0; i < vectorSize; i++) {
        dotResult += a[i] * b[i];
    }
    return dotResult;
}

float Scene::dot(int a[], int b[], int vectorSize) {
    float dotResult = 0.0;
    for(int i = 0; i < vectorSize; i++) {
        dotResult += a[i] * b[i];
    }
    return dotResult;
}

float* Scene::normalize(float* vector, int vectorSize) {
    float* normalizedVector = new float[vectorSize];
    float vectorMagnitude = magnitude(vector);
    for(int i = 0; i < vectorSize; i++) {
        normalizedVector[i] = vector[i] / vectorMagnitude;
    }
    return normalizedVector;


}

float* Scene::normalize(int* vector, int vectorSize) {
    float* normalizedVector = new float[vectorSize];
    float vectorMagnitude = magnitude(vector);
    for(int i = 0; i < vectorSize; i++) {
        normalizedVector[i] = (float)vector[i] / vectorMagnitude;
    }
    return normalizedVector;
}

float Scene::magnitude(float* vector, int vectorSize) {
    float squareSum = 0;
    for(int i = 0; i < vectorSize; i++) {
        squareSum += vector[i] * vector[i];
    }
    return sqrt(squareSum);
}

float Scene::magnitude(int* vector, int vectorSize) {
    float squareSum = 0;
    for(int i = 0; i < vectorSize; i++) {
        squareSum += vector[i] * vector[i];
    }
    return sqrt(squareSum);
}