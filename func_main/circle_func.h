//
// Created by iceoc0 on 2025/3/15.
//

#ifndef RECTANGLEDISPLAY_CIRCLE_FUNC_H
#define RECTANGLEDISPLAY_CIRCLE_FUNC_H
#include"triangle_func_3D2D.h"
#include"../polygonClass/CircleDemo.h"
void freshCircle_by_axis_go(CircleDemo* CircleObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL);
void fresh_oTBLRXY_Go(CircleDemo* circleMain, ScreenDemo* ScreenEyeL);

void circleMoveXYZ_go(CircleDemo* CircleObjMain, char key, float oneStep);
void circleTurnXYZ(CircleDemo* CircleObjMain, ScreenDemo *ScreenEye, RectDemo *footSquare, char key, float goAngle);
void freshCircle_XY_go(CircleDemo* CircleObjMain, ScreenDemo* ScreenEyeL);

void fresh_oTBLRXY_Go(CircleDemo* circleMain, ScreenDemo* ScreenEyeL){
    // 刷新坐标 3D -> 2D
    glm::vec2 couple_lt;
    glm::vec2 couple_rt;
    glm::vec2 couple_lb;
    glm::vec2 couple_rb;
    glm::vec2 couple_center;
    glm::vec2 couple_centerTip;

    couple_lt = spotEyeScreenGo(ScreenEyeL, circleMain->tblrXYZ.ltSet, circleMain->virtual_tblrXYZ); // 左上角
    couple_rt = spotEyeScreenGo(ScreenEyeL, circleMain->tblrXYZ.rtSet, circleMain->virtual_tblrXYZ + 1); // 右上角
    couple_rb = spotEyeScreenGo(ScreenEyeL, circleMain->tblrXYZ.rbSet, circleMain->virtual_tblrXYZ + 2); // 右下角
    couple_lb = spotEyeScreenGo(ScreenEyeL, circleMain->tblrXYZ.lbSet, circleMain->virtual_tblrXYZ + 3); // 左下角
    couple_center = spotEyeScreenGo(ScreenEyeL,circleMain->tblrXYZ.center, circleMain->virtual_tblrXYZ + 4); // 中心
    couple_centerTip = spotEyeScreenGo(ScreenEyeL, circleMain->tblrXYZ.centerTip, circleMain->virtual_tblrXYZ + 5); // 中心

    circleMain->setTBLRXY_f(
            {couple_lt.x, couple_lt.y},
            {couple_rt.x, couple_rt.y},
            {couple_rb.x, couple_rb.y},
            {couple_lb.x, couple_lb.y},
            {couple_center.x, couple_center.y},
            {couple_centerTip.x, couple_centerTip.y}
    );
//    printf("显┌xy:%d,%d\n",couple_lt.y,couple_lt.x);
//    printf("显┐xy:%d,%d\n",couple_rt.y,couple_rt.x);
//    printf("显└xy:%d,%d\n",couple_lb.y,couple_lb.x);
//    printf("显┘xy:%d,%d\n",couple_rb.y,couple_rb.x);
}
void freshCircle_by_axis_go(CircleDemo* CircleObjMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL){
    // 刷新坐标 3D -> 2D
    glm::vec2 couple_lt;
    glm::vec2 couple_rt;
    glm::vec2 couple_rb;
    glm::vec2 couple_lb;

    glm::vec2 couple_Center;
    glm::vec2 couple_centerTip;

    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z };
    //printf("axis_0_0_0:%f,%f,%f\n",axis_0_0_0.y,axis_0_0_0.x,axis_0_0_0.z);
    // FLT_MAX 最大
    // ➗ cos() 转角

    // 3D xyz三步走 每步xyz都要动 都要 动
    glm::vec3 ltXYZ;
    ltXYZ = AxisTilt->goX(axis_0_0_0, CircleObjMain->tblrXYZ_unchange.ltSet.x);
    ltXYZ = AxisTilt->goY(ltXYZ, CircleObjMain->tblrXYZ_unchange.ltSet.y);
    ltXYZ = AxisTilt->goDEEP(ltXYZ, CircleObjMain->tblrXYZ_unchange.ltSet.z);

    glm::vec3 rtXYZ;
    rtXYZ = AxisTilt->goX(axis_0_0_0, CircleObjMain->tblrXYZ_unchange.rtSet.x);
    rtXYZ = AxisTilt->goY(rtXYZ, CircleObjMain->tblrXYZ_unchange.rtSet.y);
    rtXYZ = AxisTilt->goDEEP(rtXYZ, CircleObjMain->tblrXYZ_unchange.rtSet.z);

    glm::vec3 rbXYZ;
    rbXYZ = AxisTilt->goX(axis_0_0_0, CircleObjMain->tblrXYZ_unchange.rbSet.x);
    rbXYZ = AxisTilt->goY(rbXYZ, CircleObjMain->tblrXYZ_unchange.rbSet.y);
    rbXYZ = AxisTilt->goDEEP(rbXYZ, CircleObjMain->tblrXYZ_unchange.rbSet.z);

    glm::vec3 lbXYZ;
    lbXYZ = AxisTilt->goX(axis_0_0_0, CircleObjMain->tblrXYZ_unchange.lbSet.x);
    lbXYZ = AxisTilt->goY(lbXYZ, CircleObjMain->tblrXYZ_unchange.lbSet.y);
    lbXYZ = AxisTilt->goDEEP(lbXYZ, CircleObjMain->tblrXYZ_unchange.lbSet.z);


    CircleObjMain->setTBLRXYZ(ltXYZ, rtXYZ, rbXYZ, lbXYZ); // 更新3D坐标 center back

    couple_lt = spotEyeScreenGo(ScreenEyeL, CircleObjMain->tblrXYZ.ltSet, CircleObjMain->virtual_tblrXYZ);
    couple_rt = spotEyeScreenGo(ScreenEyeL, CircleObjMain->tblrXYZ.rtSet, CircleObjMain->virtual_tblrXYZ + 2);
    couple_rb= spotEyeScreenGo(ScreenEyeL, CircleObjMain->tblrXYZ.rbSet, CircleObjMain->virtual_tblrXYZ + 1);

    couple_lb = spotEyeScreenGo(ScreenEyeL,  CircleObjMain->tblrXYZ.lbSet, CircleObjMain->virtual_tblrXYZ + 3);

    couple_Center = spotEyeScreenGo(ScreenEyeL,CircleObjMain->tblrXYZ.center,CircleObjMain->virtual_tblrXYZ+4); // 中心
    couple_centerTip = spotEyeScreenGo(ScreenEyeL, CircleObjMain->tblrXYZ.centerTip,CircleObjMain->virtual_tblrXYZ+5); // 中心
    // 刷新坐标 2D -> 3D
    CircleObjMain->setTBLRXY_f(couple_lt, couple_rt,
                               couple_rb, couple_lb,
                               couple_Center, couple_centerTip);




}
void circleMoveXYZ_go(CircleDemo* CircleObjMain, char key, float oneStep){
    switch (key) {
        case 'q':  // 上移
            if (goUp){
                goto moveup;
            }
            return;

        case 'e': // 下移
            if (goDown) {
                goto movedown;
            }
            return;

        case 'w': // 前移

            if(goForward){
                goto forward;
            }
            return;

        case 's': // 后移
            if(goBack){
                goto backward;
            }
            return;
        case 'a': // 左移
            if(goLeft){
                goto moveleft;
            }
            return;
        case 'd': // 右移
            if(goRight) {
                goto moveright;
            }
            return;

    }
    moveup:
    CircleObjMain->tblrXYZ.ltSet.y -= oneStep;
    CircleObjMain->tblrXYZ.rtSet.y -= oneStep;
    CircleObjMain->tblrXYZ.lbSet.y -= oneStep;
    CircleObjMain->tblrXYZ.rbSet.y -= oneStep;
    CircleObjMain->tblrXYZ.center.y -= oneStep;
    CircleObjMain->tblrXYZ.centerTip.y -= oneStep;return;
    movedown:
    CircleObjMain->tblrXYZ.ltSet.y += oneStep;
    CircleObjMain->tblrXYZ.rtSet.y += oneStep;
    CircleObjMain->tblrXYZ.lbSet.y += oneStep;
    CircleObjMain->tblrXYZ.rbSet.y += oneStep;
    CircleObjMain->tblrXYZ.center.y += oneStep;
    CircleObjMain->tblrXYZ.centerTip.y += oneStep;return;
    forward:
    CircleObjMain->tblrXYZ.ltSet.z += oneStep;
    CircleObjMain->tblrXYZ.rtSet.z += oneStep;
    CircleObjMain->tblrXYZ.lbSet.z += oneStep;
    CircleObjMain->tblrXYZ.rbSet.z += oneStep;
    CircleObjMain->tblrXYZ.center.z += oneStep;
    CircleObjMain->tblrXYZ.centerTip.z += oneStep;return;
    backward:
    CircleObjMain->tblrXYZ.ltSet.z -= oneStep;
    CircleObjMain->tblrXYZ.rtSet.z -= oneStep;
    CircleObjMain->tblrXYZ.lbSet.z -= oneStep;
    CircleObjMain->tblrXYZ.rbSet.z -= oneStep;
    CircleObjMain->tblrXYZ.center.z -= oneStep;
    CircleObjMain->tblrXYZ.centerTip.z -= oneStep;return;
    moveleft:
    CircleObjMain->tblrXYZ.ltSet.x -= oneStep;
    CircleObjMain->tblrXYZ.rtSet.x -= oneStep;
    CircleObjMain->tblrXYZ.lbSet.x -= oneStep;
    CircleObjMain->tblrXYZ.rbSet.x -= oneStep;
    CircleObjMain->tblrXYZ.center.x -= oneStep;
    CircleObjMain->tblrXYZ.centerTip.x -= oneStep;return;
    moveright:
    CircleObjMain->tblrXYZ.ltSet.x += oneStep;
    CircleObjMain->tblrXYZ.rtSet.x += oneStep;
    CircleObjMain->tblrXYZ.lbSet.x += oneStep;
    CircleObjMain->tblrXYZ.rbSet.x += oneStep;
    CircleObjMain->tblrXYZ.center.x += oneStep;
    CircleObjMain->tblrXYZ.centerTip.x += oneStep;return;

}
void circleTurnXYZ(CircleDemo* CircleObjMain, ScreenDemo *ScreenEye, RectDemo *footSquare, char key, float goAngle){
    switch (key) {
        case 'j': // 左转
            CircleObjMain->tblrXYZ.ltSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.ltSet, 'j', goAngle);
            CircleObjMain->tblrXYZ.rtSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rtSet, 'j', goAngle);
            CircleObjMain->tblrXYZ.lbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.lbSet, 'j', goAngle);
            CircleObjMain->tblrXYZ.rbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rbSet, 'j', goAngle);
            CircleObjMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.center, 'j', goAngle);
            CircleObjMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.centerTip, 'j', goAngle);
            break;
        case 'l': // 右转
            CircleObjMain->tblrXYZ.ltSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.ltSet, 'l', goAngle);
            CircleObjMain->tblrXYZ.rtSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rtSet, 'l', goAngle);
            CircleObjMain->tblrXYZ.lbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.lbSet, 'l', goAngle);
            CircleObjMain->tblrXYZ.rbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rbSet, 'l', goAngle);
            CircleObjMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.center, 'l', goAngle);
            CircleObjMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.centerTip, 'l', goAngle);
            break;
        case 'i': // 上翻
            CircleObjMain->tblrXYZ.ltSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.ltSet, 'i', goAngle);
            CircleObjMain->tblrXYZ.rtSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rtSet, 'i', goAngle);
            CircleObjMain->tblrXYZ.lbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.lbSet, 'i', goAngle);
            CircleObjMain->tblrXYZ.rbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rbSet, 'i', goAngle);
            CircleObjMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.center, 'i', goAngle);
            CircleObjMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.centerTip, 'i', goAngle);
            break;
        case 'k': // 下翻
            CircleObjMain->tblrXYZ.ltSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.ltSet, 'k', goAngle);
            CircleObjMain->tblrXYZ.rtSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rtSet, 'k', goAngle);
            CircleObjMain->tblrXYZ.lbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.lbSet, 'k', goAngle);
            CircleObjMain->tblrXYZ.rbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rbSet, 'k', goAngle);
            CircleObjMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.center, 'k', goAngle);
            CircleObjMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.centerTip, 'k', goAngle);
            break;
        case 'u': // 左旋
            CircleObjMain->tblrXYZ.ltSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.ltSet, 'u', goAngle);
            CircleObjMain->tblrXYZ.rtSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rtSet, 'u', goAngle);
            CircleObjMain->tblrXYZ.lbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.lbSet, 'u', goAngle);
            CircleObjMain->tblrXYZ.rbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rbSet, 'u', goAngle);
            CircleObjMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.center, 'u', goAngle);
            CircleObjMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.centerTip, 'u', goAngle);
            break;
        case 'o': // 右旋
            CircleObjMain->tblrXYZ.ltSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.ltSet, 'o', goAngle);
            CircleObjMain->tblrXYZ.rtSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rtSet, 'o', goAngle);
            CircleObjMain->tblrXYZ.lbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.lbSet, 'o', goAngle);
            CircleObjMain->tblrXYZ.rbSet = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.rbSet, 'o', goAngle);
            CircleObjMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.center, 'o', goAngle);
            CircleObjMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, CircleObjMain->tblrXYZ.centerTip, 'o', goAngle);
            break;
    }
}
void freshCircle_XY_go(CircleDemo* CircleObjMain, ScreenDemo* ScreenEyeL){

    // 刷新坐标 3D -> 2D
    glm::vec2 couple_lt;
    glm::vec2 couple_rt;
    glm::vec2 couple_lb;
    glm::vec2 couple_rb;
    glm::vec2 couple_center;
    glm::vec2 couple_centerTip;


    couple_lt = spotEyeScreenGo(ScreenEyeL, CircleObjMain->tblrXYZ.ltSet, CircleObjMain->virtual_tblrXYZ); // 左上角
    couple_rt = spotEyeScreenGo(ScreenEyeL, CircleObjMain->tblrXYZ.rtSet, CircleObjMain->virtual_tblrXYZ+1); // 右上角
    couple_rb = spotEyeScreenGo(ScreenEyeL, CircleObjMain->tblrXYZ.rbSet, CircleObjMain->virtual_tblrXYZ+2); // 右下角
    couple_lb = spotEyeScreenGo(ScreenEyeL, CircleObjMain->tblrXYZ.lbSet, CircleObjMain->virtual_tblrXYZ+3); // 左下角
    couple_center = spotEyeScreenGo(ScreenEyeL, CircleObjMain->tblrXYZ.center,CircleObjMain->virtual_tblrXYZ+4); // 中心
    couple_centerTip = spotEyeScreenGo(ScreenEyeL, CircleObjMain->tblrXYZ.centerTip,CircleObjMain->virtual_tblrXYZ+5); // 中心

    CircleObjMain->setTBLRXY_f(
    {couple_lt.x, couple_lt.y},
    {couple_rt.x, couple_rt.y},
    {couple_rb.x, couple_rb.y},
    {couple_lb.x, couple_lb.y},
    {couple_center.x, couple_center.y},
    {couple_centerTip.x, couple_centerTip.y}
    );
}
#endif //RECTANGLEDISPLAY_CIRCLE_FUNC_H
