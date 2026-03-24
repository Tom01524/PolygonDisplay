//
// Created by iceoc0 on 2025/6/7.
//
#include "Bezier33Edge4.h"

#include "AxisDemo.h"


extern void* settled_ptr; // 全局设置的结构体指针
struct _settledBezier{
    int _width;
    int _height;
    int _deep;
    bool _byAxis;
};
_settledBezier* settled_ = (_settledBezier*)settled_ptr;
const int screenWidth23 = settled_-> _width;
const int screenHeight23 = settled_-> _height;
const int screenDeep23 = settled_-> _deep;
const bool byAxis23 = settled_->_byAxis;

extern void* _3d_2d_go_void_ptr; // 3d_2d_go的函数指针
// struct _3d_2d_go_bezier{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_2d)(ScreenDemo*, float, float, float);
//
// };
glm::vec2 (*__3d2dGobezier)(ScreenDemo*, glm::vec3, glm::vec3*)
= ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2dbezier)(ScreenDemo*, float, float, float)
= ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d; // 模式1 用自己的不行

struct modeBezier3{
    char now;char a;char b;char d;
};
extern void* mode_ptr;
modeBezier3 mode_ = *((modeBezier3*)mode_ptr);

glm::vec3 startEye = {screenWidth23/2,screenHeight23/2,-screenDeep23};
Rect2Flat::Rect2Flat() {

    frontBackColor[0] = 223.f/255.f;
    frontBackColor[1] = 208.f/255.f;
    frontBackColor[2] = 82.f/255.f;
    }
void Rect2Flat::fresh8Points(cloudInfo _lt, cloudInfo _rt,
    cloudInfo _lb, cloudInfo _rb) {
    virtual_ltrt_rblb[0] = _lt;
    virtual_ltrt_rblb[1] = _rt;
    virtual_ltrt_rblb[2] = _rb;
    virtual_ltrt_rblb[3] = _lb;

}

void Rect2Flat::fresh4Points_3D2D(ScreenDemo* ScreenEye) {


#ifdef showEdgeRectVertical
    this->ltrt_rblb_2d[0].first =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[0].pos.x,virtual_ltrt_rblb[0].pos.y,virtual_ltrt_rblb[0].pos.z);
    this->ltrt_rblb_2d[1].first =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[1].pos.x,virtual_ltrt_rblb[1].pos.y,virtual_ltrt_rblb[1].pos.z);
    this->ltrt_rblb_2d[2].first =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[2].pos.x,virtual_ltrt_rblb[2].pos.y,virtual_ltrt_rblb[2].pos.z);
    this->ltrt_rblb_2d[3].first =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[3].pos.x,virtual_ltrt_rblb[3].pos.y,virtual_ltrt_rblb[3].pos.z);

     this->ltrt_rblb_2d[0].second =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[0].verticalP.x,virtual_ltrt_rblb[0].verticalP.y,virtual_ltrt_rblb[0].verticalP.z);
    this->ltrt_rblb_2d[1].second =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[1].verticalP.x,virtual_ltrt_rblb[1].verticalP.y,virtual_ltrt_rblb[1].verticalP.z);
    this->ltrt_rblb_2d[2].second =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[2].verticalP.x,virtual_ltrt_rblb[2].verticalP.y,virtual_ltrt_rblb[2].verticalP.z);
    this->ltrt_rblb_2d[3].second =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[3].verticalP.x,virtual_ltrt_rblb[3].verticalP.y,virtual_ltrt_rblb[3].verticalP.z);
#else
    this->ltrt_rblb_2d[0] =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[0].pos.x,virtual_ltrt_rblb[0].pos.y,virtual_ltrt_rblb[0].pos.z);
    this->ltrt_rblb_2d[1] =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[1].pos.x,virtual_ltrt_rblb[1].pos.y,virtual_ltrt_rblb[1].pos.z);
    this->ltrt_rblb_2d[2] =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[2].pos.x,virtual_ltrt_rblb[2].pos.y,virtual_ltrt_rblb[2].pos.z);
    this->ltrt_rblb_2d[3] =
     __3d2dbezier(ScreenEye, virtual_ltrt_rblb[3].pos.x,virtual_ltrt_rblb[3].pos.y,virtual_ltrt_rblb[3].pos.z);
#endif

}

void Rect2Flat::freshLineBoundary_triangle() {
#ifdef showEdgeRectVertical
    PolygonBase::fresh2D_scanRows_3(ltrt_rblb_2d[0].first,
                              ltrt_rblb_2d[1].first,
                              ltrt_rblb_2d[3].first, &triangleLT,23);
    PolygonBase::fresh2D_scanRows_3(ltrt_rblb_2d[1].first,
                                  ltrt_rblb_2d[2].first,
                                  ltrt_rblb_2d[3].first, &triangleRB,23);
#else
    PolygonBase::fresh2D_scanRows_3(ltrt_rblb_2d[0],
                               ltrt_rblb_2d[1],
                               ltrt_rblb_2d[3], &triangleLT,23);
    PolygonBase::fresh2D_scanRows_3(ltrt_rblb_2d[1],
                                  ltrt_rblb_2d[2],
                                  ltrt_rblb_2d[3], &triangleRB,23);
#endif
}

glm::vec3 Rect2Flat::getXYZ_ByVirtual3Point(const glm::vec3& cornerIndex, float x, float y) {
    glm::vec3& p1 = virtual_ltrt_rblb[cornerIndex[0]].pos;
    glm::vec3& p2 = virtual_ltrt_rblb[cornerIndex[1]].pos;
    glm::vec3& p3 = virtual_ltrt_rblb[cornerIndex[2]].pos;
    // 两边 射线
    glm::vec3 p2Top1 = p1 - p2;
    glm::vec3 p2Top3 = p3 - p2;
    // 向量叉乘
    // 归一化法线
    glm::vec3 vertical = glm::normalize(glm::cross(p2Top1, p2Top3)); // a b c

    // ax+by+cz+d=0  d=-(ax+by+cz)
    float d = -glm::dot(vertical, p1);

    if (cornerIndex[0] == 0) { // 0 1 3
        virtual_abcd_LT[0] = vertical[0];
        virtual_abcd_LT[1] = vertical[1];
        virtual_abcd_LT[2] = vertical[2];
        virtual_abcd_LT[3] = d;
    }else { // 1 2 3
        virtual_abcd_RB[0] = vertical[0];
        virtual_abcd_RB[1] = vertical[1];
        virtual_abcd_RB[2] = vertical[2];
        virtual_abcd_RB[3] = d;
    }


    glm::vec3 virtual_ScreenPoint = {x,y,0.f};

    goLine32 rayNorm = ScreenDemo::get_AgoB_direction3D(startEye, virtual_ScreenPoint);
    // step_up = -(ax+by+cz+d)
    float step_up = -glm::dot(startEye, vertical) - d;
    // step_down = dot(rayNorm, vertical)
    float step_down = glm::dot(rayNorm._, vertical);
    float t = step_up / step_down;
    glm::vec3 result = startEye + rayNorm._ * t;
    return result;
}
glm::vec3 Rect2Flat::getXYZ_ByVirtual3Point_(const glm::vec3& cornerIndex, float x, float y,goLine32* rayNorm) {
    glm::vec3& p1 = virtual_ltrt_rblb[cornerIndex[0]].pos;
    glm::vec3& p2 = virtual_ltrt_rblb[cornerIndex[1]].pos;
    glm::vec3& p3 = virtual_ltrt_rblb[cornerIndex[2]].pos;
    // 两边 射线
    glm::vec3 p2Top1 = p1 - p2;
    glm::vec3 p2Top3 = p3 - p2;
    // 向量叉乘
    // 归一化法线
    glm::vec3 vertical = glm::normalize(glm::cross(p2Top1, p2Top3)); // a b c

    // ax+by+cz+d=0  d=-(ax+by+cz)
    float d = -glm::dot(vertical, p1);

    glm::vec3 virtual_ScreenPoint = {x,y,0.f};

    *rayNorm = ScreenDemo::get_AgoB_direction3D(startEye, virtual_ScreenPoint);
    // step_up = -(ax+by+cz+d)
    float step_up = -glm::dot(startEye, vertical) - d;
    // step_down = dot(rayNorm, vertical)
    float step_down = glm::dot((*rayNorm)._, vertical);
    float t = step_up / step_down;
    glm::vec3 result = startEye + (*rayNorm)._ * t;
    return result;
}
void Rect2Flat::fresh2FrontBack() {
    const bool & front0 = virtual_ltrt_rblb[0].onFront;
    const bool & front1 = virtual_ltrt_rblb[1].onFront;
    const bool & front2 = virtual_ltrt_rblb[2].onFront;
    const bool & front3 = virtual_ltrt_rblb[3].onFront;
    // 视点 - 顶点 = 顶点连视线  dot(视线,法线)  >0 正面  <0 背面
    //cout << "front 4 points: " << front0 << " " << front1 << " " << front2 << " " << front3 << endl;

    if (front0 && front1 && front3) { // 0 1 3
        frontLT = 1; // 全正
    }else if (!front0 && !front1 && !front3) {
        frontLT = -1; // 全负
    }else {
        frontLT = 0; // 半正半负
    }

    if (front1 && front2 && front3) { // 1 2 3
        frontRB = 1;
    }else if (!front1 && !front2 && !front3) {
        frontRB = -1;
    }else {
        frontRB = 0;
    }

}

void Rect2Flat::freshTriangle(ScreenDemo* ScreenEye, cloudInfo lt, cloudInfo rt,
        cloudInfo rb, cloudInfo lb) {
    // 世界系 4点
    fresh8Points(lt, rt, rb, lb);
    // 3d 屏幕系 2d
    fresh4Points_3D2D(ScreenEye);
    // 行扫描信息
    freshLineBoundary_triangle();
    // 两三角面 正反
    fresh2FrontBack();
}

void Rect2Flat::draw2Triangle(ScreenDemo* ScreenEye,float frontColor[],float backColor[], PolygonBase* Self) {

    for(lineBoundary & _linePosInfo : triangleLT) {
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; ++nowX) {
            glm::vec3 surfaceP = getXYZ_ByVirtual3Point({0,1,3},
                nowX, _linePosInfo.y);
            if (frontLT == 1)
            ScreenEye->putPixel(nowX, _linePosInfo.y, frontColor, surfaceP.z, Self);
            else if (frontLT == -1)
            ScreenEye->putPixel(nowX, _linePosInfo.y, backColor, surfaceP.z, Self);
            else {
                ScreenEye->putPixel(nowX, _linePosInfo.y, frontBackColor, surfaceP.z, Self);
            }

        }
    }
    for(lineBoundary & _linePosInfo : triangleRB) {
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; ++nowX) {
            glm::vec3 surfaceP = getXYZ_ByVirtual3Point({1,2,3},
                nowX, _linePosInfo.y);
            if (frontRB == 1)
            ScreenEye->putPixel(nowX, _linePosInfo.y, frontColor, surfaceP.z, Self);
            else if (frontRB == -1)
            ScreenEye->putPixel(nowX, _linePosInfo.y, backColor, surfaceP.z, Self);
            else {
                ScreenEye->putPixel(nowX, _linePosInfo.y, frontBackColor, surfaceP.z, Self);
            }

        }
    }
}
#ifdef showEdgeRectVertical
void Rect2Flat::draw2Triangle_(ScreenDemo* ScreenEye,float frontColor[],float backColor[],
    float verticalColor[], PolygonBase* Self) {
    draw2Triangle(ScreenEye,frontColor,backColor,Self);

    for(int i = 0; i < 4; ++i) {
        float deepNow = (virtual_ltrt_rblb[i].pos.z + virtual_ltrt_rblb[i].verticalP.z) / 2.f;
        ScreenDemo::line2ScreenBuffer(ScreenEye,ltrt_rblb_2d[i].first.x, ltrt_rblb_2d[i].first.y,
            ltrt_rblb_2d[i].second.x,ltrt_rblb_2d[i].second.y, verticalColor, deepNow);
    }

}
#endif
void Rect2Flat::clacAddPixelsInfo(PolygonBase* Self, glm::vec3 _p[][5],vector<pixelDeep23_>* pixelSurfaceInfo) {
    glm::vec3 p0 = virtual_ltrt_rblb[0].pos;
    glm::vec3 p1 = virtual_ltrt_rblb[1].pos;
    glm::vec3 p2 = virtual_ltrt_rblb[2].pos;
    glm::vec3 p3 = virtual_ltrt_rblb[3].pos;
    goLine32 rayNorm;
    for(auto& _linePosInfo : triangleLT) {
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; ++nowX) {
            glm::vec3 surfaceP = getXYZ_ByVirtual3Point_({0,1,3},
                nowX, _linePosInfo.y, &rayNorm);
            float pTo0_22 = glm::dot(surfaceP - p0,surfaceP - p0);
            float pTo1_22 = glm::dot(surfaceP - p1,surfaceP - p1);
            float pTo3_22 = glm::dot(surfaceP - p3,surfaceP - p3);
            unsigned char minIndex_ = minIndex(pTo0_22, pTo1_22, pTo3_22);
            if (minIndex_ == 2)minIndex_ = 3; // 修正
            glm::vec2 uv = virtual_ltrt_rblb[minIndex_].uv;

            std::expected<curveSurfaceInfo,char> resultNow =
                dynamic_cast<Bezier33Edge4*>(Self)->rayIntersectBezier3_(rayNorm,_p,uv);
            if (!resultNow)continue;
            pixelDeep23_ pixelInfo;
            pixelInfo.xy = {nowX,_linePosInfo.y};
            pixelInfo.uv = resultNow->uv;
            pixelInfo.screenDeep = resultNow->virtual_Pos.z;
            pixelInfo.faceToCamera = resultNow->faceToCamera;
            pixelSurfaceInfo->emplace_back(pixelInfo);

        }
    }
    for(auto& _linePosInfo : triangleRB) {
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; ++nowX) {
            glm::vec3 surfaceP = getXYZ_ByVirtual3Point_({0,1,3},
                nowX, _linePosInfo.y, &rayNorm);
            float pTo1_22 = glm::dot(surfaceP - p1,surfaceP - p1);
            float pTo2_22 = glm::dot(surfaceP - p2,surfaceP - p2);
            float pTo3_22 = glm::dot(surfaceP - p3,surfaceP - p3);
            unsigned char minIndex_ = minIndex(pTo1_22, pTo2_22, pTo3_22);
            minIndex_ += 1; // 修正
            glm::vec2 uv = virtual_ltrt_rblb[minIndex_].uv;

            std::expected<curveSurfaceInfo,char> resultNow =
                dynamic_cast<Bezier33Edge4*>(Self)->rayIntersectBezier3_(rayNorm,_p,uv);
            if (!resultNow)continue;
            pixelDeep23_ pixelInfo;
            pixelInfo.xy = {nowX,_linePosInfo.y};
            pixelInfo.uv = resultNow->uv;
            pixelInfo.screenDeep = resultNow->virtual_Pos.z;
            pixelInfo.faceToCamera = resultNow->faceToCamera;
            pixelSurfaceInfo->emplace_back(pixelInfo);

        }
    }
}
unsigned char Rect2Flat::minIndex(float a, float b, float c) {
    if (a < b) {
        if (a < c) {
            return 0; // a最小
        }else {
            return 2; // c最小
        }
    }else { // a >= b
        if (b < c) {
            return 1; // b最小
        }else {
            return 2; // c最小
        }
    }
    throw "minIndex error";
}
Bezier33Edge4::Bezier33Edge4(glm::vec3 _P[5][5], unsigned char _mesh): PolygonBase(23){

    __init__(_P, _mesh);
}
Bezier33Edge4::Bezier33Edge4(glm::vec3 _P[4][4], int _type) : PolygonBase(_type){
    glm::vec3 p_[5][5] = {
        {_P[0][0],_P[0][1],_P[0][2],_P[0][3],glm::vec3(0.f)},
        {_P[1][0],_P[1][1],_P[1][2],_P[1][3],glm::vec3(0.f)},
        {_P[2][0],_P[2][1],_P[2][2],_P[2][3],glm::vec3(0.f)},
        {_P[3][0], _P[3][1], _P[3][2], _P[3][3], glm::vec3(0.f)},
        {glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.f)}
    };
    __init__(p_, 4);
}

