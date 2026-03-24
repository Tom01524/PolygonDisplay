//
// Created by iceoc0 on 2025/4/11.
//
#include "SphereDemo.h"


extern void* settled_ptr; // 全局设置的结构体指针
struct _settledSphere{
    int _width;
    int _height;
    int _deep;

};
_settledSphere* settled_ = static_cast<_settledSphere *>(settled_ptr);
const int screenWidth6 = settled_-> _width;
const int screenHeight6 = settled_-> _height;
const int screenDeep6 = settled_-> _deep;


struct modeSphere{
    char now;char a;char b;char d;
};
extern void* mode_ptr;
modeSphere mode_ = *static_cast<modeSphere *>(mode_ptr);


extern void* _3d_2d_go_void_ptr; // 3d_2d_go的函数指针
// struct _3d_2d_go_sphere{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, float *, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_2d)(ScreenDemo*, float, float, float);
//
// };
glm::vec2 (*__3d2dGoSphere)(ScreenDemo*, glm::vec3, glm::vec3*) =
    static_cast<_3d_2d_go_func *>(_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2dSphere)(ScreenDemo*, float, float, float) =
    static_cast<_3d_2d_go_func *>(_3d_2d_go_void_ptr)->_3d_2d; // 模式1 用自己的不行


SphereDemo::SphereDemo(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
        glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf, unsigned char _debug_):PolygonBase(6){
//    PolygonBase::type_ = 6; // 球体类型
    imgMode = false;
    __init__(_ltn,_rtn,_rbn,_lbn,_ltf,_rtf,_rbf,_lbf,_debug_);

//    printf("球体对象首地址%p\n",this);
}
SphereDemo::SphereDemo(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
                       glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf, string _path,
                       unsigned char _debug_):PolygonBase(6){

    PolygonBase::loadImgRGB01(_path,pixelsColor);
    println("SphereDemo::SphereDemo() imgW= {} imgH={} vec size={}",
        pixelsColor.outterMax, pixelsColor.innerMax, pixelsColor.data.size());

    imgW_f = static_cast<float>(pixelsColor.innerMax);
    imgH_f = static_cast<float>(pixelsColor.outterMax);

    imgMode = true;
    __init__(_ltn,_rtn,_rbn,_lbn,_ltf,_rtf,_rbf,_lbf,_debug_);
}
void SphereDemo::__init__(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
                          glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf, unsigned char _debug_){
    boxLenX = glm::distance(_ltn, _rtn); // 右距
    boxLenY = glm::distance(_ltn, _lbn); // 下距
    boxLenZ = glm::distance(_ltn, _ltf); // 前距
//    cout << "boxLenX:" << boxLenX << endl;
//    cout << "boxLenY:" << boxLenY << endl;
//    cout << "boxLenZ:" << boxLenZ << endl;

    radiusA = boxLenX/2.f-1.f;
    radiusB = boxLenY/2.f-1.f;
    radiusC = boxLenZ/2.f-1.f;
    // 先 radius a b c
    setBox3D(_ltn, _rtn, _rbn, _lbn, _ltf, _rtf, _rbf, _lbf);
    tblrXYZnf_unchange.ltnSet = tblrXYZnf.ltnSet;
    tblrXYZnf_unchange.rtnSet = tblrXYZnf.rtnSet;
    tblrXYZnf_unchange.rbnSet = tblrXYZnf.rbnSet;
    tblrXYZnf_unchange.lbnSet = tblrXYZnf.lbnSet;

    tblrXYZnf_unchange.ltfSet = tblrXYZnf.ltfSet;
    tblrXYZnf_unchange.rtfSet = tblrXYZnf.rtfSet;
    tblrXYZnf_unchange.rbfSet = tblrXYZnf.rbfSet;
    tblrXYZnf_unchange.lbfSet = tblrXYZnf.lbfSet;

    tblrXYZnf_unchange.center = tblrXYZnf.center;
DEBUG_SECTION(
    tblrXYZnf_unchange.rtn_ltn_tip = tblrXYZnf.rtn_ltn_tip;
    tblrXYZnf_unchange.lbn_ltn_tip = tblrXYZnf.lbn_ltn_tip;
    tblrXYZnf_unchange.ltf_ltn_tip = tblrXYZnf.ltf_ltn_tip;

    tblrXYZnf_unchange.lbf_rbf_tip = tblrXYZnf.lbf_rbf_tip;
    tblrXYZnf_unchange.rtf_rbf_tip = tblrXYZnf.rtf_rbf_tip;
    tblrXYZnf_unchange.rbn_rbf_tip = tblrXYZnf.rbn_rbf_tip;
)

    debugLine = _debug_;

//    latitude0 = -radiusB;
//    latitude30 = -radiusB * glm::cos(glm::radians(30.0f));
//    latitude60 = -radiusB * glm::cos(glm::radians(60.0f));
//    latitude90 = 0.f;
//    latitude120 = -latitude60;
//    latitude150 = -latitude30;
//    latitude180 = radiusB;
}
void SphereDemo::Draw_Tick(ScreenDemo* ScreenEye){
    //println("dwar tick");
    displayNecessary = true;

//    bool all2Dleft = tblrXYnf.ltnSet.x < 0.f && tblrXYnf.rtnSet.x < 0.f &&
//                     tblrXYnf.rbnSet.x < 0.f && tblrXYnf.lbnSet.x < 0.f &&
//                     tblrXYnf.ltfSet.x < 0.f && tblrXYnf.rtfSet.x < 0.f &&
//                     tblrXYnf.rbfSet.x < 0.f && tblrXYnf.lbfSet.x < 0.f;
//    bool all2Dright = tblrXYnf.ltnSet.x > (float)screenWidth6 && tblrXYnf.rtnSet.x > (float)screenWidth6 &&
//                      tblrXYnf.rbnSet.x > (float)screenWidth6 && tblrXYnf.lbnSet.x > (float)screenWidth6 &&
//                      tblrXYnf.ltfSet.x > (float)screenWidth6 && tblrXYnf.rtfSet.x > (float)screenWidth6 &&
//                      tblrXYnf.rbfSet.x > (float)screenWidth6 && tblrXYnf.lbfSet.x > (float)screenWidth6;
//    bool all2Dtop = tblrXYnf.ltnSet.y < 0.f && tblrXYnf.rtnSet.y < 0.f &&
//                    tblrXYnf.rbnSet.y < 0.f && tblrXYnf.lbnSet.y < 0.f &&
//                    tblrXYnf.ltfSet.y < 0.f && tblrXYnf.rtfSet.y < 0.f &&
//                    tblrXYnf.rbfSet.y < 0.f && tblrXYnf.lbfSet.y < 0.f;
//    bool all2Dbottom = tblrXYnf.ltnSet.y > (float)screenHeight6 && tblrXYnf.rtnSet.y > (float)screenHeight6 &&
//                       tblrXYnf.rbnSet.y > (float)screenHeight6 && tblrXYnf.lbnSet.y > (float)screenHeight6 &&
//                       tblrXYnf.ltfSet.y > (float)screenHeight6 && tblrXYnf.rtfSet.y > (float)screenHeight6 &&
//                       tblrXYnf.rbfSet.y > (float)screenHeight6 && tblrXYnf.lbfSet.y > (float)screenHeight6;
//    bool corner2DoutOfScreen = all2Dleft || all2Dright || all2Dtop || all2Dbottom;
//
//    if(corner2DoutOfScreen){
//        cout << "包围盒 2D 屏幕外" << endl;
//        displayNecessary = false;
//    }

    // 初始最远最近
    deepFarNearBackCenter(); // 刷新深度 最远 最近


    freshVirtualGoX(); // 屏幕系 数轴三向
    freshVirtualGoY();
    freshVirtualGoDEEP();

    if(ScreenAxis2Self_SameFlat){
        freshVirtualFlatXY(); // 屏幕系 数轴三面
        freshVirtualFlatYZ();
        freshVirtualFlatXZ();
    }else{
        freshFrameRotateInfo(); // 转自己系 四元数
    }

//    if(virtual_scanBox3D.center.z + (float)screenDeep6 < 0.f){
//        cout << "球心 在 眼后" << endl;
//        displayNecessary = false;
//        // 都在屏幕外 则不绘制
//    }


    if(displayNecessary) {

        // left面 法线
        flatLeftFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
            -world_toX._,tblrXYZnf.ltnSet);
        // top面 法线
        flatTopFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
            -world_toY._,tblrXYZnf.ltnSet);
        // front面 法线
        flatFrontFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
            -world_toDEEP._,tblrXYZnf.ltnSet);
        // right面 法线
        flatRightFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
            world_toX._,tblrXYZnf.rbfSet);
        // bottom面 法线
        flatBottomFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
            world_toY._,tblrXYZnf.rbfSet);
        // back面 法线
        flatBackFacing = PolygonBase::isFrontFacing(ScreenEye->tblrXYZ.centerTip,
            world_toDEEP._,tblrXYZnf.rbfSet);

        //flatLeftFacing = rtn_ltn_tip_closer; // 哪个面对着我 ?
        //flatTopFacing = lbn_ltn_tip_closer;
        //flatRightFacing = lbf_rbf_tip_closer;
        //flatBottomFacing = rtf_rbf_tip_closer;
        //flatFrontFacing = ltf_ltn_tip_closer;
        //flatBackFacing = rbn_rbf_tip_closer;


