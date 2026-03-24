//
// Created by iceoc0 on 2025/10/2.
//

#ifndef POLYGONDISPLAY_GAMMA_FUNC_H
#define POLYGONDISPLAY_GAMMA_FUNC_H
#include"../func_main/equation/equation3_9_func.h"
#include"../../PolygonClass/equation/GammaComplex.h"
void freshGammaBox_by_axis_go(GammaComplex* Gamma_ObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL);

void freshGammaBox_by_axis_go(GammaComplex* Gamma_ObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL){
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


    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z };
    //printf("axis_0_0_0:%f,%f,%f\n",axis_0_0_0.y,axis_0_0_0.x,axis_0_0_0.z);
    // FLT_MAX 最大
    // ➗ cos() 转角

    // 3D xyz三步走 每步xyz都要动 都要 动
    glm::vec3 ltnXYZ;
    ltnXYZ = AxisTilt->goX(axis_0_0_0, Gamma_ObjMain->scanBox3D_unchange.ltnSet.x);
    ltnXYZ = AxisTilt->goY(ltnXYZ, Gamma_ObjMain->scanBox3D_unchange.ltnSet.y);
    ltnXYZ = AxisTilt->goDEEP(ltnXYZ, Gamma_ObjMain->scanBox3D_unchange.ltnSet.z);

    glm::vec3 rtnXYZ;
    rtnXYZ = AxisTilt->goX(axis_0_0_0, Gamma_ObjMain->scanBox3D_unchange.rtnSet.x);
    rtnXYZ = AxisTilt->goY(rtnXYZ, Gamma_ObjMain->scanBox3D_unchange.rtnSet.y);
    rtnXYZ = AxisTilt->goDEEP(rtnXYZ, Gamma_ObjMain->scanBox3D_unchange.rtnSet.z);

    glm::vec3 rbnXYZ;
    rbnXYZ = AxisTilt->goX(axis_0_0_0, Gamma_ObjMain->scanBox3D_unchange.rbnSet.x);
    rbnXYZ = AxisTilt->goY(rbnXYZ, Gamma_ObjMain->scanBox3D_unchange.rbnSet.y);
    rbnXYZ = AxisTilt->goDEEP(rbnXYZ, Gamma_ObjMain->scanBox3D_unchange.rbnSet.z);

    glm::vec3 lbnXYZ;
    lbnXYZ = AxisTilt->goX(axis_0_0_0, Gamma_ObjMain->scanBox3D_unchange.lbnSet.x);
    lbnXYZ = AxisTilt->goY(lbnXYZ, Gamma_ObjMain->scanBox3D_unchange.lbnSet.y);
    lbnXYZ = AxisTilt->goDEEP(lbnXYZ, Gamma_ObjMain->scanBox3D_unchange.lbnSet.z);

    glm::vec3 ltfXYZ;
    ltfXYZ = AxisTilt->goX(axis_0_0_0, Gamma_ObjMain->scanBox3D_unchange.ltfSet.x);
    ltfXYZ = AxisTilt->goY(ltfXYZ, Gamma_ObjMain->scanBox3D_unchange.ltfSet.y);
    ltfXYZ = AxisTilt->goDEEP(ltfXYZ, Gamma_ObjMain->scanBox3D_unchange.ltfSet.z);

    glm::vec3 rtfXYZ;
    rtfXYZ = AxisTilt->goX(axis_0_0_0, Gamma_ObjMain->scanBox3D_unchange.rtfSet.x);
    rtfXYZ = AxisTilt->goY(rtfXYZ, Gamma_ObjMain->scanBox3D_unchange.rtfSet.y);
    rtfXYZ = AxisTilt->goDEEP(rtfXYZ, Gamma_ObjMain->scanBox3D_unchange.rtfSet.z);

    glm::vec3 rbfXYZ;
    rbfXYZ = AxisTilt->goX(axis_0_0_0, Gamma_ObjMain->scanBox3D_unchange.rbfSet.x);
    rbfXYZ = AxisTilt->goY(rbfXYZ, Gamma_ObjMain->scanBox3D_unchange.rbfSet.y);
    rbfXYZ = AxisTilt->goDEEP(rbfXYZ, Gamma_ObjMain->scanBox3D_unchange.rbfSet.z);

    glm::vec3 lbfXYZ;
    lbfXYZ = AxisTilt->goX(axis_0_0_0, Gamma_ObjMain->scanBox3D_unchange.lbfSet.x);
    lbfXYZ = AxisTilt->goY(lbfXYZ, Gamma_ObjMain->scanBox3D_unchange.lbfSet.y);
    lbfXYZ = AxisTilt->goDEEP(lbfXYZ, Gamma_ObjMain->scanBox3D_unchange.lbfSet.z);


    Gamma_ObjMain->setBox3D(ltnXYZ, rtnXYZ, rbnXYZ, lbnXYZ,
                            ltfXYZ, rtfXYZ, rbfXYZ, lbfXYZ); // 更新3D坐标 center back

    couple_ltn = spotEyeScreenGo(ScreenEyeL,
                                 Gamma_ObjMain->scanBox3D.ltnSet, &Gamma_ObjMain->virtual_scanBox3D.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL,
                                 Gamma_ObjMain->scanBox3D.rtnSet, &Gamma_ObjMain->virtual_scanBox3D.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL,
                                 Gamma_ObjMain->scanBox3D.rbnSet, &Gamma_ObjMain->virtual_scanBox3D.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL,
                                 Gamma_ObjMain->scanBox3D.lbnSet, &Gamma_ObjMain->virtual_scanBox3D.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL,
                                 Gamma_ObjMain->scanBox3D.ltfSet, &Gamma_ObjMain->virtual_scanBox3D.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL,
                                 Gamma_ObjMain->scanBox3D.rtfSet, &Gamma_ObjMain->virtual_scanBox3D.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL,
                                 Gamma_ObjMain->scanBox3D.rbfSet, &Gamma_ObjMain->virtual_scanBox3D.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL,
                                 Gamma_ObjMain->scanBox3D.lbfSet, &Gamma_ObjMain->virtual_scanBox3D.lbfSet);


    couple_Center = spotEyeScreenGo(ScreenEyeL, Gamma_ObjMain->scanBox3D.center,
                                    &Gamma_ObjMain->virtual_scanBox3D.center); // 中心


    // 刷新坐标 3D -> 2D
    Gamma_ObjMain->setBox2D(couple_ltn, couple_rtn, couple_rbn, couple_lbn,
                            couple_ltf, couple_rtf, couple_rbf, couple_lbf,
                            couple_Center
    );

}
#endif //POLYGONDISPLAY_GAMMA_FUNC_H
