//
// Created by iceoc0 on 2025/8/16.
//
#include "EquationTwo.h"

// extern void* settled_ptr; // 全局设置的结构体指针
// struct _settledEquation2{
//     int _width;
//     int _height;
//     int _deep;
//     bool _byAxis;
// };
// _settledEquation2* settled_ = (_settledEquation2*)settled_ptr;
// const int screenWidth20 = settled_-> _width;
// const int screenHeight20 = settled_-> _height;
// const int screenDeep20 = settled_-> _deep;

extern void* _3d_2d_go_void_ptr; // 3d_2d_go的函数指针
// struct _3d_2d_go_equation2{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, float *, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_2d)(ScreenDemo*, float, float, float);
//
// };
glm::vec2 (*__3d2dGoEquation2)(ScreenDemo*, glm::vec3, glm::vec3*) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2dEquation2)(ScreenDemo*, float, float, float) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d;

EquationTwo::EquationTwo(glm::vec3 srartCenter, glm::vec3 _boxLengthHalf, float a, float b, float c,
                         unsigned char _debug_):PolygonBase(20){
    abc = glm::vec3(a,b,c);
    discriminant_ = b*b - 4*a*c;

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


//    cout << "### boxLenX:" << boxLenX << endl;
//    cout << "### boxLenY:" << boxLenY << endl;
//    cout << "### boxLenZ:" << boxLenZ << endl;

DEBUG_SECTION(
    scanBox3D.rtn_ltn_tip = goX(scanBox3D.ltnSet,-rounfBoxTipLen);

    scanBox3D.lbn_ltn_tip = goY(scanBox3D.ltnSet,-rounfBoxTipLen);

    scanBox3D.ltf_ltn_tip = goDEEP(scanBox3D.ltnSet,-rounfBoxTipLen);

    scanBox3D.lbf_rbf_tip = goX(scanBox3D.rbfSet,rounfBoxTipLen);

    scanBox3D.rtf_rbf_tip = goY(scanBox3D.rbfSet,rounfBoxTipLen);

    scanBox3D.rbn_rbf_tip = goDEEP(scanBox3D.rbfSet,rounfBoxTipLen);
)
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
//    cout << "### scanBox3D_unchange.ltfSet:" << scanBox3D_unchange.ltfSet.x <<
//          " " << scanBox3D_unchange.ltfSet.y << " " << scanBox3D_unchange.ltfSet.z << endl;
//    cout << "### scanBox3D_unchange.rtfSet:" << scanBox3D_unchange.rtfSet.x <<
//          " " << scanBox3D_unchange.rtfSet.y << " " << scanBox3D_unchange.rtfSet.z << endl;
//    cout << "### scanBox3D_unchange.lbfSet:" << scanBox3D_unchange.lbfSet.x <<
//          " " << scanBox3D_unchange.lbfSet.y << " " << scanBox3D_unchange.lbfSet.z << endl;
//    cout << "### scanBox3D_unchange.rbfSet:" << scanBox3D_unchange.rbfSet.x <<
//          " " << scanBox3D_unchange.rbfSet.y << " " << scanBox3D_unchange.rbfSet.z << endl;
DEBUG_SECTION(
    scanBox3D_unchange.rtn_ltn_tip = scanBox3D.rtn_ltn_tip;

    scanBox3D_unchange.lbn_ltn_tip = scanBox3D.lbn_ltn_tip;

    scanBox3D_unchange.ltf_ltn_tip = scanBox3D.ltf_ltn_tip;

    scanBox3D_unchange.lbf_rbf_tip = scanBox3D.lbf_rbf_tip;

    scanBox3D_unchange.rtf_rbf_tip = scanBox3D.rtf_rbf_tip;

    scanBox3D_unchange.rbn_rbf_tip = scanBox3D.rbn_rbf_tip;
)
    // startEye = {(float)screenWidth20/2.f,
    //             (float)screenHeight20/2.f,(float)-screenDeep20};

    afterMoved = false;
}
void EquationTwo::setBox3D(glm::vec3& _ltn, glm::vec3& _rtn, glm::vec3& _rbn, glm::vec3& _lbn,
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

DEBUG_SECTION(
    scanBox3D.rtn_ltn_tip = goX(scanBox3D.ltnSet,-rounfBoxTipLen);

    scanBox3D.lbn_ltn_tip = goY(scanBox3D.ltnSet,-rounfBoxTipLen);

    scanBox3D.ltf_ltn_tip = goDEEP(scanBox3D.ltnSet,-rounfBoxTipLen);

    scanBox3D.lbf_rbf_tip = goX(scanBox3D.rbfSet,rounfBoxTipLen);

    scanBox3D.rtf_rbf_tip = goY(scanBox3D.rbfSet,rounfBoxTipLen);

    scanBox3D.rbn_rbf_tip = goDEEP(scanBox3D.rbfSet,rounfBoxTipLen);
)
}

void EquationTwo::setBox2D(glm::vec2& _ltn, glm::vec2& _rtn, glm::vec2& _rbn, glm::vec2& _lbn,
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
    scanBox2D.ltnSet = _ltn;
    scanBox2D.rtnSet = _rtn;
    scanBox2D.rbnSet = _rbn;
    scanBox2D.lbnSet = _lbn;

    scanBox2D.ltfSet = _ltf;
    scanBox2D.rtfSet = _rtf;
    scanBox2D.rbfSet = _rbf;
    scanBox2D.lbfSet = _lbf;

    scanBox2D.center = _center;
DEBUG_SECTION(
    scanBox2D.rtn_ltn_tip = _rtn_ltn_tip;
    scanBox2D.lbn_ltn_tip = _lbn_ltn_tip;
    scanBox2D.ltf_ltn_tip = _ltf_ltn_tip;

    scanBox2D.lbf_rbf_tip = _lbf_rbf_tip;
    scanBox2D.rtf_rbf_tip = _rtf_rbf_tip;
    scanBox2D.rbn_rbf_tip = _rbn_rbf_tip;
)
    afterMoved = 1;
}
void EquationTwo::Draw_Tick(ScreenDemo* ScreenEye){
//    if(afterMoved == 1){
//        println("二次 的 二次--moved");
//    }else if(afterMoved == 0){
//        println("二次 的 二次--not move");
//    }

    freshVirtualGoX(); // 屏幕系 数轴三向
    freshVirtualGoY();
    freshVirtualGoDEEP();

    if(afterMoved == 1)deepFarNearBackCenter();

    freshFrameRotateInfo(); // 转自己系 四元数



    // left面 法线
    flatLeftFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        -world_toX._,scanBox3D.ltnSet);
    // top面 法线
    flatTopFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        -world_toY._,scanBox3D.ltnSet);
    // front面 法线
    flatFrontFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        -world_toDEEP._,scanBox3D.ltnSet);
    // right面 法线
    flatRightFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        world_toX._,scanBox3D.rbfSet);
    // bottom面 法线
    flatBottomFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        world_toY._,scanBox3D.rbfSet);
    // back面 法线
    flatBackFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
        world_toDEEP._,scanBox3D.rbfSet);

    //flatLeftFacing = rtn_ltn_tip_closer; // 哪个面对着我 ?
    //flatTopFacing = lbn_ltn_tip_closer;
    //flatRightFacing = lbf_rbf_tip_closer;
    //flatBottomFacing = rtf_rbf_tip_closer;
    //flatFrontFacing = ltf_ltn_tip_closer;
    //flatBackFacing = rbn_rbf_tip_closer;

    if (flatFrontFacing) { // ltn rtn rbn lbn
        solidRectangle2D_front(ScreenEye); // 反面 需要经纬度
    }
    if(flatLeftFacing){
        solidRectangle2D_left(ScreenEye);
    }
    if(flatRightFacing){
        solidRectangle2D_right(ScreenEye);
    }
    if(flatBackFacing){
        solidRectangle2D_back(ScreenEye);
    }
    if(flatTopFacing){
        solidRectangle2D_top(ScreenEye);
    }
    if(flatBottomFacing){
        solidRectangle2D_bottom(ScreenEye);
    }
    if(debugLine == 0) {
        freshComplexRect(ScreenEye);
        drawComplexRect(ScreenEye);
    }

    float _color_[3];
    if (debugLine == 1) {
//        cout << "equation draw..." << endl;
        _color_[0] = 1.0f;
        _color_[1] = 1.0f;
        _color_[2] = 1.0f; // 白色
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.ltnSet.x, scanBox2D.ltnSet.y,
                                      scanBox2D.rtnSet.x, scanBox2D.rtnSet.y,
                                      _color_, frameScreenNear);// 前框
