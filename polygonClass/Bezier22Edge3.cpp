//
// Created by iceoc0 on 2026/1/17.
//
#include "Bezier22Edge3.h"
void trianglePair::freshLineBoundary_triangle(vector<glm::vec2>& _Grid2D) {
    PolygonBase::fresh2D_scanRows_3(_Grid2D[index1[0]],
                       _Grid2D[index1[1]],
                       _Grid2D[index1[2]], &scanRow1,9);
    PolygonBase::fresh2D_scanRows_3(_Grid2D[index2[0]],
                       _Grid2D[index2[1]],
                       _Grid2D[index2[2]], &scanRow2,9);
}

void trianglePair::draw2Triangle(ScreenDemo* ScreenEye, PolygonBase* Self) {
    Bezier22Edge3* mainObj = dynamic_cast<Bezier22Edge3*>(Self);
    float deepNow;
    for(lineBoundary & _linePosInfo : scanRow1) {
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++) {
            deepNow = getDeep_ByVirtual3Point(Self, nowX, _linePosInfo.y,1);
            if (onFront1)
            ScreenEye->putPixel_(nowX, _linePosInfo.y, mainObj->colorP, deepNow, Self);
            else {
                ScreenEye->putPixel_(nowX, _linePosInfo.y, mainObj->backColor, deepNow, Self);
            }

        }
    }
    for(lineBoundary & _linePosInfo : scanRow2) {
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++) {
            deepNow = getDeep_ByVirtual3Point(Self,nowX, _linePosInfo.y,2);
            if (onFront2)
            ScreenEye->putPixel_(nowX, _linePosInfo.y, mainObj->colorGrid, deepNow, Self);
            else {
                ScreenEye->putPixel_(nowX, _linePosInfo.y, mainObj->backColor, deepNow, Self);
            }
        }
    }
}
float trianglePair::getDeep_ByVirtual3Point(PolygonBase* Self, float x, float y,char triangle) {
    Bezier22Edge3* mainObj = dynamic_cast<Bezier22Edge3*>(Self);
    glm::vec3* p1;
    glm::vec3* p2;
    glm::vec3* p3;
    if (triangle==1) {
        p1 = &mainObj->Grid_virtual[index1[0]];
        p2 = &mainObj->Grid_virtual[index1[1]];
        p3 = &mainObj->Grid_virtual[index1[2]];
    }else {
        p1 = &mainObj->Grid_virtual[index2[0]];
        p2 = &mainObj->Grid_virtual[index2[1]];
        p3 = &mainObj->Grid_virtual[index2[2]];
    }

    // 两边 射线
    glm::vec3 p2Top1 = *p1 - *p2;
    glm::vec3 p2Top3 = *p3 - *p2;
    // 向量叉乘
    // 归一化法线
    goLine32 vertical = glm::normalize(glm::cross(p2Top1, p2Top3)); // a b c

    if (triangle==1) { // 刷新 正反面
        onFront1 = PolygonBase::isFrontFacing(mainObj->startEye,vertical,*p1);
    }else {
        onFront2 = PolygonBase::isFrontFacing(mainObj->startEye,vertical,*p1);
    }


    // ax+by+cz+d=0  d=-(ax+by+cz)
    float d = -glm::dot(vertical._, *p1);

    // if (cornerIndex[0] == 0) { // 0 1 3
    //     virtual_abcd_LT[0] = vertical[0];
    //     virtual_abcd_LT[1] = vertical[1];
    //     virtual_abcd_LT[2] = vertical[2];
    //     virtual_abcd_LT[3] = d;
    // }else { // 1 2 3
    //     virtual_abcd_RB[0] = vertical[0];
    //     virtual_abcd_RB[1] = vertical[1];
    //     virtual_abcd_RB[2] = vertical[2];
    //     virtual_abcd_RB[3] = d;
    // }


    glm::vec3 virtual_ScreenPoint = {x,y,0.f};

    goLine32 rayNorm = ScreenDemo::get_AgoB_direction3D(mainObj->startEye, virtual_ScreenPoint);
    // step_up = -(ax+by+cz+d)
    float step_up = -glm::dot(mainObj->startEye, vertical._) - d;
    // step_down = dot(rayNorm, vertical)
    float step_down = glm::dot(rayNorm._, vertical._);
    float t = step_up / step_down;
    float result = mainObj->startEye.z + rayNorm.dz * t;
    return result;
}

void triangleSelf::freshLineBoundary_triangle(vector<glm::vec2>& _Grid2D) {
    PolygonBase::fresh2D_scanRows_3(_Grid2D[index1[0]],
                       _Grid2D[index1[1]],
                       _Grid2D[index1[2]], &scanRow1,9);

}
void triangleSelf::draw2Triangle(ScreenDemo* ScreenEye, PolygonBase* Self) {
    Bezier22Edge3* mainObj = dynamic_cast<Bezier22Edge3*>(Self);
    float deepNow;
    for(lineBoundary & _linePosInfo : scanRow1) {
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++) {
            deepNow = getDeep_ByVirtual3Point(Self, nowX, _linePosInfo.y);
            if (onFront1)
            ScreenEye->putPixel_(nowX, _linePosInfo.y, mainObj->colorP, deepNow, Self);
            else {
                ScreenEye->putPixel_(nowX, _linePosInfo.y, mainObj->backColor, deepNow, Self);
            }

        }
    }

}
float triangleSelf::getDeep_ByVirtual3Point(PolygonBase* Self, float x, float y) {
    Bezier22Edge3* mainObj = dynamic_cast<Bezier22Edge3*>(Self);

    glm::vec3& p1 = mainObj->Grid_virtual[index1[0]];
    glm::vec3& p2 = mainObj->Grid_virtual[index1[1]];
    glm::vec3& p3 = mainObj->Grid_virtual[index1[2]];


    // 两边 射线
    glm::vec3 p2Top1 = p1 - p2;
    glm::vec3 p2Top3 = p3 - p2;
    // 向量叉乘
    // 归一化法线
    goLine32 vertical = glm::normalize(glm::cross(p2Top1, p2Top3)); // a b c

    // 刷新 正反面
    onFront1 = PolygonBase::isFrontFacing(mainObj->startEye,vertical,p1);



    // ax+by+cz+d=0  d=-(ax+by+cz)
    float d = -glm::dot(vertical._, p1);

    // if (cornerIndex[0] == 0) { // 0 1 3
    //     virtual_abcd_LT[0] = vertical[0];
    //     virtual_abcd_LT[1] = vertical[1];
    //     virtual_abcd_LT[2] = vertical[2];
    //     virtual_abcd_LT[3] = d;
    // }else { // 1 2 3
    //     virtual_abcd_RB[0] = vertical[0];
    //     virtual_abcd_RB[1] = vertical[1];
    //     virtual_abcd_RB[2] = vertical[2];
    //     virtual_abcd_RB[3] = d;
    // }


    glm::vec3 virtual_ScreenPoint = {x,y,0.f};

    goLine32 rayNorm = ScreenDemo::get_AgoB_direction3D(mainObj->startEye, virtual_ScreenPoint);
    // step_up = -(ax+by+cz+d)
    float step_up = -glm::dot(mainObj->startEye, vertical._) - d;
    // step_down = dot(rayNorm, vertical)
    float step_down = glm::dot(rayNorm._, vertical._);
    float t = step_up / step_down;
    float result = mainObj->startEye.z + rayNorm.dz * t;
    return result;
}
template<typename T>
bool is_complex_nan(const complex<T>& c) {
    static_assert(std::is_floating_point_v<T>,"T must be a floating-point type");
    return isnan(c.real()) || isnan(c.imag());
}

