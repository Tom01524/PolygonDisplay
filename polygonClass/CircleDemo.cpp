//
// Created by iceoc0 on 2025/3/15.
//

#include "CircleDemo.h"


extern void* settled_ptr; // 全局设置的结构体指针
struct _settledCircle{
    int _width;
    int _height;
    int _deep;

};
_settledCircle* settled_ = (_settledCircle*)settled_ptr;
const int screenWidth10 = settled_-> _width;
const int screenHeight10 = settled_-> _height;
const int screenDeep10 = settled_-> _deep;



struct modeCircle{
    char now;char a;char b;char d;
};
extern void* mode_ptr;
modeCircle mode_ = *((modeCircle*)mode_ptr);


extern void* _3d_2d_go_void_ptr; // 3d_2d_go的函数指针
// struct _3d_2d_go_circle{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, float *, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_2d)(ScreenDemo*, float, float, float);
// };
glm::vec2 (*__3d2dGoCircle)(ScreenDemo*, glm::vec3, glm::vec3*) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2dCircle)(ScreenDemo*, float, float, float) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d; // 模式1 用自己的不行

CircleDemo::CircleDemo(glm::vec3 _lt, glm::vec3 _rt, glm::vec3 _rb, glm::vec3 _lb, bool backFont, unsigned char _debug_):PolygonBase(10) {
//    PolygonBase::type_ = 10; // 圆形

    if(backFont){
        _backFont = 1.0f; // 中突
    }else _backFont = -1.0f;
//    cout << "~~CircleDemo tblrXYZ.lt.y:" << tblrXYZ.ltSet.y << " tblrXYZ.rb.y:" << tblrXYZ.rbSet.y << endl;
    setTBLRXYZ(_lt, _rt, _rb, _lb);
//    tblrXYZ.ltSet = _lt; tblrXYZ.rtSet = _rt;tblrXYZ.lbSet = _rb;tblrXYZ.rbSet = _lb;
//    tblrXYZ.center.x = (_lt.x + _rb.x) / 2.0f;
//    tblrXYZ.center.y = (_lt.y + _rb.y) / 2.0f;
//    tblrXYZ.center.z = (_lt.z + _rb.z) / 2.0f;
//
//    // 计算两个边相量
//    glm::vec3 center2t = {tblrXYZ.center.x - _lt.x, tblrXYZ.center.y - _lt.y, tblrXYZ.center.z - _lt.z};
//
//    glm::vec3 center2r = {tblrXYZ.center.x - _lb.x, tblrXYZ.center.y - _lb.y, tblrXYZ.center.z - _lb.z};
//    // 计算法向量
//    float normal[3] = {0}; // 法向量 立方体对角线单位一
//    normal[0] = center2t.y * center2r.z - center2t.z * center2r.y;
//    normal[1] = center2t.z * center2r.x - center2t.x * center2r.z;
//    normal[2] = center2t.x * center2r.y - center2t.y * center2r.x;
//
//    // 归一化法向量
//    float magnitude = glm::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
//    normal[0] /= magnitude;
//    normal[1] /= magnitude;
//    normal[2] /= magnitude; // 法向量 立方体对角线单位一
//
//    if(_backFont == -1.0f){
//        normal[0] *= -1.0f;
//        normal[1] *= -1.0f;
//        normal[2] *= -1.0f; // 法向量 取反 ?
//    }
//
//    tblrXYZ.centerTip.x = tblrXYZ.center.x + normal[0] * 20.0f;
//    tblrXYZ.centerTip.y = tblrXYZ.center.y + normal[1] * 20.0f;
//    tblrXYZ.centerTip.z = tblrXYZ.center.z + normal[2] * 20.0f;

    tblrXYZ_unchange.ltSet = tblrXYZ.ltSet;
    tblrXYZ_unchange.rtSet = tblrXYZ.rtSet;
    tblrXYZ_unchange.lbSet = tblrXYZ.lbSet;
    tblrXYZ_unchange.rbSet = tblrXYZ.rbSet;
    tblrXYZ_unchange.center = tblrXYZ.center;
    tblrXYZ_unchange.centerTip = tblrXYZ.centerTip;
//    cout << "CircleDemo tblrXYZ.lt" << tblrXYZ.ltSet.x << " " << tblrXYZ.ltSet.y << " " <<
//    tblrXYZ.ltSet.z << endl;
//    cout << "CircleDemo tblrXYZ.center" << tblrXYZ.center.x << " " << tblrXYZ.center.y << " " <<
//    tblrXYZ.center.z << endl;

    virtual_tblrXYZ[0] = tblrXYZ.ltSet;
    virtual_tblrXYZ[1] = tblrXYZ.rtSet;
    virtual_tblrXYZ[2] = tblrXYZ.lbSet;
    virtual_tblrXYZ[3] = tblrXYZ.rbSet;
    virtual_tblrXYZ[4] = tblrXYZ.center;
    virtual_tblrXYZ[5] = tblrXYZ.centerTip;


    debugLine = _debug_;
    glm::vec3 midPointTop; // 正方 上边 中点
    midPointTop.x = (tblrXYZ.ltSet.x + tblrXYZ.rtSet.x) / 2.0f;
    midPointTop.y = (tblrXYZ.ltSet.y + tblrXYZ.rtSet.y) / 2.0f;
    midPointTop.z = (tblrXYZ.ltSet.z + tblrXYZ.rtSet.z) / 2.0f;
    // 连到 圆心 -2
    radius = glm::distance(midPointTop, tblrXYZ.center) - 2;

    squareEdge = glm::distance(tblrXYZ.ltSet, tblrXYZ.rtSet); // 边长
    squareDepth = glm::distance(tblrXYZ.center, tblrXYZ.centerTip); // 中突
}
void CircleDemo::Draw_Tick(ScreenDemo* ScreenEye){


        // 0     1      2     3     4     5
        // ltSet rbtSet rbSet lbSet center centerTip
        if(virtual_tblrXYZ[4].z + ScreenEye->rectDepth > 0.1F){ // 眼心距>100 才渲染

        }else {
            // println("圆面 距离过近 : {} + {} > 0.1F",virtual_tblrXYZ[4].z,ScreenEye->rectDepth);
            return;
        }



    bool onFront;float _color[3];
    if(cTipEyeCloser(ScreenEye->getCenterTip())){
        onFront = true;
    }else{
        onFront = false;
    }
//    cout << "tblrXYZ.ltSet" << tblrXYZ.ltSet.x << " " << tblrXYZ.ltSet.y << " " << tblrXYZ.ltSet.z << endl;
//    cout << "tblrXYZ_unchange.ltSet" << tblrXYZ_unchange.ltSet.x << " " << tblrXYZ_unchange.ltSet.y <<
//    " " << tblrXYZ_unchange.ltSet.z << endl;
//    setlinecolor(WHITE); // 恢复 画线颜色###

    if(onFront){
        if(debugLine == 1){

            _color[0] = 1.f;_color[1] = 1.f;_color[2] = 1.f;
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[4].x,tblrXY_f[4].y,
                                          tblrXY_f[0].x,tblrXY_f[0].y,
                                          _color,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[4].x,tblrXY_f[4].y,
                                          tblrXY_f[1].x,tblrXY_f[1].y,
                                          _color,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[4].x,tblrXY_f[4].y,
                                          tblrXY_f[2].x,tblrXY_f[2].y,
                                          _color,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[4].x,tblrXY_f[4].y,
                                          tblrXY_f[3].x,tblrXY_f[3].y,
                                          _color,screenNear);

        }


        _solidCircle2D(ScreenEye, onFront);
        if(debugLine == 1){
// center tip###

            _color[0] = 1.f;_color[1] = 1.f;_color[2] = 1.f;
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[4].x,tblrXY_f[4].y,
                                          tblrXY_f[5].x,tblrXY_f[5].y,
                                          _color,screenNear);

        }

    }
    else{ // 背面
        if(debugLine == 1){


            _color[0] = 1.f;_color[1] = 1.f;_color[2] = 1.f;
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[4].x,tblrXY_f[4].y,
                                          tblrXY_f[5].x,tblrXY_f[5].y,
                                          _color,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[4].x,tblrXY_f[4].y,
                                          tblrXY_f[0].x,tblrXY_f[0].y,
                                          _color,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[4].x,tblrXY_f[4].y,
                                          tblrXY_f[1].x,tblrXY_f[1].y,
                                          _color,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[4].x,tblrXY_f[4].y,
                                          tblrXY_f[2].x,tblrXY_f[2].y,
                                          _color,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[4].x,tblrXY_f[4].y,
                                          tblrXY_f[3].x,tblrXY_f[3].y,
                                          _color,screenNear);
        }

        _solidCircle2D(ScreenEye, onFront);

        if(debugLine == 1){
// center back###

            _color[0] = 1.f;_color[1] = 1.f;_color[2] = 1.f;
//            PolygonBase::line(tblrXY_f[4].x,tblrXY_f[4].y,
//                              centerBackXY.x, centerBackXY.y,_color);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[4].x,tblrXY_f[4].y,
                                          centerBackXY.x, centerBackXY.y,
                                          _color,screenNear);
        }

    }

    if(debugLine==2){
        freshCircleAxis(); // 更新坐标轴 info
        //drawCircleAxis(ScreenEye); // 画坐标轴
    }

}
glm::vec3 CircleDemo::getCenter() {
    return tblrXYZ.center;
}
glm::vec3 CircleDemo::getVirtualCenter(){
    return virtual_tblrXYZ[4];
}
void CircleDemo::_solidCircle2D(ScreenDemo* ScreenEye, bool onFront){
    bool all2Dleft = tblrXY_f[0].x < 0.f && tblrXY_f[1].x < 0.f && tblrXY_f[2].x < 0.f &&
            tblrXY_f[3].x < 0.f;
    bool all2Dright = tblrXY_f[0].x > static_cast<float>(screenWidth10) && tblrXY_f[1].x > static_cast<float>(screenWidth10) &&
            tblrXY_f[2].x > static_cast<float>(screenWidth10) && tblrXY_f[3].x > static_cast<float>(screenWidth10);
    bool all2Dtop = tblrXY_f[0].y < 0.f && tblrXY_f[1].y < 0.f && tblrXY_f[2].y < 0.f &&
                    tblrXY_f[3].y < 0.f;
    bool all2Dbottom = tblrXY_f[0].y > static_cast<float>(screenHeight10) && tblrXY_f[1].y > static_cast<float>(screenHeight10) &&
            tblrXY_f[2].y > static_cast<float>(screenHeight10) && tblrXY_f[3].y > static_cast<float>(screenHeight10);
    // 0     1      2     3     4     5
    // ltSet rbtSet rbSet lbSet center centerTip
    bool cornerClose2Eye = virtual_tblrXYZ[4].z + ScreenEye->rectDepth < 0.1f;
    bool corner2DoutOfScreen = all2Dleft || all2Dright || all2Dtop || all2Dbottom;

    if(cornerClose2Eye || corner2DoutOfScreen)return;


    // horizontalDeepCalc4(ScreenEye);
    PolygonBase::fresh2D_scanRows_4(tblrXY_f[0],
                                    tblrXY_f[1],
                                    tblrXY_f[2],
                                    tblrXY_f[3], &lineScanFillColor,type_);

    centerBackXY = __3d2dGoCircle(ScreenEye, centerBackXYZ, nullptr);

    pixelEyeDeep.clear();



    float frameEyeFar, frameEyeNear; // 定点深度初始化
    if(mode_.now == mode_.b){
        frameEyeFar = tblrXYZ.center.z;
        frameEyeNear = tblrXYZ.center.z; // 定点深度初始化
    }else{
        frameEyeFar = virtual_tblrXYZ[4].z;
        frameEyeNear = virtual_tblrXYZ[4].z; // 定点深度初始化
    }

    for(auto& _linePosInfo : lineScanFillColor){
        if(std::isnan(_linePosInfo.lx)){
//            cerr << "lineScanFillColor.lx:" << _linePosInfo.lx <<
//                 " is nan" << endl;
            continue;
        }
        if(std::isnan(_linePosInfo.rx)){
            println(stderr,"圆 lineScanFillColor.rx:", _linePosInfo.rx,
                 " is nan");
            continue;
        }
        if(_linePosInfo.rx < _linePosInfo.lx){
            println(stderr,"圆 lineScanFillColor.rx:", _linePosInfo.rx,
                 " < lineScanFillColor.lx:", _linePosInfo.lx);
            continue;
        }

        rowPixelDeep10 rowDeepInfo;
        rowDeepInfo.y = _linePosInfo.y; // 本行 y
        rowDeepInfo.pixelDeeps.clear(); // 本行 x deep 空
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){
//            cout << "^^^nowX:" << nowX << " y:" << _linePosInfo.y << endl;
            //float deepNow = getEyeDeepbyXY(nowX, _linePosInfo.y);
            float deepNow = getScreenDeepbyXY(nowX, _linePosInfo.y); // 2D→3D 得到屏幕深度
            if(isnan(deepNow)){
                rowDeepInfo.pixelDeeps.push_back({nowX, deepNow, false}); // 圆外 2D→3D 不计深度 nan
                continue;
            }


            if(deepNow > frameEyeFar)frameEyeFar = deepNow;
                // 比大的更大 不可能还比小得更小
            else if(deepNow < frameEyeNear)frameEyeNear = deepNow;

            rowDeepInfo.pixelDeeps.push_back({nowX, deepNow, true}); // 本行 x deep

        }
        pixelEyeDeep.push_back(rowDeepInfo);


    }
    screenFar = frameEyeFar; // 当前帧 最远最近获得
    screenNear = frameEyeNear;

    for(auto& _linfDeepInfo : pixelEyeDeep){
        for(int i=0;i<_linfDeepInfo.pixelDeeps.size()/*-1*/;i++){
            int nowX = _linfDeepInfo.pixelDeeps[i].x;
            float nowDeep = _linfDeepInfo.pixelDeeps[i].screenDeep;

            if(onFront){
                //cout << "debugLine" << (int)debugLine << endl;
                if(debugLine==1) {
                    
                    if(_linfDeepInfo.pixelDeeps[i].inCirce){
                        int colorNow = black2ColorfulScreenDeep(nowDeep);
//                        putpixel((int) roundf(nowX), _linfDeepInfo.y, colorNow); // ### screenDeep eyeDistace
                        BGR3f colorNow1;
                        colorNow1.setBGR(colorNow,1);
                        float _color_[3] = {colorNow1.r1,colorNow1.g1,colorNow1.b1};
                        ScreenEye->putPixel(nowX,static_cast<int>(_linfDeepInfo.y),_color_,nowDeep,(PolygonBase*)this);


                    }

//
                }else{
                    if(_linfDeepInfo.pixelDeeps[i].inCirce){
                        float _color_[3] = {frontColor_rgb01[0],frontColor_rgb01[1],frontColor_rgb01[2]};
                        ScreenEye->putPixel(nowX,static_cast<int>(_linfDeepInfo.y),_color_,nowDeep,(PolygonBase*)this);

                    }

                }
            }
            else{
                if(_linfDeepInfo.pixelDeeps[i].inCirce){
                    float _color_[3] = {backColor_rgb01[0],backColor_rgb01[1],backColor_rgb01[2]};
                    ScreenEye->putPixel(nowX,static_cast<int>(_linfDeepInfo.y),_color_,nowDeep,(PolygonBase*)this);

                }


            }
        }
    }

}
bool CircleDemo::cTipEyeCloser(glm::vec3 eyeCenter){

    centerBackXYZ.x = 2*tblrXYZ.center.x-tblrXYZ.centerTip.x;
    centerBackXYZ.y = 2*tblrXYZ.center.y-tblrXYZ.centerTip.y;
    centerBackXYZ.z = 2*tblrXYZ.center.z-tblrXYZ.centerTip.z; // virtualCenterBack

    if(mode_.now == mode_.b){

        float cBackFarX = eyeCenter.x - centerBackXYZ.x;
        float cBackFarY = eyeCenter.y - centerBackXYZ.y;
        float cBackFarZ = eyeCenter.z - centerBackXYZ.z; // virtualCenterBack

        float ctFarX = eyeCenter.x - tblrXYZ.centerTip.x;
        float ctFarY = eyeCenter.y - tblrXYZ.centerTip.y;
        float ctFarZ = eyeCenter.z - tblrXYZ.centerTip.z;

        float centerDistance_square = cBackFarX*cBackFarX + cBackFarY*cBackFarY + cBackFarZ*cBackFarZ;
        float centerTipDistance_square = ctFarX*ctFarX + ctFarY*ctFarY + ctFarZ*ctFarZ;

        if(centerDistance_square > centerTipDistance_square){
            return true;
        }
        else{
            return false;
        }
    }else {
        glm::vec3 stratEye = {(float)screenWidth10/2.0f, (float)screenHeight10/2.0f, (float)-screenDeep10}; // 初始化一次 (600,400,-1000)
        virtual_centerBack.x = 2 * virtual_tblrXYZ[4].x - virtual_tblrXYZ[5].x;
        virtual_centerBack.y = 2 * virtual_tblrXYZ[4].y - virtual_tblrXYZ[5].y;
        virtual_centerBack.z = 2 * virtual_tblrXYZ[4].z - virtual_tblrXYZ[5].z; // virtualCenterBack
        float cBackFarX = stratEye.x - virtual_centerBack.x;
        float cBackFarY = stratEye.y - virtual_centerBack.y;
        float cBackFarZ = stratEye.z - virtual_centerBack.z; // virtualCenterBack

        float ctFarX = stratEye.x - virtual_tblrXYZ[5].x;
        float ctFarY = stratEye.y - virtual_tblrXYZ[5].y;
        float ctFarZ = stratEye.z - virtual_tblrXYZ[5].z;

        float centerBackDistance_square = cBackFarX * cBackFarX + cBackFarY * cBackFarY + cBackFarZ * cBackFarZ;
        float centerTipDistance_square = ctFarX * ctFarX + ctFarY * ctFarY + ctFarZ * ctFarZ;

        if (centerBackDistance_square > centerTipDistance_square) {
            return true;
        } else {
            return false;
        }
    }
}
float CircleDemo::getEyeDeepbyXY(float x, float y){
//    cout << "^^^x:" << x << " y:" << y << endl;
    // 初始化一次 (600,400,-1000)
    glm::vec3 startEye = {(float)screenWidth10/2.0f, (float)screenHeight10/2.0f, (float)-screenDeep10}; // 初始化一次 (600,400,-1000)
    glm::vec3 pointXYZ = getFlatPointXYZbyXY(x, y);// 计算像素点到屏幕中心的距离
//    cout << "pointXYZ:" << pointXYZ.x << " " << pointXYZ.y << " " << pointXYZ.z << endl;

    float centerDistence = glm::distance(virtual_tblrXYZ[4], pointXYZ); // 计算像素点到圆心的距离
//    cout << "centerDistence:" << centerDistence << "radius:" << radius << endl;
    if(centerDistence > radius){
        return nanf(""); // 超出圆心 无效值
    }
    float eyeDistence = glm::distance(startEye, pointXYZ); // 计算像素点到屏幕中心的距离
    return eyeDistence; // 计算像素点到屏幕中心的距离
}
float CircleDemo::getScreenDeepbyXY(float x, float y){
    // 初始化一次 (600,400,-1000)
    glm::vec3 startEYE = {(float)screenWidth10/2.0f, (float)screenHeight10/2.0f, (float)-screenDeep10};
    goLine32 eyeGoPixel = eye2ScreenPixel_dxyz(x, y); // 计算 屏幕中心到像素点 的向量
//    cout << "eyeGoPixel:" << eyeGoPixel.dx << " " << eyeGoPixel.dy << " " << eyeGoPixel.dz << endl;
    // eye.x + dx * step = x
    // eye.y + dy * step = y
    // eye.z + dz * step = z

    // 已知 abcd ax+by+cz+d=0
    // a*(eye.x + dx * step) + rtSet*(eye.y + dy * step) + c*(eye.z + dz * step) + d = 0
    float a, b, c, d;
    if(mode_.now == mode_.b){
        a = a_b_c_d[0];
        b = a_b_c_d[1];
        c = a_b_c_d[2];
        d = a_b_c_d[3];
    }else{ // mode 4
        a = virtualBack_a_b_c_d[0];
        b = virtualBack_a_b_c_d[1];
        c = virtualBack_a_b_c_d[2];
        d = virtualBack_a_b_c_d[3];
    }



//    if(std::isnan(a)){
//        cerr << "a is nan" << endl;
//    }
//    if(std::isnan(b)){
//        cerr << "b is nan" << endl;
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
    glm::vec3 _result = {startEYE.x + eyeGoPixel.dx * step,
                       startEYE.y + eyeGoPixel.dy * step,
                       startEYE.z + eyeGoPixel.dz * step};
    float centerDistence = glm::distance(virtual_tblrXYZ[4], _result); // 计算像素点到圆心的距离
//    cout << "centerDistence:" << centerDistence << "radius:" << radius << endl;
    if(centerDistence > radius){
        return nanf(""); // 超出圆心 无效值
    }


    float pointScreenDeep = eyeGoPixel.dz * step - screenDeep10;
    return pointScreenDeep; // 计算像素点到屏幕中心的距离
}
glm::vec3 CircleDemo::getFlatPointXYZbyXY(float x, float y){
    // 已知 眼xyz 步进xyz

    // 初始化一次 (600,400,-1000)
    glm::vec3 startEYE = {(float)screenWidth10/2.0f, (float)screenHeight10/2.0f, (float)-screenDeep10};
    goLine32 eyeGoPixel = eye2ScreenPixel_dxyz(x, y); // 计算 屏幕中心到像素点 的向量
//    cout << "eyeGoPixel:" << eyeGoPixel.dx << " " << eyeGoPixel.dy << " " << eyeGoPixel.dz << endl;
    // eye.x + dx * step = x
    // eye.y + dy * step = y
    // eye.z + dz * step = z

    // 已知 abcd ax+by+cz+d=0
    // a*(eye.x + dx * step) + rtSet*(eye.y + dy * step) + c*(eye.z + dz * step) + d = 0
    float a, b, c, d;

        a = virtualBack_a_b_c_d[0];
        b = virtualBack_a_b_c_d[1];
        c = virtualBack_a_b_c_d[2];
        d = virtualBack_a_b_c_d[3];


    if(std::isnan(a)){
        println(stderr,"a is nan");
    }
    if(std::isnan(b)){
        println(stderr,"b is nan");
    }
    if(std::isnan(c)){
        println(stderr,"c is nan");
    }
    if(std::isnan(d)){
        println(stderr,"d is nan");
    }
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
    glm::vec3 _result = {startEYE.x + eyeGoPixel.dx * step,
                       startEYE.y + eyeGoPixel.dy * step,
                       startEYE.z + eyeGoPixel.dz * step};
//    cout << "result:" << _result.x << " " << _result.y << " " << _result.z << endl;
    // 得到了 像素点的 xyz
    return _result;
}
goLine32 CircleDemo::eye2ScreenPixel_dxyz(float x, float y){
    glm::vec3 pixelXYZ = {x, y, 0.0f};
//    cout << "pixelXYZ:" << pixelXYZ.x << " " << pixelXYZ.y << " " << pixelXYZ.z << endl;
    glm::vec3 startEYE = {(float)screenWidth10/2.0f, (float)screenHeight10/2.0f, (float)-screenDeep10}; // 初始化一次 (600,400,-1000)
    float pixel2eye_far = glm::distance(startEYE, pixelXYZ); // 计算像素点到屏幕中心的距离

    float farX = pixelXYZ.x - startEYE.x; // 大减小 为正 走右
    float farY = pixelXYZ.y - startEYE.y; // 大减小 为正 走下
    float farZ = 0.0f - startEYE.z; // 初始化一次 (1000)
    float dx = farX / pixel2eye_far;
    float dy = farY / pixel2eye_far;
    float dz = farZ / pixel2eye_far;
    return {dx, dy, dz}; // 计算像素点到屏幕中心的向量
}

