//
// Created by iceoc0 on 2026/1/17.
//

#ifndef POLYGONDISPLAY_BEZIER22EDGE3_1_H
#define POLYGONDISPLAY_BEZIER22EDGE3_1_H
#include"./equation/gamma_1.h"
#include"../polygonClass/Bezier22Edge3.h"

void Bezier223Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid,
                  unsigned char _debug_);
void Bezier223Init2(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid,
                  unsigned char _debug_);
controlPoint3D testP_1;
const glm::vec3 moved = {
    220.f,120.f,50.f
};
const glm::vec3 moved2 = {
    -320.f,80.f,50.f
};
void initPos1() {
    testP_1.tip[0] = {0.f+moved.x,0.f+moved.y,20.f+moved.z};
    testP_1.tip[1] = {-60.f+moved.x,60.f+moved.y,20.f+moved.z};
    testP_1.tip[2] = {60.f+moved.x,60.f+moved.y,20.f+moved.z};

    testP_1.edgeMid[0] = {-44.f+moved.x,16.f+moved.y,0.f+moved.z};
    testP_1.edgeMid[1] = {0.f+moved.x,74.f+moved.y,0.f+moved.z};
    testP_1.edgeMid[2] = {44.f+moved.x,16.f+moved.y,0.f+moved.z};
}
void initPos2() {

    testP_1.tip[0] = {50.f+moved.x, 20.f+moved.y, 30.f+moved.z};
    testP_1.tip[1] = {-40.f+moved.x, 70.f+moved.y, 30.f+moved.z};
    testP_1.tip[2] = {90.f+moved.x, 80.f+moved.y, 30.f+moved.z};

    testP_1.edgeMid[0] = {-20.f+moved.x, 30.f+moved.y, 40.f+moved.z};
    testP_1.edgeMid[1] = {60.f+moved.x, 90.f+moved.y, 40.f+moved.z};
    testP_1.edgeMid[2] = {70.f+moved.x, 40.f+moved.y, 40.f+moved.z};
}
void initPos3() {

    testP_1.tip[0] = {80.f+moved2.x, 20.f+moved2.y, 20.f+moved2.z};
    testP_1.tip[1] = {20.f+moved2.x, 70.f+moved2.y, 20.f+moved2.z};
    testP_1.tip[2] = {120.f+moved2.x, 110.f+moved2.y, 20.f+moved2.z};

    testP_1.edgeMid[0] = {40.f+moved2.x, 60.f+moved2.y, 70.f+moved2.z};
    testP_1.edgeMid[1] = {100.f+moved2.x, 120.f+moved2.y, 70.f+moved2.z};
    testP_1.edgeMid[2] = {140.f+moved2.x, 70.f+moved2.y, 70.f+moved2.z};
}
void Bezier223Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid,int colorBack,
    unsigned char _debug_){
    initPos1();

    unique_ptr<Bezier22Edge3> patch = make_unique<Bezier22Edge3>(testP_1,_debug_);

    patch->setColor(_colorP, _colorGrid,colorBack);

    polygonAllPtr->push_back(std::move(patch));
}
void Bezier223Init2(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid,int colorBack,
    unsigned char _debug_){
    initPos3();

    unique_ptr<Bezier22Edge3> patch = make_unique<Bezier22Edge3>(testP_1,_debug_);

    patch->setColor(_colorP, _colorGrid,colorBack);

    polygonAllPtr->push_back(std::move(patch));
}
#endif //POLYGONDISPLAY_BEZIER22EDGE3_1_H