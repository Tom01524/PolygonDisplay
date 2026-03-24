//
// Created by iceoc0 on 2024/11/9.
//


#include "TriangleDemo.h"


struct modeTria{ // 同类型组 的 结构体指针 移花接木
    char now;char a;char b;char d;
};
extern void* mode_ptr;
modeTria mode_ = *((modeTria*)mode_ptr);

extern void* settled_ptr; // 全局设置的结构体指针
struct _settledTria{
    int _width;
    int _height;
    int _deep;

};
_settledTria* settled_ = (_settledTria*)settled_ptr;
const int screenWidth3 = settled_-> _width;
const int screenHeight3 = settled_-> _height;
const int screenDeep3 = settled_-> _deep;

extern void* _3d_2d_go_void_ptr; // 3d_2d_go的函数指针
// struct _3d_2d_go_tria{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, float *, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_2d)(ScreenDemo*, float, float, float);
// };

glm::vec2 (*__3d2dGoTria)(ScreenDemo*, glm::vec3, glm::vec3*) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2dTria)(ScreenDemo*, float, float, float) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d; // 模式1 用自己的不行


TriangleDemo::TriangleDemo(glm::vec3 tipA, glm::vec3 tipB, glm::vec3 tipC,
                          int _objName) {
    debugLine = 0;//cout << "~~__debug~??" << debugLine << endl;
    if(_objName != NULL)this->objName = _objName;

    //printf("~~_objName: %hd\n", this->objName);
    _init_main(tipA, tipB, tipC);
}
TriangleDemo::TriangleDemo(glm::vec3 tipA, glm::vec3 tipB, glm::vec3 tipC,
                           unsigned char _debug_, int _objName) {
    debugLine = _debug_;//cout << "~~_debug_~~~" << debugLine << endl;
    if(_objName != NULL)this->objName = _objName;
    //printf("~~~~_objName: %hd\n", this->objName);
    _init_main(tipA, tipB, tipC);
}
void TriangleDemo::_init_main(glm::vec3 _faceS_XYZ, glm::vec3 _faceM_XYZ, glm::vec3 _faceL_XYZ){
    PolygonBase::type_ = 3; // 三角形

    _2S2M2L_XYZ.pA.x = _faceS_XYZ.x;
    _2S2M2L_XYZ.pA.y = _faceS_XYZ.y;
    _2S2M2L_XYZ.pA.z = _faceS_XYZ.z;

    _2S2M2L_XYZ.pB.x = _faceM_XYZ.x;
    _2S2M2L_XYZ.pB.y = _faceM_XYZ.y;
    _2S2M2L_XYZ.pB.z = _faceM_XYZ.z;

    _2S2M2L_XYZ.pC.x = _faceL_XYZ.x;
    _2S2M2L_XYZ.pC.y = _faceL_XYZ.y;
    _2S2M2L_XYZ.pC.z = _faceL_XYZ.z;



    // 相对于 世界坐标轴 同距
    _2S2M2L_XYZ_unchange.pA.x = _faceS_XYZ.x;
    _2S2M2L_XYZ_unchange.pA.y = _faceS_XYZ.y;
    _2S2M2L_XYZ_unchange.pA.z = _faceS_XYZ.z;

    _2S2M2L_XYZ_unchange.pB.x = _faceM_XYZ.x;
    _2S2M2L_XYZ_unchange.pB.y = _faceM_XYZ.y;
    _2S2M2L_XYZ_unchange.pB.z = _faceM_XYZ.z;

    _2S2M2L_XYZ_unchange.pC.x = _faceL_XYZ.x;
    _2S2M2L_XYZ_unchange.pC.y = _faceL_XYZ.y;
    _2S2M2L_XYZ_unchange.pC.z = _faceL_XYZ.z;


    startEye = {(float)screenWidth3/2.f,(float)screenHeight3/2.f,(float)-screenDeep3};

    frontColor_rgb01[0] = 1.f; // 无颜色默认
    frontColor_rgb01[1] = 1.f;
    frontColor_rgb01[2] = 1.f;
    if(objName==3) { // 网格分区色
        frontSubColor_rgb01[0] = frontColor_rgb01[0] * 0.75f;
        frontSubColor_rgb01[1] = frontColor_rgb01[1] * 0.75f;
        frontSubColor_rgb01[2] = frontColor_rgb01[2] * 0.75f;
    }
    backColor_rgb01[0] = 0.4f; // 无颜色默认
    backColor_rgb01[1] = 0.4f;
    backColor_rgb01[2] = 0.4f;

    centerLongist = glm::distance(_2S2M2L_XYZ.pA, _2S2M2L_XYZ.pB) / 2.0F;

    //printf("---三角形中心最远点距离：%f\n", centerLongist);

}

