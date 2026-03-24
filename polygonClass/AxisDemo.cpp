//
// Created by iceoc0 on 2024/11/16.
//


#include <valarray>
#include "AxisDemo.h"
#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif

struct modeAxis{
    char now;char a;char b;char d;
};
extern void* mode_ptr;
modeAxis mode_ = *((modeAxis*)mode_ptr);
// malloc一个超级结构体 AxisDemo
AxisDemo::AxisDemo(glm::vec3 _Xl_xyz, glm::vec3 _Xr_xyz, glm::vec3 _Yt_xyz, glm::vec3 _Yb_xyz, glm::vec3 _DEEPc_xyz, glm::vec3 _DEEPf_xyz)
{


    axisXYZ.Xl.x = _Xl_xyz.x;
    axisXYZ.Xl.y = _Xl_xyz.y;
    axisXYZ.Xl.z = _Xl_xyz.z;

    axisXYZ.Xr.x = _Xr_xyz.x;
    axisXYZ.Xr.y = _Xr_xyz.y;
    axisXYZ.Xr.z = _Xr_xyz.z;

    axisXYZ.Yt.x = _Yt_xyz.x;
    axisXYZ.Yt.y = _Yt_xyz.y;
    axisXYZ.Yt.z = _Yt_xyz.z;

    axisXYZ.Yb.x = _Yb_xyz.x;
    axisXYZ.Yb.y = _Yb_xyz.y;
    axisXYZ.Yb.z = _Yb_xyz.z;

    axisXYZ.DEEPc.x = _DEEPc_xyz.x; // 中心点
    axisXYZ.DEEPc.y = _DEEPc_xyz.y;
    axisXYZ.DEEPc.z = _DEEPc_xyz.z;

    axisXYZ.DEEPf.x = _DEEPf_xyz.x; // 中心点的尖端
    axisXYZ.DEEPf.y = _DEEPf_xyz.y;
    axisXYZ.DEEPf.z = _DEEPf_xyz.z;

    // 相对于 世界坐标轴 同距
    axisXYZ_unchange.Xl.x = _Xl_xyz.x;
    axisXYZ_unchange.Xl.y = _Xl_xyz.y;
    axisXYZ_unchange.Xl.z = _Xl_xyz.z;

    axisXYZ_unchange.Xr.x = _Xr_xyz.x;
    axisXYZ_unchange.Xr.y = _Xr_xyz.y;
    axisXYZ_unchange.Xr.z = _Xr_xyz.z;

    axisXYZ_unchange.Yt.x = _Yt_xyz.x;
    axisXYZ_unchange.Yt.y = _Yt_xyz.y;
    axisXYZ_unchange.Yt.z = _Yt_xyz.z;

    axisXYZ_unchange.Yb.x = _Yb_xyz.x;
    axisXYZ_unchange.Yb.y = _Yb_xyz.y;
    axisXYZ_unchange.Yb.z = _Yb_xyz.z;

    axisXYZ_unchange.DEEPc.x = _DEEPc_xyz.x; // 中心点
    axisXYZ_unchange.DEEPc.y = _DEEPc_xyz.y;
    axisXYZ_unchange.DEEPc.z = _DEEPc_xyz.z;

    axisXYZ_unchange.DEEPf.x = _DEEPf_xyz.x; // 中心点的尖端
    axisXYZ_unchange.DEEPf.y = _DEEPf_xyz.y;
    axisXYZ_unchange.DEEPf.z = _DEEPf_xyz.z;

    angleXYZ = {0.f,0.f,0.f};

    rectColor = WHITE;/*无setcolor时默认*/

    axisLong.x = glm::distance(axisXYZ.Xl, axisXYZ.Xr); // x轴 长度初始化
    axisLong.y = glm::distance(axisXYZ.Yt, axisXYZ.Yb); // y轴 长度初始化
    axisLong.z = glm::distance(axisXYZ.DEEPc, axisXYZ.DEEPf); // deep轴 长度初始化



}



