//
// Created by iceoc0 on 2025/10/2.
//

#include "GammaComplex.h"

extern void* _3d_2d_go_void_ptr; // 3d_2d_go的函数指针
// struct _3d_2d_go_gamma{
//     glm::vec2 (*_3d_2d_go)(ScreenDemo*, glm::vec3, glm::vec3*);
//     glm::vec2 (*_3d_2d)(ScreenDemo*, float, float, float);
//
// };
glm::vec2 (*__3d2dGogamma)(ScreenDemo*, glm::vec3, glm::vec3*) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d_go;
glm::vec2 (*__3d2dgamma)(ScreenDemo*, float, float, float) = ((_3d_2d_go_func*)_3d_2d_go_void_ptr)->_3d_2d;

using namespace Eigen;
namespace SolvePro{
    complex<double> M_PI_I = complex<double>(3.14159265358979323846, 0.0);

// 定义一个全局变量来存储误差信息
    std::array<double,2> checkRootErr = {-1.0, -1.0};
// Lanczos approximation for complex gamma function
    std::complex<double> my_gamma (const std::complex<double>& z) {
        static const double g = 7;
        static const double p[] = {
                0.99999999999980993,
                676.5203681218851,
                -1259.1392167224028,
                771.32342877765313,
                -176.61502916214059,
                12.507343278686905,
                -0.13857109526572012,
                9.9843695780195716e-6,
                1.5056327351493116e-7
        };
        if (z.real() < 0.5) {
            // Reflection formula
            return M_PI_I / (sin(M_PI_I * z) * my_gamma(1.0 - z));
        } else {
            std::complex<double> z1 = z - 1.0;
            std::complex<double> x = p[0];
            for (int i = 1; i < 9; ++i)
                x += p[i] / (z1 + (double)i);
            std::complex<double> t = z1 + g + 0.5;
            return sqrt(2.0 * M_PI_I) * pow(t, z1 + 0.5) * exp(-t) * x;
        }
    }
    // 从 SciPy 源码提取的复数伽玛函数实现
    std::complex<double> complex_gamma(std::complex<double> z) {
        const double PI = 3.14159265358979323846;
        const double lanczos_g = 7.0;  // Lanczos 常数

        if (std::real(z) < 0.5) {
            // 反射公式 Γ(z) = π / [sin(πz) Γ(1-z)]
            return PI / (std::sin(PI * z) * complex_gamma(1.0 - z));
        }

        // Lanczos 近似核心计算
        std::complex<double> x(0.99999999999980993, 0);
        std::array<double, 6> coeffs = {
                676.5203681218851, -1259.1392167224028, 771.32342877765313,
                -176.61502916214059, 12.507343278686905, -0.13857109526572012
        };

        z -= 1.0;
        for (int i = 0; i < coeffs.size(); ++i) {
            x += coeffs[i] / (z + std::complex<double>(i + 1.0, 0));
        }

        std::complex<double> t = z + lanczos_g + 0.5;
        return std::sqrt(2 * PI) * std::pow(t, z + 0.5) * std::exp(-t) * x;
    }

// 浮点数比较函数
    bool float_equal(double a, double b, double tol = 1e-9) {
        return abs(a - b) <= tol;
    }

// 检查结果的函数
    bool checkRoot(complex<double> xx, complex<double> yy,complex<double>* yy_) {
//        cout << "checkRoot: " << xx.real() << " + " <<
//             xx.imag() << " j, " << yy.real() << " + " << yy.imag() << " j" << endl;
        *yy_ = complex_gamma(xx);
//        cout << "yy_: " << yy_->real() << " + " << yy_->imag() << " j" << endl;
        checkRootErr[0] = abs(yy_->real() - yy.real());
        checkRootErr[1] = abs(yy_->imag() - yy.imag());
        if (checkRootErr[0] < 0.001 && checkRootErr[1] < 0.001) {
            return true;
        } else {
            return false;
        }
    }

// 残差函数
    std::array<double,2> residuals(double t, double b, const Vector3d& startPos, const Vector3d& goLine) {
        complex<double> xx = complex<double>(startPos[0] + t * goLine[0], b);
        complex<double> yy = complex_gamma(xx);
        double f1 = yy.real() - (startPos[1] + t * goLine[1]);
        double f2 = yy.imag() - (startPos[2] + t * goLine[2]);
        return {f1, f2};
    }


// 多元牛顿法求解
    bool solveRootNewton(const Vector3d& startPos, const Vector3d& goLine, Vector2d& tb,
                         int max_iter = 100, double tol = 1e-6) {
        double last_res_norm = 1e20; // 初始化一个大值
        int stopCnt1 = 0;
        const double STAG_THRESH = 0.8;  // 残差下降阈值
        vector<double> res_history;

        for (int iter = 0; iter < max_iter; ++iter) {
            Vector2d f;
            {
                auto res = residuals(tb[0], tb[1], startPos, goLine);
                f << res[0], res[1];
            }
            if (f.norm() < tol) return true;

// 监测残差变化（新增）
//            res_history.push_back(f.norm());
//            if (res_history.size() > 3) {
//                // 下降停滞检测
//                if (res_history.back() > res_history[res_history.size()-2]*STAG_THRESH) {
//                    return false;
//                }
//                // 振荡检测
//                auto [min_it, max_it]
//                        = minmax_element(res_history.end()-3, res_history.end());
//                if (*max_it - *min_it < 0.1 * res_history.back()) {
//                    return false;
//                }
//            }



            // 新增停止条件：残差范数停止下降
            if (iter > 3 && f.norm() > last_res_norm*0.9) {
                stopCnt1++;
                if(stopCnt1 > 3){
                    return false; // 连续3次残差无明显下降
                }

            }else{
                stopCnt1 = 0; // 连三次 被打断
            }
            last_res_norm = f.norm();


            // 数值计算雅可比矩阵
            double h = 1e-8;
            Matrix2d J;
            for (int i = 0; i < 2; ++i) {
                Vector2d tb1 = tb;
                tb1[i] += h;
                auto res1 = residuals(tb1[0], tb1[1], startPos, goLine);
                J.col(i) << (res1[0] - f[0]) / h, (res1[1] - f[1]) / h;
            }

            // 修改雅可比矩阵计算部分
            FullPivLU<Matrix2d> lu(J);
            if (!lu.isInvertible() || lu.rank() < 2) {    // 新增矩阵可逆判断
                return false;            // 矩阵不可逆时直接退出
            }
            Vector2d delta = lu.solve(-f);

            // 在solveRootNewton中添加信任域保护
            if (delta.norm() > 5.0) { // 限制单步最大变化量
                delta = delta.normalized() * 5.0;
            }
            tb += delta;

//            if (delta.norm() < tol) return true;
        }
        return false;
    }
    pair<complex<double>,complex<double>>
    getBestSolve(Vector3d current_startPos, Vector3d current_goLine, double max_length){
//        cout << "初始点: (" << current_startPos[0] << ", " << current_startPos[1] << ", " << current_startPos[2] << ")" << endl;
//        cout << "步进向量: (" << current_goLine[0] << ", " << current_goLine[1] << ", " << current_goLine[2] << ")" << endl;
        double b0 = 0.0;

        for (double step = 0; step < max_length; step += 1.0) {
            Vector2d tb(step, b0);
            bool found = SolvePro::solveRootNewton(current_startPos, current_goLine, tb);
            if (found) {
                double stepLen = tb[0];
                double b = tb[1];
                if (0 <= stepLen && stepLen <= max_length) {

                    Vector3d finalPos = current_startPos + stepLen * current_goLine;
                    complex<double> nowXX(finalPos[0], b);
                    complex<double> nowYY = {finalPos[1], finalPos[2]};
                    complex<double> __yy = complex<double>(0.0, 0.0);// = complex_gamma(nowXX);
                    complex<double> *_yy = &__yy;// = complex_gamma(nowXX);

                    if (SolvePro::checkRoot(nowXX, nowYY, _yy)) {
//                    cout << "\033[1;33m";
//                    cout << "初始点: (" << current_startPos[0] << ", " << current_startPos[1] << ", " << current_startPos[2] << ")" << endl;
//                    cout << "步进向量: (" << current_goLine[0] << ", " << current_goLine[1] << ", " << current_goLine[2] << ")" << endl;
//                    cout << "视线步长: " << stepLen << ", xx.imag: " << b << endl;
//                    cout << "交点坐标: (" << finalPos[0] << ", " << finalPos[1] << ", " << finalPos[2] << ")" << endl;
//                    cout << _yy->real() << "," << _yy->imag() << endl;
//                    cout << "err : " << SolvePro::checkRootErr[0] << " + " << SolvePro::checkRootErr[1] << " j" << endl;
//                    cout << "\033[0m" << endl;
                        return make_pair(complex<double>(finalPos[0], b), complex<double>(finalPos[1], finalPos[2]));
                    } else {
//                    cout << "步长: " << stepLen << ", xx.imag: " << b << endl;
//                    cout << "坐标: (" << finalPos[0] << ", " << finalPos[1] << ", " << finalPos[2] << ")" << endl;
//                    cout << "交点无效。" << endl;
//                    cout << "err : " << SolvePro::checkRootErr[0] << " + " << SolvePro::checkRootErr[1] << " j" << endl;
                        continue;
                    }
                }
            }

            if (SolvePro::float_equal(step, max_length - 1.0)) {
//                cout << "step: " << step << "未找到交点。" << endl;
            }
        }
        return make_pair(complex<double>(numeric_limits<double>::quiet_NaN(),
                                         numeric_limits<double>::quiet_NaN()),
                         complex<double>(numeric_limits<double>::quiet_NaN(),
                                         numeric_limits<double>::quiet_NaN())
        );
    }
}
namespace AdvancedSolvePro {