//        cout << "~~draw ltn(" << scanBox2D.ltnSet.x << ", " << scanBox2D.ltnSet.y << ")" <<
//         "draw rtn(" << scanBox2D.rtnSet.x << ", " << scanBox2D.rtnSet.y << ")" << endl;
//        cout << " color:" << _color_[0] << " " << _color_[1] << " " << _color_[2] << endl;
//        cout << " frameScreenNear:" << frameScreenNear << endl;

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rtnSet.x, scanBox2D.rtnSet.y,
                                      scanBox2D.rbnSet.x, scanBox2D.rbnSet.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rbnSet.x, scanBox2D.rbnSet.y,
                                      scanBox2D.lbnSet.x, scanBox2D.lbnSet.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.lbnSet.x, scanBox2D.lbnSet.y,
                                      scanBox2D.ltnSet.x, scanBox2D.ltnSet.y,
                                      _color_, frameScreenNear);

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.ltfSet.x, scanBox2D.ltfSet.y,
                                      scanBox2D.rtfSet.x, scanBox2D.rtfSet.y,
                                      _color_, frameScreenNear);// 后框
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rtfSet.x, scanBox2D.rtfSet.y,
                                      scanBox2D.rbfSet.x, scanBox2D.rbfSet.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rbfSet.x, scanBox2D.rbfSet.y,
                                      scanBox2D.lbfSet.x, scanBox2D.lbfSet.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.lbfSet.x, scanBox2D.lbfSet.y,
                                      scanBox2D.ltfSet.x, scanBox2D.ltfSet.y,
                                      _color_, frameScreenNear);

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.ltnSet.x, scanBox2D.ltnSet.y,
                                      scanBox2D.ltfSet.x, scanBox2D.ltfSet.y,
                                      _color_, frameScreenNear);// 前后连
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rtnSet.x, scanBox2D.rtnSet.y,
                                      scanBox2D.rtfSet.x, scanBox2D.rtfSet.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rbnSet.x, scanBox2D.rbnSet.y,
                                      scanBox2D.rbfSet.x, scanBox2D.rbfSet.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.lbnSet.x, scanBox2D.lbnSet.y,
                                      scanBox2D.lbfSet.x, scanBox2D.lbfSet.y,
                                      _color_, frameScreenNear);

