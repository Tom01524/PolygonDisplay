//
// Created by iceoc0 on 2025/8/23.
//

#ifndef POLYGONDISPLAY_EQUATIONTWO4_H
#define POLYGONDISPLAY_EQUATIONTWO4_H
#include "../source/ScreenDemo.h"

struct onepixelInfo21{
    int x; // long x long y
    float screenDeep; // 屏垂距
    float rgb[3]; // rgb color

};

struct rowPixelInfo21 {
    vector<onepixelInfo21> pixelDeeps; // 行的像素深度
    int y; // 行
};

struct RayCalcInfo21 {
    double step; // 步长
    double vx;
    glm::vec3 surfacePoint_Self;
};

struct Coefficient5_ {
    complex<double> a, b, c, d, e;
};

//struct vec4_ {
//    complex<double> x1, x2, x3, x4;
//};

class EquationTwo4 : public PolygonBase {
public:
    EquationTwo4(glm::vec3 srartCenter, glm::vec3 _boxLengthHalf, float a, float b, float c,
            unsigned char _debug_ = 0);
    glm::vec3 abc;
    unsigned char debugLine;

    CubeBox3D scanBox3D;
    CubeBox3D scanBox3D_unchange;
    CubeBox3D virtual_scanBox3D;
//    CubeBoxXY scanBox2D;
    CubeBox2D scanBox2D_;

    float rounfBoxTipLen = 40.f;

    // glm::vec3 startEye;

    glm::vec3 halfBoxLength;
    float boxLenX,boxLenY,boxLenZ;


    unsigned char afterMoved;

    void setBox3D(glm::vec3& _ltn, glm::vec3& _rtn, glm::vec3& _rbn, glm::vec3& _lbn,
                  glm::vec3& _ltf, glm::vec3& _rtf, glm::vec3& _rbf, glm::vec3& _lbf);

    void setBox2D(glm::vec2& _ltn, glm::vec2& _rtn, glm::vec2& _rbn, glm::vec2& _lbn,
                  glm::vec2& _ltf, glm::vec2& _rtf, glm::vec2& _rbf, glm::vec2& _lbf,
                  glm::vec2& _center
    );
    void Draw_Tick(ScreenDemo* ScreenEye);

    void solidRectangle2D_(ScreenDemo* ScreenEye, bool onFront);
    vector<lineBoundary> lineScanFillColor_;
    vector<rowPixelInfo21> pixelSurfaceInfo_;

    float frameScreenFar, frameScreenNear; // 定点深度初始化
    void deepFarNearBackCenter(); // 计算最远点和最近点的深度

    glm::vec3 frontColor1_rgb01;
    glm::vec3 frontColor2_rgb01;

    glm::vec3 backColor_rgb01;
    void setFrontColor(int _color1, int _color2);
    void setBackColor(int _color);


    goLine32 world_toX; //  长 单位一向量
    goLine32 world_toY; //  宽 单位一向量
    goLine32 world_toDEEP; //  深 单位一向量

