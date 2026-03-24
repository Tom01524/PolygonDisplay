//
// Created by iceoc0 on 2025/8/31.
//
#include "EquationThree9.h"
//#include "Eigen/src/Eigenvalues/ComplexEigenSolver.h"

// extern void* settled_ptr; // 全局设置的结构体指针
// struct _settledEquation3_9{
//     int _width;
//     int _height;
//     int _deep;
//     bool _byAxis;
// };
// _settledEquation3_9* settled_ = (_settledEquation3_9*)settled_ptr;
// const int screenWidth24 = settled_-> _width;
// const int screenHeight24 = settled_-> _height;
// const int screenDeep24 = settled_-> _deep;

struct modeEquation3_9{ // 同类型组 的 结构体指针 移花接木
    char now;char a;char b;char d;
};
extern void* mode_ptr;
modeEquation3_9 mode_ = *static_cast<modeEquation3_9*>(mode_ptr);

extern void* _3d_2d_go_void_ptr; // 3d_2d_go的函数指针

glm::vec2 (*__3d2dGoEquation3_9)(ScreenDemo*, glm::vec3, glm::vec3*) =
    static_cast<_3d_2d_go_func *>(_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2dEquation3_9)(ScreenDemo*, float, float, float) =
    static_cast<_3d_2d_go_func *>(_3d_2d_go_void_ptr)->_3d_2d;


EquationThree9::EquationThree9(glm::vec3 srartCenter, glm::vec3 _boxLengthHalf, float a, float b, float c,
                               float d,unsigned char _debug_):PolygonBase(24){
    abcd[0] = a;abcd[1] = b;
    abcd[2] = c;abcd[3] = d;

    debugLine = _debug_;

    halfBoxLength = _boxLengthHalf;
    boxLenX = _boxLengthHalf.x * 2.f;
    boxLenY = _boxLengthHalf.y * 2.f;
    boxLenZ = _boxLengthHalf.z * 2.f;

    scanBox3D.center = srartCenter; // 包围盒中心

    scanBox3D.ltnSet.x = srartCenter.x - _boxLengthHalf.x; // 包围盒8角
    scanBox3D.ltnSet.y = srartCenter.y - _boxLengthHalf.y;
    scanBox3D.ltnSet.z = srartCenter.z - _boxLengthHalf.z;

    scanBox3D.rtnSet.x = srartCenter.x + _boxLengthHalf.x;
    scanBox3D.rtnSet.y = srartCenter.y - _boxLengthHalf.y;
    scanBox3D.rtnSet.z = srartCenter.z - _boxLengthHalf.z;

    scanBox3D.rbnSet.x = srartCenter.x + _boxLengthHalf.x;
    scanBox3D.rbnSet.y = srartCenter.y + _boxLengthHalf.y;
    scanBox3D.rbnSet.z = srartCenter.z - _boxLengthHalf.z;

    scanBox3D.lbnSet.x = srartCenter.x - _boxLengthHalf.x;
    scanBox3D.lbnSet.y = srartCenter.y + _boxLengthHalf.y;
    scanBox3D.lbnSet.z = srartCenter.z - _boxLengthHalf.z;

    scanBox3D.ltfSet.x = srartCenter.x - _boxLengthHalf.x;
    scanBox3D.ltfSet.y = srartCenter.y - _boxLengthHalf.y;
    scanBox3D.ltfSet.z = srartCenter.z + _boxLengthHalf.z;

    scanBox3D.rtfSet.x = srartCenter.x + _boxLengthHalf.x;
    scanBox3D.rtfSet.y = srartCenter.y - _boxLengthHalf.y;
    scanBox3D.rtfSet.z = srartCenter.z + _boxLengthHalf.z;

    scanBox3D.rbfSet.x = srartCenter.x + _boxLengthHalf.x;
    scanBox3D.rbfSet.y = srartCenter.y + _boxLengthHalf.y;
    scanBox3D.rbfSet.z = srartCenter.z + _boxLengthHalf.z;

    scanBox3D.lbfSet.x = srartCenter.x - _boxLengthHalf.x;
    scanBox3D.lbfSet.y = srartCenter.y + _boxLengthHalf.y;
    scanBox3D.lbfSet.z = srartCenter.z + _boxLengthHalf.z;

    // 刷新 世界系 斜向 三轴 步进
    freshGoX();freshGoY();freshGoDEEP();


    // 初始化 不变盒子位置
    scanBox3D_unchange.center = scanBox3D.center;

    scanBox3D_unchange.ltnSet = scanBox3D.ltnSet;
    scanBox3D_unchange.rtnSet = scanBox3D.rtnSet;
    scanBox3D_unchange.rbnSet = scanBox3D.rbnSet;
    scanBox3D_unchange.lbnSet = scanBox3D.lbnSet;

    scanBox3D_unchange.ltfSet = scanBox3D.ltfSet;
    scanBox3D_unchange.rtfSet = scanBox3D.rtfSet;
    scanBox3D_unchange.lbfSet = scanBox3D.lbfSet;
    scanBox3D_unchange.rbfSet = scanBox3D.rbfSet;

    // startEye = {(float)screenWidth24/2.f,
    //             (float)screenHeight24/2.f,(float)-screenDeep24};

    renderNext = false;
    startRowIndex_ = 0;


    particle_inited = false;

    smallerCoef = 10.0;
    smallerCoef_2 = smallerCoef * smallerCoef;
    smallerCoef_3 = smallerCoef_2 * smallerCoef;
    smallerCoef_4 = smallerCoef_3 * smallerCoef;
    smallerCoef_5 = smallerCoef_4 * smallerCoef;
    smallerCoef_6 = smallerCoef_5 * smallerCoef;
    smallerCoef_7 = smallerCoef_6 * smallerCoef;
    smallerCoef_8 = smallerCoef_7 * smallerCoef;
    smallerCoef_9 = smallerCoef_8 * smallerCoef;

}
void EquationThree9::setBox3D(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
                            glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf){
    scanBox3D.ltnSet = _ltn;
    scanBox3D.rtnSet = _rtn;
    scanBox3D.rbnSet = _rbn;
    scanBox3D.lbnSet = _lbn;

    scanBox3D.ltfSet = _ltf;
    scanBox3D.rtfSet = _rtf;
    scanBox3D.rbfSet = _rbf;
    scanBox3D.lbfSet = _lbf;

    freshGoX();freshGoY();freshGoDEEP();

    glm::vec3 centerThen = goX(_ltn,halfBoxLength.x);
    centerThen = goY(centerThen,halfBoxLength.y);
    centerThen = goDEEP(centerThen,halfBoxLength.z);
    scanBox3D.center = centerThen;

//    cout << "### boxLenX:" << boxLenX << endl;
//    cout << "### boxLenY:" << boxLenY << endl;
//    cout << "### boxLenZ:" << boxLenZ << endl;


//    scanBox3D.rtn_ltn_tip = goX(scanBox3D.ltnSet,-rounfBoxTipLen);
//    scanBox3D.rtn_ltn_back = goX(scanBox3D.ltnSet,rounfBoxTipLen);
//
//    scanBox3D.lbn_ltn_tip = goY(scanBox3D.ltnSet,-rounfBoxTipLen);
//    scanBox3D.lbn_ltn_back = goY(scanBox3D.ltnSet,rounfBoxTipLen);
//
//    scanBox3D.ltf_ltn_tip = goDEEP(scanBox3D.ltnSet,-rounfBoxTipLen);
//    scanBox3D.ltf_ltn_back = goDEEP(scanBox3D.ltnSet,rounfBoxTipLen);
//
//    scanBox3D.lbf_rbf_tip = goX(scanBox3D.rbfSet,rounfBoxTipLen);
//    scanBox3D.lbf_rbf_back = goX(scanBox3D.rbfSet,-rounfBoxTipLen);
//
//    scanBox3D.rtf_rbf_tip = goY(scanBox3D.rbfSet,rounfBoxTipLen);
//    scanBox3D.rtf_rbf_back = goY(scanBox3D.rbfSet,-rounfBoxTipLen);
//
//    scanBox3D.rbn_rbf_tip = goDEEP(scanBox3D.rbfSet,rounfBoxTipLen);
//    scanBox3D.rbn_rbf_back = goDEEP(scanBox3D.rbfSet,-rounfBoxTipLen);


}

