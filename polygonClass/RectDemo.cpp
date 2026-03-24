//
// Created by iceoc0 on 2024/10/31.
//

#include "RectDemo.h"
//#include <cmath>

struct modeRect{
    char now;char a;char b;char d;
};
extern void* mode_ptr;
modeRect mode_ = *((modeRect*)mode_ptr);

extern void* settled_ptr; // 全局设置的结构体指针
struct _settledRect{
    int _width;
    int _height;
    int _deep;

};
_settledRect* settled_ = (_settledRect*)settled_ptr;
const int screenWidth4 = settled_-> _width;
const int screenHeight4 = settled_-> _height;
const int screenDeep4 = settled_-> _deep;

extern void* _3d_2d_go_void_ptr;
// struct _3d_2d_go_rect{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, float *, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_ad)(ScreenDemo*, float, float, float);
// };
glm::vec2 (*__3d2dGoRect)(ScreenDemo*, glm::vec3, glm::vec3*) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2dRect)(ScreenDemo*, float, float, float) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d; // 模式1 用自己的不行



// malloc一个超级结构体 RectDemo
RectDemo::RectDemo(glm::vec3 _lt_xyz, glm::vec3 _rt_xyz, glm::vec3 _rb_xyz, glm::vec3 _lb_xyz,
                   glm::vec3 _center_xyz, glm::vec3 _centerTip_xyz, int _type):PolygonBase(_type)
{
//    if (std::isnan(_lt_xyz.y) || std::isnan(_lt_xyz.x) || std::isnan(_lt_xyz.z)) {
//        throw std::invalid_argument("Invalid parameter: NaN detected");
//    }
//    if (std::isinf(_lt_xyz.y) || std::isinf(_lt_xyz.x) || std::isinf(_lt_xyz.z)) {
//        throw std::invalid_argument("Invalid parameter: Infinity detected");
//    }
    debugLine = 0;
    _init_main(_lt_xyz, _rt_xyz, _rb_xyz, _lb_xyz, _center_xyz, _centerTip_xyz,_type);
}
RectDemo::RectDemo(glm::vec3 _lt_xyz, glm::vec3 _rt_xyz, glm::vec3 _rb_xyz, glm::vec3 _lb_xyz,
                   glm::vec3 _center_xyz, glm::vec3 _centerTip_xyz, int _type,unsigned char _debug_):PolygonBase(_type)
{

//    printf("-lt: %f %f %f\n" ,_lt_xyz.y,_lt_xyz.x ,_lt_xyz.z );
//    printf("-rt: %f %f %f\n" ,_rt_xyz.y,_rt_xyz.x ,_rt_xyz.z );
//    printf("-rb: %f %f %f\n" ,_rb_xyz.y,_rb_xyz.x ,_rb_xyz.z );
//    printf("-lb: %f %f %f\n" ,_lb_xyz.y,_lb_xyz.x ,_lb_xyz.z );
//    printf("-center: %f %f %f\n" ,_center_xyz.y,_center_xyz.x ,_center_xyz.z );
//    printf("-centerTip: %f %f %f\n" ,_centerTip_xyz.y,_centerTip_xyz.x ,_centerTip_xyz.z );

    debugLine = _debug_;
//    printf("debugLine:%hd\n", debugLine);
    _init_main(_lt_xyz, _rt_xyz, _rb_xyz, _lb_xyz, _center_xyz, _centerTip_xyz,_type);
}
void RectDemo::_init_main(glm::vec3& _lt_xyz, glm::vec3& _rt_xyz, glm::vec3& _rb_xyz,glm::vec3& _lb_xyz,
                          glm::vec3& _center_xyz, glm::vec3& _centerTip_xyz, int _type) {
//    PolygonBase::type_ = _type; // 矩形

    tblrXYZ.lt.x = _lt_xyz.x;
    tblrXYZ.lt.y = _lt_xyz.y;
    tblrXYZ.lt.z = _lt_xyz.z;

    tblrXYZ.rt.x = _rt_xyz.x;
    tblrXYZ.rt.y = _rt_xyz.y;
    tblrXYZ.rt.z = _rt_xyz.z;

    tblrXYZ.rb.x = _rb_xyz.x;
    tblrXYZ.rb.y = _rb_xyz.y;
    tblrXYZ.rb.z = _rb_xyz.z;

    tblrXYZ.lb.x = _lb_xyz.x;
    tblrXYZ.lb.y = _lb_xyz.y;
    tblrXYZ.lb.z = _lb_xyz.z;

    tblrXYZ.center.x = _center_xyz.x; // 中心点
    tblrXYZ.center.y = _center_xyz.y;
    tblrXYZ.center.z = _center_xyz.z;

    tblrXYZ.centerTip.x = _centerTip_xyz.x; // 中心点的尖端
    tblrXYZ.centerTip.y = _centerTip_xyz.y;
    tblrXYZ.centerTip.z = _centerTip_xyz.z;

    // 相对于 世界坐标轴 同距
    tblrXYZ_unchange.lt.x = _lt_xyz.x;
    tblrXYZ_unchange.lt.y = _lt_xyz.y;
    tblrXYZ_unchange.lt.z = _lt_xyz.z;

    tblrXYZ_unchange.rt.x = _rt_xyz.x;
    tblrXYZ_unchange.rt.y = _rt_xyz.y;
    tblrXYZ_unchange.rt.z = _rt_xyz.z;

    tblrXYZ_unchange.rb.x = _rb_xyz.x;
    tblrXYZ_unchange.rb.y = _rb_xyz.y;
    tblrXYZ_unchange.rb.z = _rb_xyz.z;

    tblrXYZ_unchange.lb.x = _lb_xyz.x;
    tblrXYZ_unchange.lb.y = _lb_xyz.y;
    tblrXYZ_unchange.lb.z = _lb_xyz.z;

    tblrXYZ_unchange.center.x = _center_xyz.x; // 中心点
    tblrXYZ_unchange.center.y = _center_xyz.y;
    tblrXYZ_unchange.center.z = _center_xyz.z;

    tblrXYZ_unchange.centerTip.x = _centerTip_xyz.x; // 中心点的尖端
    tblrXYZ_unchange.centerTip.y = _centerTip_xyz.y;
    tblrXYZ_unchange.centerTip.z = _centerTip_xyz.z;
//    angleXYZ = {0.0F, 0.0F, 0.0F}; // 初始角度

    frontColor_rgb01[0] = 1.f; // 无颜色默认
    frontColor_rgb01[1] = 1.f;
    frontColor_rgb01[2] = 1.f;
    backColor_rgb01[0] = 0.4f; // 无颜色默认
    backColor_rgb01[1] = 0.4f;
    backColor_rgb01[2] = 0.4f;


    centerLongist = glm::distance(tblrXYZ.lt, tblrXYZ.rb) / 2.0F; // 长轴长度

    rectWidth = glm::distance(tblrXYZ.lt, tblrXYZ.rt); // 宽度
    rectHeight = glm::distance(tblrXYZ.lt, tblrXYZ.lb); // 高度
    rectDepth = glm::distance(tblrXYZ.center, tblrXYZ.centerTip); // 深度
//    printf("--lt: %f %f %f\n" ,_lt_xyz.y,_lt_xyz.x ,_lt_xyz.z );
//    printf("--rt: %f %f %f\n" ,_rt_xyz.y,_rt_xyz.x ,_rt_xyz.z );
//    printf("--rb: %f %f %f\n" ,_rb_xyz.y,_rb_xyz.x ,_rb_xyz.z );
//    printf("--lb: %f %f %f\n" ,_lb_xyz.y,_lb_xyz.x ,_lb_xyz.z );
//    printf("--center: %f %f %f\n" ,_center_xyz.y,_center_xyz.x ,_center_xyz.z );
//    printf("--centerTip: %f %f %f\n" ,_centerTip_xyz.y,_centerTip_xyz.x ,_centerTip_xyz.z );

//      printf("~~矩形中心最远点距离：%f\n", centerLongist);
}



