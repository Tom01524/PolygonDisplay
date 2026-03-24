//
// Created by iceoc0 on 2024/11/2.
//

#ifndef RECTANGLEDISPLAY_CALC_FUNC_3D2D_H
#define RECTANGLEDISPLAY_CALC_FUNC_3D2D_H

// #include<cfloat>

// 3D 2D 转换 计算的逻辑函数
//#include"../polygonClass/RectDemo.h"
#include"../polygonClass/AxisDemo.h"
#include "../src/GlobalSettings.h"

//#define screenGoSameFlatTransfer // 坐标系回正 还是坐标系转换
#define quaternionFunc


bool goForward = true, goLeft = true, goRight = true, goBack = true, goUp = true, goDown = true;

//const glm::vec3 axis_0_0_0 = {windowWidth / 2, windowHeight / 2, -500};
//const glm::vec3 centerXYZ = {windowWidth / 2, windowHeight / 2, 0};

glm::vec2 virtual_Pos_3Dto2D(ScreenDemo* ScreenEye, float x, float y, float deep);

[[nodiscard]]glm::vec2 spotEyeScreenGo(ScreenDemo* ScreenEyeL, glm::vec3 _src, glm::vec3 *centerCTipXYZ);
void spotEyeScreenGo_no2D(ScreenDemo* ScreenEyeL, glm::vec3 _src, glm::vec3 *centerCTipXYZ);

glm::vec2 spotEyeScreenSelf(glm::vec3 selfCenter,glm::vec3 selfCenterTip, float x, float y, float deep);

void freshRectCollisionClose(RectDemo* rectMain,  RectDemo* footSquare, char key,float oneStep);

void rectMoveXYZ(RectDemo *rectMain, char key, float oneStep);
void rectMoveXYZSelf(RectDemo* footSquare, char key,float oneStep);
void rectTurnXYZ(RectDemo* rectMain,RectDemo* ScreenEye, RectDemo* footSquare, char key, float goAngle);
glm::vec3 pointTurning(ScreenDemo* ScreenEye, RectDemo* footSquare, glm::vec3 XYZ, char key, float angleOnce);
glm::vec3 turningByCenter(glm::vec3* centerXYZ, glm::vec3 XYZpoint, char key, float angleOnce);

void freshTBLRXY(RectDemo* rectMain, RectDemo* ScreenEye);
void freshTBLRXY_Go(RectDemo* rectMain, RectDemo* ScreenEyeL);

void freshTBLRXY_SelfL(RectDemo* rectMain, RectDemo* ScreenEyeL);

void screenTurnXYZ(ScreenDemo* ScreenEye, char key, float goAngle);
void screenTuring(ScreenDemo* ScreenEye, glm::vec3* XYZpoint, char key, float angleOnce);
void screenMoveXYZ(ScreenDemo *ScreenEyeGo, char key, float oneStep);
void virtualScreenPointTurning(glm::vec3& startCenter, glm::vec3* XYZ_p, char key, angleXYZ_t* angleThisOr);
glm::vec3 eye2ScreenCenter_back2Zero(ScreenDemo* ScreenEye, glm::vec3 XYZpoint, char key, float angleOnce);

void axisMoveXYZ(AxisDemo* AxisWorld, char key, float oneStep);

void axisTurnXYZ_EulerAngle(AxisDemo* AxisTilt, ScreenDemo* ScreenEye, char key, float goAngle);
void axisTurnXYZ_Quaternion(AxisDemo* AxisTilt,  ScreenDemo* ScreenEye, char key, float goAngle);
glm::vec3 turning_axis_Quaternion(AxisDemo* AxisTilt, Quaternion q, glm::vec3 outP);

glm::vec3 turning_axis(ScreenDemo* ScreenEye,AxisDemo* AxisTilt,glm::vec3 XYZpoint, char key, float angleOnce);
void freshTBLRXY_axis(AxisDemo* AxisTilt, AxisDemo* ParallelAxis, ScreenDemo* ScreenEye);
void freshTBLRXY_axis_Go(AxisDemo* AxisTilt, AxisDemo* ParallelAxis, ScreenDemo* ScreenEyeL);

glm::vec3 turning_by_axis(glm::vec3 axis_0_0_0,glm::vec3 XYZ, char key, float angleOnce);
void freshTBLRXY_by_axis(RectDemo* rectMain, AxisDemo* AxisTilt, AxisDemo* AxisParallel, ScreenDemo* ScreenEye, char key);
void freshTBLRXY_by_axis_Go(RectDemo* rectMain, AxisDemo* AxisTilt,  ScreenDemo* ScreenEyeL);




glm::vec2 virtual_Pos_3Dto2D(ScreenDemo* ScreenEye, float x, float y, float deep){
    glm::vec3 startEye = {ScreenEye->rectWidth / 2.f, ScreenEye->rectHeight / 2.f, -ScreenEye->rectDepth};
    // Ex*Pz-Px*Ez
    //--------------
    // Pz-Ez
    float resultX = (startEye.x * deep - x * startEye.z) / (deep - startEye.z); // 屏幕显示  点的x值
    // Ey*Pz-Py*Ez
    //--------------
    // Pz-Ez
    float resultY = (startEye.y * deep - y * startEye.z) / (deep - startEye.z); // 屏幕显示  点的y值


    glm::vec2 result2 = {resultX, resultY}; // 四舍五入
    return result2;
}

glm::vec2 spotEyeScreenGo(ScreenDemo* ScreenEyeL, glm::vec3 _src, glm::vec3 *centerCTipXYZ){
    glm::vec3 point_p = _src;

    // glm::vec3 startEyeCenter = {windowWidth/2.0f,windowHeight/2.0f,(float)-GlobalEyeDeep};
    // glm::vec3 nowEyeCenter = ScreenEyeL->tblrXYZ.centerTip;
    float Px, Py, Pdeep;
    if(runningMode == 4) { // leftView不需要 屏幕移转 信息修正


        // 屏幕系下 从歪歪世界 原点出发 goX goY goZ
#ifdef screenGoSameFlatTransfer
        point_p = ScreenEyeL->worldXYZ2ScreenXYZ_AxisLock(_src);
#endif
#ifdef quaternionFunc
        if(ScreenEyeL->tblrXYZ.lt.x == 0.f && ScreenEyeL->tblrXYZ.lt.y == 0.f && ScreenEyeL->tblrXYZ.lt.z == 0.f){

        }else{
//            cout << "point_p:(" << point_p.x << ", " << point_p.y << ", " << point_p.z << ")" << endl;
            // point_p = ScreenEyeL->tiltTurnPoint2(point_p);
            point_p = ScreenEyeL->worldXYZ2ScreenXYZ_quat(point_p);
//            cout << "|_point_p:(" << point_p.x << ", " << point_p.y << ", " << point_p.z << ")" << endl;
        }

//        if (ScreenEyeL->angleXYZ.z != 0.0f){
//            virtualScreenPointTurning(startEyeCenter, &point_p, 'o', &(ScreenEyeL->angleXYZ)); // z(Roll)  x x
//        }

#endif

        Px = point_p.x;
        Py = point_p.y;
        Pdeep = point_p.z;
    }else{
        Px = _src.x;
        Py = _src.y;
        Pdeep = _src.z;
    }
    if(centerCTipXYZ != nullptr){ // 屏幕系下 顶点屏垂距
        centerCTipXYZ->x = Px;
        centerCTipXYZ->y = Py;
        centerCTipXYZ->z = Pdeep;
    }
    // 计算屏幕坐标



    /* 先x 再y
     *                |\
     * GlobalEyeDeep  | \
     *                |__\
     *                |   \
     * Pdeep          |    \
     *                |_____\
     * */
    // 俯视图

    // if(_pointEye != nullptr){
    //     *_pointEye = GlobalEyeDeep + Pdeep; // 指针直接操作  点 眼 距 值  (左右转头 左视缩水)
    //     //cout << *_pointEye << endl;
    // }

    return virtual_Pos_3Dto2D(ScreenEyeL, Px, Py, Pdeep);

}
void spotEyeScreenGo_no2D(ScreenDemo* ScreenEyeL, glm::vec3 _src, glm::vec3 *centerCTipXYZ) {
    glm::vec3 point_p = _src;

    // glm::vec3 startEyeCenter = {windowWidth/2.0f,windowHeight/2.0f,(float)-GlobalEyeDeep};
    // glm::vec3 nowEyeCenter = ScreenEyeL->tblrXYZ.centerTip;
    float Px, Py, Pdeep;
    if(runningMode == 4 || runningMode == 1) { // leftView不需要 屏幕移转 信息修正


        // 屏幕系下 从歪歪世界 原点出发 goX goY goZ
#ifdef screenGoSameFlatTransfer
        point_p = ScreenEyeL->worldXYZ2ScreenXYZ_AxisLock(_src);
#endif
#ifdef quaternionFunc
        if(ScreenEyeL->tblrXYZ.lt.x == 0.f && ScreenEyeL->tblrXYZ.lt.y == 0.f && ScreenEyeL->tblrXYZ.lt.z == 0.f){

        }else{
            //            cout << "point_p:(" << point_p.x << ", " << point_p.y << ", " << point_p.z << ")" << endl;
            point_p = ScreenEyeL->tiltTurnPoint2(point_p);
            //            cout << "|_point_p:(" << point_p.x << ", " << point_p.y << ", " << point_p.z << ")" << endl;
        }

        //        if (ScreenEyeL->angleXYZ.z != 0.0f){
        //            virtualScreenPointTurning(startEyeCenter, &point_p, 'o', &(ScreenEyeL->angleXYZ)); // z(Roll)  x x
        //        }

#endif

        Px = point_p.x;
        Py = point_p.y;
        Pdeep = point_p.z;
    }else{
        Px = _src.x;
        Py = _src.y;
        Pdeep = _src.z;
    }
    if(centerCTipXYZ != nullptr){ // 屏幕系下 顶点屏垂距
        centerCTipXYZ->x = Px;
        centerCTipXYZ->y = Py;
        centerCTipXYZ->z = Pdeep;
    }
    // 计算屏幕坐标



    /* 先x 再y
     *                |\
     * GlobalEyeDeep  | \
     *                |__\
     *                |   \
     * Pdeep          |    \
     *                |_____\
     * */
    // 俯视图


}
glm::vec2 spotEyeScreenSelf(glm::vec3 selfCenter,glm::vec3 selfCenterTip, float x, float y, float deep){

    // 计算屏幕坐标                 初次初始化原点不改

    // 初次文件内初始化 还没有可用的RectDemo* ScreenEye时
    // 先用spotEyeScreenSelf代替spotEyeScreen
    float eye_screen = selfCenterTip.z * -1;
    float farScreen = deep;
    /* 先x 再y
     *             |\
     * eye_screen  | \
     *             |__\
     *             |   \
     * farScreen   |    \
     *             |_____\
     * */
    float farCenterX = x - selfCenter.x;
    float offCenterX = farCenterX * eye_screen / (eye_screen + farScreen);
    float resultX = offCenterX + windowWidth / 2;

//    std::cout << "far DEEPc y:" << farCenterX << std::endl;
//    std::cout << "eye_screen:" << eye_screen << std::endl;
//    std::cout << "farScreen:" << farScreen << std::endl;

    float farCenterY = y - selfCenter.y;
    float offCenterY = farCenterY * eye_screen / (eye_screen + farScreen);
    float resultY = offCenterY + windowHeight / 2;

//    std::cout << "far DEEPc x:" << farCenterY << std::endl;

    //printf("display X:%f,display Y:%f\n", resultX, resultY);
    glm::vec2 result5 = {resultX, resultY}; // 四舍五入
    return result5;
}

