//
// Created by iceoc0 on 2025/1/27.
//

#ifndef RECTANGLEDISPLAY_FOGDEMO_H
#define RECTANGLEDISPLAY_FOGDEMO_H


#include "./source/ScreenDemo.h"


#ifndef RED
#define	RED				0x0000AA
#endif


#ifndef _BGR3f
#define _BGR3f
class BGR3f{
public:
    BGR3f() = default;
    float b;
    float g;
    float r;
    void setBGR(int _color){
        this->b=(float)((_color>>16)&0xff) / 255.0f;
        this->g=(float)((_color>>8)&0xff) / 255.0f;
        this->r=(float)(_color&0xff) / 255.0f;
    }
};
#endif

#ifndef _angleXYZ
#define _angleXYZ
typedef struct {
    float x; // x转
    float y; // y转
    float deep; // deep转
}angleXYZ_t; // 三维角度
#endif




struct Corner{
    glm::vec3 ltn, rtn, rbn, lbn;
    glm::vec3 ltf, rtf, rbf, lbf;
};


class FogDemo{
public:
    FogDemo() = default;
    FogDemo(glm::vec3 _pos3D, int _color);
    FogDemo(glm::vec3 _pos3D, glm::vec3 _color);
    glm::vec3 pos3D; // 三维坐标
    glm::vec3 virtualPos3D; // 屏幕系三维坐标
    glm::vec2 pos2D; // 二维坐标
    int color; // 颜色
    float colorRGB01[3]; // 颜色
    void Draw_Tick(ScreenDemo* ScreenEye,PolygonBase* _this) const; // 绘制点

};
class FogObjDemo : public PolygonBase {
public:
    FogObjDemo(bool _debugMode);
    glm::vec3 centerPos3D; // 三维坐标
    glm::vec3 virtualCenterPos3D; // 上一次的三维坐标

    Corner allCorner; // 八个顶点坐标
    Corner virtualAllCorner; // 屏幕系的八个顶点坐标

    glm::vec2 centerPos2D; // 二维坐标
    glm::vec2 allCorner2D[8]; // 八个顶点坐标 ltn rtn rbn lbn ltf rtf rbf lbf
    std::vector<unique_ptr<FogDemo>> fogPoints; // 聚合体


    void Draw_Tick(ScreenDemo* ScreenEye); // 绘制对象
    void drawCircleOutline(ScreenDemo* ScreenEye,float centerX, float centerY, float radius, int color, int segments); // 绘制圆轮廓
    void drawCornerLines(); // 绘制八个顶点线
    void centerSet(); //
    void cornerSet(std::pair<float, float> _x, std::pair<float, float> _y, std::pair<float, float> _z); // 计算8个顶点坐标

    void cornerMove(char key, float goStep); // 移动八个顶点

    void switchDebug(); // 切换调试模式
    bool PolyScanClicked(int x,int y); // 点击聚合体



private:
    bool debugMode; // 调试模式

    void cornerGoZ(float goStep);
    void cornerGoY(float goStep);
    void cornerGoX(float goStep);
    void cornerBackZ(float goStep);
    void cornerBackY(float goStep);
    void cornerBackX(float goStep);
};
#endif //RECTANGLEDISPLAY_FOGDEMO_H
