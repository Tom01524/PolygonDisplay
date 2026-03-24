//
// Created by iceoc0 on 2025/6/7.
//

#ifndef POLYGONDISPLAY_BECUBICBEZIER_1_H
#define POLYGONDISPLAY_BECUBICBEZIER_1_H

#include"../polygon_init/cone_1.h"
#include "../polygonClass/Bezier33Edge4Mirror.h"
#include "../polygonClass/Bezier3Img.h"

void BicubicBezierInit(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid);
void BicubicBezierInit2(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid);
void BicubicBezierInitUtah1(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid);
void BicubicBezierInitUtah2(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid);
void BicubicBezierInitUtah3(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid);
glm::vec3 transferVec3(glm::vec3 _src);
glm::vec3 transferVec3_(glm::vec3 _src);

void controlPointsMove(glm::vec3 _src[4][4], glm::vec3 move);
void Bezier3MirrorInit(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 controlP[4][4],glm::vec3 move,int _colorP, int _colorGrid);
void Bezier3ImgInit(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid);

float toX = 250.f;
float toY = 50.f;
float toZ = -100.f;
glm::vec3 _P[5][5] = {
    {{  0 + toX, 0 + toY, 95 + toZ },
     { 40 + toX, 0 + toY, -5 + toZ },
     { 80 + toX, 0 + toY, -5 + toZ },
     {120 + toX, 0 + toY, 95 + toZ },
     {160 + toX, 0 + toY, -80 + toZ}},

    {{  0 + toX, 40 + toY, 75 + toZ },
     { 40 + toX, 40 + toY, -25 + toZ},
     { 80 + toX, 40 + toY, -25 + toZ},
     {120 + toX, 40 + toY, 75 + toZ },
     {160 + toX, 40 + toY, -80 + toZ}},

    {{  0 + toX, 80 + toY, 75 + toZ },
     { 40 + toX, 80 + toY, -25 + toZ},
     { 80 + toX, 80 + toY, -25 + toZ},
     {120 + toX, 80 + toY, 75 + toZ },
     {160 + toX, 80 + toY, -80 + toZ}},

    {{  0 + toX, 120 + toY, 95 + toZ },
     { 40 + toX, 120 + toY, -5 + toZ},
     { 80 + toX, 120 + toY, -5 + toZ},
     {120 + toX, 120 + toY, 95 + toZ },
     {160 + toX, 120 + toY, -80 + toZ}},

    {{  0 + toX, 160 + toY, 75 + toZ },
     { 40 + toX, 160 + toY, -25 + toZ},
     { 80 + toX, 160 + toY, -25 + toZ},
     {120 + toX, 160 + toY, 75 + toZ },
     {160 + toX, 160 + toY, -80 + toZ}}
                   };

