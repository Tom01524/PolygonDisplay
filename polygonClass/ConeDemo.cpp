//
// Created by iceoc0 on 2025/4/20.
//

#include "ConeDemo.h"

extern void* settled_ptr; // 全局设置的结构体指针
struct _settledCone{
    int _width;
    int _height;
    int _deep;

};
_settledCone* settled_ = (_settledCone*)settled_ptr;
const int screenWidth13 = settled_-> _width;
const int screenHeight13 = settled_-> _height;
const int screenDeep13 = settled_-> _deep;


extern void* _3d_2d_go_void_ptr; // 3d_2d_go的函数指针
// struct _3d_2d_go_cone{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, float *, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_2d)(ScreenDemo*, float, float, float);
//
// };
glm::vec2 (*__3d2dGocone)(ScreenDemo*, glm::vec3, glm::vec3*) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2dcone)(ScreenDemo*, float, float, float) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d; // 模式1 用自己的不行

namespace SelfAxisInfo{
    glm::vec3 screenPoint;
    goLine32 eyeGoScreen;
    glm::vec3 pointNear;

}

ConeDemo::ConeDemo(glm::vec3 _lt,glm::vec3 _rt,glm::vec3 _rb,glm::vec3 _lb, glm::vec3 _downTip, unsigned char _debug_):PolygonBase(13) {
//    PolygonBase::type_ = 13; // 圆锥体类型

    debugLine = _debug_;
    setTBLRDXYZ(_lt, _rt, _rb, _lb, _downTip);

    tblrdXYZ_unchange.ltSet = tblrdXYZ.ltSet;
    tblrdXYZ_unchange.rtSet = tblrdXYZ.rtSet;
    tblrdXYZ_unchange.rbSet = tblrdXYZ.rbSet;
    tblrdXYZ_unchange.lbSet = tblrdXYZ.lbSet;
    tblrdXYZ_unchange.downCuspSet = tblrdXYZ.downCuspSet;

    tblrdXYZ_unchange.center = tblrdXYZ.center;
    tblrdXYZ_unchange.centerTip = tblrdXYZ.centerTip;
    tblrdXYZ_unchange.centerBack = tblrdXYZ.centerBack;

    tblrdXYZ_unchange.lt_rt_tip = tblrdXYZ.lt_rt_tip;
    tblrdXYZ_unchange.lt_rt_back = tblrdXYZ.lt_rt_back;
    tblrdXYZ_unchange.lt_lb_tip = tblrdXYZ.lt_lb_tip;
    tblrdXYZ_unchange.lt_lb_back = tblrdXYZ.lt_lb_back;

    tblrdXYZ_unchange.rb_rt_tip = tblrdXYZ.rb_rt_tip;
    tblrdXYZ_unchange.rb_rt_back = tblrdXYZ.rb_rt_back;
    tblrdXYZ_unchange.rb_lb_tip = tblrdXYZ.rb_lb_tip;
    tblrdXYZ_unchange.rb_lb_back = tblrdXYZ.rb_lb_back;

    squareEdge = glm::distance(_lt,_rt);
    radius = squareEdge / 2.f - 2.f;
    height = glm::distance(tblrdXYZ.center,tblrdXYZ.downCuspSet);

    radiusDivideHeight = radius / height; // 圆锥 经高比

    height_1_3 = height / 3.f;
    height_2_3 = height_1_3 * 2.f;

    startEye = {(float)screenWidth13/2.f,(float)screenHeight13/2.f,(float)-screenDeep13};

    if(!ScreenAxis2Self_SameFlat) {
        freshFrameRotateInfo(); // 屏幕系 批量转 自己系 初始化
    }
}

void ConeDemo::Draw_Tick(ScreenDemo *ScreenEye) {
    displayNecessary = true;

    bool all2Dleft = tblrdXY.ltSet.x < 0.f && tblrdXY.rtSet.x < 0.f &&
            tblrdXY.rbSet.x < 0.f && tblrdXY.lbSet.x < 0.f && tblrdXY.downCuspSet.x < 0.f;
    bool all2Dright = tblrdXY.ltSet.x > (float)screenWidth13 && tblrdXY.rtSet.x > (float)screenWidth13 &&
                      tblrdXY.rbSet.x > (float)screenWidth13 && tblrdXY.lbSet.x > (float)screenWidth13 &&
                      tblrdXY.downCuspSet.x > (float)screenWidth13;
    bool all2Dtop = tblrdXY.ltSet.y < 0.f && tblrdXY.rtSet.y < 0.f &&
                    tblrdXY.rbSet.y < 0.f && tblrdXY.lbSet.y < 0.f && tblrdXY.downCuspSet.y < 0.f;
    bool all2Dbottom = tblrdXY.ltSet.y > (float)screenHeight13 && tblrdXY.rtSet.y > (float)screenHeight13 &&
                       tblrdXY.rbSet.y > (float)screenHeight13 && tblrdXY.lbSet.y > (float)screenHeight13 &&
                       tblrdXY.downCuspSet.y > (float)screenHeight13;
    bool corner2DoutOfScreen = all2Dleft || all2Dright || all2Dtop || all2Dbottom;

    if(corner2DoutOfScreen){
        println("圆锥在 屏幕外");
        displayNecessary = false;
    }
        if(debugLine==2){
            // 移动才刷新 mode2 写在自己setXYZ mode4看 屏幕setXYZ
            // 还是每帧刷新吧
            freshCircleAxis();
        }

    freshVirtualGoX(); // 屏幕系 数轴三向
    freshVirtualGoY();
    freshVirtualGoDEEP();
    if(ScreenAxis2Self_SameFlat){
        freshVirtualFlatXY(); // 屏幕系 数轴三面
        freshVirtualFlatYZ();
        freshVirtualFlatXZ();
    }

    if(!ScreenAxis2Self_SameFlat){
        freshFrameRotateInfo(); // wxyz 转自己系
    }


//    glm::vec3 selfLTset = screenXYZ2SelfXYZ(virtual_tblrdXYZ.ltSet);
//        cout << "ConeDemo::Draw_Tick() selfLTset.x=" << selfLTset.x << " selfLTset.y=" <<
//        selfLTset.y << " selfLTset.z=" << selfLTset.z << endl; // 实验 屏幕系 转自己系 √

//    glm::vec3 selfRBset = screenXYZ2SelfXYZ(virtual_tblrdXYZ.rbSet);
//    cout << "ConeDemo::Draw_Tick() selfRBset.x=" << selfRBset.x << " selfRBset.y=" <<
//         selfRBset.y << " selfRBset.z=" << selfRBset.z << endl; // 实验 屏幕系 转自己系 √



    if(ScreenAxis2Self_SameFlat) {
        eyeOnSelfAxis = screenXYZ2SelfXYZ(startEye);

        screenLT_onSelfAxis = screenXYZ2SelfXYZ({0.f,0.f,0.f});
        screenRT_onSelfAxis = screenXYZ2SelfXYZ({ScreenEye->rectWidth,0.f,0.f});
        screenLB_onSelfAxis = screenXYZ2SelfXYZ({0.f,ScreenEye->rectHeight,0.f});

        freshScreenGoX_OnSelfAxis(); // 屏幕走 在自己系看
        freshScreenGoY_OnSelfAxis(); // x → y ↓
    }else{
        eyeOnSelfAxis = screenXYZ2SelfXYZ2(startEye);
    }



    frameScreenNear = virtual_tblrdXYZ.center.z; // 初始 屏垂距 最近最远
    frameScreenFar = virtual_tblrdXYZ.center.z;

    bool cornerClose2Eye = frameScreenNear + (float)screenDeep13 < 100.0F;
    if(cornerClose2Eye){
        println("圆锥视点近");
        displayNecessary = false;
    }

//    cout << "ConeDemo::Draw_Tick() eyeOnSelfAxis.x=" << eyeOnSelfAxis.x << " eyeOnSelfAxis.y=" <<
//         eyeOnSelfAxis.y << " eyeOnSelfAxis.z=" << eyeOnSelfAxis.z << endl; // 屏幕系 转自己系 √

//    pair<float,float> stepNF = getEyeThenStepByScreenXY(tblrdXY.center);

//    cout << "圆锥Draw_Tick() stepNF.first=" << stepNF.first << " stepNF.second=" << stepNF.second << endl;

    flatLtRtFacing = cTipEyeCloser(ScreenEye->getCenterTip(), tblrdXYZ.lt_rt_tip, tblrdXYZ.lt_rt_back);
    flatRtRbFacing = cTipEyeCloser(ScreenEye->getCenterTip(), tblrdXYZ.rb_rt_tip, tblrdXYZ.rb_rt_back);
    flatRbLbFacing = cTipEyeCloser(ScreenEye->getCenterTip(), tblrdXYZ.rb_lb_tip, tblrdXYZ.rb_lb_back);
    flatLbLtFacing = cTipEyeCloser(ScreenEye->getCenterTip(), tblrdXYZ.lt_lb_tip, tblrdXYZ.lt_lb_back);
    rectFacing = cTipEyeCloser(ScreenEye->getCenterTip(), tblrdXYZ.centerTip, tblrdXYZ.centerBack);

//    cout << "ConeDemo::Draw_Tick() " << endl;


//    cout << " flatLtRtFacing=" << flatLtRtFacing << " flatRtRbFacing=" <<
//    flatRtRbFacing << " flatRbLbFacing=" << flatRbLbFacing << " flatLbLtFacing=" << flatLbLtFacing <<
//    " rectFacing=" << rectFacing << endl;
    if(displayNecessary){
        if(flatRbLbFacing){
            _solidBoxRect2D_front(ScreenEye, true);
//            cout << "包围盒 正面" << endl;
        }
        if(flatLbLtFacing){
            _solidBoxRect2D_left(ScreenEye, true);
//            cout << "包围盒 左面" << endl;
        }
        if(flatRtRbFacing){
            _solidBoxRect2D_right(ScreenEye, true);
//            cout << "包围盒 右面" << endl;
        }
        if(flatLtRtFacing){
            _solidBoxRect2D_back(ScreenEye, true);
//            cout << "包围盒 背面" << endl;
        }
        if(rectFacing){
            _solidBoxRect2D_top(ScreenEye, true);
//            cout << "包围盒 上面" << endl;
        }
        float _color[3] = {1.0f, 1.0f, 1.0f};
        if(debugLine==1){

            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.ltSet.x, tblrdXY.ltSet.y,
                                          tblrdXY.rtSet.x, tblrdXY.rtSet.y,
                                          _color,frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.rtSet.x, tblrdXY.rtSet.y,
                                          tblrdXY.rbSet.x, tblrdXY.rbSet.y,
                                          _color,frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.rbSet.x, tblrdXY.rbSet.y,
                                          tblrdXY.lbSet.x, tblrdXY.lbSet.y,
                                          _color,frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.lbSet.x, tblrdXY.lbSet.y,
                                          tblrdXY.ltSet.x, tblrdXY.ltSet.y,
                                          _color,frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.ltSet.x, tblrdXY.ltSet.y,
                                          tblrdXY.downCuspSet.x, tblrdXY.downCuspSet.y,
                                          _color,frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.rtSet.x, tblrdXY.rtSet.y,
                                          tblrdXY.downCuspSet.x, tblrdXY.downCuspSet.y,
                                          _color,frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.rbSet.x, tblrdXY.rbSet.y,
                                          tblrdXY.downCuspSet.x, tblrdXY.downCuspSet.y,
                                          _color,frameScreenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.lbSet.x, tblrdXY.lbSet.y,
                                          tblrdXY.downCuspSet.x, tblrdXY.downCuspSet.y,
                                          _color,frameScreenNear);


//            glBegin(GL_LINES);

            if(flatLtRtFacing){
                _color[0]=0.0f;_color[1]=1.0f;_color[2]=0.0f;
//                glColor3f(0.0f, 1.0f, 0.0f);
            }else{
                _color[0]=1.0f;_color[1]=0.0f;_color[2]=0.0f;
//                glColor3f(1.0f, 0.0f, 0.0f);
            }
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.lt_rt_tip.x, tblrdXY.lt_rt_tip.y,
                                          tblrdXY.lt_rt_back.x, tblrdXY.lt_rt_back.y,
                                          _color,frameScreenNear);


            if(flatRtRbFacing){
                _color[0]=0.0f;_color[1]=1.0f;_color[2]=0.0f;
//                glColor3f(0.0f, 1.0f, 0.0f);
            }else{
                _color[0]=1.0f;_color[1]=0.0f;_color[2]=0.0f;
//                glColor3f(1.0f, 0.0f, 0.0f);
            }
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.rb_rt_tip.x, tblrdXY.rb_rt_tip.y,
                                          tblrdXY.rbSet.x, tblrdXY.rbSet.y,
                                          _color,frameScreenNear);


            if(flatRbLbFacing){
                _color[0]=0.0f;_color[1]=1.0f;_color[2]=0.0f;
//                glColor3f(0.0f, 1.0f, 0.0f);
            }else{
                _color[0]=1.0f;_color[1]=0.0f;_color[2]=0.0f;
//                glColor3f(1.0f, 0.0f, 0.0f);
            }
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.rb_lb_tip.x, tblrdXY.rb_lb_tip.y,
                                          tblrdXY.rb_lb_back.x, tblrdXY.rb_lb_back.y,
                                          _color,frameScreenNear);


            if(flatLbLtFacing){
                _color[0]=0.0f;_color[1]=1.0f;_color[2]=0.0f;
//                glColor3f(0.0f, 1.0f, 0.0f);
            }else{
                _color[0]=1.0f;_color[1]=0.0f;_color[2]=0.0f;
//                glColor3f(1.0f, 0.0f, 0.0f);
            }
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.lt_lb_tip.x, tblrdXY.lt_lb_tip.y,
                                          tblrdXY.ltSet.x, tblrdXY.ltSet.y,
                                          _color,frameScreenNear);



            if(rectFacing) {
                _color[0]=0.0f;_color[1]=1.0f;_color[2]=0.0f;
//                glColor3f(0.0f, 1.0f, 0.0f);
            }else{
                _color[0]=1.0f;_color[1]=0.0f;_color[2]=0.0f;
//                glColor3f(1.0f, 0.0f, 0.0f);
            }
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrdXY.centerTip.x, tblrdXY.centerTip.y,
                                          tblrdXY.center.x, tblrdXY.center.y,
                                          _color,frameScreenNear);


