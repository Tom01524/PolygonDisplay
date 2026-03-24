//
// Created by iceoc0 on 2024/12/8.
//
#ifndef RECTANGLEDISPLAY_ARROW_1_H
#define RECTANGLEDISPLAY_ARROW_1_H

#include"../polygonClass/TriangleDemo.h"
#include"axis_1.h"
glm::vec3 _top = {450, -300, 595}; // 顶点
glm::vec3 _top2 = {450, -300, 600}; // 顶点2
float scaleX = 0.25f, scaleY = 0.3;

int arrowFrontColor = 0x7e50eb; // 箭头前景色 夹竹桃红
int arrowBackColor = 0x90aab5; // 箭头背景色 银鼠灰
int arrowFrontColor2 = 0x07c3fc;  // 箭头前景色2 金盏黄

class _arrow_type{
public:
    _arrow_type(int a1,int a2){
        arrow1 = a1;
        arrow2 = a2;
    }
    int arrow1;
    int arrow2;
};
_arrow_type* arrow_type = new _arrow_type(0x01,0x02);

void* _top_ptr_go = (void*)&_top;
extern void* _top_ptr_go;

glm::vec3 topRectCenter = {_top.x, _top.y- 50 * scaleY - 20, (_top.z + _top2.z) / 2.0f}; // 矩形中心点
glm::vec3 &trc = topRectCenter; // 矩形中心点


RectXYZ* rectTopXYZ = new RectXYZ(  // 取右上点 右下点 加点更深
        { trc.x- 30 * scaleY, trc.y - 30 * scaleY, trc.z },     //lt
        { trc.x+ 30 * scaleY, trc.y - 30 * scaleY, trc.z },     //rt
        { trc.x- 30 * scaleY, trc.y + 30 * scaleY, trc.z },     //lb
        { trc.x+ 30 * scaleY, trc.y + 30 * scaleY, trc.z },     //rb
        {0.0f,0.0f,0.0f},     //center
        {0.0f,0.0f,0.0f}); // centerTip

glm::vec3 bottomRectCenter = {_top.x, _top.y + (578 + 628) * scaleY + 20, (_top.z + _top2.z) / 2.0f}; // 底部点
glm::vec3 &brc = bottomRectCenter; // 矩形中心点
RectXYZ* rectBottomXYZ = new RectXYZ(  // 矩形只按scaleY
        { brc.x- 30 * scaleY, brc.y - 30 * scaleY, brc.z },     //lt
        { brc.x+ 30 * scaleY, brc.y - 30 * scaleY, brc.z },     //rt
        { brc.x- 30 * scaleY, brc.y + 30 * scaleY, brc.z },     //lb
        { brc.x+ 30 * scaleY, brc.y + 30 * scaleY, brc.z },     //rb
        {0.0f,0.0f,0.0f},     //center
        {0.0f,0.0f,0.0f}); // centerTip

TriangleXYZ* Triangle10001XYZ = new TriangleXYZ(
        { _top.x,_top.y,_top.z},
        { _top.x- 35 * scaleX, _top.y + 184 * scaleY, _top.z },
        { _top.x- 103 * scaleX, _top.y + 134 * scaleY, _top.z }
);
TriangleXYZ* Triangle10002XYZ = new TriangleXYZ(
        { _top.x- 35 * scaleX, _top.y + 184 * scaleY, _top.z},
        { _top.x- 192 * scaleX, _top.y + 250 * scaleY, _top.z },
        {  _top.x- 103 * scaleX, _top.y + 134 * scaleY, _top.z}
);
TriangleXYZ* Triangle10003XYZ = new TriangleXYZ(
        { _top.x,_top.y,_top.z},
        {_top.x,_top.y+ 184 * scaleY, _top.z},
        { _top.x- 35 * scaleX, _top.y + 184 * scaleY, _top.z }
);
TriangleXYZ* Triangle10004XYZ = new TriangleXYZ(
        {_top.x,_top.y,_top.z},
        { _top.x+ 103 * scaleX, _top.y + 134 * scaleY, _top.z },
        { _top.x+ 35 * scaleX, _top.y + 184 * scaleY, _top.z}
);

TriangleXYZ* Triangle10006XYZ = new TriangleXYZ(
        { _top.x+ 103 * scaleX, _top.y + 134 * scaleY, _top.z},
        { _top.x+ 192 * scaleX, _top.y + 250 * scaleY, _top.z },
        { _top.x+ 35 * scaleX, _top.y + 184 * scaleY, _top.z}
);
TriangleXYZ* Triangle10007XYZ = new TriangleXYZ(
        { _top.x,_top.y,_top.z},
        { _top.x+ 35 * scaleX, _top.y + 184 * scaleY, _top.z},
        {_top.x,_top.y+ 184 * scaleY, _top.z}
);
TriangleXYZ* Triangle10008XYZ = new TriangleXYZ(
        { _top.x- 35 * scaleX, _top.y + 184 * scaleY, _top.z},
        { _top.x- 35 * scaleX, _top.y + 419 * scaleY, _top.z},
        { _top.x- 55 * scaleX, _top.y + 419 * scaleY, _top.z}
);

