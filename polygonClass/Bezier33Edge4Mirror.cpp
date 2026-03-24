//
// Created by iceoc0 on 2025/11/30.
//
#include "Bezier33Edge4Mirror.h"

extern void* _3d_2d_go_void_ptr; // 3d_2d_go的函数指针

glm::vec2 (*__3d2dGo_bezierMirror)(ScreenDemo*, glm::vec3, glm::vec3*)
= static_cast<_3d_2d_go_func *>(_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2d_bezierMirror)(ScreenDemo*, float, float, float)
= static_cast<_3d_2d_go_func *>(_3d_2d_go_void_ptr)->_3d_2d; // 模式1 用自己的不行

Bezier33Edge4Mirror::Bezier33Edge4Mirror(glm::vec3 _P[4][4]): Bezier33Edge4(_P, 22) {
    if (this->fastIteration) this->fastIteration = 0;
    if (this->showEdgeRect) this->showEdgeRect = 0;

    reflectRaysColors[0] = {225.f,138.f,174.f};reflectRaysColors[0] /= 255.f;
    reflectRaysColors_[0] = reflectRaysColors[0] * 0.75f;

    reflectRaysColors[1] = {225.f,169.f,138.f};reflectRaysColors[1] /= 255.f;
    reflectRaysColors_[1] = reflectRaysColors[1] * 0.75f;

    reflectRaysColors[2] = {220.f,208.f,125.f};reflectRaysColors[2] /= 255.f;
    reflectRaysColors_[2] = reflectRaysColors[2] * 0.75f;

    reflectRaysColors[3] = {185.f,220.f,125.f};reflectRaysColors[3] /= 255.f;
    reflectRaysColors_[3] = reflectRaysColors[3] * 0.75f;

    reflectRaysColors[3] = {125.f,220.f,197.f};reflectRaysColors[3] /= 255.f;
    reflectRaysColors_[3] = reflectRaysColors[3] * 0.75f;

    roundAfterCount = 0;

    back2Reflect = 300.f;//(this->boxLenX + this->boxLenY + this->boxLenZ) / 3.f;
    // back2Reflect *= 10.f;


    getDistanceSquared = [](glm::vec3& _nowPos, glm::vec3& _startPos, goLine32& ray) {
     glm::vec3 toPoint = _nowPos - _startPos;
     glm::vec3 getCrossed = glm::cross(toPoint, ray._);
     return glm::dot(getCrossed, getCrossed);
    };
}

void Bezier33Edge4Mirror::solidRectangle2D_(ScreenDemo* ScreenEye,AxisDemo* AxisTilt){
    scanBox2D_.setLineBounary(lineScanFillColor_);
    //println("子类 ~~ solidRectangle2D_");

    if(lineScanFillColor_.empty())return;
    //int rowLast = static_cast<int>(lineScanFillColor_.size()) + lineScanFillColor_[0].y;

//    _pixelSurfaceInfo.clear();
//-    bool firstOut = true;
    if(renderNext == 1){

            backRenderRow:
            if(startRowIndex_ < lineScanFillColor_.size()){ // 0based < 1based
                lineBoundary _linePosInfo = lineScanFillColor_[startRowIndex_];
                rowPixelDeep22 rowDeepInfo;


                if (_linePosInfo.rx == _linePosInfo.lx) {
                    // 屏幕外的行 左右x相同

                    startRowIndex_++;
                    goto backRenderRow;
                }
                rowDeepInfo.y =  _linePosInfo.y; // 本行 y

                for(int nowX = (int) roundf(_linePosInfo.lx); nowX <= _linePosInfo.rx; nowX++){
                    // 列 nowX

                    // uv

                    goLine32 sightDir_screenAxis = ScreenDemo::get_AgoB_direction3D(startEye,{nowX,rowDeepInfo.y,0.f});


                    std::expected<thisPixelDeep22,char>
                    _info = rayIntersect(ScreenEye,AxisTilt,
                            sightDir_screenAxis,{nowX,rowDeepInfo.y}, virtual_P);

                    if (_info) {
                        // println("rayIntersect() expected 有解");
                        _info->x = nowX;
                    }

                    // 屏垂距
                    rowDeepInfo.pixelDeeps.emplace_back(_info); // 本行 x deep

                }
                _pixelSurfaceInfo.emplace_back(rowDeepInfo);
                startRowIndex_++;
            }
            // 列 循环
            // glm::vec3 reflectPos3D{};
            // glm::vec2 reflectPos2D{};

            for(int j=0;j< _pixelSurfaceInfo.size();j++) {
                size_t vecSizeCurrent=_pixelSurfaceInfo[j].pixelDeeps.size();
                for (int i = 0; i < vecSizeCurrent; i++) {
                    // 使用 _pixelSurfaceInfo[j].pixelDeeps[i]
                    if (!_pixelSurfaceInfo[j].pixelDeeps[i].has_value()) continue;
                    // println("~~~~像素渲染");
                    int nowX = _pixelSurfaceInfo[j].pixelDeeps[i]->x;
                    float nowDeep = _pixelSurfaceInfo[j].pixelDeeps[i]->pos_screenAxis.z;

                    glm::vec2 nowUV = _pixelSurfaceInfo[j].pixelDeeps[i]->uv;
                    // if(isnan(nowUV[0]) || isnan(nowUV[1]))continue;
                    bool faceFront = _pixelSurfaceInfo[j].pixelDeeps[i]->faceToCamera;

                    float* colorNow = getColorByUV(nowUV);

                    if(colorNow != nullptr){
                        if(faceFront){
                            ScreenEye->putPixel(nowX,_pixelSurfaceInfo[j].y,
                                                colorNow,nowDeep,this);
                            //println("front xy:({},{})",nowX,_pixelSurfaceInfo[j].y);
                            if (showReflectRays) {
                                // 静时 <首轮>
                                if (startRowIndex_ < lineScanFillColor_.size()) {
                                    if (j + 1 == _pixelSurfaceInfo.size()) {
                                        // 反射点
                                        drawReflectLine(ScreenEye,AxisTilt,*_pixelSurfaceInfo[j].pixelDeeps[i],_pixelSurfaceInfo[j].y);
                                    }
                                }else {
                                    // 静时 <后面轮>
                                    // println("j={}, round after count = {}",j,roundAfterCount);
                                    if (j  == roundAfterCount) {
                                        // 反射点
                                        drawReflectLine(ScreenEye,AxisTilt,*_pixelSurfaceInfo[j].pixelDeeps[i],_pixelSurfaceInfo[j].y);
                                    }
                                }
                            }
                        }else{
                            ScreenEye->putPixel(nowX,_pixelSurfaceInfo[j].y,
                                                backColor,nowDeep,this);
                            //println("back xy:({},{})",nowX,_pixelSurfaceInfo[j].y);
                        }


                    }


                }

            }
        if (showReflectRays) {
            // 静时 <首轮>
            if (startRowIndex_ < lineScanFillColor_.size()) {

            }else {
                // 静时 <后面轮>
                roundAfterCount++;
                if (roundAfterCount + 1 >= _pixelSurfaceInfo.size()) {
                    // println("round after count = {}",roundAfterCount);
                    roundAfterCount = 0;
                    // println("--- round after count = {}",roundAfterCount);
                }

            }
        }
        // }

    }

    else {
        // 移动时 三角面近似 无 超越函数 计算

        freshVirtualCloudsFrontBack(); // 预刷新 400点 正反朝向
        // 动态 前帧
        // 赋予 屏幕系 四点
        for(int i=0;i<N_v-1;i++) {
            for(int j=0;j<N_u-1;j++) {
                rect2Flats(i, j).freshTriangle(ScreenEye,virtual_Grid(i,j),virtual_Grid(i,j+1),
                    virtual_Grid(i+1,j),virtual_Grid(i+1,j+1));
                if ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0)) {
                    rect2Flats(i, j).draw2Triangle(ScreenEye,colorP,backColor,this);
                }else {
                    rect2Flats(i, j).draw2Triangle(ScreenEye,colorGrid,backColor,this);
                }
            }

        }
        if (!settledColorGrid70) {
            colorGrid_70[0] = colorGrid[0]*0.7f;
            colorGrid_70[1] = colorGrid[1]*0.7f;
            colorGrid_70[2] = colorGrid[2]*0.7f;
            settledColorGrid70 = false;
        }

        for(int i=0;i<rect2Flats_Top.size();i++) {
            rect2Flats_Top[i].freshTriangle(ScreenEye,virtual_Grid_edgeTop[i],virtual_Grid_edgeTop[i+1],
            virtual_Grid(0,i),virtual_Grid(0,i+1));
            if (showEdgeRect) {
                if (i % 2 == 0 ) {

                    rect2Flats_Top[i].draw2Triangle(ScreenEye,colorP_70,colorP_70,this);

                }else {

                    rect2Flats_Top[i].draw2Triangle(ScreenEye,colorGrid_70,colorGrid_70,this);

                }
            }

        }
        for(int i=0;i<rect2Flats_Bottom.size();i++) {
            rect2Flats_Bottom[i].freshTriangle(ScreenEye,virtual_Grid_edgeBottom[i],virtual_Grid_edgeBottom[i+1],
            virtual_Grid(N_v-1,i),virtual_Grid(N_v-1,i+1));
            if (showEdgeRect) {
                if ((i % 2 != 0 && N_v % 2 != 0) || (i % 2 == 0 && N_v % 2 == 0)) {

                    rect2Flats_Bottom[i].draw2Triangle(ScreenEye,colorP_70,colorP_70,this);

                }else {

                    rect2Flats_Bottom[i].draw2Triangle(ScreenEye,colorGrid_70,colorGrid_70,this);

                }
            }

        }
        for(int i=0;i<rect2Flats_Left.size();i++) {
            rect2Flats_Left[i].freshTriangle(ScreenEye,virtual_Grid_edgeLeft[i],virtual_Grid_edgeLeft[i+1],
            virtual_Grid(i,0),virtual_Grid(i+1,0));
            if (showEdgeRect) {
                if ((i % 2 != 0 && N_u % 2 != 0) || (i % 2 == 0 && N_u % 2 == 0)) {

                    rect2Flats_Left[i].draw2Triangle(ScreenEye,colorP_70,colorP_70,this);

                }else {

                    rect2Flats_Left[i].draw2Triangle(ScreenEye,colorGrid_70,colorGrid_70,this);

                }
            }

        }
        for(int i=0;i<rect2Flats_Right.size();i++) {
            rect2Flats_Right[i].freshTriangle(ScreenEye,virtual_Grid_edgeRight[i],virtual_Grid_edgeRight[i+1],
            virtual_Grid(i,N_u-1),virtual_Grid(i+1,N_u-1));
            if (showEdgeRect) {
                if ((i % 2 != 0 && N_u % 2 != 0) || (i % 2 == 0 && N_u % 2 == 0)) {

                    rect2Flats_Right[i].draw2Triangle(ScreenEye,colorP_70,colorP_70,this);
                }else {
                    rect2Flats_Right[i].draw2Triangle(ScreenEye,colorGrid_70,colorGrid_70,this);

                }
            }

        }


    }

}