void TriangleDemo::Draw_Tick(ScreenDemo* ScreenEye){
    // println("三角面 draw");
    //glm::vec3 nowEyeCenter = ScreenEye->tblrXYZ.centerTip; // 眼睛中心点
    // glm::vec3 startEyeCenter = {(float)screenWidth3 / 2.0f, (float)screenHeight3 / 2.0f,
    //                             (float)-screenDeep3};

    fresh_virtual_abcd();
    //horizontalDeepCalc(ScreenEye);
    bool all2Dleft = _2S2M2L_XY_f[0].x < 0.f && _2S2M2L_XY_f[1].x < 0.f &&
            _2S2M2L_XY_f[2].x < 0.f;
    bool all2Dright = _2S2M2L_XY_f[0].x >  ScreenEye->rectWidth && _2S2M2L_XY_f[1].x > ScreenEye->rectWidth &&
                      _2S2M2L_XY_f[2].x >  ScreenEye->rectWidth;
    bool all2Dtop = _2S2M2L_XY_f[0].y < 0.f && _2S2M2L_XY_f[1].y < 0.f &&
                    _2S2M2L_XY_f[2].y < 0.f;
    bool all2Dbottom = _2S2M2L_XY_f[0].y > ScreenEye->rectHeight && _2S2M2L_XY_f[1].y > ScreenEye->rectHeight &&
                       _2S2M2L_XY_f[2].y > ScreenEye->rectHeight;
    bool corner2DoutOfScreen = all2Dleft || all2Dright || all2Dtop || all2Dbottom;
    bool cornerClose2Eye = virtual_2S2M2L_XYZ[0].z + ScreenEye->rectDepth < 0.1F;

    //allBackAngle();

    if(!cornerClose2Eye && !corner2DoutOfScreen){ // 眼心距>100 才渲染

    }else {
        if (cornerClose2Eye) {
            println("三角面 draw 贴脸\n virtual_2S2M2L_XYZ[0].z: {}",virtual_2S2M2L_XYZ[0].z);
        }
        // if (corner2DoutOfScreen)println("三角面 draw 屏幕外!!");
        return;
    }



    //ax1_by1_cz1_d1();
    if (cTipEyeCloser()) { // 正面

        // 面远 线近
            _solidTriangle2D(ScreenEye,true);

    } else { // 背面

            _solidTriangle2D(ScreenEye,false);
    }


    //printf("直角点距屏幕%f\n",points2EyeBack.faceL_Eye);
}