void Bezier33Edge4::__init__(glm::vec3 _P[5][5], unsigned char _mesh) {
    // type_ = 23;

    assert(_mesh <= 5 && _mesh >=3);
    this->surfaceTimes = _mesh;

    if (fastIteration) {
        if (_mesh != 4) {
            throw std::exception("fastIteration support only for mesh 4");
            assert(_mesh == 4);
        }
    }

    // 存储控制点
    for(int i=0;i<5; ++i){
        for(int j=0;j<5; ++j){
            P[i][j].x = _P[i][j].x;
            P[i][j].y = _P[i][j].y;
            P[i][j].z = _P[i][j].z;
            P_unchange[i][j].x = _P[i][j].x;
            P_unchange[i][j].y = _P[i][j].y;
            P_unchange[i][j].z = _P[i][j].z;
        }
    }
    // n阶曲面需要(n+1)²控制点
    if(surfaceTimes == 3){
        generateGrid_2(); // 生成曲面网格点
    }else if(surfaceTimes == 4){
        generateGrid_3(); // 生成曲面网格点
    }else if(surfaceTimes == 5){
        generateGrid_4(); // 生成曲面网格点
    }



    initBox_TBLRNF(); // 在拿到网格点后 计算包围盒 外围

    initBoxInfo(); // 计算包围盒 顶点 与 all tips

    // smallBoxExpand = {
    //     (boxVolume.rightX-boxVolume.leftX) * 0.005f,
    //     (boxVolume.bottomY-boxVolume.topY) * 0.005f,
    //     (boxVolume.farZ-boxVolume.nearZ) * 0.005f
    // };
    initBox4Points(); // 计算包围盒 4点
    initBox9Cubes(); // 计算包围盒 内9个立方体

    backColor[0] = 149.f/255.f;
    backColor[1] = 143.f/255.f;
    backColor[2] = 93.f/255.f;

    renderNext = false;

    startRowIndex_=0;



    rect2Flats.outterMax = N_v - 1;
    rect2Flats.innerMax = N_u - 1;
    rect2Flats.data.resize(rect2Flats.outterMax * rect2Flats.innerMax);
    for(int outter=0;outter<rect2Flats.outterMax; ++outter) {
        for(int inner=0;inner<rect2Flats.innerMax; ++inner){
            rect2Flats(outter, inner) = Rect2Flat();
        }

    }
    for(int i = 0; i < rect2Flats_Top.size(); ++i) {
        rect2Flats_Top[i] = Rect2Flat();
    }
    for(int i = 0; i < rect2Flats_Bottom.size(); ++i) {
        rect2Flats_Bottom[i] = Rect2Flat();
    }
    for(int i = 0; i < rect2Flats_Left.size(); ++i) {
        rect2Flats_Left[i] = Rect2Flat();
    }
    for(int i = 0; i < rect2Flats_Right.size(); ++i) {
        rect2Flats_Right[i] = Rect2Flat();
    }

    verticalColor[0] = 244.f/255.f;
    verticalColor[1] = 166.f/255.f;
    verticalColor[2] = 35.f/255.f;

    isIn  = [](vector<int>& vec, int num) {
        if (vec.empty()) return false;
        return std::find(vec.begin(), vec.end(), num) != vec.end();
    };
    solve3x3 = [](const float J[3][3], const float F[3], float delta[3]) {
        float det = J[0][0] * (J[1][1]*J[2][2] - J[1][2]*J[2][1])
                    - J[0][1] * (J[1][0]*J[2][2] - J[1][2]*J[2][0])
                    + J[0][2] * (J[1][0]*J[2][1] - J[1][1]*J[2][0]);

        if (fabs(det) < 1e-12f) return false;

        float invDet = 1.0f / det;

        delta[0] = invDet * (F[0]*(J[1][1]*J[2][2] - J[1][2]*J[2][1])
                             - F[1]*(J[0][1]*J[2][2] - J[0][2]*J[2][1])
                             + F[2]*(J[0][1]*J[1][2] - J[0][2]*J[1][1]));

        delta[1] = invDet * (-F[0]*(J[1][0]*J[2][2] - J[1][2]*J[2][0])
                             + F[1]*(J[0][0]*J[2][2] - J[0][2]*J[2][0])
                             - F[2]*(J[0][0]*J[1][2] - J[0][2]*J[1][0]));

        delta[2] = invDet * (F[0]*(J[1][0]*J[2][1] - J[1][1]*J[2][0])
                             - F[1]*(J[0][0]*J[2][1] - J[0][1]*J[2][0])
                             + F[2]*(J[0][0]*J[1][1] - J[0][1]*J[1][0]));
        return true;
    };
    solve3x3_ = [](const float J[3][3], const glm::vec3& F, float delta[3]) {
        float det = J[0][0] * (J[1][1]*J[2][2] - J[1][2]*J[2][1])
                    - J[0][1] * (J[1][0]*J[2][2] - J[1][2]*J[2][0])
                    + J[0][2] * (J[1][0]*J[2][1] - J[1][1]*J[2][0]);

        if (fabs(det) < 1e-12f) return false;

        float invDet = 1.0f / det;

        delta[0] = invDet * (F[0]*(J[1][1]*J[2][2] - J[1][2]*J[2][1])
                             - F[1]*(J[0][1]*J[2][2] - J[0][2]*J[2][1])
                             + F[2]*(J[0][1]*J[1][2] - J[0][2]*J[1][1]));

        delta[1] = invDet * (-F[0]*(J[1][0]*J[2][2] - J[1][2]*J[2][0])
                             + F[1]*(J[0][0]*J[2][2] - J[0][2]*J[2][0])
                             - F[2]*(J[0][0]*J[1][2] - J[0][2]*J[1][0]));

        delta[2] = invDet * (F[0]*(J[1][0]*J[2][1] - J[1][1]*J[2][0])
                             - F[1]*(J[0][0]*J[2][1] - J[0][1]*J[2][0])
                             + F[2]*(J[0][0]*J[1][1] - J[0][1]*J[1][0]));
        return true;
    };


}
void Bezier33Edge4::generateGrid_4(){
    float delta_u = 1.f / (N_u - 1); // 步长1/15
    float delta_v = 1.f / (N_v - 1); // 步长1/15

    float x, y, z;

    for(int u_step = 0; u_step < N_v; ++u_step) {
        float u = u_step * delta_u; // 0~1
        for(int v_step = 0; v_step < N_u; ++v_step) {
            float v = v_step * delta_v; // 0~1

            // 计算基函数值 杨辉三角 14641
            float Bu[5] = {
                    (1-u) * (1-u) * (1-u) * (1-u),
                    4 * u * (1-u) * (1-u) * (1-u),
                    6 * u * u * (1 - u) * (1 - u),
                    4 * u * u * u * (1 - u),
                    u * u * u * u
            };

            float Bv[5] = {
                    (1-v) * (1-v) * (1-v) * (1-v),
                    4 * v * (1-v) * (1-v) * (1-v),
                    6 * v * v * (1 - v) * (1 - v),
                    4 * v * v * v * (1 - v),
                    v * v * v * v
            };
/*            x=0;y=0;z=0;
            for(int i=0;i<5; ++i){
                for(int j=0;j<5; ++j){
                    x+=Bu[i]*Bv[j]*P[i][j].x;
                    y+=Bu[i]*Bv[j]*P[i][j].y;
                    z+=Bu[i]*Bv[j]*P[i][j].z;
                }
            }*/
x = Bu[0]*Bv[0] * P[0][0].x + Bu[0]*Bv[1] * P[0][1].x + Bu[0]*Bv[2] * P[0][2].x + Bu[0]*Bv[3] * P[0][3].x + Bu[0]*Bv[4] * P[0][4].x +
    Bu[1]*Bv[0] * P[1][0].x + Bu[1]*Bv[1] * P[1][1].x + Bu[1]*Bv[2] * P[1][2].x + Bu[1]*Bv[3] * P[1][3].x + Bu[1]*Bv[4] * P[1][4].x +
    Bu[2]*Bv[0] * P[2][0].x + Bu[2]*Bv[1] * P[2][1].x + Bu[2]*Bv[2] * P[2][2].x + Bu[2]*Bv[3] * P[2][3].x + Bu[2]*Bv[4] * P[2][4].x +
    Bu[3]*Bv[0] * P[3][0].x + Bu[3]*Bv[1] * P[3][1].x + Bu[3]*Bv[2] * P[3][2].x + Bu[3]*Bv[3] * P[3][3].x + Bu[3]*Bv[4] * P[3][4].x +
    Bu[4]*Bv[0] * P[4][0].x + Bu[4]*Bv[1] * P[4][1].x + Bu[4]*Bv[2] * P[4][2].x + Bu[4]*Bv[3] * P[4][3].x + Bu[4]*Bv[4] * P[4][4].x;

y = Bu[0]*Bv[0] * P[0][0].y + Bu[0]*Bv[1] * P[0][1].y + Bu[0]*Bv[2] * P[0][2].y + Bu[0]*Bv[3] * P[0][3].y + Bu[0]*Bv[4] * P[0][4].y +
    Bu[1]*Bv[0] * P[1][0].y + Bu[1]*Bv[1] * P[1][1].y + Bu[1]*Bv[2] * P[1][2].y + Bu[1]*Bv[3] * P[1][3].y + Bu[1]*Bv[4] * P[1][4].y +
    Bu[2]*Bv[0] * P[2][0].y + Bu[2]*Bv[1] * P[2][1].y + Bu[2]*Bv[2] * P[2][2].y + Bu[2]*Bv[3] * P[2][3].y + Bu[2]*Bv[4] * P[2][4].y +
    Bu[3]*Bv[0] * P[3][0].y + Bu[3]*Bv[1] * P[3][1].y + Bu[3]*Bv[2] * P[3][2].y + Bu[3]*Bv[3] * P[3][3].y + Bu[3]*Bv[4] * P[3][4].y +
    Bu[4]*Bv[0] * P[4][0].y + Bu[4]*Bv[1] * P[4][1].y + Bu[4]*Bv[2] * P[4][2].y + Bu[4]*Bv[3] * P[4][3].y + Bu[4]*Bv[4] * P[4][4].y;

z = Bu[0]*Bv[0] * P[0][0].z + Bu[0]*Bv[1] * P[0][1].z + Bu[0]*Bv[2] * P[0][2].z + Bu[0]*Bv[3] * P[0][3].z + Bu[0]*Bv[4] * P[0][4].z +
    Bu[1]*Bv[0] * P[1][0].z + Bu[1]*Bv[1] * P[1][1].z + Bu[1]*Bv[2] * P[1][2].z + Bu[1]*Bv[3] * P[1][3].z + Bu[1]*Bv[4] * P[1][4].z +
    Bu[2]*Bv[0] * P[2][0].z + Bu[2]*Bv[1] * P[2][1].z + Bu[2]*Bv[2] * P[2][2].z + Bu[2]*Bv[3] * P[2][3].z + Bu[2]*Bv[4] * P[2][4].z +
    Bu[3]*Bv[0] * P[3][0].z + Bu[3]*Bv[1] * P[3][1].z + Bu[3]*Bv[2] * P[3][2].z + Bu[3]*Bv[3] * P[3][3].z + Bu[3]*Bv[4] * P[3][4].z +
    Bu[4]*Bv[0] * P[4][0].z + Bu[4]*Bv[1] * P[4][1].z + Bu[4]*Bv[2] * P[4][2].z + Bu[4]*Bv[3] * P[4][3].z + Bu[4]*Bv[4] * P[4][4].z;

            // 存储网格点
            Grid(v_step,u_step).first.x = x;
            Grid(v_step,u_step).first.y = y;
            Grid(v_step,u_step).first.z = z;
            Grid_unchange(v_step,u_step).first.x = x;
            Grid_unchange(v_step,u_step).first.y = y;
            Grid_unchange(v_step,u_step).first.z = z;
        }
    }
}
void Bezier33Edge4::generateGrid_3(){

    float delta_u = 1.0 / (N_u - 1); // 步长1/15
    float delta_v = 1.0 / (N_v - 1); // 步长1/15
    float x,y,z;


    for(int v_step = 0; v_step < N_v; ++v_step) {
        float v = v_step * delta_v; // 0~1

        for(int u_step = 0; u_step < N_u; ++u_step) {
            float u = u_step * delta_u; // 0~1

            // 计算基函数值 杨辉三角 1331
            float Bu[4] = {
                    (1-u) * (1-u) * (1-u),
                    3 * u * (1-u) * (1-u),
                    3 * u * u * (1 - u),
                    u * u * u
            };

            float Bv[4] = {
                    (1-v) * (1-v) * (1-v),
                    3 * v * (1-v) * (1-v),
                    3 * v * v * (1 - v),
                    v * v * v
            };

            // 计算坐标加权和
            x = 0.0;y = 0.0;z = 0.0;
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    x += Bu[i] * Bv[j] * P[i][j].x; // P 世界系 锚点
                    y += Bu[i] * Bv[j] * P[i][j].y;
                    z += Bu[i] * Bv[j] * P[i][j].z;
                }
            }

            // x = Bu[0]*Bv[0] * P[0][0].x + Bu[0]*Bv[1] * P[0][1].x + Bu[0]*Bv[2] * P[0][2].x + Bu[0]*Bv[3] * P[0][3].x +
            //     Bu[1]*Bv[0] * P[1][0].x + Bu[1]*Bv[1] * P[1][1].x + Bu[1]*Bv[2] * P[1][2].x + Bu[1]*Bv[3] * P[1][3].x +
            //     Bu[2]*Bv[0] * P[2][0].x + Bu[2]*Bv[1] * P[2][1].x + Bu[2]*Bv[2] * P[2][2].x + Bu[2]*Bv[3] * P[2][3].x +
            //     Bu[3]*Bv[0] * P[3][0].x + Bu[3]*Bv[1] * P[3][1].x + Bu[3]*Bv[2] * P[3][2].x + Bu[3]*Bv[3] * P[3][3].x;
            //
            // y = Bu[0]*Bv[0] * P[0][0].y + Bu[0]*Bv[1] * P[0][1].y + Bu[0]*Bv[2] * P[0][2].y + Bu[0]*Bv[3] * P[0][3].y +
            //     Bu[1]*Bv[0] * P[1][0].y + Bu[1]*Bv[1] * P[1][1].y + Bu[1]*Bv[2] * P[1][2].y + Bu[1]*Bv[3] * P[1][3].y +
            //     Bu[2]*Bv[0] * P[2][0].y + Bu[2]*Bv[1] * P[2][1].y + Bu[2]*Bv[2] * P[2][2].y + Bu[2]*Bv[3] * P[2][3].y +
            //     Bu[3]*Bv[0] * P[3][0].y + Bu[3]*Bv[1] * P[3][1].y + Bu[3]*Bv[2] * P[3][2].y + Bu[3]*Bv[3] * P[3][3].y;
            //
            // z = Bu[0]*Bv[0] * P[0][0].z + Bu[0]*Bv[1] * P[0][1].z + Bu[0]*Bv[2] * P[0][2].z + Bu[0]*Bv[3] * P[0][3].z +
            //     Bu[1]*Bv[0] * P[1][0].z + Bu[1]*Bv[1] * P[1][1].z + Bu[1]*Bv[2] * P[1][2].z + Bu[1]*Bv[3] * P[1][3].z +
            //     Bu[2]*Bv[0] * P[2][0].z + Bu[2]*Bv[1] * P[2][1].z + Bu[2]*Bv[2] * P[2][2].z + Bu[2]*Bv[3] * P[2][3].z +
            //     Bu[3]*Bv[0] * P[3][0].z + Bu[3]*Bv[1] * P[3][1].z + Bu[3]*Bv[2] * P[3][2].z + Bu[3]*Bv[3] * P[3][3].z;

            // 存储网格点
            Grid(v_step,u_step).first.x = x;
            Grid(v_step,u_step).first.y = y;
            Grid(v_step,u_step).first.z = z;
            Grid_unchange(v_step,u_step).first.x = x;
            Grid_unchange(v_step,u_step).first.y = y;
            Grid_unchange(v_step,u_step).first.z = z;

            glm::vec3 S_, Su_, Sv_;
            surfaceDerivatives3(u, v, P, &S_, &Su_, &Sv_);
            // 计算法线（叉乘前先归一化）
            glm::vec3 normalVertical = glm::normalize(glm::cross(Su_, Sv_));
            //cout << "--normalVertical: " << normalVertical.x << " " << normalVertical.y << " " << normalVertical.z << endl;

            Grid(v_step,u_step).second = Grid(v_step,u_step).first - normalVertical;
            Grid_unchange(v_step,u_step).second = Grid_unchange(v_step,u_step).first - normalVertical;

            virtual_Grid(v_step,u_step).uv = glm::vec2(u, v);
        }
    }
    if (fastIteration || showEdgeRect) {
        for(int u_step = 0; u_step < N_u; ++u_step) {
        float u = u_step * delta_u; // 0~1
        float v = -delta_v * edgeFlatWide;

        // 计算基函数值 杨辉三角 1331
        float Bu[4] = {
            (1-u) * (1-u) * (1-u),
            3 * u * (1-u) * (1-u),
            3 * u * u * (1 - u),
            u * u * u
        };

        float Bv[4] = {
            (1-v) * (1-v) * (1-v),
            3 * v * (1-v) * (1-v),
            3 * v * v * (1 - v),
            v * v * v
         };

        // 计算坐标加权和
        x = 0.0;y = 0.0;z = 0.0;
        for(int i = 0; i < 4; ++i) {
            for(int j = 0; j < 4; ++j) {
                x += Bu[i] * Bv[j] * P[i][j].x;
                y += Bu[i] * Bv[j] * P[i][j].y;
                z += Bu[i] * Bv[j] * P[i][j].z;
            }
        }

        Grid_edgeTop[u_step].first.x = x;
        Grid_edgeTop[u_step].first.y = y;
        Grid_edgeTop[u_step].first.z = z;
        Grid_edgeTop_unchange[u_step].first.x = x;
        Grid_edgeTop_unchange[u_step].first.y = y;
        Grid_edgeTop_unchange[u_step].first.z = z;

        glm::vec3 S_, Su_, Sv_;
        surfaceDerivatives3(u, v, P, &S_, &Su_, &Sv_);
        // 计算法线（叉乘前先归一化）
        glm::vec3 normalVertical = glm::normalize(glm::cross(Su_, Sv_));
        //cout << "--normalVertical: " << normalVertical.x << " " << normalVertical.y << " " << normalVertical.z << endl;

        Grid_edgeTop[u_step].second = Grid_edgeTop[u_step].first - normalVertical;
        Grid_edgeTop_unchange[u_step].second = Grid_edgeTop_unchange[u_step].first - normalVertical;

        virtual_Grid_edgeTop[u_step].uv = glm::vec2(u, v);


        }
        for(int u_step = 0; u_step < N_u; ++u_step) {
            float u = u_step * delta_u; // 0~1
            float v = 1.f + delta_v * edgeFlatWide;

            // 计算基函数值 杨辉三角 1331
            float Bu[4] = {
                (1-u) * (1-u) * (1-u),
                3 * u * (1-u) * (1-u),
                3 * u * u * (1 - u),
                u * u * u
        };

            float Bv[4] = {
                (1-v) * (1-v) * (1-v),
                3 * v * (1-v) * (1-v),
                3 * v * v * (1 - v),
                v * v * v
        };

        // 计算坐标加权和
        x = 0.0;y = 0.0;z = 0.0;
        for(int i = 0; i < 4; ++i) {
            for(int j = 0; j < 4; ++j) {
                x += Bu[i] * Bv[j] * P[i][j].x;
                y += Bu[i] * Bv[j] * P[i][j].y;
                z += Bu[i] * Bv[j] * P[i][j].z;
            }
        }
        Grid_edgeBottom[u_step].first.x = x;
        Grid_edgeBottom[u_step].first.y = y;
        Grid_edgeBottom[u_step].first.z = z;
        Grid_edgeBottom_unchange[u_step].first.x = x;
        Grid_edgeBottom_unchange[u_step].first.y = y;
        Grid_edgeBottom_unchange[u_step].first.z = z;

        glm::vec3 S_, Su_, Sv_;
        surfaceDerivatives3(u, v, P, &S_, &Su_, &Sv_);
        // 计算法线（叉乘前先归一化）
        glm::vec3 normalVertical = glm::normalize(glm::cross(Su_, Sv_));
        //cout << "--normalVertical: " << normalVertical.x << " " << normalVertical.y << " " << normalVertical.z << endl;

        Grid_edgeBottom[u_step].second = Grid_edgeBottom[u_step].first - normalVertical;
        Grid_edgeBottom_unchange[u_step].second = Grid_edgeBottom_unchange[u_step].first - normalVertical;

        virtual_Grid_edgeBottom[u_step].uv = glm::vec2(u, v);
        }
        for(int v_step = 0; v_step < N_v; ++v_step) {
            float u = -delta_u * edgeFlatWide; // 0~1
            float v = v_step * delta_v ;

            // 计算基函数值 杨辉三角 1331
            float Bu[4] = {
                (1-u) * (1-u) * (1-u),
                3 * u * (1-u) * (1-u),
                3 * u * u * (1 - u),
                u * u * u
            };

                float Bv[4] = {
                    (1-v) * (1-v) * (1-v),
                    3 * v * (1-v) * (1-v),
                    3 * v * v * (1 - v),
                    v * v * v
            };

            // 计算坐标加权和
            x = 0.0;y = 0.0;z = 0.0;
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    x += Bu[i] * Bv[j] * P[i][j].x;
                    y += Bu[i] * Bv[j] * P[i][j].y;
                    z += Bu[i] * Bv[j] * P[i][j].z;
                }
            }
            Grid_edgeLeft[v_step].first.x = x;
            Grid_edgeLeft[v_step].first.y = y;
            Grid_edgeLeft[v_step].first.z = z;
            Grid_edgeLeft_unchange[v_step].first.x = x;
            Grid_edgeLeft_unchange[v_step].first.y = y;
            Grid_edgeLeft_unchange[v_step].first.z = z;

            glm::vec3 S_, Su_, Sv_;
            surfaceDerivatives3(u, v, P, &S_, &Su_, &Sv_);
            // 计算法线（叉乘前先归一化）
            glm::vec3 normalVertical = glm::normalize(glm::cross(Su_, Sv_));
            //cout << "--normalVertical: " << normalVertical.x << " " << normalVertical.y << " " << normalVertical.z << endl;

            Grid_edgeLeft[v_step].second = Grid_edgeLeft[v_step].first - normalVertical;
            Grid_edgeLeft_unchange[v_step].second = Grid_edgeLeft_unchange[v_step].first - normalVertical;

            virtual_Grid_edgeLeft[v_step].uv = glm::vec2(u, v);
        }
        for(int v_step = 0; v_step < N_v; ++v_step) {

            float u = 1.f + delta_u * edgeFlatWide; // 0~1
            float v = v_step * delta_v;

            // 计算基函数值 杨辉三角 1331
            float Bu[4] = {
                (1-u) * (1-u) * (1-u),
                3 * u * (1-u) * (1-u),
                3 * u * u * (1 - u),
                u * u * u
            };

            float Bv[4] = {
                (1-v) * (1-v) * (1-v),
                3 * v * (1-v) * (1-v),
                3 * v * v * (1 - v),
                v * v * v
            };

            // 计算坐标加权和
            x = 0.0;y = 0.0;z = 0.0;
            for(int i = 0; i < 4; ++i) {
                for(int j = 0; j < 4; ++j) {
                    x += Bu[i] * Bv[j] * P[i][j].x;
                    y += Bu[i] * Bv[j] * P[i][j].y;
                    z += Bu[i] * Bv[j] * P[i][j].z;
                }
            }
            Grid_edgeRight[v_step].first.x = x;
            Grid_edgeRight[v_step].first.y = y;
            Grid_edgeRight[v_step].first.z = z;
            Grid_edgeRight_unchange[v_step].first.x = x;
            Grid_edgeRight_unchange[v_step].first.y = y;
            Grid_edgeRight_unchange[v_step].first.z = z;

            glm::vec3 S_, Su_, Sv_;
            surfaceDerivatives3(u, v, P, &S_, &Su_, &Sv_);
            // 计算法线（叉乘前先归一化）
            glm::vec3 normalVertical = glm::normalize(glm::cross(Su_, Sv_));
            //cout << "--normalVertical: " << normalVertical.x << " " << normalVertical.y << " " << normalVertical.z << endl;

            Grid_edgeRight[v_step].second = Grid_edgeRight[v_step].first - normalVertical;
            Grid_edgeRight_unchange[v_step].second = Grid_edgeRight_unchange[v_step].first - normalVertical;

            virtual_Grid_edgeRight[v_step].uv = glm::vec2(u, v);
        }
    }

}
void Bezier33Edge4::generateGrid_2(){
    float delta_u = 1.0 / (N_u - 1); // 步长1/15
    float delta_v = 1.0 / (N_v - 1); // 步长1/15
    float x, y, z;

    for(int u_step = 0; u_step < N_v; ++u_step) {
        float u = u_step * delta_u; // 0~1
        for(int v_step = 0; v_step < N_u; ++v_step) {
            float v = v_step * delta_v; // 0~1

            // 计算基函数值 杨辉三角 121
            float Bu[3] = {
                    (1-u) * (1-u),
                    2 * u * (1-u),
                    u * u
            };
            float Bv[3] = {
                    (1-v) * (1-v),
                    2 * v * (1-v),
                    v * v
            };
            x = Bu[0]*Bv[0] * P[0][0].x + Bu[0]*Bv[1] * P[0][1].x + Bu[0]*Bv[2] * P[0][2].x +
                Bu[1]*Bv[0] * P[1][0].x + Bu[1]*Bv[1] * P[1][1].x + Bu[1]*Bv[2] * P[1][2].x +
                Bu[2]*Bv[0] * P[2][0].x + Bu[2]*Bv[1] * P[2][1].x + Bu[2]*Bv[2] * P[2][2].x;
            y = Bu[0]*Bv[0] * P[0][0].y + Bu[0]*Bv[1] * P[0][1].y + Bu[0]*Bv[2] * P[0][2].y +
                Bu[1]*Bv[0] * P[1][0].y + Bu[1]*Bv[1] * P[1][1].y + Bu[1]*Bv[2] * P[1][2].y +
                Bu[2]*Bv[0] * P[2][0].y + Bu[2]*Bv[1] * P[2][1].y + Bu[2]*Bv[2] * P[2][2].y;
            z = Bu[0]*Bv[0] * P[0][0].z + Bu[0]*Bv[1] * P[0][1].z + Bu[0]*Bv[2] * P[0][2].z +
                Bu[1]*Bv[0] * P[1][0].z + Bu[1]*Bv[1] * P[1][1].z + Bu[1]*Bv[2] * P[1][2].z +
                Bu[2]*Bv[0] * P[2][0].z + Bu[2]*Bv[1] * P[2][1].z + Bu[2]*Bv[2] * P[2][2].z;


            // 存储网格点
            Grid(v,u).first.x = x;
            Grid(v,u).first.y = y;
            Grid(v,u).first.z = z;
            Grid_unchange(v,u).first.x = x;
            Grid_unchange(v,u).first.y = y;
            Grid_unchange(v,u).first.z = z;
        }
    }
    //只有step为正且u、v在[0,1]的解才是有效的交点
}
TBLRFB Bezier33Edge4::initBox_TBLRNF(){
    // 上下 左右 近远
    boxVolume = {Grid(0,0).first.y, Grid(0,0).first.y,
                        Grid(0,0).first.x, Grid(0,0).first.x,
                        Grid(0,0).first.z, Grid(0,0).first.z}; // 初始化为数组内的 避免自己把极值定到外边
    // 便利网格点 找出最小最大值
    for(int i=0;i<N_v; ++i){
        for(int j=0;j<N_u; ++j){
            if(Grid(i,j).first.y < boxVolume.topY) boxVolume.topY = Grid(i,j).first.y;
            else if(Grid(i,j).first.y > boxVolume.bottomY) boxVolume.bottomY = Grid(i,j).first.y;

            if(Grid(i,j).first.x < boxVolume.leftX) boxVolume.leftX = Grid(i,j).first.x;
            else if(Grid(i,j).first.x > boxVolume.rightX) boxVolume.rightX = Grid(i,j).first.x;

            if(Grid(i,j).first.z < boxVolume.nearZ) boxVolume.nearZ = Grid(i,j).first.z;
            else if(Grid(i,j).first.z > boxVolume.farZ) boxVolume.farZ = Grid(i,j).first.z;
        }
    }
    // float top_bottom_distance = (boxVolume.bottomY - boxVolume.topY) / 2.f;
    // float right_left_distance = (boxVolume.rightX - boxVolume.leftX) / 2.f;
    // float far_near_distance = (boxVolume.farZ - boxVolume.nearZ) / 2.f;
    // boxLenX = top_bottom_distance;
    // boxLenY = right_left_distance;
    // boxLenZ = far_near_distance;

    float betweenY_ = boxVolume.bottomY - boxVolume.topY;
    float betweenX_ = boxVolume.rightX - boxVolume.leftX;
    float betweenZ_ = boxVolume.farZ - boxVolume.nearZ;
    float top_bottom_distance = betweenY_ / 2.f;
    float right_left_distance = betweenX_ / 2.f;
    float far_near_distance =   betweenZ_ / 2.f;


    boxVolume.topY -= top_bottom_distance * 0.03f; // 上拓 5%
    //cout << " 上拓 5% " << endl;

    boxVolume.bottomY += top_bottom_distance * 0.03f; // 下拓 5%
    //cout << " 下拓 5% " << endl;

    boxVolume.leftX -= right_left_distance * 0.03f; // 左拓 5%
    //cout << " 左拓 5% " << endl;

    boxVolume.rightX += right_left_distance * 0.03f; // 右拓 5%
    //cout << " 右拓 5% " << endl;

    boxVolume.nearZ -= far_near_distance * 0.03f; // 近拓 5%
    //cout << " 近拓 5% " << endl;

    boxVolume.farZ += far_near_distance * 0.03f; // 远拓 5%
    //cout << " 远拓 5% " << endl;

    boxLenY = boxVolume.bottomY - boxVolume.topY;
    boxLenX = boxVolume.rightX - boxVolume.leftX;
    boxLenZ = boxVolume.farZ - boxVolume.nearZ;

    boxLenHalfX = boxLenX;
    boxLenHalfY = boxLenY;
    boxLenHalfZ = boxLenZ;
    return boxVolume;
}
void Bezier33Edge4::initBoxInfo(){
    glm::vec3 ltnSet = {boxVolume.leftX, boxVolume.topY, boxVolume.nearZ};
    glm::vec3 rtnSet = {boxVolume.rightX, boxVolume.topY, boxVolume.nearZ};
    glm::vec3 rbnSet = {boxVolume.rightX, boxVolume.bottomY, boxVolume.nearZ};
    glm::vec3 lbnSet = {boxVolume.leftX, boxVolume.bottomY, boxVolume.nearZ};


    glm::vec3 ltfSet = {boxVolume.leftX, boxVolume.topY, boxVolume.farZ};
    glm::vec3 rtfSet = {boxVolume.rightX, boxVolume.topY, boxVolume.farZ};
    glm::vec3 rbfSet = {boxVolume.rightX, boxVolume.bottomY, boxVolume.farZ};
    glm::vec3 lbfSet = {boxVolume.leftX, boxVolume.bottomY, boxVolume.farZ};

    setBox3D(ltnSet, rtnSet, rbnSet, lbnSet, ltfSet, rtfSet, rbfSet, lbfSet);
    scanBox3D_unchange.ltnSet = scanBox3D.ltnSet;
    scanBox3D_unchange.rtnSet = scanBox3D.rtnSet;
    scanBox3D_unchange.rbnSet = scanBox3D.rbnSet;
    scanBox3D_unchange.lbnSet = scanBox3D.lbnSet;

    scanBox3D_unchange.ltfSet = scanBox3D.ltfSet;
    scanBox3D_unchange.rtfSet = scanBox3D.rtfSet;
    scanBox3D_unchange.rbfSet = scanBox3D.rbfSet;
    scanBox3D_unchange.lbfSet = scanBox3D.lbfSet;

    scanBox3D_unchange.center = scanBox3D.center;

}
void Bezier33Edge4::initBox4Points() {
    // 初始化 mode2 轴系 mode4 世界系
    // 包围盒
    for(int outter=0;outter<box4Row; ++outter)
    for(int inner=0;inner<box4Col; ++inner)  // 4 点 一盒
        {
            // 4 点 一盒
            glm::vec3& p1 = Grid_unchange(outter,inner).first; // 0 0
            glm::vec3& p2 = Grid_unchange(outter,inner+1).first; // 0 1
            glm::vec3& p3 = Grid_unchange(outter+1,inner).first; // 1 0
            glm::vec3& p4 = Grid_unchange(outter+1,inner+1).first; // 1 1
            Box4Points tinyBoxNow = Box4Points(make_pair(p1,glm::ivec2{outter,inner}),
                                                make_pair(p2,glm::ivec2{outter,inner+1}),
                                                make_pair(p3,glm::ivec2{outter+1,inner}),
                                                make_pair(p4,glm::ivec2{outter+1,inner+1}),
                                                0.2f);
            box4Points(outter, inner) = tinyBoxNow;
        }

}

