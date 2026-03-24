//
// Created by iceoc0 on 2024/11/9.
//

#ifndef POLYGONDISPLAY_TRIANGLE_1_H
#define POLYGONDISPLAY_TRIANGLE_1_H

#include"../func_main/triangle_func_3D2D.h"
#include"./rect_1.h"
// 任意三角形
// 平衡点_三边中线交点
// 外接圆_三边中垂线交点
// 内接圆_三角平分线交点

// 可用两个直角三角形 组成任意三角形
// 平衡点 将中线分为 1:2 两段
// void setCenterTipBy3Corner_(TriangleXYZ* corners, bool backFont);
// void setCenterBy2Points_(TriangleXYZ* corners);

void triaComonInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr, TriangleXYZ* triangleSpotXYZ, int fontColor, int backColor,
                   bool backFont, int _objName=NULL);
void triaComonInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr, TriangleXYZ* triangleSpotXYZ, int fontColor, int backColor,
                   bool backFont, unsigned char __debug, int _objName=NULL);

inline float imul_a_a(float a);
//POINT couple_faceS = {0, 0};
//POINT couple_faceM = {0, 0};
//POINT couple_faceL = {0, 0};
//POINT couple_balanceCenter = {0, 0};
//POINT couple_centerTip = {0, 0};
bool loadOBJ(const std::string& path,std::vector<glm::vec3>& outVertices,std::vector<glm::ivec3>& outIndices);
void loadMainObj(vector<unique_ptr<PolygonBase>>*polygonAllPtr,string _path);
void loadRooTriangles(vector<unique_ptr<PolygonBase>>*polygonAllPtr);

/*void setCenterTipBy3Corner_(TriangleXYZ* corners, bool backFont){
    float _backFront = backFont ? 1.0f : -1.0f;
    // 计算两个边相量
    glm::vec3 lt2rt = {corners->pC.x - corners->pA.x, corners->pC.y - corners->pA.y,
            //
                     corners->pC.z - corners->pA.z};
    //
    glm::vec3 lt2lb = {corners->pC.x - corners->pB.x, corners->pC.y - corners->pB.y,
            //
                     corners->pC.z - corners->pB.z};
    // 计算法向量
    float normal[3] = {0};
    normal[0] = lt2rt.y * lt2lb.z - lt2rt.z * lt2lb.y; //
    normal[1] = lt2rt.z * lt2lb.x - lt2rt.x * lt2lb.z; //
    normal[2] = lt2rt.x * lt2lb.y - lt2rt.y * lt2lb.x; //
    //cout << "~~normal▲: " << normal[0] << ", " << normal[1] << ", " << normal[2] << endl;

    // 归一化法向量
    float magnitude = glm::sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]); //
    //cout << "magnitude▲: " << magnitude << endl; //
    normal[0] /= magnitude;
    normal[1] /= magnitude;
    normal[2] /= magnitude; //
    //cout << "normal▲: " << normal[0] << ", " << normal[1] << ", " << normal[2] << endl;
    // 使用top边与left边的垂直向量作为法向量, 计算centerTip
    corners->centerTip.x = corners->inCenter.x + normal[0] * 20 * _backFront;
    corners->centerTip.y = corners->inCenter.y + normal[1] * 20 * _backFront;
    corners->centerTip.z = corners->inCenter.z + normal[2] * 20 * _backFront;
    //cout << "centerTip▲: " << corners->centerTip.y << ", " << corners->centerTip.x << ", " << corners->centerTip.z << endl;
}
void setCenterBy2Points_(TriangleXYZ* corners){
    glm::vec3& P_A = corners->pA;
    glm::vec3& P_B = corners->pB;
    glm::vec3& P_C = corners->pC;
    float pa_faceLen = glm::distance(P_B,P_C);
    float pb_faceLen = glm::distance(P_A,P_C);
    float pc_faceLen = glm::distance(P_A,P_B);
    float lenSum = pa_faceLen + pb_faceLen + pc_faceLen;
    if (lenSum < 1e-6) { // 防止三点共线或重合导致除零
        corners->inCenter = (P_A + P_B + P_C) / 3.0f; // 退化为普通  重心
        return;
    }
   // 计算  内心
    corners->inCenter = (corners->pA*pa_faceLen + corners->pB*pb_faceLen + corners->pC*pc_faceLen) / lenSum;

}*/