DEBUG_SECTION(
        if (flatLeftFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.rtn_ltn_tip.x, scanBox2D.rtn_ltn_tip.y,
                                          scanBox2D.ltnSet.x, scanBox2D.ltnSet.y,
                                          _color_, frameScreenNear);


        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.rtn_ltn_tip.x, scanBox2D.rtn_ltn_tip.y,
                                          scanBox2D.ltnSet.x, scanBox2D.ltnSet.y,
                                          _color_, frameScreenNear);

        }
        if (flatTopFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.lbn_ltn_tip.x, scanBox2D.lbn_ltn_tip.y,
                                          scanBox2D.ltnSet.x, scanBox2D.ltnSet.y,
                                          _color_, frameScreenNear);

        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.lbn_ltn_tip.x, scanBox2D.lbn_ltn_tip.y,
                                          scanBox2D.ltnSet.x, scanBox2D.ltnSet.y,
                                          _color_, frameScreenNear);

        }
        if (flatFrontFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.ltf_ltn_tip.x, scanBox2D.ltf_ltn_tip.y,
                                          scanBox2D.ltnSet.x, scanBox2D.ltnSet.y,
                                          _color_, frameScreenNear);
        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.ltf_ltn_tip.x, scanBox2D.ltf_ltn_tip.y,
                                          scanBox2D.ltnSet.x, scanBox2D.ltnSet.y,
                                          _color_, frameScreenNear);

        }
        if (flatRightFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.lbf_rbf_tip.x, scanBox2D.lbf_rbf_tip.y,
                                          scanBox2D.rbfSet.x, scanBox2D.rbfSet.y,
                                          _color_, frameScreenNear);
        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.lbf_rbf_tip.x, scanBox2D.lbf_rbf_tip.y,
                                          scanBox2D.rbfSet.x, scanBox2D.rbfSet.y,
                                          _color_, frameScreenNear);

        }
        if (flatBottomFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.rtf_rbf_tip.x, scanBox2D.rtf_rbf_tip.y,
                                          scanBox2D.rbfSet.x, scanBox2D.rbfSet.y,
                                          _color_, frameScreenNear);
        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.rtf_rbf_tip.x, scanBox2D.rtf_rbf_tip.y,
                                          scanBox2D.rbfSet.x, scanBox2D.rbfSet.y,
                                          _color_, frameScreenNear);

        }

        if (flatBackFacing) {
            _color_[0] = 0.0f;
            _color_[1] = 1.0f;
            _color_[2] = 0.0f; // 绿色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.rbn_rbf_tip.x, scanBox2D.rbn_rbf_tip.y,
                                          scanBox2D.rbfSet.x, scanBox2D.rbfSet.y,
                                          _color_, frameScreenNear);
        } else {
            _color_[0] = 1.0f;
            _color_[1] = 0.0f;
            _color_[2] = 0.0f; // 红色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          scanBox2D.rbn_rbf_tip.x, scanBox2D.rbn_rbf_tip.y,
                                          scanBox2D.rbfSet.x, scanBox2D.rbfSet.y,
                                          _color_, frameScreenNear);
        }
)
    }
    if(debugLine==2) {
        freshTheAxis(); // 更新坐标轴 info
        //drawSphereAxis(ScreenEye); // 画坐标轴
    }
    afterMoved = 0; // 是否 前帧移动
}
bool EquationTwo::cTipEyeCloser(glm::vec3 eyeCenter, glm::vec3 tip, glm::vec3 back){
    float tipDis_square = (tip.x - eyeCenter.x)*(tip.x - eyeCenter.x) +
                          (tip.y - eyeCenter.y)*(tip.y - eyeCenter.y) +
                          (tip.z - eyeCenter.z)*(tip.z - eyeCenter.z);
    float backDis_square = (back.x - eyeCenter.x)*(back.x - eyeCenter.x) +
                           (back.y - eyeCenter.y)*(back.y - eyeCenter.y) +
                           (back.z - eyeCenter.z)*(back.z - eyeCenter.z);
    return tipDis_square < backDis_square;
}
void EquationTwo::solidRectangle2D_front(ScreenDemo* ScreenEye) {

    // 默认 0 ltn 1 rtn 2 rbn 3 lbn
    PolygonBase::fresh2D_scanRows_4(scanBox2D.ltnSet,
                                    scanBox2D.rtnSet,
                                    scanBox2D.rbnSet,
                                    scanBox2D.lbnSet, &lineScanFillColor_front,type_);
    if(afterMoved == 1) { // 移动了 才 更新 pixels 信息
        pixelSurfaceInfo_front.clear();

        for (auto &_linePosInfo: lineScanFillColor_front) { // 行循环
            if (_linePosInfo.rx == _linePosInfo.lx) {
                // 屏幕外的行 左右x相同
                continue;
            }
            rowPixelInfo20 rowpixelsInfo;
            rowpixelsInfo.y = (float) _linePosInfo.y; // 本行 y
            for (int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++) { // 单像素循环

                glm::vec3 startEye_Self = screenXYZ2SelfXYZ2(startEye);
                glm::vec3 screenPoint_Self = screenXYZ2SelfXYZ2({nowX, _linePosInfo.y, 0.f});
                goLine32 eyeRay_Self = ScreenDemo::get_AgoB_direction3D(startEye_Self, screenPoint_Self); // 计算视线

                goLine32 eyeRay_ScreenAxis = ScreenDemo::get_AgoB_direction3D(startEye,
                                                                              {nowX, _linePosInfo.y, 0.f}); // 视线 屏幕坐标系

                // 计算视线与方程的交点   ①最多两个解 ②步长 > 0 ③在盒内
                RayCalcInfo20 step_vy = solveQuadratic(startEye_Self.x, startEye_Self.y, startEye_Self.z,
                                                       eyeRay_Self.dx, eyeRay_Self.dy, eyeRay_Self.dz,
                                                       startEye_Self, eyeRay_Self);


                step_vy.solveBy = getSolveBy(step_vy.surfacePoint_Self, step_vy.vy);

//          cout << "surfacePoint_Self(" << surfacePoint_Self.x << ", " <<
//          surfacePoint_Self.y << ", " << surfacePoint_Self.z << ")" << endl;
                glm::vec3 surfacePoint_Screen = startEye + (float) step_vy.step * eyeRay_ScreenAxis._;
//            cout << "surfacePoint_Screen(" << surfacePoint_Screen.x << ", " <<
//            surfacePoint_Screen.y << ", " << surfacePoint_Screen.z << ")" << endl;

                struct onepixelInfo20 pixelsInfoNow;

                if (!isnan(step_vy.step)) {
                    float deepNow = startEye.z + step_vy.step * eyeRay_ScreenAxis.dz; // 视线与方程交点深度

                    if (deepNow < frameScreenNear) {
                        frameScreenNear = deepNow; // 刷新 近 屏垂距
                    } else if (deepNow > frameScreenFar) {
                        frameScreenFar = deepNow; // 刷新 远 屏垂距
                    }
//               cout << "y.imag() 自己系:" << step_vy.vy << " 屏垂距:" << deepNow << endl;
                    glm::vec3 colorNow;
                    if (abs(step_vy.vy) < 1e-6) {
                        colorNow = {1.f, 1.f, 1.f}; // 实数y 白色
                    } else {
                        colorNow = getColorBy_vY(step_vy.solveBy, step_vy.vy);
                    }


                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = nowX;
                    pixelsInfoNow.screenDeep = deepNow;
                    pixelsInfoNow.rgb[0] = colorNow[0];
                    pixelsInfoNow.rgb[1] = colorNow[1];
                    pixelsInfoNow.rgb[2] = colorNow[2];
                } else {
                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = 0;
                    pixelsInfoNow.screenDeep = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[0] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[1] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[2] = numeric_limits<float>::quiet_NaN();
                }


                rowpixelsInfo.pixelDeeps.push_back(pixelsInfoNow); // 本行 像素 信息
            }
            pixelSurfaceInfo_front.push_back(rowpixelsInfo); // 所有行 像素
        }
    }

    for(auto& _lineDeepInfo : pixelSurfaceInfo_front) {
        size_t vecSizeCurrent = _lineDeepInfo.pixelDeeps.size();
        for (int i = 0; i < vecSizeCurrent/*-1*/; i++) {
            if(!isnan(_lineDeepInfo.pixelDeeps[i].rgb[0])){
                ScreenEye->putPixel(_lineDeepInfo.pixelDeeps[i].x,static_cast<int>(_lineDeepInfo.y),
                                    _lineDeepInfo.pixelDeeps[i].rgb,_lineDeepInfo.pixelDeeps[i].screenDeep,(PolygonBase*)this);
            }

        }
    }

}
void EquationTwo::solidRectangle2D_left(ScreenDemo* ScreenEye) {

    // 默认 0 ltf 1 ltn 2 lbn 3 lbf
    PolygonBase::fresh2D_scanRows_4(scanBox2D.ltfSet,
                                    scanBox2D.ltnSet,
                                    scanBox2D.lbnSet,
                                    scanBox2D.lbfSet, &lineScanFillColor_left,type_);
    if(afterMoved == 1) { // 移动了 才 更新 pixels 信息
        pixelSurfaceInfo_left.clear();

        for (auto &_linePosInfo: lineScanFillColor_left) { // 行循环
            if (_linePosInfo.rx == _linePosInfo.lx) {
                // 屏幕外的行 左右x相同
                continue;
            }
            rowPixelInfo20 rowpixelsInfo;
            rowpixelsInfo.y = (float) _linePosInfo.y; // 本行 y
            for (int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++) { // 单像素循环
                glm::vec3 startEye_Self = screenXYZ2SelfXYZ2(startEye);
                glm::vec3 screenPoint_Self = screenXYZ2SelfXYZ2({nowX, _linePosInfo.y, 0.f});
                goLine32 eyeRay_Self = ScreenDemo::get_AgoB_direction3D(startEye_Self, screenPoint_Self); // 计算视线

                goLine32 eyeRay_ScreenAxis = ScreenDemo::get_AgoB_direction3D(startEye,
                                                                              {nowX, _linePosInfo.y, 0.f}); // 视线 屏幕坐标系

                // 计算视线与方程的交点   ①最多两个解 ②步长 > 0 ③在盒内
                RayCalcInfo20 step_vy = solveQuadratic(startEye_Self.x, startEye_Self.y, startEye_Self.z,
                                                       eyeRay_Self.dx, eyeRay_Self.dy, eyeRay_Self.dz,
                                                       startEye_Self, eyeRay_Self);


                step_vy.solveBy = getSolveBy(step_vy.surfacePoint_Self, step_vy.vy);

//          cout << "surfacePoint_Self(" << surfacePoint_Self.x << ", " <<
//          surfacePoint_Self.y << ", " << surfacePoint_Self.z << ")" << endl;
                glm::vec3 surfacePoint_Screen = startEye + (float) step_vy.step * eyeRay_ScreenAxis._;
//            cout << "surfacePoint_Screen(" << surfacePoint_Screen.x << ", " <<
//            surfacePoint_Screen.y << ", " << surfacePoint_Screen.z << ")" << endl;

                struct onepixelInfo20 pixelsInfoNow;

                if (!isnan(step_vy.step)) {
                    float deepNow = startEye.z + step_vy.step * eyeRay_ScreenAxis.dz; // 视线与方程交点深度

                    if (deepNow < frameScreenNear) {
                        frameScreenNear = deepNow; // 刷新 近 屏垂距
                    } else if (deepNow > frameScreenFar) {
                        frameScreenFar = deepNow; // 刷新 远 屏垂距
                    }
//               cout << "y.imag() 自己系:" << step_vy.vy << " 屏垂距:" << deepNow << endl;
                    glm::vec3 colorNow;
                    if (abs(step_vy.vy) < 1e-6) {
                        colorNow = {1.f, 1.f, 1.f}; // 实数y 白色
                    } else {
                        colorNow = getColorBy_vY(step_vy.solveBy, step_vy.vy);
                    }


                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = nowX;
                    pixelsInfoNow.screenDeep = deepNow;
                    pixelsInfoNow.rgb[0] = colorNow[0];
                    pixelsInfoNow.rgb[1] = colorNow[1];
                    pixelsInfoNow.rgb[2] = colorNow[2];
                } else {
                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = 0;
                    pixelsInfoNow.screenDeep = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[0] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[1] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[2] = numeric_limits<float>::quiet_NaN();
                }


                rowpixelsInfo.pixelDeeps.push_back(pixelsInfoNow); // 本行 像素 信息
            }
            pixelSurfaceInfo_left.push_back(rowpixelsInfo); // 所有行 像素
        }
    }

    for(auto& _lineDeepInfo : pixelSurfaceInfo_left) {
        size_t vecSizeCurrent = _lineDeepInfo.pixelDeeps.size();
        for (int i = 0; i < vecSizeCurrent/*-1*/; i++) {
            if(!isnan(_lineDeepInfo.pixelDeeps[i].rgb[0])){
                ScreenEye->putPixel(_lineDeepInfo.pixelDeeps[i].x,static_cast<int>(_lineDeepInfo.y),
                                    _lineDeepInfo.pixelDeeps[i].rgb,_lineDeepInfo.pixelDeeps[i].screenDeep,(PolygonBase*)this);
            }

        }
    }

}
void EquationTwo::solidRectangle2D_right(ScreenDemo* ScreenEye) {

    // 默认 0 rtn 1 rtf 2 rbf 3 rbn
    PolygonBase::fresh2D_scanRows_4(scanBox2D.rtnSet,
                                    scanBox2D.rtfSet,
                                    scanBox2D.rbfSet,
                                    scanBox2D.rbnSet, &lineScanFillColor_right,type_);
    if(afterMoved == 1) { // 移动了 才 更新 pixels 信息
        pixelSurfaceInfo_right.clear();

        for (auto &_linePosInfo: lineScanFillColor_right) { // 行循环
            if (_linePosInfo.rx == _linePosInfo.lx) {
                // 屏幕外的行 左右x相同
                continue;
            }
            rowPixelInfo20 rowpixelsInfo;
            rowpixelsInfo.y = (float) _linePosInfo.y; // 本行 y
            for (int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++) { // 单像素循环
                glm::vec3 startEye_Self = screenXYZ2SelfXYZ2(startEye);
                glm::vec3 screenPoint_Self = screenXYZ2SelfXYZ2({nowX, _linePosInfo.y, 0.f});
                goLine32 eyeRay_Self = ScreenDemo::get_AgoB_direction3D(startEye_Self, screenPoint_Self); // 计算视线

                goLine32 eyeRay_ScreenAxis = ScreenDemo::get_AgoB_direction3D(startEye,
                                                                              {nowX, _linePosInfo.y, 0.f}); // 视线 屏幕坐标系

                // 计算视线与方程的交点   ①最多两个解 ②步长 > 0 ③在盒内
                RayCalcInfo20 step_vy = solveQuadratic(startEye_Self.x, startEye_Self.y, startEye_Self.z,
                                                       eyeRay_Self.dx, eyeRay_Self.dy, eyeRay_Self.dz,
                                                       startEye_Self, eyeRay_Self);


                step_vy.solveBy = getSolveBy(step_vy.surfacePoint_Self, step_vy.vy);

//          cout << "surfacePoint_Self(" << surfacePoint_Self.x << ", " <<
//          surfacePoint_Self.y << ", " << surfacePoint_Self.z << ")" << endl;
                glm::vec3 surfacePoint_Screen = startEye + (float) step_vy.step * eyeRay_ScreenAxis._;
//            cout << "surfacePoint_Screen(" << surfacePoint_Screen.x << ", " <<
//            surfacePoint_Screen.y << ", " << surfacePoint_Screen.z << ")" << endl;

                struct onepixelInfo20 pixelsInfoNow;

                if (!isnan(step_vy.step)) {
                    float deepNow = startEye.z + step_vy.step * eyeRay_ScreenAxis.dz; // 视线与方程交点深度

                    if (deepNow < frameScreenNear) {
                        frameScreenNear = deepNow; // 刷新 近 屏垂距
                    } else if (deepNow > frameScreenFar) {
                        frameScreenFar = deepNow; // 刷新 远 屏垂距
                    }
//               cout << "y.imag() 自己系:" << step_vy.vy << " 屏垂距:" << deepNow << endl;
                    glm::vec3 colorNow;
                    if (abs(step_vy.vy) < 1e-6) {
                        colorNow = {1.f, 1.f, 1.f}; // 实数y 白色
                    } else {
                        colorNow = getColorBy_vY(step_vy.solveBy, step_vy.vy);
                    }


                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = nowX;
                    pixelsInfoNow.screenDeep = deepNow;
                    pixelsInfoNow.rgb[0] = colorNow[0];
                    pixelsInfoNow.rgb[1] = colorNow[1];
                    pixelsInfoNow.rgb[2] = colorNow[2];
                } else {
                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = 0;
                    pixelsInfoNow.screenDeep = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[0] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[1] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[2] = numeric_limits<float>::quiet_NaN();
                }


                rowpixelsInfo.pixelDeeps.push_back(pixelsInfoNow); // 本行 像素 信息
            }
            pixelSurfaceInfo_right.push_back(rowpixelsInfo); // 所有行 像素
        }
    }

    for(auto& _lineDeepInfo : pixelSurfaceInfo_right) {
        size_t vecSizeCurrent = _lineDeepInfo.pixelDeeps.size();
        for (int i = 0; i < vecSizeCurrent/*-1*/; i++) {
            if(!isnan(_lineDeepInfo.pixelDeeps[i].rgb[0])){
                ScreenEye->putPixel(_lineDeepInfo.pixelDeeps[i].x,static_cast<int>(_lineDeepInfo.y),
                                    _lineDeepInfo.pixelDeeps[i].rgb,_lineDeepInfo.pixelDeeps[i].screenDeep,(PolygonBase*)this);
            }

        }
    }

}
void EquationTwo::solidRectangle2D_back(ScreenDemo* ScreenEye) {

    // 默认 0 rtf 1 ltf 2 lbf 3 rbf
    PolygonBase::fresh2D_scanRows_4(scanBox2D.rtfSet,
                                    scanBox2D.ltfSet,
                                    scanBox2D.lbfSet,
                                    scanBox2D.rbfSet, &lineScanFillColor_back,type_);
    if(afterMoved == 1) { // 移动了 才 更新 pixels 信息
        pixelSurfaceInfo_back.clear();

        for (auto &_linePosInfo: lineScanFillColor_back) { // 行循环
            if (_linePosInfo.rx == _linePosInfo.lx) {
                // 屏幕外的行 左右x相同
                continue;
            }
            rowPixelInfo20 rowpixelsInfo;
            rowpixelsInfo.y = (float) _linePosInfo.y; // 本行 y
            for (int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++) { // 单像素循环
                glm::vec3 startEye_Self = screenXYZ2SelfXYZ2(startEye);
                glm::vec3 screenPoint_Self = screenXYZ2SelfXYZ2({nowX, _linePosInfo.y, 0.f});
                goLine32 eyeRay_Self = ScreenDemo::get_AgoB_direction3D(startEye_Self, screenPoint_Self); // 计算视线

                goLine32 eyeRay_ScreenAxis = ScreenDemo::get_AgoB_direction3D(startEye,
                                                                              {nowX, _linePosInfo.y, 0.f}); // 视线 屏幕坐标系

                // 计算视线与方程的交点   ①最多两个解 ②步长 > 0 ③在盒内
                RayCalcInfo20 step_vy = solveQuadratic(startEye_Self.x, startEye_Self.y, startEye_Self.z,
                                                       eyeRay_Self.dx, eyeRay_Self.dy, eyeRay_Self.dz,
                                                       startEye_Self, eyeRay_Self);


                step_vy.solveBy = getSolveBy(step_vy.surfacePoint_Self, step_vy.vy);

//          cout << "surfacePoint_Self(" << surfacePoint_Self.x << ", " <<
//          surfacePoint_Self.y << ", " << surfacePoint_Self.z << ")" << endl;
                glm::vec3 surfacePoint_Screen = startEye + (float) step_vy.step * eyeRay_ScreenAxis._;
//            cout << "surfacePoint_Screen(" << surfacePoint_Screen.x << ", " <<
//            surfacePoint_Screen.y << ", " << surfacePoint_Screen.z << ")" << endl;

                struct onepixelInfo20 pixelsInfoNow;

                if (!isnan(step_vy.step)) {
                    float deepNow = startEye.z + step_vy.step * eyeRay_ScreenAxis.dz; // 视线与方程交点深度

                    if (deepNow < frameScreenNear) {
                        frameScreenNear = deepNow; // 刷新 近 屏垂距
                    } else if (deepNow > frameScreenFar) {
                        frameScreenFar = deepNow; // 刷新 远 屏垂距
                    }
//               cout << "y.imag() 自己系:" << step_vy.vy << " 屏垂距:" << deepNow << endl;
                    glm::vec3 colorNow;
                    if (abs(step_vy.vy) < 1e-6) {
                        colorNow = {1.f, 1.f, 1.f}; // 实数y 白色
                    } else {
                        colorNow = getColorBy_vY(step_vy.solveBy, step_vy.vy);
                    }


                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = nowX;
                    pixelsInfoNow.screenDeep = deepNow;
                    pixelsInfoNow.rgb[0] = colorNow[0];
                    pixelsInfoNow.rgb[1] = colorNow[1];
                    pixelsInfoNow.rgb[2] = colorNow[2];
                } else {
                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = 0;
                    pixelsInfoNow.screenDeep = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[0] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[1] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[2] = numeric_limits<float>::quiet_NaN();
                }


                rowpixelsInfo.pixelDeeps.push_back(pixelsInfoNow); // 本行 像素 信息
            }
            pixelSurfaceInfo_back.push_back(rowpixelsInfo); // 所有行 像素
        }
    }

    for(auto& _lineDeepInfo : pixelSurfaceInfo_back) {
        size_t vecSizeCurrent = _lineDeepInfo.pixelDeeps.size();
        for (int i = 0; i < vecSizeCurrent/*-1*/; i++) {
            if(!isnan(_lineDeepInfo.pixelDeeps[i].rgb[0])){
                ScreenEye->putPixel(_lineDeepInfo.pixelDeeps[i].x,static_cast<int>(_lineDeepInfo.y),
                                    _lineDeepInfo.pixelDeeps[i].rgb,_lineDeepInfo.pixelDeeps[i].screenDeep,(PolygonBase*)this);
            }

        }
    }

}
void EquationTwo::solidRectangle2D_top(ScreenDemo* ScreenEye) {

    // 默认 0 ltf 1 rtf 2 rtn 3 ltn
    PolygonBase::fresh2D_scanRows_4(scanBox2D.ltfSet,
                                    scanBox2D.rtfSet,
                                    scanBox2D.rtnSet,
                                    scanBox2D.ltnSet, &lineScanFillColor_top,type_);
    if(afterMoved == 1) { // 移动了 才 更新 pixels 信息
        pixelSurfaceInfo_top.clear();

        for (auto &_linePosInfo: lineScanFillColor_top) { // 行循环
            if (_linePosInfo.rx == _linePosInfo.lx) {
                // 屏幕外的行 左右x相同
                continue;
            }
            rowPixelInfo20 rowpixelsInfo;
            rowpixelsInfo.y = (float) _linePosInfo.y; // 本行 y
            for (int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++) { // 单像素循环
                glm::vec3 startEye_Self = screenXYZ2SelfXYZ2(startEye);
                glm::vec3 screenPoint_Self = screenXYZ2SelfXYZ2({nowX, _linePosInfo.y, 0.f});
                goLine32 eyeRay_Self = ScreenDemo::get_AgoB_direction3D(startEye_Self, screenPoint_Self); // 计算视线

                goLine32 eyeRay_ScreenAxis = ScreenDemo::get_AgoB_direction3D(startEye,
                                                                              {nowX, _linePosInfo.y, 0.f}); // 视线 屏幕坐标系

                // 计算视线与方程的交点   ①最多两个解 ②步长 > 0 ③在盒内
                RayCalcInfo20 step_vy = solveQuadratic(startEye_Self.x, startEye_Self.y, startEye_Self.z,
                                                       eyeRay_Self.dx, eyeRay_Self.dy, eyeRay_Self.dz,
                                                       startEye_Self, eyeRay_Self);


                step_vy.solveBy = getSolveBy(step_vy.surfacePoint_Self, step_vy.vy);

//          cout << "surfacePoint_Self(" << surfacePoint_Self.x << ", " <<
//          surfacePoint_Self.y << ", " << surfacePoint_Self.z << ")" << endl;
                glm::vec3 surfacePoint_Screen = startEye + (float) step_vy.step * eyeRay_ScreenAxis._;
//            cout << "surfacePoint_Screen(" << surfacePoint_Screen.x << ", " <<
//            surfacePoint_Screen.y << ", " << surfacePoint_Screen.z << ")" << endl;

                struct onepixelInfo20 pixelsInfoNow;

                if (!isnan(step_vy.step)) {
                    float deepNow = startEye.z + step_vy.step * eyeRay_ScreenAxis.dz; // 视线与方程交点深度

                    if (deepNow < frameScreenNear) {
                        frameScreenNear = deepNow; // 刷新 近 屏垂距
                    } else if (deepNow > frameScreenFar) {
                        frameScreenFar = deepNow; // 刷新 远 屏垂距
                    }
//               cout << "y.imag() 自己系:" << step_vy.vy << " 屏垂距:" << deepNow << endl;
                    glm::vec3 colorNow;
                    if (abs(step_vy.vy) < 1e-6) {
                        colorNow = {1.f, 1.f, 1.f}; // 实数y 白色
                    } else {
                        colorNow = getColorBy_vY(step_vy.solveBy, step_vy.vy);
                    }


                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = nowX;
                    pixelsInfoNow.screenDeep = deepNow;
                    pixelsInfoNow.rgb[0] = colorNow[0];
                    pixelsInfoNow.rgb[1] = colorNow[1];
                    pixelsInfoNow.rgb[2] = colorNow[2];
                } else {
                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = 0;
                    pixelsInfoNow.screenDeep = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[0] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[1] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[2] = numeric_limits<float>::quiet_NaN();
                }


                rowpixelsInfo.pixelDeeps.push_back(pixelsInfoNow); // 本行 像素 信息
            }
            pixelSurfaceInfo_top.push_back(rowpixelsInfo); // 所有行 像素
        }
    }

    for(auto& _lineDeepInfo : pixelSurfaceInfo_top) {
        size_t vecSizeCurrent = _lineDeepInfo.pixelDeeps.size();
        for (int i = 0; i < vecSizeCurrent/*-1*/; i++) {
            if(!isnan(_lineDeepInfo.pixelDeeps[i].rgb[0])){
                ScreenEye->putPixel(_lineDeepInfo.pixelDeeps[i].x,static_cast<int>(_lineDeepInfo.y),
                                    _lineDeepInfo.pixelDeeps[i].rgb,_lineDeepInfo.pixelDeeps[i].screenDeep,(PolygonBase*)this);
            }

        }
    }

}
void EquationTwo::solidRectangle2D_bottom(ScreenDemo* ScreenEye) {

    // 默认 0 lbn 1 rbn 2 rbf 3 lbf
    PolygonBase::fresh2D_scanRows_4(scanBox2D.lbnSet,
                                    scanBox2D.rbnSet,
                                    scanBox2D.rbfSet,
                                    scanBox2D.lbfSet, &lineScanFillColor_bottom,type_);
    if(afterMoved == 1) { // 移动了 才 更新 pixels 信息
        pixelSurfaceInfo_bottom.clear();

        for (auto &_linePosInfo: lineScanFillColor_bottom) { // 行循环
            if (_linePosInfo.rx == _linePosInfo.lx) {
                // 屏幕外的行 左右x相同
                continue;
            }
            rowPixelInfo20 rowpixelsInfo;
            rowpixelsInfo.y = (float) _linePosInfo.y; // 本行 y
            for (int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++) { // 单像素循环
                glm::vec3 startEye_Self = screenXYZ2SelfXYZ2(startEye);
                glm::vec3 screenPoint_Self = screenXYZ2SelfXYZ2({nowX, _linePosInfo.y, 0.f});
                goLine32 eyeRay_Self = ScreenDemo::get_AgoB_direction3D(startEye_Self, screenPoint_Self); // 计算视线

                goLine32 eyeRay_ScreenAxis = ScreenDemo::get_AgoB_direction3D(startEye,
                                                                              {nowX, _linePosInfo.y, 0.f}); // 视线 屏幕坐标系

                // 计算视线与方程的交点   ①最多两个解 ②步长 > 0 ③在盒内
                RayCalcInfo20 step_vy = solveQuadratic(startEye_Self.x, startEye_Self.y, startEye_Self.z,
                                                       eyeRay_Self.dx, eyeRay_Self.dy, eyeRay_Self.dz,
                                                       startEye_Self, eyeRay_Self);


                step_vy.solveBy = getSolveBy(step_vy.surfacePoint_Self, step_vy.vy);

//          cout << "surfacePoint_Self(" << surfacePoint_Self.x << ", " <<
//          surfacePoint_Self.y << ", " << surfacePoint_Self.z << ")" << endl;
                glm::vec3 surfacePoint_Screen = startEye + (float) step_vy.step * eyeRay_ScreenAxis._;
//            cout << "surfacePoint_Screen(" << surfacePoint_Screen.x << ", " <<
//            surfacePoint_Screen.y << ", " << surfacePoint_Screen.z << ")" << endl;

                struct onepixelInfo20 pixelsInfoNow;

                if (!isnan(step_vy.step)) {
                    float deepNow = startEye.z + step_vy.step * eyeRay_ScreenAxis.dz; // 视线与方程交点深度

                    if (deepNow < frameScreenNear) {
                        frameScreenNear = deepNow; // 刷新 近 屏垂距
                    } else if (deepNow > frameScreenFar) {
                        frameScreenFar = deepNow; // 刷新 远 屏垂距
                    }
//               cout << "y.imag() 自己系:" << step_vy.vy << " 屏垂距:" << deepNow << endl;
                    glm::vec3 colorNow;
                    if (abs(step_vy.vy) < 1e-6) {
                        colorNow = {1.f, 1.f, 1.f}; // 实数y 白色
                    } else {
                        colorNow = getColorBy_vY(step_vy.solveBy, step_vy.vy);
                    }


                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = nowX;
                    pixelsInfoNow.screenDeep = deepNow;
                    pixelsInfoNow.rgb[0] = colorNow[0];
                    pixelsInfoNow.rgb[1] = colorNow[1];
                    pixelsInfoNow.rgb[2] = colorNow[2];
                } else {
                    // x 屏垂距 y虚部 步长 颜色
                    pixelsInfoNow.x = 0;
                    pixelsInfoNow.screenDeep = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[0] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[1] = numeric_limits<float>::quiet_NaN();
                    pixelsInfoNow.rgb[2] = numeric_limits<float>::quiet_NaN();
                }


                rowpixelsInfo.pixelDeeps.push_back(pixelsInfoNow); // 本行 像素 信息
            }
            pixelSurfaceInfo_bottom.push_back(rowpixelsInfo); // 所有行 像素
        }
    }

    for(auto& _lineDeepInfo : pixelSurfaceInfo_bottom) {
        size_t vecSizeCurrent = _lineDeepInfo.pixelDeeps.size();
        for (int i = 0; i < vecSizeCurrent/*-1*/; i++) {
            if(!isnan(_lineDeepInfo.pixelDeeps[i].rgb[0])){
                ScreenEye->putPixel(_lineDeepInfo.pixelDeeps[i].x,static_cast<int>(_lineDeepInfo.y),
                                    _lineDeepInfo.pixelDeeps[i].rgb,_lineDeepInfo.pixelDeeps[i].screenDeep,(PolygonBase*)this);
            }

        }
    }

}
void EquationTwo::deepFarNearBackCenter(){
    frameScreenFar = virtual_scanBox3D.center.z;
    frameScreenNear = virtual_scanBox3D.center.z;
}
void EquationTwo::setFrontColor(int _color1, int _color2) {
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

void EquationTwo::setBackColor(int _color) {
    BGR3f colorNow;
    colorNow.setBGR(_color,1);
    backColor_rgb01[0] = colorNow.r1;
    backColor_rgb01[1] = colorNow.g1;
    backColor_rgb01[2] = colorNow.b1;
}

void EquationTwo::freshGoX(){
    world_toX.dx = (scanBox3D.rtnSet.x - scanBox3D.ltnSet.x) / boxLenX;
    world_toX.dy = (scanBox3D.rtnSet.y - scanBox3D.ltnSet.y) / boxLenX;
    world_toX.dz = (scanBox3D.rtnSet.z - scanBox3D.ltnSet.z) / boxLenX;
}
void EquationTwo::freshGoY(){
    world_toY.dx = (scanBox3D.lbnSet.x - scanBox3D.ltnSet.x) / boxLenY;
    world_toY.dy = (scanBox3D.lbnSet.y - scanBox3D.ltnSet.y) / boxLenY;
    world_toY.dz = (scanBox3D.lbnSet.z - scanBox3D.ltnSet.z) / boxLenY;
}
void EquationTwo::freshGoDEEP() {
    world_toDEEP.dx = (scanBox3D.ltfSet.x - scanBox3D.ltnSet.x) / boxLenZ;
    world_toDEEP.dy = (scanBox3D.ltfSet.y - scanBox3D.ltnSet.y) / boxLenZ;
    world_toDEEP.dz = (scanBox3D.ltfSet.z - scanBox3D.ltnSet.z) / boxLenZ;
//    world_toDEEP = ScreenDemo::get_AgoB_direction3D(scanBox3D.ltnSet, scanBox3D.ltfSet);
}
glm::vec3 EquationTwo::goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toX._;
    return _srcXYZ;
}
glm::vec3 EquationTwo::goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toY._;
    return _srcXYZ;
}
glm::vec3 EquationTwo::goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toDEEP._;
    return _srcXYZ;
}

