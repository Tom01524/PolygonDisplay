//
// Created by iceoc0 on 2024/11/2.
//

#ifndef RECTANGLEDISPLAY_RECT_1_H
#define RECTANGLEDISPLAY_RECT_1_H
// 初始化矩形

#include "screen_1.h"


//AxisXYZ* _spotsXYZ = new AxisXYZ(); // 现在四角 xyz

RectDemo* bodySquare_init(vector<unique_ptr<PolygonBase>>* polygonAllPtr);
void setCenterTipBy3Corner(RectXYZ* corners, bool backFont);
void setCenterBy2Points(RectXYZ* corners);


void rectComonInit( vector<unique_ptr<PolygonBase>>*polygonAllPtr, RectXYZ* rectSpotXYZ, int fontColor,
                   int backColor, bool backFont);
void rectComonInit( vector<unique_ptr<PolygonBase>>*polygonAllPtr, RectXYZ* rectSpotXYZ, int fontColor,
                   int backColor, bool backFont, unsigned char __debug);



glm::vec3 centerXYZ, eyeXYZ;

const float bodyWideX = 100;
const float bodyWideZ = 125;
const float bodyHigh = 300;
float halfBodyWideX = 50;
float halfBodyWideZ = 62.5;
float halfBodyHigh = 150;


RectDemo* bodySquare_init(vector<unique_ptr<PolygonBase>>* polygonAllPtr) {
    if(runningMode == mode._leftView || runningMode == mode._screenGo){
        centerXYZ = screenAndEyeL.center; // 屏幕中心点 简写
        eyeXYZ = screenAndEyeL.centerTip; // 眼睛中心点
    }

    RectXYZ bodyQuarter = RectXYZ(  // 自己脚下
            { centerXYZ.x-halfBodyWideX, windowHeight, halfBodyWideZ + 0.0f},     //lt
            { centerXYZ.x+halfBodyWideX, windowHeight, halfBodyWideZ + 0.0f},      //rt
            { centerXYZ.x-halfBodyWideX, windowHeight, 0.0f + 2},     //lb 深度不减
            { centerXYZ.x+halfBodyWideX, windowHeight, 0.0f + 2},    //rb 深度不减
            { centerXYZ.x,windowHeight - halfBodyHigh,0.0f}, // center
            { 0.0f,0.0f,0.0f}); // centerTip

    unique_ptr<RectDemo> BodySquarePtr = make_unique<RectDemo>(
            glm::vec3{  (bodyQuarter.lt.x),  (bodyQuarter.lt.y),  (bodyQuarter.lt.z) },
            glm::vec3{  (bodyQuarter.rt.x ), (bodyQuarter.rt.y),  (bodyQuarter.rt.z) },
            glm::vec3{  (bodyQuarter.rb.x ), (bodyQuarter.rb.y),  (bodyQuarter.rb.z) },
            glm::vec3{  (bodyQuarter.lb.x ), (bodyQuarter.lb.y),  (bodyQuarter.lb.z) },
            glm::vec3{  bodyQuarter.center.x, bodyQuarter.center.y, bodyQuarter.center.z }, // 身体中心点 渲染顺序
            glm::vec3{  0.0f,0.0f,0.0f },1
    );
    BodySquarePtr->tblrXYZ.lt.y -= bodyHigh; // 身高300
    BodySquarePtr->tblrXYZ.rt.y -= bodyHigh;// 不unchange当上头 +300
    BodySquarePtr->tblrXYZ.lb.y -= bodyHigh;// unchange当作底下 不变
    BodySquarePtr->tblrXYZ.rb.y -= bodyHigh;


    BodySquarePtr->setColor(0xdcf4f9); // 乳白

    polygonAllPtr->push_back(std::move(BodySquarePtr));

    return dynamic_cast<RectDemo*>(polygonAllPtr->back().get());
}



