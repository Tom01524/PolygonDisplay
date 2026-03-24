//
// Created by iceoc0 on 2025/3/27.
//

#include "ScreenDemo.h"

#include <cassert>

struct modeScreen{
    char now;char a;char b;char d;
};
extern void* mode_ptr;
modeScreen mode_ = *static_cast<modeScreen *>(mode_ptr);

extern void* settled_ptr; // 全局设置的结构体指针
struct _settledScreen{
    int _width;
    int _height;
    int _deep;
    bool _byAxis;
};
_settledScreen* settled_ = (_settledScreen*)settled_ptr;
const int screenWidth11 = settled_-> _width;
const int screenHeight11 = settled_-> _height;
const int screenDeep11 = settled_-> _deep;
const float screenWidthF11 = static_cast<float>(screenWidth11);
const float screenHeightF11 =static_cast<float>(screenHeight11);
const float screenDeepF11 =  static_cast<float>(screenDeep11);

extern void* _3d_2d_go_void_ptr;
// struct _3d_2d_go_screen{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_ad)(ScreenDemo*, float, float, float);
// };
glm::vec2 (*__3d2dGoScreen)(ScreenDemo*, glm::vec3, glm::vec3*) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d_go;
[[maybe_unused]]
glm::vec2 (*__3d2dScreen)(ScreenDemo*, float, float, float) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d; // 模式1 用自己的不行



// malloc一个超级结构体 ScreenDemo
ScreenDemo::ScreenDemo(glm::vec3 _lt_xyz, glm::vec3 _rt_xyz, glm::vec3 _rb_xyz, glm::vec3 _lb_xyz,
                   glm::vec3 _center_xyz, glm::vec3 _centerTip_xyz, int _type)
{
//    if (std::isnan(_lt_xyz.y) || std::isnan(_lt_xyz.x) || std::isnan(_lt_xyz.z)) {
//        throw std::invalid_argument("Invalid parameter: NaN detected");
//    }
//    if (std::isinf(_lt_xyz.y) || std::isinf(_lt_xyz.x) || std::isinf(_lt_xyz.z)) {
//        throw std::invalid_argument("Invalid parameter: Infinity detected");
//    }

    _init_main(_lt_xyz, _rt_xyz, _rb_xyz, _lb_xyz, _center_xyz, _centerTip_xyz,_type);
}
void ScreenDemo::freshInfo(){
    //println("fresh info!");
    // 刷新 (世界axis)对于(屏幕axis self) 信息
    freshFrameRotateInfo(); // 两步斜转
    freshAxisWorldOnAxisScreen_quat();
//    needTurn = freshBackTurnInfo();
//    cout << "need turn:" << needTurn << endl;

    // if(debugLine==2){
    //     freshRectAxis(); // 更新坐标轴 info
    //     //drawCircleAxis(ScreenEye); // 画坐标轴
    // }
    //printf("lb点距屏幕%f\n",points2EyeBack.lbEye);
}
glm::vec3 ScreenDemo::getCenter() {
    return tblrXYZ.center;
}

