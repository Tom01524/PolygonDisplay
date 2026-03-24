//
// Created by iceoc0 on 2025/6/7.
//

#ifndef POLYGONDISPLAY_BICUBICBEZIER_H
#define POLYGONDISPLAY_BICUBICBEZIER_H

#include "./AxisDemo.h"

#ifndef TBLRFB__
#define TBLRFB__
struct TBLRFB {
    float topY, bottomY, leftX, rightX, nearZ, farZ;
};
#endif

struct pixelDeep23{
    int x; // 列
    glm::vec2 uv; // 纹理坐标
    float screenDeep; // float deep
    bool faceToCamera;
};

struct rowPixelDeep23 {
    vector<std::expected<pixelDeep23,char>> pixelDeeps; // 行的像素深度
    float y; // 行
};
// xy独立各体
struct pixelDeep23_ {
    glm::ivec2 xy; // 坐标
    glm::vec2 uv; // 纹理坐标
    float screenDeep; // float deep
    bool faceToCamera;
};


struct curveSurfaceInfo{
    glm::vec2 uv;
    glm::vec3 virtual_Pos;
    float sightLineLen;
    bool faceToCamera;
};
struct cloudInfo {
    glm::vec3 pos;
    glm::vec3 verticalP; // 法线步进1
    bool onFront;
    void freshOnFront(glm::vec3& startEye) { // 区分颜色
        // float judge = glm::dot(startEye - pos, verticalP - pos);
        // onFront = judge > 0 ? true : false;

        goLine32 vertical_ = verticalP - pos;
        //assert(abs(glm::dot(vertical_._,vertical_._) - 1.f)<0.01f);

        onFront = PolygonBase::isFrontFacing(startEye,vertical_,pos);

        //cout << "onFront: " << onFront << endl;
    }
    glm::vec2 uv;
};
//#define showEdgeRectVertical
class Rect2Flat {
public:

    array<cloudInfo, 4> virtual_ltrt_rblb;
#ifdef showEdgeRectVertical
    array<pair<glm::vec2,glm::vec2>, 4> ltrt_rblb_2d;
#else
    array<glm::vec2, 4> ltrt_rblb_2d;
#endif


    Rect2Flat();
    void fresh8Points(cloudInfo _lt, cloudInfo _rt,
    cloudInfo _lb, cloudInfo _rb);

    void fresh4Points_3D2D(ScreenDemo* ScreenEye);

    vector<lineBoundary> triangleLT;
    vector<lineBoundary> triangleRB;
    void freshLineBoundary_triangle() ;

    array<float,4> virtual_abcd_LT;
    array<float,4> virtual_abcd_RB; // 屏幕系 共面方程
    glm::vec3 getXYZ_ByVirtual3Point(const glm::vec3& cornerIndex, float x, float y);
    glm::vec3 getXYZ_ByVirtual3Point_(const glm::vec3& cornerIndex, float x, float y,goLine32* rayNorm);
    char frontLT, frontRB;
    void fresh2FrontBack();
    void freshTriangle(ScreenDemo* ScreenEye, cloudInfo lt, cloudInfo rt,
        cloudInfo rb, cloudInfo lb);