void freshRectCollisionClose(RectDemo* rectMain,  RectDemo* footSquare, char key,float oneStep){
    switch (key) {
        case 'q':  // 上移
            if (goUp){
                goDown = true;
                if(rectMain->rightest().x > footSquare->tblrXYZ_unchange.lt.x // 右侵左
                   && rectMain->leftest().x < footSquare->tblrXYZ_unchange.rt.x // 左侵右
                   && rectMain->fontmost().z < footSquare->tblrXYZ_unchange.lt.z // 前侵前
                   && rectMain->backmost().z > footSquare->tblrXYZ_unchange.lb.z) { // 背侵背 看

                    if(rectMain->topmost().y > footSquare->tblrXYZ_unchange.lt.y) { // 顶未侵底 看
                        if(rectMain->topmost().y > footSquare->tblrXYZ_unchange.lt.y + oneStep) { // 够一步

                        }else{ // 小半步
                            goUp = false;
                        }

                    }else if(rectMain->bottommost().y < footSquare->tblrXYZ.lb.y) { // 底未侵顶 ok

                    }else{ // 左右过近 前后过近 上下过近
                        goUp = false;
                    }
                }else{ // 或前 或后 或左 或右 ok

                }
            }
            return;

        case 'e': // 下移
            if (goDown) {
                goUp = true;
                if(rectMain->rightest().x > footSquare->tblrXYZ_unchange.lt.x
                   && rectMain->leftest().x < footSquare->tblrXYZ_unchange.rt.x // 非左过 非右过 看
                   && rectMain->fontmost().z < footSquare->tblrXYZ_unchange.lt.z
                   && rectMain->backmost().z > footSquare->tblrXYZ_unchange.lb.z) { // 非前过 非后过 看
                    if(rectMain->topmost().y > footSquare->tblrXYZ_unchange.lt.y){ // 判触底 ok

                    }else if(rectMain->bottommost().y < footSquare->tblrXYZ.lb.y) { // 判触顶
                        if(rectMain->bottommost().y < footSquare->tblrXYZ.lb.y - oneStep) { // 够一步

                        }else{ // 小半步
                            goDown = false;
                        }
                    }else{ // 左右过近 前后过近 上下过近
                        goDown = false;
                    }
                }else{ // 或前 或后 或左 或右 ok

                }
            }
            return;
        case 'w': // 前移

            if(goForward){
                goBack = true;
                if(rectMain->topmost().y < footSquare->tblrXYZ_unchange.lt.y
                   && rectMain->bottommost().y > footSquare->tblrXYZ.lt.y // 非上越 非下越 看
                   && rectMain->rightest().x > footSquare->tblrXYZ_unchange.lt.x
                   && rectMain->leftest().x < footSquare->tblrXYZ_unchange.rt.x) { // 非左过 非右过 看

                    if (rectMain->fontmost().z > footSquare->tblrXYZ_unchange.lt.z) { // 判前过近 OK

                    }else if(rectMain->backmost().z < footSquare->tblrXYZ_unchange.lb.z){
                        //判后过近 看
                        if( rectMain->backmost().z < footSquare->tblrXYZ_unchange.lb.z - oneStep) { // 后距够一步

                        }else{ // 小半步
                            goForward = false;
                        }
                    }else{ // 左右过近 前后过近
                        goForward = false;
                    }
                }else { // 左右躲 上越 或 下越 ok

                }
            }
            return;

        case 's': // 后移

            if(goBack){
                goForward = true;
                if(rectMain->topmost().y < footSquare->tblrXYZ_unchange.lt.y
                   && rectMain->bottommost().y > footSquare->tblrXYZ.lt.y // 非上越 非下越 看
                   &&(rectMain->rightest().x > footSquare->tblrXYZ_unchange.lt.x)
                   && (rectMain->leftest().x < footSquare->tblrXYZ_unchange.rt.x)) // 非左过 非右过 看
                {
                    if (rectMain->fontmost().z > footSquare->tblrXYZ_unchange.lt.z) { // 判前过近 看
                        if(rectMain->fontmost().z > footSquare->tblrXYZ_unchange.lt.z + oneStep){ // 前距 够一步

                        }else{ // 小半步
                            goBack = false;
                        }

                    }else if(rectMain->backmost().z < footSquare->tblrXYZ_unchange.lb.z){
                        //判后过近 ok

                    }else { // 左右过近 前后过近
                        goBack = false;
                    }
                } else { // 左右躲 上越 或 下越 OK

                }
            }
            return;
        case 'a': // 左移
            if(goLeft){
                goRight = true;
                if(rectMain->topmost().y < footSquare->tblrXYZ_unchange.lt.y
                   && rectMain->bottommost().y > footSquare->tblrXYZ.lt.y // 非上越 非下越 看
                   && rectMain->fontmost().z < footSquare->tblrXYZ_unchange.lt.z
                   && rectMain->backmost().z > footSquare->tblrXYZ_unchange.lb.z) { // 前后过近
                    if (rectMain->rightest().x < footSquare->tblrXYZ_unchange.lt.x) { // 左空 OK

                    } else if (rectMain->leftest().x > footSquare->tblrXYZ_unchange.rt.x) {
                        // 右空 看
                        if (rectMain->leftest().x > footSquare->tblrXYZ_unchange.rt.x + oneStep) { // 够一步

                        } else { // 小半步
                            goLeft = false;
                        }
                    } else { // 左右过近 前后过近
                        goLeft = false;
                    }
                } else { // 前过 后过 上越 或 下越 OK

                }
            }
            return;
        case 'd': // 右移
            if(goRight) {
                goLeft = true;
                // Y越大越下
                if(rectMain->topmost().y < footSquare->tblrXYZ_unchange.lt.y
                   && rectMain->bottommost().y > footSquare->tblrXYZ.lt.y // 非上越 非下越 看
                   && rectMain->fontmost().z < footSquare->tblrXYZ_unchange.lt.z
                   && rectMain->backmost().z > footSquare->tblrXYZ_unchange.lb.z) { // 前后过近
                    if (rectMain->leftest().x > footSquare->tblrXYZ_unchange.rt.x) { // 右空 OK

                    } else if (rectMain->rightest().x < footSquare->tblrXYZ_unchange.lt.x) {
                        // 左空 看
                        if (rectMain->rightest().x < footSquare->tblrXYZ_unchange.lt.x - oneStep) { // 够一步

                        } else { // 小半步
                            goRight = false;
                        }
                    } else { // 左右过近 前后过近
                        goRight = false;
                    }
                }else { // 前过 后过 上越 或 下越 OK

                }

            }
            return;

    }
}

void rectMoveXYZ(RectDemo *rectMain, char key, float oneStep) {
    // 更改三维空间坐标
    // 取地址修改class

    //freshRectCollisionClose(rectMain, footSquare, key,oneStep);
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
    rectMain->tblrXYZ.lt.y -= oneStep;
    rectMain->tblrXYZ.rt.y -= oneStep;
    rectMain->tblrXYZ.lb.y -= oneStep;
    rectMain->tblrXYZ.rb.y -= oneStep;
    rectMain->tblrXYZ.center.y -= oneStep;
    rectMain->tblrXYZ.centerTip.y -= oneStep;return;
    movedown:
    rectMain->tblrXYZ.lt.y += oneStep;
    rectMain->tblrXYZ.rt.y += oneStep;
    rectMain->tblrXYZ.lb.y += oneStep;
    rectMain->tblrXYZ.rb.y += oneStep;
    rectMain->tblrXYZ.center.y += oneStep;
    rectMain->tblrXYZ.centerTip.y += oneStep;return;
    forward:
    rectMain->tblrXYZ.lt.z += oneStep;
    rectMain->tblrXYZ.rt.z += oneStep;
    rectMain->tblrXYZ.lb.z += oneStep;
    rectMain->tblrXYZ.rb.z += oneStep;
    rectMain->tblrXYZ.center.z += oneStep;
    rectMain->tblrXYZ.centerTip.z += oneStep;return;
    backward:
    rectMain->tblrXYZ.lt.z -= oneStep;
    rectMain->tblrXYZ.rt.z -= oneStep;
    rectMain->tblrXYZ.lb.z -= oneStep;
    rectMain->tblrXYZ.rb.z -= oneStep;
    rectMain->tblrXYZ.center.z -= oneStep;
    rectMain->tblrXYZ.centerTip.z -= oneStep;return;
    moveleft:
    rectMain->tblrXYZ.lt.x -= oneStep;
    rectMain->tblrXYZ.rt.x -= oneStep;
    rectMain->tblrXYZ.lb.x -= oneStep;
    rectMain->tblrXYZ.rb.x -= oneStep;
    rectMain->tblrXYZ.center.x -= oneStep;
    rectMain->tblrXYZ.centerTip.x -= oneStep;return;
    moveright:
    rectMain->tblrXYZ.lt.x += oneStep;
    rectMain->tblrXYZ.rt.x += oneStep;
    rectMain->tblrXYZ.lb.x += oneStep;
    rectMain->tblrXYZ.rb.x += oneStep;
    rectMain->tblrXYZ.center.x += oneStep;
    rectMain->tblrXYZ.centerTip.x += oneStep;return;

//    printf("左上角xyz:%f,%f,%f\n",rectMain->axisXYZ.Xl.y,rectMain->axisXYZ.Xl.x,rectMain->axisXYZ.Xl.z);
//    printf("右上角xyz:%f,%f,%f\n",rectMain->axisXYZ.Xr.y,rectMain->axisXYZ.Xr.x,rectMain->axisXYZ.Xr.z);
//    printf("左下角xyz:%f,%f,%f\n",rectMain->axisXYZ.Yt.y,rectMain->axisXYZ.Yt.x,rectMain->axisXYZ.Yt.z);
//    printf("右下角xyz:%f,%f,%f\n",rectMain->axisXYZ.Yb.y,rectMain->axisXYZ.Yb.x,rectMain->axisXYZ.Yb.z);

}
void rectMoveXYZSelf(RectDemo* footSquare, char key,float oneStep){
    // 更改三维空间坐标
    // 取地址修改class

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
    footSquare->tblrXYZ.lt.y -= oneStep;
    footSquare->tblrXYZ.rt.y -= oneStep;
    footSquare->tblrXYZ.lb.y -= oneStep;
    footSquare->tblrXYZ.rb.y -= oneStep;
    footSquare->tblrXYZ.center.y -= oneStep;
    footSquare->tblrXYZ.centerTip.y -= oneStep;
    footSquare->tblrXYZ_unchange.lt.y -= oneStep;
    footSquare->tblrXYZ_unchange.rt.y -= oneStep;
    footSquare->tblrXYZ_unchange.lb.y -= oneStep;
    footSquare->tblrXYZ_unchange.rb.y -= oneStep;
    footSquare->tblrXYZ_unchange.center.y -= oneStep;
    footSquare->tblrXYZ_unchange.centerTip.y -= oneStep;return;
    movedown:
    footSquare->tblrXYZ.lt.y += oneStep;
    footSquare->tblrXYZ.rt.y += oneStep;
    footSquare->tblrXYZ.lb.y += oneStep;
    footSquare->tblrXYZ.rb.y += oneStep;
    footSquare->tblrXYZ.center.y += oneStep;
    footSquare->tblrXYZ.centerTip.y += oneStep;
    footSquare->tblrXYZ_unchange.lt.y += oneStep;
    footSquare->tblrXYZ_unchange.rt.y += oneStep;
    footSquare->tblrXYZ_unchange.lb.y += oneStep;
    footSquare->tblrXYZ_unchange.rb.y += oneStep;
    footSquare->tblrXYZ_unchange.center.y += oneStep;
    footSquare->tblrXYZ_unchange.centerTip.y += oneStep;return;
    forward:
    footSquare->tblrXYZ.lt.z += oneStep;
    footSquare->tblrXYZ.rt.z += oneStep;
    footSquare->tblrXYZ.lb.z += oneStep;
    footSquare->tblrXYZ.rb.z += oneStep;
    footSquare->tblrXYZ.center.z += oneStep;
    footSquare->tblrXYZ.centerTip.z += oneStep;
    footSquare->tblrXYZ_unchange.lt.z += oneStep;
    footSquare->tblrXYZ_unchange.rt.z += oneStep;
    footSquare->tblrXYZ_unchange.lb.z += oneStep;
    footSquare->tblrXYZ_unchange.rb.z += oneStep;
    footSquare->tblrXYZ_unchange.center.z += oneStep;
    footSquare->tblrXYZ_unchange.centerTip.z += oneStep;return;
    backward:
    footSquare->tblrXYZ.lt.z -= oneStep;
    footSquare->tblrXYZ.rt.z -= oneStep;
    footSquare->tblrXYZ.lb.z -= oneStep;
    footSquare->tblrXYZ.rb.z -= oneStep;
    footSquare->tblrXYZ.center.z -= oneStep;
    footSquare->tblrXYZ.centerTip.z -= oneStep;
    footSquare->tblrXYZ_unchange.lt.z -= oneStep;
    footSquare->tblrXYZ_unchange.rt.z -= oneStep;
    footSquare->tblrXYZ_unchange.lb.z -= oneStep;
    footSquare->tblrXYZ_unchange.rb.z -= oneStep;
    footSquare->tblrXYZ_unchange.center.z -= oneStep;
    footSquare->tblrXYZ_unchange.centerTip.z -= oneStep;return;
    moveleft:
    footSquare->tblrXYZ.lt.x -= oneStep;
    footSquare->tblrXYZ.rt.x -= oneStep;
    footSquare->tblrXYZ.lb.x -= oneStep;
    footSquare->tblrXYZ.rb.x -= oneStep;
    footSquare->tblrXYZ.center.x -= oneStep;
    footSquare->tblrXYZ.centerTip.x -= oneStep;
    footSquare->tblrXYZ_unchange.lt.x -= oneStep;
    footSquare->tblrXYZ_unchange.rt.x -= oneStep;
    footSquare->tblrXYZ_unchange.lb.x -= oneStep;
    footSquare->tblrXYZ_unchange.rb.x -= oneStep;
    footSquare->tblrXYZ_unchange.center.x -= oneStep;
    footSquare->tblrXYZ_unchange.centerTip.x -= oneStep;return;
    moveright:
    footSquare->tblrXYZ.lt.x += oneStep;
    footSquare->tblrXYZ.rt.x += oneStep;
    footSquare->tblrXYZ.lb.x += oneStep;
    footSquare->tblrXYZ.rb.x += oneStep;
    footSquare->tblrXYZ.center.x += oneStep;
    footSquare->tblrXYZ.centerTip.x += oneStep;
    footSquare->tblrXYZ_unchange.lt.x += oneStep;
    footSquare->tblrXYZ_unchange.rt.x += oneStep;
    footSquare->tblrXYZ_unchange.lb.x += oneStep;
    footSquare->tblrXYZ_unchange.rb.x += oneStep;
    footSquare->tblrXYZ_unchange.center.x += oneStep;
    footSquare->tblrXYZ_unchange.centerTip.x += oneStep;return;
}
void rectTurnXYZ(RectDemo* rectMain,ScreenDemo* ScreenEye, RectDemo* footSquare, char key, float goAngle){

    switch (key) {
        case 'j': // 左转
            rectMain->tblrXYZ.lt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lt, 'j', goAngle);
            rectMain->tblrXYZ.rt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rt, 'j', goAngle);
            rectMain->tblrXYZ.lb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lb, 'j', goAngle);
            rectMain->tblrXYZ.rb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rb, 'j', goAngle);
            rectMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.center, 'j', goAngle);
            rectMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.centerTip, 'j', goAngle);
            break;
        case 'l': // 右转
            rectMain->tblrXYZ.lt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lt, 'l', goAngle);
            rectMain->tblrXYZ.rt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rt, 'l', goAngle);
            rectMain->tblrXYZ.lb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lb, 'l', goAngle);
            rectMain->tblrXYZ.rb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rb, 'l', goAngle);
            rectMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.center, 'l', goAngle);
            rectMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.centerTip, 'l', goAngle);
            break;
        case 'i': // 上翻
            rectMain->tblrXYZ.lt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lt, 'i', goAngle);
            rectMain->tblrXYZ.rt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rt, 'i', goAngle);
            rectMain->tblrXYZ.lb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lb, 'i', goAngle);
            rectMain->tblrXYZ.rb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rb, 'i', goAngle);
            rectMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.center, 'i', goAngle);
            rectMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.centerTip, 'i', goAngle);
            break;
        case 'k': // 下翻
            rectMain->tblrXYZ.lt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lt, 'k', goAngle);
            rectMain->tblrXYZ.rt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rt, 'k', goAngle);
            rectMain->tblrXYZ.lb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lb, 'k', goAngle);
            rectMain->tblrXYZ.rb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rb, 'k', goAngle);
            rectMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.center, 'k', goAngle);
            rectMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.centerTip, 'k', goAngle);
            break;
        case 'u': // 左旋
            rectMain->tblrXYZ.lt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lt, 'u', goAngle);
            rectMain->tblrXYZ.rt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rt, 'u', goAngle);
            rectMain->tblrXYZ.lb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lb, 'u', goAngle);
            rectMain->tblrXYZ.rb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rb, 'u', goAngle);
            rectMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.center, 'u', goAngle);
            rectMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.centerTip, 'u', goAngle);
            break;
        case 'o': // 右旋
            rectMain->tblrXYZ.lt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lt, 'o', goAngle);
            rectMain->tblrXYZ.rt = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rt, 'o', goAngle);
            rectMain->tblrXYZ.lb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.lb, 'o', goAngle);
            rectMain->tblrXYZ.rb = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.rb, 'o', goAngle);
            rectMain->tblrXYZ.center = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.center, 'o', goAngle);
            rectMain->tblrXYZ.centerTip = pointTurning(ScreenEye, footSquare, rectMain->tblrXYZ.centerTip, 'o', goAngle);
            break;
    }

}
glm::vec3 pointTurning(ScreenDemo* ScreenEye, RectDemo* footSquare, glm::vec3 XYZ, char key, float angleOnce){ // 一个点 一个点 turn

    // 转头
    glm::vec3 _screenCenter = {0.0,0.0,0.0};
    glm::vec3 _result = {0.0,0.0,0.0};
    //glm::vec3 _screenCenter = ScreenEye->axisXYZ.DEEPf; // 眼睛坐标
    if(runningMode == 2){
        _screenCenter = footSquare->tblrXYZ.center;
        _result = turningByCenter(&_screenCenter,XYZ,key, angleOnce);
    }else {
        _screenCenter = ScreenEye->tblrXYZ.center; // 屏幕正中
        _result = turningByCenter(&_screenCenter,XYZ,key, angleOnce);
    }

    return _result;
}

