//
// Created by iceoc0 on 2025/6/15.
//
#include "ImgRect.h"

struct modeImgRect{ // 同类型组 的 结构体指针 移花接木
    char now;char a;char b;char d;
};
extern void* mode_ptr;
modeImgRect mode_ = *static_cast<modeImgRect*>(mode_ptr);


extern void* settled_ptr; // 全局设置的结构体指针
struct _settledImgRect{
    int _width;
    int _height;
    int _deep;

};
_settledImgRect* settled_ = (_settledImgRect*)settled_ptr;
const int screenWidth8 = settled_-> _width;
const int screenHeight8 = settled_-> _height;
const int screenDeep8 = settled_-> _deep;


ImgRect::ImgRect(string filename, glm::vec3 _lt_xyz, glm::vec3 _rt_xyz, glm::vec3 _rb_xyz, glm::vec3 _lb_xyz,bool backFront):
PolygonBase(8)
{
    PolygonBase::loadImgRGB01(filename,pixelsColor);
    println("ImgRect::ImgRect() imgW={} imgH={} vec size:{}",
        pixelsColor.outterMax, pixelsColor.innerMax, pixelsColor.data.size());
    imgH_f = static_cast<float>(pixelsColor.outterMax);
    imgW_f = static_cast<float>(pixelsColor.innerMax);

//    float edgeT_len = glm::distance(_lt_xyz, _rt_xyz);
//    float edgeL_len = glm::distance(_lt_xyz, _lb_xyz);

    set2S2M2L_XYZ(_rt_xyz, _lb_xyz, _lt_xyz); // 对高 对宽 对斜

    validatePlanarity(); // 确定共面

    _backFont = backFront;

    // 相对于 世界坐标轴 同距
    _lrt_XYZ_unchange.rt = _lrt_XYZ.rt;
    _lrt_XYZ_unchange.lb = _lrt_XYZ.lb;
    _lrt_XYZ_unchange.lt = _lrt_XYZ.lt;

    rbXYZ_unchange = rbXYZ;

    startEye = {(float)screenWidth8/2.f,(float)screenHeight8/2.f,(float)-screenDeep8};
    width = glm::distance(_lrt_XYZ.lt, _lrt_XYZ.rt);
    height = glm::distance(_lrt_XYZ.lt, _lrt_XYZ.lb);

    halfRectW = width / 2.0f;
    halfRectH = height / 2.0f;

    justMoved = false;
}

