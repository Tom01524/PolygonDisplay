//
// Created by iceoc0 on 2025/8/23.
//
#include "EquationTwo4.h"

struct modeEquation2_4{ // 同类型组 的 结构体指针 移花接木
    char now;char a;char b;char d;
};
extern void* mode_ptr;
modeEquation2_4 mode_ = *static_cast<modeEquation2_4*>(mode_ptr);

// extern void* settled_ptr; // 全局设置的结构体指针
// struct _settledEquation2_4{
//     int _width;
//     int _height;
//     int _deep;
//     bool _byAxis;
// };
// _settledEquation2_4* settled_ = (_settledEquation2_4*)settled_ptr;
// const int screenWidth21 = settled_-> _width;
// const int screenHeight21 = settled_-> _height;
// const int screenDeep21 = settled_-> _deep;

extern void* _3d_2d_go_void_ptr; // 3d_2d_go的函数指针
// struct _3d_2d_go_equation2_4{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, float *, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_2d)(ScreenDemo*, float, float, float);
//
// };
glm::vec2 (*__3d2dGoEquation2_4)(ScreenDemo*, glm::vec3, glm::vec3*) =
        static_cast<_3d_2d_go_func *>(_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2dEquation2_4)(ScreenDemo*, float, float, float) =
        static_cast<_3d_2d_go_func *>(_3d_2d_go_void_ptr)->_3d_2d; // 模式1 用自己的不行