bool CircleDemo::PolyScanClicked(int x,int y)
{
    for(auto& _rowInfo : pixelEyeDeep){
        if(y == _rowInfo.y){
            for(auto& _pixelInfo : _rowInfo.pixelDeeps){
                if(x == _pixelInfo.x && _pixelInfo.inCirce){
                    return true; // 点在圆内 x也对
                }
            }break;
        }
//        if(y==lineBoundary.y && x>=lineBoundary.lx && x<=lineBoundary.rx){
//            cout << "三角形被点击了！";
//            return true; // 三角形被点击了！
//        }
    }
    return false; // 三角形未被点击
}


bool CircleDemo::midPointLineLeft(glm::vec2& lineBegin, glm::vec2& lineEnd, glm::vec2& midPoint){

//    // 检查点是否在线段上
//    if (lenBC > lenAC) {
//        return false; // 点不在线段上
//    }

    // 使用向量叉积判断点的位置
    float cross = crossProduct(lineBegin, lineEnd, midPoint);

    // 如果叉积大于0，点在线段的左侧
    if (cross > 0) {
        return true; // 点在线段左侧
    }
    return false; // 点在线段右侧或在线段上
}
float CircleDemo::crossProduct(const glm::vec2& lineBegin, const glm::vec2& lineEnd, const glm::vec2& midPoint) {
    float ABx = lineEnd.x - lineBegin.x;
    float ABy = lineEnd.y - lineBegin.y;
    float ACx = midPoint.x - lineBegin.x;
    float ACy = midPoint.y - lineBegin.y;

    /*
                 ABx
                 m
           b__________e
            |    |    |
            |    |    | ACy
       ABy m|____|____|
            |    |
            |    |
           e|____|
             ACx
       */
    /*
                 ABx
                 m
           b__________e
            |\   |    |
            | \  |big | ACy
            |  \ |ger |
       ABy m|___\|____|
            |    | mP
            |smal|\
            |ler | \
           e|____|  \
             ACx
        */
    return ABx * ACy - ABy * ACx;
}
float CircleDemo::getXby_line_y_2D(int upperP_th, int lowerP_th, float y){
    // y = a*x + b
    glm::vec2 upperP = tblrXY_f[upperP_th];
    glm::vec2 lowerP = tblrXY_f[lowerP_th];
    float x;


    // if(y > lowerP.y){
    //     //cerr << "2D lx rx: fix y:" << y << " > lowerP.y:" << lowerP.y <<
    //     //" lowerP.x:" << lowerP.x << endl;
    //     //cerr << "lt rt rb lb:" << lowerP_th << endl;
    //     y = lowerP.y; // 防止y越下界 求 lx rx 行扫描
    // }
    // else if(y < upperP.y){
    //     // cerr << "2D lx rx: fix y:" << y << " < upperP.y:" << upperP.y <<
    //     // " lowerP.x:" << lowerP.x << endl;
    //     // cerr << "lt rt rb lb:" << upperP_th << endl; // ### ###
    //     y = upperP.y; // 防止y越上界 求 lx rx 行扫描
    // }
    y = std::clamp(y,upperP.y,lowerP.y);

    // 等比例三角形求法
    /*         upperP(x,y)
     *           /|
     *          / |
     *      ?x /__| y
     *        /   |
     *       /    |
     *      /     |
     *     /      |
     *    /_______|
     *  lowerP(x,y)
     *
    */
    // (lowery - uppery) / (y - uppery) = (upperx - lowerx) / (upperx - x)
    // x = ux - (y-uy)*(ux-lx)/(ly-uy)
    if(lowerP.y != upperP.y){
        x = upperP.x - (y - upperP.y) * (upperP.x - lowerP.x) / (lowerP.y - upperP.y);
    }else{
        x = upperP.x - (y - upperP.y) * (upperP.x - lowerP.x) / 0.00001f;
        println(stderr,"circleDemo lowerP.y:", lowerP.y, " upperP.y:", lowerP.y, " 相等");
    }
    return x;

}
int CircleDemo::black2ColorfulScreenDeep(float deepNow){


    float _eyeDist_far;
    float _eyeDist_near;


    //cout << "allPointsEyeDeep 大小" << allPointsEyeDeep.size() << endl;

//    if(_first){ // 调试 allPointsEyeDeep 信息
//        float _y;
//        int _last;
//        for(auto _inner : allPointsEyeDeep){
//            _y = _inner.y;
//            _last = _inner.lineInfoVec.size()-1;
//            cout << "^^^x:" << _inner.lineInfoVec[0].x << " y:" << _y <<
//            " deep:" << _inner.lineInfoVec[0].eyeDistace << endl;
//            cout << "^^^x:" << _inner.lineInfoVec[_last].x << " y:" << _y <<
//                 " deep:" << _inner.lineInfoVec[_last].eyeDistace << endl;
//        }
//    }

    _eyeDist_far = screenFar;
    _eyeDist_near = screenNear;


// 所有深度
//    if(_first){
//        cout << "_eyeDist_far:" << _eyeDist_far << " _eyeDist_near:" << _eyeDist_near << endl;
//        cout << "四 顶点 screenFar:" << screenFar << " screenNear:" << screenNear << endl;
//    }

    float deepBetween = _eyeDist_far - _eyeDist_near; // 两端深度差
    float B = frontColor_rgb01[2] * 255.f;
    float G = frontColor_rgb01[1] * 255.f; // 右移 保留后两位
    float R = frontColor_rgb01[0] * 255.f; // 保留后两位
    //cout << hex << "B:" << B << " G:" << G << " R:" << R << endl;
    if(deepBetween==0.0f){
        deepBetween = 0.000001f;
        //puts("颜色偏白 最深最浅差是0 不能除0 (0.000001)"); // 一打印就卡死
    }
    float dB = (255.0f-B) / deepBetween; // 最深和最近的差 颜色变化
    float dG = (255.0f-G) / deepBetween;
    float dR = (255.0f-R) / deepBetween; // 白 255 - 黑 无 --------------------------------------
    //cout << hex << "dB:" << dB << " dG:" << dG << " dR:" << dR << endl;

//    float rowLDeep, rowRDeep;
//    for(auto& lineScanDeep : lineScanFillColor){
//        if(Py == lineScanDeep.x){ // 是这一行 拿深度
//            rowLDeep = lineScanDeep.lx;
//            rowRDeep = lineScanDeep.rx;
//        }
//    }
//    float rowLX, rowRX;
//    for(auto& lineScanPos : lineScanFill){ // 获取当前行的 lx rx
//        if(Py == lineScanPos.x) {
//            rowLX = lineScanPos.lx;
//            rowRX = lineScanPos.rx;
//        }
//    }
    float pointDeep = deepNow; // 找到当前点的 在深度vector
//    if(pointDeep < screenNear){
//        //cerr << "pointDeep:" << pointDeep << " < screenNear:" << screenNear << endl; // ### ###
//        pointDeep = screenNear;
//    }else if(pointDeep > screenFar){
//        //cerr << "pointDeep:" << pointDeep << " > screenFar:" << screenFar << endl;
//        pointDeep = screenFar;
//    }


//    if(_first){
        //cout << "pointDeep:" << pointDeep << endl;
//        _first = false;
//    }
    float ofFarthest = _eyeDist_far - pointDeep; // 对于 最深和当前的深度差
    //float ofNearest = pointDeep - frameScreenNear; // 对于 最深和当前的深度差

    // 如果dB dG dR 一步到头 ofFarthest 可以走小半步
    float nowB = 255.0f - ofFarthest * dB;
    float nowG = 255.0f - ofFarthest * dG;
    float nowR = 255.0f - ofFarthest * dR; // 白 255 - 黑 无 --------------------------------------
    int color = ((int)roundf(nowB) << 16) + ((int)roundf(nowG) << 8) + (int)roundf(nowR);
    color = (color & 0x00ffffff); // 最左一字节 00

//    if(std::isnan(nowB) || std::isnan(nowG) || std::isnan(nowR)){
//        cerr << "nowB:" << nowB << " nowG:" << nowG << " nowR:" << nowR << endl;
//    }

    //cout << "color final:" << color << endl;
    return color;
}
//void CircleDemo::freshDeepFarNear(){
//
//    float deepLT = virtual_tblrXYZ[0].z;
//    float deepRT = virtual_tblrXYZ[1].z;
//    float deepRB = virtual_tblrXYZ[2].z;
//    float deepLB = virtual_tblrXYZ[3].z;
//    float fourPointsDeep[4] = {deepLT, deepRT, deepRB, deepLB};
//    float frameScreenFar = fourPointsDeep[0], frameScreenNear = fourPointsDeep[0];
//    for(int i=0;i<4;i++){
//        if(fourPointsDeep[i] > frameScreenFar){ // 比我大
//            frameScreenFar = fourPointsDeep[i];
//        }
//        else if(fourPointsDeep[i] < frameScreenNear){ // 比我小  比大的更大 不可能比小得更小
//            frameScreenNear = fourPointsDeep[i];
//        }
//    }
//    screenFar = frameScreenFar; // 记录一下
//    screenNear = frameScreenNear; // 记录一下
//
//}
void CircleDemo::setColor(int fontColor1){
    BGR3f colorBGR;
    colorBGR.setBGR(fontColor1,1.f);
    frontColor_rgb01[0] = colorBGR.r1;
    frontColor_rgb01[1] = colorBGR.g1;
    frontColor_rgb01[2] = colorBGR.b1;

}
void CircleDemo::setBackColor(int backColor1){
    BGR3f colorBGR;
    colorBGR.setBGR(backColor1,1.f);
    backColor_rgb01[0] = colorBGR.r1;
    backColor_rgb01[1] = colorBGR.g1;
    backColor_rgb01[2] = colorBGR.b1;
}