void EquationThree9::setBox2D(glm::vec2 _ltn, glm::vec2 _rtn, glm::vec2 _rbn, glm::vec2 _lbn,
                            glm::vec2 _ltf, glm::vec2 _rtf, glm::vec2 _rbf, glm::vec2 _lbf,
                            glm::vec2 _center

){


    scanBox2D_.set13P(_ltn, _rtn, _rbn, _lbn,
            _ltf, _rtf, _rbf, _lbf,
            _center);


    renderNext = 0;

    startRowIndex_ = 0;
    pixelSurfaceInfo_.clear();


}
void EquationThree9::Draw_Tick(ScreenDemo* ScreenEye){
//    if(renderNext == 0){
//        println("--move");
//    }else if(renderNext == 1){
//        println("--not move");
//    }

    freshVirtualGoX(); // 屏幕系 数轴三向
    freshVirtualGoY();
    freshVirtualGoDEEP();

    if(!particle_inited){
        init_particle_info();
        particle_inited = true;
    }

    if(renderNext == 1)deepFarNearBackCenter();

    freshFrameRotateInfo(); // 转自己系 四元数


    solidRectangle2D_(ScreenEye);

    if(debugLine == 0) {
        freshComplexRect(ScreenEye);
        drawComplexRect(ScreenEye);
    }

    if (!renderNext){
        draw_particle(ScreenEye); // 粒子效果
    }


    float _color_[3];
    if (debugLine == 1) {

        _color_[0] = 1.0f;
        _color_[1] = 1.0f;
        _color_[2] = 1.0f; // 白色
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.ltn.x, scanBox2D_.ltn.y,
                                      scanBox2D_.rtn.x, scanBox2D_.rtn.y,
                                      _color_, frameScreenNear);// 前框
//        cout << "~~draw ltn(" << scanBox2D.ltnSet.x << ", " << scanBox2D.ltnSet.y << ")" <<
//         "draw rtn(" << scanBox2D.rtnSet.x << ", " << scanBox2D.rtnSet.y << ")" << endl;
//        cout << " color:" << _color_[0] << " " << _color_[1] << " " << _color_[2] << endl;
//        cout << " frameScreenNear:" << frameScreenNear << endl;

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rtn.x, scanBox2D_.rtn.y,
                                      scanBox2D_.rbn.x, scanBox2D_.rbn.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rbn.x, scanBox2D_.rbn.y,
                                      scanBox2D_.lbn.x, scanBox2D_.lbn.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.lbn.x, scanBox2D_.lbn.y,
                                      scanBox2D_.ltn.x, scanBox2D_.ltn.y,
                                      _color_, frameScreenNear);

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.ltf.x, scanBox2D_.ltf.y,
                                      scanBox2D_.rtf.x, scanBox2D_.rtf.y,
                                      _color_, frameScreenNear);// 后框
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rtf.x, scanBox2D_.rtf.y,
                                      scanBox2D_.rbf.x, scanBox2D_.rbf.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rbf.x, scanBox2D_.rbf.y,
                                      scanBox2D_.lbf.x, scanBox2D_.lbf.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.lbf.x, scanBox2D_.lbf.y,
                                      scanBox2D_.ltf.x, scanBox2D_.ltf.y,
                                      _color_, frameScreenNear);

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.ltn.x, scanBox2D_.ltn.y,
                                      scanBox2D_.ltf.x, scanBox2D_.ltf.y,
                                      _color_, frameScreenNear);// 前后连
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rtn.x, scanBox2D_.rtn.y,
                                      scanBox2D_.rtf.x, scanBox2D_.rtf.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.rbn.x, scanBox2D_.rbn.y,
                                      scanBox2D_.rbf.x, scanBox2D_.rbf.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D_.lbn.x, scanBox2D_.lbn.y,
                                      scanBox2D_.lbf.x, scanBox2D_.lbf.y,
                                      _color_, frameScreenNear);




    }

    renderNext = 1; // 看又 移动了 ?
}

void EquationThree9::solidRectangle2D_(ScreenDemo* ScreenEye) {


    scanBox2D_.setLineBounary(lineScanFillColor_);

//    for(auto& _linePosInfo : lineScanFillColor_) { // 行循环
//        for(int i = _linePosInfo.lx; i <= _linePosInfo.rx; ++i){
//            float colorNOw[3] = {frontColor1_rgb01[0],frontColor1_rgb01[1],frontColor1_rgb01[2]};
//            ScreenEye->putPixel(i,_linePosInfo.y,
//                                colorNOw,virtual_scanBox3D.center.z-500.f,
//                                (PolygonBase*)this);
//        }
//
//    }return;

    size_t rowAll = lineScanFillColor_.size() + lineScanFillColor_[0].y;


    if(renderNext == 1){
        backRenderRow:
        if(startRowIndex_ < lineScanFillColor_.size()){
            lineBoundary _linePosInfo = lineScanFillColor_[startRowIndex_];

            rowPixelInfo24 rowpixelsInfo;
            println("ray 行:{}/{},列L:{},列R:{}",
                    _linePosInfo.y,rowAll,_linePosInfo.lx,_linePosInfo.rx);
            if (_linePosInfo.rx == _linePosInfo.lx) {
                // 屏幕外的行 左右x相同

                startRowIndex_++;
                goto backRenderRow;
            }
            rowpixelsInfo.y = (float) _linePosInfo.y; // 本行 y
            for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; ++nowX) { // 单像素循环
                onepixelInfo24 onepixelInfo;


                glm::vec3 startEye_Self = screenXYZ2SelfXYZ2(startEye);
                glm::vec3 screenPoint_Self = screenXYZ2SelfXYZ2({nowX, _linePosInfo.y,0.f});

                goLine32 eyeRay_Self = ScreenDemo::get_AgoB_direction3D(startEye_Self,screenPoint_Self); // 计算视线

                goLine32 eyeRay_ScreenAxis = ScreenDemo::get_AgoB_direction3D(startEye,{nowX, _linePosInfo.y,0.f}); // 视线 屏幕坐标系
                RayCalcInfo24 nearestInBoxPoint = getBestSolve(startEye_Self.x, startEye_Self.y, startEye_Self.z,
                                                               eyeRay_Self.dx, eyeRay_Self.dy, eyeRay_Self.dz);

                if(!isnan(nearestInBoxPoint.step)) {
                    //1
                    onepixelInfo.x = (float) nowX; // 本像素 x

                    float screenDeep_ScreenAxis =
                            startEye.z + eyeRay_ScreenAxis.dz * nearestInBoxPoint.step; // 视线深度 屏幕坐标系

                    //2
                    onepixelInfo.screenDeep = screenDeep_ScreenAxis; // 像素深度 屏幕坐标系

                    if (screenDeep_ScreenAxis < frameScreenNear) {
                        frameScreenNear = screenDeep_ScreenAxis; // 刷新 近 屏垂距
                    } else if (screenDeep_ScreenAxis > frameScreenFar) {
                        frameScreenFar = screenDeep_ScreenAxis; // 刷新 远 屏垂距
                    }

                    unsigned char solveBy_ = getSolveBy(nearestInBoxPoint.surfacePoint_Self,nearestInBoxPoint.vx);
                    glm::vec3 colorNow = getColorBy_vX(solveBy_,nearestInBoxPoint.vx);
                    //3
                    onepixelInfo.rgb[0] = colorNow[0];
                    onepixelInfo.rgb[1] = colorNow[1];
                    onepixelInfo.rgb[2] = colorNow[2];

                }else{
                    onepixelInfo.x = nowX; // 像素深度 屏幕坐标系
                    onepixelInfo.screenDeep = numeric_limits<float>::quiet_NaN(); // 像素深度 屏幕坐标系
                    onepixelInfo.rgb[0] = numeric_limits<float>::quiet_NaN();
                    onepixelInfo.rgb[1] = numeric_limits<float>::quiet_NaN();
                    onepixelInfo.rgb[2] = numeric_limits<float>::quiet_NaN();
                }

                rowpixelsInfo.pixelDeeps.emplace_back(onepixelInfo);
            }
            pixelSurfaceInfo_.emplace_back(rowpixelsInfo);

            startRowIndex_++;
        }

        for(auto& _rowpixelsInfo : pixelSurfaceInfo_) {

            for (auto& _onepixelInfo : _rowpixelsInfo.pixelDeeps) {

                if (isnan(_onepixelInfo.rgb[0])) {
                    continue;
                }

                ScreenEye->putPixel(_onepixelInfo.x,_rowpixelsInfo.y,
                                    _onepixelInfo.rgb,_onepixelInfo.screenDeep,
                                    (PolygonBase*)this);
            }
        }
    }

}