void Bezier33Edge4::drawBox4Points(ScreenDemo* screenEye) {

    float smallBoxColor[3] = {221.f/255.f,55.f/255.f,215.f/255.f};
    // int indexNow;
    for(int outter=0;outter<box4Row; ++outter)
    for(int inner=0;inner<box4Col; ++inner)  // 4 点 一盒
         {
        // indexNow = outter * box4Col + inner;
        glm::vec3& world_ltn = box4Points(outter, inner).cornersWorld[static_cast<int>(corner::ltn)];
        glm::vec3 screen_ltn{};
        glm::vec2 ltn2D = __3d2dGobezier(screenEye,world_ltn,&screen_ltn);
        glm::vec3& world_rtn = box4Points(outter, inner).cornersWorld[static_cast<int>(corner::rtn)];
        glm::vec3 screen_rtn{};
        glm::vec2 rtn2D = __3d2dGobezier(screenEye,world_rtn,&screen_rtn);
        glm::vec3& world_rbn = box4Points(outter, inner).cornersWorld[static_cast<int>(corner::rbn)];
        glm::vec3 screen_rbn{};
        glm::vec2 rbn2D = __3d2dGobezier(screenEye,world_rbn,&screen_rbn);
        glm::vec3& world_lbn = box4Points(outter, inner).cornersWorld[static_cast<int>(corner::lbn)];
        glm::vec3 screen_lbn{};
        glm::vec2 lbn2D = __3d2dGobezier(screenEye,world_lbn,&screen_lbn);
        glm::vec3& world_ltf = box4Points(outter, inner).cornersWorld[static_cast<int>(corner::ltf)];
        glm::vec3 screen_ltf{};
        glm::vec2 ltf2D = __3d2dGobezier(screenEye,world_ltf,&screen_ltf);
        glm::vec3& world_rtf = box4Points(outter, inner).cornersWorld[static_cast<int>(corner::rtf)];
        glm::vec3 screen_rtf{};
        glm::vec2 rtf2D = __3d2dGobezier(screenEye,world_rtf,&screen_rtf);
        glm::vec3& world_rbf = box4Points(outter, inner).cornersWorld[static_cast<int>(corner::rbf)];
        glm::vec3 screen_rbf{};
        glm::vec2 rbf2D = __3d2dGobezier(screenEye,world_rbf,&screen_rbf);
        glm::vec3& world_lbf = box4Points(outter, inner).cornersWorld[static_cast<int>(corner::lbf)];
        glm::vec3 screen_lbf{};
        glm::vec2 lbf2D = __3d2dGobezier(screenEye,world_lbf,&screen_lbf);

        // ltn rtn
        float deepNow = (screen_ltn.z + screen_rtn.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,ltn2D.x, ltn2D.y, rtn2D.x, rtn2D.y, smallBoxColor, deepNow);
        // rtn rbn
        deepNow = (screen_rtn.z + screen_rbn.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rtn2D.x, rtn2D.y, rbn2D.x, rbn2D.y, smallBoxColor, deepNow);
        // rbn lbn
        deepNow = (screen_rbn.z + screen_lbn.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rbn2D.x, rbn2D.y, lbn2D.x, lbn2D.y, smallBoxColor, deepNow);
        // lbn ltn
        deepNow = (screen_lbn.z + screen_ltn.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,lbn2D.x, lbn2D.y, ltn2D.x, ltn2D.y, smallBoxColor, deepNow);

        // ltf rtf
        deepNow = (screen_ltf.z + screen_rtf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,ltf2D.x, ltf2D.y, rtf2D.x, rtf2D.y, smallBoxColor, deepNow);
        // rtf rbf
        deepNow = (screen_rtf.z + screen_rbf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rtf2D.x, rtf2D.y, rbf2D.x, rbf2D.y, smallBoxColor, deepNow);
        // rbf lbf
        deepNow = (screen_rbf.z + screen_lbf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rbf2D.x, rbf2D.y, lbf2D.x, lbf2D.y, smallBoxColor, deepNow);
        // lbf ltf
        deepNow = (screen_lbf.z + screen_ltf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,lbf2D.x, lbf2D.y, ltf2D.x, ltf2D.y, smallBoxColor, deepNow);

        // ltn ltf
        deepNow = (screen_ltn.z + screen_ltf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,ltn2D.x, ltn2D.y, ltf2D.x, ltf2D.y, smallBoxColor, deepNow);
        // rtn rtf
        deepNow = (screen_rtn.z + screen_rtf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rtn2D.x, rtn2D.y, rtf2D.x, rtf2D.y, smallBoxColor, deepNow);
        // rbn rbf
        deepNow = (screen_rbn.z + screen_rbf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rbn2D.x, rbn2D.y, rbf2D.x, rbf2D.y, smallBoxColor, deepNow);
        // lbn lbf
        deepNow = (screen_lbn.z + screen_lbf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,lbn2D.x, lbn2D.y, lbf2D.x, lbf2D.y, smallBoxColor, deepNow);


    }

}

void Bezier33Edge4::freshBox4Display(AxisDemo* AxisTilt){


    // int indexNow;
    for(int outter = 0; outter < this-> box4Row; ++outter)
    for(int inner = 0; inner < this-> box4Col; ++inner)
        {
            // unchange 轴系 转 世界系

        this->box4Points(outter, inner).cornersWorld[static_cast<int>(corner::ltn)] =
AxisTilt->AxisTilt2world(this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::ltn)].x,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::ltn)].y,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::ltn)].z);

        this->box4Points(outter, inner).cornersWorld[static_cast<int>(corner::rtn)] =
AxisTilt->AxisTilt2world(this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rtn)].x,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rtn)].y,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rtn)].z);


        this->box4Points(outter, inner).cornersWorld[static_cast<int>(corner::rbn)] =
AxisTilt->AxisTilt2world(this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rbn)].x,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rbn)].y,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rbn)].z);

        this->box4Points(outter, inner).cornersWorld[static_cast<int>(corner::lbn)] =
AxisTilt->AxisTilt2world(this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::lbn)].x,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::lbn)].y,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::lbn)].z);

        this->box4Points(outter, inner).cornersWorld[static_cast<int>(corner::ltf)] =
AxisTilt->AxisTilt2world(this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::ltf)].x,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::ltf)].y,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::ltf)].z);

        this->box4Points(outter, inner).cornersWorld[static_cast<int>(corner::rtf)] =
AxisTilt->AxisTilt2world(this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rtf)].x,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rtf)].y,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rtf)].z);

        this->box4Points(outter, inner).cornersWorld[static_cast<int>(corner::rbf)] =
AxisTilt->AxisTilt2world(this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rbf)].x,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rbf)].y,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::rbf)].z);

        this->box4Points(outter, inner).cornersWorld[static_cast<int>(corner::lbf)] =
AxisTilt->AxisTilt2world(this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::lbf)].x,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::lbf)].y,
                        this->box4Points(outter, inner).corners_unchange[static_cast<int>(corner::lbf)].z);
        }
}
void Bezier33Edge4::freshBox9Display(AxisDemo* AxisTilt){

    // int indexNow;
    for(int outter = 0; outter < this-> box9Row; ++outter)
    for(int inner = 0; inner < this-> box9Col; ++inner)
         {

        this->box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::ltn)] =
AxisTilt->AxisTilt2world(this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::ltn)].x,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::ltn)].y,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::ltn)].z);

        this->box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::rtn)] =
AxisTilt->AxisTilt2world(this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rtn)].x,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rtn)].y,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rtn)].z);

        this->box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::rbn)] =
AxisTilt->AxisTilt2world(this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rbn)].x,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rbn)].y,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rbn)].z);

        this->box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::lbn)] =
AxisTilt->AxisTilt2world(this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::lbn)].x,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::lbn)].y,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::lbn)].z);

        this->box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::ltf)] =
AxisTilt->AxisTilt2world(this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::ltf)].x,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::ltf)].y,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::ltf)].z);

        this->box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::rtf)] =
