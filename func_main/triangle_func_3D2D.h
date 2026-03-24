//
// Created by iceoc0 on 2024/11/9.
//

#ifndef RECTANGLEDISPLAY_TRIANGLE_FUNC_3D2D_H
#define RECTANGLEDISPLAY_TRIANGLE_FUNC_3D2D_H

#include"FogPoint_func.h"

#include"../polygonClass/TriangleDemo.h"


[[maybe_unused]]void freshTriaCollisionClose(TriangleDemo* triangleMain,  RectDemo* footSquare, char key,float oneStep);

void triangleMoveXYZ(TriangleDemo* triangleMain,RectDemo* footSquare, char key,float oneStep);
void triangleTurnXYZ(TriangleDemo* triangleMain,ScreenDemo* ScreenEye,RectDemo* footSquare, char key, float goAngle);
void triangleCenterTurnXYZ(TriangleDemo* triangleMain, glm::vec3* centerPoint, char key, float goAngle);
void triangleTurn_Unchange_XYZ(TriangleDemo* triangleMain, glm::vec3* centerPoint, char key, float goAngle);
//spotXYZ pointTurning(ScreenDemo* ScreenEye,spotXYZ XYZ, char key, float angleOnce); 有了
void fresh2S2M2L_XY(TriangleDemo* triangleMain, ScreenDemo* ScreenEye);
void fresh2S2M2L_XY_Go(TriangleDemo* triangleMain, ScreenDemo* ScreenEyeL);


void fresh2S2M2L_XY_by_axis(TriangleDemo* triangleMain, RectDemo* footSquare, AxisDemo* AxisWorld, ScreenDemo* ScreenEye, char key);
void fresh2S2M2L_XY_by_axis_Go(TriangleDemo* triangleMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL);