void CircleDemo::switchDebug(){
    if(debugLine==0){
        debugLine = 1;
        println("circle debugLine 1");
    }
    else if(debugLine==1){
        debugLine = 2;
        println("circle debugLine 2");
    }
    else{
        debugLine = 0;
        println("circle debugLine 0");
    }
}
void CircleDemo::setTBLRXY_l(glm::ivec2 tblr0, glm::ivec2 tblr1, glm::ivec2 tblr2, glm::ivec2 tblr3, glm::ivec2 tblrC, glm::ivec2 tblrCT){

    tblrXY_l[0].x = tblr0.x; // lt
    tblrXY_l[0].y = tblr0.y;
    tblrXY_l[1].x = tblr1.x; // rt
    tblrXY_l[1].y = tblr1.y;
    tblrXY_l[2].x = tblr2.x; // rb
    tblrXY_l[2].y = tblr2.y;
    tblrXY_l[3].x = tblr3.x; // lb
    tblrXY_l[3].y = tblr3.y;
    tblrXY_l[4].x = tblrC.x; // center
    tblrXY_l[4].y = tblrC.y;
    tblrXY_l[5].x = tblrCT.x; // ctip
    tblrXY_l[5].y = tblrCT.y;
//    printf("~~~~~~Xl X:%d, Y:%d\n", tblrXY_l[0].y, tblrXY_l[0].x);
//    printf("~~~~~~Xr X:%d, Y:%d\n", tblrXY_l[1].y, tblrXY_l[1].x);
//    printf("~~~~~~Yb X:%d, Y:%d\n", tblrXY_l[2].y, tblrXY_l[2].x);
//    printf("~~~~~~Yt X:%d, Y:%d\n", tblrXY_l[3].y, tblrXY_l[3].x);

}
void CircleDemo::setTBLRXY_f(glm::vec2 lt_XY, glm::vec2 rt_XY, glm::vec2 rb_XY, glm::vec2 lb_XY, glm::vec2 center_XY, glm::vec2 ctip_XY){

    tblrXY_f[0].x = lt_XY.x; // lt
    tblrXY_f[0].y = lt_XY.y;
    tblrXY_f[1].x = rt_XY.x; // rt
    tblrXY_f[1].y = rt_XY.y;
    tblrXY_f[2].x = rb_XY.x; // rb
    tblrXY_f[2].y = rb_XY.y;
    tblrXY_f[3].x = lb_XY.x; // lb
    tblrXY_f[3].y = lb_XY.y;
    tblrXY_f[4].x = center_XY.x; // center
    tblrXY_f[4].y = center_XY.y;
    tblrXY_f[5].x = ctip_XY.x; // ctip
    tblrXY_f[5].y = ctip_XY.y;
//    printf("~~~~~~Xl X:%d, Y:%d\n", tblrXY_l[0].y, tblrXY_l[0].x);
//    printf("~~~~~~Xr X:%d, Y:%d\n", tblrXY_l[1].y, tblrXY_l[1].x);
//    printf("~~~~~~Yb X:%d, Y:%d\n", tblrXY_l[2].y, tblrXY_l[2].x);
//    printf("~~~~~~Yt X:%d, Y:%d\n", tblrXY_l[3].y, tblrXY_l[3].x);

//    glm::ivec2 _0 = {(long)roundf(tblrXY_f[0].x), (long)roundf(tblrXY_f[0].y)};
//    glm::ivec2 _1 = {(long)roundf(tblrXY_f[1].x), (long)roundf(tblrXY_f[1].y)};
//    glm::ivec2 _2 = {(long)roundf(tblrXY_f[2].x), (long)roundf(tblrXY_f[2].y)};
//    glm::ivec2 _3 = {(long)roundf(tblrXY_f[3].x), (long)roundf(tblrXY_f[3].y)};
//    glm::ivec2 _4 = {(long)roundf(tblrXY_f[4].x), (long)roundf(tblrXY_f[4].y)};
//    glm::ivec2 _5 = {(long)roundf(tblrXY_f[5].x), (long)roundf(tblrXY_f[5].y)};
//    setTBLRXY_l(_0, _1, _2, _3, _4, _5);

    // 刚刷新 virtual 在3D→2D 世界坐标系→屏幕坐标
    ax1_by1_cz1_d1_virtualFlat();

}
void CircleDemo::setTBLRXYZ(glm::vec3 _lt, glm::vec3 _rt, glm::vec3 _rb, glm::vec3 _lb){

    tblrXYZ.ltSet.x = _lt.x;
    tblrXYZ.ltSet.y = _lt.y;
    tblrXYZ.ltSet.z = _lt.z;

    tblrXYZ.rtSet.x = _rt.x;
    tblrXYZ.rtSet.y = _rt.y;
    tblrXYZ.rtSet.z = _rt.z;

    tblrXYZ.rbSet.x = _rb.x;
    tblrXYZ.rbSet.y = _rb.y;
    tblrXYZ.rbSet.z = _rb.z;

    tblrXYZ.lbSet.x = _lb.x;
    tblrXYZ.lbSet.y = _lb.y;
    tblrXYZ.lbSet.z = _lb.z;

    tblrXYZ.center.x = (_lt.x + _rb.x) / 2.0f; // 中心点

    tblrXYZ.center.y = (_lt.y + _rb.y) / 2.0f;
    tblrXYZ.center.z = (_lt.z + _rb.z) / 2.0f;
//    cout << "CircleDemo tblrXYZ.lt" << tblrXYZ.ltSet.x << " " << tblrXYZ.ltSet.y << " " <<
//         tblrXYZ.ltSet.z << endl;
//    cout << "CircleDemo tblrXYZ.center" << tblrXYZ.center.x << " " << tblrXYZ.center.y << " " <<
//         tblrXYZ.center.z << endl;
//    cout << "CircleDemo tblrXYZ.rb" << tblrXYZ.rbSet.x << " " << tblrXYZ.rbSet.y << " " <<
//         tblrXYZ.rbSet.z << endl;



    // 计算两个边相量
    glm::vec3 center2t = {tblrXYZ.center.x - _lt.x, tblrXYZ.center.y - _lt.y, tblrXYZ.center.z - _lt.z};

    glm::vec3 center2r = {tblrXYZ.center.x - _rt.x, tblrXYZ.center.y - _rt.y, tblrXYZ.center.z - _rt.z};
    // 计算法向量
    float normal[3] = {0};
    normal[0] = center2t.y * center2r.z - center2t.z * center2r.y; // lt2lb左 lt2rt右
    normal[1] = center2t.z * center2r.x - center2t.x * center2r.z; // x→ y→ z→ x
    normal[2] = center2t.x * center2r.y - center2t.y * center2r.x; //

    // 归一化法向量
    float magnitude = glm::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    normal[0] /= magnitude;
    normal[1] /= magnitude;
    normal[2] /= magnitude; // 法向量 立方体对角线单位一

    if(_backFont == -1.0f){
        normal[0] *= -1.0f;
        normal[1] *= -1.0f;
        normal[2] *= -1.0f; // 法向量 取反 ?
    }

    tblrXYZ.centerTip.x = tblrXYZ.center.x + normal[0] * 20.0f; // 中心点的尖端
    tblrXYZ.centerTip.y = tblrXYZ.center.y + normal[1] * 20.0f;
    tblrXYZ.centerTip.z = tblrXYZ.center.z + normal[2] * 20.0f;

    if(mode_.now == mode_.b ){
        a_b_c_d[0] = normal[0];
        a_b_c_d[1] = normal[1];
        a_b_c_d[2] = normal[2];
        a_b_c_d[3] = -normal[0] * tblrXYZ.center.x - normal[1] * tblrXYZ.center.y - normal[2] * tblrXYZ.center.z;
    }

    // 方程 ax + by + cz + d = 0
//    if(mode_.now == mode_.b){
//        // 模式2 依轴 同步 回正点info
//        virtual_tblrXYZ[0] = tblrXYZ.ltSet;
//        virtual_tblrXYZ[1] = tblrXYZ.rtSet;
//        virtual_tblrXYZ[2] = tblrXYZ.lbSet;
//        virtual_tblrXYZ[3] = tblrXYZ.rbSet;
//        virtual_tblrXYZ[4] = tblrXYZ.center;
//        virtual_tblrXYZ[5] = tblrXYZ.centerTip;
//    }

}
void CircleDemo::ax1_by1_cz1_d1_virtualFlat(){

    // 计算两个边相量
    glm::vec3 center2lt = {virtual_tblrXYZ[4].x - virtual_tblrXYZ[0].x,
                        virtual_tblrXYZ[4].y - virtual_tblrXYZ[0].y, virtual_tblrXYZ[4].z - virtual_tblrXYZ[0].z};

    glm::vec3 center2rt = {virtual_tblrXYZ[4].x - virtual_tblrXYZ[1].x,
                        virtual_tblrXYZ[4].y - virtual_tblrXYZ[1].y, virtual_tblrXYZ[4].z - virtual_tblrXYZ[1].z};
    // 计算法向量
    float normal[3] = {0};
    normal[0] = center2lt.y * center2rt.z - center2lt.z * center2rt.y; // lt2lb左 lt2rt右
    normal[1] = center2lt.z * center2rt.x - center2lt.x * center2rt.z; // x→ y→ z→ x
    normal[2] = center2lt.x * center2rt.y - center2lt.y * center2rt.x; //

    // 归一化法向量
    float magnitude = glm::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    normal[0] /= magnitude;
    normal[1] /= magnitude;
    normal[2] /= magnitude; // 法向量 立方体对角线单位一

    if(_backFont == -1.0f){
        normal[0] *= -1.0f;
        normal[1] *= -1.0f;
        normal[2] *= -1.0f; // 法向量 取反 ?
    }

    // ax + by + cz + d = 0
    // d = -ax1 - by1 - cz1

    virtualBack_a_b_c_d[0] = normal[0];
    virtualBack_a_b_c_d[1] = normal[1];
    virtualBack_a_b_c_d[2] = normal[2];
    virtualBack_a_b_c_d[3] = -normal[0] * virtual_tblrXYZ[4].x - normal[1] * virtual_tblrXYZ[4].y - normal[2] * virtual_tblrXYZ[4].z;

//    cout << "virtual back a:" << virtualBack_a_b_c_d[0] << " b:" << virtualBack_a_b_c_d[1] <<
//         " c:" << virtualBack_a_b_c_d[2] << " d:" << virtualBack_a_b_c_d[3] << endl;
    // 得到了 ax + by + cz + d = 0 方程 可用 系数

}
float CircleDemo::imul_a_a(float a){
    // 只管平方的话 这个func简单
    return a * a;
}

