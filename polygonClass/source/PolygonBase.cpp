//
// Created by iceoc0 on 2025/9/17.
//
#include "PolygonBase.h"

extern void* settled_ptr; // 全局设置的结构体指针
struct _settledBase{
    int _width;
    int _height;
    int _deep;
    bool _byAxis;
};
_settledBase* settled_ = (_settledBase*)settled_ptr;
const int screenWidth_base = settled_-> _width;
const int screenHeight_base = settled_-> _height;
const int screenDeep_base = settled_-> _deep;

PolygonBase::PolygonBase(int type):type_(type){
    // this->type_ = type;
    startEye = {static_cast<float>(screenWidth_base)/2.f,
                static_cast<float>(screenHeight_base)/2.f,static_cast<float>(-screenDeep_base)};
//    println("~PolygonBase start eye: ({}, {}, {})", startEye.x, startEye.y, startEye.z);

}
void PolygonBase::rasterLine(int x0, int y0, int x1, int y1, vector<glm::vec2>& _linePoints) {

    /* Bresenham 直线算法（通用整数版本）
     *
     * 每次在 x 方向前进一个单位（x++），然后决定 y 是否也增加（y++）。
       通过维护一个“误差项”（error term）来判断当前像素离理想直线的偏差。
       如果误差超过阈值，就向上走一步（y++），并修正误差。
     *
     */
    //       _linePoints.clear();

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int x2Right = x0 < x1 ? 1 : -1;
    int y2Down = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        _linePoints.emplace_back(x0, y0);
        if (x0 == x1 && y0 == y1) break; // 起点终点一致
        int e2 = 2 * err;
        if (e2 > -dy) { // 应该在 x 方向走一步
            err -= dy;
            x0 += x2Right;
        }
        if (e2 < dx) { // 应该在 y 方向走一步
            err += dx;
            y0 += y2Down;
        }
    }
}
inline Quaternion PolygonBase::multiply(Quaternion& a, Quaternion& b) {
//    return Quaternion(
//    a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z, // 新汤底
//
//    a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y, // 处理x +yz -zy
//    a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z, // 处理y +zx -xz
//    a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x); // 处理z +xy -yx
    return a * b;
}

void PolygonBase::rotate_vector(goLine64& vec2zero, Quaternion& q) {
    // 把向量变成四元数 (食物插在筷子上)
    Quaternion vec_q(0, vec2zero.dx, vec2zero.dy, vec2zero.dz);

    // 计算反向旋转 (q的逆 = 共轭, 因为单位四元数)
    Quaternion inv_q(q.w, -q.x, -q.y, -q.z);


    // 旋转公式: v' = q * v * q^-1 (正反搅拌两次)
    Quaternion temp = multiply(q, vec_q);
    Quaternion result = multiply(temp, inv_q);

    // 更新原向量
    vec2zero.dx = result.x;
    vec2zero.dy = result.y;
    vec2zero.dz = result.z;
}
Quaternion PolygonBase::create_rotation2(double angle_rad, const goLine64& axis){
    if(angle_rad == 0.f)angle_rad = 1e-12;
    // 角度转弧度
    double half_rad = angle_rad / 2.0;
    double sin_val = glm::sin(half_rad);

    // 构建四元数
    double w = glm::cos(half_rad);
    double x = sin_val * axis.dx;
    double y = sin_val * axis.dy;
    double z = sin_val * axis.dz;

    // 检查单位四元数
    double len_sq = w*w + x*x + y*y + z*z;
    if(fabs(len_sq - 1.0) > 1e-6){
        // 允许微小误差
        println(stderr, "create_rotation: Warning: Quaternion is not normalized. len_sq = {}", len_sq);
    }

    return Quaternion(w, x, y, z);
}