void freshTriaCollisionClose(TriangleDemo* triangleMain, RectDemo* footSquare, char key,float oneStep){
    switch (key) {
        case 'q':
            if (goUp){
                goDown = true;
                if(triangleMain->rightest().x > footSquare->tblrXYZ_unchange.lt.x // 右侵左
                   && triangleMain->leftest().x < footSquare->tblrXYZ_unchange.rt.x // 左侵右
                   && triangleMain->fontmost().z < footSquare->tblrXYZ_unchange.lt.z // 前侵前
                   && triangleMain->backmost().z > footSquare->tblrXYZ_unchange.lb.z) { // 背侵背 看

                    if(triangleMain->topmost().y > footSquare->tblrXYZ_unchange.lt.y) { // 顶未侵底 看
                        //printf("~~~~triangle top point:%f, triangle bottom point:%f\n",triangleMain->topmost().x,triangleMain->bottommost().x);
                        if(triangleMain->topmost().y > footSquare->tblrXYZ_unchange.lt.y + oneStep) { // 够一步

                        }else{ // 小半步
                            goUp = false;//return;
                        }

                    }else if(triangleMain->bottommost().y < footSquare->tblrXYZ.lb.y) { // 底未侵顶 ok

                    }else{ // 前后左右上下过近
                        goUp = false;//return;
                    }
                }else{ // 或前 或后 或左 或右 ok

                }

            }
            return;

        case 'e':

            if (goDown) {
                goUp = true;
                if(triangleMain->rightest().x > footSquare->tblrXYZ_unchange.lt.x
                   && triangleMain->leftest().x < footSquare->tblrXYZ_unchange.rt.x // 非左过 非右过 看
                   && triangleMain->fontmost().z < footSquare->tblrXYZ_unchange.lt.z
                   && triangleMain->backmost().z > footSquare->tblrXYZ_unchange.lb.z) { // 非前过 非后过 看
                    if(triangleMain->topmost().y > footSquare->tblrXYZ_unchange.lt.y){ // 判触底 ok

                    }else if(triangleMain->bottommost().y < footSquare->tblrXYZ.lb.y) { // 判触顶
                        if(triangleMain->bottommost().y < footSquare->tblrXYZ.lb.y - oneStep) { // 够一步

                        }else{ // 小半步
                            goDown = false;//return;
                        }
                    }else{ // 前后左右上下过近
                        goDown = false;//return;
                    }
                }else{ // 或前 或后 或左 或右 ok

                }

            }
            return;


        case 'w': // 前移

            if(goForward){
                goBack = true;
                if(triangleMain->topmost().y < footSquare->tblrXYZ_unchange.lt.y
                   && triangleMain->bottommost().y > footSquare->tblrXYZ.lt.y// 非上越 非下越 看
                   && (triangleMain->rightest().x > footSquare->tblrXYZ_unchange.lt.x)
                   && (triangleMain->leftest().x < footSquare->tblrXYZ_unchange.rt.x)) {// 非左过 非右过 看

                    if (triangleMain->fontmost().z > footSquare->tblrXYZ_unchange.lt.z) { // 判前过近 OK


                    }else if(triangleMain->backmost().z < footSquare->tblrXYZ_unchange.lb.z){
                        //判后过近 看
                        if( triangleMain->backmost().z < footSquare->tblrXYZ_unchange.lb.z - oneStep) { // 后距够一步

                        }else{ // 小半步
                            goForward = false;//return;
                        }
                    }else{ // 前后左右上下过近
                        goForward = false;//return;
                    }

                }else { // 左右躲 上越 或 下越 ok

                }


            }
            return;

        case 's': // 后移
            if(goBack){
                goForward = true;
                if(triangleMain->topmost().y < footSquare->tblrXYZ_unchange.lt.y
                   && triangleMain->bottommost().y > footSquare->tblrXYZ.lt.y // 非上越 非下越 看
                   && (triangleMain->rightest().x > footSquare->tblrXYZ_unchange.lt.x)
                   && (triangleMain->leftest().x < footSquare->tblrXYZ_unchange.rt.x)) // 非左过 非右过 看
                {
                    if (triangleMain->fontmost().z > footSquare->tblrXYZ_unchange.lt.z) { // 判前过近 看
                        if (triangleMain->fontmost().z > footSquare->tblrXYZ_unchange.lt.z + oneStep){ // 够一步

                        }else{ // 小半步
                            goBack = false;//return;
                        }
                    }else if(triangleMain->backmost().z < footSquare->tblrXYZ_unchange.lb.z){
                        //判后过近 ok

                    }else{ // 前后左右上下过近
                        goBack = false;//return;
                    }
                } else { // 左右躲 上越 或 下越 ok

                }


            }
            return;

        case 'a': // 左移
            if(goLeft){
                goRight = true;
                if(triangleMain->topmost().y < footSquare->tblrXYZ_unchange.lt.y
                   && triangleMain->bottommost().y > footSquare->tblrXYZ.lt.y // 非上越 非下越 看
                   && triangleMain->fontmost().z < footSquare->tblrXYZ_unchange.lt.z
                   && triangleMain->backmost().z > footSquare->tblrXYZ_unchange.lb.z) { // 非前过 非后过 看
                    if (triangleMain->rightest().x < footSquare->tblrXYZ_unchange.lt.x) { // 左空 OK

                    } else if (triangleMain->leftest().x > footSquare->tblrXYZ_unchange.rt.x) {
                        // 右空 看
                        if (triangleMain->leftest().x > footSquare->tblrXYZ_unchange.rt.x + oneStep){ // 够一步

                        }else{ // 小半步
                            goLeft = false;//return;
                        }
                    } else { // 前后左右上下过近
                        goLeft = false;//return;
                    }

                } else { // 前过 后过 上越 或 下越 ok

                }


            }
            return;
        case 'd': // 右移
            if(goRight) {
                goLeft = true;
                if(triangleMain->topmost().y < footSquare->tblrXYZ_unchange.lt.y
                   && triangleMain->bottommost().y > footSquare->tblrXYZ.lt.y
                   && triangleMain->fontmost().z < footSquare->tblrXYZ_unchange.lt.z // 非上越 非下越 看
                   && triangleMain->backmost().z > footSquare->tblrXYZ_unchange.lb.z) { // 非前过 非后过 看
                    if (triangleMain->leftest().x > footSquare->tblrXYZ_unchange.rt.x) { // 右空 OK

                    } else if (triangleMain->rightest().x < footSquare->tblrXYZ_unchange.lt.x) {
                        // 左空 看
                        if (triangleMain->rightest().x < footSquare->tblrXYZ_unchange.lt.x - oneStep){ // 够一步

                        }else{ // 小半步
                            goRight = false;//return;
                        }
                    } else { // 前后左右上下过近
                        goRight = false;//return;
                    }
                } else { // 前过 后过 上越 或 下越 ok

                }
            }
            return;
    }
}