const double EPSILON = 1e-12; // 处理浮点精度误差

RayCalcInfo20 EquationTwo::solveQuadratic(
        double ex, double ey, double ez,
        double dx, double dy, double dz,glm::vec3 startEye_Self,goLine32 eyeRay_Self)
{
    vector<pair<double, double>> solutions; // 视线步长 y虚部
    RayCalcInfo20 result;
    glm::vec3 surfacePoint_now;

    auto getSurfacePoint_Self = [startEye_Self,eyeRay_Self](float step) -> glm::vec3{
        return startEye_Self + step * eyeRay_Self._;
    };

    // 计算实部方程系数  a_real*s² + b_real*s + c_real = 0
    double A_real = abc[0] * (dx*dx - dz*dz);
    double B_real = 2.0*abc[0]*(ex*dx - ez*dz) + abc[1]*dx - dy;
    double C_real = abc[0]*(ex*ex - ez*ez) + abc[1]*ex + abc[2] - ey;

    // 计算虚部表达式系数  a_imag*s² + b_imag*s + c_const - vy = 0
    double A_imag = 2.0*abc[0]*dx*dz;
    double B_imag = 2.0*abc[0]*(ex*dz + dx*ez) + abc[1]*dz;
    double C_const = 2.0*abc[0]*ex*ez + abc[1]*ez; // vy的常数项

    // 处理实部方程 A_real*s² + B_real*s + C_real = 0
    if (fabs(A_real) > EPSILON) { // 标准二次方程
        double discriminant = B_real*B_real - 4.0*A_real*C_real; // 跟判别式

        if (discriminant >= 0.0) {
            double sqrt_d = glm::sqrt(discriminant);

            // 第一个解
            double s1 = (-B_real + sqrt_d) / (2.0*A_real); // 求根公式

            if(s1>=0.f){
                double vy1 = C_const + A_imag*s1*s1 + B_imag*s1;
                solutions.emplace_back(s1, vy1);
            }


            // 第二个解（当判别式>0时）
            if (discriminant != 0.0) {
                double s2 = (-B_real - sqrt_d) / (2.0*A_real); // 求根公式

                if(s2>=0.f){
                    double vy2 = C_const + A_imag*s2*s2 + B_imag*s2;
                    solutions.emplace_back(s2, vy2);
                }

            }
        }
    }
    else if (fabs(B_real) > EPSILON) { // 一次方程 B_real*s + C_real = 0
        println(stderr,"Warning: A_real = 0, B_real != 0");
        double s = -C_real / B_real;

        if(s>=0.f){
            double vy = C_const + A_imag*s*s + B_imag*s;
            solutions.emplace_back(s, vy);
        }

    }
    else if (fabs(C_real) < EPSILON) { // 0*s + 0 = 0 (无穷解)
        // 此时虚部方程需满足: A_imag*s² + B_imag*s = vy - C_const
        // 无法枚举所有解，返回空表示无穷解
        println(stderr,"Warning: A_real = 0, B_real = 0, C_real = 0");
        result.step = numeric_limits<float>::quiet_NaN();
        result.vy = numeric_limits<float>::quiet_NaN();
        result.surfacePoint_Self = glm::vec3(numeric_limits<float>::quiet_NaN());
        result.solveBy = numeric_limits<unsigned char>::quiet_NaN();
        return result;

    }

    // 最多两个解
    if(solutions.size() == 2){
        // 选择最近的解
        auto [step1, vy1] = solutions[0]; // + 根式
        auto [step2, vy2] = solutions[1]; // - 根式

        glm::vec3 surfacePoint_1 = getSurfacePoint_Self(step1);
        bool _1InBox = selfPosInBox(surfacePoint_1);
        glm::vec3 surfacePoint_2 = getSurfacePoint_Self(step2);
        bool _2InBox = selfPosInBox(surfacePoint_2);

        if(_1InBox && _2InBox){ // 两点 都在 box (步大零)
            // 两个解都在屏幕系正半轴上，选择距离中心最近的解
            if(step1 < step2){ // 看谁近
                result.step = step1; // +式
                result.vy = vy1;
                result.surfacePoint_Self = surfacePoint_1;
                result.solveBy = numeric_limits<unsigned char>::quiet_NaN();
                return result;
            }else{ // 看谁近
                result.step = step2; // -式
                result.vy = vy2;
                result.surfacePoint_Self = surfacePoint_2;
                result.solveBy = numeric_limits<unsigned char>::quiet_NaN();
                return result;
            }
        }else if(_1InBox){ // +式 在盒内 (步大零)
            result.step = step1;
            result.vy = vy1;
            result.surfacePoint_Self = surfacePoint_1;
            result.solveBy = numeric_limits<unsigned char>::quiet_NaN();
            return result;
        }else if(_2InBox){ // -式 在盒内 (步大零)
            result.step = step2;
            result.vy = vy2;
            result.surfacePoint_Self = surfacePoint_2;
            result.solveBy = numeric_limits<unsigned char>::quiet_NaN();
            return result;
        }


    }else if(solutions.size() == 1){ //
        auto [step1, vy1] = solutions[0]; // + 根式

        surfacePoint_now = getSurfacePoint_Self(step1);
        bool thisInBox = selfPosInBox(surfacePoint_now);
        if(thisInBox){ // 在盒内
            result.step = step1;
            result.vy = vy1;
            result.surfacePoint_Self = surfacePoint_now;
            result.solveBy = numeric_limits<unsigned char>::quiet_NaN();
            return result;
        }

    }
    result.step = numeric_limits<double>::quiet_NaN();
    result.vy = numeric_limits<double>::quiet_NaN();
    result.surfacePoint_Self = glm::vec3(numeric_limits<float>::quiet_NaN());
    result.solveBy = numeric_limits<unsigned char>::quiet_NaN();
    return result;
}
unsigned char EquationTwo::getSolveBy(glm::dvec3 surfacePoint_Self, double vy){

    complex<double> x = {surfacePoint_Self.x, surfacePoint_Self.z};
    complex<double> y = {surfacePoint_Self.y, vy};

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

    const double tol = 1e-3; // 精度要求高了 视线不命中 !!!

    if(x1_real_err < tol && x1_imag_err < tol){
        return 1; // + 根式
    }else if(x2_real_err < tol && x2_imag_err < tol){
        return 2; // - 根式
    }
    // 整数 nan 是 0
    return 0; // 无根式

}
glm::vec3 EquationTwo::getColorBy_vY(unsigned char solveBy, float _vY){
    int remainder = static_cast<int>(_vY) % 10; // -9~9

    float colorRatio = 1.f + 0.07f * (float)remainder;

    if(solveBy == 1){ // + 根式
       return frontColor1_rgb01 * colorRatio;

    }else if(solveBy == 2){ // - 根式
        return frontColor2_rgb01 * colorRatio;

    }


    return glm::vec3{std::numeric_limits<float>::quiet_NaN()};

}
/* 使用示例：
auto results = solveQuadratic(ex, ey, ez, dx, dy, dz, a, b, c);
for (auto& [step, vy] : results) {
    cout << "step: " << step << ", vy: " << vy << endl;
}
*/
void EquationTwo::freshVirtualGoX() {
    // 提前 求向量长度 便于归一化
//    virtual_squareEdgeLen = glm::distance(virtual_scanBox3D.ltnSet, virtual_scanBox3D.rtnSet);

    virtual_toX.dx = (virtual_scanBox3D.rtnSet.x - virtual_scanBox3D.ltnSet.x) / boxLenX;
    virtual_toX.dy = (virtual_scanBox3D.rtnSet.y - virtual_scanBox3D.ltnSet.y) / boxLenX;
    virtual_toX.dz = (virtual_scanBox3D.rtnSet.z - virtual_scanBox3D.ltnSet.z) / boxLenX;
//    virtual_toX = ScreenDemo::get_AgoB_direction3D(virtual_scanBox3D.ltnSet, virtual_scanBox3D.rtnSet);
}

