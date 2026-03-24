//
// Created by iceoc0 on 2025/6/7.
//

#ifndef POLYGONDISPLAY_BECUBICBEZIER_FUNC_H
#define POLYGONDISPLAY_BECUBICBEZIER_FUNC_H

#include"./cone_func.h"

#include "../polygonClass/Bezier33Edge4Mirror.h"
#include "../polygonClass/Bezier3Img.h"

void freshBezier334_by_axis_go(Bezier33Edge4* BezierObj, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL);
void freshBezier334_P_Grid_XY_Go(Bezier33Edge4* BezierObj, ScreenDemo* ScreenEyeL);

void freshBezier334Mirror_by_axis_go(Bezier33Edge4Mirror* BezierMirror, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL);
void bezier334Mirror_P_Grid_XY_Go(Bezier33Edge4Mirror* BezierMirror, ScreenDemo* ScreenEyeL);

void freshBezier3Img_by_axis_go(Bezier3Img* BezierImg, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL);
void bezier3Img_P_Grid_XY_Go(Bezier3Img* BezierImg, ScreenDemo* ScreenEyeL);

void freshBezier334_by_axis_go(Bezier33Edge4* BezierObj, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL) {


    glm::vec3 _P[5][5];
    for(int i=0;i<5; ++i){
        for(int j=0;j<5; ++j){
            _P[i][j] = AxisTilt->AxisTilt2world(BezierObj->P_unchange[i][j].x,
                                                BezierObj->P_unchange[i][j].y,
                                                BezierObj->P_unchange[i][j].z);
        }
    }BezierObj->set_P_XYZ(_P);

    //array<array<pair<glm::vec3, glm::vec3>, BezierObj->N_u>, BezierObj->N_v> _Grid;
    for(int i=0;i<BezierObj->N_v; ++i) {
        for(int j = 0; j < BezierObj->N_u; ++j) {
            BezierObj->Grid(i,j).first =
                AxisTilt->AxisTilt2world(BezierObj->Grid_unchange(i,j).first.x,
                                        BezierObj->Grid_unchange(i,j).first.y,
                                        BezierObj->Grid_unchange(i,j).first.z);
            //cout << "_Grid(i,j).first: " << _Grid(i,j).first.x << " " << _Grid(i,j).first.y << " " << _Grid(i,j).first.z << endl;

           BezierObj->Grid(i,j).second =
            AxisTilt->AxisTilt2world(BezierObj->Grid_unchange(i,j).second.x,
                                    BezierObj->Grid_unchange(i,j).second.y,
                                    BezierObj->Grid_unchange(i,j).second.z);
            //cout << "_Grid(i,j).second: " << _Grid(i,j).second.x << " " << _Grid(i,j).second.y << " " << _Grid(i,j).second.z << endl;

        }
    }
    // BezierObj->set_Grid_XYZ(_Grid);
    if (BezierObj->fastIteration || BezierObj->showEdgeRect) {
        //array<pair<glm::vec3,glm::vec3>, BezierObj->N_u> _Grid_Top;
        for(int i=0;i<BezierObj->N_u; ++i) {
            // 基向量 仿射变换

            BezierObj->Grid_edgeTop[i].first =
            AxisTilt->AxisTilt2world(BezierObj->Grid_edgeTop_unchange[i].first.x,
                                    BezierObj->Grid_edgeTop_unchange[i].first.y,
                                    BezierObj->Grid_edgeTop_unchange[i].first.z);

            BezierObj->Grid_edgeTop[i].second =
             AxisTilt->AxisTilt2world(BezierObj->Grid_edgeTop_unchange[i].second.x,
                                     BezierObj->Grid_edgeTop_unchange[i].second.y,
                                     BezierObj->Grid_edgeTop_unchange[i].second.z);
        }
        //BezierObj->set_Grid_XYZ_Top(_Grid_Top);

        //array<pair<glm::vec3,glm::vec3>, BezierObj->N_u> _Grid_Bottom;
        for(int i=0;i<BezierObj->N_u; ++i) {
            // 基向量 仿射变换
            BezierObj->Grid_edgeBottom[i].first =
                        AxisTilt->AxisTilt2world(BezierObj->Grid_edgeBottom_unchange[i].first.x,
                                                BezierObj->Grid_edgeBottom_unchange[i].first.y,
                                                BezierObj->Grid_edgeBottom_unchange[i].first.z);

            BezierObj->Grid_edgeBottom[i].second =
             AxisTilt->AxisTilt2world(BezierObj->Grid_edgeBottom_unchange[i].second.x,
                                     BezierObj->Grid_edgeBottom_unchange[i].second.y,
                                     BezierObj->Grid_edgeBottom_unchange[i].second.z);
        }
        // BezierObj->set_Grid_XYZ_Bottom(_Grid_Bottom);

        //array<pair<glm::vec3,glm::vec3>, BezierObj->N_v> _Grid_Left;
        for(int i=0;i<BezierObj->N_v; ++i) {
            // 基向量 仿射变换
            BezierObj->Grid_edgeLeft[i].first =
                                    AxisTilt->AxisTilt2world(BezierObj->Grid_edgeLeft_unchange[i].first.x,
                                                            BezierObj->Grid_edgeLeft_unchange[i].first.y,
                                                            BezierObj->Grid_edgeLeft_unchange[i].first.z);

            BezierObj->Grid_edgeLeft[i].second =
             AxisTilt->AxisTilt2world(BezierObj->Grid_edgeLeft_unchange[i].second.x,
                                     BezierObj->Grid_edgeLeft_unchange[i].second.y,
                                     BezierObj->Grid_edgeLeft_unchange[i].second.z);
        }
        // BezierObj->set_Grid_XYZ_Left(_Grid_Left);

        //array<pair<glm::vec3,glm::vec3>, BezierObj->N_v> _Grid_Right;
        for(int i=0;i<BezierObj->N_v; ++i) {
            // 基向量 仿射变换
            BezierObj->Grid_edgeRight[i].first =
            AxisTilt->AxisTilt2world(BezierObj->Grid_edgeRight_unchange[i].first.x,
                                    BezierObj->Grid_edgeRight_unchange[i].first.y,
                                    BezierObj->Grid_edgeRight_unchange[i].first.z);

            BezierObj->Grid_edgeRight[i].second =
             AxisTilt->AxisTilt2world(BezierObj->Grid_edgeRight_unchange[i].second.x,
                                     BezierObj->Grid_edgeRight_unchange[i].second.y,
                                     BezierObj->Grid_edgeRight_unchange[i].second.z);
        }
    }

    // BezierObj->set_Grid_XYZ_Right(_Grid_Right);

    //glm::vec2 _P2D[5][5];
    for(int i=0;i<5; ++i) {
        for(int j = 0; j < 5; ++j) {
            BezierObj->P2D[i][j] = spotEyeScreenGo(ScreenEyeL, BezierObj->P[i][j],
                                        &BezierObj->virtual_P[i][j]);
        }
    }
    // BezierObj->set_P_XY(_P2D);

    //array<array<pair<glm::vec2, glm::vec2>, BezierObj->N_u>, BezierObj->N_v> _Grid2D;
    for(int i=0;i<BezierObj->N_v; ++i) {
        for(int j = 0; j < BezierObj->N_u; ++j) {
            BezierObj->Grid2D(i,j).first = spotEyeScreenGo(ScreenEyeL, BezierObj->Grid(i,j).first,
                                            &BezierObj->virtual_Grid(i, j).pos);
            if (BezierObj->showVerticals) { // 显示曲面法线
                BezierObj->Grid2D(i,j).second = spotEyeScreenGo(ScreenEyeL, BezierObj->Grid(i,j).second,
                                            &BezierObj->virtual_Grid(i, j).verticalP);
                //cout << "~~second:" << _Grid2D[i*BezierObj->N_v+j].second.x << "," << _Grid2D[i*BezierObj->N_v+j].second.y << endl;
            }else {
                spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->Grid(i,j).second,
                                            &BezierObj->virtual_Grid(i, j).verticalP);
            }
        }
    }
    BezierObj->moveFreshStatus();

    if (BezierObj->fastIteration || BezierObj->showEdgeRect) {
        for(int i=0;i<BezierObj->N_u; ++i) { // 只要屏幕系 不要2D
        spotEyeScreenGo_no2D(ScreenEyeL,  BezierObj->Grid_edgeTop[i].first,
                                            &BezierObj->virtual_Grid_edgeTop[i].pos);
        spotEyeScreenGo_no2D(ScreenEyeL,  BezierObj->Grid_edgeTop[i].second,
                                            &BezierObj->virtual_Grid_edgeTop[i].verticalP);
        }
        for(int i=0;i<BezierObj->N_u; ++i) { // 只要屏幕系 不要2D
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierObj->Grid_edgeBottom[i].first,
                                                &BezierObj->virtual_Grid_edgeBottom[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierObj->Grid_edgeBottom[i].second,
                                                &BezierObj->virtual_Grid_edgeBottom[i].verticalP);
        }
        for(int i=0;i<BezierObj->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierObj->Grid_edgeLeft[i].first,
                                                &BezierObj->virtual_Grid_edgeLeft[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierObj->Grid_edgeLeft[i].second,
                                                &BezierObj->virtual_Grid_edgeLeft[i].verticalP);
        }
        for(int i=0;i<BezierObj->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierObj->Grid_edgeRight[i].first,
                                                &BezierObj->virtual_Grid_edgeRight[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierObj->Grid_edgeRight[i].second,
                                                &BezierObj->virtual_Grid_edgeRight[i].verticalP);
        }
    }

    if (BezierObj->debugMode == 2) {
        BezierObj->freshBox4Display(AxisTilt);
    }else if (BezierObj->debugMode == 3) {
        BezierObj->freshBox9Display(AxisTilt);
    }else if (BezierObj->debugMode == 4) {
        BezierObj->freshBox4Display(AxisTilt);
        BezierObj->freshBox9Display(AxisTilt);
    }


    // 刷新坐标 3D -> 2D


    //glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z };
    //printf("axis_0_0_0:%f,%f,%f\n",axis_0_0_0.y,axis_0_0_0.x,axis_0_0_0.z);


    // 3D xyz三步走 每步xyz都要动 都要 动
    glm::vec3 ltnXYZ = AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.ltnSet.x,
                                                BezierObj->scanBox3D_unchange.ltnSet.y,
                                                BezierObj->scanBox3D_unchange.ltnSet.z);

    glm::vec3 rtnXYZ=AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.rtnSet.x,
                                                BezierObj->scanBox3D_unchange.rtnSet.y,
                                                BezierObj->scanBox3D_unchange.rtnSet.z);

    glm::vec3 rbnXYZ=AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.rbnSet.x,
                                                BezierObj->scanBox3D_unchange.rbnSet.y,
                                                BezierObj->scanBox3D_unchange.rbnSet.z);

    glm::vec3 lbnXYZ=AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.lbnSet.x,
                                                BezierObj->scanBox3D_unchange.lbnSet.y,
                                                BezierObj->scanBox3D_unchange.lbnSet.z);

    glm::vec3 ltfXYZ=AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.ltfSet.x,
                                                BezierObj->scanBox3D_unchange.ltfSet.y,
                                                BezierObj->scanBox3D_unchange.ltfSet.z);

    glm::vec3 rtfXYZ=AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.rtfSet.x,
                                                BezierObj->scanBox3D_unchange.rtfSet.y,
                                                BezierObj->scanBox3D_unchange.rtfSet.z);

    glm::vec3 rbfXYZ=AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.rbfSet.x,
                                                BezierObj->scanBox3D_unchange.rbfSet.y,
                                                BezierObj->scanBox3D_unchange.rbfSet.z);

    glm::vec3 lbfXYZ=AxisTilt->AxisTilt2world(BezierObj->scanBox3D_unchange.lbfSet.x,
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

    couple_ltn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.ltnSet, &BezierObj->virtual_scanBox3D.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.rtnSet, &BezierObj->virtual_scanBox3D.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.rbnSet, &BezierObj->virtual_scanBox3D.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.lbnSet, &BezierObj->virtual_scanBox3D.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.ltfSet, &BezierObj->virtual_scanBox3D.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.rtfSet, &BezierObj->virtual_scanBox3D.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.rbfSet, &BezierObj->virtual_scanBox3D.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.lbfSet, &BezierObj->virtual_scanBox3D.lbfSet);

    couple_Center = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.center,&BezierObj->virtual_scanBox3D.center); // 中心

    // 刷新坐标 3D -> 2D
    BezierObj->setBox2D(couple_ltn, couple_rtn,couple_rbn, couple_lbn,
                        couple_ltf, couple_rtf,couple_rbf, couple_lbf,
                        couple_Center);
}