    const double TRUST_REGION_INIT = 5.0;
    const double CLUSTER_EPSILON = 1e-5;

    struct Solution {
        Vector2d tb;
        Vector3d pos;
        complex<double> gamma_val;
        double residual_norm;

        bool operator<(const Solution& other) const {
            return tb[0] < other.tb[0]; // 按步长排序
        }
    };

    vector<Solution> solution_cache;
    mutex cache_mutex;

    // 从 SciPy 源码提取的复数伽玛函数实现
    std::complex<double> complex_gamma(std::complex<double> z) {
        const double PI = 3.14159265358979323846;
        const double lanczos_g = 7.0;  // Lanczos 常数

        if (std::real(z) < 0.5) {
            // 反射公式 Γ(z) = π / [sin(πz) Γ(1-z)]
            return PI / (std::sin(PI * z) * complex_gamma(1.0 - z));
        }

        // Lanczos 近似核心计算
        std::complex<double> x(0.99999999999980993, 0);
        std::array<double, 6> coeffs = {
                676.5203681218851, -1259.1392167224028, 771.32342877765313,
                -176.61502916214059, 12.507343278686905, -0.13857109526572012
        };

        z -= 1.0;
        for (int i = 0; i < coeffs.size(); ++i) {
            x += coeffs[i] / (z + std::complex<double>(i + 1.0, 0));
        }

        std::complex<double> t = z + lanczos_g + 0.5;
        return std::sqrt(2 * PI) * std::pow(t, z + 0.5) * std::exp(-t) * x;
    }

    // 增强版伽马函数（添加缓存）
    complex<double> enhanced_gamma(const complex<double>& z) {
        static map<pair<double, double>, complex<double>> cache;
        auto key = make_pair(z.real(), z.imag());

        if (cache.find(key) != cache.end())
            return cache[key];

        auto result = complex_gamma(z);
        cache[key] = result;
        return result;
    }

    // 改进的残差计算
    Vector2d enhanced_residuals(double t, double b,
                                const Vector3d& start, const Vector3d& dir) {
        complex<double> z(start[0] + t*dir[0], b);
        complex<double> gamma = enhanced_gamma(z);
        return {
                gamma.real() - (start[1] + t*dir[1]),
                gamma.imag() - (start[2] + t*dir[2])
        };
    }