void TriangleDemo::_solidTriangle2D(ScreenDemo* ScreenEye,bool onFront){
    // println("三角面 solidTriangle2D");
//    horizontalDeepCalc(); // 边信息与准备 边信息算得 填色
    PolygonBase::fresh2D_scanRows_3(_2S2M2L_XY_f[0],
                                    _2S2M2L_XY_f[1],
                                    _2S2M2L_XY_f[2], &lineScanFillColor,type_);

    if(objName==3){
        pixel2EyeDeepArea.clear();
    }
    else {
        pixelEyeDeep.clear();
    }

//    int isFIrst = 0;
    freshDeepFarNear(); // 填色深度 最远最近
    if(objName==3){ // 分区域网格
        for(auto& _linePosInfo : lineScanFillColor){
            rowPixelDeep4Area rowDeepInfo;
            rowDeepInfo.y = _linePosInfo.y; // 本行 y
            for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){

                //float deepNow = getEyeDeepbyXY(nowX, _linePosInfo.y);
                float* _αβγ = get_αβγ(nowX, _linePosInfo.y);
                float deepNow = getScreenDeepbyXY_αβγ(_αβγ);
                char areaNow = getFlatAreaByXY(_αβγ);
                if(deepNow < screenNear){
//                cerr << "deepNow:" << deepNow << " screenNear:" << screenNear << endl;
                    deepNow = screenNear; // 防止深度溢出
                }else if(deepNow > screenFar){
//                cerr << "deepNow:" << deepNow << " screenFar:" << screenFar << endl;
                    deepNow = screenFar; // 防止深度溢出
                }

                rowDeepInfo.pixelDeeps.push_back({nowX, deepNow,areaNow}); // 本行 x deep
            }
            pixel2EyeDeepArea.push_back(rowDeepInfo);

        }

        size_t subSizeNow;
        for(auto& _lineDeepInfo : pixel2EyeDeepArea){
            subSizeNow=_lineDeepInfo.pixelDeeps.size();
            for(int i=0; i < subSizeNow/*-1*/; i++){
                int nowX = _lineDeepInfo.pixelDeeps[i].x;
                float nowDeep = _lineDeepInfo.pixelDeeps[i].eyeDeep;
                char area = _lineDeepInfo.pixelDeeps[i].area; // 网格分区

                if(onFront){
                    //cout << "debugLine" << (int)debugLine << endl;
                    if(debugLine==1) {
                        int colorNow_ = black2ColorfulDeep(nowDeep);
//                    putpixel((int) roundf(nowX), _lineDeepInfo.y, colorNow); // ### screenDeep eyeDistace
                        BGR3f colorNow1;
                        colorNow1.setBGR(colorNow_,1);

                        float _color_[3] = {colorNow1.r1,colorNow1.g1,colorNow1.b1};
                        ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_, nowDeep, (PolygonBase*)this);

                    }else{
                        if(area==0){
                            ScreenEye->putPixel(nowX, _lineDeepInfo.y, frontColor_rgb01,
                                                nowDeep, (PolygonBase*)this);
                        }else{ //=1
                            ScreenEye->putPixel(nowX, _lineDeepInfo.y, frontSubColor_rgb01,
                                                nowDeep, (PolygonBase*)this);
                        }


                    }
                }
                else{

                    ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), backColor_rgb01, nowDeep, (PolygonBase*)this);

                }
            }
        }
    }else{
        // 不分区域网格
        for(auto& _linePosInfo : lineScanFillColor){
            rowPixelDeep4 rowDeepInfo;
            rowDeepInfo.y = _linePosInfo.y; // 本行 y
//        rowDeepInfo.pixelDeeps.clear(); // 本行 x deep 空
            for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){

                //float deepNow = getEyeDeepbyXY(nowX, _linePosInfo.y);
                float* _αβγ = get_αβγ(nowX, _linePosInfo.y);
                float deepNow = getScreenDeepbyXY_αβγ(_αβγ);
                if(deepNow < screenNear){
//                cerr << "deepNow:" << deepNow << " screenNear:" << screenNear << endl;
                    deepNow = screenNear; // 防止深度溢出
                }else if(deepNow > screenFar){
//                cerr << "deepNow:" << deepNow << " screenFar:" << screenFar << endl;
                    deepNow = screenFar; // 防止深度溢出
                }

                rowDeepInfo.pixelDeeps.push_back({nowX, deepNow}); // 本行 x deep
            }
            pixelEyeDeep.push_back(rowDeepInfo);
        }

        size_t subSizeNow;
        for(auto& _lineDeepInfo : pixelEyeDeep){
            subSizeNow=_lineDeepInfo.pixelDeeps.size();
            for(int i=0; i < subSizeNow/*-1*/; i++){
                int nowX = _lineDeepInfo.pixelDeeps[i].x;
                float nowDeep = _lineDeepInfo.pixelDeeps[i].eyeDeep;

                if(onFront){
                    //cout << "debugLine" << (int)debugLine << endl;
                    if(debugLine==1) {
                        // println("三角面 正面 行扫描");
                        int colorNow_ = black2ColorfulDeep(nowDeep);
//                    putpixel((int) roundf(nowX), _lineDeepInfo.y, colorNow); // ### screenDeep eyeDistace
                        BGR3f colorNow1;
                        colorNow1.setBGR(colorNow_,1);

                        float _color_[3] = {colorNow1.r1,colorNow1.g1,colorNow1.b1};
                        ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), _color_, nowDeep, (PolygonBase*)this);

                    }else{
                        ScreenEye->putPixel(nowX, _lineDeepInfo.y, frontColor_rgb01, nowDeep, (PolygonBase*)this);

                    }
                }
                else{

                    ScreenEye->putPixel(nowX, static_cast<int>(_lineDeepInfo.y), backColor_rgb01, nowDeep, (PolygonBase*)this);

                }
            }
        }
    }


}