AxisTilt->AxisTilt2world(this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rtf)].x,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rtf)].y,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rtf)].z);

        this->box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::rbf)] =
AxisTilt->AxisTilt2world(this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rbf)].x,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rbf)].y,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::rbf)].z);

        this->box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::lbf)] =
AxisTilt->AxisTilt2world(this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::lbf)].x,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::lbf)].y,
                        this->box9Cubes(outter, inner).corners_unchange[static_cast<int>(corner::lbf)].z);
        }
}
Matrix2D<Box4Points*>
Bezier33Edge4::getMidBoxExpand(this Bezier33Edge4 &self, int _outter, int _inner, int outterBoxFind, int innerBoxFind) {
    Matrix2D<Box4Points*> smallBoxes =
        Matrix2D<Box4Points*>(outterBoxFind,innerBoxFind); // 1based

    for(int outter=0;outter<outterBoxFind; ++outter) { // 0based
        for(int inner=0;inner<innerBoxFind; ++inner) { // 0based

            smallBoxes(outter, inner) = &self.box4Points(_outter*3+outter,_inner*3+inner);
                //glm::ivec2{midBoxRow*3+outter,midBoxCol*3+inner});
            //println("box4Points index outter:{},inner:{}",midBoxRow*3+outter,midBoxCol*3+inner);
        }//println();
    }//println("------------------------------------------");

    return smallBoxes;
}
void Bezier33Edge4::initBox9Cubes() {
    // println("--------init box 9 col:{},row:{}",box9Col,box9Row);
    int rowLast = box4Row % 3 ; // ∈ [0,2]
    int colLast = box4Col % 3 ; // ∈ [0,2]
    int outterBoxFind = 3, innerBoxFind = 3; // 1based


    for(int outter=0;outter<box9Row; ++outter) {
        if (outter==box9Row-1 && rowLast!=0) { // 整除不改
            outterBoxFind = rowLast; // 不回来了
        }
        for(int inner=0;inner<box9Col; ++inner){
            if (inner==box9Col-1 && colLast!=0) { // 整除不改
                innerBoxFind = colLast;
            }
            //println("-init box 9 outter:{},inner:{},col find:{},row find:{}",outter,inner,innerBoxFind,outterBoxFind);
            Matrix2D<Box4Points*>
                smallBoxes = getMidBoxExpand(outter,inner,outterBoxFind,innerBoxFind);
            // 二维 不存在 empty()

            Box9Cube midBox = Box9Cube(smallBoxes);
            box9Cubes(outter,inner) = midBox;
            if (inner==box9Col-1) {
                innerBoxFind = 3; // 还回来
            }
        }//println();
    }

}
void Bezier33Edge4::drawBox9Cubes(ScreenDemo* screenEye) {

    float smallBoxColor[3] = {20.f/255.f,146.f/255.f,64.f/255.f};//149240
    // int indexNow;
    for(int outter=0;outter<box9Row; ++outter)
    for(int inner=0;inner<box9Col; ++inner)  // 9 点 一盒
         {
        // indexNow = outter * this-> box9Col + inner;
        glm::vec3& world_ltn = box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::ltn)];
        glm::vec3 screen_ltn{};
        glm::vec2 ltn2D = __3d2dGobezier(screenEye,world_ltn,&screen_ltn);
        glm::vec3& world_rtn = box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::rtn)];
        glm::vec3 screen_rtn{};
        glm::vec2 rtn2D = __3d2dGobezier(screenEye,world_rtn,&screen_rtn);
        glm::vec3& world_rbn = box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::rbn)];
        glm::vec3 screen_rbn{};
        glm::vec2 rbn2D = __3d2dGobezier(screenEye,world_rbn,&screen_rbn);
        glm::vec3& world_lbn = box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::lbn)];
        glm::vec3 screen_lbn{};
        glm::vec2 lbn2D = __3d2dGobezier(screenEye,world_lbn,&screen_lbn);
        glm::vec3& world_ltf = box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::ltf)];
        glm::vec3 screen_ltf{};
        glm::vec2 ltf2D = __3d2dGobezier(screenEye,world_ltf,&screen_ltf);
        glm::vec3& world_rtf = box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::rtf)];
        glm::vec3 screen_rtf{};
        glm::vec2 rtf2D = __3d2dGobezier(screenEye,world_rtf,&screen_rtf);
        glm::vec3& world_rbf = box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::rbf)];
        glm::vec3 screen_rbf{};
        glm::vec2 rbf2D = __3d2dGobezier(screenEye,world_rbf,&screen_rbf);
        glm::vec3& world_lbf = box9Cubes(outter, inner).cornersWorld[static_cast<int>(corner::lbf)];
        glm::vec3 screen_lbf{};
        glm::vec2 lbf2D = __3d2dGobezier(screenEye,world_lbf,&screen_lbf);

        // ltn rtn
        float deepNow = (screen_ltn.z + screen_rtn.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,ltn2D.x, ltn2D.y, rtn2D.x, rtn2D.y, smallBoxColor, deepNow);
        // rtn rbn
        deepNow = (screen_rtn.z + screen_rbn.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rtn2D.x, rtn2D.y, rbn2D.x, rbn2D.y, smallBoxColor, deepNow);
        // rbn lbn
        deepNow = (screen_rbn.z + screen_lbn.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rbn2D.x, rbn2D.y, lbn2D.x, lbn2D.y, smallBoxColor, deepNow);
        // lbn ltn
        deepNow = (screen_lbn.z + screen_ltn.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,lbn2D.x, lbn2D.y, ltn2D.x, ltn2D.y, smallBoxColor, deepNow);

        // ltf rtf
        deepNow = (screen_ltf.z + screen_rtf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,ltf2D.x, ltf2D.y, rtf2D.x, rtf2D.y, smallBoxColor, deepNow);
        // rtf rbf
        deepNow = (screen_rtf.z + screen_rbf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rtf2D.x, rtf2D.y, rbf2D.x, rbf2D.y, smallBoxColor, deepNow);
        // rbf lbf
        deepNow = (screen_rbf.z + screen_lbf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rbf2D.x, rbf2D.y, lbf2D.x, lbf2D.y, smallBoxColor, deepNow);
        // lbf ltf
        deepNow = (screen_lbf.z + screen_ltf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,lbf2D.x, lbf2D.y, ltf2D.x, ltf2D.y, smallBoxColor, deepNow);

        // ltn ltf
        deepNow = (screen_ltn.z + screen_ltf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,ltn2D.x, ltn2D.y, ltf2D.x, ltf2D.y, smallBoxColor, deepNow);
        // rtn rtf
        deepNow = (screen_rtn.z + screen_rtf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rtn2D.x, rtn2D.y, rtf2D.x, rtf2D.y, smallBoxColor, deepNow);
        // rbn rbf
        deepNow = (screen_rbn.z + screen_rbf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,rbn2D.x, rbn2D.y, rbf2D.x, rbf2D.y, smallBoxColor, deepNow);
        // lbn lbf
        deepNow = (screen_lbn.z + screen_lbf.z) / 2.f;
        screenEye->line2ScreenBuffer(screenEye,lbn2D.x, lbn2D.y, lbf2D.x, lbf2D.y, smallBoxColor, deepNow);


    }
}
glm::vec3 Bezier33Edge4::screen2World(ScreenDemo* screenEye, glm::vec3& _src) {
    glm::vec3 tmp = screenEye->tblrXYZ.lt;
    tmp = screenEye->goX(tmp, _src.x);
    tmp = screenEye->goY(tmp, _src.y);
    tmp = screenEye->goDEEP(tmp, _src.z);
    return tmp;

}
// glm::vec3 Bezier33Edge4::world2AxisTilt(AxisDemo* AxisTilt, glm::vec3& _src) {
//     glm::vec3 tmp = AxisTilt->tilt_C_world_oxyz[0];
//     AxisTilt->startWorld_stepX(tmp, _src.x);
//     AxisTilt->startWorld_stepY(tmp, _src.y);
//     AxisTilt->startWorld_stepZ(tmp, _src.z);
//     return tmp;
// }


void Bezier33Edge4::shotOnBox_AxisTilt_4(Box4Points& box4Points,glm::vec3& startP_axisTilt, goLine32& rayDirUnit,
    pair<bool,float>* result) {

    // glm::vec3 &eye = this->startEye_axisTilt;
    glm::vec3 boxMin{}, boxMax{};
    // x
    boxMin.x = box4Points.corners_unchange[static_cast<int>(corner::ltn)].x;
    boxMax.x = box4Points.corners_unchange[static_cast<int>(corner::rtn)].x;
    boxMin.y = box4Points.corners_unchange[static_cast<int>(corner::ltn)].y;
    boxMax.y = box4Points.corners_unchange[static_cast<int>(corner::lbn)].y;
    boxMin.z = box4Points.corners_unchange[static_cast<int>(corner::ltn)].z;
    boxMax.z = box4Points.corners_unchange[static_cast<int>(corner::ltf)].z;

    float stepMin = numeric_limits<float>::lowest();
    float stepMax = numeric_limits<float>::max();

    float inv_dir, step1, step2, t_near, t_far;
    for(int xyzIndex=0; xyzIndex<3; ++xyzIndex) {
        inv_dir = 1.f / rayDirUnit._[xyzIndex]; // 应该不会 除0

        step1 = (boxMin[xyzIndex] - startP_axisTilt[xyzIndex]) * inv_dir;
        step2 = (boxMax[xyzIndex] - startP_axisTilt[xyzIndex]) * inv_dir;

        t_near = fminf(step1, step2); // 避免 NAN
        t_far = fmaxf(step1, step2);

        stepMin = fmaxf(stepMin, t_near);
        stepMax = fminf(stepMax, t_far);

        if (stepMin > stepMax) { // 倍 提速
            result->first = false;
            result->second = numeric_limits<float>::quiet_NaN();return;
        } // 直接排除 不相交

    }
    if (t_far >= 0.f) {
        result->first = true;
        result->second = t_near;return;
    }

    result->first = false;
    result->second = numeric_limits<float>::quiet_NaN();
}
void Bezier33Edge4::shotOnBox_AxisTilt_9(Box9Cube& box4Points,glm::vec3& startP_axisTilt, goLine32& rayDirUnit,
    pair<bool,float>* result) {

    // glm::vec3 &eye = this->startEye_axisTilt;
    glm::vec3 boxMin{}, boxMax{};
    // x
    boxMin.x = box4Points.corners_unchange[static_cast<int>(corner::ltn)].x;
    boxMax.x = box4Points.corners_unchange[static_cast<int>(corner::rtn)].x;
    boxMin.y = box4Points.corners_unchange[static_cast<int>(corner::ltn)].y;
    boxMax.y = box4Points.corners_unchange[static_cast<int>(corner::lbn)].y;
    boxMin.z = box4Points.corners_unchange[static_cast<int>(corner::ltn)].z;
    boxMax.z = box4Points.corners_unchange[static_cast<int>(corner::ltf)].z;

    float stepMin = numeric_limits<float>::lowest();
    float stepMax = numeric_limits<float>::max();

    float inv_dir, step1, step2, t_near, t_far;
    for(int xyzIndex=0; xyzIndex<3; ++xyzIndex) {
        inv_dir = 1.f / rayDirUnit._[xyzIndex]; // 应该不会 除0

        step1 = (boxMin[xyzIndex] - startP_axisTilt[xyzIndex]) * inv_dir;
        step2 = (boxMax[xyzIndex] - startP_axisTilt[xyzIndex]) * inv_dir;

        t_near = fminf(step1, step2); // 避免 NAN
        t_far = fmaxf(step1, step2);

        stepMin = fmaxf(stepMin, t_near);
        stepMax = fminf(stepMax, t_far);

        if (stepMin > stepMax) { // 倍 提速
            result->first = false;
            result->second = numeric_limits<float>::quiet_NaN();return;
        } // 直接排除 不相交

    }
    if (t_far >= 0.f) {
        result->first = true;
        result->second = t_near;return;
    }

    result->first = false;
    result->second = numeric_limits<float>::quiet_NaN();
}

void Bezier33Edge4::setBox3D(glm::vec3& _ltn, glm::vec3& _rtn, glm::vec3& _rbn, glm::vec3& _lbn,
                             glm::vec3& _ltf, glm::vec3& _rtf, glm::vec3& _rbf, glm::vec3& _lbf){
    scanBox3D.ltnSet = _ltn;
    scanBox3D.rtnSet = _rtn;
    scanBox3D.rbnSet = _rbn;
    scanBox3D.lbnSet = _lbn;

    scanBox3D.ltfSet = _ltf;
    scanBox3D.rtfSet = _rtf;
    scanBox3D.rbfSet = _rbf;
    scanBox3D.lbfSet = _lbf;

    freshGoX();freshGoY();freshGoZ();

    glm::vec3 centerThen = _ltn;
    goX(centerThen,boxLenHalfX);
    goY(centerThen,boxLenHalfY);
    goZ(centerThen,boxLenHalfZ);
    scanBox3D.center = centerThen;

//    cout << "### boxLenX:" << boxLenX << endl;
//    cout << "### boxLenY:" << boxLenY << endl;
//    cout << "### boxLenZ:" << boxLenZ << endl;

}
void Bezier33Edge4::setBox2D(glm::vec2& _ltn, glm::vec2& _rtn, glm::vec2& _rbn, glm::vec2& _lbn,
                             glm::vec2& _ltf, glm::vec2& _rtf, glm::vec2& _rbf, glm::vec2& _lbf,
                             glm::vec2& _center
){

    scanBox2D_.set13P(_ltn, _rtn, _rbn, _lbn,
                      _ltf, _rtf, _rbf, _lbf,
                      _center);

}

void Bezier33Edge4::freshGoX(){
//     DEBUG_SECTION(
//     float boxLenXCalc = glm::distance(scanBox3D.rtnSet, scanBox3D.ltnSet);
// if (abs(boxLenXCalc - boxLenX) > 1e-4f) {
// println(stderr,"贝塞尔334 boxLenXCalc:{} ≠ boxLenX:{}",boxLenXCalc,boxLenX);
// }
// )
    world_toX._ = (scanBox3D.rtnSet - scanBox3D.ltnSet) / boxLenX;
}
void Bezier33Edge4::freshGoY(){
//     DEBUG_SECTION(
//  float boxLenYCalc = glm::distance(scanBox3D.lbnSet, scanBox3D.ltnSet);
// if (abs(boxLenYCalc - boxLenY) > 1e-4f) {
// println(stderr,"贝塞尔334 boxLenYCalc:{} ≠ boxLenY:{}",boxLenYCalc,boxLenY);
// }
// )
    world_toY._ = (scanBox3D.lbnSet - scanBox3D.ltnSet) / boxLenY;
}
void Bezier33Edge4::freshGoZ() {
//     DEBUG_SECTION(
// float boxLenZCalc = glm::distance(scanBox3D.ltfSet, scanBox3D.ltnSet);
// if (abs(boxLenZCalc - boxLenZ) > 1e-4f) {
// println(stderr,"贝塞尔334 boxLenZCalc:{} ≠ boxLenZ:{}",boxLenZCalc,boxLenZ);
// }
// )
    world_toZ._ = (scanBox3D.ltfSet - scanBox3D.ltnSet) / boxLenZ;
}
void Bezier33Edge4::goX(glm::vec3& _srcXYZ, float _move){
    _srcXYZ = _srcXYZ + _move * world_toX._;
}
void Bezier33Edge4::goY(glm::vec3& _srcXYZ, float _move){
    _srcXYZ = _srcXYZ + _move * world_toY._;
}
void Bezier33Edge4::goZ(glm::vec3& _srcXYZ, float _move){
    _srcXYZ = _srcXYZ + _move * world_toZ._;
}