void RectDemo::Draw_Tick(ScreenDemo* ScreenEye){
    _first = true;
    //glm::vec3 nowEyeCenter = ScreenEye->tblrXYZ.centerTip;

    bool all2Dleft = tblrXY_f[0].x < 0.f && tblrXY_f[1].x < 0.f &&
                     tblrXY_f[2].x < 0.f && tblrXY_f[3].x < 0.f;
    bool all2Dright = tblrXY_f[0].x > (float)screenWidth4 && tblrXY_f[1].x > (float)screenWidth4 &&
                      tblrXY_f[2].x > (float)screenWidth4 && tblrXY_f[3].x > (float)screenWidth4;
    bool all2Dtop = tblrXY_f[0].y < 0.f && tblrXY_f[1].y < 0.f &&
                    tblrXY_f[2].y < 0.f && tblrXY_f[3].y < 0.f;
    bool all2Dbottom = tblrXY_f[0].y > (float)screenHeight4 && tblrXY_f[1].y > (float)screenHeight4 &&
                       tblrXY_f[2].y > (float)screenHeight4 && tblrXY_f[3].y > (float)screenHeight4;
    bool corner2DoutOfScreen = all2Dleft || all2Dright || all2Dtop || all2Dbottom;
    // 0  1  2  3  4      5
    // lt rt rb lb center centerTip
    bool cornerClose2Eye = virtual_tblrXYZ[4].z + ScreenEye->rectDepth < 0.1F;

    glm::vec3 startEyeCenter = {screenWidth4 / 2.0f, screenHeight4 / 2.0f, (float)-screenDeep4};
    // 自身斜彩轴



     // 斜视角 上下抬头低头
        if(!corner2DoutOfScreen && !cornerClose2Eye){ // 眼心距>100 才渲染
            goto drawRect;
        }else {
//            cout << "屏幕外 角在视点后" << endl;
            return;
        }

    drawRect:
    ax1_by1_cz1_d1(); // 共面算法 uvw 系数关系
    if(cTipEyeCloser(startEyeCenter)){ // 正面
//        setfillcolor(frontColor); ###
        // 面远 线近
        // 虚拟中心后点线
        if(debugLine==1){

                centerBack = {2 * tblrXYZ.center.x - tblrXYZ.centerTip.x,
                              2 * tblrXYZ.center.y - tblrXYZ.centerTip.y,
                              2 * tblrXYZ.center.z - tblrXYZ.centerTip.z
                };
                //cout << "~~centerBackXYZ: " << centerBackXYZ.y << " " << centerBackXYZ.x << " " << centerBackXYZ.z << endl;
                virtualCenterBackXY = __3d2dGoRect(ScreenEye, centerBack,
                                                   nullptr);

                float colorNow[3] = {1.f, 1.f, 1.f};
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              virtualCenterBackXY.x, virtualCenterBackXY.y,
                                              tblrXY_f[4].x, tblrXY_f[4].y,
                                              colorNow,screenNear);


        }


        if(debugLine==1){// 还要外边线
//            _fillRectangle3D(ScreenEye,true);
            _solidRectangle2D(ScreenEye,true);

            //solidpolygon(tblrXY_l,4);

        }else{
//            _solidRectangle3D(ScreenEye,true);
            _solidRectangle2D(ScreenEye,true);

            //solidpolygon(tblrXY_l,4);
        }

        if(debugLine==1) {
//            line(tblrXY_l[0].x, tblrXY_l[0].y, tblrXY_l[5].x, tblrXY_l[5].y); // 四角与中突线
//            line(tblrXY_l[1].x, tblrXY_l[1].y, tblrXY_l[5].x, tblrXY_l[5].y);
//            line(tblrXY_l[2].x, tblrXY_l[2].y, tblrXY_l[5].x, tblrXY_l[5].y);
//            line(tblrXY_l[3].x, tblrXY_l[3].y, tblrXY_l[5].x, tblrXY_l[5].y);
//            setlinecolor(0xaae8f7); // 杏仁黄 ###
//            line(tblrXY_l[4].x, tblrXY_l[4].y, tblrXY_l[5].x, tblrXY_l[5].y); // 中点中突
            float colorNow[3] = {1.f, 1.f, 1.f};
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[5].x, tblrXY_f[5].y,
                                          tblrXY_f[0].x, tblrXY_f[0].y,
                                          colorNow,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[5].x, tblrXY_f[5].y,
                                          tblrXY_f[1].x, tblrXY_f[1].y,
                                          colorNow,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[5].x, tblrXY_f[5].y,
                                          tblrXY_f[2].x, tblrXY_f[2].y,
                                          colorNow,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[5].x, tblrXY_f[5].y,
                                          tblrXY_f[3].x, tblrXY_f[3].y,
                                          colorNow,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[5].x, tblrXY_f[5].y,
                                          tblrXY_f[4].x, tblrXY_f[4].y,
                                          colorNow,screenNear);

        }
    }
    else{ // 背面
//        setfillcolor(backColor); ###
        // 面近 线远
        if(debugLine==1) {
//            line(tblrXY_l[0].x, tblrXY_l[0].y, tblrXY_l[5].x, tblrXY_l[5].y); // 四角与中突线
//            line(tblrXY_l[1].x, tblrXY_l[1].y, tblrXY_l[5].x, tblrXY_l[5].y);
//            line(tblrXY_l[2].x, tblrXY_l[2].y, tblrXY_l[5].x, tblrXY_l[5].y);
//            line(tblrXY_l[3].x, tblrXY_l[3].y, tblrXY_l[5].x, tblrXY_l[5].y);
//            setlinecolor(0xaae8f7); // 杏仁黄 ###
//            line(tblrXY_l[4].x, tblrXY_l[4].y, tblrXY_l[5].x, tblrXY_l[5].y); // 中点中突
            float colorNow[3] = {1.f,1.f,1.f};
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[5].x, tblrXY_f[5].y,
                                          tblrXY_f[0].x, tblrXY_f[0].y,
                                          colorNow,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[5].x, tblrXY_f[5].y,
                                          tblrXY_f[1].x, tblrXY_f[1].y,
                                          colorNow,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[5].x, tblrXY_f[5].y,
                                          tblrXY_f[2].x, tblrXY_f[2].y,
                                          colorNow,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[5].x, tblrXY_f[5].y,
                                          tblrXY_f[3].x, tblrXY_f[3].y,
                                          colorNow,screenNear);
            ScreenDemo::line2ScreenBuffer(ScreenEye,
                                          tblrXY_f[5].x, tblrXY_f[5].y,
                                          tblrXY_f[4].x, tblrXY_f[4].y,
                                          colorNow,screenNear);

        }


        _solidRectangle2D(ScreenEye,false);


        if(debugLine==1) {

                centerBack = 2.f * tblrXYZ.center - tblrXYZ.centerTip;

                //cout << "~~centerBackXYZ: " << centerBackXYZ.y << " " << centerBackXYZ.x << " " << centerBackXYZ.z << endl;
                virtualCenterBackXY = __3d2dGoRect(ScreenEye, centerBack,nullptr);
                float colorNow[3] = {1.f, 1.f, 1.f};
                ScreenDemo::line2ScreenBuffer(ScreenEye,
                                              virtualCenterBackXY.x, virtualCenterBackXY.y,
                                              tblrXY_f[4].x, tblrXY_f[4].y,
                                              colorNow,screenNear);


        }

    }
    if(debugLine==2){
        freshRectAxis(); // 更新坐标轴 info
        //drawCircleAxis(ScreenEye); // 画坐标轴
    }
    //printf("lb点距屏幕%f\n",points2EyeBack.lbEye);
}