//    cout << "virtual_scanBox3D.center.z: " << virtual_scanBox3D.center.z << endl;
//    cout << "ltnSet_ScreenDeep: " << ltnSet_ScreenDeep << endl;



        if (flatFrontFacing) { // ltn rtn rbn lbn
            _solidRectangle2D_(ScreenEye, tblrXYnf.ltnSet,
                                    tblrXYnf.rtnSet,
                                    tblrXYnf.rbnSet,
                                    tblrXYnf.lbnSet,
                                    lineScanFillColor_front,pixelEyeDeep_front); // 反面 需要经纬度
            //println("front solid");
        }
        if (flatBackFacing) { // rtf ltf lbf rbf
            _solidRectangle2D_(ScreenEye, tblrXYnf.rtfSet,
                                    tblrXYnf.ltfSet,
                                    tblrXYnf.lbfSet,
                                    tblrXYnf.rbfSet,
                                    lineScanFillColor_back,pixelEyeDeep_back); // 反面 需要经纬度
            //println("back solid");
        }
        if (flatLeftFacing) { // ltf ltn lbn lbf
            _solidRectangle2D_(ScreenEye, tblrXYnf.ltfSet,
                                    tblrXYnf.ltnSet,
                                    tblrXYnf.lbnSet,
                                    tblrXYnf.lbfSet,
                                    lineScanFillColor_left,pixelEyeDeep_left); // 反面 需要经纬度
            //println("left solid");
        }
        if (flatRightFacing) { // rtn rtf rbf rbn
            _solidRectangle2D_(ScreenEye, tblrXYnf.rtnSet,
                                    tblrXYnf.rtfSet,
                                    tblrXYnf.rbfSet,
                                    tblrXYnf.rbnSet,
                                    lineScanFillColor_right,pixelEyeDeep_right); // 反面 需要经纬度
            //println("right solid");
        }
        if (flatTopFacing) {
            _solidRectangle2D_(ScreenEye, tblrXYnf.ltfSet,
                                    tblrXYnf.rtfSet,
                                    tblrXYnf.rtnSet,
                                    tblrXYnf.ltnSet,
                                    lineScanFillColor_top,pixelEyeDeep_top); // 反面 需要经纬度
            //println("top solid");
        }
        if (flatBottomFacing) {
            _solidRectangle2D_(ScreenEye, tblrXYnf.lbnSet,
                                    tblrXYnf.rbnSet,
                                    tblrXYnf.rbfSet,
                                    tblrXYnf.lbfSet,
                                    lineScanFillColor_bottom,pixelEyeDeep_bottom); // 反面 需要经纬度
            //println("bottom solid");
        }


        float _color_[3];
        if (debugLine == 1) {
            //println("showBox");
            _color_[0] = 1.0f;
            _color_[1] = 1.0f;
            _color_[2] = 1.0f; // 白色
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.ltnSet.x, tblrXYnf.ltnSet.y,
                                          tblrXYnf.rtnSet.x, tblrXYnf.rtnSet.y,
                                          _color_, frameScreenNear);// 前框
            // println("ltn:{},rtn:{}",
            //     showVec2(tblrXYnf.ltnSet),showVec2(tblrXYnf.rtnSet));
            // println("frameScreenNear:{}",frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.rtnSet.x, tblrXYnf.rtnSet.y,
                                          tblrXYnf.rbnSet.x, tblrXYnf.rbnSet.y,
                                          _color_, frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.rbnSet.x, tblrXYnf.rbnSet.y,
                                          tblrXYnf.lbnSet.x, tblrXYnf.lbnSet.y,
                                          _color_, frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.lbnSet.x, tblrXYnf.lbnSet.y,
                                          tblrXYnf.ltnSet.x, tblrXYnf.ltnSet.y,
                                          _color_, frameScreenNear);

            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.ltfSet.x, tblrXYnf.ltfSet.y,
                                          tblrXYnf.rtfSet.x, tblrXYnf.rtfSet.y,
                                          _color_, frameScreenNear);// 后框
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.rtfSet.x, tblrXYnf.rtfSet.y,
                                          tblrXYnf.rbfSet.x, tblrXYnf.rbfSet.y,
                                          _color_, frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.rbfSet.x, tblrXYnf.rbfSet.y,
                                          tblrXYnf.lbfSet.x, tblrXYnf.lbfSet.y,
                                          _color_, frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.lbfSet.x, tblrXYnf.lbfSet.y,
                                          tblrXYnf.ltfSet.x, tblrXYnf.ltfSet.y,
                                          _color_, frameScreenNear);

            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.ltnSet.x, tblrXYnf.ltnSet.y,
                                          tblrXYnf.ltfSet.x, tblrXYnf.ltfSet.y,
                                          _color_, frameScreenNear);// 前后连
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.rtnSet.x, tblrXYnf.rtnSet.y,
                                          tblrXYnf.rtfSet.x, tblrXYnf.rtfSet.y,
                                          _color_, frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.rbnSet.x, tblrXYnf.rbnSet.y,
                                          tblrXYnf.rbfSet.x, tblrXYnf.rbfSet.y,
                                          _color_, frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXYnf.lbnSet.x, tblrXYnf.lbnSet.y,
                                          tblrXYnf.lbfSet.x, tblrXYnf.lbfSet.y,
                                          _color_, frameScreenNear);

DEBUG_SECTION(
            if (flatLeftFacing) {
                _color_[0] = 0.0f;
                _color_[1] = 1.0f;
                _color_[2] = 0.0f; // 绿色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.rtn_ltn_tip.x, tblrXYnf.rtn_ltn_tip.y,
                                              tblrXYnf.ltnSet.x, tblrXYnf.ltnSet.y,
                                              _color_, frameScreenNear);


            } else {
                _color_[0] = 1.0f;
                _color_[1] = 0.0f;
                _color_[2] = 0.0f; // 红色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.rtn_ltn_tip.x, tblrXYnf.rtn_ltn_tip.y,
                                              tblrXYnf.ltnSet.x, tblrXYnf.ltnSet.y,
                                              _color_, frameScreenNear);

            }
            if (flatTopFacing) {
                _color_[0] = 0.0f;
                _color_[1] = 1.0f;
                _color_[2] = 0.0f; // 绿色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.lbn_ltn_tip.x, tblrXYnf.lbn_ltn_tip.y,
                                              tblrXYnf.ltnSet.x, tblrXYnf.ltnSet.y,
                                              _color_, frameScreenNear);

            } else {
                _color_[0] = 1.0f;
                _color_[1] = 0.0f;
                _color_[2] = 0.0f; // 红色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.lbn_ltn_tip.x, tblrXYnf.lbn_ltn_tip.y,
                                              tblrXYnf.ltnSet.x, tblrXYnf.ltnSet.y,
                                              _color_, frameScreenNear);

            }
            if (flatFrontFacing) {
                _color_[0] = 0.0f;
                _color_[1] = 1.0f;
                _color_[2] = 0.0f; // 绿色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.ltf_ltn_tip.x, tblrXYnf.ltf_ltn_tip.y,
                                              tblrXYnf.ltnSet.x, tblrXYnf.ltnSet.y,
                                              _color_, frameScreenNear);
            } else {
                _color_[0] = 1.0f;
                _color_[1] = 0.0f;
                _color_[2] = 0.0f; // 红色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.ltf_ltn_tip.x, tblrXYnf.ltf_ltn_tip.y,
                                              tblrXYnf.ltnSet.x, tblrXYnf.ltnSet.y,
                                              _color_, frameScreenNear);

            }
            if (flatRightFacing) {
                _color_[0] = 0.0f;
                _color_[1] = 1.0f;
                _color_[2] = 0.0f; // 绿色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.lbf_rbf_tip.x, tblrXYnf.lbf_rbf_tip.y,
                                              tblrXYnf.rbfSet.x, tblrXYnf.rbfSet.y,
                                              _color_, frameScreenNear);
            } else {
                _color_[0] = 1.0f;
                _color_[1] = 0.0f;
                _color_[2] = 0.0f; // 红色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.lbf_rbf_tip.x, tblrXYnf.lbf_rbf_tip.y,
                                              tblrXYnf.rbfSet.x, tblrXYnf.rbfSet.y,
                                              _color_, frameScreenNear);

            }
            if (flatBottomFacing) {
                _color_[0] = 0.0f;
                _color_[1] = 1.0f;
                _color_[2] = 0.0f; // 绿色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.rtf_rbf_tip.x, tblrXYnf.rtf_rbf_tip.y,
                                              tblrXYnf.rbfSet.x, tblrXYnf.rbfSet.y,
                                              _color_, frameScreenNear);
            } else {
                _color_[0] = 1.0f;
                _color_[1] = 0.0f;
                _color_[2] = 0.0f; // 红色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.rtf_rbf_tip.x, tblrXYnf.rtf_rbf_tip.y,
                                              tblrXYnf.rbfSet.x, tblrXYnf.rbfSet.y,
                                              _color_, frameScreenNear);

            }

            if (flatBackFacing) {
                _color_[0] = 0.0f;
                _color_[1] = 1.0f;
                _color_[2] = 0.0f; // 绿色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.rbn_rbf_tip.x, tblrXYnf.rbn_rbf_tip.y,
                                              tblrXYnf.rbfSet.x, tblrXYnf.rbfSet.y,
                                              _color_, frameScreenNear);
            } else {
                _color_[0] = 1.0f;
                _color_[1] = 0.0f;
                _color_[2] = 0.0f; // 红色
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              tblrXYnf.rbn_rbf_tip.x, tblrXYnf.rbn_rbf_tip.y,
                                              tblrXYnf.rbfSet.x, tblrXYnf.rbfSet.y,
                                              _color_, frameScreenNear);
            }
)
        }
        if(debugLine==2) {
            freshCircleAxis(); // 更新坐标轴 info
            //drawSphereAxis(ScreenEye); // 画坐标轴
        }
    }

