//
// Created by iceoc0 on 2026/1/17.
//

#ifndef POLYGONDISPLAY_BEZIER22EDGE3_FUNC_H
#define POLYGONDISPLAY_BEZIER22EDGE3_FUNC_H
#include"./equation/gamma_func.h"
#include"../polygonClass/Bezier22Edge3.h"

void freshBezier223_by_axis_go(Bezier22Edge3* BezierObj, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL);
void freshBezier223_P_Grid_XY_Go(Bezier22Edge3* BezierObj, ScreenDemo* ScreenEyeL);

void freshBezier223_by_axis_go(Bezier22Edge3* BezierObj, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL) {

    //println("mode 2 by axis");
    controlPoint3D _P;
    for(int i=0;i<3;i++){
        _P.tip[i] = AxisTilt->AxisTilt2world(BezierObj->P_unchange.tip[i].x,
                                BezierObj->P_unchange.tip[i].y,
                                BezierObj->P_unchange.tip[i].z);

        _P.edgeMid[i] = AxisTilt->AxisTilt2world(BezierObj->P_unchange.edgeMid[i].x,
            BezierObj->P_unchange.edgeMid[i].y,
            BezierObj->P_unchange.edgeMid[i].z);


    }BezierObj->P_world.freshP(_P);

    if (BezierObj->showP) {
        for(int i=0;i<3;i++) {

            BezierObj->P2D.tip[i] = spotEyeScreenGo(ScreenEyeL, BezierObj->P_world.tip[i],
                                        &BezierObj->P_virtual.tip[i]);
            BezierObj->P2D.edgeMid[i] = spotEyeScreenGo(ScreenEyeL, BezierObj->P_world.edgeMid[i],
                                        &BezierObj->P_virtual.edgeMid[i]);
        }
    }else {
        for(int i=0;i<3;i++) {
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->P_world.tip[i],
                                        &BezierObj->P_virtual.tip[i]);
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->P_world.edgeMid[i],
                                        &BezierObj->P_virtual.edgeMid[i]);
        }
    }

        size_t cloudsHave = BezierObj->Grid_unchange.size();

        for (int i=0;i<cloudsHave;i++) {
            BezierObj->Grid_world[i] = AxisTilt->AxisTilt2world(BezierObj->Grid_unchange[i].x,
                                                   BezierObj->Grid_unchange[i].y,
                                                   BezierObj->Grid_unchange[i].z);

        }
  // 不受 showGrid 限制
    for (int i=0;i<cloudsHave;i++) {
        BezierObj->Grid2D[i] = spotEyeScreenGo(ScreenEyeL, BezierObj->Grid_world[i],
            &BezierObj->Grid_virtual[i]);
    }
    BezierObj->moveFreshStatus();
// 3D xyz三步走 每步xyz都要动 都要 动
    glm::vec3 ltnXYZ = AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.ltnSet.x,
                                                BezierObj->scanBox3D_unchange.ltnSet.y,
                                                BezierObj->scanBox3D_unchange.ltnSet.z);

    glm::vec3 rtnXYZ = AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.rtnSet.x,
                                                BezierObj->scanBox3D_unchange.rtnSet.y,
                                                BezierObj->scanBox3D_unchange.rtnSet.z);

    glm::vec3 rbnXYZ = AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.rbnSet.x,
                                                BezierObj->scanBox3D_unchange.rbnSet.y,
                                                BezierObj->scanBox3D_unchange.rbnSet.z);

    glm::vec3 lbnXYZ = AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.lbnSet.x,
                                                BezierObj->scanBox3D_unchange.lbnSet.y,
                                                BezierObj->scanBox3D_unchange.lbnSet.z);

    glm::vec3 ltfXYZ = AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.ltfSet.x,
                                                BezierObj->scanBox3D_unchange.ltfSet.y,
                                                BezierObj->scanBox3D_unchange.ltfSet.z);

    glm::vec3 rtfXYZ = AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.rtfSet.x,
                                                BezierObj->scanBox3D_unchange.rtfSet.y,
                                                BezierObj->scanBox3D_unchange.rtfSet.z);

    glm::vec3 rbfXYZ = AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.rbfSet.x,
                                                BezierObj->scanBox3D_unchange.rbfSet.y,
                                                BezierObj->scanBox3D_unchange.rbfSet.z);

    glm::vec3 lbfXYZ = AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.lbfSet.x,
                                                BezierObj->scanBox3D_unchange.lbfSet.y,
                                                BezierObj->scanBox3D_unchange.lbfSet.z);


    BezierObj->setBox3D(ltnXYZ, rtnXYZ, rbnXYZ, lbnXYZ,
                        ltfXYZ, rtfXYZ, rbfXYZ, lbfXYZ); // 更新3D坐标 center back


    glm::vec2 couple_ltn{};
    glm::vec2 couple_rtn{};
    glm::vec2 couple_rbn{};
    glm::vec2 couple_lbn{};

    glm::vec2 couple_ltf{};
    glm::vec2 couple_rtf{};
    glm::vec2 couple_rbf{};
    glm::vec2 couple_lbf{};

    glm::vec2 couple_Center{};
