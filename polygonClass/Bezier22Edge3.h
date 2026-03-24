//
// Created by iceoc0 on 2026/1/17.
//

#ifndef POLYGONDISPLAY_BEZIER22EDGE3_H
#define POLYGONDISPLAY_BEZIER22EDGE3_H
#include "./AxisDemo.h"

/*
*    0
*  _0 _2
*  1 _1  2
*/
struct controlPoint3D {
    controlPoint3D() = default; // 保留默认构造
    void freshP(controlPoint3D& _src) {
        this->tip[0]=_src.tip[0];
        this->tip[1]=_src.tip[1];
        this->tip[2]=_src.tip[2];
        this->edgeMid[0]=_src.edgeMid[0];
        this->edgeMid[1]=_src.edgeMid[1];
        this->edgeMid[2]=_src.edgeMid[2];
    }
    glm::vec3 tip[3];
    glm::vec3 edgeMid[3];
};
struct controlPoint2D {
    controlPoint2D() = default; // 保留默认构造
    void freshP(controlPoint2D& _src) {
        this->tip[0]=_src.tip[0];
        this->tip[1]=_src.tip[1];
        this->tip[2]=_src.tip[2];
        this->edgeMid[0]=_src.edgeMid[0];
        this->edgeMid[1]=_src.edgeMid[1];
        this->edgeMid[2]=_src.edgeMid[2];
    }
    glm::vec2 tip[3];
    glm::vec2 edgeMid[3];
};
struct trianglePair {
    trianglePair() = default;
    bool onFront1, onFront2;
    glm::ivec3 index1, index2;
    vector<lineBoundary> scanRow1, scanRow2;
    void freshLineBoundary_triangle(vector<glm::vec2>& _Grid2D);
    void draw2Triangle(ScreenDemo* ScreenEye, PolygonBase* Self);
    float getDeep_ByVirtual3Point(PolygonBase* Self, float x, float y,char triangle);
};
struct triangleSelf {
    triangleSelf() = default;
    bool onFront1;
    glm::ivec3 index1;
    vector<lineBoundary> scanRow1;
    void freshLineBoundary_triangle(vector<glm::vec2>& _Grid2D);
    void draw2Triangle(ScreenDemo* ScreenEye, PolygonBase* Self);
    float getDeep_ByVirtual3Point(PolygonBase* Self, float x, float y);
};

#ifndef TBLRFB__
#define TBLRFB__
struct TBLRFB {
    float topY, bottomY, leftX, rightX, nearZ, farZ;
};
#endif

struct oneUVWInfo {
    glm::dvec3 uvw;
    glm::dvec3 surfaceP_screenAxis;
    double far2Eye_22;
    glm::vec3 color;
    int x;
    std::expected<bool,char> onFront;
};
struct rowUVWInfo {
    vector<std::expected<oneUVWInfo,char>> rowsInfo;
    int y;
};

constexpr int resolution = 7;
constexpr size_t sizeNeed = (resolution + 1) * (resolution + 2) / 2;
constexpr float resolutionf = static_cast<float>(resolution);
class Bezier22Edge3 : public PolygonBase {
public:
    Bezier22Edge3(controlPoint3D& _P,unsigned char __debug);

    controlPoint3D P_world, P_unchange;

    controlPoint3D P_virtual;
    controlPoint2D P2D;

    glm::vec3 colorP, colorGrid, backColor;
    void generateGrid();
    glm::vec3 evaluatePatch2_screenAxis(const glm::vec3& _uvw);
    CubeBoxXYZ_ scanBox3D_world;
    CubeBoxXYZ_ scanBox3D_unchange; // 锁坐标系
    CubeBoxXYZ_ virtual_scanBox3D; // 屏幕系
    CubeBoxXY_ scanBox2D_;

    TBLRFB boxVolume;
    bool renderNext; // false

    bool firstRendered_front;
    bool firstRendered_back;
    bool firstRendered_left;
    bool firstRendered_right;
    bool firstRendered_top;
    bool firstRendered_bottom;

DEBUG_SECTION(
    float rounfBoxTipLen = 40.f;
)
    float boxLenX, boxLenY, boxLenZ;
    float boxLenHalfX, boxLenHalfY, boxLenHalfZ;

