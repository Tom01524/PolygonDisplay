//
// Created by iceoc0 on 2025/8/16.
//

#ifndef POLYGONDISPLAY_EQUATIONTWO_H
#define POLYGONDISPLAY_EQUATIONTWO_H
#include "../source/ScreenDemo.h"


struct onepixelInfo20{
    int x; // long x long y
    float screenDeep; // 屏垂距
    float rgb[3]; // rgb color

};


struct rowPixelInfo20 {
    vector<onepixelInfo20> pixelDeeps; // 行的像素深度
    float y; // 行
};

struct RayCalcInfo20 {
    double step; // 步长
    double vy;
    glm::vec3 surfacePoint_Self;
    unsigned char solveBy;
};

class EquationTwo : public PolygonBase{
public:
    EquationTwo(glm::vec3 srartCenter, glm::vec3 _boxLengthHalf, float a, float b, float c,
                unsigned char _debug_ = 0);
    glm::vec3 abc;
    float discriminant_;
    unsigned char debugLine;

    CubeBoxXYZ_ scanBox3D;
    CubeBoxXYZ_ scanBox3D_unchange;
    CubeBoxXYZ_ virtual_scanBox3D;
    CubeBoxXY_ scanBox2D;
    float rounfBoxTipLen = 40.f;


    glm::vec3 halfBoxLength;
    float boxLenX,boxLenY,boxLenZ;

    bool flatFrontFacing;
    bool flatBackFacing;
    bool flatLeftFacing;
    bool flatRightFacing;
    bool flatTopFacing;
    bool flatBottomFacing;

    bool afterMoved; // 移动后是否需要重新计算

    void setBox3D(glm::vec3& _ltn, glm::vec3& _rtn, glm::vec3& _rbn, glm::vec3& _lbn,
                  glm::vec3& _ltf, glm::vec3& _rtf, glm::vec3& _rbf, glm::vec3& _lbf);

    void setBox2D(glm::vec2& _ltn, glm::vec2& _rtn, glm::vec2& _rbn, glm::vec2& _lbn,
                  glm::vec2& _ltf, glm::vec2& _rtf, glm::vec2& _rbf, glm::vec2& _lbf,
                  glm::vec2& _center
#if defined(DEBUG_ON)
                  ,
                  glm::vec2& _rtn_ltn_tip,
                  glm::vec2& _lbn_ltn_tip,
                  glm::vec2& _ltf_ltn_tip,

                  glm::vec2& _lbf_rbf_tip,
                  glm::vec2& _rtf_rbf_tip,
                  glm::vec2& _rbn_rbf_tip
#endif
    );
    void Draw_Tick(ScreenDemo* ScreenEye);
    bool cTipEyeCloser(glm::vec3 eyeCenter, glm::vec3 tip, glm::vec3 back);

    void solidRectangle2D_front(ScreenDemo* ScreenEye);
    void solidRectangle2D_left(ScreenDemo* ScreenEye);
    void solidRectangle2D_right(ScreenDemo* ScreenEye);
    void solidRectangle2D_back(ScreenDemo* ScreenEye);
    void solidRectangle2D_top(ScreenDemo* ScreenEye);
    void solidRectangle2D_bottom(ScreenDemo* ScreenEye);

    vector<lineBoundary> lineScanFillColor_front{}; // lx 左屏深  rx 右屏深  y 扫描线的y坐标
    vector<lineBoundary> lineScanFillColor_left{};
    vector<lineBoundary> lineScanFillColor_right{};
    vector<lineBoundary> lineScanFillColor_back{}; // lx 左屏深  rx 右屏深  y 扫描线的y坐标
    vector<lineBoundary> lineScanFillColor_top{};
    vector<lineBoundary> lineScanFillColor_bottom{};

    vector<rowPixelInfo20> pixelSurfaceInfo_front{};  // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelInfo20> pixelSurfaceInfo_left{}; // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelInfo20> pixelSurfaceInfo_right{}; // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelInfo20> pixelSurfaceInfo_back{};  // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelInfo20> pixelSurfaceInfo_top{}; // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelInfo20> pixelSurfaceInfo_bottom{}; // XY2D 屏幕坐标  screenDeep 深度

    float frameScreenFar, frameScreenNear; // 定点深度初始化
    void deepFarNearBackCenter(); // 计算最远点和最近点的深度

    glm::vec3 frontColor1_rgb01;
    glm::vec3 frontColor2_rgb01;

    glm::vec3 backColor_rgb01;
    void setFrontColor(int _color1, int _color2);
    [[maybe_unused]]void setBackColor(int _color);


    goLine32 world_toX; //  长 单位一向量
    goLine32 world_toY; //  宽 单位一向量
    goLine32 world_toDEEP; //  深 单位一向量

    void freshGoX(); // 基于世界系 盒子顶点
    void freshGoY();
    void freshGoDEEP();
    glm::vec3 goX(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goY(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goDEEP(glm::vec3 _srcXYZ, float _move);

    RayCalcInfo20 solveQuadratic( // 视线解算 复曲面方程求解
            double ex, double ey, double ez,
            double dx, double dy, double dz,glm::vec3 startEye_Self,goLine32 eyeRay_Self);

    unsigned char getSolveBy(glm::dvec3 surfacePoint_Self, double vy);
    glm::vec3 getColorBy_vY(unsigned char solveBy, float _vY);

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

    bool selfPosInBox(glm::vec3 _selfPos); // 判断自身位置是否在盒子内

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

    glm::vec2 downFlatLT_2D, downFlatRT_2D, downFlatRB_2D, downFlatLB_2D; // 按下时四个角的屏幕坐标
    void freshComplexRect(ScreenDemo* ScreenEye);
    void drawComplexRect(ScreenDemo* ScreenEye); // 画复杂矩形
};

#endif //POLYGONDISPLAY_EQUATIONTWO_H
