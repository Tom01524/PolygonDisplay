//
// Created by iceoc0 on 2025/9/17.
//

#ifndef POLYGONDISPLAY_POLYGONBASE_H
#define POLYGONDISPLAY_POLYGONBASE_H
#include "GLFW/glfw3.h"
#include <opencv2/opencv.hpp> // 图片加载

#include <glm.hpp>
#include <detail/type_quat.hpp> // glm::quat
#include "Eigen/Eigenvalues" // 特征值计算 解方程
#include <unsupported/Eigen/Polynomials>
// #include<iostream> // cout cerr endl
#include<vector> // 扩容数组

#include<print> // println()
#include<random>
#include <filesystem>
#include <fstream>
#include <mutex>

#include <expected>
#include<format>


#if defined(_MSC_VER)
#include <intrin.h> // MSVC
#pragma message("msvc compiler")
    #ifdef _DEBUG
        // debug 模式 才运行
        #define DEBUG_ON
        #define DEBUG_SECTION(code) code

        #define NONDEBUG_SECTION(code)
    #else
        #define DEBUG_SECTION(code)

        #define NONDEBUG_SECTION(code) code
    #endif
#elif defined(__GNUC__)
#error GCC未兼容
#elif defined(__clang__)
#error clang未兼容
#else
#error 未知编译器
#endif

using std::vector, std::pair, std::runtime_error, std::string, std::string_view,
std::numeric_limits, std::to_string, std::array, std::complex, std::ifstream, std::make_pair,
std::unique_ptr, std::make_unique,std::ofstream, std::stringstream, std::println, std::print,
std::map, std::lock_guard, std::mutex;

#ifndef DEBUG_ON
    #define EIGEN_NO_DEBUG // 禁用eigen的边界检查
    #define EIGEN_NO_STATIC_ASSERT // 禁用静态断言
    #define EIGEN_DONT_PARALLELIZE // 如需控制并行化
#endif

#ifndef _Quaternion
#define _Quaternion

typedef glm::quat Quaternion;
#endif

#ifndef _goLine32
#define _goLine32
union goLine32{
    struct {
        float dx;
        float dy;
        float dz;
    };
    glm::vec3 _;
    goLine32() = default;
    goLine32(float x, float y, float z):
    _(x,y,z){}
    goLine32(glm::vec3 v):_(v){}
};

#endif


#ifndef _goLine64
#define _goLine64
union goLine64{
    struct {
        double dx;
        double dy;
        double dz;
    };
    glm::dvec3 _;
    goLine64() = default;
    goLine64(double x, double y, double z):
    _(x,y,z){}
    goLine64(glm::vec3 v):_(v){}
};
#endif

#ifndef _order3point_
#define _order3point_
struct _order3point{
    glm::vec2 point;
    int _th; // 0 rt 1 lb 2 lt
};
#endif

#ifndef _order4point_
#define _order4point_

struct _order4point{
    glm::vec2 point;
    int _th; // 0 lt 1 rt 2 rb 3 lb
};

#endif

#ifndef _lineBoundary
#define _lineBoundary
struct lineBoundary{

    int y; // 行 上0下大
    float lx;
    float rx;
};
#endif

class CubeBox3D{
public:
    CubeBox3D() = default;
    //    CubeBox3D(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
    //              glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf){
    //        ltn = _ltn;
    //        rtn = _rtn;
    //        rbn = _rbn;
    //        lbn = _lbn;

    //        ltf = _ltf;
    //        rtf = _rtf;
    //        rbf = _rbf;
    //        lbf = _lbf;

    //        center.x = (ltn.x + rbf.x) / 2.f;
    //        center.y = (ltn.y + rbf.y) / 2.f;
    //        center.z = (ltn.z + rbf.z) / 2.f;

    //    }
    glm::vec3 ltnSet, rtnSet, rbnSet, lbnSet;

    glm::vec3 ltfSet, rtfSet, rbfSet, lbfSet;