constexpr double uvwRange[2] = {-0.0,1.0}; // -1.0 1.0
constexpr float boxExpand = 0.03f; // 0.03
Bezier22Edge3::Bezier22Edge3(controlPoint3D& _P,unsigned char __debug):PolygonBase(9) {


    debugMode = __debug;
    this->P_world.freshP(_P);
    this->P_unchange.freshP(_P);
    generateGrid();

    initBox_TBLRNF(); // 在拿到网格点后 计算包围盒 外围
    initBoxInfo(); // 计算包围盒 顶点 与 all tips

    // std::fill(Grid2D.begin(), Grid2D.end(), glm::vec2{0,0});
    backColor = {149.f/255.f,143.f/255.f,93.f/255.f};

    renderNext = false;

    startEye64 = startEye;

    firstRendered_front = true;
    firstRendered_back = true;
    firstRendered_left = true;
    firstRendered_right = true;
    firstRendered_top = true;
    firstRendered_bottom = true;

}
void Bezier22Edge3::generateGrid() {

    int cnt = 0;
    // 遍历 barycentric coordinates (u, v, w), where w = 1 - u - v
    for (int i = 0; i <= resolution; ++i) {
        float u = static_cast<float>(i) / resolution;
        for (int j = 0; j <= resolution - i; ++j,cnt++) {
            float v = static_cast<float>(j) / resolution;
            float w = 1.0f - u - v;

            // 二次 Bernstein 基函数
            float B200 = u * u;                     // (2,0,0)
            float B020 = v * v;                     // (0,2,0)
            float B002 = w * w;                     // (0,0,2)
            float B110 = 2.0f * u * v;              // (1,1,0)
            float B011 = 2.0f * v * w;              // (0,1,1)
            float B101 = 2.0f * u * w;              // (1,0,1)

            glm::vec3 point =
                B200 * P_unchange.tip[0] +
                B020 * P_unchange.tip[1] +
                B002 * P_unchange.tip[2] +
                B110 * P_unchange.edgeMid[0] +
                B011 * P_unchange.edgeMid[1] +
                B101 * P_unchange.edgeMid[2];

            Grid_world[cnt]=point;
            Grid_unchange[cnt]=point;
            // println("cnt:{}, u:{}, v:{}, w:{}",cnt,u,v,w);
        }
    }
    // println(stderr,"surface points got{}",Grid_unchange.size());

    // 2. 构建三角形索引（使用三角剖分）
// println("~~~Grid_world size:{} = {}",cnt,(resolution + 1) * (resolution + 2) / 2);

    // 重新计算索引（更清晰的方式：用函数映射 (i,j) -> index）
    auto index = [](int i, int j) -> int {
        return i * (2 * resolution - i + 3) / 2 + j; // 或预存偏移
    };

    // 更简单：先存储所有点到 vector，再用双层循环建索引

    triangles.resize((resolution + 1) * (resolution + 2) / 2);
    // 第一步：生成点（同前）


    // 第二步：建索引（安全版）
    int cnt_ = 0;
    for (int i = 0; i < resolution; ++i) {
        for (int j = 0; j < resolution - i - 1; ++j,cnt_++) { // 注意：-1！
            int p0 = index(i, j);
            int p1 = index(i + 1, j);
            int p2 = index(i, j + 1);
            int p3 = index(i + 1, j + 1);
            if (triangleBackFront) {
                triangles[cnt_].index1 = {p0, p1, p2};
                triangles[cnt_].index2 = {p1, p3, p2};
            }else {
                triangles[cnt_].index1 = {p2, p1, p0};
                triangles[cnt_].index2 = {p2, p3, p1};
            }


        }
    }

    vector<int> rowStart(resolution + 2);
    rowStart[0] = 0;
    for (int r = 0; r <= resolution; ++r) {
        rowStart[r + 1] = rowStart[r] + (resolution - r + 1);
    }
    auto index_ = [rowStart](int i, int j) -> int {
        return rowStart[i] + j;
    };

    triangleLast.resize(resolution );
    glm::ivec3 indexNow;
    for (int k = 0; k < resolution; ++k) {
        if (triangleBackFront) {
            indexNow[2] = index_(k, resolution - k);         // (k, R−k)
            indexNow[1] = index_(k + 1, resolution - k - 1); // (k+1, R−k−1)
            indexNow[0] = index_(k, resolution - k - 1);     // (k, R−k−1)
        }else {
            indexNow[0] = index_(k, resolution - k);         // (k, R−k)
            indexNow[1] = index_(k + 1, resolution - k - 1); // (k+1, R−k−1)
            indexNow[2] = index_(k, resolution - k - 1);     // (k, R−k−1)
        }


        triangleLast[k].index1 = indexNow;
        //println("index last row ({},{},{})",indexNow[0],indexNow[1],indexNow[2]);
    }
}
glm::vec3 Bezier22Edge3::evaluatePatch2_screenAxis(const glm::vec3& _uvw) {
    // 二次 Bernstein 基函数
    float B200 = _uvw[0] * _uvw[0];                     // (2,0,0)
    float B020 = _uvw[1] * _uvw[1];                     // (0,2,0)
    float B002 = _uvw[2] * _uvw[2];                     // (0,0,2)
    float B110 = 2.0f * _uvw[0] * _uvw[1];              // (1,1,0)
    float B011 = 2.0f * _uvw[1] * _uvw[2];              // (0,1,1)
    float B101 = 2.0f * _uvw[0] * _uvw[2];              // (1,0,1)

    glm::vec3 point =
        B200 * P_virtual.tip[0] +
        B020 * P_virtual.tip[1] +
        B002 * P_virtual.tip[2] +
        B110 * P_virtual.edgeMid[0] +
        B011 * P_virtual.edgeMid[1] +
        B101 * P_virtual.edgeMid[2];
    return point;
}
void Bezier22Edge3::freshGoX(){
//     DEBUG_SECTION(
//         float boxLenXCalc = glm::distance(scanBox3D_world.rtnSet, scanBox3D_world.ltnSet);
// if (abs(boxLenXCalc - boxLenX) > 1e-4f) {
//     println(stderr,"贝塞尔223 boxLenXCalc:{} ≠ boxLenX:{}",boxLenXCalc,boxLenX);
// }
//     )
    world_toX._ = (scanBox3D_world.rtnSet - scanBox3D_world.ltnSet) / boxLenX;
    // world_toX.dx = (scanBox3D_world.rtnSet.x - scanBox3D_world.ltnSet.x) / boxLenX;
    // world_toX.dy = (scanBox3D_world.rtnSet.y - scanBox3D_world.ltnSet.y) / boxLenX;
    // world_toX.dz = (scanBox3D_world.rtnSet.z - scanBox3D_world.ltnSet.z) / boxLenX;
}
void Bezier22Edge3::freshGoY(){
//     DEBUG_SECTION(
//      float boxLenYCalc = glm::distance(scanBox3D_world.lbnSet, scanBox3D_world.ltnSet);
// if (abs(boxLenYCalc - boxLenY) > 1e-4f) {
//  println(stderr,"贝塞尔223 boxLenYCalc:{} ≠ boxLenY:{}",boxLenYCalc,boxLenY);
// }
//  )
    world_toY._ = (scanBox3D_world.lbnSet - scanBox3D_world.ltnSet) / boxLenY;
    // world_toY.dx = (scanBox3D_world.lbnSet.x - scanBox3D_world.ltnSet.x) / boxLenY;
    // world_toY.dy = (scanBox3D_world.lbnSet.y - scanBox3D_world.ltnSet.y) / boxLenY;
    // world_toY.dz = (scanBox3D_world.lbnSet.z - scanBox3D_world.ltnSet.z) / boxLenY;
}
void Bezier22Edge3::freshGoDEEP() {
//     DEBUG_SECTION(
//   float boxLenZCalc = glm::distance(scanBox3D_world.ltfSet, scanBox3D_world.ltnSet);
// if (abs(boxLenZCalc - boxLenZ) > 1e-4f) {
// println(stderr,"贝塞尔223 boxLenZCalc:{} ≠ boxLenZ:{}",boxLenZCalc,boxLenZ);
// }
// )
    world_toDEEP._ = (scanBox3D_world.ltfSet - scanBox3D_world.ltnSet) / boxLenZ;
    // world_toDEEP.dx = (scanBox3D_world.ltfSet.x - scanBox3D_world.ltnSet.x) / boxLenZ;
    // world_toDEEP.dy = (scanBox3D_world.ltfSet.y - scanBox3D_world.ltnSet.y) / boxLenZ;
    // world_toDEEP.dz = (scanBox3D_world.ltfSet.z - scanBox3D_world.ltnSet.z) / boxLenZ;
}

