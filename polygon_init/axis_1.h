//
// Created by iceoc0 on 2024/12/8.
//
#include<stdio.h>

#ifndef RECTANGLEDISPLAY_AXIS_1_H
#define RECTANGLEDISPLAY_AXIS_1_H

#include"./fogPoint_1.h"

extern void* _top_ptr_go;
glm::vec3 top_ = {((glm::vec3*)_top_ptr_go)->x, ((glm::vec3*)_top_ptr_go)->y, ((glm::vec3*)_top_ptr_go)->z}; // 顶点
unique_ptr<AxisDemo> axisXYZ_init();
unique_ptr<AxisDemo> parallel_axisXYZ_init();

AxisXYZ axisXYZ = AxisXYZ(
        { 0,0,0 },     //Xl         X
        { 250,0,0 },     //Xr         X
        { 0,0,0 },     //Yt         Y
        { 0,250,0},     //Yb         Y
        { 0,0,0 },     //DEEPc     DEEP
        { 0,0,250 });   //DEEPf   DEEP

unique_ptr<AxisDemo> axisXYZ_init() {//printf("~~~_top.y = %f\n", top_.y);
    unique_ptr<AxisDemo> AxisXYZ = make_unique<AxisDemo>(
            axisXYZ.Xl, axisXYZ.Xr,
            axisXYZ.Yt, axisXYZ.Yb,
            axisXYZ.DEEPc, axisXYZ.DEEPf
    );

//    AxisXYZ.tiltAxisColor[0] = 0x62a120; // 翠绿
//    AxisXYZ.tiltAxisColor[1] = 0xb9902f; // 云山蓝
//    AxisXYZ.tiltAxisColor[2] = 0x0ea4d9; // 芥黄
    BGR3f _green;
    _green.setBGR(0x62a120,1);
    AxisXYZ->_green[0] = _green.r1;
    AxisXYZ->_green[1] = _green.g1;
    AxisXYZ->_green[2] = _green.b1;
    BGR3f _blue;
    _blue.setBGR(0xb9902f,1);
    AxisXYZ->_blue[0] = _blue.r1;
    AxisXYZ->_blue[1] = _blue.g1;
    AxisXYZ->_blue[2] = _blue.b1;
    BGR3f _yellow;
    _yellow.setBGR(0x0ea4d9,1);
    AxisXYZ->_yellow[0] = _yellow.r1;
    AxisXYZ->_yellow[1] = _yellow.g1;
    AxisXYZ->_yellow[2] = _yellow.b1;
    return std::move(AxisXYZ);
}

inline AxisXYZ paralel_axisXYZ = AxisXYZ(
        { -axisBack,0,0 },     //Xl
        { 200,0,0 },     //Xr
        { 0,-axisBack,0 },     //Yt
        { 0,200,0},     //Yb
        { 0,0,-axisBack },     //DEEPc
        { 0,0,200 });   //DEEPf

unique_ptr<AxisDemo> parallel_axisXYZ_init() {
    unique_ptr<AxisDemo> ParallelAxisMain = make_unique<AxisDemo>(
            paralel_axisXYZ.Xl, paralel_axisXYZ.Xr,
            paralel_axisXYZ.Yt, paralel_axisXYZ.Yb,
            paralel_axisXYZ.DEEPc, paralel_axisXYZ.DEEPf
    );

    ParallelAxisMain->setColor(WHITE); // 白色
    return std::move(ParallelAxisMain);
}
#endif //RECTANGLEDISPLAY_AXIS_1_H