    float frontBackColor[3];
    void draw2Triangle(ScreenDemo* ScreenEye,float frontColor[],float backColor[], PolygonBase* Self);
#ifdef showEdgeRectVertical
    void draw2Triangle_(ScreenDemo* ScreenEye,float frontColor[],float backColor[], float verticalColor[], PolygonBase* Self);
#endif
    void clacAddPixelsInfo(PolygonBase* Self, glm::vec3 _p[][5],vector<pixelDeep23_>* pixelSurfaceInfo);
    unsigned char minIndex(float a, float b, float c);
};
struct Box4Points {
    enum class _ : array<void*,1>::size_type {
        ltn=0, rtn, rbn, lbn, ltf, rtf, rbf, lbf
    };
    Box4Points() = default; // 用 array 保留空参构造 !!!
    Box4Points(pair<glm::vec3,glm::ivec2> p1, pair<glm::vec3,glm::ivec2> p2,
        pair<glm::vec3,glm::ivec2> p3, pair<glm::vec3,glm::ivec2> p4, float expandRate) {
        // 接受 unchange
        // mode 2 轴系 mode 4 世界系

        // 点云确定包围盒
        glm::vec3 _min;
        glm::vec3 _max;
        _min[0] = std::min(p1.first.x, std::min(p2.first.x, std::min(p3.first.x, p4.first.x)));
        _min[1] = std::min(p1.first.y, std::min(p2.first.y, std::min(p3.first.y, p4.first.y)));
        _min[2] = std::min(p1.first.z, std::min(p2.first.z, std::min(p3.first.z, p4.first.z)));
        _max[0] = std::max(p1.first.x, std::max(p2.first.x, std::max(p3.first.x, p4.first.x)));
        _max[1] = std::max(p1.first.y, std::max(p2.first.y, std::max(p3.first.y, p4.first.y)));
        _max[2] = std::max(p1.first.z, std::max(p2.first.z, std::max(p3.first.z, p4.first.z)));

        glm::vec3 boxLen = _max - _min;
        glm::vec3 expand = boxLen * expandRate;
        _min -= expand;
        _max += expand;
        //println("小盒 expand ({},{},{})",expand.x,expand.y,expand.z);
        cornersWorld[static_cast<int>(_::ltn)].x = _min.x;
        cornersWorld[static_cast<int>(_::ltn)].y = _min.y;
        cornersWorld[static_cast<int>(_::ltn)].z = _min.z;

        cornersWorld[static_cast<int>(_::rtn)].x = _max.x;
        cornersWorld[static_cast<int>(_::rtn)].y = _min.y;
        cornersWorld[static_cast<int>(_::rtn)].z = _min.z;

        cornersWorld[static_cast<int>(_::rbn)].x = _max.x;
        cornersWorld[static_cast<int>(_::rbn)].y = _max.y;
        cornersWorld[static_cast<int>(_::rbn)].z = _min.z;

        cornersWorld[static_cast<int>(_::lbn)].x = _min.x;
        cornersWorld[static_cast<int>(_::lbn)].y = _max.y;
        cornersWorld[static_cast<int>(_::lbn)].z = _min.z;

        cornersWorld[static_cast<int>(_::ltf)].x = _min.x;
        cornersWorld[static_cast<int>(_::ltf)].y = _min.y;
        cornersWorld[static_cast<int>(_::ltf)].z = _max.z;

        cornersWorld[static_cast<int>(_::rtf)].x = _max.x;
        cornersWorld[static_cast<int>(_::rtf)].y = _min.y;
        cornersWorld[static_cast<int>(_::rtf)].z = _max.z;

        cornersWorld[static_cast<int>(_::rbf)].x = _max.x;
        cornersWorld[static_cast<int>(_::rbf)].y = _max.y;
        cornersWorld[static_cast<int>(_::rbf)].z = _max.z;

        cornersWorld[static_cast<int>(_::lbf)].x = _min.x;
        cornersWorld[static_cast<int>(_::lbf)].y = _max.y;
        cornersWorld[static_cast<int>(_::lbf)].z = _max.z;

        setUnchangeBy_();
        // 点云索引
        cloudsIndex[0] = p1.second;
        cloudsIndex[1] = p2.second;
        cloudsIndex[2] = p3.second;
        cloudsIndex[3] = p4.second;
    }
    void setUnchangeBy_() {
        corners_unchange[static_cast<int>(_::ltn)].x = cornersWorld[static_cast<int>(_::ltn)].x;
        corners_unchange[static_cast<int>(_::ltn)].y = cornersWorld[static_cast<int>(_::ltn)].y;
        corners_unchange[static_cast<int>(_::ltn)].z = cornersWorld[static_cast<int>(_::ltn)].z;

        corners_unchange[static_cast<int>(_::rtn)].x = cornersWorld[static_cast<int>(_::rtn)].x;
        corners_unchange[static_cast<int>(_::rtn)].y = cornersWorld[static_cast<int>(_::rtn)].y;
        corners_unchange[static_cast<int>(_::rtn)].z = cornersWorld[static_cast<int>(_::rtn)].z;

        corners_unchange[static_cast<int>(_::rbn)].x = cornersWorld[static_cast<int>(_::rbn)].x;
        corners_unchange[static_cast<int>(_::rbn)].y = cornersWorld[static_cast<int>(_::rbn)].y;
        corners_unchange[static_cast<int>(_::rbn)].z = cornersWorld[static_cast<int>(_::rbn)].z;

        corners_unchange[static_cast<int>(_::lbn)].x = cornersWorld[static_cast<int>(_::lbn)].x;
        corners_unchange[static_cast<int>(_::lbn)].y = cornersWorld[static_cast<int>(_::lbn)].y;
        corners_unchange[static_cast<int>(_::lbn)].z = cornersWorld[static_cast<int>(_::lbn)].z;

        corners_unchange[static_cast<int>(_::ltf)].x = cornersWorld[static_cast<int>(_::ltf)].x;
        corners_unchange[static_cast<int>(_::ltf)].y = cornersWorld[static_cast<int>(_::ltf)].y;
        corners_unchange[static_cast<int>(_::ltf)].z = cornersWorld[static_cast<int>(_::ltf)].z;

        corners_unchange[static_cast<int>(_::rtf)].x = cornersWorld[static_cast<int>(_::rtf)].x;
        corners_unchange[static_cast<int>(_::rtf)].y = cornersWorld[static_cast<int>(_::rtf)].y;
        corners_unchange[static_cast<int>(_::rtf)].z = cornersWorld[static_cast<int>(_::rtf)].z;

        corners_unchange[static_cast<int>(_::rbf)].x = cornersWorld[static_cast<int>(_::rbf)].x;
        corners_unchange[static_cast<int>(_::rbf)].y = cornersWorld[static_cast<int>(_::rbf)].y;
        corners_unchange[static_cast<int>(_::rbf)].z = cornersWorld[static_cast<int>(_::rbf)].z;

        corners_unchange[static_cast<int>(_::lbf)].x = cornersWorld[static_cast<int>(_::lbf)].x;
        corners_unchange[static_cast<int>(_::lbf)].y = cornersWorld[static_cast<int>(_::lbf)].y;
        corners_unchange[static_cast<int>(_::lbf)].z = cornersWorld[static_cast<int>(_::lbf)].z;
    }