void CircleDemo::freshCircleAxis(){

    freshGoX();freshGoY();freshGoDEEP();

    freshTiltAxis(); // 刷新 倾斜轴
    freshParallelAxis(); // 刷新 平行轴
}
void CircleDemo::drawCircleAxis(ScreenDemo *ScreenEye) {
    if(debugLine != 2)return;
    drawTiltAxis(ScreenEye); // 画倾斜轴
    drawParallelAxis(ScreenEye); // 画平行轴
}
void CircleDemo::freshGoX(){
    toX.dx = (tblrXYZ.rtSet.x - tblrXYZ.ltSet.x) / squareEdge;
    toX.dy = (tblrXYZ.rtSet.y - tblrXYZ.ltSet.y) / squareEdge;
    toX.dz = (tblrXYZ.rtSet.z - tblrXYZ.ltSet.z) / squareEdge;
}
void CircleDemo::freshGoY(){
    toY.dx = (tblrXYZ.lbSet.x - tblrXYZ.ltSet.x) / squareEdge;
    toY.dy = (tblrXYZ.lbSet.y - tblrXYZ.ltSet.y) / squareEdge;
    toY.dz = (tblrXYZ.lbSet.z - tblrXYZ.ltSet.z) / squareEdge;
}
void CircleDemo::freshGoDEEP() {
    toDEEP.dx = (tblrXYZ.center.x - tblrXYZ.centerTip.x) / squareDepth;
    toDEEP.dy = (tblrXYZ.center.y - tblrXYZ.centerTip.y) / squareDepth;
    toDEEP.dz = (tblrXYZ.center.z - tblrXYZ.centerTip.z) / squareDepth;
}
glm::vec3 CircleDemo::goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * toX.dx;
    _srcXYZ.y = _srcXYZ.y + _move * toX.dy;
    _srcXYZ.z = _srcXYZ.z + _move * toX.dz;
    return _srcXYZ;
}
glm::vec3 CircleDemo::goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * toY.dx;
    _srcXYZ.y = _srcXYZ.y + _move * toY.dy;
    _srcXYZ.z = _srcXYZ.z + _move * toY.dz;
    return _srcXYZ;
}
glm::vec3 CircleDemo::goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * toDEEP.dx;
    _srcXYZ.y = _srcXYZ.y + _move * toDEEP.dy;
    _srcXYZ.z = _srcXYZ.z + _move * toDEEP.dz;
    return _srcXYZ;
}
void CircleDemo::freshTiltAxis(){
    // 中
    tiltAxis3D[0] = tblrXYZ.center;
    // x轴
    tiltAxis3D[1].x = tblrXYZ.center.x + toX.dx * squareEdge; // 数轴长度 看宽
    tiltAxis3D[1].y = tblrXYZ.center.y + toX.dy * squareEdge;
    tiltAxis3D[1].z = tblrXYZ.center.z + toX.dz * squareEdge;
    // y轴
    tiltAxis3D[2].x = tblrXYZ.center.x + toY.dx * squareEdge;
    tiltAxis3D[2].y = tblrXYZ.center.y + toY.dy * squareEdge;
    tiltAxis3D[2].z = tblrXYZ.center.z + toY.dz * squareEdge;
    // z轴
    tiltAxis3D[3].x = tblrXYZ.center.x + toDEEP.dx * squareEdge;
    tiltAxis3D[3].y = tblrXYZ.center.y + toDEEP.dy * squareEdge;
    tiltAxis3D[3].z = tblrXYZ.center.z + toDEEP.dz * squareEdge;
}