void RectDemo::drawRectOnly(ScreenDemo* ScreenEye){
    // glm::vec3 eyeCenter = ScreenEye->getCenterTip();

        if(tblrXYZ.lt.z + ScreenEye->rectDepth > 0.f && tblrXYZ.rt.z + ScreenEye->rectDepth > 0.f &&
                tblrXYZ.rb.z + ScreenEye->rectDepth > 0.f && tblrXYZ.lb.z + ScreenEye->rectDepth > 0.f){

        }else{
            return;
        }



//    setlinecolor(frontColor); ###

//    POINTl tblrCornerUp[4];
//    tblrCornerUp[0].x = tblrXY_l[0].x; tblrCornerUp[0].y = tblrXY_l[0].y; // Xl
//    tblrCornerUp[1].x = tblrXY_l[1].x; tblrCornerUp[1].y = tblrXY_l[1].y; // Xr
//    tblrCornerUp[2].x = tblrXY_l[2].x; tblrCornerUp[2].y = tblrXY_l[2].y; // Yb
//    tblrCornerUp[3].x = tblrXY_l[3].x; tblrCornerUp[3].y = tblrXY_l[3].y; // Yt
//    polygon(tblrCornerUp, 4); // 原点为左上角 ###
    float colorNow[3] = {1.f, 1.f, 1.f};
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_f[0].x, tblrXY_f[0].y,
                                  tblrXY_f[1].x, tblrXY_f[1].y,
                                  colorNow,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_f[1].x, tblrXY_f[1].y,
                                  tblrXY_f[2].x, tblrXY_f[2].y,
                                  colorNow,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_f[2].x, tblrXY_f[2].y,
                                  tblrXY_f[3].x, tblrXY_f[3].y,
                                  colorNow,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_f[3].x, tblrXY_f[3].y,
                                  tblrXY_f[0].x, tblrXY_f[0].y,
                                  colorNow,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_down[0].x, tblrXY_down[0].y,
                                  tblrXY_down[1].x, tblrXY_down[1].y,
                                  colorNow,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_down[1].x, tblrXY_down[1].y,
                                  tblrXY_down[2].x, tblrXY_down[2].y,
                                  colorNow,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_down[2].x, tblrXY_down[2].y,
                                  tblrXY_down[3].x, tblrXY_down[3].y,
                                  colorNow,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_down[3].x, tblrXY_down[3].y,
                                  tblrXY_down[0].x, tblrXY_down[0].y,
                                  colorNow,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_f[0].x, tblrXY_f[0].y,
                                  tblrXY_down[0].x, tblrXY_down[0].y,
                                  colorNow,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_f[1].x, tblrXY_f[1].y,
                                  tblrXY_down[1].x, tblrXY_down[1].y,
                                  colorNow,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_f[2].x, tblrXY_f[2].y,
                                  tblrXY_down[2].x, tblrXY_down[2].y,
                                  colorNow,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tblrXY_f[3].x, tblrXY_f[3].y,
                                  tblrXY_down[3].x, tblrXY_down[3].y,
                                  colorNow,screenNear);


}

