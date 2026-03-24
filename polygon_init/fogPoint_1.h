//
// Created by iceoc0 on 2025/1/27.
//

#ifndef RECTANGLEDISPLAY_FOGPOINT_1_H
#define RECTANGLEDISPLAY_FOGPOINT_1_H

//#include <string>
#include"./triangle_1.h"

#include "../polygonClass/FogDemo.h" // wish once ONLY


FogObjDemo* fogObjInit(vector<unique_ptr<PolygonBase>>* polygonAllPtr,bool _debug);
FogObjDemo* fogObjCustom1Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 _center,int _color1, bool _debug);
FogObjDemo* fogObjCustom2Init(vector<unique_ptr<PolygonBase>>*polygonAllPtr, glm::vec3 _center,int _color2, bool _debug);
FogObjDemo* fogObjCustom3Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 _center,int _color, bool _debug);
FogObjDemo* fogObjCustom4Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 _center,int _color, bool _debug);
void fogObjInit_roo(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 _center,int _color, bool _debug);



FogObjDemo* fogObjInit(vector<unique_ptr<PolygonBase>>* polygonAllPtr,bool _debug){
    unique_ptr<FogObjDemo> FogObjMain01 = make_unique<FogObjDemo>(_debug);

    polygonAllPtr->push_back(std::move(FogObjMain01));

    return dynamic_cast<FogObjDemo*>(polygonAllPtr->back().get());
}
FogObjDemo* fogObjCustom1Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 _center,int _color1, bool _debug){
    unique_ptr<FogObjDemo> FogObjMain01 = make_unique<FogObjDemo>(_debug);

    glm::vec3 posNow;
    float longitude; // 东西
    float latitude; // 南北
    float R = 140, r = 70; // 半径
    for(longitude=0.0001f;longitude<360.0f;longitude+=1.0f){
        for(latitude=0.0001f;latitude<360.0f;latitude+=45.0f){
            posNow.x = (R + r*cosf(glm::radians(longitude)) ) * cosf(glm::radians(latitude));
            posNow.y = (R + r*cosf(glm::radians(longitude)) ) * sinf(glm::radians(latitude));
            posNow.z = r*sinf(glm::radians(longitude));
            posNow.x += _center.x;
            posNow.y += _center.y;
            posNow.z += _center.z;

//            if(posNow.x*posNow.x+posNow.y*posNow.y+posNow.z*posNow.z<R*R+r*r){ // 点在球内
            unique_ptr<FogDemo> FogPointCurr = make_unique<FogDemo>(posNow,_color1); // 当下雾点
            FogObjMain01->fogPoints.push_back(std::move(FogPointCurr)); // 添加到雾点列表
//            }else{
//
//            }

        }
    }


    FogObjMain01->centerSet(); // 计算中心点

    polygonAllPtr->push_back(std::move(FogObjMain01));
    return dynamic_cast<FogObjDemo*>(polygonAllPtr->back().get());
}
FogObjDemo* fogObjCustom2Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 _center,int _color2, bool _debug){
    unique_ptr<FogObjDemo> FogObjMain01 = make_unique<FogObjDemo>(_debug);

    glm::vec3 posNow;
    float longitude; // 东西
    float latitude; // 南北
    float R = 140, r = 70; // 半径

    for( longitude=0.0001f;longitude<360.0f;longitude+=45.0f) {
        for ( latitude = 0.0001f; latitude < 360.0f; latitude += 1.0f) {
            posNow.x = (R + r * cosf(glm::radians(longitude))) * cosf(glm::radians(latitude));
            posNow.y = (R + r * cosf(glm::radians(longitude))) * sinf(glm::radians(latitude));
            posNow.z = r * sinf(glm::radians(longitude));
            posNow.x += _center.x;
            posNow.y += _center.y;
            posNow.z += _center.z;

            unique_ptr<FogDemo> FogPointCurr = make_unique<FogDemo>(posNow,_color2); // 当下雾点
            FogObjMain01->fogPoints.push_back(std::move(FogPointCurr)); // 添加到雾点列表

        }
    }


    FogObjMain01->centerSet(); // 计算中心点

    polygonAllPtr->push_back(std::move(FogObjMain01));
    return dynamic_cast<FogObjDemo*>(polygonAllPtr->back().get());
}
struct SolvePair {
    double xReal;
    double xImag;
    double yReal;
    double yImag;
};
std::string strip(const std::string &s) {
    // 去除首部空白（包括空格、\t、\n、\r等）
    size_t start = s.find_first_not_of(" \t\n\r");
    // 去除尾部空白
    size_t end = s.find_last_not_of(" \t\n\r");

    // 如果全为空，返回空字符串
    if (start == std::string::npos || end == std::string::npos) {
        println(stderr,"strip()函数：输入字符串全为空白！");
        return "nan";
    }

    return s.substr(start, end - start + 1);
}
void read_out(string filename,vector<SolvePair>* solvePairs){

    namespace fs = std::filesystem;

// 检查文件是否存在
    if (fs::exists(filename)) {
        // 文件操作...
        std::ifstream theFile(filename);
        std::string theLine;

        if (theFile.is_open()) {
            while (getline(theFile, theLine, ';')) { // 逐行读取
                std::istringstream rowNow(theLine);
                std::string varstr;
                for(int i=0; getline(rowNow, varstr, ','); ++i){
                    varstr = strip(varstr);
//                    cout << "varstr: " << varstr << endl;
                    switch (i) {
                        case 0:
                            solvePairs->emplace_back();
                            solvePairs->back().xReal = stod(varstr);
                            break;
                        case 1:
                            solvePairs->back().xImag = stod(varstr);
                            break;
                        case 2:
                            solvePairs->back().yReal = stod(varstr);
                            break;
                        case 3:
                            solvePairs->back().yImag = stod(varstr);
                            break;
                        default:
                            throw std::runtime_error("Invalid input file format");
                            break;
                    }
                }

//                std::cout << theLine << std::endl;
            }
            theFile.close();
        } else {
            println(stderr,"无法打开文件 {}",filename);
        }
    }else{
        println(stderr,"文件不存在 {}",filename);
    }

}
glm::vec3 getColorBy_vY(glm::vec3 color, float _vY){
//    cout << "solve of vY:" << _vY << endl;
    int remainder = static_cast<int>(_vY) % 10; // -9~9
    float colorRatio;
    if(_vY>0){
        colorRatio = 1.f + 0.07f * (float)remainder;
    }else{
        colorRatio = 1.f - 0.07f * (float)remainder;
    }

//    cout << " ~~ remainder = " << remainder << endl;
//    cout << " ~~ colorRatio = " << colorRatio << endl;
    color *= colorRatio;
//    cout << " ~~ color: (" << color.x
//        << ", " << color.y
//        << ", " << color.z << ")" << endl;
    return color;


//    return {0.9f, 0.9f, 0.9f};

}
unique_ptr<vector<SolvePair>> solvePairs = make_unique<vector<SolvePair>>();