bool TriangleDemo::PolyScanClicked(int x,int y)
{
    for(auto& lineScan : lineScanFillColor){
        if(y==lineScan.y && x>=lineScan.lx && x<=lineScan.rx){
            println("三角形被点击了！");
            return true; // 三角形被点击了！
        }
    }
    return false; // 三角形未被点击
}

void TriangleDemo::fresh_virtual_abcd(){
    // 计算两个边相量
    glm::vec3 pa2pc = virtual_2S2M2L_XYZ[2] - virtual_2S2M2L_XYZ[0];

    glm::vec3 pa2pb = virtual_2S2M2L_XYZ[1] - virtual_2S2M2L_XYZ[0];
    // 计算法向量
    glm::vec3 vertical_norm = glm::cross(pa2pc,pa2pb); // 法向量 立方体对角线单位一
    vertical_norm = glm::normalize(vertical_norm);
    // normal[0] = pa2pc.y * pa2pb.z - pa2pc.z * pa2pb.y;
    // normal[1] = pa2pc.z * pa2pb.x - pa2pc.x * pa2pb.z;
    // normal[2] = pa2pc.x * pa2pb.y - pa2pc.y * pa2pb.x;


    // 归一化法向量
    // float magnitude = glm::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
    // normal[0] /= magnitude;
    // normal[1] /= magnitude;
    // normal[2] /= magnitude; // 法向量 立方体对角线单位一

    if(_backFont == -1.0f){
        vertical_norm = -vertical_norm; // 法向量 取反 ?
    }
    virtualBack_a_b_c_d[0] = vertical_norm[0];
    virtualBack_a_b_c_d[1] = vertical_norm[1];
    virtualBack_a_b_c_d[2] = vertical_norm[2];
    // ax + by + cz + d = 0
    // d = -a1*x1 - b1*y1 - c1*z1
    virtualBack_a_b_c_d[3] = -glm::dot(vertical_norm, virtual_2S2M2L_XYZ[0]);





    // 得到了 ax + by + cz + d = 0 方程 可用 系数

}
goLine32 TriangleDemo::eye2ScreenPixel_dxyz(float x, float y){
    glm::vec3 pixelXYZ = {x, y, 0.0f};
    // 初始化一次 (600,400,-1000)
    float pixel2eye_far = glm::distance(startEye, pixelXYZ); // 计算像素点到屏幕中心的距离

    float farX = pixelXYZ.x - startEye.x; // 大减小 为正 走右
    float farY = pixelXYZ.y - startEye.y; // 大减小 为正 走下
    float farZ = 0.0f - startEye.z; // 初始化一次 (1000)
    float dx = farX / pixel2eye_far;
    float dy = farY / pixel2eye_far;
    float dz = farZ / pixel2eye_far;
    return goLine32{dx, dy, dz}; // 计算像素点到屏幕中心的向量
}
glm::vec3 TriangleDemo::getEyeGoXYZbyXY(float x, float y){
    // 已知 眼xyz 步进xyz

    // 初始化一次 (600,400,-1000)

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
    // 求 step
    float step, step_up, step_down;
    step_up = -a*startEye.x - b*startEye.y - c*startEye.z - d;
    step_down = a*eyeGoPixel.dx + b*eyeGoPixel.dy + c*eyeGoPixel.dz;
    step = step_up / step_down;
    // 得到了 step 步进值
    glm::vec3 _eyeGoXYZ = {eyeGoPixel.dx * step,
                      eyeGoPixel.dy * step,
                           eyeGoPixel.dz * step};
    // 得到了 像素点的 xyz
    return _eyeGoXYZ;
}
float TriangleDemo::getEyeDeepbyXY(float x, float y){
    // 初始化一次 (600,400,-1000)

    glm::vec3 eyeGoXYZ = getEyeGoXYZbyXY(x, y); // 计算像素点到屏幕中心的距离
    float eyeDeep = glm::sqrt(eyeGoXYZ.x * eyeGoXYZ.x + eyeGoXYZ.y * eyeGoXYZ.y + eyeGoXYZ.z * eyeGoXYZ.z);
    return eyeDeep; // 计算像素点到屏幕中心的距离
}
float TriangleDemo::getScreenDeepbyXY(float x, float y){
    // 初始化一次 (600,400,-1000)

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
    // 求 step
    float step, step_up, step_down;
    step_up = -a*startEye.x - b*startEye.y - c*startEye.z - d;
    step_down = a*eyeGoPixel.dx + b*eyeGoPixel.dy + c*eyeGoPixel.dz;
    step = step_up / step_down;
    // 得到了 step 步进值
//    glm::vec3 _eyeGoXYZ = {eyeGoPixel.dx * step,
//                         eyeGoPixel.dy * step,
//                         eyeGoPixel.dz * step};
    float pointScreenDeep = eyeGoPixel.dz * step - screenDeep3;
    return pointScreenDeep; // 得到了 像素点的 xyz
}
float TriangleDemo::getScreenDeepbyXY_αβγ(float* alpha_beta_gamma){

    float Z0 = virtual_2S2M2L_XYZ[0].z + screenDeep3; // 到视点 + 1000
    float Z1 = virtual_2S2M2L_XYZ[1].z + screenDeep3;
    float Z2 = virtual_2S2M2L_XYZ[2].z + screenDeep3;


    float Z_down = alpha_beta_gamma[0]/Z0 + alpha_beta_gamma[1]/Z1 + alpha_beta_gamma[2]/Z2;
    float Z = 1.f / Z_down;
    return Z - screenDeep3; // 得到了 像素点的 xyz
}
char TriangleDemo::getFlatAreaByXY(float* alpha_beta_gamma){
    // row奇 col偶  ||  row偶 col奇  是原色
    bool rowEven = static_cast<int>(alpha_beta_gamma[0]*10.f) % 2 == 0; // α row
    bool colEven = static_cast<int>(alpha_beta_gamma[1]*10.f) % 2 == 0; // β col
    if((!rowEven && colEven) || (rowEven && !colEven)){
        return 0;// 原色
    }
    return 1;
}
float* TriangleDemo::get_αβγ(float x, float y){
    // 归一化 0~1
    float x0 = _2S2M2L_XY_f[0].x / static_cast<float>(screenWidth3); // 1600
    float y0 = _2S2M2L_XY_f[0].y / static_cast<float>(screenHeight3); // 1000
    float x1 = _2S2M2L_XY_f[1].x / static_cast<float>(screenWidth3);
    float y1 = _2S2M2L_XY_f[1].y / static_cast<float>(screenHeight3);
    float x2 = _2S2M2L_XY_f[2].x / static_cast<float>(screenWidth3);
    float y2 = _2S2M2L_XY_f[2].y / static_cast<float>(screenHeight3);

    float x_ = x / static_cast<float>(screenWidth3);
    float y_ = y / static_cast<float>(screenHeight3);

    float result[3]; // α β γ
    float beTa_up = (y_-y0)*(x2-x0)-(x_-x0)*(y2-y0);
    float beTa_down = (y1-y0)*(x2-x0)-(x1-x0)*(y2-y0);
    float beTa = beTa_up / beTa_down;
    result[1] = beTa; // β

    float gaMa_up = (y_-y0)*(x1-x0)-(x_-x0)*(y1-y0);
    float gaMa_down = (y2-y0)*(x1-x0)-(x2-x0)*(y1-y0);
    float gaMa = gaMa_up / gaMa_down;
    result[2] = gaMa; // γ

    float alpha = 1.0f - beTa - gaMa;
    result[0] = alpha; // α

    return result;
}
void TriangleDemo::freshDeepFarNear() { // 眼深 实实在在
    float deepOf3Corner[3];
    deepOf3Corner[0] = virtual_2S2M2L_XYZ[0].z; // rt
    deepOf3Corner[1] = virtual_2S2M2L_XYZ[1].z; // lb
    deepOf3Corner[2] = virtual_2S2M2L_XYZ[2].z; // lt

    float deepFar = deepOf3Corner[0], deepNear = deepOf3Corner[0];
    for(int i=0;i<3;i++){
        if(deepOf3Corner[i] > deepFar){ // 比我大
            deepFar = deepOf3Corner[i];
        }
        else if(deepOf3Corner[i] < deepNear){ // 比我小
            deepNear = deepOf3Corner[i];
        }
    }
    screenFar = deepFar;
    screenNear = deepNear;
}
int TriangleDemo::black2ColorfulDeep(float pointDeep){

    //float deepOf3[3] = {SYdeep, MYdeep, LYdeep};
    // println("三角面 深度偏白");

    float deepBetween = screenFar - screenNear; // 两端深度差
    float B = frontColor_rgb01[2] * 255.f;
    float G = frontColor_rgb01[1] * 255.f;
    float R = frontColor_rgb01[0] * 255.f; // 保留后两位
    //cout << hex << "B:" << B << " G:" << G << " R:" << R << endl;
    float dB = (255.0f-B) / deepBetween; // 最深和最近的差 颜色变化
    float dG = (255.0f-G) / deepBetween;
    float dR = (255.0f-R) / deepBetween; // 白 255 - 黑 无 --------------------------------------
    //cout << hex << "dB:" << dB << " dG:" << dG << " dR:" << dR << endl;



//    if(pointDeep < screenNear){
//        //cerr << "pointDeep:" << pointDeep << " < screenNear:" << screenNear << endl; // ### ###
//        pointDeep = screenNear;
//    }else if(pointDeep > screenFar){
//        //cerr << "pointDeep:" << pointDeep << " > screenFar:" << screenFar << endl;
//        pointDeep = screenFar;
//    }
    //cout << "pointDeep:" << pointDeep << endl;
    float ofFarthest = screenFar - pointDeep; // 对于 最深和当前的深度差
    //float ofNearest = pointDeep - frameScreenNear; // 对于 最深和当前的深度差
    float nowB = 255.0f - ofFarthest * dB;
    float nowG = 255.0f - ofFarthest * dG;
    float nowR = 255.0f - ofFarthest * dR; // 白 255 - 黑 无 --------------------------------------
    int color = (int(nowB) << 16) + (int(nowG) << 8) + int(nowR);
    color = (color & 0x00ffffff); // 最左一字节 0
    //cout << "color final:" << color << endl;
    return color;

}
#ifdef MAYBE_UNUSED
float* TriangleDemo::black2ColorfulDeep2(float pointDeep){
    float deepBetween = screenFar - screenNear; // 两端深度差
    float B = frontColor_rgb01[2];
    float G = frontColor_rgb01[1];
    float R = frontColor_rgb01[0]; // 保留后两位
    //cout << hex << "B:" << B << " G:" << G << " R:" << R << endl;
    float dB = (1.f-B) / deepBetween; // 最深和最近的差 颜色变化
    float dG = (1.f-G) / deepBetween;
    float dR = (1.f-R) / deepBetween; // 白 255 - 黑 无 --------------------------------------
    //cout << hex << "dB:" << dB << " dG:" << dG << " dR:" << dR << endl;


    float ofFarthest = screenFar - pointDeep; // 对于 最深和当前的深度差
    //float ofNearest = pointDeep - frameScreenNear; // 对于 最深和当前的深度差
    float nowB = 1.f - ofFarthest * dB;
    float nowG = 1.f - ofFarthest * dG;
    float nowR = 1.f - ofFarthest * dR; // 白 255 - 黑 无 --------------------------------------
    float result[3] = {nowR,nowG,nowB};

    return result;
}
#endif
int TriangleDemo::deepColorOf3DPoint(ScreenDemo* ScreenEye, float deepNow){
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
void TriangleDemo::switchDebug(){
    if(debugLine==0){
        debugLine = 1;
        println("triangle debugLine 1");
    }else{
        debugLine = 0;
        println("triangle debugLine 0");
    }
}
void TriangleDemo::setColor(int NormalColor1) {
    BGR3f colorNow;
    colorNow.setBGR(NormalColor1,1);
    frontColor_rgb01[0] = colorNow.r1;
    frontColor_rgb01[1] = colorNow.g1;
    frontColor_rgb01[2] = colorNow.b1;
    if(objName==3){
        frontSubColor_rgb01[0] = frontColor_rgb01[0] * 0.75f;
        frontSubColor_rgb01[1] = frontColor_rgb01[1] * 0.75f;
        frontSubColor_rgb01[2] = frontColor_rgb01[2] * 0.75f;
    }

}
void TriangleDemo::setBackColor(int backColor1){
    BGR3f colorNow;
    colorNow.setBGR(backColor1,1);
    backColor_rgb01[0] = colorNow.r1;
    backColor_rgb01[1] = colorNow.g1;
    backColor_rgb01[2] = colorNow.b1;
}


void TriangleDemo::set2S2M2L_XY_f(glm::vec2 _faceS_XY, glm::vec2 _faceM_XY, glm::vec2 _faceL_XY){
    _2S2M2L_XY_f[0].x = _faceS_XY.x; // rt
    _2S2M2L_XY_f[0].y = _faceS_XY.y;
    _2S2M2L_XY_f[1].x = _faceM_XY.x; // lb
    _2S2M2L_XY_f[1].y = _faceM_XY.y;
    _2S2M2L_XY_f[2].x = _faceL_XY.x; // lt
    _2S2M2L_XY_f[2].y = _faceL_XY.y;


//    POINTl _0 = {(long)roundf(_2S2M2L_XY_f[0].x), (long)roundf(_2S2M2L_XY_f[0].y)};
//    POINTl _1 = {(long)roundf(_2S2M2L_XY_f[1].x), (long)roundf(_2S2M2L_XY_f[1].y)};
//    POINTl _2 = {(long)roundf(_2S2M2L_XY_f[2].x), (long)roundf(_2S2M2L_XY_f[2].y)};
//    POINTl _3 = {(long)roundf(_2S2M2L_XY_f[3].x), (long)roundf(_2S2M2L_XY_f[3].y)};
//    POINTl _4 = {(long)roundf(_2S2M2L_XY_f[4].x), (long)roundf(_2S2M2L_XY_f[4].y)};
//    set2S2M2L_XY_l(_0,_1,_2,_3,_4);
}
void TriangleDemo::set2S2M2L_XYZ(glm::vec3 _faceS_XYZ, glm::vec3 _faceM_XYZ, glm::vec3 _faceL_XYZ){

    _2S2M2L_XYZ.pA = _faceS_XYZ;

    _2S2M2L_XYZ.pB = _faceM_XYZ;

    _2S2M2L_XYZ.pC = _faceL_XYZ;

}



bool TriangleDemo::cTipEyeCloser(){
    // 比较 中心点与中突点 到眼睛中心的距离


    float a = virtualBack_a_b_c_d[0];
    float b = virtualBack_a_b_c_d[1];
    float c = virtualBack_a_b_c_d[2];
    float d = virtualBack_a_b_c_d[3];

    return a*startEye.x + b*startEye.y + c*startEye.z + d > 0; // 共面方程 符号距离 判断正反
}

float TriangleDemo::getAvgeDeep(){
    return (screenFar + screenNear) / 2.0f;
}

glm::vec3 TriangleDemo::rightest(){
    glm::vec3 nowXYZcorner[3] = {_2S2M2L_XYZ.pA, _2S2M2L_XYZ.pB, _2S2M2L_XYZ.pC};
    glm::vec3 rightestXYZ = nowXYZcorner[0];
    for(int i = 1; i < 3; i++){
        if(nowXYZcorner[i].x > rightestXYZ.x){ // x最大
            rightestXYZ = nowXYZcorner[i];
        }
    }//cout << "rightestXYZ: " << rightestXYZ.y << ", " << rightestXYZ.x << ", " << rightestXYZ.z << endl;
    return rightestXYZ;
}
glm::vec3 TriangleDemo::leftest(){
    glm::vec3 nowXYZcorner[3] = {_2S2M2L_XYZ.pA, _2S2M2L_XYZ.pB, _2S2M2L_XYZ.pC};
    glm::vec3 leftestXYZ = nowXYZcorner[0];
    for(int i = 1; i < 3; i++){
        if(nowXYZcorner[i].x < leftestXYZ.x){ // x最小
            leftestXYZ = nowXYZcorner[i];
        }
    }//cout << "leftestXYZ: " << leftestXYZ.y << ", " << leftestXYZ.x << ", " << leftestXYZ.z << endl;
    return leftestXYZ;
}
glm::vec3 TriangleDemo::fontmost(){
    glm::vec3 nowXYZcorner[3] = {_2S2M2L_XYZ.pA, _2S2M2L_XYZ.pB, _2S2M2L_XYZ.pC};
    glm::vec3 fontmostXYZ = nowXYZcorner[0];
    for(int i = 1; i < 3; i++){
        if(nowXYZcorner[i].z < fontmostXYZ.z){ // z最小
            fontmostXYZ = nowXYZcorner[i];
        }
    }//cout << "fontmostXYZ: " << fontmostXYZ.y << ", " << fontmostXYZ.x << ", " << fontmostXYZ.z << endl;
    return fontmostXYZ;
}
glm::vec3 TriangleDemo::backmost(){
    glm::vec3 nowXYZcorner[3] = {_2S2M2L_XYZ.pA, _2S2M2L_XYZ.pB, _2S2M2L_XYZ.pC};
    glm::vec3 backmostXYZ = nowXYZcorner[0];
    for(int i = 1; i < 3; i++){
        if(nowXYZcorner[i].z > backmostXYZ.z){ // z最大
            backmostXYZ = nowXYZcorner[i];
        }
    }//cout << "backmostXYZ: " << backmostXYZ.y << ", " << backmostXYZ.x << ", " << backmostXYZ.z << endl;
    return backmostXYZ;
}
glm::vec3 TriangleDemo::topmost(){
    glm::vec3 nowXYZcorner[3] = {_2S2M2L_XYZ.pA, _2S2M2L_XYZ.pB, _2S2M2L_XYZ.pC};
//    printf("triangle rt:[%f,%f,%f], lb:[%f,%f,%f], lt:[%f,%f,%f]\n",
//           nowXYZcorner[0].y,nowXYZcorner[0].x,nowXYZcorner[0].z,
//           nowXYZcorner[1].y,nowXYZcorner[1].x,nowXYZcorner[1].z,
//           nowXYZcorner[2].y,nowXYZcorner[2].x,nowXYZcorner[2].z);
    glm::vec3 topmostXYZ = nowXYZcorner[0];
    for(int i = 1; i < 3; i++){
        if(nowXYZcorner[i].y < topmostXYZ.y){ // y最小
            topmostXYZ = nowXYZcorner[i];
        }
    }return topmostXYZ;
}
glm::vec3 TriangleDemo::bottommost(){
    glm::vec3 nowXYZcorner[3] = {_2S2M2L_XYZ.pA, _2S2M2L_XYZ.pB, _2S2M2L_XYZ.pC};
    glm::vec3 bottommostXYZ = nowXYZcorner[0];
    for(int i = 1; i < 3; i++){
        if(nowXYZcorner[i].y > bottommostXYZ.y){ // y最大
            bottommostXYZ = nowXYZcorner[i];
        }
    }return bottommostXYZ;
}


//cout << "leftestXYZ: " << leftestXYZ.y << ", " << leftestXYZ.x << ", " << leftestXYZ.z << endl;
