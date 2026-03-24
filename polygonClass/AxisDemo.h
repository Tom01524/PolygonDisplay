//
// Created by iceoc0 on 2024/11/16.
//

#ifndef RECTANGLEDISPLAY_AXISDEMO_H
#define RECTANGLEDISPLAY_AXISDEMO_H

// 面向对象 把对象所有用到内容写到类中

#include"RectDemo.h"


// 原点在屏幕左上角

class AxisXYZ {
public:
    AxisXYZ() {}
    AxisXYZ(glm::vec3 Xl, glm::vec3 Xr, glm::vec3 Yt, glm::vec3 Yb, glm::vec3 DEEPc, glm::vec3 DEEPf) {
        this->Xl = Xl;
        this->Xr = Xr;
        this->Yt = Yt;
        this->Yb = Yb;
        this->DEEPc = DEEPc;
        this->DEEPf = DEEPf;
    }
    glm::vec3 Xl; // lt
    glm::vec3 Xr; // rt
    glm::vec3 Yt; // lb
    glm::vec3 Yb; // rb
    glm::vec3 DEEPc; // 中心点
    glm::vec3 DEEPf;
}; // 三维位置矩形


// struct points_eyeA{
//     float XrEye;
//     float YbEye;
//     float DEEPcEye;
//     float DEEPfEye;
// };
// 声明超级结构体 RectDemo
const float axisBack = 40.f;
class AxisDemo{
public:
    AxisDemo(glm::vec3 tblr0, glm::vec3 _Xr_xyz, glm::vec3 _Yt_xyz, glm::vec3 _Yb_xyz, glm::vec3 _DEEPc_xyz, glm::vec3 _DEEPf_xyz);


    void drawAxis(ScreenDemo* ScreenEye);
    void drawTiltAxis3Color(ScreenDemo* ScreenEye);
    /*设置颜色*/
    void setColor(int NormalColor1); /*用setcolor时默认*/

    void setTBLRXY(glm::vec2 tblr0, glm::vec2 tblr1, glm::vec2 tblr2, glm::vec2 tblr3, glm::vec2 tblrC, glm::vec2 tblrCT);

    void setTBLRXYZ(glm::vec3 ltXYZ, glm::vec3 rtXYZ, glm::vec3 rbXYZ, glm::vec3 lbXYZ, glm::vec3 centerXYZ, glm::vec3 centerTipXYZ);


    void freshGoLineDir();
    glm::vec3 goX(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goY(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goDEEP(glm::vec3 _srcXYZ, float _move);

    void goX_(glm::vec3& _srcXYZ, float _move);
    void goY_(glm::vec3& _srcXYZ, float _move);
    void goDEEP_(glm::vec3& _srcXYZ, float _move);
    glm::vec3 axis_0_0_0;
    glm::vec3 AxisTilt2world(float moveX, float moveY, float moveZ);
    glm::vec3 getCenter() ; // 获取中心点


    AxisXYZ axisXYZ; // 三维位置 坐标系
    AxisXYZ axisXYZ_unchange; // 三维位置 坐标系

    glm::vec2 tblrXY_f[6]; // Xl Xr Yb Yt DEEPc DEEPf

    glm::vec3 angleXYZ;
//    int tiltAxisColor[3]; // 倾斜轴颜色
    float _green[3];
    float _blue[3];
    float _yellow[3];
    // points_eyeA pointsEye;

    goLine32 toX; // 斜轴系 转 世界系
    goLine32 toY;
    goLine32 toDEEP;
    glm::vec3 axisLong;

    array<glm::vec3,4> tilt_C_world_oxyz;
    void freshWorldOxyz();
    goLine32 startWorld_goX; // 世界系 转 斜轴系
    goLine32 startWorld_goY;
    goLine32 startWorld_goDEEP; // 斜轴 转世界系
    void freshStartWorld_GoDir();
    void startWorld_stepX(glm::vec3& _srcXYZ, float _move);
    void startWorld_stepY(glm::vec3& _srcXYZ, float _move);
    void startWorld_stepZ(glm::vec3& _srcXYZ, float _move);

    glm::vec3 world2AxisTilt(glm::vec3& _src);
private:// 私有成员

    int rectColor;// 颜色 DWORD
    // 位置 struct{long;long} .y .x



};




#endif //RECTANGLEDISPLAY_AXISDEMO_H