// 两边向量 得到中突向量
void setCenterTipBy3Corner(RectXYZ* corners, bool backFont){
    float _backFront = backFont ? 1.0f : -1.0f;
    // 计算两个边相量         300-500=-200                                      400-400=0
    glm::vec3 lt2rt = {corners->lt.x - corners->rt.x, corners->lt.y - corners->rt.y,
            // 300-300=0
                     corners->lt.z - corners->rt.z};
    // 300-300=0                                400-550=-150
    glm::vec3 lt2lb = {corners->lt.x - corners->lb.x, corners->lt.y - corners->lb.y,
            // 300-300=0
                     corners->lt.z - corners->lb.z};
    // 计算法向量
    float normal[3] = {0};

    normal[0] = lt2lb.y * lt2rt.z - lt2lb.z * lt2rt.y; // lt2lb左 lt2rt右
    normal[1] = lt2lb.z * lt2rt.x - lt2lb.x * lt2rt.z; // x→ y→ z→ x
    normal[2] = lt2lb.x * lt2rt.y - lt2lb.y * lt2rt.x; //
    //cout << "~~normal: " << normal[0] << ", " << normal[1] << ", " << normal[2] << endl;

    // 归一化法向量
    float magnitude = glm::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]); // 30000
    //cout << "magnitude: " << magnitude << endl; // 30000
    normal[0] /= magnitude;
    normal[1] /= magnitude;
    normal[2] /= magnitude; // 30000 / 30000 = 1
    //cout << "normal: " << normal[0] << ", " << normal[1] << ", " << normal[2] << endl;
    // 使用top边与left边的垂直向量作为法向量, 计算centerTip
    corners->centerTip.x = corners->center.x - normal[0] * 20 * _backFront;
    corners->centerTip.y = corners->center.y - normal[1] * 20 * _backFront;
    corners->centerTip.z = corners->center.z - normal[2] * 20 * _backFront;
    //cout << "centerTip: " << corners->centerTip.y << ", " << corners->centerTip.x << ", " << corners->centerTip.z << endl;

}
void setCenterBy2Points(RectXYZ* corners){
    corners->center.x = (corners->lt.x + corners->rb.x) / 2.0f;
    corners->center.y = (corners->lt.y + corners->rb.y) / 2.0f;
    corners->center.z = (corners->lt.z + corners->rb.z) / 2.0f;
}

RectXYZ* rect1SpotXYZ = new RectXYZ(
        { 300.0f,500.0f,50.0f },     //lt y,x,deep
        { 400.0f,500.0f,50.0f },     //rt
        { 300.0f,600.0f,50.0f },     //lb
        { 400.0f,600.0f,50.0f },     //rb
        {0.0f,0.0f,0.0f},     //center
        //{ 400,475,300 },
        //{ 400,475,270 }
        {0.0f,0.0f,0.0f});    //centerTip
RectXYZ* rect2SpotXYZ = new RectXYZ(  // 取右上点 右下点 加点更深
        { 400.0f,500.0f,50.0f },     //lt y,x,deep
        { 400.0f,500.0f,150.0f },     //rt
        { 400.0f,600.0f,50.0f },     //lb
        { 400.0f,600.0f,150.0f },     //rb
        {0.0f,0.0f,0.0f},     //center
        //{ 500,475,350 },
        //{ 530,475,350 }
        {0.0f,0.0f,0.0f}); // centerTip


