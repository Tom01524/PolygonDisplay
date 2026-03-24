//
// Created by iceoc0 on 2025/1/27.
//

#ifndef RECTANGLEDISPLAY_FOGPOINT_FUNC_H
#define RECTANGLEDISPLAY_FOGPOINT_FUNC_H

#include"calc_func_3D2D.h"


#include "../polygonClass/FogDemo.h" // wish once ONLY

// ScreenGo 模式 不需要移动

void FogObjMoveXYZ(FogObjDemo* FogObjMain, char key, float oneStep);
void FogPointTurnXYZ(FogObjDemo* FogObjMain, ScreenDemo* ScreenEye, RectDemo* footSquare, char key, float goAngle);
void FogPointCornerTurn(FogObjDemo* FogObjMain, ScreenDemo* ScreenEye, glm::vec3 rotateCenter, char key, float goAngle);

void freshFogObj_XY(FogObjDemo* FogObjMain, ScreenDemo* ScreenEyeL);
void freshFogObj_XY_L(FogObjDemo* FogObjMain, ScreenDemo* ScreenEyeL);
void freshFogCorner_XY_L(FogObjDemo* FogObjMain, ScreenDemo* ScreenEyeL);
void freshFogObj_XY_Go(FogObjDemo* FogObjMain, ScreenDemo* ScreenEyeL);
void freshFogCorner_XY_Go(FogObjDemo* FogObjMain, ScreenDemo* ScreenEyeL);

void freshFogObj_XY_by_axis(FogObjDemo* FogObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL, char key);
void freshFogObj_XY_by_axis_L(FogObjDemo* FogObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL, char key);