void Bezier33Edge4::solidRectangle2D_(ScreenDemo* ScreenEye,AxisDemo* AxisTilt){
    scanBox2D_.setLineBounary(lineScanFillColor_);

    if(lineScanFillColor_.empty())return;
    //int rowLast = static_cast<int>(lineScanFillColor_.size()) + lineScanFillColor_[0].y;

//    pixelSurfaceInfo_.clear();
//-    bool firstOut = true;
    if(renderNext == 1){
        if (fastIteration) {
            if (startRowIndex_ == 0) { // 首行
            // 首行 边四边面
            for(int i=0;i<rect2Flats_Top.size(); ++i) {
                rect2Flats_Top[i].clacAddPixelsInfo(this,virtual_P,&pixelSurfaceInfo__);

            }
            for(int j=0;j<N_u-1; ++j) { // 中间行 首行
                rect2Flats(0, j).clacAddPixelsInfo(this,virtual_P,&pixelSurfaceInfo__);

            }
            startRowIndex_++;
            }
            else if (startRowIndex_ < N_v - 1) { // 中间行
                int i = startRowIndex_;

                for(int j=0;j<N_u-1; ++j) {
                    rect2Flats(i, j).clacAddPixelsInfo(this,virtual_P,&pixelSurfaceInfo__);

                }

                rect2Flats_Left[i].clacAddPixelsInfo(this,virtual_P,&pixelSurfaceInfo__);

                rect2Flats_Right[i].clacAddPixelsInfo(this,virtual_P,&pixelSurfaceInfo__);

                startRowIndex_++;
            }
            // 正常 四边面
            else if (startRowIndex_ == N_v) { // 末行
                for(int i=0;i<rect2Flats_Bottom.size(); ++i) {
                    rect2Flats_Left[i].clacAddPixelsInfo(this,virtual_P,&pixelSurfaceInfo__);

                }
                startRowIndex_++;
            }
            for(pixelDeep23_& _lineDeepInfo : pixelSurfaceInfo__) {

                float* colorNow = getColorByUV(_lineDeepInfo.uv);

                if(colorNow != nullptr){
                    if(_lineDeepInfo.faceToCamera){
                        ScreenEye->putPixel(_lineDeepInfo.xy[0],_lineDeepInfo.xy[1],
                                            colorNow,_lineDeepInfo.screenDeep,this);
                    }else{
                        ScreenEye->putPixel(_lineDeepInfo.xy[0],_lineDeepInfo.xy[1],
                                            backColor,_lineDeepInfo.screenDeep,this);
                    }

                }

            }
        }
        else {
            backRenderRow:
            if(startRowIndex_ < lineScanFillColor_.size()){
                lineBoundary _linePosInfo = lineScanFillColor_[startRowIndex_];
                rowPixelDeep23 rowDeepInfo;

    //-            if(meshWidth==3 || !allPoints_sameDir) {
    //-                if (firstOut) {
                //cout << "front row: " << _linePosInfo.y << " / " << rowLast << "\n";
    //-                    firstOut = false;
    //-                } else {
    //-                    // 一行一行
    //-                    cout << "front row: " << _linePosInfo.y << " / " << rowLast << "\n";
    //-                    cout << "\033[A\033[k"; // 上移一行 并清空
    //-                }
    //-            }
                if (_linePosInfo.rx == _linePosInfo.lx) {
                    // 屏幕外的行 左右x相同

                    startRowIndex_++;
                    goto backRenderRow;
                }
                rowDeepInfo.y = (float) _linePosInfo.y; // 本行 y

                for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; ++nowX){
                    // 列 nowX

                    // uv

                    goLine32 sightDir = ScreenDemo::get_AgoB_direction3D(startEye,{nowX,rowDeepInfo.y,0.f});

                    std::expected<curveSurfaceInfo,char> _info;
                    if(surfaceTimes == 4){
                        _info = rayIntersectBezier3(ScreenEye,AxisTilt,
                            sightDir,{nowX,rowDeepInfo.y}, virtual_P);
                    }

    //                 else if(surfaceTimes == 3){
    // //                    _info = rayIntersectBezier2_(startEye, sightDir, virtual_P);
    //                     _info = rayIntersectBezier2(startEye, sightDir._, virtual_P);
    //                 }else if(surfaceTimes == 5){
    //                     _info = rayIntersectBezier4(startEye, sightDir._, virtual_P);
    //                 }

                    // 屏垂距
                    if (_info) {
                       rowDeepInfo.pixelDeeps.emplace_back(pixelDeep23{nowX,_info->uv,
                        _info->virtual_Pos.z,_info->faceToCamera}); // 本行 x deep
                    }else {
                        rowDeepInfo.pixelDeeps.emplace_back(std::unexpected(0));
                    }


                }
                pixelSurfaceInfo_.emplace_back(rowDeepInfo);
                startRowIndex_++;
            }
            // 列 循环

            for(auto& _lineDeepInfo : pixelSurfaceInfo_) {
                size_t vecSizeCurrent=_lineDeepInfo.pixelDeeps.size();
                for(int i = 0; i < vecSizeCurrent; ++i) {
                    if (!_lineDeepInfo.pixelDeeps[i])continue;
                    int nowX = _lineDeepInfo.pixelDeeps[i]->x;
                    float nowDeep = _lineDeepInfo.pixelDeeps[i]->screenDeep;

                    glm::vec2 nowUV = _lineDeepInfo.pixelDeeps[i]->uv;
                    // if(isnan(nowUV[0]) || isnan(nowUV[1]))continue;
                    bool faceFront = _lineDeepInfo.pixelDeeps[i]->faceToCamera;

                    float* colorNow = getColorByUV(nowUV);

                    if(colorNow != nullptr){
                        if(faceFront){
                            ScreenEye->putPixel(nowX,static_cast<int>(_lineDeepInfo.y),
                                                colorNow,nowDeep,this);
                        }else{
                            ScreenEye->putPixel(nowX,static_cast<int>(_lineDeepInfo.y),
                                                backColor,nowDeep,this);
                        }

                    }


                }

            }

        }

    }

    else {

        freshVirtualCloudsFrontBack(); // 预刷新 400点 正反朝向
        // 动态 前帧
        // 赋予 屏幕系 四点
        for(int i=0;i<N_v-1; ++i) {
            for(int j=0;j<N_u-1; ++j) {
                rect2Flats(i, j).freshTriangle(ScreenEye,virtual_Grid(i,j),virtual_Grid(i,j+1),
                    virtual_Grid(i+1,j),virtual_Grid(i+1,j+1));
                if ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) {
                    rect2Flats(i, j).draw2Triangle(ScreenEye,colorP,backColor,this);
                }else {
                    rect2Flats(i, j).draw2Triangle(ScreenEye,colorGrid,backColor,this);
                }
            }

        }
        if (!settledColorGrid70) {
            colorGrid_70[0] = colorGrid[0]*0.7f;
            colorGrid_70[1] = colorGrid[1]*0.7f;
            colorGrid_70[2] = colorGrid[2]*0.7f;
            settledColorGrid70 = false;
        }
        if (fastIteration || showEdgeRect) {
            for(int i=0;i<rect2Flats_Top.size(); ++i) {
            rect2Flats_Top[i].freshTriangle(ScreenEye,virtual_Grid_edgeTop[i],virtual_Grid_edgeTop[i+1],
            virtual_Grid(0,i),virtual_Grid(0,i+1));
            if (showEdgeRect) {
                    if (i % 2 == 0 ) {
#ifdef showEdgeRectVertical
                    rect2Flats_Top[i].draw2Triangle_(ScreenEye,colorP_70,colorP_70,verticalColor,this);
#else
                    rect2Flats_Top[i].draw2Triangle(ScreenEye,colorP_70,colorP_70,this);
#endif
                    }else {
#ifdef showEdgeRectVertical
                        rect2Flats_Top[i].draw2Triangle_(ScreenEye,colorGrid_70,colorGrid_70,verticalColor,this);
#else
                        rect2Flats_Top[i].draw2Triangle(ScreenEye,colorGrid_70,colorGrid_70,this);
#endif
                    }
                }

            }
            for(int i=0;i<rect2Flats_Bottom.size(); ++i) {
                rect2Flats_Bottom[i].freshTriangle(ScreenEye,virtual_Grid_edgeBottom[i],virtual_Grid_edgeBottom[i+1],
                virtual_Grid(N_v-1,i),virtual_Grid(N_v-1,i+1));
                if (showEdgeRect) {
                    if ((i % 2 != 0 && N_v % 2 != 0) || (i % 2 == 0 && N_v % 2 == 0)) {
#ifdef showEdgeRectVertical
                        rect2Flats_Bottom[i].draw2Triangle_(ScreenEye,colorP_70,colorP_70,verticalColor,this);
#else
                        rect2Flats_Bottom[i].draw2Triangle(ScreenEye,colorP_70,colorP_70,this);
#endif
                    }else {
#ifdef showEdgeRectVertical
                        rect2Flats_Bottom[i].draw2Triangle_(ScreenEye,colorGrid_70,colorGrid_70,verticalColor,this);
#else
                        rect2Flats_Bottom[i].draw2Triangle(ScreenEye,colorGrid_70,colorGrid_70,this);
#endif
                    }
                }

            }
            for(int i=0;i<rect2Flats_Left.size(); ++i) {
                rect2Flats_Left[i].freshTriangle(ScreenEye,virtual_Grid_edgeLeft[i],virtual_Grid_edgeLeft[i+1],
                virtual_Grid(i,0),virtual_Grid(i+1,0));
                if (showEdgeRect) {
                    if ((i % 2 != 0 && N_u % 2 != 0) || (i % 2 == 0 && N_u % 2 == 0)) {
#ifdef showEdgeRectVertical
                        rect2Flats_Left[i].draw2Triangle_(ScreenEye,colorP_70,colorP_70,verticalColor,this);
#else
                        rect2Flats_Left[i].draw2Triangle(ScreenEye,colorP_70,colorP_70,this);
#endif
                    }else {
#ifdef showEdgeRectVertical
                        rect2Flats_Left[i].draw2Triangle_(ScreenEye,colorGrid_70,colorGrid_70,verticalColor,this);
#else
                        rect2Flats_Left[i].draw2Triangle(ScreenEye,colorGrid_70,colorGrid_70,this);
#endif
                    }
                }

            }
            for(int i=0;i<rect2Flats_Right.size(); ++i) {
                rect2Flats_Right[i].freshTriangle(ScreenEye,virtual_Grid_edgeRight[i],virtual_Grid_edgeRight[i+1],
                virtual_Grid(i,N_u-1),virtual_Grid(i+1,N_u-1));
                if (showEdgeRect) {
                    if ((i % 2 != 0 && N_u % 2 != 0) || (i % 2 == 0 && N_u % 2 == 0)) {
#ifdef showEdgeRectVertical
                        rect2Flats_Right[i].draw2Triangle_(ScreenEye,colorP_70,colorP_70,verticalColor,this);
#else
                        rect2Flats_Right[i].draw2Triangle(ScreenEye,colorP_70,colorP_70,this);
#endif
                    }else {
#ifdef showEdgeRectVertical
                        rect2Flats_Right[i].draw2Triangle_(ScreenEye,colorGrid_70,colorGrid_70,verticalColor,this);
#else
                        rect2Flats_Right[i].draw2Triangle(ScreenEye,colorGrid_70,colorGrid_70,this);
#endif
                    }
                }

            }
        }



    }

}
void Bezier33Edge4::freshVirtualCloudsFrontBack() {

    for (cloudInfo& _cloud : virtual_Grid.data) {
        _cloud.freshOnFront(startEye);
        // cout << "stary eye: " << startEye.x << " " << startEye.y << " " << startEye.z << endl;
        // cout << "~~cloud on front: " << _cloud.onFront << endl;
    }

    if (fastIteration || showEdgeRect) {
        for (cloudInfo& _cloud : virtual_Grid_edgeTop) {
        _cloud.freshOnFront(startEye);
        }
        for (cloudInfo& _cloud : virtual_Grid_edgeBottom) {
            _cloud.freshOnFront(startEye);
        }
        for (cloudInfo& _cloud : virtual_Grid_edgeLeft) {
            _cloud.freshOnFront(startEye);
        }
        for (cloudInfo& _cloud : virtual_Grid_edgeRight) {
            _cloud.freshOnFront(startEye);
        }
    }


}

void Bezier33Edge4::setColor(int color1, int color2){
    BGR3f color_1;
    color_1.setBGR(color1,1);
    colorP[0] = color_1.r1;
    colorP[1] = color_1.g1;
    colorP[2] = color_1.b1;
    BGR3f color_2;
    color_2.setBGR(color2,1);
    colorGrid[0] = color_2.r1;
    colorGrid[1] = color_2.g1;
    colorGrid[2] = color_2.b1;

    colorP_70[0] = colorP[0]*0.7f; // 预存储 节约计算
    colorP_70[1] = colorP[1]*0.7f;
    colorP_70[2] = colorP[2]*0.7f;
    colorGrid_70[0] = colorGrid[0]*0.7f;
    colorGrid_70[0] = colorGrid[1]*0.7f;
    colorGrid_70[0] = colorGrid[2]*0.7f;

}
float* Bezier33Edge4::getColorByUV(glm::vec2& uv){
    // if(uv.x < 0.f || uv.x > 1.f || uv.y < 0.f || uv.y > 1.f){
    //     return nullptr;
    // }
    // if(isnan(uv.x) || isnan(uv.y))return nullptr;

    bool colEven = (int)roundf(uv[0]*(float)N_u) % 2 == 0;//偶数
    bool rowEven = (int)roundf(uv[1]*(float)N_v) % 2 == 0;
    if(rowEven && !colEven || !rowEven && colEven){
        return colorP;
    }
    return colorGrid;

}
void Bezier33Edge4::set_P_XYZ(glm::vec3 _P[5][5]){
    for(int i=0;i<5; ++i){
        for(int j=0;j<5; ++j){
            P[i][j] = _P[i][j];
        }
    }
}

void Bezier33Edge4::moveFreshStatus(){


    renderNext = 0;

    startRowIndex_=0;
    if (fastIteration) {

        pixelSurfaceInfo__.clear();
    }
    else

        pixelSurfaceInfo_.clear();

}

void Bezier33Edge4::switchDebug(AxisDemo* AxisTilt){
    // 0 1 2
    if(debugMode==0)debugMode=1;
    else if(debugMode==1) {
        freshBox4Display(AxisTilt);
        debugMode=2;
    }
    else if(debugMode==2) {
        freshBox9Display(AxisTilt);
        debugMode=3;
    }
    else if (debugMode==3) {
        freshBox4Display(AxisTilt);
        freshBox9Display(AxisTilt);
        debugMode=4;
    }
    else debugMode=0;
}
void Bezier33Edge4::Draw_Tick(ScreenDemo* ScreenEye, AxisDemo* AxisTilt){

    float eyeBackZ = ScreenEye->rectDepth - 100.f;
    int mesh_1;
    // if (!renderNext){
    //     showGrid = 1; // 显示网格
    // }else{
    //     showGrid = 0; // 不显示
    // }
    if (showGrid)goto showGridOnly;

    solidRectangle2D_(ScreenEye, AxisTilt); // 反面

    screenAxis2axisTilt(ScreenEye, AxisTilt,&startEye,&startEye_axisTilt); // 更新视角

    float _color_[3];

    if(debugMode == 1){
        _color_[0] = 1.0f;
        _color_[1] = 1.0f;
        _color_[2] = 1.0f; // 白色
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.ltn.x, scanBox2D_.ltn.y,
                                      scanBox2D_.rtn.x, scanBox2D_.rtn.y,
                                      _color_, virtual_scanBox3D.center.z);// 前框
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rtn.x, scanBox2D_.rtn.y,
                                      scanBox2D_.rbn.x, scanBox2D_.rbn.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rbn.x, scanBox2D_.rbn.y,
                                      scanBox2D_.lbn.x, scanBox2D_.lbn.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.lbn.x, scanBox2D_.lbn.y,
                                      scanBox2D_.ltn.x, scanBox2D_.ltn.y,
                                      _color_, virtual_scanBox3D.center.z);

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.ltf.x, scanBox2D_.ltf.y,
                                      scanBox2D_.rtf.x, scanBox2D_.rtf.y,
                                      _color_, virtual_scanBox3D.center.z);// 后框
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rtf.x, scanBox2D_.rtf.y,
                                      scanBox2D_.rbf.x, scanBox2D_.rbf.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rbf.x, scanBox2D_.rbf.y,
                                      scanBox2D_.lbf.x, scanBox2D_.lbf.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.lbf.x, scanBox2D_.lbf.y,
                                      scanBox2D_.ltf.x, scanBox2D_.ltf.y,
                                      _color_, virtual_scanBox3D.center.z);

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.ltn.x, scanBox2D_.ltn.y,
                                      scanBox2D_.ltf.x, scanBox2D_.ltf.y,
                                      _color_, virtual_scanBox3D.center.z);// 前后连
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rtn.x, scanBox2D_.rtn.y,
                                      scanBox2D_.rtf.x, scanBox2D_.rtf.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rbn.x, scanBox2D_.rbn.y,
                                      scanBox2D_.rbf.x, scanBox2D_.rbf.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.lbn.x, scanBox2D_.lbn.y,
                                      scanBox2D_.lbf.x, scanBox2D_.lbf.y,
                                      _color_, virtual_scanBox3D.center.z);

    }
    else if (debugMode == 2) {
        drawBox4Points(ScreenEye); // 画立方体

    }else if (debugMode == 3) {
        drawBox9Cubes(ScreenEye);
    }else if (debugMode == 4) {
        drawBox4Points(ScreenEye); // 画立方体
        drawBox9Cubes(ScreenEye);
    }



    float zDeepNow;



    mesh_1 = surfaceTimes - 1; // 保存原值
    if(showP){
        // P横画

        for(int i=0;i<surfaceTimes; ++i) {
            for(int j = 0; j < mesh_1; ++j) {
                zDeepNow = (virtual_P[i][j].z + virtual_P[i][j + 1].z) / 2.f;

                if(zDeepNow + eyeBackZ > 0.f){
                    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                                  P2D[i][j].x, P2D[i][j].y,
                                                  P2D[i][j + 1].x, P2D[i][j + 1].y,
                                                  colorP, zDeepNow);
                }

            }
        }


        // P竖画
        for(int j=0;j<mesh_1; ++j) {
            for(int i = 0; i < surfaceTimes; ++i) {
                zDeepNow = (virtual_P[j][i].z + virtual_P[j + 1][i].z) / 2.f;

                if(zDeepNow + eyeBackZ > 0.f){
                    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                                  P2D[j][i].x, P2D[j][i].y,
                                                  P2D[j + 1][i].x, P2D[j + 1][i].y,
                                                  colorP, zDeepNow);
                }

            }
        }

    }

    if(0){
        showGridOnly:

        // 网格画 横
        for(int outter=0; outter < N_v; ++outter){ // 15条 横线
            for(int inner=0; inner < N_u - 1; ++inner){ // 一条横线 15段
                zDeepNow = (virtual_Grid(outter,inner).pos.z + virtual_Grid(outter,inner + 1).pos.z) / 2.f;
                if(zDeepNow + eyeBackZ > 0.f){
                    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                                  Grid2D(outter,inner).first.x,Grid2D(outter,inner).first.y,
                                                  Grid2D(outter,inner+1).first.x,Grid2D(outter,inner+1).first.y,
                                                  colorGrid,zDeepNow);
                    // println("xy:{},\n xy:{}",
                    //     showVec2(Grid2D(outter,inner).first),showVec2(Grid2D(outter,inner+1).first));
                }

            }
        }
        // 网格画 竖
        for(int inner=0; inner < N_u ; ++inner){ // 一条竖线 15段
            for(int outter=0; outter < N_v- 1; ++outter){ // 15条竖线

                zDeepNow = (virtual_Grid(outter,inner).pos.z + virtual_Grid(outter+1,inner).pos.z) / 2.f;
                if(zDeepNow + eyeBackZ > 0.f){
                    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                                  Grid2D(outter,inner).first.x,Grid2D(outter,inner).first.y,
                                                  Grid2D(outter+1,inner).first.x,Grid2D(outter+1,inner).first.y,
                                                  colorGrid,zDeepNow);
                }

            }
        }
        goto showGridAfter;
    }
    if (showVerticals) {
        for(int i=0; i < N_u; ++i) {
            // 15条竖线
            for(int j=0; j < N_v - 1; ++j){ // 一条竖线 15段
                zDeepNow = (virtual_Grid(j,i).pos.z + virtual_Grid(j,i).verticalP.z) / 2.f;
                if(zDeepNow + eyeBackZ > 0.f) {
                    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                                          Grid2D(j,i).first.x,Grid2D(j,i).first.y,
                                                          Grid2D(j,i).second.x,Grid2D(j,i).second.y,
                                                          verticalColor,zDeepNow);
                }
            }
        }
    }

    showGridAfter:
    renderNext = 1; // 看又 移动了 ?

}