glm::vec3 ScreenDemo::getCenterTip(){
    return tblrXYZ.centerTip;
}
glm::ivec2 ScreenDemo::pos2DbyIndex(int _index) {
    glm::ivec2 result;
    result.x = _index % static_cast<int>(rectWidth); // 除法取余
    result.y = _index / static_cast<int>(rectWidth); // 除法取整
    return result;
}
void ScreenDemo::line2ScreenBuffer(ScreenDemo* ScreenEye, float x0f, float y0f, float x1f, float y1f,
                                 float color[],float zDeep){
    if(zDeep + ScreenEye->rectDepth < 0.f)return; // 当前2D线 统一深度 在视点后 退出去

    vector<glm::vec2> _linePoints;
    int x0 = (int)roundf(x0f);
    int x1 = (int)roundf(x1f);
    int y0 = (int)roundf(y0f);
    int y1 = (int)roundf(y1f);
    PolygonBase::rasterLine(x0, y0, x1, y1,_linePoints);

    // glm::vec3 colorNow = {color[0],color[1],color[2]};
    for(glm::vec2 _pos : _linePoints){
        if(ScreenEye->outOfScreen(_pos.x,_pos.y))continue; // 屏幕外 退出去



#pragma omp critical
        if(zDeep < ScreenEye->zBuffer(_pos.y,_pos.x)){ // 有更浅的
            ScreenEye->coloredPixels(roundf(_pos.y),roundf(_pos.x)) = {color[0],color[1],color[2]}; // 设置颜色
            //cout << "设置color now (" << colorNow.r01 << ", " << colorNow.g01 << ", " << colorNow.b01 << ")" << endl;
            ScreenEye->zBuffer(_pos.y,_pos.x) = zDeep; // 设置深度
        }

    }

}
void ScreenDemo::line2ScreenBuffer_(ScreenDemo* ScreenEye, float x0f, float y0f, float x1f, float y1f,
                                 const glm::vec3& color,float zDeep) {
    if(zDeep + ScreenEye->rectDepth < 0.f)return; // 当前2D线 统一深度 在视点后 退出去

    vector<glm::vec2> _linePoints;
    int x0 = (int)roundf(x0f);
    int x1 = (int)roundf(x1f);
    int y0 = (int)roundf(y0f);
    int y1 = (int)roundf(y1f);
    PolygonBase::rasterLine(x0, y0, x1, y1,_linePoints);

    // glm::vec3 colorNow = {color[0],color[1],color[2]};
    for(glm::vec2 _pos : _linePoints){
        if(ScreenEye->outOfScreen(_pos.x,_pos.y))continue; // 屏幕外 退出去



#pragma omp critical
        if(zDeep < ScreenEye->zBuffer(_pos.y,_pos.x)){ // 有更浅的
            ScreenEye->coloredPixels(roundf(_pos.y),roundf(_pos.x)) = color; // 设置颜色
            //cout << "设置color now (" << colorNow.r01 << ", " << colorNow.g01 << ", " << colorNow.b01 << ")" << endl;
            ScreenEye->zBuffer(_pos.y,_pos.x) = zDeep; // 设置深度
        }

    }
}
void ScreenDemo::downLine2ScreenBuffer(ScreenDemo* ScreenEye, int xf, int y0f, int y1f,float color[]){
    int yMin = std::min(y0f,y1f);
    int yMax = std::max(y0f,y1f);
    for(int _y=yMin;_y<=yMax; ++_y){
        ScreenEye->putPixel2(xf,_y,color);
    }
}
void ScreenDemo::putPixel(int x, int y,float color[],float depth,PolygonBase* _this){
    // <= 排除 避免极值 !!!
    if(outOfScreen(x,y))return; // 屏幕外 退出去

    if(depth+rectDepth<0.0f)return; // 负深度 退出去


    float deepBefore = zBuffer(y,x);

#pragma omp critical
    if(depth < deepBefore){ // 更近
        coloredPixels(y,x) = glm::vec3(color[0],color[1],color[2]);
        zBuffer(y,x) = depth;


        if(objBufferFresh && _this!= nullptr){
            objBuffer(y,x) = _this;
        }

    }
}
void ScreenDemo::putPixel_(int x, int y,glm::vec3& color,float depth,PolygonBase* _this){
    // <= 排除 避免极值 !!!
    if(outOfScreen(x,y))return; // 屏幕外 退出去

    if(depth+rectDepth<0.0f)return; // 负深度 退出去


    float deepBefore = zBuffer(y,x);

#pragma omp critical
    if(depth < deepBefore){ // 更近
        coloredPixels(y,x) = color;
        zBuffer(y,x) = depth;


        if(objBufferFresh && _this!= nullptr){
            objBuffer(y,x) = _this;
        }

    }
}
void ScreenDemo::putPixel2(int x, int y,float color[]){
    if(outOfScreen(x,y))return; // 屏幕外 退出去

    // 不管深度 不管objPtr缓存

    //    float deepBefore = zBuffer[indexNow];
    coloredPixels(y,x) = glm::vec3(color[0],color[1],color[2]);
}
bool ScreenDemo::outOfScreen(float x, float y){
    if(x<0 || x>=screenWidthF11 || y<0 || y>=screenHeightF11)return true; // 屏幕外 退出去
    return false;
}
void ScreenDemo::flushBatchDraw() {

    size_t vecSize = screenWidth11 * screenHeight11;
    glm::vec3 colorNow;glm::ivec2 pos2D;
    glBegin(GL_POINTS);

    for(int i=0;i<vecSize; ++i){

        colorNow = coloredPixels.data[i];
        if(colorNow.r==0.f && colorNow.g==0.f && colorNow.b==0.f)continue;

        //        cout << "使用color now (" << colorNow.r01 << ", " << colorNow.g01 << ", " << colorNow.b01 << ")" << endl;
        glColor3f(colorNow.r,colorNow.g,colorNow.b); // 确认颜色
        pos2D = pos2DbyIndex(i);
        glVertex2i(pos2D.x,pos2D.y);
        //        cout << "使用now (" << pos2D.x << ", " << pos2D.y << ")" << endl;

    }
    glEnd();

    //    coloredPixels.resize(static_cast<int>(rectWidth * rectHeight));
    //    zBuffer.resize(static_cast<int>(rectWidth * rectHeight));
    //    objBuffer.resize(static_cast<int>(rectWidth * rectHeight));

    std::fill(coloredPixels.data.begin(), coloredPixels.data.end(), glm::vec3{0.f,0.f,0.f}); // 初始化为黑色
    std::fill(zBuffer.data.begin(), zBuffer.data.end(), 10000.f); // 初始化为 距离 一万
    if(this->objBufferFresh){
        std::fill(objBuffer.data.begin(), objBuffer.data.end(), nullptr); // 初始化为空指针
    }


}
void ScreenDemo::freshGoX(){
    screenOnWorld_toX = get_AgoB_direction3D(tblrXYZ.lt, tblrXYZ.rt);
}
void ScreenDemo::freshGoY(){
    screenOnWorld_toY = get_AgoB_direction3D(tblrXYZ.lt, tblrXYZ.lb);
}
void ScreenDemo::freshGoDEEP() {
    screenOnWorld_toDEEP = get_AgoB_direction3D(tblrXYZ.centerTip, tblrXYZ.center);
}
glm::vec3 ScreenDemo::goX(glm::vec3& _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * screenOnWorld_toX.dx;
    _srcXYZ.y = _srcXYZ.y + _move * screenOnWorld_toX.dy;
    _srcXYZ.z = _srcXYZ.z + _move * screenOnWorld_toX.dz;
    return _srcXYZ;
}
glm::vec3 ScreenDemo::goY(glm::vec3& _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * screenOnWorld_toY.dx;
    _srcXYZ.y = _srcXYZ.y + _move * screenOnWorld_toY.dy;
    _srcXYZ.z = _srcXYZ.z + _move * screenOnWorld_toY.dz;
    return _srcXYZ;
}
glm::vec3 ScreenDemo::goDEEP(glm::vec3& _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * screenOnWorld_toDEEP.dx;
    _srcXYZ.y = _srcXYZ.y + _move * screenOnWorld_toDEEP.dy;
    _srcXYZ.z = _srcXYZ.z + _move * screenOnWorld_toDEEP.dz;
    return _srcXYZ;
}
void ScreenDemo::drawRectAxis(ScreenDemo *ScreenEye) {

    drawTiltAxis(ScreenEye); // 画倾斜轴
    drawParallelAxis(ScreenEye); // 画平行轴
}
glm::vec3 ScreenDemo::worldXYZ2ScreenXYZ(glm::vec3 worldXYZ){
    // 世界坐标系 任一点 走反z轴 到 (屏幕)xy面 距离
    glm::vec3 screenXYZ;
    screenXYZ.z = world2ScreenXYZ_GetZ(worldXYZ);
    // 世界坐标系 任一点 走反z轴 到 (屏幕)xy面 距离
    screenXYZ.x = world2ScreenXYZ_Getx(worldXYZ);
    screenXYZ.y = world2ScreenXYZ_Gety(worldXYZ);
    return screenXYZ;
}
glm::vec3 ScreenDemo::worldXYZ2ScreenXYZ_AxisLock(glm::vec3 worldXYZ){
    glm::vec3 _then = axisWorldOnAxisScreen._0_0_0;
    //    cout << "input(" << worldXYZ.x <<
    //    ", " << worldXYZ.y << ",  " << worldXYZ.z << ")" << endl;

    _then.x = _then.x + axisWorldOnAxisScreen.toX.dx * worldXYZ.x;
    _then.y = _then.y + axisWorldOnAxisScreen.toX.dy * worldXYZ.x;
    _then.z = _then.z + axisWorldOnAxisScreen.toX.dz * worldXYZ.x;

    _then.x = _then.x + axisWorldOnAxisScreen.toY.dx * worldXYZ.y;
    _then.y = _then.y + axisWorldOnAxisScreen.toY.dy * worldXYZ.y;
    _then.z = _then.z + axisWorldOnAxisScreen.toY.dz * worldXYZ.y;

    _then.x = _then.x + axisWorldOnAxisScreen.toDEEP.dx * worldXYZ.z;
    _then.y = _then.y + axisWorldOnAxisScreen.toDEEP.dy * worldXYZ.z;
    _then.z = _then.z + axisWorldOnAxisScreen.toDEEP.dz * worldXYZ.z;

    //    cout << "output(" << worldXYZ.x <<
    //         ", " << worldXYZ.y << ",  " << worldXYZ.z << ")" << endl;
    return _then;
}
void ScreenDemo::freshFrameRotateInfo(){
    // 屏幕系转世界系 全刷新
    freshGoX();freshGoY();freshGoDEEP();

    frameRotateInfo_q = PolygonBase::getFrameRotateInfo_(screenOnWorld_toX,screenOnWorld_toDEEP);
}
void ScreenDemo::freshAxisWorldOnAxisScreen_quat() {
    // freshInfo() → freshFrameRotateInfo() 之后

    // 屏幕轴 反观 世界轴
    glm::vec3 _0_0_0 = tiltTurnPoint2(glm::vec3{0.0f, 0.0f, 0.0f});
    axisWorldOnAxisScreen._0_0_0 = _0_0_0;
    glm::vec3 _200_0_0 = tiltTurnPoint2(glm::vec3{200.0f, 0.0f, 0.0f});
    glm::vec3 _0_200_0 = tiltTurnPoint2(glm::vec3{0.0f, 200.0f, 0.0f});
    glm::vec3 _0_0_200 = tiltTurnPoint2(glm::vec3{0.0f, 0.0f, 200.0f});
    // 归一化的向量
    axisWorldOnAxisScreen.toX = get_AgoB_direction3D(_0_0_0, _200_0_0); // xright
    axisWorldOnAxisScreen.toY = get_AgoB_direction3D(_0_0_0, _0_200_0); // ybuttom
    axisWorldOnAxisScreen.toDEEP = get_AgoB_direction3D(_0_0_0, _0_0_200); // zfar
}
glm::vec3 ScreenDemo::worldXYZ2ScreenXYZ_quat(const glm::vec3& worldXYZ) {
    glm::vec3 _then = axisWorldOnAxisScreen._0_0_0;
    //    cout << "input(" << worldXYZ.x <<
    //    ", " << worldXYZ.y << ",  " << worldXYZ.z << ")" << endl;

    _then.x = _then.x + axisWorldOnAxisScreen.toX.dx * worldXYZ.x;
    _then.y = _then.y + axisWorldOnAxisScreen.toX.dy * worldXYZ.x;
    _then.z = _then.z + axisWorldOnAxisScreen.toX.dz * worldXYZ.x;

    _then.x = _then.x + axisWorldOnAxisScreen.toY.dx * worldXYZ.y;
    _then.y = _then.y + axisWorldOnAxisScreen.toY.dy * worldXYZ.y;
    _then.z = _then.z + axisWorldOnAxisScreen.toY.dz * worldXYZ.y;

    _then.x = _then.x + axisWorldOnAxisScreen.toDEEP.dx * worldXYZ.z;
    _then.y = _then.y + axisWorldOnAxisScreen.toDEEP.dy * worldXYZ.z;
    _then.z = _then.z + axisWorldOnAxisScreen.toDEEP.dz * worldXYZ.z;

    //    cout << "output(" << worldXYZ.x <<
    //         ", " << worldXYZ.y << ",  " << worldXYZ.z << ")" << endl;
    return _then;
}
void ScreenDemo::freshAxisWorldOnAxisScreen(){
    freshScreenAxisOnWorld();

    // 世界轴 基本信息
    // 原点(0,0,0) xright(200,0,0) ybuttom(0,200,0) zfar(0,0,200)

    // 屏幕轴 反观 世界轴
    glm::vec3 _0_0_0 = worldXYZ2ScreenXYZ(glm::vec3{0.0f, 0.0f, 0.0f});
    axisWorldOnAxisScreen._0_0_0 = _0_0_0;
    glm::vec3 _200_0_0 = worldXYZ2ScreenXYZ(glm::vec3{200.0f, 0.0f, 0.0f});
    glm::vec3 _0_200_0 = worldXYZ2ScreenXYZ(glm::vec3{0.0f, 200.0f, 0.0f});
    glm::vec3 _0_0_200 = worldXYZ2ScreenXYZ(glm::vec3{0.0f, 0.0f, 200.0f});
    // 归一化的向量
    axisWorldOnAxisScreen.toX = get_AgoB_direction3D(_0_0_0, _200_0_0); // xright
    axisWorldOnAxisScreen.toY = get_AgoB_direction3D(_0_0_0, _0_200_0); // ybuttom
    axisWorldOnAxisScreen.toDEEP = get_AgoB_direction3D(_0_0_0, _0_0_200); // zfar

//    cout << "axisWorldOnAxisScreen._0_0_0:" << axisWorldOnAxisScreen._0_0_0.x << " " <<
//        axisWorldOnAxisScreen._0_0_0.y << " " << axisWorldOnAxisScreen._0_0_0.z << endl;
//    cout << "axisWorldOnAxisScreen.screenOnWorld_toX:" << axisWorldOnAxisScreen.screenOnWorld_toX.dx << " " <<
//        axisWorldOnAxisScreen.screenOnWorld_toX.dy << " " << axisWorldOnAxisScreen.screenOnWorld_toX.dz << endl;
//    cout << "axisWorldOnAxisScreen.screenOnWorld_toY:" << axisWorldOnAxisScreen.screenOnWorld_toY.dx << " " <<
//        axisWorldOnAxisScreen.screenOnWorld_toY.dy << " " << axisWorldOnAxisScreen.screenOnWorld_toY.dz << endl;
//    cout << "axisWorldOnAxisScreen.screenOnWorld_toDEEP:" << axisWorldOnAxisScreen.screenOnWorld_toDEEP.dx << " " <<
//        axisWorldOnAxisScreen.screenOnWorld_toDEEP.dy << " " << axisWorldOnAxisScreen.screenOnWorld_toDEEP.dz << endl;
    float normal[4];

    normal[0] = axisWorldOnAxisScreen.toX.dx;
    normal[1] = axisWorldOnAxisScreen.toX.dy;
    normal[2] = axisWorldOnAxisScreen.toX.dz; // 法向量 左视
    normal[3] = -normal[0] * _0_0_0.x - normal[1] * _0_0_0.y - normal[2] * _0_0_0.z; // 代入原点
    axisWorldOnAxisScreen.a_b_c_d_yzFlat[0] = normal[0];
    axisWorldOnAxisScreen.a_b_c_d_yzFlat[1] = normal[1];
    axisWorldOnAxisScreen.a_b_c_d_yzFlat[2] = normal[2];
    axisWorldOnAxisScreen.a_b_c_d_yzFlat[3] = normal[3];

    normal[0] = axisWorldOnAxisScreen.toY.dx;
    normal[1] = axisWorldOnAxisScreen.toY.dy;
    normal[2] = axisWorldOnAxisScreen.toY.dz; // 法向量 俯视
    normal[3] = -normal[0] * _0_0_0.x - normal[1] * _0_0_0.y - normal[2] * _0_0_0.z; // 代入原点
    axisWorldOnAxisScreen.a_b_c_d_xzFlat[0] = normal[0];
    axisWorldOnAxisScreen.a_b_c_d_xzFlat[1] = normal[1];
    axisWorldOnAxisScreen.a_b_c_d_xzFlat[2] = normal[2];
    axisWorldOnAxisScreen.a_b_c_d_xzFlat[3] = normal[3];

    normal[0] = axisWorldOnAxisScreen.toDEEP.dx;
    normal[1] = axisWorldOnAxisScreen.toDEEP.dy;
    normal[2] = axisWorldOnAxisScreen.toDEEP.dz; // 法向量 主视
    normal[3] = -normal[0] * _0_0_0.x - normal[1] * _0_0_0.y - normal[2] * _0_0_0.z; // 代入原点
    axisWorldOnAxisScreen.a_b_c_d_xyFlat[0] = normal[0];
    axisWorldOnAxisScreen.a_b_c_d_xyFlat[1] = normal[1];
    axisWorldOnAxisScreen.a_b_c_d_xyFlat[2] = normal[2];
    axisWorldOnAxisScreen.a_b_c_d_xyFlat[3] = normal[3];

//    cout << "axisWorldOnAxisScreen.a_b_c_d_yzFlat:" << axisWorldOnAxisScreen.a_b_c_d_yzFlat[0] << " " <<
//        axisWorldOnAxisScreen.a_b_c_d_yzFlat[1] << " " << axisWorldOnAxisScreen.a_b_c_d_yzFlat[2] << " " <<
//        axisWorldOnAxisScreen.a_b_c_d_yzFlat[3] << endl;
//    cout << "axisWorldOnAxisScreen.a_b_c_d_xzFlat:" << axisWorldOnAxisScreen.a_b_c_d_xzFlat[0] << " " <<
//        axisWorldOnAxisScreen.a_b_c_d_xzFlat[1] << " " << axisWorldOnAxisScreen.a_b_c_d_xzFlat[2] << " " <<
//        axisWorldOnAxisScreen.a_b_c_d_xzFlat[3] << endl;
//    cout << "axisWorldOnAxisScreen.a_b_c_d_xyFlat:" << axisWorldOnAxisScreen.a_b_c_d_xyFlat[0] << " " <<
//        axisWorldOnAxisScreen.a_b_c_d_xyFlat[1] << " " << axisWorldOnAxisScreen.a_b_c_d_xyFlat[2] << " " <<
//        axisWorldOnAxisScreen.a_b_c_d_xyFlat[3] << endl;

//    glm::vec3 world_1_1_1 = worldXYZ2ScreenXYZ(glm::vec3{1.0f, 1.0f, 1.0f});
//    cout << "world_1_1_1:" << world_1_1_1.x << " " << world_1_1_1.y << " " << world_1_1_1.z << endl;
}

