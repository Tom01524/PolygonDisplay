//
// Created by iceoc0 on 2025/8/31.
//

#ifndef POLYGONDISPLAY_EQUATIONTHREE9_H
#define POLYGONDISPLAY_EQUATIONTHREE9_H
#include "../source/ScreenDemo.h"


#include <complex> // 复数



struct onepixelInfo24{
    int x; // long x long y
    float screenDeep; // 屏垂距
    float rgb[3]; // rgb color

};

struct rowPixelInfo24 {
    vector<onepixelInfo24> pixelDeeps; // 行的像素深度
    int y; // 行
};

struct RayCalcInfo24 {
    double step; // 步长
    double vx;
    glm::vec3 surfacePoint_Self;
};
struct Particle24 {
    glm::vec2 real;
    glm::vec2 img1;
    glm::vec2 img2;
    glm::vec3 color1;
    glm::vec3 color2;

    glm::vec3 getPos1(){
//        println("---getPos1: {},{},{}", real.x, real.y, img1.y );
        return {real.x, real.y, img1.y};
    }
    glm::vec3 getPos2(){
//        println("---getPos2: {},{},{}", real.x, real.y, img2.y );
        return {real.x, real.y, img2.y};
    }
};


class EquationThree9 : public PolygonBase {
public:
    EquationThree9(glm::vec3 srartCenter, glm::vec3 _boxLengthHalf, float a, float b, float c,float d,
                   unsigned char _debug_ = 0);
    glm::vec4 abcd;

    CubeBox3D scanBox3D;
    CubeBox3D scanBox3D_unchange;
    CubeBox3D virtual_scanBox3D;

    CubeBox2D scanBox2D_;

//    float rounfBoxTipLen = 40.f;

    // glm::vec3 startEye;

    glm::vec3 halfBoxLength;
    float boxLenX,boxLenY,boxLenZ;

    unsigned char debugLine;

    double smallerCoef,smallerCoef_2,smallerCoef_3,smallerCoef_4,smallerCoef_5,
    smallerCoef_6,smallerCoef_7,smallerCoef_8,smallerCoef_9; // 最小系数

    unsigned char renderNext; // false
    int startRowIndex_; // 0

//    glm::vec2 box_ltn_last,  box_rtn_last,  box_lbn_last,  box_ltf_last; // 0,0

    bool particle_inited;

    void setBox3D(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
                  glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf);

    void setBox2D(glm::vec2 _ltn, glm::vec2 _rtn, glm::vec2 _rbn, glm::vec2 _lbn,
                  glm::vec2 _ltf, glm::vec2 _rtf, glm::vec2 _rbf, glm::vec2 _lbf,
                  glm::vec2 _center
    );
    void Draw_Tick(ScreenDemo* ScreenEye);
//    bool cTipEyeCloser(glm::vec3 eyeCenter, glm::vec3 tip, glm::vec3 back);

    void solidRectangle2D_(ScreenDemo* ScreenEye);
    vector<lineBoundary> lineScanFillColor_;
    vector<rowPixelInfo24> pixelSurfaceInfo_;


    float frameScreenFar, frameScreenNear; // 定点深度初始化
    void deepFarNearBackCenter(); // 计算最远点和最近点的深度

    glm::vec3 frontColor1_rgb01;
    glm::vec3 frontColor2_rgb01;
    glm::vec3 frontColor3_rgb01;
    void setFrontColor(int _color1, int _color2,int _color3);

    goLine32 world_toX; //  长 单位一向量
    goLine32 world_toY; //  宽 单位一向量
    goLine32 world_toDEEP; //  深 单位一向量

    void freshGoX(); // 基于世界系 盒子顶点
    void freshGoY();
    void freshGoDEEP();
    glm::vec3 goX(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goY(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goDEEP(glm::vec3 _srcXYZ, float _move);

    [[maybe_unused]]array<double, 10> getCoefficents(double ex, double ey, double ez,
                                     double dx, double dy, double dz); // 得到方程系数
    array<double, 10> getCoefficents2(double ex, double ey, double ez,
                                     double dx, double dy, double dz); // 得到方程系数
    array<complex<double>,9> solveNonic(complex<double> A, complex<double> B, complex<double> C,
                                      complex<double> D, complex<double> E, complex<double> F,
                                      complex<double> G, complex<double> H, complex<double> I,
                                      complex<double> J); // 解9次方程
    double x_img_1in2(double x_img,
                     double ex, double ey, double ez,
                     double dx, double dy, double dz,
                     double step);
    double get_x_img_by_step(double step,
                             double ex, double ey, double ez,
                             double dx, double dy, double dz);
    vector<pair<double, double>> solve(
            double ex, double ey, double ez,
            double dx, double dy, double dz); // 视线步进 >0 是实数  i.img

    bool selfPosInBox(glm::vec3 _selfPos);

    RayCalcInfo24 getBestSolve(double ex, double ey, double ez,
                               double dx, double dy, double dz); // 得到最佳解
    unsigned char getSolveBy(glm::dvec3 surfacePoint_Self, float vx);
    glm::vec3 getColorBy_vX(unsigned char solveBy, float _vX);

    pair<glm::vec2, glm::vec2> preCalculateParticle(double x_real, double y_real);

    goLine32 virtual_toX; //  长 单位一向量
    goLine32 virtual_toY; //  宽 单位一向量
    goLine32 virtual_toDEEP; //  深 单位一向量
    void freshVirtualGoX();
    void freshVirtualGoY();
    void freshVirtualGoDEEP();
    glm::vec3 Virtual_goX(glm::vec3 _srcXYZ, float _move);
    glm::vec3 Virtual_goY(glm::vec3 _srcXYZ, float _move);
    glm::vec3 Virtual_goDEEP(glm::vec3 _srcXYZ, float _move);

    glm::vec3 self2screenAxis(glm::vec3 _selfAxisPos); // 自身坐标转屏幕坐标

    vector<Particle24> particle_info; // 粒子信息
    float particleStepX, particleStepY;
    void init_particle_info(); // 初始化粒子信息
    void draw_particle(ScreenDemo* ScreenEye); // 绘制粒子

    Quaternion frameRotateInfo_q;
    void freshFrameRotateInfo();
    glm::vec3 screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos); // 屏幕坐标转自身坐标2

    glm::vec2 sideFlatLT_2D, sideFlatRT_2D, sideFlatRB_2D, sideFlatLB_2D; // 按下时四个角的屏幕坐标
    void freshComplexRect(ScreenDemo* ScreenEye);
    void drawComplexRect(ScreenDemo* ScreenEye); // 画复杂矩形
};

#endif //POLYGONDISPLAY_EQUATIONTHREE9_H