void freshBezier334_P_Grid_XY_Go(Bezier33Edge4* BezierObj, ScreenDemo* ScreenEyeL) {
    //glm::vec2 _P2D[5][5];


    for(int i=0;i<5; ++i) {
        for(int j = 0; j < 5; ++j) {
            BezierObj->P2D[i][j] = spotEyeScreenGo(ScreenEyeL, BezierObj->P[i][j],
                                        &BezierObj->virtual_P[i][j]);
        }
    }
    //BezierObj->set_P_XY(_P2D);
    //array<array<pair<glm::vec2, glm::vec2>, BezierObj->N_u>, BezierObj->N_v> _Grid2D;
    for(int i=0;i<BezierObj->N_v; ++i) {
        for(int j = 0; j < BezierObj->N_u; ++j) {
            BezierObj->Grid2D(i,j).first = spotEyeScreenGo(ScreenEyeL, BezierObj->Grid(i,j).first,
                                            &BezierObj->virtual_Grid(i, j).pos);
            if (BezierObj->showVerticals) { // 显示曲面法线
                BezierObj->Grid2D(i,j).second = spotEyeScreenGo(ScreenEyeL, BezierObj->Grid(i,j).second,
                                            &BezierObj->virtual_Grid(i, j).verticalP);
            }else {
                spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->Grid(i,j).second,
                                            &BezierObj->virtual_Grid(i, j).verticalP);
            }
        }
    }
    BezierObj->moveFreshStatus();

    if (BezierObj->fastIteration || BezierObj->showEdgeRect) {
        for(int i=0;i<BezierObj->N_u; ++i) { // 只要屏幕系 不要2D
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->Grid_edgeTop[i].first,
                                                &BezierObj->virtual_Grid_edgeTop[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->Grid_edgeTop[i].second,
                                                &BezierObj->virtual_Grid_edgeTop[i].verticalP);
        }
        for(int i=0;i<BezierObj->N_u; ++i) { // 只要屏幕系 不要2D
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->Grid_edgeBottom[i].first,
                                                &BezierObj->virtual_Grid_edgeBottom[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->Grid_edgeBottom[i].second,
                                                &BezierObj->virtual_Grid_edgeBottom[i].verticalP);
        }
        for(int i=0;i<BezierObj->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->Grid_edgeLeft[i].first,
                                                &BezierObj->virtual_Grid_edgeLeft[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->Grid_edgeLeft[i].second,
                                                &BezierObj->virtual_Grid_edgeLeft[i].verticalP);
        }
        for(int i=0;i<BezierObj->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->Grid_edgeRight[i].first,
                                                &BezierObj->virtual_Grid_edgeRight[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL, BezierObj->Grid_edgeRight[i].second,
                                                &BezierObj->virtual_Grid_edgeRight[i].verticalP);
        }
    }


    glm::vec2 couple_ltn{};
    glm::vec2 couple_rtn{};
    glm::vec2 couple_rbn{};
    glm::vec2 couple_lbn{};

    glm::vec2 couple_ltf{};
    glm::vec2 couple_rtf{};
    glm::vec2 couple_rbf{};
    glm::vec2 couple_lbf{};

    glm::vec2 couple_Center{};

    couple_ltn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.ltnSet, &BezierObj->virtual_scanBox3D.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.rtnSet, &BezierObj->virtual_scanBox3D.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.rbnSet, &BezierObj->virtual_scanBox3D.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.lbnSet, &BezierObj->virtual_scanBox3D.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.ltfSet, &BezierObj->virtual_scanBox3D.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.rtfSet, &BezierObj->virtual_scanBox3D.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.rbfSet, &BezierObj->virtual_scanBox3D.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.lbfSet, &BezierObj->virtual_scanBox3D.lbfSet);



    couple_Center = spotEyeScreenGo(ScreenEyeL, BezierObj->scanBox3D.center,&BezierObj->virtual_scanBox3D.center); // 中心

    // 刷新坐标 3D -> 2D
    BezierObj->setBox2D(couple_ltn, couple_rtn,couple_rbn, couple_lbn,
                        couple_ltf, couple_rtf,couple_rbf, couple_lbf,
                        couple_Center);
}
void freshBezier334Mirror_by_axis_go(Bezier33Edge4Mirror* BezierMirror, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL) {


    glm::vec3 _P[5][5];
    for(int i=0;i<5; ++i){
        for(int j=0;j<5; ++j){
            _P[i][j] = AxisTilt->AxisTilt2world(BezierMirror->P_unchange[i][j].x,
                                    BezierMirror->P_unchange[i][j].y,
                                    BezierMirror->P_unchange[i][j].z);
        }
    }BezierMirror->set_P_XYZ(_P);


    for(int i=0;i<BezierMirror->N_v; ++i) {
        for(int j = 0; j < BezierMirror->N_u; ++j) {

            BezierMirror->Grid(i,j).first =
                            AxisTilt->AxisTilt2world(BezierMirror->Grid_unchange(i,j).first.x,
                                                    BezierMirror->Grid_unchange(i,j).first.y,
                                                    BezierMirror->Grid_unchange(i,j).first.z);

            BezierMirror->Grid(i,j).second =
             AxisTilt->AxisTilt2world(BezierMirror->Grid_unchange(i,j).second.x,
                                     BezierMirror->Grid_unchange(i,j).second.y,
                                     BezierMirror->Grid_unchange(i,j).second.z);

        }
    }
    if (BezierMirror->fastIteration || BezierMirror->showEdgeRect) {
        for(int i=0;i<BezierMirror->N_u; ++i) {
            // 基向量 仿射变换
            BezierMirror->Grid_edgeTop[i].first =
                        AxisTilt->AxisTilt2world(BezierMirror->Grid_edgeTop_unchange[i].first.x,
                                                BezierMirror->Grid_edgeTop_unchange[i].first.y,
                                                BezierMirror->Grid_edgeTop_unchange[i].first.z);

            BezierMirror->Grid_edgeTop[i].second =
             AxisTilt->AxisTilt2world(BezierMirror->Grid_edgeTop_unchange[i].second.x,
                                     BezierMirror->Grid_edgeTop_unchange[i].second.y,
                                     BezierMirror->Grid_edgeTop_unchange[i].second.z);
        }

        for(int i=0;i<BezierMirror->N_u; ++i) {
            // 基向量 仿射变换
            BezierMirror->Grid_edgeBottom[i].first =
                                    AxisTilt->AxisTilt2world(BezierMirror->Grid_edgeBottom_unchange[i].first.x,
                                                            BezierMirror->Grid_edgeBottom_unchange[i].first.y,
                                                            BezierMirror->Grid_edgeBottom_unchange[i].first.z);

            BezierMirror->Grid_edgeBottom[i].second =
             AxisTilt->AxisTilt2world(BezierMirror->Grid_edgeBottom_unchange[i].second.x,
                                     BezierMirror->Grid_edgeBottom_unchange[i].second.y,
                                     BezierMirror->Grid_edgeBottom_unchange[i].second.z);
        }

        for(int i=0;i<BezierMirror->N_v; ++i) {
            // 基向量 仿射变换
            BezierMirror->Grid_edgeLeft[i].first =
            AxisTilt->AxisTilt2world(BezierMirror->Grid_edgeLeft_unchange[i].first.x,
                                    BezierMirror->Grid_edgeLeft_unchange[i].first.y,
                                    BezierMirror->Grid_edgeLeft_unchange[i].first.z);

            BezierMirror->Grid_edgeLeft[i].second =
             AxisTilt->AxisTilt2world(BezierMirror->Grid_edgeLeft_unchange[i].second.x,
                                     BezierMirror->Grid_edgeLeft_unchange[i].second.y,
                                     BezierMirror->Grid_edgeLeft_unchange[i].second.z);
        }

        for(int i=0;i<BezierMirror->N_v; ++i) {
            // 基向量 仿射变换
            BezierMirror->Grid_edgeRight[i].first =
                        AxisTilt->AxisTilt2world(BezierMirror->Grid_edgeRight_unchange[i].first.x,
                                                BezierMirror->Grid_edgeRight_unchange[i].first.y,
                                                BezierMirror->Grid_edgeRight_unchange[i].first.z);

            BezierMirror->Grid_edgeRight[i].second =
             AxisTilt->AxisTilt2world(BezierMirror->Grid_edgeRight_unchange[i].second.x,
                                     BezierMirror->Grid_edgeRight_unchange[i].second.y,
                                     BezierMirror->Grid_edgeRight_unchange[i].second.z);
        }
    }


    for(int i=0;i<5; ++i) {
        for(int j = 0; j < 5; ++j) {
            BezierMirror->P2D[i][j] = spotEyeScreenGo(ScreenEyeL, BezierMirror->P[i][j],
                                        &BezierMirror->virtual_P[i][j]);
        }
    }

    for(int i=0;i<BezierMirror->N_v; ++i) {
        for(int j = 0; j < BezierMirror->N_u; ++j) {
            BezierMirror->Grid2D(i,j).first = spotEyeScreenGo(ScreenEyeL, BezierMirror->Grid(i,j).first,
                                            &BezierMirror->virtual_Grid(i, j).pos);
            if (BezierMirror->showVerticals) { // 显示曲面法线
                BezierMirror->Grid2D(i,j).second = spotEyeScreenGo(ScreenEyeL, BezierMirror->Grid(i,j).second,
                                            &BezierMirror->virtual_Grid(i, j).verticalP);
                //cout << "~~second:" << _Grid2D[i*BezierObj->N_v+j].second.x << "," << _Grid2D[i*BezierObj->N_v+j].second.y << endl;
            }else {
                spotEyeScreenGo_no2D(ScreenEyeL, BezierMirror->Grid(i,j).second,
                                            &BezierMirror->virtual_Grid(i, j).verticalP);
            }
        }
    }
    BezierMirror->moveFreshStatus();

    if (BezierMirror->fastIteration || BezierMirror->showEdgeRect) {
        for(int i=0;i<BezierMirror->N_u; ++i) { // 只要屏幕系 不要2D
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeTop[i].first,
                                                &BezierMirror->virtual_Grid_edgeTop[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeTop[i].second,
                                                &BezierMirror->virtual_Grid_edgeTop[i].verticalP);
        }
        for(int i=0;i<BezierMirror->N_u; ++i) { // 只要屏幕系 不要2D
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeBottom[i].first,
                                                &BezierMirror->virtual_Grid_edgeBottom[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeBottom[i].second,
                                                &BezierMirror->virtual_Grid_edgeBottom[i].verticalP);
        }
        for(int i=0;i<BezierMirror->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeLeft[i].first,
                                                &BezierMirror->virtual_Grid_edgeLeft[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeLeft[i].second,
                                                &BezierMirror->virtual_Grid_edgeLeft[i].verticalP);
        }
        for(int i=0;i<BezierMirror->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeRight[i].first,
                                                &BezierMirror->virtual_Grid_edgeRight[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeRight[i].second,
                                                &BezierMirror->virtual_Grid_edgeRight[i].verticalP);
        }
    }



    // 刷新坐标 3D -> 2D
    if (BezierMirror->debugMode == 2) {
        BezierMirror->freshBox4Display(AxisTilt);
    }else if (BezierMirror->debugMode == 3) {
        BezierMirror->freshBox9Display(AxisTilt);
    }else if (BezierMirror->debugMode == 4) {
        BezierMirror->freshBox4Display(AxisTilt);
        BezierMirror->freshBox9Display(AxisTilt);
    }


    // 3D xyz三步走 每步xyz都要动 都要 动

    glm::vec3 ltnXYZ = AxisTilt->AxisTilt2world(BezierMirror->scanBox3D_unchange.ltnSet.x,
                                                BezierMirror->scanBox3D_unchange.ltnSet.y,
                                                BezierMirror->scanBox3D_unchange.ltnSet.z);

    glm::vec3 rtnXYZ=AxisTilt->AxisTilt2world(BezierMirror->scanBox3D_unchange.rtnSet.x,
                                                BezierMirror->scanBox3D_unchange.rtnSet.y,
                                                BezierMirror->scanBox3D_unchange.rtnSet.z);

    glm::vec3 rbnXYZ=AxisTilt->AxisTilt2world(BezierMirror->scanBox3D_unchange.rbnSet.x,
                                                BezierMirror->scanBox3D_unchange.rbnSet.y,
                                                BezierMirror->scanBox3D_unchange.rbnSet.z);

    glm::vec3 lbnXYZ=AxisTilt->AxisTilt2world(BezierMirror->scanBox3D_unchange.lbnSet.x,
                                                BezierMirror->scanBox3D_unchange.lbnSet.y,
                                                BezierMirror->scanBox3D_unchange.lbnSet.z);

    glm::vec3 ltfXYZ=AxisTilt->AxisTilt2world(BezierMirror->scanBox3D_unchange.ltfSet.x,
                                                BezierMirror->scanBox3D_unchange.ltfSet.y,
                                                BezierMirror->scanBox3D_unchange.ltfSet.z);

    glm::vec3 rtfXYZ=AxisTilt->AxisTilt2world(BezierMirror->scanBox3D_unchange.rtfSet.x,
                                                BezierMirror->scanBox3D_unchange.rtfSet.y,
                                                BezierMirror->scanBox3D_unchange.rtfSet.z);

    glm::vec3 rbfXYZ=AxisTilt->AxisTilt2world(BezierMirror->scanBox3D_unchange.rbfSet.x,
                                                BezierMirror->scanBox3D_unchange.rbfSet.y,
                                                BezierMirror->scanBox3D_unchange.rbfSet.z);

    glm::vec3 lbfXYZ=AxisTilt->AxisTilt2world(BezierMirror->scanBox3D_unchange.lbfSet.x,
                                                BezierMirror->scanBox3D_unchange.lbfSet.y,
                                                BezierMirror->scanBox3D_unchange.lbfSet.z);

    BezierMirror->setBox3D(ltnXYZ, rtnXYZ, rbnXYZ, lbnXYZ,
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

    couple_ltn = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.ltnSet, &BezierMirror->virtual_scanBox3D.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.rtnSet, &BezierMirror->virtual_scanBox3D.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.rbnSet, &BezierMirror->virtual_scanBox3D.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.lbnSet, &BezierMirror->virtual_scanBox3D.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.ltfSet, &BezierMirror->virtual_scanBox3D.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.rtfSet, &BezierMirror->virtual_scanBox3D.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.rbfSet, &BezierMirror->virtual_scanBox3D.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.lbfSet, &BezierMirror->virtual_scanBox3D.lbfSet);

    couple_Center = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.center,&BezierMirror->virtual_scanBox3D.center); // 中心

    // 刷新坐标 3D -> 2D
    BezierMirror->setBox2D(couple_ltn, couple_rtn,couple_rbn, couple_lbn,
                        couple_ltf, couple_rtf,couple_rbf, couple_lbf,
                        couple_Center);
}
void bezier334Mirror_P_Grid_XY_Go(Bezier33Edge4Mirror* BezierMirror, ScreenDemo* ScreenEyeL) {
    for(int i=0;i<5; ++i) {
        for(int j = 0; j < 5; ++j) {
            BezierMirror->P2D[i][j] = spotEyeScreenGo(ScreenEyeL, BezierMirror->P[i][j],
                                        &BezierMirror->virtual_P[i][j]);
        }
    }

    for(int i=0;i<BezierMirror->N_v; ++i) {
        for(int j = 0; j < BezierMirror->N_u; ++j) {
            BezierMirror->Grid2D(i,j).first = spotEyeScreenGo(ScreenEyeL, BezierMirror->Grid(i,j).first,
                                            &BezierMirror->virtual_Grid(i, j).pos);
            if (BezierMirror->showVerticals) { // 显示曲面法线
                BezierMirror->Grid2D(i,j).second = spotEyeScreenGo(ScreenEyeL, BezierMirror->Grid(i,j).second,
                                            &BezierMirror->virtual_Grid(i, j).verticalP);
            }else {
                spotEyeScreenGo_no2D(ScreenEyeL, BezierMirror->Grid(i,j).second,
                                            &BezierMirror->virtual_Grid(i, j).verticalP);
            }
        }
    }
    BezierMirror->moveFreshStatus();

    if (BezierMirror->fastIteration || BezierMirror->showEdgeRect) {
        for(int i=0;i<BezierMirror->N_u; ++i) { // 只要屏幕系 不要2D
            spotEyeScreenGo_no2D(ScreenEyeL, BezierMirror->Grid_edgeTop[i].first,
                                                &BezierMirror->virtual_Grid_edgeTop[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL, BezierMirror->Grid_edgeTop[i].second,
                                                &BezierMirror->virtual_Grid_edgeTop[i].verticalP);
        }
        for(int i=0;i<BezierMirror->N_u; ++i) { // 只要屏幕系 不要2D
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeBottom[i].first,
                                                &BezierMirror->virtual_Grid_edgeBottom[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeBottom[i].second,
                                                &BezierMirror->virtual_Grid_edgeBottom[i].verticalP);
        }
        for(int i=0;i<BezierMirror->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL, BezierMirror->Grid_edgeLeft[i].first,
                                                &BezierMirror->virtual_Grid_edgeLeft[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL, BezierMirror->Grid_edgeLeft[i].second,
                                                &BezierMirror->virtual_Grid_edgeLeft[i].verticalP);
        }
        for(int i=0;i<BezierMirror->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeRight[i].first,
                                                &BezierMirror->virtual_Grid_edgeRight[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierMirror->Grid_edgeRight[i].second,
                                                &BezierMirror->virtual_Grid_edgeRight[i].verticalP);
        }
    }


    glm::vec2 couple_ltn{};
    glm::vec2 couple_rtn{};
    glm::vec2 couple_rbn{};
    glm::vec2 couple_lbn{};

    glm::vec2 couple_ltf{};
    glm::vec2 couple_rtf{};
    glm::vec2 couple_rbf{};
    glm::vec2 couple_lbf{};

    glm::vec2 couple_Center{};

    couple_ltn = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.ltnSet, &BezierMirror->virtual_scanBox3D.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.rtnSet, &BezierMirror->virtual_scanBox3D.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.rbnSet, &BezierMirror->virtual_scanBox3D.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.lbnSet, &BezierMirror->virtual_scanBox3D.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.ltfSet, &BezierMirror->virtual_scanBox3D.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.rtfSet, &BezierMirror->virtual_scanBox3D.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.rbfSet, &BezierMirror->virtual_scanBox3D.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.lbfSet, &BezierMirror->virtual_scanBox3D.lbfSet);



    couple_Center = spotEyeScreenGo(ScreenEyeL, BezierMirror->scanBox3D.center,&BezierMirror->virtual_scanBox3D.center); // 中心

    // 刷新坐标 3D -> 2D
    BezierMirror->setBox2D(couple_ltn, couple_rtn,couple_rbn, couple_lbn,
                        couple_ltf, couple_rtf,couple_rbf, couple_lbf,
                        couple_Center);
}