//    cout << "sphere draw tick ~" << endl;

}


void SphereDemo::setBox3D(glm::vec3& _ltn, glm::vec3& _rtn, glm::vec3& _rbn, glm::vec3& _lbn,
                  glm::vec3& _ltf, glm::vec3& _rtf, glm::vec3& _rbf, glm::vec3& _lbf){
    tblrXYZnf.ltnSet = _ltn;
    tblrXYZnf.rtnSet = _rtn;
    tblrXYZnf.rbnSet = _rbn;
    tblrXYZnf.lbnSet = _lbn;

    tblrXYZnf.ltfSet = _ltf;
    tblrXYZnf.rtfSet = _rtf;
    tblrXYZnf.rbfSet = _rbf;
    tblrXYZnf.lbfSet = _lbf;

    freshGoX();freshGoY();freshGoDEEP();

    // println("椭球 world box ltn{}",showVec3(_ltn));
    // println("world to x:{}",showVec3(world_toX._));
    // println("world to y:{}",showVec3(world_toY._));
    // println("world to z:{}",showVec3(world_toDEEP._));
    // println("radius a:{},b:{},c:{}",radiusA,radiusB,radiusC);
    glm::vec3 centerThen = goX(_ltn,radiusA);
    centerThen = goY(centerThen,radiusB);
    centerThen = goDEEP(centerThen,radiusC);
    tblrXYZnf.center = centerThen;

    // println("椭球 world box center{}",showVec3(tblrXYZnf.center));

//    cout << "### boxLenX:" << boxLenX << endl;
//    cout << "### boxLenY:" << boxLenY << endl;
//    cout << "### boxLenZ:" << boxLenZ << endl;

DEBUG_SECTION(
    tblrXYZnf.rtn_ltn_tip = goX(tblrXYZnf.ltnSet,-rounfBoxTipLen);

    tblrXYZnf.lbn_ltn_tip = goY(tblrXYZnf.ltnSet,-rounfBoxTipLen);

    tblrXYZnf.ltf_ltn_tip = goDEEP(tblrXYZnf.ltnSet,-rounfBoxTipLen);

    tblrXYZnf.lbf_rbf_tip = goX(tblrXYZnf.rbfSet,rounfBoxTipLen);

    tblrXYZnf.rtf_rbf_tip = goY(tblrXYZnf.rbfSet,rounfBoxTipLen);

    tblrXYZnf.rbn_rbf_tip = goDEEP(tblrXYZnf.rbfSet,rounfBoxTipLen);
)
    //println("椭球 set 3D");
}

void SphereDemo::setBox2D(glm::vec2& _ltn, glm::vec2& _rtn, glm::vec2& _rbn, glm::vec2& _lbn,
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
    tblrXYnf.ltnSet = _ltn;
    tblrXYnf.rtnSet = _rtn;
    tblrXYnf.rbnSet = _rbn;
    tblrXYnf.lbnSet = _lbn;

    tblrXYnf.ltfSet = _ltf;
    tblrXYnf.rtfSet = _rtf;
    tblrXYnf.rbfSet = _rbf;
    tblrXYnf.lbfSet = _lbf;

    tblrXYnf.center = _center;
DEBUG_SECTION(
    tblrXYnf.rtn_ltn_tip = _rtn_ltn_tip;
    tblrXYnf.lbn_ltn_tip = _lbn_ltn_tip;
    tblrXYnf.ltf_ltn_tip = _ltf_ltn_tip;

    tblrXYnf.lbf_rbf_tip = _lbf_rbf_tip;
    tblrXYnf.rtf_rbf_tip = _rtf_rbf_tip;
    tblrXYnf.rbn_rbf_tip = _rbn_rbf_tip;
)
    // println("椭球 set 2D");
    // println("ltn:{}",showVec2(tblrXYnf.ltnSet));
    // println("rtn:{}",showVec2(tblrXYnf.rtnSet));
}