//            glEnd();
        }
        if(debugLine == 2){
            drawVerticalTipByInfo(ScreenEye);
        }
    }



}

void ConeDemo::setTBLRDXYZ(glm::vec3 _lt, glm::vec3 _rt, glm::vec3 _rb, glm::vec3 _lb, glm::vec3 _downCusp) {

    tblrdXYZ.ltSet = _lt;
    tblrdXYZ.rtSet = _rt;
    tblrdXYZ.rbSet = _rb;
    tblrdXYZ.lbSet = _lb;
    tblrdXYZ.downCuspSet = _downCusp;

    tblrdXYZ.center.x = (_lt.x + _rb.x) / 2.f;
    tblrdXYZ.center.y = (_lt.y + _rb.y) / 2.f;
    tblrdXYZ.center.z = (_lt.z + _rb.z) / 2.f;

    goLine32 c_rt_dir = ScreenDemo::get_AgoB_direction3D(tblrdXYZ.center, tblrdXYZ.rtSet);
    goLine32 c_lt_dir = ScreenDemo::get_AgoB_direction3D(tblrdXYZ.center, tblrdXYZ.ltSet);
    goLine32 c_ctip_dir;
    c_ctip_dir._ = glm::cross(c_rt_dir._, c_lt_dir._);
    c_ctip_dir._ = glm::normalize(c_ctip_dir._);
    tblrdXYZ.centerTip = {tblrdXYZ.center.x+c_ctip_dir.dx*rounfBoxTipLen, tblrdXYZ.center.y+c_ctip_dir.dy*rounfBoxTipLen,
                          tblrdXYZ.center.z+ c_ctip_dir.dz * rounfBoxTipLen};
    tblrdXYZ.centerBack = {tblrdXYZ.center.x-c_ctip_dir.dx*rounfBoxTipLen, tblrdXYZ.center.y-c_ctip_dir.dy*rounfBoxTipLen,
                           tblrdXYZ.center.z- c_ctip_dir.dz * rounfBoxTipLen};

    goLine32 lt_d_dir = ScreenDemo::get_AgoB_direction3D(_lt, tblrdXYZ.downCuspSet);

    goLine32 lt_rt_dir = ScreenDemo::get_AgoB_direction3D(_lt, _rt);
    goLine32 lt_rt_tip_dir;
    lt_rt_tip_dir._ = glm::cross(lt_rt_dir._, lt_d_dir._); // 后侧 法线
    lt_rt_tip_dir._ = glm::normalize(lt_rt_tip_dir._);
    tblrdXYZ.lt_rt_tip = {_lt.x+lt_rt_tip_dir.dx*rounfBoxTipLen, _lt.y+lt_rt_tip_dir.dy*rounfBoxTipLen,
                          _lt.z+ lt_rt_tip_dir.dz * rounfBoxTipLen};
    tblrdXYZ.lt_rt_back = {_lt.x-lt_rt_tip_dir.dx*rounfBoxTipLen, _lt.y-lt_rt_tip_dir.dy*rounfBoxTipLen,
                           _lt.z- lt_rt_tip_dir.dz * rounfBoxTipLen};

    goLine32 lt_lb_dir = ScreenDemo::get_AgoB_direction3D(_lb,_lt);
    goLine32 lt_lb_tip_dir;
    lt_lb_tip_dir._ = glm::cross(lt_lb_dir._, lt_d_dir._); // 左侧 法线
    lt_lb_tip_dir._ = glm::normalize(lt_lb_tip_dir._);
    tblrdXYZ.lt_lb_tip = {_lt.x + lt_lb_tip_dir.dx * rounfBoxTipLen, _lt.y + lt_lb_tip_dir.dy * rounfBoxTipLen,
                          _lt.z + lt_lb_tip_dir.dz * rounfBoxTipLen};
    tblrdXYZ.lt_lb_back = {_lt.x - lt_lb_tip_dir.dx * rounfBoxTipLen, _lt.y - lt_lb_tip_dir.dy * rounfBoxTipLen,
                           _lt.z - lt_lb_tip_dir.dz * rounfBoxTipLen};

    goLine32 rb_d_dir = ScreenDemo::get_AgoB_direction3D(_rb, tblrdXYZ.downCuspSet);

    goLine32 rb_rt_dir = ScreenDemo::get_AgoB_direction3D(_rt,_rb);
    goLine32 rb_rt_tip_dir;
    rb_rt_tip_dir._ = glm::cross(rb_rt_dir._, rb_d_dir._); // 右侧 法线
    rb_rt_tip_dir._ = glm::normalize(rb_rt_tip_dir._);
    tblrdXYZ.rb_rt_tip = {_rb.x + rb_rt_tip_dir.dx * rounfBoxTipLen, _rb.y + rb_rt_tip_dir.dy * rounfBoxTipLen,
                          _rb.z + rb_rt_tip_dir.dz * rounfBoxTipLen};
    tblrdXYZ.rb_rt_back = {_rb.x - rb_rt_tip_dir.dx * rounfBoxTipLen, _rb.y - rb_rt_tip_dir.dy * rounfBoxTipLen,
                           _rb.z - rb_rt_tip_dir.dz * rounfBoxTipLen};

    goLine32 rb_lb_dir = ScreenDemo::get_AgoB_direction3D(_rb, _lb);
    goLine32 rb_lb_tip_dir;
    rb_lb_tip_dir._ = glm::cross(rb_lb_dir._, rb_d_dir._); // 前面 法线
    rb_lb_tip_dir._ = glm::normalize(rb_lb_tip_dir._);
    tblrdXYZ.rb_lb_tip = {_rb.x+rb_lb_tip_dir.dx*rounfBoxTipLen, _rb.y+rb_lb_tip_dir.dy*rounfBoxTipLen,
                          _rb.z+ rb_lb_tip_dir.dz * rounfBoxTipLen};
    tblrdXYZ.rb_lb_back = {_rb.x-rb_lb_tip_dir.dx*rounfBoxTipLen, _rb.y-rb_lb_tip_dir.dy*rounfBoxTipLen,
                           _rb.z- rb_lb_tip_dir.dz * rounfBoxTipLen};


}

void ConeDemo::setTBLRDXY(glm::vec2 _lt, glm::vec2 _rt, glm::vec2 _rb, glm::vec2 _lb, glm::vec2 _downCusp,
                          glm::vec2 _center,
                          glm::vec2 _lt_rt_tip,glm::vec2 _lt_rt_back,
                          glm::vec2 _lt_lb_tip,glm::vec2 _lt_lb_back,
                          glm::vec2 _rb_rt_tip,glm::vec2 _rb_rt_back,
                          glm::vec2 _rb_lb_tip,glm::vec2 _rb_lb_back,
                          glm::vec2 _centerTip, glm::vec2 _centerBack) {
    tblrdXY.ltSet = _lt;
    tblrdXY.rtSet = _rt;
    tblrdXY.rbSet = _rb;
    tblrdXY.lbSet = _lb;

    tblrdXY.downCuspSet = _downCusp;
    tblrdXY.center = _center;

    tblrdXY.lt_rt_tip = _lt_rt_tip;
    tblrdXY.lt_rt_back = _lt_rt_back;

    tblrdXY.lt_lb_tip = _lt_lb_tip;
    tblrdXY.lt_lb_back = _lt_lb_back;

    tblrdXY.rb_rt_tip = _rb_rt_tip;
    tblrdXY.rb_rt_back = _rb_rt_back;

    tblrdXY.rb_lb_tip = _rb_lb_tip;
    tblrdXY.rb_lb_back = _rb_lb_back;

    tblrdXY.centerTip = _centerTip;
    tblrdXY.centerBack = _centerBack;

}