void EquationThree9::deepFarNearBackCenter(){
    frameScreenFar = virtual_scanBox3D.center.z;
    frameScreenNear = virtual_scanBox3D.center.z;
}
void EquationThree9::setFrontColor(int _color1, int _color2,int _color3){
    BGR3f colorNow;
    colorNow.setBGR(_color1,1);
    frontColor1_rgb01[0] = colorNow.r1;
    frontColor1_rgb01[1] = colorNow.g1;
    frontColor1_rgb01[2] = colorNow.b1;

    colorNow.setBGR(_color2,1);
    frontColor2_rgb01[0] = colorNow.r1;
    frontColor2_rgb01[1] = colorNow.g1;
    frontColor2_rgb01[2] = colorNow.b1;

    colorNow.setBGR(_color3,1);
    frontColor3_rgb01[0] = colorNow.r1;
    frontColor3_rgb01[1] = colorNow.g1;
    frontColor3_rgb01[2] = colorNow.b1;
}
void EquationThree9::freshGoX(){
    world_toX.dx = (scanBox3D.rtnSet.x - scanBox3D.ltnSet.x) / boxLenX;
    world_toX.dy = (scanBox3D.rtnSet.y - scanBox3D.ltnSet.y) / boxLenX;
    world_toX.dz = (scanBox3D.rtnSet.z - scanBox3D.ltnSet.z) / boxLenX;
}
void EquationThree9::freshGoY(){
    world_toY.dx = (scanBox3D.lbnSet.x - scanBox3D.ltnSet.x) / boxLenY;
    world_toY.dy = (scanBox3D.lbnSet.y - scanBox3D.ltnSet.y) / boxLenY;
    world_toY.dz = (scanBox3D.lbnSet.z - scanBox3D.ltnSet.z) / boxLenY;
}
void EquationThree9::freshGoDEEP() {
    world_toDEEP.dx = (scanBox3D.ltfSet.x - scanBox3D.ltnSet.x) / boxLenZ;
    world_toDEEP.dy = (scanBox3D.ltfSet.y - scanBox3D.ltnSet.y) / boxLenZ;
    world_toDEEP.dz = (scanBox3D.ltfSet.z - scanBox3D.ltnSet.z) / boxLenZ;
//    world_toDEEP = ScreenDemo::get_AgoB_direction3D(scanBox3D.ltnSet, scanBox3D.ltfSet);
}
glm::vec3 EquationThree9::goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toX._;
    return _srcXYZ;
}
glm::vec3 EquationThree9::goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toY._;
    return _srcXYZ;
}
glm::vec3 EquationThree9::goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toDEEP._;
    return _srcXYZ;
}
array<double, 10> EquationThree9::getCoefficents(double ex, double ey, double ez,
                                 double dx, double dy, double dz){
    // Hey, I'm correct!
    std::array<double, 10> result;
    double a = abcd[0];
    double b = abcd[1];
    double c = abcd[2];
    double d = abcd[3];

    double l9 = -64 * pow5(a) * pow9(dx);
    double l8 = -576 * pow5(a) * pow8(dx) * ex - 192 * pow4(a) * b * pow8(dx);
    double l7 = (-2304 * pow5(a) * pow7(dx) * pow2(ex) - 1536 * pow4(a) * b * pow7(dx) * ex
                 - 96 * pow4(a) * c * pow7(dx) + 48 * pow4(a) * pow6(dx) * dy - 224 * pow3(a) * pow2(b) * pow7(dx));
    double l6 = (-5376 * pow5(a) * pow6(dx) * pow3(ex) - 5376 * pow4(a) * b * pow6(dx) * pow2(ex)
                 - 672 * pow4(a) * c * pow6(dx) * ex - 48 * pow4(a) * d * pow6(dx)
                 + 48 * pow4(a) * pow6(dx) * ey + 288 * pow4(a) * pow5(dx) * dy * ex
                 - 1568 * pow3(a) * pow2(b) * pow6(dx) * ex - 208 * pow3(a) * b * c * pow6(dx)
                 + 96 * pow3(a) * b * pow5(dx) * dy - 128 * pow2(a) * pow3(b) * pow6(dx));
    double l5 = (-8064 * pow5(a) * pow5(dx) * pow4(ex) - 10752 * pow4(a) * b * pow5(dx) * pow3(ex)
                 - 2016 * pow4(a) * c * pow5(dx) * pow2(ex) - 288 * pow4(a) * d * pow5(dx) * ex
                 + 288 * pow4(a) * pow5(dx) * ex * ey + 720 * pow4(a) * pow4(dx) * dy * pow2(ex)
                 - 4704 * pow3(a) * pow2(b) * pow5(dx) * pow2(ex) - 1248 * pow3(a) * b * c * pow5(dx) * ex
                 - 96 * pow3(a) * b * d * pow5(dx) + 96 * pow3(a) * b * pow5(dx) * ey
                 + 480 * pow3(a) * b * pow4(dx) * dy * ex - 36 * pow3(a) * pow2(c) * pow5(dx)
                 + 12 * pow3(a) * c * pow4(dx) * dy + 15 * pow3(a) * pow3(dx) * pow2(dy)
                 + 27 * pow3(a) * pow3(dx) * pow2(dz) - 768 * pow2(a) * pow3(b) * pow5(dx) * ex
                 - 168 * pow2(a) * pow2(b) * c * pow5(dx) + 76 * pow2(a) * pow2(b) * pow4(dx) * dy
                 - 36 * a * pow4(b) * pow5(dx));
    double l4 = (-8064 * pow5(a) * pow4(dx) * pow5(ex) - 13440 * pow4(a) * b * pow4(dx) * pow4(ex)
                 - 3360 * pow4(a) * c * pow4(dx) * pow3(ex) - 720 * pow4(a) * d * pow4(dx) * pow2(ex)
                 + 720 * pow4(a) * pow4(dx) * pow2(ex) * ey + 960 * pow4(a) * pow3(dx) * dy * pow3(ex)
                 - 7840 * pow3(a) * pow2(b) * pow4(dx) * pow3(ex) - 3120 * pow3(a) * b * c * pow4(dx) * pow2(ex)
                 - 480 * pow3(a) * b * d * pow4(dx) * ex + 480 * pow3(a) * b * pow4(dx) * ex * ey
                 + 960 * pow3(a) * b * pow3(dx) * dy * pow2(ex) - 180 * pow3(a) * pow2(c) * pow4(dx) * ex
                 - 12 * pow3(a) * c * d * pow4(dx) + 12 * pow3(a) * c * pow4(dx) * ey
                 + 48 * pow3(a) * c * pow3(dx) * dy * ex - 30 * pow3(a) * d * pow3(dx) * dy
                 + 30 * pow3(a) * pow3(dx) * dy * ey + 54 * pow3(a) * pow3(dx) * dz * ez
                 + 45 * pow3(a) * pow2(dx) * pow2(dy) * ex + 81 * pow3(a) * pow2(dx) * pow2(dz) * ex
                 - 1920 * pow2(a) * pow3(b) * pow4(dx) * pow2(ex) - 840 * pow2(a) * pow2(b) * c * pow4(dx) * ex
                 - 76 * pow2(a) * pow2(b) * d * pow4(dx) + 76 * pow2(a) * pow2(b) * pow4(dx) * ey
                 + 304 * pow2(a) * pow2(b) * pow3(dx) * dy * ex - 56 * pow2(a) * b * pow2(c) * pow4(dx)
                 + 26 * pow2(a) * b * c * pow3(dx) * dy + 15 * pow2(a) * b * pow2(dx) * pow2(dy)
                 + 27 * pow2(a) * b * pow2(dx) * pow2(dz) - 180 * a * pow4(b) * pow4(dx) * ex
                 - 60 * a * pow3(b) * c * pow4(dx) + 28 * a * pow3(b) * pow3(dx) * dy - 4 * pow5(b) * pow4(dx));
    double l3 = (-5376 * pow5(a) * pow3(dx) * pow6(ex) - 10752 * pow4(a) * b * pow3(dx) * pow5(ex)
                 - 3360 * pow4(a) * c * pow3(dx) * pow4(ex) - 960 * pow4(a) * d * pow3(dx) * pow3(ex)
                 + 960 * pow4(a) * pow3(dx) * pow3(ex) * ey + 720 * pow4(a) * pow2(dx) * dy * pow4(ex)
                 - 7840 * pow3(a) * pow2(b) * pow3(dx) * pow4(ex) - 4160 * pow3(a) * b * c * pow3(dx) * pow3(ex)
                 - 960 * pow3(a) * b * d * pow3(dx) * pow2(ex) + 960 * pow3(a) * b * pow3(dx) * pow2(ex) * ey
                 + 960 * pow3(a) * b * pow2(dx) * dy * pow3(ex) - 360 * pow3(a) * pow2(c) * pow3(dx) * pow2(ex)
                 - 48 * pow3(a) * c * d * pow3(dx) * ex + 48 * pow3(a) * c * pow3(dx) * ex * ey
                 + 72 * pow3(a) * c * pow2(dx) * dy * pow2(ex) + 15 * pow3(a) * pow2(d) * pow3(dx)
                 - 30 * pow3(a) * d * pow3(dx) * ey - 90 * pow3(a) * d * pow2(dx) * dy * ex
                 + 15 * pow3(a) * pow3(dx) * pow2(ey) + 27 * pow3(a) * pow3(dx) * pow2(ez)
                 + 90 * pow3(a) * pow2(dx) * dy * ex * ey + 162 * pow3(a) * pow2(dx) * dz * ex * ez
                 + 45 * pow3(a) * dx * pow2(dy) * pow2(ex) + 81 * pow3(a) * dx * pow2(dz) * pow2(ex)
                 - 2560 * pow2(a) * pow3(b) * pow3(dx) * pow3(ex) - 1680 * pow2(a) * pow2(b) * c * pow3(dx) * pow2(ex)
                 - 304 * pow2(a) * pow2(b) * d * pow3(dx) * ex + 304 * pow2(a) * pow2(b) * pow3(dx) * ex * ey
                 + 456 * pow2(a) * pow2(b) * pow2(dx) * dy * pow2(ex) - 224 * pow2(a) * b * pow2(c) * pow3(dx) * ex
                 - 26 * pow2(a) * b * c * d * pow3(dx) + 26 * pow2(a) * b * c * pow3(dx) * ey
                 + 78 * pow2(a) * b * c * pow2(dx) * dy * ex - 30 * pow2(a) * b * d * pow2(dx) * dy
                 + 30 * pow2(a) * b * pow2(dx) * dy * ey + 54 * pow2(a) * b * pow2(dx) * dz * ez
                 + 30 * pow2(a) * b * dx * pow2(dy) * ex + 54 * pow2(a) * b * dx * pow2(dz) * ex
                 - 4 * pow2(a) * pow3(c) * pow3(dx) + 3 * pow2(a) * c * dx * pow2(dy) + pow2(a) * pow3(dy)
                 - 360 * a * pow4(b) * pow3(dx) * pow2(ex) - 240 * a * pow3(b) * c * pow3(dx) * ex
                 - 28 * a * pow3(b) * d * pow3(dx) + 28 * a * pow3(b) * pow3(dx) * ey
                 + 84 * a * pow3(b) * pow2(dx) * dy * ex - 29 * a * pow2(b) * pow2(c) * pow3(dx)
                 + 18 * a * pow2(b) * c * pow2(dx) * dy + 4 * a * pow2(b) * dx * pow2(dy)
                 + 9 * a * pow2(b) * dx * pow2(dz) - 16 * pow5(b) * pow3(dx) * ex - 8 * pow4(b) * c * pow3(dx)
                 + 4 * pow4(b) * pow2(dx) * dy);
    double l2 = (-2304 * pow5(a) * pow2(dx) * pow7(ex) - 5376 * pow4(a) * b * pow2(dx) * pow6(ex)
                 - 2016 * pow4(a) * c * pow2(dx) * pow5(ex) - 720 * pow4(a) * d * pow2(dx) * pow4(ex)
                 + 720 * pow4(a) * pow2(dx) * pow4(ex) * ey + 288 * pow4(a) * dx * dy * pow5(ex)
                 - 4704 * pow3(a) * pow2(b) * pow2(dx) * pow5(ex) - 3120 * pow3(a) * b * c * pow2(dx) * pow4(ex)
                 - 960 * pow3(a) * b * d * pow2(dx) * pow3(ex) + 960 * pow3(a) * b * pow2(dx) * pow3(ex) * ey
                 + 480 * pow3(a) * b * dx * dy * pow4(ex) - 360 * pow3(a) * pow2(c) * pow2(dx) * pow3(ex)
                 - 72 * pow3(a) * c * d * pow2(dx) * pow2(ex) + 72 * pow3(a) * c * pow2(dx) * pow2(ex) * ey
                 + 48 * pow3(a) * c * dx * dy * pow3(ex) + 45 * pow3(a) * pow2(d) * pow2(dx) * ex
                 - 90 * pow3(a) * d * pow2(dx) * ex * ey - 90 * pow3(a) * d * dx * dy * pow2(ex)
                 + 45 * pow3(a) * pow2(dx) * ex * pow2(ey) + 81 * pow3(a) * pow2(dx) * ex * pow2(ez)
                 + 90 * pow3(a) * dx * dy * pow2(ex) * ey + 162 * pow3(a) * dx * dz * pow2(ex) * ez
                 + 15 * pow3(a) * pow2(dy) * pow3(ex) + 27 * pow3(a) * pow2(dz) * pow3(ex)
                 - 1920 * pow2(a) * pow3(b) * pow2(dx) * pow4(ex) - 1680 * pow2(a) * pow2(b) * c * pow2(dx) * pow3(ex)
                 - 456 * pow2(a) * pow2(b) * d * pow2(dx) * pow2(ex) + 456 * pow2(a) * pow2(b) * pow2(dx) * pow2(ex) * ey
                 + 304 * pow2(a) * pow2(b) * dx * dy * pow3(ex) - 336 * pow2(a) * b * pow2(c) * pow2(dx) * pow2(ex)
                 - 78 * pow2(a) * b * c * d * pow2(dx) * ex + 78 * pow2(a) * b * c * pow2(dx) * ex * ey
                 + 78 * pow2(a) * b * c * dx * dy * pow2(ex) + 15 * pow2(a) * b * pow2(d) * pow2(dx)
                 - 30 * pow2(a) * b * d * pow2(dx) * ey - 60 * pow2(a) * b * d * dx * dy * ex
                 + 15 * pow2(a) * b * pow2(dx) * pow2(ey) + 27 * pow2(a) * b * pow2(dx) * pow2(ez)
                 + 60 * pow2(a) * b * dx * dy * ex * ey + 108 * pow2(a) * b * dx * dz * ex * ez
                 + 15 * pow2(a) * b * pow2(dy) * pow2(ex) + 27 * pow2(a) * b * pow2(dz) * pow2(ex)
                 - 12 * pow2(a) * pow3(c) * pow2(dx) * ex - 6 * pow2(a) * c * d * dx * dy
                 + 6 * pow2(a) * c * dx * dy * ey + 3 * pow2(a) * c * pow2(dy) * ex - 3 * pow2(a) * d * pow2(dy)
                 + 3 * pow2(a) * pow2(dy) * ey - 360 * a * pow4(b) * pow2(dx) * pow3(ex)
                 - 360 * a * pow3(b) * c * pow2(dx) * pow2(ex) - 84 * a * pow3(b) * d * pow2(dx) * ex
                 + 84 * a * pow3(b) * pow2(dx) * ex * ey + 84 * a * pow3(b) * dx * dy * pow2(ex)
                 - 87 * a * pow2(b) * pow2(c) * pow2(dx) * ex - 18 * a * pow2(b) * c * d * pow2(dx)
                 + 18 * a * pow2(b) * c * pow2(dx) * ey + 36 * a * pow2(b) * c * dx * dy * ex
                 - 8 * a * pow2(b) * d * dx * dy + 8 * a * pow2(b) * dx * dy * ey
                 + 18 * a * pow2(b) * dx * dz * ez + 4 * a * pow2(b) * pow2(dy) * ex
                 + 9 * a * pow2(b) * pow2(dz) * ex - 4 * a * b * pow3(c) * pow2(dx)
                 + 2 * a * b * pow2(c) * dx * dy + 2 * a * b * c * pow2(dy) - 24 * pow5(b) * pow2(dx) * pow2(ex)
                 - 24 * pow4(b) * c * pow2(dx) * ex - 4 * pow4(b) * d * pow2(dx) + 4 * pow4(b) * pow2(dx) * ey
                 + 8 * pow4(b) * dx * dy * ex - 5 * pow3(b) * pow2(c) * pow2(dx) + 4 * pow3(b) * c * dx * dy
                 + pow3(b) * pow2(dz));
    double l1 = (-576 * pow5(a) * dx * pow8(ex) - 1536 * pow4(a) * b * dx * pow7(ex)
                 - 672 * pow4(a) * c * dx * pow6(ex) - 288 * pow4(a) * d * dx * pow5(ex)
                 + 288 * pow4(a) * dx * pow5(ex) * ey + 48 * pow4(a) * dy * pow6(ex)
                 - 1568 * pow3(a) * pow2(b) * dx * pow6(ex) - 1248 * pow3(a) * b * c * dx * pow5(ex)
                 - 480 * pow3(a) * b * d * dx * pow4(ex) + 480 * pow3(a) * b * dx * pow4(ex) * ey
                 + 96 * pow3(a) * b * dy * pow5(ex) - 180 * pow3(a) * pow2(c) * dx * pow4(ex)
                 - 48 * pow3(a) * c * d * dx * pow3(ex) + 48 * pow3(a) * c * dx * pow3(ex) * ey
                 + 12 * pow3(a) * c * dy * pow4(ex) + 45 * pow3(a) * pow2(d) * dx * pow2(ex)
                 - 90 * pow3(a) * d * dx * pow2(ex) * ey - 30 * pow3(a) * d * dy * pow3(ex)
                 + 45 * pow3(a) * dx * pow2(ex) * pow2(ey) + 81 * pow3(a) * dx * pow2(ex) * pow2(ez)
                 + 30 * pow3(a) * dy * pow3(ex) * ey + 54 * pow3(a) * dz * pow3(ex) * ez
                 - 768 * pow2(a) * pow3(b) * dx * pow5(ex) - 840 * pow2(a) * pow2(b) * c * dx * pow4(ex)
                 - 304 * pow2(a) * pow2(b) * d * dx * pow3(ex) + 304 * pow2(a) * pow2(b) * dx * pow3(ex) * ey
                 + 76 * pow2(a) * pow2(b) * dy * pow4(ex) - 224 * pow2(a) * b * pow2(c) * dx * pow3(ex)
                 - 78 * pow2(a) * b * c * d * dx * pow2(ex) + 78 * pow2(a) * b * c * dx * pow2(ex) * ey
                 + 26 * pow2(a) * b * c * dy * pow3(ex) + 30 * pow2(a) * b * pow2(d) * dx * ex
                 - 60 * pow2(a) * b * d * dx * ex * ey - 30 * pow2(a) * b * d * dy * pow2(ex)
                 + 30 * pow2(a) * b * dx * ex * pow2(ey) + 54 * pow2(a) * b * dx * ex * pow2(ez)
                 + 30 * pow2(a) * b * dy * pow2(ex) * ey + 54 * pow2(a) * b * dz * pow2(ex) * ez
                 - 12 * pow2(a) * pow3(c) * dx * pow2(ex) + 3 * pow2(a) * c * pow2(d) * dx
                 - 6 * pow2(a) * c * d * dx * ey - 6 * pow2(a) * c * d * dy * ex
                 + 3 * pow2(a) * c * dx * pow2(ey) + 6 * pow2(a) * c * dy * ex * ey
                 + 3 * pow2(a) * pow2(d) * dy - 6 * pow2(a) * d * dy * ey + 3 * pow2(a) * dy * pow2(ey)
                 - 180 * a * pow4(b) * dx * pow4(ex) - 240 * a * pow3(b) * c * dx * pow3(ex)
                 - 84 * a * pow3(b) * d * dx * pow2(ex) + 84 * a * pow3(b) * dx * pow2(ex) * ey
                 + 28 * a * pow3(b) * dy * pow3(ex) - 87 * a * pow2(b) * pow2(c) * dx * pow2(ex)
                 - 36 * a * pow2(b) * c * d * dx * ex + 36 * a * pow2(b) * c * dx * ex * ey
                 + 18 * a * pow2(b) * c * dy * pow2(ex) + 4 * a * pow2(b) * pow2(d) * dx
                 - 8 * a * pow2(b) * d * dx * ey - 8 * a * pow2(b) * d * dy * ex
                 + 4 * a * pow2(b) * dx * pow2(ey) + 9 * a * pow2(b) * dx * pow2(ez)
                 + 8 * a * pow2(b) * dy * ex * ey + 18 * a * pow2(b) * dz * ex * ez
                 - 8 * a * b * pow3(c) * dx * ex - 2 * a * b * pow2(c) * d * dx
                 + 2 * a * b * pow2(c) * dx * ey + 2 * a * b * pow2(c) * dy * ex
                 - 4 * a * b * c * d * dy + 4 * a * b * c * dy * ey - 16 * pow5(b) * dx * pow3(ex)
                 - 24 * pow4(b) * c * dx * pow2(ex) - 8 * pow4(b) * d * dx * ex + 8 * pow4(b) * dx * ex * ey
                 + 4 * pow4(b) * dy * pow2(ex) - 10 * pow3(b) * pow2(c) * dx * ex - 4 * pow3(b) * c * d * dx
                 + 4 * pow3(b) * c * dx * ey + 4 * pow3(b) * c * dy * ex + 2 * pow3(b) * dz * ez
                 - pow2(b) * pow3(c) * dx + pow2(b) * pow2(c) * dy);
    double l0 = (-64 * pow5(a) * pow9(ex) - 192 * pow4(a) * b * pow8(ex) - 96 * pow4(a) * c * pow7(ex)
                 - 48 * pow4(a) * d * pow6(ex) + 48 * pow4(a) * pow6(ex) * ey - 224 * pow3(a) * pow2(b) * pow7(ex)
                 - 208 * pow3(a) * b * c * pow6(ex) - 96 * pow3(a) * b * d * pow5(ex)
                 + 96 * pow3(a) * b * pow5(ex) * ey - 36 * pow3(a) * pow2(c) * pow5(ex)
                 - 12 * pow3(a) * c * d * pow4(ex) + 12 * pow3(a) * c * pow4(ex) * ey
                 + 15 * pow3(a) * pow2(d) * pow3(ex) - 30 * pow3(a) * d * pow3(ex) * ey
                 + 15 * pow3(a) * pow3(ex) * pow2(ey) + 27 * pow3(a) * pow3(ex) * pow2(ez)
                 - 128 * pow2(a) * pow3(b) * pow6(ex) - 168 * pow2(a) * pow2(b) * c * pow5(ex)
                 - 76 * pow2(a) * pow2(b) * d * pow4(ex) + 76 * pow2(a) * pow2(b) * pow4(ex) * ey
                 - 56 * pow2(a) * b * pow2(c) * pow4(ex) - 26 * pow2(a) * b * c * d * pow3(ex)
                 + 26 * pow2(a) * b * c * pow3(ex) * ey + 15 * pow2(a) * b * pow2(d) * pow2(ex)
                 - 30 * pow2(a) * b * d * pow2(ex) * ey + 15 * pow2(a) * b * pow2(ex) * pow2(ey)
                 + 27 * pow2(a) * b * pow2(ex) * pow2(ez) - 4 * pow2(a) * pow3(c) * pow3(ex)
                 + 3 * pow2(a) * c * pow2(d) * ex - 6 * pow2(a) * c * d * ex * ey
                 + 3 * pow2(a) * c * ex * pow2(ey) - pow2(a) * pow3(d) + 3 * pow2(a) * pow2(d) * ey
                 - 3 * pow2(a) * d * pow2(ey) + pow2(a) * pow3(ey) - 36 * a * pow4(b) * pow5(ex)
                 - 60 * a * pow3(b) * c * pow4(ex) - 28 * a * pow3(b) * d * pow3(ex)
                 + 28 * a * pow3(b) * pow3(ex) * ey - 29 * a * pow2(b) * pow2(c) * pow3(ex)
                 - 18 * a * pow2(b) * c * d * pow2(ex) + 18 * a * pow2(b) * c * pow2(ex) * ey
                 + 4 * a * pow2(b) * pow2(d) * ex - 8 * a * pow2(b) * d * ex * ey
                 + 4 * a * pow2(b) * ex * pow2(ey) + 9 * a * pow2(b) * ex * pow2(ez)
                 - 4 * a * b * pow3(c) * pow2(ex) - 2 * a * b * pow2(c) * d * ex
                 + 2 * a * b * pow2(c) * ex * ey + 2 * a * b * c * pow2(d) - 4 * a * b * c * d * ey
                 + 2 * a * b * c * pow2(ey) - 4 * pow5(b) * pow4(ex) - 8 * pow4(b) * c * pow3(ex)
                 - 4 * pow4(b) * d * pow2(ex) + 4 * pow4(b) * pow2(ex) * ey - 5 * pow3(b) * pow2(c) * pow2(ex)
                 - 4 * pow3(b) * c * d * ex + 4 * pow3(b) * c * ex * ey + pow3(b) * pow2(ez)
                 - pow2(b) * pow3(c) * ex - pow2(b) * pow2(c) * d + pow2(b) * pow2(c) * ey);

    result[0] = l9;
    result[1] = l8;
    result[2] = l7;
    result[3] = l6;
    result[4] = l5;
    result[5] = l4;
    result[6] = l3;
    result[7] = l2;
    result[8] = l1;
    result[9] = l0;

    return result;

}
array<double, 10> EquationThree9::getCoefficents2(double ex, double ey, double ez,
                                  double dx, double dy, double dz){
    // I'm correct too.
    double a = abcd[0];
    double b = abcd[1];
    double c = abcd[2];
    double d = abcd[3];

    double A = -pow2(a) * pow3(dx);
    double B = -pow2(a) * 3 * ex * pow2(dx) - a*b*pow2(dx);
    double C = -pow2(a) * 3 * pow2(ex) * dx - a*b*2*ex*dx - a*c*dx + a*dy;
    double D = a*ey - pow2(a) * pow3(ex) - a*b*pow2(ex) - a*d - a*c*ex;

    double E = -a * pow3(dx);
    double F = -a * 3 * ex * pow2(dx) - b * pow2(dx);
    double G = -a * 3 * pow2(ex) * dx - b * 2 * ex * dx - c * dx + dy;
    double H = ey - a * pow3(ex) - b * pow2(ex) - d - c * ex;

    double I = -2 * pow2(a) * 3 * pow2(dx);
    double J = -2 * pow2(a) * 6 * ex * dx - 2 * a * b * 2 * dx;
    double K = -2 * pow2(a) * 3 * pow2(ex) - 4 * a * b * ex - 2 * a * c;

    double L = -a * 3 * dx;
    double M = -a * 3 * ex - b;

    double N = a * 3 * pow2(dx);
    double O = a * 6 * ex * dx + b * 2 * dx;
    double P = a * 3 * pow2(ex) + 2 * b * ex + c;

    double Q = dy - a * 3 * pow2(ex) * dx - b * 2 * ex * dx - c * dx;
    double R = ey - a * pow3(ex) - b * pow2(ex) - d - c * ex;

    double S = pow2(dz);
    double T = 2 * dz * ez;
    double U = pow2(ez);

    double V = -a * 3 * dx;

    double l9 = pow2(A) * E + pow2(E) * I * L + E * pow2(L) * pow2(N);
    double l8 = pow2(A) * F + 2 * A * B * E + pow2(E) * I * M
                + pow2(E) * J * L + 2 * E * F * I * L + 2 * E * pow2(L) * N * O
                + 2 * E * L * M * pow2(N) + F * pow2(L) * pow2(N);
    double l7 = pow2(A) * G + 2 * A * B * F + 2 * A * C * E + pow2(B) * E
                + pow2(E) * J * M + pow2(E) * K * L + 2 * E * F * I * M
                + 2 * E * F * J * L + 2 * E * G * I * L + 2 * E * pow2(L) * N * P
                + E * pow2(L) * pow2(O) + 4 * E * L * M * N * O + E * pow2(M) * pow2(N)
                + pow2(F) * I * L + 2 * F * pow2(L) * N * O + 2 * F * L * M * pow2(N)
                + pow2(L) * pow2(N) * Q;
    double l6 = pow2(A) * H + 2 * A * B * G + 2 * A * C * F + 2 * A * D * E
                + pow2(B) * F + 2 * B * C * E + pow2(E) * K * M + 2 * E * F * J * M
                + 2 * E * F * K * L + 2 * E * G * I * M + 2 * E * G * J * L
                + 2 * E * H * I * L + 2 * E * pow2(L) * O * P + 4 * E * L * M * N * P
                + 2 * E * L * M * pow2(O) + 2 * E * pow2(M) * N * O + pow2(F) * I * M
                + pow2(F) * J * L + 2 * F * G * I * L + 2 * F * pow2(L) * N * P
                + F * pow2(L) * pow2(O) + 4 * F * L * M * N * O + F * pow2(M) * pow2(N)
                + pow2(L) * pow2(N) * R + 2 * pow2(L) * N * O * Q + 2 * L * M * pow2(N) * Q;
    double l5 = 2 * A * B * H + 2 * A * C * G + 2 * A * D * F + pow2(B) * G
                + 2 * B * C * F + 2 * B * D * E + pow2(C) * E + 2 * E * F * K * M
                + 2 * E * G * J * M + 2 * E * G * K * L + 2 * E * H * I * M
                + 2 * E * H * J * L + E * pow2(L) * pow2(P) + 4 * E * L * M * O * P
                + 2 * E * pow2(M) * N * P + E * pow2(M) * pow2(O) + pow2(F) * J * M
                + pow2(F) * K * L + 2 * F * G * I * M + 2 * F * G * J * L
                + 2 * F * H * I * L + 2 * F * pow2(L) * O * P + 4 * F * L * M * N * P
                + 2 * F * L * M * pow2(O) + 2 * F * pow2(M) * N * O + pow2(G) * I * L
                + 2 * pow2(L) * N * O * R + 2 * pow2(L) * N * P * Q + pow2(L) * pow2(O) * Q
                + 2 * L * M * pow2(N) * R + 4 * L * M * N * O * Q + pow2(M) * pow2(N) * Q
                - S * pow3(V);
    double l4 = 2 * A * C * H + 2 * A * D * G + pow2(B) * H + 2 * B * C * G
                + 2 * B * D * F + pow2(C) * F + 2 * C * D * E + 2 * E * G * K * M
                + 2 * E * H * J * M + 2 * E * H * K * L + 2 * E * L * M * pow2(P)
                + 2 * E * pow2(M) * O * P + pow2(F) * K * M + 2 * F * G * J * M
                + 2 * F * G * K * L + 2 * F * H * I * M + 2 * F * H * J * L
                + F * pow2(L) * pow2(P) + 4 * F * L * M * O * P + 2 * F * pow2(M) * N * P
                + F * pow2(M) * pow2(O) + pow2(G) * I * M + pow2(G) * J * L + 2 * G * H * I * L
                + 2 * pow2(L) * N * P * R + pow2(L) * pow2(O) * R + 2 * pow2(L) * O * P * Q
                + 4 * L * M * N * O * R + 4 * L * M * N * P * Q + 2 * L * M * pow2(O) * Q
                + pow2(M) * pow2(N) * R + 2 * pow2(M) * N * O * Q - 3 * M * S * pow2(V)
                - T * pow3(V);
    double l3 = 2 * A * D * H + 2 * B * C * H + 2 * B * D * G + pow2(C) * G
                + 2 * C * D * F + pow2(D) * E + 2 * E * H * K * M + E * pow2(M) * pow2(P)
                + 2 * F * G * K * M + 2 * F * H * J * M + 2 * F * H * K * L
                + 2 * F * L * M * pow2(P) + 2 * F * pow2(M) * O * P + pow2(G) * J * M
                + pow2(G) * K * L + 2 * G * H * I * M + 2 * G * H * J * L
                + pow2(H) * I * L + 2 * pow2(L) * O * P * R + pow2(L) * pow2(P) * Q
                + 4 * L * M * N * P * R + 2 * L * M * pow2(O) * R + 4 * L * M * O * P * Q
                + 2 * pow2(M) * N * O * R + 2 * pow2(M) * N * P * Q + pow2(M) * pow2(O) * Q
                - 3 * pow2(M) * S * V - 3 * M * T * pow2(V) - U * pow3(V);
    double l2 = 2 * B * D * H + pow2(C) * H + 2 * C * D * G + pow2(D) * F
                + 2 * F * H * K * M + F * pow2(M) * pow2(P) + pow2(G) * K * M
                + 2 * G * H * J * M + 2 * G * H * K * L + pow2(H) * I * M
                + pow2(H) * J * L + pow2(L) * pow2(P) * R + 4 * L * M * O * P * R
                + 2 * L * M * pow2(P) * Q - pow3(M) * S + 2 * pow2(M) * N * P * R
                + pow2(M) * pow2(O) * R + 2 * pow2(M) * O * P * Q - 3 * pow2(M) * T * V
                - 3 * M * U * pow2(V);
    double l1 = 2 * C * D * H + pow2(D) * G + 2 * G * H * K * M + pow2(H) * J * M
                + pow2(H) * K * L + 2 * L * M * pow2(P) * R - pow3(M) * T
                + 2 * pow2(M) * O * P * R + pow2(M) * pow2(P) * Q - 3 * pow2(M) * U * V;
    double l0 = pow2(D) * H + pow2(H) * K * M - pow3(M) * U + pow2(M) * pow2(P) * R;

    array<double, 10> result = {l9, l8, l7, l6, l5, l4, l3, l2, l1, l0};

    return result;
}
array<complex<double>,9> EquationThree9::solveNonic(complex<double> A, complex<double> B, complex<double> C,
                                                  complex<double> D, complex<double> E, complex<double> F,
                                                  complex<double> G, complex<double> H, complex<double> I,
                                                  complex<double> J){
    if (A.real() == 0 && A.imag() == 0){
        println(stderr,"Coefficient A: ({},{}) cannot be zero",A.real(),A.imag());
        A = {1e-10};
    }



    // 归一化为monic多项式 x^9 + b x^8 + ... + j
    complex<double> b(B/A), c(C/A), d(D/A), e(E/A), f(F/A);
    complex<double> g(G/A), h(H/A), i(I/A), j(J/A);

//     DEBUG_SECTION(
//     print("fixed2 b:({},{})",b.real(),b.imag());
//     print("c:({},{})",c.real(),c.imag());
//     print("d:({},{})\n",d.real(),d.imag());
//     print("e:({},{})",e.real(),e.imag());
//     print("f:({},{})",f.real(),f.imag());
//     print("g:({},{})",g.real(),g.imag());
//     print("h:({},{})\n",h.real(),h.imag());
//     print("i:({},{})",i.real(),i.imag());
//     print("j:({},{})\n",j.real(),j.imag());
// )

    // 构建9x9伴随矩阵
    Eigen::MatrixXcd companion(9, 9);
    companion <<
              0,0,0,0,0,0,0,0,-j,
            1,0,0,0,0,0,0,0,-i,
            0,1,0,0,0,0,0,0,-h,
            0,0,1,0,0,0,0,0,-g,
            0,0,0,1,0,0,0,0,-f,
            0,0,0,0,1,0,0,0,-e,
            0,0,0,0,0,1,0,0,-d,
            0,0,0,0,0,0,1,0,-c,
            0,0,0,0,0,0,0,1,-b;

    // 计算特征值
    Eigen::ComplexEigenSolver<Eigen::MatrixXcd> solver;
    solver.compute(companion);

    if (solver.info() != Eigen::Success)
        throw runtime_error("Failed to compute eigenvalues");

    Eigen::VectorXcd roots = solver.eigenvalues();
    array<complex<double>,9> result = {roots[0], roots[1], roots[2], roots[3],
                                       roots[4], roots[5], roots[6], roots[7], roots[8]};
    return result;
}

