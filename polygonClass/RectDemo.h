//
// Created by iceoc0 on 2024/10/31.
//
#ifndef TRIANGLEDISPLAY_RECTDEMO_H
#define TRIANGLEDISPLAY_RECTDEMO_H

// 面向对象 把对象所有用到内容写到类中

#include"source/ScreenDemo.h"


// using namespace std;


// 原点在屏幕左上角


#ifndef _angleXYZ
#define _angleXYZ
typedef struct {
    float y; // x转
    float x; // y转
    float deep; // deep转
}angleXYZ_t; // 三维角度
#endif


#ifndef _RectXYZ
#define _RectXYZ
class RectXYZ {
    public:
    RectXYZ() {}
    RectXYZ(glm::vec3 lt, glm::vec3 rt, glm::vec3 lb, glm::vec3 rb, glm::vec3 center, glm::vec3 centerTip) {
        this->lt = lt;
        this->rt = rt;
        this->lb = lb;
        this->rb = rb;
        this->center = center;
        this->centerTip = centerTip;
    }
    glm::vec3 lt;
    glm::vec3 rt;
    glm::vec3 lb;
    glm::vec3 rb;
    glm::vec3 center; // 中心点
    glm::vec3 centerTip;
}; // 三维位置矩形
#endif

// #ifndef _points_eye4
// #define _points_eye4
// struct points_eye4{
//     float ltEye;
//     float rtEye;
//     float rbEye;
//     float lbEye;
// };
// #endif



#ifndef _goLine64
#define _goLine64
typedef struct {
    double dx;
    double dy;
    double dz;
}goLine64; // 直线 向量
#endif

#ifndef _lineBoundary
#define _lineBoundary
struct lineBoundary{

    int y; // 行 上0下大
    float lx;
    float rx;
};
#endif

#ifndef _pixelDeep4
#define _pixelDeep4
struct pixelDeep4{
    int x; // long x long y
    float eyeDeep; // float deep
};
#endif

#ifndef _rowPixelDeep4
#define _rowPixelDeep4
struct rowPixelDeep4 {
    vector<pixelDeep4> pixelDeeps; // 行的像素深度
    float y; // 行
};
#endif




#ifndef _depth_3Dpos
#define _depth_3Dpos
struct depth_3Dpos{
    glm::vec3 pos;
    float depth;
};
#endif

#ifndef _order4point_
#define _order4point_

struct _order4point{
    glm::vec2 point;
    int _th; // 0 lt 1 rt 2 rb 3 lb
};


#endif


// 声明超级结构体 RectDemo
class RectDemo : public PolygonBase{
public:
    RectDemo(glm::vec3 _lt_xyz, glm::vec3 _rt_xyz, glm::vec3 _rb_xyz, glm::vec3 _lb_xyz,
             glm::vec3 _center_xyz, glm::vec3 _centerTip_xyz,int _type);
    RectDemo(glm::vec3 _lt_xyz, glm::vec3 _rt_xyz, glm::vec3 _rb_xyz, glm::vec3 _lb_xyz,
             glm::vec3 _center_xyz, glm::vec3 _centerTip_xyz,int _type,unsigned char _debug_);


    bool PolyScanClicked(int x,int y); // 点击到▲
    void switchDebug(); // 切换调试模式

    /*设置颜色*/
    void setColor(int NormalColor1); /*用setcolor时默认*/

    void setBackColor(int backColor); // 设置背面颜色


    void setTBLRXY_f(glm::vec2 lt_XY, glm::vec2 rt_XY, glm::vec2 rb_XY, glm::vec2 lb_XY, glm::vec2 center_XY, glm::vec2 ctip_XY);
    void setTBLRXY_Down(glm::vec2 tblr0, glm::vec2 tblr1, glm::vec2 tblr2, glm::vec2 tblr3, glm::vec2 tblrC, glm::vec2 tblrCT);