glm::vec3 turningByCenter(glm::vec3* centerXYZ, glm::vec3 XYZpoint, char key, float _angleOnce){
    float angleX,radiusX,newX,newZ;
    float angleY,radiusY,newY;
    float eyeAxisAngle, eyeAxisRadius, hypotenuse;

    //glm::vec3 eyeXYZ = ScreenEye->axisXYZ.DEEPf; // 眼睛坐标
    //static glm::vec3 eyeXYZ;
    float angleOnce = glm::radians(_angleOnce);

    switch (key) {
        case 'j': // 左转 绕y轴

            angleX = glm::atan(centerXYZ->x - XYZpoint.x , -centerXYZ->z + XYZpoint.z);
            //std::cout << "angleX:" << angleX << std::endl;
            radiusX = glm::sqrt(
                    (centerXYZ->x - XYZpoint.x) * (centerXYZ->x - XYZpoint.x)
                    + (-centerXYZ->z + XYZpoint.z) * (-centerXYZ->z + XYZpoint.z));
            //std::cout << "radiusX:" << radiusX << std::endl;
            angleX += angleOnce;
            newX = centerXYZ->x - radiusX * glm::sin(angleX);
            newZ = radiusX * glm::cos(angleX) - (-centerXYZ->z);
            XYZpoint.x = newX;
            XYZpoint.z = newZ;
            break;
        case 'l': // 右转 绕y轴
            angleX = glm::atan(centerXYZ->x - XYZpoint.x, -centerXYZ->z + XYZpoint.z);
            //std::cout << "angleX:" << angleX << std::endl;
            radiusX = glm::sqrt(
                    (centerXYZ->x - XYZpoint.x) * (centerXYZ->x - XYZpoint.x)
                    + (-centerXYZ->z + XYZpoint.z) * (-centerXYZ->z + XYZpoint.z));
            //std::cout << "radiusX:" << radiusX << std::endl;
            angleX -= angleOnce;
            newX = centerXYZ->x - radiusX * glm::sin(angleX);
            newZ = radiusX * glm::cos(angleX) - (-centerXYZ->z);
            XYZpoint.x = newX;
            XYZpoint.z = newZ;
            break;
        case 'i': // 上转 绕x轴
            angleY = glm::atan(centerXYZ->y - XYZpoint.y,
                           -centerXYZ->z + XYZpoint.z);
            //std::cout << "angleY:" << angleY << std::endl;
            radiusY = glm::sqrt(
                    (centerXYZ->y - XYZpoint.y) * (centerXYZ->y - XYZpoint.y) +
                    (-centerXYZ->z + XYZpoint.z) * (-centerXYZ->z + XYZpoint.z));
            //std::cout << "radiusY:" << radiusY << std::endl;
            angleY += angleOnce;
            newY = centerXYZ->y - radiusY * glm::sin(angleY);
            newZ = radiusY * glm::cos(angleY) - (-centerXYZ->z);
            XYZpoint.y = newY;
            XYZpoint.z = newZ;
            break;
        case 'k': // 下转 绕x轴
            angleY = glm::atan(centerXYZ->y - XYZpoint.y,
                           -centerXYZ->z + XYZpoint.z);
            //std::cout << "angleY:" << angleY << std::endl;
            radiusY = glm::sqrt(
                    (centerXYZ->y - XYZpoint.y) * (centerXYZ->y - XYZpoint.y)
                    + (-centerXYZ->z + XYZpoint.z) * (-centerXYZ->z + XYZpoint.z));
            //std::cout << "radiusY:" << radiusY << std::endl;
            angleY -= angleOnce;
            newY = centerXYZ->y - radiusY * glm::sin(angleY);
            newZ = radiusY * glm::cos(angleY) - (-centerXYZ->z);
            XYZpoint.y = newY;
            XYZpoint.z = newZ;
            break;
        case 'u':
            // flat 平面
            hypotenuse = glm::sqrt((centerXYZ->x-XYZpoint.x) * (centerXYZ->x-XYZpoint.x)
                              + (centerXYZ->y-XYZpoint.y) * (centerXYZ->y-XYZpoint.y));



            //eyeAxisAngle = acos(  (centerXYZ->x-XYZpoint.x)/hypotenuse ) / M_PI * 180.0; // flat 临/斜
            eyeAxisAngle = atan2f(-centerXYZ->x+XYZpoint.x, centerXYZ->y-XYZpoint.y);

            eyeAxisAngle = M_PI - eyeAxisAngle; // 补角
            eyeAxisAngle -= angleOnce;

            //std::cout << "eyeAxisAngle:" << eyeAxisAngle << std::endl;

            eyeAxisRadius = hypotenuse;
            //std::cout << "eyeAxisRadius:" << eyeAxisRadius << std::endl;


            newX = glm::sin(eyeAxisAngle) * eyeAxisRadius + centerXYZ->x;
            newY = glm::cos(eyeAxisAngle) * eyeAxisRadius + centerXYZ->y;
            XYZpoint.x = newX;
            XYZpoint.y = newY;
            break;
        case 'o': // 右旋
            // flat 平面
            hypotenuse = glm::sqrt((centerXYZ->x-XYZpoint.x) * (centerXYZ->x-XYZpoint.x)
                              + (centerXYZ->y-XYZpoint.y) * (centerXYZ->y-XYZpoint.y));



            //eyeAxisAngle = acos(  (centerXYZ->x-XYZpoint.x)/hypotenuse ) / M_PI * 180.0; // flat 临/斜
            eyeAxisAngle = atan2f(-centerXYZ->x+XYZpoint.x, centerXYZ->y-XYZpoint.y);

            eyeAxisAngle = M_PI - eyeAxisAngle; // 补角
            eyeAxisAngle += angleOnce;

            //std::cout << "eyeAxisAngle:" << eyeAxisAngle << std::endl;

            eyeAxisRadius = hypotenuse;
            //std::cout << "eyeAxisRadius:" << eyeAxisRadius << std::endl;


            newX = glm::sin(eyeAxisAngle) * eyeAxisRadius + centerXYZ->x;
            newY = glm::cos(eyeAxisAngle) * eyeAxisRadius + centerXYZ->y;
            XYZpoint.x = newX;
            XYZpoint.y = newY;
            break;
    }
    return XYZpoint;
}

void freshTBLRXY(RectDemo* rectMain, ScreenDemo* ScreenEye){
    // 刷新坐标 3D -> 2D
    glm::vec2 couple_lt = {0.0f, 0.0f};
    glm::vec2 couple_rt = {0.0f, 0.0f};
    glm::vec2 couple_lb = {0.0f, 0.0f};
    glm::vec2 couple_rb = {0.0f, 0.0f};
    glm::vec2 couple_center = {0.0f, 0.0f};
    glm::vec2 couple_centerTip = {0.0f, 0.0f};

    couple_lb = virtual_Pos_3Dto2D(ScreenEye, rectMain->tblrXYZ.lb.x, rectMain->tblrXYZ.lb.y, rectMain->tblrXYZ.lb.z); // 左下角
    couple_rt= virtual_Pos_3Dto2D(ScreenEye, rectMain->tblrXYZ.rt.x, rectMain->tblrXYZ.rt.y, rectMain->tblrXYZ.rt.z); // 右上角
    couple_lt = virtual_Pos_3Dto2D(ScreenEye, rectMain->tblrXYZ.lt.x, rectMain->tblrXYZ.lt.y, rectMain->tblrXYZ.lt.z); // 左上角
    couple_rb= virtual_Pos_3Dto2D(ScreenEye, rectMain->tblrXYZ.rb.x, rectMain->tblrXYZ.rb.y, rectMain->tblrXYZ.rb.z); // 右下角
    couple_center = virtual_Pos_3Dto2D(ScreenEye, rectMain->tblrXYZ.center.x, rectMain->tblrXYZ.center.y,
                                       rectMain->tblrXYZ.center.z); // 中心
    couple_centerTip = virtual_Pos_3Dto2D(ScreenEye, rectMain->tblrXYZ.centerTip.x, rectMain->tblrXYZ.centerTip.y,
                                          rectMain->tblrXYZ.centerTip.z); // 中心

    rectMain->setTBLRXY_f(
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
void freshTBLRXY_Go(RectDemo* rectMain, ScreenDemo* ScreenEyeL){
    // 刷新坐标 3D -> 2D
    glm::vec2 couple_lt;
    glm::vec2 couple_rt;
    glm::vec2 couple_lb;
    glm::vec2 couple_rb;
    glm::vec2 couple_center;
    glm::vec2 couple_centerTip;

    couple_lt = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.lt, rectMain->virtual_tblrXYZ); // 左上角
    couple_rt = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.rt, rectMain->virtual_tblrXYZ+1); // 右上角
    couple_rb = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.rb, rectMain->virtual_tblrXYZ+2); // 右下角
    couple_lb = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.lb, rectMain->virtual_tblrXYZ+3); // 左下角
    couple_center = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.center,rectMain->virtual_tblrXYZ+4); // 中心
    couple_centerTip = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.centerTip,rectMain->virtual_tblrXYZ+5); // 中心

    rectMain->setTBLRXY_f(
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

void freshTBLRXY_SelfL(RectDemo* rectMain, ScreenDemo* ScreenEyeL){
    // 刷新坐标 3D -> 2D
    glm::vec2 couple_lt = {0.0f, 0.0f};
    glm::vec2 couple_rt = {0.0f, 0.0f};
    glm::vec2 couple_lb = {0.0f, 0.0f};
    glm::vec2 couple_rb = {0.0f, 0.0f};
    glm::vec2 couple_center = {0.0f, 0.0f};
    glm::vec2 couple_centerTip = {0.0f, 0.0f};


    couple_lt = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.lt, rectMain->virtual_tblrXYZ); // 左上角
    couple_rt= spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.rt, rectMain->virtual_tblrXYZ+1); // 右上角
    couple_rb= spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.rb, rectMain->virtual_tblrXYZ+2); // 右下角
    couple_lb = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.lb, rectMain->virtual_tblrXYZ+3); // 左下角
    couple_center = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.center, rectMain->virtual_tblrXYZ+4); // 中心
    couple_centerTip = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.centerTip, rectMain->virtual_tblrXYZ+5); // 中心

    rectMain->setTBLRXY_f(
            {couple_lt.x, couple_lt.y},
            {couple_rt.x, couple_rt.y},
            {couple_rb.x, couple_rb.y},
            {couple_lb.x, couple_lb.y},
            {couple_center.x, couple_center.y},
            {couple_centerTip.x, couple_centerTip.y}
    );
    // 刷新坐标 3D -> 2D

    couple_lt = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ_unchange.lt, nullptr); // 左上角
    couple_rt= spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ_unchange.rt, nullptr); // 右上角
    couple_rb= spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ_unchange.rb, nullptr); // 右下角
    couple_lb = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ_unchange.lb, nullptr); // 左下角
    couple_center = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ_unchange.center, nullptr); // 中心
    couple_centerTip = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ_unchange.centerTip, nullptr); // 中心

    rectMain->setTBLRXY_Down(
            {couple_lt.x, couple_lt.y},
            {couple_rt.x, couple_rt.y},
            {couple_rb.x, couple_rb.y},
            {couple_lb.x, couple_lb.y},
            {couple_center.x, couple_center.y},
            {couple_centerTip.x, couple_centerTip.y}
    );
}

