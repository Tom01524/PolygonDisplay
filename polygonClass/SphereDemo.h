//
// Created by iceoc0 on 2025/4/11.
//

#ifndef POLYGONDISPLAY_SPHEREDEMO_H
#define POLYGONDISPLAY_SPHEREDEMO_H

#include "./source/ScreenDemo.h"


struct pixelDeep6{
    int x; // long x long y
    float screenDeep_front; // float deep
    float screenDeep_back; // float deep
    char area;
    float rgb[3]; // rgb color
};


struct rowPixelDeep6 {
    vector<pixelDeep6> pixelDeeps; // 行的像素深度
    float y; // 行
};


struct ellipseInfo {
    double cx;
    double cy;
    double a;
    double b;
    double rotation;
};



class SphereDemo : public PolygonBase{
public:
    SphereDemo(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
               glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf, unsigned char _debug_ = 0);
    SphereDemo(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
               glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf, string _path,
               unsigned char _debug_ = 0);
    void __init__(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
                  glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf, unsigned char _debug_);
    CubeBoxXYZ_ tblrXYZnf;
    CubeBoxXYZ_ tblrXYZnf_unchange; // 锁坐标系
    CubeBoxXYZ_ virtual_tblrXYZnf; // 屏幕系
    // float ltnSet_ScreenDeep;
    // float rtnSet_ScreenDeep;
    // float rbnSet_ScreenDeep;
    // float lbnSet_ScreenDeep;
    //
    // float ltfSet_ScreenDeep;
    // float rtfSet_ScreenDeep;
    // float rbfSet_ScreenDeep;
    // float lbfSet_ScreenDeep;

    CubeBoxXY_ tblrXYnf;

    float rounfBoxTipLen = 40.f;
    float radiusA,radiusB,radiusC;
    float boxLenX,boxLenY,boxLenZ;
//    float virtual_squareEdgeLen; // 避免误差

//    float latitude0, latitude30, latitude60, latitude90, latitude120, latitude150, latitude180; // 纬度

    float frameScreenFar, frameScreenNear; // 定点深度初始化

    bool flatFrontFacing;
    bool flatBackFacing;
    bool flatLeftFacing;
    bool flatRightFacing;
    bool flatTopFacing;
    bool flatBottomFacing;

    bool displayNecessary;

    bool imgMode; // 图像模式

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

    [[maybe_unused]]bool PolyScanClicked(int x,int y); // 点击到◙    ○●◍◓◒
    [[maybe_unused]]bool scanClickedBox(int x,int y);
#ifdef MAYBE_UNUSED
    bool scanClickedCircle(int x, int y);
#endif
    void switchDebug(); // 切换调试模式

    unsigned char debugLine;

    Matrix2D<glm::vec3> pixelsColor; // 加载 保存图像
    float imgW_f,imgH_f; // 图像宽高

    float frontColor1_rgb01[3];
    float frontColor2_rgb01[3];

    float backColor_rgb01[3];
    void setFrontColor(int _color1, int _color2);
    void setBackColor(int _color);

    glm::vec3 getCenter();
    glm::vec3 getVirtualCenter();

    goLine32 world_toX; //  长 单位一向量
    goLine32 world_toY; //  宽 单位一向量
    goLine32 world_toDEEP; //  深 单位一向量
    void drawSphereAxis(ScreenDemo* ScreenEye); // 画矩形坐标轴

private:
    void _solidRectangle2D_(ScreenDemo* ScreenEye,glm::vec2& p1,glm::vec2& p2,glm::vec2& p3,glm::vec2& p4,
        vector<lineBoundary>& lineScanFillColor,vector<rowPixelDeep6>& pixelEyeDeep);


    vector<lineBoundary> lineScanFillColor_front; // lx 左屏深  rx 右屏深  y 扫描线的y坐标
    vector<lineBoundary> lineScanFillColor_back; // lx 左屏深  rx 右屏深  y 扫描线的y坐标
    vector<lineBoundary> lineScanFillColor_left;
    vector<lineBoundary> lineScanFillColor_right;
    vector<lineBoundary> lineScanFillColor_top;
    vector<lineBoundary> lineScanFillColor_bottom;