void Bezier22Edge3::goX_(glm::vec3& _srcXYZ, float _move){
    _srcXYZ = _srcXYZ + _move * world_toX._;
}
void Bezier22Edge3::goY_(glm::vec3& _srcXYZ, float _move){
    _srcXYZ = _srcXYZ + _move * world_toY._;
}
void Bezier22Edge3::goDEEP_(glm::vec3& _srcXYZ, float _move){
    _srcXYZ = _srcXYZ + _move * world_toDEEP._;
}
TBLRFB Bezier22Edge3::initBox_TBLRNF(){
    // 上下 左右 近远
    boxVolume = {Grid_world[0].y, Grid_world[0].y,
                        Grid_world[0].x, Grid_world[0].x,
                        Grid_world[0].z, Grid_world[0].z}; // 初始化为数组内的 避免自己把极值定到外边
    // 遍历点云 刷出最小 最大 值
    for(int i=0;i<sizeNeed; ++i){

        if(Grid_world[i].y < boxVolume.topY) boxVolume.topY = Grid_world[i].y;
        else if(Grid_world[i].y > boxVolume.bottomY) boxVolume.bottomY = Grid_world[i].y;

        if(Grid_world[i].x < boxVolume.leftX) boxVolume.leftX = Grid_world[i].x;
        else if(Grid_world[i].x > boxVolume.rightX) boxVolume.rightX = Grid_world[i].x;

        if(Grid_world[i].z < boxVolume.nearZ) boxVolume.nearZ = Grid_world[i].z;
        else if(Grid_world[i].z > boxVolume.farZ) boxVolume.farZ = Grid_world[i].z;

    }

    float betweenY_ = boxVolume.bottomY - boxVolume.topY;
    float betweenX_ = boxVolume.rightX - boxVolume.leftX;
    float betweenZ_ = boxVolume.farZ - boxVolume.nearZ;
    float top_bottom_distance = betweenY_ / 2.f;
    float right_left_distance = betweenX_ / 2.f;
    float far_near_distance =   betweenZ_ / 2.f;


    boxVolume.topY -= top_bottom_distance * boxExpand; // 上拓 5%
    //cout << " 上拓 5% " << endl;

    boxVolume.bottomY += top_bottom_distance * boxExpand; // 下拓 5%
    //cout << " 下拓 5% " << endl;

    boxVolume.leftX -= right_left_distance * boxExpand; // 左拓 5%
    //cout << " 左拓 5% " << endl;

    boxVolume.rightX += right_left_distance * boxExpand; // 右拓 5%
    //cout << " 右拓 5% " << endl;

    boxVolume.nearZ -= far_near_distance * boxExpand; // 近拓 5%
    //cout << " 近拓 5% " << endl;

    boxVolume.farZ += far_near_distance * boxExpand; // 远拓 5%
    //cout << " 远拓 5% " << endl;

    boxLenY = boxVolume.bottomY - boxVolume.topY;
    boxLenX = boxVolume.rightX - boxVolume.leftX;
    boxLenZ = boxVolume.farZ - boxVolume.nearZ;

    boxLenHalfX = boxLenX;
    boxLenHalfY = boxLenY;
    boxLenHalfZ = boxLenZ;
    return boxVolume;
}
void Bezier22Edge3::initBoxInfo(){
    glm::vec3 ltnSet = {boxVolume.leftX, boxVolume.topY, boxVolume.nearZ};
    glm::vec3 rtnSet = {boxVolume.rightX, boxVolume.topY, boxVolume.nearZ};
    glm::vec3 rbnSet = {boxVolume.rightX, boxVolume.bottomY, boxVolume.nearZ};
    glm::vec3 lbnSet = {boxVolume.leftX, boxVolume.bottomY, boxVolume.nearZ};


    glm::vec3 ltfSet = {boxVolume.leftX, boxVolume.topY, boxVolume.farZ};
    glm::vec3 rtfSet = {boxVolume.rightX, boxVolume.topY, boxVolume.farZ};
    glm::vec3 rbfSet = {boxVolume.rightX, boxVolume.bottomY, boxVolume.farZ};
    glm::vec3 lbfSet = {boxVolume.leftX, boxVolume.bottomY, boxVolume.farZ};

    setBox3D(ltnSet, rtnSet, rbnSet, lbnSet, ltfSet, rtfSet, rbfSet, lbfSet);
    scanBox3D_unchange.ltnSet = scanBox3D_world.ltnSet;
    scanBox3D_unchange.rtnSet = scanBox3D_world.rtnSet;
    scanBox3D_unchange.rbnSet = scanBox3D_world.rbnSet;
    scanBox3D_unchange.lbnSet = scanBox3D_world.lbnSet;

    scanBox3D_unchange.ltfSet = scanBox3D_world.ltfSet;
    scanBox3D_unchange.rtfSet = scanBox3D_world.rtfSet;
    scanBox3D_unchange.rbfSet = scanBox3D_world.rbfSet;
    scanBox3D_unchange.lbfSet = scanBox3D_world.lbfSet;

    scanBox3D_unchange.center = scanBox3D_world.center;

}
void Bezier22Edge3::setBox3D(glm::vec3& _ltn, glm::vec3& _rtn, glm::vec3& _rbn, glm::vec3& _lbn,
                  glm::vec3& _ltf, glm::vec3& _rtf, glm::vec3& _rbf, glm::vec3& _lbf){
    scanBox3D_world.ltnSet = _ltn;
    scanBox3D_world.rtnSet = _rtn;
    scanBox3D_world.rbnSet = _rbn;
    scanBox3D_world.lbnSet = _lbn;

    scanBox3D_world.ltfSet = _ltf;
    scanBox3D_world.rtfSet = _rtf;
    scanBox3D_world.rbfSet = _rbf;
    scanBox3D_world.lbfSet = _lbf;

    freshGoX();freshGoY();freshGoDEEP();

    // println("椭球 world box ltn{}",showVec3(_ltn));
    // println("world to x:{}",showVec3(world_toX._));
    // println("world to y:{}",showVec3(world_toY._));
    // println("world to z:{}",showVec3(world_toDEEP._));
    // println("radius a:{},b:{},c:{}",radiusA,radiusB,radiusC);
    scanBox3D_world.center= _ltn;
    goX_(scanBox3D_world.center,boxLenHalfX);
    goY_(scanBox3D_world.center,boxLenHalfY);
    goDEEP_(scanBox3D_world.center,boxLenHalfZ);


    // println("椭球 world box center{}",showVec3(tblrXYZnf.center));

//    cout << "### boxLenX:" << boxLenX << endl;
//    cout << "### boxLenY:" << boxLenY << endl;
//    cout << "### boxLenZ:" << boxLenZ << endl;

DEBUG_SECTION(
    scanBox3D_world.rtn_ltn_tip = scanBox3D_world.ltnSet;
    goX_(scanBox3D_world.rtn_ltn_tip,-rounfBoxTipLen);

    scanBox3D_world.lbn_ltn_tip = scanBox3D_world.ltnSet;
    goY_(scanBox3D_world.lbn_ltn_tip,-rounfBoxTipLen);

    scanBox3D_world.ltf_ltn_tip = scanBox3D_world.ltnSet;
    goDEEP_(scanBox3D_world.ltf_ltn_tip,-rounfBoxTipLen);

    scanBox3D_world.lbf_rbf_tip = scanBox3D_world.rbfSet;
    goX_(scanBox3D_world.lbf_rbf_tip,rounfBoxTipLen);

    scanBox3D_world.rtf_rbf_tip = scanBox3D_world.rbfSet;
    goY_(scanBox3D_world.rtf_rbf_tip,rounfBoxTipLen);

    scanBox3D_world.rbn_rbf_tip = scanBox3D_world.rbfSet;
    goDEEP_(scanBox3D_world.rbn_rbf_tip,rounfBoxTipLen);
)
    //println("椭球 set 3D");
}

void Bezier22Edge3::setBox2D(glm::vec2& _ltn, glm::vec2& _rtn, glm::vec2& _rbn, glm::vec2& _lbn,
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
){
    scanBox2D_.ltnSet = _ltn;
    scanBox2D_.rtnSet = _rtn;
    scanBox2D_.rbnSet = _rbn;
    scanBox2D_.lbnSet = _lbn;

    scanBox2D_.ltfSet = _ltf;
    scanBox2D_.rtfSet = _rtf;
    scanBox2D_.rbfSet = _rbf;
    scanBox2D_.lbfSet = _lbf;

    scanBox2D_.center = _center;
DEBUG_SECTION(
    scanBox2D_.rtn_ltn_tip = _rtn_ltn_tip;
    scanBox2D_.lbn_ltn_tip = _lbn_ltn_tip;
    scanBox2D_.ltf_ltn_tip = _ltf_ltn_tip;

    scanBox2D_.lbf_rbf_tip = _lbf_rbf_tip;
    scanBox2D_.rtf_rbf_tip = _rtf_rbf_tip;
    scanBox2D_.rbn_rbf_tip = _rbn_rbf_tip;
)
    // println("椭球 set 2D");
    // println("ltn:{}",showVec2(tblrXYnf.ltnSet));
    // println("rtn:{}",showVec2(tblrXYnf.rtnSet));
}
void Bezier22Edge3::setColor(int color1, int color2,int colorBack) {
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
    BGR3f color_back;
    color_back.setBGR(colorBack,1);
    backColor[0] = color_back.r1;
    backColor[1] = color_back.g1;
    backColor[2] = color_back.b1;
}
void Bezier22Edge3::switchDebug() {
    // 0 1 2
    if(debugMode==0) {
        debugMode=1;
        println("贝塞尔223 debugMode:1");
    }
    else {
        debugMode=0;
        println("贝塞尔223 debugMode:0");
    }
}