void RectDemo::_solidRectangle2D(ScreenDemo* ScreenEye, bool onFront){


//    horizontalDeepCalc(); // 2D y lx rx Pos 完了 再 2D y lx rx deep

    // 默认 0 lt 1 rt 2 rb 3 lb
    PolygonBase::fresh2D_scanRows_4(tblrXY_f[0],
                                    tblrXY_f[1],
                                    tblrXY_f[2],
                                    tblrXY_f[3], &lineScanFillColor,type_);
    pixel2ScreenDeep.clear();

    int isFIrst = 0;
    glm::vec3 startEye = {(float)screenWidth4/2.0f, (float)screenHeight4/2.0f, (float)-screenDeep4}; // 初始化一次 (600,400,-1000)
    freshDeepFarNear(); // 刷新最远最近深度
    for(auto& _linePosInfo : lineScanFillColor){
//        if(std::isnan(_linePosInfo.lx)){
//            cerr << "矩形 lineScanFillColor.lx:" << _linePosInfo.lx <<
//                 " is nan" << endl;
//            continue;
//        }
//        if(std::isnan(_linePosInfo.rx)){
//            cerr << "矩形 lineScanFillColor.rx:" << _linePosInfo.rx <<
//                 " is nan" << endl;
//            continue;
//        }
        if(_linePosInfo.rx < _linePosInfo.lx){
            println(stderr, "矩形 lineScanFillColor.rx:" , _linePosInfo.rx ,
                 " < lineScanFillColor.lx:" , _linePosInfo.lx);
            continue;
        }

        rowPixelDeep4 rowDeepInfo;
        rowDeepInfo.y = _linePosInfo.y; // 本行 y
        rowDeepInfo.pixelDeeps.clear(); // 本行 x deep 空
        for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){

            //float deepNow = getEyeDeepbyXY(nowX, _linePosInfo.y);
            float deepNow = getScreenDeepByXY(nowX, _linePosInfo.y);
            if(deepNow < screenNear){
//                cerr << "deepNow:" << deepNow << " < screenNear:" << screenNear << endl;
                deepNow = screenNear; // 太近就设为最低深度
            }else if(deepNow > screenFar){
//                cerr << "deepNow:" << deepNow << " > screenFar:" << screenFar << endl;
                deepNow = screenFar; // 太远就设为最高深度
            }

            rowDeepInfo.pixelDeeps.push_back({nowX, deepNow}); // 本行 x deep

        }
        pixel2ScreenDeep.push_back(rowDeepInfo);


    }


    for(auto& _linfDeepInfo : pixel2ScreenDeep){
        for(int i=0;i<_linfDeepInfo.pixelDeeps.size()/*-1*/;i++){
            int nowX = _linfDeepInfo.pixelDeeps[i].x;
            float nowDeep = _linfDeepInfo.pixelDeeps[i].eyeDeep;

            if(onFront){
                //cout << "debugLine" << (int)debugLine << endl;
                if(debugLine==1) {
                    int colorNow = black2ColorfulScreenDeep(nowDeep);

                    BGR3f colorNow1;
                    colorNow1.setBGR(colorNow,1);
//                    glPointSize(1.0f); // 点大小
//                    glBegin(GL_POINTS);
//                    glColor3f(colorNow1.r1,colorNow1.g1,colorNow1.b1);
//                    glVertex2f(nowX,_linfDeepInfo.y);
//                    glEnd();
                    float _color_[3] = {colorNow1.r1,colorNow1.g1,colorNow1.b1};
                    ScreenEye->putPixel(nowX,static_cast<int>(_linfDeepInfo.y),_color_,nowDeep,(PolygonBase*)this);

                }else{
                    ScreenEye->putPixel(nowX,_linfDeepInfo.y,frontColor_rgb01,nowDeep,(PolygonBase*)this);
//                    glPointSize(1.0f); // 点大小
//                    glBegin(GL_POINTS);
//                    glColor3f(frontColor_rgb01[0],frontColor_rgb01[1],frontColor_rgb01[2]);
//                    glVertex2f(nowX,_linfDeepInfo.y);
//                    glEnd();
                }
            }
            else{
                ScreenEye->putPixel(nowX,static_cast<int>(_linfDeepInfo.y),backColor_rgb01,nowDeep,(PolygonBase*)this);
//                glPointSize(1.0f); // 点大小
//                glBegin(GL_POINTS);
//                glColor3f(backColor_rgb01[0],backColor_rgb01[1],backColor_rgb01[2]);
//                glVertex2f(nowX,_linfDeepInfo.y);
//                glEnd();
            }

        }
    }

    //_ScreenCacheFun->FlushBatchDraw_();cout << "扫描线填充完成。flush" << endl;

}

bool RectDemo::PolyScanClicked(int x,int y)
{     for(auto& _lineScanInfo : lineScanFillColor){
        if(y == _lineScanInfo.y && x >= _lineScanInfo.lx && x <= _lineScanInfo.rx){
            println("矩形被点击了！");
            return true; // 三角形被点击了！
        }
    }
    return false; // 三角形未被点击
}


