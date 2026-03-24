//
// Created by iceoc0 on 2025/8/31.
//

#ifndef POLYGONDISPLAY_EQUATION3_9_1_H
#define POLYGONDISPLAY_EQUATION3_9_1_H
#include"../polygon_init/equation/equation3_1.h"
#include "../../polygonClass/equation/EquationThree9.h"
void equation3_9Init(vector<unique_ptr<PolygonBase>> *polygonAllPtr, glm::vec3 startCenter, glm::vec3 _boxLenHalf, float a,
                     float b, float c, float d, int frontColor1, int frontColor2, int frontColor3, unsigned char _debug);

void equation3_9Init(vector<unique_ptr<PolygonBase>> *polygonAllPtr, glm::vec3 startCenter, glm::vec3 _boxLenHalf, float a,
                     float b, float c, float d, int frontColor1, int frontColor2, int frontColor3, unsigned char _debug){
    unique_ptr<EquationThree9> equation3_9 = make_unique<EquationThree9>(startCenter,
        _boxLenHalf, a,b,c,d,_debug);
    equation3_9->setFrontColor(frontColor1, frontColor2, frontColor3); // 1 ? 2 葵扇黄


    polygonAllPtr->push_back(std::move(equation3_9));
}

#endif //POLYGONDISPLAY_EQUATION3_9_1_H