    vector<rowPixelDeep6> pixelEyeDeep_front;  // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelDeep6> pixelEyeDeep_back;  // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelDeep6> pixelEyeDeep_left; // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelDeep6> pixelEyeDeep_right; // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelDeep6> pixelEyeDeep_top; // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelDeep6> pixelEyeDeep_bottom; // XY2D 屏幕坐标  screenDeep 深度

    Quaternion frameRotateInfo_q;
    void freshFrameRotateInfo();
    glm::vec3 screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos); // 屏幕坐标转自身坐标2


    [[maybe_unused]]pair<glm::vec3,glm::vec3> getVirtualSurfacePointbyXY(ScreenDemo* ScreenEye, float x, float y); // 2D坐标转屏幕深度

    Ray getRay_SelfAxis(float x, float y);
    Ray getRay_ScreenAxis(float x, float y);
    std::expected<pair<float,float>,char>
    getSurfacePointStepbyXY(Ray& ray, float x, float y); // 2D渲染坐标转球面点步数
    glm::vec3 getSurfacePointbyStep_SelfAxis(Ray& ray, float step); // 2D渲染坐标转球面点

    goLine32 eye2ScreenPixel_dxyz(float x, float y);

    int white2ColorfulScreenDeep(float pointDeep, float* color3);

    void deepFarNearBackCenter(); // 计算最远点和最近点的深度

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

    [[maybe_unused]]float distanceOfPoint2D_pair(const pair<float,float>& p1,const pair<float,float>& p2);


    goLine32 virtual_toX; //  长 单位一向量
    goLine32 virtual_toY; //  宽 单位一向量
    goLine32 virtual_toDEEP; //  深 单位一向量
    void freshVirtualGoX();
    void freshVirtualGoY();
    void freshVirtualGoDEEP();
//    glm::vec3 virtual_goX(glm::vec3 _srcXYZ, float _move);
//    glm::vec3 virtual_goY(glm::vec3 _srcXYZ, float _move);
//    glm::vec3 virtual_goDEEP(glm::vec3 _srcXYZ, float _move);

    [[maybe_unused]]float virtual_a_b_c_d_XY[4]; // 共面方程信息
    [[maybe_unused]]float virtual_a_b_c_d_XZ[4];
    [[maybe_unused]]float virtual_a_b_c_d_YZ[4];
    [[maybe_unused]]void freshVirtualFlatXY(); // 计算共面方程信息
    [[maybe_unused]]void freshVirtualFlatXZ();
    [[maybe_unused]]void freshVirtualFlatYZ();

    [[maybe_unused]]float virtual_Point2FlatYZ(glm::vec3& _point); // 点到YZ平面的距离
    [[maybe_unused]]float virtual_Point2FlatXZ(glm::vec3& _point); // 点到XZ平面的距离
    [[maybe_unused]]float virtual_Point2FlatXY(glm::vec3& _point); // 点到XY平面的距离

    bool ScreenAxis2Self_SameFlat = 0;

    [[maybe_unused]]glm::vec3 screenXYZ2SelfXYZ(glm::vec3& _screenXYZ); // 屏幕坐标转自身坐标

    float getLatitudeOnSelfAxis(glm::vec3& _point);

    float getLongitudeOnSelfAxis(glm::vec3& _point);

    glm::vec2 getUV_by_Latitude_Longitude(float longitude, float latitude); // 纬度 经度转uv
    glm::vec3 getImgColor_by_UV(glm::vec2& uv01); // uv转图像颜色

    float radius2D;
    [[maybe_unused]]void freshRadius2D();
    [[maybe_unused]]void drawRounfCircle(ScreenDemo* ScreenEye);

    float imul_a_a(float a);
};

#endif //POLYGONDISPLAY_SPHEREDEMO_H