    glm::vec3 center;

};

template<typename AnyType>
class Matrix2D {
// Non puch_back(),emplace_back(),pop_back(),erase().
// just at(),[] is ok!
public:
    size_t outterMax, innerMax;
    vector<AnyType> data;
    Matrix2D() = default;
    Matrix2D(size_t _rows, size_t _cols):
    outterMax(_rows), innerMax(_cols), data(_rows*_cols) {}
    AnyType& operator()(size_t outter, size_t inner) {
        return data[outter*innerMax+inner];
    }
};

class PolygonBase{
public:
    PolygonBase() = default;
    PolygonBase(int type);
    virtual ~PolygonBase() = default;
    int type_;
    glm::vec3 startEye; // 视点
    static void rasterLine(int x0, int y0, int x1, int y1, vector<glm::vec2>& _linePoints);

    static float distanceOfPoint2D(const glm::vec2& p1,const glm::vec2& p2){
        float betweenX = p1.x - p2.x, betweenY = p1.y - p2.y;
        float distance = glm::sqrt(betweenX*betweenX + betweenY*betweenY);
        return distance;
    }

    static Quaternion getFrameRotateInfo_(goLine32& goX, goLine32& goZ);
    inline static Quaternion multiply(Quaternion& a, Quaternion& b);
    static void rotate_vector(goLine64& vec2zero, Quaternion& q);
    static Quaternion create_rotation2(double angle_rad,const goLine64& axis);

    [[maybe_unused]][[nodiscard]]
    static glm::vec3 tiltTurnFrom000(glm::vec3& outP, glm::vec3& obliqueDir, float angle_deg); // 绕任意轴旋转 从 原点

    static float angleBetweenVectors_deg(const glm::vec3& _a, const glm::vec3& _b);
    static double angleBetweenVectors_rad(const glm::vec3& _a, const glm::vec3& _b);


    static void loadImgRGB01(string& filename, Matrix2D<glm::vec3>& _imgRGB);

    static void fresh2D_scanRows_3(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3,
                                   vector<lineBoundary>* _lineBoundaries, int obj_t);
    static void setLineScanScreenDeepLR_3(_order3point order3point[], glm::vec2 p_3[],
                                          vector<lineBoundary>* _lineBoundaries, int obj_t) ;

    static float clampY(float y); // 限制 y 范围
    static void fresh2D_scanRows_4(glm::vec2& p1, glm::vec2& p2, glm::vec2& p3, glm::vec2& p4,
                                   vector<lineBoundary>* _lineBoundaries, int obj_t);
    // 计算左右边界 深度
    static void setLineScanScreenDeepLR_4(_order4point order4point[], glm::vec2 p_4[],
                                          vector<lineBoundary>* _lineBoundaries, int obj_t);

    static void fresh2D_scanRows_4_noClear(glm::vec2& p1, glm::vec2& p2, glm::vec2& p3, glm::vec2& p4,
                                           vector<lineBoundary>* _lineBoundaries, int obj_t);
    // 计算左右边界 深度
    static void setLineScanScreenDeepLR_4_noClear(_order4point order4point[], glm::vec2 p_4[],
                                                  vector<lineBoundary>* _lineBoundaries, int obj_t);
    static float getXby_line_y_2D_4(glm::vec2 p_4[], int upperP_th, int lowerP_th, float y, int obj_t);

    static bool midPointLineLeft(glm::vec2& lineBegin, glm::vec2& lineEnd, glm::vec2& midPoint);
    inline static float xLR_editInRange(float _x);
    static bool yOutOfScreen(int y); // 判断是否超出屏幕

    static bool isFrontFacing(const glm::vec3& eyePos,
                              const goLine32& flatVertical,
                              const glm::vec3& flatCenter);
    inline static glm::vec3 calcReflect(const glm::vec3& inDirection, const glm::vec3& normal);
    double pow2(double x);
    double pow3(double x);
    double pow4(double x);
    double pow5(double x);
    double pow6(double x);
    double pow7(double x);
    double pow8(double x);
    double pow9(double x);
};