// bool SphereDemo::cTipEyeCloser(glm::vec3 eyeCenter, glm::vec3 tip, glm::vec3 back){
//     float tipDis_square = (tip.x - eyeCenter.x)*(tip.x - eyeCenter.x) +
//             (tip.y - eyeCenter.y)*(tip.y - eyeCenter.y) +
//             (tip.z - eyeCenter.z)*(tip.z - eyeCenter.z);
//     float backDis_square = (back.x - eyeCenter.x)*(back.x - eyeCenter.x) +
//             (back.y - eyeCenter.y)*(back.y - eyeCenter.y) +
//             (back.z - eyeCenter.z)*(back.z - eyeCenter.z);
//     return tipDis_square < backDis_square;
// }
bool SphereDemo::PolyScanClicked(int x,int y) {
    bool result = false;

    result = scanClickedBox(x,y);

    if(result)
    println("球被点击了！");

    return result;

}
bool SphereDemo::scanClickedBox(int x,int y){
    if (flatFrontFacing) {
        for (auto &_rowInfo: pixelEyeDeep_front) {
            if (y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (x == _pixelInfo.x) {
                        goto clickedOn; // 点在圆内 x也对
                    }
                }
                goto afterN; // 找到y 扫完x 没有 退
            }

        }
    }afterN:
    if(flatBackFacing){
        for (auto &_rowInfo: pixelEyeDeep_back) {
            if (y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (x == _pixelInfo.x) {
                        goto clickedOn; // 点在圆内 x也对
                    }
                }
                goto afterF; // 找到y 扫完x 没有 退
            }
        }
    }afterF:
    if (flatLeftFacing) {
        for (auto &_rowInfo: pixelEyeDeep_left) {
            if (y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (x == _pixelInfo.x) {
                        goto clickedOn; // 点在圆内 x也对
                    }
                }
                goto afterL; // 找到y 扫完x 没有 退
            }

        }
    }afterL:
    if(flatRightFacing){
        for (auto &_rowInfo: pixelEyeDeep_right) {
            if (y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (x == _pixelInfo.x) {
                        goto clickedOn; // 点在圆内 x也对
                    }
                }
                goto afterR; // 找到y 扫完x 没有 退
            }
        }
    }afterR:
    if(flatTopFacing){
        for (auto &_rowInfo: pixelEyeDeep_top) {
            if (y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (x == _pixelInfo.x) {
                        goto clickedOn; // 点在圆内 x也对
                    }
                }
                goto afterT; // 找到y 扫完x 没有 退
            }
        }
    }afterT:
    if(flatBottomFacing){
        for (auto &_rowInfo: pixelEyeDeep_bottom) {
            if (y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (x == _pixelInfo.x) {
                        goto clickedOn; // 点在圆内 x也对
                    }
                }
                goto afterB; // 找到y 扫完x 没有 退
            }
        }
    }afterB:

    // 都不在 xy
    return false;

    clickedOn:

    return true;
}
#ifdef MAYBE_UNUSED
bool SphereDemo::scanClickedCircle(int x, int y){

    for(auto &_rowInfo: lineScanFillColor_circle) {
                if (y == _rowInfo.y && _rowInfo.lx < x && _rowInfo.rx > x) {
                    return true; // 点在圆内 x也对
            }
        }


    return false;
}
#endif
void SphereDemo::setFrontColor(int _color1, int _color2) {
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

void SphereDemo::setBackColor(int _color) {
    BGR3f colorNow;
    colorNow.setBGR(_color,1);
    backColor_rgb01[0] = colorNow.r1;
    backColor_rgb01[1] = colorNow.g1;
    backColor_rgb01[2] = colorNow.b1;

}

glm::vec3 SphereDemo::getCenter() {
    return tblrXYZnf.center;
}
glm::vec3 SphereDemo::getVirtualCenter(){
    return virtual_tblrXYZnf.center;
}
void SphereDemo::_solidRectangle2D_(ScreenDemo* ScreenEye,glm::vec2& p1,glm::vec2& p2,glm::vec2& p3,glm::vec2& p4,
        vector<lineBoundary>& lineScanFillColor,vector<rowPixelDeep6>& pixelEyeDeep) {

    // 默认 0 ltn 1 rtn 2 rbn 3 lbn
    PolygonBase::fresh2D_scanRows_4(p1,p2,p3,p4, &lineScanFillColor,type_);
    pixelEyeDeep.clear();


    //println("rows count by box front side:{}",lineScanFillColor_front.size());
    for(auto& _linePosInfo : lineScanFillColor){

        if(_linePosInfo.rx == _linePosInfo.lx){
//            cerr << "球 lineScanFillColor.rx:" << _linePosInfo.rx <<
//                 " = lineScanFillColor.lx:" << _linePosInfo.lx << endl;
            continue;
        }

        rowPixelDeep6 rowDeepInfo;
        rowDeepInfo.y = (float)_linePosInfo.y; // 本行 y
//        rowDeepInfo.pixelDeeps.clear(); // 本行 x deep 空
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){
//            cout << "^^^nowX:" << nowX << " y:" << _linePosInfo.y << endl;
            //float deepFrontNow = getEyeDeepbyXY(nowX, _linePosInfo.y);

            glm::vec3 selfAxisSurfaceNear;
            pair<glm::vec3, glm::vec3> virtual_SurfacePoint;
            if(ScreenAxis2Self_SameFlat){
                throw std::exception("不应可达");
                virtual_SurfacePoint = getVirtualSurfacePointbyXY(ScreenEye,nowX, _linePosInfo.y); // 2D→3D 得到虚拟表面点

                if (std::isnan(virtual_SurfacePoint.first.x) ||
                    std::isnan(virtual_SurfacePoint.second.x) ) {
                    // 无交点
                    rowDeepInfo.pixelDeeps.push_back({nowX, std::nanf(""),std::nanf(""),-1, false}); // 圆外 2D→3D 不计深度 nan
                    continue;
                }
                selfAxisSurfaceNear = screenXYZ2SelfXYZ(virtual_SurfacePoint.first); // 屏幕系 → 自己系
            }else{
                Ray ray_SelfAxis = getRay_SelfAxis( nowX, _linePosInfo.y);
                std::expected<pair<float,float>,char>
                step = getSurfacePointStepbyXY(ray_SelfAxis, nowX, _linePosInfo.y);
                if(!step) {
                    //println("bad result");
                    continue;
                }
                //println("good result");
                Ray ray_ScreenAxis = getRay_ScreenAxis(nowX, _linePosInfo.y);

                selfAxisSurfaceNear = getSurfacePointbyStep_SelfAxis(ray_SelfAxis, step->first);
                virtual_SurfacePoint.first = ray_ScreenAxis.src + ray_ScreenAxis.dir * step->first;
                virtual_SurfacePoint.second = ray_ScreenAxis.src + ray_ScreenAxis.dir * step->second;
            }
            pair<float,float> deepNow = make_pair(virtual_SurfacePoint.first.z, virtual_SurfacePoint.second.z);

            //            float latitudeAngleNow = getLatitudeOnSelfAxis(selfAxisSurfaceNear); // 自己系 → 得到纬度角
            // 准确的 维度
            float latitudeAngleNow = getLatitudeOnSelfAxis(selfAxisSurfaceNear);

            float longitudeAngleNow = getLongitudeOnSelfAxis(selfAxisSurfaceNear); // 自己系 → 得到经度角
            char area ;float colorNow[3];
//            bool _rowA = (latitudeAngleNow > 0 && latitudeAngleNow <= 30.f) || (latitudeAngleNow > 60.f && latitudeAngleNow <= 90.f) ||
//                         (latitudeAngleNow > 120.f && latitudeAngleNow <= 150.f);
            bool imgArea = !(latitudeAngleNow>0.f&&latitudeAngleNow<30.f) && !(latitudeAngleNow>150.f&&latitudeAngleNow<180.f) &&
                           longitudeAngleNow > -90.f && longitudeAngleNow < 90.f;

            if(!imgArea || !imgMode){
                bool _rowA =  (latitudeAngleNow>0.f&&latitudeAngleNow<30.f) ||
                        (latitudeAngleNow>60.f&&latitudeAngleNow<90.f) ||
                        (latitudeAngleNow>120.f&&latitudeAngleNow<150.f);
                bool _colA = (longitudeAngleNow > -180.f && longitudeAngleNow <= -120.f) ||
                             (longitudeAngleNow > -60.f && longitudeAngleNow <= 0.f) || (longitudeAngleNow > 60.f && longitudeAngleNow <= 120.f);
                bool inOdd = (_rowA && !_colA) || (!_rowA && _colA);
                if(inOdd){
                    area = 0;
                    colorNow[0] = frontColor1_rgb01[0];
                    colorNow[1] = frontColor1_rgb01[1];
                    colorNow[2] = frontColor1_rgb01[2];
                }else{
                    area = 1;
                    colorNow[0] = frontColor2_rgb01[0];
                    colorNow[1] = frontColor2_rgb01[1];
                    colorNow[2] = frontColor2_rgb01[2];
                }
            }else{
                area = 2;

                // 经纬 获取 uv
                glm::vec2 uv = getUV_by_Latitude_Longitude(longitudeAngleNow,latitudeAngleNow);
                glm::vec3 colorNow1 = getImgColor_by_UV(uv);
                colorNow[0] = colorNow1[0];
                colorNow[1] = colorNow1[1];
                colorNow[2] = colorNow1[2];
            }

                    //getScreenDeepbyXY(ScreenEye, nowX, _linePosInfo.y); // 2D→3D 得到屏幕深度

//            if(isnan(deepNow.first) || isnan(deepNow.second)){
//                rowDeepInfo.pixelDeeps.push_back({nowX, std::nanf(""),std::nanf(""), false}); // 圆外 2D→3D 不计深度 nan
//                continue;
//            }

            if(deepNow.first < frameScreenNear){ // 有更近
//                cerr << "deepNow.first:" << deepNow.first << " < frameScreenNear:" << frameScreenNear << endl;
                frameScreenNear = deepNow.first;
            }else if(deepNow.first > frameScreenFar) { // 有更远
                frameScreenFar = deepNow.first;
            }

            struct pixelDeep6 pixelDeepInfoNow = {nowX,
                    deepNow.first,
                    deepNow.second,
                    area,
                    colorNow[0],colorNow[1],colorNow[2]
};
            rowDeepInfo.pixelDeeps.push_back(pixelDeepInfoNow); // 本行 x deep

        }
        pixelEyeDeep.push_back(rowDeepInfo);

    }
//println("row got:{}",pixelEyeDeep_front.size());



    for(auto& _lineDeepInfo : pixelEyeDeep) {
        size_t vecSizeCurrent=_lineDeepInfo.pixelDeeps.size();
        //println("col got:{}",vecSizeCurrent);
        for (int i = 0; i < vecSizeCurrent/*-1*/; i++) {
            int nowX = _lineDeepInfo.pixelDeeps[i].x;
            float nowDeep = _lineDeepInfo.pixelDeeps[i].screenDeep_front;

            if (1) {
                //println("^^on front");
                float _color_[3];
                if (debugLine == 1) {
                    //println("^^debug 1");

                    //println("in circle");
                    int colorNow = white2ColorfulScreenDeep(nowDeep,
                                   _lineDeepInfo.pixelDeeps[i].rgb);

                    BGR3f colorNow1;
                    colorNow1.setBGR(colorNow,1);
                    _color_[0] = colorNow1.r1;
                    _color_[1] = colorNow1.g1;
                    _color_[2] = colorNow1.b1;
                    ScreenEye->putPixel(nowX,static_cast<int>(_lineDeepInfo.y),_color_,nowDeep,(PolygonBase*)this);
                    //std::cout << "front color r:" << colorNow1.r1 << " g:" << colorNow1.g1 << " b:" << colorNow1.b1 << "\n";


                }
                else{


                    _color_[0] = _lineDeepInfo.pixelDeeps[i].rgb[0];
                    _color_[1] = _lineDeepInfo.pixelDeeps[i].rgb[1];
                    _color_[2] = _lineDeepInfo.pixelDeeps[i].rgb[2];

                    ScreenEye->putPixel(nowX,static_cast<int>(_lineDeepInfo.y),_color_,nowDeep,(PolygonBase*)this);


                }
            } else {

                float _color_[3];

                if(_lineDeepInfo.pixelDeeps[i].area == 0){
                    _color_[0] = frontColor1_rgb01[0];
                    _color_[1] = frontColor1_rgb01[1];
                    _color_[2] = frontColor1_rgb01[2];

                }else{
                    _color_[0] = frontColor2_rgb01[0];
                    _color_[1] = frontColor2_rgb01[1];
                    _color_[2] = frontColor2_rgb01[2];

                }
                ScreenEye->putPixel(nowX,static_cast<int>(_lineDeepInfo.y),_color_,nowDeep,(PolygonBase*)this);



            }
        }
    }


}