    array<glm::vec3,8> cornersWorld; // 世界系
    array<glm::vec3,8> corners_unchange;
    array<glm::ivec2, 4> cloudsIndex;

};
using corner = Box4Points::_;

struct Box9Cube {
    Box9Cube() = default;//  保留空参构造 !!!

    Box9Cube(Matrix2D<Box4Points*>& smallBoxes)
    {

        // 用于收集坐标的向量（或 array，但用 vector 更方便）
        std::vector<float> allMinX, allMaxX;
        std::vector<float> allMinY, allMaxY;
        std::vector<float> allMinZ, allMaxZ;
        // outter size inner size
        box4_P = vector<Box4Points*>(smallBoxes.innerMax * smallBoxes.outterMax);
        // 遍历所有小盒子
        for (size_t outter = 0; outter < smallBoxes.outterMax; ++outter) {
            for (size_t inner = 0; inner < smallBoxes.innerMax; ++inner) {
                const array<glm::vec3, 8>& box = smallBoxes(outter,inner)->cornersWorld;

                // ltn = left-top-near, rtn = right-top-near, lbn = left-bottom-near, ltf = left-top-far
                allMinX.emplace_back(box[static_cast<int>(Box4Points::_::ltn)].x);
                allMaxX.emplace_back(box[static_cast<int>(Box4Points::_::rtn)].x);

                allMinY.emplace_back(box[static_cast<int>(Box4Points::_::ltn)].y);
                allMaxY.emplace_back(box[static_cast<int>(Box4Points::_::lbn)].y);

                allMinZ.emplace_back(box[static_cast<int>(Box4Points::_::ltn)].z);
                allMaxZ.emplace_back(box[static_cast<int>(Box4Points::_::ltf)].z);

                // 同时保存到 boxColRow（只填 [0..Rows-1][0..Cols-1]）
                box4_P[outter*smallBoxes.innerMax + inner] = smallBoxes(outter, inner);
            }
        }
        assert(!allMinX.empty() && !allMaxX.empty() && !allMinY.empty() && !allMaxY.empty() && !allMinZ.empty() && !allMaxZ.empty());
        // if (allMinX.empty() || allMaxX.empty() || allMinY.empty() || allMaxY.empty() || allMinZ.empty() || allMaxZ.empty()) {
        //     println("smallBoxes.size():{} smallBoxes[0].size():{}", smallBoxes.size(), smallBoxes[0].size());
        //     throw "allMinX is empty";
        // }

        // 计算整体包围盒
        glm::vec3 minPt{
            *std::ranges::min_element(allMinX),
            *std::ranges::min_element(allMinY),
            *std::ranges::min_element(allMinZ)
        };
        glm::vec3 maxPt{
            *std::ranges::max_element(allMaxX),
            *std::ranges::max_element(allMaxY),
            *std::ranges::max_element(allMaxZ)
        };

        // 填充 8 个角点（标准 AABB 角点命名）
        using Corner = Box4Points::_;
        this->cornersWorld[static_cast<int>(Corner::ltn)] = glm::vec3(minPt.x, minPt.y, minPt.z); // left-top-near
        this->cornersWorld[static_cast<int>(Corner::rtn)] = glm::vec3(maxPt.x, minPt.y, minPt.z); // right-top-near
        this->cornersWorld[static_cast<int>(Corner::rbn)] = glm::vec3(maxPt.x, maxPt.y, minPt.z); // right-bottom-near
        this->cornersWorld[static_cast<int>(Corner::lbn)] = glm::vec3(minPt.x, maxPt.y, minPt.z); // left-bottom-near
        this->cornersWorld[static_cast<int>(Corner::ltf)] = glm::vec3(minPt.x, minPt.y, maxPt.z); // left-top-far
        this->cornersWorld[static_cast<int>(Corner::rtf)] = glm::vec3(maxPt.x, minPt.y, maxPt.z); // right-top-far
        this->cornersWorld[static_cast<int>(Corner::rbf)] = glm::vec3(maxPt.x, maxPt.y, maxPt.z); // right-bottom-far
        this->cornersWorld[static_cast<int>(Corner::lbf)] = glm::vec3(minPt.x, maxPt.y, maxPt.z); // left-bottom-far

        setUnchangeBy_();
    }
    void setUnchangeBy_() {
        using Corner = Box4Points::_;
        this->corners_unchange[static_cast<int>(Corner::ltn)].x = cornersWorld[static_cast<int>(Corner::ltn)].x;
        this->corners_unchange[static_cast<int>(Corner::ltn)].y = cornersWorld[static_cast<int>(Corner::ltn)].y;
        this->corners_unchange[static_cast<int>(Corner::ltn)].z = cornersWorld[static_cast<int>(Corner::ltn)].z;

        this->corners_unchange[static_cast<int>(Corner::rtn)].x = cornersWorld[static_cast<int>(Corner::rtn)].x;
        this->corners_unchange[static_cast<int>(Corner::rtn)].y = cornersWorld[static_cast<int>(Corner::rtn)].y;
        this->corners_unchange[static_cast<int>(Corner::rtn)].z = cornersWorld[static_cast<int>(Corner::rtn)].z;

        this->corners_unchange[static_cast<int>(Corner::rbn)].x = cornersWorld[static_cast<int>(Corner::rbn)].x;
        this->corners_unchange[static_cast<int>(Corner::rbn)].y = cornersWorld[static_cast<int>(Corner::rbn)].y;
        this->corners_unchange[static_cast<int>(Corner::rbn)].z = cornersWorld[static_cast<int>(Corner::rbn)].z;

        this->corners_unchange[static_cast<int>(Corner::lbn)].x = cornersWorld[static_cast<int>(Corner::lbn)].x;
        this->corners_unchange[static_cast<int>(Corner::lbn)].y = cornersWorld[static_cast<int>(Corner::lbn)].y;
        this->corners_unchange[static_cast<int>(Corner::lbn)].z = cornersWorld[static_cast<int>(Corner::lbn)].z;

        this->corners_unchange[static_cast<int>(Corner::ltf)].x = cornersWorld[static_cast<int>(Corner::ltf)].x;
        this->corners_unchange[static_cast<int>(Corner::ltf)].y = cornersWorld[static_cast<int>(Corner::ltf)].y;
        this->corners_unchange[static_cast<int>(Corner::ltf)].z = cornersWorld[static_cast<int>(Corner::ltf)].z;

        this->corners_unchange[static_cast<int>(Corner::rtf)].x = cornersWorld[static_cast<int>(Corner::rtf)].x;
        this->corners_unchange[static_cast<int>(Corner::rtf)].y = cornersWorld[static_cast<int>(Corner::rtf)].y;
        this->corners_unchange[static_cast<int>(Corner::rtf)].z = cornersWorld[static_cast<int>(Corner::rtf)].z;

        this->corners_unchange[static_cast<int>(Corner::rbf)].x = cornersWorld[static_cast<int>(Corner::rbf)].x;
        this->corners_unchange[static_cast<int>(Corner::rbf)].y = cornersWorld[static_cast<int>(Corner::rbf)].y;
        this->corners_unchange[static_cast<int>(Corner::rbf)].z = cornersWorld[static_cast<int>(Corner::rbf)].z;

        this->corners_unchange[static_cast<int>(Corner::lbf)].x = cornersWorld[static_cast<int>(Corner::lbf)].x;
        this->corners_unchange[static_cast<int>(Corner::lbf)].y = cornersWorld[static_cast<int>(Corner::lbf)].y;
        this->corners_unchange[static_cast<int>(Corner::lbf)].z = cornersWorld[static_cast<int>(Corner::lbf)].z;
    }
    array<glm::vec3,8> cornersWorld; // 世界系
    array<glm::vec3,8> corners_unchange;
    vector<Box4Points*> box4_P; // 其vector的索引

};