glm::vec3 ScreenDemo::screenXYZ2WorldXYZ(glm::vec3 screenXYZ){
    glm::vec3 worldXYZ;
    worldXYZ.z = screen2World_GetZ(screenXYZ);
    worldXYZ.y = screen2World_Gety(screenXYZ);
    worldXYZ.x = screen2World_Getx(screenXYZ);
    return worldXYZ;
}
float ScreenDemo::screen2World_GetZ(glm::vec3 screenXYZ){
    goLine32 goBackZ = {-axisWorldOnAxisScreen.toDEEP.dx, -axisWorldOnAxisScreen.toDEEP.dy,
                        -axisWorldOnAxisScreen.toDEEP.dz}; // 中心往中后走的向量
     float a = axisWorldOnAxisScreen.a_b_c_d_xyFlat[0];
     float b = axisWorldOnAxisScreen.a_b_c_d_xyFlat[1];
     float c = axisWorldOnAxisScreen.a_b_c_d_xyFlat[2];
     float d = axisWorldOnAxisScreen.a_b_c_d_xyFlat[3];
     float step, step_up, step_down;
     step_up = -a*screenXYZ.x - b*screenXYZ.y - c*screenXYZ.z - d;
     step_down = a*goBackZ.dx + b*goBackZ.dy + c*goBackZ.dz;
     step = step_up / step_down;
     return step;
}
float ScreenDemo::screen2World_Gety(glm::vec3 screenXYZ){
    goLine32 goBackY = {-axisWorldOnAxisScreen.toY.dx, -axisWorldOnAxisScreen.toY.dy,
                        -axisWorldOnAxisScreen.toY.dz}; // 中心往中后走的向量
    float a = axisWorldOnAxisScreen.a_b_c_d_xzFlat[0]; // xz面 垂y
    float b = axisWorldOnAxisScreen.a_b_c_d_xzFlat[1];
    float c = axisWorldOnAxisScreen.a_b_c_d_xzFlat[2];
    float d = axisWorldOnAxisScreen.a_b_c_d_xzFlat[3];
    float step, step_up, step_down;
    step_up = -a*screenXYZ.x - b*screenXYZ.y - c*screenXYZ.z - d;
    step_down = a*goBackY.dx + b*goBackY.dy + c*goBackY.dz;
    step = step_up / step_down;
    return step;

}
float ScreenDemo::screen2World_Getx(glm::vec3 screenXYZ){
    goLine32 goBackX = {-axisWorldOnAxisScreen.toX.dx, -axisWorldOnAxisScreen.toX.dy,
                        -axisWorldOnAxisScreen.toX.dz}; // 中心往中后走的向量
    float a = axisWorldOnAxisScreen.a_b_c_d_yzFlat[0]; // yz面 垂x
    float b = axisWorldOnAxisScreen.a_b_c_d_yzFlat[1];
    float c = axisWorldOnAxisScreen.a_b_c_d_yzFlat[2];
    float d = axisWorldOnAxisScreen.a_b_c_d_yzFlat[3];
    float step, step_up, step_down;
    step_up = -a*screenXYZ.x - b*screenXYZ.y - c*screenXYZ.z - d;
    step_down = a*goBackX.dx + b*goBackX.dy + c*goBackX.dz;
    step = step_up / step_down;
    return step;

}
void ScreenDemo::initLeftLookAngleOfSelfAxis(){
    // 左z 与 下y的视图
    /*
     *           lt rt
     *          | \
     *          |  \
     *          |   \
     *          |    \
     *          |     \
     *  center  |______\ eye
     *
     *
     */
    float center[2] = {-screenDeepF11, screenHeightF11/2.0f}; // (-1000,400)
    float topL[2] = {0.0f, 0.0f}; // 左视原点
    float buttomL[2] = {0.0f, screenHeightF11}; // 左视y轴 (0,800)
    // float centerL[2] = {0.0f, (float)screenHeight11/2.0f}; // 左视中心 (0,400)

    // left view: 上边 中点 下边
    leftLookAngleOfEye[0] = glm::degrees(glm::atan(center[1] - topL[1],
                                   -center[0] + topL[0]));
    leftLookAngleOfEye[1] = 0.0f;
    leftLookAngleOfEye[2] = glm::degrees(glm::atan(center[1] - buttomL[1],
                                   -center[0] + buttomL[0]));


}
void ScreenDemo::headUp(float angle){

    // 抬头 左视 屏幕axis下
    // x 是 -z  y 是 y
    float center[2] = {-screenDeepF11, screenHeightF11/2.0f}; // (-1000,400)
    float topL[2] = {0.0f, 0.0f}; // 左视原点
    pair<float,float> newTopL = headUpPoint(center, topL,leftLookAngleOfEye[0], angle); // 转后 topL
    float buttomL[2] = {0.0f, screenHeightF11}; // 左视y轴 (0,800)

    pair<float,float> newButtomL = headUpPoint(center, buttomL,leftLookAngleOfEye[2], angle); // 转后 buttomL
    float centerL[2] = {0.0f, screenHeightF11/2.0f}; // 左视中心 (0,400)

    pair<float,float> newCenterL = headUpPoint(center, centerL,leftLookAngleOfEye[1], angle); // 转后 centerL

    // 屏幕坐标系下 只是微挪一步 转世界坐标系就了得了
    glm::vec3 screenAxis_lt = {0.0f, newTopL.first, newTopL.second};
    glm::vec3 screenAxis_rt = {screenWidthF11, newTopL.first, newTopL.second};
    glm::vec3 screenAxis_lb = {0.0f, newButtomL.first, newButtomL.second};
    glm::vec3 screenAxis_rb = {screenWidthF11, newButtomL.first, newButtomL.second};
    glm::vec3 screenAxis_center = {screenWidthF11/2.0f, newCenterL.first, newCenterL.second};
    glm::vec3 screenAxis_eye = {screenWidthF11/2.0f, center[1], center[0]}; // (600,400,-1000)

    tblrXYZ.lt = screenXYZ2WorldXYZ(screenAxis_lt);
    tblrXYZ.rt = screenXYZ2WorldXYZ(screenAxis_rt);
    tblrXYZ.lb = screenXYZ2WorldXYZ(screenAxis_lb);
    tblrXYZ.rb = screenXYZ2WorldXYZ(screenAxis_rb);
    tblrXYZ.center = screenXYZ2WorldXYZ(screenAxis_center);
    screenAxis_eye = screenXYZ2WorldXYZ(screenAxis_eye);
    if(fabsf(screenAxis_eye.x - tblrXYZ.centerTip.x) > 0.01f ||
       fabsf(screenAxis_eye.y - tblrXYZ.centerTip.y) > 0.01f ||
       fabsf(screenAxis_eye.z - tblrXYZ.centerTip.z) > 0.01f){
       println(stderr,"不变 eye: {} {} {}",tblrXYZ.centerTip.x,tblrXYZ.centerTip.y,tblrXYZ.centerTip.z);
       println(stderr,"转换 eye: {} {} {}",screenAxis_eye.x,screenAxis_eye.y,screenAxis_eye.z);

    }tblrXYZ.centerTip = screenAxis_eye; // 修正

}
pair<float,float> ScreenDemo::headUpPoint(float center[], float point[],float baseAngle, float angle){
    // 左z 与 下y的视图
    /*
     *           lt rt
     *          | \
     *          |  \
     *          |   \
     *          |    \
     *          |     \
     *  center  |______\ eye
     *
     *
     */
    // center[0] -z  center[1] y
    // point[0] -z  point[1] y
    float long_center2point = PolygonBase::distanceOfPoint2D({point[0],point[1]},{center[0],center[1]});
//    float angleX = toDegrees(glm::atan(center[1] - point[1], -center[0] + point[0]));
    float angleX = baseAngle;
//    cout << "___angelX:" << toDegrees(glm::atan(center[1] - point[1], -center[0] + point[0])) <<
//    " baseAngle:" << baseAngle << endl;

    angleX += angle; // 上扬1度
    float result_z = center[0] + long_center2point * glm::cos(glm::radians(angleX));
    float resultY = center[1] - long_center2point * glm::sin(glm::radians(angleX));
    return make_pair(resultY,result_z);

}
void ScreenDemo::headDown(float angle){
    headUp(-angle);
}
void ScreenDemo::initDownLookAngleOfSelfAxis(){
    // 右x 与 上z的视图
    /*
     *                       point
     *                       rt rb
     *                       / |
     *                    /    |
     *                 /       |
     *              /          |
     *           /             |
     *        /________________|
     *       eye_center
     *
     *
     *
     */
    float center[2] = {screenWidthF11/2.0f, -screenDeepF11}; // (600, -1000)
    float rightXZ[2] = {screenWidthF11, 0.0f}; // (1200,0)
    float leftXZ[2] = {0.0f, 0.0f};
    float centerXZ[2] = {(float)screenWidth11/2.0f, 0.0f}; // (600,0)

    // down view: 左边 中点 右边
    downLookAngle[0] = glm::degrees(glm::atan(leftXZ[1] - center[1],
                                       leftXZ[0] - center[0]));
    downLookAngle[1] = 90.0f;
    downLookAngle[2] = glm::degrees(glm::atan(rightXZ[1] - center[1],
                                       rightXZ[0] - center[0]));


}
void ScreenDemo::headLeft(float angle){

    // 左看 俯视 屏幕axis下
    // x 是 x  y 是 z
    float center[2] = {screenWidthF11/2.0f, -screenDeepF11}; // (600, -1000)
    float rightXZ[2] = {screenWidthF11, 0.0f}; // (1200,0)
    pair<float,float> newRightXZ = headLeftPoint(center, rightXZ,downLookAngle[2], angle); // 转后 rightXZ

    float leftXZ[2] = {0.0f, 0.0f};
    pair<float,float> newLeftXZ = headLeftPoint(center, leftXZ,downLookAngle[0], angle); // 转后 leftXZ

    float centerXZ[2] = {screenWidthF11/2.0f, 0.0f}; // (600,0)
    pair<float,float> newCenterXZ = headLeftPoint(center, centerXZ,downLookAngle[1], angle); // 转后 centerXZ

    // 屏幕坐标系下 只是微挪一步 转世界坐标系就了得了
    glm::vec3 screenAxis_lt = {newLeftXZ.first, 0.0f, newLeftXZ.second};
    glm::vec3 screenAxis_rt = {newRightXZ.first, 0.0f, newRightXZ.second};
    glm::vec3 screenAxis_lb = {newLeftXZ.first, screenHeightF11, newLeftXZ.second};
    glm::vec3 screenAxis_rb = {newRightXZ.first, screenHeightF11, newRightXZ.second};
    glm::vec3 screenAxis_center = {newCenterXZ.first, screenHeightF11/2.0f, newCenterXZ.second};


    tblrXYZ.lt = screenXYZ2WorldXYZ(screenAxis_lt);
    tblrXYZ.rt = screenXYZ2WorldXYZ(screenAxis_rt);
    tblrXYZ.lb = screenXYZ2WorldXYZ(screenAxis_lb);
    tblrXYZ.rb = screenXYZ2WorldXYZ(screenAxis_rb);
    tblrXYZ.center = screenXYZ2WorldXYZ(screenAxis_center);
}
pair<float,float> ScreenDemo::headLeftPoint(float center[], float point[], float baseAngle, float angle){
    // 右x 与 上z的视图
    /*
     *                       point
     *                       rt rb
     *                       / |
     *                    /    |
     *                 /       |
     *              /          |
     *           /             |
     *        /________________|
     *       eye_center
     *
     *
     *
     */
    // center[0] x  center[1] z
    // point[0] x  point[1] z
    float long_center2point = PolygonBase::distanceOfPoint2D({point[0],point[1]},{center[0],center[1]});
    //    float angleY = toDegrees(glm::atan(point[1] - center[1], point[0] - center[0]));
    float angleY = baseAngle;
    //    cout << "___angelY:" << toDegrees(glm::atan(point[1] - center[1], point[0] - center[0])) <<
    //    " baseAngle:" << baseAngle << endl;

    angleY += angle; // 左转1度
    float result_x = center[0] + long_center2point * glm::cos(glm::radians(angleY));
    float resultZ = center[1] + long_center2point * glm::sin(glm::radians(angleY));
    return make_pair(result_x,resultZ);


}
void ScreenDemo::headRight(float angle){
    headLeft(-angle);
}
void ScreenDemo::initFrontLook4Corner(){
    float center[2] = {screenWidthF11/2.0f, screenHeightF11/2.0f}; // (600, 400)
    float lt[2] = {0.0f, 0.0f};
    float rt[2] = {screenWidthF11, 0.0f}; // (1200,0)
    float rb[2] = {screenWidthF11, screenHeightF11}; // (1200,800)
    float lb[2] = {0.0f, screenHeightF11}; // (0,800)

    frontLook4Corner[0] = glm::degrees(glm::atan(center[1] - lt[1], lt[0] - center[0])); // dy/dx ↓ →
    frontLook4Corner[1] = glm::degrees(glm::atan(center[1] - rt[1], rt[0] - center[0])); // dy/dx → ↓
    frontLook4Corner[2] = glm::degrees(glm::atan(center[1] - rb[1], rb[0] - center[0])); // dy/dx ↑ →
    frontLook4Corner[3] = glm::degrees(glm::atan(center[1] - lb[1], lb[0] - center[0])); // dy/dx ↓ ←


}
void ScreenDemo::headRollBackClock(float angle){
    // 左歪 主视 屏幕axis下
    // x 是 x  y 是 y
    float center[2] = {screenWidthF11/2.0f, screenHeightF11/2.0f}; // (600, 400)
    float lt[2] = {0.0f, 0.0f};
    pair<float,float> newLt = headRollBackPoint(center, lt,frontLook4Corner[0], angle); // 转后 lt

    float rt[2] = {screenWidthF11, 0.0f}; // (1200,0)
    pair<float,float> newRt = headRollBackPoint(center, rt,frontLook4Corner[1], angle); // 转后 rt

    float rb[2] = {screenWidthF11, screenHeightF11}; // (1200,800)
    pair<float,float> newRb = headRollBackPoint(center, rb,frontLook4Corner[2], angle); // 转后 rb

    float lb[2] = {0.0f, screenHeightF11}; // (0,800)
    pair<float,float> newLb = headRollBackPoint(center, lb,frontLook4Corner[3], angle); // 转后 lb

    // 屏幕坐标系下 只是微挪一步 转世界坐标系就了得了
    glm::vec3 screenAxis_lt = {newLt.first, newLt.second, 0.0f};
    glm::vec3 screenAxis_rt = {newRt.first, newRt.second, 0.0f};
    glm::vec3 screenAxis_lb = {newLb.first, newLb.second, 0.0f};
    glm::vec3 screenAxis_rb = {newRb.first, newRb.second, 0.0f};
    glm::vec3 screenAxis_center = {screenWidthF11/2.0f, screenHeightF11/2.0f, 0.0f};
    glm::vec3 screenAxis_centerTip = {screenWidthF11/2.0f, screenHeightF11/2.0f, -screenDeepF11};


    tblrXYZ.lt = screenXYZ2WorldXYZ(screenAxis_lt);
    tblrXYZ.rt = screenXYZ2WorldXYZ(screenAxis_rt);
    tblrXYZ.lb = screenXYZ2WorldXYZ(screenAxis_lb);
    tblrXYZ.rb = screenXYZ2WorldXYZ(screenAxis_rb);

    glm::vec3 centerSo = screenXYZ2WorldXYZ(screenAxis_center);
    glm::vec3 centerTipSo = screenXYZ2WorldXYZ(screenAxis_centerTip);
    if(fabsf(centerSo.x - tblrXYZ.center.x) > 0.01f ||
        fabsf(centerSo.y - tblrXYZ.center.y) > 0.01f ||
        fabsf(centerSo.z - tblrXYZ.center.z) > 0.01f){
        println(stderr,"不变 center: {} {} {}",tblrXYZ.center.x,tblrXYZ.center.y,tblrXYZ.center.z);
        println(stderr,"转换 center: {} {} {}",centerSo.x,centerSo.y,centerSo.z);
    }
    if(fabsf(centerTipSo.x - tblrXYZ.centerTip.x) > 0.01f ||
        fabsf(centerTipSo.y - tblrXYZ.centerTip.y) > 0.01f ||
        fabsf(centerTipSo.z - tblrXYZ.centerTip.z) > 0.01f){
        println(stderr,"不变 centerTip: {} {} {}",tblrXYZ.centerTip.x,
            tblrXYZ.centerTip.y,tblrXYZ.centerTip.z);
        println(stderr,"转换 centerTip: {} {} {}",centerTipSo.x,centerTipSo.y,centerTipSo.z);
    }
    tblrXYZ.center = centerSo;
    tblrXYZ.centerTip = centerTipSo;
}
pair<float,float> ScreenDemo::headRollBackPoint(float center[], float point[], float baseAngle, float angle){
    // 右x 与 下y的视图
    /*
     *                         .
     *                       / / \
     *                   /   /     \
     *               /    ./_______/
     *           /      eye   /
     *            \       /
     *              \ /
     *
     */
    // center[0] x  center[1] y
    // point[0] x  point[1] y
    float long_center2point = PolygonBase::distanceOfPoint2D({point[0],point[1]},{center[0],center[1]});
    float angleZ = baseAngle;//toDegrees(glm::atan(center[1] - point[1], point[0] - center[0])); // dy/dx ↓ →
//    cout << "___angelZ:" << toDegrees(glm::atan(center[1] - point[1], point[0] - center[0])) <<
//    " baseAngle:" << baseAngle << endl;

    angleZ += angle; // 左转1度
    float result_x = center[0] + long_center2point * glm::cos(glm::radians(angleZ));
    float resultY = center[1] - long_center2point * glm::sin(glm::radians(angleZ));
    return make_pair(result_x,resultY);
}
void ScreenDemo::headRollForwardClock(float angle){
    headRollBackClock(-angle);
}
goLine64 ScreenDemo::rotate_vector2(goLine64 vec2zero, Quaternion q){
    // 把向量变成四元数 (食物插在筷子上)
    Quaternion vec_q(0, vec2zero.dx, vec2zero.dy, vec2zero.dz);

    // 计算反向旋转 (q的逆 = 共轭, 因为单位四元数)
    Quaternion inv_q(q.w, -q.x, -q.y, -q.z);


    // 旋转公式: v' = q * v * q^-1 (正反搅拌两次)
    Quaternion temp = PolygonBase::multiply(q, vec_q);
    Quaternion result = PolygonBase::multiply(temp, inv_q);

    // 更新原向量
    //    vec2zero.dx = result.x;
    //    vec2zero.dy = result.y;
    //    vec2zero.dz = result.z;
    return {result.x, result.y, result.z};
}
Quaternion ScreenDemo::create_rotation(double angle_deg, goLine64 axis) {
    // 角度转弧度
    double half_rad = glm::radians(angle_deg) / 2.0;
    double sin_val = glm::sin(half_rad);

    // 构建四元数
    double w = glm::cos(half_rad);
    double x = sin_val * axis.dx;
    double y = sin_val * axis.dy;
    double z = sin_val * axis.dz;

    // 检查单位四元数
    double len_sq = w*w + x*x + y*y + z*z;
    if(fabs(len_sq - 1.0) > 1e-6){
        // 允许微小误差
        println(stderr,"create_rotation: Warning: Quaternion is not normalized. len_sq = {}", len_sq);
    }

    return Quaternion(w, x, y, z);
}
goLine64 ScreenDemo::getScreenOnWorld2X64() { // 世界系下 屏幕右x
    goLine32 res1 = get_AgoB_direction3D(tblrXYZ.lt, tblrXYZ.rt);
    return goLine64{res1.dx, res1.dy, res1.dz};
}