bool ConeDemo::cTipEyeCloser(glm::vec3 eyeCenter, glm::vec3 tip, glm::vec3 back){
    float tipDis_square = (tip.x - eyeCenter.x)*(tip.x - eyeCenter.x) +
                          (tip.y - eyeCenter.y)*(tip.y - eyeCenter.y) +
                          (tip.z - eyeCenter.z)*(tip.z - eyeCenter.z);
    float backDis_square = (back.x - eyeCenter.x)*(back.x - eyeCenter.x) +
                           (back.y - eyeCenter.y)*(back.y - eyeCenter.y) +
                           (back.z - eyeCenter.z)*(back.z - eyeCenter.z);
    return tipDis_square < backDis_square;
}
#ifdef MAYBE_UNUSED
bool ConeDemo::PolyScanClicked(ScreenDemo* ScreenEye, int x,int y) {
    bool thisOnTop = false;
    if (flatRbLbFacing) {
        for (auto &_rowInfo: pixelSurfaceInfo_front) {
            if (y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (x == _pixelInfo.x && (_pixelInfo.area == 1 || _pixelInfo.area == 2)) {
                        goto clickedOn; // 点在锥面 x也对
                    }
                }
                goto N2next; // 找到y 扫完x 没有 退
            }

        }
    }N2next:
    if (flatLbLtFacing) {
        for (auto &_rowInfo: pixelEyeDeep_left) {
            if (y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (x == _pixelInfo.x && (_pixelInfo.area == 1 || _pixelInfo.area == 2)) {
                        goto clickedOn; // 点在锥面 x也对
                    }
                }
                goto L2next; // 找到y 扫完x 没有 退
            }

        }
    }L2next:
    if (flatRtRbFacing) {
        for (auto &_rowInfo: pixelEyeDeep_right) {
            if (y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (x == _pixelInfo.x && (_pixelInfo.area == 1 || _pixelInfo.area == 2)) {
                        goto clickedOn; // 点在锥面 x也对
                    }
                }
                goto R2next; // 找到y 扫完x 没有 退
            }

        }
    }R2next:
    if (flatLtRtFacing) {
        for (auto &_rowInfo: pixelEyeDeep_back) {
            if (y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (x == _pixelInfo.x && (_pixelInfo.area == 1 || _pixelInfo.area == 2)) {
                        goto clickedOn; // 点在锥面 x也对
                    }
                }
                goto F2next; // 找到y 扫完x 没有 退
            }

        }
    }F2next:
    if(rectFacing){
        for (auto &_rowInfo: pixelEyeDeep_top) {
            if (y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (x == _pixelInfo.x && (_pixelInfo.area == 1 || _pixelInfo.area == 2)) {
                        thisOnTop = true;
                        goto clickedOn; // 点在锥面 x也对
                    }
                }
                goto T2next; // 找到y 扫完x 没有 退
            }

        }
    }T2next:


    // 都不在 xy
    return false;

    clickedOn:
    clickedSurfacePos = {(float)x,(float)y};
    freshSurfaceAndTipLine_Self(ScreenEye, thisOnTop);
    cout << "圆锥 被点击了！" << endl;
    return true;

}
#endif

void ConeDemo::switchDebug(ScreenDemo* ScreenEye){
    if(debugLine==0){
        debugLine = 1;
        println("cone debugLine 1");
    }
    else if(debugLine==1){
        debugLine = 2;
        println("cone debugLine 2");
    }
    else{
        debugLine = 0;
        println("cone debugLine 0");
    }

    bool thisOnTop = false;
    glm::ivec2 clickedPos = ScreenEye->clickedLast;
    if (flatRbLbFacing) {
        for (auto &_rowInfo: pixelEyeDeep_front) {
            if (clickedPos.y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (clickedPos.x == _pixelInfo.x && (_pixelInfo.area == 1 || _pixelInfo.area == 2)) {
                        goto clickedOn; // 点在锥面 x也对
                    }
                }
                goto N2next; // 找到y 扫完x 没有 退
            }

        }
    }N2next:
    if (flatLbLtFacing) {
        for (auto &_rowInfo: pixelEyeDeep_left) {
            if (clickedPos.y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (clickedPos.x == _pixelInfo.x && (_pixelInfo.area == 1 || _pixelInfo.area == 2)) {
                        goto clickedOn; // 点在锥面 x也对
                    }
                }
                goto L2next; // 找到y 扫完x 没有 退
            }

        }
    }L2next:
    if (flatRtRbFacing) {
        for (auto &_rowInfo: pixelEyeDeep_right) {
            if (clickedPos.y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (clickedPos.x == _pixelInfo.x && (_pixelInfo.area == 1 || _pixelInfo.area == 2)) {
                        goto clickedOn; // 点在锥面 x也对
                    }
                }
                goto R2next; // 找到y 扫完x 没有 退
            }

        }
    }R2next:
    if (flatLtRtFacing) {
        for (auto &_rowInfo: pixelEyeDeep_back) {
            if (clickedPos.y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (clickedPos.x == _pixelInfo.x && (_pixelInfo.area == 1 || _pixelInfo.area == 2)) {
                        goto clickedOn; // 点在锥面 x也对
                    }
                }
                goto F2next; // 找到y 扫完x 没有 退
            }

        }
    }F2next:
    if(rectFacing){
        for (auto &_rowInfo: pixelEyeDeep_top) {
            if (clickedPos.y == _rowInfo.y) {
                for (auto &_pixelInfo: _rowInfo.pixelDeeps) {
                    if (clickedPos.x == _pixelInfo.x && (_pixelInfo.area == 1 || _pixelInfo.area == 2)) {
                        thisOnTop = true;
                        goto clickedOn; // 点在锥面 x也对
                    }
                }
                goto T2next; // 找到y 扫完x 没有 退
            }

        }
    }T2next:

    clickedOn:
    clickedSurfacePos = clickedPos;

    freshSurfaceAndTipLine_Self(ScreenEye, thisOnTop);
    println("圆锥 被点击了！");
}
void ConeDemo::freshSurfaceAndTipLine_Self(ScreenDemo* ScreenEye, bool boxTop){

    bool onCircle = false;
    if(!boxTop){
        // 锥面点 自己系
        surfacePos_SelfAxis = getEyeThenStepSelfPosNear_ByScreenXY(clickedSurfacePos);
    }else{
        // 圆面点 自己系
        surfacePos_SelfAxis = get_EyeThenStepPos_OfCircle_ByScreenXY(clickedSurfacePos);
        if(isnan(surfacePos_SelfAxis.x) || isnan(surfacePos_SelfAxis.y) || isnan(surfacePos_SelfAxis.z)){
            // 锥面点 自己系
            surfacePos_SelfAxis = getEyeThenStepSelfPosNear_ByScreenXY(clickedSurfacePos);
        }else{
            onCircle = true;
        }
    }
//    cout << "圆锥表面点 在自己系 点在(" << surfacePos_SelfAxis.x << ", " << surfacePos_SelfAxis.y <<
//    ", " << surfacePos_SelfAxis.z << ")" << endl;
    if(!onCircle){
        // 锥面 法线 上挑角
        float sideSurfaceVertical_Angle2XAxis = glm::atan(radius,height);

        float verticalTipY = surfacePos_SelfAxis.y +
                             glm::sin(sideSurfaceVertical_Angle2XAxis) * (rounfBoxTipLen/2.f); // 侧面 法线 tip 长 40/2

        // 俯视 法线凸 投影 长
        float current_radius_at_point = radius * (1 - surfacePos_SelfAxis.y / height);
        float downView_TipExpand = glm::cos(sideSurfaceVertical_Angle2XAxis) * (rounfBoxTipLen/2.f);
        float downView_AngleX = glm::atan(surfacePos_SelfAxis.z,surfacePos_SelfAxis.x);
        float verticalTipX = (current_radius_at_point + downView_TipExpand) * glm::cos(downView_AngleX);
        float verticalTipZ = (current_radius_at_point + downView_TipExpand) * glm::sin(downView_AngleX);
        verticalTip_SelfAxis = {verticalTipX,verticalTipY,verticalTipZ};
//    cout << "圆锥表面法线点 在自己系 点在(" << verticalTip_SelfAxis.x << ", " << verticalTip_SelfAxis.y <<
//         ", " << verticalTip_SelfAxis.z << ")" << endl;
    }else{
        verticalTip_SelfAxis = {surfacePos_SelfAxis.x,-rounfBoxTipLen/2.f,surfacePos_SelfAxis.z};
    }



}
void ConeDemo::drawVerticalTipByInfo(ScreenDemo* ScreenEye){
    glm::vec3 surfacePos_Screen = PosSelfAxis2ScreenAxis(surfacePos_SelfAxis);
    glm::vec3 surfacePointVerticalTip_Screen = PosSelfAxis2ScreenAxis(verticalTip_SelfAxis);

    surfacePos2D = __3d2dcone(ScreenEye,surfacePos_Screen.x,surfacePos_Screen.y,surfacePos_Screen.z);
    surfaceTipPos2D = __3d2dcone(ScreenEye,surfacePointVerticalTip_Screen.x,surfacePointVerticalTip_Screen.y,
                                 surfacePointVerticalTip_Screen.z);
    float _color[3] = {0.1803921568627451f,1.f,1.f};
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  surfacePos2D.x,surfacePos2D.y,
                                  surfaceTipPos2D.x,surfaceTipPos2D.y,
                                  _color,frameScreenNear);

}
void ConeDemo::setFrontColor(int color1, int color2){
    BGR3f colorNow1;
    colorNow1.setBGR(color1,1);
    frontColor1_rgb[0] = colorNow1.r1;
    frontColor1_rgb[1] = colorNow1.g1;
    frontColor1_rgb[2] = colorNow1.b1;

    BGR3f colorNow2;
    colorNow2.setBGR(color2,1);
    frontColor2_rgb[0] = colorNow2.r1;
    frontColor2_rgb[1] = colorNow2.g1;
    frontColor2_rgb[2] = colorNow2.b1;

}
void ConeDemo::setBackColor(int color){
    BGR3f colorNow;
    colorNow.setBGR(color,1);
    backColor_rgb[0] = colorNow.r1;
    backColor_rgb[1] = colorNow.g1;
    backColor_rgb[2] = colorNow.b1;

}
BGR3f ConeDemo::white2ColorfulScreenDeep(float pointDeep, char colorType){
    float deepBetween = frameScreenFar - frameScreenNear; // 两端深度差
    float B, G, R;
    if(colorType == 0){
        B = frontColor1_rgb[2] * 255.f;
        G = frontColor1_rgb[1] * 255.f;
        R = frontColor1_rgb[0] * 255.f; // 保留后两位
    }
    else{
        B = frontColor2_rgb[2] * 255.f;
        G = frontColor2_rgb[1] * 255.f;
        R = frontColor2_rgb[0] * 255.f; // 保留后两位
    }


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

//    int color = (int(nowB) << 16) + (int(nowG) << 8) + int(nowR);
//    color = (color & 0x00ffffff); // 最左一字节 0
    BGR3f resultColor;
    resultColor.setRGB3f(nowR / 255.f,nowG / 255.f, nowB / 255.f);

    return resultColor;
}
void ConeDemo::_solidBoxRect2D_front(ScreenDemo *ScreenEye, bool onFront) {
//    horizontalDeepCalc_front();
    // 默认 0 lb 1 rb 2 downCuspSet
    PolygonBase::fresh2D_scanRows_3(tblrdXY.lbSet,
                                    tblrdXY.rbSet,
                                    tblrdXY.downCuspSet, &lineScanFillColor_front,type_);

    pixelEyeDeep_front.clear(); // 去掉 包围盒 残留

    for(auto& _linePosInfo : lineScanFillColor_front){
        rowPixelDeep13 rowDeepInfo; // y  vec(x screenDeep_near screenDeep_far area inCirce)

        rowDeepInfo.y = _linePosInfo.y; // 本行 y
//        rowDeepInfo.pixelDeeps.clear(); // 本行 x deep 空
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){

            //float deepNow = getEyeDeepbyXY(nowX, _linePosInfo.y);

            pair<float,float> stepNow = getEyeThenStepByScreenXY({(float)nowX, (float)_linePosInfo.y});
            float deepNear = getZDeepByStep_ScreenAxis(stepNow.first,nowX, _linePosInfo.y);

//            if(deepNow < screenNear){
// //                cerr << "deepNow:" << deepNow << " screenNear:" << screenNear << endl;
//                deepNow = screenNear; // 防止深度溢出
//            }else if(deepNow > screenFar){
// //                cerr << "deepNow:" << deepNow << " screenFar:" << screenFar << endl;
//                deepNow = screenFar; // 防止深度溢出
//            }
            // deep z far 先不算了
            if(!isnan(deepNear)){
                if(getAreaByPos_selfAxis(SelfAxisInfo::pointNear) == 1){ // SelfAxisInfo::pointNear 有效才会刷新
                    rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),1,false});
                }else{
                    rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),2,false});
                }

                if(deepNear < frameScreenNear)frameScreenNear = deepNear;
                else if(deepNear > frameScreenFar)frameScreenFar = deepNear;
            }else{// 本行 x screenDeep_near screenDeep_far area inCirce
                rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),0,false});
            }
        }
        pixelEyeDeep_front.push_back(rowDeepInfo);
    }


    for(auto& _lineDeepInfo : pixelEyeDeep_front){
        for(int i=0; i < _lineDeepInfo.pixelDeeps.size()/*-1*/; i++){
            int nowX = _lineDeepInfo.pixelDeeps[i].x;
            float _deepNear = _lineDeepInfo.pixelDeeps[i].screenDeep_near;

            if(isnan(_deepNear) == false){ // 扫包围盒面 没扫偏 没扫过高过低
                if(onFront){
                    //cout << "debugLine" << (int)debugLine << endl;
                    float _color_[3];
                            if(debugLine==1) {
                                BGR3f colorNow1;
                                if(_lineDeepInfo.pixelDeeps[i].area == 1)
                                {colorNow1= white2ColorfulScreenDeep(_deepNear,0);}
                                else if(_lineDeepInfo.pixelDeeps[i].area == 2)
                                {colorNow1= white2ColorfulScreenDeep(_deepNear,1);}

                                float _color_[3] = {colorNow1.r1,colorNow1.g1,colorNow1.b1};
                                ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                                    _deepNear, (PolygonBase*)this);

                            }else{

                                if(_lineDeepInfo.pixelDeeps[i].area == 1){
                                    _color_[0]= frontColor1_rgb[0];
                                    _color_[1]= frontColor1_rgb[1];
                                    _color_[2]= frontColor1_rgb[2];
//                                    glColor3f(frontColor1_rgb[0], frontColor1_rgb[1], frontColor1_rgb[2]);
                                }
                                else if(_lineDeepInfo.pixelDeeps[i].area == 2){
                                    _color_[0]= frontColor2_rgb[0];
                                    _color_[1]= frontColor2_rgb[1];
                                    _color_[2]= frontColor2_rgb[2];
//                                    glColor3f(frontColor2_rgb[0], frontColor2_rgb[1], frontColor2_rgb[2]);
                                }

                                ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                                    _deepNear, (PolygonBase*)this);


//                    cout << "put pixel (" << nowX << "," << _lineDeepInfo.y << ")" << endl;

                            }
                }
                else{
                    float _color_[3] = {backColor_rgb[0],backColor_rgb[1],backColor_rgb[2]};
                    ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                        _deepNear, (PolygonBase*)this);


                }
            }

        }
    }

}
void ConeDemo::_solidBoxRect2D_left(ScreenDemo* ScreenEye, bool onFront){

//    horizontalDeepCalc_left();
    // 默认 0 lt 1 lb 2 downCuspSet
    PolygonBase::fresh2D_scanRows_3(tblrdXY.ltSet,
                                    tblrdXY.lbSet,
                                    tblrdXY.downCuspSet, &lineScanFillColor_left,type_);
    pixelEyeDeep_left.clear();

    for(auto& _linePosInfo : lineScanFillColor_left){
        rowPixelDeep13 rowDeepInfo; // y  vec(x screenDeep_near screenDeep_far area inCirce)

        rowDeepInfo.y = _linePosInfo.y; // 本行 y
//        rowDeepInfo.pixelDeeps.clear(); // 本行 x deep 空
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){

            //float deepNow = getEyeDeepbyXY(nowX, _linePosInfo.y);

            pair<float,float> stepNow = getEyeThenStepByScreenXY({(float)nowX, (float)_linePosInfo.y});
            float deepNear = getZDeepByStep_ScreenAxis(stepNow.first,nowX, _linePosInfo.y);

//            if(deepNow < screenNear){
// //                cerr << "deepNow:" << deepNow << " screenNear:" << screenNear << endl;
//                deepNow = screenNear; // 防止深度溢出
//            }else if(deepNow > screenFar){
// //                cerr << "deepNow:" << deepNow << " screenFar:" << screenFar << endl;
//                deepNow = screenFar; // 防止深度溢出
//            }
            // deep z far 先不算了
            if(!isnan(deepNear)){
                if(getAreaByPos_selfAxis(SelfAxisInfo::pointNear) == 1){ // SelfAxisInfo::pointNear 有效才会刷新
                    rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),1,false});
                }else{
                    rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),2,false});
                }
                if(deepNear < frameScreenNear)frameScreenNear = deepNear;
                else if(deepNear > frameScreenFar)frameScreenFar = deepNear;
            }else{// 本行 x screenDeep_near screenDeep_far area inCirce
                rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),0,false});
            }
        }
        pixelEyeDeep_left.push_back(rowDeepInfo);
    }


    for(auto& _lineDeepInfo : pixelEyeDeep_left){
        for(int i=0; i < _lineDeepInfo.pixelDeeps.size()/*-1*/; i++){
            int nowX = _lineDeepInfo.pixelDeeps[i].x;
            float _deepNear = _lineDeepInfo.pixelDeeps[i].screenDeep_near;

            if(isnan(_deepNear) == false){ // 扫包围盒面 没扫偏 没扫过高过低
                if(onFront){
                    //cout << "debugLine" << (int)debugLine << endl;
                    if(debugLine==1) {

                        BGR3f colorNow1;
                        if(_lineDeepInfo.pixelDeeps[i].area == 1)
                        {colorNow1= white2ColorfulScreenDeep(_deepNear,0);}
                        else if(_lineDeepInfo.pixelDeeps[i].area == 2)
                        {colorNow1= white2ColorfulScreenDeep(_deepNear,1);}

                        float _color_[3] = {colorNow1.r1,colorNow1.g1,colorNow1.b1};
                        ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                            _deepNear, (PolygonBase*)this);

                    }else{

                        float _color_[3];
                        if(_lineDeepInfo.pixelDeeps[i].area == 1){
                            _color_[0]= frontColor1_rgb[0];
                            _color_[1]= frontColor1_rgb[1];
                            _color_[2]= frontColor1_rgb[2];


                        }
                        else if(_lineDeepInfo.pixelDeeps[i].area == 2){
                            _color_[0]= frontColor2_rgb[0];
                            _color_[1]= frontColor2_rgb[1];
                            _color_[2]= frontColor2_rgb[2];

                        }

                        ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                            _deepNear, (PolygonBase*)this);


//                    cout << "put pixel (" << nowX << "," << _lineDeepInfo.y << ")" << endl;

                        }
                }
                else{
                    float _color_[3] = {backColor_rgb[0],backColor_rgb[1],backColor_rgb[2]};
                    ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                        _deepNear, (PolygonBase*)this);


                }
            }

        }
    }

}
void ConeDemo::_solidBoxRect2D_right(ScreenDemo* ScreenEye, bool onFront){

//    horizontalDeepCalc_right();
    // 默认 0 rb 1 rt 2 downCuspSet
    PolygonBase::fresh2D_scanRows_3(tblrdXY.rbSet,
                                    tblrdXY.rtSet,
                                    tblrdXY.downCuspSet, &lineScanFillColor_right,type_);
    pixelEyeDeep_right.clear();

    for(auto& _linePosInfo : lineScanFillColor_right){
        rowPixelDeep13 rowDeepInfo; // y  vec(x screenDeep_near screenDeep_far area inCirce)

        rowDeepInfo.y = _linePosInfo.y; // 本行 y
//        rowDeepInfo.pixelDeeps.clear(); // 本行 x deep 空
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){

            //float deepNow = getEyeDeepbyXY(nowX, _linePosInfo.y);

            pair<float,float> stepNow = getEyeThenStepByScreenXY({(float)nowX, (float)_linePosInfo.y});
            float deepNear = getZDeepByStep_ScreenAxis(stepNow.first,nowX, _linePosInfo.y);

//            if(deepNow < screenNear){
// //                cerr << "deepNow:" << deepNow << " screenNear:" << screenNear << endl;
//                deepNow = screenNear; // 防止深度溢出
//            }else if(deepNow > screenFar){
// //                cerr << "deepNow:" << deepNow << " screenFar:" << screenFar << endl;
//                deepNow = screenFar; // 防止深度溢出
//            }
            // deep z far 先不算了
            if(!isnan(deepNear)){
                if(getAreaByPos_selfAxis(SelfAxisInfo::pointNear) == 1){ // SelfAxisInfo::pointNear 有效才会刷新
                    rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),1,false});
                }else{
                    rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),2,false});
                }
                if(deepNear < frameScreenNear)frameScreenNear = deepNear;
                else if(deepNear > frameScreenFar)frameScreenFar = deepNear;
            }else{// 本行 x screenDeep_near screenDeep_far area inCirce
                rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),0,false});
            }
        }
        pixelEyeDeep_right.push_back(rowDeepInfo);
    }