void triangleMoveXYZ(TriangleDemo* triangleMain,RectDemo* footSquare, char key,float oneStep){
    // 更改三维空间坐标
    // 取地址修改class

    //freshTriaCollisionClose(triangleMain, footSquare, key, oneStep);
    switch (key) {
        case 'q':
            if (goUp){
                triangleMain->_2S2M2L_XYZ.pA.y -= oneStep;
                triangleMain->_2S2M2L_XYZ.pB.y -= oneStep;
                triangleMain->_2S2M2L_XYZ.pC.y -= oneStep;
                }
            return;

        case 'e':
            if (goDown) {
                triangleMain->_2S2M2L_XYZ.pA.y += oneStep;
                triangleMain->_2S2M2L_XYZ.pB.y += oneStep;
                triangleMain->_2S2M2L_XYZ.pC.y += oneStep;
                }
            return;

        case 'w': // 前移
            if(goForward){
                triangleMain->_2S2M2L_XYZ.pA.z += oneStep;
                triangleMain->_2S2M2L_XYZ.pB.z += oneStep;
                triangleMain->_2S2M2L_XYZ.pC.z += oneStep;
                }
            return;

        case 's': // 后移
            if(goBack){
                triangleMain->_2S2M2L_XYZ.pA.z -= oneStep;
                triangleMain->_2S2M2L_XYZ.pB.z -= oneStep;
                triangleMain->_2S2M2L_XYZ.pC.z -= oneStep;
                }
            return;

        case 'a': // 左移
            if(goLeft){
                triangleMain->_2S2M2L_XYZ.pA.x -= oneStep;
                triangleMain->_2S2M2L_XYZ.pB.x -= oneStep;
                triangleMain->_2S2M2L_XYZ.pC.x -= oneStep;
                }
            return;
        case 'd': // 右移
            if(goRight) {
                triangleMain->_2S2M2L_XYZ.pA.x += oneStep;
                triangleMain->_2S2M2L_XYZ.pB.x += oneStep;
                triangleMain->_2S2M2L_XYZ.pC.x += oneStep;
                }
            //return;
    }


}
void triangleTurnXYZ(TriangleDemo* triangleMain,ScreenDemo* ScreenEye,RectDemo* footSquare, char key, float goAngle){

    switch (key) {
        case 'j': // 左转
            triangleMain->_2S2M2L_XYZ.pA = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pA, 'j', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pB, 'j', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pC, 'j', goAngle);

            break;
        case 'l': // 右转
            triangleMain->_2S2M2L_XYZ.pA = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pA, 'l', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pB, 'l', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pC, 'l', goAngle);

            break;
        case 'i': // 上翻
            triangleMain->_2S2M2L_XYZ.pA = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pA, 'i', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pB, 'i', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pC, 'i', goAngle);

            break;
        case 'k': // 下翻
            triangleMain->_2S2M2L_XYZ.pA = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pA, 'k', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pB, 'k', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pC, 'k', goAngle);

            break;
        case 'u': // 左旋
            triangleMain->_2S2M2L_XYZ.pA = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pA, 'u', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pB, 'u', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pC, 'u', goAngle);

            break;
        case 'o': // 右旋
            triangleMain->_2S2M2L_XYZ.pA = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pA, 'o', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pB, 'o', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = pointTurning(ScreenEye, footSquare, triangleMain->_2S2M2L_XYZ.pC, 'o', goAngle);

            break;
    }

}
void triangleCenterTurnXYZ(TriangleDemo* triangleMain, glm::vec3* centerPoint, char key, float goAngle){
    switch (key) {
        case 'j': // 左转
            triangleMain->_2S2M2L_XYZ.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pA, 'j', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pB, 'j', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pC, 'j', goAngle);

            break;
        case 'l': // 右转
            triangleMain->_2S2M2L_XYZ.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pA, 'l', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pB, 'l', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pC, 'l', goAngle);

            break;
        case 'i': // 上翻
            triangleMain->_2S2M2L_XYZ.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pA, 'i', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pB, 'i', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pC, 'i', goAngle);

            break;
        case 'k': // 下翻
            triangleMain->_2S2M2L_XYZ.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pA, 'k', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pB, 'k', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pC, 'k', goAngle);

            break;
        case 'u': // 左旋
            triangleMain->_2S2M2L_XYZ.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pA, 'u', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pB, 'u', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pC, 'u', goAngle);

            break;
        case 'o': // 右旋
            triangleMain->_2S2M2L_XYZ.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pA, 'o', goAngle);
            triangleMain->_2S2M2L_XYZ.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pB, 'o', goAngle);
            triangleMain->_2S2M2L_XYZ.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ.pC, 'o', goAngle);

            break;
    }
}
void triangleTurn_Unchange_XYZ(TriangleDemo* triangleMain, glm::vec3* centerPoint, char key, float goAngle){
    switch (key) {
        case 'j': // 左转
            triangleMain->_2S2M2L_XYZ_unchange.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pA, 'j', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pB, 'j', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pC, 'j', goAngle);

            break;
        case 'l': // 右转
            triangleMain->_2S2M2L_XYZ_unchange.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pA, 'l', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pB, 'l', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pC, 'l', goAngle);

            break;
        case 'i': // 上翻
            triangleMain->_2S2M2L_XYZ_unchange.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pA, 'i', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pB, 'i', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pC, 'i', goAngle);

            break;
        case 'k': // 下翻
            triangleMain->_2S2M2L_XYZ_unchange.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pA, 'k', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pB, 'k', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pC, 'k', goAngle);

            break;
        case 'u': // 左旋
            triangleMain->_2S2M2L_XYZ_unchange.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pA, 'u', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pB, 'u', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pC, 'u', goAngle);

            break;
        case 'o': // 右旋
            triangleMain->_2S2M2L_XYZ_unchange.pA = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pA, 'o', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pB = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pB, 'o', goAngle);
            triangleMain->_2S2M2L_XYZ_unchange.pC = turningByCenter(centerPoint, triangleMain->_2S2M2L_XYZ_unchange.pC, 'o', goAngle);

            break;
    }