    // 自适应信任域牛顿法
    bool adaptive_solve(const Vector3d& start, const Vector3d& dir,
                        Vector2d& tb, double trust_region = TRUST_REGION_INIT) {
        for (int iter = 0; iter < 100; ++iter) {
            auto res = enhanced_residuals(tb[0], tb[1], start, dir);
            Vector2d f(res[0], res[1]);

            if (f.norm() < 1e-8) return true;

            // 动态雅可比计算
            Matrix2d J;
            const double h = 1e-8 * (1 + iter); // 自适应步长
            for (int i = 0; i < 2; ++i) {
                Vector2d perturbed = tb;
                perturbed[i] += h;
                auto res_p = enhanced_residuals(perturbed[0], perturbed[1], start, dir);
                J.col(i) << (res_p[0]-res[0])/h, (res_p[1]-res[1])/h;
            }

            // 信任域调整
            Vector2d delta = J.fullPivLu().solve(-f);
            Vector2d new_res = enhanced_residuals(tb[0]+delta[0], tb[1]+delta[1], start, dir);
            double actual_reduction = f.squaredNorm() - Vector2d(new_res[0], new_res[1]).squaredNorm();

            // 动态调整信任域
            if (actual_reduction > 0) {
                trust_region *= 1.2;
                tb += delta;
            } else {
                trust_region *= 0.5;
                delta = delta.normalized() * trust_region;
            }
            // 计算实际减少量时添加显式类型转换


            if (delta.norm() < 1e-8) return true;
        }
        return false;
    }

    // 并行区间扫描
    void fractal_scan(double t_min, double t_max, const Vector3d& start,
                      const Vector3d& dir, int depth = 0) {
        if (depth > 12) return; // 最大递归深度

        const double threshold = 1e-6 * (1 << depth);
        Vector2d res_min = enhanced_residuals(t_min, 0, start, dir);
        Vector2d res_max = enhanced_residuals(t_max, 0, start, dir);

        // 残差符号变化检测
        if (res_min[0]*res_max[0] < 0 || res_min[1]*res_max[1] < 0) {
//#pragma omp parallel sections
            {
//#pragma omp section
                {
                    Vector2d tb(t_min + (t_max-t_min)*0.25, 0);
                    if (adaptive_solve(start, dir, tb)) {
                        lock_guard<mutex> lock(cache_mutex);
                        solution_cache.push_back({tb, start + tb[0]*dir,
                                                  enhanced_gamma({start[0]+tb[0]*dir[0], tb[1]}),
                                                  Vector2d(res_min[0], res_min[1]).norm()});
                    }
                }

//#pragma omp section
                {
                    Vector2d tb(t_min + (t_max-t_min)*0.75, 0);
                    if (adaptive_solve(start, dir, tb)) {
                        lock_guard<mutex> lock(cache_mutex);
                        solution_cache.push_back({tb, start + tb[0]*dir,
                                                  enhanced_gamma({start[0]+tb[0]*dir[0], tb[1]}),
                                                  Vector2d(res_max[0], res_max[1]).norm()});
                    }
                }
            }

            fractal_scan(t_min, (t_min+t_max)/2, start, dir, depth+1);
            fractal_scan((t_min+t_max)/2, t_max, start, dir, depth+1);
        }
    }

    // 多解择优
    pair<complex<double>, complex<double>>
    optimized_solve(const Vector3d start, const Vector3d dir, double max_len) {
        solution_cache.clear();

        // 第一阶段：分形扫描
        fractal_scan(0, max_len, start, dir);

        // 第二阶段：全局搜索
//#pragma omp parallel for
        double once = max_len/100.0;
        for (double t = 0; t < max_len; t += once) {
            Vector2d tb(t, 0);
            if (adaptive_solve(start, dir, tb)) {
                lock_guard<mutex> lock(cache_mutex);
                Vector2d res = enhanced_residuals(tb[0], tb[1], start, dir);
                solution_cache.push_back({tb, start + tb[0]*dir,
                                          enhanced_gamma({start[0]+tb[0]*dir[0], tb[1]}),
                                          res.norm()});
            }
        }

        // 解聚类
        sort(solution_cache.begin(), solution_cache.end());
        vector<Solution> filtered;
        for (auto& s : solution_cache) {
            if (filtered.empty() || abs(filtered.back().tb[0] - s.tb[0]) > CLUSTER_EPSILON) {
                filtered.emplace_back(s);
            }
        }

        // 返回最优解
        vector<Solution>::iterator
        best = min_element(filtered.begin(), filtered.end(),
                                [](const Solution& a, const Solution& b) {
                                    return a.residual_norm < b.residual_norm;
                                });

        if (best != filtered.end() && best->residual_norm < 0.1 && best->tb[0] <= max_len) {
//            cout << "步长:" << best->tb[0] << endl;
            return {complex<double>(best->pos[0], best->tb[1]),
                    complex<double>(best->gamma_val.real(), best->gamma_val.imag())};
        }
        return {{numeric_limits<double>::quiet_NaN(),
                        numeric_limits<double>::quiet_NaN()},
                {numeric_limits<double>::quiet_NaN(),
                        numeric_limits<double>::quiet_NaN()}};
    }
}