//    glPointSize(1.0f);
//    glBegin(GL_POINTS);
    for(auto& _lineDeepInfo : pixelEyeDeep_right){
        for(int i=0; i < _lineDeepInfo.pixelDeeps.size()/*-1*/; i++){
            int nowX = _lineDeepInfo.pixelDeeps[i].x;
            float _deepNear = _lineDeepInfo.pixelDeeps[i].screenDeep_near;

            if(!isnan(_deepNear)){ // 扫包围盒面 没扫偏 没扫过高过低
                if(onFront){
                    //cout << "debugLine" << (int)debugLine << endl;
                        float _color_[3];
                        if(debugLine==1) {
                            BGR3f colorNow1;
                            if(_lineDeepInfo.pixelDeeps[i].area == 1)
                            {colorNow1= white2ColorfulScreenDeep(_deepNear,0);}
                            else if(_lineDeepInfo.pixelDeeps[i].area == 2)
                            {colorNow1= white2ColorfulScreenDeep(_deepNear,1);}

                            _color_[0]= colorNow1.r1;
                            _color_[1]= colorNow1.g1;
                            _color_[2]= colorNow1.b1;
                            ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                                _deepNear, (PolygonBase*)this);
//                            glColor3f(colorNow1.r1,colorNow1.g1,colorNow1.b1);
//                            glVertex2f(nowX,_lineDeepInfo.y);
                        }else{


                            if(_lineDeepInfo.pixelDeeps[i].area == 1){
                                _color_[0]= frontColor1_rgb[0];
                                _color_[1]= frontColor1_rgb[1];
                                _color_[2]= frontColor1_rgb[2];
//                                glColor3f(frontColor1_rgb[0], frontColor1_rgb[1], frontColor1_rgb[2]);
                            }
                            else if(_lineDeepInfo.pixelDeeps[i].area == 2){
                                _color_[0]= frontColor2_rgb[0];
                                _color_[1]= frontColor2_rgb[1];
                                _color_[2]= frontColor2_rgb[2];
//                                glColor3f(frontColor2_rgb[0], frontColor2_rgb[1], frontColor2_rgb[2]);
                            }
                            ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                                _deepNear, (PolygonBase*)this);
//                    glVertex2f(nowX, _lineDeepInfo.y);

//                    cout << "put pixel (" << nowX << "," << _lineDeepInfo.y << ")" << endl;

                                    }
                }
                else{
                    float _color_[3] = {backColor_rgb[0],backColor_rgb[1],backColor_rgb[2]};
                    ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                        _deepNear, (PolygonBase*)this);
//                    glColor3f(backColor_rgb[0],backColor_rgb[1],backColor_rgb[2]);
//                    glVertex2f(nowX, _lineDeepInfo.y);

                }
            }

        }
    }