FogObjDemo* fogObjCustom3Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 _center,int _color, bool _debug){


    read_out(R"(D:\PycharmProjects\RayOfGammaEquation\output.txt)",solvePairs.get()); // 获取点云信息
    println("clouds have: {}",solvePairs->size());

    glm::vec3 posNow;
    unique_ptr<FogObjDemo> FogObjMain01 = make_unique<FogObjDemo>(_debug);
    for(auto& solvePair:*solvePairs){

        posNow.x = solvePair.xReal;
        posNow.y = solvePair.yReal;
        posNow.z = solvePair.xImag;
        if(isnan(solvePair.xReal) || isnan(solvePair.yReal) ||
        isnan(solvePair.xImag) || isnan(solvePair.yImag))continue;
        posNow.x += _center.x;
        posNow.y += _center.y;
        posNow.z += _center.z;

        BGR3f colorNow1;
        colorNow1.setBGR(_color,1);
        glm::vec3 colorVec3;

        colorVec3.r = colorNow1.r1;
        colorVec3.g = colorNow1.g1;
        colorVec3.b = colorNow1.b1;
        colorVec3 = getColorBy_vY(colorVec3, solvePair.yImag);
//        println("--colorVec3 r={}, g={}, b={}",colorVec3.r,colorVec3.g,colorVec3.b);


        unique_ptr<FogDemo> FogPointCurr = make_unique<FogDemo>(posNow,colorVec3); // 当下雾点
        FogObjMain01->fogPoints.push_back(std::move(FogPointCurr)); // 添加到雾点列表

//        cout << "xReal=" << solvePair.xReal << " xImag=" << solvePair.xImag <<
//             " yReal=" << solvePair.yReal << " yImag=" << solvePair.yImag << endl;
    }


    FogObjMain01->centerSet(); // 计算中心点

    polygonAllPtr->push_back(std::move(FogObjMain01));

    return dynamic_cast<FogObjDemo*>(polygonAllPtr->back().get());
}
glm::vec3 getColorBy_vX(glm::vec3 color, float _vX){
//    cout << "solve of vX:" << _vX << endl;
    int remainder = static_cast<int>(_vX) % 10; // -9~9
    float colorRatio;
    if(_vX>0){
        colorRatio = 1.f + 0.07f * (float)remainder;
    }else{
        colorRatio = 1.f - 0.07f * (float)remainder;
    }
//    cout << " ~~ remainder = " << remainder << endl;
//    cout << " ~~ colorRatio = " << colorRatio << endl;
    color *= colorRatio;
//    cout << " ~~ color: (" << color.x
//        << ", " << color.y
//        << ", " << color.z << ")" << endl;
    return color;


}
FogObjDemo* fogObjCustom4Init(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 _center,int _color, bool _debug){

    glm::vec3 posNow;
    unique_ptr<FogObjDemo> FogObjMain01 = make_unique<FogObjDemo>(_debug);
    for(auto& solvePair:*solvePairs){

        posNow.x = solvePair.xReal;
        posNow.y = solvePair.yReal;
        posNow.z = solvePair.yImag;
        if(isnan(solvePair.xReal) || isnan(solvePair.yReal) ||
           isnan(solvePair.xImag) || isnan(solvePair.yImag))continue;
        posNow.x += _center.x;
        posNow.y += _center.y;
        posNow.z += _center.z;

        BGR3f colorNow1;
        colorNow1.setBGR(_color,1);
        glm::vec3 colorVec3;

        colorVec3.x = colorNow1.r1;
        colorVec3.y = colorNow1.g1;
        colorVec3.z = colorNow1.b1;
        colorVec3 = getColorBy_vX(colorVec3, solvePair.xImag);



        unique_ptr<FogDemo> FogPointCurr = make_unique<FogDemo>(posNow,colorVec3); // 当下雾点
        FogObjMain01->fogPoints.push_back(std::move(FogPointCurr)); // 添加到雾点列表
//        cout << "xReal=" << solvePair.xReal << " xImag=" << solvePair.xImag <<
//             " yReal=" << solvePair.yReal << " yImag=" << solvePair.yImag << endl;
    }

    solvePairs.reset(); // 提前释放

    FogObjMain01->centerSet(); // 计算中心点

    polygonAllPtr->push_back(std::move(FogObjMain01));
    return dynamic_cast<FogObjDemo*>(polygonAllPtr->back().get());;
}
#include"clouds_from.h"
void fogObjInit_roo(vector<unique_ptr<PolygonBase>>* polygonAllPtr, glm::vec3 _center,int _color, bool _debug) {
    

    glm::vec3 posNow1, posNow2, posNow3;
    unique_ptr<FogObjDemo> FogObjMain01 = make_unique<FogObjDemo>(_debug);
    for (const glm::ivec3& _th : indexs) {

        BGR3f colorNow1;
        colorNow1.setBGR(_color, 1);
        glm::vec3 colorVec3;

        colorVec3.x = colorNow1.r1;
        colorVec3.y = colorNow1.g1;
        colorVec3.z = colorNow1.b1;

        posNow1 = points[_th[0]]+_center;
        posNow2 = points[_th[1]]+_center;
        posNow3 = points[_th[2]]+_center;

        unique_ptr<FogDemo> FogPointNow1 = make_unique<FogDemo>(posNow1, colorVec3); // 当下雾点
        FogObjMain01->fogPoints.push_back(std::move(FogPointNow1)); // 添加到雾点列表
        unique_ptr<FogDemo> FogPointNow2 = make_unique<FogDemo>(posNow2, colorVec3); 
        FogObjMain01->fogPoints.push_back(std::move(FogPointNow2));
        unique_ptr<FogDemo> FogPointNow3 = make_unique<FogDemo>(posNow3, colorVec3);
        FogObjMain01->fogPoints.push_back(std::move(FogPointNow3));
    }
    FogObjMain01->centerSet(); // 计算中心点

    polygonAllPtr->push_back(std::move(FogObjMain01));


    vector<glm::ivec3> void1;
    vector<glm::vec3> void2;
    std::swap(void1, indexs);
    std::swap(void2, points);
}
#endif //RECTANGLEDISPLAY_FOGPOINT_1_H