double EquationThree9::x_img_1in2(double x_img,
                  double ex, double ey, double ez,
                  double dx, double dy, double dz,
                  double step){
    double a = abcd[0], b = abcd[1], c = abcd[2], d = abcd[3];

    double l1 = - a * pow3(x_img);
    double l2 = (a * 3 * pow2(dx) * pow2(step) + a * 6 * ex * dx * step
                 + b * 2 * dx * step + a * 3 * pow2(ex) + b * 2 * ex + c) * x_img;
    double l3  = - dz * step - ez;

    double err = l1 + l2 + l3;
    return err ;
}

double EquationThree9::get_x_img_by_step(double step,
                         double ex, double ey, double ez,
                         double dx, double dy, double dz){
    double a = abcd[0], b = abcd[1], c = abcd[2], d = abcd[3];

    double ximg_up = (-a * pow3(dx) * pow3(step)
                      - a * 3 * ex * pow2(dx) * pow2(step) - b * pow2(dx) * pow2(step)
                      - a * 3 * pow2(ex) * dx * step - b * 2 * ex * dx * step - c * dx * step
                      + dy * step - a * pow3(ex) - b * pow2(ex) - d + ey - c * ex);

    double ximg_down = (-a * 3 * dx * step - a * 3 * ex - b);

    double x_img_2 = ximg_up/ximg_down;
    if(x_img_2 < 0){
//        cerr << "! step:"<<step<<"的x_img²"<<x_img_2<<"无x_img实数解"<< endl;
        return numeric_limits<double>::quiet_NaN();
    }
    double x_img = std::sqrt(x_img_2);

    // x_img 两解 二选一
    double err_positive = x_img_1in2(x_img, ex, ey, ez, dx, dy, dz, step);
    double err_negative = x_img_1in2(-x_img, ex, ey, ez, dx, dy, dz, step);

    if (abs(err_positive) < abs(err_negative)) {
//        println("排除 -x_img:{} error: {}", -x_img, err_negative);
//        println("选择 x_img:{} error: {}", x_img, err_positive);
    }else{
//        println("排除 x_img:{} error: {}", x_img, err_positive);
//        println("选择 -x_img:{} error: {}", -x_img, err_negative);
        x_img = -x_img;

    }

    return x_img;
}
vector<pair<double, double>> EquationThree9::solve(
        double ex, double ey, double ez,
        double dx, double dy, double dz)
{

//    double a = abcd[0], b = abcd[1], c = abcd[2], d = abcd[3];

// 获取系数
    array<double, 10> coefficients = getCoefficents2(ex, ey, ez, dx, dy, dz);
//    println("a:{}, b:{}, c:{}, d:{}, ex:{}, ey:{}, ez:{}, dx:{}, dy:{}, dz:{}",
//            abcd[0],abcd[1],abcd[2],abcd[3],
//            ex,ey,ez,dx,dy,dz);
//

    // DEBUG_SECTION(
    //     println("~~ coefficients: {:.10g} {:.10g} {:.10g} {:.10g} {:.10g} {:.10g} {:.10g} {:.10g} {:.10g} {:.10g}",
    //         coefficients[0], coefficients[1], coefficients[2],
    //         coefficients[3], coefficients[4], coefficients[5], coefficients[6],
    //         coefficients[7], coefficients[8], coefficients[9]);
    // )


    array<complex<double>, 9> roots_complex;

    smallerCoef = pow(abs(coefficients[0]), -1.f/9.f);
    smallerCoef_2 = smallerCoef * smallerCoef;
    smallerCoef_3 = smallerCoef_2 * smallerCoef;
    smallerCoef_4 = smallerCoef_3 * smallerCoef;
    smallerCoef_5 = smallerCoef_4 * smallerCoef;
    smallerCoef_6 = smallerCoef_5 * smallerCoef;
    smallerCoef_7 = smallerCoef_6 * smallerCoef;
    smallerCoef_8 = smallerCoef_7 * smallerCoef;
    smallerCoef_9 = smallerCoef_8 * smallerCoef;


    coefficients[1] /= smallerCoef;
    coefficients[2]/=smallerCoef_2;
    coefficients[3]/=smallerCoef_3;
    coefficients[4]/=smallerCoef_4;
    coefficients[5]/=smallerCoef_5;
    coefficients[6]/=smallerCoef_6;
    coefficients[7]/=smallerCoef_7;
    coefficients[8]/=smallerCoef_8;
    coefficients[9]/=smallerCoef_9;
    roots_complex = solveNonic(
            complex<double>(coefficients[0], 0.f),
            complex<double>(coefficients[1], 0.f),
            complex<double>(coefficients[2], 0.f),
            complex<double>(coefficients[3], 0.f),
            complex<double>(coefficients[4], 0.f),
            complex<double>(coefficients[5], 0.f),
            complex<double>(coefficients[6], 0.f),
            complex<double>(coefficients[7], 0.f),
            complex<double>(coefficients[8], 0.f),
            complex<double>(coefficients[9], 0.f)
    );
    // DEBUG_SECTION(
    //     println("fixed coefficients: {:.10g} {:.10g} {:.10g} {:.10g} {:.10g} {:.10g} {:.10g} {:.10g} {:.10g} {:.10g}",
    //         coefficients[0], coefficients[1]/smallerCoef, coefficients[2]/smallerCoef_2,
    //         coefficients[3]/smallerCoef_3, coefficients[4]/smallerCoef_4, coefficients[5]/smallerCoef_5, coefficients[6]/smallerCoef_6,
    //         coefficients[7]/smallerCoef_7, coefficients[8]/smallerCoef_8, coefficients[9]/smallerCoef_9);
    // )


//    println(" J: {}, J/smallerCoef: {},",coefficients[9],coefficients[9]/smallerCoef_9);

// 解出9个复根
    vector<pair<double, double>> valid_pairs(9);
    double x_img,step;
    for (complex<double> _root : roots_complex) {
        _root *= smallerCoef; // 乘回来

//        cout << "complex root: " << _root << endl;
        if(abs(_root.imag()) < 0.2f){
        step = _root.real();

        x_img = get_x_img_by_step(step, ex, ey, ez, dx, dy, dz);


//        println("~~step:{}, x_img: {}",step, x_img);
        valid_pairs.emplace_back(make_pair(step, x_img));
        }
    }



    // 按step排序
    sort(valid_pairs.begin(), valid_pairs.end(),
         [](const pair<double, double>& _a, const pair<double, double>& _b) -> bool {
             return _a.first < _b.first;
         });

    return valid_pairs;
}