//    glEnd();
}
void ConeDemo::_solidBoxRect2D_back(ScreenDemo* ScreenEye, bool onFront){

//    horizontalDeepCalc_back();
    // 默认 0 rt 1 lt 2 downCuspSet
    PolygonBase::fresh2D_scanRows_3(tblrdXY.rtSet,
                                    tblrdXY.ltSet,
                                    tblrdXY.downCuspSet, &lineScanFillColor_back,type_);
    pixelEyeDeep_back.clear();

    for(auto& _linePosInfo : lineScanFillColor_back){
        rowPixelDeep13 rowDeepInfo; // y  vec(x screenDeep_near screenDeep_far area inCirce)

        rowDeepInfo.y = _linePosInfo.y; // 本行 y
//        rowDeepInfo.pixelDeeps.clear(); // 本行 x deep 空
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){

            //float deepNow = getEyeDeepbyXY(nowX, _linePosInfo.y);

            pair<float,float> stepNow = getEyeThenStepByScreenXY({(float)nowX, (float)_linePosInfo.y});
            float deepNear = getZDeepByStep_ScreenAxis(stepNow.first,nowX, _linePosInfo.y);

//            if(deepNow < screenNear){
// //                cerr << "deepNow:" << deepNow << " screenNear:" << screenNear << endl;
//                deepNow = screenNear; // 防止深度溢出
//            }else if(deepNow > screenFar){
// //                cerr << "deepNow:" << deepNow << " screenFar:" << screenFar << endl;
//                deepNow = screenFar; // 防止深度溢出
//            }
            // deep z far 先不算了
            if(!isnan(deepNear)){
                if(getAreaByPos_selfAxis(SelfAxisInfo::pointNear) == 1){ // SelfAxisInfo::pointNear 有效才会刷新
                    rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),1,false});
                }else{
                    rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),2,false});
                }
                if(deepNear < frameScreenNear)frameScreenNear = deepNear;
                else if(deepNear > frameScreenFar)frameScreenFar = deepNear;
            }else{// 本行 x screenDeep_near screenDeep_far area inCirce
                rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),0,false});
            }

        }
        pixelEyeDeep_back.push_back(rowDeepInfo);
    }

//    glPointSize(1.0f);
//    glBegin(GL_POINTS);
    for(auto& _lineDeepInfo : pixelEyeDeep_back){
        for(int i=0; i < _lineDeepInfo.pixelDeeps.size()/*-1*/; i++){
            int nowX = _lineDeepInfo.pixelDeeps[i].x;
            float _deepNear = _lineDeepInfo.pixelDeeps[i].screenDeep_near;

            if(isnan(_deepNear) == false){ // 扫包围盒面 没扫偏 没扫过高过低
                if(onFront){
                    //cout << "debugLine" << (int)debugLine << endl;
                    float _color_[3];
                        if(debugLine==1) {
                            BGR3f colorNow1;
                            if(_lineDeepInfo.pixelDeeps[i].area == 1)
                            {colorNow1= white2ColorfulScreenDeep(_deepNear,0);}
                            else if(_lineDeepInfo.pixelDeeps[i].area == 2)
                            {colorNow1= white2ColorfulScreenDeep(_deepNear,1);}

                            _color_[0]= colorNow1.r1;
                            _color_[1]= colorNow1.g1;
                            _color_[2]= colorNow1.b1;
                            ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                                _deepNear, (PolygonBase*)this);

//                            glColor3f(colorNow1.r1,colorNow1.g1,colorNow1.b1);
//                            glVertex2f(nowX, _lineDeepInfo.y);


                        }else{

                            if(_lineDeepInfo.pixelDeeps[i].area == 1){
                                _color_[0]= frontColor1_rgb[0];
                                _color_[1]= frontColor1_rgb[1];
                                _color_[2]= frontColor1_rgb[2];
//                                glColor3f(frontColor1_rgb[0], frontColor1_rgb[1], frontColor1_rgb[2]);
                            }
                            else if(_lineDeepInfo.pixelDeeps[i].area == 2){
                                _color_[0]= frontColor2_rgb[0];
                                _color_[1]= frontColor2_rgb[1];
                                _color_[2]= frontColor2_rgb[2];
//                                glColor3f(frontColor2_rgb[0], frontColor2_rgb[1], frontColor2_rgb[2]);
                            }
                            ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                                _deepNear, (PolygonBase*)this);
//                    glVertex2f(nowX, _lineDeepInfo.y);

//                    cout << "put pixel (" << nowX << "," << _lineDeepInfo.y << ")" << endl;

                                    }
                }
                else{
                    float _color_[3] = {backColor_rgb[0],backColor_rgb[1],backColor_rgb[2]};
                    ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                        _deepNear, (PolygonBase*)this);
//                    glColor3f(backColor_rgb[0],backColor_rgb[1],backColor_rgb[2]);
//                    glVertex2f(nowX, _lineDeepInfo.y);

                }
            }

        }
    }
//    glEnd();
}
void ConeDemo::_solidBoxRect2D_top(ScreenDemo* ScreenEye, bool onFront){
    // 改 horizontalDeepCalc_top pixelEyeDeep_top lineScanFillColor_top
//    horizontalDeepCalc_top();
    // 默认 0 lt 1 rt 2 rb 3 lb
    PolygonBase::fresh2D_scanRows_4(tblrdXY.ltSet,
                                    tblrdXY.rtSet,
                                    tblrdXY.rbSet,
                                    tblrdXY.lbSet, &lineScanFillColor_top,type_);
    pixelEyeDeep_top.clear();

    for(auto& _linePosInfo : lineScanFillColor_top){
        rowPixelDeep13 rowDeepInfo; // y  vec(x screenDeep_near screenDeep_far area inCirce)

        rowDeepInfo.y = _linePosInfo.y; // 本行 y
//        rowDeepInfo.pixelDeeps.clear(); // 本行 x deep 空
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){

            //float deepNow = getEyeDeepbyXY(nowX, _linePosInfo.y);
            float stepOfTopFlat = getEyeThenStepOfFlatByScreenXY(glm::vec2{(float)nowX, (float)_linePosInfo.y});
            if(!isnan(stepOfTopFlat)){ // top面 圆内
                float deepNear_ = getZDeepByStep_ScreenAxis(stepOfTopFlat,(float)nowX, (float)_linePosInfo.y);
//                cout << "视点 距离 :" << stepOfTopFlat << endl;
//                cout << "圆锥 圆面 视线射中坐标 (" << SelfAxisInfo::pointNear.x <<
//                ", " << SelfAxisInfo::pointNear.y << ", " << SelfAxisInfo::pointNear.z << ")" << endl;

                if(SelfAxisInfo::pointNear.x > 0) // 圆面 分 双色
                rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear_,std::nanf(""),2,true});
                else rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear_,std::nanf(""),1,true});

                if(deepNear_ < frameScreenNear)frameScreenNear = deepNear_;
                else if(deepNear_ > frameScreenFar)frameScreenFar = deepNear_;

                continue;
            }

            pair<float,float> stepNow = getEyeThenStepByScreenXY(glm::vec2{(float)nowX, (float)_linePosInfo.y},true);
            float deepNear = getZDeepByStep_ScreenAxis(stepNow.first,nowX, _linePosInfo.y);

//            if(deepNow < screenNear){
// //                cerr << "deepNow:" << deepNow << " screenNear:" << screenNear << endl;
//                deepNow = screenNear; // 防止深度溢出
//            }else if(deepNow > screenFar){
// //                cerr << "deepNow:" << deepNow << " screenFar:" << screenFar << endl;
//                deepNow = screenFar; // 防止深度溢出
//            }
            // deep z far 先不算了
            if(!isnan(deepNear)){
                if(getAreaByPos_selfAxis(SelfAxisInfo::pointNear) == 1){ // SelfAxisInfo::pointNear 有效才会刷新
                    rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),1,false});
                }else{
                    rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),2,false});
                }
                if(deepNear < frameScreenNear)frameScreenNear = deepNear;
                else if(deepNear > frameScreenFar)frameScreenFar = deepNear;
            }else{// 本行 x screenDeep_near screenDeep_far area inCirce
                rowDeepInfo.pixelDeeps.push_back(pixelDeep13{nowX, deepNear,std::nanf(""),0,false});
            }

        }
        pixelEyeDeep_top.push_back(rowDeepInfo);
    }

//    glPointSize(1.0f);
//    glBegin(GL_POINTS);
    for(auto& _lineDeepInfo : pixelEyeDeep_top){
        for(int i=0; i < _lineDeepInfo.pixelDeeps.size()/*-1*/; i++){
            int nowX = _lineDeepInfo.pixelDeeps[i].x;
            float _deepNear = _lineDeepInfo.pixelDeeps[i].screenDeep_near;

            if(isnan(_deepNear) == false){ // 扫包围盒面 没扫偏 没扫过高过低
                if(onFront){
                    //cout << "debugLine" << (int)debugLine << endl;
                    float _color_[3];
                    if(debugLine==1) {
                        BGR3f colorNow1;
                        if(_lineDeepInfo.pixelDeeps[i].area == 1)
                        {colorNow1= white2ColorfulScreenDeep(_deepNear,0);}
                        else if(_lineDeepInfo.pixelDeeps[i].area == 2)
                        {colorNow1= white2ColorfulScreenDeep(_deepNear,1);}

                        _color_[0]= colorNow1.r1;
                        _color_[1]= colorNow1.g1;
                        _color_[2]= colorNow1.b1;
                        ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                            _deepNear, (PolygonBase*)this);

//                        glColor3f(colorNow1.r1,colorNow1.g1,colorNow1.b1);
//                        glVertex2f(nowX, _lineDeepInfo.y);
                    }else{

                        if(_lineDeepInfo.pixelDeeps[i].area == 1){
                            _color_[0]= frontColor1_rgb[0];
                            _color_[1]= frontColor1_rgb[1];
                            _color_[2]= frontColor1_rgb[2];
//                            glColor3f(frontColor1_rgb[0], frontColor1_rgb[1], frontColor1_rgb[2]);
                        }
                        else if(_lineDeepInfo.pixelDeeps[i].area == 2){
                            _color_[0]= frontColor2_rgb[0];
                            _color_[1]= frontColor2_rgb[1];
                            _color_[2]= frontColor2_rgb[2];
//                            glColor3f(frontColor2_rgb[0], frontColor2_rgb[1], frontColor2_rgb[2]);
                        }
                        ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                            _deepNear, (PolygonBase*)this);
//                    glVertex2f(nowX, _lineDeepInfo.y);

//                    cout << "put pixel (" << nowX << "," << _lineDeepInfo.y << ")" << endl;

                                    }
                }
                else{
                    float _color_[3] = {backColor_rgb[0],backColor_rgb[1],backColor_rgb[2]};
                    ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_,
                                        _deepNear, (PolygonBase*)this);
//                    glColor3f(backColor_rgb[0],backColor_rgb[1],backColor_rgb[2]);
//                    glVertex2f(nowX, _lineDeepInfo.y);

                }
            }

        }
    }
//    glEnd();
}