void SphereDemo::freshFrameRotateInfo(){
    frameRotateInfo_q = PolygonBase::getFrameRotateInfo_(virtual_toX,virtual_toDEEP);
}
glm::vec3 SphereDemo::screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos){
    if(isnan(_screenAxisPos.x) || isnan(_screenAxisPos.y) || isnan(_screenAxisPos.z)){
        println(stderr, "NAN _screenAxisPos ({},{},{})",_screenAxisPos.x,_screenAxisPos.y,_screenAxisPos.z);
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }// 不是 nan
    glm::vec3 back000 = virtual_tblrXYZnf.center;
//    float backX = virtual_scanBox3D.center.x;
//    float backY = virtual_scanBox3D.center.y;
//    float backZ = virtual_scanBox3D.center.z;
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


    if(isnan(farScreenAxis000.x) || isnan(farScreenAxis000.y) || isnan(farScreenAxis000.z)){
        println(stderr, "NAN farScreenAxis000 ({},{},{})",farScreenAxis000.x,farScreenAxis000.y,farScreenAxis000.z);
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }
    return farScreenAxis000;
}

pair<glm::vec3,glm::vec3> SphereDemo::getVirtualSurfacePointbyXY(ScreenDemo* ScreenEye, float x, float y){
    // ---屏幕系下---
    // 眼 ex ey ez
    //glm::vec3 startEye = {(float)screenWidth6/2.0f, (float)screenHeight6/2.0f, (float)-screenDeep6};
    float ex = startEye.x; // 600
    float ey = startEye.y; // 800
    float ez = startEye.z; // -1000
    // 眼屏进 dx dy dz
    goLine32 eyeGoPixel = eye2ScreenPixel_dxyz(x, y); // 计算 屏幕中心到像素点 的向量
    float _dx = eyeGoPixel.dx;
    float _dy = eyeGoPixel.dy;
    float _dz = eyeGoPixel.dz;
    // 球心 cx cy cz
    float cx = virtual_tblrXYZnf.center.x;
    float cy = virtual_tblrXYZnf.center.y;
    float cz = virtual_tblrXYZnf.center.z;
    // 求 step
    // ax² + bx + c = 0
    float radius = std::min(std::min(boxLenX,boxLenY),boxLenZ) / 2.f -1.f;
    // a
    float a = _dx * _dx + _dy * _dy + _dz * _dz;
    // b
    float b = 2 * (_dx * (ex-cx) + _dy * (ey-cy) + _dz * (ez-cz));
    // c
    float c = (ex - cx)*(ex - cx) + (ey - cy)*(ey - cy) + (ez - cz)*(ez - cz) - radius * radius;
    // 跟判别式 计算交点

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        // 无交点
        return make_pair(glm::vec3{std::numeric_limits<float>::quiet_NaN()},
                                 glm::vec3{std::numeric_limits<float>::quiet_NaN()}
                                 );
    }
    float t1 = (-b + glm::sqrt(discriminant)) / (2 * a);
    float t2 = (-b - glm::sqrt(discriminant)) / (2 * a);
    // t1-t2 = glm::sqrt(delta) / a  [glm::sqrt(delta) > 0才会有解,所以看a的正负]
    // a>0  t1>t2
    // a<0  t1<t2
    float farStep, nearStep;
//    if(a>0){
        nearStep = t2;
        farStep = t1;
//    }else{
//        nearStep = t1;
//        farStep = t2;
//    }

    glm::vec3 virtual_SurfacePointNear = {
            ex + _dx * nearStep,
            ey + _dy * nearStep,
            ez + _dz * nearStep
    };
    glm::vec3 virtual_SurfacePointFar = {
                ex + _dx * farStep,
                ey + _dy * farStep,
                ez + _dz * farStep
        };


    return make_pair(virtual_SurfacePointNear, virtual_SurfacePointFar);
}
Ray SphereDemo::getRay_SelfAxis(float x, float y){
    // 眼 ex ey ez
    glm::vec3 startEye = {(float)screenWidth6/2.0f, (float)screenHeight6/2.0f, (float)-screenDeep6};
    glm::vec3 selfAxisEye = screenXYZ2SelfXYZ2(startEye); // 自己坐标系下 眼的坐标

    // 眼屏进 dx dy dz
    glm::vec3 screenPoint_SelfAxis = screenXYZ2SelfXYZ2(glm::vec3(x,y,0.f)); // 自己坐标系下 像素点的坐标
    goLine32 eyeGoPixel_SelfAxis = ScreenDemo::get_AgoB_direction3D(selfAxisEye, screenPoint_SelfAxis); // 计算 屏幕中心到像素点 的向量

    return Ray(selfAxisEye, glm::vec3{eyeGoPixel_SelfAxis.dx,
                                      eyeGoPixel_SelfAxis.dy,
                                      eyeGoPixel_SelfAxis.dz});
}
Ray SphereDemo::getRay_ScreenAxis(float x, float y){
    // 眼 ex ey ez
    glm::vec3 startEye = {(float)screenWidth6/2.0f, (float)screenHeight6/2.0f, (float)-screenDeep6};

    // 眼屏进 dx dy dz
    goLine32 eyeGoPixel = eye2ScreenPixel_dxyz(x, y); // 计算 屏幕中心到像素点 的向量

    return Ray(startEye, glm::vec3{eyeGoPixel.dx,
                                   eyeGoPixel.dy,
                                   eyeGoPixel.dz});
}
std::expected<pair<float,float>,char>
SphereDemo::getSurfacePointStepbyXY(Ray& ray, float x, float y){
    // ---屏幕系下---
    // 眼 ex ey ez
    float ex = ray.src.x;
    float ey = ray.src.y;
    float ez = ray.src.z;
    // 眼屏进 dx dy dz
    float _dx = ray.dir.x;
    float _dy = ray.dir.y;
    float _dz = ray.dir.z;
    // 球心 cx cy cz ~~球心往(左、下) 等价于 眼睛往(右、上)
//    float cx = 0.f;
//    float cy = 0.f;
//    float cz = 0.f;

    // 求 step
    // ax² + bx + c = 0
    // a
    float a = _dx * _dx/(radiusA * radiusA)
              + _dy * _dy/(radiusB * radiusB)
              + _dz * _dz/(radiusC * radiusC);
    // b
    float b = 2.0f * ( _dx * ex/(radiusA * radiusA)
                       + _dy * ey/(radiusB * radiusB)
                       + _dz * ez/(radiusC * radiusC) );
    // c
    float c = (ex*ex)/(radiusA * radiusA)
              + (ey*ey)/(radiusB * radiusB)
              + (ez*ez)/(radiusC * radiusC)
              - 1.0f;
    // 跟判别式 计算交点

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        // 无交点
        return std::unexpected(0);

    }
    float t1 = (-b + glm::sqrt(discriminant)) / (2 * a);
    float t2 = (-b - glm::sqrt(discriminant)) / (2 * a);
    // t1-t2 = glm::sqrt(delta) / a  [glm::sqrt(delta) > 0才会有解,所以看a的正负]

    float farStep, nearStep;

    nearStep = t2;
    farStep = t1;


    return make_pair(nearStep, farStep);
}
glm::vec3 SphereDemo::getSurfacePointbyStep_SelfAxis(Ray& ray, float step){
    // 眼 ex ey ez
    float ex = ray.src.x; // 600
    float ey = ray.src.y; // 800
    float ez = ray.src.z; // -

    // 眼屏进 dx dy dz
    float _dx = ray.dir.x;
    float _dy = ray.dir.y;
    float _dz = ray.dir.z;
    return glm::vec3{ex + _dx * step, ey + _dy * step, ez + _dz * step};
}