EquationTwo4::EquationTwo4(glm::vec3 srartCenter, glm::vec3 _boxLengthHalf, float a, float b, float c,
unsigned char _debug_):PolygonBase(21){
    abc = glm::vec3(a, b, c);
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


    // startEye = {(float)screenWidth21/2.f,
    //             (float)screenHeight21/2.f,(float)-screenDeep21};

    afterMoved = false;
}
void EquationTwo4::setBox3D(glm::vec3& _ltn, glm::vec3& _rtn, glm::vec3& _rbn, glm::vec3& _lbn,
                           glm::vec3& _ltf, glm::vec3& _rtf, glm::vec3& _rbf, glm::vec3& _lbf){
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

void EquationTwo4::setBox2D(glm::vec2& _ltn, glm::vec2& _rtn, glm::vec2& _rbn, glm::vec2& _lbn,
                           glm::vec2& _ltf, glm::vec2& _rtf, glm::vec2& _rbf, glm::vec2& _lbf,
                           glm::vec2& _center
){

    scanBox2D_.set13P(_ltn, _rtn, _rbn, _lbn,
                      _ltf, _rtf, _rbf, _lbf,
                      _center);


    afterMoved = 1;

}
void EquationTwo4::Draw_Tick(ScreenDemo* ScreenEye){
//    if(afterMoved == 1){
//        println("二次 的 四次--moved");
//    }else if(afterMoved == 0){
//        println("二次 的 四次--not move");
//    }

    freshVirtualGoX(); // 屏幕系 数轴三向
    freshVirtualGoY();
    freshVirtualGoDEEP();

    if(afterMoved == 1)deepFarNearBackCenter();

    freshFrameRotateInfo(); // 转自己系 四元数

    solidRectangle2D_(ScreenEye, true);

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
//        cout << "~~draw ltn(" << scanBox2D_.ltn.x << ", " << scanBox2D_.ltn.y << ")" <<
//         "draw rtn(" << scanBox2D_.rtn.x << ", " << scanBox2D_.rtn.y << ")" << endl;
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
    if(debugLine==2) {
        freshTheAxis(); // 更新坐标轴 info
        //drawSphereAxis(ScreenEye); // 画坐标轴
    }
    afterMoved = 0; // 是否 前帧移动
}

void EquationTwo4::solidRectangle2D_(ScreenDemo* ScreenEye, bool onFront) {

    scanBox2D_.setLineBounary(lineScanFillColor_);

    // for(auto& _linePosInfo : lineScanFillColor_) { // 行循环
    //     for(int i = _linePosInfo.lx; i <= _linePosInfo.rx; i++){
    //         float colorNOw[3] = {frontColor1_rgb01[0],frontColor1_rgb01[1],frontColor1_rgb01[2]};
    //         ScreenEye->putPixel(i,_linePosInfo.y,
    //                             colorNOw,virtual_scanBox3D.center.z-500.f,
    //                             (PolygonBase*)this);
    //     }
    //
    // }return;

    if(afterMoved == 1){ // 移动了 才 更新 pixels 信息
        pixelSurfaceInfo_.clear();

        for(auto& _linePosInfo : lineScanFillColor_) { // 行循环
            rowPixelInfo21 rowpixelsInfo;
            if (_linePosInfo.rx == _linePosInfo.lx) {
                // 屏幕外的行 左右x相同
                continue;
            }
            rowpixelsInfo.y = static_cast<float>(_linePosInfo.y); // 本行 y


            for (int nowX = static_cast<int>(roundf(_linePosInfo.lx)); nowX <= _linePosInfo.rx; nowX++) { // 单像素循环
                onepixelInfo21 onepixelInfo;


                glm::vec3 startEye_Self = screenXYZ2SelfXYZ2(startEye);
                glm::vec3 screenPoint_Self = screenXYZ2SelfXYZ2({nowX, _linePosInfo.y,0.f});
                goLine32 eyeRay_Self = ScreenDemo::get_AgoB_direction3D(startEye_Self,screenPoint_Self); // 计算视线

                goLine32 eyeRay_ScreenAxis = ScreenDemo::get_AgoB_direction3D(startEye,{nowX, _linePosInfo.y,0.f}); // 视线 屏幕坐标系
                RayCalcInfo21 consilientResult = getBestSolve(startEye_Self.x,startEye_Self.y,startEye_Self.z,
                                                              eyeRay_Self.dx,eyeRay_Self.dy,eyeRay_Self.dz);
//            cout << "step:" << consilientResult.step << ", vx:" << consilientResult.vx << endl;
//            cout << "surfacePoint_Self:" << consilientResult.surfacePoint_Self.x << " " <<
//            consilientResult.surfacePoint_Self.y << " " << consilientResult.surfacePoint_Self.z << endl;

                if(!isnan(consilientResult.step)) {
                    //1
                    onepixelInfo.x = static_cast<float>(nowX); // 本像素 x

                    float screenDeep_ScreenAxis =
                            startEye.z + eyeRay_ScreenAxis.dz * consilientResult.step; // 视线深度 屏幕坐标系
                    //2
                    onepixelInfo.screenDeep = screenDeep_ScreenAxis; // 像素深度 屏幕坐标系

                    if (screenDeep_ScreenAxis < frameScreenNear) {
                        frameScreenNear = screenDeep_ScreenAxis; // 刷新 近 屏垂距
                    } else if (screenDeep_ScreenAxis > frameScreenFar) {
                        frameScreenFar = screenDeep_ScreenAxis; // 刷新 远 屏垂距
                    }
                    unsigned char solveBy_ = getSolveBy(consilientResult.surfacePoint_Self,consilientResult.vx);
                    glm::vec3 colorNow = getColorBy_vX(solveBy_,consilientResult.vx);
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

//            float testColor[3] = {5.f/8.f,0.f,0.f};
//            ScreenEye->putPixel(onepixelInfo.x ,rowpixelsInfo.y,
//                                testColor,frameScreenNear-500.f,(PolygonBase*)this);

                rowpixelsInfo.pixelDeeps.push_back(onepixelInfo);
            }
            pixelSurfaceInfo_.push_back(rowpixelsInfo);
        }
    }


    for(auto& _rowpixelsInfo : pixelSurfaceInfo_) {
        //size_t vecSizeCurrent = _rowpixelsInfo.pixelDeeps.size();
        for (auto& _onepixelInfo : _rowpixelsInfo.pixelDeeps) {

//            float testColor[3] = {5.f/8.f,0.f,0.f};
//            ScreenEye->putPixel(_lineDeepInfo.pixelDeeps[i].x,_lineDeepInfo.y,
//                                testColor,frameScreenNear-500.f,(PolygonBase*)this);

            if (isnan(_onepixelInfo.rgb[0])) {
                continue;
            }
            ScreenEye->putPixel(_onepixelInfo.x,_rowpixelsInfo.y,
                                _onepixelInfo.rgb,_onepixelInfo.screenDeep,
                                (PolygonBase*)this);
        }
    }
}

void EquationTwo4::deepFarNearBackCenter(){
    frameScreenFar = virtual_scanBox3D.center.z;
    frameScreenNear = virtual_scanBox3D.center.z;
}
void EquationTwo4::setFrontColor(int _color1, int _color2) {
    BGR3f colorNow;
    colorNow.setBGR(_color1,1);
    frontColor1_rgb01[0] = colorNow.r1;
    frontColor1_rgb01[1] = colorNow.g1;
    frontColor1_rgb01[2] = colorNow.b1;

    colorNow.setBGR(_color2,1);
    frontColor2_rgb01[0] = colorNow.r1;
    frontColor2_rgb01[1] = colorNow.g1;
    frontColor2_rgb01[2] = colorNow.b1;
}

void EquationTwo4::setBackColor(int _color) {
    BGR3f colorNow;
    colorNow.setBGR(_color,1);
    backColor_rgb01[0] = colorNow.r1;
    backColor_rgb01[1] = colorNow.g1;
    backColor_rgb01[2] = colorNow.b1;
}
void EquationTwo4::freshGoX(){
    world_toX.dx = (scanBox3D.rtnSet.x - scanBox3D.ltnSet.x) / boxLenX;
    world_toX.dy = (scanBox3D.rtnSet.y - scanBox3D.ltnSet.y) / boxLenX;
    world_toX.dz = (scanBox3D.rtnSet.z - scanBox3D.ltnSet.z) / boxLenX;
}
void EquationTwo4::freshGoY(){
    world_toY.dx = (scanBox3D.lbnSet.x - scanBox3D.ltnSet.x) / boxLenY;
    world_toY.dy = (scanBox3D.lbnSet.y - scanBox3D.ltnSet.y) / boxLenY;
    world_toY.dz = (scanBox3D.lbnSet.z - scanBox3D.ltnSet.z) / boxLenY;
}
void EquationTwo4::freshGoDEEP() {
    world_toDEEP.dx = (scanBox3D.ltfSet.x - scanBox3D.ltnSet.x) / boxLenZ;
    world_toDEEP.dy = (scanBox3D.ltfSet.y - scanBox3D.ltnSet.y) / boxLenZ;
    world_toDEEP.dz = (scanBox3D.ltfSet.z - scanBox3D.ltnSet.z) / boxLenZ;
//    world_toDEEP = ScreenDemo::get_AgoB_direction3D(scanBox3D.ltnSet, scanBox3D.ltfSet);
}
glm::vec3 EquationTwo4::goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toX._;
    return _srcXYZ;
}
glm::vec3 EquationTwo4::goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toY._;
    return _srcXYZ;
}
glm::vec3 EquationTwo4::goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toDEEP._;
    return _srcXYZ;
}