float ConeDemo::getZDeepByStep_ScreenAxis(float _step, float x, float y){

    glm::vec3 screenPoint = {x,y,0.f};
    float sightLineLength = glm::distance(startEye, screenPoint);
    float dz = (screenPoint.z - startEye.z) / sightLineLength; // 0 - (-1000) = 1000
    return startEye.z + _step * dz;
}
char ConeDemo::getAreaByPos_selfAxis(glm::vec3 _pos){
    if(_pos.x > 0.f && _pos.y > 0.f && _pos.y <= height_1_3){
        return 1;
    }
    if(_pos.x < 0.f && _pos.y > height_1_3 && _pos.y <= height_2_3){
        return 1;
    }
    if(_pos.x > 0.f && _pos.y > height_2_3 && _pos.y <= height){
        return 1;
    }
    return 2;
}
void ConeDemo::freshCircleAxis(){

    freshGoX();freshGoY();freshGoDEEP();

    freshTiltAxis(); // 刷新 倾斜轴
    freshParallelAxis(); // 刷新 平行轴
}
void ConeDemo::drawConeAxis(ScreenDemo *ScreenEye) {
    if(debugLine != 2)return;
    drawTiltAxis(ScreenEye); // 画倾斜轴
    drawParallelAxis(ScreenEye); // 画平行轴
}
glm::vec3 ConeDemo::PosSelfAxis2ScreenAxis(glm::vec3 p1){
    glm::vec3 _then;
    _then = virtual_goX(virtual_tblrdXYZ.center,p1.x);
    _then = virtual_goY(_then,p1.y);
    _then = virtual_goDEEP(_then,p1.z);
    return _then;
}
void ConeDemo::freshGoX(){
    world_toX.dx = (tblrdXYZ.rtSet.x - tblrdXYZ.ltSet.x) / squareEdge;
    world_toX.dy = (tblrdXYZ.rtSet.y - tblrdXYZ.ltSet.y) / squareEdge;
    world_toX.dz = (tblrdXYZ.rtSet.z - tblrdXYZ.ltSet.z) / squareEdge;
}
void ConeDemo::freshGoY(){
    world_toY.dx = (tblrdXYZ.downCuspSet.x - tblrdXYZ.center.x) / height;
    world_toY.dy = (tblrdXYZ.downCuspSet.y - tblrdXYZ.center.y) / height;
    world_toY.dz = (tblrdXYZ.downCuspSet.z - tblrdXYZ.center.z) / height;
}
void ConeDemo::freshGoDEEP() {
    world_toDEEP.dx = (tblrdXYZ.ltSet.x - tblrdXYZ.lbSet.x) / squareEdge;
    world_toDEEP.dy = (tblrdXYZ.ltSet.y - tblrdXYZ.lbSet.y) / squareEdge;
    world_toDEEP.dz = (tblrdXYZ.ltSet.z - tblrdXYZ.lbSet.z) / squareEdge;
}
glm::vec3 ConeDemo::goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * world_toX.dx;
    _srcXYZ.y = _srcXYZ.y + _move * world_toX.dy;
    _srcXYZ.z = _srcXYZ.z + _move * world_toX.dz;
    return _srcXYZ;
}
glm::vec3 ConeDemo::goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * world_toY.dx;
    _srcXYZ.y = _srcXYZ.y + _move * world_toY.dy;
    _srcXYZ.z = _srcXYZ.z + _move * world_toY.dz;
    return _srcXYZ;
}
glm::vec3 ConeDemo::goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * world_toDEEP.dx;
    _srcXYZ.y = _srcXYZ.y + _move * world_toDEEP.dy;
    _srcXYZ.z = _srcXYZ.z + _move * world_toDEEP.dz;
    return _srcXYZ;
}
void ConeDemo::freshTiltAxis(){
    // 中
    tiltAxis3D[0] = tblrdXYZ.center;
    // x轴
    tiltAxis3D[1].x = tblrdXYZ.center.x + world_toX.dx * squareEdge; // 数轴长度 看宽
    tiltAxis3D[1].y = tblrdXYZ.center.y + world_toX.dy * squareEdge;
    tiltAxis3D[1].z = tblrdXYZ.center.z + world_toX.dz * squareEdge;
    // y轴
    tiltAxis3D[2].x = tblrdXYZ.center.x + world_toY.dx * squareEdge;
    tiltAxis3D[2].y = tblrdXYZ.center.y + world_toY.dy * squareEdge;
    tiltAxis3D[2].z = tblrdXYZ.center.z + world_toY.dz * squareEdge;
    // z轴
    tiltAxis3D[3].x = tblrdXYZ.center.x + world_toDEEP.dx * squareEdge;
    tiltAxis3D[3].y = tblrdXYZ.center.y + world_toDEEP.dy * squareEdge;
    tiltAxis3D[3].z = tblrdXYZ.center.z + world_toDEEP.dz * squareEdge;
}

void ConeDemo::freshParallelAxis(){
    // 中
    parallelAxis3D[0] = tblrdXYZ.center;
    // x轴
    parallelAxis3D[1].x = tblrdXYZ.center.x + squareEdge; // 数轴长度 看宽
    parallelAxis3D[1].y = tblrdXYZ.center.y;
    parallelAxis3D[1].z = tblrdXYZ.center.z;
    // y轴
    parallelAxis3D[2].x = tblrdXYZ.center.x;
    parallelAxis3D[2].y = tblrdXYZ.center.y + squareEdge;
    parallelAxis3D[2].z = tblrdXYZ.center.z;
    // z轴
    parallelAxis3D[3].x = tblrdXYZ.center.x;
    parallelAxis3D[3].y = tblrdXYZ.center.y;
    parallelAxis3D[3].z = tblrdXYZ.center.z + squareEdge;
}

void ConeDemo::drawTiltAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴  世界系 屏幕系 3D→2D
    tiltAxis2D_f[0] = __3d2dGocone(ScreenEye, tiltAxis3D[0], nullptr);
    tiltAxis2D_f[1] = __3d2dGocone(ScreenEye, tiltAxis3D[1], nullptr);
    tiltAxis2D_f[2] = __3d2dGocone(ScreenEye, tiltAxis3D[2], nullptr);
    tiltAxis2D_f[3] = __3d2dGocone(ScreenEye, tiltAxis3D[3], nullptr);


//    BGR3f _green;
    //(0.3843137254901961,0.6313725490196078,0.12549019607843137)
//    _green.setBGR(0x62a120,1);// 翠绿
//    BGR3f _blue;
    //(0.7254901960784313,0.5647058823529412,0.1843137254901961)
//    _blue.setBGR(0xb9902f,1);// 云山蓝
//    BGR3f _yellow;
    //(0.054901960784313725,0.6431372549019608,0.8509803921568627)
//    _yellow.setBGR(0x0ea4d9,1);// 芥黄
    float _color[3];
    _color[0]=0.12549019607843137;_color[1]=0.6313725490196078;_color[2]=0.3843137254901961;
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[1].x,tiltAxis2D_f[1].y,
                                  _color,frameScreenNear);
    _color[0]=0.1843137254901961;_color[1]=0.5647058823529412;_color[2]=0.7254901960784313;
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[2].x,tiltAxis2D_f[2].y,
                                  _color,frameScreenNear);
    _color[0]=0.8509803921568627;_color[1]=0.6431372549019608;_color[2]=0.054901960784313725;
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[3].x,tiltAxis2D_f[3].y,
                                  _color,frameScreenNear);
//    glLineWidth(1.0f); // 线宽
//    glBegin(GL_LINES);
//
//    glColor3f(0.12549019607843137,0.6313725490196078,0.3843137254901961);
//    glVertex2f(tiltAxis2D_f[0].x,tiltAxis2D_f[0].y);
//    glVertex2f(tiltAxis2D_f[1].x,tiltAxis2D_f[1].y);
//
//    glColor3f(0.1843137254901961,0.5647058823529412,0.7254901960784313);
//    glVertex2f(tiltAxis2D_f[0].x,tiltAxis2D_f[0].y);
//    glVertex2f(tiltAxis2D_f[2].x,tiltAxis2D_f[2].y);
//
//    glColor3f(0.8509803921568627,0.6431372549019608,0.054901960784313725);
//    glVertex2f(tiltAxis2D_f[0].x,tiltAxis2D_f[0].y);
//    glVertex2f(tiltAxis2D_f[3].x,tiltAxis2D_f[3].y);
//    glEnd();
}

void ConeDemo::drawParallelAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴
    parallelAxis2D_f[0] = __3d2dGocone(ScreenEye, parallelAxis3D[0], nullptr);
    parallelAxis2D_f[1] = __3d2dGocone(ScreenEye, parallelAxis3D[1], nullptr);
    parallelAxis2D_f[2] = __3d2dGocone(ScreenEye, parallelAxis3D[2], nullptr);
    parallelAxis2D_f[3] = __3d2dGocone(ScreenEye, parallelAxis3D[3], nullptr);
//    setlinecolor(WHITE); // 回 白色###
//    line((int)roundf(parallelAxis2D_f[0].x), (int)roundf(parallelAxis2D_f[0].y),
//         (int)roundf(parallelAxis2D_f[1].x), (int)roundf(parallelAxis2D_f[1].y)); // x轴
//    line((int)roundf(parallelAxis2D_f[0].x), (int)roundf(parallelAxis2D_f[0].y),
//         (int)roundf(parallelAxis2D_f[2].x), (int)roundf(parallelAxis2D_f[2].y)); // y轴
//    line((int)roundf(parallelAxis2D_f[0].x), (int)roundf(parallelAxis2D_f[0].y),
//         (int)roundf(parallelAxis2D_f[3].x), (int)roundf(parallelAxis2D_f[3].y)); // z轴
    float _color[3] = {1.f, 1.f, 1.f};
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  parallelAxis2D_f[0].x,parallelAxis2D_f[0].y,
                                  parallelAxis2D_f[1].x,parallelAxis2D_f[1].y,
                                  _color,frameScreenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  parallelAxis2D_f[0].x,parallelAxis2D_f[0].y,
                                  parallelAxis2D_f[2].x,parallelAxis2D_f[2].y,
                                  _color,frameScreenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  parallelAxis2D_f[0].x,parallelAxis2D_f[0].y,
                                  parallelAxis2D_f[3].x,parallelAxis2D_f[3].y,
                                  _color,frameScreenNear);
//    glLineWidth(1.0f); // 线宽
//    glBegin(GL_LINES);
//
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

void ConeDemo::freshVirtualGoX() {
    virtual_toX.dx = (virtual_tblrdXYZ.rtSet.x - virtual_tblrdXYZ.ltSet.x) / squareEdge;
    virtual_toX.dy = (virtual_tblrdXYZ.rtSet.y - virtual_tblrdXYZ.ltSet.y) / squareEdge;
    virtual_toX.dz = (virtual_tblrdXYZ.rtSet.z - virtual_tblrdXYZ.ltSet.z) / squareEdge;
}

void ConeDemo::freshVirtualGoY() {
    virtual_toY.dx = (virtual_tblrdXYZ.downCuspSet.x - virtual_tblrdXYZ.center.x) / height;
    virtual_toY.dy = (virtual_tblrdXYZ.downCuspSet.y - virtual_tblrdXYZ.center.y) / height;
    virtual_toY.dz = (virtual_tblrdXYZ.downCuspSet.z - virtual_tblrdXYZ.center.z) / height;
}

void ConeDemo::freshVirtualGoDEEP() {
    virtual_toDEEP.dx = (virtual_tblrdXYZ.ltSet.x - virtual_tblrdXYZ.lbSet.x) / squareEdge;
    virtual_toDEEP.dy = (virtual_tblrdXYZ.ltSet.y - virtual_tblrdXYZ.lbSet.y) / squareEdge;
    virtual_toDEEP.dz = (virtual_tblrdXYZ.ltSet.z - virtual_tblrdXYZ.lbSet.z) / squareEdge;
}
glm::vec3 ConeDemo::virtual_goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * virtual_toX.dx;
    _srcXYZ.y = _srcXYZ.y + _move * virtual_toX.dy;
    _srcXYZ.z = _srcXYZ.z + _move * virtual_toX.dz;
    return _srcXYZ;
}