goLine64 ScreenDemo::getScreenOnWorld2Z64() {
    goLine32 res1 = get_AgoB_direction3D(tblrXYZ.centerTip, tblrXYZ.center);
    return goLine64{res1.dx, res1.dy, res1.dz};
}
glm::vec3 ScreenDemo::tiltTurnPoint2(const glm::vec3& p1){
    if(isnan(p1.x) || isnan(p1.y) || isnan(p1.z)){
        println(stderr,"NAN farWorld000 ({},{},{})",p1.x,p1.y,p1.z);
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }
    float movedX = tblrXYZ.lt.x;
    float movedY = tblrXYZ.lt.y;
    float movedZ = tblrXYZ.lt.z;
    //    cout << "movedX:" << movedX << endl;

    //    cout << "p1(" << p1.x << ", " << p1.y << ", " << p1.z << ")" << endl;
    glm::vec3 p1ToWorld000 = {p1.x - movedX,p1.y - movedY,p1.z - movedZ}; // 归原点
    //    cout << "p1ToWorld000(" << p1.x << ", " << p1.y << ", " << p1.z << ")" << endl;

    float distanceOf000 = glm::distance(p1ToWorld000,glm::vec3{0.f,0.f,0.f} ); // 原点距
    goLine64 p1ToWorld000_dir1 = {p1ToWorld000.x /= distanceOf000,
                                          p1ToWorld000.y /= distanceOf000,
                                          p1ToWorld000.z /= distanceOf000}; // 归一化


    // 没两角全0  不然不用斜转

    PolygonBase::rotate_vector(p1ToWorld000_dir1, frameRotateInfo_q);


    //    cout << "q2 p1ToWorld000_dir1(" <<  p1ToWorld000_dir1.dx << ", " << p1ToWorld000_dir1.dy <<
    //         ", " << p1ToWorld000_dir1.dz << ")" << endl;

    glm::vec3 farWorld000 = {(float)p1ToWorld000_dir1.dx * distanceOf000,
            (float)p1ToWorld000_dir1.dy * distanceOf000,
                             (float)p1ToWorld000_dir1.dz * distanceOf000};
    //    glm::vec3 result = world0002Back(farWorld000,movedX,movedY,movedZ);

    if(isnan(farWorld000.x) || isnan(farWorld000.y) || isnan(farWorld000.z)){
        println(stderr,"NAN farWorld000 ({},{},{})",farWorld000.x,farWorld000.y,farWorld000.z);
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }
    return farWorld000;
}
inline goLine32 ScreenDemo::get_AgoB_direction3D(glm::vec3 pa, glm::vec3 pb){
    goLine32 result(glm::normalize(pb - pa));
    return result;
}

