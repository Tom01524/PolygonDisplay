//
// Created by iceoc0 on 2025/6/15.
//

#ifndef POLYGONDISPLAY_IMGRECT_H
#define POLYGONDISPLAY_IMGRECT_H


#include "./source/ScreenDemo.h"
class TriangleXYZ2 {
public:
    TriangleXYZ2() = default;
    TriangleXYZ2(glm::vec3 _faceLeft, glm::vec3 _faceTop, glm::vec3 _faceSlash, glm::vec3 _circumCenter, glm::vec3 _centerTip) {
        rt = _faceLeft;
        lb = _faceTop;
        lt = _faceSlash;

        //ensureSML(_faceS,_faceM,_faceL); // 确保三边长的顺序
    }

    glm::vec3 rt;
    glm::vec3 lb;
    glm::vec3 lt;


}; // 三维位置矩形

#ifndef _pixelDeep8Area
#define _pixelDeep8Area

struct pixelDeep8Area{
    int x; // long x long y
    float eyeDeep; // float deep
    float r01,g01,b01;
};

#endif

#ifndef _rowPixelDeep8Area
#define _rowPixelDeep8Area
struct rowPixelDeep8Area {
    vector<pixelDeep8Area> pixelDeeps; // 行的像素深度
    int y; // 行
};
#endif
class ImgRect : public PolygonBase {
public:
    ImgRect(string _src, glm::vec3 _lt_xyz, glm::vec3 _rt_xyz, glm::vec3 _rb_xyz, glm::vec3 _lb_xyz,bool backFront);


    Matrix2D<glm::vec3> pixelsColor;
    float width, height;

    float imgW_f,imgH_f; // 图片宽高

    TriangleXYZ2 _lrt_XYZ; // 三维位置▲
    TriangleXYZ2 _lrt_XYZ_unchange; // 三维位置▲
    glm::vec3 rbXYZ,rbXYZ_unchange;

    glm::vec2 _lrt_XY[3]; // rt lb lt mid tip reverseTip
    glm::vec2 rbXY;

    TriangleXYZ2 virtual_lrt_XYZ; // 屏幕系点的位置
    glm::vec3 virtual_rbXYZ;

    glm::vec3 startEye;

    bool justMoved; // 前帧 刚移动

    void setColor(int fontColor1); /*用setcolor时默认*/
    void setBackColor(int backColor1); // 设置背面颜色
    float frontColor_rgb01[3];
    float backColor_rgb01[3];
    void validatePlanarity();// 增加平面性检测（构造函数中）
    void set2S2M2L_XY(glm::vec2 _faceLeft_XY, glm::vec2 _faceTop_XY, glm::vec2 _faceSlash_XY,
                      glm::vec2 _rb_XY);

    void set2S2M2L_XYZ(glm::vec3 _rt_XYZ, glm::vec3 _lb_XYZ, glm::vec3 _lt_XYZ);
    void Draw_Tick(ScreenDemo* ScreenEye);

    bool cTipEyeCloser();
    bool _backFont; // 法线向量取反

    vector<lineBoundary> lineScanFillColor; // 扫描线填充颜色
    vector<rowPixelDeep8Area> pixel2EyeDeepArea; // XY2D 屏幕坐标  screenDeep 深度  area 0 原色 1 暗色
    vector<lineBoundary> lineScanFillColorRB; // 扫描线填充
    vector<rowPixelDeep8Area> pixel2EyeDeepAreaRB;

    void _solidTriangle2D(ScreenDemo* ScreenEye,bool onFront); //
    void _solidTriangle2D_rb(ScreenDemo* ScreenEye,bool onFront); // 绘制三角形

    glm::vec4 virtualBack_a_b_c_d; // 共面点函数
    void virtual_ax1_by1_cz1_d1();
    goLine32 eye2ScreenPixel_dxyz(float x, float y);
    glm::vec3 get_FlatPointVirtual_ByXY(float x, float y);

    float VerticalTopFlat_d;
    void freshVerticalTopFlat_d();
    glm::vec2 getUV01_ByVirtualFlatPoint(glm::vec3 posNow);
    glm::vec3 getColorByUV01(glm::vec2 uv01);

    goLine32 virtual_goX;
    goLine32 virtual_goY;
    [[maybe_unused]]goLine32 virtual_goZ;
    void freshVirtual2X();
    void freshVirtual2Y();
    [[maybe_unused]]void freshVirtual2Z();
    Quaternion frameRotateInfo_q;
    [[maybe_unused]]void freshFrameRotateInfo(); // 斜转 换坐标系
    [[maybe_unused]]glm::vec3 screenXYZ2SelfXYZ(glm::vec3 _screenAxisPos); // 屏幕坐标转自身坐标2

    float halfRectW, halfRectH; // 宽高的一半
    [[maybe_unused]]glm::vec3 getColorBySelfAxisPos(glm::vec3 _selfAxisPos);

};

#endif //POLYGONDISPLAY_IMGRECT_H