void ImgRect::setColor(int NormalColor1) {
    BGR3f colorNow;
    colorNow.setBGR(NormalColor1,1);
    frontColor_rgb01[0] = colorNow.r1;
    frontColor_rgb01[1] = colorNow.g1;
    frontColor_rgb01[2] = colorNow.b1;
//    frontSubColor_rgb01[0] = frontColor_rgb01[0] * 0.75f;
//    frontSubColor_rgb01[1] = frontColor_rgb01[1] * 0.75f;
//    frontSubColor_rgb01[2] = frontColor_rgb01[2] * 0.75f;
}
void ImgRect::setBackColor(int backColor1){
    BGR3f colorNow;
    colorNow.setBGR(backColor1,1);
    backColor_rgb01[0] = colorNow.r1;
    backColor_rgb01[1] = colorNow.g1;
    backColor_rgb01[2] = colorNow.b1;
}
void ImgRect::validatePlanarity() {
    glm::vec3 backLB = _lrt_XYZ.lb - _lrt_XYZ.lt; // 左上归原点 lb走
    glm::vec3 backRT = _lrt_XYZ.rt - _lrt_XYZ.lt; // 左上归原点 rt走
    glm::vec3 verticalVec = glm::cross(backLB, backRT); // 此面法线vec

    glm::vec3 backRB = rbXYZ - _lrt_XYZ.lt; // 左上归原点 rb走
    //ax+by+cz+d=0;  共面方程
    // a = verticalVec.x b = verticalVec.y c = verticalVec.z;
    // 原点共面 a*x0+b*y0+c*z0+d=0 → d=0
    // 代入 rb → verticalVec.x*rb.x + verticalVec.y*rb.y + verticalVec.z*rb.z + 0 = 0 → dot()

    float deviation = glm::abs(glm::dot(verticalVec, backRB));

    if(deviation > 1e-5f) {
        std::cout << "Warning: Non-planar quadrilateral detected! Deviation: "
                  << deviation << std::endl;
    }
}
void ImgRect::set2S2M2L_XY(glm::vec2 _faceLeft_XY, glm::vec2 _faceTop_XY, glm::vec2 _faceSlash_XY,
                           glm::vec2 _rb_XY) {
    _lrt_XY[0].x = _faceLeft_XY.x; // rt
    _lrt_XY[0].y = _faceLeft_XY.y;
    _lrt_XY[1].x = _faceTop_XY.x; // lb
    _lrt_XY[1].y = _faceTop_XY.y;
    _lrt_XY[2].x = _faceSlash_XY.x; // lt
    _lrt_XY[2].y = _faceSlash_XY.y;

    rbXY = _rb_XY;

    justMoved = 1; // 看又 移动了 ?

}
void ImgRect::set2S2M2L_XYZ(glm::vec3 _rt_XYZ, glm::vec3 _lb_XYZ, glm::vec3 _lt_XYZ){

    _lrt_XYZ.rt = _rt_XYZ;

    _lrt_XYZ.lb = _lb_XYZ;

    _lrt_XYZ.lt = _lt_XYZ;

//    rbXYZ = _lb_XYZ + (_rt_XYZ - _lt_XYZ);

    // 任意直角三角形 外心 斜边一半
    glm::vec3 slashCenter = (_rt_XYZ + _lb_XYZ) / 2.0f;
    rbXYZ = slashCenter * 2.f - _lt_XYZ; // 右下角顶点
//    cout << "---faces: " << _lrt_XYZ.rt.x << " " << _lrt_XYZ.rt.y << " " << _lrt_XYZ.rt.z << endl;
//    cout << "---facem: " << _lrt_XYZ.lb.x << " " << _lrt_XYZ.lb.y << " " << _lrt_XYZ.lb.z << endl;
//    cout << "---facel: " << _lrt_XYZ.lt.x << " " << _lrt_XYZ.lt.y << " " << _lrt_XYZ.lt.z << endl;

    // 计算两个边相量
    // glm::vec3 LT2RT = (_lt_XYZ - _rt_XYZ);
    //
    // glm::vec3 LT2LB = (_lt_XYZ - _lb_XYZ);
    // 计算法向量

//    float normal[3] = {0}; // 法向量 立方体对角线单位一
//    normal[0] = LT2RT.y * LT2LB.z - LT2RT.z * LT2LB.y;
//    normal[1] = LT2RT.z * LT2LB.x - LT2RT.x * LT2LB.z;
//    normal[2] = LT2RT.x * LT2LB.y - LT2RT.y * LT2LB.x;

    // glm::vec3 normal(glm::cross(LT2LB,LT2RT ));
    // normal = glm::normalize(normal); // 法向量 立方体对角线单位一
    // 归一化法向量


    // _lrt_XYZ.centerTip = _lrt_XYZ.slashCenter + normal * 20.0f; // 中心点的尖端 法向量 立方体对角线单位一
    //
    // _lrt_XYZ.centerBack = _lrt_XYZ.slashCenter - normal * 20.0f; // 中心点的背端


}
void ImgRect::Draw_Tick(ScreenDemo* ScreenEye){

    //glm::vec3 nowEyeCenter = ScreenEye->tblrXYZ.centerTip; // 眼睛中心点


    //horizontalDeepCalc(ScreenEye);
    bool all2Dleft = _lrt_XY[0].x < 0.f && _lrt_XY[1].x < 0.f
            && _lrt_XY[2].x < 0.f;
    if(all2Dleft)return; // 全部在左侧 则不渲染

    bool all2Dright = _lrt_XY[0].x > (float)screenWidth8 && _lrt_XY[1].x > (float)screenWidth8
            && _lrt_XY[2].x > (float)screenWidth8;
    if(all2Dright)return; // 全部在右侧 则不渲染

    bool all2Dtop = _lrt_XY[0].y < 0.f && _lrt_XY[1].y < 0.f
            && _lrt_XY[2].y < 0.f;
    if(all2Dtop)return; // 全部在上侧 则不渲染

    bool all2Dbottom = _lrt_XY[0].y > (float)screenHeight8 && _lrt_XY[1].y > (float)screenHeight8
            && _lrt_XY[2].y > (float)screenHeight8;
    if(all2Dbottom)return; // 全部在下侧 则不渲染

//    bool corner2DoutOfScreen = all2Dleft || all2Dright || all2Dtop || all2Dbottom;
    bool cornerClose2Eye = virtual_lrt_XYZ.rt.z < (float)-screenDeep8 || virtual_lrt_XYZ.lb.z < (float)-screenDeep8 ||
                           virtual_lrt_XYZ.lt.z < (float)-screenDeep8;
    if(cornerClose2Eye)return; // 眼心距<100 则不渲染


//    if(cornerClose2Eye || corner2DoutOfScreen){ // 眼心距>100 才渲染
//        return;
//    }

    virtual_ax1_by1_cz1_d1(); // 共面方程

    freshVirtual2X();freshVirtual2Y();
    freshVerticalTopFlat_d(); // 屋檐垂面 的d值 每帧预计算

    //freshVirtual2Z(); // 屏幕系 矩形面 走X 走Y
    //freshFrameRotateInfo(); // 刷新 旋转信息

    if (cTipEyeCloser()) { // 正面

        // 面远 线近
        _solidTriangle2D(ScreenEye,true);
        _solidTriangle2D_rb(ScreenEye,true);
    } else { // 背面

        _solidTriangle2D(ScreenEye,false);
        _solidTriangle2D_rb(ScreenEye,false);
    }

    justMoved = 0; // 恢复 0
}
bool ImgRect::cTipEyeCloser(){
    // 比较 中心点与中突点 到眼睛中心的距离

    float a = virtualBack_a_b_c_d[0];
    float b = virtualBack_a_b_c_d[1];
    float c = virtualBack_a_b_c_d[2];
    float d = virtualBack_a_b_c_d[3];

    return a*startEye.x + b*startEye.y + c*startEye.z + d > 0; // 共面方程 符号距离 判断正反
}