glm::vec3 PolygonBase::tiltTurnFrom000(glm::vec3& outP, glm::vec3& obliqueDir, float angle_deg){
    float angle_rad = glm::radians(angle_deg); // 角度转弧度
    // 已经从原点 000 出发 求长度
    float lenPToOrigin = glm::length(outP);
    float lenAxisToOrigin = glm::length(obliqueDir);
    // 缩到一
    goLine64 shortenP;
    if(abs(lenPToOrigin - 1.f) > 1e-12) // 不是1 才缩  待转点
        shortenP._ = outP / lenPToOrigin;
    else
        shortenP._ = outP;

    goLine64 shortenDir;
    if(abs(lenAxisToOrigin - 1.f) < 1e-12) // 不是1 才缩  斜转轴
        shortenDir._ = obliqueDir / lenAxisToOrigin;
    else
        shortenDir._ = obliqueDir;
    // 斜转
    glm::quat q = PolygonBase::create_rotation2(angle_rad, shortenDir);
    PolygonBase::rotate_vector(shortenP, q);
    // 伸回去
    glm::vec3 result = shortenP._ * static_cast<double>(lenPToOrigin);
    return result;
}
Quaternion PolygonBase::getFrameRotateInfo_(goLine32& goX, goLine32& goZ){
    goLine32 frameRotateInfo_tileAxis(0.f,-1.f,0.f);
    float frameRotateInfo_tileAngle;
    float frameRotateInfo_clockBackAngle = std::numeric_limits<float>::quiet_NaN();

    // 斜转轴 --------
    goLine32 selfAxis2Z = goZ; // draw_tick时先刷新 solid在draw后
//    cout << "selfAxis2Z (" << worldAxis2Z.dx << ", " << worldAxis2Z.dy << ", " << worldAxis2Z.dz << ")" << endl;
    goLine32 __tiltAxis, tiltAxis_;
    if(selfAxis2Z.dx != 0.f || selfAxis2Z.dy != 0.f || selfAxis2Z.dz != 1.f){
        __tiltAxis._ = glm::cross(selfAxis2Z._, {0,0,1});
        tiltAxis_._ = glm::normalize(__tiltAxis._); // 归一化斜转轴
//        cout << "Z需要斜转使重合" << endl;
    }else{
        tiltAxis_ = {0,0,1};
//        cout << "Z无需斜转使重合" << endl;
    }
    if(!isnan(tiltAxis_.dx) && !isnan(tiltAxis_.dy) && !isnan(tiltAxis_.dz)){
        frameRotateInfo_tileAxis = tiltAxis_;
    }else{
        println(stderr, "getFrameRotateInfo_: Warning: NaN in 1.斜转轴(回Z轴重合)");
    }

    // 斜转角 --------
    float same000_SelfAxis001_ScreenZAxis_distance = glm::sqrt(selfAxis2Z.dx*selfAxis2Z.dx + selfAxis2Z.dy*selfAxis2Z.dy);

    float _tiltAngle = glm::atan(same000_SelfAxis001_ScreenZAxis_distance,selfAxis2Z.dz);
    if(!isnan(_tiltAngle)){
        frameRotateInfo_tileAngle = _tiltAngle;
    }else{
        frameRotateInfo_tileAngle = numeric_limits<float>::quiet_NaN();
        println(stderr, "getFrameRotateInfo_: Warning: NaN in 1.斜转角(回Z轴重合)");
    }


    goLine64 same000_RightX = {goX.dx, goX.dy, goX.dz};
    Quaternion _q;
    if(!isnan(frameRotateInfo_tileAngle) && !isnan(frameRotateInfo_tileAxis.dx) &&
       !isnan(frameRotateInfo_tileAxis.dy) && !isnan(frameRotateInfo_tileAxis.dz)){
        goLine64 frameRotateInfo_tileAxis_d = {
            frameRotateInfo_tileAxis.dx,
            frameRotateInfo_tileAxis.dy,
            frameRotateInfo_tileAxis.dz
        };
        _q = create_rotation2(frameRotateInfo_tileAngle, frameRotateInfo_tileAxis_d);
    }else{
        println(stderr, "getFrameRotateInfo_: Warning: NaN 或Z轴重合 没有一样~");
        _q = {1, 0, 0, 0}; // 和没转一样
    }

    rotate_vector(same000_RightX, _q);

    // 正传轴 就是z轴
    // 正转角 --------

    double _clockBackAngle = glm::atan(same000_RightX.dy,same000_RightX.dx);
    if(!isnan(_clockBackAngle)){
        frameRotateInfo_clockBackAngle = (float)_clockBackAngle;
    }

    Quaternion& q1 = _q;

    Quaternion q2 = create_rotation2(frameRotateInfo_clockBackAngle, {0,0,-1});
    Quaternion result;
    if(frameRotateInfo_tileAngle!=0.f || frameRotateInfo_clockBackAngle!=0.f) {
        if (frameRotateInfo_tileAngle == 0.f) { // 转z重 0度
            result = q2; // 只转x
        } else if (frameRotateInfo_clockBackAngle == 0.f) { // 再 转x重 0度
            result = q1; // 只转z
        } else { // 都不是0度
            result = multiply(q2, q1);
        }
    }else{
        // 1 旋转角度为0度（或360度的整数倍）
        // 2 旋转轴可以是任意方向（因为不旋转）
        result = Quaternion(1, 0, 0, 0); // 和没转一样
    }
    return result;
}