goLine32 SphereDemo::eye2ScreenPixel_dxyz(float x, float y) {

//    cout << "pixelXYZ:" << pixelXYZ.x << " " << pixelXYZ.y << " " << pixelXYZ.z << endl;
    //glm::vec3 startEYE = {(float)screenWidth6/2.0f, (float)screenHeight6/2.0f, (float)-screenDeep6}; // 初始化一次 (600,400,-1000)

    return ScreenDemo::get_AgoB_direction3D(startEye, {x, y, 0.0f}); // 计算 屏幕中心到像素点 的向量
}
int SphereDemo::white2ColorfulScreenDeep(float pointDeep, float* color3){
    float deepBetween = frameScreenFar - frameScreenNear; // 两端深度差
    float B, G, R;

    B = color3[2] * 255.f;
    G = color3[1] * 255.f;
    R = color3[0] * 255.f; // 保留后两位

    //cout << hex << "B:" << B << " G:" << G << " R:" << R << endl;
    float dB = (255.0f-B) / deepBetween; // 最深和最近的差 颜色变化
    float dG = (255.0f-G) / deepBetween;
    float dR = (255.0f-R) / deepBetween; // 白 255 - 黑 无 --------------------------------------
    //cout << hex << "dB:" << dB << " dG:" << dG << " dR:" << dR << endl;



//    if(pointDeep < screenNear){
//        //cerr << "pointDeep:" << pointDeep << " < screenNear:" << screenNear << endl; // ### ###
//        pointDeep = screenNear;
//    }else if(pointDeep > screenFar){
//        //cerr << "pointDeep:" << pointDeep << " > screenFar:" << screenFar << endl;
//        pointDeep = screenFar;
//    }
    //cout << "pointDeep:" << pointDeep << endl;
    float ofFarthest = frameScreenFar - pointDeep; // 对于 最深和当前的深度差
    //float ofNearest = pointDeep - frameScreenNear; // 对于 最深和当前的深度差
    float nowB = 255.0f - ofFarthest * dB;
    float nowG = 255.0f - ofFarthest * dG;
    float nowR = 255.0f - ofFarthest * dR; // 白 255 - 黑 无 --------------------------------------
    int color = (static_cast<int>(nowB) << 16) + (static_cast<int>(nowG) << 8) + static_cast<int>(nowR);
    color = (color & 0x00ffffff); // 最左一字节 0
    //cout << "color final:" << color << endl;
    return color;
}
void SphereDemo::deepFarNearBackCenter(){

    frameScreenFar = virtual_tblrXYZnf.center.z;
    frameScreenNear = virtual_tblrXYZnf.center.z;
    DEBUG_SECTION(
        if (virtual_tblrXYZnf.center.z < -screenDeep6)
        println(stderr,"!!! center_z:{} < {}",
            virtual_tblrXYZnf.center.z,-screenDeep6);
        )

}


float SphereDemo::distanceOfPoint2D_pair(const pair<float,float>& p1,const pair<float,float>& p2){
    float distance = glm::sqrt((p1.first - p2.first)*(p1.first - p2.first) + (p1.second - p2.second)*(p1.second - p2.second));
    return distance;
}
void SphereDemo::switchDebug(){
    if(debugLine==0){
        debugLine = 1;
        println(stderr,"sphere debugLine 1");
    }
    else if(debugLine==1){
        debugLine = 2;
        println(stderr,"sphere debugLine 2");
        // __debugbreak(); // 强制中断
    }
    else{
        debugLine = 0;
        println(stderr,"sphere debugLine 0");
    }
}
void SphereDemo::freshCircleAxis(){

//    freshGoX();freshGoY();freshGoDEEP(); // 刷新世界系3D的时候 已经..

    freshTiltAxis(); // 刷新 倾斜轴
    freshParallelAxis(); // 刷新 平行轴
}
void SphereDemo::drawSphereAxis(ScreenDemo *ScreenEye) {
    if(debugLine != 2)return;
    drawTiltAxis(ScreenEye); // 画倾斜轴
    drawParallelAxis(ScreenEye); // 画平行轴
}
void SphereDemo::freshGoX(){
    world_toX.dx = (tblrXYZnf.rtnSet.x - tblrXYZnf.ltnSet.x) / boxLenX;
    world_toX.dy = (tblrXYZnf.rtnSet.y - tblrXYZnf.ltnSet.y) / boxLenX;
    world_toX.dz = (tblrXYZnf.rtnSet.z - tblrXYZnf.ltnSet.z) / boxLenX;
}
void SphereDemo::freshGoY(){
    world_toY.dx = (tblrXYZnf.lbnSet.x - tblrXYZnf.ltnSet.x) / boxLenY;
    world_toY.dy = (tblrXYZnf.lbnSet.y - tblrXYZnf.ltnSet.y) / boxLenY;
    world_toY.dz = (tblrXYZnf.lbnSet.z - tblrXYZnf.ltnSet.z) / boxLenY;
}
void SphereDemo::freshGoDEEP() {
    world_toDEEP.dx = (tblrXYZnf.ltfSet.x - tblrXYZnf.ltnSet.x) / boxLenZ;
    world_toDEEP.dy = (tblrXYZnf.ltfSet.y - tblrXYZnf.ltnSet.y) / boxLenZ;
    world_toDEEP.dz = (tblrXYZnf.ltfSet.z - tblrXYZnf.ltnSet.z) / boxLenZ;
}
glm::vec3 SphereDemo::goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * world_toX.dx;
    _srcXYZ.y = _srcXYZ.y + _move * world_toX.dy;
    _srcXYZ.z = _srcXYZ.z + _move * world_toX.dz;
    return _srcXYZ;
}
glm::vec3 SphereDemo::goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * world_toY.dx;
    _srcXYZ.y = _srcXYZ.y + _move * world_toY.dy;
    _srcXYZ.z = _srcXYZ.z + _move * world_toY.dz;
    return _srcXYZ;
}
glm::vec3 SphereDemo::goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * world_toDEEP.dx;
    _srcXYZ.y = _srcXYZ.y + _move * world_toDEEP.dy;
    _srcXYZ.z = _srcXYZ.z + _move * world_toDEEP.dz;
    return _srcXYZ;
}
void SphereDemo::freshTiltAxis(){
    // 中
    tiltAxis3D[0] = tblrXYZnf.center;
    // x轴
    tiltAxis3D[1].x = tblrXYZnf.center.x + world_toX.dx * radiusA*1.2f; // 数轴长度 看宽
    tiltAxis3D[1].y = tblrXYZnf.center.y + world_toX.dy * radiusA*1.2f;
    tiltAxis3D[1].z = tblrXYZnf.center.z + world_toX.dz * radiusA * 1.2f;
    // y轴
    tiltAxis3D[2].x = tblrXYZnf.center.x + world_toY.dx * radiusB*1.2f;
    tiltAxis3D[2].y = tblrXYZnf.center.y + world_toY.dy * radiusB*1.2f;
    tiltAxis3D[2].z = tblrXYZnf.center.z + world_toY.dz * radiusB * 1.2f;
    // z轴
    tiltAxis3D[3].x = tblrXYZnf.center.x + world_toDEEP.dx * radiusC*1.2f;
    tiltAxis3D[3].y = tblrXYZnf.center.y + world_toDEEP.dy * radiusC*1.2f;
    tiltAxis3D[3].z = tblrXYZnf.center.z + world_toDEEP.dz * radiusC * 1.2f;
}

void SphereDemo::freshParallelAxis(){
    // 中
    parallelAxis3D[0] = tblrXYZnf.center;
    // x轴
    parallelAxis3D[1].x = tblrXYZnf.center.x + radiusA*1.2f; // 数轴长度 看宽
    parallelAxis3D[1].y = tblrXYZnf.center.y;
    parallelAxis3D[1].z = tblrXYZnf.center.z;
    // y轴
    parallelAxis3D[2].x = tblrXYZnf.center.x;
    parallelAxis3D[2].y = tblrXYZnf.center.y + radiusB*1.2f;
    parallelAxis3D[2].z = tblrXYZnf.center.z;
    // z轴
    parallelAxis3D[3].x = tblrXYZnf.center.x;
    parallelAxis3D[3].y = tblrXYZnf.center.y;
    parallelAxis3D[3].z = tblrXYZnf.center.z + radiusC*1.2f;
}

void SphereDemo::drawTiltAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴  世界系 屏幕系 3D→2D
    tiltAxis2D_f[0] = __3d2dGoSphere(ScreenEye, tiltAxis3D[0], nullptr);
    tiltAxis2D_f[1] = __3d2dGoSphere(ScreenEye, tiltAxis3D[1], nullptr);
    tiltAxis2D_f[2] = __3d2dGoSphere(ScreenEye, tiltAxis3D[2], nullptr);
    tiltAxis2D_f[3] = __3d2dGoSphere(ScreenEye, tiltAxis3D[3], nullptr);


//    BGR3f _green;
    //(0.3843137254901961,0.6313725490196078,0.12549019607843137)
//    _green.setBGR(0x62a120,1);// 翠绿
//    BGR3f _blue;
    //(0.7254901960784313,0.5647058823529412,0.1843137254901961)