complex<double>(*safe_divide_imgNum)(complex<double>,complex<double>)
 = [](complex<double> num, complex<double> den)->complex<double> {
    const double epsilon = 1e-12;
    if (abs(den) < epsilon) return num / epsilon;
    return num / den;
};

array<complex<double>,4>  EquationTwo4::solveEquation_4_(Coefficient5_& src) {
//    using namespace std::complex_literals;
    complex<double> A = src.a, B = src.b, C = src.c, D = src.d, E = src.e;

    complex<double> delta1 = C*C - 3.0*B*D + 12.0*A*E;
    complex<double> delta2 = 2.0*C*C*C - 9.0*B*C*D + 27.0*A*D*D + 27.0*B*B*E - 72.0*A*C*E;
    complex<double> sqrt_term = sqrt(-4.0*delta1*delta1*delta1 + delta2*delta2);

    complex<double> denom_pow = pow(delta2 + sqrt_term, 1.0/3.0);
    complex<double> deltaL = safe_divide_imgNum(pow(2.0, 1.0 / 3.0) * delta1, 3.0 * A * denom_pow);
    complex<double> deltaR = safe_divide_imgNum(denom_pow, 3.0 * pow(2.0, 1.0 / 3.0) * A);
    complex<double> delta = deltaL + deltaR;

    complex<double> term_B2_4A2 = (B*B)/(4.0*A*A);
    complex<double> sqrt_arg_L = term_B2_4A2 - (2.0*C)/(3.0*A) + delta;
    complex<double> sqrt_L = sqrt(sqrt_arg_L);

    complex<double> xL_minus = -B/(4.0*A) - 0.5 * sqrt_L;
    complex<double> xL_plus = -B/(4.0*A) + 0.5 * sqrt_L;

    complex<double> numerator = -(B*B*B)/(A*A*A) + (4.0*B*C)/(A*A) - (8.0*D)/A;
    complex<double> denom_xR = 4.0 * sqrt_L;
    complex<double> term_inside = safe_divide_imgNum(numerator, denom_xR);

    complex<double> sqrt_arg_R1 = (B*B)/(2.0*A*A) - (4.0*C)/(3.0*A) - delta - term_inside;
    complex<double> sqrt_arg_R2 = (B*B)/(2.0*A*A) - (4.0*C)/(3.0*A) - delta + term_inside;

    complex<double> xR_minus = 0.5 * sqrt(sqrt_arg_R1);
    complex<double> xR_plus = 0.5 * sqrt(sqrt_arg_R2);

    return {xL_minus - xR_minus, xL_minus + xR_minus,
            xL_plus - xR_plus, xL_plus + xR_plus};
}
double safe_divide(double num, double den) {
    const double epsilon = 1e-12;
    if (abs(den) < epsilon) return num / epsilon;
    return num / den;
};
vector<pair<double, double>> EquationTwo4::solve(
        double ex, double ey, double ez,
        double dx, double dy, double dz)
{

    const double epsilon = 0.1;
    Coefficient5_ coeff;

    // 计算四次方程系数


    double term1 = abc[0] * pow2(dx);
    double term2 = 8.0 * pow2(abc[0]) * dx * ex + 4.0 * abc[0] * dx * abc[1];
    double term3 = 2.0 * abc[0] * ex * dx + abc[1] * dx - dy;
    double term4 = 4.0 * pow2(abc[0]) * pow2(dx);
    double term5 = 4.0 * pow2(abc[0]) * pow2(ex) + 4.0 * abc[0] * ex * abc[1] + pow2(abc[1]);
    double term6 = abc[0] * pow2(ex) + abc[1] * ex + abc[2] - ey;

    double _12 = term1 * term2;
    double _23 = term2 * term3;
    double _34 = term3 * term4;
    double _15 = term1 * term5;
    double _46 = term6 * term4;
    double _35 = term3 * term5;
    double _26 = term6 * term2;

    coeff.a = term1 * term4;//4.0 * a³ * dx⁴;
    coeff.b = _12 + _34;
    coeff.c = _15 + _23 + _46 - abc[0] * dz * dz;
// 4a²ex²+4*a*ex*b+b²
 // 8a²dxex +4adx b
    coeff.d = _35 + _26 - 2.0 * abc[0] * dz * ez;
    coeff.e = term6 * term5 - abc[0] * ez * ez;

//    cout <<  coeff.a << "x⁴ + " << coeff.b << "x³ + " << coeff.c << "x² + " <<
//         coeff.d << "x + " << coeff.e << "=0"<< endl;
    // 解四次方程
    array<complex<double>,4>  roots = solveEquation_4_(coeff);

    vector<pair<double, double>> valid_pairs;
    valid_pairs.reserve(4);

    for (const auto& root : roots) {
        // 检查实根且大于0
        if (abs(root.imag()) < epsilon && root.real() > 0) {
            double step = root.real();

            // 计算分母
            double denominator = 2.0 * abc[0] * dx * step + 2.0 * abc[0] * ex + abc[1];

            // 计算分子
            double numerator = dz * step + ez;
            double x_img = safe_divide(numerator, denominator);

            valid_pairs.emplace_back(step, x_img);
        }
    }

    // 按step排序
    sort(valid_pairs.begin(), valid_pairs.end(),
         [](const pair<double, double>& _a, const pair<double, double>& _b) -> bool {
             return _a.first < _b.first;
         });

    return valid_pairs;
}
bool EquationTwo4::selfPosInBox(glm::vec3 _selfPos){

    bool pointInBox = _selfPos.x > -halfBoxLength.x && _selfPos.x < halfBoxLength.x &&
                      _selfPos.y > -halfBoxLength.y && _selfPos.y < halfBoxLength.y &&
                      _selfPos.z > -halfBoxLength.z && _selfPos.z < halfBoxLength.z;
    return pointInBox;
}
RayCalcInfo21 EquationTwo4::getBestSolve(double ex, double ey, double ez,
                                  double dx, double dy, double dz){
    RayCalcInfo21 bestInfo;
    // 视线步长 实数 且>0 , 由小到大
    vector<pair<double, double>> valid_pairs = solve(ex, ey, ez, dx, dy, dz);

    if(valid_pairs.empty()){
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
        if(selfPosInBox(selfSurfacePos)){
            bestInfo.step = _pair.first;
            bestInfo.vx = _pair.second;
            bestInfo.surfacePoint_Self = selfSurfacePos;
            return bestInfo;
        }
    }
    bestInfo.step = numeric_limits<double>::quiet_NaN();
    bestInfo.vx = numeric_limits<double>::quiet_NaN();
    bestInfo.surfacePoint_Self = glm::vec3(numeric_limits<double>::quiet_NaN());
    return bestInfo;
}