float PolygonBase::angleBetweenVectors_deg(const glm::vec3& _a, const glm::vec3& _b) {

    /*
    glm::dvec3 a = glm::dvec3(_a);
    glm::dvec3 b = glm::dvec3(_b);

    // 计算向量模长   到原点的距离
    double lenA = glm::length(a);//sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    double lenB = glm::length(b);//sqrt(b.x * b.x + b.y * b.y + b.z * b.z);

    // 处理零向量情况
    if (lenA == 0 || lenB == 0) return 0.0;

    // 计算归一化点积（直接得到cosθ）
    /*(a.x * b.x + a.y * b.y + a.z * b.z)#1#
    double cos_theta = glm::dot(a, b) / (lenA * lenB);

    // 计算归一化叉积模长（直接得到sinθ）
    glm::dvec3 cross_ = glm::cross(a, b) / (lenA * lenB);


    double sin_theta = glm::length(cross_);

    // 使用atan2获取精确角度（单位：弧度）
    double angle_rad = atan2(sin_theta, cos_theta);

    // 转换为角度制返回
    return glm::degrees((float)angle_rad);*/

    double len_a = glm::length(_a);
    double len_b = glm::length(_b);
    if (len_a == 0.0 || len_b == 0.0) return 0.0f;

    double dot_ab = glm::dot(_a, _b);
    double cross_len = glm::length(glm::cross(_a, _b));
    double inv_norm = 1.0 / (len_a * len_b);

    double cos_theta = dot_ab * inv_norm;
    double sin_theta = cross_len * inv_norm;

    // clamp to avoid numerical errors outside [-1,1] for acos (though atan2 is safer)
    cos_theta = glm::clamp(cos_theta, -1.0, 1.0);

    double angle_rad = std::atan2(sin_theta, cos_theta);
    return static_cast<float>(glm::degrees(angle_rad));
}
double PolygonBase::angleBetweenVectors_rad(const glm::vec3& _a, const glm::vec3& _b) {

    double len_a = glm::length(_a);
    double len_b = glm::length(_b);
    if (len_a == 0.0 || len_b == 0.0) return 0.0f;

    double dot_ab = glm::dot(_a, _b);
    double cross_len = glm::length(glm::cross(_a, _b));
    double inv_norm = 1.0 / (len_a * len_b);

    double cos_theta = dot_ab * inv_norm;
    double sin_theta = cross_len * inv_norm;

    // clamp to avoid numerical errors outside [-1,1] for acos (though atan2 is safer)
    cos_theta = glm::clamp(cos_theta, -1.0, 1.0);

    double angle_rad = std::atan2(sin_theta, cos_theta);
    return angle_rad;
}
void PolygonBase::loadImgRGB01(string& filename, Matrix2D<glm::vec3>& _imgRGB){

    cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR); // 从文件读取RGB图像
    if (img.empty()) {
        println(stderr,"无法读取图像: ", filename);

    }

    _imgRGB.outterMax = img.rows;
    _imgRGB.innerMax = img.cols;
    _imgRGB.data.resize(_imgRGB.innerMax*_imgRGB.outterMax);

//    for(int i=0; i<img.rows; i+=1) {
//        vector <glm::vec3> tmpNow_ = vector<glm::vec3>(img.cols); // 存入数组
//        _imgRGB->push_back(tmpNow_);
//
//    }


//    _imgRGB->resize(img.rows*img.cols); // 预先分配空间

    for(int outter=0; outter<img.rows; outter+=1) {
        for (int inner = 0; inner < img.cols; inner += 1) {

            cv::Vec3b color = img.at<cv::Vec3b>(outter, inner); // 读取像素点的BGR值

            // 像素点 BGR 归一化
            glm::vec3 colorNow_ = {static_cast<float>(color[2])/255.f,
                                   static_cast<float>(color[1])/255.f,
                                   static_cast<float>(color[0])/255.f}; // 转换为RGB值

            _imgRGB(outter, inner) = colorNow_; // 存入数组
            //if(i%100==0 && j%100==0)cout << "i:" << i << "/" << img.rows << " j:" << j << "/" << img.cols<< endl;
        }
    }

}