    goLine32 world_toX; //  长 单位一向量
    goLine32 world_toY; //  宽 单位一向量
    goLine32 world_toDEEP; //  深 单位一向量
    void freshGoX();
    void freshGoY();
    void freshGoDEEP();

    void goX_(glm::vec3& _srcXYZ, float _move);
    void goY_(glm::vec3& _srcXYZ, float _move);
    void goDEEP_(glm::vec3& _srcXYZ, float _move);
    bool flatFrontFacing;
    bool flatBackFacing;
    bool flatLeftFacing;
    bool flatRightFacing;
    bool flatTopFacing;
    bool flatBottomFacing;

    TBLRFB initBox_TBLRNF(); // Top Bottom Left Right Near Far
    void initBoxInfo();

    vector<glm::vec3> Grid_world = vector<glm::vec3>(sizeNeed),
    Grid_unchange = vector<glm::vec3>(sizeNeed),
    Grid_virtual = vector<glm::vec3>(sizeNeed);

    vector<glm::vec2> Grid2D = vector<glm::vec2>(sizeNeed);
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
    void setColor(int color1, int color2,int colorBack);
    unsigned char debugMode;
    void switchDebug();
    void Draw_Tick(ScreenDemo* ScreenEye);

    void solidRectangle2D(ScreenDemo* ScreenEye);
    bool showP = 0;
    bool showGrid = 0;

    bool triangleBackFront = 0;
    vector<trianglePair> triangles;

    vector<triangleSelf> triangleLast;

    void computeTriQuadFromVerts(
        float u, float v, float w,
        // const glm::vec3& a,   // P200 (u²)
        // const glm::vec3& b,   // P020 (v²)
        // const glm::vec3& c,   // P002 (w²)
        // const glm::vec3& ab,  // P110 (2uv) - AB边中点
        // const glm::vec3& bc,  // P011 (2vw) - BC边中点
        // const glm::vec3& ca,  // P101 (2uw) - CA边中点
        glm::vec3* Su, glm::vec3* Sv);


    array<double,5> getRayCoefficients_u_screenAxis(goLine64& rayDir);

    [[nodiscard]]array<double, 4> solveEquation_4_u(array<double, 5>& src);
    [[nodiscard]]array<double, 4> solveEquation_4_u_(array<double, 5>& src,array<complex<double>, 4>& complexRes);
    std::expected<double,char> isResultUOK(complex<double> num);

    array<double,3> getCoefficients_v_screenAxis(goLine32& rayDir,double u);
    [[nodiscard]]
    std::expected<array<double,2>,char> solveEquation_2_v(array<double,3>& src);
    bool uvw_InRange01(double num);

    double len2Eye_22_screenAxis(glm::dvec3& surfaceP);
    bool checkRealU(array<double,5>& coefficients,double u);
    std::expected<oneUVWInfo,char> getBestSolve_UVW(goLine32& rayDir);
    void addVertical2uvwInfo(oneUVWInfo& _uvw);
    glm::vec3 getColorByUVW(const glm::vec3& _uvw);

    void _solidRectangle2D_(ScreenDemo* ScreenEye,glm::vec2& p1,glm::vec2& p2,glm::vec2& p3,glm::vec2& p4,
    vector<lineBoundary>& lineScanFillColor,vector<rowUVWInfo>& pixelEyeDeep,bool firstStop);

    vector<lineBoundary> lineScanFillColor_front; // lx 左屏深  rx 右屏深  y 扫描线的y坐标
    vector<lineBoundary> lineScanFillColor_back; // lx 左屏深  rx 右屏深  y 扫描线的y坐标
    vector<lineBoundary> lineScanFillColor_left;
    vector<lineBoundary> lineScanFillColor_right;
    vector<lineBoundary> lineScanFillColor_top;
    vector<lineBoundary> lineScanFillColor_bottom;

    vector<rowUVWInfo> pixelEyeDeep_front;
    vector<rowUVWInfo> pixelEyeDeep_back;
    vector<rowUVWInfo> pixelEyeDeep_left;
    vector<rowUVWInfo> pixelEyeDeep_right;
    vector<rowUVWInfo> pixelEyeDeep_top;
    vector<rowUVWInfo> pixelEyeDeep_bottom;

    void moveFreshStatus();
    glm::dvec3 startEye64;
};


#endif //POLYGONDISPLAY_BEZIER22EDGE3_H