DEBUG_SECTION(
    glm::vec2 couple_rtn_ltn_tip{};
    glm::vec2 couple_lbn_ltn_tip{};
    glm::vec2 couple_ltf_ltn_tip{};

    glm::vec2 couple_lbf_rbf_tip{};
    glm::vec2 couple_rtf_rbf_tip{};
    glm::vec2 couple_rbn_rbf_tip{};
)
    couple_ltn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.ltnSet, &BezierObj->virtual_scanBox3D.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rtnSet, &BezierObj->virtual_scanBox3D.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rbnSet, &BezierObj->virtual_scanBox3D.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.lbnSet, &BezierObj->virtual_scanBox3D.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.ltfSet, &BezierObj->virtual_scanBox3D.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rtfSet, &BezierObj->virtual_scanBox3D.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rbfSet, &BezierObj->virtual_scanBox3D.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.lbfSet, &BezierObj->virtual_scanBox3D.lbfSet);

    couple_Center = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.center,&BezierObj->virtual_scanBox3D.center); // 中心
    //println("box center world:{}",showVec3(BezierObj->scanBox3D_world.center));
DEBUG_SECTION(
    couple_rtn_ltn_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rtn_ltn_tip, &BezierObj->virtual_scanBox3D.rtn_ltn_tip);
    couple_lbn_ltn_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.lbn_ltn_tip, &BezierObj->virtual_scanBox3D.lbn_ltn_tip);
    couple_ltf_ltn_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.ltf_ltn_tip, &BezierObj->virtual_scanBox3D.ltf_ltn_tip);

    couple_lbf_rbf_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.lbf_rbf_tip, &BezierObj->virtual_scanBox3D.lbf_rbf_tip);
    couple_rtf_rbf_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rtf_rbf_tip, &BezierObj->virtual_scanBox3D.rtf_rbf_tip);
    couple_rbn_rbf_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rbn_rbf_tip, &BezierObj->virtual_scanBox3D.rbn_rbf_tip);
)
    // 刷新坐标 3D -> 2D
    BezierObj->setBox2D(couple_ltn, couple_rtn,couple_rbn, couple_lbn,
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

void freshBezier223_P_Grid_XY_Go(Bezier22Edge3* BezierObj, ScreenDemo* ScreenEyeL) {
    if (BezierObj->showP) {
        for(int i=0;i<3;i++) {

            BezierObj->P2D.tip[i] = spotEyeScreenGo(ScreenEyeL, BezierObj->P_world.tip[i],
                                        &BezierObj->P_virtual.tip[i]);
            BezierObj->P2D.edgeMid[i] = spotEyeScreenGo(ScreenEyeL, BezierObj->P_world.edgeMid[i],
                                        &BezierObj->P_virtual.edgeMid[i]);
        }
    }else {
        for(int i=0;i<3;i++) {
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->P_world.tip[i],
                                        &BezierObj->P_virtual.tip[i]);
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->P_world.edgeMid[i],
                                        &BezierObj->P_virtual.edgeMid[i]);
        }
    }
    size_t cloudsHave = BezierObj->Grid_world.size();


    for (int i=0;i<cloudsHave;i++) {
        BezierObj->Grid2D[i] = spotEyeScreenGo(ScreenEyeL, BezierObj->Grid_world[i],
            &BezierObj->Grid_virtual[i]);
    }
    BezierObj->moveFreshStatus();
glm::vec2 couple_ltn{};
    glm::vec2 couple_rtn{};
    glm::vec2 couple_rbn{};
    glm::vec2 couple_lbn{};

    glm::vec2 couple_ltf{};
    glm::vec2 couple_rtf{};
    glm::vec2 couple_rbf{};
    glm::vec2 couple_lbf{};

    glm::vec2 couple_Center{};
DEBUG_SECTION(
    glm::vec2 couple_rtn_ltn_tip{};
    glm::vec2 couple_lbn_ltn_tip{};
    glm::vec2 couple_ltf_ltn_tip{};

    glm::vec2 couple_lbf_rbf_tip{};
    glm::vec2 couple_rtf_rbf_tip{};
    glm::vec2 couple_rbn_rbf_tip{};
)
    couple_ltn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.ltnSet, &BezierObj->virtual_scanBox3D.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rtnSet, &BezierObj->virtual_scanBox3D.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rbnSet, &BezierObj->virtual_scanBox3D.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.lbnSet, &BezierObj->virtual_scanBox3D.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.ltfSet, &BezierObj->virtual_scanBox3D.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rtfSet, &BezierObj->virtual_scanBox3D.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rbfSet, &BezierObj->virtual_scanBox3D.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.lbfSet, &BezierObj->virtual_scanBox3D.lbfSet);

    couple_Center = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.center,&BezierObj->virtual_scanBox3D.center); // 中心
DEBUG_SECTION(
    couple_rtn_ltn_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rtn_ltn_tip, &BezierObj->virtual_scanBox3D.rtn_ltn_tip);
    couple_lbn_ltn_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.lbn_ltn_tip, &BezierObj->virtual_scanBox3D.lbn_ltn_tip);
    couple_ltf_ltn_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.ltf_ltn_tip, &BezierObj->virtual_scanBox3D.ltf_ltn_tip);

    couple_lbf_rbf_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.lbf_rbf_tip, &BezierObj->virtual_scanBox3D.lbf_rbf_tip);
    couple_rtf_rbf_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rtf_rbf_tip, &BezierObj->virtual_scanBox3D.rtf_rbf_tip);
    couple_rbn_rbf_tip = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D_world.rbn_rbf_tip, &BezierObj->virtual_scanBox3D.rbn_rbf_tip);
)
    // 刷新坐标 3D -> 2D
    BezierObj->setBox2D(couple_ltn, couple_rtn,couple_rbn, couple_lbn,
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
#endif //POLYGONDISPLAY_BEZIER22EDGE3_FUNC_H