std::array<double, 9> Bezier33Edge4::coeffientForU(
        glm::vec3& eye,
        goLine32& dir,
        glm::vec3 p[5][5]
) {
    // 之前错了 哎~~~
    throw runtime_error("函数没写出来!!!");
    return {0,0,0,0,0,0,0,0,0};
}
array<complex<double>, 8> Bezier33Edge4::solveOctic_(
    complex<double> A, complex<double> B, complex<double> C,
    complex<double> D, complex<double> E, complex<double> F,
    complex<double> G, complex<double> H, complex<double> I) {
    // 检查A是否为0
    if (A.real() == 0 && A.imag() == 0){
        println(stderr, "Coefficient A: ({},{}) cannot be zero",A.real(),A.imag());
        A = {1e-10};
    }
    // 归一化为monic多项式 x^8 + b x^7 + ... + i
    complex<double> b(B / A), c(C / A), d(D / A), e(E / A), f(F / A);
    complex<double> g(G / A), h(H / A), i(I / A);

    Eigen::MatrixXcd companion(8, 8); // 矩阵改为8x8

    // 归一化后方程：x⁸ + b x⁷ + ... + i = 0
    companion <<
        0, 0, 0, 0, 0, 0, 0, -i,
        1, 0, 0, 0, 0, 0, 0, -h,
        0, 1, 0, 0, 0, 0, 0, -g,
        0, 0, 1, 0, 0, 0, 0, -f,
        0, 0, 0, 1, 0, 0, 0, -e,
        0, 0, 0, 0, 1, 0, 0, -d,
        0, 0, 0, 0, 0, 1, 0, -c,
        0, 0, 0, 0, 0, 0, 1, -b;
    // 返回array大小改为8
    // 计算特征值
    Eigen::ComplexEigenSolver<Eigen::MatrixXcd> solver;
    solver.compute(companion);

    if (solver.info() != Eigen::Success)
        throw runtime_error("Failed to compute eigenvalues");

    Eigen::VectorXcd roots = solver.eigenvalues();
    array<complex<double>, 8> result = { roots[0], roots[1], roots[2], roots[3],
                                       roots[4], roots[5], roots[6], roots[7] };
    return result;
}
// 辅助函数：计算 f(u,v)=0 关于 v 的系数
array<float,3> Bezier33Edge4::coeffientForV(float u, glm::vec3& eye, goLine32& dir, glm::vec3 p[5][5]
) {
    // 计算 S(u,v) 在 u=u 处的系数 A(u), B(u), C(u)
//    float Bu[3] = {(1-u)*(1-u), 2*u*(1-u), u*u};
//
//    glm::vec3 A(0), B(0), C(0);
//    for(int i = 0; i < 3; ++i) {
//        A += Bu[i] * p[i][0];
//        B += Bu[i] * p[i][1];
//        C += Bu[i] * p[i][2];
//    }
//    B *= 2; // B(u) 对应的是 v 的一次项系数
//
//    // f(u,v) = (S_y - eye_y)*dir_z - (S_z - eye_z)*dir_y = 0
//    // 展开后是关于 v 的二次方程
//    float a = (B.y * dir.dz - C.z * dir.dy);
//    float b = (A.y * dir.dz - C.z * dir.dy) + (B.y * dir.dz - B.z * dir.dy);
//    float c = (A.y - eye.y) * dir.dz - (A.z - eye.z) * dir.dy;
    float Bu[3] = {(1-u)*(1-u), 2*u*(1-u), u*u};
    glm::vec3 A(0), B(0), C(0);
    for(int i = 0; i < 3; ++i) {
        A += Bu[i] * p[i][0];
        B += Bu[i] * p[i][1];
        C += Bu[i] * p[i][2];
    }
    B *= 2; // B(u) 对应的是 v 的一次项系数

    // 修正：使用正确的系数公式
    float a = (C.y * dir.dz - C.z * dir.dy);
    float b = (B.y * dir.dz - B.z * dir.dy);
    float c = (A.y - eye.y) * dir.dz - (A.z - eye.z) * dir.dy;
    return {a,b,c};
}
array<double,2> Bezier33Edge4::getVbyCoeffient(double a, double b, double c) {
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        println(stderr,"贝塞尔2 u不得v");
        return { numeric_limits<double>::quiet_NaN(),
            numeric_limits<double>::quiet_NaN() };
    }
    double sqrt_d = sqrt(discriminant);
    double v1 = (-b + sqrt_d) / (2 * a);
    double v2 = (-b - sqrt_d) / (2 * a);
    return {v1,v2};

}
// 计算固定u时，使曲面点距离视线最近的三次方程系数
// 返回 std::array<double, 4> = [a, b, c, d] 对应方程: a*v^3 + b*v^2 + c*v + d = 0
std::array<double, 4> Bezier33Edge4::coeffientForV_(
        float u, glm::vec3& eye, goLine32& dir, glm::vec3 p[5][5] ) {
    // 1. 计算u对应的伯恩斯坦基函数
    float Bu[3] = {(1 - u) * (1 - u), 2 * u * (1 - u), u * u};

    // 2. 计算A(u), B(u), C(u) - 双二次贝塞尔曲面
    glm::vec3 A(0), B(0), C(0);
    for(int i = 0; i < 3; ++i) {
        A += Bu[i] * p[i][2];  // j=2 (v^2项)
        B += Bu[i] * p[i][1];  // j=1 (v^1项)
        C += Bu[i] * p[i][0];  // j=0 (v^0项)
    }
    B *= 2;  // B(u) 对应v的一次项系数（双二次曲面特性）

    // 3. 构造方向向量 (x, y, z)
    glm::vec3 dir_vec(dir._);

    // 4. 计算X = A(u) × dir, Y = B(u) × dir, Z = (C(u) - eye) × dir
    glm::vec3 X = glm::cross(A, dir_vec);
    glm::vec3 Y = glm::cross(B, dir_vec);
    glm::vec3 Z = glm::cross(C - eye, dir_vec);

    // 5. 计算点积
    double XX = glm::dot(X, X);
    double XY = glm::dot(X, Y);
    double XZ = glm::dot(X, Z);
    double YY = glm::dot(Y, Y);
    double YZ = glm::dot(Y, Z);

    // 6. 计算三次方程系数 (4*XX, 6*XY, 2*(XZ+YY), 2*YZ)
    std::array<double, 4> coefficients = {
            4.0 * XX,
            6.0 * XY,
            2.0 * (XZ + YY),
            2.0 * YZ
    };

    return coefficients;
}
array<complex<double>, 3> Bezier33Edge4::solveCubic(double _a, double _b, double _c, double _d) {
    complex<double> a = {_a,0.0}, b = {_b, 0.0}, c = {_c, 0.0}, d = {_d, 0.0};

    complex<double> p = (3.0 * a * c - b * b) / (3.0 * a * a);
    complex<double> q = (2.0 * b * b * b - 9.0 * a * b * c + 27.0 * a * a * d) / (27.0 * a * a * a);
    complex<double> w = { -0.5, sqrt(3.0) / 2.0 };

    // 计算立方根并保证 uv 关系
    complex<double> sqrt_disc = std::sqrt(q * q / 4.0 + p * p * p / 27.0);
    complex<double> u = pow(-q / 2.0 + sqrt_disc, 1.0 / 3.0);
    complex<double> v = -p / (3.0 * u);  // 关键修正点

    complex<double> root1 = (u + v) - b / (3.0 * a);
    complex<double> root2 = (w * u + w * w * v) - b / (3.0 * a);
    complex<double> root3 = (w * w * u + w * v) - b / (3.0 * a);
return {root1, root2, root3};
}
vector<double> Bezier33Edge4::getVbyCoeffient_(double a, double b, double c, double _d) {
    array<complex<double>, 3> roots = solveCubic(a, b, c, _d);
    vector<double> v_all;
    for (auto& root : roots) {
        if (abs(root.imag()) < 1e-3 && root.real() >= 0 && root.real() <= 1) {
            v_all.emplace_back(root.real());
        }
    }
    return v_all;
}
goLine32 Bezier33Edge4::computeNormal(float u, float v, glm::vec3 p[5][5]) {
    // 计算基函数及其导数
    float Bu[3]   = {(1-u)*(1-u),     2*u*(1-u),     u*u};
    float Bv[3]   = {(1-v)*(1-v),     2*v*(1-v),     v*v};
    float dBu[3]  = {-2*(1-u),        2*(1-2*u),     2*u};
    float dBv[3]  = {-2*(1-v),        2*(1-2*v),     2*v};

    glm::vec3 dS_du(0.0f), dS_dv(0.0f);

    // 计算 ∂S/∂u
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            dS_du += dBu[i] * Bv[j] * p[i][j];
            dS_dv += Bu[i] * dBv[j] * p[i][j];
        }
    }

    // 法线 = ∂S/∂u × ∂S/∂v
    goLine32 normal = glm::cross(dS_du, dS_dv);

    // 归一化
    if (glm::length(normal._) > 1e-6f) {
        normal._ = glm::normalize(normal._);
    }else {
        throw runtime_error("Normal is zero!");
    }

    return normal;
}
bool Bezier33Edge4::isFrontFacing(goLine32& normal, goLine32& viewDir) {
    // viewDir 是从交点指向摄像机的方向（即 -dir）
    // 或者直接用 -dir（如果 dir 是从摄像机出发的）
    float dot = glm::dot(normal._, -viewDir._);
    return dot > 0.0f; // 正面朝向
}
bool Bezier33Edge4::getFrontFacing(float u, float v, glm::vec3& surfaceP, glm::vec3 p[5][5]){
    // 3. 计算法线
    goLine32 normal = computeNormal(u, v, p);

    // 4. 判断是否正面朝向
    bool isFront = PolygonBase::isFrontFacing(startEye,normal,surfaceP);
        //isFrontFacing(normal, viewDir); // dir 是从 eye 出发的方向
    return isFront;
}
float Bezier33Edge4::distanceToRay(glm::vec3& eye, goLine32& rayDir, glm::vec3& roundP) {

    glm::vec3 eyeGoP = roundP - eye;
    float proj = glm::dot(eyeGoP, rayDir._); // 投影长度
    // proj > 0
    glm::vec3 projPoint = eye + rayDir._ * proj;
    return glm::length(roundP - projPoint);

    // 点到直线
    // float distance = glm::length(glm::cross(roundP - eye, dir._));
}

curveSurfaceInfo Bezier33Edge4::rayIntersectBezier2_(glm::vec3& _startEye,
    goLine32& sightLine, glm::vec3 P[5][5]){
    array<double,9> coefficients_u = coeffientForU(_startEye, sightLine,virtual_P);
    array<complex<double>, 9> coefficients_u_complex = {
        complex<double>(coefficients_u[0], 0),
        complex<double>(coefficients_u[1], 0),
        complex<double>(coefficients_u[2], 0),
        complex<double>(coefficients_u[3], 0),
        complex<double>(coefficients_u[4], 0),
        complex<double>(coefficients_u[5], 0),
        complex<double>(coefficients_u[6], 0),
        complex<double>(coefficients_u[7], 0),
        complex<double>(coefficients_u[8], 0)
    };

        array<complex<double>, 8> u_all8 = solveOctic_(coefficients_u_complex[0], coefficients_u_complex[1],
            coefficients_u_complex[2], coefficients_u_complex[3], coefficients_u_complex[4],
            coefficients_u_complex[5], coefficients_u_complex[6], coefficients_u_complex[7],
            coefficients_u_complex[8]);
    vector<double> correctU;
    for (auto& u : u_all8) {
        // 实数 0~1 筛u
        if (abs(u.imag()) < 1e-3 && u.real() >= 0 && u.real() <= 1) {
            correctU.emplace_back(u.real());
        }

    }
    vector<array<float,6>> correctUV; // u v step x y z ~~
	array<float, 3> coeffient_V;
    array<double, 2> v_all2;
 //   array<double, 4> coeffient_V;
	//vector<double> v_all3;
    glm::vec2 uv;
    glm::vec3 posScreenAxis;
    for (auto& u : correctU) {
		//coeffient_V = coeffientForV_(u, _startEye, sightLine, virtual_P);
  //      v_all3 = getVbyCoeffient_(coeffient_V[0], coeffient_V[1], coeffient_V[2], coeffient_V[3]);

  //      for(auto& v : v_all3) { // 1u解(0~3)v  误差内接收
  //          uv = { u, (float)v };
  //          posScreenAxis = evaluatePatch2(uv[0], uv[1], virtual_P);
  //          float nowStep = glm::distance(posScreenAxis, _startEye); // 符合条件 都算距离, 最后取最近
  //          glm::vec3 rayPos = _startEye + sightLine._ * nowStep;

  //          float stepErr = glm::distance(posScreenAxis, rayPos);//distanceToRay(_startEye, sightLine, posScreenAxis);
		//	bool sameRay = stepErr < 1.0f;
  //          if (sameRay) {
  //              ;
  //              correctUV.push_back({ uv[0],uv[1],nowStep,posScreenAxis.x,posScreenAxis.y,posScreenAxis.z });
  //          }
  //          else {
  //                         println("start eye: {},{},{}, sightLine: {},{},{}",
  //                             _startEye.x, _startEye.y, _startEye.z,
  //                             sightLine.dx, sightLine.dy, sightLine.dz);
  //                         println("pos: {},{},{}", posScreenAxis.x, posScreenAxis.y, posScreenAxis.z);
  //                         cout << "u: " <<u<<" → v: "<<v<<
  //                             "\nerr: "<< stepErr <<
  //                             "视线偏离" << endl;
  //          }
		//}
        coeffient_V = coeffientForV(u, _startEye, sightLine, virtual_P);
        v_all2 = getVbyCoeffient(coeffient_V[0], coeffient_V[1], coeffient_V[2]);
        // 二次是实根

		// v ∈ [0,1] 筛v
        if(!isnan(v_all2[0]) && v_all2[0] >= 0 && v_all2[0] <= 1){
            uv = {u, (float)v_all2[0]};
            posScreenAxis = evaluatePatch2(uv[0], uv[1], virtual_P);
            float stepErr = distanceToRay(_startEye, sightLine, posScreenAxis);
            bool sameRay = stepErr < 1.0f;


            if (sameRay) {

                float nowStep = glm::distance(posScreenAxis, _startEye);
                glm::vec3 rayPos = _startEye + sightLine._ * nowStep;

                correctUV.push_back({ uv[0],uv[1],nowStep,posScreenAxis.x,posScreenAxis.y,posScreenAxis.z });
            }

            else {
        /*       println("start eye: {},{},{}, sightLine: {},{},{}",
                    _startEye.x, _startEye.y, _startEye.z,
                    sightLine.dx, sightLine.dy, sightLine.dz);
                println("pos: {},{},{}", posScreenAxis.x, posScreenAxis.y, posScreenAxis.z);
                cout << "u: " <<u<<" → v: "<<v_all2[0]<<
                    "\nerr: "<< stepErr <<
                    "视线偏离0" << endl;*/
            }
		}
        if (!isnan(v_all2[1]) && v_all2[1] >= 0 && v_all2[1] <= 1) {
            uv = {u, (float)v_all2[1]};
            posScreenAxis = evaluatePatch2(uv[0], uv[1], virtual_P);
            float stepErr = distanceToRay(_startEye, sightLine, posScreenAxis);
            bool sameRay = stepErr < 1.0f;


            if (sameRay) {
                float nowStep = glm::distance(posScreenAxis, _startEye);
                glm::vec3 rayPos = _startEye + sightLine._ * nowStep;

                correctUV.push_back({ uv[0],uv[1],nowStep,posScreenAxis.x,posScreenAxis.y,posScreenAxis.z });
            }

            else {
                println(stderr,"start eye: {},{},{}, sightLine: {},{},{}",
                    _startEye.x, _startEye.y, _startEye.z,
                    sightLine.dx, sightLine.dy, sightLine.dz);
                println(stderr,"pos: {},{},{}", posScreenAxis.x, posScreenAxis.y, posScreenAxis.z);
                println(stderr,"u: " , u , " → v: " , v_all2[0] ,
                    "\nerr: ", stepErr,  "视线偏离1");

            }
        }


    }
    vector<curveSurfaceInfo> candidate;
    curveSurfaceInfo res;

    float rayLen = -1,lenNow;
    if (correctUV.empty()) {
        // 本视线 无 合适uv
        res.uv = glm::vec2(std::numeric_limits<float>::quiet_NaN());
        res.virtual_Pos = glm::vec3(std::numeric_limits<float>::quiet_NaN());
        res.sightLineLen = std::numeric_limits<float>::quiet_NaN();
        res.faceToCamera = false;
        return res;
    }
    if(correctUV.size() == 1) {
        // 本视线 唯一 合适 uv
        res.uv[0] = correctUV[0][0]; res.uv[1] = correctUV[0][1];
        res.virtual_Pos = { correctUV[0][3],correctUV[0][4],correctUV[0][5] };

        res.sightLineLen = correctUV[0][2];
        res.faceToCamera = getFrontFacing(res.uv[0], res.uv[1], res.virtual_Pos, virtual_P);
        return res;
    }

    int rightIndex = 0;
    for(int i = 0; i < correctUV.size(); ++i) {
        posScreenAxis = { correctUV[i][3],correctUV[i][4],correctUV[i][5] };

        if (rayLen == -1) {
            lenNow = correctUV[i][2];
            rayLen = lenNow;
        }
        else {
            lenNow = correctUV[i][2];
            if (lenNow < rayLen) {
                rayLen = lenNow;
                rightIndex = i;
            }
        }
        candidate.push_back({ {correctUV[i][0],correctUV[i][1] }, posScreenAxis, lenNow, false }); // 先不管正反面

    }// 多少个 correctUV 就多少个 candidate
	assert(candidate.size() == correctUV.size());
    res.uv = candidate[rightIndex].uv;
    res.virtual_Pos = candidate[rightIndex].virtual_Pos;
    res.sightLineLen = candidate[rightIndex].sightLineLen;
    res.faceToCamera = getFrontFacing(res.uv[0], res.uv[0], res.virtual_Pos, virtual_P); // 定下了 算正反朝

   return res;
}

constexpr float EPSILON = 1e-6f;
const int MAX_ITERATIONS = 10;//20 次数少了 缺陷瑕疵!!
const int NUM_SAMPLES = 2;//15 写个1 也能算~~