glm::vec3 ScreenDemo::back2World000(glm::vec3 _src){
    float movedX = tblrXYZ.lt.x;
    float movedY = tblrXYZ.lt.y;
    float movedZ = tblrXYZ.lt.z;
    glm::vec3 result = {_src.x - movedX,_src.y - movedY,_src.z - movedZ};
    return result;
}
/*ScreenDemo::ScreenDemo(glm::vec3 _lt_xyz, glm::vec3 _rt_xyz, glm::vec3 _rb_xyz, glm::vec3 _lb_xyz,
                   glm::vec3 _center_xyz, glm::vec3 _centerTip_xyz, int _type,unsigned char _debug_)
{

//    printf("-lt: %f %f %f\n" ,_lt_xyz.y,_lt_xyz.x ,_lt_xyz.z );
//    printf("-rt: %f %f %f\n" ,_rt_xyz.y,_rt_xyz.x ,_rt_xyz.z );
//    printf("-rb: %f %f %f\n" ,_rb_xyz.y,_rb_xyz.x ,_rb_xyz.z );
//    printf("-lb: %f %f %f\n" ,_lb_xyz.y,_lb_xyz.x ,_lb_xyz.z );
//    printf("-center: %f %f %f\n" ,_center_xyz.y,_center_xyz.x ,_center_xyz.z );
//    printf("-centerTip: %f %f %f\n" ,_centerTip_xyz.y,_centerTip_xyz.x ,_centerTip_xyz.z );

    debugLine = _debug_;
//    printf("debugLine:%hd\n", debugLine);
    _init_main(_lt_xyz, _rt_xyz, _rb_xyz, _lb_xyz, _center_xyz, _centerTip_xyz,_type);
}*/
void ScreenDemo::_init_main(glm::vec3& _lt_xyz, glm::vec3& _rt_xyz, glm::vec3& _rb_xyz,glm::vec3& _lb_xyz,
                          glm::vec3& _center_xyz, glm::vec3& _centerTip_xyz, int _type) {


    tblrXYZ.lt.x = _lt_xyz.x;
    tblrXYZ.lt.y = _lt_xyz.y;
    tblrXYZ.lt.z = _lt_xyz.z;

    tblrXYZ.rt.x = _rt_xyz.x;
    tblrXYZ.rt.y = _rt_xyz.y;
    tblrXYZ.rt.z = _rt_xyz.z;

    tblrXYZ.rb.x = _rb_xyz.x;
    tblrXYZ.rb.y = _rb_xyz.y;
    tblrXYZ.rb.z = _rb_xyz.z;

    tblrXYZ.lb.x = _lb_xyz.x;
    tblrXYZ.lb.y = _lb_xyz.y;
    tblrXYZ.lb.z = _lb_xyz.z;

    tblrXYZ.center.x = _center_xyz.x; // 中心点
    tblrXYZ.center.y = _center_xyz.y;
    tblrXYZ.center.z = _center_xyz.z;

    tblrXYZ.centerTip.x = _centerTip_xyz.x; // 中心点的尖端
    tblrXYZ.centerTip.y = _centerTip_xyz.y;
    tblrXYZ.centerTip.z = _centerTip_xyz.z;


    // 相对于 世界坐标轴 同距
    tblrXYZ_unchange.lt.x = _lt_xyz.x;
    tblrXYZ_unchange.lt.y = _lt_xyz.y;
    tblrXYZ_unchange.lt.z = _lt_xyz.z;

    tblrXYZ_unchange.rt.x = _rt_xyz.x;
    tblrXYZ_unchange.rt.y = _rt_xyz.y;
    tblrXYZ_unchange.rt.z = _rt_xyz.z;

    tblrXYZ_unchange.rb.x = _rb_xyz.x;
    tblrXYZ_unchange.rb.y = _rb_xyz.y;
    tblrXYZ_unchange.rb.z = _rb_xyz.z;

    tblrXYZ_unchange.lb.x = _lb_xyz.x;
    tblrXYZ_unchange.lb.y = _lb_xyz.y;
    tblrXYZ_unchange.lb.z = _lb_xyz.z;

    tblrXYZ_unchange.center.x = _center_xyz.x; // 中心点
    tblrXYZ_unchange.center.y = _center_xyz.y;
    tblrXYZ_unchange.center.z = _center_xyz.z;

    tblrXYZ_unchange.centerTip.x = _centerTip_xyz.x; // 中心点的尖端
    tblrXYZ_unchange.centerTip.y = _centerTip_xyz.y;
    tblrXYZ_unchange.centerTip.z = _centerTip_xyz.z;
    angleXYZ = {0.0F, 0.0F, 0.0F}; // 初始角度

//    rectColor = WHITE;//无setcolor时默认
//    centerLongist = distanceOfPoint3D(tblrXYZ.lt, tblrXYZ.rb) / 2.0F; // 长轴长度

    rectWidth = glm::distance(tblrXYZ.lt, tblrXYZ.rt) ; // 宽度
    rectHeight = glm::distance(tblrXYZ.lt, tblrXYZ.lb); // 高度
    rectDepth = glm::distance(tblrXYZ.center, tblrXYZ.centerTip); // 深度

    objBufferFresh = false;

    coloredPixels.outterMax = rectHeight;
    coloredPixels.innerMax = rectWidth;
    coloredPixels.data.resize(static_cast<int>(rectWidth * rectHeight));
    std::fill(coloredPixels.data.begin(), coloredPixels.data.end(), glm::vec3{0,0,0}); // 初始化为黑色
//    for(auto pixel : coloredPixels){
//        if(pixel.r01 != 0.f || pixel.g01 != 0.f || pixel.b01 != 0.f)
//        cout << "(" << pixel.r01 << "," << pixel.g01 << "," << pixel.b01 << ") ";
//    }
//    cout << "coloredPixels size:" << coloredPixels.size() << endl;
    zBuffer.outterMax = rectHeight;
    zBuffer.innerMax = rectWidth;
    zBuffer.data.resize(static_cast<int>(rectWidth * rectHeight));
    std::fill(zBuffer.data.begin(), zBuffer.data.end(), 10000.f); // 初始化为0距离
    objBuffer.outterMax = rectHeight;
    objBuffer.innerMax = rectWidth;
    objBuffer.data.resize(static_cast<int>(rectWidth * rectHeight));
    std::fill(objBuffer.data.begin(), objBuffer.data.end(), nullptr); // 初始化为空指针

    initLeftLookAngleOfSelfAxis(); // 俯视 左视 self axis 默认角
    initDownLookAngleOfSelfAxis();
    initFrontLook4Corner(); // lt rt rb lb 到屏幕中心 与 右x得 夹角
//    printf("--lt: %f %f %f\n" ,_lt_xyz.y,_lt_xyz.x ,_lt_xyz.z );
//    printf("--rt: %f %f %f\n" ,_rt_xyz.y,_rt_xyz.x ,_rt_xyz.z );
//    printf("--rb: %f %f %f\n" ,_rb_xyz.y,_rb_xyz.x ,_rb_xyz.z );
//    printf("--lb: %f %f %f\n" ,_lb_xyz.y,_lb_xyz.x ,_lb_xyz.z );
//    printf("--center: %f %f %f\n" ,_center_xyz.y,_center_xyz.x ,_center_xyz.z );
//    printf("--centerTip: %f %f %f\n" ,_centerTip_xyz.y,_centerTip_xyz.x ,_centerTip_xyz.z );

//      printf("~~矩形中心最远点距离：%f\n", centerLongist);
    freshFrameRotateInfo();

    // string rowFname = "RowFlatVec4.txt";
    // rowFname = "../polygonClass/source/" + rowFname;
    // string colFname = "ColFlatVec4.txt";
    // colFname = "../polygonClass/source/" + colFname;
    // if (!checkRowFlatFile(rowFname)) {
    //     freshRowFlatFile(rowFname);
    // }
    // if (!checkColFlatFile(colFname)) {
    //     freshColFlatFile(colFname);
    // }
    // readRowFlatFile(rowFname); // 读取行方向的平面方程
    // readColFlatFile(colFname); // 读取列方向的平面方程
}