void RectDemo::ax1_by1_cz1_d1(){
    // 计算两个边相量
    glm::vec3 lt2rt = virtual_tblrXYZ[0] - virtual_tblrXYZ[1];

    glm::vec3 lt2lb = virtual_tblrXYZ[0] - virtual_tblrXYZ[3];
    // 计算法向量
    glm::vec4 normal = {glm::cross(lt2rt, lt2lb), 0};
//    normal[0] = lt2rt.y * lt2lb.z - lt2rt.z * lt2lb.y; // 0*0 - 0*(-150) = 0
//    normal[1] = lt2rt.z * lt2lb.x - lt2rt.x * lt2lb.z; // 0*0 - (-200)*0 = 0
//    normal[2] = lt2rt.x * lt2lb.y - lt2rt.y * lt2lb.x; // -200*(-150) - 0*0 = 30000

    // 归一化法向量
    float magnitude = glm::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    normal[0] /= magnitude;
    normal[1] /= magnitude;
    normal[2] /= magnitude; // 法向量 立方体对角线单位一

    if(_backFont == -1.0f){
        normal[0] = -normal[0];
        normal[1] = -normal[1];
        normal[2] = -normal[2]; // 法向量 取反 ?
    }

    // ax + by + cz + d = 0
    // d = -ax1*x1 - by1*y1 - cz1*z1
    normal[3] = -normal[0] * virtual_tblrXYZ[0].x - normal[1] * virtual_tblrXYZ[0].y - normal[2] * virtual_tblrXYZ[0].z;

    // ax + by + cz + d = 0

    virtualBack_a_b_c_d = normal;

    // 得到了 共面方程 可用 系数

}
goLine32 RectDemo::eye2ScreenPixel_dxyz(float x, float y){
    glm::vec3 pixelXYZ = {x, y, 0.0f};
    glm::vec3 startEYE = {(float)screenWidth4/2.0f, (float)screenHeight4/2.0f, (float)-screenDeep4}; // 初始化一次 (600,400,-1000)
    //float pixel2eye_far = glm::distance(startEYE, pixelXYZ); // 计算像素点到屏幕中心的距离

    goLine32 rayGo1 = ScreenDemo::get_AgoB_direction3D(startEYE, pixelXYZ);
//    rayGo1._ = glm::normalize(pixelXYZ - startEYE); // 像素点到屏幕中心的向量

    return rayGo1; // 计算像素点到屏幕中心的向量
}
#ifdef MAYBE_UNUSED
glm::vec3 RectDemo::getEyeGoXYZbyXY(float x, float y){
    // 已知 眼xyz 步进xyz

    // 初始化一次 (600,400,-1000)
    glm::vec3 startEYE = {(float)screenWidth4/2.0f, (float)screenHeight4/2.0f, (float)-screenDeep4};
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
    glm::vec3 _eyeGoXYZ = {eyeGoPixel.dx * step,
                      eyeGoPixel.dy * step,
                      eyeGoPixel.dz * step};
    // 得到了 像素点的 xyz
    return _eyeGoXYZ;
}
float RectDemo::getEyeDeepbyXY(float x, float y){
    // 初始化一次 (600,400,-1000)

    glm::vec3 eyeGoXYZ = getEyeGoXYZbyXY(x, y);// 计算像素点到屏幕中心的距离
    float eyeDeep = glm::sqrt(eyeGoXYZ.x * eyeGoXYZ.x + eyeGoXYZ.y * eyeGoXYZ.y + eyeGoXYZ.z * eyeGoXYZ.z);
    return eyeDeep; // 计算像素点到屏幕中心的距离
}
#endif
float RectDemo::getScreenDeepByXY(float x, float y){
    // 初始化一次 (600,400,-1000)
    glm::vec3 startEYE = {(float)screenWidth4/2.0f, (float)screenHeight4/2.0f, (float)-screenDeep4};
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
//    glm::vec3 _eyeGoXYZ = {eyeGoPixel.dx * step,
//                         eyeGoPixel.dy * step,
//                         eyeGoPixel.dz * step};
    float pointScreenDeep = eyeGoPixel.dz * step - screenDeep4; // 得到了 像素点的 xyz

//    cout << "pointScreenDeep:" << pointScreenDeep << endl;
    return pointScreenDeep; // 得到了 像素点的 xyz
}

void RectDemo::freshDeepFarNear(){
    float deepLT = virtual_tblrXYZ[0].z;
    float deepRT = virtual_tblrXYZ[1].z;
    float deepRB = virtual_tblrXYZ[2].z;
    float deepLB = virtual_tblrXYZ[3].z;
    float fourPointsDeep[4] = {deepLT, deepRT, deepRB, deepLB};
    float deepFar = fourPointsDeep[0], deepNear = fourPointsDeep[0];
    for(int i=0;i<4;i++){
        if(fourPointsDeep[i] > deepFar){ // 比我大
            deepFar = fourPointsDeep[i];
        }
        else if(fourPointsDeep[i] < deepNear){ // 比我小  比大的更大 不可能比小得更小
            deepNear = fourPointsDeep[i];
        }
    }
    screenFar = deepFar; // 记录一下
    screenNear = deepNear; // 记录一下

}