//struct _autoC_CTip {
//    void (*_setCenterTipBy3Corner)(TriangleXYZ*, bool);
//    void (*_setCenterBy2Points)(TriangleXYZ*);
//};
//struct _autoC_CTip autoC_CTip = {&setCenterTipBy3Corner_, &setCenterBy2Points_};
//void* autoC_CTip_voidptr = (void*)&autoC_CTip;
//extern void* autoC_CTip_voidptr;
const float expand = 100.f;
TriangleXYZ* triangle1SpotXYZ = new TriangleXYZ(
        { 540-expand,580+expand,200 },
        { 600+expand,500-expand,200 },     // rt lb lt auto
        { 540-expand,500-expand,200 }
        );


TriangleXYZ* triangle2SpotXYZ = new TriangleXYZ(
        { 540-expand,580+expand,200 },
        { 600+expand,500-expand,200 },     // rt lb lt auto
        { 600+expand,580+expand,200 }
);
inline float imul_a_a(float a){
    return a * a;
}

void triaComonInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr, TriangleXYZ* triangleSpotXYZ, int fontColor, int backColor, bool backFont, int _objName){

    //printf("-init objName = %hd\n", _objName);
    unique_ptr<TriangleDemo> TriangleMain01 = make_unique<TriangleDemo>(
            glm::vec3{triangleSpotXYZ->pA.x, triangleSpotXYZ->pA.y, triangleSpotXYZ->pA.z },
            glm::vec3{triangleSpotXYZ->pB.x , triangleSpotXYZ->pB.y, triangleSpotXYZ->pB.z },
            glm::vec3{triangleSpotXYZ->pC.x , triangleSpotXYZ->pC.y, triangleSpotXYZ->pC.z },
             _objName
    );

    TriangleMain01->setColor(fontColor); //  BGR
    TriangleMain01->setBackColor(backColor);
    TriangleMain01->_backFont = backFont ? 1.0f : -1.0f;

    //cout << "&TriangleMain01: " << &TriangleMain01 << endl;
    //polygonGot* polygon10001 = new polygonGot(TriangleMain01,3);
    //printf("polygon10001 %p\n", polygon10001);
    polygonAllPtr->push_back(std::move(TriangleMain01));

    //delete triangleSpotXYZ;

}
void triaComonInit(vector<unique_ptr<PolygonBase>>*polygonAllPtr, TriangleXYZ* triangleSpotXYZ, int fontColor, int backColor,
                   bool backFont,unsigned char __debug, int _objName){


    //printf("+init objName = %hd\n", _objName);
    unique_ptr<TriangleDemo> TriangleMain01 = make_unique<TriangleDemo>(
            glm::vec3{triangleSpotXYZ->pA.x, triangleSpotXYZ->pA.y, triangleSpotXYZ->pA.z },
            glm::vec3{triangleSpotXYZ->pB.x , triangleSpotXYZ->pB.y, triangleSpotXYZ->pB.z },
            glm::vec3{triangleSpotXYZ->pC.x , triangleSpotXYZ->pC.y, triangleSpotXYZ->pC.z },
            __debug,
            _objName
    );

    TriangleMain01->setColor(fontColor); //  BGR
    TriangleMain01->setBackColor(backColor);
    TriangleMain01->_backFont = backFont ? 1.0f : -1.0f;

    //cout << "&TriangleMain01: " << &TriangleMain01 << endl;
    //polygonGot* polygon10001 = new polygonGot(TriangleMain01,3);
    //printf("polygon10001 %p\n", polygon10001);
    polygonAllPtr->push_back(std::move(TriangleMain01));

    delete triangleSpotXYZ;

}
bool loadOBJ(const std::string& path,std::vector<glm::vec3>& outVertices,std::vector<glm::ivec3>& outIndices)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        println(stderr, "Failed to open file: {}", path);
        return false;
    }

    std::string line;

    for (;std::getline(file, line);) {

            std::istringstream iss(line);
            std::string prefix;
            iss >> prefix;

            if (prefix == "v") {
                float x, y, z;
                if (!(iss >> x >> y >> z)) {
                    println(stderr, "Invalid vertex line: {}", line);
                    continue;
                }
                outVertices.emplace_back(x, y, z);
            }
            else if (prefix == "f") {
                int v1, v2, v3;
                // OBJ indices are 1-based; we subtract 1 to make them 0-based
                if (!(iss >> v1 >> v2 >> v3)) {
                    println(stderr, "Invalid face line (expecting triangle): {}", line);
                    continue;
                }
                outIndices.emplace_back(v1 - 1, v2 - 1, v3 - 1);
            }


        // 忽略其他行（如 g, s, vt, vn 等）
    }

    file.close();
    return true;
}
void loadMainObj(vector<unique_ptr<PolygonBase>>*polygonAllPtr, string _path) {
    std::vector<glm::vec3> vertices;
    std::vector<glm::ivec3> indexes;
    if (!loadOBJ(_path, vertices, indexes)) {
        println("{} load obj failed", _path);
        return;
    }
    bool backFont = 0; // 不进行反转
    TriangleXYZ tipsNow;
    int fontColor1 = 0x458cf3; // 橙色
    int fontColor2 = 0x854f9e; // 粉色
    int backColor = 0x4b808e;
    bool colorFlag = true;
    for (int i = 0; i < indexes.size(); ++i) {
        tipsNow.pA = vertices[indexes[i][0]];
        tipsNow.pB = vertices[indexes[i][1]];
        tipsNow.pC = vertices[indexes[i][2]];
        tipsNow.pA *= 50.f;
        tipsNow.pB *= 50.f;
        tipsNow.pC *= 50.f;


        unique_ptr<TriangleDemo> TriangleMain01 = make_unique<TriangleDemo>(
        tipsNow.pA,tipsNow.pB,tipsNow.pC);
        if (i % 2 == 0) { // 逢偶换色
            if (colorFlag)colorFlag = false;
            else colorFlag = true;
        }

        if (colorFlag)TriangleMain01->setColor(fontColor1); //  BGR
        else TriangleMain01->setColor(fontColor2);

        TriangleMain01->setBackColor(backColor);
        TriangleMain01->_backFont = backFont ? 1.0f : -1.0f;


        //TriangleMain01->debugLine = 1;

        //cout << "&TriangleMain01: " << &TriangleMain01 << endl;
        //polygonGot* polygon10001 = new polygonGot(TriangleMain01,3);
        //printf("polygon10001 %p\n", polygon10001);
        polygonAllPtr->push_back(std::move(TriangleMain01));
    }
    println("load obj success, size = {}", polygonAllPtr->size());
}
#include"clouds_from.h"
void loadRooTriangles(vector<unique_ptr<PolygonBase>>*polygonAllPtr) {
glm::vec3 xyzMove = {0.f,0.f,0.f};

    int fontColor1 = 0x458cf3; // 橙色
    int fontColor2 = 0x854f9e; // 粉色
    int backColor = 0x4b808e;
    bool colorFlag = true;

    bool backFont = 0; // 不进行反转
    glm::vec3 posNow1, posNow2, posNow3; int cnt = 0;
    for (const glm::ivec3& _th : indexs) {
        posNow1 = points[_th[0]]+xyzMove;
        posNow2 = points[_th[1]]+xyzMove;
        posNow3 = points[_th[2]]+xyzMove;

        unique_ptr<TriangleDemo> TriangleMain01 = make_unique<TriangleDemo>(
       posNow1,posNow2,posNow3);
        if (cnt % 2 == 0) { // 逢偶换色
            if (colorFlag)colorFlag = false;
            else colorFlag = true;
        }

        if (colorFlag)TriangleMain01->setColor(fontColor1); //  BGR
        else TriangleMain01->setColor(fontColor2);

        TriangleMain01->setBackColor(backColor);
        TriangleMain01->_backFont = backFont ? 1.0f : -1.0f;


        TriangleMain01->debugLine = 1;

        //cout << "&TriangleMain01: " << &TriangleMain01 << endl;
        //polygonGot* polygon10001 = new polygonGot(TriangleMain01,3);
        //printf("polygon10001 %p\n", polygon10001);
        polygonAllPtr->push_back(std::move(TriangleMain01));

        cnt++;
    }

    vector<glm::ivec3> void1;
    vector<glm::vec3> void2;
    std::swap(void1, indexs);
    std::swap(void2, points);
}
#endif //POLYGONDISPLAY_TRIANGLE_1_H