unsigned char EquationTwo4::getSolveBy(glm::dvec3 surfacePoint_Self, double vx){

    complex<double> x = {surfacePoint_Self.x, vx};
    complex<double> y = {surfacePoint_Self.y, surfacePoint_Self.z};

    complex<double> a = {abc[0], 0.f}, b={abc[1], 0.f}, c={abc[2], 0.f};
    complex<double> discriminant = sqrt(b*b - 4.0*a*(c - y) );
    complex<double> res_x1 = (-b + discriminant) / (2.0*a);
    complex<double> res_x2 = (-b - discriminant) / (2.0*a);

    double x1_real_err = abs(res_x1.real() - x.real());
    double x1_imag_err = abs(res_x1.imag() - x.imag());
//    cout << "x real:" << x.real() << ", x imag:" << x.imag() << endl;
//    cout << "x1 real:" << res_x1.real() << ", x1 imag:" << res_x1.imag() << endl;
//    cout << "x1_real_miss: " << x1_real_err << ", x1_imag_miss: " << x1_imag_err << endl;

    double x2_real_err = abs(res_x2.real() - x.real());
    double x2_imag_err = abs(res_x2.imag() - x.imag());
//    cout << "x real:" << x.real() << ", x imag:" << x.imag() << endl;
//    cout << "x2 real:" << res_x2.real() << ", x2 imag:" << res_x2.imag() << endl;
//    cout << "x2_real_miss: " << x2_real_err << ", x2_imag_miss: " << x2_imag_err << endl;

    const double tol = 1e-2; // 精度要求高了 视线不命中 !!!

    if(x1_real_err < tol && x1_imag_err < tol){
        return 1; // + 根式
    }else if(x2_real_err < tol && x2_imag_err < tol){
        return 2; // - 根式
    }
    // 整数 nan 是 0
    return 0; // 无根式

}
glm::vec3 EquationTwo4::getColorBy_vX(unsigned char solveBy, double _vX){

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

    return glm::vec3(numeric_limits<float>::quiet_NaN());
}
void EquationTwo4::freshVirtualGoX() {
    // 提前 求向量长度 便于归一化
//    virtual_squareEdgeLen = glm::distance(virtual_scanBox3D.ltnSet, virtual_scanBox3D.rtnSet);

    virtual_toX.dx = (virtual_scanBox3D.rtnSet.x - virtual_scanBox3D.ltnSet.x) / boxLenX;
    virtual_toX.dy = (virtual_scanBox3D.rtnSet.y - virtual_scanBox3D.ltnSet.y) / boxLenX;
    virtual_toX.dz = (virtual_scanBox3D.rtnSet.z - virtual_scanBox3D.ltnSet.z) / boxLenX;
//    virtual_toX = ScreenDemo::get_AgoB_direction3D(virtual_scanBox3D.ltnSet, virtual_scanBox3D.rtnSet);
}