void screenTurnXYZ(ScreenDemo* ScreenEye, char key, float goAngle){

#ifdef quaternionFunc

    float backX = ScreenEye->tblrXYZ.centerTip.x;
    float backY = ScreenEye->tblrXYZ.centerTip.y;
    float backDEEP = ScreenEye->tblrXYZ.centerTip.z;
    // 屏幕去原点
    ScreenEye->tblrXYZ.lt.x -= backX;
    ScreenEye->tblrXYZ.rt.x -= backX;
    ScreenEye->tblrXYZ.lb.x -= backX;
    ScreenEye->tblrXYZ.rb.x -= backX;
    ScreenEye->tblrXYZ.center.x -= backX;
//    ScreenEye->tblrXYZ.centerTip.x -= backX; // 0.0f;

    ScreenEye->tblrXYZ.lt.y -= backY;
    ScreenEye->tblrXYZ.rt.y -= backY;
    ScreenEye->tblrXYZ.lb.y -= backY;
    ScreenEye->tblrXYZ.rb.y -= backY;
    ScreenEye->tblrXYZ.center.y -= backY;
//    ScreenEye->tblrXYZ.centerTip.y -= backY; // 0.0f;

    ScreenEye->tblrXYZ.lt.z -= backDEEP;
    ScreenEye->tblrXYZ.rt.z -= backDEEP;
    ScreenEye->tblrXYZ.lb.z -= backDEEP;
    ScreenEye->tblrXYZ.rb.z -= backDEEP;
    ScreenEye->tblrXYZ.center.z -= backDEEP;
//    ScreenEye->tblrXYZ.centerTip.z -= backDEEP; // 0.0f;

    goLine64 axisTilt;
    Quaternion q;
    float _lt_0_len = glm::sqrt(ScreenEye->tblrXYZ.lt.x * ScreenEye->tblrXYZ.lt.x +
            ScreenEye->tblrXYZ.lt.y * ScreenEye->tblrXYZ.lt.y +
            ScreenEye->tblrXYZ.lt.z * ScreenEye->tblrXYZ.lt.z);
    float _rt_0_len = glm::sqrt(ScreenEye->tblrXYZ.rt.x * ScreenEye->tblrXYZ.rt.x +
            ScreenEye->tblrXYZ.rt.y * ScreenEye->tblrXYZ.rt.y +
            ScreenEye->tblrXYZ.rt.z * ScreenEye->tblrXYZ.rt.z);
    float _lb_0_len = glm::sqrt(ScreenEye->tblrXYZ.lb.x * ScreenEye->tblrXYZ.lb.x +
            ScreenEye->tblrXYZ.lb.y * ScreenEye->tblrXYZ.lb.y +
            ScreenEye->tblrXYZ.lb.z * ScreenEye->tblrXYZ.lb.z);
    float _rb_0_len = glm::sqrt(ScreenEye->tblrXYZ.rb.x * ScreenEye->tblrXYZ.rb.x +
            ScreenEye->tblrXYZ.rb.y * ScreenEye->tblrXYZ.rb.y +
            ScreenEye->tblrXYZ.rb.z * ScreenEye->tblrXYZ.rb.z);
    float _center_0_len = glm::sqrt(ScreenEye->tblrXYZ.center.x * ScreenEye->tblrXYZ.center.x +
            ScreenEye->tblrXYZ.center.y * ScreenEye->tblrXYZ.center.y + ScreenEye->tblrXYZ.center.z * ScreenEye->tblrXYZ.center.z);

    goLine64 _lt2zero = {ScreenEye->tblrXYZ.lt.x/_lt_0_len, ScreenEye->tblrXYZ.lt.y/_lt_0_len,
                         ScreenEye->tblrXYZ.lt.z/_lt_0_len};
    goLine64 _rt2zero = {ScreenEye->tblrXYZ.rt.x/_rt_0_len, ScreenEye->tblrXYZ.rt.y/_rt_0_len,
                         ScreenEye->tblrXYZ.rt.z/_rt_0_len};
    goLine64 _lb2zero = {ScreenEye->tblrXYZ.lb.x/_lb_0_len, ScreenEye->tblrXYZ.lb.y/_lb_0_len,
                         ScreenEye->tblrXYZ.lb.z/_lb_0_len};
    goLine64 _rb2zero = {ScreenEye->tblrXYZ.rb.x/_rb_0_len, ScreenEye->tblrXYZ.rb.y/_rb_0_len,
                         ScreenEye->tblrXYZ.rb.z/_rb_0_len};
    goLine64 _center2zero = {ScreenEye->tblrXYZ.center.x/_center_0_len, ScreenEye->tblrXYZ.center.y/_center_0_len,
                             ScreenEye->tblrXYZ.center.z/_center_0_len};
    switch (key) {
        case 'j': // 左转
            axisTilt = {0.0, 1.0, 0.0}; // 绕 世界 y
            q = ScreenDemo::create_rotation(-goAngle, axisTilt);

            PolygonBase::rotate_vector(_lt2zero, q);
            PolygonBase::rotate_vector(_rt2zero, q);
            PolygonBase::rotate_vector(_lb2zero, q);
            PolygonBase::rotate_vector(_rb2zero, q);
            PolygonBase::rotate_vector(_center2zero, q);
//            ScreenEye->rotate_vector(&ScreenEye->tblrXYZ.centerTip, q);
            break;

        case 'l': // 右转
            axisTilt = {0.0, 1.0, 0.0}; // 绕 世界 y
            q = ScreenDemo::create_rotation(goAngle, axisTilt);

            PolygonBase::rotate_vector(_lt2zero, q);
            PolygonBase::rotate_vector(_rt2zero, q);
            PolygonBase::rotate_vector(_lb2zero, q);
            PolygonBase::rotate_vector(_rb2zero, q);
            PolygonBase::rotate_vector(_center2zero, q);
//            ScreenEye->rotate_vector(&ScreenEye->tblrXYZ.centerTip, q);
            break;

        case 'i': // 上翻
            axisTilt = ScreenEye->getScreenOnWorld2X64(); //screenOnWorld_toX 在 aGob已被归一化
//            cout << "axisTilt.x:" << axisTilt.dx << " axisTilt.y:" << axisTilt.dy <<
//            " axisTilt.z:" << axisTilt.dz << endl;
            q = ScreenDemo::create_rotation(goAngle, axisTilt);

            PolygonBase::rotate_vector(_lt2zero, q);
            PolygonBase::rotate_vector(_rt2zero, q);
            PolygonBase::rotate_vector(_lb2zero, q);
            PolygonBase::rotate_vector(_rb2zero, q);
            PolygonBase::rotate_vector(_center2zero, q);
//            ScreenEye->rotate_vector(&ScreenEye->tblrXYZ.centerTip, q);
            break;


            break;
        case 'k': // 下翻
            axisTilt = ScreenEye->getScreenOnWorld2X64(); //screenOnWorld_toX 在 aGob已被归一化
//            cout << "axisTilt.x:" << axisTilt.dx << " axisTilt.y:" << axisTilt.dy <<
//            " axisTilt.z:" << axisTilt.dz << endl;
            q = ScreenDemo::create_rotation(-goAngle, axisTilt);

            PolygonBase::rotate_vector(_lt2zero, q);
            PolygonBase::rotate_vector(_rt2zero, q);
            PolygonBase::rotate_vector(_lb2zero, q);
            PolygonBase::rotate_vector(_rb2zero, q);
            PolygonBase::rotate_vector(_center2zero, q);
//            ScreenEye->rotate_vector(&ScreenEye->tblrXYZ.centerTip, q);
            break;
        case 'u': // 左旋
            axisTilt = ScreenEye->getScreenOnWorld2Z64(); //screenOnWorld_toZ 在 aGob已被归一化

            q = ScreenDemo::create_rotation(goAngle, axisTilt);

            PolygonBase::rotate_vector(_lt2zero, q);
            PolygonBase::rotate_vector(_rt2zero, q);
            PolygonBase::rotate_vector(_lb2zero, q);
            PolygonBase::rotate_vector(_rb2zero, q);
            PolygonBase::rotate_vector(_center2zero, q);
//            ScreenEye->angleXYZ.z -= goAngle;
//            printf("+angleXYZ_t.z:%f\n", ScreenEye->angleXYZ.z); // 记录角度 模拟歪头
            break;
        case 'o': // 右旋
            axisTilt = ScreenEye->getScreenOnWorld2Z64(); //screenOnWorld_toZ 在 aGob已被归一化

            q = ScreenDemo::create_rotation(-goAngle, axisTilt);

            PolygonBase::rotate_vector(_lt2zero, q);
            PolygonBase::rotate_vector(_rt2zero, q);
            PolygonBase::rotate_vector(_lb2zero, q);
            PolygonBase::rotate_vector(_rb2zero, q);
            PolygonBase::rotate_vector(_center2zero, q);
//            ScreenEye->angleXYZ.z += goAngle;
//            printf("+angleXYZ_t.z:%f\n", ScreenEye->angleXYZ.z); // 记录角度 模拟歪头
            break;


    }
    // 屏幕归位
    ScreenEye->tblrXYZ.lt.x = _lt2zero.dx*_lt_0_len + backX;
    ScreenEye->tblrXYZ.rt.x = _rt2zero.dx*_rt_0_len + backX;
    ScreenEye->tblrXYZ.lb.x = _lb2zero.dx*_lb_0_len + backX;
    ScreenEye->tblrXYZ.rb.x = _rb2zero.dx*_rb_0_len + backX;
    ScreenEye->tblrXYZ.center.x = _center2zero.dx*_center_0_len + backX;
//    ScreenEye->tblrXYZ.centerTip.x = 0.0f + backX;

    ScreenEye->tblrXYZ.lt.y = _lt2zero.dy*_lt_0_len + backY;
    ScreenEye->tblrXYZ.rt.y = _rt2zero.dy*_rt_0_len + backY;
    ScreenEye->tblrXYZ.lb.y = _lb2zero.dy*_lb_0_len + backY;
    ScreenEye->tblrXYZ.rb.y = _rb2zero.dy*_rb_0_len + backY;
    ScreenEye->tblrXYZ.center.y = _center2zero.dy*_center_0_len + backY;
//    ScreenEye->tblrXYZ.centerTip.y = 0.0f + backY;

    ScreenEye->tblrXYZ.lt.z = _lt2zero.dz*_lt_0_len + backDEEP;
    ScreenEye->tblrXYZ.rt.z = _rt2zero.dz*_rt_0_len + backDEEP;
    ScreenEye->tblrXYZ.lb.z = _lb2zero.dz*_lb_0_len + backDEEP;
    ScreenEye->tblrXYZ.rb.z = _rb2zero.dz*_rb_0_len + backDEEP;
    ScreenEye->tblrXYZ.center.z = _center2zero.dz*_center_0_len + backDEEP;
//    ScreenEye->tblrXYZ.centerTip.z = 0.0f + backDEEP;

//    cout << "screen center x:" << ScreenEye->tblrXYZ.center.x <<
//    " y:" << ScreenEye->tblrXYZ.center.y << " z:" << ScreenEye->tblrXYZ.center.z << endl;
//    cout << "screen centerTip x:" << ScreenEye->tblrXYZ.centerTip.x <<
//    " y:" << ScreenEye->tblrXYZ.centerTip.y << " z:" << ScreenEye->tblrXYZ.centerTip.z << endl;


    glm::vec3 noLRcenter = eye2ScreenCenter_back2Zero(ScreenEye, ScreenEye->tblrXYZ.center,'j',goAngle);
    eye2ScreenCenter_back2Zero(ScreenEye, noLRcenter,'i',goAngle); // 刷新 角y 角x




#endif // quaternionFunc
#ifdef screenGoSameFlatTransfer // ###
    switch (key) {
        case 'j': // 左转

            screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.lt), 'j', goAngle);
            screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.rt), 'j', goAngle);
            screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.lb), 'j', goAngle);
            screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.rb), 'j', goAngle);
            screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.center), 'j', goAngle);
            //screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.centerTip), 'j', goAngle);


            //            ScreenEye->headLeft(goAngle);
            ScreenEye->freshAxisWorldOnAxisScreen();


//            ScreenEye->angleXYZ.y -= goAngle; // 坐标轴记录角度
//            printf("+angleXYZ_t.y:%f\n", ScreenEye->angleXYZ.y);
            break;
        case 'l': // 右转
            screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.lt), 'l', goAngle);
            screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.rt), 'l', goAngle);
            screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.lb), 'l', goAngle);
            screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.rb), 'l', goAngle);
            screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.center), 'l', goAngle);
            //screenTuring(ScreenEye, &(ScreenEye->tblrXYZ.centerTip), 'lbSet', goAngle);

//            ScreenEye->headRight(goAngle);
            ScreenEye->freshAxisWorldOnAxisScreen();


//            ScreenEye->angleXYZ.y += goAngle;
//            printf("-angleXYZ_t.y:%f\n", ScreenEye->angleXYZ.y);
            break;
        case 'i': // 上翻

            ScreenEye->headUp(goAngle);
            ScreenEye->freshAxisWorldOnAxisScreen();

//            ScreenEye->angleXYZ.x -= goAngle;
//            printf("+angleXYZ_t.x:%f\n", ScreenEye->angleXYZ.x);
            break;
        case 'k': // 下翻

            ScreenEye->headDown(goAngle);
            ScreenEye->freshAxisWorldOnAxisScreen();