bool EquationThree9::selfPosInBox(glm::vec3 _selfPos){
//    return true;

    bool pointInBox = _selfPos.x > -halfBoxLength.x && _selfPos.x < halfBoxLength.x &&
                      _selfPos.y > -halfBoxLength.y && _selfPos.y < halfBoxLength.y &&
                      _selfPos.z > -halfBoxLength.z && _selfPos.z < halfBoxLength.z;
    return pointInBox;
}
RayCalcInfo24 EquationThree9::getBestSolve(double ex, double ey, double ez,
                                           double dx, double dy, double dz) {
    RayCalcInfo24 bestInfo;
    // 视线步长 实数 且>0 , 由小到大
    vector<pair<double, double>> valid_pairs = solve(ex, ey, ez, dx, dy, dz);

    if (valid_pairs.empty()) {
        // 无解 直接返回
        bestInfo.step = numeric_limits<double>::quiet_NaN();
        bestInfo.vx = numeric_limits<double>::quiet_NaN();
        bestInfo.surfacePoint_Self = glm::vec3(numeric_limits<double>::quiet_NaN());
        return bestInfo;
    }

    glm::vec3 selfSurfacePos;
    for(auto& _pair : valid_pairs){
        selfSurfacePos.x = ex + dx*_pair.first;
        selfSurfacePos.y = ey + dy*_pair.first;
        selfSurfacePos.z = ez + dz*_pair.first;
        if(selfPosInBox(selfSurfacePos) && _pair.first > 0){ // 从最近表面点 第一个在box内 ~~
            bestInfo.step = _pair.first;
            bestInfo.vx = _pair.second;
            bestInfo.surfacePoint_Self = selfSurfacePos;
//            println("~~~ bestInfo.step:{}, bestInfo.vx:{}, bestInfo.surfacePoint_Self:({},{},{})",
//                    bestInfo.step, bestInfo.vx,
//                    bestInfo.surfacePoint_Self.x, bestInfo.surfacePoint_Self.y, bestInfo.surfacePoint_Self.z);
            return bestInfo;
        }
    }
    bestInfo.step = numeric_limits<double>::quiet_NaN();
    bestInfo.vx = numeric_limits<double>::quiet_NaN();
    bestInfo.surfacePoint_Self = glm::vec3(numeric_limits<double>::quiet_NaN());
    return bestInfo;
}
unsigned char EquationThree9::getSolveBy(glm::dvec3 surfacePoint_Self, float vx){
    // 内置 一元三次方程 求根公式
    complex<double> _y = {surfacePoint_Self.y, surfacePoint_Self.z};

    complex<double> a = {abcd[0]}, b = {abcd[1]}, c = {abcd[2]}, d = {abcd[3]};
    d -= _y;
    complex<double> _x = {surfacePoint_Self.x, vx};
    // 归一化
    complex<double> p = (3.0 * a * c - b * b) / (3.0 * a * a);
    complex<double> q = (2.0 * b * b * b - 9.0 * a * b * c + 27.0 * a * a * d) / (27.0 * a * a * a);
    complex<double> w = {-0.5, sqrt(3.0) / 2.0};
    //    cout << "~~" << w.real() << " " << w.imag() << endl;
    //    Complex disc = q * q / 4.0 + p * p * p / 27.0;
    //    Complex shift = -b / 3.0;

    // 计算立方根并保证 uv 关系
    complex<double> sqrt_disc = std::sqrt(q * q / 4.0 + p * p * p / 27.0);
    complex<double> u = pow(-q / 2.0 + sqrt_disc, 1.0 / 3.0);
    complex<double> v = -p / (3.0 * u);  // 关键修正点

    double errorOk = 0.1, errorOk_2 = 0.2f;
    // 三个根的计算
    complex<double> root1 = (u + v) - b / (3.0 * a);
    double err1 = abs(root1.real() - _x.real()) + abs(root1.imag() - _x.imag());
    if(err1 < errorOk_2){
        return 1;
    }
    complex<double> root2 = (w * u + w * w * v) - b / (3.0 * a);
    double err2 = abs(root2.real() - _x.real()) + abs(root2.imag() - _x.imag());
    if(err2 < errorOk_2){
        return 2;
    }
    complex<double> root3 = (w * w * u + w * v) - b / (3.0 * a);
    double err3 = abs(root3.real() - _x.real()) + abs(root3.imag() - _x.imag());
    if(err3 < errorOk_2){
        return 3;
    }

    // 求根式 的误差 都过大
    double minErr = err1;
    unsigned char minErr_index = 1;
    if(err2 < minErr){
        minErr = err2;
        minErr_index = 2;
    }
    if(err3 < minErr){
        minErr = err3;
        minErr_index = 3;
    }
    if(minErr > 1.1f)
        println(stderr,"3次 9次 求根式 min error: {}, index: {}", minErr, minErr_index);
    return minErr_index;

}
glm::vec3 EquationThree9::getColorBy_vX(unsigned char solveBy, float _vX){
//    cout << "solve of vX:" << _vX << endl;
    int remainder = static_cast<int>(_vX) % 10; // -9~9
    float colorRatio = 1.f + 0.07f * (float)remainder;
//    cout << " ~~ remainder = " << remainder << endl;
//    cout << " ~~ colorRatio = " << colorRatio << endl;
    if(solveBy == 1){
        return frontColor1_rgb01 * colorRatio;
    }

    else if(solveBy == 2){
        return frontColor2_rgb01 * colorRatio;
    }
    else if(solveBy == 3){
        return frontColor3_rgb01 * colorRatio;
    }

    return {0.9f, 0.9f, 0.9f};

}