void Bezier22Edge3::Draw_Tick(ScreenDemo *ScreenEye) {
    /*
    *    0
    *  _0 _2
    *  1 _1  2
    */
    // left面 法线
    flatLeftFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        -world_toX._,scanBox3D_world.ltnSet);
    // top面 法线
    flatTopFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        -world_toY._,scanBox3D_world.ltnSet);
    // front面 法线
    flatFrontFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        -world_toDEEP._,scanBox3D_world.ltnSet);
    // right面 法线
    flatRightFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        world_toX._,scanBox3D_world.rbfSet);
    // bottom面 法线
    flatBottomFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        world_toY._,scanBox3D_world.rbfSet);
    // back面 法线
    flatBackFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        world_toDEEP._,scanBox3D_world.rbfSet);

    if (renderNext) {

        if (flatFrontFacing) { // ltn rtn rbn lbn
        _solidRectangle2D_(ScreenEye, scanBox2D_.ltnSet,
                                scanBox2D_.rtnSet,
                                scanBox2D_.rbnSet,
                                scanBox2D_.lbnSet,
        lineScanFillColor_front,pixelEyeDeep_front,firstRendered_front); // 反面 需要经纬度
        //println("front solid");

            firstRendered_front = false; // 移动 才变true
        }
        if (flatBackFacing) { // rtf ltf lbf rbf
            _solidRectangle2D_(ScreenEye, scanBox2D_.rtfSet,
                                    scanBox2D_.ltfSet,
                                    scanBox2D_.lbfSet,
                                    scanBox2D_.rbfSet,
            lineScanFillColor_back,pixelEyeDeep_back,firstRendered_back); // 反面 需要经纬度
            //println("back solid");
            firstRendered_back = false;
        }
        if (flatLeftFacing) { // ltf ltn lbn lbf
            _solidRectangle2D_(ScreenEye, scanBox2D_.ltfSet,
                                    scanBox2D_.ltnSet,
                                    scanBox2D_.lbnSet,
                                    scanBox2D_.lbfSet,
            lineScanFillColor_left,pixelEyeDeep_left,firstRendered_left); // 反面 需要经纬度
            //println("left solid");
            firstRendered_left = false;
        }
        if (flatRightFacing) { // rtn rtf rbf rbn
            _solidRectangle2D_(ScreenEye, scanBox2D_.rtnSet,
                                    scanBox2D_.rtfSet,
                                    scanBox2D_.rbfSet,
                                    scanBox2D_.rbnSet,
            lineScanFillColor_right,pixelEyeDeep_right,firstRendered_right); // 反面 需要经纬度
            //println("right solid");
            firstRendered_right = false;
        }
        if (flatTopFacing) {
            _solidRectangle2D_(ScreenEye, scanBox2D_.ltfSet,
                                    scanBox2D_.rtfSet,
                                    scanBox2D_.rtnSet,
                                    scanBox2D_.ltnSet,
            lineScanFillColor_top,pixelEyeDeep_top,firstRendered_top); // 反面 需要经纬度
            //println("top solid");
            firstRendered_top = false;
        }
        if (flatBottomFacing) {
            _solidRectangle2D_(ScreenEye, scanBox2D_.lbnSet,
                                    scanBox2D_.rbnSet,
                                    scanBox2D_.rbfSet,
                                    scanBox2D_.lbfSet,
            lineScanFillColor_bottom,pixelEyeDeep_bottom,firstRendered_bottom); // 反面 需要经纬度
            //println("bottom solid");
            firstRendered_bottom = false;
        }
    }else {

        solidRectangle2D(ScreenEye);
    }


    if (showP) {
        // 0 _0
        float deepNow = (P_virtual.tip[0].z + P_virtual.edgeMid[0].z) / 2.f;
        ScreenDemo::line2ScreenBuffer_(ScreenEye,P2D.tip[0].x,P2D.tip[0].y,P2D.edgeMid[0].x,P2D.edgeMid[0].y,
            colorP,deepNow);
        // _0 1
        deepNow = (P_virtual.edgeMid[0].z + P_virtual.tip[1].z) / 2.f;
        ScreenDemo::line2ScreenBuffer_(ScreenEye,P2D.edgeMid[0].x,P2D.edgeMid[0].y,P2D.tip[1].x,P2D.tip[1].y,
            colorP,deepNow);
        // 1 _1
        deepNow = (P_virtual.tip[1].z + P_virtual.edgeMid[1].z) / 2.f;
        ScreenDemo::line2ScreenBuffer_(ScreenEye,P2D.tip[1].x,P2D.tip[1].y,P2D.edgeMid[1].x,P2D.edgeMid[1].y,
            colorP,deepNow);
        // _1 2
        deepNow = (P_virtual.edgeMid[1].z + P_virtual.tip[2].z) / 2.f;
        ScreenDemo::line2ScreenBuffer_(ScreenEye,P2D.edgeMid[1].x,P2D.edgeMid[1].y,P2D.tip[2].x,P2D.tip[2].y,
            colorP,deepNow);
        // 2 _2
        deepNow = (P_virtual.tip[2].z + P_virtual.edgeMid[2].z) / 2.f;
        ScreenDemo::line2ScreenBuffer_(ScreenEye,P2D.tip[2].x,P2D.tip[2].y,P2D.edgeMid[2].x,P2D.edgeMid[2].y,
            colorP,deepNow);
        // _2 0
        deepNow = (P_virtual.edgeMid[2].z + P_virtual.tip[0].z) / 2.f;
        ScreenDemo::line2ScreenBuffer_(ScreenEye,P2D.edgeMid[2].x,P2D.edgeMid[2].y,P2D.tip[0].x,P2D.tip[0].y,
            colorP,deepNow);
        // _0 _1
        // deepNow = (P_virtual.edgeMid[0].z + P_virtual.edgeMid[1].z) / 2.f;
        // ScreenDemo::line2ScreenBuffer_(ScreenEye,P2D.edgeMid[0].x,P2D.edgeMid[0].y,P2D.edgeMid[1].x,P2D.edgeMid[1].y,
        //     colorP,deepNow);
        // _1 _2
        // deepNow = (P_virtual.edgeMid[1].z + P_virtual.edgeMid[2].z) / 2.f;
        // ScreenDemo::line2ScreenBuffer_(ScreenEye,P2D.edgeMid[1].x,P2D.edgeMid[1].y,P2D.edgeMid[2].x,P2D.edgeMid[2].y,
        //     colorP,deepNow);
        // _2 _0
        // deepNow = (P_virtual.edgeMid[2].z + P_virtual.edgeMid[0].z) / 2.f;
        // ScreenDemo::line2ScreenBuffer_(ScreenEye,P2D.edgeMid[2].x,P2D.edgeMid[2].y,P2D.edgeMid[0].x,P2D.edgeMid[0].y,
        //     colorP,deepNow);
    }
    if (showGrid)
    for (int i=0;i<Grid2D.size();i++) {

        ScreenEye->putPixel_(Grid2D[i].x,Grid2D[i].y,colorGrid,Grid_virtual[i].z,this);
    }

    if (debugMode==1) {
        float _color_[3];

        // println("showBox");
        _color_[0] = 1.0f;
        _color_[1] = 1.0f;
        _color_[2] = 1.0f; // 白色
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.ltnSet.x, scanBox2D_.ltnSet.y,
                                      scanBox2D_.rtnSet.x, scanBox2D_.rtnSet.y,
                                      _color_, virtual_scanBox3D.center.z);// 前框
        // println("ltn:{},rtn:{}",
        //     showVec2(scanBox2D_.ltnSet),showVec2(scanBox2D_.rtnSet));
        // println("box center z:{}",virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rtnSet.x, scanBox2D_.rtnSet.y,
                                      scanBox2D_.rbnSet.x, scanBox2D_.rbnSet.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rbnSet.x, scanBox2D_.rbnSet.y,
                                      scanBox2D_.lbnSet.x, scanBox2D_.lbnSet.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.lbnSet.x, scanBox2D_.lbnSet.y,
                                      scanBox2D_.ltnSet.x, scanBox2D_.ltnSet.y,
                                      _color_, virtual_scanBox3D.center.z);

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.ltfSet.x, scanBox2D_.ltfSet.y,
                                      scanBox2D_.rtfSet.x, scanBox2D_.rtfSet.y,
                                      _color_, virtual_scanBox3D.center.z);// 后框
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rtfSet.x, scanBox2D_.rtfSet.y,
                                      scanBox2D_.rbfSet.x, scanBox2D_.rbfSet.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rbfSet.x, scanBox2D_.rbfSet.y,
                                      scanBox2D_.lbfSet.x, scanBox2D_.lbfSet.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.lbfSet.x, scanBox2D_.lbfSet.y,
                                      scanBox2D_.ltfSet.x, scanBox2D_.ltfSet.y,
                                      _color_, virtual_scanBox3D.center.z);

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.ltnSet.x, scanBox2D_.ltnSet.y,
                                      scanBox2D_.ltfSet.x, scanBox2D_.ltfSet.y,
                                      _color_, virtual_scanBox3D.center.z);// 前后连
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rtnSet.x, scanBox2D_.rtnSet.y,
                                      scanBox2D_.rtfSet.x, scanBox2D_.rtfSet.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rbnSet.x, scanBox2D_.rbnSet.y,
                                      scanBox2D_.rbfSet.x, scanBox2D_.rbfSet.y,
                                      _color_, virtual_scanBox3D.center.z);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.lbnSet.x, scanBox2D_.lbnSet.y,
                                      scanBox2D_.lbfSet.x, scanBox2D_.lbfSet.y,
                                      _color_, virtual_scanBox3D.center.z);

DEBUG_SECTION(
        if (flatLeftFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.rtn_ltn_tip.x, scanBox2D_.rtn_ltn_tip.y,
                                          scanBox2D_.ltnSet.x, scanBox2D_.ltnSet.y,
                                          _color_, virtual_scanBox3D.center.z);


        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.rtn_ltn_tip.x, scanBox2D_.rtn_ltn_tip.y,
                                          scanBox2D_.ltnSet.x, scanBox2D_.ltnSet.y,
                                          _color_, virtual_scanBox3D.center.z);

        }
        if (flatTopFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.lbn_ltn_tip.x, scanBox2D_.lbn_ltn_tip.y,
                                          scanBox2D_.ltnSet.x, scanBox2D_.ltnSet.y,
                                          _color_, virtual_scanBox3D.center.z);

        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.lbn_ltn_tip.x, scanBox2D_.lbn_ltn_tip.y,
                                          scanBox2D_.ltnSet.x, scanBox2D_.ltnSet.y,
                                          _color_, virtual_scanBox3D.center.z);

        }
        if (flatFrontFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.ltf_ltn_tip.x, scanBox2D_.ltf_ltn_tip.y,
                                          scanBox2D_.ltnSet.x, scanBox2D_.ltnSet.y,
                                          _color_, virtual_scanBox3D.center.z);
        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.ltf_ltn_tip.x, scanBox2D_.ltf_ltn_tip.y,
                                          scanBox2D_.ltnSet.x, scanBox2D_.ltnSet.y,
                                          _color_, virtual_scanBox3D.center.z);

        }
        if (flatRightFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.lbf_rbf_tip.x, scanBox2D_.lbf_rbf_tip.y,
                                          scanBox2D_.rbfSet.x, scanBox2D_.rbfSet.y,
                                          _color_, virtual_scanBox3D.center.z);
        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.lbf_rbf_tip.x, scanBox2D_.lbf_rbf_tip.y,
                                          scanBox2D_.rbfSet.x, scanBox2D_.rbfSet.y,
                                          _color_, virtual_scanBox3D.center.z);

        }
        if (flatBottomFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.rtf_rbf_tip.x, scanBox2D_.rtf_rbf_tip.y,
                                          scanBox2D_.rbfSet.x, scanBox2D_.rbfSet.y,
                                          _color_, virtual_scanBox3D.center.z);
        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.rtf_rbf_tip.x, scanBox2D_.rtf_rbf_tip.y,
                                          scanBox2D_.rbfSet.x, scanBox2D_.rbfSet.y,
                                          _color_, virtual_scanBox3D.center.z);

        }

        if (flatBackFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.rbn_rbf_tip.x, scanBox2D_.rbn_rbf_tip.y,
                                          scanBox2D_.rbfSet.x, scanBox2D_.rbfSet.y,
                                          _color_, virtual_scanBox3D.center.z);
        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D_.rbn_rbf_tip.x, scanBox2D_.rbn_rbf_tip.y,
                                          scanBox2D_.rbfSet.x, scanBox2D_.rbfSet.y,
                                          _color_, virtual_scanBox3D.center.z);
        }
)

    }


    renderNext = 1; // 慢改真
}