//            ScreenEye->angleXYZ.x += goAngle;
//            printf("-angleXYZ_t.x:%f\n", ScreenEye->angleXYZ.x);
            break;
        case 'u': // 左旋

            ScreenEye->headRollBackClock(goAngle);
            ScreenEye->freshAxisWorldOnAxisScreen();

            break;
        case 'o': // 右旋

            ScreenEye->headRollForwardClock(goAngle);
            ScreenEye->freshAxisWorldOnAxisScreen();

            break;
    }
    // 刷新坐标 角y

    eye2ScreenCenter_back2Zero(ScreenEye, ScreenEye->tblrXYZ.center,'j',goAngle);

#endif // screenGoSameFlatTransfer ###

}
void screenTuring(ScreenDemo* ScreenEye, glm::vec3* XYZpoint,  char key, float angleOnce){

    //glm::vec3 _screenCenter = ScreenEye->axisXYZ.DEEPf; // 眼睛坐标
    glm::vec3 _screenCenter = ScreenEye->tblrXYZ.centerTip, _result; // 眼睛坐标 为中心点
    // 无需更改当前点 ,和中心重合
    if(_screenCenter.x == XYZpoint->x && _screenCenter.z == XYZpoint->z && _screenCenter.y == XYZpoint->y)return;

    _result = turningByCenter(&_screenCenter, *XYZpoint, key, angleOnce);
    XYZpoint->x = _result.x; // 刷新传入xyz坐标
    XYZpoint->y = _result.y;
    XYZpoint->z = _result.z;

}
void screenMoveXYZ(ScreenDemo *ScreenEyeGo, char key, float oneStep){
    // 更改三维空间坐标
    // 取地址修改class

    switch (key) {
        case 'q':  // 上移
            if (goUp){
                ScreenEyeGo->tblrXYZ.lt.y -= oneStep;
                ScreenEyeGo->tblrXYZ.rt.y -= oneStep;
                ScreenEyeGo->tblrXYZ.lb.y -= oneStep;
                ScreenEyeGo->tblrXYZ.rb.y -= oneStep;
                ScreenEyeGo->tblrXYZ.center.y -= oneStep;
                ScreenEyeGo->tblrXYZ.centerTip.y -= oneStep;
#ifdef screenGoSameFlatTransfer
                ScreenEyeGo->freshAxisWorldOnAxisScreen();
#endif
            }

            return;

        case 'e': // 下移
            if (goDown) {
                ScreenEyeGo->tblrXYZ.lt.y += oneStep;
                ScreenEyeGo->tblrXYZ.rt.y += oneStep;
                ScreenEyeGo->tblrXYZ.lb.y += oneStep;
                ScreenEyeGo->tblrXYZ.rb.y += oneStep;
                ScreenEyeGo->tblrXYZ.center.y += oneStep;
                ScreenEyeGo->tblrXYZ.centerTip.y += oneStep;
#ifdef screenGoSameFlatTransfer
                ScreenEyeGo->freshAxisWorldOnAxisScreen();
#endif
            }

            return;

        case 'w': // 前移

            if(goForward){
                ScreenEyeGo->tblrXYZ.lt.z += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rt.z += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.lb.z += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rb.z += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.center.z += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.centerTip.z += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));

                ScreenEyeGo->tblrXYZ.lt.x += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rt.x += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.lb.x += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rb.x += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.center.x += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.centerTip.x += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
#ifdef screenGoSameFlatTransfer
                ScreenEyeGo->freshAxisWorldOnAxisScreen();
#endif
            }
            return;

        case 's': // 后移
            if(goBack){
                ScreenEyeGo->tblrXYZ.lt.z -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rt.z -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.lb.z -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rb.z -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.center.z -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.centerTip.z -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));

                ScreenEyeGo->tblrXYZ.lt.x -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rt.x -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.lb.x -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rb.x -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.center.x -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.centerTip.x -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
#ifdef screenGoSameFlatTransfer
                ScreenEyeGo->freshAxisWorldOnAxisScreen();
#endif
            }
            return;
        case 'a': // 左移
            if(goLeft){
                ScreenEyeGo->tblrXYZ.lt.x -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rt.x -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.lb.x -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rb.x -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.center.x -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.centerTip.x -= oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));

                ScreenEyeGo->tblrXYZ.lt.z += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rt.z += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.lb.z += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rb.z += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.center.z += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.centerTip.z += oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
#ifdef screenGoSameFlatTransfer
                ScreenEyeGo->freshAxisWorldOnAxisScreen();
#endif
            }
            return;
        case 'd': // 右移
            if(goRight) {
                ScreenEyeGo->tblrXYZ.lt.x += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rt.x += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.lb.x += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rb.x += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.center.x += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.centerTip.x += oneStep * cosf(glm::radians(ScreenEyeGo->angleXYZ.y));

                ScreenEyeGo->tblrXYZ.lt.z -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rt.z -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.lb.z -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.rb.z -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.center.z -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
                ScreenEyeGo->tblrXYZ.centerTip.z -= oneStep * sinf(glm::radians(ScreenEyeGo->angleXYZ.y));
#ifdef screenGoSameFlatTransfer
                ScreenEyeGo->freshAxisWorldOnAxisScreen();
#endif
            }
            return;

    }

//    moveup:
//return;
//    movedown:
//return;

//    forward:
//    ScreenEyeGo->tblrXYZ.lt.z += oneStep;
//    ScreenEyeGo->tblrXYZ.rt.z += oneStep;
//    ScreenEyeGo->tblrXYZ.lb.z += oneStep;
//    ScreenEyeGo->tblrXYZ.rb.z += oneStep;
//    ScreenEyeGo->tblrXYZ.center.z += oneStep;
//    ScreenEyeGo->tblrXYZ.centerTip.z += oneStep;return;
//    backward:
//    ScreenEyeGo->tblrXYZ.lt.z -= oneStep;
//    ScreenEyeGo->tblrXYZ.rt.z -= oneStep;
//    ScreenEyeGo->tblrXYZ.lb.z -= oneStep;
//    ScreenEyeGo->tblrXYZ.rb.z -= oneStep;
//    ScreenEyeGo->tblrXYZ.center.z -= oneStep;
//    ScreenEyeGo->tblrXYZ.centerTip.z -= oneStep;return;
//    moveleft:
//    ScreenEyeGo->tblrXYZ.lt.y -= oneStep;
//    ScreenEyeGo->tblrXYZ.rt.y -= oneStep;
//    ScreenEyeGo->tblrXYZ.lb.y -= oneStep;
//    ScreenEyeGo->tblrXYZ.rb.y -= oneStep;
//    ScreenEyeGo->tblrXYZ.center.y -= oneStep;
//    ScreenEyeGo->tblrXYZ.centerTip.y -= oneStep;return;
//    moveright:
//    ScreenEyeGo->tblrXYZ.lt.y += oneStep;
//    ScreenEyeGo->tblrXYZ.rt.y += oneStep;
//    ScreenEyeGo->tblrXYZ.lb.y += oneStep;
//    ScreenEyeGo->tblrXYZ.rb.y += oneStep;
//    ScreenEyeGo->tblrXYZ.center.y += oneStep;
//    ScreenEyeGo->tblrXYZ.centerTip.y += oneStep;return;
}
void virtualScreenPointTurning(glm::vec3& startCenter, glm::vec3* XYZ_p, char key, angleXYZ_t* angleThisOr){
    // 转头
//    float angleX,radiusX,newX,newZ;
//    float angleY,radiusY,newY;
//    float eyeAxisAngle, eyeAxisRadius, hypotenuse;
    // 基于 世界坐标 原点
    glm::vec3* eyeXYZ_p = &startCenter;
    glm::vec3 _result;
    if(key == 'j')
    _result = turningByCenter(eyeXYZ_p,*XYZ_p,key, angleThisOr->y);
    else if(key == 'i')
    _result = turningByCenter(eyeXYZ_p,*XYZ_p,key, angleThisOr->x);
    else if(key == 'o')
    _result = turningByCenter(eyeXYZ_p,*XYZ_p,key, angleThisOr->z);

    XYZ_p->x = _result.x;
    XYZ_p->y = _result.y;
    XYZ_p->z = _result.z;


}
glm::vec3 eye2ScreenCenter_back2Zero(ScreenDemo* ScreenEye, glm::vec3 XYZpoint, char key, float angleOnce){
    float angleX,radiusX,newX,newZ;
    float angleY,radiusY,newY;
    float eyeAxisAngle, eyeAxisRadius, hypotenuse;

    //glm::vec3 eyeXYZ = ScreenEye->axisXYZ.DEEPf; // 眼睛坐标
    //static glm::vec3 eyeXYZ;
    glm::vec3* centerXYZ = &ScreenEye->tblrXYZ.centerTip; // 眼睛坐标 为中心点

    switch (key) {
        case 'j': // 左转 绕y轴

            angleX = glm::degrees(glm::atan(centerXYZ->x - XYZpoint.x , -centerXYZ->z + XYZpoint.z));
            std::cout << "眼 屏心 角X:" << angleX << std::endl;
            ScreenEye->angleXYZ.y = -angleX;
            radiusX = glm::sqrt(
                    (centerXYZ->x - XYZpoint.x) * (centerXYZ->x - XYZpoint.x)
                    + (-centerXYZ->z + XYZpoint.z) * (-centerXYZ->z + XYZpoint.z));
            //std::cout << "radiusX:" << radiusX << std::endl;
            //angleX += angleOnce;
            angleX = 0.0f;
            newX = centerXYZ->x - radiusX * 0.0f/*glm::sin(toRadians(angleX))*/;
            newZ = radiusX * 1.0f/*glm::cos(toRadians(angleX))*/ - (-centerXYZ->z);
            XYZpoint.x = newX;
            XYZpoint.z = newZ;
            break;
        case 'l': // 右转 绕y轴
            angleX = glm::degrees(glm::atan(centerXYZ->x - XYZpoint.x, -centerXYZ->z + XYZpoint.z));
            std::cout << "眼 屏心 角X:" << angleX << std::endl;
            ScreenEye->angleXYZ.y = -angleX;
            radiusX = glm::sqrt(
                    (centerXYZ->x - XYZpoint.x) * (centerXYZ->x - XYZpoint.x)
                    + (-centerXYZ->z + XYZpoint.z) * (-centerXYZ->z + XYZpoint.z));
            //std::cout << "radiusX:" << radiusX << std::endl;
            //angleX -= angleOnce;
            angleX = 0.0f;
            newX = centerXYZ->x - radiusX * 0.0f/*glm::sin(toRadians(angleX))*/;
            newZ = radiusX * 1.0f/*glm::cos(toRadians(angleX))*/ - (-centerXYZ->z);
            XYZpoint.x = newX;
            XYZpoint.z = newZ;
            break;
        case 'i': // 上转 绕x轴
            angleY = glm::degrees(glm::atan(centerXYZ->y - XYZpoint.y,
                                     -centerXYZ->z + XYZpoint.z));
            std::cout << "眼 屏心 角Y:" << angleY << std::endl;
            ScreenEye->angleXYZ.x = -angleY;
            radiusY = glm::sqrt(
                    (centerXYZ->y - XYZpoint.y) * (centerXYZ->y - XYZpoint.y) +
                    (-centerXYZ->z + XYZpoint.z) * (-centerXYZ->z + XYZpoint.z));
            //std::cout << "radiusY:" << radiusY << std::endl;
            //angleY += angleOnce;
            angleY = 0.0f;
            newY = centerXYZ->y - radiusY * 0.0f/*glm::sin(toRadians(angleY))*/;
            newZ = radiusY * 1.0f/*glm::cos(toRadians(angleY))*/ - (-centerXYZ->z);
            XYZpoint.y = newY;
            XYZpoint.z = newZ;
            break;
        case 'k': // 下转 绕x轴
            angleY = glm::degrees(glm::atan(centerXYZ->y - XYZpoint.y,
                                     -centerXYZ->z + XYZpoint.z));
            std::cout << "眼 屏心 角Y:" << angleY << std::endl;
            ScreenEye->angleXYZ.x = -angleY;
            radiusY = glm::sqrt(
                    (centerXYZ->y - XYZpoint.y) * (centerXYZ->y - XYZpoint.y)
                    + (-centerXYZ->z + XYZpoint.z) * (-centerXYZ->z + XYZpoint.z));
            //std::cout << "radiusY:" << radiusY << std::endl;
            //angleY -= angleOnce;
            angleY = 0.0f;
            newY = centerXYZ->y - radiusY * 0.0f/*glm::sin(toRadians(angleY))*/;
            newZ = radiusY * 1.0f/*glm::cos(toRadians(angleY))*/ - (-centerXYZ->z);
            XYZpoint.y = newY;
            XYZpoint.z = newZ;
            break;
        case 'u':
            // flat 平面
            hypotenuse = glm::sqrt((centerXYZ->x-XYZpoint.x) * (centerXYZ->x-XYZpoint.x)
                              + (centerXYZ->y-XYZpoint.y) * (centerXYZ->y-XYZpoint.y));



            //eyeAxisAngle = acos(  (centerXYZ->x-XYZpoint.x)/hypotenuse ) / M_PI * 180.0; // flat 临/斜
            eyeAxisAngle = glm::degrees(atan2f(-centerXYZ->x+XYZpoint.x, centerXYZ->y-XYZpoint.y));

            eyeAxisAngle = 180.0f - eyeAxisAngle; // 补角
            eyeAxisAngle -= angleOnce;

            //std::cout << "eyeAxisAngle:" << eyeAxisAngle << std::endl;

            eyeAxisRadius = hypotenuse;
            //std::cout << "eyeAxisRadius:" << eyeAxisRadius << std::endl;


            newX = glm::sin(glm::radians(eyeAxisAngle)) * eyeAxisRadius + centerXYZ->x;
            newY = glm::cos(glm::radians(eyeAxisAngle)) * eyeAxisRadius + centerXYZ->y;
            XYZpoint.x = newX;
            XYZpoint.y = newY;
            break;
        case 'o': // 右旋
            // flat 平面
            hypotenuse = glm::sqrt((centerXYZ->x-XYZpoint.x) * (centerXYZ->x-XYZpoint.x)
                              + (centerXYZ->y-XYZpoint.y) * (centerXYZ->y-XYZpoint.y));



            //eyeAxisAngle = acos(  (centerXYZ->x-XYZpoint.x)/hypotenuse ) / M_PI * 180.0; // flat 临/斜
            eyeAxisAngle = glm::degrees(atan2f(-centerXYZ->x+XYZpoint.x, centerXYZ->y-XYZpoint.y));

            eyeAxisAngle = 180.0f - eyeAxisAngle; // 补角
            eyeAxisAngle += angleOnce;

            //std::cout << "eyeAxisAngle:" << eyeAxisAngle << std::endl;

            eyeAxisRadius = hypotenuse;
            //std::cout << "eyeAxisRadius:" << eyeAxisRadius << std::endl;


            newX = glm::sin(glm::radians(eyeAxisAngle)) * eyeAxisRadius + centerXYZ->x;
            newY = glm::cos(glm::radians(eyeAxisAngle)) * eyeAxisRadius + centerXYZ->y;
            XYZpoint.x = newX;
            XYZpoint.y = newY;
            break;
    }
    return XYZpoint;
}

