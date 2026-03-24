//
// Created by iceoc0 on 2025/8/16.
//

#ifndef POLYGONDISPLAY_EQUATION2_FUNC_H
#define POLYGONDISPLAY_EQUATION2_FUNC_H

#include"../imgrect_func.h"
#include"../../polygonClass/equation/EquationTwo.h"

void freshEquationBox_by_axis_go(EquationTwo* Equation2ObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL);
void fresh_EquationBox_Go(EquationTwo* Equation2ObjMain, ScreenDemo* ScreenEyeL);


void freshEquationBox_by_axis_go(EquationTwo* Equation2ObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL){
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
    ltnXYZ = AxisTilt->goX(axis_0_0_0, Equation2ObjMain->scanBox3D_unchange.ltnSet.x);
    ltnXYZ = AxisTilt->goY(ltnXYZ, Equation2ObjMain->scanBox3D_unchange.ltnSet.y);
    ltnXYZ = AxisTilt->goDEEP(ltnXYZ, Equation2ObjMain->scanBox3D_unchange.ltnSet.z);

    glm::vec3 rtnXYZ;
    rtnXYZ = AxisTilt->goX(axis_0_0_0, Equation2ObjMain->scanBox3D_unchange.rtnSet.x);
    rtnXYZ = AxisTilt->goY(rtnXYZ, Equation2ObjMain->scanBox3D_unchange.rtnSet.y);
    rtnXYZ = AxisTilt->goDEEP(rtnXYZ, Equation2ObjMain->scanBox3D_unchange.rtnSet.z);

    glm::vec3 rbnXYZ;
    rbnXYZ = AxisTilt->goX(axis_0_0_0, Equation2ObjMain->scanBox3D_unchange.rbnSet.x);
    rbnXYZ = AxisTilt->goY(rbnXYZ, Equation2ObjMain->scanBox3D_unchange.rbnSet.y);
    rbnXYZ = AxisTilt->goDEEP(rbnXYZ, Equation2ObjMain->scanBox3D_unchange.rbnSet.z);

    glm::vec3 lbnXYZ;
    lbnXYZ = AxisTilt->goX(axis_0_0_0, Equation2ObjMain->scanBox3D_unchange.lbnSet.x);
    lbnXYZ = AxisTilt->goY(lbnXYZ, Equation2ObjMain->scanBox3D_unchange.lbnSet.y);
    lbnXYZ = AxisTilt->goDEEP(lbnXYZ, Equation2ObjMain->scanBox3D_unchange.lbnSet.z);

    glm::vec3 ltfXYZ;
    ltfXYZ = AxisTilt->goX(axis_0_0_0, Equation2ObjMain->scanBox3D_unchange.ltfSet.x);
    ltfXYZ = AxisTilt->goY(ltfXYZ, Equation2ObjMain->scanBox3D_unchange.ltfSet.y);
    ltfXYZ = AxisTilt->goDEEP(ltfXYZ, Equation2ObjMain->scanBox3D_unchange.ltfSet.z);

    glm::vec3 rtfXYZ;
    rtfXYZ = AxisTilt->goX(axis_0_0_0, Equation2ObjMain->scanBox3D_unchange.rtfSet.x);
    rtfXYZ = AxisTilt->goY(rtfXYZ, Equation2ObjMain->scanBox3D_unchange.rtfSet.y);
    rtfXYZ = AxisTilt->goDEEP(rtfXYZ, Equation2ObjMain->scanBox3D_unchange.rtfSet.z);

    glm::vec3 rbfXYZ;
    rbfXYZ = AxisTilt->goX(axis_0_0_0, Equation2ObjMain->scanBox3D_unchange.rbfSet.x);
    rbfXYZ = AxisTilt->goY(rbfXYZ, Equation2ObjMain->scanBox3D_unchange.rbfSet.y);
    rbfXYZ = AxisTilt->goDEEP(rbfXYZ, Equation2ObjMain->scanBox3D_unchange.rbfSet.z);

    glm::vec3 lbfXYZ;
    lbfXYZ = AxisTilt->goX(axis_0_0_0, Equation2ObjMain->scanBox3D_unchange.lbfSet.x);
    lbfXYZ = AxisTilt->goY(lbfXYZ, Equation2ObjMain->scanBox3D_unchange.lbfSet.y);
    lbfXYZ = AxisTilt->goDEEP(lbfXYZ, Equation2ObjMain->scanBox3D_unchange.lbfSet.z);


    Equation2ObjMain->setBox3D(ltnXYZ, rtnXYZ, rbnXYZ, lbnXYZ,
                               ltfXYZ, rtfXYZ, rbfXYZ, lbfXYZ); // 更新3D坐标 center back

    couple_ltn = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.ltnSet, &Equation2ObjMain->virtual_scanBox3D.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.rtnSet, &Equation2ObjMain->virtual_scanBox3D.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL,
                                Equation2ObjMain->scanBox3D.rbnSet, &Equation2ObjMain->virtual_scanBox3D.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.lbnSet, &Equation2ObjMain->virtual_scanBox3D.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.ltfSet, &Equation2ObjMain->virtual_scanBox3D.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.rtfSet, &Equation2ObjMain->virtual_scanBox3D.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.rbfSet, &Equation2ObjMain->virtual_scanBox3D.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.lbfSet, &Equation2ObjMain->virtual_scanBox3D.lbfSet);



    couple_Center = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.center,
                                    &Equation2ObjMain->virtual_scanBox3D.center); // 中心
