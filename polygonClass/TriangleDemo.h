//
// Created by iceoc0 on 2024/11/9.
//

#ifndef RECTANGLEDISPLAY_TRIANGLEDEMO_H
#define RECTANGLEDISPLAY_TRIANGLEDEMO_H
#include "./source/ScreenDemo.h"

// 原点在屏幕左上角

#ifndef _angleXYZ
#define _angleXYZ
typedef struct {
    float y; // x转
    float x; // y转
    float deep; // deep转
}angleXYZ_t; // 三维角度
#endif



#ifndef _lineBoundary
#define _lineBoundary
struct lineBoundary{

    int y; // 行 上0下大
    float lx;
    float rx;
};
#endif

class TriangleXYZ {
public:
    TriangleXYZ() = default;
    TriangleXYZ(glm::vec3 _pa, glm::vec3 _pb, glm::vec3 _pc) {
        pA = _pa;
        pB = _pb;
        pC = _pc;

    }

    glm::vec3 pA;
    glm::vec3 pB;
    glm::vec3 pC;


}; // 三维位置矩形

// struct points_eye3{
//     float faceS_Eye;
//     float faceM_Eye;
//     float faceL_Eye;
// };

#ifndef _pixelDeep
#define _pixelDeep
struct pixelDeep{
    int x; // long x long y
    float eyeDeep; // float deep
};
#endif

#ifndef _pixelDeep4Area
#define _pixelDeep4Area
struct pixelDeep4Area{
    int x; // long x long y
    float eyeDeep; // float deep
    char area; // 0 原色 1 暗色
};
#endif

#ifndef _rowPixelDeep4Area
#define _rowPixelDeep4Area
struct rowPixelDeep4Area {
    vector<pixelDeep4Area> pixelDeeps; // 行的像素深度
    float y; // 行
};
#endif
#ifndef _rowPixelDeep4
#define _rowPixelDeep4
struct rowPixelDeep4 {
    vector<pixelDeep> pixelDeeps; // 行的像素深度
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

#ifndef _order3point_
#define _order3point_
struct _order3point{
    glm::vec2 point;
    int _th; // 0 rt 1 lb 2 lt
};
#endif

// 声明超级结构体 RectDemo
class TriangleDemo : public PolygonBase{
public:

    TriangleDemo(glm::vec3 tipA, glm::vec3 tipB, glm::vec3 tipC,
                  int _objName =NULL);
    TriangleDemo(glm::vec3 tipA, glm::vec3 tipB, glm::vec3 tipC,
                  unsigned char _debug_, int _objName=NULL);


    bool PolyScanClicked(int x,int y); // 点击到▲
    void switchDebug(); // 切换调试模式

    /*设置颜色*/
    void setColor(int fontColor1); /*用setcolor时默认*/

    void setBackColor(int backColor1); // 设置背面颜色



    void set2S2M2L_XY_f(glm::vec2 _faceS_XY, glm::vec2 _faceM_XY, glm::vec2 _faceL_XY);

    void set2S2M2L_XYZ(glm::vec3 _faceS_XYZ, glm::vec3 _faceM_XYZ, glm::vec3 _faceL_XYZ);
    void Draw_Tick(ScreenDemo* ScreenEye);

    bool cTipEyeCloser();



    glm::vec3 rightest(); // 右侧最远点
    glm::vec3 leftest(); // 左侧最远点
    glm::vec3 topmost(); // 上侧最高点
    glm::vec3 bottommost(); // 下侧最低点
    glm::vec3 fontmost(); // 最近点
    glm::vec3 backmost(); // 最远点


    float centerLongist; // 中心到最远点的距离
    float getAvgeDeep(); // 平均深度

    // float triaWidth; // 宽度
    // float triaHeight; // 高度
    // float triaDepth; // 深度

    TriangleXYZ _2S2M2L_XYZ; // 三维位置▲
    TriangleXYZ _2S2M2L_XYZ_unchange; // 三维位置▲

    glm::vec2 _2S2M2L_XY_f[3]; // ###

    // points_eye3 points2Eye;
    glm::vec3 virtual_2S2M2L_XYZ[3]; // 虚拟中心点和中心点的位置
    int objName; // 名称
    float _backFont; // 法线向量取反

    // goLine32 toX; //  长 单位一向量
    // goLine32 toY; //  宽 单位一向量
    // goLine32 toDEEP; //  深 单位一向量
    // void drawTriaAxis(ScreenDemo* ScreenEye); // 画矩形坐标轴

    float screenFar; // 最远点的深度
    float screenNear; // 最近点的深度

    unsigned char debugLine; // 调试开关
private:// 私有成员

    // glm::vec3 centerBack; // 背面中心点
    // a b c cen cenT
    // glm::vec2 virtualCenterBackXY; // 背面中心点的坐标点

    float frontColor_rgb01[3];
    float frontSubColor_rgb01[3];
    float backColor_rgb01[3];

    vector<lineBoundary> lineScanFillColor; // 扫描线填充颜色
    vector<rowPixelDeep4> pixelEyeDeep; // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelDeep4Area> pixel2EyeDeepArea; // XY2D 屏幕坐标  screenDeep 深度  area 0 原色 1 暗色

    // 位置 struct{long;long} .y .x
    void _init_main(glm::vec3 _faceS_XYZ, glm::vec3 _faceM_XYZ, glm::vec3 _faceL_XYZ);
    void _solidTriangle2D(ScreenDemo* ScreenEye,bool onFront); //


    float virtualBack_a_b_c_d[4]; // 共面点函数
    [[maybe_unused]]void fresh_virtual_abcd();
    goLine32 eye2ScreenPixel_dxyz(float x, float y);
    [[maybe_unused]]glm::vec3 getEyeGoXYZbyXY(float x, float y); // 2D坐标转3D坐标
    [[maybe_unused]]float getEyeDeepbyXY(float x, float y); // 2D坐标转深度
    [[maybe_unused]]float getScreenDeepbyXY(float x, float y); // 3D坐标转深度

    float getScreenDeepbyXY_αβγ(float* alpha_beta_gamma); // 3D坐标转深度 αβγ
    char getFlatAreaByXY(float* alpha_beta_gamma);
    float* get_αβγ(float x, float y);


    float upMidDownY_deep[3]; // 上中下三角形三点的深度
    int black2ColorfulDeep(float pointDeep); // 黑色转彩色 看深度
#ifdef MAYBE_UNUSED
    [[maybe_unused]]float* black2ColorfulDeep2(float pointDeep); // 发黄 失败!
#endif
    void freshDeepFarNear(); // 计算最远点和最近点的深度
    int deepColorOf3DPoint(ScreenDemo* ScreenEye, float deepNow);

    // void freshTriaAxis();
    //
    // void freshGoX();
    // void freshGoY();
    // void freshGoDEEP();

    // glm::vec3 tiltAxis3D[4]; // 四个倾斜轴的顶点 中 x y z
    // glm::vec3 parallelAxis3D[4]; // 四个平行轴的顶点
    // glm::vec2 tiltAxis2D_f[4]; // 四个倾斜轴的顶点 中 x y z
    // glm::vec2 parallelAxis2D_f[4]; // 四个平行轴的顶点

    // void freshTiltAxis(); // 计算倾斜轴
    // void freshParallelAxis(); // 计算平行轴
    //
    // void drawTiltAxis(ScreenDemo* ScreenEye); // 画倾斜轴
    // void drawParallelAxis(ScreenDemo* ScreenEye); // 画平行轴
};



#endif //RECTANGLEDISPLAY_TRIANGLEDEMO_H