void PolygonBase::fresh2D_scanRows_3(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3,
                                     vector<lineBoundary>* _lineBoundaries, int obj_t){
    //glm::vec2 up, mid, down;
    glm::vec2 acmes[3] = {p1, p2, p3};

    float biggestY = acmes[0].y, smallestY = acmes[0].y;

    _order3point order3point[3] = { // 默认 不是 不是 随机值!!
            {acmes[0], 0}, // 默认全是 rt 的
            {acmes[0], 0},
            {acmes[0], 0}
    };


    for(int i=0;i<3;++i){ // rt lb lt

        if(acmes[i].y > biggestY){ // 有更大?
            biggestY = acmes[i].y;
            order3point[2].point.x = acmes[i].x;
            order3point[2].point.y = acmes[i].y;
            order3point[2]._th = i;
        }
        else if(acmes[i].y < smallestY){ // 有更小?
            smallestY = acmes[i].y;
            order3point[0].point.x = acmes[i].x;
            order3point[0].point.y = acmes[i].y;
            order3point[0]._th = i;
        }
    }// 余下那个点就是 中间y高的

    for(int i=0;i<3;++i){
        if(order3point[0]._th != i && order3point[2]._th != i){ // 用刚才确定的_th 确定 中间点 y高可能完全一样

            order3point[1].point.x = acmes[i].x;
            order3point[1].point.y = acmes[i].y;
            order3point[1]._th = i;
            break;
        }
    }

    setLineScanScreenDeepLR_3(order3point,acmes, _lineBoundaries, obj_t); // point2deep()用的
}
void PolygonBase::setLineScanScreenDeepLR_3(_order3point order3point[], glm::vec2 p_3[],
                                            vector<lineBoundary>* _lineBoundaries, int obj_t) {
    _lineBoundaries->clear();

    float smallestY, midY, biggestY;int smallestY_int;
    smallestY = order3point[0].point.y;midY = order3point[1].point.y;
    biggestY = order3point[2].point.y;
    smallestY_int = static_cast<int>(roundf(smallestY));
    //_lineBoundaries->reserve(static_cast<int>(roundf(biggestY) - roundf(smallestY) + 1)); // smallestY偏大 biggestY偏小

    int nowY;
    if(midPointLineLeft(order3point[0].point, order3point[2].point, order3point[1].point)){
        // 中点在左侧 rx 顶到底
        //---cout << "midPoint左" << endl;



        int ii = 0; // lx 两线 连着用
        float nowEdgeX;
        float dx_dy;
        for(;ii<=midY - roundf(smallestY);++ii){// 中点在左侧 1~2 <2
            _lineBoundaries->push_back({});
            nowY = smallestY_int + ii;
            if(yOutOfScreen(nowY)){ // y 界外
                (*_lineBoundaries)[ii].lx = 0.f;
            }else {
                nowEdgeX = getXby_line_y_2D_4(p_3,order3point[0]._th, order3point[1]._th, (float) ii + roundf(smallestY),obj_t);
                (*_lineBoundaries)[ii].lx = nowEdgeX;
            }
        }


        for(;ii<=biggestY - roundf(smallestY);++ii){// 中点在左侧 2~3 <3
            _lineBoundaries->push_back({});
            nowY = smallestY_int + ii;
            if(yOutOfScreen(nowY)){ // y 界外
                (*_lineBoundaries)[ii].lx = 0.f;
            }else {
                nowEdgeX = getXby_line_y_2D_4(p_3,order3point[1]._th, order3point[2]._th,
                                              static_cast<float>(nowY), obj_t);
                (*_lineBoundaries)[ii].lx = nowEdgeX;
            }
        }

        for(int i=0;i<=biggestY - roundf(smallestY);++i){// 中点在左侧 1~3 <3

//            lineScanDeepLR[i].rx = smallestYdeep/*y自上往下记录*/ - i * SY_LY_deltaDeep;
//            lineScanDeepLR[i].y = i + smallestY; // 深度缓存 y自上往下记录
            nowY = smallestY_int + i;
            if(yOutOfScreen(nowY)){ // y 界外
                (*_lineBoundaries)[i].rx = 0.f;
            }else {
                // x 界外
                nowEdgeX = getXby_line_y_2D_4(p_3,order3point[0]._th, order3point[2]._th,
                                              static_cast<float>(nowY), obj_t);
                (*_lineBoundaries)[i].rx = nowEdgeX;
            }
            (*_lineBoundaries)[i].y = i + (int)roundf(smallestY);
        }

    }else{ // 中点在右侧 lx 顶到底
        //---cout << "midPoint右" << endl;



        int ii = 0; // lx 两线 连着用
        float nowEdgeX;
        for(;ii<=midY - roundf(smallestY); ++ii){// 中点在右侧 1~2 <2
            _lineBoundaries->push_back({});
//            lineScanDeepLR[ii].rx = smallestYdeep/*y自上往下记录*/ - ii * SY_MY_deltaDeep;
            nowY = smallestY_int + ii;
            if(yOutOfScreen(nowY)){
                (*_lineBoundaries)[ii].rx = 0.f;
            }else{
                nowEdgeX = getXby_line_y_2D_4(p_3,order3point[0]._th, order3point[1]._th,
                                              static_cast<float>(nowY), obj_t);
                (*_lineBoundaries)[ii].rx = nowEdgeX;
            }

        }



        for(;ii<=biggestY - roundf(smallestY); ++ii){// 中点在右侧  2~3 <3
            _lineBoundaries->push_back({});
//            lineScanDeepLR[ii].rx = midYdeep/*y自上往下记录*/ - (ii-jj) * MY_LY_deltaDeep;
            nowY = smallestY_int + ii;
            if(yOutOfScreen(nowY)){
                (*_lineBoundaries)[ii].rx = 0.f;
            }else{
                nowEdgeX = getXby_line_y_2D_4(p_3,order3point[1]._th, order3point[2]._th,
                                              static_cast<float>(nowY), obj_t);
                (*_lineBoundaries)[ii].rx = nowEdgeX;
            }


        }

        for(int i=0;i<=biggestY - roundf(smallestY); ++i){// 中点在右侧 1~3 <3

//            lineScanDeepLR[i].lx = smallestYdeep/*y自上往下记录*/ - i * SY_LY_deltaDeep;
//            lineScanDeepLR[i].y = i + smallestY; // 深度缓存 y自上往下记录
            nowY = smallestY_int + i;
            if(yOutOfScreen(nowY)){
                (*_lineBoundaries)[i].lx = 0.f;
            }else {
                nowEdgeX = getXby_line_y_2D_4(p_3,order3point[0]._th, order3point[2]._th,
                                              static_cast<float>(nowY), obj_t);
                (*_lineBoundaries)[i].lx = nowEdgeX;
            }
            (*_lineBoundaries)[i].y = nowY;
        }
    }
}
float PolygonBase::clampY(float y){
    return std::clamp(y, 0.0f, static_cast<float>(screenHeight_base));
}
void PolygonBase::fresh2D_scanRows_4(glm::vec2& p1, glm::vec2& p2, glm::vec2& p3, glm::vec2& p4,
                                     vector<lineBoundary>* _lineBoundaries, int obj_t){
    _order4point order4point[4] = { // 默认 不是 不是 随机值
            {p1,0}, // 默认 0 ltn 1 rtn 2 rbn 3 lbn
            {p2,1},
            {p3,2},
            {p4,3}
    };
    _order4point tmpInfo{};
    // 0 ltn 1 rtn 2 rbn 3 lbn
    for(int i=0;i<4-1; ++i){  // 0 1 2
        for(int j=0;j<4-1-i; ++j){ // (0,1,2) (0,1) (0)
            if(order4point[j].point.y > order4point[j+1].point.y){ // 有更大?
                tmpInfo.point = order4point[j].point;
                tmpInfo._th = order4point[j]._th;

                order4point[j].point = order4point[j+1].point;
                order4point[j]._th = order4point[j+1]._th;

                order4point[j+1].point = tmpInfo.point;
                order4point[j+1]._th = tmpInfo._th;
            }
        }
    }
    glm::vec2 p_4[4] = {p1,p2,p3,p4};
    setLineScanScreenDeepLR_4(order4point, p_4, _lineBoundaries, obj_t);
    DEBUG_SECTION(
        if(_lineBoundaries->size() > 5000){
        println(stderr,"lineBoundaries size: {} too large",
            _lineBoundaries->size());

    }
        )

}
void PolygonBase::setLineScanScreenDeepLR_4(_order4point order4point[], glm::vec2 p_4[],
                                            vector<lineBoundary>* _lineBoundaries, int obj_t){

    _lineBoundaries->clear();

    float smallestY, midSmallY, midBigY, biggestY;int smallest_int;
    smallestY = clampY(order4point[0].point.y);
    midSmallY = clampY(order4point[1].point.y);
    midBigY   = clampY(order4point[2].point.y);
    biggestY  = clampY(order4point[3].point.y);
    smallest_int = static_cast<int>(roundf(smallestY));
    //_lineBoundaries->reserve(int(floorf(biggestY) - roundf(smallestY) + 1)); // smallestY偏大 biggestY偏小
    int nowY;
    if(midPointLineLeft(order4point[0].point, order4point[3].point, order4point[1].point)){ //midSmallY 居左
        if(midPointLineLeft(order4point[0].point, order4point[3].point, order4point[2].point)){ // midBigY 居左

            // 左视角度
            int y_l = 0; // lx 两线 连着用

            for(; smallest_int + y_l < midSmallY; ++y_l){// 中点在左侧 1~2 <2
                nowY = smallest_int + y_l;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                // 高2D点 和 低2D点 定2D边线 y=ax+rtSet 再入y
                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[1]._th, static_cast<float>(nowY), obj_t);

            }

            for(; smallest_int + y_l < midBigY; ++y_l){// 中点在左侧 2~3 <3
                nowY = smallest_int + y_l;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[1]._th,
                                                                order4point[2]._th, static_cast<float>(nowY), obj_t);

            }

            for(; smallest_int + y_l <= biggestY; ++y_l){// 中点在左侧 3~4 <4
                nowY = smallest_int + y_l;
                _lineBoundaries->push_back({}); //                            0.0:float 0:int

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[2]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

            }

            // --------------------------- 画线 -----

            for(int y_r=0; smallest_int + y_r <= biggestY; ++y_r){// 中1点在左侧 中2点在左侧 rx 顶到底
                nowY = smallest_int + y_r;


                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_r].y = y_r + smallest_int; // 深度缓存 y自上往下记录
            }

        }
        else{ // midBigY 居右

            int y_l = 0; // lx 两线 连着用

            for(; smallest_int + y_l < midSmallY; ++y_l){// 中点在左侧 1~2 <2
                nowY = smallest_int + y_l;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[1]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_l].y = nowY; // 深度缓存 y自上往下记录

            }

            for(; smallest_int + y_l <= biggestY; ++y_l){// 中点在左侧 2~4 <4
                nowY = smallest_int + y_l;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[1]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_l].y = nowY; // 深度缓存 y自上往下记录

            }

            int y_r = 0; // rx 两线 连着用
            for(; smallest_int + y_r < midBigY; y_r++ ){// 中点在右侧 1~3 <3
                nowY = smallest_int + y_r;

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[2]._th, static_cast<float>(nowY), obj_t);


            }

            int mid0i = y_r; // 第二个循环 中点 可要从0开始加
            for(; smallest_int + y_r <= biggestY; y_r++ ){// 中点在右侧 3~4 <4
                nowY = smallest_int + y_r;

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[2]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

            }

        }
    }else{ //midSmallY 居右
        if(midPointLineLeft(order4point[0].point, order4point[3].point, order4point[2].point)){ // midBigY 居左

            int y_r = 0; // lx 两线 连着用

            for(; smallest_int + y_r < midSmallY; ++y_r){// 中点在右侧 1~2 <2
                nowY = smallest_int + y_r;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[1]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_r].y = nowY; // 深度缓存 y自上往下记录
            }

            for(; smallest_int + y_r <= biggestY; ++y_r){// 中点在右侧 2~4 <4
                nowY = smallest_int + y_r;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[1]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_r].y = nowY; // 深度缓存 y自上往下记录
            }

            int y_l = 0; // rx 两线 连着用
            for(; smallest_int + y_l < midBigY; y_l++ ){// 中点在左侧 1~3 <3
                nowY = smallest_int + y_l;

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[2]._th, static_cast<float>(nowY), obj_t);

            }

            for(; smallest_int + y_l <= biggestY; ++y_l){// 中点在左侧 3~4 <4
                nowY = smallest_int + y_l;

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[2]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

            }

        }
        else{ // midBigY 居右

            int y_r = 0; // rx 两线 连着用

            for(; smallest_int + y_r < midSmallY; ++y_r){// 中点在右侧 1~2 <2
                nowY = smallest_int + y_r;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[1]._th, static_cast<float>(nowY), obj_t);

            }

            for(; smallest_int + y_r < midBigY; ++y_r){// 中点在右侧 2~3 <3
                nowY = smallest_int + y_r;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[1]._th,
                                                                order4point[2]._th, static_cast<float>(nowY), obj_t);

            }



            for(; smallest_int + y_r <= biggestY; ++y_r){// 中点在右侧 3~4 <4
                nowY = smallest_int + y_r;
                _lineBoundaries->push_back({}); //                            0.0:float 0:int

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[2]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

            }

            for(int y_l=0; smallest_int + y_l <= biggestY; ++y_l){// 中1点在左侧 中2点在左侧 rx 顶到底
                nowY = smallest_int + y_l;

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_l].y = y_l + smallest_int; // 深度缓存 y自上往下记录
            }

        }
    }
}
void PolygonBase::fresh2D_scanRows_4_noClear(glm::vec2& p1, glm::vec2& p2, glm::vec2& p3, glm::vec2& p4,
                                             vector<lineBoundary>* _lineBoundaries, int obj_t){
    _order4point order4point[4] = { // 默认 不是 不是 随机值
            {p1,0}, // 默认 0 ltn 1 rtn 2 rbn 3 lbn
            {p2,1},
            {p3,2},
            {p4,3}
    };
    _order4point tmpInfo{};
    // 0 ltn 1 rtn 2 rbn 3 lbn
    for(int i=0;i<4-1; ++i){  // 0 1 2
        for(int j=0;j<4-1-i; ++j){ // (0,1,2) (0,1) (0)
            if(order4point[j].point.y > order4point[j+1].point.y){ // 有更大?
                tmpInfo.point = order4point[j].point;
                tmpInfo._th = order4point[j]._th;

                order4point[j].point = order4point[j+1].point;
                order4point[j]._th = order4point[j+1]._th;

                order4point[j+1].point = tmpInfo.point;
                order4point[j+1]._th = tmpInfo._th;
            }
        }
    }
    glm::vec2 p_4[4] = {p1,p2,p3,p4};
    setLineScanScreenDeepLR_4_noClear(order4point, p_4, _lineBoundaries, obj_t);
    if(_lineBoundaries->size() > 5000){
        string err = "lineBoundaries size: " + to_string(_lineBoundaries->size())
                     + " too large (no inner clear)";
        throw std::out_of_range(err);
    }
}
void PolygonBase::setLineScanScreenDeepLR_4_noClear(_order4point order4point[], glm::vec2 p_4[],
                                                    vector<lineBoundary>* _lineBoundaries, int obj_t){

    float smallestY, midSmallY, midBigY, biggestY;int smallest_int;
    smallestY = clampY(order4point[0].point.y);
    midSmallY = clampY(order4point[1].point.y);
    midBigY   = clampY(order4point[2].point.y);
    biggestY  = clampY(order4point[3].point.y);
    smallest_int = static_cast<int>(roundf(smallestY));
    //_lineBoundaries->reserve(int(floorf(biggestY) - roundf(smallestY) + 1)); // smallestY偏大 biggestY偏小
    int nowY;
    if(midPointLineLeft(order4point[0].point, order4point[3].point, order4point[1].point)){ //midSmallY 居左
        if(midPointLineLeft(order4point[0].point, order4point[3].point, order4point[2].point)){ // midBigY 居左

            // 左视角度
            int y_l = 0; // lx 两线 连着用

            for(; smallest_int + y_l < midSmallY; ++y_l){// 中点在左侧 1~2 <2
                nowY = smallest_int + y_l;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                // 高2D点 和 低2D点 定2D边线 y=ax+rtSet 再入y
                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[1]._th, static_cast<float>(nowY), obj_t);

            }

            for(; smallest_int + y_l < midBigY; ++y_l){// 中点在左侧 2~3 <3
                nowY = smallest_int + y_l;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[1]._th,
                                                                order4point[2]._th, static_cast<float>(nowY), obj_t);

            }

            for(; smallest_int + y_l <= biggestY; ++y_l){// 中点在左侧 3~4 <4
                nowY = smallest_int + y_l;
                _lineBoundaries->push_back({}); //                            0.0:float 0:int

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[2]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

            }

            // --------------------------- 画线 -----

            for(int y_r=0; smallest_int + y_r <= biggestY; ++y_r){// 中1点在左侧 中2点在左侧 rx 顶到底
                nowY = smallest_int + y_r;


                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_r].y = y_r + smallest_int; // 深度缓存 y自上往下记录
            }

        }
        else{ // midBigY 居右

            int y_l = 0; // lx 两线 连着用

            for(; smallest_int + y_l < midSmallY; ++y_l){// 中点在左侧 1~2 <2
                nowY = smallest_int + y_l;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[1]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_l].y = nowY; // 深度缓存 y自上往下记录

            }

            for(; smallest_int + y_l <= biggestY; ++y_l){// 中点在左侧 2~4 <4
                nowY = smallest_int + y_l;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[1]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_l].y = nowY; // 深度缓存 y自上往下记录

            }

            int y_r = 0; // rx 两线 连着用
            for(; smallest_int + y_r < midBigY; y_r++ ){// 中点在右侧 1~3 <3
                nowY = smallest_int + y_r;

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[2]._th, static_cast<float>(nowY), obj_t);


            }

            int mid0i = y_r; // 第二个循环 中点 可要从0开始加
            for(; smallest_int + y_r <= biggestY; y_r++ ){// 中点在右侧 3~4 <4
                nowY = smallest_int + y_r;

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[2]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

            }

        }
    }else{ //midSmallY 居右
        if(midPointLineLeft(order4point[0].point, order4point[3].point, order4point[2].point)){ // midBigY 居左

            int y_r = 0; // lx 两线 连着用

            for(; smallest_int + y_r < midSmallY; ++y_r){// 中点在右侧 1~2 <2
                nowY = smallest_int + y_r;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[1]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_r].y = nowY; // 深度缓存 y自上往下记录
            }

            for(; smallest_int + y_r <= biggestY; ++y_r){// 中点在右侧 2~4 <4
                nowY = smallest_int + y_r;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[1]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_r].y = nowY; // 深度缓存 y自上往下记录
            }

            int y_l = 0; // rx 两线 连着用
            for(; smallest_int + y_l < midBigY; y_l++ ){// 中点在左侧 1~3 <3
                nowY = smallest_int + y_l;

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[2]._th, static_cast<float>(nowY), obj_t);

            }

            for(; smallest_int + y_l <= biggestY; ++y_l){// 中点在左侧 3~4 <4
                nowY = smallest_int + y_l;

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[2]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

            }
        }
        else{ // midBigY 居右

            int y_r = 0; // rx 两线 连着用

            for(; smallest_int + y_r < midSmallY; ++y_r){// 中点在右侧 1~2 <2
                nowY = smallest_int + y_r;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[1]._th, static_cast<float>(nowY), obj_t);

            }

            for(; smallest_int + y_r < midBigY; ++y_r){// 中点在右侧 2~3 <3
                nowY = smallest_int + y_r;
                _lineBoundaries->push_back({}); //                            0.0:float 0.0:float 0:int

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[1]._th,
                                                                order4point[2]._th, static_cast<float>(nowY), obj_t);

            }



            for(; smallest_int + y_r <= biggestY; ++y_r){// 中点在右侧 3~4 <4
                nowY = smallest_int + y_r;
                _lineBoundaries->push_back({}); //                            0.0:float 0:int

                (*_lineBoundaries)[y_r].rx = getXby_line_y_2D_4(p_4, order4point[2]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

            }

            for(int y_l=0; smallest_int + y_l <= biggestY; ++y_l){// 中1点在左侧 中2点在左侧 rx 顶到底
                nowY = smallest_int + y_l;

                (*_lineBoundaries)[y_l].lx = getXby_line_y_2D_4(p_4, order4point[0]._th,
                                                                order4point[3]._th, static_cast<float>(nowY), obj_t);

                (*_lineBoundaries)[y_l].y = y_l + smallest_int; // 深度缓存 y自上往下记录
            }

        }
    }
}
float PolygonBase::getXby_line_y_2D_4(glm::vec2 p_4[], int upperP_th, int lowerP_th, float y, int obj_t){
    // y = a*x + b

    glm::vec2 upperP, lowerP;

    // 0 ltn 1 rtn 2 rbn 3 lbn

    upperP = p_4[upperP_th];
    lowerP = p_4[lowerP_th];


    float x;
    // 上下限锁
    // if(y > lowerP.y){
    //     //cerr << "2D lx rx: fix y:" << y << " > lowerP.y:" << lowerP.y <<
    //     //" lowerP.x:" << lowerP.x << endl;
    //     //cerr << "lt rt rb lb:" << lowerP_th << endl;
    //     y = lowerP.y; // 防止y越下界 求 lx rx 行扫描
    // }
    // else if(y < upperP.y){
    //     //cerr << "2D lx rx: fix y:" << y << " < upperP.y:" << upperP.y <<
    //     //" lowerP.x:" << lowerP.x << endl;
    //     //cerr << "lt rt rb lb:" << upperP_th << endl; // ### ###
    //     y = upperP.y; // 防止y越上界 求 lx rx 行扫描
    // }
    y = std::clamp(y,upperP.y,lowerP.y);


    // 等比例三角形求法
    /*         upperP(x,y)
     *           /|
     *          / |
     *      ?x /__| y
     *        /   |
     *       /    |
     *      /     |
     *     /      |
     *    /_______|
     *  lowerP(x,y)
     *
    */
    // (lowery - uppery) / (y - uppery) = (upperx - lowerx) / (upperx - x)
    // x = ux - (y-uy)*(ux-lx)/(ly-uy)

    if(lowerP.y != upperP.y){
        float dx_dy = (upperP.x - lowerP.x) / (lowerP.y - upperP.y);
        x = upperP.x + (upperP.y - y) * dx_dy;
    }else{
        x = upperP.x;// - (y - upperP.y) * (upperP.x - lowerP.x) / 1e-5f;
        //cerr << "polygon type: " << obj_t <<
        //     " 顶点y相等 lowerP.y:" << lowerP.y << " upperP.y:" << lowerP.y << " 相等" << endl;
    }
    return xLR_editInRange(x); // 左右x 哪个来了都不能出界!

}
bool PolygonBase::midPointLineLeft(glm::vec2& lineBegin, glm::vec2& lineEnd, glm::vec2& midPoint){
//    float ABx = lineEnd.x - lineBegin.x;
//    float ABy = lineEnd.y - lineBegin.y;
//    float ACx = midPoint.x - lineBegin.x;
//    float ACy = midPoint.y - lineBegin.y;
    glm::vec2 AB = lineEnd - lineBegin;
    glm::vec2 AC = midPoint - lineBegin;

    /*
             ABx                                      ABx
             m                                        m
       b__________e                             b__________e
        |    |    |                              |\   |    |
        |    |    | ACy                          | \  |big | ACy
   ABy m|____|____|                              |  \ |ger |
        |    |                              ABy m|___\|____|
        |    |                                   |    | mP
       e|____|                                   |smal|\
         ACx                                     |ler | \
                                                e|____|  \
                                                  ACx

   */


    // 使用向量叉积判断点的位置
    float cross = AB.x * AC.y - AB.y * AC.x; //crossProduct(lineBegin, lineEnd, midPoint);

    // 如果叉积大于0，点在线段的左侧
    if (cross > 0) {
        return true; // 点在线段左侧
    }
    return false; // 点在线段右侧或在线段上
}
float PolygonBase::xLR_editInRange(float _x){
//    if(_x < 0.f)return 0.f;
//    if(_x > static_cast<float>(screenWidth11))
//        return static_cast<float>(screenWidth11);
//    return _x;
    return std::clamp(_x, 0.f, static_cast<float>(screenWidth_base));
}
bool PolygonBase::yOutOfScreen(int y){
    return y < 0 || y > screenHeight_base;
}
bool PolygonBase::isFrontFacing(const glm::vec3& eyePos,
                                const goLine32& flatVertical,
                                const glm::vec3& flatCenter)
{
    /*
     // ax + by + cz + d = 0 (-垂距)
    // d = -ax - by - cz
    const float d = -flatVertical.dx*flatCenter.x - flatVertical.dy*flatCenter.y - flatVertical.dz*flatCenter.z;
    // 构造平面方程：
    const float eye2flat = glm::dot(eyePos, flatVertical._) + d;


    // 当方程值<0时视点在平面前方（法线指向侧）
    return eye2flat > 0.f;
    */

    glm::vec3 toEye = eyePos - flatCenter;
    return glm::dot(flatVertical._, toEye) > 0.0f;
}
glm::vec3 PolygonBase::calcReflect(const glm::vec3& inDirection, const glm::vec3& normal) {
    return glm::reflect(inDirection, normal);

    // float dotProduct = glm::dot(inDirection, normal);
    // return inDirection - 2.0f * dotProduct * normal;
}
double PolygonBase::pow2(double x) { return x * x; }
double PolygonBase::pow3(double x) { return x * x * x; }
double PolygonBase::pow4(double x) { return x * x * x * x; }
double PolygonBase::pow5(double x) { return x * x * x * x * x; }
double PolygonBase::pow6(double x) { return x * x * x * x * x * x; }
double PolygonBase::pow7(double x) { return x * x * x * x * x * x * x; }
double PolygonBase::pow8(double x) { return x * x * x * x * x * x * x * x; }
double PolygonBase::pow9(double x) { return x * x * x * x * x * x * x * x * x; }