class Bezier33Edge4 : public PolygonBase {
public:
    Bezier33Edge4(glm::vec3 _P[5][5], unsigned char _mesh);
    Bezier33Edge4(glm::vec3 _P[4][4], int _type = 23);
    virtual ~Bezier33Edge4() = default;

    void __init__(glm::vec3 _P[5][5], unsigned char _mesh);

    int N_u = 16; // inner
    int N_v = 15; // outter
    float rayRadius_22 = 100.f;

    unsigned char surfaceTimes; // 双几次贝塞尔曲面
    unsigned char renderNext; // false
    bool settledColorGrid70 = false;

    float edgeFlatWide = 0.1f;

    glm::vec3 P[5][5];
    Matrix2D<pair<glm::vec3,glm::vec3>> Grid = Matrix2D<pair<glm::vec3,glm::vec3>>(N_v,N_u);
    glm::vec3 P_unchange[5][5];
    Matrix2D<pair<glm::vec3,glm::vec3>> Grid_unchange = Matrix2D<pair<glm::vec3,glm::vec3>>(N_v,N_u);

    vector<pair<glm::vec3,glm::vec3>> Grid_edgeTop = vector<pair<glm::vec3,glm::vec3>>(N_u);
    vector<pair<glm::vec3,glm::vec3>> Grid_edgeTop_unchange = vector<pair<glm::vec3,glm::vec3>>(N_u);
    vector<pair<glm::vec3,glm::vec3>> Grid_edgeBottom = vector<pair<glm::vec3,glm::vec3>>(N_u);
    vector<pair<glm::vec3,glm::vec3>> Grid_edgeBottom_unchange = vector<pair<glm::vec3,glm::vec3>>(N_u);