bool ScreenDemo::checkRowFlatFile(string& fileName){

    ifstream file(fileName); // 打开文件
    // 检查文件是否存在
    if (file.good()) {

        string line;

        if (getline(file,line)) {
            // if (!line.empty() && line.back()==';') {
            //     line.pop_back(); // 去掉结尾的分号
            // }
            if (line.find(to_string(screenHeight11) + ';') != string::npos) {
                line.pop_back();
                println("行文件正常, 高:{}", line);
                return true;
            }
                println(stderr,"首行不是正常的高: {};",screenHeight11);
                return false;

        }
    }else {
        println(stderr,"文件不存在, 新建文件");
    }
    return false;
}
bool ScreenDemo::checkColFlatFile(string& fileName){

    // string fileName = "RowFlatVec4.txt";

    ifstream file(fileName); // 打开文件
    // 检查文件是否存在
    if (file.good()) {

        string line;

        if (getline(file,line)) {
            // if (!line.empty() && line.back()==';') {
            //     line.pop_back(); // 去掉结尾的分号
            // }
            if (line.find(to_string(screenWidth11) + ';') != string::npos) {
                line.pop_back();
                println("列文件正常, 宽:{}", line);
                return true;
            }else {
                println(stderr,"首行不是正常的宽: {};",screenWidth11);
                return false;
            }
        }
    }else {
        println(stderr,"文件不存在, 新建文件");
    }
    return false;
}
void ScreenDemo::freshRowFlatFile(string& fileName){
    ofstream outfile(fileName); // 打开文件 'w'

    outfile << to_string(screenHeight11) << ';' << '\n'; // 写入宽 首行

    glm::vec3 lPoint, rPoint;
    goLine32 vertical;
    glm::vec3 startEye = {rectWidth/2.f,rectHeight/2.f,-rectDepth};
    //cout << "row startEye:" << startEye.x << " " << startEye.y << " " << startEye.z << endl;
    for(float y = 0.f; y < screenHeightF11; ++y) { // 0 ~ 999
        lPoint[0] = 0.f;
        lPoint[1] = y;
        lPoint[2] = 0.f;
        rPoint[0] = screenWidthF11 - 1.f; // 1599
        rPoint[1] = y;
        rPoint[2] = 0.f;
        // 法线朝上
        vertical._ = glm::normalize(glm::cross(rPoint-startEye, lPoint-startEye));
        // assert(vertical.dy < 0.f);

        // ax+by+cz+d=0 (a b c 取自 vertical)
        float d = -glm::dot(vertical._, startEye);
        outfile << to_string(vertical.dx) << ',' << to_string(vertical.dy)
            << ',' << to_string(vertical.dz) + ',' << to_string(d) << ';' << '\n';
    }
    outfile.close(); // 记得关闭文件 !!
}
void ScreenDemo::freshColFlatFile(string& fileName){
    ofstream outfile(fileName); // 打开文件 'w'

    outfile << to_string(screenWidth11) << ';' << '\n'; // 写入宽 首行

    glm::vec3 tPoint, bPoint;
    goLine32 vertical;
    glm::vec3 startEye = {rectWidth/2.f,rectHeight/2.f,-rectDepth};
    //cout << "col startEye:" << startEye.x << " " << startEye.y << " " << startEye.z << endl;
    for(float x = 0.f; x < screenWidthF11; ++x) { // 0 ~ 1599
        tPoint[0] = x;
        tPoint[1] = 0.f;
        tPoint[2] = 0.f;
        bPoint[0] = x;
        bPoint[1] = screenHeightF11 - 1.f; // 999
        bPoint[2] = 0.f;
        // 法线 朝左
        vertical._ = glm::normalize(glm::cross(tPoint-startEye, bPoint-startEye));
        // assert(vertical.dx < 0.f);

        // ax+by+cz+d=0 (a b c 取自 vertical)
        float d = -glm::dot(vertical._, startEye);
        outfile << to_string(vertical.dx) << ',' << to_string(vertical.dy)
            << ',' << to_string(vertical.dz) + ',' << to_string(d) << ';' << '\n';
    }
    outfile.close(); // 记得关闭文件 !!
}
void ScreenDemo::readRowFlatFile(string& fileName) {
    ifstream file(fileName); // 打开文件

    if (!file.good()) {
        throw std::invalid_argument("文件不存在");
    }
    string line;

    // 先读第一行
    if (getline(file,line)) {}
    rowFlatData.reserve(screenHeight11); // 1000行
    float a = numeric_limits<float>::quiet_NaN();
    float b = numeric_limits<float>::quiet_NaN();
    float c = numeric_limits<float>::quiet_NaN();
    float d = numeric_limits<float>::quiet_NaN();
    // 逐行读取 后续数据
    while (getline(file,line)) {
        // 去掉行末分号
        if (!line.empty() && line.back() == ';') {
            line.pop_back();
        }
        // 用字符串流解析数据
        stringstream ss(line);
        string token;

        if (getline(ss, token, ','))
            a = stof(token);
        if (getline(ss, token, ','))
            b = stof(token);
        if (getline(ss, token, ','))
            c = stof(token);
        if (getline(ss, token, ','))
            d = stof(token);
        rowFlatData.push_back({a, b, c, d});

    }
    file.close(); // 记得关闭文件 !!

    // for(int i=0; i< 30; ++i) { // 测试
    //     cout << "rowFlatData: " << rowFlatData[i][0] << " " << rowFlatData[i][1]
    //     << " " << rowFlatData[i][2] << " " << rowFlatData[i][3] << endl;
    // }

}
void ScreenDemo::readColFlatFile(string& fileName) {
    ifstream file(fileName); // 打开文件

    if (!file.good()) {
        throw std::invalid_argument("文件不存在");
    }
    string line;

    // 先读第一行
    if (getline(file,line)) {}
    rowFlatData.reserve(screenWidth11); // 1600列
    float a = numeric_limits<float>::quiet_NaN();
    float b = numeric_limits<float>::quiet_NaN();
    float c = numeric_limits<float>::quiet_NaN();
    float d = numeric_limits<float>::quiet_NaN();
    // 逐行读取 后续数据
    while (getline(file,line)) {
        // 去掉行末分号
        if (!line.empty() && line.back() == ';') {
            line.pop_back();
        }
        // 用字符串流解析数据
        stringstream ss(line);
        string token;

        if (getline(ss, token, ','))
            a = stof(token);
        if (getline(ss, token, ','))
            b = stof(token);
        if (getline(ss, token, ','))
            c = stof(token);
        if (getline(ss, token, ','))
            d = stof(token);
        colFlatData.push_back({a, b, c, d});

    }
    file.close(); // 记得关闭文件 !!

    // for(int i=0; i< 30; ++i) { // 测试
    //     cout << "colFlatData: " << colFlatData[i][0] << " " << colFlatData[i][1]
    //     << " " << colFlatData[i][2] << " " << colFlatData[i][3] << endl;
    // }

}




