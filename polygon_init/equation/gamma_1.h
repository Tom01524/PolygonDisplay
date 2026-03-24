//
// Created by iceoc0 on 2025/10/2.
//

#ifndef POLYGONDISPLAY_GAMMA_1_H
#define POLYGONDISPLAY_GAMMA_1_H
#include"./equation/equation3_9_1.h"
#include "../../polygonClass/equation/GammaComplex.h"

void gammaInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr, glm::vec3 startCenter, glm::vec3 _boxLenHalf,
               int color, unsigned char _debug);
void gammaInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr, glm::vec3 startCenter, glm::vec3 _boxLenHalf,
                   int color, unsigned char _debug){
    unique_ptr<GammaComplex> gamma = make_unique<GammaComplex>(startCenter, _boxLenHalf, _debug);
    gamma->setFrontColor(color);

    polygonAllPtr->emplace_back(std::move(gamma));
}
#endif //POLYGONDISPLAY_GAMMA_1_H