GammaComplex::GammaComplex(glm::vec3 srartCenter, glm::vec3 _boxLengthHalf, unsigned char _debug_):
    PolygonBase(28){
    debugLine = _debug_;

    halfBoxLength = _boxLengthHalf;
    boxLenX = _boxLengthHalf.x * 2.f;
    boxLenY = _boxLengthHalf.y * 2.f;
    boxLenZ = _boxLengthHalf.z * 2.f;

    scanBox3D.center = srartCenter; // 包围盒中心

    scanBox3D.ltnSet.x = srartCenter.x - _boxLengthHalf.x; // 包围盒8角
    scanBox3D.ltnSet.y = srartCenter.y - _boxLengthHalf.y;
    scanBox3D.ltnSet.z = srartCenter.z - _boxLengthHalf.z;

    scanBox3D.rtnSet.x = srartCenter.x + _boxLengthHalf.x;
    scanBox3D.rtnSet.y = srartCenter.y - _boxLengthHalf.y;
    scanBox3D.rtnSet.z = srartCenter.z - _boxLengthHalf.z;

    scanBox3D.rbnSet.x = srartCenter.x + _boxLengthHalf.x;
    scanBox3D.rbnSet.y = srartCenter.y + _boxLengthHalf.y;
    scanBox3D.rbnSet.z = srartCenter.z - _boxLengthHalf.z;

    scanBox3D.lbnSet.x = srartCenter.x - _boxLengthHalf.x;
    scanBox3D.lbnSet.y = srartCenter.y + _boxLengthHalf.y;
    scanBox3D.lbnSet.z = srartCenter.z - _boxLengthHalf.z;

    scanBox3D.ltfSet.x = srartCenter.x - _boxLengthHalf.x;
    scanBox3D.ltfSet.y = srartCenter.y - _boxLengthHalf.y;
    scanBox3D.ltfSet.z = srartCenter.z + _boxLengthHalf.z;

    scanBox3D.rtfSet.x = srartCenter.x + _boxLengthHalf.x;
    scanBox3D.rtfSet.y = srartCenter.y - _boxLengthHalf.y;
    scanBox3D.rtfSet.z = srartCenter.z + _boxLengthHalf.z;

    scanBox3D.rbfSet.x = srartCenter.x + _boxLengthHalf.x;
    scanBox3D.rbfSet.y = srartCenter.y + _boxLengthHalf.y;
    scanBox3D.rbfSet.z = srartCenter.z + _boxLengthHalf.z;

    scanBox3D.lbfSet.x = srartCenter.x - _boxLengthHalf.x;
    scanBox3D.lbfSet.y = srartCenter.y + _boxLengthHalf.y;
    scanBox3D.lbfSet.z = srartCenter.z + _boxLengthHalf.z;

    scanBox3D_unchange.center = scanBox3D.center;

    scanBox3D_unchange.ltnSet = scanBox3D.ltnSet;
    scanBox3D_unchange.rtnSet = scanBox3D.rtnSet;
    scanBox3D_unchange.rbnSet = scanBox3D.rbnSet;
    scanBox3D_unchange.lbnSet = scanBox3D.lbnSet;

    scanBox3D_unchange.ltfSet = scanBox3D.ltfSet;
    scanBox3D_unchange.rtfSet = scanBox3D.rtfSet;
    scanBox3D_unchange.lbfSet = scanBox3D.lbfSet;
    scanBox3D_unchange.rbfSet = scanBox3D.rbfSet;

    renderNext = false;
    startRowIndex_ = 0;

    preNext = 0;

    allClouds.xRange[0] = -halfBoxLength.x;
    allClouds.xRange[1] = -halfBoxLength.x / 2.f;
    allClouds.xRange[2] = halfBoxLength.x / 2.0;
    allClouds.xRange[3] = halfBoxLength.x;

    allClouds.yRange[0] = -halfBoxLength.y;
    allClouds.yRange[1] = -halfBoxLength.y / 2.f;
    allClouds.yRange[2] = halfBoxLength.y / 2.0;
    allClouds.yRange[3] = halfBoxLength.y;

    allClouds.zRange[0] = -halfBoxLength.z;
    allClouds.zRange[1] = -halfBoxLength.z / 2.f;
    allClouds.zRange[2] = halfBoxLength.z / 2.0;
    allClouds.zRange[3] = halfBoxLength.z;


}
void GammaComplex::setBox3D(glm::vec3 _ltn, glm::vec3 _rtn, glm::vec3 _rbn, glm::vec3 _lbn,
                             glm::vec3 _ltf, glm::vec3 _rtf, glm::vec3 _rbf, glm::vec3 _lbf){
    scanBox3D.ltnSet = _ltn;
    scanBox3D.rtnSet = _rtn;
    scanBox3D.rbnSet = _rbn;
    scanBox3D.lbnSet = _lbn;

    scanBox3D.ltfSet = _ltf;
    scanBox3D.rtfSet = _rtf;
    scanBox3D.rbfSet = _rbf;
    scanBox3D.lbfSet = _lbf;

    freshGoX();freshGoY();freshGoDEEP();

    glm::vec3 centerThen = goX(_ltn,halfBoxLength.x);
    centerThen = goY(centerThen,halfBoxLength.y);
    centerThen = goDEEP(centerThen,halfBoxLength.z);
    scanBox3D.center = centerThen;

//    cout << "### boxLenX:" << boxLenX << endl;
//    cout << "### boxLenY:" << boxLenY << endl;
//    cout << "### boxLenZ:" << boxLenZ << endl;


}

