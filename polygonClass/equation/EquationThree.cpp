//
// Created by iceoc0 on 2025/9/20.
//
#include "EquationThree.h"
// extern void* settled_ptr;
// struct _settledEquation3{
//     int _width;
//     int _height;
//     int _deep;
//     bool _byAxis;
// };
// _settledEquation3* settled_ = (_settledEquation3*)settled_ptr;
// const int screenWidth25 = settled_-> _width;
// const int screenHeight25 = settled_-> _height;
// const int screenDeep25 = settled_-> _deep;

extern void* _3d_2d_go_void_ptr; // 3d_2d_go的函数指针
// struct _3d_2d_go_equation3{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_2d)(ScreenDemo*, float, float, float);
//
// };
glm::vec2 (*__3d2dGoEquation3)(ScreenDemo*, glm::vec3, glm::vec3*) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2dEquation3)(ScreenDemo*, float, float, float) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d;

EquationThree::EquationThree(glm::vec3 srartCenter, glm::vec3 _boxLengthHalf, float a, float b, float c,float d,
unsigned char _debug_):PolygonBase(25){
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

    scanBox3D_unchange.center = scanBox3D.center;

    scanBox3D_unchange.ltnSet = scanBox3D.ltnSet;
    scanBox3D_unchange.rtnSet = scanBox3D.rtnSet;
    scanBox3D_unchange.rbnSet = scanBox3D.rbnSet;
    scanBox3D_unchange.lbnSet = scanBox3D.lbnSet;

    scanBox3D_unchange.ltfSet = scanBox3D.ltfSet;
    scanBox3D_unchange.rtfSet = scanBox3D.rtfSet;
    scanBox3D_unchange.lbfSet = scanBox3D.lbfSet;
    scanBox3D_unchange.rbfSet = scanBox3D.rbfSet;

    // startEye = {(float)screenWidth25/2.f,
    //             (float)screenHeight25/2.f,(float)-screenDeep25};

    afterMoved = false;
}
void EquationThree::setBox3D(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
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


}