void EquationTwo4::freshVirtualGoY() {
    virtual_toY.dx = (virtual_scanBox3D.lbnSet.x - virtual_scanBox3D.ltnSet.x) / boxLenY;
    virtual_toY.dy = (virtual_scanBox3D.lbnSet.y - virtual_scanBox3D.ltnSet.y) / boxLenY;
    virtual_toY.dz = (virtual_scanBox3D.lbnSet.z - virtual_scanBox3D.ltnSet.z) / boxLenY;
//    virtual_toY = ScreenDemo::get_AgoB_direction3D(virtual_scanBox3D.ltnSet, virtual_scanBox3D.lbnSet);
}

void EquationTwo4::freshVirtualGoDEEP() {
    virtual_toDEEP.dx = (virtual_scanBox3D.ltfSet.x - virtual_scanBox3D.ltnSet.x) / boxLenZ;
    virtual_toDEEP.dy = (virtual_scanBox3D.ltfSet.y - virtual_scanBox3D.ltnSet.y) / boxLenZ;
    virtual_toDEEP.dz = (virtual_scanBox3D.ltfSet.z - virtual_scanBox3D.ltnSet.z) / boxLenZ;
//    virtual_toDEEP = ScreenDemo::get_AgoB_direction3D(virtual_scanBox3D.ltnSet, virtual_scanBox3D.ltfSet);
}
glm::vec3 EquationTwo4::Virtual_goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toX._;
    return _srcXYZ;
}
glm::vec3 EquationTwo4::Virtual_goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toY._;
    return _srcXYZ;
}
glm::vec3 EquationTwo4::Virtual_goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toDEEP._;
    return _srcXYZ;
}
glm::vec3 EquationTwo4::self2screenAxis(glm::vec3 _selfAxisPos){
    // 屏幕系下 自己系 斜走x 斜走y 斜走z
    glm::vec3 posNow = virtual_scanBox3D.center;
    posNow = Virtual_goX(posNow, _selfAxisPos.x);
    posNow = Virtual_goY(posNow, _selfAxisPos.y);
    posNow = Virtual_goDEEP(posNow, _selfAxisPos.z);
    return posNow;
}
void EquationTwo4::freshFrameRotateInfo(){
    frameRotateInfo_q = PolygonBase::getFrameRotateInfo_(virtual_toX,virtual_toDEEP);
}
glm::vec3 EquationTwo4::screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos){
    if(isnan(_screenAxisPos.x) || isnan(_screenAxisPos.y) || isnan(_screenAxisPos.z)){
        println(stderr,"_screenAxisPos(", _screenAxisPos.x, ", ", _screenAxisPos.y, ", ", _screenAxisPos.z, ")");
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
        println(stderr,"farScreenAxis000(", farScreenAxis000.x, ", ", farScreenAxis000.y, ", ", farScreenAxis000.z, ")");
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }
    return farScreenAxis000;
}

