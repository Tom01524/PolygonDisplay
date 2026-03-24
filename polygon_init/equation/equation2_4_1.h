//
// Created by iceoc0 on 2025/8/23.
//

#ifndef POLYGONDISPLAY_EQUATION2_4_1_H
#define POLYGONDISPLAY_EQUATION2_4_1_H
#include"equation2_1.h"
#include "../../polygonClass/equation/EquationTwo4.h"

void equation2_4Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 startCenter, glm::vec3 _boxLenHalf, float a,
                   float b, float c, int frontColor1, int frontColor2, int backColor,unsigned char _debug);



void equation2_4Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 startCenter, glm::vec3 _boxLenHalf, float a,
                   float b, float c, int frontColor1, int frontColor2, int backColor,unsigned char _debug){


    unique_ptr<EquationTwo4> equation2_4 = make_unique<EquationTwo4>(startCenter, _boxLenHalf, a,b,c,_debug);
    equation2_4->setFrontColor(frontColor1,frontColor2); // 1 ? 2 葵扇黄
    equation2_4->setBackColor(backColor);

    polygonAllPtr->push_back(std::move(equation2_4));

}

#endif //POLYGONDISPLAY_EQUATION2_4_1_H
