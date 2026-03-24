//
// Created by iceoc0 on 2025/8/16.
//

#ifndef POLYGONDISPLAY_EQUATION2_1_H
#define POLYGONDISPLAY_EQUATION2_1_H

#include"../imgrect_1.h"
#include "../../polygonClass/equation/EquationTwo.h"

void equation2Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 startCenter, glm::vec3 _boxLenHalf, float a,
                   float b, float c, int frontColor1, int frontColor2, int backColor,unsigned char _debug);



void equation2Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 startCenter, glm::vec3 _boxLenHalf, float a,
                   float b, float c, int frontColor1, int frontColor2, int backColor,unsigned char _debug){


    unique_ptr<EquationTwo> equation02 = make_unique<EquationTwo>(startCenter, _boxLenHalf, a,b,c,_debug);
    equation02->setFrontColor(frontColor1,frontColor2); // 1 ? 2 葵扇黄
    equation02->setBackColor(backColor);

    polygonAllPtr->push_back(std::move(equation02));

}

#endif //POLYGONDISPLAY_EQUATION2_1_H
