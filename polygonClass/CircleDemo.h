//
// Created by iceoc0 on 2025/3/15.
//

#ifndef RECTANGLEDISPLAY_CIRCLEDEMO_H
#define RECTANGLEDISPLAY_CIRCLEDEMO_H

#include "source/ScreenDemo.h"



#ifndef _lineBoundary
#define _lineBoundary
struct lineBoundary{

    int y; // 行 上0下大
    float lx;
    float rx;
};
#endif

#ifndef _points_eye4
#define _points_eye4
struct points_eye4{
    float ltEye;
    float rtEye;
    float rbEye;
    float lbEye;
};
#endif

#ifndef _pixelDeep10
#define _pixelDeep10
struct pixelDeep10{
    int x; // long x long y
    float screenDeep; // float deep
    bool inCirce;
};
#endif

#ifndef _order4point_
#define _order4point_
struct _order4point{
    glm::vec2 point;
    int _th; // 0 lt 1 rt 2 rb 3 lb
};
#endif

#ifndef _rowPixelDeep10
#define _rowPixelDeep10
struct rowPixelDeep10 {
    vector<pixelDeep10> pixelDeeps; // 行的像素深度
    int y; // 行
};
#endif

class CircleXYZ{
    public:
    CircleXYZ() = default;
        CircleXYZ(glm::vec3 _lt, glm::vec3 _rt, glm::vec3 _rb, glm::vec3 _lb){
            ltSet = _lt;
            rtSet = _rt;
            rbSet = _rb;
            lbSet = _lb;


        }
        glm::vec3 ltSet;
        glm::vec3 rtSet;
        glm::vec3 rbSet;
        glm::vec3 lbSet;

        glm::vec3 center;
        glm::vec3 centerTip;
};

class CircleDemo: public PolygonBase {
public:
    CircleDemo(glm::vec3 _lt, glm::vec3 _rt, glm::vec3 _rb, glm::vec3 _lb, bool backFont = false, unsigned char _debug_ = 0);
    ~CircleDemo() = default;
    CircleXYZ tblrXYZ;
    CircleXYZ tblrXYZ_unchange;

    float _backFont;
    unsigned char debugLine;

    float radius;
    float screenFar;
    float screenNear;
    goLine32 toT; // 到t的向量
    goLine32 toR; // 到r的向量


    glm::ivec2 tblrXY_l[6]; // 四个顶点的坐标点
    glm::vec2 tblrXY_f[6]; // ltSet rbtSet rbSet lbSet center centerTip


    // points_eye4 points2EyeBack; // 四点到屏幕的距离 + 视点
    glm::vec3 virtual_tblrXYZ[6]; // ltSet rbtSet rbSet lbSet center centerTip
    glm::vec3 virtual_centerBack;


    bool PolyScanClicked(int x,int y); // 点击到◙    ○●◍◓◒
    void switchDebug(); // 切换调试模式

    glm::vec3 getCenter() ; // 获取中心点
    glm::vec3 getVirtualCenter(); // 获取虚拟中心点


    void _solidCircle2D(ScreenDemo* ScreenEye, bool onFront);


    bool midPointLineLeft(glm::vec2& lineBegin, glm::vec2& lineEnd, glm::vec2& midPoint);
    float crossProduct(const glm::vec2& lineBegin, const glm::vec2& lineEnd, const glm::vec2& midPoint); // 叉乘
    float getXby_line_y_2D(int upperP_th, int lowerP_th, float y); // 根据y值计算x值  先有直线

    int black2ColorfulScreenDeep(float deepNow); // 黑色转彩色 看深度
//    void freshDeepFarNear(); // 计算最远点和最近点的深度




    void setColor(int fontColor1);
    void setBackColor(int backColor1);

    void setTBLRXY_l(glm::ivec2 tblr0, glm::ivec2 tblr1, glm::ivec2 tblr2, glm::ivec2 tblr3, glm::ivec2 tblrC, glm::ivec2 tblrCT);
    void setTBLRXY_f(glm::vec2 lt_XY, glm::vec2 rt_XY, glm::vec2 rb_XY, glm::vec2 lb_XY, glm::vec2 center_XY, glm::vec2 ctip_XY);

    void setTBLRXYZ(glm::vec3 _lt, glm::vec3 _rt, glm::vec3 _rb, glm::vec3 _lb);

    void Draw_Tick(ScreenDemo* ScreenEye);
    bool cTipEyeCloser(glm::vec3 eyeCenter);

    float imul_a_a(float a);


    float squareEdge; // 边长
    float squareDepth; // 深度

    goLine32 toX; //  长 单位一向量
    goLine32 toY; //  宽 单位一向量
    goLine32 toDEEP; //  深 单位一向量
    void drawCircleAxis(ScreenDemo* ScreenEye); // 画矩形坐标轴

private:

    float frontColor_rgb01[3];
    float backColor_rgb01[3];

    glm::vec3 centerBackXYZ; // 背面中心点
    glm::vec2 centerBackXY; // 背面中心点的坐标点

    float a_b_c_d[4]; // 圆心方程参数
    float virtualBack_a_b_c_d[4]; // 虚拟背面方程参数
    void ax1_by1_cz1_d1_virtualFlat();

    vector<lineBoundary> lineScanFillColor; // lx 左屏深  rx 右屏深  y 扫描线的y坐标
    vector<rowPixelDeep10> pixelEyeDeep; // XY2D 屏幕坐标  screenDeep 深度

    float getEyeDeepbyXY(float x, float y); // 2D坐标转深度
    float getScreenDeepbyXY(float x, float y); // 2D坐标转屏幕深度
    glm::vec3 getFlatPointXYZbyXY(float x, float y); // 2D坐标转3D坐标
    goLine32 eye2ScreenPixel_dxyz(float x, float y);

    void freshCircleAxis();

    void freshGoX();
    void freshGoY();
    void freshGoDEEP();
    glm::vec3 goX(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goY(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goDEEP(glm::vec3 _srcXYZ, float _move);

    glm::vec3 tiltAxis3D[4]; // 四个倾斜轴的顶点 中 x y z
    glm::vec3 parallelAxis3D[4]; // 四个平行轴的顶点
    glm::vec2 tiltAxis2D_f[4]; // 四个倾斜轴的顶点 中 x y z
    glm::vec2 parallelAxis2D_f[4]; // 四个平行轴的顶点
    void freshTiltAxis(); // 计算倾斜轴
    void freshParallelAxis(); // 计算平行轴

    void drawTiltAxis(ScreenDemo* ScreenEye); // 画倾斜轴
    void drawParallelAxis(ScreenDemo* ScreenEye); // 画平行轴

};

#endif //RECTANGLEDISPLAY_CIRCLEDEMO_H