//    _blue.setBGR(0xb9902f,1);// 云山蓝
//    BGR3f _yellow;
    //(0.054901960784313725,0.6431372549019608,0.8509803921568627)
//    _yellow.setBGR(0x0ea4d9,1);// 芥黄

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

void SphereDemo::drawParallelAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴
    parallelAxis2D_f[0] = __3d2dGoSphere(ScreenEye, parallelAxis3D[0], nullptr);
    parallelAxis2D_f[1] = __3d2dGoSphere(ScreenEye, parallelAxis3D[1], nullptr);
    parallelAxis2D_f[2] = __3d2dGoSphere(ScreenEye, parallelAxis3D[2], nullptr);
    parallelAxis2D_f[3] = __3d2dGoSphere(ScreenEye, parallelAxis3D[3], nullptr);


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
//    glLineWidth(1.0f); // 线宽
//    glBegin(GL_LINES);
//    glColor3f(1.f, 1.f, 1.f);
//    glVertex2f(parallelAxis2D_f[0].x,parallelAxis2D_f[0].y);
//    glVertex2f(parallelAxis2D_f[1].x,parallelAxis2D_f[1].y);
//
//    glVertex2f(parallelAxis2D_f[0].x,parallelAxis2D_f[0].y);
//    glVertex2f(parallelAxis2D_f[2].x,parallelAxis2D_f[2].y);
//
//    glVertex2f(parallelAxis2D_f[0].x,parallelAxis2D_f[0].y);
//    glVertex2f(parallelAxis2D_f[3].x,parallelAxis2D_f[3].y);
//    glEnd();
}


void SphereDemo::freshVirtualGoX() {
    // 提前 求向量长度 便于归一化
//    virtual_squareEdgeLen = glm::distance(virtual_scanBox3D.ltnSet, virtual_scanBox3D.rtnSet);

    virtual_toX.dx = (virtual_tblrXYZnf.rtnSet.x - virtual_tblrXYZnf.ltnSet.x) / boxLenX;
    virtual_toX.dy = (virtual_tblrXYZnf.rtnSet.y - virtual_tblrXYZnf.ltnSet.y) / boxLenX;
    virtual_toX.dz = (virtual_tblrXYZnf.rtnSet.z - virtual_tblrXYZnf.ltnSet.z) / boxLenX;
}

void SphereDemo::freshVirtualGoY() {
    virtual_toY.dx = (virtual_tblrXYZnf.lbnSet.x - virtual_tblrXYZnf.ltnSet.x) / boxLenY;
    virtual_toY.dy = (virtual_tblrXYZnf.lbnSet.y - virtual_tblrXYZnf.ltnSet.y) / boxLenY;
    virtual_toY.dz = (virtual_tblrXYZnf.lbnSet.z - virtual_tblrXYZnf.ltnSet.z) / boxLenY;
}

void SphereDemo::freshVirtualGoDEEP() {
    virtual_toDEEP.dx = (virtual_tblrXYZnf.ltfSet.x - virtual_tblrXYZnf.ltnSet.x) / boxLenZ;
    virtual_toDEEP.dy = (virtual_tblrXYZnf.ltfSet.y - virtual_tblrXYZnf.ltnSet.y) / boxLenZ;
    virtual_toDEEP.dz = (virtual_tblrXYZnf.ltfSet.z - virtual_tblrXYZnf.ltnSet.z) / boxLenZ;
}

void SphereDemo::freshVirtualFlatXY() {
    float normal[4] = {0};

    // xy面 垂z
    normal[0] = virtual_toDEEP.dx;
    normal[1] = virtual_toDEEP.dy;
    normal[2] = virtual_toDEEP.dz; // 法向量 取反 ?


    // ax + by + cz + d = 0
    // d = -a*x1 - b*y1 - c*z1
    normal[3] = -normal[0] * virtual_tblrXYZnf.center.x - normal[1] * virtual_tblrXYZnf.center.y - normal[2] * virtual_tblrXYZnf.center.z;

    // ax + by + cz + d = 0

    virtual_a_b_c_d_XY[0] = normal[0];
    virtual_a_b_c_d_XY[1] = normal[1];
    virtual_a_b_c_d_XY[2] = normal[2];
    virtual_a_b_c_d_XY[3] = normal[3];
}

void SphereDemo::freshVirtualFlatXZ() {
    float normal[4] = {0};

    // xz面 垂y
    normal[0] = virtual_toY.dx;
    normal[1] = virtual_toY.dy;
    normal[2] = virtual_toY.dz; // 法向量 俯视
    normal[3] = -normal[0] * virtual_tblrXYZnf.center.x - normal[1] * virtual_tblrXYZnf.center.y -
            normal[2] * virtual_tblrXYZnf.center.z; // 代入中心
    virtual_a_b_c_d_XZ[0] = normal[0];
    virtual_a_b_c_d_XZ[1] = normal[1];
    virtual_a_b_c_d_XZ[2] = normal[2];
    virtual_a_b_c_d_XZ[3] = normal[3];
}

void SphereDemo::freshVirtualFlatYZ() {
    float normal[4] = {0};

    // yz面 垂x
    normal[0] = virtual_toX.dx;
    normal[1] = virtual_toX.dy;
    normal[2] = virtual_toX.dz; // 法向量 左视
    normal[3] = -normal[0] * virtual_tblrXYZnf.center.x - normal[1] * virtual_tblrXYZnf.center.y -
                normal[2] * virtual_tblrXYZnf.center.z; // 代入中心
    virtual_a_b_c_d_YZ[0] = normal[0];
    virtual_a_b_c_d_YZ[1] = normal[1];
    virtual_a_b_c_d_YZ[2] = normal[2];
    virtual_a_b_c_d_YZ[3] = normal[3];

}

float SphereDemo::virtual_Point2FlatYZ(glm::vec3& _point) {
    goLine32 goBackX;
    goBackX._ = -virtual_toX._;

    float a = virtual_a_b_c_d_YZ[0]; // yz面 垂x
    float b = virtual_a_b_c_d_YZ[1];
    float c = virtual_a_b_c_d_YZ[2];
    float d = virtual_a_b_c_d_YZ[3];
    float step, step_up, step_down;
    step_up = -a*_point.x - b*_point.y - c*_point.z - d;
//    if(std::isnan(step_up)){
//        cerr << "step_up is nan" << endl;
//    }
    step_down = a*goBackX.dx + b*goBackX.dy + c*goBackX.dz;
//    if(std::isnan(step_down)){
//        cerr << "step_down is nan" << endl;
//    }
    step = step_up / step_down;
    return step;

}

float SphereDemo::virtual_Point2FlatXZ(glm::vec3 &_point) {
    goLine32 goBackY = {-virtual_toY.dx, -virtual_toY.dy, -virtual_toY.dz};

    float a = virtual_a_b_c_d_XZ[0]; // xz面 垂y
    float b = virtual_a_b_c_d_XZ[1];
    float c = virtual_a_b_c_d_XZ[2];
    float d = virtual_a_b_c_d_XZ[3];
    float step, step_up, step_down;
    step_up = -a*_point.x - b*_point.y - c*_point.z - d;
//    if(std::isnan(step_up)){
//        cerr << "step_up is nan" << endl;
//    }
    step_down = a*goBackY.dx + b*goBackY.dy + c*goBackY.dz;
//    if(std::isnan(step_down)){
//        cerr << "step_down is nan" << endl;
//    }
    step = step_up / step_down;
    return step;
}

float SphereDemo::virtual_Point2FlatXY(glm::vec3 &_point) {
    goLine32 goBackZ = {-virtual_toDEEP.dx, -virtual_toDEEP.dy, -virtual_toDEEP.dz};

    float a = virtual_a_b_c_d_XY[0];
    float b = virtual_a_b_c_d_XY[1];
    float c = virtual_a_b_c_d_XY[2];
    float d = virtual_a_b_c_d_XY[3];
    float step, step_up, step_down;
    step_up = -a*_point.x - b*_point.y - c*_point.z - d;
//    if(std::isnan(step_up)){
//        cerr << "step_up is nan" << endl;
//    }
    step_down = a*goBackZ.dx + b*goBackZ.dy + c*goBackZ.dz;
//    if(std::isnan(step_down)){
//        cerr << "step_down is nan" << endl;
//    }
    step = step_up / step_down;
    return step;
}

glm::vec3 SphereDemo::screenXYZ2SelfXYZ(glm::vec3 &_screenXYZ) {
    float leaveZeroX = virtual_Point2FlatYZ(_screenXYZ);
    float leaveZeroY = virtual_Point2FlatXZ(_screenXYZ);
    float leaveZeroZ = virtual_Point2FlatXY(_screenXYZ);

    return glm::vec3{leaveZeroX, leaveZeroY, leaveZeroZ};
}