int RectDemo::black2ColorfulScreenDeep(float deepNow){


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


    if(_first){
        //cout << "pointDeep:" << pointDeep << endl;
        _first = false;
    }
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

bool RectDemo::XYonScreen_f(float x, float y){
    int x_i = (int)roundf(x), y_i = (int)roundf(y);
    if(x_i <0 || x_i > screenWidth4){
        println(stderr, "x:",x," out of range");
        return false;
    }
    if(y_i <0 || y_i > screenHeight4){
        println(stderr, "y:",y," out of range");
        return false;
    }
    return true;
}


int RectDemo::deepColorOf3DPoint(ScreenDemo* ScreenEye, float deepNow){
    float deepBetween = screenFar - screenNear; // 两端深度差
    float B = frontColor_rgb01[2] * 255.f;
    float G = frontColor_rgb01[1] * 255.f; // 右移 保留后两位
    float R = frontColor_rgb01[0] * 255.f; // 保留后两位

    float dB = (255.0f-B) / deepBetween; // 最深和最近的差 颜色变化
    float dG = (255.0f-G) / deepBetween;
    float dR = (255.0f-R) / deepBetween; // 白 255 - 黑 无 --------------------------------------
    float pointDeep = deepNow;
    float ofFarthest = screenFar - pointDeep; // 对于 最深和当前的深度差
//    float ofNearest = pointDeep - screenNear; // 对于 最深和当前的深度差

//    float nowB = (B + ofNearest * dB) <= 255.0f ? (B + ofNearest * dB) : 255.0f;
//    float nowG = (G + ofNearest * dG) <= 255.0f ? (G + ofNearest * dG) : 255.0f;
//    float nowR = (R + ofNearest * dR) <= 255.0f ? (R + ofNearest * dR) : 255.0f; // 白 255 - 黑 无 ---
    float nowB = 255.0f - ofFarthest * dB;
    float nowG = 255.0f - ofFarthest * dG;
    float nowR = 255.0f - ofFarthest * dR; // 白 255 - 黑 无 --------------------------------------
    int color = ((int)roundf(nowB) << 16) + ((int)roundf(nowG) << 8) + (int)roundf(nowR);
    color = (color & 0x00ffffff); // 最左一字节 00
    //cout << "color final:" << color << endl;
    return color;
}


void RectDemo::switchDebug(){
    if(debugLine==0){
        debugLine = 1;
        println("rectangle debugLine 1");
    }else if(debugLine==1){
        debugLine = 2;
        println("rectangle debugLine 2");
    }else{
        debugLine = 0;
        println("rectangle debugLine 0");
    }
}
void RectDemo::setColor(int NormalColor1) {

    BGR3f colorNow;
    colorNow.setBGR(NormalColor1,1);
    frontColor_rgb01[0] = colorNow.r1;
    frontColor_rgb01[1] = colorNow.g1;
    frontColor_rgb01[2] = colorNow.b1;
}
void RectDemo::setBackColor(int backColor1){

    BGR3f colorNow;
    colorNow.setBGR(backColor1,1);
    backColor_rgb01[0] = colorNow.r1;
    backColor_rgb01[1] = colorNow.g1;
    backColor_rgb01[2] = colorNow.b1;
}




void RectDemo::setTBLRXY_f(glm::vec2 lt_XY, glm::vec2 rt_XY, glm::vec2 rb_XY, glm::vec2 lb_XY, glm::vec2 center_XY, glm::vec2 ctip_XY){

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

}
void RectDemo::setTBLRXY_Down(glm::vec2 tblr0, glm::vec2 tblr1, glm::vec2 tblr2, glm::vec2 tblr3, glm::vec2 tblrC, glm::vec2 tblrCT){
    tblrXY_down[0].x = tblr0.x; // lt
    tblrXY_down[0].y = tblr0.y;
    tblrXY_down[1].x = tblr1.x; // rt
    tblrXY_down[1].y = tblr1.y;
    tblrXY_down[2].x = tblr2.x; // rb
    tblrXY_down[2].y = tblr2.y;
    tblrXY_down[3].x = tblr3.x; // lb
    tblrXY_down[3].y = tblr3.y;
    tblrXY_down[4].x = tblrC.x; // center
    tblrXY_down[4].y = tblrC.y;
    tblrXY_down[5].x = tblrCT.x; // centerTip
    tblrXY_down[5].y = tblrCT.y;
}
void RectDemo::setTBLRXYZ(glm::vec3 ltXYZ, glm::vec3 rtXYZ, glm::vec3 rbXYZ, glm::vec3 lbXYZ){

    tblrXYZ.lt.x = ltXYZ.x;
    tblrXYZ.lt.y = ltXYZ.y;
    tblrXYZ.lt.z = ltXYZ.z;

    tblrXYZ.rt.x = rtXYZ.x;
    tblrXYZ.rt.y = rtXYZ.y;
    tblrXYZ.rt.z = rtXYZ.z;

    tblrXYZ.rb.x = rbXYZ.x;
    tblrXYZ.rb.y = rbXYZ.y;
    tblrXYZ.rb.z = rbXYZ.z;

    tblrXYZ.lb.x = lbXYZ.x;
    tblrXYZ.lb.y = lbXYZ.y;
    tblrXYZ.lb.z = lbXYZ.z;

    tblrXYZ.center.x = (ltXYZ.x + rbXYZ.x) / 2.0f; // 中心点
    tblrXYZ.center.y = (ltXYZ.y + rbXYZ.y) / 2.0f;
    tblrXYZ.center.z = (ltXYZ.z + rbXYZ.z) / 2.0f;

    // 计算两个边相量
    glm::vec3 lt2rt = {ltXYZ.x - rtXYZ.x, ltXYZ.y - rtXYZ.y,  ltXYZ.z - rtXYZ.z};

    glm::vec3 lt2lb = {ltXYZ.x - lbXYZ.x, ltXYZ.y - lbXYZ.y, ltXYZ.z - lbXYZ.z};
    // 计算法向量
    float normal[3] = {0};
    normal[0] = lt2lb.y * lt2rt.z - lt2lb.z * lt2rt.y; // lt2lb左 lt2rt右
    normal[1] = lt2lb.z * lt2rt.x - lt2lb.x * lt2rt.z; // x→ y→ z→ x
    normal[2] = lt2lb.x * lt2rt.y - lt2lb.y * lt2rt.x; //

    // 归一化法向量
    float magnitude = glm::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    normal[0] /= magnitude;
    normal[1] /= magnitude;
    normal[2] /= magnitude; // 法向量 立方体对角线单位一

    if(_backFont == 1.0f){
        normal[0] *= -1.0f;
        normal[1] *= -1.0f;
        normal[2] *= -1.0f; // 法向量 取反 ?
    }

    tblrXYZ.centerTip.x = tblrXYZ.center.x + normal[0] * 20.0f; // 中心点的尖端
    tblrXYZ.centerTip.y = tblrXYZ.center.y + normal[1] * 20.0f;
    tblrXYZ.centerTip.z = tblrXYZ.center.z + normal[2] * 20.0f;

}


bool RectDemo::cTipEyeCloser(glm::vec3 eyeCenter){

//    const float windowWidth = 1200.0F;
//    const float windowHeight = 800.0F;
//    const glm::vec3 eyeXYZ = {windowWidth / 2, windowHeight / 2, -100};

// 使用 刷新屏幕与几何面顶点2D坐标的函数 获得的虚拟依屏扶正点
    if(mode_.now == mode_.b){
        float cBackFarX = eyeCenter.x - (2*tblrXYZ.center.x-tblrXYZ.centerTip.x);
        float cBackFarY = eyeCenter.y - (2*tblrXYZ.center.y-tblrXYZ.centerTip.y);
        float cBackFarZ = eyeCenter.z - (2*tblrXYZ.center.z-tblrXYZ.centerTip.z); // virtualCenterBack

        float ctFarX = eyeCenter.x - tblrXYZ.centerTip.x;
        float ctFarY = eyeCenter.y - tblrXYZ.centerTip.y;
        float ctFarZ = eyeCenter.z - tblrXYZ.centerTip.z;

        float centerDistance = glm::sqrt(cBackFarX*cBackFarX + cBackFarY*cBackFarY + cBackFarZ*cBackFarZ);
        float centerTipDistance = glm::sqrt(ctFarX*ctFarX + ctFarY*ctFarY + ctFarZ*ctFarZ);

        if(centerDistance > centerTipDistance){
            return true;
        }
        else{
            return false;
        }
    }else{
        float cBackFarX = eyeCenter.x - (2*virtual_tblrXYZ[4].x-virtual_tblrXYZ[5].x);
        float cBackFarY = eyeCenter.y - (2*virtual_tblrXYZ[4].y-virtual_tblrXYZ[5].y);
        float cBackFarZ = eyeCenter.z - (2*virtual_tblrXYZ[4].z-virtual_tblrXYZ[5].z); // virtualCenterBack

        float ctFarX = eyeCenter.x - virtual_tblrXYZ[5].x;
        float ctFarY = eyeCenter.y - virtual_tblrXYZ[5].y;
        float ctFarZ = eyeCenter.z - virtual_tblrXYZ[5].z;

        float centerDistance = glm::sqrt(cBackFarX*cBackFarX + cBackFarY*cBackFarY + cBackFarZ*cBackFarZ);
        float centerTipDistance = glm::sqrt(ctFarX*ctFarX + ctFarY*ctFarY + ctFarZ*ctFarZ);

        if(centerDistance > centerTipDistance){
            return true;
        }
        else{
            return false;
        }
    }


}
glm::vec3 RectDemo::getCenter() {
    return tblrXYZ.center;
}
glm::vec3 RectDemo::getVirtualCenter() { // center
    return virtual_tblrXYZ[4];
}
glm::vec3 RectDemo::getCenterTip(){
    return tblrXYZ.centerTip;
}
float RectDemo::getAvgeDeep(){
    return (screenFar + screenNear) / 2.0f;
}
void RectDemo::freshRectAxis(){

    freshGoX();freshGoY();freshGoDEEP();

    freshTiltAxis(); // 刷新 倾斜轴
    freshParallelAxis(); // 刷新 平行轴
}
void RectDemo::drawRectAxis(ScreenDemo *ScreenEye) {
    if(debugLine != 2)return;
    drawTiltAxis(ScreenEye); // 画倾斜轴
    drawParallelAxis(ScreenEye); // 画平行轴
}
void RectDemo::freshGoX(){
    toX.dx = (tblrXYZ.rt.x - tblrXYZ.lt.x) / rectWidth;
    toX.dy = (tblrXYZ.rt.y - tblrXYZ.lt.y) / rectWidth;
    toX.dz = (tblrXYZ.rt.z - tblrXYZ.lt.z) / rectWidth;
}
void RectDemo::freshGoY(){
    toY.dx = (tblrXYZ.lb.x - tblrXYZ.lt.x) / rectHeight;
    toY.dy = (tblrXYZ.lb.y - tblrXYZ.lt.y) / rectHeight;
    toY.dz = (tblrXYZ.lb.z - tblrXYZ.lt.z) / rectHeight;
}
void RectDemo::freshGoDEEP() {
    toDEEP.dx = (tblrXYZ.center.x - tblrXYZ.centerTip.x) / rectDepth;
    toDEEP.dy = (tblrXYZ.center.y - tblrXYZ.centerTip.y) / rectDepth;
    toDEEP.dz = (tblrXYZ.center.z - tblrXYZ.centerTip.z) / rectDepth;
}
glm::vec3 RectDemo::goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * toX.dx;
    _srcXYZ.y = _srcXYZ.y + _move * toX.dy;
    _srcXYZ.z = _srcXYZ.z + _move * toX.dz;
    return _srcXYZ;
}
glm::vec3 RectDemo::goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * toY.dx;
    _srcXYZ.y = _srcXYZ.y + _move * toY.dy;
    _srcXYZ.z = _srcXYZ.z + _move * toY.dz;
    return _srcXYZ;
}
glm::vec3 RectDemo::goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * toDEEP.dx;
    _srcXYZ.y = _srcXYZ.y + _move * toDEEP.dy;
    _srcXYZ.z = _srcXYZ.z + _move * toDEEP.dz;
    return _srcXYZ;
}
void RectDemo::freshTiltAxis(){
    // 中
    tiltAxis3D[0] = tblrXYZ.center;
    // x轴
    tiltAxis3D[1].x = tblrXYZ.center.x + toX.dx * rectWidth; // 数轴长度 看宽
    tiltAxis3D[1].y = tblrXYZ.center.y + toX.dy * rectWidth;
    tiltAxis3D[1].z = tblrXYZ.center.z + toX.dz * rectWidth;
    // y轴
    tiltAxis3D[2].x = tblrXYZ.center.x + toY.dx * rectWidth;
    tiltAxis3D[2].y = tblrXYZ.center.y + toY.dy * rectWidth;
    tiltAxis3D[2].z = tblrXYZ.center.z + toY.dz * rectWidth;
    // z轴
    tiltAxis3D[3].x = tblrXYZ.center.x + toDEEP.dx * rectWidth;
    tiltAxis3D[3].y = tblrXYZ.center.y + toDEEP.dy * rectWidth;
    tiltAxis3D[3].z = tblrXYZ.center.z + toDEEP.dz * rectWidth;
}

