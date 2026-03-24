//
// Created by iceoc0 on 2025/4/20.
//

#ifndef POLYGONDISPLAY_CONEDEMO_H
#define POLYGONDISPLAY_CONEDEMO_H

#include "./source/ScreenDemo.h"


struct pixelDeep13{
    int x; // long x long y
    float screenDeep_near; // float deep
    float screenDeep_far; // float deep
    char area;
    bool inCirce;
};



struct rowPixelDeep13 {
    vector<pixelDeep13> pixelDeeps; // 行的像素深度
    float y; // 行
};

#ifndef _order3point_
#define _order3point_
struct _order3point{
    glm::vec2 point;
    int _th; // 0 rt 1 lb 2 lt
};
#endif


class ConeXYZ{
public:
    ConeXYZ() = default;
    ConeXYZ(glm::vec3 _lt,glm::vec3 _rt,glm::vec3 _rb,glm::vec3 _lb, glm::vec3 _downTip){
        ltSet = _lt;rtSet = _rt;rbSet = _rb;lbSet = _lb;downCuspSet = _downTip;

        center.x = (ltSet.x + rbSet.x) / 2.f;
        center.y = (ltSet.y + rbSet.y) / 2.f;
        center.z = (ltSet.z + rbSet.z) / 2.f;

        goLine32 c_rt_dir = ScreenDemo::get_AgoB_direction3D(center, rtSet);
        goLine32 c_lt_dir = ScreenDemo::get_AgoB_direction3D(center, ltSet);
        goLine32 c_ctip_dir;
        c_ctip_dir._ = glm::normalize(glm::cross(c_rt_dir._, c_lt_dir._));

        centerTip = {center.x+c_ctip_dir.dx*40.f, center.y+c_ctip_dir.dy*40.f, center.z+ c_ctip_dir.dz * 40.f};
        centerBack = {center.x-c_ctip_dir.dx*40.f, center.y-c_ctip_dir.dy*40.f, center.z- c_ctip_dir.dz * 40.f};

        goLine32 lt_d_dir = ScreenDemo::get_AgoB_direction3D(ltSet, downCuspSet);

        goLine32 lt_rt_dir = ScreenDemo::get_AgoB_direction3D(ltSet, rtSet);
        goLine32 lt_rt_tip_dir;
        lt_rt_tip_dir._ = glm::normalize(glm::cross(lt_rt_dir._, lt_d_dir._));

         lt_rt_tip = {ltSet.x + lt_rt_tip_dir.dx * 40.f, ltSet.y + lt_rt_tip_dir.dy * 40.f, ltSet.z + lt_rt_tip_dir.dz * 40.f};
        lt_rt_back = {ltSet.x - lt_rt_tip_dir.dx * 40.f, ltSet.y - lt_rt_tip_dir.dy * 40.f, ltSet.z - lt_rt_tip_dir.dz * 40.f};

        goLine32 lt_lb_dir = ScreenDemo::get_AgoB_direction3D(lbSet,ltSet);
        goLine32 lt_lb_tip_dir;
        lt_lb_tip_dir._ = glm::normalize(glm::cross(lt_lb_dir._, lt_d_dir._));
        lt_lb_tip = {ltSet.x + lt_lb_tip_dir.dx * 40.f, ltSet.y + lt_lb_tip_dir.dy * 40.f, ltSet.z + lt_lb_tip_dir.dz * 40.f};
        lt_lb_back = {ltSet.x - lt_lb_tip_dir.dx * 40.f, ltSet.y - lt_lb_tip_dir.dy * 40.f, ltSet.z - lt_lb_tip_dir.dz * 40.f};

        goLine32 rb_d_dir = ScreenDemo::get_AgoB_direction3D(rbSet, downCuspSet);

        goLine32 rb_rt_dir = ScreenDemo::get_AgoB_direction3D(rtSet, rbSet);
        goLine32 rb_rt_tip_dir;
        rb_rt_tip_dir._ = glm::cross(rb_rt_dir._, rb_d_dir._);
        rb_rt_tip_dir._ = glm::normalize(rb_rt_tip_dir._);
        rb_rt_tip = {rbSet.x + rb_rt_tip_dir.dx * 40.f, rbSet.y + rb_rt_tip_dir.dy * 40.f, rbSet.z + rb_rt_tip_dir.dz * 40.f};
        rb_rt_back = {rbSet.x - rb_rt_tip_dir.dx * 40.f, rbSet.y - rb_rt_tip_dir.dy * 40.f, rbSet.z - rb_rt_tip_dir.dz * 40.f};

        goLine32 rb_lb_dir = ScreenDemo::get_AgoB_direction3D(rbSet, lbSet);
        goLine32 rb_lb_tip_dir;
        rb_lb_tip_dir._ = glm::cross(rb_lb_dir._, rb_d_dir._);
        rb_lb_tip_dir._ = glm::normalize(rb_lb_tip_dir._);
        rb_lb_tip = {rbSet.x + rb_lb_tip_dir.dx * 40.f, rbSet.y + rb_lb_tip_dir.dy * 40.f, rbSet.z + rb_lb_tip_dir.dz * 40.f};
        rb_lb_back = {rbSet.x - rb_lb_tip_dir.dx * 40.f, rbSet.y - rb_lb_tip_dir.dy * 40.f, rbSet.z - rb_lb_tip_dir.dz * 40.f};

//        cout << " tblrdXYZ.lt_rt_tip.x=" << lt_rt_tip.x << " lt_rt_tip.y=" << lt_rt_tip.y <<
//             " lt_rt_tip.z=" << lt_rt_tip.z << endl;
//        cout << " lt_rt_back.x=" << lt_rt_back.x << " lt_rt_back.y=" << lt_rt_back.y <<
//             " lt_rt_back.z=" << lt_rt_back.z << endl;
//        cout << " rb_rt_tip.x=" << rb_rt_tip.x << " rb_rt_tip.y=" << rb_rt_tip.y <<
//             " rb_rt_tip.z=" << rb_rt_tip.z << endl;
//        cout << " rb_rt_back.x=" << rb_rt_back.x << " rb_rt_back.y=" << rb_rt_back.y <<
//             " rb_rt_back.z=" << rb_rt_back.z << endl;
//        cout << " rb_lb_tip.x=" << rb_lb_tip.x << " rb_lb_tip.y=" << rb_lb_tip.y <<
//             " rb_lb_tip.z=" << rb_lb_tip.z << endl;
//        cout << " rb_lb_back.x=" << rb_lb_back.x << " rb_lb_back.y=" << rb_lb_back.y <<
//             " rb_lb_back.z=" << rb_lb_back.z << endl;
//        cout << " lt_lb_tip.x=" << lt_lb_tip.x << " lt_lb_tip.y=" << lt_lb_tip.y <<
//             " lt_lb_tip.z=" << lt_lb_tip.z << endl;
//        cout << " lt_lb_back.x=" << lt_lb_back.x << " lt_lb_back.y=" << lt_lb_back.y <<
//             " lt_lb_back.z=" << lt_lb_back.z << endl;
//        cout << " center.x=" << center.x << " center.y=" << center.y <<
//             " center.z=" << center.z << endl;
//        cout << " centerTip.x=" << centerTip.x << " centerTip.y=" << centerTip.y <<
//             " centerTip.z=" << centerTip.z << endl;
//        cout << " centerBack.x=" << centerBack.x << " centerBack.y=" << centerBack.y <<
//             " centerBack.z=" << centerBack.z << endl;
    }
    // 向量归一化