void AxisDemo::drawAxis(ScreenDemo* ScreenEye){
    glm::vec3 eyeCenter = ScreenEye->getCenterTip();
    if(mode_.now == mode_.b){
        if(axisXYZ.Xl.z + ScreenEye->rectDepth > 0.1f){ // 眼心距>100 才渲染

        }else return;
    }else if(mode_.now ==mode_.d){ // 自由机位 白轴先不画了
        return;
    }


    BGR3f _color;
    _color.setBGR(rectColor,1);// 翠绿


    float color_[3] = {_color.r1,_color.g1,_color.b1};
    ScreenDemo::line2ScreenBuffer(ScreenEye,tblrXY_f[0].x, tblrXY_f[0].y,
                                  tblrXY_f[1].x, tblrXY_f[1].y,color_,0.f);
    ScreenDemo::line2ScreenBuffer(ScreenEye,tblrXY_f[2].x, tblrXY_f[2].y,
                                  tblrXY_f[3].x, tblrXY_f[3].y,color_,0.f);
    ScreenDemo::line2ScreenBuffer(ScreenEye,tblrXY_f[4].x, tblrXY_f[4].y,
                                  tblrXY_f[5].x, tblrXY_f[5].y,color_,0.f);
//    PolygonBase::line(tblrXY_f[0].x, tblrXY_f[0].y,
//    tblrXY_f[1].x, tblrXY_f[1].y,color_);
//
//    PolygonBase::line(tblrXY_f[2].x, tblrXY_f[2].y,
//                      tblrXY_f[3].x, tblrXY_f[3].y,color_);
//
//    PolygonBase::line(tblrXY_f[4].x, tblrXY_f[4].y,
//                      tblrXY_f[5].x, tblrXY_f[5].y,color_);

    //printf("前原点距屏幕%f\n",points2EyeBack.DEEPcEye);
}

void AxisDemo::drawTiltAxis3Color(ScreenDemo* ScreenEye){
    //glm::vec3 eyeCenter = ScreenEye->getCenterTip();


    if(mode_.now ==mode_.b) {
        // mode2 斜轴 不是世界系
        // 需要转换 info
        freshWorldOxyz();
        freshStartWorld_GoDir(); // 三轴 向量
    }
if(axisXYZ.Xl.z + ScreenEye->rectDepth < 0.1f){ // 眼心距>100 才渲染
            println(stderr,"眼心距太近，不渲染斜轴");
            return;
        }

    float color_[3] = {_green[0],_green[1],_green[2]};

    ScreenDemo::line2ScreenBuffer(ScreenEye,tblrXY_f[0].x, tblrXY_f[0].y,
                                  tblrXY_f[1].x, tblrXY_f[1].y,color_,0.f);


    color_[0] = _blue[0];color_[1] = _blue[1];color_[2] = _blue[2];

    ScreenDemo::line2ScreenBuffer(ScreenEye,tblrXY_f[2].x, tblrXY_f[2].y,
                                  tblrXY_f[3].x, tblrXY_f[3].y,color_,0.f);
    color_[0] = _yellow[0];color_[1] = _yellow[1];color_[2] = _yellow[2];

    //printf("原点距屏幕%f\n",points2EyeBack.DEEPcEye);
    ScreenDemo::line2ScreenBuffer(ScreenEye,tblrXY_f[4].x, tblrXY_f[4].y,
                                      tblrXY_f[5].x, tblrXY_f[5].y,color_,0.f);
}

void AxisDemo::setColor(int NormalColor1) {
    rectColor = NormalColor1; // 白色定轴
}


void AxisDemo::setTBLRXY(glm::vec2 tblr0, glm::vec2 tblr1, glm::vec2 tblr2, glm::vec2 tblr3, glm::vec2 tblrC, glm::vec2 tblrCT){

    tblrXY_f[0].x = tblr0.x; // Xl
    tblrXY_f[0].y = tblr0.y;
    tblrXY_f[1].x = tblr1.x; // Xr
    tblrXY_f[1].y = tblr1.y;
    tblrXY_f[2].x = tblr2.x; // Yb
    tblrXY_f[2].y = tblr2.y;
    tblrXY_f[3].x = tblr3.x; // Yt
    tblrXY_f[3].y = tblr3.y;
    tblrXY_f[4].x = tblrC.x; // DEEPc
    tblrXY_f[4].y = tblrC.y;
    tblrXY_f[5].x = tblrCT.x; // DEEPf
    tblrXY_f[5].y = tblrCT.y;
//    printf("~~~~~~Xl X:%d, Y:%d\n", tblrXY_l[0].y, tblrXY_l[0].x);
//    printf("~~~~~~Xr X:%d, Y:%d\n", tblrXY_l[1].y, tblrXY_l[1].x);
//    printf("~~~~~~Yb X:%d, Y:%d\n", tblrXY_l[2].y, tblrXY_l[2].x);
//    printf("~~~~~~Yt X:%d, Y:%d\n", tblrXY_l[3].y, tblrXY_l[3].x);
    // 不要等 最后画轴 再刷新 !!!
    freshGoLineDir(); // 三轴 向量
}