glm::vec3 Bezier33Edge4::evaluatePatch2(float u, float v, const glm::vec3 P[5][5]) {
    float Bu[3], Bv[3];

    float iu = 1.0f - u;
    Bu[0] = iu * iu;          // (1-t)^2
    Bu[1] = 2.0f * u * iu;    // 2t(1-t)
    Bu[2] = u * u;            // t^2

    float iv = 1.0f - v;
    Bv[0] = iv * iv;          // (1-t)^2
    Bv[1] = 2.0f * v * iv;    // 2t(1-t)
    Bv[2] = v * v;            // t^2


    glm::vec3 point(0);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            point += Bu[i] * Bv[j] * P[i][j];
        }
    }
    return point;
}
void Bezier33Edge4::computeBezierBasis2(float t, float B[3], float dB[3]) {
    float it = 1.0f - t;
    B[0] = it * it;          // (1-t)^2
    B[1] = 2.0f * t * it;    // 2t(1-t)
    B[2] = t * t;            // t^2

    dB[0] = -2.0f * it;      // 导数 d/dt
    dB[1] = 2.0f - 4.0f * t;
    dB[2] = 2.0f * t;
}
void Bezier33Edge4::surfaceDerivatives2(float u, float v, glm::vec3 P[5][5],
                        glm::vec3& S, glm::vec3& Su, glm::vec3& Sv)
{
    float Bu[3], Bv[3], dBu[3], dBv[3];
    computeBezierBasis2(u, Bu, dBu);
    computeBezierBasis2(v, Bv, dBv);

    S = Su = Sv = {0,0,0};

    // 改为3x3循环
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            float basis = Bu[i] * Bv[j];
            S += basis * P[i][j];

            Su += dBu[i] * (Bv[j] * P[i][j]);
            Sv += Bu[i] * (dBv[j] * P[i][j]);
        }
    }
}
curveSurfaceInfo Bezier33Edge4::rayIntersectBezier2(glm::vec3& _startEye, glm::vec3& sightLine, glm::vec3 P[5][5]) {
    std::vector<curveSurfaceInfo> solutions;
    curveSurfaceInfo result = {};

    float u, v;
    for (int i = 0; i <= NUM_SAMPLES; ++i) {
        u = i / (float)NUM_SAMPLES; // 1/15 ~ 15/15
        for (int j = 0; j <= NUM_SAMPLES; ++j) {
            v = j / (float)NUM_SAMPLES; // 1/15 ~ 15/15
            float t = 0.0f;

            glm::vec3 S, Su, Sv;
            for (int iter = 0; iter < MAX_ITERATIONS; ++iter) {
                surfaceDerivatives2(u, v, P, S, Su, Sv);

                float F[3] = {
                        S.x - (_startEye.x + t * sightLine.x),
                        S.y - (_startEye.y + t * sightLine.y),
                        S.z - (_startEye.z + t * sightLine.z)
                };

                if (fabs(F[0]) < EPSILON &&
                    fabs(F[1]) < EPSILON &&
                    fabs(F[2]) < EPSILON) break;

                float J[3][3] = {
                        {Su.x, Sv.x, -sightLine.x},
                        {Su.y, Sv.y, -sightLine.y},
                        {Su.z, Sv.z, -sightLine.z}
                };

                float delta[3];
                if (!solve3x3(J, F, delta)) break;

                u -= delta[0];
                v -= delta[1];
                t -= delta[2];
            } // 内三层循环后 处理solution扩容数组

            if (/*u >= -EPSILON && u <= 1.0f+EPSILON &&
                v >= -EPSILON && v <= 1.0f+EPSILON &&
                t > -EPSILON*/
                u >= 0 && u <= 1.0f &&
                v >= 0 && v <= 1.0f &&
                t > 0.f)
            {
//                u = std::clamp(u, 0.0f, 1.0f);
//                v = std::clamp(v, 0.0f, 1.0f);

                bool exists = false; // 结果去重
                for (auto& infoNow : solutions) {
                    if (fabs(infoNow.uv[0] - u) < 1e-4f &&
                        fabs(infoNow.uv[1] - v) < 1e-4f) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    // 计算表面点后立即进行法线计算
                    glm::vec3 surfacePoint_final = evaluatePatch2(u, v, P);

                    // 重新计算精确的导数（考虑clamp后的uv）
                    glm::vec3 S_clamped, Su_clamped, Sv_clamped;
                    surfaceDerivatives2(u, v, P, S_clamped, Su_clamped, Sv_clamped);
                    // 计算法线（叉乘前先归一化）
                    goLine32 normal = glm::normalize(glm::cross(Su_clamped, Sv_clamped));
                    // 计算视线方向（从表面点到相机的方向）
                    glm::vec3 viewDir = glm::normalize(_startEye - surfacePoint_final);
                    // 背面剔除判断（点积小于等于0为背面）
                    bool faceFront = true;
                    if(PolygonBase::isFrontFacing(startEye,normal,surfacePoint_final)) {
                        faceFront = false;
                    }

                    float rayNotSameAngle = PolygonBase::angleBetweenVectors_deg(-viewDir, sightLine); // 排除 不一致视线 夹角差
                    bool sameRay = rayNotSameAngle < 0.02f;
                    if (!sameRay)continue; // 不在视线内

                    glm::vec3 rayVec = surfacePoint_final - _startEye;

                    if(sameRay){

                        float sightLen_final = glm::dot(rayVec, sightLine);//(rayVec.x*sightLine.x + rayVec.y*sightLine.y + rayVec.z*sightLine.z);
                        if (sightLen_final > 0.f) {
    //                        return {glm::vec2{u, v}, surfacePoint_final, sightLen_final};
                            solutions.push_back({glm::vec2{u, v},surfacePoint_final,sightLen_final,faceFront});
                        }
                        // 视线长 step
                        // step² = 视线立方x² + 视线立方y² + 视线立方z²
                        // step² = 视线立方x*dx*step + 视线立方y*dy*step + 视线立方z*dz*step
                        // step = 视线立方x*dx + 视线立方y*dy + 视线立方z*dz
                    }
                }
            }
        }
    }
    size_t solutionCount = solutions.size();
    if (solutionCount == 1){
        result.uv = solutions[0].uv;
        result.virtual_Pos = solutions[0].virtual_Pos;
        result.sightLineLen = solutions[0].sightLineLen;
        result.faceToCamera = solutions[0].faceToCamera;
        return result;
    }
    if (solutionCount == 0){
        result.uv = glm::vec2(std::numeric_limits<float>::quiet_NaN());
        result.virtual_Pos = glm::vec3(std::numeric_limits<float>::quiet_NaN());
        result.sightLineLen = std::numeric_limits<float>::quiet_NaN();
        result.faceToCamera = false;
        return result;
    }

    float minT = solutions[0].sightLineLen;
    int index = 0;
    // 最小步长 那个解
    for(int i=0;i<solutionCount; ++i){
        if(solutions[i].sightLineLen<minT){
            minT = solutions[i].sightLineLen;
            index = i;

        }
    }

    return solutions[index];


}
// const float EPSILON = 1e-7f;
std::expected<glm::vec3,char> Bezier33Edge4::RayTriangleIntersect(const glm::vec3& startEye, const glm::vec3& rayDir,
                          const glm::vec3& pa, const glm::vec3& pb, const glm::vec3& pc) {

    glm::vec3 pointOnFlat;

    glm::vec3 edge1 = pb - pa;
    glm::vec3 edge2 = pc - pa;
    glm::vec3 pvec = cross(rayDir, edge2);

    float det = glm::dot(edge1, pvec);

    // 当行列式接近0时，视为光线与三角形平行
    if (det > -EPSILON && det < EPSILON)
        return std::unexpected(0);

    float inv_det = 1.0f / det;

    glm::vec3 tvec = startEye - pa;
    float u = dot(tvec, pvec) * inv_det;

    // u超出[0,1]范围时无交点
    if (u < 0.0f || u > 1.0f)
        return std::unexpected(0);

    glm::vec3 qvec = cross(tvec, edge1);
    float v = dot(rayDir, qvec) * inv_det;

    // v超出[0,1]或u+v超过1时无交点
    if (v < 0.0f || u + v > 1.0f)
        return std::unexpected(0);

    float t = dot(edge2, qvec) * inv_det;


    // t必须为正表示在光线方向上的交点
    if (t > EPSILON) {
        // 计算交点位置：使用重心坐标公式
        pointOnFlat = pa + u * edge1 + v * edge2;
        return pointOnFlat;
    }


    return std::unexpected(0);
}
glm::vec2 Bezier33Edge4::getNearestTipUV_byFlatPoint(const glm::vec3& flatPoint,
    Rect2Flat& rect2Flat, unsigned char triangleIndex) {
    // float step, step_up, step_down;
    // float a, b, c, d;

    glm::vec2 uv;
    if (triangleIndex == 0) {
        // lt


        glm::vec3 p1 = rect2Flat.virtual_ltrt_rblb[0].pos; // 0 1 3
        glm::vec3 p2 = rect2Flat.virtual_ltrt_rblb[1].pos;
        glm::vec3 p3 = rect2Flat.virtual_ltrt_rblb[3].pos;

        float pTo1_22 = (flatPoint.x - p1.x)*(flatPoint.x - p1.x) + (flatPoint.y - p1.y)*(flatPoint.y - p1.y)
            + (flatPoint.z - p1.z)*(flatPoint.z - p1.z);
        float pTo2_22 = (flatPoint.x - p2.x)*(flatPoint.x - p2.x) + (flatPoint.y - p2.y)*(flatPoint.y - p2.y)
        + (flatPoint.z - p2.z)*(flatPoint.z - p2.z);
        float pTo3_22 = (flatPoint.x - p3.x)*(flatPoint.x - p3.x) + (flatPoint.y - p3.y)*(flatPoint.y - p3.y)
        + (flatPoint.z - p3.z)*(flatPoint.z - p3.z);
        unsigned char minIndex_ = rect2Flat.minIndex(pTo1_22, pTo2_22, pTo3_22);
        if (minIndex_ == 2)minIndex_ = 3; // 修正

        uv = rect2Flat.virtual_ltrt_rblb[minIndex_].uv;
    }else if (triangleIndex == 1) {
        // rb


        glm::vec3 p1 = rect2Flat.virtual_ltrt_rblb[1].pos; // 1 2 3
        glm::vec3 p2 = rect2Flat.virtual_ltrt_rblb[2].pos;
        glm::vec3 p3 = rect2Flat.virtual_ltrt_rblb[3].pos;

        glm::vec3 _1ToP = glm::vec3(flatPoint.x - p1.x);
        float pTo1_22 = glm::dot(_1ToP,_1ToP);
        glm::vec3 _2ToP = glm::vec3(flatPoint.x - p2.x);
        float pTo2_22 = glm::dot(_2ToP,_2ToP);
        glm::vec3 _3ToP = glm::vec3(flatPoint.x - p3.x);
        float pTo3_22 = glm::dot(_3ToP,_3ToP);
        unsigned char minIndex_ = rect2Flat.minIndex(pTo1_22, pTo2_22, pTo3_22);
        minIndex_ += 1; // 修正

        uv = rect2Flat.virtual_ltrt_rblb[minIndex_].uv;
    }else {
        throw runtime_error("index not 0 or 1!");
    }
    return uv;
}
vector<glm::vec2> Bezier33Edge4::generateCandidateVUs_3(const glm::vec3& startEye, const glm::vec3& rayDir) {
    // 遍历所有三角面
    // 射中三角面
    // 最近顶点
    // 获得初始uv (为了牛顿迭代)
    std::expected<glm::vec3,char> TriangleLT_in,TriangleRB_in;
    vector<glm::vec2> vuResult;
    glm::vec2 nowUV, nowVU;

    for (Rect2Flat& rectNow : rect2Flats.data) {
        TriangleLT_in = RayTriangleIntersect(startEye,rayDir,
            rectNow.virtual_ltrt_rblb[0].pos,rectNow.virtual_ltrt_rblb[1].pos,
            rectNow.virtual_ltrt_rblb[3].pos);

        TriangleRB_in = RayTriangleIntersect(startEye,rayDir,
            rectNow.virtual_ltrt_rblb[1].pos,rectNow.virtual_ltrt_rblb[2].pos,
            rectNow.virtual_ltrt_rblb[3].pos);

        if (TriangleLT_in) {
            nowUV = getNearestTipUV_byFlatPoint(*TriangleLT_in,rectNow,0);
            nowVU[0] = nowUV[1];nowVU[1] = nowUV[0];
            vuResult.emplace_back(nowVU);
        }else if (TriangleRB_in) {
            nowUV = getNearestTipUV_byFlatPoint(*TriangleRB_in,rectNow,1);
            nowVU[0] = nowUV[1];nowVU[1] = nowUV[0];
            vuResult.emplace_back(nowVU);
        }
    }

    return vuResult;
}
vector<glm::vec2> Bezier33Edge4::generateCandidateVUs_2(glm::vec3& _startEye, glm::vec3& rayDir_norm) {
    vector<pair<glm::vec2, float>> vuResult;
    vector<glm::vec2> candidatesFiltered;

    const float deltaU = 1.0f/(N_u-1);
    const float deltaV = 1.0f/(N_v-1);
    glm::vec3 cloudNow{}, toPoint{}, getCrossed{};
    float distance_22;
    // array<float,4>& rowFlatData = ScreenEye->rowFlatData[pos2D.y]; // 引用 类型
    // array<float,4>& colFlatData = ScreenEye->colFlatData[pos2D.x];


    for(int v_step = 0; v_step < N_v; ++v_step) {
        for(int u_step = 0; u_step < N_u; ++u_step) {
            cloudNow = virtual_Grid(v_step,u_step).pos;
            toPoint = cloudNow - _startEye;
            getCrossed = glm::cross(toPoint, rayDir_norm);
            distance_22 = getCrossed.x*getCrossed.x + getCrossed.y*getCrossed.y + getCrossed.z*getCrossed.z;
            if (distance_22 > rayRadius_22) continue; // 视线过远


            vuResult.push_back({{v_step*deltaV, u_step*deltaU}, distance_22});

        }
    }
    if (vuResult.size() < 8) {
        for (pair<glm::vec2, float>& vu : vuResult) {
            candidatesFiltered.push_back(vu.first);
        }
    }else {
        // 到视线的距离 平方最近
        nth_element(vuResult.begin(), vuResult.begin() + 7, vuResult.end(),
        [](const pair<glm::vec2, float>& a, const pair<glm::vec2, float>& b) {
        return a.second < b.second;
    });
        for(int i = 0; i < 8; ++i) {
            candidatesFiltered.push_back(vuResult[i].first);
        }
    }

    return candidatesFiltered;
}
void Bezier33Edge4::screenAxis2axisTilt(ScreenDemo* ScreenEye, AxisDemo *AxisTilt,glm::vec3*const src, glm::vec3*const dst) {
    // ScreenDemo::freshFrameRotateInfo()
    *dst = screen2World(ScreenEye, *src);
    if (mode_.now == mode_.b) {
        // void AxisDemo::freshStartWorld_GoDir()
        *dst = AxisTilt->world2AxisTilt(*dst);
    }

}
void Bezier33Edge4::getCandidatesVU_bySelfBox(glm::vec3& startPos_axisTilt, goLine32& rayDir_axisTilt,
    vector<glm::vec2>& candidates) {

    // glm::vec3 transferPos;
    // screenAxis2axisTilt(ScreenEye, AxisTilt, &screenPos, &transferPos);
    //
    //
    // goLine32 rayUnit_axisTilt = glm::normalize(transferPos - startEye_axisTilt);
    pair<bool,float> shotBox_distance;
    glm::vec2 nowUV,nowVU;

    // vector<glm::vec2> res3; // 点线 最近 前7
    //cout << "--------------------\n";
    vector<Box4Points*> currentBox4Points; // 中盒 找小盒

    for(int outter = 0;outter < box9Row; ++outter) {
        for(int inner = 0;inner < box9Col; ++inner) {
            // indexNow = outter * this-> box9Col + inner;
             shotOnBox_AxisTilt_9(box9Cubes(outter, inner), startPos_axisTilt,rayDir_axisTilt,
                 &shotBox_distance);//shotOnBox_AxisTilt_9(box9Cubes[indexNow], rayUnit_axisTilt);
            if (!shotBox_distance.first) continue;
            //midBoxGot++;
            for (Box4Points* smallBox : box9Cubes(outter, inner).box4_P) {
                currentBox4Points.push_back(smallBox);
            }
        }
    }
    vector<int> singleIndexHave;int singleIndex;
    for (Box4Points* tinyBox : currentBox4Points) { // 小盒 找云索引

        shotOnBox_AxisTilt_4(*tinyBox, startPos_axisTilt,rayDir_axisTilt,&shotBox_distance);

        if (!shotBox_distance.first) continue;

        class std::random_device rd;  // 获取一个随机数，作为种子
        std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数
        // 定义一个均匀分布的范围
        class std::uniform_int_distribution<> distr(0,3);
        int randomIndex = distr(gen);
        nowUV = virtual_Grid(tinyBox->cloudsIndex[randomIndex].x,tinyBox->cloudsIndex[randomIndex].y).uv ; // u 列 v 行
        nowVU[0] = nowUV[1];
        nowVU[1] = nowUV[0];

        singleIndex = tinyBox->cloudsIndex[randomIndex].x * virtual_Grid.innerMax + tinyBox->cloudsIndex[randomIndex].y;

        if (!isIn(singleIndexHave,singleIndex)) {
            // 没有 一维索引 加进去
            singleIndexHave.push_back(singleIndex);
            candidates.emplace_back(nowVU);
        }//else println(stderr," bezier33 重复的 一维索引 !!!");

        randomIndex = randomIndex == 3 ? 2 : randomIndex + 1;
        nowUV = virtual_Grid(tinyBox->cloudsIndex[randomIndex].x,tinyBox->cloudsIndex[randomIndex].y).uv ; // u 列 v 行
        nowVU[0] = nowUV[1];
        nowVU[1] = nowUV[0];

        singleIndex = tinyBox->cloudsIndex[randomIndex].x * virtual_Grid.innerMax + tinyBox->cloudsIndex[randomIndex].y;

        if (!isIn(singleIndexHave,singleIndex)) {
            // 没有 一维索引 加进去
            singleIndexHave.push_back(singleIndex);
            candidates.emplace_back(nowVU);
        }//else println(stderr," bezier33 重复的 一维索引 !!!");

    }

}
glm::vec3 Bezier33Edge4::evaluatePatch3(float u, float v, const glm::vec3 P[5][5]) {
    float Bu[4] = {
            (1-u)*(1-u)*(1-u),
            3*u*(1-u)*(1-u),
            3*u*u*(1-u),
            u*u*u
    };
    float Bv[4] = {
            (1-v)*(1-v)*(1-v),
            3*v*(1-v)*(1-v),
            3*v*v*(1-v),
            v*v*v
    };

    glm::vec3 point = {0, 0, 0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float weight = Bu[i] * Bv[j];
            point.x += weight * P[i][j].x;
            point.y += weight * P[i][j].y;
            point.z += weight * P[i][j].z;
        }
    }
    return point;
}

void computeBezierBasis3(float t, float B[4], float dB[4]){

    float t2 = t * t;
    float t3 = t2 * t;
    float it = 1.0f - t;
    float it2 = it * it;
    float it3 = it2 * it;

    B[0] = it3;
    B[1] = 3.0f * t * it2;
    B[2] = 3.0f * t2 * it;
    B[3] = t3;

    dB[0] = -3.0f * it2;
    dB[1] = 3.0f * it2 - 6.0f * t * it;
    dB[2] = 6.0f * t * it - 3.0f * t2;
    dB[3] = 3.0f * t2;

}

void Bezier33Edge4::surfaceDerivatives3(float u, float v, const glm::vec3 P[5][5],
                         glm::vec3* S, glm::vec3* Su, glm::vec3* Sv) {
    float Bu[4], Bv[4], dBu[4], dBv[4];
    computeBezierBasis3(u, Bu, dBu);
    computeBezierBasis3(v, Bv, dBv);

    *S = *Su = *Sv = {0,0,0};

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            float basis = Bu[i] * Bv[j];
            S->x += basis * P[i][j].x;
            S->y += basis * P[i][j].y;
            S->z += basis * P[i][j].z;

            Su->x += dBu[i] * Bv[j] * P[i][j].x;
            Su->y += dBu[i] * Bv[j] * P[i][j].y;
            Su->z += dBu[i] * Bv[j] * P[i][j].z;

            Sv->x += Bu[i] * dBv[j] * P[i][j].x;
            Sv->y += Bu[i] * dBv[j] * P[i][j].y;
            Sv->z += Bu[i] * dBv[j] * P[i][j].z;
        }
    }
}

// bool BicubicBezier::solve3x3(const float J[3][3], const float F[3], float delta[3])


