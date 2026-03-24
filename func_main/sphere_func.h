//
// Created by iceoc0 on 2025/4/11.
//

#ifndef POLYGONDISPLAY_SPHERE_FUNC_H
#define POLYGONDISPLAY_SPHERE_FUNC_H

#include "circle_func.h"
#include "../polygonClass/SphereDemo.h"
void freshSphere_by_axis_go(SphereDemo* SphereObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL);
void fresh_oTBLRXYNF_Go(SphereDemo* SphereObjMain, ScreenDemo* ScreenEyeL);

void freshSphere_by_axis_go(SphereDemo* SphereObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL){
    // 刷新坐标 3D -> 2D
    glm::vec2 couple_ltn;
    glm::vec2 couple_rtn;
    glm::vec2 couple_rbn;
    glm::vec2 couple_lbn;

    glm::vec2 couple_ltf;
    glm::vec2 couple_rtf;
    glm::vec2 couple_rbf;
    glm::vec2 couple_lbf;

    glm::vec2 couple_Center;
DEBUG_SECTION(
    glm::vec2 couple_rtn_ltn_tip;
    glm::vec2 couple_lbn_ltn_tip;
    glm::vec2 couple_ltf_ltn_tip;

    glm::vec2 couple_lbf_rbf_tip;
    glm::vec2 couple_rtf_rbf_tip;
    glm::vec2 couple_rbn_rbf_tip;
)
    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z };
    //printf("axis_0_0_0:%f,%f,%f\n",axis_0_0_0.y,axis_0_0_0.x,axis_0_0_0.z);
    // FLT_MAX 最大
    // ➗ cos() 转角

    // 3D xyz三步走 每步xyz都要动 都要 动
    glm::vec3 ltnXYZ;
    ltnXYZ = AxisTilt->goX(axis_0_0_0, SphereObjMain->tblrXYZnf_unchange.ltnSet.x);
    ltnXYZ = AxisTilt->goY(ltnXYZ, SphereObjMain->tblrXYZnf_unchange.ltnSet.y);
    ltnXYZ = AxisTilt->goDEEP(ltnXYZ, SphereObjMain->tblrXYZnf_unchange.ltnSet.z);

    glm::vec3 rtnXYZ;
    rtnXYZ = AxisTilt->goX(axis_0_0_0, SphereObjMain->tblrXYZnf_unchange.rtnSet.x);
    rtnXYZ = AxisTilt->goY(rtnXYZ, SphereObjMain->tblrXYZnf_unchange.rtnSet.y);
    rtnXYZ = AxisTilt->goDEEP(rtnXYZ, SphereObjMain->tblrXYZnf_unchange.rtnSet.z);

    glm::vec3 rbnXYZ;
    rbnXYZ = AxisTilt->goX(axis_0_0_0, SphereObjMain->tblrXYZnf_unchange.rbnSet.x);
    rbnXYZ = AxisTilt->goY(rbnXYZ, SphereObjMain->tblrXYZnf_unchange.rbnSet.y);
    rbnXYZ = AxisTilt->goDEEP(rbnXYZ, SphereObjMain->tblrXYZnf_unchange.rbnSet.z);

    glm::vec3 lbnXYZ;
    lbnXYZ = AxisTilt->goX(axis_0_0_0, SphereObjMain->tblrXYZnf_unchange.lbnSet.x);
    lbnXYZ = AxisTilt->goY(lbnXYZ, SphereObjMain->tblrXYZnf_unchange.lbnSet.y);
    lbnXYZ = AxisTilt->goDEEP(lbnXYZ, SphereObjMain->tblrXYZnf_unchange.lbnSet.z);

    glm::vec3 ltfXYZ;
    ltfXYZ = AxisTilt->goX(axis_0_0_0, SphereObjMain->tblrXYZnf_unchange.ltfSet.x);
    ltfXYZ = AxisTilt->goY(ltfXYZ, SphereObjMain->tblrXYZnf_unchange.ltfSet.y);
    ltfXYZ = AxisTilt->goDEEP(ltfXYZ, SphereObjMain->tblrXYZnf_unchange.ltfSet.z);

    glm::vec3 rtfXYZ;
    rtfXYZ = AxisTilt->goX(axis_0_0_0, SphereObjMain->tblrXYZnf_unchange.rtfSet.x);
    rtfXYZ = AxisTilt->goY(rtfXYZ, SphereObjMain->tblrXYZnf_unchange.rtfSet.y);
    rtfXYZ = AxisTilt->goDEEP(rtfXYZ, SphereObjMain->tblrXYZnf_unchange.rtfSet.z);

    glm::vec3 rbfXYZ;
    rbfXYZ = AxisTilt->goX(axis_0_0_0, SphereObjMain->tblrXYZnf_unchange.rbfSet.x);
    rbfXYZ = AxisTilt->goY(rbfXYZ, SphereObjMain->tblrXYZnf_unchange.rbfSet.y);
    rbfXYZ = AxisTilt->goDEEP(rbfXYZ, SphereObjMain->tblrXYZnf_unchange.rbfSet.z);

    glm::vec3 lbfXYZ;
    lbfXYZ = AxisTilt->goX(axis_0_0_0, SphereObjMain->tblrXYZnf_unchange.lbfSet.x);
    lbfXYZ = AxisTilt->goY(lbfXYZ, SphereObjMain->tblrXYZnf_unchange.lbfSet.y);
    lbfXYZ = AxisTilt->goDEEP(lbfXYZ, SphereObjMain->tblrXYZnf_unchange.lbfSet.z);


    SphereObjMain->setBox3D(ltnXYZ, rtnXYZ, rbnXYZ, lbnXYZ,
                                 ltfXYZ, rtfXYZ, rbfXYZ, lbfXYZ); // 更新3D坐标 center back

    couple_ltn = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.ltnSet, &SphereObjMain->virtual_tblrXYZnf.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rtnSet, &SphereObjMain->virtual_tblrXYZnf.rtnSet);
    couple_rbn= spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rbnSet, &SphereObjMain->virtual_tblrXYZnf.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.lbnSet, &SphereObjMain->virtual_tblrXYZnf.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.ltfSet, &SphereObjMain->virtual_tblrXYZnf.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rtfSet, &SphereObjMain->virtual_tblrXYZnf.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rbfSet, &SphereObjMain->virtual_tblrXYZnf.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.lbfSet, &SphereObjMain->virtual_tblrXYZnf.lbfSet);



    couple_Center = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.center,&SphereObjMain->virtual_tblrXYZnf.center); // 中心