void EquationThree::setBox2D(glm::vec2 _ltn, glm::vec2 _rtn, glm::vec2 _rbn, glm::vec2 _lbn,
                              glm::vec2 _ltf, glm::vec2 _rtf, glm::vec2 _rbf, glm::vec2 _lbf,
                              glm::vec2 _center

){

    scanBox2D_.set13P(_ltn, _rtn, _rbn, _lbn,
                      _ltf, _rtf, _rbf, _lbf,
                      _center);


//    renderNext = 0;
//
//    startRowIndex_ = 0;
    pixelSurfaceInfo_.clear();
    afterMoved = 1;


}
void EquationThree::Draw_Tick(ScreenDemo* ScreenEye){
//    if(afterMoved == 1){
//        println("3次 的 3次--moved");
//    }else if(afterMoved == 0){
//        println("3次 的 3次--not move");
//    }

    freshVirtualGoX(); // 屏幕系 数轴三向
    freshVirtualGoY();
    freshVirtualGoDEEP();

    if(afterMoved == 1)deepFarNearBackCenter();

    freshFrameRotateInfo(); // 转自己系 四元数

    solidRectangle2D_(ScreenEye);

    if(debugLine == 0) {
        freshComplexRect(ScreenEye);
        drawComplexRect(ScreenEye);
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
}
void EquationThree::solidRectangle2D_(ScreenDemo* ScreenEye) {
//    pixelSurfaceInfo_.clear();

    scanBox2D_.setLineBounary(lineScanFillColor_);
//    println("lineScanFillColor_ size:{}", lineScanFillColor_.size());

//    for(auto& _linePosInfo : lineScanFillColor_) { // 行循环
//        for(int i = _linePosInfo.lx; i <= _linePosInfo.rx; ++i){
//            float colorNOw[3] = {frontColor1_rgb01[0],frontColor1_rgb01[1],frontColor1_rgb01[2]};
//            ScreenEye->putPixel(i,_linePosInfo.y,
//                                colorNOw,virtual_scanBox3D.center.z-500.f,
//                                (PolygonBase*)this);
//        }
//
//    }return;
    if(afterMoved){
        for(lineBoundary& rowNow : lineScanFillColor_) {
            rowPixelInfo25 rowpixelsInfo;
            rowpixelsInfo.y = (float) rowNow.y; // 本行 y
//        println("rowNow.y:{}", rowNow.y);

            for(int nowX = (int) roundf(rowNow.lx); nowX < rowNow.rx; ++nowX) { // 单像素循环
                onepixelInfo25 onepixelInfo;

                glm::vec3 startEye_Self = screenXYZ2SelfXYZ2(startEye);
                glm::vec3 screenPoint_Self = screenXYZ2SelfXYZ2({nowX, rowNow.y, 0.f});

                goLine32 eyeRay_Self = ScreenDemo::get_AgoB_direction3D(startEye_Self, screenPoint_Self); // 计算视线

                goLine32 eyeRay_ScreenAxis = ScreenDemo::get_AgoB_direction3D(startEye, {nowX, rowNow.y, 0.f}); // 视线 屏幕坐标系

                RayCalcInfo25 nearestInBoxPoint = getBestSolve(startEye_Self.x, startEye_Self.y, startEye_Self.z,
                                                               eyeRay_Self.dx, eyeRay_Self.dy, eyeRay_Self.dz);
                if (!isnan(nearestInBoxPoint.step)) {
                    //1
                    onepixelInfo.x = (float) nowX; // 本像素 x
//                println("2d:({}, {})", onepixelInfo.x, rowpixelsInfo.y);

                    float screenDeep_ScreenAxis =
                            startEye.z + eyeRay_ScreenAxis.dz * nearestInBoxPoint.step; // 视线深度 屏幕坐标系
                    //2
                    onepixelInfo.screenDeep = screenDeep_ScreenAxis; // 像素深度 屏幕坐标系

                    if (screenDeep_ScreenAxis < frameScreenNear) {
                        frameScreenNear = screenDeep_ScreenAxis; // 刷新 近 屏垂距
                    } else if (screenDeep_ScreenAxis > frameScreenFar) {
                        frameScreenFar = screenDeep_ScreenAxis; // 刷新 远 屏垂距
                    }

                    unsigned char solveBy_ = getSolveBy(nearestInBoxPoint.surfacePoint_Self,nearestInBoxPoint.vy);
                    glm::vec3 colorNow = getColorBy_vX(solveBy_,nearestInBoxPoint.vy);

                    //3
                    onepixelInfo.rgb[0] = colorNow[0];
                    onepixelInfo.rgb[1] = colorNow[1];
                    onepixelInfo.rgb[2] = colorNow[2];
                } else {
//                cout << "nan info!" << endl;
                    onepixelInfo.x = nowX; // 像素深度 屏幕坐标系
                    onepixelInfo.screenDeep = numeric_limits<float>::quiet_NaN(); // 像素深度 屏幕坐标系
                    onepixelInfo.rgb[0] = numeric_limits<float>::quiet_NaN();
                    onepixelInfo.rgb[1] = numeric_limits<float>::quiet_NaN();
                    onepixelInfo.rgb[2] = numeric_limits<float>::quiet_NaN();
                }

                rowpixelsInfo.pixelDeeps.emplace_back(onepixelInfo);
            }
            pixelSurfaceInfo_.emplace_back(rowpixelsInfo);
        }
    }

//    size_t vec_size = pixelSurfaceInfo_.size();
//    println("pixelSurfaceInfo_ size:{}", vec_size);
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
    afterMoved = 0;

}
void EquationThree::freshGoX(){
    world_toX.dx = (scanBox3D.rtnSet.x - scanBox3D.ltnSet.x) / boxLenX;
    world_toX.dy = (scanBox3D.rtnSet.y - scanBox3D.ltnSet.y) / boxLenX;
    world_toX.dz = (scanBox3D.rtnSet.z - scanBox3D.ltnSet.z) / boxLenX;
}
void EquationThree::freshGoY(){
    world_toY.dx = (scanBox3D.lbnSet.x - scanBox3D.ltnSet.x) / boxLenY;
    world_toY.dy = (scanBox3D.lbnSet.y - scanBox3D.ltnSet.y) / boxLenY;
    world_toY.dz = (scanBox3D.lbnSet.z - scanBox3D.ltnSet.z) / boxLenY;
}
void EquationThree::freshGoDEEP() {
    world_toDEEP.dx = (scanBox3D.ltfSet.x - scanBox3D.ltnSet.x) / boxLenZ;
    world_toDEEP.dy = (scanBox3D.ltfSet.y - scanBox3D.ltnSet.y) / boxLenZ;
    world_toDEEP.dz = (scanBox3D.ltfSet.z - scanBox3D.ltnSet.z) / boxLenZ;

}
glm::vec3 EquationThree::goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toX._;
    return _srcXYZ;
}
glm::vec3 EquationThree::goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toY._;
    return _srcXYZ;
}
glm::vec3 EquationThree::goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toDEEP._;
    return _srcXYZ;
}
void EquationThree::deepFarNearBackCenter(){
    frameScreenFar = virtual_scanBox3D.center.z;
    frameScreenNear = virtual_scanBox3D.center.z;
}
void EquationThree::setFrontColor(int _color1, int _color2,int _color3){
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
void EquationThree::freshVirtualGoX() {
    // 提前 求向量长度 便于归一化

    virtual_toX.dx = (virtual_scanBox3D.rtnSet.x - virtual_scanBox3D.ltnSet.x) / boxLenX;
    virtual_toX.dy = (virtual_scanBox3D.rtnSet.y - virtual_scanBox3D.ltnSet.y) / boxLenX;
    virtual_toX.dz = (virtual_scanBox3D.rtnSet.z - virtual_scanBox3D.ltnSet.z) / boxLenX;

}

void EquationThree::freshVirtualGoY() {
    virtual_toY.dx = (virtual_scanBox3D.lbnSet.x - virtual_scanBox3D.ltnSet.x) / boxLenY;
    virtual_toY.dy = (virtual_scanBox3D.lbnSet.y - virtual_scanBox3D.ltnSet.y) / boxLenY;
    virtual_toY.dz = (virtual_scanBox3D.lbnSet.z - virtual_scanBox3D.ltnSet.z) / boxLenY;
}

void EquationThree::freshVirtualGoDEEP() {
    virtual_toDEEP.dx = (virtual_scanBox3D.ltfSet.x - virtual_scanBox3D.ltnSet.x) / boxLenZ;
    virtual_toDEEP.dy = (virtual_scanBox3D.ltfSet.y - virtual_scanBox3D.ltnSet.y) / boxLenZ;
    virtual_toDEEP.dz = (virtual_scanBox3D.ltfSet.z - virtual_scanBox3D.ltnSet.z) / boxLenZ;
}
glm::vec3 EquationThree::Virtual_goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toX._;
    return _srcXYZ;
}
glm::vec3 EquationThree::Virtual_goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toY._;
    return _srcXYZ;
}
glm::vec3 EquationThree::Virtual_goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toDEEP._;
    return _srcXYZ;
}
glm::vec3 EquationThree::self2screenAxis(glm::vec3 _selfAxisPos){
    // 屏幕系下 自己系 斜走x 斜走y 斜走z
    glm::vec3 posNow = virtual_scanBox3D.center;
    posNow = Virtual_goX(posNow, _selfAxisPos.x);
    posNow = Virtual_goY(posNow, _selfAxisPos.y);
    posNow = Virtual_goDEEP(posNow, _selfAxisPos.z);
    return posNow;
}
void EquationThree::freshFrameRotateInfo(){
    frameRotateInfo_q = PolygonBase::getFrameRotateInfo_(virtual_toX,virtual_toDEEP);
}
glm::vec3 EquationThree::screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos){
    if(isnan(_screenAxisPos.x) || isnan(_screenAxisPos.y) || isnan(_screenAxisPos.z)){
        println(stderr, "9次 _screenAxisPos({:.4f}, {:.4f}, {:.4f})",
            _screenAxisPos.x, _screenAxisPos.y, _screenAxisPos.z);
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }// 不是 nan
    glm::vec3 back000 = virtual_scanBox3D.center;

    glm::vec3 p1ToScreenAxis000 = _screenAxisPos - back000; // 归原点

    float distanceOf000 = glm::length(p1ToScreenAxis000); // 原点距
    goLine64 p1ToScreenAxis000_dir1 = {p1ToScreenAxis000.x / distanceOf000,
                                  p1ToScreenAxis000.y / distanceOf000,
                                  p1ToScreenAxis000.z / distanceOf000}; // 归一化
    // 没两角全0  不然不用斜转

    PolygonBase::rotate_vector(p1ToScreenAxis000_dir1, frameRotateInfo_q);
    glm::vec3 farScreenAxis000 = {(float)p1ToScreenAxis000_dir1.dx * distanceOf000,
                                  (float)p1ToScreenAxis000_dir1.dy * distanceOf000,
                                  (float)p1ToScreenAxis000_dir1.dz * distanceOf000};

//    farScreenAxis000 += back000; // 离原点

    if(isnan(farScreenAxis000.x) || isnan(farScreenAxis000.y) || isnan(farScreenAxis000.z)){
        println(stderr, "9次 farScreenAxis000({:.4f}, {:.4f}, {:.4f})",
            farScreenAxis000.x, farScreenAxis000.y, farScreenAxis000.z);
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }
    return farScreenAxis000;
}
vector<double> EquationThree::getStep(double ex, double ey, double ez, double dx, double dy, double dz){
    double a_ = abcd[0], b_ = abcd[1], c_ = abcd[2], d_ = abcd[3];
    double l3 = a_ * pow3(dx) - 3 * a_ * dx * pow2(dz);

    double l2 = 3 * a_ * pow2(dx) * ex
                - 6 * a_ * dx * dz * ez
                - 3 * a_ * pow2(dz) * ex
                + b_ * pow2(dx)
                - b_ * pow2(dz);


    double l1 = 3 * a_ * dx * pow2(ex)
                - 3 * a_ * dx * pow2(ez)
                - 6 * a_ * dz * ex * ez
                + 2 * b_ * dx * ex
                - 2 * b_ * dz * ez + c_ * dx
                - dy;

    double l0 = a_ * pow3(ex)
                - 3 * a_ * ex * pow2(ez)
                + b_ * pow2(ex)
                - b_ * pow2(ez)
                + c_ * ex
                - ey;
    // 三次 求根公式
    complex<double> a = {l3, 0}, b = {l2, 0}, c = {l1, 0}, d = {l0, 0};

    complex<double> p = (3.0 * a * c - b * b) / (3.0 * a * a);
    complex<double> q = (2.0 * b * b * b - 9.0 * a * b * c + 27.0 * a * a * d) / (27.0 * a * a * a);
    complex<double> w = {-0.5, sqrt(3.0) / 2.0};

    complex<double> sqrt_disc = std::sqrt(q * q / 4.0 + p * p * p / 27.0);
    complex<double> u = pow(-q / 2.0 + sqrt_disc, 1.0 / 3.0);
    complex<double> v = -p / (3.0 * u);  // 关键修正点

    complex<double> root1 = (u + v) - b / (3.0 * a);
    complex<double> root2 = (w * u + w * w * v) - b / (3.0 * a);
    complex<double> root3 = (w * w * u + w * v) - b / (3.0 * a);

    vector<double> real_steps;
    // 虚部几乎没有  实部>0
    if (abs(root1.imag()) < 0.2 && root1.real() > 0) {
        real_steps.emplace_back(root1.real());
    }
    if (abs(root2.imag()) < 0.2 && root2.real() > 0) {
        real_steps.emplace_back(root2.real());
    }
    if (abs(root3.imag()) < 0.2 && root3.real() > 0) {
        real_steps.emplace_back(root3.real());
    }
//    for(double step : real_steps){
//        println("--real step: {}", step);
//    }
    // 按step排序
    sort(real_steps.begin(), real_steps.end(),
         [](const double& _a, const double& _b) -> bool {
             return _a < _b;
         });
    return real_steps;
}
double EquationThree::getYimg_byStep(double ex, double ey, double ez, double dx, double dy, double dz,double step){
    double a = abcd[0], b = abcd[1], c = abcd[2], d = abcd[3];
    double l3 = 3 * a * pow2(dx) * dz - a * pow3(dz);

    double l2 = -  3 * a * pow2(dz) * ez
            +  2 * b * dx * dz
            +  3 * a * pow2(dx) * ez
            +  6 * a * dx * dz * ex;

    double l1 = 6 * a * dx * ex * ez
            + 3 * a * dz * pow2(ex)
            - 3 * a * dz * pow2(ez)
            + 2 * b * dx * ez
            + 2 * b * dz * ex
            + c * dz;

    double l0 =  3 * a * pow2(ex) * ez
         - a * pow3(ez)
         + 2 * b * ex * ez
         + c * ez + d;
    double y_img = l3*pow3(step) + l2*pow2(step) + l1*step + l0;
    return y_img;
}
bool EquationThree::selfPosInBox(glm::vec3 pos){
    bool inBox = pos.x > -halfBoxLength.x && pos.x < halfBoxLength.x
            && pos.y > -halfBoxLength.y && pos.y < halfBoxLength.y
            && pos.z > -halfBoxLength.z && pos.z < halfBoxLength.z;
    return inBox;
}
RayCalcInfo25 EquationThree::getBestSolve(double ex, double ey, double ez, double dx, double dy, double dz){
    // 实数 步长 >0 由近到远
    vector<double> steps = getStep(ex, ey, ez, dx, dy, dz);
    RayCalcInfo25 result;
    for(double step : steps) {
        glm::vec3 selfPos = {ex + step * dx, ey + step * dy, ez + step * dz};
        if (selfPosInBox(selfPos)) {

            double y_img = getYimg_byStep(ex, ey, ez, dx, dy, dz, step);

            return {step, y_img,selfPos};
        }
    }
    result.step = numeric_limits<double>::quiet_NaN();
    result.vy = numeric_limits<double>::quiet_NaN();
    result.surfacePoint_Self = glm::vec3{numeric_limits<float>::quiet_NaN()};
    return result;


}
unsigned char EquationThree::getSolveBy(glm::vec3 surfacePoint_Self, double vy){

    complex<double> _y = {surfacePoint_Self.y, vy};
    complex<double> a = {abcd[0]}, b = {abcd[1]}, c = {abcd[2]}, d = {abcd[3]};
    d -= _y;
    complex<double> _x = {surfacePoint_Self.x, surfacePoint_Self.z};

    complex<double> p = (3.0 * a * c - b * b) / (3.0 * a * a);
    complex<double> q = (2.0 * b * b * b - 9.0 * a * b * c + 27.0 * a * a * d) / (27.0 * a * a * a);
    complex<double> w = {-0.5, sqrt(3.0) / 2.0};

    complex<double> sqrt_disc = std::sqrt(q * q / 4.0 + p * p * p / 27.0);
    complex<double> u = pow(-q / 2.0 + sqrt_disc, 1.0 / 3.0);
    complex<double> v = -p / (3.0 * u);  // 关键修正点

    double errorOk_2 = 0.2f;

    complex<double> root1 = (u + v) - b / (3.0 * a);
    double err1 = abs(root1.imag()-_x.imag()) + abs(root1.real()-_x.real());
    if(err1 < errorOk_2){
        return 1;
    }
    complex<double> root2 = (w * u + w * w * v) - b / (3.0 * a);
    double err2 = abs(root2.imag()-_x.imag()) + abs(root2.real()-_x.real());
    if(err2 < errorOk_2){
        return 2;
    }
    complex<double> root3 = (w * w * u + w * v) - b / (3.0 * a);
    double err3 = abs(root3.imag()-_x.imag()) + abs(root3.real()-_x.real());
    if(err3 < errorOk_2){
        return 3;
    }
//    return 0;

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
    if(minErr > 1.1f)println(stderr,"3次 3次 求根式 min error: ", minErr, " index: ", minErr_index);
    return minErr_index;

}
glm::vec3 EquationThree::getColorBy_vX(unsigned char solveBy, float _vX){
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
void EquationThree::freshComplexRect(ScreenDemo* ScreenEye){
    glm::vec3 downFlatLT_selfAxis = {-halfBoxLength.x, 0, halfBoxLength.z};
    glm::vec3 downFlatRT_selfAxis = {halfBoxLength.x, 0, halfBoxLength.z};
    glm::vec3 downFlatRB_selfAxis = {halfBoxLength.x, 0, -halfBoxLength.z};
    glm::vec3 downFlatLB_selfAxis = {-halfBoxLength.x, 0, -halfBoxLength.z};

    glm::vec3 downFlatLT_screenAxis = self2screenAxis(downFlatLT_selfAxis);
    glm::vec3 downFlatRT_screenAxis = self2screenAxis(downFlatRT_selfAxis);
    glm::vec3 downFlatRB_screenAxis = self2screenAxis(downFlatRB_selfAxis);
    glm::vec3 downFlatLB_screenAxis = self2screenAxis(downFlatLB_selfAxis);

    this->downFlatLT_2D = __3d2dEquation3(ScreenEye,downFlatLT_screenAxis.x,
                                          downFlatLT_screenAxis.y,downFlatLT_screenAxis.z);
    this->downFlatRT_2D = __3d2dEquation3(ScreenEye,downFlatRT_screenAxis.x,
                                          downFlatRT_screenAxis.y,downFlatRT_screenAxis.z);
    this->downFlatRB_2D = __3d2dEquation3(ScreenEye,downFlatRB_screenAxis.x,
                                          downFlatRB_screenAxis.y,downFlatRB_screenAxis.z);
    this->downFlatLB_2D = __3d2dEquation3(ScreenEye,downFlatLB_screenAxis.x,
                                          downFlatLB_screenAxis.y,downFlatLB_screenAxis.z);

}
void EquationThree::drawComplexRect(ScreenDemo* ScreenEye){
    // 把 复平面 框出来
    float _white[3] = {1.f, 1.f, 1.f};
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  this->downFlatLT_2D.x,this->downFlatLT_2D.y,
                                  this->downFlatRT_2D.x,this->downFlatRT_2D.y,
                                  _white,frameScreenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  this->downFlatRT_2D.x,this->downFlatRT_2D.y,
                                  this->downFlatRB_2D.x,this->downFlatRB_2D.y,
                                  _white,frameScreenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  this->downFlatRB_2D.x,this->downFlatRB_2D.y,
                                  this->downFlatLB_2D.x,this->downFlatLB_2D.y,
                                  _white,frameScreenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  this->downFlatLB_2D.x,this->downFlatLB_2D.y,
                                  this->downFlatLT_2D.x,this->downFlatLT_2D.y,
                                  _white,frameScreenNear);
}