    vector<pair<glm::vec3,glm::vec3>> Grid_edgeLeft = vector<pair<glm::vec3,glm::vec3>>(N_v);
    vector<pair<glm::vec3,glm::vec3>> Grid_edgeLeft_unchange = vector<pair<glm::vec3,glm::vec3>>(N_v);
    vector<pair<glm::vec3,glm::vec3>> Grid_edgeRight = vector<pair<glm::vec3,glm::vec3>>(N_v);
    vector<pair<glm::vec3,glm::vec3>> Grid_edgeRight_unchange = vector<pair<glm::vec3,glm::vec3>>(N_v);
    void generateGrid_4();
    void generateGrid_3();
    void generateGrid_2();


    CubeBox3D scanBox3D;
    CubeBox3D scanBox3D_unchange; // 锁坐标系
    CubeBox3D virtual_scanBox3D; // 屏幕系
    CubeBox2D scanBox2D_;

    TBLRFB boxVolume;
    float boxLenX, boxLenY, boxLenZ;
    float boxLenHalfX, boxLenHalfY, boxLenHalfZ;

    int startRowIndex_;

    Matrix2D<Rect2Flat> rect2Flats; // = Matrix2D<Rect2Flat>(N_v-1, N_u-1); // n_u n_v
    vector<Rect2Flat> rect2Flats_Top = vector<Rect2Flat>(N_u-1);
    vector<Rect2Flat> rect2Flats_Bottom = vector<Rect2Flat>(N_u-1);
    vector<Rect2Flat> rect2Flats_Left = vector<Rect2Flat>(N_v-1);
    vector<Rect2Flat> rect2Flats_Right = vector<Rect2Flat>(N_v-1);