glm::vec3 jardiniere[5][5] = {
        {{  0 + toX, 0 + toY, 0 + toZ },
                { 50 + toX, 0 + toY, 0 + toZ },
                { 100 + toX, 0 + toY, 0 + toZ },
                {150 + toX, 0 + toY, 0 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 50 + toY, 50 + toZ },
                { 50 + toX, 50 + toY, 100 + toZ},
                { 100 + toX, 50 + toY, 100 + toZ},
                {150 + toX, 50 + toY, 50 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 100 + toY, 100 + toZ },
                { 50 + toX, 100 + toY, 150 + toZ},
                { 100 + toX, 100 + toY, 150 + toZ},
                {150 + toX, 100 + toY, 100 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 150 + toY, 0 + toZ },
                { 50 + toX, 150 + toY, 0 + toZ},
                { 100 + toX, 150 + toY, 0 + toZ},
                {150 + toX, 150 + toY, 0 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 0 + toY, 0 + toZ },
                { 0 + toX, 0 + toY, 0 + toZ},
                { 0 + toX, 0 + toY, 0 + toZ},
                {0 + toX, 0 + toY, 0 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}}
};
glm::vec3 petal[5][5] = {
        {{  0 + toX, 0 + toY, 0 + toZ },
                { 50 + toX, 0 + toY, 100 + toZ },
                { 100 + toX, 0 + toY, 100 + toZ },
                {150 + toX, 0 + toY, 0 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 50 + toY, 50 + toZ },
                { 50 + toX, 50 + toY, 150 + toZ},
                { 100 + toX, 50 + toY, 150 + toZ},
                {150 + toX, 50 + toY, 50 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 100 + toY, 50 + toZ },
                { 50 + toX, 100 + toY, 150 + toZ},
                { 100 + toX, 100 + toY, 150 + toZ},
                {150 + toX, 100 + toY, 50 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 150 + toY, 0 + toZ },
                { 50 + toX, 150 + toY, 100 + toZ},
                { 100 + toX, 150 + toY, 100 + toZ},
                {150 + toX, 150 + toY, 0 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 0 + toY, 0 + toZ },
                { 0 + toX, 0 + toY, 0 + toZ},
                { 0 + toX, 0 + toY, 0 + toZ},
                {0 + toX, 0 + toY, 0 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}}
};
glm::vec3 art[4][4] = {
        {{  0 + toX, 150 + toY, 0 + toZ },
                { 50 + toX, 150 + toY, 100 + toZ},
                { 100 + toX, 150 + toY, 50 + toZ},
                {150 + toX, 150 + toY, 150 + toZ }},

        {{  0 + toX, 100 + toY, -50 + toZ },
                { 50 + toX, 100 + toY, 50 + toZ},
                { 100 + toX, 100 + toY, 200 + toZ},
                {150 + toX, 100 + toY, 100 + toZ }},

        {{  0 + toX, 50 + toY, 50 + toZ },
                { 50 + toX, 50 + toY, 150 + toZ},
                { 100 + toX, 50 + toY, 100 + toZ},
                {150 + toX, 50 + toY, 0 + toZ }},

        {{  0 + toX, 0 + toY, 100 + toZ },
                { 50 + toX, 0 + toY, 0 + toZ },
                { 100 + toX, 0 + toY, -50 + toZ },
                {150 + toX, 0 + toY, 50 + toZ }}

};
glm::vec3 gearGap[5][5] = {
        {{  0 + toX, 0 + toY, 0 + toZ },
                { 50 + toX, 0 + toY, 0 + toZ },
                { 100 + toX, 0 + toY, 0 + toZ },
                {150 + toX, 0 + toY, 0 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 50 + toY, 0 + toZ },
                { 50 + toX, 50 + toY, -50 + toZ},
                { 100 + toX, 50 + toY, -50 + toZ},
                {150 + toX, 50 + toY, 0 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 100 + toY, 0 + toZ },
                { 50 + toX, 100 + toY, 50 + toZ},
                { 100 + toX, 100 + toY, 50 + toZ},
                {150 + toX, 100 + toY, 0 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 150 + toY, 0 + toZ },
                { 50 + toX, 150 + toY, 0 + toZ},
                { 100 + toX, 150 + toY, 0 + toZ},
                {150 + toX, 150 + toY, 0 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}},

        {{  0 + toX, 0 + toY, 0 + toZ },
                { 0 + toX, 0 + toY, 0 + toZ},
                { 0 + toX, 0 + toY, 0 + toZ},
                {0 + toX, 0 + toY, 0 + toZ },
                {0 + toX, 0 + toY, 0 + toZ}}
};
glm::vec3 control_sphere[5][5] = {
        {{50+toX, 50+toY, 0+toZ},{100+toX, 50+toY, 50+toZ},{150+toX, 50+toY, 0+toZ},{200+toX, 50+toY, 0+toZ},{0+toX,0+toY,0+toZ}},
        {{50+toX, 100+toY, 50+toZ},{100+toX, 100+toY, 150+toZ},{150+toX, 100+toY, 50+toZ},{200+toX, 100+toY, 0+toZ},{0+toX,0+toY,0+toZ}},
        {{50+toX, 150+toY, 0+toZ},{100+toX, 150+toY, 50+toZ},{150+toX, 150+toY, 0+toZ},{200+toX, 150+toY, 0+toZ},{0+toX,0+toY,0+toZ}},
        {{50+toX, 200+toY, 0+toZ},{100+toX, 200+toY, 0+toZ},{150+toX, 200+toY, 0+toZ},{200+toX, 200+toY, 0+toZ},{0+toX,0+toY,0+toZ}},
        {{50+toX, 250+toY, 0+toZ},{100+toX, 250+toY, 0+toZ},{150+toX, 250+toY, 0+toZ},{200+toX, 250+toY, 0+toZ},{0+toX,0+toY,0+toZ}}
};
glm::vec3 pouch[5][5] = {
        {{0.0+toX,-90+toY,0.0+toZ},{-80+toX,-70+toY,60+toZ},{-80+toX,-40+toY,80+toZ},{0.0+toX,0.0+toY,90+toZ},{0.0+toX,0.0+toY,0.0+toZ}},
        {{-80+toX,-50+toY,-30+toZ},{-80+toX,-30+toY,10+toZ},{-80+toX,-10+toY,50+toZ},{-80+toX,20+toY,60+toZ},{0.0+toX,0.0+toY,0.0+toZ}},
        {{-80+toX,-20+toY,-50+toZ},{-80+toX,-10+toY,-30+toZ},{-80+toX,30+toY,20+toZ},{-80+toX,60+toY,20+toZ},{0.0+toX,0.0+toY,0.0+toZ}},
        {{0.0+toX,0.0+toY,-90+toZ},{-80+toX,40+toY,-80+toZ},{-80+toX,70+toY,-60+toZ},{0.0+toX,90+toY,0.0+toZ},{0.0+toX,0.0+toY,0.0+toZ}},
        {{0.0+toX,0.0+toY,0.0+toZ},{0.0+toX,0.0+toY,0.0+toZ},{0.0+toX,0.0+toY,0.0+toZ},{0.0+toX,0.0+toY,0.0+toZ},{0.0+toX,0.0+toY,0.0+toZ}}
};



glm::vec3 sample1[5][5] = {
{{100+toX,150+toY,160+toZ},{160+toX,110+toY,100+toZ},{110+toX,160+toY,170+toZ},{170+toX,120+toY,110+toZ},{0.0f+toX,0.0f+toY,0.0f+toZ}},
{{120+toX,170+toY,180+toZ},{180+toX,130+toY,120+toZ},{130+toX,180+toY,190+toZ},{190+toX,140+toY,130+toZ},{0.0f+toX,0.0f+toY,0.0f+toZ}},
{{150+toX,200+toY,210+toZ},{210+toX,160+toY,150+toZ},{160+toX,210+toY,220+toZ},{220+toX,170+toY,160+toZ},{0.0f+toX,0.0f+toY,0.0f+toZ}},
{{170+toX,220+toY,230+toZ},{230+toX,180+toY,170+toZ},{180+toX,230+toY,240+toZ},{240+toX,190+toY,180+toZ},{0.0f+toX,0.0f+toY,0.0f+toZ}},
{{0.0f+toX,0.0f+toY,0.0f+toZ},{0.0f+toX,0.0f+toY,0.0f+toZ},{0.0f+toX,0.0f+toY,0.0f+toZ},{0.0f+toX,0.0f+toY,0.0f+toZ},{0.0f+toX,0.0f+toY,0.0f+toZ}}
};
glm::vec3 petalControls[4][4] = { {{-20, 30, 0}, {-15, 40, 0}, {15, 40, 0}, {20, 30, 0}},
        {{-30, 10, 0}, {-20, 20, 10}, {20, 20, 10}, {30, 10, 0}},
        {{-30, -10, 0}, {-20, -5, 10}, {20, -5, 10}, {30, -10, 0}},
        {{-20, -30, 0}, {-15, -20, 0}, {15, -20, 0}, {20, -30, 0}} }; // 花萼控制点
