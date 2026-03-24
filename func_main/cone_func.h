//
// Created by iceoc0 on 2025/4/20.
//

#ifndef POLYGONDISPLAY_CONE_FUNC_H
#define POLYGONDISPLAY_CONE_FUNC_H

#include "sphere_func.h"
#include "../polygonClass/ConeDemo.h"

void freshCone_by_axis_go(ConeDemo* ConeObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL);
void fresh_oTBLRDXY_Go(ConeDemo* ConeObjMain, ScreenDemo* ScreenEyeL);


void freshCone_by_axis_go(ConeDemo* ConeObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL){

    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z };

    glm::vec3 ltXYZ;
    ltXYZ = AxisTilt->goX(axis_0_0_0, ConeObjMain->tblrdXYZ_unchange.ltSet.x);
    ltXYZ = AxisTilt->goY(ltXYZ, ConeObjMain->tblrdXYZ_unchange.ltSet.y);
    ltXYZ = AxisTilt->goDEEP(ltXYZ, ConeObjMain->tblrdXYZ_unchange.ltSet.z);
    glm::vec3 rtXYZ;
    rtXYZ = AxisTilt->goX(axis_0_0_0, ConeObjMain->tblrdXYZ_unchange.rtSet.x);
    rtXYZ = AxisTilt->goY(rtXYZ, ConeObjMain->tblrdXYZ_unchange.rtSet.y);
    rtXYZ = AxisTilt->goDEEP(rtXYZ, ConeObjMain->tblrdXYZ_unchange.rtSet.z);
    glm::vec3 rbXYZ;
    rbXYZ = AxisTilt->goX(axis_0_0_0, ConeObjMain->tblrdXYZ_unchange.rbSet.x);
    rbXYZ = AxisTilt->goY(rbXYZ, ConeObjMain->tblrdXYZ_unchange.rbSet.y);
    rbXYZ = AxisTilt->goDEEP(rbXYZ, ConeObjMain->tblrdXYZ_unchange.rbSet.z);
    glm::vec3 lbXYZ;
    lbXYZ = AxisTilt->goX(axis_0_0_0, ConeObjMain->tblrdXYZ_unchange.lbSet.x);
    lbXYZ = AxisTilt->goY(lbXYZ, ConeObjMain->tblrdXYZ_unchange.lbSet.y);
    lbXYZ = AxisTilt->goDEEP(lbXYZ, ConeObjMain->tblrdXYZ_unchange.lbSet.z);
    glm::vec3 downCuspXYZ;
    downCuspXYZ = AxisTilt->goX(axis_0_0_0, ConeObjMain->tblrdXYZ_unchange.downCuspSet.x);
    downCuspXYZ = AxisTilt->goY(downCuspXYZ, ConeObjMain->tblrdXYZ_unchange.downCuspSet.y);
    downCuspXYZ = AxisTilt->goDEEP(downCuspXYZ, ConeObjMain->tblrdXYZ_unchange.downCuspSet.z);