pair<glm::vec2, glm::vec2> EquationThree9::preCalculateParticle(double x_real, double y_real){
    double a = abcd[0], b = abcd[1], c = abcd[2], d = abcd[3];
    // (-3*a*x₀-b)*x₁²+(a*x₀³+b*x₀²+c*x₀+d-y₀)=0;
    // (-a)*x₁³+(3*a*x₀²+2*b*x₀+c)*x₁-y₁=0;
    double A1 = -3*a*x_real-b, //B1 = 0.0,
           C1 = a*pow3(x_real)+b*pow2(x_real)+c*x_real+d-y_real;

    // 检查分母非零且 -C1/A1 ≥0
    // 没用求根式 一式直接挪...
    if (A1 == 0 || (-C1 / A1) < 0) {
        return make_pair(glm::vec2{numeric_limits<double>::quiet_NaN()},
                         glm::vec2{numeric_limits<double>::quiet_NaN()});
    }

    double sqrt_val = sqrt(-C1 / A1);
    double x_imag1 = sqrt_val;
    double x_imag2 = -sqrt_val;

    // 二式
    double y_imag1 = -a * pow3(x_imag1) + (3 * a * pow2(x_real) + 2 * b * x_real + c) * x_imag1;
//    complex<double> error1 = a * pow(complex<double>(x_real, x_imag1), 3.0) + b * pow(complex<double>(x_real, x_imag1), 2.0)
//                             + c*complex<double>(x_real, x_imag1) + d - complex<double>(y_real, y_imag1);
//    if(abs(error1.real()) > 0.01 || abs(error1.imag()) > 0.01){
//        cout << "!! error1: " << error1.real() << " " << error1.imag() << endl;
//    }
    if(y_imag1 > this->halfBoxLength.z || y_imag1 < -this->halfBoxLength.z){
        y_imag1 = numeric_limits<double>::quiet_NaN();
    }
    double y_imag2 = -a * pow3(x_imag2) + (3 * a * pow2(x_real) + 2 * b * x_real + c) * x_imag2;
//    complex<double> error2 = a * pow(complex<double>(x_real, x_imag2), 3.0) + b * pow(complex<double>(x_real, x_imag2), 2.0)
//                             + c*complex<double>(x_real, x_imag2) + d - complex<double>(y_real, y_imag2);
//    if(abs(error2.real()) > 0.01 || abs(error2.imag()) > 0.01){
//        cout << "!! error2: " << error2.real() << " " << error2.imag() << endl;
//    }
    if(y_imag2 > this->halfBoxLength.z || y_imag2 < -this->halfBoxLength.z){
        y_imag2 = numeric_limits<double>::quiet_NaN();
    }
    return make_pair(glm::vec2{x_imag1, y_imag1}, glm::vec2{x_imag2, y_imag2});
}
void EquationThree9::freshVirtualGoX() {
    // 提前 求向量长度 便于归一化
//    virtual_squareEdgeLen = glm::distance(virtual_scanBox3D.ltnSet, virtual_scanBox3D.rtnSet);

    virtual_toX.dx = (virtual_scanBox3D.rtnSet.x - virtual_scanBox3D.ltnSet.x) / boxLenX;
    virtual_toX.dy = (virtual_scanBox3D.rtnSet.y - virtual_scanBox3D.ltnSet.y) / boxLenX;
    virtual_toX.dz = (virtual_scanBox3D.rtnSet.z - virtual_scanBox3D.ltnSet.z) / boxLenX;
//    virtual_toX = ScreenDemo::get_AgoB_direction3D(virtual_scanBox3D.ltnSet, virtual_scanBox3D.rtnSet);
}

