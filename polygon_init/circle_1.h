//
// Created by iceoc0 on 2025/3/15.
//

#ifndef RECTANGLEDISPLAY_CIRCLE_1_H
#define RECTANGLEDISPLAY_CIRCLE_1_H

#include"./arrow_1.h"
#ifndef CircleDemo_H
#define CircleDemo_H
#include "../polygonClass/CircleDemo.h" // wish once ONLY
#endif


// 中 750,450,200 半径 50
// 先画一个 正方 边长 100 +2 +2 = 104
CircleXYZ* CirclePos001 = new CircleXYZ({750-52,450-52,200}, // lt
                          {750+52,450-52,200}, // rt
                          {750+52,450+52,200}, // rb
                          {750-52,450+52,200}); // lb

void circleInit(vector<unique_ptr<PolygonBase>> *polygonAllPtr,CircleXYZ* _trbl,int fontColor, int backColor, bool backFont, unsigned char _debug);

void circleInit(vector<unique_ptr<PolygonBase>> *polygonAllPtr,CircleXYZ* _trbl,int fontColor, int backColor, bool backFont, unsigned char _debug){
    unique_ptr<CircleDemo> circle01 = make_unique<CircleDemo>(_trbl->ltSet, _trbl->rtSet, _trbl->rbSet, _trbl->lbSet, backFont, _debug);

    circle01->setColor(fontColor); // 青矾绿 0x78962c
    circle01->setBackColor(backColor); // 淡绿灰 0x7d8870

    polygonAllPtr->push_back(std::move(circle01));
}

#endif //RECTANGLEDISPLAY_CIRCLE_1_H