DEBUG_SECTION(
    couple_rtn_ltn_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rtn_ltn_tip, &SphereObjMain->virtual_tblrXYZnf.rtn_ltn_tip);
    couple_lbn_ltn_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.lbn_ltn_tip, &SphereObjMain->virtual_tblrXYZnf.lbn_ltn_tip);
    couple_ltf_ltn_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.ltf_ltn_tip, &SphereObjMain->virtual_tblrXYZnf.ltf_ltn_tip);

    couple_lbf_rbf_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.lbf_rbf_tip, &SphereObjMain->virtual_tblrXYZnf.lbf_rbf_tip);
    couple_rtf_rbf_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rtf_rbf_tip, &SphereObjMain->virtual_tblrXYZnf.rtf_rbf_tip);
    couple_rbn_rbf_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rbn_rbf_tip, &SphereObjMain->virtual_tblrXYZnf.rbn_rbf_tip);
)
    // 刷新坐标 3D -> 2D
    SphereObjMain->setBox2D(couple_ltn, couple_rtn,couple_rbn, couple_lbn,
                               couple_ltf, couple_rtf,couple_rbf, couple_lbf,
                               couple_Center
#if defined(DEBUG_ON)
                               ,
                               couple_rtn_ltn_tip,
                               couple_lbn_ltn_tip,
                               couple_ltf_ltn_tip,

                               couple_lbf_rbf_tip,
                               couple_rtf_rbf_tip,
                               couple_rbn_rbf_tip
#endif
                               );


}
void fresh_oTBLRXYNF_Go(SphereDemo* SphereObjMain, ScreenDemo* ScreenEyeL){
    glm::vec2 couple_ltn;
    glm::vec2 couple_rtn;
    glm::vec2 couple_rbn;
    glm::vec2 couple_lbn;

    glm::vec2 couple_ltf;
    glm::vec2 couple_rtf;
    glm::vec2 couple_rbf;
    glm::vec2 couple_lbf;

    glm::vec2 couple_Center;
DEBUG_SECTION(
    glm::vec2 couple_rtn_ltn_tip;
    glm::vec2 couple_lbn_ltn_tip;
    glm::vec2 couple_ltf_ltn_tip;

    glm::vec2 couple_lbf_rbf_tip;
    glm::vec2 couple_rtf_rbf_tip;
    glm::vec2 couple_rbn_rbf_tip;
)
    couple_ltn = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.ltnSet, &SphereObjMain->virtual_tblrXYZnf.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rtnSet, &SphereObjMain->virtual_tblrXYZnf.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rbnSet, &SphereObjMain->virtual_tblrXYZnf.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.lbnSet, &SphereObjMain->virtual_tblrXYZnf.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.ltfSet, &SphereObjMain->virtual_tblrXYZnf.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rtfSet, &SphereObjMain->virtual_tblrXYZnf.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rbfSet, &SphereObjMain->virtual_tblrXYZnf.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.lbfSet, &SphereObjMain->virtual_tblrXYZnf.lbfSet);



    couple_Center = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.center,&SphereObjMain->virtual_tblrXYZnf.center); // 中心
    //println("world box center:{}",showVec3(SphereObjMain->tblrXYZnf.center));
DEBUG_SECTION(
    couple_rtn_ltn_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rtn_ltn_tip, &SphereObjMain->virtual_tblrXYZnf.rtn_ltn_tip);
    couple_lbn_ltn_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.lbn_ltn_tip, &SphereObjMain->virtual_tblrXYZnf.lbn_ltn_tip);
    couple_ltf_ltn_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.ltf_ltn_tip, &SphereObjMain->virtual_tblrXYZnf.ltf_ltn_tip);

    couple_lbf_rbf_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.lbf_rbf_tip, &SphereObjMain->virtual_tblrXYZnf.lbf_rbf_tip);
    couple_rtf_rbf_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rtf_rbf_tip, &SphereObjMain->virtual_tblrXYZnf.rtf_rbf_tip);
    couple_rbn_rbf_tip = spotEyeScreenGo(ScreenEyeL, SphereObjMain->tblrXYZnf.rbn_rbf_tip, &SphereObjMain->virtual_tblrXYZnf.rbn_rbf_tip);
)
    // 刷新坐标 3D -> 2D
    SphereObjMain->setBox2D(couple_ltn, couple_rtn,couple_rbn, couple_lbn,
                               couple_ltf, couple_rtf,couple_rbf, couple_lbf,
                               couple_Center
#if defined(DEBUG_ON)
                               ,
                               couple_rtn_ltn_tip,
                               couple_lbn_ltn_tip,
                               couple_ltf_ltn_tip,

                               couple_lbf_rbf_tip,
                               couple_rtf_rbf_tip,
                               couple_rbn_rbf_tip
#endif
                               );
}
#endif //POLYGONDISPLAY_SPHERE_FUNC_H