glm::vec3 ConeDemo::virtual_goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * virtual_toY.dx;
    _srcXYZ.y = _srcXYZ.y + _move * virtual_toY.dy;
    _srcXYZ.z = _srcXYZ.z + _move * virtual_toY.dz;
    return _srcXYZ;
}
glm::vec3 ConeDemo::virtual_goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * virtual_toDEEP.dx;
    _srcXYZ.y = _srcXYZ.y + _move * virtual_toDEEP.dy;
    _srcXYZ.z = _srcXYZ.z + _move * virtual_toDEEP.dz;
    return _srcXYZ;
}
void ConeDemo::freshVirtualFlatXY() {
    float normal[4] = {0};

    // xy面 垂z
    normal[0] = virtual_toDEEP.dx;
    normal[1] = virtual_toDEEP.dy;
    normal[2] = virtual_toDEEP.dz; // 法向量 取反 ?


    // ax + by + cz + d = 0
    // d = -a*x1 - b*y1 - c*z1
    normal[3] = -normal[0] * virtual_tblrdXYZ.center.x - normal[1] * virtual_tblrdXYZ.center.y - normal[2] * virtual_tblrdXYZ.center.z;

    // ax + by + cz + d = 0

    virtual_a_b_c_d_XY[0] = normal[0];
    virtual_a_b_c_d_XY[1] = normal[1];
    virtual_a_b_c_d_XY[2] = normal[2];
    virtual_a_b_c_d_XY[3] = normal[3];
}

void ConeDemo::freshVirtualFlatXZ() {
    float normal[4] = {0};

    // xz面 垂y
    normal[0] = virtual_toY.dx;
    normal[1] = virtual_toY.dy;
    normal[2] = virtual_toY.dz; // 法向量 俯视
    normal[3] = -normal[0] * virtual_tblrdXYZ.center.x - normal[1] * virtual_tblrdXYZ.center.y -
                normal[2] * virtual_tblrdXYZ.center.z; // 代入中心
    virtual_a_b_c_d_XZ[0] = normal[0];
    virtual_a_b_c_d_XZ[1] = normal[1];
    virtual_a_b_c_d_XZ[2] = normal[2];
    virtual_a_b_c_d_XZ[3] = normal[3];
}

void ConeDemo::freshVirtualFlatYZ() {
    float normal[4] = {0};

    // yz面 垂x
    normal[0] = virtual_toX.dx;
    normal[1] = virtual_toX.dy;
    normal[2] = virtual_toX.dz; // 法向量 左视
    normal[3] = -normal[0] * virtual_tblrdXYZ.center.x - normal[1] * virtual_tblrdXYZ.center.y -
                normal[2] * virtual_tblrdXYZ.center.z; // 代入中心
    virtual_a_b_c_d_YZ[0] = normal[0];
    virtual_a_b_c_d_YZ[1] = normal[1];
    virtual_a_b_c_d_YZ[2] = normal[2];
    virtual_a_b_c_d_YZ[3] = normal[3];

}

float ConeDemo::virtual_Point2FlatYZ(glm::vec3& _point) {


    float a = virtual_a_b_c_d_YZ[0]; // yz面 垂x
    float b = virtual_a_b_c_d_YZ[1];
    float c = virtual_a_b_c_d_YZ[2];
    float d = virtual_a_b_c_d_YZ[3];



    float step, step_up, step_down;
    step_up = -a*_point.x - b*_point.y - c*_point.z - d;
//    if(std::isnan(step_up)){
//        cerr << "step_up is nan" << endl;
//    }
#ifdef MAYBE_UNUSED
    [[maybe_unused]]goLine32 goBackX = {-a, -b, -c};
//    step_down = a*goBackX.dx + b*goBackX.dy + c*goBackX.dz;
#endif
    step_down = -1.f;// 反法线 分母1


//    if(fabs(step_down + 1.0f) > 1e-6){
//        cerr << "step_down + 1 = " << fabs(step_down + 1.0f) << " > 1e-6" << endl;
//    }; // 验证归一化正确性


    step = step_up / step_down;
    return step;

}

float ConeDemo::virtual_Point2FlatXZ(glm::vec3 &_point) {


    float a = virtual_a_b_c_d_XZ[0]; // xz面 垂y
    float b = virtual_a_b_c_d_XZ[1];
    float c = virtual_a_b_c_d_XZ[2];
    float d = virtual_a_b_c_d_XZ[3];
#ifdef MAYBE_UNUSED
    [[maybe_unused]]goLine32 goBackY = {-a, -b, -c};
#endif
    float step, step_up, step_down;
    step_up = -a*_point.x - b*_point.y - c*_point.z - d;
//    if(std::isnan(step_up)){
//        cerr << "step_up is nan" << endl;
//    }

    step_down = -1.f;//a*goBackY.dx + b*goBackY.dy + c*goBackY.dz;


//    if(fabs(step_down + 1.0f) > 1e-6){
//        cerr << "step_down + 1 = " << fabs(step_down + 1.0f) << " > 1e-6" << endl;
//    }; // 验证归一化正确性

    step = step_up / step_down;
    return step;
}

float ConeDemo::virtual_Point2FlatXY(glm::vec3 &_point) {

    float a = virtual_a_b_c_d_XY[0];
    float b = virtual_a_b_c_d_XY[1];
    float c = virtual_a_b_c_d_XY[2];
    float d = virtual_a_b_c_d_XY[3];
#ifdef MAYBE_UNUSED
    [[maybe_unused]]goLine32 goBackZ = {-a, -b, -c};
#endif
    float step, step_up, step_down;
    step_up = -a*_point.x - b*_point.y - c*_point.z - d;
//    if(std::isnan(step_up)){
//        cerr << "step_up is nan" << endl;
//    }
    step_down = -1.f;//a*goBackZ.dx + b*goBackZ.dy + c*goBackZ.dz;


//    if(fabs(step_down + 1.0f) > 1e-6){
//        cerr << "step_down + 1 = " << fabs(step_down + 1.0f) << " > 1e-6" << endl;
//    }; // 验证归一化正确性

    step = step_up / step_down;
    return step;
}