DEBUG_SECTION(
    couple_rtn_ltn_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.rtn_ltn_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.rtn_ltn_tip);

    couple_lbn_ltn_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.lbn_ltn_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.lbn_ltn_tip);

    couple_ltf_ltn_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.ltf_ltn_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.ltf_ltn_tip);


    couple_lbf_rbf_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.lbf_rbf_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.lbf_rbf_tip);

    couple_rtf_rbf_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.rtf_rbf_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.rtf_rbf_tip);

    couple_rbn_rbf_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.rbn_rbf_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.rbn_rbf_tip);
)

    // 刷新坐标 3D -> 2D
    Equation2ObjMain->setBox2D(couple_ltn, couple_rtn, couple_rbn, couple_lbn,
                               couple_ltf, couple_rtf, couple_rbf, couple_lbf,
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
void fresh_EquationBox_Go(EquationTwo* Equation2ObjMain, ScreenDemo* ScreenEyeL){
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
    couple_ltn = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.ltnSet, &Equation2ObjMain->virtual_scanBox3D.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.rtnSet, &Equation2ObjMain->virtual_scanBox3D.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.rbnSet, &Equation2ObjMain->virtual_scanBox3D.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.lbnSet, &Equation2ObjMain->virtual_scanBox3D.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.ltfSet, &Equation2ObjMain->virtual_scanBox3D.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.rtfSet, &Equation2ObjMain->virtual_scanBox3D.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.rbfSet, &Equation2ObjMain->virtual_scanBox3D.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL,
                                 Equation2ObjMain->scanBox3D.lbfSet, &Equation2ObjMain->virtual_scanBox3D.lbfSet);



    couple_Center = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.center,
                                    &Equation2ObjMain->virtual_scanBox3D.center); // 中心
DEBUG_SECTION(
    couple_rtn_ltn_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.rtn_ltn_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.rtn_ltn_tip);

    couple_lbn_ltn_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.lbn_ltn_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.lbn_ltn_tip);

    couple_ltf_ltn_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.ltf_ltn_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.ltf_ltn_tip);


    couple_lbf_rbf_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.lbf_rbf_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.lbf_rbf_tip);

    couple_rtf_rbf_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.rtf_rbf_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.rtf_rbf_tip);

    couple_rbn_rbf_tip = spotEyeScreenGo(ScreenEyeL, Equation2ObjMain->scanBox3D.rbn_rbf_tip,
                                         &Equation2ObjMain->virtual_scanBox3D.rbn_rbf_tip);
)

    // 刷新坐标 3D -> 2D
    Equation2ObjMain->setBox2D(couple_ltn, couple_rtn, couple_rbn, couple_lbn,
                               couple_ltf, couple_rtf, couple_rbf, couple_lbf,
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
#endif //POLYGONDISPLAY_EQUATION2_FUNC_H
