//
// Created by iceoc0 on 2025/1/27.
//
#include "FogDemo.h"
#include <iostream>
//#include <cmath>

struct modeFog{
    char now;char a;char b;char d;
};
extern void* mode_ptr;
modeFog mode_ = *((modeFog*)mode_ptr);


extern void* settled_ptr; // 全局设置的结构体指针
struct _settledFogPoint {
    int _width;
    int _height;
    int _deep;
};
_settledFogPoint* settled_ = (_settledFogPoint*)settled_ptr;
const int screenWidth5 = settled_-> _width;
const int screenHeight5 = settled_-> _height;
const int screenDeep5 = settled_-> _deep;

FogDemo::FogDemo(glm::vec3 _pos3D, int _color) {
    pos3D = _pos3D;

    color = _color;
    BGR3f colorNow1;
    colorNow1.setBGR(_color,1);


    colorRGB01[0] = colorNow1.r1;
    colorRGB01[1] = colorNow1.g1;
    colorRGB01[2] = colorNow1.b1;

}
FogDemo::FogDemo(glm::vec3 _pos3D, glm::vec3 _color){
    pos3D = _pos3D;

    colorRGB01[0] = _color.r;
    colorRGB01[1] = _color.g;
    colorRGB01[2] = _color.b;
}
void FogDemo::Draw_Tick(ScreenDemo* ScreenEye,PolygonBase* _this) const {

    float Px = pos2D.x;
    float Py = pos2D.y;
    if (Px < 0 || Py < 0 || Px >= screenWidth5 || Py >= screenHeight5) {
        return;
    }

    float colorNow[3] = {colorRGB01[0],colorRGB01[1],colorRGB01[2]};
    //cout << "colorNow: " << colorNow[0] << " " << colorNow[1] << " " << colorNow[2] << endl;

    ScreenEye->putPixel(Px,Py,colorNow,virtualPos3D.z,_this);



//    cout << "virtualPos3D.z: " << virtualPos3D.z << endl;


    //printf("FogPoint Draw ( %d %d )",Px,Py);
}

FogObjDemo::FogObjDemo(bool _debugMode):PolygonBase(5) {

//    PolygonBase::type_ = 5; // 雾点类型

    debugMode = _debugMode;

}
void FogObjDemo::Draw_Tick(ScreenDemo* ScreenEye) {
    if(mode_.now == 2){ // 渲染 先后顺序 用得到
        virtualCenterPos3D.x = centerPos3D.x;
        virtualCenterPos3D.y = centerPos3D.y;
        virtualCenterPos3D.z = centerPos3D.z;
    }
    for(auto& fogPoint : fogPoints){
        fogPoint->Draw_Tick(ScreenEye,(PolygonBase*)this);

    }
//    int len = fogPoints.size();
//    for(int i = 0; i < len; ++i) {
//        FogDemo* fogPoint;
//        fogPoint = fogPoints.at(i);
//
//        fogPoint->Draw_Tick();
//    }
    if (debugMode) {
//        setfillcolor(RED); // 雾 的 中点###
//        fillcircle((int)roundf(centerPos2D.x), (int)roundf(centerPos2D.y), 5);
        drawCircleOutline(ScreenEye,centerPos2D.x, centerPos2D.y, 15, RED, 8);

//        drawCornerLines(); // 画八个顶点的线
    }


}
void FogObjDemo::drawCircleOutline(ScreenDemo* ScreenEye,float centerX, float centerY, float radius, int color, int segments) {

    println("画点雾 圈圈");
    BGR3f colorNow1;
    colorNow1.setBGR(color,1);

    vector<glm::vec2> tmp;
    tmp.resize(segments+2);
    float colorNow[3] = {colorNow1.r1, colorNow1.g1, colorNow1.b1};

//    glBegin(GL_LINE_LOOP);
//    glColor3f(colorNow1.r1, colorNow1.g1, colorNow1.b1); // 设置颜色

    for (int i = 0; i < segments; ++i) {
        float angle = 2.0f * (float)M_PI * float(i) / float(segments);  // 计算角度 弧度制
        float x = radius * cosf(angle); // 计算X坐标
        float y = radius * sinf(angle); // 计算Y坐标
        tmp[i].x = centerX + x;
        tmp[i].y = centerY + y;

    }
    for(int i=0;i<segments-1; ++i){
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      tmp[i].x,tmp[i].y,tmp[i+1].x,tmp[i+1].y,
                                      colorNow,virtualCenterPos3D.z-40);
    }