void Bezier22Edge3::solidRectangle2D(ScreenDemo* ScreenEye){
    size_t triangleHave = triangles.size();
    for(int i=0;i<triangleHave-1;i++) {

        triangles[i].freshLineBoundary_triangle(Grid2D);

        triangles[i].draw2Triangle(ScreenEye,this);

    }
    size_t triangleLastHave = triangleLast.size();
    for(int i=0;i<triangleLastHave;i++) {
        triangleLast[i].freshLineBoundary_triangle(Grid2D);
        triangleLast[i].draw2Triangle(ScreenEye,this);
    }
}
auto cross_xy = [](const glm::dvec3& A, const goLine64& B) -> float {
    return A.x * B.dy - A.y * B.dx;
};
auto cross_yz = [](const glm::dvec3& A, const goLine64& B) -> float {
    return A.y * B.dz - A.z * B.dy;
};
auto cross_zx = [](const glm::dvec3& A, const goLine64& B) -> double {
    return A.x * B.dz - A.z * B.dx;
};
void Bezier22Edge3::computeTriQuadFromVerts(
    float u, float v, float w, glm::vec3* Su, glm::vec3* Sv)
{
    // === 基函数值 (二次三角形Bezier) ===
    // float B_a   = u * u;      // B200
    // float B_b   = v * v;      // B020
    // float B_c   = w * w;      // B002
    // float B_ab  = 2.0f * u * v; // B110
    // float B_bc  = 2.0f * v * w; // B011
    // float B_ca  = 2.0f * u * w; // B101

    // === ∂B/∂u (链式法则: ∂w/∂u = -1) ===
    float dB_a_du  = 2.0f * u;
    float dB_b_du  = 0.0f;
    float dB_c_du  = -2.0f * w;        // ∂(w²)/∂u = 2w * (-1)
    float dB_ab_du = 2.0f * v;
    float dB_bc_du = -2.0f * v;        // ∂(2vw)/∂u = 2v*(-1)
    float dB_ca_du = 2.0f * (w - u);   // ∂(2uw)/∂u = 2w + 2u*(-1) = 2(w-u)

    // === ∂B/∂v (链式法则: ∂w/∂v = -1) ===
    float dB_a_dv  = 0.0f;
    float dB_b_dv  = 2.0f * v;
    float dB_c_dv  = -2.0f * w;        // ∂(w²)/∂v = 2w * (-1)
    float dB_ab_dv = 2.0f * u;
    float dB_bc_dv = 2.0f * (w - v);   // ∂(2vw)/∂v = 2w + 2v*(-1) = 2(w-v)
    float dB_ca_dv = -2.0f * u;        // ∂(2uw)/∂v = 2u*(-1)

    // 初始化
    // *S  = glm::vec3(0.0f);
    *Su = glm::vec3(0.0f);
    *Sv = glm::vec3(0.0f);

    // 累加顶点贡献
    // *S  += B_a  * P_virtual.tip[0];
    // *S  += B_b  * P_virtual.tip[1];
    // *S  += B_c  * P_virtual.tip[2];
    *Su += dB_a_du  * P_virtual.tip[0];   *Sv += dB_a_dv  * P_virtual.tip[0];
    *Su += dB_b_du  * P_virtual.tip[1];   *Sv += dB_b_dv  * P_virtual.tip[1];
    *Su += dB_c_du  * P_virtual.tip[2];   *Sv += dB_c_dv  * P_virtual.tip[2];

    // 累加边中点贡献
    // *S  += B_ab * P_virtual.edgeMid[0];
    // *S  += B_bc * P_virtual.edgeMid[1];
    // *S  += B_ca * P_virtual.edgeMid[2];
    *Su += dB_ab_du * P_virtual.edgeMid[0];  *Sv += dB_ab_dv * P_virtual.edgeMid[0];
    *Su += dB_bc_du * P_virtual.edgeMid[1];  *Sv += dB_bc_dv * P_virtual.edgeMid[1];
    *Su += dB_ca_du * P_virtual.edgeMid[2];  *Sv += dB_ca_dv * P_virtual.edgeMid[2];
}