    // 向量叉乘


    glm::vec3 ltSet,rtSet,rbSet,lbSet,downCuspSet,center;

    glm::vec3 centerTip,centerBack;

    glm::vec3 lt_rt_tip,lt_rt_back;
    glm::vec3 lt_lb_tip,lt_lb_back;

    glm::vec3 rb_rt_tip,rb_rt_back;
    glm::vec3 rb_lb_tip,rb_lb_back;

};

class ConeXY{
    public:
        ConeXY() = default;
    glm::vec2 ltSet,rtSet,rbSet,lbSet,downCuspSet,center;
    glm::vec2 centerTip, centerBack;
    glm::vec2 lt_rt_tip,lt_rt_back;
    glm::vec2 lt_lb_tip,lt_lb_back;

    glm::vec2 rb_rt_tip,rb_rt_back;
    glm::vec2 rb_lb_tip,rb_lb_back;
};

class ConeDemo : public PolygonBase {
public:
    ConeDemo(glm::vec3 _lt,glm::vec3 _rt,glm::vec3 _rb,glm::vec3 _lb, glm::vec3 _downTip, unsigned char _debug_ = 0);

    ConeXYZ tblrdXYZ;
    ConeXYZ tblrdXYZ_unchange;
    ConeXYZ virtual_tblrdXYZ;