void CircleDemo::freshParallelAxis(){
    // 中
    parallelAxis3D[0] = tblrXYZ.center;
    // x轴
    parallelAxis3D[1].x = tblrXYZ.center.x + squareEdge; // 数轴长度 看宽
    parallelAxis3D[1].y = tblrXYZ.center.y;
    parallelAxis3D[1].z = tblrXYZ.center.z;
    // y轴
    parallelAxis3D[2].x = tblrXYZ.center.x;
    parallelAxis3D[2].y = tblrXYZ.center.y + squareEdge;
    parallelAxis3D[2].z = tblrXYZ.center.z;
    // z轴
    parallelAxis3D[3].x = tblrXYZ.center.x;
    parallelAxis3D[3].y = tblrXYZ.center.y;
    parallelAxis3D[3].z = tblrXYZ.center.z + squareEdge;
}

void CircleDemo::drawTiltAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴
    tiltAxis2D_f[0] = __3d2dGoCircle(ScreenEye, tiltAxis3D[0], nullptr);
    tiltAxis2D_f[1] = __3d2dGoCircle(ScreenEye, tiltAxis3D[1], nullptr);
    tiltAxis2D_f[2] = __3d2dGoCircle(ScreenEye, tiltAxis3D[2], nullptr);
    tiltAxis2D_f[3] = __3d2dGoCircle(ScreenEye, tiltAxis3D[3], nullptr);


