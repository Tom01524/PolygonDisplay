//
// Created by iceoc0 on 2025/4/11.
//

#ifndef POLYGONDISPLAY_SPHERE_1_H
#define POLYGONDISPLAY_SPHERE_1_H

#include "circle_1.h"

#include "../polygonClass/SphereDemo.h"

// 边长 150
glm::vec3 sphereGo = {-350.f,0.f,0.f};
glm::vec3 sphereGo2 = {-350.f,0.f,200.f};
CubeBoxXYZ_ SpherePos001 = CubeBoxXYZ_( // O X Y Z
        glm::vec3{450.f,50.f,100.f}+sphereGo,glm::vec3{600.f,50.f,100.f}+sphereGo,
        glm::vec3{450.f,300.f,100.f}+sphereGo, glm::vec3{450.f,50.f,250.f}+sphereGo); // 后方
CubeBoxXYZ_ SpherePos002 = CubeBoxXYZ_(
        glm::vec3{405.f,50.f,105.f}+sphereGo2, // O 包围盒左上角坐标点
        glm::vec3{645.f,50.f,105.f}+sphereGo2, // x
        glm::vec3{405.f,390.f,105.f}+sphereGo2, // y
        glm::vec3{405.f,50.f,345.f}+sphereGo2); // z
void sphereInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr,glm::vec3 ltn,glm::vec3 rtn,glm::vec3 lbn,glm::vec3 ltf,int frontColor1,int frontColor2,
                int backColor,  unsigned char _debug);
void sphereImgInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr,glm::vec3 ltn,glm::vec3 rtn,glm::vec3 lbn,glm::vec3 ltf,
                   int frontColor1,int frontColor2, int backColor, string _path, unsigned char _debug);
glm::vec3 goDirectionAfter(glm::vec3 _start, goLine32 _dir, float _step);
void sphereInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr,glm::vec3 ltn,glm::vec3 rtn,glm::vec3 lbn,glm::vec3 ltf,int frontColor1,int frontColor2,
                int backColor,  unsigned char _debug){
    goLine32 boxGoX = ScreenDemo::get_AgoB_direction3D(ltn,rtn);
    goLine32 boxGoY = ScreenDemo::get_AgoB_direction3D(ltn,lbn);
    goLine32 boxGoZ = ScreenDemo::get_AgoB_direction3D(ltn,ltf);

    float boxLenX = glm::distance(ltn,rtn);
    float boxLenY = glm::distance(ltn,lbn);
//    float boxLenZ = ScreenDemo::distanceOfPoint3D(ltn,ltf);

    glm::vec3 rbn = goDirectionAfter(rtn,boxGoY,boxLenY);

    glm::vec3 rtf = goDirectionAfter(ltf,boxGoX,boxLenX);
    glm::vec3 rbf = goDirectionAfter(rtf,boxGoY,boxLenY);
    glm::vec3 lbf = goDirectionAfter(ltf,boxGoY,boxLenY);

    unique_ptr<SphereDemo> sphere01 = make_unique<SphereDemo>(ltn, rtn, rbn, lbn,
                                          ltf, rtf, rbf, lbf, _debug);
    sphere01->setFrontColor(frontColor1,frontColor2); // 1 ? 2 葵扇黄
    sphere01->setBackColor(backColor);

    polygonAllPtr->push_back(std::move(sphere01));
}
void sphereImgInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr,glm::vec3 ltn,glm::vec3 rtn,glm::vec3 lbn,glm::vec3 ltf,
                   int frontColor1,int frontColor2, int backColor, string _path, unsigned char _debug){
    // 包围盒顶点 4 找 8
    goLine32 boxGoX = ScreenDemo::get_AgoB_direction3D(ltn,rtn);
    goLine32 boxGoY = ScreenDemo::get_AgoB_direction3D(ltn,lbn);
    goLine32 boxGoZ = ScreenDemo::get_AgoB_direction3D(ltn,ltf);

    float boxLenX = glm::distance(ltn,rtn);
    float boxLenY = glm::distance(ltn,lbn);
//    float boxLenZ = ScreenDemo::distanceOfPoint3D(ltn,ltf);

    glm::vec3 rbn = goDirectionAfter(rtn,boxGoY,boxLenY);

    glm::vec3 rtf = goDirectionAfter(ltf,boxGoX,boxLenX);
    glm::vec3 rbf = goDirectionAfter(rtf,boxGoY,boxLenY);
    glm::vec3 lbf = goDirectionAfter(ltf,boxGoY,boxLenY);

    unique_ptr<SphereDemo> sphere02 = make_unique<SphereDemo>(ltn, rtn, rbn, lbn,
                                            ltf, rtf, rbf, lbf, _path, _debug);
    sphere02->setFrontColor(frontColor1,frontColor2); // 1 ? 2 葵扇黄
    sphere02->setBackColor(backColor);

    polygonAllPtr->push_back(std::move(sphere02));

}
glm::vec3 goDirectionAfter(glm::vec3 _start, goLine32 _dir, float _step){
    glm::vec3 afterPos = {_start.x+_dir.dx * _step,
                   _start.y+_dir.dy * _step,
                   _start.z+ _dir.dz * _step};
    return afterPos;
}
#endif //POLYGONDISPLAY_SPHERE_1_H
