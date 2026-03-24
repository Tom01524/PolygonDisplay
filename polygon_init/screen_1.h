//
// Created by iceoc0 on 2025/9/17.
//

#ifndef POLYGONDISPLAY_SCREEN_1_H
#define POLYGONDISPLAY_SCREEN_1_H

#include"../func_main/calc_func_3D2D.h"

RectXYZ* screenAndEye = new RectXYZ{
        {0.0f, 0.0f, 0.0f},   //lt
        {windowWidth, 0.0f, 0.0f},  //rt
        {0.0f, windowHeight, 0.0f},  //lb
        {windowWidth, windowHeight, 0.0f},  //rb
        {windowWidth/2, windowHeight/2, 0.0f},
        {windowWidth/2, windowHeight/2, -GlobalEyeDeep} // centerTip 作眼睛
};
ScreenDemo* screenAndEye_init() {
    ScreenDemo* ScreenEye = new ScreenDemo(
            {(screenAndEye->lt.x), (screenAndEye->lt.y), (screenAndEye->lt.z)},
            {(screenAndEye->rt.x), (screenAndEye->rt.y), (screenAndEye->rt.z)},
            {(screenAndEye->rb.x), (screenAndEye->rb.y), (screenAndEye->rb.z)},
            {(screenAndEye->lb.x), (screenAndEye->lb.y), (screenAndEye->lb.z)},
            {(screenAndEye->center.x), (screenAndEye->center.y), (screenAndEye->center.z)},
            {(screenAndEye->centerTip.x), (screenAndEye->centerTip.y), (screenAndEye->centerTip.z)},NULL
    );


    println("",screenAndEye->lt.y, "~~", screenAndEye->lt.x, "~~", screenAndEye->lt.z);
    println("",screenAndEye->rt.y, "~~", screenAndEye->rt.x, "~~", screenAndEye->rt.z);
    println("",screenAndEye->rb.y, "~~", screenAndEye->rb.x, "~~", screenAndEye->rb.z);
    println("",screenAndEye->lb.y, "~~", screenAndEye->lb.x, "~~", screenAndEye->lb.z);
    println("",screenAndEye->center.y, "~~", screenAndEye->center.x, "~~", screenAndEye->center.z);
    println("",screenAndEye->centerTip.y, "~~", screenAndEye->centerTip.x, "~~", screenAndEye->centerTip.z);
    return ScreenEye;
}


float _goR, _goUp, _goDeep; // 屏幕偏移

RectXYZ screenAndEyeL = {
        {0.0f, 0.0f, 0.0f},   //lt
        {windowWidth, 0.0f, 0.0f},  //rt
        {0.0f, windowHeight, 0.0f},  //lb
        {windowWidth, windowHeight, 0.0f},  //rb
        {windowWidth/2, windowHeight/2, 0.0f},
        {windowWidth/2, windowHeight/2, -GlobalEyeDeep} // DEEPf 作眼睛
};
unique_ptr<ScreenDemo> screenAndEyeGo_init() {

    // 屏幕偏移 在fisrt init调整
    unique_ptr<ScreenDemo> ScreenEyeL = make_unique<ScreenDemo>(
            glm::vec3{screenAndEyeL.lt.x, screenAndEyeL.lt.y, screenAndEyeL.lt.z},
            glm::vec3{screenAndEyeL.rt.x, screenAndEyeL.rt.y, screenAndEyeL.rt.z},
            glm::vec3{screenAndEyeL.rb.x, screenAndEyeL.rb.y, screenAndEyeL.rb.z},
            glm::vec3{screenAndEyeL.lb.x, screenAndEyeL.lb.y, screenAndEyeL.lb.z},
            glm::vec3{screenAndEyeL.center.x, screenAndEyeL.center.y, screenAndEyeL.center.z},
            glm::vec3{screenAndEyeL.centerTip.x, screenAndEyeL.centerTip.y, screenAndEyeL.centerTip.z},NULL
    );

    //ScreenEyeL.setFrontColor(0xaae8f7); // 杏仁黄


    println("({}--{}--{})",screenAndEyeL.lt.y,screenAndEyeL.lt.x,screenAndEyeL.lt.z);
    println("({}--{}--{})",screenAndEyeL.rt.y,screenAndEyeL.rt.x,screenAndEyeL.rt.z);
    println("({}--{}--{})",screenAndEyeL.rb.y,screenAndEyeL.rb.x,screenAndEyeL.rb.z);
    println("({}--{}--{})",screenAndEyeL.lb.y,screenAndEyeL.lb.x,screenAndEyeL.lb.z);
    println("({}--{}--{})",screenAndEyeL.center.y,screenAndEyeL.center.x,screenAndEyeL.center.z);
    println("({}--{}--{})",screenAndEyeL.centerTip.y,screenAndEyeL.centerTip.x,screenAndEyeL.centerTip.z);

    return std::move(ScreenEyeL);
}

#endif //POLYGONDISPLAY_SCREEN_1_H
