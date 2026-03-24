//
// Created by iceoc0 on 2024/11/24.
//

#ifndef GLOBALSETTINGS_H
#define GLOBALSETTINGS_H

// #ifndef M_PI
// #define M_PI		3.14159265358979323846f
// #endif


float goStep = 3.0f; // 步长
float goAngle = 1.0f; // 一次旋转角度


char runningMode = 2; // 运行模式 2 4

struct _mode{
    char _modeNow;
    char _fontView;
    char _leftView;
    char _screenGo;

};

_mode mode = {
        runningMode, // modeNow
        1, // fontView
        2, // leftView
        4 // leftViewGo

};
void* mode_ptr = &mode;

const int windowWidth = 1600;
const int windowHeight = 1000;
const int GlobalEyeDeep = 1000; // 眼睛深度

struct _settled{
    int _width;
    int _height;
    int _deep;

};
_settled settled = {
        windowWidth, // width
        windowHeight, // height
        GlobalEyeDeep, // deep

};
void* settled_ptr = &settled;


const int colorBarHeight = 20; // 颜色条高度
const int colorBarLeft = 0; // 颜色条左

int widthI = 2;
int blueI = 232; // BGR
int greenI = 100;
int redI = 210;
bool colorBarShow = true; // 是否显示颜色条


#endif //GLOBALSETTINGS_H