void freshBezier3Img_by_axis_go(Bezier3Img* BezierImg, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL) {


    glm::vec3 _P[5][5];
    for(int i=0;i<5; ++i){
        for(int j=0;j<5; ++j){
            _P[i][j] = AxisTilt->AxisTilt2world(BezierImg->P_unchange[i][j].x,
                                BezierImg->P_unchange[i][j].y,
                                BezierImg->P_unchange[i][j].z);
        }
    }BezierImg->set_P_XYZ(_P);


    for(int i=0;i<BezierImg->N_v; ++i) {
        for(int j = 0; j < BezierImg->N_u; ++j) {

            BezierImg->Grid(i,j).first =
                                        AxisTilt->AxisTilt2world(BezierImg->Grid_unchange(i,j).first.x,
                                                                BezierImg->Grid_unchange(i,j).first.y,
                                                                BezierImg->Grid_unchange(i,j).first.z);
            BezierImg->Grid(i,j).second =
             AxisTilt->AxisTilt2world(BezierImg->Grid_unchange(i,j).second.x,
                                     BezierImg->Grid_unchange(i,j).second.y,
                                     BezierImg->Grid_unchange(i,j).second.z);
        }
    }
    if (BezierImg->fastIteration || BezierImg->showEdgeRect) {
        for(int i=0;i<BezierImg->N_u; ++i) {
            // 基向量 仿射变换
            BezierImg->Grid_edgeTop[i].first =
            AxisTilt->AxisTilt2world(BezierImg->Grid_edgeTop_unchange[i].first.x,
                                    BezierImg->Grid_edgeTop_unchange[i].first.y,
                                    BezierImg->Grid_edgeTop_unchange[i].first.z);

            BezierImg->Grid_edgeTop[i].second =
             AxisTilt->AxisTilt2world(BezierImg->Grid_edgeTop_unchange[i].second.x,
                                     BezierImg->Grid_edgeTop_unchange[i].second.y,
                                     BezierImg->Grid_edgeTop_unchange[i].second.z);
        }

        for(int i=0;i<BezierImg->N_u; ++i) {
            // 基向量 仿射变换
            BezierImg->Grid_edgeBottom[i].first =
                        AxisTilt->AxisTilt2world(BezierImg->Grid_edgeBottom_unchange[i].first.x,
                                                BezierImg->Grid_edgeBottom_unchange[i].first.y,
                                                BezierImg->Grid_edgeBottom_unchange[i].first.z);

            BezierImg->Grid_edgeBottom[i].second =
             AxisTilt->AxisTilt2world(BezierImg->Grid_edgeBottom_unchange[i].second.x,
                                     BezierImg->Grid_edgeBottom_unchange[i].second.y,
                                     BezierImg->Grid_edgeBottom_unchange[i].second.z);
        }

        for(int i=0;i<BezierImg->N_v; ++i) {
            // 基向量 仿射变换
            BezierImg->Grid_edgeLeft[i].first =
                                    AxisTilt->AxisTilt2world(BezierImg->Grid_edgeLeft_unchange[i].first.x,
                                                            BezierImg->Grid_edgeLeft_unchange[i].first.y,
                                                            BezierImg->Grid_edgeLeft_unchange[i].first.z);

            BezierImg->Grid_edgeLeft[i].second =
             AxisTilt->AxisTilt2world(BezierImg->Grid_edgeLeft_unchange[i].second.x,
                                     BezierImg->Grid_edgeLeft_unchange[i].second.y,
                                     BezierImg->Grid_edgeLeft_unchange[i].second.z);
        }

        for(int i=0;i<BezierImg->N_v; ++i) {
            // 基向量 仿射变换
            BezierImg->Grid_edgeRight[i].first =
                                                AxisTilt->AxisTilt2world(BezierImg->Grid_edgeRight_unchange[i].first.x,
                                                                        BezierImg->Grid_edgeRight_unchange[i].first.y,
                                                                        BezierImg->Grid_edgeRight_unchange[i].first.z);

            BezierImg->Grid_edgeRight[i].second =
             AxisTilt->AxisTilt2world(BezierImg->Grid_edgeRight_unchange[i].second.x,
                                     BezierImg->Grid_edgeRight_unchange[i].second.y,
                                     BezierImg->Grid_edgeRight_unchange[i].second.z);
        }
    }


    for(int i=0;i<5; ++i) {
        for(int j = 0; j < 5; ++j) {
            BezierImg->P2D[i][j] = spotEyeScreenGo(ScreenEyeL, BezierImg->P[i][j],
                                        &BezierImg->virtual_P[i][j]);
        }
    }

    for(int i=0;i<BezierImg->N_v; ++i) {
        for(int j = 0; j < BezierImg->N_u; ++j) {
            BezierImg->Grid2D(i,j).first = spotEyeScreenGo(ScreenEyeL, BezierImg->Grid(i,j).first,
                                            &BezierImg->virtual_Grid(i, j).pos);
            if (BezierImg->showVerticals) { // 显示曲面法线
                BezierImg->Grid2D(i,j).second = spotEyeScreenGo(ScreenEyeL, BezierImg->Grid(i,j).second,
                                            &BezierImg->virtual_Grid(i, j).verticalP);
                //cout << "~~second:" << _Grid2D[i*BezierObj->N_v+j].second.x << "," << _Grid2D[i*BezierObj->N_v+j].second.y << endl;
            }else {
                spotEyeScreenGo_no2D(ScreenEyeL, BezierImg->Grid(i,j).second,
                                            &BezierImg->virtual_Grid(i, j).verticalP);
            }
        }
    }
    BezierImg->moveFreshStatus();

    if (BezierImg->fastIteration || BezierImg->showEdgeRect) {
        for(int i=0;i<BezierImg->N_u; ++i) { // 只要屏幕系 不要2D
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeTop[i].first,
                                                &BezierImg->virtual_Grid_edgeTop[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeTop[i].second,
                                                &BezierImg->virtual_Grid_edgeTop[i].verticalP);
        }
        for(int i=0;i<BezierImg->N_u; ++i) { // 只要屏幕系 不要2D
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeBottom[i].first,
                                                &BezierImg->virtual_Grid_edgeBottom[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeBottom[i].second,
                                                &BezierImg->virtual_Grid_edgeBottom[i].verticalP);
        }
        for(int i=0;i<BezierImg->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeLeft[i].first,
                                                &BezierImg->virtual_Grid_edgeLeft[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeLeft[i].second,
                                                &BezierImg->virtual_Grid_edgeLeft[i].verticalP);
        }
        for(int i=0;i<BezierImg->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeRight[i].first,
                                                &BezierImg->virtual_Grid_edgeRight[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeRight[i].second,
                                                &BezierImg->virtual_Grid_edgeRight[i].verticalP);
        }
    }


    // 刷新坐标 3D -> 2D
    if (BezierImg->debugMode == 2) {
        BezierImg->freshBox4Display(AxisTilt);
    }else if (BezierImg->debugMode == 3) {
        BezierImg->freshBox9Display(AxisTilt);
    }else if (BezierImg->debugMode == 4) {
        BezierImg->freshBox4Display(AxisTilt);
        BezierImg->freshBox9Display(AxisTilt);
    }


    // 3D xyz三步走 每步xyz都要动 都要 动
    glm::vec3 ltnXYZ = AxisTilt->AxisTilt2world(BezierImg->scanBox3D_unchange.ltnSet.x,
                                                BezierImg->scanBox3D_unchange.ltnSet.y,
                                                BezierImg->scanBox3D_unchange.ltnSet.z);

    glm::vec3 rtnXYZ=AxisTilt->AxisTilt2world(BezierImg->scanBox3D_unchange.rtnSet.x,
                                                BezierImg->scanBox3D_unchange.rtnSet.y,
                                                BezierImg->scanBox3D_unchange.rtnSet.z);

    glm::vec3 rbnXYZ=AxisTilt->AxisTilt2world(BezierImg->scanBox3D_unchange.rbnSet.x,
                                                BezierImg->scanBox3D_unchange.rbnSet.y,
                                                BezierImg->scanBox3D_unchange.rbnSet.z);

    glm::vec3 lbnXYZ=AxisTilt->AxisTilt2world(BezierImg->scanBox3D_unchange.lbnSet.x,
                                                BezierImg->scanBox3D_unchange.lbnSet.y,
                                                BezierImg->scanBox3D_unchange.lbnSet.z);

    glm::vec3 ltfXYZ=AxisTilt->AxisTilt2world(BezierImg->scanBox3D_unchange.ltfSet.x,
                                                BezierImg->scanBox3D_unchange.ltfSet.y,
                                                BezierImg->scanBox3D_unchange.ltfSet.z);

    glm::vec3 rtfXYZ=AxisTilt->AxisTilt2world(BezierImg->scanBox3D_unchange.rtfSet.x,
                                                BezierImg->scanBox3D_unchange.rtfSet.y,
                                                BezierImg->scanBox3D_unchange.rtfSet.z);

    glm::vec3 rbfXYZ=AxisTilt->AxisTilt2world(BezierImg->scanBox3D_unchange.rbfSet.x,
                                                BezierImg->scanBox3D_unchange.rbfSet.y,
                                                BezierImg->scanBox3D_unchange.rbfSet.z);

    glm::vec3 lbfXYZ=AxisTilt->AxisTilt2world(BezierImg->scanBox3D_unchange.lbfSet.x,
                                                BezierImg->scanBox3D_unchange.lbfSet.y,
                                                BezierImg->scanBox3D_unchange.lbfSet.z);

    BezierImg->setBox3D(ltnXYZ, rtnXYZ, rbnXYZ, lbnXYZ,
                        ltfXYZ, rtfXYZ, rbfXYZ, lbfXYZ); // 更新3D坐标 center back


    BezierImg->setBox3D(ltnXYZ, rtnXYZ, rbnXYZ, lbnXYZ,
                        ltfXYZ, rtfXYZ, rbfXYZ, lbfXYZ); // 更新3D坐标 center back


    glm::vec2 couple_ltn{0};
    glm::vec2 couple_rtn{0};
    glm::vec2 couple_rbn{0};
    glm::vec2 couple_lbn{0};

    glm::vec2 couple_ltf{0};
    glm::vec2 couple_rtf{0};
    glm::vec2 couple_rbf{0};
    glm::vec2 couple_lbf{0};

    glm::vec2 couple_Center{0};

    couple_ltn = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.ltnSet, &BezierImg->virtual_scanBox3D.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.rtnSet, &BezierImg->virtual_scanBox3D.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.rbnSet, &BezierImg->virtual_scanBox3D.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.lbnSet, &BezierImg->virtual_scanBox3D.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.ltfSet, &BezierImg->virtual_scanBox3D.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.rtfSet, &BezierImg->virtual_scanBox3D.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.rbfSet, &BezierImg->virtual_scanBox3D.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.lbfSet, &BezierImg->virtual_scanBox3D.lbfSet);

    couple_Center = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.center,&BezierImg->virtual_scanBox3D.center); // 中心

    // 刷新坐标 3D -> 2D
    BezierImg->setBox2D(couple_ltn, couple_rtn,couple_rbn, couple_lbn,
                        couple_ltf, couple_rtf,couple_rbf, couple_lbf,
                        couple_Center);
}
void bezier3Img_P_Grid_XY_Go(Bezier3Img* BezierImg, ScreenDemo* ScreenEyeL) {
    for(int i=0;i<5; ++i) {
        for(int j = 0; j < 5; ++j) {
            BezierImg->P2D[i][j] = spotEyeScreenGo(ScreenEyeL, BezierImg->P[i][j],
                                        &BezierImg->virtual_P[i][j]);
        }
    }

    for(int i=0;i<BezierImg->N_v; ++i) {
        for(int j = 0; j < BezierImg->N_u; ++j) {
            BezierImg->Grid2D(i,j).first = spotEyeScreenGo(ScreenEyeL, BezierImg->Grid(i,j).first,
                                            &BezierImg->virtual_Grid(i, j).pos);
            if (BezierImg->showVerticals) { // 显示曲面法线
                BezierImg->Grid2D(i,j).second = spotEyeScreenGo(ScreenEyeL, BezierImg->Grid(i,j).second,
                                            &BezierImg->virtual_Grid(i, j).verticalP);
            }else {
                spotEyeScreenGo_no2D(ScreenEyeL, BezierImg->Grid(i,j).second,
                                            &BezierImg->virtual_Grid(i, j).verticalP);
            }
        }
    }
    BezierImg->moveFreshStatus();

    if (BezierImg->fastIteration || BezierImg->showEdgeRect) {
        for(int i=0;i<BezierImg->N_u; ++i) { // 只要屏幕系 不要2D
            spotEyeScreenGo_no2D(ScreenEyeL, BezierImg->Grid_edgeTop[i].first,
                                                &BezierImg->virtual_Grid_edgeTop[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL, BezierImg->Grid_edgeTop[i].second,
                                                &BezierImg->virtual_Grid_edgeTop[i].verticalP);
        }
        for(int i=0;i<BezierImg->N_u; ++i) { // 只要屏幕系 不要2D
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeBottom[i].first,
                                                &BezierImg->virtual_Grid_edgeBottom[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeBottom[i].second,
                                                &BezierImg->virtual_Grid_edgeBottom[i].verticalP);
        }
        for(int i=0;i<BezierImg->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL, BezierImg->Grid_edgeLeft[i].first,
                                                &BezierImg->virtual_Grid_edgeLeft[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL, BezierImg->Grid_edgeLeft[i].second,
                                                &BezierImg->virtual_Grid_edgeLeft[i].verticalP);
        }
        for(int i=0;i<BezierImg->N_v; ++i) {
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeRight[i].first,
                                                &BezierImg->virtual_Grid_edgeRight[i].pos);
            spotEyeScreenGo_no2D(ScreenEyeL,  BezierImg->Grid_edgeRight[i].second,
                                                &BezierImg->virtual_Grid_edgeRight[i].verticalP);
        }
    }


    glm::vec2 couple_ltn{};
    glm::vec2 couple_rtn{};
    glm::vec2 couple_rbn{};
    glm::vec2 couple_lbn{};

    glm::vec2 couple_ltf{};
    glm::vec2 couple_rtf{};
    glm::vec2 couple_rbf{};
    glm::vec2 couple_lbf{};

    glm::vec2 couple_Center{};

    couple_ltn = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.ltnSet, &BezierImg->virtual_scanBox3D.ltnSet);
    couple_rtn = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.rtnSet, &BezierImg->virtual_scanBox3D.rtnSet);
    couple_rbn = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.rbnSet, &BezierImg->virtual_scanBox3D.rbnSet);

    couple_lbn = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.lbnSet, &BezierImg->virtual_scanBox3D.lbnSet);

    couple_ltf = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.ltfSet, &BezierImg->virtual_scanBox3D.ltfSet);
    couple_rtf = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.rtfSet, &BezierImg->virtual_scanBox3D.rtfSet);
    couple_rbf = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.rbfSet, &BezierImg->virtual_scanBox3D.rbfSet);
    couple_lbf = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.lbfSet, &BezierImg->virtual_scanBox3D.lbfSet);



    couple_Center = spotEyeScreenGo(ScreenEyeL, BezierImg->scanBox3D.center,&BezierImg->virtual_scanBox3D.center); // 中心

    // 刷新坐标 3D -> 2D
    BezierImg->setBox2D(couple_ltn, couple_rtn,couple_rbn, couple_lbn,
                        couple_ltf, couple_rtf,couple_rbf, couple_lbf,
                        couple_Center);
}
#endif //POLYGONDISPLAY_BECUBICBEZIER_FUNC_H