void ImgRect::_solidTriangle2D(ScreenDemo* ScreenEye,bool onFront){


//    horizontalDeepCalc(); // 边信息与准备 边信息算得 填色
    // rt lb lt mid tip reverseTip
    if (justMoved) {
       PolygonBase::fresh2D_scanRows_3(_lrt_XY[2],
                                    _lrt_XY[0],
                                    _lrt_XY[1], &lineScanFillColor,type_);
       pixel2EyeDeepArea.clear();


    //   int isFIrst = 0;

       // 分区域网格
       for(auto& _linePosInfo : lineScanFillColor){
           if(_linePosInfo.lx == _linePosInfo.rx)continue; // 无效线段 跳过

           rowPixelDeep8Area rowDeepInfo;
           rowDeepInfo.y = _linePosInfo.y; // 本行 y
           float deepNow;
           glm::vec3 virtualPosNow, selfAxisPos, colorNow;
           for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){


               virtualPosNow = get_FlatPointVirtual_ByXY((float)nowX, (float)_linePosInfo.y);
    //           cout << "virtualPosNow: " << virtualPosNow.x << " " << virtualPosNow.y << " " << virtualPosNow.z << endl;

               deepNow = virtualPosNow.z; // 取虚拟点的深度

               glm::vec2 uv01 = getUV01_ByVirtualFlatPoint(virtualPosNow);
               colorNow = getColorByUV01(uv01);
    //           cout << "deepNow: " << deepNow << endl;
               //selfAxisPos = screenXYZ2SelfXYZ(virtualPosNow); -- 转自己系 找uv 找index 找颜色
               //colorNow = getColorBySelfAxisPos(selfAxisPos);
    //           glm::vec3 colorNow = getPixelColor(_αβγ[1],_αβγ[0]);

               rowDeepInfo.pixelDeeps.push_back({nowX, deepNow,colorNow[0],colorNow[1],colorNow[2]}); // 本行 x deep
           }
           pixel2EyeDeepArea.push_back(rowDeepInfo);

       }
        // println("image rectanle 刷新信息");
    }


    size_t subSizeNow;float colorNow[3];
    for(auto& _lineDeepInfo : pixel2EyeDeepArea){
        subSizeNow=_lineDeepInfo.pixelDeeps.size();
        for(int i=0; i < subSizeNow/*-1*/; i++){
            int nowX = _lineDeepInfo.pixelDeeps[i].x;
            float nowDeep = _lineDeepInfo.pixelDeeps[i].eyeDeep;
//            char area = _lineDeepInfo.pixelDeeps[i].area; // 网格分区
            colorNow[0] = _lineDeepInfo.pixelDeeps[i].r01;
            colorNow[1] = _lineDeepInfo.pixelDeeps[i].g01;
            colorNow[2] = _lineDeepInfo.pixelDeeps[i].b01;

            if(onFront){

                    ScreenEye->putPixel(nowX, _lineDeepInfo.y, colorNow,
                                        nowDeep, (PolygonBase*)this);

            }else{

                ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), backColor_rgb01, nowDeep, (PolygonBase*)this);

            }
        }
    }


}
void ImgRect::_solidTriangle2D_rb(ScreenDemo* ScreenEye,bool onFront){
//    horizontalDeepCalc_rb(); // 边信息与准备 边信息算得 填色
    // rt lb lt mid tip reverseTip
    PolygonBase::fresh2D_scanRows_3(_lrt_XY[0],
                                    _lrt_XY[1],
                                    rbXY, &lineScanFillColorRB,type_);
    pixel2EyeDeepAreaRB.clear();

//    fprintf(stdout,"^^^^^^");


    // 分区域网格
    for(auto& _linePosInfo : lineScanFillColorRB){
        if(_linePosInfo.lx == _linePosInfo.rx)continue; // 无效线段 跳过

        rowPixelDeep8Area rowDeepInfo;
        float deepNow;
        glm::vec3 virtualPosNow, selfAxisPos, colorNow;
        rowDeepInfo.y = _linePosInfo.y; // 本行 y
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){

            //float deepNow = getEyeDeepbyXY(nowX, _linePosInfo.y);
//            float* _αβγ = get_αβγ_rb(nowX, _linePosInfo.y);
//            float deepNow = getScreenDeepbyXY_αβγ_rb(_αβγ);
//            char areaNow = getFlatAreaByXY(_αβγ);
//            glm::vec3 colorNow = getPixelColor_rb(_αβγ[1],_αβγ[0]);
//            cout << "--rb areaNow: " << areaNow << endl;


            virtualPosNow = get_FlatPointVirtual_ByXY((float)nowX, (float)_linePosInfo.y); // 屏幕系表面点
//            cout << "virtualPosNow: " << virtualPosNow.x << " " << virtualPosNow.y << " " << virtualPosNow.z << endl;
            deepNow = virtualPosNow.z; // 取屏幕系 点的深度
//            cout << "deepNow: " << deepNow << endl;
            glm::vec2 uv01 = getUV01_ByVirtualFlatPoint(virtualPosNow);
            colorNow = getColorByUV01(uv01);
            //selfAxisPos = screenXYZ2SelfXYZ(virtualPosNow); -- 转自己系 找uv 找index 找颜色
            //colorNow = getColorBySelfAxisPos(selfAxisPos);

            rowDeepInfo.pixelDeeps.push_back({nowX, deepNow,colorNow[0],colorNow[1],colorNow[2]}); // 本行 x deep
        }
        pixel2EyeDeepAreaRB.push_back(rowDeepInfo);

    }