void FogObjMoveXYZ(FogObjDemo* FogObjMain, char key, float oneStep){
    // 移动雾点 无碰撞检测
//    glm::vec2 couple_center;
    size_t len = FogObjMain->fogPoints.size();
        switch (key) {
            case 'w':
                if (goForward) {
                    for (int i = 0; i < len; i++) {// 每个雾点的 movedX movedY movedZ
                        FogObjMain->fogPoints[i]->pos3D.z += oneStep;
                    }
                    FogObjMain->centerPos3D.z += oneStep; // 聚合体中心点 movedX movedY movedZ
                    FogObjMain->cornerMove('w',oneStep);
                }
                break;
            case 's':
                if (goBack) {
                    for (int i = 0; i < len; i++) {
                        FogObjMain->fogPoints[i]->pos3D.z -= oneStep;
                    }
                    FogObjMain->centerPos3D.z -= oneStep;
                    FogObjMain->cornerMove('s',oneStep);
                }
                break;
            case 'a':
                if (goLeft) {
                    for (int i = 0; i < len; i++) {
                        FogObjMain->fogPoints[i]->pos3D.x -= oneStep;
                    }
                    FogObjMain->centerPos3D.x -= oneStep;
                    FogObjMain->cornerMove('a',oneStep);
                }
                break;
            case 'd':
                if (goRight) {
                    for (int i = 0; i < len; i++) {
                        FogObjMain->fogPoints[i]->pos3D.x += oneStep;
                    }
                    FogObjMain->centerPos3D.x += oneStep;
                    FogObjMain->cornerMove('d',oneStep);
                }
                break;
            case 'q':
                if (goUp) {
                    for (int i = 0; i < len; i++) {
                        FogObjMain->fogPoints[i]->pos3D.y -= oneStep;
                    }
                    FogObjMain->centerPos3D.y -= oneStep;
                    FogObjMain->cornerMove('q',oneStep);
                }
                break;
            case 'e':
                if (goDown) {
                    for (int i = 0; i < len; i++) {
                        FogObjMain->fogPoints[i]->pos3D.y += oneStep;
                    }
                    FogObjMain->centerPos3D.y += oneStep;
                    FogObjMain->cornerMove('e',oneStep);
                }
                break;
        }

        // 3D→2D
//        couple_center = spotEyeScreenGo(ScreenEyeL, nullptr, FogObjMain->fogPoints[i]->pos3D.y, FogObjMain->fogPoints[i]->pos3D.x,
//                                        FogObjMain->fogPoints[i]->pos3D.z,nullptr);
//        FogObjMain->fogPoints[i]->pos2D.y = couple_center.y;
//        FogObjMain->fogPoints[i]->pos2D.x = couple_center.x;

}
void FogPointTurnXYZ(FogObjDemo* FogObjMain, ScreenDemo* ScreenEye, RectDemo* footSquare, char key, float goAngle){
    // 旋转雾点 无碰撞检测
    glm::vec3 rotateCenter = footSquare->tblrXYZ.center; // mode == 2
    size_t sumPoints = FogObjMain->fogPoints.size(); // 雾点数量
    glm::vec3 pointNow, objNow;
    switch (key) {
        case 'j':
            for(int i=0; i<sumPoints; i++){
                pointNow = turningByCenter(&rotateCenter,FogObjMain->fogPoints[i]->pos3D,'j', goAngle); // 雾点每个点旋转
                FogObjMain->fogPoints[i]->pos3D = pointNow; // 更新雾点位置
            }
            objNow = turningByCenter(&rotateCenter,FogObjMain->centerPos3D,'j', goAngle); // 雾点中心点旋转
            FogObjMain->centerPos3D = objNow; // 更新雾点中心点位置
            FogPointCornerTurn(FogObjMain, ScreenEye, rotateCenter, 'j', goAngle);
            break;
        case'l':
            for(int i=0; i<sumPoints; i++){
                pointNow = turningByCenter(&rotateCenter,FogObjMain->fogPoints[i]->pos3D,'l', goAngle); // 雾点每个点旋转
                FogObjMain->fogPoints[i]->pos3D = pointNow; // 更新雾点位置
            }
            objNow = turningByCenter(&rotateCenter,FogObjMain->centerPos3D,'l', goAngle); // 雾点中心点旋转
            FogObjMain->centerPos3D = objNow; // 更新雾点中心点位置
            FogPointCornerTurn(FogObjMain, ScreenEye, rotateCenter, 'l', goAngle);
            break;
        case 'i':
            for(int i=0; i<sumPoints; i++){
                pointNow = turningByCenter(&rotateCenter,FogObjMain->fogPoints[i]->pos3D,'i', goAngle); // 雾点每个点旋转
                FogObjMain->fogPoints[i]->pos3D = pointNow; // 更新雾点位置
            }
            objNow = turningByCenter(&rotateCenter,FogObjMain->centerPos3D,'i', goAngle); // 雾点中心点旋转
            FogObjMain->centerPos3D = objNow; // 更新雾点中心点位置
            FogPointCornerTurn(FogObjMain, ScreenEye, rotateCenter, 'i', goAngle);
            break;
        case 'k':
            for(int i=0; i<sumPoints; i++){
                pointNow = turningByCenter(&rotateCenter,FogObjMain->fogPoints[i]->pos3D,'k', goAngle); // 雾点每个点旋转
                FogObjMain->fogPoints[i]->pos3D = pointNow; // 更新雾点位置
            }
            objNow = turningByCenter(&rotateCenter,FogObjMain->centerPos3D,'k', goAngle); // 雾点中心点旋转
            FogObjMain->centerPos3D = objNow; // 更新雾点中心点位置
            FogPointCornerTurn(FogObjMain, ScreenEye, rotateCenter, 'k', goAngle);
            break;
        case 'u':
            for(int i=0; i<sumPoints; i++){
                pointNow = turningByCenter(&rotateCenter,FogObjMain->fogPoints[i]->pos3D,'u', goAngle); // 雾点每个点旋转
                FogObjMain->fogPoints[i]->pos3D = pointNow; // 更新雾点位置
            }
            objNow = turningByCenter(&rotateCenter,FogObjMain->centerPos3D,'u', goAngle); // 雾点中心点旋转
            FogObjMain->centerPos3D = objNow; // 更新雾点中心点位置
            FogPointCornerTurn(FogObjMain, ScreenEye, rotateCenter, 'u', goAngle);
            break;
        case 'o':
            for(int i=0; i<sumPoints; i++){
                pointNow = turningByCenter(&rotateCenter,FogObjMain->fogPoints[i]->pos3D,'o', goAngle); // 雾点每个点旋转
                FogObjMain->fogPoints[i]->pos3D = pointNow; // 更新雾点位置
            }
            objNow = turningByCenter(&rotateCenter,FogObjMain->centerPos3D,'o', goAngle); // 雾点中心点旋转
            FogObjMain->centerPos3D = objNow; // 更新雾点中心点位置
            FogPointCornerTurn(FogObjMain, ScreenEye, rotateCenter, 'o', goAngle);
            break;
    }
//    cout << "fog object xyz position: " << FogObjMain->centerPos3D.y << ", " << FogObjMain->centerPos3D.x << ", "
//         << FogObjMain->centerPos3D.z << endl;
}
void FogPointCornerTurn(FogObjDemo* FogObjMain, ScreenDemo* ScreenEye, glm::vec3 rotateCenter, char key, float goAngle){

    glm::vec3 pointNow;
    switch (key) {
        case 'j': // 转左
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltn,'j', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtn,'j', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbn,'j', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbn,'j', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltf,'j', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtf,'j', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbf,'j', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbf,'j', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbf = pointNow; // 更新雾点位置
            break;

        case'l': // 转右
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltn,'l', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtn,'l', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbn,'l', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbn,'l', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltf,'l', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtf,'l', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbf,'l', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbf,'l', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbf = pointNow; // 更新雾点位置
            break;
        case 'i': // 转上
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltn,'i', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtn,'i', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbn,'i', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbn,'i', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltf,'i', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtf,'i', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbf,'i', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbf,'i', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbf = pointNow; // 更新雾点位置
            break;
        case 'k': // 转下
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltn,'k', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtn,'k', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbn,'k', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbn,'k', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltf,'k', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtf,'k', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbf,'k', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbf,'k', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbf = pointNow; // 更新雾点位置
            break;
        case 'u': // 转顺时针
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltn,'u', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtn,'u', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbn,'u', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbn,'u', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltf,'u', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtf,'u', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbf,'u', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbf,'u', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbf = pointNow; // 更新雾点位置
            break;
        case 'o':  // 转逆时针
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltn,'o', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtn,'o', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbn,'o', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbn,'o', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbn = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.ltf,'o', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.ltf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rtf,'o', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rtf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.rbf,'o', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.rbf = pointNow; // 更新雾点位置
            pointNow = turningByCenter(&rotateCenter,FogObjMain->allCorner.lbf,'o', goAngle); // 雾点每个点旋转
            FogObjMain->allCorner.lbf = pointNow; // 更新雾点位置
            break;

    }
}
void freshFogObj_XY(FogObjDemo* FogObjMain, ScreenDemo* ScreenEyeL){
    glm::vec2 couple_center;
    size_t len = FogObjMain->fogPoints.size();
    for(int i=0; i<len; i++){ // 每个雾点的3D→2D
        FogDemo* FogPoint = FogObjMain->fogPoints[i].get();
        couple_center = spotEyeScreenGo(ScreenEyeL,FogPoint->pos3D,
                                        &FogPoint->virtualPos3D);
        FogPoint->pos2D.x = couple_center.x;
        FogPoint->pos2D.y = couple_center.y;
    }
//    cout << "centerPos3D (" << FogObjMain->centerPos3D.y << ", " << FogObjMain->centerPos3D.x << ", "
//         << FogObjMain->centerPos3D.z << ")" << endl;
    couple_center = spotEyeScreenGo(ScreenEyeL,FogObjMain->centerPos3D,&FogObjMain->virtualCenterPos3D);
    FogObjMain->centerPos2D.x = couple_center.x; // obj中心点的3D→2D坐标
    FogObjMain->centerPos2D.y = couple_center.y;
}
void freshFogObj_XY_L(FogObjDemo* FogObjMain, ScreenDemo* ScreenEyeL){
    glm::vec2 couple_center;
    size_t len = FogObjMain->fogPoints.size();
    for(int i=0; i<len; i++){ // 每个雾点的3D→2D
        FogDemo* FogPoint = FogObjMain->fogPoints[i].get();
        couple_center = spotEyeScreenGo(ScreenEyeL,FogPoint->pos3D,&FogPoint->virtualPos3D);

        FogPoint->pos2D.x = couple_center.x;
        FogPoint->pos2D.y = couple_center.y;
    }
//    cout << "centerPos3D (" << FogObjMain->centerPos3D.y << ", " << FogObjMain->centerPos3D.x << ", "
//         << FogObjMain->centerPos3D.z << ")" << endl;
    couple_center = spotEyeScreenGo(ScreenEyeL, FogObjMain->centerPos3D,&FogObjMain->virtualCenterPos3D);
    FogObjMain->centerPos2D.x = couple_center.x; // obj中心点的3D→2D坐标
    FogObjMain->centerPos2D.y = couple_center.y;

    freshFogCorner_XY_L(FogObjMain, ScreenEyeL);
}
void freshFogCorner_XY_L(FogObjDemo* FogObjMain, ScreenDemo* ScreenEyeL){
    glm::vec2 couple_XY;
    couple_XY = spotEyeScreenGo(ScreenEyeL,FogObjMain->allCorner.ltn,&FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[0].x = couple_XY.x;
    FogObjMain->allCorner2D[0].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,FogObjMain->allCorner.rtn,&FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[1].x = couple_XY.x;
    FogObjMain->allCorner2D[1].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,FogObjMain->allCorner.rbn,&FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[2].x = couple_XY.x;
    FogObjMain->allCorner2D[2].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,FogObjMain->allCorner.lbn,&FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[3].x = couple_XY.x;
    FogObjMain->allCorner2D[3].y = couple_XY.y;

    couple_XY = spotEyeScreenGo(ScreenEyeL,FogObjMain->allCorner.ltf,&FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[4].x = couple_XY.x;
    FogObjMain->allCorner2D[4].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,FogObjMain->allCorner.rtf,&FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[5].x = couple_XY.x;
    FogObjMain->allCorner2D[5].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,FogObjMain->allCorner.rbf,&FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[6].x = couple_XY.x;
    FogObjMain->allCorner2D[6].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,FogObjMain->allCorner.lbf,&FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[7].x = couple_XY.x;
    FogObjMain->allCorner2D[7].y = couple_XY.y;
}
void freshFogObj_XY_Go(FogObjDemo* FogObjMain, ScreenDemo* ScreenEyeL){
    glm::vec2 couple_center;
    size_t len = FogObjMain->fogPoints.size();
//#pragma omp parallel for
    for(int i=0; i<len; i++){ // 每个雾点的3D→2D
        FogDemo* FogPoint = FogObjMain->fogPoints[i].get();
        couple_center = spotEyeScreenGo(ScreenEyeL, FogPoint->pos3D,
                                         &FogPoint->virtualPos3D);

        FogPoint->pos2D.x = couple_center.x;
        FogPoint->pos2D.y = couple_center.y;
    }
//    cout << "centerPos3D (" << FogObjMain->centerPos3D.y << ", " << FogObjMain->centerPos3D.x << ", "
//         << FogObjMain->centerPos3D.z << ")" << endl;
    couple_center = spotEyeScreenGo(ScreenEyeL, FogObjMain->centerPos3D,&FogObjMain->virtualCenterPos3D);
    FogObjMain->centerPos2D.x = couple_center.x; // obj中心点的3D→2D坐标
    FogObjMain->centerPos2D.y = couple_center.y;

    freshFogCorner_XY_Go(FogObjMain, ScreenEyeL);
}
void freshFogCorner_XY_Go(FogObjDemo* FogObjMain, ScreenDemo* ScreenEyeL){
    glm::vec2 couple_XY;
    couple_XY = spotEyeScreenGo(ScreenEyeL,
               FogObjMain->allCorner.ltn,
               &FogObjMain->virtualAllCorner.ltn);
    FogObjMain->allCorner2D[0].x = couple_XY.x;
    FogObjMain->allCorner2D[0].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,
               FogObjMain->allCorner.rtn,
               &FogObjMain->virtualAllCorner.rtn);
    FogObjMain->allCorner2D[1].x = couple_XY.x;
    FogObjMain->allCorner2D[1].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,
               FogObjMain->allCorner.rbn,
               &FogObjMain->virtualAllCorner.rbn);
    FogObjMain->allCorner2D[2].x = couple_XY.x;
    FogObjMain->allCorner2D[2].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,
               FogObjMain->allCorner.lbn,
               &FogObjMain->virtualAllCorner.lbn);
    FogObjMain->allCorner2D[3].x = couple_XY.x;
    FogObjMain->allCorner2D[3].y = couple_XY.y;

    couple_XY = spotEyeScreenGo(ScreenEyeL,
               FogObjMain->allCorner.ltf,
               &FogObjMain->virtualAllCorner.ltf);
    FogObjMain->allCorner2D[4].x = couple_XY.x;
    FogObjMain->allCorner2D[4].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,
               FogObjMain->allCorner.rtf,
               &FogObjMain->virtualAllCorner.rtf);
    FogObjMain->allCorner2D[5].x = couple_XY.x;
    FogObjMain->allCorner2D[5].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,
              FogObjMain->allCorner.rbf,
              &FogObjMain->virtualAllCorner.rbf);
    FogObjMain->allCorner2D[6].x = couple_XY.x;
    FogObjMain->allCorner2D[6].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL,
               FogObjMain->allCorner.lbf,
               &FogObjMain->virtualAllCorner.lbf);
    FogObjMain->allCorner2D[7].x = couple_XY.x;
    FogObjMain->allCorner2D[7].y = couple_XY.y;
}
void freshFogObj_XY_by_axis(FogObjDemo* FogObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL, char key){
    glm::vec2 couple_center,couple_point;
    glm::vec3 objCenterXYZ, fogPointXYZ;

    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z };

    int pointSum = (int)FogObjMain->fogPoints.size();
    if(key == 'j' || key == 'i' || key == 'o' || key == 'l' || key == 'k' || key == 'u'){
        objCenterXYZ = turning_by_axis(axis_0_0_0, FogObjMain->centerPos3D, key, goAngle);
        FogObjMain->centerPos3D = objCenterXYZ; // 更新旋转雾点中心点位置
        for(int i=0; i<pointSum; i++){
            fogPointXYZ = turning_by_axis(axis_0_0_0, FogObjMain->fogPoints[i]->pos3D, key, goAngle);
            FogObjMain->fogPoints[i]->pos3D = fogPointXYZ; // 更新旋转雾点3D位置
        }
        FogPointCornerTurn(FogObjMain, ScreenEyeL, axis_0_0_0, key, goAngle);
    }
    else{
        FogObjMoveXYZ(FogObjMain, key, goStep); // 移动简单 中心 雾点

    }

    couple_center = spotEyeScreenGo(ScreenEyeL, FogObjMain->centerPos3D,&FogObjMain->virtualCenterPos3D); // 左下角
    FogObjMain->centerPos2D.x = couple_center.x; // obj中心点的3D→2D坐标
    FogObjMain->centerPos2D.y = couple_center.y;

    FogDemo* fogPointNow;// 点的首地址
    for(int i=0; i<pointSum; i++){
        fogPointNow = FogObjMain->fogPoints[i].get();
        couple_point = spotEyeScreenGo(ScreenEyeL, fogPointNow->pos3D,&fogPointNow->virtualPos3D);

        fogPointNow->pos2D.x = couple_point.x;
        fogPointNow->pos2D.y = couple_point.y;
    }
    freshFogCorner_XY_L(FogObjMain, ScreenEyeL); // 更新8个顶点的2D坐标
}
void freshFogObj_XY_by_axis_L(FogObjDemo* FogObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL, char key){
    glm::vec2 couple_center,couple_point;
    glm::vec3 objCenterXYZ, fogPointXYZ;

    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z };
    int pointSum = (int)FogObjMain->fogPoints.size();

    if(key == 'j' || key == 'i' || key == 'o' || key == 'l' || key == 'k' || key == 'u'){
        objCenterXYZ = turning_by_axis(axis_0_0_0, FogObjMain->centerPos3D, key, goAngle);
        FogObjMain->centerPos3D = objCenterXYZ; // 更新旋转雾点中心点位置
        for(int i=0; i<pointSum; i++){
            fogPointXYZ = turning_by_axis(axis_0_0_0, FogObjMain->fogPoints[i]->pos3D, key, goAngle);
            FogObjMain->fogPoints[i]->pos3D = fogPointXYZ; // 更新旋转雾点3D位置
        }
        FogPointCornerTurn(FogObjMain, ScreenEyeL, axis_0_0_0, key, goAngle);
    }
    else{
        FogObjMoveXYZ(FogObjMain, key, goStep); // 移动简单 中心 雾点
    }

    couple_center = spotEyeScreenGo(ScreenEyeL, FogObjMain->centerPos3D,&FogObjMain->virtualCenterPos3D); // 左下角

    FogObjMain->centerPos2D.x = couple_center.x; // obj中心点的3D→2D坐标
    FogObjMain->centerPos2D.y = couple_center.y;

    FogDemo* fogPointNow;// 点的首地址
    for(int i=0; i<pointSum; i++){
        fogPointNow = FogObjMain->fogPoints[i].get();
        couple_point = spotEyeScreenGo(ScreenEyeL, fogPointNow->pos3D,&fogPointNow->virtualPos3D);
//        cout << "fogPointNow->pos3D (" << fogPointNow->pos3D.x<< ", " << fogPointNow->pos3D.y
//        << ", " << fogPointNow->pos3D.z<< ")" << endl;
//        cout << "virtualPos3D.z: " << fogPointNow->virtualPos3D.z << endl;
        fogPointNow->pos2D.x = couple_point.x;
        fogPointNow->pos2D.y = couple_point.y;
    }

    // 更新8个顶点的2D坐标
    glm::vec2 couple_XY;
    couple_XY = spotEyeScreenGo(ScreenEyeL, FogObjMain->allCorner.ltn, &FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[0].x = couple_XY.x;
    FogObjMain->allCorner2D[0].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL, FogObjMain->allCorner.rtn, &FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[1].x = couple_XY.x;
    FogObjMain->allCorner2D[1].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL, FogObjMain->allCorner.rbn, &FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[2].x = couple_XY.x;
    FogObjMain->allCorner2D[2].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL, FogObjMain->allCorner.lbn, &FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[3].x = couple_XY.x;
    FogObjMain->allCorner2D[3].y = couple_XY.y;

    couple_XY = spotEyeScreenGo(ScreenEyeL, FogObjMain->allCorner.ltf, &FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[4].x = couple_XY.x;
    FogObjMain->allCorner2D[4].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL, FogObjMain->allCorner.rtf, &FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[5].x = couple_XY.x;
    FogObjMain->allCorner2D[5].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL, FogObjMain->allCorner.rbf, &FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[6].x = couple_XY.x;
    FogObjMain->allCorner2D[6].y = couple_XY.y;
    couple_XY = spotEyeScreenGo(ScreenEyeL, FogObjMain->allCorner.lbf, &FogObjMain->virtualCenterPos3D);
    FogObjMain->allCorner2D[7].x = couple_XY.x;
    FogObjMain->allCorner2D[7].y = couple_XY.y;
}


#endif //RECTANGLEDISPLAY_FOGPOINT_FUNC_H