void axisMoveXYZ(AxisDemo* AxisWorld, char key, float oneStep) {

    // 数轴有 碰撞限制
    switch (key) {
        case 'q':
            if(goUp){
                if(!goDown)goDown = true;
                AxisWorld->axisXYZ.Xl.y -= oneStep;
                AxisWorld->axisXYZ.Xr.y -= oneStep;
                AxisWorld->axisXYZ.Yt.y -= oneStep;
                AxisWorld->axisXYZ.Yb.y -= oneStep;
                AxisWorld->axisXYZ.DEEPc.y -= oneStep;
                AxisWorld->axisXYZ.DEEPf.y -= oneStep;
//                cout << "axis up - " << oneStep << endl;
            }
            break;

        case 'e':
            if(goDown) {
                if(!goUp)goUp = true;
                AxisWorld->axisXYZ.Xl.y += oneStep;
                AxisWorld->axisXYZ.Xr.y += oneStep;
                AxisWorld->axisXYZ.Yt.y += oneStep;
                AxisWorld->axisXYZ.Yb.y += oneStep;
                AxisWorld->axisXYZ.DEEPc.y += oneStep;
                AxisWorld->axisXYZ.DEEPf.y += oneStep;
//                cout << "axis down + " << oneStep << endl;
            }
            break;


        case 'w': // 前移
            if(goForward){
                if(!goBack)goBack = true;
                AxisWorld->axisXYZ.Xl.z += oneStep;
                AxisWorld->axisXYZ.Xr.z += oneStep;
                AxisWorld->axisXYZ.Yt.z += oneStep;
                AxisWorld->axisXYZ.Yb.z += oneStep;
                AxisWorld->axisXYZ.DEEPc.z += oneStep;
                AxisWorld->axisXYZ.DEEPf.z += oneStep;
//                cout << "axis forward + " << oneStep << endl;
            }
            break;

        case 's': // 后移
            if(goBack){
                if(!goForward)goForward = true;
                AxisWorld->axisXYZ.Xl.z -= oneStep;
                AxisWorld->axisXYZ.Xr.z -= oneStep;
                AxisWorld->axisXYZ.Yt.z -= oneStep;
                AxisWorld->axisXYZ.Yb.z -= oneStep;
                AxisWorld->axisXYZ.DEEPc.z -= oneStep;
                AxisWorld->axisXYZ.DEEPf.z -= oneStep;
//                cout << "axis back - " << oneStep << endl;
            }
            break;
        case 'a': // 左移
            if(goLeft) {
                if(!goRight)goRight = true;
                AxisWorld->axisXYZ.Xl.x -= oneStep;
                AxisWorld->axisXYZ.Xr.x -= oneStep;
                AxisWorld->axisXYZ.Yt.x -= oneStep;
                AxisWorld->axisXYZ.Yb.x -= oneStep;
                AxisWorld->axisXYZ.DEEPc.x -= oneStep;
                AxisWorld->axisXYZ.DEEPf.x -= oneStep;
//                cout << "axis left - " << oneStep << endl;
            }
            break;
        case 'd': // 右移
            if(goRight) {
                if(!goLeft)goLeft = true;
                AxisWorld->axisXYZ.Xl.x += oneStep;
                AxisWorld->axisXYZ.Xr.x += oneStep;
                AxisWorld->axisXYZ.Yt.x += oneStep;
                AxisWorld->axisXYZ.Yb.x += oneStep;
                AxisWorld->axisXYZ.DEEPc.x += oneStep;
                AxisWorld->axisXYZ.DEEPf.x += oneStep;
//                cout << "axis right + " << oneStep << endl;
            }
            break;

    }
//    cout << "$$$axis Xl:" << AxisWorld->axisXYZ.Xl.x << " " << AxisWorld->axisXYZ.Xl.y << " " << AxisWorld->axisXYZ.Xl.z << endl;
//    cout << "$$$axis Xr:" << AxisWorld->axisXYZ.Xr.x << " " << AxisWorld->axisXYZ.Xr.y << " " << AxisWorld->axisXYZ.Xr.z << endl;
//    cout << "$$$axis Yb:" << AxisWorld->axisXYZ.Yb.x << " " << AxisWorld->axisXYZ.Yb.y << " " << AxisWorld->axisXYZ.Yb.z << endl;
//    cout << "$$$axis Yt:" << AxisWorld->axisXYZ.Yt.x << " " << AxisWorld->axisXYZ.Yt.y << " " << AxisWorld->axisXYZ.Yt.z << endl;
//    cout << "$$$axis DEEPc:" << AxisWorld->axisXYZ.DEEPc.x << " " << AxisWorld->axisXYZ.DEEPc.y << " " << AxisWorld->axisXYZ.DEEPc.z << endl;
//    cout << "$$$axis DEEPf:" << AxisWorld->axisXYZ.DEEPf.x << " " << AxisWorld->axisXYZ.DEEPf.y << " " << AxisWorld->axisXYZ.DEEPf.z << endl;
}
void axisTurnXYZ_EulerAngle(AxisDemo* AxisTilt, ScreenDemo* ScreenEye, char key, float goAngle){
    switch (key) {
        case 'j': // 左转

            // if(!by_axis)AxisTilt->axisXYZ.Xl = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Xl, 'j', goAngle);
            AxisTilt->axisXYZ.Xr = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Xr, 'j', goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.Yt = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Yt, 'j', goAngle);
            AxisTilt->axisXYZ.Yb = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Yb, 'j', goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.DEEPc = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.DEEPc, 'j', goAngle);
            AxisTilt->axisXYZ.DEEPf = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.DEEPf, 'j', goAngle);

//            freshAxisAngleX(AxisTilt);
//            AxisTilt->angleXYZ_t.y += goAngle; // 坐标轴记录角度
//            freshAxisAngleY(AxisTilt);
//            freshAxisAngleDEEP(AxisTilt);

            //printf("+angleXYZ_t.y:%f\n", AxisTilt->angleXYZ_t.y);
            break;
        case 'l': // 右转

            // if(!by_axis)AxisTilt->axisXYZ.Xl = turning_axis(ScreenEye, AxisTilt,
            //                                                     AxisTilt->axisXYZ.Xl, 'l', goAngle);
            AxisTilt->axisXYZ.Xr = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Xr, 'l',
                                                goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.Yt = turning_axis(ScreenEye, AxisTilt,
            //                                                     AxisTilt->axisXYZ.Yt, 'l', goAngle);
            AxisTilt->axisXYZ.Yb = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Yb, 'l',
                                                goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.DEEPc = turning_axis(ScreenEye, AxisTilt,
            //                                                        AxisTilt->axisXYZ.DEEPc, 'l', goAngle);
            AxisTilt->axisXYZ.DEEPf = turning_axis(ScreenEye, AxisTilt,  AxisTilt->axisXYZ.DEEPf, 'l',
                                                       goAngle);

//            freshAxisAngleX(AxisTilt);
//            AxisTilt->angleXYZ_t.y -= goAngle;
//            freshAxisAngleY(AxisTilt);
//            freshAxisAngleDEEP(AxisTilt);

            //printf("-angleXYZ_t.y:%f\n", AxisTilt->angleXYZ_t.y);
            break;
        case 'i': // 上翻

            // if(!by_axis)AxisTilt->axisXYZ.Xl = turning_axis(ScreenEye, AxisTilt,
            //                                                     AxisTilt->axisXYZ.Xl, 'i', goAngle);
            AxisTilt->axisXYZ.Xr = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Xr, 'i',
                                                goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.Yt = turning_axis(ScreenEye, AxisTilt,
            //                                                     AxisTilt->axisXYZ.Yt, 'i', goAngle);
            AxisTilt->axisXYZ.Yb = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Yb, 'i',
                                                goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.DEEPc = turning_axis(ScreenEye, AxisTilt,
            //                                                        AxisTilt->axisXYZ.DEEPc, 'i', goAngle);
            AxisTilt->axisXYZ.DEEPf = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.DEEPf, 'i',
                                                   goAngle);

//            freshAxisAngleY(AxisTilt);
//            AxisTilt->angleXYZ_t.x += goAngle;
//            freshAxisAngleX(AxisTilt);
//            freshAxisAngleDEEP(AxisTilt);

            //printf("+angleXYZ_t.x:%f\n", AxisTilt->angleXYZ_t.x);
            break;
        case 'k': // 下翻

            // if(!by_axis)AxisTilt->axisXYZ.Xl = turning_axis(ScreenEye, AxisTilt,
            //                                                     AxisTilt->axisXYZ.Xl, 'k', goAngle);
            AxisTilt->axisXYZ.Xr = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Xr, 'k',
                                                goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.Yt = turning_axis(ScreenEye, AxisTilt,
            //                                                     AxisTilt->axisXYZ.Yt, 'k', goAngle);
            AxisTilt->axisXYZ.Yb = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Yb, 'k',
                                                goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.DEEPc = turning_axis(ScreenEye, AxisTilt,
            //                                                        AxisTilt->axisXYZ.DEEPc, 'k', goAngle);
            AxisTilt->axisXYZ.DEEPf = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.DEEPf, 'k',
                                                   goAngle);

//            freshAxisAngleY(AxisTilt);
//            AxisTilt->angleXYZ_t.x -= goAngle;
//            freshAxisAngleX(AxisTilt);
//            freshAxisAngleDEEP(AxisTilt);

            //printf("-angleXYZ_t.x:%f\n", AxisTilt->angleXYZ_t.x);
            break;
        case 'u': // 左旋

            // if(!by_axis)AxisTilt->axisXYZ.Xl = turning_axis(ScreenEye, AxisTilt,
            //                                                     AxisTilt->axisXYZ.Xl, 'u', goAngle);
            AxisTilt->axisXYZ.Xr = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Xr, 'u',
                                                goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.Yt = turning_axis(ScreenEye, AxisTilt,
            //                                                     AxisTilt->axisXYZ.Yt, 'u', goAngle);
            AxisTilt->axisXYZ.Yb = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Yb, 'u',
                                                goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.DEEPc = turning_axis(ScreenEye, AxisTilt,
            //                                                        AxisTilt->axisXYZ.DEEPc, 'u', goAngle);
            AxisTilt->axisXYZ.DEEPf = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.DEEPf, 'u',
                                                   goAngle);

//            freshAxisAngleDEEP(AxisTilt);
//            AxisTilt->angleXYZ_t.z -= goAngle;
//            freshAxisAngleX(AxisTilt);
//            freshAxisAngleY(AxisTilt);

            //printf("-angleXYZ_t.z:%f\n", AxisTilt->angleXYZ_t.z);
            break;
        case 'o': // 右旋

            // if(!by_axis)AxisTilt->axisXYZ.Xl = turning_axis(ScreenEye, AxisTilt,
            //                                                     AxisTilt->axisXYZ.Xl, 'o', goAngle);
            AxisTilt->axisXYZ.Xr = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Xr, 'o',
                                                goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.Yt = turning_axis(ScreenEye, AxisTilt,
            //                                                     AxisTilt->axisXYZ.Yt, 'o', goAngle);
            AxisTilt->axisXYZ.Yb = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.Yb, 'o',
                                                goAngle);
            // if(!by_axis)AxisTilt->axisXYZ.DEEPc = turning_axis(ScreenEye, AxisTilt,
            //                                                        AxisTilt->axisXYZ.DEEPc, 'o', goAngle);
            AxisTilt->axisXYZ.DEEPf = turning_axis(ScreenEye, AxisTilt, AxisTilt->axisXYZ.DEEPf, 'o',
                                                   goAngle);

//            freshAxisAngleDEEP(AxisTilt);
//            AxisTilt->angleXYZ_t.z += goAngle;
//            freshAxisAngleX(AxisTilt);
//            freshAxisAngleY(AxisTilt);

            //printf("+angleXYZ_t.z:%f\n", AxisTilt->angleXYZ_t.z);
            break;
    }
}
void axisTurnXYZ_Quaternion(AxisDemo* AxisTilt,  ScreenDemo* ScreenEye, char key, float goAngle){

    float angle_rad = glm::radians(goAngle); // 斜转角
//    cout << " 坐标系 斜转角:" << angle_rad << endl;
    glm::vec3 backTo000;
    goLine64 obliqueAxis; // 斜转轴
    Quaternion q; // 所需 四元数

//    cout << "坐标系 o(" << AxisTilt->axisXYZ.Xl.x << "," << AxisTilt->axisXYZ.Xl.y << "," << AxisTilt->axisXYZ.Xl.z << ")" << endl;
//    cout << "坐标系 x(" << AxisTilt->axisXYZ.Xr.x << "," << AxisTilt->axisXYZ.Xr.y << "," << AxisTilt->axisXYZ.Xr.z << ")" << endl;
//    cout << "坐标系 y(" << AxisTilt->axisXYZ.Yb.x << "," << AxisTilt->axisXYZ.Yb.y << "," << AxisTilt->axisXYZ.Yb.z << ")" << endl;
//    cout << "坐标系 z(" << AxisTilt->axisXYZ.DEEPf.x << "," << AxisTilt->axisXYZ.DEEPf.y <<
//    "," << AxisTilt->axisXYZ.DEEPf.z << ")" << endl;

    switch (key) {
        case 'j': // 左转
            backTo000 = AxisTilt->axisXYZ.Yb - AxisTilt->axisXYZ.Xl;
            backTo000 = glm::normalize(backTo000);
            obliqueAxis.dx = backTo000.x;obliqueAxis.dy = backTo000.y;obliqueAxis.dz = backTo000.z;
            q = PolygonBase::create_rotation2(-angle_rad, obliqueAxis);


            AxisTilt->axisXYZ.Xr = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.Xr);

            AxisTilt->axisXYZ.DEEPf = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.DEEPf);

//            freshAxisAngleX(AxisTilt);
//            AxisTilt->angleXYZ_t.y += goAngle; // 坐标轴记录角度
//            freshAxisAngleY(AxisTilt);
//            freshAxisAngleDEEP(AxisTilt);

            //printf("+angleXYZ_t.y:%f\n", AxisTilt->angleXYZ_t.y);
            break;
        case 'l': // 右转
            backTo000 = AxisTilt->axisXYZ.Yb - AxisTilt->axisXYZ.Xl;
            backTo000 = glm::normalize(backTo000);
            obliqueAxis.dx = backTo000.x;obliqueAxis.dy = backTo000.y;obliqueAxis.dz = backTo000.z;
            q = PolygonBase::create_rotation2(angle_rad, obliqueAxis);


            AxisTilt->axisXYZ.Xr = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.Xr);

            AxisTilt->axisXYZ.DEEPf = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.DEEPf);

//            freshAxisAngleX(AxisTilt);
//            AxisTilt->angleXYZ_t.y -= goAngle;
//            freshAxisAngleY(AxisTilt);
//            freshAxisAngleDEEP(AxisTilt);

            //printf("-angleXYZ_t.y:%f\n", AxisTilt->angleXYZ_t.y);
            break;
        case 'i': // 上翻
            backTo000 = AxisTilt->axisXYZ.Xr - AxisTilt->axisXYZ.Xl;
            backTo000 = glm::normalize(backTo000);
            obliqueAxis.dx = backTo000.x;obliqueAxis.dy = backTo000.y;obliqueAxis.dz = backTo000.z;
            q = PolygonBase::create_rotation2(angle_rad, obliqueAxis);


            AxisTilt->axisXYZ.Yb = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.Yb);

            AxisTilt->axisXYZ.DEEPf = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.DEEPf);