//    cout << " ltXYZ(" << ltXYZ.x << ", " << ltXYZ.y << ", " << ltXYZ.z << ")" << endl;
//    cout << " rtXYZ(" << rtXYZ.x << ", " << rtXYZ.y << ", " << rtXYZ.z << ")" << endl;
//    cout << " rbXYZ(" << rbXYZ.x << ", " << rbXYZ.y << ", " << rbXYZ.z << ")" << endl;
//    cout << " lbXYZ(" << lbXYZ.x << ", " << lbXYZ.y << ", " << lbXYZ.z << ")" << endl;
//    cout << " downCuspXYZ(" << downCuspXYZ.x << ", " << downCuspXYZ.y << ", " <<
//         downCuspXYZ.z << ")" << endl;


    ConeObjMain->setTBLRDXYZ(ltXYZ, rtXYZ, rbXYZ, lbXYZ, downCuspXYZ);

    glm::vec2 couple_lt;
    glm::vec2 couple_rt;
    glm::vec2 couple_rb;
    glm::vec2 couple_lb;
    glm::vec2 couple_downTip;

    glm::vec2 couple_Center;

    glm::vec2 couple_lt_rt_tip, couple_lt_rt_back;
    glm::vec2 couple_lt_lb_tip, couple_lt_lb_back;

    glm::vec2 couple_rb_rt_tip, couple_rb_rt_back;
    glm::vec2 couple_rb_lb_tip, couple_rb_lb_back;

    glm::vec2 couple_center_tip, couple_center_back;

    couple_lt = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.ltSet,
                                 &ConeObjMain->virtual_tblrdXYZ.ltSet);
    couple_rt = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rtSet,
                                 &ConeObjMain->virtual_tblrdXYZ.rtSet);
    couple_rb = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rbSet,
                                 &ConeObjMain->virtual_tblrdXYZ.rbSet);
    couple_lb = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.lbSet,
                                 &ConeObjMain->virtual_tblrdXYZ.lbSet);
    couple_downTip = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.downCuspSet,
                                 &ConeObjMain->virtual_tblrdXYZ.downCuspSet);
    couple_Center = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.center,
                                 &ConeObjMain->virtual_tblrdXYZ.center);

    couple_lt_rt_tip = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.lt_rt_tip,
                                 &ConeObjMain->virtual_tblrdXYZ.lt_rt_tip);
    couple_lt_rt_back = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.lt_rt_back,
                                 &ConeObjMain->virtual_tblrdXYZ.lt_rt_back);
    couple_lt_lb_tip = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.lt_lb_tip,
                                 &ConeObjMain->virtual_tblrdXYZ.lt_lb_tip);
    couple_lt_lb_back = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.lt_lb_back,
                                 &ConeObjMain->virtual_tblrdXYZ.lt_lb_back);
    couple_rb_rt_tip = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rb_rt_tip,
                                 &ConeObjMain->virtual_tblrdXYZ.rb_rt_tip);
    couple_rb_rt_back = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rb_rt_back,
                                 &ConeObjMain->virtual_tblrdXYZ.rb_rt_back);
    couple_rb_lb_tip = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rb_lb_tip,
                                 &ConeObjMain->virtual_tblrdXYZ.rb_lb_tip);
    couple_rb_lb_back = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rb_lb_back,
                                 &ConeObjMain->virtual_tblrdXYZ.rb_lb_back);
    couple_center_tip = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.centerTip,
                                 &ConeObjMain->virtual_tblrdXYZ.centerTip);
    couple_center_back = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.centerBack,
                                 &ConeObjMain->virtual_tblrdXYZ.centerBack);


    ConeObjMain->setTBLRDXY(couple_lt, couple_rt, couple_rb, couple_lb,
                            couple_downTip, couple_Center,
                            couple_lt_rt_tip, couple_lt_rt_back,
                            couple_lt_lb_tip, couple_lt_lb_back,
                            couple_rb_rt_tip, couple_rb_rt_back,
                            couple_rb_lb_tip, couple_rb_lb_back,
                            couple_center_tip, couple_center_back);

}
void fresh_oTBLRDXY_Go(ConeDemo* ConeObjMain, ScreenDemo* ScreenEyeL){
    glm::vec2 couple_lt;
    glm::vec2 couple_rt;
    glm::vec2 couple_rb;
    glm::vec2 couple_lb;

    glm::vec2 couple_downCusp;

    glm::vec2 couple_Center;

    glm::vec2 couple_lt_rt_tip, couple_lt_rt_back;
    glm::vec2 couple_lt_lb_tip, couple_lt_lb_back;
    glm::vec2 couple_rb_rt_tip, couple_rb_rt_back;
    glm::vec2 couple_rb_lb_tip, couple_rb_lb_back;
    glm::vec2 couple_centerTip, couple_centerBack;



    couple_lt = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.ltSet, &ConeObjMain->virtual_tblrdXYZ.ltSet);
    couple_rt = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rtSet, &ConeObjMain->virtual_tblrdXYZ.rtSet);
    couple_rb = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rbSet, &ConeObjMain->virtual_tblrdXYZ.rbSet);

    couple_lb = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.lbSet, &ConeObjMain->virtual_tblrdXYZ.lbSet);

    couple_downCusp = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.downCuspSet, &ConeObjMain->virtual_tblrdXYZ.downCuspSet);


    couple_Center = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.center,&ConeObjMain->virtual_tblrdXYZ.center); // 中心

    couple_lt_rt_tip = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.lt_rt_tip,
                                         &ConeObjMain->virtual_tblrdXYZ.lt_rt_tip);
    couple_lt_rt_back = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.lt_rt_back,
                                          &ConeObjMain->virtual_tblrdXYZ.lt_rt_back);
    couple_lt_lb_tip = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.lt_lb_tip,
                                         &ConeObjMain->virtual_tblrdXYZ.lt_lb_tip);
    couple_lt_lb_back = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.lt_lb_back,
                                          &ConeObjMain->virtual_tblrdXYZ.lt_lb_back);
    couple_rb_rt_tip = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rb_rt_tip,
                                         &ConeObjMain->virtual_tblrdXYZ.rb_rt_tip);
    couple_rb_rt_back = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rb_rt_back,
                                          &ConeObjMain->virtual_tblrdXYZ.rb_rt_back);

    couple_rb_lb_tip = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rb_lb_tip,
                                         &ConeObjMain->virtual_tblrdXYZ.rb_lb_tip);
    couple_rb_lb_back = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.rb_lb_back,
                                          &ConeObjMain->virtual_tblrdXYZ.rb_lb_back);
    couple_centerTip = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.centerTip,
                                         &ConeObjMain->virtual_tblrdXYZ.centerTip);
    couple_centerBack = spotEyeScreenGo(ScreenEyeL, ConeObjMain->tblrdXYZ.centerBack,
                                          &ConeObjMain->virtual_tblrdXYZ.centerBack);

    // 刷新坐标 3D -> 2D
    ConeObjMain->setTBLRDXY(couple_lt, couple_rt,couple_rb, couple_lb,
                               couple_downCusp,couple_Center,
                               couple_lt_rt_tip, couple_lt_rt_back,
                               couple_lt_lb_tip, couple_lt_lb_back,
                               couple_rb_rt_tip, couple_rb_rt_back,

                               couple_rb_lb_tip, couple_rb_lb_back,
                               couple_centerTip, couple_centerBack
                               );
}

#endif //POLYGONDISPLAY_CONE_FUNC_H
