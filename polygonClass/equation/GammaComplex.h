//
// Created by iceoc0 on 2025/10/2.
//

#ifndef POLYGONDISPLAY_GAMMACOMPLEX_H
#define POLYGONDISPLAY_GAMMACOMPLEX_H
#include "../source/ScreenDemo.h"

// #include <Eigen/Dense> // 使用 Eigen 库进行向量和矩阵运算
struct onepixelInfo28{
    int x; // long x long y
    float screenDeep; // 屏垂距
    float rgb[3]; // rgb color

};

struct rowPixelInfo28 {
    vector<onepixelInfo28> pixelDeeps; // 行的像素深度
    int y; // 行
};

struct Particle28 {

    Particle28() = default;

    double xxRe,xxIm, yyRe,yyIm;
//    glm::vec3 posScreenAxis;
    glm::vec3 color;
};
struct cloud {
    glm::vec3 pos;
    glm::vec3 color;
};
struct tinyBoxClouds {
    vector<cloud> pointsInTinyBox;
};
struct _allClouds {
    array<float, 4> xRange, yRange, zRange;
    array<tinyBoxClouds,64> tinyBox64;
    int totalSize;
    int getIndexByPos(glm::vec3 pos){
        int xIndex;
        if(pos.x > xRange[0] && pos.x <= xRange[1]){ // 左左~左中
            xIndex = 0;
        }else if(pos.x > xRange[1] && pos.x <= 0.f){ // 左中~中
            xIndex = 1;
        }else if(pos.x > 0.f && pos.x <= xRange[2]){ // 中~中右
            xIndex = 2;
        }else if(pos.x > xRange[2] && pos.x <= xRange[3]){ // 中右~右右
            xIndex = 3;
        }else{
            println(stderr, "x out of box");
            return -1;
        }
        int yIndex;
        if(pos.y > yRange[0] && pos.y <= yRange[1]){ // 上上~上中
            yIndex = 0;
        }else if(pos.y > yRange[1] && pos.y <= 0.f){ // 上中~中
            yIndex = 1;
        }else if(pos.y > 0.f && pos.y <= yRange[2]){ // 中~中下
            yIndex = 2;
        }else if(pos.y > yRange[2] && pos.y <= yRange[3]){ // 中下~下下
            yIndex = 3;
        }else{
            println(stderr, "y out of box");
            return -1;
        }
        int zIndex;
        if(pos.z > zRange[0] && pos.z <= zRange[1]){ // 后后~中后
            zIndex = 0;
        }else if(pos.z > zRange[1] && pos.z <= 0.f){ // 中后~中
            zIndex = 1;
        }else if(pos.z > 0.f && pos.z <= zRange[2]){ // 中~前中
            zIndex = 2;
        }else if(pos.z > zRange[2] && pos.z <= zRange[3]){ // 前中~前前
            zIndex = 3;
        }else{
            println(stderr, "z out of box");
            return -1;
        }
        return zIndex + yIndex*4 + xIndex*16;
    }
    bool closeIn(float a, float b){
        return abs(a-b) < 0.01;
    }
    void setPosButClose(glm::vec3 _pos, glm::vec3 _color){
        if(isnan(_pos.x) || isnan(_pos.y) || isnan(_pos.z) ||
        isnan(_color.x) || isnan(_color.y) || isnan(_color.z)){
            println(stderr, "nan in set pos or color");
            return;
        }
        int index = getIndexByPos(_pos);
        if(index == -1){
            println(stderr, "~ invalid index");
            return;
        }
        for(auto& p : tinyBox64[index].pointsInTinyBox){
            if(closeIn(p.pos.x, _pos.x) && closeIn(p.pos.y, _pos.y) && closeIn(p.pos.z, _pos.z)){
                // 附近有了 不加了
                return;
            }
        }
        tinyBox64[index].pointsInTinyBox.push_back({_pos, _color});

    }
    void freshTotalSize(){
        totalSize = 0;
        for(auto& box : tinyBox64){
            totalSize += (int)box.pointsInTinyBox.size();
        }
    }


};
//std::mutex cout_mutex;

class GammaComplex : public PolygonBase{
    public:
    GammaComplex(glm::vec3 srartCenter, glm::vec3 _boxLengthHalf, unsigned char _debug_ = 0);

    CubeBox3D scanBox3D;
    CubeBox3D scanBox3D_unchange;
    CubeBox3D virtual_scanBox3D;

    CubeBox2D scanBox2D;

    glm::vec3 halfBoxLength;
    float boxLenX,boxLenY,boxLenZ;

    unsigned char debugLine;

    unsigned char renderNext; // false
    int startRowIndex_; // 0

    unsigned char preNext;

    void setBox3D(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
                  glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf);

    void setBox2D(glm::vec2 _ltn, glm::vec2 _rtn, glm::vec2 _rbn, glm::vec2 _lbn,
                  glm::vec2 _ltf, glm::vec2 _rtf, glm::vec2 _rbf, glm::vec2 _lbf,
                  glm::vec2 _center
    );
    void Draw_Tick(ScreenDemo* ScreenEye);

    void solidRectangle2D(ScreenDemo* ScreenEye);
    vector<lineBoundary> lineScanFillColor;
    vector<rowPixelInfo28> pixelSurfaceInfo_;

    float min_1in3(float a, float b, float c);
    float max_1in3(float a, float b, float c);

    float stepInBox(glm::vec3 Eye_Self,goLine32 eyeRay_Self);
    float stepOutBox(glm::vec3 Eye_Self,goLine32 eyeRay_Self);

    goLine32 world_toX; //  长 单位一向量
    goLine32 world_toY; //  宽 单位一向量
    goLine32 world_toDEEP; //  深 单位一向量

    void freshGoX(); // 基于世界系 盒子顶点
    void freshGoY();
    void freshGoDEEP();
    glm::vec3 goX(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goY(glm::vec3 _srcXYZ, float _move);
    glm::vec3 goDEEP(glm::vec3 _srcXYZ, float _move);

    float frameScreenFar, frameScreenNear; // 定点深度初始化
    void deepFarNearBackCenter(); // 计算最远点和最近点的深度

    glm::vec3 frontColor_rgb01;
    void setFrontColor(int _color1);

    goLine32 virtual_toX; //  长 单位一向量
    goLine32 virtual_toY; //  宽 单位一向量
    goLine32 virtual_toDEEP; //  深 单位一向量
    void freshVirtualGoX();
    void freshVirtualGoY();
    void freshVirtualGoDEEP();
    glm::vec3 Virtual_goX(glm::vec3 _srcXYZ, float _move);
    glm::vec3 Virtual_goY(glm::vec3 _srcXYZ, float _move);
    glm::vec3 Virtual_goDEEP(glm::vec3 _srcXYZ, float _move);


    Quaternion frameRotateInfo_q;
    void freshFrameRotateInfo();
    glm::vec3 screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos); // 屏幕坐标转自身坐标2

    vector<Particle28> particleInBox;
    bool xxRealInBox(double xxReal);
//    bool xxImagInBox(double xxImag);
    bool yyRealInBox(double yyReal);
    bool yyImagInBox(double yyImag);
    string strip(const string &s);
    void loadParticle(string filename);
    void draw_particle(ScreenDemo* ScreenEye);

    glm::vec3 getColorBy_vX(float _vX);

    glm::vec3 self2screenAxis(glm::vec3 _selfAxisPos);

    _allClouds allClouds;
    void draw_allClouds(ScreenDemo* ScreenEye);

};

#endif //POLYGONDISPLAY_GAMMACOMPLEX_H