glm::vec3 ConeDemo::screenXYZ2SelfXYZ(glm::vec3 _screenXYZ) {
    float leaveZeroX = virtual_Point2FlatYZ(_screenXYZ);
    float leaveZeroY = virtual_Point2FlatXZ(_screenXYZ);
    float leaveZeroZ = virtual_Point2FlatXY(_screenXYZ);

    return glm::vec3{leaveZeroX, leaveZeroY, leaveZeroZ};
}
glm::vec3 ConeDemo::screenXY2SelfXYZ_LockAxis(glm::vec2 _screenXY){
    glm::vec3 _then = screenLT_onSelfAxis; // 初始屏幕左上角 自己系看

    _then.x = _then.x + screenGoX_OnSelfAxis.dx * _screenXY.x;
    _then.y = _then.y + screenGoX_OnSelfAxis.dy * _screenXY.x;
    _then.z = _then.z + screenGoX_OnSelfAxis.dz * _screenXY.x;

    _then.x = _then.x + screenGoY_OnSelfAxis.dx * _screenXY.y;
    _then.y = _then.y + screenGoY_OnSelfAxis.dy * _screenXY.y;
    _then.z = _then.z + screenGoY_OnSelfAxis.dz * _screenXY.y;

    return _then;

}
void ConeDemo::freshFrameRotateInfo(){
    frameRotateInfo_q = PolygonBase::getFrameRotateInfo_(virtual_toX,virtual_toDEEP);
}
glm::vec3 ConeDemo::back2Screen000(glm::vec3 _src){
    float backX = virtual_tblrdXYZ.center.x;
    float backY = virtual_tblrdXYZ.center.y;
    float backZ = virtual_tblrdXYZ.center.z;
    glm::vec3 result = {_src.x - backX,_src.y - backY,_src.z - backZ};
    return result;
}
glm::vec3 ConeDemo::screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos){
    if(isnan(_screenAxisPos.x) || isnan(_screenAxisPos.y) || isnan(_screenAxisPos.z)){
        println(stderr,"_screenAxisPos(", _screenAxisPos.x, ", ", _screenAxisPos.y, ", ", _screenAxisPos.z, ")");
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }// 不是 nan
//    float backX = virtual_tblrdXYZ.center.x;
//    float backY = virtual_tblrdXYZ.center.y;
//    float backZ = virtual_tblrdXYZ.center.z;

    glm::vec3 p1ToWorld000 = _screenAxisPos - virtual_tblrdXYZ.center;
    // {_screenAxisPos.x - backX, _screenAxisPos.y - backY, _screenAxisPos.z - backZ}; // 归原点
    float distanceOf000 = glm::length(p1ToWorld000); // 原点距
    goLine64 p1ToWorld000_dir1 = {p1ToWorld000.x /= distanceOf000,
                                          p1ToWorld000.y /= distanceOf000,
                                          p1ToWorld000.z /= distanceOf000}; // 归一化
    // 没两角全0  不然不用斜转

    PolygonBase::rotate_vector(p1ToWorld000_dir1, frameRotateInfo_q);
    glm::vec3 farScreenAxis000 = {(float)p1ToWorld000_dir1.dx * distanceOf000,
                           (float)p1ToWorld000_dir1.dy * distanceOf000,
                                  (float)p1ToWorld000_dir1.dz * distanceOf000};


    if(isnan(farScreenAxis000.x) || isnan(farScreenAxis000.y) || isnan(farScreenAxis000.z)){
        println(stderr,"farScreenAxis000(", farScreenAxis000.x, ", ", farScreenAxis000.y, ", ", farScreenAxis000.z, ")");
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }
    return farScreenAxis000;
}
glm::vec3 ConeDemo::screenXY2SelfXYZ(glm::vec2 _screenXY){
    return screenXYZ2SelfXYZ2(glm::vec3(_screenXY.x,_screenXY.y,0.f));
}
pair<float,float> ConeDemo::getEyeThenStepByScreenXY(glm::vec2 _screenXY, bool quoteInfo){
    // 自己系
    // 眼睛XYZ 眼屏步进dxdydz height高 radius半径

    /*
         /       高 - 表面y \ ²
        | 半径 * ---------  | = 表面x² + 表面z²
         \           高    /
     */
    float ex = eyeOnSelfAxis.x, ey = eyeOnSelfAxis.y, ez = eyeOnSelfAxis.z;
    glm::vec3 screenPointOnSelfAxis; goLine32 eyeGoDir;


if(!quoteInfo){

    //glm::vec3 pointOnSelfAxis = screenXYZ2SelfXYZ(glm::vec3{_screenXY.x, _screenXY.y, 0.f});
    if(ScreenAxis2Self_SameFlat){
        screenPointOnSelfAxis = screenXY2SelfXYZ_LockAxis(_screenXY);
    }else{
        screenPointOnSelfAxis = screenXY2SelfXYZ(_screenXY); // 锁定坐标轴
    }

//    cout << "#####pointOnSelfAxis: " << pointOnSelfAxis.x << " " << pointOnSelfAxis.y << " " << pointOnSelfAxis.z << endl;
    eyeGoDir = ScreenDemo::get_AgoB_direction3D(eyeOnSelfAxis, screenPointOnSelfAxis);

}else{
    screenPointOnSelfAxis = SelfAxisInfo::screenPoint;
    eyeGoDir = SelfAxisInfo::eyeGoScreen;
}

    float dx = eyeGoDir.dx, dy = eyeGoDir.dy, dz = eyeGoDir.dz;

    // ax² + bx + c = 0

    // a =  dx² + dz² - (r*dy/tall)²
    float k = radius / height; // 径高比系数
    float a = dx*dx + dz*dz - (k * dy)*(k * dy); // 信~
    // b = 2*(( r²*dy/tall*(1 - ey/tall) + ex*dx + ez*dz)
    float b = 2*(  (k*radius*dy  - k*k*ey*dy) + ex*dx + ez*dz  ); // 自~
    // c = r²*(1 - ey/tall)² - (ex² + ez²)
    float c = ex*ex + ez*ez - (radius - ey*k)*(radius - ey*k); // 己~ 也可更优

//    cout << "radius:" << radius << " height:" << height << "\n ey:" << ey << " dx:" << dx <<
//    " dy:" << dy << " dz:" << dz << "\n a:" << a << " b:" << b << " c:" << c << endl;
    // 解方程
    float delta = b*b - 4*a*c;
    float t1, t2;
    if(delta < 0){
        return make_pair(std::nanf(""),std::nanf(""));
    }else{
        t1 = (-b + glm::sqrt(delta))/(2*a);
        t2 = (-b - glm::sqrt(delta))/(2*a);

    }
    // t1-t2 = glm::sqrt(delta) / a  [glm::sqrt(delta) > 0才会有解,所以看a的正负]
    // a>0  t1>t2
    // a<0  t1<t2
    float farStep, nearStep;


    nearStep = t2;
    farStep = t1;


//    float step2Y0 = ey / dy; // 步y0 比步
//    if(virtual_tblrdXYZ.center.z > -screenDeep13){ // 眼板前 > -1000
//        step2Y0 = fabs(step2Y0);
//    }else{
//        step2Y0 = fabs(step2Y0) * -1;
//    }

//    cout << "ey:" << ey << " dy:" << dy << " step2Y0:" << step2Y0 << " nearStep:" << nearStep << endl;

    float pointNearY = ey + nearStep*dy; // 判断锥面过高过低
//    float pointFarY = ey + farStep*dy;


//    glm::vec3 pointFar;

    // 刷新 自己系 表面点 缓存
    SelfAxisInfo::pointNear = {ex + nearStep*dx,
             pointNearY,
             ez + nearStep*dz};
//    cout << "^^^^nearStep:" << nearStep << " farStep:" << farStep << endl;
//
//    cout << "^^^^pointNear( " << pointNear.x << " " << pointNear.y << " " << pointNear.z << " ) " << endl;


//    cout << "当前锥面点的 径:" << nowRadius << " 高:" << pointNearY <<
//         " 径高比:" << nowRadiusDivideHeight << endl;

//    float nowRadius, nowRadiusDivideHeight;

    if(/*nearStep>step2Y0*/pointNearY<0){ // 步y0 超过上0
//        cerr << "nearStep:" << nearStep << " < step2Y0:" << step2Y0 << endl;
        nearStep = std::nanf("");
        goto pass001;
    }
    if(pointNearY>height){ // 表面点 过低 out
 //        cerr << "pointNearY:" << pointNearY << " > height:" << height << endl;
        nearStep = std::nanf("");
        goto pass001;
    }
    if(virtual_tblrdXYZ.center.z > -screenDeep13 && nearStep<0.f){ // 步 负 无意义
        println(stderr,"eye front nearStep:", nearStep, " < 0");
        nearStep = std::nanf("");
        goto pass001;
    }

//    nowRadius = distanceOfPoint2D({pointNear.x,pointNear.z},{0.f,0.f});
//    nowRadiusDivideHeight = nowRadius / (height - pointNearY);
//    if(fabs(nowRadiusDivideHeight - radiusDivideHeight) > 0.005){ // 径高比 与 对象 径高比 差距过大
//        cerr << "nearStep:" << nearStep << " step2Y0:" << step2Y0 << endl;
//        cerr << "当前锥面点的 径:" << nowRadius << " 高:" << pointNearY <<
//             " 径高比:" << nowRadiusDivideHeight << " ≠ 对象 径高比:" << radiusDivideHeight << endl;
//    }

pass001:

//    if(pointFarY<0 || pointFarY>height){ // 锥面 过高过低
//        farStep = std::nanf("");
//
//    }

//    else{ // 不过高过低
//        pointFar = {ex + farStep*dx,
//                    pointFarY,
//                    ez + farStep*dz};
//    }

    return make_pair(nearStep,farStep);
}
glm::vec3 ConeDemo::getEyeThenStepSelfPosNear_ByScreenXY(glm::vec2 _screenXY){
    // 自己系
    // 眼睛XYZ 眼屏步进dxdydz height高 radius半径

    /*
         /       高 - 表面y \ ²
        | 半径 * ---------  | = 表面x² + 表面z²
         \           高    /
     */
    float ex = eyeOnSelfAxis.x, ey = eyeOnSelfAxis.y, ez = eyeOnSelfAxis.z;
    glm::vec3 screenPointOnSelfAxis; goLine32 eyeGoDir;

    if(ScreenAxis2Self_SameFlat){
        screenPointOnSelfAxis = screenXY2SelfXYZ_LockAxis(_screenXY);
    }else{
        screenPointOnSelfAxis = screenXY2SelfXYZ(_screenXY); // 从 自己系 screenLT goX goY
    }

//    cout << "#####pointOnSelfAxis: " << pointOnSelfAxis.x << " " << pointOnSelfAxis.y << " " << pointOnSelfAxis.z << endl;
    eyeGoDir = ScreenDemo::get_AgoB_direction3D(eyeOnSelfAxis, screenPointOnSelfAxis);


    float dx = eyeGoDir.dx, dy = eyeGoDir.dy, dz = eyeGoDir.dz;

    // ax² + bx + c = 0

    // a =  dx² + dz² - (r*dy/tall)²
    float a = dx*dx + dz*dz - (radius*dy/height)*(radius*dy/height); // 信!
    // b = 2*(( r²*dy/tall*(1 - ey/tall) + ex*dx + ez*dz)
    float b = 2*(  (radius*radius*dy /height)*(1 - ey/height) + ex*dx + ez*dz  ); // 自!
    // c = r²*(1 - ey/tall)² - (ex² + ez²)
    float c = ex*ex + ez*ez - radius*radius*(1 - ey/height)*(1 - ey/height); // 己!

//    cout << "radius:" << radius << " height:" << height << "\n ey:" << ey << " dx:" << dx <<
//    " dy:" << dy << " dz:" << dz << "\n a:" << a << " b:" << b << " c:" << c << endl;
    // 解方程
    float delta = b*b - 4*a*c;
    float t1, t2;
    if(delta < 0){
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }else{
//        t1 = (-b + glm::sqrt(delta))/(2*a);
        t2 = (-b - glm::sqrt(delta))/(2*a);

    }

    float farStep, nearStep;


    nearStep = t2;
//    farStep = t1;


//    float step2Y0 = ey / dy; // 步y0 比步
//    if(virtual_tblrdXYZ.center.z > -screenDeep13){ // 眼板前 > -1000
//        step2Y0 = fabs(step2Y0);
//    }else{
//        step2Y0 = fabs(step2Y0) * -1;
//    }

//    cout << "ey:" << ey << " dy:" << dy << " step2Y0:" << step2Y0 << " nearStep:" << nearStep << endl;

    float pointNearY = ey + nearStep*dy; // 判断锥面过高过低
//    float pointFarY = ey + farStep*dy;


//    glm::vec3 pointFar;

    // 刷新 自己系 表面点 缓存
    glm::vec3 pointNear = {ex + nearStep*dx,
                               pointNearY,
                               ez + nearStep*dz};
//    cout << "^^^^nearStep:" << nearStep << " farStep:" << farStep << endl;
//
//    cout << "^^^^pointNear( " << pointNear.x << " " << pointNear.y << " " << pointNear.z << " ) " << endl;


//    cout << "当前锥面点的 径:" << nowRadius << " 高:" << pointNearY <<
//         " 径高比:" << nowRadiusDivideHeight << endl;

//    float nowRadius, nowRadiusDivideHeight;

    if(/*nearStep>step2Y0*/pointNearY<0){ // 步y0 超过上0
//        cerr << "nearStep:" << nearStep << " < step2Y0:" << step2Y0 << endl;
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }
    if(pointNearY>height){ // 表面点 过低 out
        //        cerr << "pointNearY:" << pointNearY << " > height:" << height << endl;
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }


    return pointNear;
}
float ConeDemo::getEyeThenStepOfFlatByScreenXY(glm::vec2 _screenXY){
    float ex = eyeOnSelfAxis.x, ey = eyeOnSelfAxis.y, ez = eyeOnSelfAxis.z;

    //glm::vec3 pointOnSelfAxis = screenXYZ2SelfXYZ(glm::vec3{_screenXY.x, _screenXY.y, 0.f});
    glm::vec3 screenPointOnSelfAxis;
    if(ScreenAxis2Self_SameFlat){
        screenPointOnSelfAxis = screenXY2SelfXYZ_LockAxis(_screenXY);
    }else{
        screenPointOnSelfAxis = screenXY2SelfXYZ(_screenXY); // 锁定坐标轴
    }

    SelfAxisInfo::screenPoint = screenPointOnSelfAxis; // 缓存
//    cout << "#####pointOnSelfAxis: " << pointOnSelfAxis.x << " " << pointOnSelfAxis.y << " " << pointOnSelfAxis.z << endl;

    goLine32 eyeGoDir = ScreenDemo::get_AgoB_direction3D(eyeOnSelfAxis, screenPointOnSelfAxis);
    SelfAxisInfo::eyeGoScreen = eyeGoDir; // 缓存

    // 眼睛在top面的上面 高y
    // eye.y + stepToZero * dy = 0
    // stepToZero * dy = - eye.y
    float step2Zero = -ey / eyeGoDir.dy; // -正 / 负
    float onFlatX = ex + step2Zero * eyeGoDir.dx;
    float onFlatZ = ez + step2Zero * eyeGoDir.dz;

    float distanceOfCenterSquared = onFlatX*onFlatX + onFlatZ*onFlatZ;
    if(distanceOfCenterSquared < radius*radius){ // 在top面圆内
        // 刷新 自己系 表面点 缓存
        SelfAxisInfo::pointNear = glm::vec3{onFlatX,0.f,onFlatZ};

        return step2Zero;
    }else return std::nanf("");
}
glm::vec3 ConeDemo::get_EyeThenStepPos_OfCircle_ByScreenXY(glm::vec2 _screenXY){
    float ex = eyeOnSelfAxis.x, ey = eyeOnSelfAxis.y, ez = eyeOnSelfAxis.z;


    glm::vec3 screenPointOnSelfAxis = screenXY2SelfXYZ(_screenXY); // 锁定坐标轴

//    cout << "#####pointOnSelfAxis: " << pointOnSelfAxis.x << " " << pointOnSelfAxis.y << " " << pointOnSelfAxis.z << endl;

    goLine32 eyeGoDir = ScreenDemo::get_AgoB_direction3D(eyeOnSelfAxis, screenPointOnSelfAxis);


    // 眼睛在top面的上面 高y
    // eye.y + stepToZero * dy = 0
    // stepToZero * dy = - eye.y
    float step2Zero = -ey / eyeGoDir.dy; // -正 / 负
    float onFlatX = ex + step2Zero * eyeGoDir.dx;
    float onFlatZ = ez + step2Zero * eyeGoDir.dz;

    float distanceOfCenterSquared = onFlatX*onFlatX + onFlatZ*onFlatZ;
    glm::vec3 circlePoint_OnSeflAxis;
    if(distanceOfCenterSquared < radius*radius){ // 在top面圆内
        // 刷新 自己系 表面点 缓存
        circlePoint_OnSeflAxis = glm::vec3{onFlatX,0.f,onFlatZ};

        return circlePoint_OnSeflAxis;
    }else return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
}
void ConeDemo::freshScreenGoX_OnSelfAxis(){
    screenGoX_OnSelfAxis = ScreenDemo::get_AgoB_direction3D(screenLT_onSelfAxis,screenRT_onSelfAxis);
}
void ConeDemo::freshScreenGoY_OnSelfAxis(){
    screenGoY_OnSelfAxis = ScreenDemo::get_AgoB_direction3D(screenLT_onSelfAxis,screenLB_onSelfAxis);
}