void EquationTwo4::freshTiltAxis(){
    // 中
    tiltAxis3D[0] = scanBox3D.center;
    // x轴
    tiltAxis3D[1].x = scanBox3D.center.x + world_toX.dx * boxLenX*1.2f; // 数轴长度 看宽
    tiltAxis3D[1].y = scanBox3D.center.y + world_toX.dy * boxLenX*1.2f;
    tiltAxis3D[1].z = scanBox3D.center.z + world_toX.dz * boxLenX * 1.2f;
    // y轴
    tiltAxis3D[2].x = scanBox3D.center.x + world_toY.dx * boxLenY*1.2f;
    tiltAxis3D[2].y = scanBox3D.center.y + world_toY.dy * boxLenY*1.2f;
    tiltAxis3D[2].z = scanBox3D.center.z + world_toY.dz * boxLenY * 1.2f;
    // z轴
    tiltAxis3D[3].x = scanBox3D.center.x + world_toDEEP.dx * boxLenZ*1.2f;
    tiltAxis3D[3].y = scanBox3D.center.y + world_toDEEP.dy * boxLenZ*1.2f;
    tiltAxis3D[3].z = scanBox3D.center.z + world_toDEEP.dz * boxLenZ * 1.2f;
}

void EquationTwo4::freshParallelAxis(){
    // 中
    parallelAxis3D[0] = scanBox3D.center;
    // x轴
    parallelAxis3D[1].x = scanBox3D.center.x + boxLenX*1.2f; // 数轴长度 看宽
    parallelAxis3D[1].y = scanBox3D.center.y;
    parallelAxis3D[1].z = scanBox3D.center.z;
    // y轴
    parallelAxis3D[2].x = scanBox3D.center.x;
    parallelAxis3D[2].y = scanBox3D.center.y + boxLenY*1.2f;
    parallelAxis3D[2].z = scanBox3D.center.z;
    // z轴
    parallelAxis3D[3].x = scanBox3D.center.x;
    parallelAxis3D[3].y = scanBox3D.center.y;
    parallelAxis3D[3].z = scanBox3D.center.z + boxLenZ*1.2f;
}