    void setTBLRXYZ(glm::vec3 ltXYZ, glm::vec3 rtXYZ, glm::vec3 rbXYZ, glm::vec3 lbXYZ);
    void Draw_Tick(ScreenDemo* ScreenEye);
    void drawRectOnly(ScreenDemo* ScreenEye);
    glm::vec3 getCenter() ; // 获取中心点
    glm::vec3 getVirtualCenter(); // 获取虚拟中心点
    glm::vec3 getCenterTip() ; // 获取中心点


    glm::vec3 rightest(); // 右侧最远点
    glm::vec3 leftest(); // 左侧最远点
    glm::vec3 topmost(); // 上侧最高点
    glm::vec3 bottommost(); // 下侧最低点
    glm::vec3 fontmost(); // 最近点
    glm::vec3 backmost(); // 最远点


    bool cTipEyeCloser(glm::vec3 eyeCenter);



    float centerLongist; // 中心到最远点的距离

    float getAvgeDeep(); // 平均深度

    float rectWidth; // 宽度
    float rectHeight; // 高度
    float rectDepth; // 深度

    RectXYZ tblrXYZ; // 三维位置矩形
    RectXYZ tblrXYZ_unchange; // 三维位置矩形

    glm::ivec2 tblrXY_l[6]; // 四个顶点的坐标点
    glm::vec2 tblrXY_f[6]; // 四个顶点的坐标点
    glm::vec2 tblrXY_down[6]; //   body    额外四个低点的坐标点


    // points_eye4 points2Eye;
    glm::vec3 virtual_tblrXYZ[6]; // lt rt rb lb center centerTip
    float _backFont; // 法线向量取反

    goLine32 toX; //  长 单位一向量
    goLine32 toY; //  宽 单位一向量
    goLine32 toDEEP; //  深 单位一向量
    void drawRectAxis(ScreenDemo* ScreenEye); // 画矩形坐标轴

    float screenFar; // 最远点的深度
    float screenNear; // 最近点的深度



private:// 私有成员
    unsigned char debugLine; // 调试开关
    bool _first;
    glm::vec3 centerBack; // 背面中心点
    glm::vec2 virtualCenterBackXY; // 背面中心点的坐标点


    float frontColor_rgb01[3];
    float backColor_rgb01[3];

    vector<lineBoundary> lineScanFillColor; // lx 左屏深  rx 右屏深  y 扫描线的y坐标
    vector<rowPixelDeep4> pixel2ScreenDeep; // XY2D 屏幕坐标  screenDeep 深度


    // 位置 struct{long;long} .y .x
    void _init_main(glm::vec3& _lt_xyz, glm::vec3& _rt_xyz, glm::vec3& _rb_xyz,glm::vec3& _lb_xyz,
                    glm::vec3& _center_xyz, glm::vec3& _centerTip_xyz, int _type);
    void _solidRectangle2D(ScreenDemo* ScreenEye, bool onFront);


    glm::vec4 virtualBack_a_b_c_d; // 共面点函数
    void ax1_by1_cz1_d1();
    goLine32 eye2ScreenPixel_dxyz(float x, float y);
#ifdef MAYBE_UNUSED
    [[maybe_unused]]glm::vec3 getEyeGoXYZbyXY(float x, float y); // 2D坐标转3D坐标
    [[maybe_unused]]float getEyeDeepbyXY(float x, float y); // 2D坐标转深度
#endif
    float getScreenDeepByXY(float x, float y); // 2D坐标转屏幕深度

    // 计算直线点与屏幕的距离




    int black2ColorfulScreenDeep(float deepNow); // 黑色转彩色 看深度

//------------------- 有错误 线性深度预测 先用正垂于眼睛deep的 距离
    bool XYonScreen_f(float x, float y);


//---------------------
    int deepColorOf3DPoint(ScreenDemo* ScreenEye, float deepNow);

    void freshDeepFarNear(); // 计算最远点和最近点的深度

    void freshRectAxis();

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

#endif //TRIANGLEDISPLAY_RECTDEMO_H