    TBLRFB initBox_TBLRNF(); // Top Bottom Left Right Near Far
    void initBoxInfo();

     int box4Col = N_u-1; // 预处理 必须是 属类的
     int box4Row = N_v-1;
    // 小包围盒
    Matrix2D<Box4Points> box4Points = Matrix2D<Box4Points>(box4Row , box4Col);
    void initBox4Points();
    // glm::vec3 smallBoxExpand;
    void drawBox4Points(ScreenDemo* screenEye);
    int box9Col = box4Col / 3 + (box4Col % 3 == 0 ? 0 : 1); // 整除 不然加一个盒
    int box9Row = box4Row / 3 + (box4Row % 3 == 0 ? 0 : 1); // 整除 不然加一个盒
    // 中包围盒
    Matrix2D<Box9Cube> box9Cubes = Matrix2D<Box9Cube>(box9Row, box9Col);

    void freshBox4Display(AxisDemo* AxisTilt);
    void freshBox9Display(AxisDemo* AxisTilt);

    Matrix2D<Box4Points*>
    getMidBoxExpand(this Bezier33Edge4& self,int _outter, int _inner,int outterBoxFind,int innerBoxFind); // 33

    void initBox9Cubes();
    void drawBox9Cubes(ScreenDemo* screenEye);

    glm::vec3 screen2World(ScreenDemo* screenEye, glm::vec3& _src);

    // glm::vec3 world2AxisTilt(AxisDemo* AxisTilt, glm::vec3& _src);

    void shotOnBox_AxisTilt_4(Box4Points& box4Points,glm::vec3& startP_axisTilt, goLine32& rayDirUnit,
        pair<bool,float>* result); // qwen推荐 轴对齐包围盒 射中与否
    void shotOnBox_AxisTilt_9(Box9Cube& box4Points,glm::vec3& startP_axisTilt, goLine32& rayDirUnit,
        pair<bool,float>* result); // qwen推荐 轴对齐包围盒 射中与否

