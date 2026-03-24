//
// Created by iceoc0 on 2025/3/27.
//

#ifndef POLYGONDISPLAY_SCREENDEMO_H
#define POLYGONDISPLAY_SCREENDEMO_H

#include "PolygonBase.h"


#ifndef M_PI
#define M_PI		3.14159265358979323846f
#endif

// 原点在屏幕左上角

#ifndef WHITE
#define WHITE 0xFFFFFF
#endif
#ifndef RED
#define	RED	0x0000AA
#endif

#ifndef _BGR3f
#define _BGR3f
class BGR3f{
public:
    BGR3f() = default;
    float b1,g1,r1;
//    int b255,g255,r255;
//    signed char b127,g127,r127;
    void setBGR(int _color, int _type){
        if(_type==1){ // 0~1
            this->b1=(float)((_color>>16)&0xff) / 255.0f;
            this->g1=(float)((_color>>8)&0xff) / 255.0f;
            this->r1=(float)(_color&0xff) / 255.0f;
        }
//        else if(_type==127){ // -127~127
//            this->b127=(signed char) (((_color>>16)&0xff) - 128);
//            this->g127=(signed char) (((_color>>8)&0xff) - 128);
//            this->r127=(signed char) ((_color&0xff) - 128);
//        }else if(_type==255){ // 0~255
//            this->b255=((_color>>16)&0xff);
//            this->g255=((_color>>8)&0xff);
//            this->r255=(_color&0xff);
//        }

    }
    void setRGB3f(float r01, float g01, float b01){
        r1 = r01;
        g1 = g01;
        b1 = b01;
    }
};
#endif

#ifndef _Ray
#define _Ray
class Ray{
public:
    Ray() = default;
    Ray(glm::vec3 _src, glm::vec3 _dir) {
        this->src = _src;
        this->dir = _dir;
    }
    glm::vec3 src; // 起点
    glm::vec3 dir; // 方向
};
#endif