void Bezier33Edge4Mirror::getCandidatesVU_bySelfBox_randomTwo(glm::vec3& startPos_axisTilt, goLine32& rayDir_axisTilt,
    vector<pair<glm::vec2,Box4Points*>>& candidates) {

    // glm::vec3 transferPos;
    // screenAxis2axisTilt(ScreenEye, AxisTilt, &screenPos, &transferPos);
    //
    //
    // goLine32 rayUnit_axisTilt = glm::normalize(transferPos - startEye_axisTilt);
    pair<bool,float> shotBox_distance;
    glm::vec2 nowUV,nowVU;

    // vector<glm::vec2> res3; // 点线 最近 前7
    //cout << "--------------------\n";
    vector<Box4Points*> currentBox4Points; // 中盒 找小盒

    for (int outter = 0;outter < box9Row;outter++) {
        for (int inner = 0;inner < box9Col;inner++) {
            // indexNow = outter * this-> box9Col + inner;
             shotOnBox_AxisTilt_9__(box9Cubes(outter, inner), startPos_axisTilt,rayDir_axisTilt,
                 &shotBox_distance,false);
            if (!shotBox_distance.first) continue;
            //midBoxGot++;
            for (Box4Points* smallBox : box9Cubes(outter, inner).box4_P) {
                currentBox4Points.push_back(smallBox);
            }
        }
    }
    vector<int> singleIndexHave;int singleIndex;
    for (Box4Points* tinyBox : currentBox4Points) { // 小盒 找云索引

        shotOnBox_AxisTilt_4__(*tinyBox, startPos_axisTilt,rayDir_axisTilt,&shotBox_distance,false);

        if (!shotBox_distance.first) continue;

        class std::random_device rd;  // 获取一个随机数，作为种子
        std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数
        // 定义一个均匀分布的范围
        class std::uniform_int_distribution<> distr(0,3);
        int randomIndex = distr(gen);
        nowUV = virtual_Grid(tinyBox->cloudsIndex[randomIndex].x,tinyBox->cloudsIndex[randomIndex].y).uv ; // u 列 v 行
        nowVU[0] = nowUV[1];
        nowVU[1] = nowUV[0];

        singleIndex = tinyBox->cloudsIndex[randomIndex].x * virtual_Grid.innerMax + tinyBox->cloudsIndex[randomIndex].y;

        if (!isIn(singleIndexHave,singleIndex)) {
            // 没有 一维索引 加进去
            singleIndexHave.push_back(singleIndex);
            candidates.emplace_back(make_pair(nowVU,tinyBox));
        }//else println(stderr," 一次射中 重复的 一维索引 !!!");

        randomIndex = randomIndex == 3 ? 2 : randomIndex + 1;
        nowUV = virtual_Grid(tinyBox->cloudsIndex[randomIndex].x,tinyBox->cloudsIndex[randomIndex].y).uv ; // u 列 v 行
        nowVU[0] = nowUV[1];
        nowVU[1] = nowUV[0];

        singleIndex = tinyBox->cloudsIndex[randomIndex].x * virtual_Grid.innerMax + tinyBox->cloudsIndex[randomIndex].y;

        if (!isIn(singleIndexHave,singleIndex)) {
            // 没有 一维索引 加进去
            singleIndexHave.push_back(singleIndex);
            candidates.emplace_back(make_pair(nowVU,tinyBox));
        }//else println(stderr," 一次射中 重复的 一维索引 !!!");
    }

}

// function<float(glm::vec3&,glm::vec3&,goLine32&)>
// getDistanceSquared2 = [](glm::vec3& _nowPos, glm::vec3& _startPos, goLine32& ray) {
//         float a=-ray.dx, b=-ray.dy, c=-ray.dz;
//             // d = -ax - by - cz
//         float d = -a*_nowPos.x - b*_nowPos.y - c*_nowPos.z;
//         float startEye2Flat_Far = -a*_startPos.x - b*_startPos.y - c*_startPos.z - d;
//
//         float c22 = glm::dot(_nowPos - _startPos, _nowPos - _startPos);
//         float b22 = startEye2Flat_Far * startEye2Flat_Far;
//
//         return c22 - b22;
// }; XXXXXXXXXXX