    float rounfBoxTipLen = 20.f;
    void setBox3D(glm::vec3& _ltn, glm::vec3& _rtn, glm::vec3& _rbn, glm::vec3& _lbn,
                  glm::vec3& _ltf, glm::vec3& _rtf, glm::vec3& _rbf, glm::vec3& _lbf);
    void setBox2D(glm::vec2& _ltn, glm::vec2& _rtn, glm::vec2& _rbn, glm::vec2& _lbn,
                  glm::vec2& _ltf, glm::vec2& _rtf, glm::vec2& _rbf, glm::vec2& _lbf,
                  glm::vec2& _center);


    goLine32 world_toX, world_toY, world_toZ;
    void freshGoX();
    void freshGoY();
    void freshGoZ();
    void goX(glm::vec3& _srcXYZ, float _move);
    void goY(glm::vec3& _srcXYZ, float _move);
    void goZ(glm::vec3& _srcXYZ, float _move);


    virtual void solidRectangle2D_(ScreenDemo* ScreenEye,AxisDemo* AxisTilt);
    vector<lineBoundary> lineScanFillColor_;
    vector<rowPixelDeep23> pixelSurfaceInfo_;
    vector<pixelDeep23_> pixelSurfaceInfo__;

    void freshVirtualCloudsFrontBack();

    float colorP[3];
    float colorGrid[3];
    float backColor[3];
    float verticalColor[3];

    float colorP_70[3];
    float colorGrid_70[3]; // setted color grid (once on first)


    void setColor(int color1, int color2);
    float* getColorByUV(glm::vec2& uv);


    void set_P_XYZ(glm::vec3 _P[5][5]);

    virtual void moveFreshStatus();


    glm::vec3 virtual_P[5][5];
    Matrix2D<cloudInfo> virtual_Grid = Matrix2D<cloudInfo>(N_v, N_u);
    vector<cloudInfo> virtual_Grid_edgeTop = vector<cloudInfo>(N_u);
    vector<cloudInfo> virtual_Grid_edgeBottom = vector<cloudInfo>(N_u);
    vector<cloudInfo> virtual_Grid_edgeLeft = vector<cloudInfo>(N_v);
    vector<cloudInfo> virtual_Grid_edgeRight = vector<cloudInfo>(N_v);

    glm::vec2 P2D[5][5];

    Matrix2D<pair<glm::vec2,glm::vec2>> Grid2D = Matrix2D<pair<glm::vec2,glm::vec2>>(N_v, N_u);


    bool showP = 0;
    bool showGrid = 0;
    char debugMode = 0;

    bool showVerticals = 0;

    bool showEdgeRect = 0; // for fast iteration

    bool fastIteration = 0;

    void switchDebug(AxisDemo* AxisTilt);

    void Draw_Tick(ScreenDemo* ScreenEye, AxisDemo* AxisTilt);


    [[maybe_unused]]std::array<double, 9> coeffientForU(glm::vec3& eye, goLine32& dir, glm::vec3 p[5][5]);
    [[maybe_unused]]array<complex<double>, 8> solveOctic_(
        complex<double> A, complex<double> B, complex<double> C,
        complex<double> D, complex<double> E, complex<double> F,
        complex<double> G, complex<double> H, complex<double> I);
    [[maybe_unused]]array<float,3> coeffientForV(float u, glm::vec3& eye, goLine32& dir, glm::vec3 p[5][5]);
    [[maybe_unused]]array<double,2> getVbyCoeffient(double a, double b, double c);

    std::array<double, 4> coeffientForV_(float u, glm::vec3& eye, goLine32& dir, glm::vec3 p[5][5]);
    [[maybe_unused]] array<complex<double>, 3> solveCubic(double _a, double _b, double _c, double _d);
    [[maybe_unused]] vector<double> getVbyCoeffient_(double a, double b, double c, double _d);