//    triangleMain->_lrt_XYZ.rt = triangleMain->_lrt_XYZ_unchange.rt;
//    triangleMain->_lrt_XYZ.lb = triangleMain->_lrt_XYZ_unchange.lb;
//    triangleMain->_lrt_XYZ.lt = triangleMain->_lrt_XYZ_unchange.lt;
//    triangleMain->_lrt_XYZ.slashCenter = triangleMain->_lrt_XYZ_unchange.slashCenter;
//    triangleMain->_lrt_XYZ.centerTip = triangleMain->_lrt_XYZ_unchange.centerTip;
}

void fresh2S2M2L_XY(TriangleDemo* triangleMain, ScreenDemo* ScreenEye){
    // 刷新坐标 3D -> 2D
    glm::vec2 couple_faceS;
    glm::vec2 couple_faceM;
    glm::vec2 couple_faceL;


    couple_faceS = virtual_Pos_3Dto2D(ScreenEye, triangleMain->_2S2M2L_XYZ.pA.x, triangleMain->_2S2M2L_XYZ.pA.y,
                                      triangleMain->_2S2M2L_XYZ.pA.z); // 左下角
    couple_faceM= virtual_Pos_3Dto2D(ScreenEye, triangleMain->_2S2M2L_XYZ.pB.x, triangleMain->_2S2M2L_XYZ.pB.y,
                                     triangleMain->_2S2M2L_XYZ.pB.z); // 右上角
    couple_faceL = virtual_Pos_3Dto2D(ScreenEye, triangleMain->_2S2M2L_XYZ.pC.x, triangleMain->_2S2M2L_XYZ.pC.y,
                                      triangleMain->_2S2M2L_XYZ.pC.z); // 左上角


    triangleMain->set2S2M2L_XY_f(
            {couple_faceS.x, couple_faceS.y},
            {couple_faceM.x, couple_faceM.y},
            {couple_faceL.x, couple_faceL.y}
    );
//    printf("显┌xy:%d,%d\n",couple_lt.y,couple_lt.x);
//    printf("显┐xy:%d,%d\n",couple_rt.y,couple_rt.x);
//    printf("显└xy:%d,%d\n",couple_lb.y,couple_lb.x);
//    printf("显┘xy:%d,%d\n",couple_rb.y,couple_rb.x);
}
void fresh2S2M2L_XY_Go(TriangleDemo* triangleMain, ScreenDemo* ScreenEyeL){
    // 刷新坐标 3D -> 2D
    glm::vec2 couple_faceS;
    glm::vec2 couple_faceM;
    glm::vec2 couple_faceL;


    couple_faceS = spotEyeScreenGo(ScreenEyeL, triangleMain->_2S2M2L_XYZ.pA,triangleMain->virtual_2S2M2L_XYZ); // 左下角
    couple_faceM= spotEyeScreenGo(ScreenEyeL, triangleMain->_2S2M2L_XYZ.pB,triangleMain->virtual_2S2M2L_XYZ+1); // 右上角
    couple_faceL = spotEyeScreenGo(ScreenEyeL, triangleMain->_2S2M2L_XYZ.pC,triangleMain->virtual_2S2M2L_XYZ+2); // 左上角


    triangleMain->set2S2M2L_XY_f(
            {couple_faceS.x, couple_faceS.y},
            {couple_faceM.x, couple_faceM.y},
            {couple_faceL.x, couple_faceL.y}

    );
}