//            freshAxisAngleY(AxisTilt);
//            AxisTilt->angleXYZ_t.x += goAngle;
//            freshAxisAngleX(AxisTilt);
//            freshAxisAngleDEEP(AxisTilt);

            //printf("+angleXYZ_t.x:%f\n", AxisTilt->angleXYZ_t.x);
            break;
        case 'k': // 下翻
            backTo000 = AxisTilt->axisXYZ.Xr - AxisTilt->axisXYZ.Xl;
            backTo000 = glm::normalize(backTo000);
            obliqueAxis.dx = backTo000.x;obliqueAxis.dy = backTo000.y;obliqueAxis.dz = backTo000.z;
            q = PolygonBase::create_rotation2(-angle_rad, obliqueAxis);



            AxisTilt->axisXYZ.Yb = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.Yb);

            AxisTilt->axisXYZ.DEEPf = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.DEEPf);

//            freshAxisAngleY(AxisTilt);
//            AxisTilt->angleXYZ_t.x -= goAngle;
//            freshAxisAngleX(AxisTilt);
//            freshAxisAngleDEEP(AxisTilt);

            //printf("-angleXYZ_t.x:%f\n", AxisTilt->angleXYZ_t.x);
            break;
        case 'u': // 左旋
            backTo000 = AxisTilt->axisXYZ.DEEPf - AxisTilt->axisXYZ.Xl;
            backTo000 = glm::normalize(backTo000);
            obliqueAxis.dx = backTo000.x;obliqueAxis.dy = backTo000.y;obliqueAxis.dz = backTo000.z;
            q = PolygonBase::create_rotation2(angle_rad, obliqueAxis);


            AxisTilt->axisXYZ.Xr = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.Xr);

            AxisTilt->axisXYZ.Yb = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.Yb);


//            freshAxisAngleDEEP(AxisTilt);
//            AxisTilt->angleXYZ_t.z -= goAngle;
//            freshAxisAngleX(AxisTilt);
//            freshAxisAngleY(AxisTilt);

            //printf("-angleXYZ_t.z:%f\n", AxisTilt->angleXYZ_t.z);
            break;
        case 'o': // 右旋
            backTo000 = AxisTilt->axisXYZ.DEEPf - AxisTilt->axisXYZ.Xl;
            backTo000 = glm::normalize(backTo000);
            obliqueAxis.dx = backTo000.x;obliqueAxis.dy = backTo000.y;obliqueAxis.dz = backTo000.z;
            q = PolygonBase::create_rotation2(-angle_rad, obliqueAxis);


            AxisTilt->axisXYZ.Xr = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.Xr);

            AxisTilt->axisXYZ.Yb = turning_axis_Quaternion(AxisTilt,q, AxisTilt->axisXYZ.Yb);


//            freshAxisAngleDEEP(AxisTilt);
//            AxisTilt->angleXYZ_t.z += goAngle;
//            freshAxisAngleX(AxisTilt);
//            freshAxisAngleY(AxisTilt);

            //printf("+angleXYZ_t.z:%f\n", AxisTilt->angleXYZ_t.z);
            break;
    }
    float checkNormalize = glm::sqrt(obliqueAxis.dx * obliqueAxis.dx +
            obliqueAxis.dy * obliqueAxis.dy + obliqueAxis.dz * obliqueAxis.dz);

//    cout << " 坐标系 斜转轴:" << obliqueAxis.dx << ", " << obliqueAxis.dy << ", " << obliqueAxis.dz << endl;
//    assert(checkNormalize > 0.999 && checkNormalize < 1.001);
}

glm::vec3 turning_axis_Quaternion(AxisDemo* AxisTilt, Quaternion q, glm::vec3 outP) {

//    bool out_p_inf = glm::isinf(outP.x) || glm::isinf(outP.y) || glm::isinf(outP.z);
//    if(out_p_inf){
//        cerr << "outP is inf" << endl;
//        return outP;
//    }

//    float backX = AxisTilt->axisXYZ.Xl.x;
//    float backY = AxisTilt->axisXYZ.Xl.y;
//    float backZ = AxisTilt->axisXYZ.Xl.z;

//    cout << " 先outP:" << outP.x << ", " << outP.y << ", " << outP.z << endl;
//    cout << " 先 坐标系o点:" << AxisTilt->axisXYZ.Xl.x << ", " <<
//         AxisTilt->axisXYZ.Xl.y << ", " << AxisTilt->axisXYZ.Xl.z << endl;
    outP = outP - AxisTilt->axisXYZ.Xl; // 移 原点
    float pLenToOrigin = glm::length(outP); // 求长
//    cout << "归原点 outP:" << outP.x << ", " << outP.y << ", " << outP.z << endl;
//    cout << "归原点 outP 距原点:" << pLenToOrigin << endl;
    goLine64 shortenP;
    shortenP.dx = outP.x / pLenToOrigin; // 缩一
    shortenP.dy = outP.y / pLenToOrigin;
    shortenP.dz = outP.z / pLenToOrigin;
//    cout << "转前点:" << shortenP.dx << ", " << shortenP.dy << ", " << shortenP.dz << endl;
    PolygonBase::rotate_vector(shortenP, q); // 斜转
//    cout << "转后点:" << shortenP.dx << ", " << shortenP.dy << ", " << shortenP.dz << endl;

    glm::vec3 resultP = {shortenP.dx * pLenToOrigin,
                         shortenP.dy * pLenToOrigin,
                         shortenP.dz * pLenToOrigin}; // 伸回去
//    cout << " 转后点 伸回去:" << resultP.x << ", " << resultP.y << ", " << resultP.z << endl;
    resultP += AxisTilt->axisXYZ.Xl; // 移 原来
//    cout << " 转后点 移 原来:" << resultP.x << ", " << resultP.y << ", " << resultP.z << endl;
    return resultP;
}