//    glEnd();
}
void FogObjDemo::drawCornerLines(){

    glLineWidth(1.0f); // 线宽
    glBegin(GL_LINES);

    glColor3f(1.f, 1.f, 1.f);
    glVertex2f(allCorner2D[0].x,allCorner2D[0].y);
    glVertex2f(allCorner2D[1].x,allCorner2D[1].y);

    glVertex2f(allCorner2D[1].x,allCorner2D[1].y);
    glVertex2f(allCorner2D[2].x,allCorner2D[2].y);

    glVertex2f(allCorner2D[2].x,allCorner2D[2].y);
    glVertex2f(allCorner2D[3].x,allCorner2D[3].y);

    glVertex2f(allCorner2D[3].x,allCorner2D[3].y);
    glVertex2f(allCorner2D[0].x,allCorner2D[0].y);


    glVertex2f(allCorner2D[4].x,allCorner2D[4].y);
    glVertex2f(allCorner2D[5].x,allCorner2D[5].y);

    glVertex2f(allCorner2D[5].x,allCorner2D[5].y);
    glVertex2f(allCorner2D[6].x,allCorner2D[6].y);

    glVertex2f(allCorner2D[6].x,allCorner2D[6].y);
    glVertex2f(allCorner2D[7].x,allCorner2D[7].y);

    glVertex2f(allCorner2D[7].x,allCorner2D[7].y);
    glVertex2f(allCorner2D[4].x,allCorner2D[4].y);


    glVertex2f(allCorner2D[0].x,allCorner2D[0].y);
    glVertex2f(allCorner2D[4].x,allCorner2D[4].y);

    glVertex2f(allCorner2D[1].x,allCorner2D[1].y);
    glVertex2f(allCorner2D[5].x,allCorner2D[5].y);

    glVertex2f(allCorner2D[2].x,allCorner2D[2].y);
    glVertex2f(allCorner2D[6].x,allCorner2D[6].y);

    glVertex2f(allCorner2D[3].x,allCorner2D[3].y);
    glVertex2f(allCorner2D[7].x,allCorner2D[7].y);

    glEnd();
}




