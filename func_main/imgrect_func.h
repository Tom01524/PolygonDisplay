//
// Created by iceoc0 on 2025/6/15.
//

#ifndef POLYGONDISPLAY_IMGRECT_FUNC_H
#define POLYGONDISPLAY_IMGRECT_FUNC_H

#include"../func_main/bezier33Edge4_func.h"
#include"../polygonClass/ImgRect.h"
void freshImg_2S2M2L_XY(ImgRect* imgRectObj, ScreenDemo* ScreenEyeL);
void freshImg_2S2M2L_XY_by_axis(ImgRect* imgRectObj, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL);

void freshImg_2S2M2L_XY(ImgRect* imgRectObj, ScreenDemo* ScreenEyeL){
    // 刷新坐标 3D -> 2D
    glm::vec2 couple_faceS;
    glm::vec2 couple_faceM;
    glm::vec2 couple_faceL;


    glm::vec2 couple_rb;
    // rt lb lt
    couple_faceS = spotEyeScreenGo(ScreenEyeL, imgRectObj->_lrt_XYZ.rt, &imgRectObj->virtual_lrt_XYZ.rt); // 左下角
    couple_faceM= spotEyeScreenGo(ScreenEyeL, imgRectObj->_lrt_XYZ.lb, &imgRectObj->virtual_lrt_XYZ.lb); // 右上角
    couple_faceL = spotEyeScreenGo(ScreenEyeL, imgRectObj->_lrt_XYZ.lt, &imgRectObj->virtual_lrt_XYZ.lt); // 左上角

    couple_rb = spotEyeScreenGo(ScreenEyeL, imgRectObj->rbXYZ,
                                &imgRectObj->virtual_rbXYZ);
    imgRectObj->set2S2M2L_XY(
            couple_faceS,
            couple_faceM,
            couple_faceL,

            couple_rb
    );
}
void freshImg_2S2M2L_XY_by_axis(ImgRect* imgRectObj, AxisDemo* AxisTilt, ScreenDemo* ScreenEyeL){
    glm::vec2 couple_faceS;
    glm::vec2 couple_faceM;
    glm::vec2 couple_faceL;

    glm::vec2 couple_rb;

    glm::vec3 axis_0_0_0 = {AxisTilt->axisXYZ.Xl.x, AxisTilt->axisXYZ.Xl.y, AxisTilt->axisXYZ.Xl.z };
    //printf("axis_0_0_0:%f,%f,%f\n",axis_0_0_0.y,axis_0_0_0.x,axis_0_0_0.z);
    // FLT_MAX 浮点数最大
    // ➗ cos() 转角

    // 3D xyz三步走 每步xyz都要动 都要 动
    glm::vec3 faceS_XYZ;
    faceS_XYZ = AxisTilt->goX(axis_0_0_0, imgRectObj->_lrt_XYZ_unchange.rt.x);
    faceS_XYZ = AxisTilt->goY(faceS_XYZ, imgRectObj->_lrt_XYZ_unchange.rt.y);
    faceS_XYZ = AxisTilt->goDEEP(faceS_XYZ, imgRectObj->_lrt_XYZ_unchange.rt.z);

    glm::vec3 faceM_XYZ;
    faceM_XYZ = AxisTilt->goX(axis_0_0_0, imgRectObj->_lrt_XYZ_unchange.lb.x);
    faceM_XYZ = AxisTilt->goY(faceM_XYZ, imgRectObj->_lrt_XYZ_unchange.lb.y);
    faceM_XYZ = AxisTilt->goDEEP(faceM_XYZ, imgRectObj->_lrt_XYZ_unchange.lb.z);

    glm::vec3 faceL_XYZ;
    faceL_XYZ = AxisTilt->goX(axis_0_0_0, imgRectObj->_lrt_XYZ_unchange.lt.x);
    faceL_XYZ = AxisTilt->goY(faceL_XYZ, imgRectObj->_lrt_XYZ_unchange.lt.y);
    faceL_XYZ = AxisTilt->goDEEP(faceL_XYZ, imgRectObj->_lrt_XYZ_unchange.lt.z);


    imgRectObj->set2S2M2L_XYZ(faceS_XYZ, faceM_XYZ, faceL_XYZ); // 刷新单面坐标 3D
    //     左转 上翻 右旋 + 右转 下翻 左旋 -
    couple_faceS = spotEyeScreenGo(ScreenEyeL,
                                   faceS_XYZ,&imgRectObj->virtual_lrt_XYZ.rt); // 左下角
    // rt lb lt
    couple_faceM = spotEyeScreenGo(ScreenEyeL,
                                   faceM_XYZ, &imgRectObj->virtual_lrt_XYZ.lb); // 右上角

    couple_faceL = spotEyeScreenGo(ScreenEyeL,
                                   faceL_XYZ, &imgRectObj->virtual_lrt_XYZ.lt); // 左下角

    // imgRectObj->_lrt_XYZ.circumCenter与centerTip 已被顶点刷新


    couple_rb = spotEyeScreenGo(ScreenEyeL,
                                imgRectObj->rbXYZ,
                                &imgRectObj->virtual_rbXYZ);
    imgRectObj->set2S2M2L_XY(
            couple_faceS,
            couple_faceM,

            couple_faceL,

            couple_rb
    );
}
#endif //POLYGONDISPLAY_IMGRECT_FUNC_H
