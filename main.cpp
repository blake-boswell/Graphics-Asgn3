// Author: Blake Boswell
// Synopsis: This file is used to test out the Phong Shading class

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include "Scene.h"

using namespace std;

vector<string> split(string text, string delimiter) {
    vector<string> list;
    size_t pos = 0;
    string token;
    while((pos = text.find(delimiter)) != -1) {
        token = text.substr(0, pos);
        list.push_back(token);
        text.erase(0, pos + delimiter.length());
    }
    token = text.substr(0, text.length());
    list.push_back(token);
    return list;
}

enum stringCode {
    Camera,
    Light,
    Object,
    Point
};

stringCode hashString(string const& input) {
    if(input == "Camera") {
        return Camera;
    }
    if(input == "Light") {
        return Light;
    }
    if(input == "Object") {
        return Object;
    }
    if(input == "Point") {
        return Point;
    }
}

void readFile(string filename) {
    float* cameraPosition = new float[3]{0.0, 0.0, -300.0};
    int* lightSourceColor = new int[3]{100, 100, 100};
    float* lightSourcePosition = new float[3]{.5, .5, -.7};
    int* objectColor = new int[3]{255, 255, 0};
    float* materialProperties = new float[4]{0.2, 0.4, 0.4, 2.0};
    float* pixelLocation = new float[3]{100.0, 100.0, 200.0};
    float* surfaceNormal = new float[3]{0.398925, 0.598388, -0.453324};
    Scene* p = new Scene();
    vector<string> words;
    fstream fs;
    string line;
    string delimiter = " ";
    stringCode type;

    fs.open(filename.c_str(), fstream::in);
    if(fs.is_open()) {
        while(!fs.eof()) {
            getline(fs, line);
            if(line.length() > 0) {
                words = split(line, delimiter);
                // for(int i = 0; i < words.size(); i++) {
                //     cout << "[" << i << "] " << words[i] << endl;
                // }
                type = hashString(words[0].c_str());
                switch(type) {
                    case Camera:
                        for(int i = 0; i < 3; i++) {
                            cameraPosition[i] = atof(words[i+1].c_str());
                        }
                        Scene::setCamera(cameraPosition);
                        break;
                    case Light:
                        for(int i = 0; i < 3; i++) {
                            lightSourceColor[i] = atoi(words[i+1].c_str());
                            lightSourcePosition[i] = atof(words[i+4].c_str());
                        }
                        Scene::setLight(lightSourceColor, lightSourcePosition);
                        break;
                    case Object:
                        for(int i = 0; i < 4; i++) {
                            if(i < 3) {
                                objectColor[i] = atoi(words[i+1].c_str());
                            }
                            materialProperties[i] = atof(words[i+4].c_str());
                        }
                        Scene::setObject(objectColor, materialProperties);
                        break;
                    case Point: 
                        for(int i = 0; i < 3; i++) {
                            pixelLocation[i] = atof(words[i+1].c_str());
                            surfaceNormal[i] = atof(words[i+4].c_str());
                        }
                        float* shade = p->getShade(pixelLocation, surfaceNormal);
                        cout << pixelLocation[0] << "," << pixelLocation[1] << "," << pixelLocation[2] << " " << shade[0] << "," << shade[1] << "," << shade[2] << endl; 
                }
            } 
        }
        fs.close();
    }

}

int main() {
    readFile("input.txt");

    return 0;
}