    ConeXY tblrdXY;

    float rounfBoxTipLen = 40.f;
    float radius;
    float height;
    float squareEdge;

    float height_1_3;
    float height_2_3;

    float radiusDivideHeight;
    unsigned char debugLine;

    bool flatLtRtFacing;
    bool flatRtRbFacing;
    bool flatRbLbFacing;
    bool flatLbLtFacing;
    bool rectFacing;

    bool displayNecessary;
    bool ScreenAxis2Self_SameFlat = 0;
    glm::vec3 startEye;

    void setTBLRDXYZ(glm::vec3 _lt, glm::vec3 _rt, glm::vec3 _rb, glm::vec3 _lb,glm::vec3 _downCusp);

    void setTBLRDXY(glm::vec2 _lt, glm::vec2 _rt, glm::vec2 _rb, glm::vec2 _lb, glm::vec2 _downCusp,
                    glm::vec2 _center,
                    glm::vec2 _lt_rt_tip,glm::vec2 _lt_rt_back,
                    glm::vec2 _lt_lb_tip,glm::vec2 _lt_lb_back,
                    glm::vec2 _rb_rt_tip,glm::vec2 _rb_rt_back,
                    glm::vec2 _rb_lb_tip,glm::vec2 _rb_lb_back,
                    glm::vec2 _centerTip, glm::vec2 _centerBack);
    void Draw_Tick(ScreenDemo* ScreenEye);

    bool cTipEyeCloser(glm::vec3 eyeCenter, glm::vec3 tip, glm::vec3 back);
#ifdef MAYBE_UNUSED
    [[maybe_unused]]bool PolyScanClicked(ScreenDemo* ScreenEye, int x,int y); // 点击到 圆锥
#endif
    void switchDebug(ScreenDemo* ScreenEye); // 切换调试模式

    glm::vec2 clickedSurfacePos;
    glm::vec3 surfacePos_SelfAxis; // 单法线 根
    glm::vec3 verticalTip_SelfAxis; // 单法线 尖
    glm::vec2 surfacePos2D;
    glm::vec2 surfaceTipPos2D;
    void freshSurfaceAndTipLine_Self(ScreenDemo* ScreenEye, bool boxTop);
    void drawVerticalTipByInfo(ScreenDemo* ScreenEye);


    float frontColor1_rgb[3];
    float frontColor2_rgb[3];
    float backColor_rgb[3];
    void setFrontColor(int color1, int color2);
    void setBackColor(int color);

    goLine32 world_toX; //  长 单位一向量
    goLine32 world_toY; //  宽 单位一向量
    goLine32 world_toDEEP; //  深 单位一向量
    void drawConeAxis(ScreenDemo* ScreenEye); // 画矩形坐标轴

private:
    void _solidBoxRect2D_front(ScreenDemo* ScreenEye, bool onFront);
    void _solidBoxRect2D_back(ScreenDemo* ScreenEye, bool onFront);
    void _solidBoxRect2D_left(ScreenDemo* ScreenEye, bool onFront);
    void _solidBoxRect2D_right(ScreenDemo* ScreenEye, bool onFront);
    void _solidBoxRect2D_top(ScreenDemo* ScreenEye, bool onFront);

    vector<lineBoundary> lineScanFillColor_front; // lx 左屏深  rx 右屏深  y 扫描线的y坐标
    vector<lineBoundary> lineScanFillColor_back; // lx 左屏深  rx 右屏深  y 扫描线的y坐标
    vector<lineBoundary> lineScanFillColor_left;
    vector<lineBoundary> lineScanFillColor_right;
    vector<lineBoundary> lineScanFillColor_top;