glm::vec3 turning_axis(ScreenDemo* ScreenEye,AxisDemo* AxisTilt, glm::vec3 XYZpoint, char key, float angleOnce){
    // 只axis 其他还一样
    // 转头

    //glm::vec3 centerTypeXYZ = ScreenEye->axisXYZ.DEEPf; // 眼睛坐标
    glm::vec3 centerTypeXYZ, _result;
    // if(!by_axis) {
    //     centerTypeXYZ = ScreenEye->tblrXYZ.center; // 屏幕正中
    //     _result = turningByCenter(&centerTypeXYZ, XYZpoint, key, angleOnce);
    // }else{
        centerTypeXYZ = AxisTilt->axisXYZ.DEEPc; // 数轴原点坐标
        _result = turningByCenter(&centerTypeXYZ, XYZpoint, key, angleOnce);
//        if(AxisTilt->axisXYZ.DEEPc == AxisTilt->axisXYZ.Xl){
//            puts("DEEPc == Xl");
//        }else{
//            perror("DEEPc != Xl");
//        }
    // }

    return _result;
}
void freshTBLRXY_axis(AxisDemo* AxisTilt, AxisDemo* ParallelAxis, ScreenDemo* ScreenEye){
    // 只axis 其他还一样       坐标系刷新
    glm::vec2 couple_lt;
    glm::vec2 couple_rt;
    glm::vec2 couple_lb;
    glm::vec2 couple_rb;
    glm::vec2 couple_center;
    glm::vec2 couple_centerTip;


    couple_lt = virtual_Pos_3Dto2D(ScreenEye, AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z); // X left
    couple_rt= virtual_Pos_3Dto2D(ScreenEye, AxisTilt->axisXYZ.Xr.x, AxisTilt->axisXYZ.Xr.y, AxisTilt->axisXYZ.Xr.z); // X right

    couple_rb= virtual_Pos_3Dto2D(ScreenEye, AxisTilt->axisXYZ.Yb.x, AxisTilt->axisXYZ.Yb.y, AxisTilt->axisXYZ.Yb.z); // Y top
    couple_lb = virtual_Pos_3Dto2D(ScreenEye, AxisTilt->axisXYZ.Yt.x, AxisTilt->axisXYZ.Yt.y, AxisTilt->axisXYZ.Yt.z); // Y bottom
    couple_center = virtual_Pos_3Dto2D(ScreenEye, AxisTilt->axisXYZ.DEEPc.x, AxisTilt->axisXYZ.DEEPc.y,
                                       AxisTilt->axisXYZ.DEEPc.z); // DEEP close
    couple_centerTip = virtual_Pos_3Dto2D(ScreenEye, AxisTilt->axisXYZ.DEEPf.x, AxisTilt->axisXYZ.DEEPf.y,
                                          AxisTilt->axisXYZ.DEEPf.z); // DEEP far

    AxisTilt->setTBLRXY(
            {couple_lt.x, couple_lt.y},
            {couple_rt.x, couple_rt.y},
            {couple_rb.x, couple_rb.y},
            {couple_lb.x, couple_lb.y},
            {couple_center.x, couple_center.y},
            {couple_centerTip.x, couple_centerTip.y}
    );

    // 坐标轴平行坐标系刷新  斜轴拿原点  算平行各轴始末
    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z }; // 坐标系 当下原点
    AxisXYZ paralel_axisXYZ = AxisXYZ(
            { axis_0_0_0.x-40,axis_0_0_0.y,axis_0_0_0.z },     //Xl         X
            { axis_0_0_0.x+200,axis_0_0_0.y,axis_0_0_0.z },     //Xr         X
            { axis_0_0_0.x,axis_0_0_0.y-40,axis_0_0_0.z },     //Yt         Y
            { axis_0_0_0.x,axis_0_0_0.y+200,axis_0_0_0.z},     //Yb         Y
            { axis_0_0_0.x,axis_0_0_0.y,axis_0_0_0.z-40 },     //DEEPc     DEEP
            { axis_0_0_0.x,axis_0_0_0.y,axis_0_0_0.z+200 });   //DEEPf   DEEP
    // 平行轴坐标系刷新 (出界不渲染)
    ParallelAxis->setTBLRXYZ(paralel_axisXYZ.Xl,paralel_axisXYZ.Xr,paralel_axisXYZ.Yt,paralel_axisXYZ.Yb,paralel_axisXYZ.DEEPc,paralel_axisXYZ.DEEPf);
    // 转2D 组
    couple_lt = virtual_Pos_3Dto2D(ScreenEye, paralel_axisXYZ.Xl.x, paralel_axisXYZ.Xl.y, paralel_axisXYZ.Xl.z); // X left
    couple_rt= virtual_Pos_3Dto2D(ScreenEye, paralel_axisXYZ.Xr.x, paralel_axisXYZ.Xr.y, paralel_axisXYZ.Xr.z); // X right

    couple_rb= virtual_Pos_3Dto2D(ScreenEye, paralel_axisXYZ.Yb.x, paralel_axisXYZ.Yb.y, paralel_axisXYZ.Yb.z); // Y top
    couple_lb = virtual_Pos_3Dto2D(ScreenEye, paralel_axisXYZ.Yt.x, paralel_axisXYZ.Yt.y, paralel_axisXYZ.Yt.z); // Y bottom
    couple_center = virtual_Pos_3Dto2D(ScreenEye, paralel_axisXYZ.DEEPc.x, paralel_axisXYZ.DEEPc.y,
                                       paralel_axisXYZ.DEEPc.z); // DEEP close
    couple_centerTip = virtual_Pos_3Dto2D(ScreenEye, paralel_axisXYZ.DEEPf.x, paralel_axisXYZ.DEEPf.y,
                                          paralel_axisXYZ.DEEPf.z); // DEEP far


    ParallelAxis->setTBLRXY(
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
void freshTBLRXY_axis_Go(AxisDemo* AxisTilt, AxisDemo* ParallelAxis, ScreenDemo* ScreenEyeL){
    // 只axis 其他还一样       坐标系刷新
    glm::vec2 couple_lt;
    glm::vec2 couple_rt;
    glm::vec2 couple_lb;
    glm::vec2 couple_rb;
    glm::vec2 couple_center;
    glm::vec2 couple_centerTip;


    couple_lt = spotEyeScreenGo(ScreenEyeL, AxisTilt->axisXYZ.Xl, nullptr); // X left
    couple_rt= spotEyeScreenGo(ScreenEyeL, AxisTilt->axisXYZ.Xr, nullptr); // X right

    couple_rb= spotEyeScreenGo(ScreenEyeL,AxisTilt->axisXYZ.Yb, nullptr); // Y top
    couple_lb = spotEyeScreenGo(ScreenEyeL, AxisTilt->axisXYZ.Yt, nullptr); // Y bottom
    couple_center = spotEyeScreenGo(ScreenEyeL, AxisTilt->axisXYZ.DEEPc, nullptr); // DEEP close
    couple_centerTip = spotEyeScreenGo(ScreenEyeL, AxisTilt->axisXYZ.DEEPf, nullptr/*数轴没有虚拟点缓存*/); // DEEP far

    AxisTilt->setTBLRXY(
            {couple_lt.x, couple_lt.y},
            {couple_rt.x, couple_rt.y},
            {couple_rb.x, couple_rb.y},
            {couple_lb.x, couple_lb.y},
            {couple_center.x, couple_center.y},
            {couple_centerTip.x, couple_centerTip.y}
    );

    // 坐标轴平行坐标系刷新  斜轴拿原点  算平行各轴始末
    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z }; // 坐标系 当下原点
    AxisXYZ paralel_axisXYZ = AxisXYZ(
            { axis_0_0_0.x-40,axis_0_0_0.y,axis_0_0_0.z },     //Xl         X
            { axis_0_0_0.x+200,axis_0_0_0.y,axis_0_0_0.z },     //Xr         X
            { axis_0_0_0.x,axis_0_0_0.y-40,axis_0_0_0.z },     //Yt         Y
            { axis_0_0_0.x,axis_0_0_0.y+200,axis_0_0_0.z},     //Yb         Y
            { axis_0_0_0.x,axis_0_0_0.y,axis_0_0_0.z-40 },     //DEEPc     DEEP
            { axis_0_0_0.x,axis_0_0_0.y,axis_0_0_0.z+200 });   //DEEPf   DEEP

    // 平行轴坐标系刷新 (出界不渲染)
    ParallelAxis->setTBLRXYZ(paralel_axisXYZ.Xl,paralel_axisXYZ.Xr,paralel_axisXYZ.Yt,paralel_axisXYZ.Yb,paralel_axisXYZ.DEEPc,paralel_axisXYZ.DEEPf);
    // 转2D 组
    couple_lt = spotEyeScreenGo(ScreenEyeL, paralel_axisXYZ.Xl, nullptr); // X left
    couple_rt= spotEyeScreenGo(ScreenEyeL, paralel_axisXYZ.Xr, nullptr); // X right

    couple_rb= spotEyeScreenGo(ScreenEyeL, paralel_axisXYZ.Yb, nullptr); // Y top
    couple_lb = spotEyeScreenGo(ScreenEyeL, paralel_axisXYZ.Yt, nullptr); // Y bottom
    couple_center = spotEyeScreenGo(ScreenEyeL, paralel_axisXYZ.DEEPc, nullptr); // DEEP close
    couple_centerTip = spotEyeScreenGo(ScreenEyeL, paralel_axisXYZ.DEEPf, nullptr); // DEEP far


    ParallelAxis->setTBLRXY(
            {couple_lt.x, couple_lt.y},
            {couple_rt.x, couple_rt.y},
            {couple_rb.x, couple_rb.y},
            {couple_lb.x, couple_lb.y},
            {couple_center.x, couple_center.y},
            {couple_centerTip.x, couple_centerTip.y}
    );

}



glm::vec3 turning_by_axis(glm::vec3 axis_0_0_0,glm::vec3 XYZ, char key, float angleOnce){
    // 转头
    // 基于 世界坐标 原点

    glm::vec3 _result;
    _result = turningByCenter(&axis_0_0_0, XYZ, key, angleOnce);

    return _result;
}
void freshTBLRXY_by_axis(RectDemo* rectMain, AxisDemo* AxisTilt, AxisDemo* AxisParallel, ScreenDemo* ScreenEye, char key){
    glm::vec2 couple_lt;
    glm::vec2 couple_rt;
    glm::vec2 couple_lb;
    glm::vec2 couple_rb;
    glm::vec2 couple_center;
    glm::vec2 couple_centerTip;

//    { -40,0,0 },     //Xl         X
//    { 500,0,0 },     //Xr         X
//    { 0,-40,0 },     //Yt         Y
//    { 0,500,0},     //Yb         Y
//    { 0,0,-40 },     //DEEPc     DEEP
//    { 0,0,500 });   //DEEPf   DEEP
    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z };
    //printf("axis_0_0_0:%f,%f,%f\n",axis_0_0_0.y,axis_0_0_0.x,axis_0_0_0.z);
    // FLT_MAX 最大
    // ➗ glm::cos() 转角

    glm::vec3& lbXYZ = rectMain->tblrXYZ.lb;
    glm::vec3& rtXYZ = rectMain->tblrXYZ.rt;
    glm::vec3& ltXYZ = rectMain->tblrXYZ.lt;
    glm::vec3& rbXYZ = rectMain->tblrXYZ.rb;
    glm::vec3& centerXYZ = rectMain->tblrXYZ.center;
    glm::vec3& centerTipXYZ = rectMain->tblrXYZ.centerTip;
    //     左转 上翻 右旋 + 右转 下翻 左旋 -     旋转用parallel
    if(key == 'j' || key == 'i' || key == 'o' || key == 'l' || key == 'k' || key == 'u'){
        lbXYZ = turning_by_axis(axis_0_0_0, lbXYZ,key, goAngle );
        rtXYZ = turning_by_axis(axis_0_0_0, rtXYZ, key, goAngle);
        ltXYZ = turning_by_axis(axis_0_0_0, ltXYZ, key, goAngle);
        rbXYZ = turning_by_axis(axis_0_0_0, rbXYZ, key, goAngle);

        rectMain->setTBLRXYZ(ltXYZ,rtXYZ,rbXYZ,lbXYZ); // 刷新单面坐标 3D
    }else{
        rectMoveXYZ(rectMain, key, goStep);
    }
    //     左转 上翻 右旋 + 右转 下翻 左旋 -
    couple_lb = virtual_Pos_3Dto2D(ScreenEye,
                                   lbXYZ.x, lbXYZ.y, lbXYZ.z); // 左下角

    couple_rt = virtual_Pos_3Dto2D(ScreenEye,
                                   rtXYZ.x, rtXYZ.y, rtXYZ.z); // 右上角

    couple_lt = virtual_Pos_3Dto2D(ScreenEye,
                                   ltXYZ.x, ltXYZ.y, ltXYZ.z); // 左下角

    couple_rb = virtual_Pos_3Dto2D(ScreenEye,
                                   rbXYZ.x, rbXYZ.y, rbXYZ.z); // 右下角

    couple_center = virtual_Pos_3Dto2D(ScreenEye,
                                       centerXYZ.x, centerXYZ.y, centerXYZ.z); // 中心

    couple_centerTip = virtual_Pos_3Dto2D(ScreenEye,
                                          centerTipXYZ.x, centerTipXYZ.y, centerTipXYZ.z); // 中心


    rectMain->setTBLRXY_f(
            couple_lt,
            couple_rt,
            couple_rb,
            couple_lb,
            couple_center,
            couple_centerTip
    );
//    rectMain->angleXYZ_t.y = AxisTilt->angleXYZ_t.y; // 角度同步
//    rectMain->angleXYZ_t.x = AxisTilt->angleXYZ_t.x;
//    rectMain->angleXYZ_t.z = AxisTilt->angleXYZ_t.z;

//    printf("显┌xy:%d,%d\n",couple_lt.y,couple_lt.x);
//    printf("显┐xy:%d,%d\n",couple_rt.y,couple_rt.x);
//    printf("显└xy:%d,%d\n",couple_lb.y,couple_lb.x);
//    printf("显┘xy:%d,%d\n",couple_rb.y,couple_rb.x);
}
void freshTBLRXY_by_axis_Go(RectDemo* rectMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL){
    glm::vec2 couple_lt;
    glm::vec2 couple_rt;
    glm::vec2 couple_lb;
    glm::vec2 couple_rb;
    glm::vec2 couple_center;
    glm::vec2 couple_centerTip;


    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z };
    //printf("axis_0_0_0:%f,%f,%f\n",axis_0_0_0.y,axis_0_0_0.x,axis_0_0_0.z);
    // FLT_MAX 最大
    // ➗ glm::cos() 转角

    // 3D xyz三步走 每步xyz都要动 都要 动
    glm::vec3 lbXYZ;
    lbXYZ = AxisTilt->goX(axis_0_0_0, rectMain->tblrXYZ_unchange.lb.x);
    lbXYZ = AxisTilt->goY(lbXYZ, rectMain->tblrXYZ_unchange.lb.y);
    lbXYZ = AxisTilt->goDEEP(lbXYZ, rectMain->tblrXYZ_unchange.lb.z);

    glm::vec3 rtXYZ;
    rtXYZ = AxisTilt->goX(axis_0_0_0, rectMain->tblrXYZ_unchange.rt.x);
    rtXYZ = AxisTilt->goY(rtXYZ, rectMain->tblrXYZ_unchange.rt.y);
    rtXYZ = AxisTilt->goDEEP(rtXYZ, rectMain->tblrXYZ_unchange.rt.z);

    glm::vec3 ltXYZ;
    ltXYZ = AxisTilt->goX(axis_0_0_0, rectMain->tblrXYZ_unchange.lt.x);
    ltXYZ = AxisTilt->goY(ltXYZ, rectMain->tblrXYZ_unchange.lt.y);
    ltXYZ = AxisTilt->goDEEP(ltXYZ, rectMain->tblrXYZ_unchange.lt.z);

    glm::vec3 rbXYZ;
    rbXYZ = AxisTilt->goX(axis_0_0_0, rectMain->tblrXYZ_unchange.rb.x);
    rbXYZ = AxisTilt->goY(rbXYZ, rectMain->tblrXYZ_unchange.rb.y);
    rbXYZ = AxisTilt->goDEEP(rbXYZ, rectMain->tblrXYZ_unchange.rb.z);


    rectMain->setTBLRXYZ(ltXYZ,rtXYZ,rbXYZ,lbXYZ); // 更新3D坐标 center back

    //     左转 上翻 右旋 + 右转 下翻 左旋 -

    couple_lt = spotEyeScreenGo(ScreenEyeL, ltXYZ, rectMain->virtual_tblrXYZ); // 左下角
    couple_rt = spotEyeScreenGo(ScreenEyeL, rtXYZ, rectMain->virtual_tblrXYZ+1); // 右上角
    couple_rb = spotEyeScreenGo(ScreenEyeL, rbXYZ, rectMain->virtual_tblrXYZ+2); // 右下角
    couple_lb = spotEyeScreenGo(ScreenEyeL, lbXYZ, rectMain->virtual_tblrXYZ+3); // 左下角
    couple_center = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.center, rectMain->virtual_tblrXYZ+4); // 中心

    couple_centerTip = spotEyeScreenGo(ScreenEyeL, rectMain->tblrXYZ.centerTip, rectMain->virtual_tblrXYZ+5); // 中心
                                                                                            // 各面缓存 屏幕扶正虚点

    rectMain->setTBLRXY_f(
            couple_lt,
            couple_rt,
            couple_rb,
            couple_lb,
            couple_center,
            couple_centerTip
    );
}


//POINT virtual_Pos_3Dto2D(RectDemo* ScreenEye, float y, float x, float deep)


// struct _3d_2d_go_head{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_2d)(ScreenDemo* , float x, float y, float deep);
// };
_3d_2d_go_func _3d_2d_go_head_1 = {&spotEyeScreenGo, &virtual_Pos_3Dto2D};


void* _3d_2d_go_void_ptr = &_3d_2d_go_head_1;
extern void* _3d_2d_go_void_ptr;


#endif //RECTANGLEDISPLAY_CALC_FUNC_3D2D_H