void AxisDemo::setTBLRXYZ(glm::vec3 ltXYZ, glm::vec3 rtXYZ, glm::vec3 rbXYZ, glm::vec3 lbXYZ, glm::vec3 centerXYZ, glm::vec3 centerTipXYZ){

    axisXYZ.Xl.x = ltXYZ.x;
    axisXYZ.Xl.y = ltXYZ.y;
    axisXYZ.Xl.z = ltXYZ.z;

    axisXYZ.Xr.x = rtXYZ.x;
    axisXYZ.Xr.y = rtXYZ.y;
    axisXYZ.Xr.z = rtXYZ.z;

    axisXYZ.Yt.x = rbXYZ.x;
    axisXYZ.Yt.y = rbXYZ.y;
    axisXYZ.Yt.z = rbXYZ.z;

    axisXYZ.Yb.x = lbXYZ.x;
    axisXYZ.Yb.y = lbXYZ.y;
    axisXYZ.Yb.z = lbXYZ.z;

    axisXYZ.DEEPc.x = centerXYZ.x; // 中心点
    axisXYZ.DEEPc.y = centerXYZ.y;
    axisXYZ.DEEPc.z = centerXYZ.z;

    axisXYZ.DEEPf.x = centerTipXYZ.x; // 中心点的尖端
    axisXYZ.DEEPf.y = centerTipXYZ.y;
    axisXYZ.DEEPf.z = centerTipXYZ.z;
    // 相对于 世界坐标轴 的刷新



}

void AxisDemo::freshGoLineDir(){
    // 按照斜x轴 向"右"
    toX = {(axisXYZ.Xr - axisXYZ.Xl) / axisLong.x
            // dy 有正负
           // dz 有正负
    };
    // 按照斜y轴 向"下"
    toY = {(axisXYZ.Yb - axisXYZ.Yt) / axisLong.y
    };
    // 按照斜deep轴 向"里"
    toDEEP = {(axisXYZ.DEEPf - axisXYZ.DEEPc) / axisLong.z
    };

    axis_0_0_0 = goX(axisXYZ.Xl,axisBack);//{axisXYZ.Xl.x+axisBack,axisXYZ.Xl.y,axisXYZ.Xl.z};
}
glm::vec3 AxisDemo::goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * toX.dx;
    _srcXYZ.y = _srcXYZ.y + _move * toX.dy;
    _srcXYZ.z = _srcXYZ.z + _move * toX.dz;
    return _srcXYZ;
}
glm::vec3 AxisDemo::goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * toY.dx;
    _srcXYZ.y = _srcXYZ.y + _move * toY.dy;
    _srcXYZ.z = _srcXYZ.z + _move * toY.dz;
    return _srcXYZ;
}
glm::vec3 AxisDemo::goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ.x = _srcXYZ.x + _move * toDEEP.dx;
    _srcXYZ.y = _srcXYZ.y + _move * toDEEP.dy;
    _srcXYZ.z = _srcXYZ.z + _move * toDEEP.dz;
    return _srcXYZ;
}
void AxisDemo::goX_(glm::vec3& _srcXYZ, float _move){
    _srcXYZ = _srcXYZ + _move * toX._;
}
void AxisDemo::goY_(glm::vec3& _srcXYZ, float _move){
    _srcXYZ = _srcXYZ + _move * toY._;
}
void AxisDemo::goDEEP_(glm::vec3& _srcXYZ, float _move){
    _srcXYZ = _srcXYZ + _move * toDEEP._;
}
glm::vec3 AxisDemo::AxisTilt2world(float moveX, float moveY, float moveZ) {
    glm::vec3 tmp = axis_0_0_0;
    goX_(tmp, moveX);
    goY_(tmp, moveY);
    goDEEP_(tmp, moveZ);
    return tmp;
}
glm::vec3 AxisDemo::getCenter() {
    return axisXYZ.DEEPc;
}