void RectDemo::freshParallelAxis(){
    // 中
    parallelAxis3D[0] = tblrXYZ.center;
    // x轴
    parallelAxis3D[1].x = tblrXYZ.center.x + rectWidth; // 数轴长度 看宽
    parallelAxis3D[1].y = tblrXYZ.center.y;
    parallelAxis3D[1].z = tblrXYZ.center.z;
    // y轴
    parallelAxis3D[2].x = tblrXYZ.center.x;
    parallelAxis3D[2].y = tblrXYZ.center.y + rectWidth;
    parallelAxis3D[2].z = tblrXYZ.center.z;
    // z轴
    parallelAxis3D[3].x = tblrXYZ.center.x;
    parallelAxis3D[3].y = tblrXYZ.center.y;
    parallelAxis3D[3].z = tblrXYZ.center.z + rectWidth;
}

void RectDemo::drawTiltAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴
    tiltAxis2D_f[0] = __3d2dGoRect(ScreenEye, tiltAxis3D[0], nullptr);
    tiltAxis2D_f[1] = __3d2dGoRect(ScreenEye, tiltAxis3D[1], nullptr);
    tiltAxis2D_f[2] = __3d2dGoRect(ScreenEye, tiltAxis3D[2], nullptr);
    tiltAxis2D_f[3] = __3d2dGoRect(ScreenEye, tiltAxis3D[3], nullptr);

//    BGR3f _green;
//    _green.setBGR(0x62a120,1);// 翠绿
//    BGR3f _blue;
//    _blue.setBGR(0xb9902f,1);// 云山蓝
//    BGR3f _yellow;
//    _yellow.setBGR(0x0ea4d9,1);// 芥黄
    float colorNow_[3] = {0.12549019607843137,0.6313725490196078,0.3843137254901961};
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[1].x,tiltAxis2D_f[1].y,
                                  colorNow_,screenNear);
    colorNow_[0] = 0.1843137254901961;colorNow_[1] = 0.5647058823529412;colorNow_[2] = 0.7254901960784313;
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[2].x,tiltAxis2D_f[2].y,
                                  colorNow_,screenNear);
    colorNow_[0] = 0.8509803921568627;colorNow_[1] = 0.6431372549019608;colorNow_[2] = 0.054901960784313725;
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[2].x,tiltAxis2D_f[2].y,
                                  colorNow_,screenNear);