void Bezier33Edge4Mirror::getCandidatesVU_bySelfBoxCustom(ScreenDemo* ScreenEye,AxisDemo* AxisTilt,
    glm::vec3& startPos_axisTilt, goLine32& rayDir_axisTilt,Box4Points* box4Ptr, vector<pair<glm::vec2,Box4Points*>>& candidates) {
    // println("getCandidatesVU_bySelfBox_nearestOne~~~~");
    pair<bool,float> shotBox_distance;
    glm::vec2 nowUV,nowVU;

    // vector<glm::vec2> res3; // 点线 最近 前7

    //cout << "--------------------\n";
    vector<Box4Points*> currentBox4Points; // 中盒 找小盒

    for (int outter = 0;outter < box9Row;outter++) {
        for (int inner = 0;inner < box9Col;inner++) {
            // indexNow = outter * this-> box9Col + inner;
            shotOnBox_AxisTilt_9__(box9Cubes(outter, inner), startPos_axisTilt,rayDir_axisTilt,
                &shotBox_distance,true);
            if (!shotBox_distance.first) {
                continue;
            }
            // println("反射 box9 射中");

            //midBoxGot++;
            for (Box4Points* smallBox : box9Cubes(outter, inner).box4_P) {
                currentBox4Points.push_back(smallBox);
            }
        }
    }
    vector<int> singleIndexHave;int singleIndex;
    for (Box4Points* tinyBox : currentBox4Points) {
        // 小盒 找云索引
        // if (tinyBox == box4Ptr) {
        //     // 自己包围盒 后撤了 回看不迭代  ╮(╯▽╰)╭
        //
        //     // println(stderr," 二次反射 在自己当前的 包围盒 !!!");
        //      continue;
        // }

        shotOnBox_AxisTilt_4__(*tinyBox, startPos_axisTilt,rayDir_axisTilt,&shotBox_distance,true);
        if (!shotBox_distance.first) continue;
        // println("反射 box4 射中");


        // class std::random_device rd;  // 获取一个随机数，作为种子
        // std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数
        // // 定义一个均匀分布的范围
        // class std::uniform_int_distribution<> distr(0,3);
        // int randomIndex = distr(gen);
        // int _04 = 0;
        for (int _04=0;_04<4;++_04) { // 二次反射计算 盒内每个点 去重后算一遍
            nowUV = virtual_Grid(tinyBox->cloudsIndex[_04].x,tinyBox->cloudsIndex[_04].y).uv ; // u 列 v 行
            nowVU[0] = nowUV[1];
            nowVU[1] = nowUV[0];

            singleIndex = tinyBox->cloudsIndex[_04].x * virtual_Grid.innerMax + tinyBox->cloudsIndex[_04].y;

            if (!isIn(singleIndexHave,singleIndex)) {
                // 没有 一维索引 加进去
                singleIndexHave.push_back(singleIndex);
                candidates.emplace_back(make_pair(nowVU,tinyBox));
            }//else println(stderr," 二次反射 重复的 一维索引 !!!");
        }



        //else println(stderr," 二次反射 重复的 一维索引 !!!");

        /*glm::vec3 nowPos_ScreenAxis, nowPos_axisTilt;

        float distanceSquaredNow;
        struct _infoP {
            float p2Ray_22;
            glm::vec2 vu;
            int inOrder;
        };
        array<_infoP,4> distance_all;
        // float closestDistance;//, closestIndex;

 // 0

        nowPos_ScreenAxis = virtual_Grid(tinyBox->cloudsIndex[0].x,tinyBox->cloudsIndex[0].y).pos;
        screenAxis2axisTilt(ScreenEye, AxisTilt, &nowPos_ScreenAxis, &nowPos_axisTilt);

        distanceSquaredNow = getDistanceSquared(nowPos_axisTilt,startPos_axisTilt,rayDir_axisTilt);
        // println("clouds far ray 0: {}",sqrt(distanceSquaredNow));

        // distanceSquaredNow = getDistanceSquared2(nowPos_axisTilt,startPos_axisTilt,rayDir_axisTilt);
        // println("--clouds far ray 0: {}",sqrt(distanceSquaredNow));

        // 刷新出 离线 最近的 vu

        // closestIndex = 0;

        nowUV = virtual_Grid(tinyBox->cloudsIndex[0].x,tinyBox->cloudsIndex[0].y).uv ; // u 列 v 行
        nowVU[0] = nowUV[1];
        nowVU[1] = nowUV[0];
        distance_all[0] = {distanceSquaredNow,nowVU,0};
// 1
        nowPos_ScreenAxis = virtual_Grid(tinyBox->cloudsIndex[1].x,tinyBox->cloudsIndex[1].y).pos;
        screenAxis2axisTilt(ScreenEye, AxisTilt, &nowPos_ScreenAxis, &nowPos_axisTilt);

        distanceSquaredNow = getDistanceSquared(nowPos_axisTilt,startPos_axisTilt,rayDir_axisTilt);
        // println("clouds far ray 1: {}",sqrt(distanceSquaredNow));

            // closestIndex = 1;
            nowUV = virtual_Grid(tinyBox->cloudsIndex[1].x,tinyBox->cloudsIndex[1].y).uv ; // u 列 v 行
            nowVU[0] = nowUV[1];
            nowVU[1] = nowUV[0];

        distance_all[1] = {distanceSquaredNow,nowVU,1};
// 2
        nowPos_ScreenAxis = virtual_Grid(tinyBox->cloudsIndex[2].x,tinyBox->cloudsIndex[2].y).pos;
        screenAxis2axisTilt(ScreenEye, AxisTilt, &nowPos_ScreenAxis, &nowPos_axisTilt);

        distanceSquaredNow = getDistanceSquared(nowPos_axisTilt,startPos_axisTilt,rayDir_axisTilt);
        // println("clouds far ray 2: {}",sqrt(distanceSquaredNow));

            // closestIndex = 2;
            nowUV = virtual_Grid(tinyBox->cloudsIndex[2].x,tinyBox->cloudsIndex[2].y).uv ; // u 列 v 行
            nowVU[0] = nowUV[1];
            nowVU[1] = nowUV[0];

        distance_all[2] = {distanceSquaredNow,nowVU,2};
//  3
        nowPos_ScreenAxis = virtual_Grid(tinyBox->cloudsIndex[3].x,tinyBox->cloudsIndex[3].y).pos;
        screenAxis2axisTilt(ScreenEye, AxisTilt, &nowPos_ScreenAxis, &nowPos_axisTilt);

        distanceSquaredNow = getDistanceSquared(nowPos_axisTilt,startPos_axisTilt,rayDir_axisTilt);
        // println("clouds far ray 3: {}",sqrt(distanceSquaredNow));

            // closestIndex = 3;
            nowUV = virtual_Grid(tinyBox->cloudsIndex[3].x,tinyBox->cloudsIndex[3].y).uv ; // u 列 v 行
            nowVU[0] = nowUV[1];
            nowVU[1] = nowUV[0];

        distance_all[3] = {distanceSquaredNow,nowVU,3};
//

        nth_element(distance_all.begin(),distance_all.begin()+2,distance_all.end(),
            [](const _infoP& a, const _infoP& b) {
                return a.p2Ray_22 < b.p2Ray_22;
            });



        singleIndex = tinyBox->cloudsIndex[distance_all[0].inOrder].x * virtual_Grid.innerMax
        + tinyBox->cloudsIndex[distance_all[0].inOrder].y;
        if (!isIn(singleIndexHave,singleIndex)) {
            // 没有 一维索引 加进去
            singleIndexHave.push_back(singleIndex);
            candidates.emplace_back(make_pair(nowVU,tinyBox));
        }//else println(stderr," 一次射中 重复的 一维索引 !!!");

        singleIndex = tinyBox->cloudsIndex[distance_all[1].inOrder].x * virtual_Grid.innerMax
        + tinyBox->cloudsIndex[distance_all[1].inOrder].y;
        if (!isIn(singleIndexHave,singleIndex)) {
            // 没有 一维索引 加进去
            singleIndexHave.push_back(singleIndex);
            candidates.emplace_back(make_pair(nowVU,tinyBox));
        }//else println(stderr," 一次射中 重复的 一维索引 !!!");*/



    }
    // }
    // println("小盒射中数量: {} / {}",smallBoxGot,currentBox4Points.size());


     // for (pair<glm::vec2,glm::vec3>& p : res) {
     //     nowPos_ScreenAxis = p.second;
     //     toPoint = nowPos_ScreenAxis - this->startEye;
     //     getCrossed = glm::cross(toPoint, rayDir_axisTilt);
     //     distance_22 = getCrossed.x*getCrossed.x + getCrossed.y*getCrossed.y + getCrossed.z*getCrossed.z;
     //     if (distance_22 > rayRadius_22) {
     //         println("视线过远 距离: {}",distance_22);
     //         continue;
     //     }; // 视线过远

         // res3.push_back(p.first);
     // }

}
const float EPSILON = 1e-6f;