void EquationThree9::freshVirtualGoY() {
    virtual_toY.dx = (virtual_scanBox3D.lbnSet.x - virtual_scanBox3D.ltnSet.x) / boxLenY;
    virtual_toY.dy = (virtual_scanBox3D.lbnSet.y - virtual_scanBox3D.ltnSet.y) / boxLenY;
    virtual_toY.dz = (virtual_scanBox3D.lbnSet.z - virtual_scanBox3D.ltnSet.z) / boxLenY;
//    virtual_toY = ScreenDemo::get_AgoB_direction3D(virtual_scanBox3D.ltnSet, virtual_scanBox3D.lbnSet);
}

void EquationThree9::freshVirtualGoDEEP() {
    virtual_toDEEP.dx = (virtual_scanBox3D.ltfSet.x - virtual_scanBox3D.ltnSet.x) / boxLenZ;
    virtual_toDEEP.dy = (virtual_scanBox3D.ltfSet.y - virtual_scanBox3D.ltnSet.y) / boxLenZ;
    virtual_toDEEP.dz = (virtual_scanBox3D.ltfSet.z - virtual_scanBox3D.ltnSet.z) / boxLenZ;
//    virtual_toDEEP = ScreenDemo::get_AgoB_direction3D(virtual_scanBox3D.ltnSet, virtual_scanBox3D.ltfSet);
}
glm::vec3 EquationThree9::Virtual_goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toX._;
    return _srcXYZ;
}
glm::vec3 EquationThree9::Virtual_goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toY._;
    return _srcXYZ;
}
glm::vec3 EquationThree9::Virtual_goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toDEEP._;
    return _srcXYZ;
}
glm::vec3 EquationThree9::self2screenAxis(glm::vec3 _selfAxisPos){
    // 屏幕系下 自己系 斜走x 斜走y 斜走z
    glm::vec3 posNow = virtual_scanBox3D.center;
    posNow = Virtual_goX(posNow, _selfAxisPos.x);
    posNow = Virtual_goY(posNow, _selfAxisPos.y);
    posNow = Virtual_goDEEP(posNow, _selfAxisPos.z);
    return posNow;
}
void EquationThree9::init_particle_info(){

//    freshVirtualGoX(); // 屏幕系 数轴三向
//    freshVirtualGoY();
//    freshVirtualGoDEEP();
    assert(this->particle_info.empty());
    this->particleStepX = 1.f;
    this->particleStepY = 1.f;
    Particle24 infoNow;

    for(float row = -halfBoxLength.y; row <= halfBoxLength.y; row+=particleStepY){
        for(float col = -halfBoxLength.x; col <= halfBoxLength.x; col+=particleStepX){

            infoNow.real = glm::vec2(col, row);

            pair<glm::vec2, glm::vec2> xy_imag_pairs = preCalculateParticle(col, row);
            if(isnan(xy_imag_pairs.first.y) || isnan(xy_imag_pairs.second.y)){
                continue;
            }
            infoNow.img1 = xy_imag_pairs.first;
            infoNow.img2 = xy_imag_pairs.second;

            infoNow.color1 = getColorBy_vX(
                    getSolveBy(glm::dvec3{col, row, infoNow.img1.y}, infoNow.img1.x),
                    infoNow.img1.x);
            infoNow.color2 = getColorBy_vX(
                    getSolveBy(glm::dvec3{col, row, infoNow.img2.y}, infoNow.img2.x),
                    infoNow.img2.x);
            particle_info.emplace_back(infoNow);

        }

    }
}
void EquationThree9::draw_particle(ScreenDemo* ScreenEye){
    for(auto& info : particle_info){
        if(isnan(info.img1.y)){
            println(stderr,"info.img1.y is nan");
        }
        glm::vec3 virtualPos1 = self2screenAxis(info.getPos1());
        glm::vec2 posNow2D1 = __3d2dEquation3_9(ScreenEye, virtualPos1.x, virtualPos1.y, virtualPos1.z);
        float color1[3] = {info.color1.r, info.color1.g, info.color1.b};
        ScreenEye->putPixel((int)posNow2D1.x, (int)posNow2D1.y, color1, virtualPos1.z, (PolygonBase*)this);


        if(isnan(info.img2.y)){
            println(stderr,"info.img2.y is nan");
        }
        glm::vec3 virtualPos2 = self2screenAxis(info.getPos2());
        glm::vec2 posNow2D2 = __3d2dEquation3_9(ScreenEye, virtualPos2.x, virtualPos2.y, virtualPos2.z);
        float color2[3] = {info.color2.r, info.color2.g, info.color2.b};
        ScreenEye->putPixel((int)posNow2D2.x, (int)posNow2D2.y, color2, virtualPos2.z, (PolygonBase*)this);


    }
}
void EquationThree9::freshFrameRotateInfo(){
    frameRotateInfo_q = PolygonBase::getFrameRotateInfo_(virtual_toX,virtual_toDEEP);
}
glm::vec3 EquationThree9::screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos){
    if(isnan(_screenAxisPos.x) || isnan(_screenAxisPos.y) || isnan(_screenAxisPos.z)){
        println(stderr,"9次 _screenAxisPos(", _screenAxisPos.x, ", ", _screenAxisPos.y, ", ", _screenAxisPos.z, ")");
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }// 不是 nan
    glm::vec3 back000 = virtual_scanBox3D.center;

    glm::vec3 p1ToWorld000 = _screenAxisPos - back000; // 归原点

    float distanceOf000 = glm::length(p1ToWorld000); // 原点距
    goLine64 p1ToWorld000_dir1 = {p1ToWorld000.x / distanceOf000,
                                  p1ToWorld000.y / distanceOf000,
                                  p1ToWorld000.z / distanceOf000}; // 归一化
    // 没两角全0  不然不用斜转

    PolygonBase::rotate_vector(p1ToWorld000_dir1, frameRotateInfo_q);
    glm::vec3 farScreenAxis000 = {(float)p1ToWorld000_dir1.dx * distanceOf000,
                                  (float)p1ToWorld000_dir1.dy * distanceOf000,
                                  (float)p1ToWorld000_dir1.dz * distanceOf000};

//    farScreenAxis000 += back000; // 离原点

    if(isnan(farScreenAxis000.x) || isnan(farScreenAxis000.y) || isnan(farScreenAxis000.z)){
        println(stderr,"9次 farScreenAxis000(", farScreenAxis000.x, ", ", farScreenAxis000.y, ", ", farScreenAxis000.z, ")");
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }
    return farScreenAxis000;
}
void EquationThree9::freshComplexRect(ScreenDemo* ScreenEye){
    // 左视 竖面
    glm::vec3 sideFlatLT_selfAxis = {0,-halfBoxLength.y, halfBoxLength.z};
    glm::vec3 sideFlatRT_selfAxis = {0,-halfBoxLength.y,-halfBoxLength.z};
    glm::vec3 sideFlatRB_selfAxis = {0,halfBoxLength.y,-halfBoxLength.z};
    glm::vec3 sideFlatLB_selfAxis = {0,halfBoxLength.y, halfBoxLength.z};

    glm::vec3 sideFlatLT_screenAxis = self2screenAxis(sideFlatLT_selfAxis);
    glm::vec3 sideFlatRT_screenAxis = self2screenAxis(sideFlatRT_selfAxis);
    glm::vec3 sideFlatRB_screenAxis = self2screenAxis(sideFlatRB_selfAxis);
    glm::vec3 sideFlatLB_screenAxis = self2screenAxis(sideFlatLB_selfAxis);

    this->sideFlatLT_2D = __3d2dEquation3_9(ScreenEye,sideFlatLT_screenAxis.x,
                                            sideFlatLT_screenAxis.y,sideFlatLT_screenAxis.z);
    this->sideFlatRT_2D = __3d2dEquation3_9(ScreenEye,sideFlatRT_screenAxis.x,
                                            sideFlatRT_screenAxis.y,sideFlatRT_screenAxis.z);
    this->sideFlatRB_2D = __3d2dEquation3_9(ScreenEye,sideFlatRB_screenAxis.x,
                                            sideFlatRB_screenAxis.y,sideFlatRB_screenAxis.z);
    this->sideFlatLB_2D = __3d2dEquation3_9(ScreenEye,sideFlatLB_screenAxis.x,
                                            sideFlatLB_screenAxis.y,sideFlatLB_screenAxis.z);

}
void EquationThree9::drawComplexRect(ScreenDemo* ScreenEye){
    // 把 复平面 框出来
    float _white[3] = {1.f, 1.f, 1.f};
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  this->sideFlatLT_2D.x,this->sideFlatLT_2D.y,
                                  this->sideFlatRT_2D.x,this->sideFlatRT_2D.y,
                                  _white,frameScreenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  this->sideFlatRT_2D.x,this->sideFlatRT_2D.y,
                                  this->sideFlatRB_2D.x,this->sideFlatRB_2D.y,
                                  _white,frameScreenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  this->sideFlatRB_2D.x,this->sideFlatRB_2D.y,
                                  this->sideFlatLB_2D.x,this->sideFlatLB_2D.y,
                                  _white,frameScreenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  this->sideFlatLB_2D.x,this->sideFlatLB_2D.y,
                                  this->sideFlatLT_2D.x,this->sideFlatLT_2D.y,
                                  _white,frameScreenNear);
}