void rectComonInit( vector<unique_ptr<PolygonBase>>*polygonAllPtr, RectXYZ* rectSpotXYZ, int fontColor, int backColor, bool backFont){
    setCenterBy2Points(rectSpotXYZ);
    setCenterTipBy3Corner(rectSpotXYZ, backFont);
    unique_ptr<RectDemo> RectMain01 = make_unique<RectDemo>(
            glm::vec3{(rectSpotXYZ->lt.x), (rectSpotXYZ->lt.y), (rectSpotXYZ->lt.z) },
            glm::vec3{(rectSpotXYZ->rt.x ), (rectSpotXYZ->rt.y), (rectSpotXYZ->rt.z) },
            glm::vec3{(rectSpotXYZ->rb.x ), (rectSpotXYZ->rb.y), (rectSpotXYZ->rb.z) },
            glm::vec3{(rectSpotXYZ->lb.x ), (rectSpotXYZ->lb.y), (rectSpotXYZ->lb.z) },
            glm::vec3{(rectSpotXYZ->center.x), (rectSpotXYZ->center.y), (rectSpotXYZ->center.z) },
            glm::vec3{(rectSpotXYZ->centerTip.x), (rectSpotXYZ->centerTip.y), (rectSpotXYZ->centerTip.z) },4 // 区分footsquare
    );

    RectMain01->setColor(fontColor); // 霁青 BGR
    RectMain01->setBackColor(backColor); // 草灰绿
    RectMain01->_backFont = backFont ? 1.0f : -1.0f;

    //polygonGot* polygon10001 = new polygonGot(RectMain01,4);
    polygonAllPtr->push_back(std::move(RectMain01));


}
void rectComonInit( vector<unique_ptr<PolygonBase>>*polygonAllPtr, RectXYZ* rectSpotXYZ, int fontColor, int backColor, bool backFont, unsigned char __debug){
//    cout << "rectSportXYZ: " << rectSpotXYZ->lt.y << ", " << rectSpotXYZ->lt.x << ", " << rectSpotXYZ->lt.z << endl;
//    cout << "rectSportXYZ: " << rectSpotXYZ->rt.y << ", " << rectSpotXYZ->rt.x << ", " << rectSpotXYZ->rt.z << endl;
//    cout << "rectSportXYZ: " << rectSpotXYZ->rb.y << ", " << rectSpotXYZ->rb.x << ", " << rectSpotXYZ->rb.z << endl;
//    cout << "rectSportXYZ: " << rectSpotXYZ->lb.y << ", " << rectSpotXYZ->lb.x << ", " << rectSpotXYZ->lb.z << endl;
//    cout << "rectSportXYZ: " << rectSpotXYZ->center.y << ", " << rectSpotXYZ->center.x << ", " << rectSpotXYZ->center.z << endl;
//    cout << "rectSportXYZ: " << rectSpotXYZ->centerTip.y << ", " << rectSpotXYZ->centerTip.x << ", " << rectSpotXYZ->centerTip.z << endl;
    setCenterBy2Points(rectSpotXYZ);
    setCenterTipBy3Corner(rectSpotXYZ, backFont);
//    cout << "_rectSportXYZ: " << rectSpotXYZ->lt.y << ", " << rectSpotXYZ->lt.x << ", " << rectSpotXYZ->lt.z << endl;
//    cout << "_rectSportXYZ: " << rectSpotXYZ->rt.y << ", " << rectSpotXYZ->rt.x << ", " << rectSpotXYZ->rt.z << endl;
//    cout << "_rectSportXYZ: " << rectSpotXYZ->rb.y << ", " << rectSpotXYZ->rb.x << ", " << rectSpotXYZ->rb.z << endl;
//    cout << "_rectSportXYZ: " << rectSpotXYZ->lb.y << ", " << rectSpotXYZ->lb.x << ", " << rectSpotXYZ->lb.z << endl;
//    cout << "_rectSportXYZ: " << rectSpotXYZ->center.y << ", " << rectSpotXYZ->center.x << ", " << rectSpotXYZ->center.z << endl;
//    cout << "_rectSportXYZ: " << rectSpotXYZ->centerTip.y << ", " << rectSpotXYZ->centerTip.x << ", " << rectSpotXYZ->centerTip.z << endl;

    unique_ptr<RectDemo> RectMain01 = make_unique<RectDemo>(
            glm::vec3{rectSpotXYZ->lt.x, (rectSpotXYZ->lt.y), (rectSpotXYZ->lt.z) },
            glm::vec3{rectSpotXYZ->rt.x, (rectSpotXYZ->rt.y), (rectSpotXYZ->rt.z) },
            glm::vec3{rectSpotXYZ->rb.x, (rectSpotXYZ->rb.y), (rectSpotXYZ->rb.z) },
            glm::vec3{rectSpotXYZ->lb.x, (rectSpotXYZ->lb.y), (rectSpotXYZ->lb.z) },
            glm::vec3{rectSpotXYZ->center.x, (rectSpotXYZ->center.y), (rectSpotXYZ->center.z) },
            glm::vec3{rectSpotXYZ->centerTip.x, (rectSpotXYZ->centerTip.y), (rectSpotXYZ->centerTip.z) },4, __debug // 区分footsquare
    );
//    printf("__debug:%hd\n",__debug);

    RectMain01->setColor(fontColor); // 霁青 BGR
    RectMain01->setBackColor(backColor); // 草灰绿
    RectMain01->_backFont = backFont ? 1.0f : -1.0f;

    //polygonGot* polygon10001 = new polygonGot(RectMain01,4);
    polygonAllPtr->push_back(std::move(RectMain01));


}




#endif //RECTANGLEDISPLAY_RECT_1_H