void GammaComplex::setBox2D(glm::vec2 _ltn, glm::vec2 _rtn, glm::vec2 _rbn, glm::vec2 _lbn,
                             glm::vec2 _ltf, glm::vec2 _rtf, glm::vec2 _rbf, glm::vec2 _lbf,
                             glm::vec2 _center

){

    scanBox2D.set13P(_ltn, _rtn, _rbn, _lbn,
                      _ltf, _rtf, _rbf, _lbf,
                      _center);

    renderNext = 0;

    startRowIndex_ = 0;
    pixelSurfaceInfo_.clear();

}
void GammaComplex::Draw_Tick(ScreenDemo* ScreenEye){
    freshVirtualGoX(); // 屏幕系 数轴三向
    freshVirtualGoY();
    freshVirtualGoDEEP();


    if(renderNext == 1)deepFarNearBackCenter();

    freshFrameRotateInfo();

    solidRectangle2D(ScreenEye); // 计算 当前帧 渲染信息

    if (!renderNext) {
//        draw_particle(ScreenEye); // 绘制粒子
        draw_allClouds(ScreenEye);
    }

    float _color_[3];
    if (debugLine == 1) {

        _color_[0] = 1.0f;
        _color_[1] = 1.0f;
        _color_[2] = 1.0f; // 白色
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.ltn.x, scanBox2D.ltn.y,
                                      scanBox2D.rtn.x, scanBox2D.rtn.y,
                                      _color_, frameScreenNear);// 前框
//        cout << "~~draw ltn(" << scanBox2D.ltnSet.x << ", " << scanBox2D.ltnSet.y << ")" <<
//         "draw rtn(" << scanBox2D.rtnSet.x << ", " << scanBox2D.rtnSet.y << ")" << endl;
//        cout << " color:" << _color_[0] << " " << _color_[1] << " " << _color_[2] << endl;
//        cout << " frameScreenNear:" << frameScreenNear << endl;

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rtn.x, scanBox2D.rtn.y,
                                      scanBox2D.rbn.x, scanBox2D.rbn.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rbn.x, scanBox2D.rbn.y,
                                      scanBox2D.lbn.x, scanBox2D.lbn.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.lbn.x, scanBox2D.lbn.y,
                                      scanBox2D.ltn.x, scanBox2D.ltn.y,
                                      _color_, frameScreenNear);

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.ltf.x, scanBox2D.ltf.y,
                                      scanBox2D.rtf.x, scanBox2D.rtf.y,
                                      _color_, frameScreenNear);// 后框
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rtf.x, scanBox2D.rtf.y,
                                      scanBox2D.rbf.x, scanBox2D.rbf.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rbf.x, scanBox2D.rbf.y,
                                      scanBox2D.lbf.x, scanBox2D.lbf.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.lbf.x, scanBox2D.lbf.y,
                                      scanBox2D.ltf.x, scanBox2D.ltf.y,
                                      _color_, frameScreenNear);

        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.ltn.x, scanBox2D.ltn.y,
                                      scanBox2D.ltf.x, scanBox2D.ltf.y,
                                      _color_, frameScreenNear);// 前后连
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rtn.x, scanBox2D.rtn.y,
                                      scanBox2D.rtf.x, scanBox2D.rtf.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.rbn.x, scanBox2D.rbn.y,
                                      scanBox2D.rbf.x, scanBox2D.rbf.y,
                                      _color_, frameScreenNear);
        ScreenDemo::line2ScreenBuffer(ScreenEye,
                                      scanBox2D.lbn.x, scanBox2D.lbn.y,
                                      scanBox2D.lbf.x, scanBox2D.lbf.y,
                                      _color_, frameScreenNear);

    }
    preNext++;
    if(preNext > 5){
        preNext = 0;
        if(allClouds.totalSize < 300000){ // 点云 < 三十万
            renderNext = 1; // 看又 移动了 ?
        }
    }


}
void GammaComplex::solidRectangle2D(ScreenDemo* ScreenEye) {
//    pixelSurfaceInfo_.clear();

    scanBox2D.setLineBounary(lineScanFillColor);

    size_t rowAll = lineScanFillColor.size() + lineScanFillColor[0].y;
    allClouds.freshTotalSize();


    if(renderNext == 1){

        backRenderRow:
        if(startRowIndex_ < lineScanFillColor.size()) {
            lineBoundary _rowPosInfo = lineScanFillColor[startRowIndex_];

            rowPixelInfo28 rowpixelsInfo;
            println("ray 行:{}/{},列L:{},列R:{}",
                    _rowPosInfo.y, rowAll, _rowPosInfo.lx, _rowPosInfo.rx);
            if (_rowPosInfo.rx == _rowPosInfo.lx) {
                // 屏幕外的行 左右x相同

                startRowIndex_++;
                goto backRenderRow;
            }
            rowpixelsInfo.y = (float) _rowPosInfo.y; // 本行 y

            int rx_i = (int)roundf(_rowPosInfo.rx);
//            lock_guard<mutex> lock(cout_mutex);
//#pragma omp parallel for schedule(dynamic, 4) num_threads(8)
            for(int nowX = (int) roundf(_rowPosInfo.lx); nowX <= rx_i; ++nowX) { // 单像素循环
                onepixelInfo28 onepixelInfo;
                onepixelInfo.x = (float) nowX; // 本像素 x
                glm::vec3 startEye_Self = screenXYZ2SelfXYZ2(startEye);
                glm::vec3 screenPoint_Self = screenXYZ2SelfXYZ2({nowX, _rowPosInfo.y, 0.f});

                goLine32 eyeRay_Self = ScreenDemo::get_AgoB_direction3D(startEye_Self, screenPoint_Self); // 计算视线

                float step_InBox = stepInBox(startEye_Self, eyeRay_Self); // 计算 视点 到 包围盒 距离
                if(step_InBox < 0){
                    println("error stepInBox:", step_InBox," < 0");
                    continue;
                }
                glm::vec3 rayInBoxP_self = startEye_Self + eyeRay_Self._ * step_InBox; // 视点 到 包围盒 距离 点
//            println("~~rayInBoxP_self ({} {} {})", rayInBoxP_self.x, rayInBoxP_self.y, rayInBoxP_self.z);
                float boxOutStep = stepOutBox(rayInBoxP_self, eyeRay_Self); // 视线 出 包围盒 距离

//                pair<complex<double>,complex<double>>
//                nearestRes = AdvancedSolvePro::optimized_solve(
//                        Vector3d(rayInBoxP_self.x, rayInBoxP_self.y, rayInBoxP_self.z),
//                        Vector3d(eyeRay_Self.dx, eyeRay_Self.dy, eyeRay_Self.dz), boxOutStep);
                pair<complex<double>,complex<double>>
                        nearestRes = SolvePro::getBestSolve(
                        Vector3d(rayInBoxP_self.x, rayInBoxP_self.y, rayInBoxP_self.z),
                        Vector3d(eyeRay_Self.dx, eyeRay_Self.dy, eyeRay_Self.dz), boxOutStep);

                bool solvePairNAN = isnan(nearestRes.first.real()) || isnan(nearestRes.first.imag()) ||
                        isnan(nearestRes.second.real()) || isnan(nearestRes.second.imag());
                if(solvePairNAN){
//                    cerr << "error solvePairNAN" << endl;
                    continue;
                }
                glm::vec3 nearPosScreen = self2screenAxis({nearestRes.first.real(),
                                                           nearestRes.second.real(), nearestRes.second.imag()});
                if(nearPosScreen.z < frameScreenNear){
                    frameScreenNear = nearPosScreen.z;
                }else if(nearPosScreen.z > frameScreenFar){
                    frameScreenFar = nearPosScreen.z;
                }
                onepixelInfo.screenDeep = nearPosScreen.z; // 像素深度

                glm::vec3 colorNow = getColorBy_vX(nearestRes.second.imag());
                onepixelInfo.rgb[0] = colorNow.x;
                onepixelInfo.rgb[1] = colorNow.y;
                onepixelInfo.rgb[2] = colorNow.z;
                //
                rowpixelsInfo.pixelDeeps.emplace_back(onepixelInfo);

                if(allClouds.totalSize < 300000){ // 小于三十万就 往里头加
                    allClouds.setPosButClose({nearestRes.first.real(),
                                              nearestRes.second.real(), nearestRes.second.imag()},
                                             colorNow);
                }

            }
            pixelSurfaceInfo_.emplace_back(rowpixelsInfo);

            startRowIndex_++;
        }
        for(auto& _rowpixelsInfo : pixelSurfaceInfo_) {

            for (auto &_onepixelInfo: _rowpixelsInfo.pixelDeeps) {
                if (isnan(_onepixelInfo.rgb[0])) {
                    continue;
                }

                ScreenEye->putPixel(_onepixelInfo.x,_rowpixelsInfo.y,
                                    _onepixelInfo.rgb,_onepixelInfo.screenDeep,
                                    (PolygonBase*)this);
            }
        }
    }

}
float GammaComplex::min_1in3(float a, float b, float c){

    return std::min(a, std::min(b, c));
}
float GammaComplex::max_1in3(float a, float b, float c){

    return std::max(a,std::max(b,c));
}
float GammaComplex::stepInBox(glm::vec3 Eye_Self,goLine32 eyeRay_Self){
    // 视点 已经在 轴范围内
    bool eyeInX = Eye_Self.x >= -halfBoxLength.x && Eye_Self.x <= halfBoxLength.x;
    bool eyeInY = Eye_Self.y >= -halfBoxLength.y && Eye_Self.y <= halfBoxLength.y;
    bool eyeInZ = Eye_Self.z >= -halfBoxLength.z && Eye_Self.z <= halfBoxLength.z;

    float stepInX = 0.f;
    float stepInY = 0.f;
    float stepInZ = 0.f;

    if(!eyeInX){
        if(eyeRay_Self.dx > 0){
            // x 左射右
            // x<0 dx>0
            stepInX = (-halfBoxLength.x - Eye_Self.x) / eyeRay_Self.dx;
        }else{
            // x 右射左
            // x>0 dx<0
            stepInX = (Eye_Self.x - halfBoxLength.x) / eyeRay_Self.dx * -1.f;
        }
//        println("~~stepInX {}", stepInX);
    }
    if(!eyeInY){
        if(eyeRay_Self.dy > 0){
            // y 上射下
            // y<0 dy>0
            stepInY = (-halfBoxLength.y - Eye_Self.y) / eyeRay_Self.dy;

        }else{
            // y 下射上
            // y>0 dy<0
            stepInY = (Eye_Self.y - halfBoxLength.y) / eyeRay_Self.dy * -1.f;
        }
//        println("~~stepInY {}", stepInY);
    }
    if(!eyeInZ){
        if(eyeRay_Self.dz > 0){
            // z 后射前
            // z<0 dz>0
            stepInZ = (-halfBoxLength.z - Eye_Self.z) / eyeRay_Self.dz;
        }else{
            // z 前射后
            // z>0 dz<0
            stepInZ = (Eye_Self.z - halfBoxLength.z) / eyeRay_Self.dz * -1.f;
        }
//        println("~~stepInZ {}", stepInZ);
    }
    return max_1in3(stepInX, stepInY, stepInZ);
}
float GammaComplex::stepOutBox(glm::vec3 flatPoint_Self,goLine32 eyeRay_Self){
    float stepOutX = 10000.f;
    float stepOutY = 10000.f;
    float stepOutZ = 10000.f;

    bool flatPosInBox = flatPoint_Self.x >= -halfBoxLength.x-2.f && flatPoint_Self.x <= halfBoxLength.x+2.f &&
                        flatPoint_Self.y >= -halfBoxLength.y-2.f && flatPoint_Self.y <= halfBoxLength.y+2.f &&
                        flatPoint_Self.z >= -halfBoxLength.z-2.f && flatPoint_Self.z <= halfBoxLength.z+2.f;
    if(!flatPosInBox){
        println("~~flatPosInBox({}, {}, {}) not in box", flatPoint_Self.x, flatPoint_Self.y, flatPoint_Self.z);
//        throw exception("flatPosInBox not in box");
    }

    if(eyeRay_Self.dx > 0){
        // x 内射右
        stepOutX = (halfBoxLength.x - flatPoint_Self.x) / eyeRay_Self.dx;
    }else{
        // x 内射左
        stepOutX = (flatPoint_Self.x - -halfBoxLength.x) / eyeRay_Self.dx * -1.f;
    }
//    println("~~stepOutX {}", stepOutX);
    if(eyeRay_Self.dy > 0){
        // y 内射下
        stepOutY = (halfBoxLength.y - flatPoint_Self.y) / eyeRay_Self.dy;

    }else{
        // y 内射上
        stepOutY = (flatPoint_Self.y - -halfBoxLength.y) / eyeRay_Self.dy * -1.f;
    }
//    println("~~stepOutY {}", stepOutY);
    if(eyeRay_Self.dz > 0){
        // z 内射前
        stepOutZ = (halfBoxLength.z - flatPoint_Self.z) / eyeRay_Self.dz;
    }else{
        // z 内射后
        stepOutZ = (flatPoint_Self.z - -halfBoxLength.z) / eyeRay_Self.dz * -1.f;
    }
//    println("~~stepOutZ {}", stepOutZ);
    return min_1in3(stepOutX, stepOutY, stepOutZ);
}
void GammaComplex::freshGoX(){
    world_toX.dx = (scanBox3D.rtnSet.x - scanBox3D.ltnSet.x) / boxLenX;
    world_toX.dy = (scanBox3D.rtnSet.y - scanBox3D.ltnSet.y) / boxLenX;
    world_toX.dz = (scanBox3D.rtnSet.z - scanBox3D.ltnSet.z) / boxLenX;
}
void GammaComplex::freshGoY(){
    world_toY.dx = (scanBox3D.lbnSet.x - scanBox3D.ltnSet.x) / boxLenY;
    world_toY.dy = (scanBox3D.lbnSet.y - scanBox3D.ltnSet.y) / boxLenY;
    world_toY.dz = (scanBox3D.lbnSet.z - scanBox3D.ltnSet.z) / boxLenY;
}
void GammaComplex::freshGoDEEP() {
    world_toDEEP.dx = (scanBox3D.ltfSet.x - scanBox3D.ltnSet.x) / boxLenZ;
    world_toDEEP.dy = (scanBox3D.ltfSet.y - scanBox3D.ltnSet.y) / boxLenZ;
    world_toDEEP.dz = (scanBox3D.ltfSet.z - scanBox3D.ltnSet.z) / boxLenZ;

}
glm::vec3 GammaComplex::goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toX._;
    return _srcXYZ;
}
glm::vec3 GammaComplex::goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toY._;
    return _srcXYZ;
}
glm::vec3 GammaComplex::goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * world_toDEEP._;
    return _srcXYZ;
}
void GammaComplex::deepFarNearBackCenter(){
    frameScreenFar = virtual_scanBox3D.center.z;
    frameScreenNear = virtual_scanBox3D.center.z;
}
void GammaComplex::setFrontColor(int _color1) {
    BGR3f colorNow;
    colorNow.setBGR(_color1, 1);
    frontColor_rgb01[0] = colorNow.r1;
    frontColor_rgb01[1] = colorNow.g1;
    frontColor_rgb01[2] = colorNow.b1;
//    cout << "color: " << frontColor_rgb01.r << ", " << frontColor_rgb01.g << ", " << frontColor_rgb01.b << endl;

//    loadParticle(R"(I:\PolygonDisplay\img\output.txt)"); // 载入粒子
}
void GammaComplex::freshVirtualGoX() {
    // 提前 求向量长度 便于归一化

    virtual_toX.dx = (virtual_scanBox3D.rtnSet.x - virtual_scanBox3D.ltnSet.x) / boxLenX;
    virtual_toX.dy = (virtual_scanBox3D.rtnSet.y - virtual_scanBox3D.ltnSet.y) / boxLenX;
    virtual_toX.dz = (virtual_scanBox3D.rtnSet.z - virtual_scanBox3D.ltnSet.z) / boxLenX;

}