glm::vec3 calyxControls[4][4] = { {{-5, -30, 0}, {-3, -35, 0}, {3, -35, 0}, {5, -30, 0}},
        {{-4, -40, 0}, {-2, -45, 0}, {2, -45, 0}, {4, -40, 0}},
        {{-3, -50, 0}, {-1, -55, 0}, {1, -55, 0}, {3, -50, 0}},
        {{-2, -60, 0}, {-1, -65, 0}, {1, -65, 0}, {2, -60, 0} }}; // 茎控制点
// glm::vec3 stemControls[4][4] = { {{0, -60, 0}, {5, -80, 0}, {-5, -100, 0}, {0, -120, 0}},
//         {{0, -60, 0}, {5, -80, 0}, {-5, -100, 0}, {0, -120, 0}},
//         {{0, -60, 0}, {5, -80, 0}, {-5, -100, 0}, {0, -120, 0}},
//         {{0, -60, 0}, {5, -80, 0}, {-5, -100, 0}, {0, -120, 0}} }; // 创建曲面

void BicubicBezierInit(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid){
    unique_ptr<Bezier33Edge4> patch = make_unique<Bezier33Edge4>(art);
    patch->setColor(_colorP, _colorGrid);

    polygonAllPtr->push_back(std::move(patch));
}
void BicubicBezierInit2(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid){
    toX = -150.f;
    toY = -50.f;
    toZ = 100.f;

        glm::vec3 pouchReverse[4][4] = {
                // 原第1行逆序：j从0→3改为3→0
                {{0.0+toX,0.0+toY,90+toZ}, {-80+toX,-40+toY,80+toZ}, {-80+toX,-70+toY,60+toZ}, {0.0+toX,-90+toY,0.0+toZ}},
                // 原第2行逆序
                {{-80+toX,20+toY,60+toZ}, {-80+toX,-10+toY,50+toZ}, {-80+toX,-30+toY,10+toZ}, {-80+toX,-50+toY,-30+toZ}},
                // 原第3行逆序
                {{-80+toX,60+toY,20+toZ}, {-80+toX,30+toY,20+toZ}, {-80+toX,-10+toY,-30+toZ}, {-80+toX,-20+toY,-50+toZ}},
                // 原第4行逆序
                {{0.0+toX,90+toY,0.0+toZ}, {-80+toX,70+toY,-60+toZ}, {-80+toX,40+toY,-80+toZ}, {0.0+toX,0.0+toY,-90+toZ}}
        };
    unique_ptr<Bezier33Edge4> patch = make_unique<Bezier33Edge4>(pouchReverse);
    patch->setColor(_colorP, _colorGrid);

    polygonAllPtr->push_back(std::move(patch));
}
glm::vec3 rollPart[4][4] = {
        // 原第1行逆序：j从0→3改为3→0
        {{50.f+toX,-9.27051+toY,-28.53170+toZ}, {25.f+toX,-9.27051+toY,-28.53170+toZ},
                {-25.f+toX,-9.27051+toY,-28.53170+toZ}, {-50.f+toX,-9.27051+toY,-28.53170+toZ}},
        // 原第2行逆序
        {{50.f+toX,-24.27051+toY,17.63356+toZ}, {25.f+toX,-24.27051+toY,17.63356+toZ},
                {-25.f+toX,-24.27051+toY,17.63356+toZ}, {-50.f+toX,-24.27051+toY,17.63356+toZ}},
        // 原第3行逆序
        {{50.f+toX,24.27051+toY,17.63356+toZ}, {25.f+toX,24.27051+toY,17.63356+toZ},
                {-25.f+toX,24.27051+toY,17.63356+toZ}, {-50.f+toX,24.27051+toY,17.63356+toZ}},
        // 原第4行逆序
        {{50.f+toX,9.27051+toY,-28.53170+toZ}, {25.f+toX,9.27051+toY,-28.53170+toZ},
                {-25.f+toX,9.27051+toY,-28.53170+toZ}, {-50.f+toX,9.27051+toY,-28.53170+toZ}}
};
glm::vec3 rollPart2[4][4] = {
        // 原第1行逆序：j从0→3改为3→0
        {{90.f+toX,-6.23735+toY,-29.34443+toZ}, {45.f+toX,-6.23735+toY,-29.34443+toZ},
                {-45.f+toX,-6.23735+toY,-29.34443+toZ}, {-90.f+toX,-6.23735+toY,-29.34443+toZ}},
        // 原第2行逆序
        {{90.f+toX,-24.87113+toY,16.77579+toZ}, {45.f+toX,-24.87113+toY,16.77579+toZ},
                {-45.f+toX,-24.87113+toY,16.77579+toZ}, {-90.f+toX,-24.87113+toY,16.77579+toZ}},
        // 原第3行逆序
        {{90.f+toX,24.87113+toY,16.77579+toZ}, {45.f+toX,24.87113+toY,16.77579+toZ},
                {-45.f+toX,24.87113+toY,16.77579+toZ}, {-90.f+toX,24.87113+toY,16.77579+toZ}},
        // 原第4行逆序
        {{90.f+toX,6.23735+toY,-29.34443+toZ}, {45.f+toX,6.23735+toY,-29.34443+toZ},
                {-45.f+toX,6.23735+toY,-29.34443+toZ}, {-90.f+toX,6.23735+toY,-29.34443+toZ}}
};
glm::vec3 pouchReverse[4][4] = {
        // 原第1行逆序：j从0→3改为3→0
        {{0.0,0.0,90}, {-80,-40,80}, {-80,-70,60}, {0.,-90,0.0}},
        // 原第2行逆序
        {{-80,20,60}, {-80,-10,50}, {-80,-30,10}, {-80,-50,-30}},
        // 原第3行逆序
        {{-80,60,20}, {-80,30,20}, {-80,-10,-30}, {-80,-20,-50}},
        // 原第4行逆序
        {{0.,90,0.0}, {-80,70,-60}, {-80,40,-80}, {0.,0.0,-90}}
};
glm::vec3 mirrorMoved1 = {-100.f,-30.f,70.f};
glm::vec3 mirrorMoved2 = {-100.f,-90.f,50.f};
void controlPointsMove(glm::vec3 _src[4][4], glm::vec3 move) {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
             _src[i][j] += move;
        }
    }
}
void Bezier3MirrorInit(vector<unique_ptr<PolygonBase>>* polygonAllPtr,glm::vec3 controlP[4][4], glm::vec3 move,int _colorP, int _colorGrid) {

        controlPointsMove(controlP, move);

        unique_ptr<Bezier33Edge4Mirror> patch = make_unique<Bezier33Edge4Mirror>(controlP);
        patch->setColor(_colorP, _colorGrid);

        polygonAllPtr->push_back(std::move(patch));
}
void Bezier3ImgInit(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid) {
        // toX = -150.f;
        // toY = -50.f;
        // toZ = 0.f;
        //
        // glm::vec3 pouchReverse[4][4] = {
        //         // 原第1行逆序：j从0→3改为3→0
        //         {{0.0+toX,0.0+toY,90+toZ}, {-80+toX,-40+toY,80+toZ}, {-80+toX,-70+toY,60+toZ}, {0.0+toX,-90+toY,0.0+toZ}},
        //         // 原第2行逆序
        //         {{-80+toX,20+toY,60+toZ}, {-80+toX,-10+toY,50+toZ}, {-80+toX,-30+toY,10+toZ}, {-80+toX,-50+toY,-30+toZ}},
        //         // 原第3行逆序
        //         {{-80+toX,60+toY,20+toZ}, {-80+toX,30+toY,20+toZ}, {-80+toX,-10+toY,-30+toZ}, {-80+toX,-20+toY,-50+toZ}},
        //         // 原第4行逆序
        //         {{0.0+toX,90+toY,0.0+toZ}, {-80+toX,70+toY,-60+toZ}, {-80+toX,40+toY,-80+toZ}, {0.0+toX,0.0+toY,-90+toZ}}
        // };
        controlPointsMove(art,mirrorMoved1);
        unique_ptr<Bezier3Img> patch2 = make_unique<Bezier3Img>(art);
        patch2->setColor(_colorP, _colorGrid);

        polygonAllPtr->push_back(std::move(patch2));



}
vector<array<int,16>> teapotIndexs = {
    { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 },
    { 4, 17, 18, 19, 8, 20, 21, 22, 12, 23, 24, 25, 16, 26, 27, 28 },
    { 19, 29, 30, 31, 22, 32, 33, 34, 25, 35, 36, 37, 28, 38, 39, 40 },
    { 31, 41, 42, 1, 34, 43, 44, 5, 37, 45, 46, 9, 40, 47, 48, 13 },
    { 13, 14, 15, 16, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 },
    { 16, 26, 27, 28, 52, 61, 62, 63, 56, 64, 65, 66, 60, 67, 68, 69 },
    { 28, 38, 39, 40, 63, 70, 71, 72, 66, 73, 74, 75, 69, 76, 77, 78 },
    { 40, 47, 48, 13, 72, 79, 80, 49, 75, 81, 82, 53, 78, 83, 84, 57 },
    { 57, 58, 59, 60, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96 },
    { 60, 67, 68, 69, 88, 97, 98, 99, 92, 100, 101, 102, 96, 103, 104, 105 },
    { 69, 76, 77, 78, 99, 106, 107, 108, 102, 109, 110, 111, 105, 112, 113, 114 },
    { 78, 83, 84, 57, 108, 115, 116, 85, 111, 117, 118, 89, 114, 119, 120, 93 },
    { 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136 },
    { 124, 137, 138, 121, 128, 139, 140, 125, 132, 141, 142, 129, 136, 143, 144, 133 },
    { 133, 134, 135, 136, 145, 146, 147, 148, 149, 150, 151, 152, 69, 153, 154, 155 },
    { 136, 143, 144, 133, 148, 156, 157, 145, 152, 158, 159, 149, 155, 160, 161, 69 },
    { 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177 },
    { 165, 178, 179, 162, 169, 180, 181, 166, 173, 182, 183, 170, 177, 184, 185, 174 },
    { 174, 175, 176, 177, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197 },
    { 177, 184, 185, 174, 189, 198, 199, 186, 193, 200, 201, 190, 197, 202, 203, 194 },
    { 204, 204, 204, 204, 207, 208, 209, 210, 211, 211, 211, 211, 212, 213, 214, 215 },
    { 204, 204, 204, 204, 210, 217, 218, 219, 211, 211, 211, 211, 215, 220, 221, 222 },
    { 204, 204, 204, 204, 219, 224, 225, 226, 211, 211, 211, 211, 222, 227, 228, 229 },
    { 204, 204, 204, 204, 226, 230, 231, 207, 211, 211, 211, 211, 229, 232, 233, 212 },
    { 212, 213, 214, 215, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245 },
    { 215, 220, 221, 222, 237, 246, 247, 248, 241, 249, 250, 251, 245, 252, 253, 254 },
    { 222, 227, 228, 229, 248, 255, 256, 257, 251, 258, 259, 260, 254, 261, 262, 263 },
    { 229, 232, 233, 212, 257, 264, 265, 234, 260, 266, 267, 238, 263, 268, 269, 242 },
    { 270, 270, 270, 270, 279, 280, 281, 282, 275, 276, 277, 278, 271, 272, 273, 274 },
    { 270, 270, 270, 270, 282, 289, 290, 291, 278, 286, 287, 288, 274, 283, 284, 285 },
    { 270, 270, 270, 270, 291, 298, 299, 300, 288, 295, 296, 297, 285, 292, 293, 294 },
    { 270, 270, 270, 270, 300, 305, 306, 279, 297, 303, 304, 275, 294, 301, 302, 271 }
};