void EquationTwo4::drawTiltAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴  世界系 屏幕系 3D→2D
    tiltAxis2D_f[0] = __3d2dGoEquation2_4(ScreenEye, tiltAxis3D[0], nullptr);
    tiltAxis2D_f[1] = __3d2dGoEquation2_4(ScreenEye, tiltAxis3D[1], nullptr);
    tiltAxis2D_f[2] = __3d2dGoEquation2_4(ScreenEye, tiltAxis3D[2], nullptr);
    tiltAxis2D_f[3] = __3d2dGoEquation2_4(ScreenEye, tiltAxis3D[3], nullptr);


    float colorNow[3] = {0.12549019607843137,0.6313725490196078,0.3843137254901961};
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[1].x,tiltAxis2D_f[1].y,
                                  colorNow,frameScreenNear);
    colorNow[0] = 0.1843137254901961;colorNow[1] = 0.5647058823529412;colorNow[2] = 0.7254901960784313;
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[2].x,tiltAxis2D_f[2].y,
                                  colorNow,frameScreenNear);
    colorNow[0] = 0.8509803921568627;colorNow[1] = 0.6431372549019608;colorNow[2] = 0.054901960784313725;
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[3].x,tiltAxis2D_f[3].y,
                                  colorNow,frameScreenNear);

}