void GammaComplex::freshVirtualGoY() {
    virtual_toY.dx = (virtual_scanBox3D.lbnSet.x - virtual_scanBox3D.ltnSet.x) / boxLenY;
    virtual_toY.dy = (virtual_scanBox3D.lbnSet.y - virtual_scanBox3D.ltnSet.y) / boxLenY;
    virtual_toY.dz = (virtual_scanBox3D.lbnSet.z - virtual_scanBox3D.ltnSet.z) / boxLenY;
}

void GammaComplex::freshVirtualGoDEEP() {
    virtual_toDEEP.dx = (virtual_scanBox3D.ltfSet.x - virtual_scanBox3D.ltnSet.x) / boxLenZ;
    virtual_toDEEP.dy = (virtual_scanBox3D.ltfSet.y - virtual_scanBox3D.ltnSet.y) / boxLenZ;
    virtual_toDEEP.dz = (virtual_scanBox3D.ltfSet.z - virtual_scanBox3D.ltnSet.z) / boxLenZ;
}
glm::vec3 GammaComplex::Virtual_goX(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toX._;
    return _srcXYZ;
}
glm::vec3 GammaComplex::Virtual_goY(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toY._;
    return _srcXYZ;
}
glm::vec3 GammaComplex::Virtual_goDEEP(glm::vec3 _srcXYZ, float _move){
    _srcXYZ += _move * virtual_toDEEP._;
    return _srcXYZ;
}