float SphereDemo::getLatitudeOnSelfAxis(glm::vec3 &_point) {
    float faceLine = sqrtf(_point.x * _point.x + _point.z * _point.z);
//    float sideLine = _point.z;
    float latitudeAngle = glm::degrees(glm::atan(faceLine, -_point.y));
    return latitudeAngle;
}

float SphereDemo::getLongitudeOnSelfAxis(glm::vec3& _point){
    float longitudeAngle = glm::degrees(glm::atan(_point.x, -_point.z));
    return longitudeAngle;
}

glm::vec2 SphereDemo::getUV_by_Latitude_Longitude(float longitude, float latitude){
    float u = (longitude + 90.f) / 180.f; // -90~90
    float v = (latitude - 30.f) / 120.f; // 30~150
    assert(longitude > -90.f && longitude < 90.f);
    if(latitude >= 30.f && latitude <= 150.f){}
    else{
        println(stderr, "latitude:", latitude, " is out of 30~150");
    }

    return {u,v};
}
glm::vec3 SphereDemo::getImgColor_by_UV(glm::vec2& uv01){
    if(uv01[0] < 0){
//        cerr << "u: " << u << " < 0" << endl;
//        return {0.f,0.f,0.f};
        uv01[0] = 0.f;
    }
    else if(uv01[0] > 1){
//        cerr << "u: " << u << " > 1" << endl;
//        return {0.f,0.f,0.f};
        uv01[0] = 1.f;
    }
    if(uv01[1] < 0){
//        cerr << "v: " << v << " < 0" << endl;
//        return {0.f,0.f,0.f};
        uv01[1] = 0.f;
    }
    else if(uv01[1] > 1){
//        cerr << "v: " << v << " > 1" << endl;
//        return {0.f,0.f,0.f};
        uv01[1] = 1.f;
    }

    int u_i = static_cast<int>(uv01[0]*imgW_f);
    int v_i = static_cast<int>(uv01[1]*imgH_f);
    // 索引
    int index = v_i * imgW_f + u_i;

    if(index < pixelsColor.data.size()){ // 最后一个和 size 相等
        return pixelsColor.data[index];
    }// 颜色
        return {0.f,0.f,0.f};

}
#ifdef MAYBE_UNUSED
void SphereDemo::freshRadius2D(){
    /*
    float t = screenDeep6 / (virtual_scanBox3D.center.z + screenDeep6);
    float sx = screenWidth6/2.f + (virtual_scanBox3D.center.x-screenWidth6/2.f) * t;
    float sy = screenHeight6/2.f + (virtual_scanBox3D.center.y-screenHeight6/2.f) * t;

    float distance_eye2center = glm::sqrt((virtual_scanBox3D.center.x - screenWidth6/2.f)*(virtual_scanBox3D.center.x - screenWidth6/2.f) +
            (virtual_scanBox3D.center.y - screenHeight6/2.f)*(virtual_scanBox3D.center.y - screenHeight6/2.f) +
            (virtual_scanBox3D.center.z + screenDeep6)*(virtual_scanBox3D.center.z + screenDeep6));
    float r_screen = radius * screenDeep6 / distance_eye2center + 0;
    float y_min = 0 > sy-r_screen ? 0 : sy-r_screen;
    float y_max = screenHeight6 - 1 < sy + r_screen ? screenHeight6 - 1 : sy + r_screen;
    glBegin(GL_POINTS);
    glColor3f(241.0f/255.f,68.0f/255.f,29.0f/255.f); // 蜻蜓红
    for(int y=y_min;y<y_max+1;y++){
        float dy = y - sy;
        if(fabs(dy) > r_screen)continue;
        float dx = glm::sqrt(r_screen*r_screen - dy*dy);
        float x_left = 0 > sx-dx ? 0 : sx-dx;
        float x_right = screenWidth6-1 < sx+dx ? screenWidth6-1 : sx+dx;

        glVertex2f(x_left,(float)y);
        glVertex2f(x_right,(float)y);
    }
        glEnd();
    */
    /*
     球体透视投影 外围 2D中心最远
     a = r' * f / D
     r' = (r/d) * sqrt(d²-r²)
     d = sqrt((cx-600)²+(cy-400)²+(cz+1000)²)
     D = (d²-r²) / d

         r*sqrt(d²-r²) * 1000      1000*r
     a = --------------------- = -------------
         d * ((d²-r²)/d)          sqrt(d²-r²)
     */
    glm::vec3 c = virtual_scanBox3D.center; // 屏幕系 球心
    glm::vec3 e = {screenWidth6/2.f,screenHeight6/2.f,-(float)screenDeep6}; // 屏幕系 固定视点
    // 视线到球心与z夹角  角度不变 转到使球心y=0  <2D椭圆投影长轴等价>
    float virtualCenter_2_ZAxisPoint = distanceOfPoint2D(glm::vec2{c.x,c.y},glm::vec2{e.x,e.y});
    float eye_2_Zpoint = c.z - e.z; // 减 -1000
    float bigAngle = atan(virtualCenter_2_ZAxisPoint / eye_2_Zpoint);
    float eyeRightShootScreen_X = tan(bigAngle) * -e.z + e.x;
    goLine32 eyeRightShoot = ScreenDemo::get_AgoB_direction3D(e,glm::vec3{eyeRightShootScreen_X,0.f,0.f});
//    cout << "eyeRightShootScreen_X:" << eyeRightShootScreen_X << endl;
    float eye2center_distance = glm::distance(e,c);
    glm::vec3 equallyCenter = {e.x + eyeRightShoot.dx*eye2center_distance,
                             e.y + 0.f,
                             e.z + eyeRightShoot.dz*eye2center_distance};
//    cout << "virtual center (" << virtual_scanBox3D.center.x << ", " << virtual_scanBox3D.center.y <<
//    ", " << virtual_scanBox3D.center.z << ") eye nearZ:" << glm::distance(e,virtual_scanBox3D.center) << endl;
//    cout << "equally center (" << equallyCenter.x << ", " << equallyCenter.y <<
//         ", " << equallyCenter.z << ") eye nearZ:" << glm::distance(e,equallyCenter) << endl;
    float radius = std::min(std::min(boxLenX,boxLenY),boxLenZ) / 2.f -1.f;
pair<float,float> centerDown = {equallyCenter.x,equallyCenter.z}; // x,z
pair<float,float> eyeDown = {e.x,e.z}; // x 600 z -1000
float eye_center_dis = distanceOfPoint2D_pair(centerDown,eyeDown);
float smallAngle = asin(radius/eye_center_dis);
float sideSightLong = glm::sqrt(eye_center_dis*eye_center_dis - radius*radius);
//float bigAngle = atan2(centerDown.first-eyeDown.first,centerDown.second-eyeDown.second);

//float smallerAngle = bigAngle - smallAngle;
//float lenXOfEyeL = glm::sin(smallerAngle) * sideSightLong;
//float lenZOfEyeL = glm::cos(smallerAngle) * sideSightLong;
//float midScreenRightL = lenXOfEyeL * (screenDeep6/lenZOfEyeL); // 俯视 比例三角形 比到屏 左侧

float biggerAngle = bigAngle + smallAngle;
float lenXOfEyeR = glm::sin(biggerAngle) * sideSightLong;
float lenZOfEyeR = glm::cos(biggerAngle) * sideSightLong;
float midScreenRightR = lenXOfEyeR * (screenDeep6/lenZOfEyeR); // 俯视 比例三角形 比到屏 右侧

float midScreenRightM = tan(bigAngle) * screenDeep6; // 俯视 圆心 到屏 中间

//float shortDistanceL = fabs(midScreenRightM - midScreenRightL); // 取绝对值 万一在右边呢?
float shortDistanceR = fabs(midScreenRightR - midScreenRightM);

    radius2D = shortDistanceR;//shortDistanceL > shortDistanceR ? shortDistanceL : shortDistanceR;
    //radius2D *= 0.95; // 扩大10像素

}

void SphereDemo::drawRounfCircle(ScreenDemo* ScreenEye){

//    glBegin(GL_POINTS);
//    glColor3f(46.f/255.f,1.f,1.f);
    float _color_[3] = {0.18039215686f,1.f,1.f}; // 浅蓝 0xffff2e

    for(auto& rowInfo : lineScanFillColor_circle){

        ScreenEye->putPixel((int)rowInfo.lx,(int)rowInfo.y,  _color_,
                             frameScreenNear,nullptr);
        ScreenEye->putPixel((int)rowInfo.rx,(int)rowInfo.y,  _color_,
                            frameScreenNear,nullptr);
//        glVertex2f(rowInfo.lx,(float)rowInfo.y);
//        glVertex2f(rowInfo.rx,(float)rowInfo.y);

    }
//    glEnd();
}
#endif
float SphereDemo::imul_a_a(float a){
    // 只管平方的话 这个func简单
    return a * a;
}