// 8点包围盒 行扫描12边
class CubeBox2dEdge {
public:
    CubeBox2dEdge() = default;
    glm::vec2 p1, p2; // 顶点坐标
    pair<glm::vec2,glm::vec2> min_max_p;

    void freshP1P2(glm::vec2& _p1, glm::vec2& _p2){
        this->p1 = _p1;
        this->p2 = _p2;
        setMinMaxY_P_byP1P2();

    }

    void setMinMaxY_P_byP1P2(){
        if(p1.y<=p2.y){ // 计算x 用
            min_max_p = {p1,p2};
        }else{
            min_max_p = {p2,p1};
        }
        // 断言 min_y <= max_y
        //assert(min_max_p.first.y <= min_max_p.second.y);

    }

    float get_x_by_y(float y){
        float x;
        glm::vec2 upperP = min_max_p.first, lowerP=min_max_p.second;

        // y不超 上下限
        y = std::clamp(y, upperP.y, lowerP.y);


        if(upperP.y != lowerP.y){
            x = upperP.x -(upperP.x-lowerP.x)*(y - upperP.y)/(lowerP.y - upperP.y);

        }else{
            x = lowerP.x;// - (y - upperP.y) * (upperP.x - lowerP.x) / 1e-5f;

            println(stderr,"包围盒 upperP.y: {}, lowerP.y: {} 相等!!",upperP.y,lowerP.y);
        }
        return PolygonBase::xLR_editInRange(x); // 左右x 哪个来了都不能出界!
    }
    bool this_y_in_mine(float y){
        // 比小y大  比大y小
        return y >= min_max_p.first.y && y <= min_max_p.second.y;

    }

};
class CubeBox2D {
public:
    CubeBox2D() = default;

    glm::vec2 ltn, rtn, rbn, lbn,
            ltf, rtf, rbf, lbf; // 长宽高
    CubeBox2dEdge ltn_rtn, rtn_rbn, rbn_lbn, lbn_ltn;
    CubeBox2dEdge ltf_rtf, rtf_rbf, rbf_lbf, lbf_ltf; // 边
    CubeBox2dEdge ltn_ltf, rtn_rtf, rbn_rbf, lbn_lbf; // 边
    glm::vec2 center; // 中心
    pair<float, float> total_min_max_y; // 最小最大z
    void set13P(glm::vec2& _ltn, glm::vec2& _rtn, glm::vec2& _rbn, glm::vec2& _lbn,
                glm::vec2& _ltf, glm::vec2& _rtf, glm::vec2& _rbf, glm::vec2& _lbf,
                glm::vec2& _center) {
        this->ltn = _ltn;
        this->rtn = _rtn;
        this->rbn = _rbn;
        this->lbn = _lbn;
        this->ltf = _ltf;
        this->rtf = _rtf;
        this->rbf = _rbf;
        this->lbf = _lbf;
        this->center = _center;
        set12Edges();
        setTotalMinMaxY_by_P();
    }

    void set12Edges() {
        ltn_rtn.freshP1P2(ltn, rtn);
        rtn_rbn.freshP1P2(rtn, rbn);
        rbn_lbn.freshP1P2(rbn, lbn);
        lbn_ltn.freshP1P2(lbn, ltn);

        ltf_rtf.freshP1P2(ltf, rtf);
        rtf_rbf.freshP1P2(rtf, rbf);
        rbf_lbf.freshP1P2(rbf, lbf);
        lbf_ltf.freshP1P2(lbf, ltf);

        ltn_ltf.freshP1P2(ltn, ltf);
        rtn_rtf.freshP1P2(rtn, rtf);
        rbn_rbf.freshP1P2(rbn, rbf);
        lbn_lbf.freshP1P2(lbn, lbf);
    }