void GammaComplex::freshFrameRotateInfo(){
    frameRotateInfo_q = PolygonBase::getFrameRotateInfo_(virtual_toX,virtual_toDEEP);
}
glm::vec3 GammaComplex::screenXYZ2SelfXYZ2(glm::vec3 _screenAxisPos){
    if(isnan(_screenAxisPos.x) || isnan(_screenAxisPos.y) || isnan(_screenAxisPos.z)){
        println(stderr,"9次 _screenAxisPos(", _screenAxisPos.x, ", ", _screenAxisPos.y,
             ", ", _screenAxisPos.z, ")");
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }// 不是 nan
    glm::vec3 back000 = virtual_scanBox3D.center;

    glm::vec3 p1ToScreenAxis000 = _screenAxisPos - back000; // 归原点

    float distanceOf000 = glm::length(p1ToScreenAxis000); // 原点距
    goLine64 p1ToScreenAxis000_dir1 = {p1ToScreenAxis000.x / distanceOf000,
                                       p1ToScreenAxis000.y / distanceOf000,
                                       p1ToScreenAxis000.z / distanceOf000}; // 归一化
    // 没两角全0  不然不用斜转

    PolygonBase::rotate_vector(p1ToScreenAxis000_dir1, frameRotateInfo_q);
    glm::vec3 farScreenAxis000 = {(float)p1ToScreenAxis000_dir1.dx * distanceOf000,
                                  (float)p1ToScreenAxis000_dir1.dy * distanceOf000,
                                  (float)p1ToScreenAxis000_dir1.dz * distanceOf000};

//    farScreenAxis000 += back000; // 离原点

    if(isnan(farScreenAxis000.x) || isnan(farScreenAxis000.y) || isnan(farScreenAxis000.z)){
        println(stderr,"9次 farScreenAxis000(", farScreenAxis000.x, ", ", farScreenAxis000.y, ", ", farScreenAxis000.z, ")");
        return glm::vec3{std::numeric_limits<float>::quiet_NaN()};
    }
    return farScreenAxis000;
}