//    cout << "pixel2EyeDeepAreaRB size: " << pixel2EyeDeepAreaRB.size() << endl;



    size_t subSizeNow;
//    float rbColor[3] = {1.f-frontColor_rgb01[0],1.f-frontColor_rgb01[1],1.f-frontColor_rgb01[2]};
//    float rbSubColor[3] = {1.f-frontSubColor_rgb01[0],1.f-frontSubColor_rgb01[1],1.f-frontSubColor_rgb01[2]};
    float colorNow[3];
    for(auto& _lineDeepInfo : pixel2EyeDeepAreaRB){
        subSizeNow=_lineDeepInfo.pixelDeeps.size();
        for(int i=0; i < subSizeNow/*-1*/; i++){
            int nowX = _lineDeepInfo.pixelDeeps[i].x;
            float nowDeep = _lineDeepInfo.pixelDeeps[i].eyeDeep;
//            char area = _lineDeepInfo.pixelDeeps[i].area; // 网格分区
            colorNow[0] = _lineDeepInfo.pixelDeeps[i].r01;
            colorNow[1] = _lineDeepInfo.pixelDeeps[i].g01;
            colorNow[2] = _lineDeepInfo.pixelDeeps[i].b01;

            if(onFront){
                ScreenEye->putPixel(nowX, _lineDeepInfo.y, colorNow,
                                    nowDeep, (PolygonBase*)this);

            }else{

                ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), backColor_rgb01, nowDeep, (PolygonBase*)this);

            }
        }
    }
}
void ImgRect::virtual_ax1_by1_cz1_d1(){
    // 计算两个边相量
    glm::vec3 lt2rt = virtual_lrt_XYZ.lt - virtual_lrt_XYZ.rt;
    // rt lb lt mid tip reverseTip ------------------------------------
    glm::vec3 lt2lb = virtual_lrt_XYZ.lt - virtual_lrt_XYZ.lb;
    // 计算法向量
    glm::vec3 normal = glm::normalize(glm::cross(lt2lb,lt2rt));
//    normal[0] = lt2rt.y * lt2lb.z - lt2rt.z * lt2lb.y;
//    normal[1] = lt2rt.z * lt2lb.x - lt2rt.x * lt2lb.z;
//    normal[2] = lt2rt.x * lt2lb.y - lt2rt.y * lt2lb.x;
    virtualBack_a_b_c_d[0] = normal[0];
    virtualBack_a_b_c_d[1] = normal[1];
    virtualBack_a_b_c_d[2] = normal[2];
    // 归一化法向量
    // float magnitude = glm::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    //
    // normal[0] /= magnitude;
    // normal[1] /= magnitude;
    // normal[2] /= magnitude; // 法向量 立方体对角线单位一

//    if(_backFont){
//        normal[0] = -normal[0];
//        normal[1] = -normal[1];
//        normal[2] = -normal[2]; // 法向量 取反 ?
//    }

    // ax + by + cz + d = 0
    // d = -ax1*x1 - by1*y1 - cz1*z1
    virtualBack_a_b_c_d[3] = -normal[0] * virtual_lrt_XYZ.rt.x - normal[1] * virtual_lrt_XYZ.rt.y - normal[2] * virtual_lrt_XYZ.rt.z;

    // if(mode_.now == 4){
    //     if(!_backFont){
    //         normal = -normal; // 法向量 取反 ?
    //     }
    // }else if(mode_.now == 2){ // 和 自由机位 反着 ...
        if(_backFont){
            virtualBack_a_b_c_d = -virtualBack_a_b_c_d; // 法向量 取反 ?
        }
    // }

    // 得到了 ax + by + cz + d = 0 方程 可用 系数

}
goLine32 ImgRect::eye2ScreenPixel_dxyz(float x, float y){
    glm::vec3 pixelXYZ = {x, y, 0.0f};

    //float pixel2eye_far = glm::distance(startEYE, pixelXYZ); // 计算像素点到屏幕中心的距离

    goLine32 rayGo1;
    rayGo1._ = glm::normalize(pixelXYZ - startEye); // 像素点到屏幕中心的向量

    return rayGo1; // 计算像素点到屏幕中心的向量
}
glm::vec3 ImgRect::get_FlatPointVirtual_ByXY(float x, float y){
    // 初始化一次 (600,400,-1000)
    glm::vec3 startEYE = startEye;
    goLine32 eyeGoPixel = eye2ScreenPixel_dxyz(x, y); // 计算 屏幕中心到像素点 的向量
    // eye.x + dx * step = x
    // eye.y + dy * step = y
    // eye.z + dz * step = z

    // 已知 abcd ax+by+cz+d=0
    // a*(eye.x + dx * step) + rtSet*(eye.y + dy * step) + c*(eye.z + dz * step) + d = 0
    float a = virtualBack_a_b_c_d[0];
    float b = virtualBack_a_b_c_d[1];
    float c = virtualBack_a_b_c_d[2];
    float d = virtualBack_a_b_c_d[3];
//    if(std::isnan(a)){
//        cerr << "a is nan" << endl;
//    }
//    if(std::isnan(rtSet)){
//        cerr << "rtSet is nan" << endl;
//    }
//    if(std::isnan(c)){
//        cerr << "c is nan" << endl;
//    }
//    if(std::isnan(d)){
//        cerr << "d is nan" << endl;
//    }
    // 求 step
    float step, step_up, step_down;
    step_up = -a*startEYE.x - b*startEYE.y - c*startEYE.z - d;
//    if(std::isnan(step_up)){
//        cerr << "step_up is nan" << endl;
//    }
    step_down = a*eyeGoPixel.dx + b*eyeGoPixel.dy + c*eyeGoPixel.dz;
//    if(std::isnan(step_down)){
//        cerr << "step_down is nan" << endl;
//    }

    step = step_up / step_down;
//    if(std::isnan(step)){
//        cerr << "step is nan" << endl;
//    }
    // 得到了 step 步进值
    glm::vec3 result = startEYE + (eyeGoPixel._ * step);

//    float pointScreenDeep = eyeGoPixel.dz * step - screenDeep4; // 得到了 像素点的 xyz

    return result; // 得到了 像素点的 xyz
}
void ImgRect::freshVerticalTopFlat_d(){
    VerticalTopFlat_d = -virtual_goY.dx* virtual_lrt_XYZ.lt.x - virtual_goY.dy* virtual_lrt_XYZ.lt.y
            - virtual_goY.dz * virtual_lrt_XYZ.lt.z;
}
glm::vec2 ImgRect::getUV01_ByVirtualFlatPoint(glm::vec3 posNow){

//    float stepU, stepV;
//
//    glm::vec3& lt = virtual_lrt_XYZ[2];
//
//    float stepV_up = (posNow.y / virtual_goY.dy
//            - lt.y / virtual_goY.dy
//                - virtual_goX.dy * posNow.x / (virtual_goX.dx * virtual_goY.dy)
//                - virtual_goX.dy * lt.x / (virtual_goX.dx * virtual_goY.dy) );
//
//    float stepV_down = 1 + virtual_goX.dy*virtual_goY.dx/ (virtual_goX.dx* virtual_goY.dy);
//
//    stepV = stepV_up / stepV_down;
//
//    stepU = (posNow.x - lt.x - virtual_goY.dx * stepV) / virtual_goX.dx;
//    return {stepU/width, stepV/height};
    float a=virtual_goY.dx, b=virtual_goY.dy, c=virtual_goY.dz;
    glm::vec3& lt = virtual_lrt_XYZ.lt;
    float d = VerticalTopFlat_d;
    // 获得走y 与lt 对应平面 ax+by+cz+d=0

    float stepV, step_up, step_down;
    step_up = -a*posNow.x - b*posNow.y - c*posNow.z - d;
    goLine32 goBackX = {-a, -b, -c};
    step_down = a*goBackX.dx + b*goBackX.dy + c*goBackX.dz;

    stepV = step_up / step_down;
    // 得到了 stepV 步进值

    glm::vec3 ltDown = lt + virtual_goY._ * stepV; // 得到了 像素点的 xyz
    float stepU = glm::distance(ltDown, posNow);

    return {stepU/width, stepV/height};
}
glm::vec3 ImgRect::getColorByUV01(glm::vec2 uv01){

    if(uv01[0] < 0){
//        cerr << "u: " << u << " < 0" << endl;
        return {0.f,0.f,0.f};
        // uv01[0] = 0.f;
    }
    else if(uv01[0] > 1){
//        cerr << "u: " << u << " > 1" << endl;
        return {0.f,0.f,0.f};
        // uv01[0] = 1.f;
    }
    if(uv01[1] < 0){
//        cerr << "v: " << v << " < 0" << endl;
        return {0.f,0.f,0.f};
        // uv01[1] = 0.f;
    }
    else if(uv01[1] > 1){
//        cerr << "v: " << v << " > 1" << endl;
        return {0.f,0.f,0.f};
        // uv01[1] = 1.f;
    }

    int u_i = static_cast<int>(uv01[0]*imgW_f);
    int v_i = static_cast<int>(uv01[1]*imgH_f);
    // 索引
    //int index = u_i * pixelsColor.innerMax + v_i;
    int index = v_i * imgW_f + u_i;

    if(index < pixelsColor.data.size()){ // 最后一个和 size 相等
        // println("u:{},v:{}",u_i,v_i);
        return pixelsColor.data[index];
    }// 颜色

    return {0.f,0.f,0.f};

}
void ImgRect::freshVirtual2X(){
    // rt lb lt mid tip reverseTip
    glm::vec3 lt2rt = virtual_lrt_XYZ.rt - virtual_lrt_XYZ.lt;
    lt2rt = glm::normalize(lt2rt);
    virtual_goX.dx = lt2rt.x;
    virtual_goX.dy = lt2rt.y;
    virtual_goX.dz = lt2rt.z;
}
void ImgRect::freshVirtual2Y(){
    // rt lb lt mid tip reverseTip
    glm::vec3 lt2lb = virtual_lrt_XYZ.lb - virtual_lrt_XYZ.lt; // lbXYZ - ltXYZ
    lt2lb = glm::normalize(lt2lb);
    virtual_goY.dx = lt2lb.x;
    virtual_goY.dy = lt2lb.y;
    virtual_goY.dz = lt2lb.z;

}
void ImgRect::freshVirtual2Z(){
    // rt lb lt mid tip reverseTip
    // glm::vec3 tip2c = virtual_lrt_XYZ[3] - virtual_lrt_XYZ[4];
    // tip2c = glm::normalize(tip2c);

    virtual_goZ.dx = virtualBack_a_b_c_d[0];
    virtual_goZ.dy = virtualBack_a_b_c_d[1];
    virtual_goZ.dz = virtualBack_a_b_c_d[2];
}
void ImgRect::freshFrameRotateInfo(){
    frameRotateInfo_q = PolygonBase::getFrameRotateInfo_(virtual_goX, virtual_goZ);
}
glm::vec3 ImgRect::screenXYZ2SelfXYZ(glm::vec3 _screenAxisPos){
    if(isnan(_screenAxisPos.x) || isnan(_screenAxisPos.y) || isnan(_screenAxisPos.z)){
        println(stderr,"_screenAxisPos(", _screenAxisPos.x, ", ", _screenAxisPos.y, ", ", _screenAxisPos.z, ")");
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }// 不是 nan
    glm::vec3 rectMid = (virtual_lrt_XYZ.lb + virtual_lrt_XYZ.rt) / 2.f;
    float backX = rectMid.x; // rt lb lt mid tip reverseTip
    float backY = rectMid.y;
    float backZ = rectMid.z;
    glm::vec3 p1ToWorld000 = {_screenAxisPos.x - backX, _screenAxisPos.y - backY, _screenAxisPos.z - backZ}; // 归原点
    float distanceOf000 = glm::distance(p1ToWorld000,glm::vec3{0.f,0.f,0.f} ); // 原点距
    goLine64 p1ToWorld000_dir1;
    p1ToWorld000_dir1 = {p1ToWorld000.x /= distanceOf000,
                                          p1ToWorld000.y /= distanceOf000,
                                          p1ToWorld000.z /= distanceOf000}; // 归一化
    // 没两角全0  不然不用斜转

    PolygonBase::rotate_vector(p1ToWorld000_dir1, frameRotateInfo_q);
    glm::vec3 farScreenAxis000 = {(float)p1ToWorld000_dir1.dx * distanceOf000,
                                  (float)p1ToWorld000_dir1.dy * distanceOf000,
                                  (float)p1ToWorld000_dir1.dz * distanceOf000};


    if(isnan(farScreenAxis000.x) || isnan(farScreenAxis000.y) || isnan(farScreenAxis000.z)){
        println(stderr,"farScreenAxis000(", farScreenAxis000.x, ", ", farScreenAxis000.y, ", ", farScreenAxis000.z, ")");
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }
    return farScreenAxis000;
}
glm::vec3 ImgRect::getColorBySelfAxisPos(glm::vec3 _selfAxisPos){
    // 上边距
    float ofY = _selfAxisPos.y + halfRectH; // y - -半高
    // 左边距
    float ofX = _selfAxisPos.x + halfRectW; // x - -半宽
    float u = ofX / (halfRectW*2);
    float v = ofY / (halfRectH*2);
    if(u < 0 ||u > 1 ||v < 0 ||v > 1){
//        cerr << "u: " << u << " < 0" << endl;
        return {0.f,0.f,0.f};
    }


    int u_i = static_cast<int>(u*imgW_f);
    int v_i = static_cast<int>(v*imgH_f);
    // 索引
    int index = v_i * pixelsColor.outterMax + u_i;

    if(index < pixelsColor.data.size()){ // 最后一个和 size 相等
        return pixelsColor.data[index];
    }// 颜色
        return {0.f,0.f,0.f};


}
