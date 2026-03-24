//
// Created by iceoc0 on 2025/11/30.
//

#ifndef POLYGONDISPLAY_BEZIER3MIRROR_H
#define POLYGONDISPLAY_BEZIER3MIRROR_H
#include "Bezier33Edge4.h"


// struct posDir_axisTilt {
//     glm::vec3 pos;
//     goLine32 rayDIr;
// };
struct thisPixelDeep22{
    int x; // 列
    glm::vec2 uv; // 纹理坐标
    glm::vec3 pos_screenAxis; // 曲面表面点 屏幕系
    goLine32 reflectedRay_screenAxis; // 反射光线法向量
    Box4Points* box4Ptr;
    // vector<posDir_axisTilt> posDir_axisTilt;
    float sightLineLen;
    bool faceToCamera;
};

struct rowPixelDeep22 {
    vector<std::expected<thisPixelDeep22,char>> pixelDeeps; // 行的像素深度
    int y; // 行
};

//#define iterationErrors

class Bezier33Edge4Mirror : public Bezier33Edge4 {
public:
    Bezier33Edge4Mirror(glm::vec3 _P[4][4]);
    ~Bezier33Edge4Mirror() = default;

    bool showReflectRays = 1;
    vector<glm::vec3> reflectRaysColors = vector<glm::vec3>(8);
    vector<glm::vec3> reflectRaysColors_ = vector<glm::vec3>(8);


    void solidRectangle2D_(ScreenDemo* ScreenEye,AxisDemo* AxisTilt) override;
    int roundAfterCount;

    float back2Reflect;

    void getCandidatesVU_bySelfBox_randomTwo(glm::vec3& startPos_axisTilt, goLine32& rayDir_axisTilt,
        vector<pair<glm::vec2,Box4Points*>>& candidates);
    float(*getDistanceSquared)(glm::vec3&,glm::vec3&,goLine32&);
    void getCandidatesVU_bySelfBoxCustom(ScreenDemo* ScreenEye,AxisDemo* AxisTilt,
        glm::vec3& startPos_axisTilt, goLine32& rayDir_axisTilt,Box4Points* box4Ptr,
        vector<pair<glm::vec2,Box4Points*>>& candidates);

    std::expected<thisPixelDeep22,char>
    rayIntersect(ScreenDemo* ScreenEye,AxisDemo *AxisTilt, goLine32& rayDir,
             glm::ivec2 pos2D,glm::vec3 _P_[5][5]);
    std::expected<pair<thisPixelDeep22,float>,std::expected<string_view,string>>
    rayIntersectCustom(ScreenDemo* ScreenEye,AxisDemo *AxisTilt, glm::vec3& startP_screenAxis,
        glm::vec3& pGo1_screenAxis,const goLine32& rayDir_screenAxis,glm::vec3& butUVT,Box4Points* box4Ptr,
        glm::vec3 _P_[5][5]);
    void newtonIteration(vector<pair<glm::vec2,Box4Points*>>& vuCandidates,glm::vec3(*_P_)[5],glm::vec3& startPos,goLine32 &rayDir,
        vector<thisPixelDeep22>& solutions);
#ifdef iterationErrors
    void newtonIterationCustom(vector<pair<glm::vec2,Box4Points*>>& vuCandidates,glm::vec3(*_P_)[5],glm::vec3& startPos,
const goLine32 &rayDir, glm::vec3& butUVT,vector<pair<thisPixelDeep22,float>>& solutions,vector<string>&errors);
#else
    void newtonIterationCustom(vector<pair<glm::vec2,Box4Points*>>& vuCandidates,glm::vec3(*_P_)[5],glm::vec3& startPos,
    const goLine32 &rayDir, glm::vec3& butUVT,vector<pair<thisPixelDeep22,float>>& solutions);
#endif
    vector<rowPixelDeep22> _pixelSurfaceInfo;

    void moveFreshStatus() override;

    void drawLastReflect(ScreenDemo *ScreenEye, size_t endOf,
        vector<
        std::expected<pair<thisPixelDeep22,float>, std::expected<string_view,string>>
        >& nearestResults);

    void drawReflectLine(ScreenDemo* ScreenEye,AxisDemo* AxisTilt,thisPixelDeep22& _info, float y);

    void tryNextReflect(ScreenDemo* ScreenEye,AxisDemo* AxisTilt,
    vector<
std::expected<pair<thisPixelDeep22,float>, std::expected<string_view, string>>
    >& _nearestResults,float _back2Reflect,int _th);

    void shotOnBox_AxisTilt_4__(Box4Points& box4Points,glm::vec3& startP_axisTilt, goLine32& rayDirUnit,
        pair<bool,float>* result,bool debug);
    void shotOnBox_AxisTilt_9__(Box9Cube& box4Points,glm::vec3& startP_axisTilt, goLine32& rayDir,
        pair<bool,float>* result,bool debug);

};
#endif //POLYGONDISPLAY_BEZIER3MIRROR_H