    glm::vec2 &getP2D(int index) {
        switch (index) {
            case 0:
                return this->ltn;
            case 1:
                return this->rtn;
            case 2:
                return this->rbn;
            case 3:
                return this->lbn;
            case 4:
                return this->ltf;
            case 5:
                return this->rtf;
            case 6:
                return this->rbf;
            case 7:
                return this->lbf;
            case 8:
                return this->center;
            default:
                throw runtime_error("CubeBox2D::getP2D() index out of range");
        }
    }


    CubeBox2dEdge &getEdge2D(int index) {
        switch (index) {
            case 0:
                return this->ltn_rtn;
            case 1:
                return this->rtn_rbn;
            case 2:
                return this->rbn_lbn;
            case 3:
                return this->lbn_ltn;
            case 4:
                return this->ltf_rtf;
            case 5:
                return this->rtf_rbf;
            case 6:
                return this->rbf_lbf;
            case 7:
                return this->lbf_ltf;
            case 8:
                return this->ltn_ltf;
            case 9:
                return this->rtn_rtf;
            case 10:
                return this->rbn_rbf;
            case 11:
                return this->lbn_lbf;
            default:
                throw runtime_error("CubeBox2D::getEdge2D() index out of range");

        }
    }

    void setTotalMinMaxY_by_P() {
        total_min_max_y.first = getP2D(0).y;
        total_min_max_y.second = getP2D(0).y;

        for(int i = 0; i < 8; ++i) {
            glm::vec2 &p = getP2D(i);
            // 还有更小
            if (p.y < total_min_max_y.first) {
                total_min_max_y.first = p.y;
            }
            // 还有更大
            if (p.y > total_min_max_y.second) {
                total_min_max_y.second = p.y;
            }
        }
        // 高在 屏幕内
        total_min_max_y.first = PolygonBase::clampY(total_min_max_y.first);
        total_min_max_y.second = PolygonBase::clampY(total_min_max_y.second);

    }

    void setLineBounary(vector<lineBoundary> &_lineBoundaries) {

        //if (!_lineBoundaries.empty())
            _lineBoundaries.clear();


        int total_min_y = (int) total_min_max_y.first;
        int total_max_y = (int) total_min_max_y.second;
//        println("total_min_y: {}, total_max_y: {}",total_min_y, total_max_y);
        lineBoundary nowLine;
        for(int _y = total_min_y; _y < total_max_y; ++_y) { // 每行
            nowLine.y = _y;
//            println("nowLine.y: {}", nowLine.y);
            nowLine.lx = -1;
            nowLine.rx = -1;
            // 遍历 12个边
            for(int j = 0; j < 12; ++j) { // 行最
                CubeBox2dEdge &edgeNow = getEdge2D(j);
                if (!edgeNow.this_y_in_mine(_y)) continue; // 边不在本行
                    if (nowLine.lx == -1) { // 首次 初始值 lx rx
                        float firstEdge_y2x = edgeNow.get_x_by_y(_y);
                        nowLine.lx = firstEdge_y2x;
                        nowLine.rx = firstEdge_y2x;

                    } else {
                        float afterEdge_y2x = edgeNow.get_x_by_y(_y);

                        // 有更小 有更大
                        if (afterEdge_y2x < nowLine.lx) {
                            nowLine.lx = afterEdge_y2x;
                        } else if (afterEdge_y2x > nowLine.rx) {
                            nowLine.rx = afterEdge_y2x;
                        }
                    }



            }
            // lx rx 都找完了最值  y也在 总内
            _lineBoundaries.emplace_back(nowLine);
//            cout << "nowLine.y: " << nowLine.y <<
//                 " nowLine.lx: " << nowLine.lx << " nowLine.rx: " << nowLine.rx << endl;

        }
    }

};

// 定义幂运算宏（提高可读性）


#endif //POLYGONDISPLAY_POLYGONBASE_H