std::expected<thisPixelDeep22,char>
Bezier33Edge4Mirror::rayIntersect(ScreenDemo* ScreenEye,AxisDemo *AxisTilt, goLine32& rayDir,
                                              glm::ivec2 pos2D,glm::vec3 _P_[5][5]) {
    vector<thisPixelDeep22> solutions;
    // curveSurfaceInfo2 result = {};
    // glm::vec3 &_startEye = this->startEye;

    glm::vec3 screenPos_axisTilt, screenPos{pos2D.x, pos2D.y,0.f};
    // 屏幕系 转到 斜彩轴
    screenAxis2axisTilt(ScreenEye, AxisTilt, &screenPos, &screenPos_axisTilt);
    goLine32 rayUnit_axisTilt = glm::normalize(screenPos_axisTilt - startEye_axisTilt);

    vector<pair<glm::vec2,Box4Points*>> vuCandidates;
    getCandidatesVU_bySelfBox_randomTwo(startEye_axisTilt,rayUnit_axisTilt,vuCandidates);
        //generateCandidateVUs_2(_startEye, rayDir);


    //cout << "---vuCandidates: " << vuCandidates.size() << endl; // ###

    if (vuCandidates.size() == 0) {

        return std::unexpected(0);
    }
        //cout << "---vuCandidates: " << vuCandidates.size() << endl;



    newtonIteration(vuCandidates, _P_,this->startEye,rayDir, solutions);

    if (solutions.empty()) {
        return std::unexpected(0);
    }

    if (solutions.size() == 1) {
        return solutions[0];
    }

//        size_t solutionCount = solutions.size();
    // float minT = solutions[0].sightLineLen;
    // int index = 0;
    // // 最小步长 那个解
    // for (int i = 0; i < solutionCount; i++) {
    //     if (solutions[i].sightLineLen < minT) {
    //         minT = solutions[i].sightLineLen;
    //         index = i;
    //
    //     }
    // }
    vector<thisPixelDeep22>::iterator
    resultItem = min_element(solutions.begin(), solutions.end(),
[](const thisPixelDeep22 &a, const thisPixelDeep22 &b)-> bool {
                       return a.sightLineLen < b.sightLineLen;
                   });

    return *resultItem;//solutions[resIndex];

}
const string globalErr4 = "没有盒内点云";
const string globalErr5 = "没有牛顿迭代收敛解";
std::expected<pair<thisPixelDeep22,float>,std::expected<string_view,string>>
Bezier33Edge4Mirror::rayIntersectCustom(ScreenDemo* ScreenEye,AxisDemo *AxisTilt,
    glm::vec3& startP_screenAxis, glm::vec3& pGo1_screenAxis,const goLine32& rayDir_screenAxis,
    glm::vec3& butUVT,Box4Points* box4Ptr, glm::vec3 _P_[5][5]) {
    // println("rayIntersectCustom~~~~");
    vector<pair<thisPixelDeep22,float>> solutions{};
#ifdef iterationErrors
    vector<string> errors{};
#endif
    // std::expected<curveSurfaceInfo4,string> result{};
    // glm::vec3 &_startEye = this->startEye;

    glm::vec3 startP_axisTilt;
    glm::vec3 pGo1_axisTilt;
    // 屏幕系 转到 斜彩轴
    screenAxis2axisTilt(ScreenEye, AxisTilt, &startP_screenAxis, &startP_axisTilt);
    screenAxis2axisTilt(ScreenEye, AxisTilt, &pGo1_screenAxis, &pGo1_axisTilt);

    goLine32 rayUnit_axisTilt = pGo1_screenAxis - startP_screenAxis;
    //println("ray Unit axis Tilt ({},{},{})",rayUnit_axisTilt.dx,rayUnit_axisTilt.dy,rayUnit_axisTilt.dz);


    vector<pair<glm::vec2,Box4Points*>> vuCandidates;
    getCandidatesVU_bySelfBoxCustom(ScreenEye,AxisTilt,
        startP_axisTilt,rayUnit_axisTilt,box4Ptr,vuCandidates);
    // getCandidatesVU_bySelfBox_randomTwo(startP_axisTilt,rayUnit_axisTilt,vuCandidates);
        //generateCandidateVUs_2(_startEye, rayDir);


    if (vuCandidates.size() == 0) {
        return std::unexpected(globalErr4);
    }

// println("---vuCandidates:{} ",vuCandidates.size());


#ifdef iterationErrors
    newtonIterationCustom(vuCandidates, _P_,startP_screenAxis,
        rayDir_screenAxis,butUVT, solutions,errors);
#else
    newtonIterationCustom(vuCandidates, _P_,startP_screenAxis,
            rayDir_screenAxis,butUVT, solutions);
#endif

    if (solutions.empty()) {
         // println(" 自交 无解");
#ifdef iterationErrors
        if (!errors.empty())println(">>>>>>>>>>>>>>>>>>>>>>>>");
        for (const string& err_ : errors) {
            println(stderr,"无解:{}",err_);
            // 输出原因
        }
#endif
        return std::unexpected(globalErr5);
    }

    if (solutions.size() == 1) {
         // println(" 自交 单解");
        // result->uv = solutions[0].uv;
        // result->pos_screenAxis = solutions[0].pos_screenAxis;
        // result->reflectedRay_screenAxis = solutions[0].reflectedRay_screenAxis;
        // result->box4Ptr = solutions[0].box4Ptr;
        // result->sightLineLen = solutions[0].sightLineLen;
        // result.xy
        return solutions[0];

    }
     // println(" 自交 {}个解",solutions.size());

    vector<pair<thisPixelDeep22, float>>::iterator
    resultItem = max_element(solutions.begin(), solutions.end(),
[](const pair<thisPixelDeep22, float>&a, const pair<thisPixelDeep22, float>&b)-> bool {

                       return a.first.sightLineLen > b.first.sightLineLen;
                   });

    return *resultItem;//solutions[resIndex];

}
void Bezier33Edge4Mirror::newtonIteration(vector<pair<glm::vec2,Box4Points*>>& vuCandidates,glm::vec3(*_P_)[5],
    glm::vec3& startPos,goLine32 &rayDir, vector<thisPixelDeep22>& solutions) {
    // if (debug)println("newtonIteration~~~~");
    int maxiteration = 10;

    size_t vuCandidates_size = vuCandidates.size();

    glm::vec3 F;
    glm::vec3 S, Su, Sv;
    for(size_t i=0;i<vuCandidates_size;++i) {

        float v = vuCandidates[i].first[0];
        float u = vuCandidates[i].first[1];
        // if (debug) {
        //     println("--vuCandidates (v:{},u:{})  No.{}", v, u,cnt++);
        // }
        //            cout << "uvCandidates: " << uvCandidates.size() << endl;


        float t = 0.0f;

        // 增加曲率自适应迭代（关键改进点）
        // float prevError = numeric_limits<float>::max();
        bool isCandidateInvalid = false;
        for (int iter = 0;/*MAX_ITERATIONS*/; ++iter) {
            surfaceDerivatives3(u, v, _P_, &S, &Su, &Sv);

            F = S - (startPos + t * rayDir._);

            if (fabs(F[0]) < EPSILON &&
                fabs(F[1]) < EPSILON &&
                fabs(F[2]) < EPSILON)
                break;

            float J[3][3] = { // 影响迭代 关键
                {Su.x, Sv.x, -rayDir.dx},
                {Su.y, Sv.y, -rayDir.dy},
                {Su.z, Sv.z, -rayDir.dz}
            };

            float delta[3];
            if (!solve3x3_(J, F, delta)) break;

            // 动态调整步长
            float currentError = glm::length(F);
            // if(currentError > prevError * 0.9f) {
            //     delta[0] *= 0.5f; // 误差未明显下降时减小步长
            //     delta[1] *= 0.5f;
            //     delta[2] *= 0.5f;
            // }
            // prevError = currentError;
            if (currentError < 0.01f) {
                //println("iter: {}", iter); // 近20次 才结束
                break; // 出结果
            }
            if (iter >= maxiteration) {
                // if (debug) println("--反射 迭代次数 {} → {}", maxiteration,iter);
                isCandidateInvalid = true; // 标记候选点无效
                break; // 迭代次数超限
            }

            // ...更新uv...
            u -= delta[0];
            v -= delta[1];
            t -= delta[2];


        } // -------- 内三层循环后 处理solution扩容数组

        // 3. 关键：内循环跳出后，先判断标志位
        if (isCandidateInvalid) {
            continue;
        }
        if (u >= 0 && u <= 1.0f &&
            v >= 0 && v <= 1.0f &&
            t > 0.f) {
            //                    u = std::clamp(u, 0.0f, 1.0f);
            //                    v = std::clamp(v, 0.0f, 1.0f);


            bool exists = // 结果去重 候选点过多
                    std::find_if(solutions.begin(), solutions.end(),
                        [u,v](const thisPixelDeep22& src)->bool {
                            return fabs(src.uv[0] - u) < 1e-4f && fabs(src.uv[1] - v) < 1e-4f;
                        }
                        ) != solutions.end();
            // for (auto &infoNow: solutions) {
            //     if (fabs(infoNow.uv[0] - u) < 1e-4f &&
            //         fabs(infoNow.uv[1] - v) < 1e-4f) {
            //         exists = true;
            //         break;
            //     }
            // }
            if (exists) continue; // 结果去重


            // 计算表面点后立即进行法线计算

            // 计算视线方向（从表面点到相机的方向）
            // goLine32 nearlyViewDir = glm::normalize(startPos - surfacePoint_final);
            // float rayNotSameAngle = PolygonBase::angleBetweenVectors(-nearlyViewDir._, rayDir._); // 排除 不一致视线 夹角差
            // bool sameRay = rayNotSameAngle < 0.02f;
            // if (!sameRay) {
            //     // if (debug) println("--反射 视线不一致");
            //     continue; // 不在视线内
            // }


            // 重新计算精确的导数（考虑clamp后的uv）
            // glm::vec3 S_clamped, Su_clamped, Sv_clamped;
            // surfaceDerivatives3(u, v, _P_, &S_clamped, &Su_clamped, &Sv_clamped);

            // 计算法线（叉乘前先归一化）
            goLine32 normalVertical = glm::normalize(glm::cross(Su, Sv));

            // 背面剔除判断（点积小于等于0为背面）
            bool faceFront = true;
            if (PolygonBase::isFrontFacing(startEye,normalVertical,S)) {
                faceFront = false;
            }

            // glm::vec3 rayVec = surfacePoint_final - startPos;


            //(rayVec.x*sightLine.x + rayVec.y*sightLine.y + rayVec.z*sightLine.z);

                // 反射向量
                goLine32 reflectedRay = glm::reflect(rayDir._, normalVertical._);
                //                        return {glm::vec2{u, v}, surfacePoint_final, sightLen_final};

                solutions.emplace_back(thisPixelDeep22{
                    .x=0,
                    .uv=glm::vec2{u, v},
                    .pos_screenAxis=S,
                    .reflectedRay_screenAxis=reflectedRay,
                    .box4Ptr=vuCandidates[i].second,
                    .sightLineLen=t,
                    .faceToCamera=faceFront
                });

            // 视线长 step
            // step² = 视线立方x² + 视线立方y² + 视线立方z²
            // step² = 视线立方x*dx*step + 视线立方y*dy*step + 视线立方z*dz*step
            // step = 视线立方x*dx + 视线立方y*dy + 视线立方z*dz


        }
        //            }
// 视点远
// 倾向于扩大收敛域但可能增加迭代次数（收敛变慢），数值问题风险相对较低，但需注意绝对阈值导致的假收敛。

// 视点近
// 倾向于缩小收敛域但可能减少迭代次数（如果收敛则更快），显著增加发散和数值不稳定性（病态 Jacobian）的风险。
    }
}
constexpr double rayAngleErr = glm::radians<double>(0.02);
#ifdef iterationErrors
const string globalErr_1 = "vec3 F →{000}";
const string globalErr_2 = "!solve3x3_(J, F, delta)";
const string globalErr_3 = "与之前uv重合≈";