void EquationTwo::freshVirtualGoY() {
    virtual_toY.dx = (virtual_scanBox3D.lbnSet.x - virtual_scanBox3D.ltnSet.x) / boxLenY;
    virtual_toY.dy = (virtual_scanBox3D.lbnSet.y - virtual_scanBox3D.ltnSet.y) / boxLenY;
    virtual_toY.dz = (virtual_scanBox3D.lbnSet.z - virtual_scanBox3D.ltnSet.z) / boxLenY;
//    virtual_toY = ScreenDemo::get_AgoB_direction3D(virtual_scanBox3D.ltnSet, virtual_scanBox3D.lbnSet);
}

void EquationTwo::freshVirtualGoDEEP() {
    virtual_toDEEP.dx = (virtual_scanBox3D.ltfSet.x - virtual_scanBox3D.ltnSet.x) / boxLenZ;
    virtual_toDEEP.dy = (virtual_scanBox3D.ltfSet.y - virtual_scanBox3D.ltnSet.y) / boxLenZ;
    virtual_toDEEP.dz = (virtual_scanBox3D.ltfSet.z - virtual_scanBox3D.ltnSet.z) / boxLenZ;
//    virtual_toDEEP = ScreenDemo::get_AgoB_direction3D(virtual_scanBox3D.ltnSet, virtual_scanBox3D.ltfSet);
}
glm::vec3 EquationTwo::Virtual_goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toX._;
    return _srcXYZ;
}
glm::vec3 EquationTwo::Virtual_goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toY._;
    return _srcXYZ;
}
glm::vec3 EquationTwo::Virtual_goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toDEEP._;
    return _srcXYZ;
}
glm::vec3 EquationTwo::self2screenAxis(glm::vec3 _selfAxisPos){
    // 屏幕系下 自己系 斜走x 斜走y 斜走z
    glm::vec3 posNow = virtual_scanBox3D.center;
    posNow = Virtual_goX(posNow, _selfAxisPos.x);
    posNow = Virtual_goY(posNow, _selfAxisPos.y);
    posNow = Virtual_goDEEP(posNow, _selfAxisPos.z);
    return posNow;
}
void EquationTwo::freshFrameRotateInfo(){
    frameRotateInfo_q = PolygonBase::getFrameRotateInfo_(virtual_toX,virtual_toDEEP);
}
glm::vec3 EquationTwo::screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos){
    if(isnan(_screenAxisPos.x) || isnan(_screenAxisPos.y) || isnan(_screenAxisPos.z)){
        println(stderr,"NAN _screenAxisPos({}, {}, {})",
            _screenAxisPos.x,_screenAxisPos.y,_screenAxisPos.z);
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
        println(stderr,"NAN farScreenAxis000({}, {}, {})",
            farScreenAxis000.x,farScreenAxis000.y,farScreenAxis000.z);
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }
    return farScreenAxis000;
}