//    glLineWidth(1.0f); // 线宽
//    glBegin(GL_LINES);
//
//    glColor3f(0.12549019607843137,0.6313725490196078,0.3843137254901961);
//    glVertex2f(tiltAxis2D_f[0].x,tiltAxis2D_f[0].y);
//    glVertex2f(tiltAxis2D_f[1].x,tiltAxis2D_f[1].y);
//
//    glColor3f(0.1843137254901961,0.5647058823529412,0.7254901960784313);
//    glVertex2f(tiltAxis2D_f[0].x,tiltAxis2D_f[0].y);
//    glVertex2f(tiltAxis2D_f[2].x,tiltAxis2D_f[2].y);
//
//    glColor3f(0.8509803921568627,0.6431372549019608,0.054901960784313725);
//    glVertex2f(tiltAxis2D_f[0].x,tiltAxis2D_f[0].y);
//    glVertex2f(tiltAxis2D_f[3].x,tiltAxis2D_f[3].y);
//    glEnd();
}

void RectDemo::drawParallelAxis(ScreenDemo* ScreenEye){

    // 中 x轴 y轴 z轴
    parallelAxis2D_f[0] = __3d2dGoRect(ScreenEye, parallelAxis3D[0], nullptr);
    parallelAxis2D_f[1] = __3d2dGoRect(ScreenEye, parallelAxis3D[1], nullptr);
    parallelAxis2D_f[2] = __3d2dGoRect(ScreenEye, parallelAxis3D[2], nullptr);
    parallelAxis2D_f[3] = __3d2dGoRect(ScreenEye, parallelAxis3D[3], nullptr);

    float colorNow_[3] = {1.f, 1.f, 1.f};
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[1].x,tiltAxis2D_f[1].y,
                                  colorNow_,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[2].x,tiltAxis2D_f[2].y,
                                  colorNow_,screenNear);
    ScreenDemo::line2ScreenBuffer(ScreenEye,
                                  tiltAxis2D_f[0].x,tiltAxis2D_f[0].y,
                                  tiltAxis2D_f[3].x,tiltAxis2D_f[3].y,
                                  colorNow_,screenNear);
//    glLineWidth(1.0f); // 线宽
//    glBegin(GL_LINES);
//
//    glColor3f(1.f, 1.f, 1.f);
//    glVertex2f(parallelAxis2D_f[0].x,parallelAxis2D_f[0].y);
//    glVertex2f(parallelAxis2D_f[1].x,parallelAxis2D_f[1].y);
//
//    glVertex2f(parallelAxis2D_f[0].x,parallelAxis2D_f[0].y);
//    glVertex2f(parallelAxis2D_f[2].x,parallelAxis2D_f[2].y);
//
//    glVertex2f(parallelAxis2D_f[0].x,parallelAxis2D_f[0].y);
//    glVertex2f(parallelAxis2D_f[3].x,parallelAxis2D_f[3].y);
//    glEnd();
}


glm::vec3 RectDemo::rightest(){
    glm::vec3 nowXYZcorner[4] = {tblrXYZ.lt, tblrXYZ.rt, tblrXYZ.rb, tblrXYZ.lb};
    glm::vec3 rightestXYZ = nowXYZcorner[0];
    for(int i = 1; i < 4; i++){
        if(nowXYZcorner[i].x > rightestXYZ.x){
            rightestXYZ = nowXYZcorner[i];
        }
    }//cout << "rightestXYZ: " << rightestXYZ.y << ", " << rightestXYZ.x << ", " << rightestXYZ.z << endl;
    return rightestXYZ;
}
glm::vec3 RectDemo::leftest() {
    glm::vec3 nowXYZcorner[4] = {tblrXYZ.lt, tblrXYZ.rt, tblrXYZ.rb, tblrXYZ.lb};
    glm::vec3 leftestXYZ = nowXYZcorner[0];
    for(int i = 1; i < 4; i++){
        if(nowXYZcorner[i].x < leftestXYZ.x){
            leftestXYZ = nowXYZcorner[i];
        }
    }//cout << "leftestXYZ: " << leftestXYZ.y << ", " << leftestXYZ.x << ", " << leftestXYZ.z << endl;
    return leftestXYZ;
}
glm::vec3 RectDemo::topmost() {
    glm::vec3 nowXYZcorner[4] = {tblrXYZ.lt, tblrXYZ.rt, tblrXYZ.rb, tblrXYZ.lb};
    glm::vec3 topmostXYZ = nowXYZcorner[0];
    for(int i = 1; i < 4; i++){
        if(nowXYZcorner[i].y < topmostXYZ.y){ // y最小
            topmostXYZ = nowXYZcorner[i];
        }
    }//cout << "topmostXYZ: " << topmostXYZ.y << ", " << topmostXYZ.x << ", " << topmostXYZ.z << endl;
    return topmostXYZ;
}
glm::vec3 RectDemo::bottommost() {
    glm::vec3 nowXYZcorner[4] = {tblrXYZ.lt, tblrXYZ.rt, tblrXYZ.rb, tblrXYZ.lb};
    glm::vec3 bottommostXYZ = nowXYZcorner[0];
    for(int i = 1; i < 4; i++){
        if(nowXYZcorner[i].y > bottommostXYZ.y){ // y最大
            bottommostXYZ = nowXYZcorner[i];
        }
    }//cout << "bottommostXYZ: " << bottommostXYZ.y << ", " << bottommostXYZ.x << ", " << bottommostXYZ.z << endl;
    return bottommostXYZ;
}
glm::vec3 RectDemo::fontmost() {
    glm::vec3 nowXYZcorner[4] = {tblrXYZ.lt, tblrXYZ.rt, tblrXYZ.rb, tblrXYZ.lb};
    glm::vec3 fontmostXYZ = nowXYZcorner[0];
    for(int i = 1; i < 4; i++){
        if(nowXYZcorner[i].z < fontmostXYZ.z){ // z最小
            fontmostXYZ = nowXYZcorner[i];
        }
    }//cout << "fontmostXYZ: " << fontmostXYZ.y << ", " << fontmostXYZ.x << ", " << fontmostXYZ.z << endl;
    return fontmostXYZ;
}
glm::vec3 RectDemo::backmost() {
    glm::vec3 nowXYZcorner[4] = {tblrXYZ.lt, tblrXYZ.rt, tblrXYZ.rb, tblrXYZ.lb};
    glm::vec3 backmostXYZ = nowXYZcorner[0];
    for(int i = 1; i < 4; i++){
        if(nowXYZcorner[i].z > backmostXYZ.z){ // z最大
            backmostXYZ = nowXYZcorner[i];
        }
    }
    return backmostXYZ;
}