    vector<rowPixelDeep13> pixelEyeDeep_front;  // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelDeep13> pixelEyeDeep_back;  // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelDeep13> pixelEyeDeep_left; // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelDeep13> pixelEyeDeep_right; // XY2D 屏幕坐标  screenDeep 深度
    vector<rowPixelDeep13> pixelEyeDeep_top; // XY2D 屏幕坐标  screenDeep 深度

    float getZDeepByStep_ScreenAxis(float _step, float x, float y);

    char getAreaByPos_selfAxis(glm::vec3 _pos);

    goLine32 virtual_toX; //  长 单位一向量
    goLine32 virtual_toY; //  宽 单位一向量
    goLine32 virtual_toDEEP; //  深 单位一向量
    void freshVirtualGoX();
    void freshVirtualGoY();
    void freshVirtualGoDEEP();
    glm::vec3 virtual_goX(glm::vec3 _srcXYZ, float _move);
    glm::vec3 virtual_goY(glm::vec3 _srcXYZ, float _move);
    glm::vec3 virtual_goDEEP(glm::vec3 _srcXYZ, float _move);

    [[maybe_unused]]float virtual_a_b_c_d_XY[4]; // 共面方程信息
    [[maybe_unused]]float virtual_a_b_c_d_XZ[4];
    [[maybe_unused]]float virtual_a_b_c_d_YZ[4];
    [[maybe_unused]]void freshVirtualFlatXY(); // 计算共面方程信息
    [[maybe_unused]]void freshVirtualFlatXZ();
    [[maybe_unused]]void freshVirtualFlatYZ();

    float virtual_Point2FlatYZ(glm::vec3& _point); // 点到YZ平面的距离
    float virtual_Point2FlatXZ(glm::vec3& _point); // 点到XZ平面的距离
    float virtual_Point2FlatXY(glm::vec3& _point); // 点到XY平面的距离

    [[maybe_unused]]glm::vec3 screenXYZ2SelfXYZ(glm::vec3 _screenXYZ); // 屏幕坐标转自身坐标

    [[maybe_unused]]glm::vec3 screenXY2SelfXYZ_LockAxis(glm::vec2 _screenXY); // 屏幕坐标转自身坐标 锁轴

    Quaternion frameRotateInfo_q;
    void freshFrameRotateInfo();
    glm::vec3 back2Screen000(glm::vec3 _src);
    glm::vec3 screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos); // 屏幕坐标转自身坐标2
    glm::vec3 screenXY2SelfXYZ(glm::vec2 _screenXY); // 屏幕坐标转自身坐标2

    glm::vec3 eyeOnSelfAxis;
    [[maybe_unused]]glm::vec3 screenLT_onSelfAxis;
    [[maybe_unused]]glm::vec3 screenRT_onSelfAxis;
    [[maybe_unused]]glm::vec3 screenLB_onSelfAxis;
    pair<float,float> getEyeThenStepByScreenXY(glm::vec2 _screenXY, bool quoteInfo = false);
    glm::vec3 getEyeThenStepSelfPosNear_ByScreenXY(glm::vec2 _screenXY);
    float getEyeThenStepOfFlatByScreenXY(glm::vec2 _screenXY);
    glm::vec3 get_EyeThenStepPos_OfCircle_ByScreenXY(glm::vec2 _screenXY);



    float frameScreenNear,frameScreenFar;

    [[maybe_unused]]goLine32 screenGoX_OnSelfAxis; //  长 单位一向量
    [[maybe_unused]]goLine32 screenGoY_OnSelfAxis; //  宽 单位一向量
    [[maybe_unused]]void freshScreenGoX_OnSelfAxis();
    [[maybe_unused]]void freshScreenGoY_OnSelfAxis();

    BGR3f white2ColorfulScreenDeep(float pointDeep, char colorType);

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

    glm::vec3 PosSelfAxis2ScreenAxis(glm::vec3 p1);

};

#endif //POLYGONDISPLAY_CONEDEMO_H