array<double,5> Bezier22Edge3::getRayCoefficients_u_screenAxis(goLine64& rayDir) {
    // DEBUG_SECTION(
    // if (abs(
    //     glm::sqrt(glm::dot(rayDir._,rayDir._))
    //      - 1) > 1e-4) {
    //     println(stderr,"双二次三边曲 ray dir不够归一化:({},{},{})",
    //         rayDir.dx,rayDir.dy,rayDir.dz);
    // }
    // )
    // --- 1. 确定最佳投影平面 ---
    // 选择射线方向向量中绝对值最小的分量，避免该分量作为叉积方程的主导因子
    double absDx = std::abs(rayDir.dx);
    double absDy = std::abs(rayDir.dy);
    double absDz = std::abs(rayDir.dz);

    // 定义一个 epsilon 用于判断“接近于0”
    const double kEpsilon = 1e-6;

    // 根据最接近0的分量，选择要使用的两个叉积项
    enum class ProjectionType { XY_XZ, XY_YZ, XZ_YZ };
    ProjectionType projType; // ---- 解决屏幕正中一行 无像素的情况-----

    if (absDx < kEpsilon) {
        projType = ProjectionType::XY_YZ; // 用 YZ 和 XZ (即 ZX) 方程
    } else if (absDy < kEpsilon) {
        projType = ProjectionType::XY_XZ; // 用 XY 和 XZ (即 ZX) 方程
    } else if (absDz < kEpsilon) {
        projType = ProjectionType::XZ_YZ; // 用 XZ (即 ZX) 和 YZ 方程
    } else {
        // 一般情况，所有分量都不接近0，沿用原方案
        projType = ProjectionType::XY_YZ;
    }

    // 解包控制点 (P_ijk)
    const glm::dvec3 tipA = P_virtual.tip[0]; // u^2
    const glm::dvec3 tipB = P_virtual.tip[1]; // v^2
    const glm::dvec3 tipC = P_virtual.tip[2]; // w^2 (常量基)

    const glm::dvec3 midAB = P_virtual.edgeMid[0]; // uv
    const glm::dvec3 midBC = P_virtual.edgeMid[1]; // vw
    const glm::dvec3 midCA = P_virtual.edgeMid[2]; // uw
    // println("tip a:{}",showVec3(const_cast<glm::vec3&>(tipA)));
    // println("tip b:{}",showVec3(const_cast<glm::vec3&>(tipB)));
    // println("tip c:{}",showVec3(const_cast<glm::vec3&>(tipC)));
    // println("edge ab:{}",showVec3(const_cast<glm::vec3&>(midAB)));
    // println("edge bc:{}",showVec3(const_cast<glm::vec3&>(midBC)));
    // println("edge ca:{}",showVec3(const_cast<glm::vec3&>(midCA)));

    // 将曲面表示为 S(u,v) = P0 + u*Pu + v*Pv + u^2*Puu + v^2*Pvv + uv*Puv
    // 其中 w = 1-u-v
    const glm::dvec3 P0  = tipC;
    const glm::dvec3 Pu  = 2.0 * (midCA - tipC);
    const glm::dvec3 Pv  = 2.0 * (midBC - tipC);
    const glm::dvec3 Puu = tipA - 2.0*midCA + tipC;
    const glm::dvec3 Pvv = tipB - 2.0*midBC + tipC;
    const glm::dvec3 Puv = 2.0 * (midAB - midCA - midBC + tipC);

    // const float dx = rayDir.x, dy = rayDir.y, dz = rayDir.z;

    // 辅助 lambda：计算向量叉积的特定分量 (A x B)_k
    // 我们只需要两个独立方程来消去 t，这里选择 xy 和 yz 平面投影

    // auto cross_zx = [](const glm::vec3& A, const glm::vec3& B) -> float {
    //     return A.z * B.x - A.x * B.z;
    // };

    // 若 rayDir 平行于某轴导致退化，应检测并切换投影面。此处假设一般情况。

    // 构建关于 v 的两个二次方程（系数是关于 u 的多项式）
    // Eq1: (S(u,v) - eye) × rayDir 的 x分量 = 0  (使用 yz 叉积? 不，用 xy 和 yz 确保独立)
    // 实际上 (S-eye) × rayDir = 0 给出两个独立标量方程（3选2）


    // --- 3. 根据投影类型构建方程 ---
    // 方程1: (S - eye) × rayDir 的第一个选定分量
    // 方程2: (S - eye) × rayDir 的第二个选定分量
    double A1, B1_1, B1_0, C1_2, C1_1, C1_0; // Eq1 coefficients
    double A2, B2_1, B2_0, C2_2, C2_1, C2_0; // Eq2 coefficients
    switch (projType) {
        case ProjectionType::XY_YZ: {
            // Eq1: xy (xz) plane -> z component of cross product
            // (S_y - ey)*dx - (S_x - ex)*dy = 0
            A1 = cross_xy(Pvv, rayDir); // This is (Pvv.y * d.x - Pvv.x * d.y), corresponds to v^2 term
            B1_1 = cross_xy(Puv, rayDir);
            B1_0 = cross_xy(Pv, rayDir);
            C1_2 = cross_xy(Puu, rayDir);
            C1_1 = cross_xy(Pu, rayDir);
            C1_0 = cross_xy(P0 - startEye64, rayDir);

            // Eq2: yz (yx) plane -> x component of cross product
            // (S_z - ez)*dy - (S_y - ey)*dz = 0
            A2 = cross_yz(Pvv, rayDir); // This is (Pvv.z * d.y - Pvv.y * d.z)
            B2_1 = cross_yz(Puv, rayDir);
            B2_0 = cross_yz(Pv, rayDir);
            C2_2 = cross_yz(Puu, rayDir);
            C2_1 = cross_yz(Pu, rayDir);
            C2_0 = cross_yz(P0 - startEye64, rayDir);
            break;
        }
        case ProjectionType::XY_XZ: {
            // Eq1: xy (xz) plane -> z component
            A1 = cross_xy(Pvv, rayDir);
            B1_1 = cross_xy(Puv, rayDir);
            B1_0 = cross_xy(Pv, rayDir);
            C1_2 = cross_xy(Puu, rayDir);
            C1_1 = cross_xy(Pu, rayDir);
            C1_0 = cross_xy(P0 - startEye64, rayDir);

            // Eq2: xz (zy) plane -> y component
            // (S_x - ex)*dz - (S_z - ez)*dx = 0
            // We need a function for (A.x * B.z - A.z * B.x)

            A2 = cross_zx(Pvv, rayDir);
            B2_1 = cross_zx(Puv, rayDir);
            B2_0 = cross_zx(Pv, rayDir);
            C2_2 = cross_zx(Puu, rayDir);
            C2_1 = cross_zx(Pu, rayDir);
            C2_0 = cross_zx(P0 - startEye64, rayDir);
            break;
        }
        case ProjectionType::XZ_YZ: {
            // We need functions for zx and yz projections


            // Eq1: xz (zy) plane -> y component
            A1 = cross_zx(Pvv, rayDir);
            B1_1 = cross_zx(Puv, rayDir);
            B1_0 = cross_zx(Pv, rayDir);
            C1_2 = cross_zx(Puu, rayDir);
            C1_1 = cross_zx(Pu, rayDir);
            C1_0 = cross_zx(P0 - startEye64, rayDir);

            // Eq2: yz (yx) plane -> x component
            A2 = cross_yz(Pvv, rayDir);
            B2_1 = cross_yz(Puv, rayDir);
            B2_0 = cross_yz(Pv, rayDir);
            C2_2 = cross_yz(Puu, rayDir);
            C2_1 = cross_yz(Pu, rayDir);
            C2_0 = cross_yz(P0 - startEye64, rayDir);
            break;
        }
    }
    /*
    // 方程1 (xy): (S_x - ex)*dy - (S_y - ey)*dx = 0
    // 整理为: A1*v^2 + B1*v + C1 = 0
    const double A1 = cross_xy(Pvv, rayDir);                 // v^2 系数
    const double B1_1 = cross_xy(Puv, rayDir);               // u*v 系数 (乘以 u)
    const double B1_0 = cross_xy(Pv, rayDir);                // v 常数系数
    const double C1_2 = cross_xy(Puu, rayDir);               // u^2 系数
    const double C1_1 = cross_xy(Pu, rayDir);                // u 系数
    const double C1_0 = cross_xy(P0 - startEye64, rayDir);          // 常数项

    // 方程2 (yz): (S_y - ey)*dz - (S_z - ez)*dy = 0
    const double A2 = cross_yz(Pvv, rayDir);
    const double B2_1 = cross_yz(Puv, rayDir);
    const double B2_0 = cross_yz(Pv, rayDir);
    const double C2_2 = cross_yz(Puu, rayDir);
    const double C2_1 = cross_yz(Pu, rayDir);
    const double C2_0 = cross_yz(P0 - startEye64, rayDir);
    */


    // 现在我们有：
    // Eq1: A1*v^2 + (B1_1*u + B1_0)*v + (C1_2*u^2 + C1_1*u + C1_0) = 0
    // Eq2: A2*v^2 + (B2_1*u + B2_0)*v + (C2_2*u^2 + C2_1*u + C2_0) = 0

    // Sylvester 结式 Resultant = (A1*C2 - A2*C1)^2 - (A1*B2 - A2*B1)*(B1*C2 - B2*C1) = 0
    // 其中 A1,A2 是常数，B1,B2 是关于 u 的一次式，C1,C2 是关于 u 的二次式

    // 定义多项式（关于 u）:
    // P(u) = A1*C2 - A2*C1 = p2*u^2 + p1*u + p0  (二次)
    const double p2 = A1*C2_2 - A2*C1_2;
    const double p1 = A1*C2_1 - A2*C1_1;
    const double p0 = A1*C2_0 - A2*C1_0;

    // Q(u) = A1*B2 - A2*B1 = q1*u + q0  (一次)
    const double q1 = A1*B2_1 - A2*B1_1;
    const double q0 = A1*B2_0 - A2*B1_0;

    // R(u) = B1*C2 - B2*C1 = r3*u^3 + r2*u^2 + r1*u + r0  (三次)
    // B1 = B1_1*u + B1_0, B2 = B2_1*u + B2_0
    // C1 = C1_2*u^2 + C1_1*u + C1_0, C2 = C2_2*u^2 + C2_1*u + C2_0

    // 展开 B1*C2:
    // (B1_1*u + B1_0)*(C2_2*u^2 + C2_1*u + C2_0)
    // = B1_1*C2_2*u^3 + (B1_1*C2_1 + B1_0*C2_2)*u^2 + (B1_1*C2_0 + B1_0*C2_1)*u + B1_0*C2_0

    const double r3 = B1_1*C2_2 - B2_1*C1_2;
    const double r2 = B1_1*C2_1 + B1_0*C2_2 - (B2_1*C1_1 + B2_0*C1_2);
    const double r1 = B1_1*C2_0 + B1_0*C2_1 - (B2_1*C1_0 + B2_0*C1_1);
    const double r0 = B1_0*C2_0 - B2_0*C1_0;

    // Resultant(u) = P(u)^2 - Q(u)*R(u) = 0
    // P^2 系数:
    // u^4: p2*p2
    // u^3: 2*p2*p1
    // u^2: 2*p2*p0 + p1*p1
    // u^1: 2*p1*p0
    // u^0: p0*p0

    // Q*R 系数:
    // u^4: q1*r3
    // u^3: q1*r2 + q0*r3
    // u^2: q1*r1 + q0*r2
    // u^1: q1*r0 + q0*r1
    // u^0: q0*r0

    array<double, 5> coeff;
    coeff[0] = p2*p2 - q1*r3;                                    // u^4
    coeff[1] = 2.0*p2*p1 - (q1*r2 + q0*r3);                     // u^3
    coeff[2] = 2.0*p2*p0 + p1*p1 - (q1*r1 + q0*r2);           // u^2
    coeff[3] = 2.0*p1*p0 - (q1*r0 + q0*r1);                     // u^1
    coeff[4] = p0*p0 - q0*r0;                                    // u^0

// #ifdef DEBUG_ON
//     bool solveBoth = false;
//     array<complex<double>,4> complexResBefore,complexResAfter;
//     array<double,4> testUall = solveEquation_4_u_(coeff,complexResBefore);
//     double testUbefore,testUafter;
//
//     if (testUall[0] != -1.0) {
//         solveBoth = true;
//         testUbefore = testUall[0];
//     }
//
// #endif
    DEBUG_SECTION(
    bool showAfter=false;
    )
    if (coeff[0]>-0.01&&coeff[0]<0.01) {
        if (coeff[0]==0.0) {

            coeff[0]=1e-12;

        }

        DEBUG_SECTION(
            showAfter=true;
            println(stderr,"1首系数小 u4:{},u3:{},u2:{},u1:{},u0:{}",
                 coeff[0],coeff[1],coeff[2],coeff[3],coeff[4]);
)
    }
        // coeff[1] = coeff[1] / coeff[0];
        // coeff[2] = coeff[2] / coeff[0];
        // coeff[3] = coeff[3] / coeff[0];
        // coeff[4] = coeff[4] / coeff[0];
        // coeff[0] = 1.f;
        // 1. 找出非零系数中绝对值最大的
        double maxAbs = 0.0;
        for (int i = 0; i < 5; ++i) {
            if (coeff[i] != 0.0) {
                maxAbs = std::max(maxAbs, std::fabs(coeff[i]));
            }
        }
        int exp,scaleExp;
        if (maxAbs == 0.0) {
            println(stderr,"方程系数 不可救!!");
            goto unable2change; // 全零，退化
        }
        // 2. 计算需要缩放的倍数：让 maxAbs ≈ 1.0
        // 使用 frexp 分解：maxAbs = mantissa * 2^exp, mantissa ∈ [0.5, 1)

        std::frexp(maxAbs, &exp); // exp 是满足 maxAbs < 2^exp 的最小整数

        // 3. 缩放因子 = 2^(-exp + 1)，使得缩放后 maxAbs ∈ [1, 2)
        scaleExp = -exp + 1;

        // 4. 对每个系数应用 ldexp(x, scaleExp) == x * 2^scaleExp
        for (int i = 0; i < 5; ++i) {
            coeff[i] = std::ldexp(coeff[i], scaleExp);
        }
// DEBUG_SECTION(
//     testUall = solveEquation_4_u_(coeff,complexResAfter);
//
//     if (testUall[0] != -1.0 && solveBoth) {
//         testUafter = testUall[0];
//         if (abs(testUbefore-testUafter) > 0.001) {
//         println("testU before:{}≠after:{}",testUbefore,testUafter);
//             println("before:");
//             for (int i=0;i<4;++i) {
//                 println("x{}: {}+{}i",i,
//                     complexResBefore[i].real(),complexResBefore[i].imag());
//             }
//             println("after:");
//             for (int i=0;i<4;++i) {
//                 println("x{}: {}+{}i",i,
//                     complexResAfter[i].real(),complexResAfter[i].imag());
//             }
//         }
//     }
// )
        unable2change:
    DEBUG_SECTION(
        if (showAfter)
        println(stderr,"2首系数小 u4:{},u3:{},u2:{},u1:{},u0:{}",
             coeff[0],coeff[1],coeff[2],coeff[3],coeff[4]);
        )


        return coeff;

}
auto safe_divide =
        [](complex<double> num, complex<double> den) {
            if (std::abs(den) < 1e-12) return num / 1e-12; // 除以0 改为极小值
            return num / den;
};
[[nodiscard]]array<double, 4> Bezier22Edge3::solveEquation_4_u(array<double, 5>& src) {
    // if (src[0]==0.f) {
    //     DEBUG_SECTION(
    //         println(stderr,"u4{}==0",src[0]);
    //         println(stderr,"u3:{},u2:{},u1:{},u0:{}",
    //             src[1],src[2],src[3],src[4]);
    //         )
    //     src[0]==1e-12f;
    // }

    // Step 1: 构造 Eigen 多项式系数（常数项在前！）
    Eigen::VectorXd coeffs(5);
    coeffs << src[4],  // u⁰
                src[3],  // u¹
                src[2],  // u²
                src[1],  // u³
                src[0];  // u⁴

    // Step 2: 创建求解器
    Eigen::PolynomialSolver<double, 4> solver;
    solver.compute(coeffs);

    std::vector<double> real_roots;
    // Step 3: 获取所有根（共 4 个）
    //const Eigen::Matrix<complex<double>, 4, 1> &roots = solver.roots();
    solver.realRoots(real_roots,1e-5);


    array<double, 4> resultU = {-1,-1,-1,-1};
    // std::expected<double,char> resNow;
    int cntOK = 0;
    for (std::vector<double>::iterator it = real_roots.begin(); it != real_roots.end(); ++it) {
        double r = *it;
        DEBUG_SECTION(
        if (isnan( r)) {
            println(stderr,"nan! u:{}",r);
        }
        )
        if (uvw_InRange01(r)) {
            resultU[cntOK++] = r;
        }
    }
    return resultU;
}
[[nodiscard]]
array<double, 4> Bezier22Edge3::solveEquation_4_u_(array<double, 5>& src,array<complex<double>, 4>& complexRes) {
    // if (src[0]==0.f) {
    //     DEBUG_SECTION(
    //         println(stderr,"u4{}==0",src[0]);
    //         println(stderr,"u3:{},u2:{},u1:{},u0:{}",
    //             src[1],src[2],src[3],src[4]);
    //         )
    //     src[0]==1e-12f;
    // }
    // Step 1: 构造 Eigen 多项式系数（常数项在前！）
    Eigen::VectorXd coeffs(5);
    coeffs << src[4],  // u⁰
                src[3],  // u¹
                src[2],  // u²
                src[1],  // u³
                src[0];  // u⁴

    // Step 2: 创建求解器
    Eigen::PolynomialSolver<double, 4> solver;
    solver.compute(coeffs);

    // Step 3: 获取所有根（共 4 个）
    const Eigen::Matrix<complex<double>, 4, 1> &roots = solver.roots();


    complexRes[0] = roots(0);
    complexRes[1] = roots(1);
    complexRes[2] = roots(2);
    complexRes[3] = roots(3);

    array<double, 4> resultU = {-1,-1,-1,-1};
    std::expected<double,char> resNow;
    int cntOK = 0;
    for (int i = 0; i < 4; ++i) {
        const std::complex<double>& r = roots(i);
        DEBUG_SECTION(
        if (is_complex_nan(r)) {
            println(stderr,"nan! u:{}+{}i",r.real(),r.imag());
        }
        )
        resNow = isResultUOK(r);
        if (resNow) {
            resultU[cntOK++] = *resNow;
        }
    }
    return resultU;
}
const double EPSILON1 = 1e-6;
std::expected<double,char> Bezier22Edge3::isResultUOK(complex<double> num) {
    if (num.imag() < -EPSILON1 || num.imag() > EPSILON1) {
        // 误差过大 非实数
        return std::unexpected(0);
    }
    if (!uvw_InRange01(num.real())) {
        // u不在范围
        return std::unexpected(0);
    }
    return num.real();
}
array<double,3> Bezier22Edge3::getCoefficients_v_screenAxis(goLine32& rayDir,double u) {
    glm::dvec3 P200 = P_virtual.tip[0];
    glm::dvec3 P020 = P_virtual.tip[1];
    glm::dvec3 P002 = P_virtual.tip[2];
    glm::dvec3 P110 = P_virtual.edgeMid[0];
    glm::dvec3 P011 = P_virtual.edgeMid[1];
    glm::dvec3 P101 = P_virtual.edgeMid[2];

    double W0 = 1.0 - u; // since w = W0 - v

    // Expand S(v) = K2*v^2 + K1*v + K0
    glm::dvec3 K2 = P020 + P002 - 2.0 * P011;
    glm::dvec3 K1 = -2.0 * P002 * W0 + 2.0 * P011 * W0 - 2.0 * P101 * u + 2.0 * P110 * u;
    glm::dvec3 K0 = P200 * u * u + P002 * W0 * W0 + 2.0 * P101 * u * W0;


    // Now: S(v) = K2*v^2 + K1*v + K0
    glm::vec3 D = K0 - startEye64;

    // Use XY component of cross(S(v) - eye, rayDir) = 0
    double dx = rayDir.dx, dy = rayDir.dy;
    double a = K2.x * dy - K2.y * dx;
    double b = K1.x * dy - K1.y * dx;
    double c = D.x   * dy - D.y   * dx;

    // DEBUG_SECTION(
    //     // if (isnan(u)) {
    //     //     println("u is nan:{}",u);
    //     // }
    //
    //     if (isnan(K2.x) || isnan(K2.y) || isnan(K2.z)) {
    //         println("k2 nan:{}",showVec3(K2));
    //     }
    //     if (isnan(K1.x) || isnan(K1.y) || isnan(K1.z)) {
    //         println("k1 nan:{}",showVec3(K1));
    //     }
    //     if (isnan(K0.x) || isnan(K0.y) || isnan(K0.z)) {
    //         println("k0 nan:{}",showVec3(K0));
    //     }
    //
    //     )

    return {a,b,c};
}
[[nodiscard]]
std::expected<array<double,2>,char> Bezier22Edge3::solveEquation_2_v(array<double,3>& coeffics) {
    double a = coeffics[0],b = coeffics[1],c = coeffics[2];

        if (a==0.0) {
        DEBUG_SECTION(
            println(stderr,"bezier223!! a:{} == 0",a);
            println(stderr,"b:{},c:{}",b,c);
            )
            if (b!=0.0) {
                return std::unexpected(1);//array{-c/b,-c/b};
            }
            // a b 都是 0.0
                return std::unexpected(0);

        }


    double discriminant = b*b - 4*a*c;
    if (discriminant<0.f) {
        return std::unexpected(0);
    }
    double res1 = (-b+glm::sqrt(discriminant))/(2*a);
    double res2 = (-b-glm::sqrt(discriminant))/(2*a);
    // 两个解刚好相等 可能性很小
    return array{res1,res2};
}
bool Bezier22Edge3::uvw_InRange01(double num) {
    // println("input v:{}",num);
    if (num > uvwRange[0]-EPSILON1 && num < uvwRange[1]+EPSILON1) {
        // v在范围
        // println("good v:{}",num);
        return true;
    }
    return false;
}
double Bezier22Edge3::len2Eye_22_screenAxis(glm::dvec3& surfaceP) {
    glm::dvec3 toEye = startEye64 - surfaceP;
    return glm::dot(toEye,toEye);
}
bool Bezier22Edge3::checkRealU(array<double,5>& coefficients,double u) {
    double result = pow4(u)*coefficients[0] +
        pow3(u)*coefficients[1] +
            pow2(u)*coefficients[2] +
                u*coefficients[3] +
                    u*coefficients[4];
    if (abs(result) > 1e-4) {

        print(stderr,"u={}\n  ({})u⁴+({})u³+({})u²+({})u+({})=",u,
            coefficients[0],coefficients[1],coefficients[2],coefficients[3],coefficients[4]);
        println(stderr,"{}≠0",result);
        return false;
    }
    return true;
}
std::expected<oneUVWInfo,char> Bezier22Edge3::getBestSolve_UVW(goLine32& rayDir) {
    if (abs(rayDir.dy) < 1e-6) {
        rayDir.dy = 1e-6;
        // println("~~~~raydir:{}",showVec3(rayDir._));
        // println("~~~~dy ≈ 0");

    }

    goLine64 rayDir64 = {rayDir.dx, rayDir.dy, rayDir.dz};
    vector<oneUVWInfo> resUVW;
    oneUVWInfo resNow;
    // 解 u
    array<double, 5> coeeficsU = getRayCoefficients_u_screenAxis(rayDir64);
    // println("{}x⁴+{}x³+{}x²+{}x+{}",
    //     coeeficsU[0],coeeficsU[1],coeeficsU[2],coeeficsU[3],coeeficsU[4]);
    array<double, 4> resU = solveEquation_4_u(coeeficsU);
    // 验 u
    // 解 v
    double v0, v1,w;
    for (double u : resU) {
        if (u==-1)continue;
        //println("correct U:{}",u);
        array<double, 3> coefficsV = getCoefficients_v_screenAxis(rayDir,u);
         // println("{}x²+{}x+{}",
         //     coefficsV[0],coefficsV[1],coefficsV[2]);
        std::expected<array<double, 2>, char> resV = solveEquation_2_v(coefficsV);

        // 跟判别式 > 0
        if (resV) {
            //println("vo:{},v1:{}",(*resV)[0],(*resV)[1]);
            v0 = (*resV)[0];
            if (uvw_InRange01(v0)) {
                w = 1-u-v0;
                if (uvw_InRange01(w)) {
                    resNow.uvw = {u,v0,w};
                //println("current v0 uvw:{}",showVec3(resNow.uvw));
                resUVW.emplace_back(resNow);
                }

            }
            v1 = (*resV)[1];

            if (uvw_InRange01(v1)) {
                w = 1-u-v1;
                if (uvw_InRange01(w)) {
                    resNow.uvw = {u,v1,w};
                    //println("current v1 uvw:{}",showVec3(resNow.uvw));
                    resUVW.emplace_back(resNow);
                }
            }
        }else if (resV.error() == 1){
            println(stderr,"!!罕见 a=0 b:{}≠0 c:{}, -c/b单解",coefficsV[1],coefficsV[2]);
            v1 = -coefficsV[2]/coefficsV[1]; // -c/b
            if (uvw_InRange01(v1)) {
                w = 1-u-v1;
                if (uvw_InRange01(w)) {
                    resNow.uvw = {u,v1,w};
                    //println("current v1 uvw:{}",showVec3(resNow.uvw));
                    resUVW.emplace_back(resNow);
                }
            }
        }
    }
    // 验 v
    // 解 w
    // 不超过4个解  找最近
    if (resUVW.empty())
        return std::unexpected(0);

    for (auto it = resUVW.begin();it != resUVW.end();) { // 补全 表面点 视线距离
        glm::vec3 surfacePos = evaluatePatch2_screenAxis(glm::vec3(it->uvw));


        goLine32 viewDir = glm::normalize(surfacePos - startEye);
        float rayNotSameAngle = PolygonBase::angleBetweenVectors_deg(viewDir._, rayDir._);
        float errRange = surfacePos.z > -100.f ? 0.02f : 0.04f;
        if (rayNotSameAngle > errRange) {

            // DEBUG_SECTION(
                //println(stderr,"× ray not same,angle error = {}",rayNotSameAngle);
                //checkRealU(coeeficsU,it->uvw[0]);
                // )

            it = resUVW.erase(it); // 是否为空
        }else {
            //println("√ ray not same,angle error = {}",rayNotSameAngle);
            it->surfaceP_screenAxis = surfacePos;
            ++it;
        }
    }
    // 🔥 新增：再次检查是否为空！
    if (resUVW.empty()) {
        return std::unexpected(1); // 可用不同错误码区分“无初解”和“全被剔除”
    }

    if (resUVW.size() == 1) {
        addVertical2uvwInfo(resUVW[0]);
        return resUVW[0];
    }
    for (oneUVWInfo& _uvw : resUVW) { // 补全 表面点 视线距离

        _uvw.far2Eye_22 = len2Eye_22_screenAxis(_uvw.surfaceP_screenAxis);

    }
    vector<oneUVWInfo>::iterator
    resultItem = min_element(resUVW.begin(), resUVW.end(),
[](const oneUVWInfo &a, const oneUVWInfo &b)-> bool {
                       return a.far2Eye_22 < b.far2Eye_22;
                   });

    addVertical2uvwInfo(*resultItem);
    return *resultItem;
}
void Bezier22Edge3::addVertical2uvwInfo(oneUVWInfo& _uvw) {
    glm::vec3 Su, Sv;//偏导数
    computeTriQuadFromVerts(_uvw.uvw[0], _uvw.uvw[1], _uvw.uvw[2],
         &Su, &Sv);

    glm::vec3 N = glm::cross(Su, Sv);
    float len2 = glm::dot(N, N);
    std::expected<goLine32,char>vertical;
    if (len2 > 1e-8f) {
        (*vertical)._ = glm::normalize(N);
        //println("法线:{}",showVec3((*vertical)._));
    }else {
        vertical = std::unexpected(0);
        println(stderr,"法线太短 无法归一化");
    }
    if (vertical) {
        *(_uvw.onFront) = PolygonBase::isFrontFacing(startEye,*vertical,
            _uvw.surfaceP_screenAxis);
        if (_uvw.onFront.value()==true) {
            //println("~~朝向正面");

        }else {
            //println("~~朝向反面");
        }
    }else {
        // 法线计算失败
        _uvw.onFront = std::unexpected(0);
    }
}
glm::vec3 Bezier22Edge3::getColorByUVW(const glm::vec3& _uvw) {
// if (!vInRange01(_uvw[0])) {
//     println(stderr,"u:{} out of 0~1",_uvw[0]);
// }
//     if (!vInRange01(_uvw[1])) {
//         println(stderr,"v:{} out of 0~1",_uvw[1]);
//     }
//     if (!vInRange01(_uvw[2])) {
//         println(stderr,"w:{} out of 0~1",_uvw[2]);
//     }
//----------------------------------------------
    int intervalU = static_cast<int>(_uvw[0] * resolutionf);
    int intervalV = static_cast<int>(_uvw[1] * resolutionf);
    int intervalW = static_cast<int>(_uvw[2] * resolutionf);
    int longIndex = intervalU + intervalV + intervalW;

    if (longIndex % 2!=0) {
        return colorP;
    }
    return colorGrid;
}