#ifndef _angleXYZ
#define _angleXYZ
typedef struct {
    float y; // x转
    float x; // y转
    float z; // deep转
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


#ifndef _pixelDeep11
#define _pixelDeep11
struct pixelDeep11{
    int x; // long x long y
    float eyeDeep; // float deep
};
#endif

#ifndef _rowPixelDeep11
#define _rowPixelDeep11
struct rowPixelDeep11 {
    vector<pixelDeep11> pixelDeeps; // 行的像素深度
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


#ifndef _AxisInfo
#define _AxisInfo
struct AxisInfo{
    glm::vec3 _0_0_0; // 原点
    goLine32 toX;
    goLine32 toY;
    goLine32 toDEEP;
    float a_b_c_d_xyFlat[4]; // 共面点函数 正视
    float a_b_c_d_xzFlat[4]; // 共面点函数 俯视
    float a_b_c_d_yzFlat[4]; // 共面点函数 左视
};
#endif

class CubeBoxXYZ_{
public:
    CubeBoxXYZ_() = default;
    CubeBoxXYZ_(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _lbn, glm::vec3 _ltf){
        // OXYZ 左上前 确定 包围盒
        ltnSet = _ltn;
        rtnSet = _rtn;
        lbnSet = _lbn;
        ltfSet = _ltf;
    }
    CubeBoxXYZ_(glm::vec3& _ltn, glm::vec3& _rtn, glm::vec3& _rbn, glm::vec3& _lbn,
               glm::vec3& _ltf, glm::vec3& _rtf, glm::vec3& _rbf, glm::vec3& _lbf){
        ltnSet = _ltn;
        rtnSet = _rtn;
        rbnSet = _rbn;
        lbnSet = _lbn;

        ltfSet = _ltf;
        rtfSet = _rtf;
        rbfSet = _rbf;
        lbfSet = _lbf;

        center.x = (ltnSet.x + rbfSet.x) / 2.f;
        center.y = (ltnSet.y + rbfSet.y) / 2.f;
        center.z = (ltnSet.z + rbfSet.z) / 2.f;

    }
    glm::vec3 ltnSet;
    glm::vec3 rtnSet;
    glm::vec3 rbnSet;
    glm::vec3 lbnSet;

    glm::vec3 ltfSet;
    glm::vec3 rtfSet;
    glm::vec3 rbfSet;
    glm::vec3 lbfSet;

    glm::vec3 center;
DEBUG_SECTION(
    // 左上
    glm::vec3 rtn_ltn_tip; // x 左
    glm::vec3 lbn_ltn_tip; // y 上
    glm::vec3 ltf_ltn_tip; // z 后

    //右下
    glm::vec3 lbf_rbf_tip; // x 右
    glm::vec3 rtf_rbf_tip; // y 下
    glm::vec3 rbn_rbf_tip; // z 前
)
};

class CubeBoxXY_{
public:
    CubeBoxXY_() = default;

    glm::vec2 ltnSet;
    glm::vec2 rtnSet;
    glm::vec2 rbnSet;
    glm::vec2 lbnSet;

    glm::vec2 ltfSet;
    glm::vec2 rtfSet;
    glm::vec2 rbfSet;
    glm::vec2 lbfSet;

    glm::vec2 center;
DEBUG_SECTION(
    // 左上
    glm::vec2 rtn_ltn_tip; // x 左
    glm::vec2 lbn_ltn_tip; // y 上
    glm::vec2 ltf_ltn_tip; // z 后

    //右下
    glm::vec2 lbf_rbf_tip; // x 右
    glm::vec2 rtf_rbf_tip; // y 下
    glm::vec2 rbn_rbf_tip; // z 前
)
};
// debug
inline string showVec3(glm::vec3& src) {
    return std::format("({},{},{})",src.x,src.y,src.z);
}
inline string showVec3(glm::dvec3& src) {
    return std::format("({},{},{})",src.x,src.y,src.z);
}
inline string showVec2(glm::vec2& src) {
    return std::format("({},{})",src.x,src.y);
}



// 声明类 ScreenDemo
class ScreenDemo {
public:
    ScreenDemo(glm::vec3 _lt_xyz, glm::vec3 _rt_xyz, glm::vec3 _rb_xyz, glm::vec3 _lb_xyz,
             glm::vec3 _center_xyz, glm::vec3 _centerTip_xyz,int _type);
//    ScreenDemo(glm::vec3 _lt_xyz, glm::vec3 _rt_xyz, glm::vec3 _rb_xyz, glm::vec3 _lb_xyz,
//             glm::vec3 _center_xyz, glm::vec3 _centerTip_xyz,int _type,unsigned char _debug_);

    void freshInfo();

    glm::vec3 getCenter() ; // 获取中心点

    glm::vec3 getCenterTip() ; // 获取中心点


    float rectWidth; // 宽度
    float rectHeight; // 高度
    float rectDepth; // 深度 正1000

    Matrix2D<glm::vec3> coloredPixels; // [y * screenWidth + x]
    Matrix2D<float> zBuffer;
    Matrix2D<PolygonBase*> objBuffer;
    // int indexOfPixelsVector(int x, int y) const ;
    glm::ivec2 pos2DbyIndex(int _index);

    static void line2ScreenBuffer(ScreenDemo* ScreenEye, float x0f, float y0f, float x1f, float y1f,
                                 float color[],float zDeep);
    static void line2ScreenBuffer_(ScreenDemo* ScreenEye, float x0f, float y0f, float x1f, float y1f,
                                 const glm::vec3& color,float zDeep);
    static void downLine2ScreenBuffer(ScreenDemo* ScreenEye, int xf, int y0f, int y1f,float color[]);

    void putPixel(int x, int y,float color[],float depth,PolygonBase* _this);
    void putPixel_(int x, int y,glm::vec3& color,float depth,PolygonBase* _this);
    void putPixel2(int x, int y,float color[]);

    bool outOfScreen(float x, float y); // 判断是否超出屏幕

    glm::ivec2 clickedLast;
    bool objBufferFresh; // 百万级对象 缓冲区是否刷新
    void flushBatchDraw() ;

    RectXYZ tblrXYZ; // 三维位置矩形
    RectXYZ tblrXYZ_unchange; // 三维位置矩形

    angleXYZ_t angleXYZ;
    // lt rt rb lb centerTip
    Quaternion frameRotateInfo_q;

    float _backFont; // 法线向量取反

    goLine32 screenOnWorld_toX; //  长 单位一向量
    goLine32 screenOnWorld_toY; //  宽 单位一向量
    goLine32 screenOnWorld_toDEEP; //  深 单位一向量
    void freshGoX();
    void freshGoY();
    void freshGoDEEP();
    glm::vec3 goX(glm::vec3& _srcXYZ, float _move);
    glm::vec3 goY(glm::vec3& _srcXYZ, float _move);
    glm::vec3 goDEEP(glm::vec3& _srcXYZ, float _move);
    [[ maybe_unused]]void drawRectAxis(ScreenDemo* ScreenEye); // 画矩形坐标轴

    glm::vec3 worldXYZ2ScreenXYZ(glm::vec3 worldXYZ); // 世界坐标转屏幕坐标
    glm::vec3 worldXYZ2ScreenXYZ_AxisLock(glm::vec3 worldXYZ); // 世界坐标转屏幕坐标2

    void freshFrameRotateInfo();
    void freshAxisWorldOnAxisScreen_quat();
    glm::vec3 worldXYZ2ScreenXYZ_quat(const glm::vec3& worldXYZ);

    [[ maybe_unused]]AxisInfo axisWorldOnAxisScreen; // 坐标轴信息
    [[ maybe_unused]]void freshAxisWorldOnAxisScreen(); // 计算世界坐标轴 在屏幕系下 信息   平移后 旋转后 都刷新


    [[ maybe_unused]]glm::vec3 screenXYZ2WorldXYZ(glm::vec3 screenXYZ); // 屏幕坐标转世界坐标
    [[ maybe_unused]]float screen2World_GetZ(glm::vec3 screenXYZ); // 屏幕转世界
    [[ maybe_unused]]float screen2World_Gety(glm::vec3 screenXYZ); // 屏幕转世界
    [[ maybe_unused]]float screen2World_Getx(glm::vec3 screenXYZ); // 屏幕转世界

    float leftLookAngleOfEye[3]; // 上边 中点 下边
    void initLeftLookAngleOfSelfAxis(); // 初始化左视角度
    [[ maybe_unused]]void headUp(float angle); // 俯仰角
    [[ maybe_unused]]pair<float,float> headUpPoint(float center[], float point[],float baseAngle, float angle);
    [[ maybe_unused]]void headDown(float angle); // 俯仰角

    float downLookAngle[3]; // 左边 中点 右边
    void initDownLookAngleOfSelfAxis(); // 初始化左视角度
    [[ maybe_unused]]void headLeft(float angle); // 左右角
    [[ maybe_unused]]pair<float,float> headLeftPoint(float center[], float point[],float baseAngle, float angle);
    [[ maybe_unused]]void headRight(float angle); // 左右角

    float frontLook4Corner[4]; // lt rt rb lb
    void initFrontLook4Corner(); // 初始化正视角度
    [[ maybe_unused]]void headRollBackClock(float angle);
    [[ maybe_unused]]pair<float,float> headRollBackPoint(float center[], float point[], float baseAngle, float angle);
    [[ maybe_unused]]void headRollForwardClock(float angle);


    [[ maybe_unused]]goLine64 rotate_vector2(goLine64 vec2zero, Quaternion q);
    static Quaternion create_rotation(double angle_deg, goLine64 axis);


    goLine64 getScreenOnWorld2X64();
    goLine64 getScreenOnWorld2Z64();


    glm::vec3 tiltTurnPoint2(const glm::vec3& p1); // 世界系 屏幕系 main !

    inline static goLine32 get_AgoB_direction3D(glm::vec3 pa, glm::vec3 pb);


    glm::vec3 back2World000(glm::vec3 _src);

    // 位置 struct{long;long} .y .x
    void _init_main(glm::vec3& _lt_xyz, glm::vec3& _rt_xyz, glm::vec3& _rb_xyz,glm::vec3& _lb_xyz,
                    glm::vec3& _center_xyz, glm::vec3& _centerTip_xyz, int _type);
    [[maybe_unused]]bool checkRowFlatFile(string& fileName);
    [[maybe_unused]]bool checkColFlatFile(string& fileName);

    [[maybe_unused]]void freshRowFlatFile(string& fileName);
    [[maybe_unused]]void freshColFlatFile(string& fileName);

    [[maybe_unused]]void readRowFlatFile(string& fileName);
    [[maybe_unused]]vector<array<float,4>> rowFlatData; // 行平面数据
    [[maybe_unused]]void readColFlatFile(string& fileName);
    [[maybe_unused]]vector<array<float,4>> colFlatData; // 列平面数据

    float a_b_c_d_xyFlat[4]; // 共面点函数 正视
    float a_b_c_d_xzFlat[4]; // 共面点函数 俯视
    float a_b_c_d_yzFlat[4]; // 共面点函数 左视
    [[ maybe_unused]]void ax1_by1_cz1_d1_OnWorld();
    [[ maybe_unused]]void freshScreenAxisOnWorld();

    float world2ScreenXYZ_GetZ(glm::vec3 worldXYZ); // 世界转屏幕
    float world2ScreenXYZ_Gety(glm::vec3 worldXYZ); // 世界转屏幕
    float world2ScreenXYZ_Getx(glm::vec3 worldXYZ); // 世界转屏幕

    [[maybe_unused]] goLine32 eye2ScreenPixel_dxyz(float x, float y);
    [[maybe_unused]] glm::vec3 getEyeGoXYZbyXY(float x, float y); // 2D坐标转3D坐标
    [[maybe_unused]] float getEyeDeepbyXY(float x, float y); // 2D坐标转深度

    // 计算直线点与屏幕的距离

    [[maybe_unused]]void freshRectAxis();

    glm::vec3 tiltAxis3D[4]; // 四个倾斜轴的顶点 中 x y z
    glm::vec3 parallelAxis3D[4]; // 四个平行轴的顶点
    glm::vec2 tiltAxis2D_f[4]; // 四个倾斜轴的顶点 中 x y z
    glm::vec2 parallelAxis2D_f[4]; // 四个平行轴的顶点
    [[maybe_unused]]void freshTiltAxis(); // 计算倾斜轴
    [[maybe_unused]]void freshParallelAxis(); // 计算平行轴

    [[ maybe_unused]]void drawTiltAxis(ScreenDemo* ScreenEye); // 画倾斜轴
    [[ maybe_unused]]void drawParallelAxis(ScreenDemo* ScreenEye); // 画平行轴


};

struct _3d_2d_go_func{
    glm::vec2 (*_3d_2d_go)(ScreenDemo*, glm::vec3, glm::vec3*);
    glm::vec2 (*_3d_2d)(ScreenDemo*, float, float, float);

};
#endif //POLYGONDISPLAY_SCREENDEMO_H
