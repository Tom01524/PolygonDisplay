//
// Created by iceoc0 on 2025/9/20.
//

#ifndef POLYGONDISPLAY_EQUATION3_1_H
#define POLYGONDISPLAY_EQUATION3_1_H
#include"./equation2_4_1.h"
#include "../../polygonClass/equation/EquationThree.h"

void equation3Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 startCenter, glm::vec3 _boxLenHalf, float a,
                     float b, float c, float d, int frontColor1, int frontColor2, int frontColor3, unsigned char _debug);

void equation3Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 startCenter, glm::vec3 _boxLenHalf, float a,
                     float b, float c, float d, int frontColor1, int frontColor2, int frontColor3, unsigned char _debug){
    unique_ptr<EquationThree> equation3 = make_unique<EquationThree>(startCenter, _boxLenHalf, a, b, c, d, _debug);
    equation3->setFrontColor(frontColor1, frontColor2, frontColor3); // 1 ? 2 葵扇黄


    polygonAllPtr->push_back(std::move(equation3));
}
#endif //POLYGONDISPLAY_EQUATION3_1_H