void AxisDemo::freshWorldOxyz() {
    // d = -ax -by -cz
    // 0_0_0 共面
    float &a_flatYZ = toX.dx;
    float &b_flatYZ = toX.dy;
    float &c_flatYZ = toX.dz;
    // float d_flatYZ = -a_flatYZ*axisXYZ.DEEPf.x - b_flatYZ*axisXYZ.DEEPf.y - c_flatYZ*axisXYZ.DEEPf.z; // 左
    float d_flatYZ = -glm::dot(toX._,axis_0_0_0); // suggested !!

    //println("toX:{},{},{}",toX.dx,toX.dy,toX.dz);
    // 0_0_0 共面
    float &a_flatXZ = toY.dx;
    float &b_flatXZ = toY.dy;
    float &c_flatXZ = toY.dz;
    // float d_flatXZ = -a_flatXZ*axisXYZ.Xr.x - b_flatXZ*axisXYZ.Xr.y - c_flatXZ*axisXYZ.Xr.z; // 俯
    float d_flatXZ = -glm::dot(toY._,axis_0_0_0); // 俯
    // 0_0_0 共面
    float &a_flatXY = toDEEP.dx;
    float &b_flatXY = toDEEP.dy;
    float &c_flatXY = toDEEP.dz;
    // float d_flatXY = -a_flatXY*axisXYZ.Xr.x - b_flatXY*axisXYZ.Xr.y - c_flatXY*axisXYZ.Xr.z; // 主
    float d_flatXY = -glm::dot(toDEEP._,axis_0_0_0); // 主


    // 垂距 ax+by+cz+d   *-1
    // 世界系oxyz 到斜轴三面 垂直距离
    const float &dirFar = axisLong.x; // 三轴 长 250
    // println("axis long:{}",showVec3(axisLong));
    //println("dir far:{}",dirFar);
    tilt_C_world_oxyz[0] = {d_flatYZ, d_flatXZ, d_flatXY}; // 0 0 0
    tilt_C_world_oxyz[1] = {a_flatYZ * dirFar+d_flatYZ,
                        a_flatXZ * dirFar+d_flatXZ,
                        a_flatXY * dirFar+d_flatXY}; // 250 0 0
    tilt_C_world_oxyz[2] = {b_flatYZ * dirFar+d_flatYZ,
                        b_flatXZ * dirFar+d_flatXZ,
                        b_flatXY * dirFar+d_flatXY}; // 0 250 0
    tilt_C_world_oxyz[3] = {c_flatYZ * dirFar+d_flatYZ,
                        c_flatXZ * dirFar+d_flatXZ,
                        c_flatXY * dirFar+d_flatXY}; // 0 0 250
    //println("startWorld O:{},{},{}",tilt_C_world_oxyz[0].x,tilt_C_world_oxyz[0].y,tilt_C_world_oxyz[0].z);
    //println("startWorld X:{},{},{}",tilt_C_world_oxyz[1].x,tilt_C_world_oxyz[1].y,tilt_C_world_oxyz[1].z);
    //println("startWorld Y:{},{},{}",tilt_C_world_oxyz[2].x,tilt_C_world_oxyz[2].y,tilt_C_world_oxyz[2].z);
    //println("startWorld Z:{},{},{}",tilt_C_world_oxyz[3].x,tilt_C_world_oxyz[3].y,tilt_C_world_oxyz[3].z);
}
void AxisDemo::freshStartWorld_GoDir() {
    startWorld_goX = ScreenDemo::get_AgoB_direction3D(tilt_C_world_oxyz[0],tilt_C_world_oxyz[1]);
    startWorld_goY = ScreenDemo::get_AgoB_direction3D(tilt_C_world_oxyz[0],tilt_C_world_oxyz[2]);
    startWorld_goDEEP = ScreenDemo::get_AgoB_direction3D(tilt_C_world_oxyz[0],tilt_C_world_oxyz[3]);

}
void AxisDemo::startWorld_stepX(glm::vec3& _srcXYZ, float _move) {
    _srcXYZ = _srcXYZ + _move * startWorld_goX._;

}
void AxisDemo::startWorld_stepY(glm::vec3& _srcXYZ, float _move) {
    _srcXYZ = _srcXYZ + _move * startWorld_goY._;

}
void AxisDemo::startWorld_stepZ(glm::vec3& _srcXYZ, float _move) {
    _srcXYZ = _srcXYZ + _move * startWorld_goDEEP._;

}
glm::vec3 AxisDemo::world2AxisTilt(glm::vec3& _src) {
    glm::vec3 tmp = tilt_C_world_oxyz[0];

    startWorld_stepX(tmp, _src.x);
    startWorld_stepY(tmp, _src.y);
    startWorld_stepZ(tmp, _src.z);
    return tmp;
}