void ScreenDemo::ax1_by1_cz1_d1_OnWorld(){
//    // 计算两个边相量
//    glm::vec3 lt2rt = {tblrXYZ.lt.x - tblrXYZ.rt.x, tblrXYZ.lt.y - tblrXYZ.rt.y,
//
//                     tblrXYZ.lt.z - tblrXYZ.rt.z};
//
//    glm::vec3 lt2lb = {tblrXYZ.lt.x - tblrXYZ.lb.x, tblrXYZ.lt.y - tblrXYZ.lb.y,
//
//                     tblrXYZ.lt.z - tblrXYZ.lb.z};
    // 计算法向量
    float normal[4] = {};
//    normal[0] = lt2rt.y * lt2lb.z - lt2rt.z * lt2lb.y; // 0*0 - 0*(-150) = 0
//    normal[1] = lt2rt.z * lt2lb.x - lt2rt.x * lt2lb.z; // 0*0 - (-200)*0 = 0
//    normal[2] = lt2rt.x * lt2lb.y - lt2rt.y * lt2lb.x; // -200*(-150) - 0*0 = 30000
//
//    // 归一化法向量
//    float magnitude = glm::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
//    normal[0] /= magnitude;
//    normal[1] /= magnitude;
//    normal[2] /= magnitude; // 法向量 立方体对角线单位一

    // xy面 垂z
    normal[0] = screenOnWorld_toDEEP.dx;
    normal[1] = screenOnWorld_toDEEP.dy;
    normal[2] = screenOnWorld_toDEEP.dz; // 法向量 取反 ?

    if(_backFont == -1.0f){
        normal[0] *= -1.0f;
        normal[1] *= -1.0f;
        normal[2] *= -1.0f; // 法向量 取反 ?
    }

    // ax + by + cz + d = 0
    // d = -ax1*x1 - by1*y1 - cz1*z1
    normal[3] = -normal[0] * tblrXYZ.lt.x - normal[1] * tblrXYZ.lt.y - normal[2] * tblrXYZ.lt.z;

    // ax + by + cz + d = 0

    a_b_c_d_xyFlat[0] = normal[0];
    a_b_c_d_xyFlat[1] = normal[1];
    a_b_c_d_xyFlat[2] = normal[2];
    a_b_c_d_xyFlat[3] = normal[3];


    // xz面 垂y
    normal[0] = screenOnWorld_toY.dx;
    normal[1] = screenOnWorld_toY.dy;
    normal[2] = screenOnWorld_toY.dz; // 法向量 俯视
    normal[3] = -normal[0] * tblrXYZ.lt.x - normal[1] * tblrXYZ.lt.y - normal[2] * tblrXYZ.lt.z; // 代入原点
    a_b_c_d_xzFlat[0] = normal[0];
    a_b_c_d_xzFlat[1] = normal[1];
    a_b_c_d_xzFlat[2] = normal[2];
    a_b_c_d_xzFlat[3] = normal[3];
    //cout << "^^^^^a:" << a_b_c_d_xzFlat[0] << " b:" << a_b_c_d_xzFlat[1] << " c:" << a_b_c_d_xzFlat[2] << " d:" << a_b_c_d_xzFlat[3] << endl;
    // 得到了 ax + by + cz + d = 0 方程 可用 系数

    // yz面 垂x
    normal[0] = screenOnWorld_toX.dx;
    normal[1] = screenOnWorld_toX.dy;
    normal[2] = screenOnWorld_toX.dz; // 法向量 左视
    normal[3] = -normal[0] * tblrXYZ.lt.x - normal[1] * tblrXYZ.lt.y - normal[2] * tblrXYZ.lt.z; // 代入原点
    a_b_c_d_yzFlat[0] = normal[0];
    a_b_c_d_yzFlat[1] = normal[1];
    a_b_c_d_yzFlat[2] = normal[2];
    a_b_c_d_yzFlat[3] = normal[3];
    //cout << "^^^^^a:" << a_b_c_d_yzFlat[0] << " b:" << a_b_c_d_yzFlat[1] << " c:" << a_b_c_d_yzFlat[2] << " d:" << a_b_c_d_yzFlat[3] << endl;
    // 得到了 ax + by + cz + d = 0 方程 可用 系数

//    cout << "---screen lt:" << tblrXYZ.lt.x << " " << tblrXYZ.lt.y << " " << tblrXYZ.lt.z << endl;
//    cout << "---screen rt:" << tblrXYZ.rt.x << " " << tblrXYZ.rt.y << " " << tblrXYZ.rt.z << endl;
//    cout << "---screen rb:" << tblrXYZ.rb.x << " " << tblrXYZ.rb.y << " " << tblrXYZ.rb.z << endl;
//    cout << "---screen lb:" << tblrXYZ.lb.x << " " << tblrXYZ.lb.y << " " << tblrXYZ.lb.z << endl;
//    cout << "---screen center:" << tblrXYZ.center.x << " " << tblrXYZ.center.y << " " << tblrXYZ.center.z << endl;
//    cout << "---screen centerTip:" << tblrXYZ.centerTip.x << " " << tblrXYZ.centerTip.y << " " << tblrXYZ.centerTip.z << endl;

}
void ScreenDemo::freshScreenAxisOnWorld(){
    screenOnWorld_toX = get_AgoB_direction3D(tblrXYZ.lt, tblrXYZ.rt);
    screenOnWorld_toY = get_AgoB_direction3D(tblrXYZ.lt, tblrXYZ.lb);
    screenOnWorld_toDEEP = get_AgoB_direction3D(tblrXYZ.centerTip, tblrXYZ.center);

    ax1_by1_cz1_d1_OnWorld(); // 共面算法 uvw 系数关系
}


float ScreenDemo::world2ScreenXYZ_GetZ(glm::vec3 worldXYZ) {


    float a = a_b_c_d_xyFlat[0];
    float b = a_b_c_d_xyFlat[1];
    float c = a_b_c_d_xyFlat[2];
    float d = a_b_c_d_xyFlat[3];
    goLine32 goBackZ = {-a, -b, -c}; // 中心往中后走的向量
    float step, step_up, step_down;
    step_up = -a*worldXYZ.x - b*worldXYZ.y - c*worldXYZ.z - d;
//    if(std::isnan(step_up)){
//        cerr << "step_up is nan" << endl;
//    }
    step_down = -1.f;//a*goBackZ.dx + b*goBackZ.dy + c*goBackZ.dz;
//    if(std::isnan(step_down)){
//        cerr << "step_down is nan" << endl;
//    }
    step = step_up / step_down;
    return step;
}
float ScreenDemo::world2ScreenXYZ_Gety(glm::vec3 worldXYZ) {


    float a = a_b_c_d_xzFlat[0]; // xz面 垂y
    float b = a_b_c_d_xzFlat[1];
    float c = a_b_c_d_xzFlat[2];
    float d = a_b_c_d_xzFlat[3];
    goLine32 goBackY = {-a, -b, -c}; // 中心往中后走的向量
    float step, step_up, step_down;
    step_up = -a*worldXYZ.x - b*worldXYZ.y - c*worldXYZ.z - d;
//    if(std::isnan(step_up)){
//        cerr << "step_up is nan" << endl;
//    }
    step_down = -1.f;//a*goBackY.dx + b*goBackY.dy + c*goBackY.dz;
//    if(std::isnan(step_down)){
//        cerr << "step_down is nan" << endl;
//    }
    step = step_up / step_down;
    return step;

}
float ScreenDemo::world2ScreenXYZ_Getx(glm::vec3 worldXYZ) {


    float a = a_b_c_d_yzFlat[0]; // yz面 垂x
    float b = a_b_c_d_yzFlat[1];
    float c = a_b_c_d_yzFlat[2];
    float d = a_b_c_d_yzFlat[3];
    goLine32 goBackX = {-a, -b, -c}; // 中心往中后走的向量
    float step, step_up, step_down;
    step_up = -a*worldXYZ.x - b*worldXYZ.y - c*worldXYZ.z - d;
//    if(std::isnan(step_up)){
//        cerr << "step_up is nan" << endl;
//    }
    step_down = -1.f;//a*goBackX.dx + b*goBackX.dy + c*goBackX.dz;
//    if(std::isnan(step_down)){
//        cerr << "step_down is nan" << endl;
//    }
    step = step_up / step_down;
    return step;
}





