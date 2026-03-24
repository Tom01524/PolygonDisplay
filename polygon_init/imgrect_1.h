//
// Created by iceoc0 on 2025/6/15.
//

#ifndef POLYGONDISPLAY_IMGRECT_1_H
#define POLYGONDISPLAY_IMGRECT_1_H

#include"../polygon_init/bezier33Edge4_1.h"
#include"../polygonClass/ImgRect.h"
const float movedX_ = -600.f,movedY_ = -200.f,movedZ_ = 550.f;
RectXYZ* rect4SpotXYZ = new RectXYZ(
        { 0.0f+movedX_ , 500.0f+movedY_,150.0f+movedZ_ },     //lt y,x,deep
        { 850.0f+movedX_,500.0f+movedY_,150.0f+movedZ_ },     //rt
        { 0.0f+movedX_,  1600.0f+movedY_,150.0f+movedZ_ },     //lb
        { 850.0f+movedX_,1600.0f+movedY_,150.0f+movedZ_ },     //rb
        {0.0f, 0.0f,0.0f},     //center

        {0.0f,0.0f,0.0f}
        );    //centerTip
const float movedX = 500.f,movedY = 650.f,movedZ = 600.f;
RectXYZ* rect5SpotXYZ = new RectXYZ(
        { 0.f+movedX, 0.f+movedY,150.f+movedZ },     //lt y,x,deep
        { 550.f+movedX,0.f+movedY,150.f+movedZ },     //rt
        { 0.f+movedX,720.f+movedY,150.f+movedZ },     //lb
        { 550.f+movedX,720.f+movedY,150.f+movedZ },     //rb
        {0.f,0.f,0.f},     //center

        {0.0f,0.0f,0.0f}
);    //centerTip
void imgRectComonInit(vector<unique_ptr<PolygonBase>>* polygonAllPtr, string _path, RectXYZ* RectTipPos,
                      int fontColor, int backColor,bool backFont);
void imgRectComonInit_WH(vector<unique_ptr<PolygonBase>>* polygonAllPtr, string _path, RectXYZ* RectTipPos,
                      int fontColor, int backColor,bool backFont);
void imgRectComonInit(vector<unique_ptr<PolygonBase>>* polygonAllPtr,  string _path, RectXYZ* RectTipPos,
                      int fontColor, int backColor,bool backFont){
    unique_ptr<ImgRect> ImgRectMain01
    = make_unique<ImgRect>(_path, RectTipPos->lt, RectTipPos->rt, RectTipPos->rb, RectTipPos->lb,  backFont);
    ImgRectMain01->setColor(fontColor);
    ImgRectMain01->setBackColor(backColor);

    polygonAllPtr->push_back(std::move(ImgRectMain01));
}
void imgRectComonInit_WH(vector<unique_ptr<PolygonBase>>* polygonAllPtr, string _path, RectXYZ* RectTipPos,
                         int fontColor, int backColor,bool backFont){
    unique_ptr<ImgRect> ImgRectMain01
    = make_unique<ImgRect>(_path, RectTipPos->lt, RectTipPos->rt, RectTipPos->rb, RectTipPos->lb,  backFont);


    ImgRectMain01->setColor(fontColor);
    ImgRectMain01->setBackColor(backColor);

    polygonAllPtr->push_back(std::move(ImgRectMain01));
}
#endif //POLYGONDISPLAY_IMGRECT_1_H