bool GammaComplex::xxRealInBox(double xxReal){
    return xxReal > -halfBoxLength.x && xxReal < halfBoxLength.x;
}
//bool GammaComplex::xxImagInBox(double xxImag){
//
//}
bool GammaComplex::yyRealInBox(double yyReal){
    return yyReal > -halfBoxLength.y && yyReal < halfBoxLength.y;
}
bool GammaComplex::yyImagInBox(double yyImag){
    return yyImag/2.0 > -halfBoxLength.z && yyImag/2.0 < halfBoxLength.z;
}
std::string GammaComplex::strip(const std::string &s) {
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
void GammaComplex::loadParticle(string filename){
    namespace fs = std::filesystem;

// 检查文件是否存在
    if (fs::exists(filename)) {
        println("filename: ", filename);
        // 文件操作...
        std::ifstream theFile(filename);
        std::string theLine;

        if (theFile.is_open()) {
            while (getline(theFile, theLine, ';')) { // 逐行读取
                std::istringstream rowNow(theLine);
                std::string varstr;

                Particle28 particleNow;
                particleNow.xxRe = numeric_limits<double>::quiet_NaN();
                particleNow.xxIm = numeric_limits<double>::quiet_NaN();
                particleNow.yyRe = numeric_limits<double>::quiet_NaN();
                particleNow.yyIm = numeric_limits<double>::quiet_NaN();
                for(int i=0; getline(rowNow, varstr, ','); ++i){

                    varstr = strip(varstr);

                    double xRe, xIm, yRe, yIm;
//                    cout << "varstr: " << varstr << endl;
                    switch (i) {
                        case 0:
//                            solvePairs->emplace_back();
                            xRe = stod(varstr);
                            if(xxRealInBox(xRe)){
                                particleNow.xxRe = xRe;
                            }
                            break;
                        case 1:
                            xIm = stod(varstr);
                            particleNow.xxIm = xIm;
                            break;
                        case 2:
                            yRe = stod(varstr);
                            if(yyRealInBox(yRe)){
                                particleNow.yyRe = yRe;
                            }
                            break;
                        case 3:
                            yIm = stod(varstr);
                            if(yyImagInBox(yIm)){
                                particleNow.yyIm = yIm;
                            }
                            break;
                        default:
                            throw std::runtime_error("Invalid input file format");
                            break;
                    }

                }
                if(isnan(particleNow.xxRe) || isnan(particleNow.xxIm) ||
                   isnan(particleNow.yyRe) || isnan(particleNow.yyIm)){
//                    cout << "loadParticle()函数：输入数据有nan！" << endl;
//                cout << "particleNow: " << particleNow.xxRe << ", " <<
//                     particleNow.xxIm << ", " << particleNow.yyRe << ", " << particleNow.yyIm << endl;
                    continue;
                }
                particleNow.color = getColorBy_vX(particleNow.xxIm);
//                cout << "particleNow: " << particleNow.xxRe << ", " <<
//                     particleNow.xxIm << ", " << particleNow.yyRe << ", " << particleNow.yyIm << endl;
//                cout << "color: " << particleNow.color.r << ", " <<
//                     particleNow.color.g << ", " << particleNow.color.b << endl;
                particleInBox.emplace_back(particleNow);
//                std::cout << theLine << std::endl;
            }
            theFile.close();
        } else {
            println(stderr,"无法打开文件");
        }
    }else{
        println("文件不存在");
    }
}
void GammaComplex::draw_particle(ScreenDemo* ScreenEye){
    for(auto& info : particleInBox){
        bool err = isnan(info.xxRe) ||
                   isnan(info.xxIm) ||
                   isnan(info.yyRe) ||
                   isnan(info.yyIm) ;
        if(err){
            println(stderr,"draw_particle()函数：输入数据有nan！");
            continue;
        }
        glm::vec3 virtualPos1 = self2screenAxis({info.xxRe, info.yyRe, info.yyIm});
        glm::vec2 posNow2D1 = __3d2dgamma(ScreenEye, virtualPos1.x, virtualPos1.y, virtualPos1.z);

        float color1[3] = {info.color.r, info.color.g, info.color.b};
        ScreenEye->putPixel((int)posNow2D1.x, (int)posNow2D1.y, color1, virtualPos1.z, (PolygonBase*)this);
    }
}
glm::vec3 GammaComplex::getColorBy_vX(float _vX){
//    cout << "solve of vX:" << _vX << endl;
    int remainder = static_cast<int>(_vX) % 10; // -9~9
    float colorRatio = 1.f + 0.07f * (float)remainder;
//    cout << " ~~ remainder = " << remainder << endl;
//    cout << " ~~ colorRatio = " << colorRatio << endl;
//    cout << "color: " << frontColor_rgb01.r << ", " << frontColor_rgb01.g << ", " << frontColor_rgb01.b << endl;
    return frontColor_rgb01 * colorRatio;


}

glm::vec3 GammaComplex::self2screenAxis(glm::vec3 _selfAxisPos){
    // 屏幕系下 自己系 斜走x 斜走y 斜走z
    glm::vec3 posNow = virtual_scanBox3D.center;
    posNow = Virtual_goX(posNow, _selfAxisPos.x);
    posNow = Virtual_goY(posNow, _selfAxisPos.y);
    posNow = Virtual_goDEEP(posNow, _selfAxisPos.z);
    return posNow;
}
void GammaComplex::draw_allClouds(ScreenDemo* ScreenEye){
    for(auto& tinyBox : allClouds.tinyBox64){
        for(auto& particle : tinyBox.pointsInTinyBox){
            glm::vec3 virtualPos1 = self2screenAxis(particle.pos);
            glm::vec2 posNow2D1 = __3d2dgamma(ScreenEye, virtualPos1.x, virtualPos1.y, virtualPos1.z);

            float color1[3] = {particle.color.r, particle.color.g, particle.color.b};
            ScreenEye->putPixel((int)posNow2D1.x, (int)posNow2D1.y, color1, virtualPos1.z, (PolygonBase*)this);
        }
    }
}