void fresh2S2M2L_XY_by_axis(TriangleDemo* triangleMain, RectDemo* footSquare, AxisDemo* AxisWorld, ScreenDemo* ScreenEye, char key){
    glm::vec2 couple_faceS;
    glm::vec2 couple_faceM;
    glm::vec2 couple_faceL;



//    { -40,0,0 },     //Xl         X
//    { 500,0,0 },     //Xr         X
//    { 0,-40,0 },     //Yt         Y
//    { 0,500,0},     //Yb         Y
//    { 0,0,-40 },     //DEEPc     DEEP
//    { 0,0,500 });   //DEEPf   DEEP
    glm::vec3 axis_0_0_0 = {AxisWorld->axisXYZ.Xl.x, AxisWorld->axisXYZ.Xl.y, AxisWorld->axisXYZ.Xl.z };
    //printf("axis_0_0_0:%f,%f,%f\n",axis_0_0_0.y,axis_0_0_0.x,axis_0_0_0.z);
    // FLT_MAX 浮点数最大
    // ➗ cos() 转角

    glm::vec3 faceS_XYZ = {triangleMain->_2S2M2L_XYZ.pA.x, triangleMain->_2S2M2L_XYZ.pA.y, triangleMain->_2S2M2L_XYZ.pA.z};
    glm::vec3 faceM_XYZ = {triangleMain->_2S2M2L_XYZ.pB.x, triangleMain->_2S2M2L_XYZ.pB.y, triangleMain->_2S2M2L_XYZ.pB.z};
    glm::vec3 faceL_XYZ = {triangleMain->_2S2M2L_XYZ.pC.x, triangleMain->_2S2M2L_XYZ.pC.y, triangleMain->_2S2M2L_XYZ.pC.z};


    if(key == 'j' || key == 'i' || key == 'o' || key == 'l' || key == 'k' || key == 'u'){
        faceS_XYZ = turning_by_axis(axis_0_0_0,faceS_XYZ, key, goAngle);
        faceM_XYZ = turning_by_axis(axis_0_0_0,faceM_XYZ, key, goAngle);
        faceL_XYZ = turning_by_axis(axis_0_0_0,faceL_XYZ,key, goAngle);


        triangleMain->set2S2M2L_XYZ(faceS_XYZ, faceM_XYZ, faceL_XYZ); // 刷新单面坐标 3D
    }else{
        triangleMoveXYZ(triangleMain,footSquare, key, goStep);
    }

    //     左转 上翻 右旋 + 右转 下翻 左旋 -
    couple_faceL = virtual_Pos_3Dto2D(ScreenEye,
                                      faceS_XYZ.x, faceS_XYZ.y, faceS_XYZ.z); // 左下角

    couple_faceM = virtual_Pos_3Dto2D(ScreenEye,
                                      faceM_XYZ.x, faceM_XYZ.y, faceM_XYZ.z); // 右上角

    couple_faceS = virtual_Pos_3Dto2D(ScreenEye,
                                      faceL_XYZ.x, faceL_XYZ.y, faceL_XYZ.z); // 左下角



    triangleMain->set2S2M2L_XY_f(
            couple_faceS,
            couple_faceM,

            couple_faceL
    );



}
void fresh2S2M2L_XY_by_axis_Go(TriangleDemo* triangleMain, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL){
    glm::vec2 couple_faceS;
    glm::vec2 couple_faceM;
    glm::vec2 couple_faceL;


    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z };
    //printf("axis_0_0_0:%f,%f,%f\n",axis_0_0_0.y,axis_0_0_0.x,axis_0_0_0.z);
    // FLT_MAX 浮点数最大
    // ➗ cos() 转角

    // 3D xyz三步走 每步xyz都要动 都要 动
    glm::vec3 faceS_XYZ;
    faceS_XYZ = AxisTilt->goX(axis_0_0_0, triangleMain->_2S2M2L_XYZ_unchange.pA.x);
    faceS_XYZ = AxisTilt->goY(faceS_XYZ, triangleMain->_2S2M2L_XYZ_unchange.pA.y);
    faceS_XYZ = AxisTilt->goDEEP(faceS_XYZ, triangleMain->_2S2M2L_XYZ_unchange.pA.z);

    glm::vec3 faceM_XYZ;
    faceM_XYZ = AxisTilt->goX(axis_0_0_0, triangleMain->_2S2M2L_XYZ_unchange.pB.x);
    faceM_XYZ = AxisTilt->goY(faceM_XYZ, triangleMain->_2S2M2L_XYZ_unchange.pB.y);
    faceM_XYZ = AxisTilt->goDEEP(faceM_XYZ, triangleMain->_2S2M2L_XYZ_unchange.pB.z);

    glm::vec3 faceL_XYZ;
    faceL_XYZ = AxisTilt->goX(axis_0_0_0, triangleMain->_2S2M2L_XYZ_unchange.pC.x);
    faceL_XYZ = AxisTilt->goY(faceL_XYZ, triangleMain->_2S2M2L_XYZ_unchange.pC.y);
    faceL_XYZ = AxisTilt->goDEEP(faceL_XYZ, triangleMain->_2S2M2L_XYZ_unchange.pC.z);


    triangleMain->set2S2M2L_XYZ(faceS_XYZ, faceM_XYZ, faceL_XYZ); // 刷新单面坐标 3D
    //     左转 上翻 右旋 + 右转 下翻 左旋 -
    couple_faceS = spotEyeScreenGo(ScreenEyeL, faceS_XYZ,triangleMain->virtual_2S2M2L_XYZ); // 左下角

    couple_faceM = spotEyeScreenGo(ScreenEyeL, faceM_XYZ,triangleMain->virtual_2S2M2L_XYZ+1); // 右上角

    couple_faceL = spotEyeScreenGo(ScreenEyeL, faceL_XYZ,triangleMain->virtual_2S2M2L_XYZ+2); // 左下角


    triangleMain->set2S2M2L_XY_f(
            couple_faceS,
            couple_faceM,

            couple_faceL
    );
}
#endif //RECTANGLEDISPLAY_TRIANGLE_FUNC_3D2D_H