    goLine32 computeNormal(float u, float v, glm::vec3 p[5][5]);
    bool isFrontFacing(goLine32& normal, goLine32& viewDir);
    bool getFrontFacing(float u, float v, glm::vec3& surfaceP, glm::vec3 p[5][5]);
    [[maybe_unused]]float distanceToRay(glm::vec3& eye, goLine32& rayDir, glm::vec3& roundP);

    [[maybe_unused]]curveSurfaceInfo rayIntersectBezier2_(glm::vec3& _startEye,
    goLine32& sightLine, glm::vec3 P[5][5]);

    [[maybe_unused]]glm::vec3 evaluatePatch2(float u, float v, const glm::vec3 P[5][5]);
    [[maybe_unused]]void computeBezierBasis2(float t, float B[3], float dB[3]);
    [[maybe_unused]]void surfaceDerivatives2(float u, float v, glm::vec3 P[5][5],
                                            glm::vec3& S, glm::vec3& Su, glm::vec3& Sv);
    [[maybe_unused]]curveSurfaceInfo rayIntersectBezier2(glm::vec3& _startEye, glm::vec3& sightLine, glm::vec3 P[5][5]);

    // bool solve3x3(const float J[3][3], const float F[3], float delta[3]);
    // bool solve3x3_(const float J[3][3], const glm::vec3& F, float delta[3]); // reload
    bool (*solve3x3)(const float J[3][3], const float F[3], float delta[3]);
    bool (*solve3x3_)(const float J[3][3], const glm::vec3& F, float delta[3]);

    std::expected<glm::vec3,char> RayTriangleIntersect(const glm::vec3& startEye, const glm::vec3& rayDir,
                          const glm::vec3& pa, const glm::vec3& pb, const glm::vec3& pc); // 视线 射中 三角形
    [[maybe_unused]] glm::vec2 getNearestTipUV_byFlatPoint(const glm::vec3& flatPoint,
        Rect2Flat& rect2Flat, unsigned char triangleIndex);
    [[maybe_unused]] vector<glm::vec2> generateCandidateVUs_3(const glm::vec3& startEye, const glm::vec3& rayDir);

    vector<glm::vec2> generateCandidateVUs_2(glm::vec3& startEye, glm::vec3& rayDir_norm);

    glm::vec3 startEye_axisTilt;
    void screenAxis2axisTilt(ScreenDemo* ScreenEye, AxisDemo *AxisTilt,glm::vec3*src, glm::vec3*dst);
    void getCandidatesVU_bySelfBox(glm::vec3& startPos_axisTilt, goLine32& rayDir_axisTilt,
        vector<glm::vec2>& candidates);


    glm::vec3 evaluatePatch3(float u, float v, const glm::vec3 P[5][5]);

    void surfaceDerivatives3(float u, float v, const glm::vec3 P[5][5],
                                            glm::vec3* S, glm::vec3* Su, glm::vec3* Sv);
    std::expected<curveSurfaceInfo,char>
    rayIntersectBezier3(ScreenDemo* ScreenEye,AxisDemo *AxisTilt, goLine32& rayDir,
             glm::ivec2 pos2D,glm::vec3 _P_[5][5]);
    std::expected<curveSurfaceInfo,char>
    rayIntersectBezier3_(goLine32 rayDir, glm::vec3 _P_[5][5], glm::vec2 uv);

    [[maybe_unused]]void computeBezierBasis4(float t, float B[5], float dB[5]);
    [[maybe_unused]]glm::vec3 evaluatePatch4(float u, float v, const glm::vec3 P[5][5]);
    [[maybe_unused]]void surfaceDerivatives4(float u, float v, glm::vec3 P[5][5],
                                            glm::vec3& S, glm::vec3& Su, glm::vec3& Sv);
    [[maybe_unused]]curveSurfaceInfo rayIntersectBezier4(glm::vec3& _startEye, glm::vec3& sightLine, glm::vec3 P[5][5]);

    bool(*isIn)(vector<int>&,int);
};
#endif //POLYGONDISPLAY_BICUBICBEZIER_H