    void freshGoX(); // 基于世界系 盒子顶点
    void freshGoY();
    void freshGoDEEP();
    glm::vec3 goX(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goY(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goDEEP(glm::vec3 _srcXYZ, float _move);

    array<complex<double>,4> solveEquation_4_(Coefficient5_& src); // 解4次方程
    vector<pair<double, double>> solve(
            double ex, double ey, double ez,
            double dx, double dy, double dz); // 视线步进 >0 是实数  i.img
    bool selfPosInBox(glm::vec3 _selfPos); // 判断自身位置是否在盒子内
    RayCalcInfo21 getBestSolve(double ex, double ey, double ez,
                                      double dx, double dy, double dz);

    unsigned char getSolveBy(glm::dvec3 surfacePoint_Self, double vx);
    glm::vec3 getColorBy_vX(unsigned char solveBy, double _vX);

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

    Quaternion frameRotateInfo_q;
    void freshFrameRotateInfo();
    glm::vec3 screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos); // 屏幕坐标转自身坐标2

    glm::vec3 tiltAxis3D[4]; // 四个倾斜轴的顶点 中 x y z
    glm::vec3 parallelAxis3D[4]; // 四个平行轴的顶点
    glm::vec2 tiltAxis2D_f[4]; // 四个倾斜轴的顶点 中 x y z
    glm::vec2 parallelAxis2D_f[4]; // 四个平行轴的顶点
    void freshTiltAxis(); // 计算倾斜轴
    void freshParallelAxis(); // 计算平行轴

    void drawTiltAxis(ScreenDemo* ScreenEye); // 画倾斜轴
    void drawParallelAxis(ScreenDemo* ScreenEye); // 画平行轴

    void freshTheAxis();
    void drawTheAxis(ScreenDemo* ScreenEye); // 画轴线

    void switchDebug(); // 切换调试模式

    glm::vec2 sideFlatLT_2D, sideFlatRT_2D, sideFlatRB_2D, sideFlatLB_2D; // 按下时四个角的屏幕坐标
    void freshComplexRect(ScreenDemo* ScreenEye);
    void drawComplexRect(ScreenDemo* ScreenEye); // 画复杂矩形

};
/* 已知 ex,ey,ez,dx,dy,dz,a,b,c;
 * 未知 step,x.img;

 * x.real = ex+dx*step;
 * y.real = ey+dy*step;
 * y.img = ez+dz*step;

 * a(x.real + x.img*I)² + b(x.real + x.img*I) + c = y.real + y.img*I;
SO~
 得到虚数方程
 * [(a*dx²)+0*i]step² + [(2*a*ex*dx+b*dx-dy)+(a*dx*x.img+a*x.img*dx-dz)*i]*step
 *  + [(a*ex²-a*x.img²+b*ex+c -  ey )+(+2*a*ex*x.img+b* x.img- ez)*i] = 0

 * A = (a*dx²)+0*I
 * B = (2*a*ex*dx+b*dx-dy)+(a*dx*x.img+a*x.img*dx-dz)*I
 * C = (a*ex² - a*x.img² + b*ex + c - ey )+(2*a*ex*x.img+b* x.img- ez)*i
SO~
 step为实数  分为实虚系数两个方程
 * (a*dx²)*step² + (2*a*ex*dx+b*dx-dy)*step + (a*ex² - a*x.img² + b*ex + c - ey ) = 0;
 * (2*a*x.img*dx - dz)*step + (2*a*x.img*ex + b* x.img- ez) = 0;
SO~
 两式联立  解四次
 * x.img = (dz*step + ez) / (2*a*dx*step + 2*a*ex + b);
SO~
 * {[a*dx²]*[4*a²*dx²]}step⁴
 * +{[a*dx²]*[8*a²*dx*ex +4*a*dx*b]+[2*a*ex*dx+b*dx-dy]*[4*a²*dx²]}step³
 * +{[a*dx²]*[4*a²*ex² + 4*a*ex*b + b²]+[2*a*ex*dx+b*dx-dy]*[8*a²*dx*ex +4*a*dx*b]+[a*ex² + b*ex + c - ey]*[4*a²*dx²]-[a*dz²]}step²
 * +{[2*a*ex*dx+b*dx-dy]*[4*a²*ex² + 4*a*ex*b + b²]+[a*ex² + b*ex + c - ey]*[8*a²*dx*ex +4*a*dx*b]-[a*2*dz*ez]}step
 * +{[a*ex² + b*ex + c - ey]*[4*a²*ex² + 4*a*ex*b + b²]-[a*ez²]}
 *  = 0;

 * A = 4*a³*dx⁴;
 * B = [a*dx²]*[8*a²*dx*ex +4*a*dx*b]+[2*a*ex*dx+b*dx-dy]*[4*a²*dx²];
 * C = [a*dx²]*[4*a²*ex² + 4*a*ex*b + b²]+[2*a*ex*dx+b*dx-dy]*[8*a²*dx*ex +4*a*dx*b]+[a*ex² + b*ex + c - ey]*[4*a²*dx²]-[a*dz²];
 * D = [2*a*ex*dx+b*dx-dy]*[4*a²*ex² + 4*a*ex*b + b²]+[a*ex² + b*ex + c - ey]*[8*a²*dx*ex +4*a*dx*b]-[a*2*dz*ez];
 * E = [a*ex² + b*ex + c - ey]*[4*a²*ex² + 4*a*ex*b + b²]-[a*ez²];
 *

 * */
#endif //POLYGONDISPLAY_EQUATIONTWO4_H