goLine32 ScreenDemo::eye2ScreenPixel_dxyz(float x, float y){
    glm::vec3 pixelXYZ = {x, y, 0.0f};
    glm::vec3 startEYE = {screenWidthF11/2.0f, screenHeightF11/2.0f, -screenDeepF11}; // 初始化一次 (600,400,-1000)
    float pixel2eye_far = glm::distance(startEYE, pixelXYZ); // 计算像素点到屏幕中心的距离

    // float farX = pixelXYZ.x - startEYE.x; // 大减小 为正 走右
    // float farY = pixelXYZ.y - startEYE.y; // 大减小 为正 走下
    // float farZ = 0.0f - startEYE.z; // 初始化一次 (1000)
    glm::vec3 far = pixelXYZ - startEYE;
    // float dx = farX / pixel2eye_far;
    // float dy = farY / pixel2eye_far;
    // float dz = farZ / pixel2eye_far;
    // return {dx, dy, dz}; // 计算像素点到屏幕中心的向量
    return goLine32(far / pixel2eye_far);
}
glm::vec3 ScreenDemo::getEyeGoXYZbyXY(float x, float y){
    // 已知 眼xyz 步进xyz

    // 初始化一次 (600,400,-1000)
    glm::vec3 startEYE = {screenWidthF11/2.0f, screenHeightF11/2.0f, -screenDeepF11};
    goLine32 eyeGoPixel = eye2ScreenPixel_dxyz(x, y); // 计算 屏幕中心到像素点 的向量
    // eye.x + dx * step = x
    // eye.y + dy * step = y
    // eye.z + dz * step = z

    // 已知 abcd ax+by+cz+d=0
    // a*(eye.x + dx * step) + rtSet*(eye.y + dy * step) + c*(eye.z + dz * step) + d = 0
    float a = a_b_c_d_xyFlat[0];
    float b = a_b_c_d_xyFlat[1];
    float c = a_b_c_d_xyFlat[2];
    float d = a_b_c_d_xyFlat[3];
//    if(std::isnan(a)){
//        cerr << "a is nan" << endl;
//    }
//    if(std::isnan(rtSet)){
//        cerr << "rtSet is nan" << endl;
//    }
//    if(std::isnan(c)){
//        cerr << "c is nan" << endl;
//    }
//    if(std::isnan(d)){
//        cerr << "d is nan" << endl;
//    }
    // 求 step
    float step, step_up, step_down;
    step_up = -a*startEYE.x - b*startEYE.y - c*startEYE.z - d;
//    if(std::isnan(step_up)){
//        cerr << "step_up is nan" << endl;
//    }
    step_down = a*eyeGoPixel.dx + b*eyeGoPixel.dy + c*eyeGoPixel.dz;
//    if(std::isnan(step_down)){
//        cerr << "step_down is nan" << endl;
//    }

    step = step_up / step_down;
//    if(std::isnan(step)){
//        cerr << "step is nan" << endl;
//    }
    // 得到了 step 步进值
    glm::vec3 _eyeGoXYZ = {eyeGoPixel.dx * step,
                         eyeGoPixel.dy * step,
                           eyeGoPixel.dz * step};
    // 得到了 像素点的 xyz
    return _eyeGoXYZ;
}
float ScreenDemo::getEyeDeepbyXY(float x, float y){
    // 已知 眼xyz 步进xyz

    // 初始化一次 (600,400,-1000)
    glm::vec3 startEYE = {screenWidthF11/2.0f, screenHeightF11/2.0f, -screenDeepF11};
    goLine32 eyeGoPixel = eye2ScreenPixel_dxyz(x, y); // 计算 屏幕中心到像素点 的向量
    // eye.x + dx * step = x
    // eye.y + dy * step = y
    // eye.z + dz * step = z

    // 已知 abcd ax+by+cz+d=0
    // a*(eye.x + dx * step) + rtSet*(eye.y + dy * step) + c*(eye.z + dz * step) + d = 0
    float a = a_b_c_d_xyFlat[0];
    float b = a_b_c_d_xyFlat[1];
    float c = a_b_c_d_xyFlat[2];
    float d = a_b_c_d_xyFlat[3];
    //    if(std::isnan(a)){
    //        cerr << "a is nan" << endl;
    //    }
    //    if(std::isnan(rtSet)){
    //        cerr << "rtSet is nan" << endl;
    //    }
    //    if(std::isnan(c)){
    //        cerr << "c is nan" << endl;
    //    }
    //    if(std::isnan(d)){
    //        cerr << "d is nan" << endl;
    //    }
    // 求 step
    float step, step_up, step_down;
    step_up = -a*startEYE.x - b*startEYE.y - c*startEYE.z - d;
    //    if(std::isnan(step_up)){
    //        cerr << "step_up is nan" << endl;
    //    }
    step_down = a*eyeGoPixel.dx + b*eyeGoPixel.dy + c*eyeGoPixel.dz;
    //    if(std::isnan(step_down)){
    //        cerr << "step_down is nan" << endl;
    //    }

    step = step_up / step_down;
    //    if(std::isnan(step)){
    //        cerr << "step is nan" << endl;
    //    }
    // 得到了 step 步进值
    return startEYE.z + eyeGoPixel.dz * step;

}
// int ScreenDemo::indexOfPixelsVector(int x, int y) const {
//     // <= 排除 避免极值 !!!
//     if(y<0 || y>=rectHeight || x<0 || x>=rectWidth)return -1;
//     return y * rectWidth + x;
// }










void ScreenDemo::freshRectAxis(){

//    freshGoX();freshGoY();freshGoDEEP();

    freshTiltAxis(); // 刷新 倾斜轴
    freshParallelAxis(); // 刷新 平行轴
}



void ScreenDemo::freshTiltAxis(){
    // 中
    tiltAxis3D[0] = tblrXYZ.center;
    // x轴
    tiltAxis3D[1].x = tblrXYZ.center.x + screenOnWorld_toX.dx * rectWidth; // 数轴长度 看宽
    tiltAxis3D[1].y = tblrXYZ.center.y + screenOnWorld_toX.dy * rectWidth;
    tiltAxis3D[1].z = tblrXYZ.center.z + screenOnWorld_toX.dz * rectWidth;
    // y轴
    tiltAxis3D[2].x = tblrXYZ.center.x + screenOnWorld_toY.dx * rectWidth;
    tiltAxis3D[2].y = tblrXYZ.center.y + screenOnWorld_toY.dy * rectWidth;
    tiltAxis3D[2].z = tblrXYZ.center.z + screenOnWorld_toY.dz * rectWidth;
    // z轴
    tiltAxis3D[3].x = tblrXYZ.center.x + screenOnWorld_toDEEP.dx * rectWidth;
    tiltAxis3D[3].y = tblrXYZ.center.y + screenOnWorld_toDEEP.dy * rectWidth;
    tiltAxis3D[3].z = tblrXYZ.center.z + screenOnWorld_toDEEP.dz * rectWidth;
}

void ScreenDemo::freshParallelAxis(){
    // 中
    parallelAxis3D[0] = tblrXYZ.center;
    // x轴
    parallelAxis3D[1].x = tblrXYZ.center.x + rectWidth; // 数轴长度 看宽
    parallelAxis3D[1].y = tblrXYZ.center.y;
    parallelAxis3D[1].z = tblrXYZ.center.z;
    // y轴
    parallelAxis3D[2].x = tblrXYZ.center.x;
    parallelAxis3D[2].y = tblrXYZ.center.y + rectWidth;
    parallelAxis3D[2].z = tblrXYZ.center.z;
    // z轴
    parallelAxis3D[3].x = tblrXYZ.center.x;
    parallelAxis3D[3].y = tblrXYZ.center.y;
    parallelAxis3D[3].z = tblrXYZ.center.z + rectWidth;
}

void ScreenDemo::drawTiltAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴
    tiltAxis2D_f[0] = __3d2dGoScreen(ScreenEye, tiltAxis3D[0], nullptr);
    tiltAxis2D_f[1] = __3d2dGoScreen(ScreenEye, tiltAxis3D[1], nullptr);
    tiltAxis2D_f[2] = __3d2dGoScreen(ScreenEye, tiltAxis3D[2], nullptr);
    tiltAxis2D_f[3] = __3d2dGoScreen(ScreenEye, tiltAxis3D[3], nullptr);

//    setlinecolor(0x62a120); // 翠绿 ###
//    line((int)roundf(tiltAxis2D_f[0].x), (int)roundf(tiltAxis2D_f[0].y),
//         (int)roundf(tiltAxis2D_f[1].x), (int)roundf(tiltAxis2D_f[1].y)); // x轴
//    setlinecolor(0xb9902f); // 云山蓝
//    line((int)roundf(tiltAxis2D_f[0].x), (int)roundf(tiltAxis2D_f[0].y),
//         (int)roundf(tiltAxis2D_f[2].x), (int)roundf(tiltAxis2D_f[2].y)); // y轴
//    setlinecolor(0x0ea4d9); // 芥黄
//    line((int)roundf(tiltAxis2D_f[0].x), (int)roundf(tiltAxis2D_f[0].y),
//         (int)roundf(tiltAxis2D_f[3].x), (int)roundf(tiltAxis2D_f[3].y)); // z轴

}

void ScreenDemo::drawParallelAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴
    parallelAxis2D_f[0] = __3d2dGoScreen(ScreenEye, parallelAxis3D[0], nullptr);
    parallelAxis2D_f[1] = __3d2dGoScreen(ScreenEye, parallelAxis3D[1], nullptr);
    parallelAxis2D_f[2] = __3d2dGoScreen(ScreenEye, parallelAxis3D[2], nullptr);
    parallelAxis2D_f[3] = __3d2dGoScreen(ScreenEye, parallelAxis3D[3], nullptr);

//    setlinecolor(WHITE); // 回 白色 ###
//    line((int)roundf(parallelAxis2D_f[0].x), (int)roundf(parallelAxis2D_f[0].y),
//         (int)roundf(parallelAxis2D_f[1].x), (int)roundf(parallelAxis2D_f[1].y)); // x轴
//    line((int)roundf(parallelAxis2D_f[0].x), (int)roundf(parallelAxis2D_f[0].y),
//         (int)roundf(parallelAxis2D_f[2].x), (int)roundf(parallelAxis2D_f[2].y)); // y轴
//    line((int)roundf(parallelAxis2D_f[0].x), (int)roundf(parallelAxis2D_f[0].y),
//         (int)roundf(parallelAxis2D_f[3].x), (int)roundf(parallelAxis2D_f[3].y)); // z轴
}

// 向量归一化
//goLine32 ScreenDemo::normalize(goLine32 dirNow) {
//    float len = glm::sqrt(dirNow.dx*dirNow.dx + dirNow.dy*dirNow.dy + dirNow.dz*dirNow.dz);
//    goLine32 result = {
//            dirNow.dx / len,
//            dirNow.dy / len,
//            dirNow.dz / len
//    };
//
//    return result;
//}


// 向量叉乘
//goLine32 ScreenDemo::cross(goLine32 a, goLine32 b) {
//    goLine32 result;
//    result.dx = a.dy*b.dz - a.dz*b.dy;
//    result.dy = a.dz*b.dx - a.dx*b.dz;
//    result.dz = a.dx*b.dy - a.dy*b.dx;
//    return result;
//}