vector<glm::vec3> teapotVertices = {
    { 1.4000, 0.0000, 2.4000 },
    { 1.4000, -0.7840, 2.4000 },
    { 0.7840, -1.4000, 2.4000 },
    { 0.0000, -1.4000, 2.4000 },
    { 1.3375, 0.0000, 2.5312 },
    { 1.3375, -0.7490, 2.5312 },
    { 0.7490, -1.3375, 2.5312 },
    { 0.0000, -1.3375, 2.5312 },
    { 1.4375, 0.0000, 2.5312 },
    { 1.4375, -0.8050, 2.5312 },
    { 0.8050, -1.4375, 2.5312 },
    { 0.0000, -1.4375, 2.5312 },
    { 1.5000, 0.0000, 2.4000 },
    { 1.5000, -0.8400, 2.4000 },
    { 0.8400, -1.5000, 2.4000 },
    { 0.0000, -1.5000, 2.4000 },
    { -0.7840, -1.4000, 2.4000 },
    { -1.4000, -0.7840, 2.4000 },
    { -1.4000, 0.0000, 2.4000 },
    { -0.7490, -1.3375, 2.5312 },
    { -1.3375, -0.7490, 2.5312 },
    { -1.3375, 0.0000, 2.5312 },
    { -0.8050, -1.4375, 2.5312 },
    { -1.4375, -0.8050, 2.5312 },
    { -1.4375, 0.0000, 2.5312 },
    { -0.8400, -1.5000, 2.4000 },
    { -1.5000, -0.8400, 2.4000 },
    { -1.5000, 0.0000, 2.4000 },
    { -1.4000, 0.7840, 2.4000 },
    { -0.7840, 1.4000, 2.4000 },
    { 0.0000, 1.4000, 2.4000 },
    { -1.3375, 0.7490, 2.5312 },
    { -0.7490, 1.3375, 2.5312 },
    { 0.0000, 1.3375, 2.5312 },
    { -1.4375, 0.8050, 2.5312 },
    { -0.8050, 1.4375, 2.5312 },
    { 0.0000, 1.4375, 2.5312 },
    { -1.5000, 0.8400, 2.4000 },
    { -0.8400, 1.5000, 2.4000 },
    { 0.0000, 1.5000, 2.4000 },
    { 0.7840, 1.4000, 2.4000 },
    { 1.4000, 0.7840, 2.4000 },
    { 0.7490, 1.3375, 2.5312 },
    { 1.3375, 0.7490, 2.5312 },
    { 0.8050, 1.4375, 2.5312 },
    { 1.4375, 0.8050, 2.5312 },
    { 0.8400, 1.5000, 2.4000 },
    { 1.5000, 0.8400, 2.4000 },
    { 1.7500, 0.0000, 1.8750 },
    { 1.7500, -0.9800, 1.8750 },
    { 0.9800, -1.7500, 1.8750 },
    { 0.0000, -1.7500, 1.8750 },
    { 2.0000, 0.0000, 1.3500 },
    { 2.0000, -1.1200, 1.3500 },
    { 1.1200, -2.0000, 1.3500 },
    { 0.0000, -2.0000, 1.3500 },
    { 2.0000, 0.0000, 0.9000 },
    { 2.0000, -1.1200, 0.9000 },
    { 1.1200, -2.0000, 0.9000 },
    { 0.0000, -2.0000, 0.9000 },
    { -0.9800, -1.7500, 1.8750 },
    { -1.7500, -0.9800, 1.8750 },
    { -1.7500, 0.0000, 1.8750 },
    { -1.1200, -2.0000, 1.3500 },
    { -2.0000, -1.1200, 1.3500 },
    { -2.0000, 0.0000, 1.3500 },
    { -1.1200, -2.0000, 0.9000 },
    { -2.0000, -1.1200, 0.9000 },
    { -2.0000, 0.0000, 0.9000 },
    { -1.7500, 0.9800, 1.8750 },
    { -0.9800, 1.7500, 1.8750 },
    { 0.0000, 1.7500, 1.8750 },
    { -2.0000, 1.1200, 1.3500 },
    { -1.1200, 2.0000, 1.3500 },
    { 0.0000, 2.0000, 1.3500 },
    { -2.0000, 1.1200, 0.9000 },
    { -1.1200, 2.0000, 0.9000 },
    { 0.0000, 2.0000, 0.9000 },
    { 0.9800, 1.7500, 1.8750 },
    { 1.7500, 0.9800, 1.8750 },
    { 1.1200, 2.0000, 1.3500 },
    { 2.0000, 1.1200, 1.3500 },
    { 1.1200, 2.0000, 0.9000 },
    { 2.0000, 1.1200, 0.9000 },
    { 2.0000, 0.0000, 0.4500 },
    { 2.0000, -1.1200, 0.4500 },
    { 1.1200, -2.0000, 0.4500 },
    { 0.0000, -2.0000, 0.4500 },
    { 1.5000, 0.0000, 0.2250 },
    { 1.5000, -0.8400, 0.2250 },
    { 0.8400, -1.5000, 0.2250 },
    { 0.0000, -1.5000, 0.2250 },
    { 1.5000, 0.0000, 0.1500 },
    { 1.5000, -0.8400, 0.1500 },
    { 0.8400, -1.5000, 0.1500 },
    { 0.0000, -1.5000, 0.1500 },
    { -1.1200, -2.0000, 0.4500 },
    { -2.0000, -1.1200, 0.4500 },
    { -2.0000, 0.0000, 0.4500 },
    { -0.8400, -1.5000, 0.2250 },
    { -1.5000, -0.8400, 0.2250 },
    { -1.5000, 0.0000, 0.2250 },
    { -0.8400, -1.5000, 0.1500 },
    { -1.5000, -0.8400, 0.1500 },
    { -1.5000, 0.0000, 0.1500 },
    { -2.0000, 1.1200, 0.4500 },
    { -1.1200, 2.0000, 0.4500 },
    { 0.0000, 2.0000, 0.4500 },
    { -1.5000, 0.8400, 0.2250 },
    { -0.8400, 1.5000, 0.2250 },
    { 0.0000, 1.5000, 0.2250 },
    { -1.5000, 0.8400, 0.1500 },
    { -0.8400, 1.5000, 0.1500 },
    { 0.0000, 1.5000, 0.1500 },
    { 1.1200, 2.0000, 0.4500 },
    { 2.0000, 1.1200, 0.4500 },
    { 0.8400, 1.5000, 0.2250 },
    { 1.5000, 0.8400, 0.2250 },
    { 0.8400, 1.5000, 0.1500 },
    { 1.5000, 0.8400, 0.1500 },
    { -1.6000, 0.0000, 2.0250 },
    { -1.6000, -0.3000, 2.0250 },
    { -1.5000, -0.3000, 2.2500 },
    { -1.5000, 0.0000, 2.2500 },
    { -2.3000, 0.0000, 2.0250 },
    { -2.3000, -0.3000, 2.0250 },
    { -2.5000, -0.3000, 2.2500 },
    { -2.5000, 0.0000, 2.2500 },
    { -2.7000, 0.0000, 2.0250 },
    { -2.7000, -0.3000, 2.0250 },
    { -3.0000, -0.3000, 2.2500 },
    { -3.0000, 0.0000, 2.2500 },
    { -2.7000, 0.0000, 1.8000 },
    { -2.7000, -0.3000, 1.8000 },
    { -3.0000, -0.3000, 1.8000 },
    { -3.0000, 0.0000, 1.8000 },
    { -1.5000, 0.3000, 2.2500 },
    { -1.6000, 0.3000, 2.0250 },
    { -2.5000, 0.3000, 2.2500 },
    { -2.3000, 0.3000, 2.0250 },
    { -3.0000, 0.3000, 2.2500 },
    { -2.7000, 0.3000, 2.0250 },
    { -3.0000, 0.3000, 1.8000 },
    { -2.7000, 0.3000, 1.8000 },
    { -2.7000, 0.0000, 1.5750 },
    { -2.7000, -0.3000, 1.5750 },
    { -3.0000, -0.3000, 1.3500 },
    { -3.0000, 0.0000, 1.3500 },
    { -2.5000, 0.0000, 1.1250 },
    { -2.5000, -0.3000, 1.1250 },
    { -2.6500, -0.3000, 0.9375 },
    { -2.6500, 0.0000, 0.9375 },
    { -2.0000, -0.3000, 0.9000 },
    { -1.9000, -0.3000, 0.6000 },
    { -1.9000, 0.0000, 0.6000 },
    { -3.0000, 0.3000, 1.3500 },
    { -2.7000, 0.3000, 1.5750 },
    { -2.6500, 0.3000, 0.9375 },
    { -2.5000, 0.3000, 1.1250 },
    { -1.9000, 0.3000, 0.6000 },
    { -2.0000, 0.3000, 0.9000 },
    { 1.7000, 0.0000, 1.4250 },
    { 1.7000, -0.6600, 1.4250 },
    { 1.7000, -0.6600, 0.6000 },
    { 1.7000, 0.0000, 0.6000 },
    { 2.6000, 0.0000, 1.4250 },
    { 2.6000, -0.6600, 1.4250 },
    { 3.1000, -0.6600, 0.8250 },
    { 3.1000, 0.0000, 0.8250 },
    { 2.3000, 0.0000, 2.1000 },
    { 2.3000, -0.2500, 2.1000 },
    { 2.4000, -0.2500, 2.0250 },
    { 2.4000, 0.0000, 2.0250 },
    { 2.7000, 0.0000, 2.4000 },
    { 2.7000, -0.2500, 2.4000 },
    { 3.3000, -0.2500, 2.4000 },
    { 3.3000, 0.0000, 2.4000 },
    { 1.7000, 0.6600, 0.6000 },
    { 1.7000, 0.6600, 1.4250 },
    { 3.1000, 0.6600, 0.8250 },
    { 2.6000, 0.6600, 1.4250 },
    { 2.4000, 0.2500, 2.0250 },
    { 2.3000, 0.2500, 2.1000 },
    { 3.3000, 0.2500, 2.4000 },
    { 2.7000, 0.2500, 2.4000 },
    { 2.8000, 0.0000, 2.4750 },
    { 2.8000, -0.2500, 2.4750 },
    { 3.5250, -0.2500, 2.4938 },
    { 3.5250, 0.0000, 2.4938 },
    { 2.9000, 0.0000, 2.4750 },
    { 2.9000, -0.1500, 2.4750 },
    { 3.4500, -0.1500, 2.5125 },
    { 3.4500, 0.0000, 2.5125 },
    { 2.8000, 0.0000, 2.4000 },
    { 2.8000, -0.1500, 2.4000 },
    { 3.2000, -0.1500, 2.4000 },
    { 3.2000, 0.0000, 2.4000 },
    { 3.5250, 0.2500, 2.4938 },
    { 2.8000, 0.2500, 2.4750 },
    { 3.4500, 0.1500, 2.5125 },
    { 2.9000, 0.1500, 2.4750 },
    { 3.2000, 0.1500, 2.4000 },
    { 2.8000, 0.1500, 2.4000 },
    { 0.0000, 0.0000, 3.1500 },
    { 0.0000, -0.0020, 3.1500 },
    { 0.0020, 0.0000, 3.1500 },
    { 0.8000, 0.0000, 3.1500 },
    { 0.8000, -0.4500, 3.1500 },
    { 0.4500, -0.8000, 3.1500 },
    { 0.0000, -0.8000, 3.1500 },
    { 0.0000, 0.0000, 2.8500 },
    { 0.2000, 0.0000, 2.7000 },
    { 0.2000, -0.1120, 2.7000 },
    { 0.1120, -0.2000, 2.7000 },
    { 0.0000, -0.2000, 2.7000 },
    { -0.0020, 0.0000, 3.1500 },
    { -0.4500, -0.8000, 3.1500 },
    { -0.8000, -0.4500, 3.1500 },
    { -0.8000, 0.0000, 3.1500 },
    { -0.1120, -0.2000, 2.7000 },
    { -0.2000, -0.1120, 2.7000 },
    { -0.2000, 0.0000, 2.7000 },
    { 0.0000, 0.0020, 3.1500 },
    { -0.8000, 0.4500, 3.1500 },
    { -0.4500, 0.8000, 3.1500 },
    { 0.0000, 0.8000, 3.1500 },
    { -0.2000, 0.1120, 2.7000 },
    { -0.1120, 0.2000, 2.7000 },
    { 0.0000, 0.2000, 2.7000 },
    { 0.4500, 0.8000, 3.1500 },
    { 0.8000, 0.4500, 3.1500 },
    { 0.1120, 0.2000, 2.7000 },
    { 0.2000, 0.1120, 2.7000 },
    { 0.4000, 0.0000, 2.5500 },
    { 0.4000, -0.2240, 2.5500 },
    { 0.2240, -0.4000, 2.5500 },
    { 0.0000, -0.4000, 2.5500 },
    { 1.3000, 0.0000, 2.5500 },
    { 1.3000, -0.7280, 2.5500 },
    { 0.7280, -1.3000, 2.5500 },
    { 0.0000, -1.3000, 2.5500 },
    { 1.3000, 0.0000, 2.4000 },
    { 1.3000, -0.7280, 2.4000 },
    { 0.7280, -1.3000, 2.4000 },
    { 0.0000, -1.3000, 2.4000 },
    { -0.2240, -0.4000, 2.5500 },
    { -0.4000, -0.2240, 2.5500 },
    { -0.4000, 0.0000, 2.5500 },
    { -0.7280, -1.3000, 2.5500 },
    { -1.3000, -0.7280, 2.5500 },
    { -1.3000, 0.0000, 2.5500 },
    { -0.7280, -1.3000, 2.4000 },
    { -1.3000, -0.7280, 2.4000 },
    { -1.3000, 0.0000, 2.4000 },
    { -0.4000, 0.2240, 2.5500 },
    { -0.2240, 0.4000, 2.5500 },
    { 0.0000, 0.4000, 2.5500 },
    { -1.3000, 0.7280, 2.5500 },
    { -0.7280, 1.3000, 2.5500 },
    { 0.0000, 1.3000, 2.5500 },
    { -1.3000, 0.7280, 2.4000 },
    { -0.7280, 1.3000, 2.4000 },
    { 0.0000, 1.3000, 2.4000 },
    { 0.2240, 0.4000, 2.5500 },
    { 0.4000, 0.2240, 2.5500 },
    { 0.7280, 1.3000, 2.5500 },
    { 1.3000, 0.7280, 2.5500 },
    { 0.7280, 1.3000, 2.4000 },
    { 1.3000, 0.7280, 2.4000 },
    { 0.0000, 0.0000, 0.0000 },
    { 1.5000, 0.0000, 0.1500 },
    { 1.5000, 0.8400, 0.1500 },
    { 0.8400, 1.5000, 0.1500 },
    { 0.0000, 1.5000, 0.1500 },
    { 1.5000, 0.0000, 0.0750 },
    { 1.5000, 0.8400, 0.0750 },
    { 0.8400, 1.5000, 0.0750 },
    { 0.0000, 1.5000, 0.0750 },
    { 1.4250, 0.0000, 0.0000 },
    { 1.4250, 0.7980, 0.0000 },
    { 0.7980, 1.4250, 0.0000 },
    { 0.0000, 1.4250, 0.0000 },
    { -0.8400, 1.5000, 0.1500 },
    { -1.5000, 0.8400, 0.1500 },
    { -1.5000, 0.0000, 0.1500 },
    { -0.8400, 1.5000, 0.0750 },
    { -1.5000, 0.8400, 0.0750 },
    { -1.5000, 0.0000, 0.0750 },
    { -0.7980, 1.4250, 0.0000 },
    { -1.4250, 0.7980, 0.0000 },
    { -1.4250, 0.0000, 0.0000 },
    { -1.5000, -0.8400, 0.1500 },
    { -0.8400, -1.5000, 0.1500 },
    { 0.0000, -1.5000, 0.1500 },
    { -1.5000, -0.8400, 0.0750 },
    { -0.8400, -1.5000, 0.0750 },
    { 0.0000, -1.5000, 0.0750 },
    { -1.4250, -0.7980, 0.0000 },
    { -0.7980, -1.4250, 0.0000 },
    { 0.0000, -1.4250, 0.0000 },
    { 0.8400, -1.5000, 0.1500 },
    { 1.5000, -0.8400, 0.1500 },
    { 0.8400, -1.5000, 0.0750 },
    { 1.5000, -0.8400, 0.0750 },
    { 0.7980, -1.4250, 0.0000 },
    { 1.4250, -0.7980, 0.0000 }
};
const int coverStart_th = 20;
const int coverEnd_th = 28;
void BicubicBezierInitUtah1(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid){
        // size_t _end = teapotIndexs.size(); // 壶身
        glm::vec3 _P[4][4];
        float expand = 20.f;
        int index;
        for(size_t i = coverStart_th; i < coverEnd_th; ++i) {
                index = teapotIndexs[i][0] - 1;
                _P[0][0] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][1] - 1;
                _P[0][1] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][2] - 1;
                _P[0][2] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][3] - 1;
                _P[0][3] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][4] - 1;
                _P[1][0] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][5] - 1;
                _P[1][1] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][6] - 1;
                _P[1][2] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][7] - 1;
                _P[1][3] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][8] - 1;
                _P[2][0] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][9] - 1;
                _P[2][1] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][10] - 1;
                _P[2][2] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][11] - 1;
                _P[2][3] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][12] - 1;
                _P[3][0] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][13] - 1;
                _P[3][1] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][14] - 1;
                _P[3][2] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][15] - 1;
                _P[3][3] = transferVec3_(teapotVertices[index]*expand);
                unique_ptr<Bezier33Edge4> patchNow = make_unique<Bezier33Edge4>(_P);
                patchNow->setColor(_colorP, _colorGrid);

                polygonAllPtr->push_back(std::move(patchNow));
        }


}
const int spoutStart_th = 16;
const int spoutEnd_th = 20;
void BicubicBezierInitUtah2(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid){
        // size_t _end = teapotIndexs.size(); // 壶身
        glm::vec3 _P[4][4];
        float expand = 20.f;
        int index;
        for(size_t i = spoutStart_th; i < spoutEnd_th; ++i) {
                index = teapotIndexs[i][0] - 1;
                _P[0][0] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][1] - 1;
                _P[0][1] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][2] - 1;
                _P[0][2] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][3] - 1;
                _P[0][3] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][4] - 1;
                _P[1][0] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][5] - 1;
                _P[1][1] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][6] - 1;
                _P[1][2] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][7] - 1;
                _P[1][3] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][8] - 1;
                _P[2][0] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][9] - 1;
                _P[2][1] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][10] - 1;
                _P[2][2] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][11] - 1;
                _P[2][3] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][12] - 1;
                _P[3][0] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][13] - 1;
                _P[3][1] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][14] - 1;
                _P[3][2] = transferVec3_(teapotVertices[index]*expand);
                index = teapotIndexs[i][15] - 1;
                _P[3][3] = transferVec3_(teapotVertices[index]*expand);
                unique_ptr<Bezier33Edge4> patchNow = make_unique<Bezier33Edge4>(_P);
                patchNow->setColor(_colorP, _colorGrid);

                polygonAllPtr->push_back(std::move(patchNow));
        }


}
void BicubicBezierInitUtah3(vector<unique_ptr<PolygonBase>>* polygonAllPtr, int _colorP, int _colorGrid){
     size_t _end = teapotIndexs.size(); // 壶身
     glm::vec3 _P[4][4];
        float expand = 20.f;int index;
     for(size_t i = 0; i < spoutStart_th; ++i) {
if (i==19||i==18||i==17||i==16)continue;
         index = teapotIndexs[i][0] - 1;
                _P[0][0] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][1] - 1;
                _P[0][1] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][2] - 1;
             _P[0][2] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][3] - 1;
             _P[0][3] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][4] - 1;
             _P[1][0] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][5] - 1;
             _P[1][1] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][6] - 1;
             _P[1][2] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][7] - 1;
             _P[1][3] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][8] - 1;
             _P[2][0] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][9] - 1;
             _P[2][1] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][10] - 1;
             _P[2][2] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][11] - 1;
             _P[2][3] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][12] - 1;
             _P[3][0] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][13] - 1;
             _P[3][1] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][14] - 1;
             _P[3][2] = transferVec3(teapotVertices[index]*expand);
        index = teapotIndexs[i][15] - 1;
             _P[3][3] = transferVec3(teapotVertices[index]*expand);
        unique_ptr<Bezier33Edge4> patchNow = make_unique<Bezier33Edge4>(_P);
        patchNow->setColor(_colorP, _colorGrid);

        polygonAllPtr->push_back(std::move(patchNow));
     }
        for(size_t i = coverEnd_th; i < _end; ++i) {
                index = teapotIndexs[i][0] - 1;
                _P[0][0] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][1] - 1;
                _P[0][1] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][2] - 1;
                _P[0][2] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][3] - 1;
                _P[0][3] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][4] - 1;
                _P[1][0] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][5] - 1;
                _P[1][1] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][6] - 1;
                _P[1][2] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][7] - 1;
                _P[1][3] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][8] - 1;
                _P[2][0] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][9] - 1;
                _P[2][1] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][10] - 1;
                _P[2][2] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][11] - 1;
                _P[2][3] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][12] - 1;
                _P[3][0] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][13] - 1;
                _P[3][1] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][14] - 1;
                _P[3][2] = transferVec3(teapotVertices[index]*expand);
                index = teapotIndexs[i][15] - 1;
                _P[3][3] = transferVec3(teapotVertices[index]*expand);
                unique_ptr<Bezier33Edge4> patchNow = make_unique<Bezier33Edge4>(_P);
                patchNow->setColor(_colorP, _colorGrid);

                polygonAllPtr->push_back(std::move(patchNow));
        }

}
const float goY = 100.f;
glm::vec3 transferVec3(glm::vec3 _src) {
        float tmpZ = _src.z;
        _src.z = _src.y;
        _src.y = -tmpZ;


        _src.y += goY;
        return _src;
}
const float goY_ = 100.f; // 壶盖
glm::vec3 transferVec3_(glm::vec3 _src) {
        float tmpZ = _src.z;
        _src.z = _src.y;
        _src.y = -tmpZ;


        _src.y += goY_;
        return _src;
}
#endif //POLYGONDISPLAY_BECUBICBEZIER_1_H