void Bezier33Edge4Mirror::newtonIterationCustom(vector<pair<glm::vec2,Box4Points*>>& vuCandidates,
    glm::vec3(*_P_)[5],glm::vec3& startPos,const goLine32 &rayDir, glm::vec3& butUVT,
    vector<pair<thisPixelDeep22,float>>& solutions,vector<string>&errors) {
#else
void Bezier33Edge4Mirror::newtonIterationCustom(vector<pair<glm::vec2,Box4Points*>>& vuCandidates,
    glm::vec3(*_P_)[5],glm::vec3& startPos,const goLine32 &rayDir, glm::vec3& butUVT,
    vector<pair<thisPixelDeep22,float>>& solutions) {
#endif

    // if (debug)println("newtonIteration~~~~");
    int maxiteration = 10;

    size_t vuCandidates_size = vuCandidates.size();

    glm::vec3 F;
    glm::vec3 S, Su, Sv;
    for(size_t i=0;i<vuCandidates_size;++i) {

        float v = vuCandidates[i].first[0];
        float u = vuCandidates[i].first[1];
        // if (debug) {
        //     println("--vuCandidates (v:{},u:{})  No.{}", v, u,cnt++);
        // }
        //            cout << "uvCandidates: " << uvCandidates.size() << endl;


        float t = 0.0f;

        // 增加曲率自适应迭代（关键改进点）
        // float prevError = numeric_limits<float>::max();int errCnt = 0;vector<float> errCache;
        bool isCandidateInvalid = false;
        for (int iter = 0;/*MAX_ITERATIONS*/; ++iter) {

            surfaceDerivatives3(u, v, _P_, &S, &Su, &Sv);

            F = S - (startPos + t * rayDir._);

            if (fabs(F[0]) < EPSILON &&
                fabs(F[1]) < EPSILON &&
                fabs(F[2]) < EPSILON) {
                isCandidateInvalid = true;
#ifdef iterationErrors
                errors.emplace_back(globalErr_1);
#endif
                break;
            }


            float J[3][3] = { // 影响迭代 关键
                {Su.x, Sv.x, -rayDir.dx},
                {Su.y, Sv.y, -rayDir.dy},
                {Su.z, Sv.z, -rayDir.dz}
            };

            float delta[3];
            if (!solve3x3_(J, F, delta)) {
#ifdef iterationErrors
                errors.emplace_back(globalErr_2);
#endif
                isCandidateInvalid = true;
                break;
            }

            // 动态调整步长
            float currentError = glm::length(F);
            // errCache.push_back(currentError);

            // if(currentError > prevError * 0.9f) {
            //     delta[0] *= 0.5f; // 误差未明显下降时减小步长
            //     delta[1] *= 0.5f;
            //     delta[2] *= 0.5f;
            // }

            // prevError = currentError;
            if (currentError < 0.01f) {
                //println("二次发射 牛顿迭代 currentError:{}",currentError);
                //println("iter: {}", iter); // 近20次 才结束
                break; // 出结果
            }
            if (iter >= maxiteration) {
#ifdef iterationErrors
                errors.emplace_back(
                   std::format("迭代次数>{}",maxiteration)
                    );
#endif
                //println(stderr, "--二次反射 迭代次数 {} > 10 ", iter);
                isCandidateInvalid = true; // 标记候选点无效
                break; // 迭代次数超限
            }

            // ...更新uv...
            u -= delta[0];
            v -= delta[1];
            t -= delta[2];


        } // -------- 内三层循环后 处理solution扩容数组

        // 3. 关键：内循环跳出后，先判断标志位
        if (isCandidateInvalid) {
            continue;
        }

        // if (abs(t - butUVT[3]) < 0.1f) {
        //     // 步长 就是 到初始点
        //     // 即使不迭代自己包围盒  也会包围盒重叠  ╮(╯▽╰)╭
        //     // println("t: {}, but step: {}", t, butStep);
        //     continue;
        // }

        if (abs(u - butUVT[0]) < 0.01f && abs(v - butUVT[1]) < 0.01f) {
            // 即使不迭代自己包围盒  也会包围盒重叠  ╮(╯▽╰)╭
#ifdef iterationErrors
            errors.emplace_back(
                std::format("当前uv({},{})≈反射起始uv({},{})",u,v,butUVT[0],butUVT[1])
                ); //归因
#endif
            continue;
        }

        if (u >= 0 && u <= 1.0f &&
            v >= 0 && v <= 1.0f &&
            t > 0.f && t < butUVT[2]-0.02f) {
            //                    u = std::clamp(u, 0.0f, 1.0f);
            //                    v = std::clamp(v, 0.0f, 1.0f);


            bool exists =  // 结果去重 候选点过多
                    std::find_if(
                        solutions.begin(),
                        solutions.end(),
[u,v](const pair<thisPixelDeep22,float>& src)->bool {
               return fabs(src.first.uv[0] - u) < 1e-4f && fabs(src.first.uv[1] - v) < 1e-4f;
                            }
                        ) != solutions.end();

            if (exists) {
#ifdef iterationErrors
                errors.emplace_back(globalErr_3); //归因
#endif
                continue; // 结果去重
            }

            // 计算表面点后立即进行法线计算



            // 计算视线方向（从表面点到相机的方向）
            // goLine32 nearlyViewDir = glm::normalize(surfacePoint_final-startPos);
            // double rayNotSameAngle = PolygonBase::angleBetweenVectors_rad(nearlyViewDir._, rayDir._); // 排除 不一致视线 夹角差
            // bool sameRay = rayNotSameAngle < rayAngleErr;
            // if (!sameRay) {
            //     // if (debug)
            //     println(stderr,"--反射 视线不一致");
            //     continue; // 不在视线内
            // }


            // 重新计算精确的导数（考虑clamp后的uv）
            // glm::vec3 S_clamped, Su_clamped, Sv_clamped;
            // surfaceDerivatives3(u, v, _P_, &S_clamped, &Su_clamped, &Sv_clamped);

            // 计算法线（叉乘前先归一化）
            goLine32 normalVertical = glm::normalize(glm::cross(Su, Sv));
            // normalVertical.dx *= -1.f;
            // normalVertical.dy *= -1.f;
            // normalVertical.dz *= -1.f;

            // 背面剔除判断（点积小于等于0为背面）

            if (!PolygonBase::isFrontFacing(startPos, normalVertical,S))
            // if (glm::dot(normalVertical._, rayDir._) > 0.0f)
                {
            //     // 二次反射 后撤 射中背面
            //     println(stderr,"current→ u: {}, v: {}, t: {}", u, v, t);
            //     println(stderr,"avoid→ u: {}, v: {}, t: {}", butUVT[0], butUVT[1], butUVT[2]);
            //
            println(stderr,"startPos:{}",showVec3(startPos));
            println(stderr,"surface pos:{}",showVec3(S));
            println(stderr,"surface pos vertical:{}",showVec3(normalVertical._));

            //二次反射 后撤 射中正面面 不可能
                println(stderr,"反看见到正面!");
                continue;
                 //throw std::runtime_error("二次反射 后撤 射中正面面");
            }


            // glm::vec3 rayDir_final = surfacePoint_final - startPos;



            //(rayVec.x*sightLine.x + rayVec.y*sightLine.y + rayVec.z*sightLine.z);

                // 反射向量
                goLine32 reflectedRay = glm::reflect(-rayDir._, normalVertical._); // 视线步进 取反
                //                        return {glm::vec2{u, v}, surfacePoint_final, sightLen_final};

            thisPixelDeep22 resultNow = {
                .x=0,
                .uv=glm::vec2{u, v},
                .pos_screenAxis=S,
                .reflectedRay_screenAxis=reflectedRay,
                .box4Ptr=vuCandidates[i].second,
                .sightLineLen=t,
                .faceToCamera=true
                                };
                solutions.emplace_back(resultNow,0);

            // 视线长 step
            // step² = 视线立方x² + 视线立方y² + 视线立方z²
            // step² = 视线立方x*dx*step + 视线立方y*dy*step + 视线立方z*dz*step
            // step = 视线立方x*dx + 视线立方y*dy + 视线立方z*dz


        }
        //            }
// 视点远
// 倾向于扩大收敛域但可能增加迭代次数（收敛变慢），数值问题风险相对较低，但需注意绝对阈值导致的假收敛。
// 视点近
// 倾向于缩小收敛域但可能减少迭代次数（如果收敛则更快），显著增加发散和数值不稳定性（病态 Jacobian）的风险。

        // if (!solutions.empty()) {
        //     // 二次反射 回看 单解足够
        //     return;
        // }
    }
}

void Bezier33Edge4Mirror::moveFreshStatus(){

    renderNext = 0;
    startRowIndex_ = 0;
    _pixelSurfaceInfo.clear();
}
const float reflectTip = 5.f;
// bool vec3Nan(glm::vec3& p1) {
//         if (isnan(p1.x) || isnan(p1.y) || isnan(p1.z)) {
//             return true;
//         }
//         return false;
//     }

pair<glm::vec3,glm::vec3>(*getFarOutAndBack1)(
    std::expected<pair<thisPixelDeep22,float>, std::expected<string_view, string>>&,float
    )  =
[](std::expected<pair<thisPixelDeep22,float>, std::expected<string_view, string>>& _src,
    float _back2Reflect)
->pair<glm::vec3,glm::vec3>
{
        glm::vec3 farOut = _src->first.pos_screenAxis + _src->first.reflectedRay_screenAxis._ * _back2Reflect;
        glm::vec3 farOutBack1 = farOut - _src->first.reflectedRay_screenAxis._; // 走远 回退 1
    return make_pair(farOut,farOutBack1);

};


void Bezier33Edge4Mirror::drawLastReflect(ScreenDemo *ScreenEye, size_t endOf,
    vector<
    std::expected<pair<thisPixelDeep22,float>, std::expected<string_view,string>>
    >& nearestResults) {

    // assert(endOf < nearestResults.size()-1);
    glm::vec2 p1_2D;
    glm::vec2 p2_2D;
    float deepP1P2;

    for (int i=0;i<endOf;i++) {

        p1_2D.x = nearestResults[i]->first.x;
        p1_2D.y = nearestResults[i]->second;
        p2_2D.x = nearestResults[i+1]->first.x;
        p2_2D.y = nearestResults[i+1]->second;

        deepP1P2 = (nearestResults[i]->first.pos_screenAxis.z + nearestResults[i+1]->first.pos_screenAxis.z) / 2.f;
        ScreenDemo::line2ScreenBuffer_(ScreenEye,p1_2D.x,p1_2D.y,
                                      p2_2D.x, p2_2D.y,reflectRaysColors[i],deepP1P2-60.f);
    }

    glm::vec3& pLast = nearestResults[endOf]->first.pos_screenAxis;
    glm::vec3 pLastFar = nearestResults[endOf]->first.pos_screenAxis +
                         nearestResults[endOf]->first.reflectedRay_screenAxis._ * reflectTip;

    glm::vec2 pLast2D = {nearestResults[endOf]->first.x,nearestResults[endOf]->second};
    glm::vec2 pLastFar2D = __3d2d_bezierMirror(ScreenEye,pLastFar.x,pLastFar.y,pLastFar.z);

    float lastFarDeep = (pLastFar.z + pLast.z) / 2.f;

    ScreenDemo::line2ScreenBuffer_(ScreenEye,pLast2D.x,pLast2D.y,
                                  pLastFar2D.x, pLastFar2D.y,reflectRaysColors[endOf],lastFarDeep-60.f);
}
float gray[3] = { 117.f/255.f,115.f/255.f,116.f/255.f };

void Bezier33Edge4Mirror::drawReflectLine(ScreenDemo* ScreenEye,AxisDemo* AxisTilt,thisPixelDeep22& _pixelDeeps, float y) {
    if (debugMode == 1) {
        glm::vec3 p1Far = _pixelDeeps.pos_screenAxis + _pixelDeeps.reflectedRay_screenAxis._ * reflectTip;
        glm::vec2 p1Far2D = __3d2d_bezierMirror(ScreenEye,p1Far.x,p1Far.y,p1Far.z);
        float lineDeep = (_pixelDeeps.pos_screenAxis.z + p1Far.z) / 2.f;

        ScreenDemo::line2ScreenBuffer_(ScreenEye,_pixelDeeps.x,y,
            p1Far2D.x,p1Far2D.y,reflectRaysColors[0],lineDeep-60.f);
        return;
    }
    // back2Reflect = glm::distance(virtual_scanBox3D.center,this->startEye); // 主包围盒 视点距离 反射点距离
    size_t reflectLastIndexNow;
    vector<
        std::expected<pair<thisPixelDeep22,float>, std::expected<string_view, string>>
    > nearestResults;
    pair<thisPixelDeep22,float> nearestResult0 = make_pair(_pixelDeeps,y);
    nearestResults.emplace_back(nearestResult0);

    tryNextReflect(ScreenEye,AxisTilt,nearestResults,back2Reflect,0);

    // glm::vec3 pLastFar;glm::vec2 pLastFar2D;float lastFarDeep;
    if (!nearestResults[1]) { // 一次反射 无自交
        // debug---
        std::expected<pair<thisPixelDeep22,float>,std::expected<string_view, string>>
        & item0 = nearestResults[0];
        glm::vec3 p1FarOut; // 不得 屏垂距 < 0.01
        float p1FarOut_z;
        float declineRay = 0.f;
        do {
            p1FarOut_z = item0->first.pos_screenAxis.z + item0->first.reflectedRay_screenAxis.dz * (back2Reflect-declineRay);
            declineRay += 100.f;
        }while (p1FarOut_z < -ScreenEye->rectDepth /*&& declineRay < 200.001f*/);
        p1FarOut = item0->first.pos_screenAxis + item0->first.reflectedRay_screenAxis._ * (back2Reflect-declineRay);

            // float near1 = glm::dot(item0->reflectedRay_screenAxis._,item0->reflectedRay_screenAxis._);
            // assert(abs(near1- 1.f) < 1e-4f);

        glm::vec2 p1FarOut2D = __3d2d_bezierMirror(ScreenEye,p1FarOut.x,
            p1FarOut.y,p1FarOut.z);
        glm::vec3 attachP_3D = item0->first.pos_screenAxis + item0->first.reflectedRay_screenAxis._ * reflectTip;
        glm::vec2 attachP_2D = __3d2d_bezierMirror(ScreenEye,attachP_3D.x,
            attachP_3D.y,attachP_3D.z);

        ScreenDemo::line2ScreenBuffer(ScreenEye,p1FarOut2D.x,p1FarOut2D.y,
            attachP_2D.x,attachP_2D.y,gray,std::max(0.01f,p1FarOut.z-100.f));
        // debug--
        reflectLastIndexNow = nearestResults.size()-1; // 1
        drawLastReflect(ScreenEye, reflectLastIndexNow-1,nearestResults);

    }
    else { // 一次反射 自交1

        // if (!nearestResults[1].checkNan())println(stderr,"nearestResult miss nan check");
        tryNextReflect(ScreenEye,AxisTilt,nearestResults,back2Reflect,1);

        // debug---
        std::expected<pair<thisPixelDeep22, float>,std::expected<string_view, string>>
        & item0 = nearestResults[0];
        std::expected<pair<thisPixelDeep22, float>,std::expected<string_view, string>>
        & item1 = nearestResults[1];
        glm::vec3 p1FarOut; // 不得 屏垂距 < 0.01
        float p1FarOut_z;
        float declineRay = 0.f;
        do {
           p1FarOut_z = item0->first.pos_screenAxis.z + item0->first.reflectedRay_screenAxis.dz * (back2Reflect-declineRay);
            declineRay += 100.f;
        }while (p1FarOut_z < -ScreenEye->rectDepth /*&& declineRay < 200.001f*/);
        p1FarOut = item0->first.pos_screenAxis + item0->first.reflectedRay_screenAxis._ * (back2Reflect-declineRay);
        // if (item0->pos_screenAxis.z + item0->reflectedRay_screenAxis.dz * back2Reflect < 1.f) {
        //     p1FarOut = item0->pos_screenAxis + item0->reflectedRay_screenAxis._ * (back2Reflect-100.f);
        // }else {
        //     p1FarOut = item0->pos_screenAxis + item0->reflectedRay_screenAxis._ * back2Reflect;
        // }

            // float near1 = glm::dot(item0->reflectedRay_screenAxis._,item0->reflectedRay_screenAxis._);
            // assert(abs(near1- 1.f) < 1e-4f);
        glm::vec2 p1FarOut2D = __3d2d_bezierMirror(ScreenEye,p1FarOut.x,
            p1FarOut.y,p1FarOut.z);
        glm::vec2 surfaceP_2D = __3d2d_bezierMirror(ScreenEye,item1->first.pos_screenAxis.x,
            nearestResults[1]->first.pos_screenAxis.y,item1->first.pos_screenAxis.z);

        ScreenDemo::line2ScreenBuffer_(ScreenEye,p1FarOut2D.x,p1FarOut2D.y,
            surfaceP_2D.x,surfaceP_2D.y,reflectRaysColors_[0],p1FarOut.z-100.f);
        // debug--

        if (!nearestResults[2]) { // 二次反射 无自交
            reflectLastIndexNow = nearestResults.size()-1; // 2
            drawLastReflect(ScreenEye, reflectLastIndexNow-1,nearestResults);
        }
        else { // 二次反射 自交2
            // if (!nearestResults[2].checkNan())println(stderr,"nearestResult2 miss nan check");

             // tryNextReflect(ScreenEye,AxisTilt,nearestResults,back2Reflect,2);
             // if (!nearestResults[3].has_value()) {


                reflectLastIndexNow = nearestResults.size()-1; // 3
                drawLastReflect(ScreenEye, reflectLastIndexNow-1, nearestResults);

             // }
             // else {
             //
             //     reflectLastIndexNow = nearestResults.size()-1; // 3
             //     // throw std::runtime_error("不可达");
             //
             //     // assert(feflectLastIndexNow == 4);
             //         glm::vec2 p1_2D;
             //     glm::vec2 p2_2D;
             //     float deepP1P2;
             //
             //     for (int i=0;i<reflectLastIndexNow;i++) {
             //         p1_2D = nearestResults[i]->xy;
             //
             //         p2_2D = nearestResults[i+1]->xy;
             //
             //         deepP1P2 = (nearestResults[i]->pos_screenAxis.z + nearestResults[i+1]->pos_screenAxis.z) / 2.f;
             //         ScreenDemo::line2ScreenBuffer_(ScreenEye,p1_2D.x,p1_2D.y,
             //                                       p2_2D.x, p2_2D.y,reflectRaysColors[i],deepP1P2-60.f);
             //     }
             //
             //     glm::vec3& pLast = nearestResults[reflectLastIndexNow]->pos_screenAxis;
             //     glm::vec3 pLastFar = nearestResults[reflectLastIndexNow]->pos_screenAxis +
             //                          nearestResults[reflectLastIndexNow]->reflectedRay_screenAxis._ * reflectTip;
             //
             //     glm::vec2& pLast2D = nearestResults[reflectLastIndexNow]->xy;
             //     glm::vec2 pLastFar2D = __3d2d_bezierMirror(ScreenEye,pLastFar.x,pLastFar.y,pLastFar.z);
             //
             //     float lastFarDeep = (pLast.z + pLastFar.z) / 2.f;
             //
             //     ScreenDemo::line2ScreenBuffer_(ScreenEye,pLast2D.x,pLast2D.y,
             //                                   pLastFar2D.x, pLastFar2D.y,
             //                                   reflectRaysColors[reflectLastIndexNow],lastFarDeep-60.f);
             //     // drawLastReflect(ScreenEye, feflectLastIndexNow-1, nearestResults);
             //
             // }

        }
    }

}
void Bezier33Edge4Mirror::tryNextReflect(ScreenDemo* ScreenEye,AxisDemo* AxisTilt,
    vector<
    std::expected<pair<thisPixelDeep22,float>, std::expected<string_view, string>>
    >& _nearestResults,float _back2Reflect,int _th) {
    //assert(_nearestResults[_th].has_value()==true); // 来源 有解

    pair<glm::vec3,glm::vec3> p1FarOutAndGo1 = getFarOutAndBack1(_nearestResults[_th], _back2Reflect);
    glm::vec3 avoid_uvt = {_nearestResults[_th]->first.uv[0],_nearestResults[_th]->first.uv[1],_back2Reflect};

    std::expected<pair<thisPixelDeep22,float>,std::expected<string_view,string>>
    nearestResult1 = rayIntersectCustom(ScreenEye,AxisTilt,p1FarOutAndGo1.first,
        p1FarOutAndGo1.second,
-_nearestResults[_th]->first.reflectedRay_screenAxis._,
avoid_uvt,_nearestResults[_th]->first.box4Ptr,virtual_P); // 视线 步进 反着

    if (nearestResult1) { // 计算迭代 有解
        glm::vec2 pos2DNow = __3d2d_bezierMirror(ScreenEye,nearestResult1->first.pos_screenAxis.x,
            nearestResult1->first.pos_screenAxis.y,nearestResult1->first.pos_screenAxis.z);

        nearestResult1->first.x = pos2DNow.x;
        nearestResult1->second = pos2DNow.y;
    _nearestResults.emplace_back(nearestResult1);
    }else { // 无解
        //println(stderr,"再反射无解:{}",nearestResult1.error());
        _nearestResults.emplace_back(std::unexpected(*nearestResult1.error()));
    }





}

void Bezier33Edge4Mirror::shotOnBox_AxisTilt_4__(Box4Points& box4Points,glm::vec3& startP_axisTilt, goLine32& rayDirUnit,
    pair<bool,float>* result,bool debug) {

    // glm::vec3 &eye = this->startEye_axisTilt;
    glm::vec3 boxMin{}, boxMax{};
    // x
    boxMin.x = box4Points.corners_unchange[static_cast<int>(corner::ltn)].x;
    boxMax.x = box4Points.corners_unchange[static_cast<int>(corner::rtn)].x;
    boxMin.y = box4Points.corners_unchange[static_cast<int>(corner::ltn)].y;
    boxMax.y = box4Points.corners_unchange[static_cast<int>(corner::lbn)].y;
    boxMin.z = box4Points.corners_unchange[static_cast<int>(corner::ltn)].z;
    boxMax.z = box4Points.corners_unchange[static_cast<int>(corner::ltf)].z;

    float stepMin = numeric_limits<float>::lowest();
    float stepMax = numeric_limits<float>::max();

    float inv_dir, step1, step2, t_near, t_far;
    for (int xyzIndex=0; xyzIndex<3; xyzIndex++) {
        inv_dir = 1.f / rayDirUnit._[xyzIndex]; // 应该不会 除0

        step1 = (boxMin[xyzIndex] - startP_axisTilt[xyzIndex]) * inv_dir;
        step2 = (boxMax[xyzIndex] - startP_axisTilt[xyzIndex]) * inv_dir;

        t_near = fminf(step1, step2); // 避免 NAN
        t_far = fmaxf(step1, step2);

        stepMin = fmaxf(stepMin, t_near);
        stepMax = fminf(stepMax, t_far);

        if (stepMin > stepMax) { // 倍 提速
            result->first = false;
            result->second = numeric_limits<float>::quiet_NaN();return;
        } // 直接排除 不相交

    }
    if (t_far >= 0.f) {
        // if (debug)println("mirror box4 有解");
        result->first = true;
        result->second = t_near;return;
    }

    result->first = false;
    result->second = numeric_limits<float>::quiet_NaN();
}

void Bezier33Edge4Mirror::shotOnBox_AxisTilt_9__(Box9Cube& box4Points,glm::vec3& startP_axisTilt, goLine32& rayDir,
    pair<bool,float>* result,bool debug) {

    // glm::vec3 &eye = this->startEye_axisTilt;
    glm::vec3 boxMin{}, boxMax{};
    // x
    boxMin.x = box4Points.corners_unchange[static_cast<int>(corner::ltn)].x;
    boxMax.x = box4Points.corners_unchange[static_cast<int>(corner::rtn)].x;
    boxMin.y = box4Points.corners_unchange[static_cast<int>(corner::ltn)].y;
    boxMax.y = box4Points.corners_unchange[static_cast<int>(corner::lbn)].y;
    boxMin.z = box4Points.corners_unchange[static_cast<int>(corner::ltn)].z;
    boxMax.z = box4Points.corners_unchange[static_cast<int>(corner::ltf)].z;

    float stepMin = numeric_limits<float>::lowest();
    float stepMax = numeric_limits<float>::max();

    float inv_dir, step1, step2, t_near, t_far;
    for (int xyzIndex=0; xyzIndex<3; xyzIndex++) {
        inv_dir = 1.f / rayDir._[xyzIndex]; // 应该不会 除0

        step1 = (boxMin[xyzIndex] - startP_axisTilt[xyzIndex]) * inv_dir;
        step2 = (boxMax[xyzIndex] - startP_axisTilt[xyzIndex]) * inv_dir;

        t_near = fminf(step1, step2); // 避免 NAN
        t_far = fmaxf(step1, step2);

        stepMin = fmaxf(stepMin, t_near);
        stepMax = fminf(stepMax, t_far);

        if (stepMin > stepMax) { // 倍 提速
            result->first = false;
            result->second = numeric_limits<float>::quiet_NaN();return;
        } // 直接排除 不相交

    }
    if (t_far >= 0.f) {
        // if (debug)println("mirror box9 有解");
        result->first = true;
        result->second = t_near;return;
    }

    result->first = false;
    result->second = numeric_limits<float>::quiet_NaN();
}