void EquationTwo4::drawParallelAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴
    parallelAxis2D_f[0] = __3d2dGoEquation2_4(ScreenEye, parallelAxis3D[0], nullptr);
    parallelAxis2D_f[1] = __3d2dGoEquation2_4(ScreenEye, parallelAxis3D[1], nullptr);
    parallelAxis2D_f[2] = __3d2dGoEquation2_4(ScreenEye, parallelAxis3D[2], nullptr);
    parallelAxis2D_f[3] = __3d2dGoEquation2_4(ScreenEye, parallelAxis3D[3], nullptr);


    float colorNow[3] = {1.f, 1.f, 1.f};
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  parallelAxis2D_f[0].x,parallelAxis2D_f[0].y,
                                  parallelAxis2D_f[1].x,parallelAxis2D_f[1].y,
                                  colorNow,frameScreenNear); // x轴
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  parallelAxis2D_f[0].x,parallelAxis2D_f[0].y,
                                  parallelAxis2D_f[2].x,parallelAxis2D_f[2].y,
                                  colorNow,frameScreenNear); // y轴
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  parallelAxis2D_f[0].x,parallelAxis2D_f[0].y,
                                  parallelAxis2D_f[3].x,parallelAxis2D_f[3].y,
                                  colorNow,frameScreenNear); // z轴

}

void EquationTwo4::freshTheAxis(){

//    freshGoX();freshGoY();freshGoDEEP(); // draw的时候 已经..

    freshTiltAxis(); // 刷新 倾斜轴
    freshParallelAxis(); // 刷新 平行轴
}
void EquationTwo4::drawTheAxis(ScreenDemo *ScreenEye) {
    // 没刷新 就不画了
    if(debugLine != 2)return;

    drawTiltAxis(ScreenEye); // 画倾斜轴
    drawParallelAxis(ScreenEye); // 画平行轴
}
void EquationTwo4::switchDebug(){
    if(debugLine==0){
        debugLine = 1;
        println("复平面² 4 debugLine 1");
    }
    else if(debugLine==1){
        debugLine = 2;
        println("复平面² 4 debugLine 2");
    }
    else{
        debugLine = 0;
        println("复平面² 4 debugLine 0");
    }
}
void EquationTwo4::freshComplexRect(ScreenDemo* ScreenEye){
    // 左视 竖面
    glm::vec3 sideFlatLT_selfAxis = {0,-halfBoxLength.y, halfBoxLength.z};
    glm::vec3 sideFlatRT_selfAxis = {0,-halfBoxLength.y,-halfBoxLength.z};
    glm::vec3 sideFlatRB_selfAxis = {0,halfBoxLength.y,-halfBoxLength.z};
    glm::vec3 sideFlatLB_selfAxis = {0,halfBoxLength.y, halfBoxLength.z};

    glm::vec3 sideFlatLT_screenAxis = self2screenAxis(sideFlatLT_selfAxis);
    glm::vec3 sideFlatRT_screenAxis = self2screenAxis(sideFlatRT_selfAxis);
    glm::vec3 sideFlatRB_screenAxis = self2screenAxis(sideFlatRB_selfAxis);
    glm::vec3 sideFlatLB_screenAxis = self2screenAxis(sideFlatLB_selfAxis);

    this->sideFlatLT_2D = __3d2dEquation2_4(ScreenEye,sideFlatLT_screenAxis.x,
                                          sideFlatLT_screenAxis.y,sideFlatLT_screenAxis.z);
    this->sideFlatRT_2D = __3d2dEquation2_4(ScreenEye,sideFlatRT_screenAxis.x,
                                          sideFlatRT_screenAxis.y,sideFlatRT_screenAxis.z);
    this->sideFlatRB_2D = __3d2dEquation2_4(ScreenEye,sideFlatRB_screenAxis.x,
                                          sideFlatRB_screenAxis.y,sideFlatRB_screenAxis.z);
    this->sideFlatLB_2D = __3d2dEquation2_4(ScreenEye,sideFlatLB_screenAxis.x,
                                          sideFlatLB_screenAxis.y,sideFlatLB_screenAxis.z);

}
void EquationTwo4::drawComplexRect(ScreenDemo* ScreenEye){
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