TriangleXYZ* Triangle10010XYZ = new TriangleXYZ(
        { _top.x+ 35 * scaleX, _top.y + 184 * scaleY, _top.z},
        { _top.x+ 55 * scaleX, _top.y + 419 * scaleY, _top.z},
        { _top.x+ 35 * scaleX, _top.y + 419 * scaleY, _top.z}
);
TriangleXYZ* Triangle10011XYZ = new TriangleXYZ(
        { _top.x- 35 * scaleX, _top.y + 184 * scaleY, _top.z},
        { _top.x+ 35 * scaleX, _top.y + 419 * scaleY, _top.z},
        { _top.x- 35 * scaleX, _top.y + 419 * scaleY, _top.z}
);
TriangleXYZ* Triangle10012XYZ = new TriangleXYZ(
        { _top.x- 35 * scaleX, _top.y + 184 * scaleY, _top.z},
        { _top.x+ 35 * scaleX, _top.y + 184 * scaleY, _top.z},
        { _top.x+ 35 * scaleX, _top.y + 419 * scaleY, _top.z}
);
TriangleXYZ* Triangle10013XYZ = new TriangleXYZ(
        { _top.x- 55 * scaleX, _top.y + 419 * scaleY, _top.z},
        {_top.x,_top.y+ 419 * scaleY, _top.z},
        {_top.x,_top.y+ 578 * scaleY, _top.z}
);
TriangleXYZ* Triangle10014XYZ = new TriangleXYZ(
        {_top.x,_top.y+ 419 * scaleY, _top.z},
        { _top.x+ 55 * scaleX, _top.y + 419 * scaleY, _top.z},
        {_top.x,_top.y+ 578 * scaleY, 1 + _top.z}
);
glm::vec3 clockCenter = {_top.x,_top.y+ 578 * scaleY, _top2.z * 2 - _top.z}; // 时钟中心点

TriangleXYZ* Triangle11001XYZ = new TriangleXYZ(
        { _top2.x,_top2.y,_top2.z},
        { _top2.x- 35 * scaleX, _top2.y + 184 * scaleY, _top2.z },
        { _top2.x- 103 * scaleX, _top2.y + 134 * scaleY, _top2.z }
);
TriangleXYZ* Triangle11002XYZ = new TriangleXYZ(
        { _top2.x- 35 * scaleX, _top2.y + 184 * scaleY, _top2.z},
        { _top2.x- 192 * scaleX, _top2.y + 250 * scaleY, _top2.z },
        {  _top2.x- 103 * scaleX, _top2.y + 134 * scaleY, _top2.z}
);
TriangleXYZ* Triangle11003XYZ = new TriangleXYZ(
        { _top2.x,_top2.y,_top2.z},
        {_top2.x,_top2.y+ 184 * scaleY, _top2.z},
        { _top2.x- 35 * scaleX, _top2.y + 184 * scaleY, _top2.z }
);
TriangleXYZ* Triangle11004XYZ = new TriangleXYZ(
        {_top2.x,_top2.y,_top2.z},
        { _top2.x+ 103 * scaleX, _top2.y + 134 * scaleY, _top2.z },
        { _top2.x+ 35 * scaleX, _top2.y + 184 * scaleY, _top2.z}
);

TriangleXYZ* Triangle11006XYZ = new TriangleXYZ(
        { _top2.x+ 103 * scaleX, _top2.y + 134 * scaleY, _top2.z},
        { _top2.x+ 192 * scaleX, _top2.y + 250 * scaleY, _top2.z },
        { _top2.x+ 35 * scaleX, _top2.y + 184 * scaleY, _top2.z}
);
TriangleXYZ* Triangle11007XYZ = new TriangleXYZ(
        { _top2.x,_top2.y,_top2.z},
        { _top2.x+ 35 * scaleX, _top2.y + 184 * scaleY, _top2.z},
        {_top2.x,_top2.y+ 184 * scaleY, _top2.z}
);
TriangleXYZ* Triangle11008XYZ = new TriangleXYZ(
        { _top2.x- 35 * scaleX, _top2.y + 184 * scaleY, _top2.z},
        { _top2.x- 35 * scaleX, _top2.y + 419 * scaleY, _top2.z},
        { _top2.x- 55 * scaleX, _top2.y + 419 * scaleY, _top2.z}
);

