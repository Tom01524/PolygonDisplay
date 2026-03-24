//
// Created by iceoc0 on 2025/9/20.
//

#ifndef POLYGONDISPLAY_EQUATIONTHREE_H
#define POLYGONDISPLAY_EQUATIONTHREE_H

#include "../source/ScreenDemo.h"

struct onepixelInfo25{
    int x; // long x long y
    float screenDeep; // 屏垂距
    float rgb[3]; // rgb color

};

struct rowPixelInfo25 {
    vector<onepixelInfo25> pixelDeeps; // 行的像素深度
    int y; // 行
};

struct RayCalcInfo25 {
    double step; // 步长
    double vy;
    glm::vec3 surfacePoint_Self;
};

class EquationThree : public PolygonBase {
public:
    EquationThree(glm::vec3 srartCenter, glm::vec3 _boxLengthHalf, float a, float b, float c,float d,
    unsigned char _debug_ = 0);

    glm::vec4 abcd;

    CubeBox3D scanBox3D;
    CubeBox3D scanBox3D_unchange;
    CubeBox3D virtual_scanBox3D;

    CubeBox2D scanBox2D_;

    // glm::vec3 startEye;

    glm::vec3 halfBoxLength;
    float boxLenX,boxLenY,boxLenZ;

    unsigned char debugLine;

    bool afterMoved; // 移动后是否需要重新计算

    void setBox3D(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
                  glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf);

    void setBox2D(glm::vec2 _ltn, glm::vec2 _rtn, glm::vec2 _rbn, glm::vec2 _lbn,
                  glm::vec2 _ltf, glm::vec2 _rtf, glm::vec2 _rbf, glm::vec2 _lbf,
                  glm::vec2 _center
    );
    void Draw_Tick(ScreenDemo* ScreenEye);

    void solidRectangle2D_(ScreenDemo* ScreenEye);
    vector<lineBoundary> lineScanFillColor_;
    vector<rowPixelInfo25> pixelSurfaceInfo_;

    goLine32 world_toX; //  长 单位一向量
    goLine32 world_toY; //  宽 单位一向量
    goLine32 world_toDEEP; //  深 单位一向量

    void freshGoX(); // 基于世界系 盒子顶点
    void freshGoY();
    void freshGoDEEP();
    glm::vec3 goX(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goY(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goDEEP(glm::vec3 _srcXYZ, float _move);

    float frameScreenFar, frameScreenNear; // 定点深度初始化
    void deepFarNearBackCenter(); // 计算最远点和最近点的深度

    glm::vec3 frontColor1_rgb01;
    glm::vec3 frontColor2_rgb01;
    glm::vec3 frontColor3_rgb01;
    void setFrontColor(int _color1, int _color2,int _color3);

    goLine32 virtual_toX; //  长 单位一向量
    goLine32 virtual_toY; //  宽 单位一向量
    goLine32 virtual_toDEEP; //  深 单位一向量
    void freshVirtualGoX();
    void freshVirtualGoY();
    void freshVirtualGoDEEP();
    glm::vec3 Virtual_goX(glm::vec3 _srcXYZ, float _move);
    glm::vec3 Virtual_goY(glm::vec3 _srcXYZ, float _move);
    glm::vec3 Virtual_goDEEP(glm::vec3 _srcXYZ, float _move);

    glm::vec3 self2screenAxis(glm::vec3 _selfAxisPos);

    Quaternion frameRotateInfo_q;
    void freshFrameRotateInfo();
    glm::vec3 screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos); // 屏幕坐标转自身坐标2

    vector<double> getStep(double ex, double ey, double ez, double dx, double dy, double dz);
    double getYimg_byStep(double ex, double ey, double ez, double dx, double dy, double dz,double step);
    bool selfPosInBox(glm::vec3 pos);
    RayCalcInfo25 getBestSolve(double ex, double ey, double ez, double dx, double dy, double dz);

    unsigned char getSolveBy(glm::vec3 surfacePoint_Self, double vy);
    glm::vec3 getColorBy_vX(unsigned char solveBy, float _vX);

    glm::vec2 downFlatLT_2D, downFlatRT_2D, downFlatRB_2D, downFlatLB_2D; // 按下时四个角的屏幕坐标
    void freshComplexRect(ScreenDemo* ScreenEye);
    void drawComplexRect(ScreenDemo* ScreenEye); // 画复杂矩形
};

#endif //POLYGONDISPLAY_EQUATIONTHREE_H