void Bezier22Edge3::_solidRectangle2D_(ScreenDemo* ScreenEye,glm::vec2& p1,glm::vec2& p2,glm::vec2& p3,glm::vec2& p4,
                                       vector<lineBoundary>& lineScanFillColor,vector<rowUVWInfo>& pixelEyeDeep,bool firstStop) {

    // 默认 0 ltn 1 rtn 2 rbn 3 lbn
    PolygonBase::fresh2D_scanRows_4(p1,p2,p3,p4, &lineScanFillColor,type_);


    if (firstStop) {
        pixelEyeDeep.clear();
        //println("rows count by box front side:{}",lineScanFillColor_front.size());
        for(auto& _linePosInfo : lineScanFillColor) {
            if(_linePosInfo.rx == _linePosInfo.lx){
                //            cerr << "球 lineScanFillColor.rx:" << _linePosInfo.rx <<
                //                 " = lineScanFillColor.lx:" << _linePosInfo.lx << endl;
                continue;
            }

            rowUVWInfo rowRenderInfo;
            rowRenderInfo.y = _linePosInfo.y; // 本行 y
            //        rowDeepInfo.pixelDeeps.clear(); // 本行 x deep 空
            for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){
                //            cout << "^^^nowX:" << nowX << " y:" << _linePosInfo.y << endl;
                //float deepFrontNow = getEyeDeepbyXY(nowX, _linePosInfo.y);

                goLine32 rayDir_screenAxis =
                ScreenDemo::get_AgoB_direction3D(startEye, {nowX, rowRenderInfo.y, 0.0f});
                std::expected<oneUVWInfo, char> nearestP = getBestSolve_UVW(rayDir_screenAxis);
                if (nearestP) {
                    //println("nearest point uvw:{}",showVec3(nearestP->uvw));
                    // 该视线有解
                    nearestP->x = nowX;
                    nearestP->color = getColorByUVW(glm::vec3(nearestP->uvw));
                    //println("nearest point color:{}",showVec3(nearestP->color));
                }

                rowRenderInfo.rowsInfo.push_back(nearestP); // 本行 x deep
            }

            pixelEyeDeep.push_back(rowRenderInfo);

        }
    }