TriangleXYZ* Triangle11010XYZ = new TriangleXYZ(
        { _top2.x+ 35 * scaleX, _top2.y + 184 * scaleY, _top2.z},
        { _top2.x+ 55 * scaleX, _top2.y + 419 * scaleY, _top2.z},
        { _top2.x+ 35 * scaleX, _top2.y + 419 * scaleY, _top2.z}
);
TriangleXYZ* Triangle11011XYZ = new TriangleXYZ(
        { _top2.x- 35 * scaleX, _top2.y + 184 * scaleY, _top2.z},
        { _top2.x+ 35 * scaleX, _top2.y + 419 * scaleY, _top2.z},
        { _top2.x- 35 * scaleX, _top2.y + 419 * scaleY, _top2.z}
);
TriangleXYZ* Triangle11012XYZ = new TriangleXYZ(
        { _top2.x- 35 * scaleX, _top2.y + 184 * scaleY, _top2.z},
        { _top2.x+ 35 * scaleX, _top2.y + 184 * scaleY, _top2.z},
        { _top2.x+ 35 * scaleX, _top2.y + 419 * scaleY, _top2.z}
);
TriangleXYZ* Triangle11013XYZ = new TriangleXYZ(
        { _top2.x- 55 * scaleX, _top2.y + 419 * scaleY, _top2.z},
        {_top2.x,_top2.y+ 419 * scaleY, _top2.z},
        {_top2.x,_top2.y+ 578 * scaleY, _top2.z}
);
TriangleXYZ* Triangle11014XYZ = new TriangleXYZ(
        {_top2.x,_top2.y+ 419 * scaleY, _top2.z},
        { _top2.x+ 55 * scaleX, _top2.y + 419 * scaleY, _top2.z},
        {_top2.x,_top2.y+ 578 * scaleY, _top2.z}
);
glm::vec3 bottomCenter = {_top.x,_top.y+ 578 * scaleY, _top.z}; // 箭头底部中心点
glm::vec3 bottomCenter2 = {_top2.x,_top2.y+ 578 * scaleY, _top2.z}; // 箭头底部中心点2

void arrow_1_init( vector<unique_ptr<PolygonBase>>* polygonAll_ptr){
    rectComonInit(polygonAll_ptr, rectTopXYZ,arrowFrontColor,arrowBackColor,false); // 针顶矩形 无debug
    rectComonInit(polygonAll_ptr, rectBottomXYZ,arrowFrontColor2,arrowBackColor,false); // 箭头底部矩形 无debug
    triaComonInit(polygonAll_ptr, Triangle10001XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1); // 夹竹桃红 银鼠灰
    triaComonInit(polygonAll_ptr, Triangle10002XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1);
    triaComonInit(polygonAll_ptr, Triangle10003XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1);
    triaComonInit(polygonAll_ptr, Triangle10004XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1);

    triaComonInit(polygonAll_ptr, Triangle10006XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1);
    triaComonInit(polygonAll_ptr, Triangle10007XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1);
    triaComonInit(polygonAll_ptr, Triangle10008XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1);

    triaComonInit(polygonAll_ptr, Triangle10010XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1);
    triaComonInit(polygonAll_ptr, Triangle10011XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1);
    triaComonInit(polygonAll_ptr, Triangle10012XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1);
    triaComonInit(polygonAll_ptr, Triangle10013XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1);

    triaComonInit(polygonAll_ptr, Triangle10014XYZ,arrowFrontColor,arrowBackColor,true,arrow_type->arrow1);
}
glm::vec3 arrow_2_init(vector<unique_ptr<PolygonBase>>* polygonAll_ptr){
    triaComonInit(polygonAll_ptr, Triangle11001XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2); // 金盏黄 银鼠灰
    triaComonInit(polygonAll_ptr, Triangle11002XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2);
    triaComonInit(polygonAll_ptr, Triangle11003XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2);
    triaComonInit(polygonAll_ptr, Triangle11004XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2); // 不写0进入另一重载函数,默认也是0

    triaComonInit(polygonAll_ptr, Triangle11006XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2);
    triaComonInit(polygonAll_ptr, Triangle11007XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2);
    triaComonInit(polygonAll_ptr, Triangle11008XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2); // 不写0进入另一重载函数,默认也是0

    triaComonInit(polygonAll_ptr, Triangle11010XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2);
    triaComonInit(polygonAll_ptr, Triangle11011XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2);
    triaComonInit(polygonAll_ptr, Triangle11012XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2);
    triaComonInit(polygonAll_ptr, Triangle11013XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2);

    triaComonInit(polygonAll_ptr, Triangle11014XYZ,arrowFrontColor2,arrowBackColor,true,arrow_type->arrow2);

    return clockCenter;
}

#endif //RECTANGLEDISPLAY_ARROW_1_H