bool EquationTwo::selfPosInBox(glm::vec3 _selfPos){
    float expand = 0.0f;
    bool pointInBox = _selfPos.x > -(halfBoxLength.x+expand) && _selfPos.x < (halfBoxLength.x+expand) &&
    _selfPos.y > -(halfBoxLength.y+expand) && _selfPos.y < (halfBoxLength.y+expand) &&
    _selfPos.z > -(halfBoxLength.z+expand) && _selfPos.z < (halfBoxLength.z+expand);
    return pointInBox;
}


void EquationTwo::freshTiltAxis(){
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

void EquationTwo::freshParallelAxis(){
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

void EquationTwo::drawTiltAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴  世界系 屏幕系 3D→2D
    tiltAxis2D_f[0] = __3d2dGoEquation2(ScreenEye, tiltAxis3D[0], nullptr);
    tiltAxis2D_f[1] = __3d2dGoEquation2(ScreenEye, tiltAxis3D[1], nullptr);
    tiltAxis2D_f[2] = __3d2dGoEquation2(ScreenEye, tiltAxis3D[2], nullptr);
    tiltAxis2D_f[3] = __3d2dGoEquation2(ScreenEye, tiltAxis3D[3], nullptr);


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

void EquationTwo::drawParallelAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴
    parallelAxis2D_f[0] = __3d2dGoEquation2(ScreenEye, parallelAxis3D[0], nullptr);
    parallelAxis2D_f[1] = __3d2dGoEquation2(ScreenEye, parallelAxis3D[1], nullptr);
    parallelAxis2D_f[2] = __3d2dGoEquation2(ScreenEye, parallelAxis3D[2], nullptr);
    parallelAxis2D_f[3] = __3d2dGoEquation2(ScreenEye, parallelAxis3D[3], nullptr);


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

void EquationTwo::freshTheAxis(){

//    freshGoX();freshGoY();freshGoDEEP(); // draw的时候 已经..

    freshTiltAxis(); // 刷新 倾斜轴
    freshParallelAxis(); // 刷新 平行轴
}
void EquationTwo::drawTheAxis(ScreenDemo *ScreenEye) {
    // 没刷新 就不画了
    if(debugLine != 2)return;

    drawTiltAxis(ScreenEye); // 画倾斜轴
    drawParallelAxis(ScreenEye); // 画平行轴
}

void EquationTwo::switchDebug(){
    if(debugLine==0){
        debugLine = 1;
        println("复平面² debugLine 1");
    }
    else if(debugLine==1){
        debugLine = 2;
        println("复平面² debugLine 2");
        // __debugbreak(); // 强制中断
    }
    else{
        debugLine = 0;
        println("复平面² debugLine 0");
    }
}
void EquationTwo::freshComplexRect(ScreenDemo* ScreenEye){
    glm::vec3 downFlatLT_selfAxis = {-halfBoxLength.x, 0, halfBoxLength.z};
    glm::vec3 downFlatRT_selfAxis = {halfBoxLength.x, 0, halfBoxLength.z};
    glm::vec3 downFlatRB_selfAxis = {halfBoxLength.x, 0, -halfBoxLength.z};
    glm::vec3 downFlatLB_selfAxis = {-halfBoxLength.x, 0, -halfBoxLength.z};

    glm::vec3 downFlatLT_screenAxis = self2screenAxis(downFlatLT_selfAxis);
    glm::vec3 downFlatRT_screenAxis = self2screenAxis(downFlatRT_selfAxis);
    glm::vec3 downFlatRB_screenAxis = self2screenAxis(downFlatRB_selfAxis);
    glm::vec3 downFlatLB_screenAxis = self2screenAxis(downFlatLB_selfAxis);

    this->downFlatLT_2D = __3d2dEquation2(ScreenEye,downFlatLT_screenAxis.x,
                    downFlatLT_screenAxis.y,downFlatLT_screenAxis.z);
    this->downFlatRT_2D = __3d2dEquation2(ScreenEye,downFlatRT_screenAxis.x,
                    downFlatRT_screenAxis.y,downFlatRT_screenAxis.z);
    this->downFlatRB_2D = __3d2dEquation2(ScreenEye,downFlatRB_screenAxis.x,
                    downFlatRB_screenAxis.y,downFlatRB_screenAxis.z);
    this->downFlatLB_2D = __3d2dEquation2(ScreenEye,downFlatLB_screenAxis.x,
                    downFlatLB_screenAxis.y,downFlatLB_screenAxis.z);

}
void EquationTwo::drawComplexRect(ScreenDemo* ScreenEye){
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