void FogObjDemo::centerSet(){
    size_t len = fogPoints.size();
    if (len == 0) {
        println(stderr,"FogObjDemo::centerSet() error: empty fogPoints");
        return;
    }
    float x_sum = 0, y_sum = 0, z_sum = 0;
    float rightestX = fogPoints[0]->pos3D.x, leftestX = fogPoints[0]->pos3D.x; // 求最要 取[0]
    float highestY = fogPoints[0]->pos3D.y, lowestY = fogPoints[0]->pos3D.y;
    float farestZ = fogPoints[0]->pos3D.z, nearestZ = fogPoints[0]->pos3D.z;

    for(auto& fogPoint : fogPoints){
        if(fogPoint->pos3D.x > rightestX)rightestX = fogPoint->pos3D.x;
        else if(fogPoint->pos3D.x < leftestX)leftestX = fogPoint->pos3D.x;

        if(fogPoint->pos3D.y < highestY)highestY = fogPoint->pos3D.y;
        else if(fogPoint->pos3D.y > lowestY)lowestY = fogPoint->pos3D.y;

        if(fogPoint->pos3D.z > farestZ)farestZ = fogPoint->pos3D.z;
        else if(fogPoint->pos3D.z < nearestZ)nearestZ = fogPoint->pos3D.z;

        x_sum += fogPoint->pos3D.x;
        y_sum += fogPoint->pos3D.y;
        z_sum += fogPoint->pos3D.z;
    }
//    for(int i = 0; i < len; ++i) {
//        FogDemo* fogPoint;
//
//        fogPoint = fogPoints.at(i);
//
//        x_sum += fogPoint->pos3D.x;
//        y_sum += fogPoint->pos3D.y;
//        z_sum += fogPoint->pos3D.z;
//    }

//    std::cout << "x_sum = " << x_sum << std::endl;
//    std::cout << "y_sum = " << y_sum << std::endl;
//    std::cout << "z_sum = " << z_sum << std::endl;
    centerPos3D.x = x_sum / len;
    centerPos3D.y = y_sum / len;
    centerPos3D.z = z_sum / len;
//    std::cout << "centerPos3D = [" << centerPos3D.x << " " << centerPos3D.y << " " << centerPos3D.z
//    << "]" << std::endl;
    cornerSet(std::make_pair(leftestX, rightestX), std::make_pair(highestY, lowestY), std::make_pair(nearestZ, farestZ));
}
void FogObjDemo::cornerSet(std::pair<float, float> _x, std::pair<float, float> _y, std::pair<float, float> _z){
    allCorner.ltn.x = _x.first; // 小 小 小
    allCorner.ltn.y = _y.first;
    allCorner.ltn.z = _z.first;

    allCorner.rtn.x = _x.second; // 大 小 小
    allCorner.rtn.y = _y.first;
    allCorner.rtn.z = _z.first;

    allCorner.rbn.x = _x.second; // 大 大 小
    allCorner.rbn.y = _y.second;
    allCorner.rbn.z = _z.first;

    allCorner.lbn.x = _x.first; // 小 大 小
    allCorner.lbn.y = _y.second;
    allCorner.lbn.z = _z.first;

    allCorner.ltf.x = _x.first; // 小 小 大
    allCorner.ltf.y = _y.first;
    allCorner.ltf.z = _z.second;

    allCorner.rtf.x = _x.second; // 大 小 大
    allCorner.rtf.y = _y.first;
    allCorner.rtf.z = _z.second;

    allCorner.rbf.x = _x.second; // 大 大 大
    allCorner.rbf.y = _y.second;
    allCorner.rbf.z = _z.second;

    allCorner.lbf.x = _x.first; // 小 大 大
    allCorner.lbf.y = _y.second;
    allCorner.lbf.z = _z.second;
}
void FogObjDemo::cornerMove(char key, float goStep){
    switch (key) {
        case 'w':
            cornerGoZ(goStep);
            break;
        case 's':
            cornerGoZ(-goStep);
            break;
        case 'a':
            cornerGoX(-goStep);
            break;
        case 'd':
            cornerGoX(goStep);
            break;
        case 'q':
            cornerGoY(-goStep);
            break;
        case 'e':
            cornerGoY(goStep);
            break;
    }

}
void FogObjDemo::cornerGoZ(float goStep){
    allCorner.ltn.z += goStep;
    allCorner.lbn.z += goStep;
    allCorner.ltf.z += goStep;
    allCorner.lbf.z += goStep;

    allCorner.rtn.z += goStep;
    allCorner.rbn.z += goStep;
    allCorner.rtf.z += goStep;
    allCorner.rbf.z += goStep;
}
void FogObjDemo::cornerGoY(float goStep){
    allCorner.ltn.y += goStep;
    allCorner.rtn.y += goStep;
    allCorner.ltf.y += goStep;
    allCorner.rtf.y += goStep;

    allCorner.lbn.y += goStep;
    allCorner.rbn.y += goStep;
    allCorner.lbf.y += goStep;
    allCorner.rbf.y += goStep;
}
void FogObjDemo::cornerGoX(float goStep){
    allCorner.ltn.x += goStep;
    allCorner.lbn.x += goStep;
    allCorner.ltf.x += goStep;
    allCorner.lbf.x += goStep;

    allCorner.rtn.x += goStep;
    allCorner.rbn.x += goStep;
    allCorner.rtf.x += goStep;
    allCorner.rbf.x += goStep;
}
void FogObjDemo::cornerBackZ(float goStep){
    cornerGoZ(-goStep);
}
void FogObjDemo::cornerBackY(float goStep){
    cornerGoY(-goStep);
}
void FogObjDemo::cornerBackX(float goStep){
    cornerGoX(-goStep);
}


bool FogObjDemo::PolyScanClicked(int x,int y){
    size_t len = fogPoints.size();
    int pos2Dl[2];
    for(int i = 0; i < len; ++i) {
        FogDemo* fogPoint = fogPoints[i].get();
        pos2Dl[0] = (int)roundf(fogPoint->pos2D.x);
        pos2Dl[1] = (int)roundf(fogPoint->pos2D.y);

        if(pos2Dl[0]==x && pos2Dl[1]==y){ // 2D 鼠标点在 雾的 单点class
            std::cout<<"FogPoint ("<<fogPoint->pos2D.x<<","<<fogPoint->pos2D.y<<") 被点击"<<std::endl;
            return true;
        }
    }
    return false;
}
void FogObjDemo::switchDebug(){
    if(debugMode){
        debugMode = false;
        std::cout<<"FogPoint debugLine off"<<std::endl;
    }else{
        debugMode = true;
        std::cout<<"FogPoint debugLine on"<<std::endl;
    }
}