//println("row got:{}",pixelEyeDeep_front.size());



    for(auto& _lineDeepInfo : pixelEyeDeep) {
        size_t vecSizeCurrent=_lineDeepInfo.rowsInfo.size();
        //println("col got:{}",vecSizeCurrent);
        for (int i = 0; i < vecSizeCurrent; i++) {
            // 该视线无解 黑区
            if (!_lineDeepInfo.rowsInfo[i])continue;

            int nowX = _lineDeepInfo.rowsInfo[i]->x;
            float nowDeep = _lineDeepInfo.rowsInfo[i]->surfaceP_screenAxis.z;
            // println("x:{},y:{}",nowX,_lineDeepInfo.y);
            // println("current deep:{}", nowDeep);
            // println("color:{}",showVec3(_lineDeepInfo.rowsInfo[i]->color));
            if (_lineDeepInfo.rowsInfo[i]->onFront.has_value()) {
                // println(stderr,"无法计算法线 未归一化 过短");
                if (*(_lineDeepInfo.rowsInfo[i]->onFront)) {
                //println("^^on front");

                    ScreenEye->putPixel_(nowX,_lineDeepInfo.y,
                        _lineDeepInfo.rowsInfo[i]->color,nowDeep,(PolygonBase*)this);

                } else {

                    ScreenEye->putPixel_(nowX,_lineDeepInfo.y,
                        backColor,nowDeep,(PolygonBase*)this);

                }
            }else { // 无法线 算反面
                ScreenEye->putPixel_(nowX,_lineDeepInfo.y,
                        backColor,nowDeep,(PolygonBase*)this);
            }

        }
    }


}
void Bezier22Edge3::moveFreshStatus() {
    renderNext = 0; // 快改假

    firstRendered_front = true;
    firstRendered_back = true;
    firstRendered_left = true;
    firstRendered_right = true;
    firstRendered_top = true;
    firstRendered_bottom = true;
}