//    BGR3f _green;
//    _green.setBGR(0x62a120,1);// 翠绿
//    BGR3f _blue;
//    _blue.setBGR(0xb9902f,1);// 云山蓝
//    BGR3f _yellow;
//    _yellow.setBGR(0x0ea4d9,1);// 芥黄
    float _color[3];


    _color[0]=0.12549019607843137;_color[1]=0.6313725490196078;_color[2]=0.3843137254901961;
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[1].x,tiltAxis2D_f[1].y,
                                  _color,screenNear);


    _color[0]=0.1843137254901961;_color[1]=0.5647058823529412;_color[2]=0.7254901960784313;
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[2].x,tiltAxis2D_f[2].y,
                                  _color,screenNear);


    _color[0]=0.8509803921568627;_color[1]=0.6431372549019608;_color[2]=0.054901960784313725;

    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[3].x,tiltAxis2D_f[3].y,
                                  _color,screenNear);
}

void CircleDemo::drawParallelAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴
    parallelAxis2D_f[0] = __3d2dGoCircle(ScreenEye, parallelAxis3D[0], nullptr);
    parallelAxis2D_f[1] = __3d2dGoCircle(ScreenEye, parallelAxis3D[1], nullptr);
    parallelAxis2D_f[2] = __3d2dGoCircle(ScreenEye, parallelAxis3D[2], nullptr);
    parallelAxis2D_f[3] = __3d2dGoCircle(ScreenEye, parallelAxis3D[3], nullptr);

    float _color[3];

    _color[0]=1.f;_color[1]=1.f;_color[2]=1.f;
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  parallelAxis2D_f[0].x,parallelAxis2D_f[0].y,
                                  parallelAxis2D_f[1].x,parallelAxis2D_f[1].y,
                                  _color,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  parallelAxis2D_f[0].x,parallelAxis2D_f[0].y,
                                  parallelAxis2D_f[2].x,parallelAxis2D_f[2].y,
                                  _color,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  parallelAxis2D_f[0].x,parallelAxis2D_f[0].y,
                                  parallelAxis2D_f[3].x,parallelAxis2D_f[3].y,
                                  _color,screenNear);

}
/*
// 向量归一化
void normalize(float v[3]) {
    float len = glm::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    v[0] /= len;
    v[1] /= len;
    v[2] /= len;
}

// 向量叉乘
void cross(float a[3], float b[3], float result[3]) {
    result[0] = a[1]*b[2] - a[2]*b[1];
    result[1] = a[2]*b[0] - a[0]*b[2];
    result[2] = a[0]*b[1] - a[1]*b[0];
}

// 向量点乘
float dot(float a[3], float b[3]) {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}

// 矩阵乘法（4x4矩阵）
void multiplyMatrix(float m[16], float v[4], float result[4]) {
    for(int i=0; i<4; i++) {
        result[i] = 0;
        for(int j=0; j<4; j++) {
            result[i] += m[i*4+j] * v[j];
        }
    }
}

void buildLocalFrame(float normal[3], float localX[3], float localY[3]) {
    normalize(normal); // Z轴
    float temp[3] = {1,0,0}; // 任意非平行向量
    if(fabs(dot(temp, normal)) > 0.9) temp[0] = 0; // 避免共线
    cross(temp, normal, localX);
    normalize(localX); // X轴
    cross(normal, localX, localY); // Y轴
}

void buildViewMatrix(float eye[3], float localFrame[3][3], float mat[16]) {
    // 构建4x4变换矩阵
    for(int i=0; i<3; i++){
        mat[i*4] = localFrame[i][0];
        mat[i*4+1] = localFrame[i][1];
        mat[i*4+2] = localFrame[i][2];
        mat[i*4+3] = -dot(localFrame[i], eye);
    }
    mat[12] = mat[13] = mat[14] = 0; // 第四行
    mat[15] = 1;
}

void computeKeyPoints(float radius, float invRot[16], float points[4][3]) {
    const float base[4][3] = {{1,0,0}, {0,1,0}, {-1,0,0}, {0,-1,0}};
    for(int i=0; i<4; i++){
        float v[4] = {base[i][0]*radius, base[i][1]*radius, base[i][2]*radius, 1};
        multiplyMatrix(invRot, v, v); // 逆向旋转
        memcpy(points[i], v, sizeof(float)*3);
    }
}

void findExtremumPoints(float points[4][3], float eyeDir[3], int indices[4]) {
    float maxProj = -FLT_MAX, minProj = FLT_MAX;
    for(int i=0; i<4; i++){
        float proj = dot(points[i], eyeDir);
        if(proj > maxProj) { indices[0] = i; maxProj = proj; } // 最近点
        if(proj < minProj) { indices[1] = i; minProj = proj; } // 最远点
    }
    // 找相位差90°的点（取剩余两点）
    indices[2] = (indices[0]+1)%4;
    indices[3] = (indices[0]+3)%4;
}
*/