std::expected<curveSurfaceInfo,char>
Bezier33Edge4::rayIntersectBezier3(ScreenDemo* ScreenEye,AxisDemo *AxisTilt, goLine32& rayDir,
             glm::ivec2 pos2D,glm::vec3 _P_[5][5]) {
    std::vector<curveSurfaceInfo> solutions;
    std::expected<curveSurfaceInfo,char> result;


    glm::vec3 screenPos_axisTilt, screenPos{pos2D.x, pos2D.y,0.f};
    // 屏幕系 转到 斜彩轴
    screenAxis2axisTilt(ScreenEye, AxisTilt, &screenPos, &screenPos_axisTilt);
    goLine32 rayUnit_axisTilt = glm::normalize(screenPos_axisTilt - startEye_axisTilt);


    // 斜彩轴 起始点 步进向量
    vector<glm::vec2> vuCandidates;
    getCandidatesVU_bySelfBox(startEye_axisTilt,rayUnit_axisTilt,vuCandidates);
        //generateCandidateVUs_2(_startEye, rayDir);


    //cout << "---vuCandidates: " << vuCandidates.size() << endl; // ###

    if (vuCandidates.size() == 0) {
        return std::unexpected(0);
    }
        //cout << "---vuCandidates: " << vuCandidates.size() << endl;


    float u, v;
    glm::vec3 S, Su, Sv;
    glm::vec3 F;
    size_t vuCandidates_size = vuCandidates.size();
    for(size_t i = 0; i < vuCandidates_size; ++i) {

//            cout << "uvCandidates: " << uvCandidates.size() << endl;
        v = vuCandidates[i][0];
        u = vuCandidates[i][1];

        float t = 0.0f;


            // 增加曲率自适应迭代（关键改进点）
        // float prevError = numeric_limits<float>::max();
        bool isCandidateInvalid = false;
        for (int iter = 0;/*MAX_ITERATIONS*/; ++iter) {
            surfaceDerivatives3(u, v, _P_, &S, &Su, &Sv);

            F = S - (this->startEye + t * rayDir._);

            if (fabs(F[0]) < EPSILON &&
                fabs(F[1]) < EPSILON &&
                fabs(F[2]) < EPSILON)
                break;

            float J[3][3] = { // 影响迭代 关键
                    {Su.x, Sv.x, -rayDir.dx},
                    {Su.y, Sv.y, -rayDir.dy},
                    {Su.z, Sv.z, -rayDir.dz}
            };

            float delta[3];
            if (!solve3x3_(J, F, delta)) break;

            // 动态调整步长
                float currentError = glm::length(glm::vec3(F[0], F[1], F[2]));
                // if(currentError > prevError * 0.9f) {
                //     delta[0] *= 0.5f; // 误差未明显下降时减小步长
                //     delta[1] *= 0.5f;
                //     delta[2] *= 0.5f;
                // }
                // prevError = currentError;
            if (currentError < 0.01f) {
                //println("iter: {}", iter); // 近20次 才结束
                break; // 出结果
            }
            if (iter == 10) {
                isCandidateInvalid = true; // 标记候选点无效
                break; // 跳出内循环（无需再迭代） // 迭代次数超限
            }
            // ...更新uv...
            u -= delta[0];
            v -= delta[1];
            t -= delta[2];

        } // -------- 内三层循环后 处理solution扩容数组


        // 3. 关键：内循环跳出后，先判断标志位
        if (isCandidateInvalid) {
            continue;
        }

            if (u >= 0 && u <= 1.0f &&
                    v >= 0 && v <= 1.0f &&
                    t > 0.f) {
                //                    u = std::clamp(u, 0.0f, 1.0f);
                //                    v = std::clamp(v, 0.0f, 1.0f);

                bool exists = // 结果去重 候选点过多
                    std::find_if(solutions.begin(), solutions.end(),
                        [u,v](const curveSurfaceInfo& src)->bool {
                            return fabs(src.uv[0] - u) < 1e-4f && fabs(src.uv[1] - v) < 1e-4f;
                        }
                        ) != solutions.end();
                // for (auto &infoNow: solutions) {
                //     if (fabs(infoNow.uv[0] - u) < 1e-4f &&
                //         fabs(infoNow.uv[1] - v) < 1e-4f) {
                //         exists = true;
                //         break;
                //     }
                // }
                if (exists) {
                    // println("牛顿迭代 重复了");
                    continue; // 结果去重
                }
                    // println("牛顿迭代 没重复");


                // 计算表面点后立即进行法线计算

                // 计算视线方向（从表面点到相机的方向）
                // goLine32 nearlyViewDir = glm::normalize(this->startEye - surfacePoint_final);
                // float rayNotSameAngle = PolygonBase::angleBetweenVectors(-nearlyViewDir._, rayDir._); // 排除 不一致视线 夹角差
                // bool sameRay = rayNotSameAngle < 0.02f;
                // if (!sameRay)continue; // 不在视线内


                // ax+by+cz+d=0 (=点的垂线距离*-1)  <视线垂面 交于点云>
//                    float d = -sightLine.x*surfacePoint_final.x
//                            - sightLine.y*surfacePoint_final.y
//                            - sightLine.z*surfacePoint_final.z;
//                    float eye2flatLen = -sightLine.x*_startEye.x - sightLine.y*_startEye.y
//                            - sightLine.z*_startEye.z - d; // 垂直距离 不需要 再除以 dot(平面法线归一,斜射线步进归一)
//                    float p2eyeLen_2_ = (surfacePoint_final.x-_startEye.x)*(surfacePoint_final.x-_startEye.x)
//                            + (surfacePoint_final.y-_startEye.y)*(surfacePoint_final.y-_startEye.y)
//                            + (surfacePoint_final.z-_startEye.z)*(surfacePoint_final.z-_startEye.z);
//                    float p2rayLen = p2eyeLen_2_ - eye2flatLen*eye2flatLen; // c² - a² = b²
//                    if(p2rayLen > 0.5f)continue; // 排除 点云 与 视线 距离过远

                // 重新计算精确的导数（考虑clamp后的uv）
                // glm::vec3 S_clamped, Su_clamped, Sv_clamped;
                // surfaceDerivatives3(u, v, _P_, &S_clamped, &Su_clamped, &Sv_clamped);
                // 计算法线（叉乘前先归一化）
                goLine32 normalVertical = glm::normalize(glm::cross(Su, Sv));

                // 背面剔除判断（点积小于等于0为背面）
                bool faceFront = true;
                if (PolygonBase::isFrontFacing(startEye,normalVertical,S)) {
                    faceFront = false;
                }

                // glm::vec3 rayVec = surfacePoint_final - this->startEye;


                //(rayVec.x*sightLine.x + rayVec.y*sightLine.y + rayVec.z*sightLine.z);

                    //                        return {glm::vec2{u, v}, surfacePoint_final, sightLen_final};

                    solutions.emplace_back(curveSurfaceInfo{glm::vec2{u, v},
                        S,
                        t,
                        faceFront});


                // 视线长 step
                // step² = 视线立方x² + 视线立方y² + 视线立方z²
                // step² = 视线立方x*dx*step + 视线立方y*dy*step + 视线立方z*dz*step
                // step = 视线立方x*dx + 视线立方y*dy + 视线立方z*dz


            }
//            }

    }

    if (solutions.empty()) {
        return std::unexpected(0);
    }


    if (solutions.size() == 1) {
        result->uv = solutions[0].uv;
        result->virtual_Pos = solutions[0].virtual_Pos;
        result->sightLineLen = solutions[0].sightLineLen;
        result->faceToCamera = solutions[0].faceToCamera;
        return result;
    }



//        size_t solutionCount = solutions.size();
    // float minT = solutions[0].sightLineLen;
    // int index = 0;
    // // 最小步长 那个解
    // for(int i = 0; i < solutionCount; ++i) {
    //     if (solutions[i].sightLineLen < minT) {
    //         minT = solutions[i].sightLineLen;
    //         index = i;
    //
    //     }
    // }
    vector<curveSurfaceInfo>::iterator
    resultItem =
        min_element(solutions.begin(), solutions.end(),
                   [](const curveSurfaceInfo &a, const curveSurfaceInfo &b) {
                       return a.sightLineLen < b.sightLineLen;
                   });

    return *resultItem;//solutions[resIndex];



}
std::expected<curveSurfaceInfo,char>
Bezier33Edge4::rayIntersectBezier3_( goLine32 rayDir, glm::vec3 _P_[5][5], glm::vec2 uv) {
    std::expected<curveSurfaceInfo,char> result;

    float u, v;
    u = uv[0];
    v = uv[1];

    float t = 0.0f;

    glm::vec3 S, Su, Sv;

        // 增加曲率自适应迭代（关键改进点）
    float prevError = numeric_limits<float>::max();
        for (int iter = 0; iter < MAX_ITERATIONS; ++iter) {
            surfaceDerivatives3(u, v, _P_, &S, &Su, &Sv);

            float F[3] = {
                    S.x - (this->startEye.x + t * rayDir._.x),
                    S.y - (this->startEye.y + t * rayDir._.y),
                    S.z - (this->startEye.z + t * rayDir._.z)
            };

            if (fabs(F[0]) < EPSILON &&
                fabs(F[1]) < EPSILON &&
                fabs(F[2]) < EPSILON)
                break;

            float J[3][3] = { // 影响迭代 关键
                    {Su.x, Sv.x, -rayDir._.x},
                    {Su.y, Sv.y, -rayDir._.y},
                    {Su.z, Sv.z, -rayDir._.z}
            };

            float delta[3];
            if (!solve3x3(J, F, delta)) break;

            // 动态调整步长
                float currentError = glm::length(glm::vec3(F[0], F[1], F[2]));
                if(currentError > prevError * 0.9f) {
                    delta[0] *= 0.5f; // 误差未明显下降时减小步长
                    delta[1] *= 0.5f;
                    delta[2] *= 0.5f;
                }
                prevError = currentError;
            if (currentError < 0.01f) {
                //println("iter: {}", iter); // 1~2次 就结束
                break; // 出结果
            }
            // ...更新uv...
            u -= delta[0];
            v -= delta[1];
            t -= delta[2];

        } // -------- 内三层循环后 处理solution扩容数组

        if (u >= 0 && u <= 1.0f &&
                v >= 0 && v <= 1.0f &&
                t > 0.f) {
            // u = std::clamp(u, 0.0f, 1.0f);
            // v = std::clamp(v, 0.0f, 1.0f);



            // 表面点 S

            // 计算视线方向（从表面点到相机的方向）
            // glm::vec3 nearlyViewDir = glm::normalize(this->startEye - surfacePoint_final);

            // float rayNotSameAngle = PolygonBase::angleBetweenVectors(-viewDir, sightLine._); // 排除 不一致视线 夹角差
            // bool sameRay = rayNotSameAngle < 0.02f;
            // if (!sameRay) {
            //     goto returnLastNull; // 不在视线内
            //
            // }; // 不在视线内

            // ax+by+cz+d=0 (=点的垂线距离*-1)  <视线垂面 交于点云>


            // 重新计算精确的导数（考虑clamp后的uv）
            // glm::vec3 S_clamped, Su_clamped, Sv_clamped;
            // surfaceDerivatives3(u, v, _P_, &S_clamped, &Su_clamped, &Sv_clamped);
            // 计算法线（叉乘前先归一化）
            glm::vec3 normalVertical = glm::normalize(glm::cross(Su, Sv));

            // 背面剔除判断（点积小于等于0为背面）
            bool faceFront = true;
            if (PolygonBase::isFrontFacing(startEye,normalVertical,S)) {
                faceFront = false;
            }

            // glm::vec3 rayVec = surfacePoint_final - this->startEye;


            //(rayVec.x*sightLine.x + rayVec.y*sightLine.y + rayVec.z*sightLine.z);

                //                        return {glm::vec2{u, v}, surfacePoint_final, sightLen_final};
                result->uv = glm::vec2{u, v};
                result->virtual_Pos = S;
                result->sightLineLen = t;
                result->faceToCamera = faceFront;
                return result;

            // 视线长 step
            // step² = 视线立方x² + 视线立方y² + 视线立方z²
            // step² = 视线立方x*dx*step + 视线立方y*dy*step + 视线立方z*dz*step
            // step = 视线立方x*dx + 视线立方y*dy + 视线立方z*dz


        }

    // returnLastNull:

    return std::unexpected(0);

}
void Bezier33Edge4::computeBezierBasis4(float t, float B[5], float dB[5]) {
    float t2 = t*t;
    float t3 = t2*t;
    float t4 = t3*t;
    float it = 1.0f - t;
    float it2 = it*it;
    float it3 = it2*it;
    float it4 = it3*it;

    // 四次贝塞尔基函数
    B[0] = it4;
    B[1] = 4.0f * t * it3;
    B[2] = 6.0f * t2 * it2;
    B[3] = 4.0f * t3 * it;
    B[4] = t4;

    // 导数计算
    dB[0] = -4.0f * it3;
    dB[1] = 4.0f * (it3 - 3.0f*t*it2);
    dB[2] = 12.0f * t * it2 - 12.0f * t2 * it;
    dB[3] = 4.0f * (3.0f*t2*it - t3);
    dB[4] = 4.0f * t3;
}

glm::vec3 Bezier33Edge4::evaluatePatch4(float u, float v, const glm::vec3 P[5][5]) {
    float Bu[5], Bv[5];

    // 计算u方向基函数
    float it = 1.0f - u;
    Bu[0] = it*it*it*it;
    Bu[1] = 4.0f * u * it*it*it;
    Bu[2] = 6.0f * u*u * it*it;
    Bu[3] = 4.0f * u*u*u * it;
    Bu[4] = u*u*u*u;

    // 计算v方向基函数
    float iv = 1.0f - v;
    Bv[0] = iv*iv*iv*iv;
    Bv[1] = 4.0f * v * iv*iv*iv;
    Bv[2] = 6.0f * v*v * iv*iv;
    Bv[3] = 4.0f * v*v*v * iv;
    Bv[4] = v*v*v*v;

    // 双四次曲面计算
    glm::vec3 point(0);
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            point += Bu[i] * Bv[j] * P[i][j];
        }
    }
    return point;
}

void Bezier33Edge4::surfaceDerivatives4(float u, float v, glm::vec3 P[5][5],
                                        glm::vec3& S, glm::vec3& Su, glm::vec3& Sv)
{
    float Bu[5], Bv[5], dBu[5], dBv[5];
    computeBezierBasis4(u, Bu, dBu);
    computeBezierBasis4(v, Bv, dBv);

    S = Su = Sv = {0,0,0};

    // 5x5控制点遍历
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            float basis = Bu[i] * Bv[j];
            S += basis * P[i][j];

            Su += dBu[i] * Bv[j] * P[i][j];
            Sv += Bu[i] * dBv[j] * P[i][j];
        }
    }
}
curveSurfaceInfo Bezier33Edge4::rayIntersectBezier4(glm::vec3& _startEye, glm::vec3& sightLine, glm::vec3 P[5][5]) {
    std::vector<curveSurfaceInfo> solutions;
    curveSurfaceInfo result = {};

    float u, v;
    for (int i = 0; i <= NUM_SAMPLES; ++i) {
        u = i / (float)NUM_SAMPLES; // 1/15 ~ 15/15
        for (int j = 0; j <= NUM_SAMPLES; ++j) {
            v = j / (float)NUM_SAMPLES; // 1/15 ~ 15/15
            float t = 0.0f;


            glm::vec3 S, Su, Sv;
            for (int iter = 0; iter < MAX_ITERATIONS; ++iter) {
                surfaceDerivatives4(u, v, P, S, Su, Sv);

                float F[3] = {
                        S.x - (_startEye.x + t * sightLine.x),
                        S.y - (_startEye.y + t * sightLine.y),
                        S.z - (_startEye.z + t * sightLine.z)
                };

                if (fabs(F[0]) < EPSILON &&
                    fabs(F[1]) < EPSILON &&
                    fabs(F[2]) < EPSILON) break;

                float J[3][3] = {
                        {Su.x, Sv.x, -sightLine.x},
                        {Su.y, Sv.y, -sightLine.y},
                        {Su.z, Sv.z, -sightLine.z}
                };

                float delta[3];
                if (!solve3x3(J, F, delta)) break;

                u -= delta[0];
                v -= delta[1];
                t -= delta[2];
            } // 内三层循环后 处理solution扩容数组

            if (u >= -EPSILON && u <= 1.0f+EPSILON &&
                v >= -EPSILON && v <= 1.0f+EPSILON &&
                t > -EPSILON
                /*u >= 0 && u <= 1.0f &&
                v >= 0 && v <= 1.0f &&
                t > 0.f*/)
            {
                u = std::clamp(u, 0.0f, 1.0f);
                v = std::clamp(v, 0.0f, 1.0f);

                bool exists = false; // 结果去重
                for (auto& infoNow : solutions) {
                    if (fabs(infoNow.uv[0] - u) < 1e-4f &&
                        fabs(infoNow.uv[1] - v) < 1e-4f) {
                        exists = true;
                        break;
                    }
                }
                if (!exists) {
                    // 计算表面点后立即进行法线计算
                    glm::vec3 surfacePoint_final = evaluatePatch4(u, v, P);

                    // 重新计算精确的导数（考虑clamp后的uv）
                    glm::vec3 S_clamped, Su_clamped, Sv_clamped;
                    surfaceDerivatives4(u, v, P, S_clamped, Su_clamped, Sv_clamped);
                    // 计算法线（叉乘前先归一化）
                    glm::vec3 normal = glm::normalize(glm::cross(Su_clamped, Sv_clamped));
                    // 计算视线方向（从表面点到相机的方向）
                    glm::vec3 viewDir = glm::normalize(_startEye - surfacePoint_final);
                    // 背面剔除判断（点积小于等于0为背面）
                    bool faceFront = true;
                    if(PolygonBase::isFrontFacing(startEye,normal,surfacePoint_final)) {
                        faceFront = false;
                    }
                glm::vec3 rayVec = surfacePoint_final - _startEye;

                    float rayNotSameAngle = PolygonBase::angleBetweenVectors_deg(-viewDir, sightLine); // 排除 不一致视线 夹角差
                    bool sameRay = rayNotSameAngle < 0.02f;

                if(sameRay){

                    float sightLen_final = glm::dot(rayVec, sightLine);//(rayVec.x*sightLine.x + rayVec.y*sightLine.y + rayVec.z*sightLine.z);
                    if (sightLen_final > 0.f) {
    //                        return {glm::vec2{u, v}, surfacePoint_final, sightLen_final};
                        solutions.push_back({glm::vec2{u, v},surfacePoint_final,sightLen_final,faceFront});
                    }
                    // 视线长 step
                    // step² = 视线立方x² + 视线立方y² + 视线立方z²
                    // step² = 视线立方x*dx*step + 视线立方y*dy*step + 视线立方z*dz*step
                    // step = 视线立方x*dx + 视线立方y*dy + 视线立方z*dz
                }
                }
            }
        }
    }
    size_t solutionCount = solutions.size();
    if (solutionCount == 1){
        result.uv = solutions[0].uv;
        result.virtual_Pos = solutions[0].virtual_Pos;
        result.sightLineLen = solutions[0].sightLineLen;
        result.faceToCamera = solutions[0].faceToCamera;
        return result;
    }
    if (solutionCount == 0){
        result.uv = glm::vec2(std::numeric_limits<float>::quiet_NaN());
        result.virtual_Pos = glm::vec3(std::numeric_limits<float>::quiet_NaN());
        result.sightLineLen = std::numeric_limits<float>::quiet_NaN();
        result.faceToCamera = false;
        return result;
    }

    float minT = solutions[0].sightLineLen;
    int index = 0;
    // 最小步长 那个解
    for(int i=0;i<solutionCount; ++i){
        if(solutions[i].sightLineLen<minT){
            minT = solutions[i].sightLineLen;
            index = i;

        }
    }

    return solutions[index];
}
