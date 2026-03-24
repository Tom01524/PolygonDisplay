
#include"../polygon_init/bezier22Edge3_1.h"

#include"../func_main/bezier22Edge3_func.h"

// #include <cstdlib>
// #include <cstdio>
#include <thread> // g++


std::mutex cout_mutex;

bool _w,_s,_a,_d,_q,_e;
bool _j,_l,_i,_k,_o,_u,_c,_v;

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void switchDebugByClickedXY();
void MovingTurning();

void Display();

[[maybe_unused]]void polygonCollisionInStep(char direction);
void firstStart();

void colorBand();
[[maybe_unused]] void loadImgByFog(vector<unique_ptr<PolygonBase>>* polygonAll_ptr, string filename,const glm::vec3& pos);
void freshPolygonAfterScreenGo();
void freshPolygonByAxis(char key);

vector<unique_ptr<PolygonBase>> polygonAll;

RectDemo* StandSquarePtr = nullptr;//bodySquare_init(&polygonAll); // 脚下 顶底两方框



unique_ptr<ScreenDemo> ScreenEyeBaseL; // 眼睛 屏幕  2 4

unique_ptr<AxisDemo> AxisTilt; // 倾斜坐标轴
unique_ptr<AxisDemo> ParallelAxis; // 平行坐标轴
AxisDemo* AxisTiltPtr; // 倾斜坐标轴
AxisDemo* ParallelAxisPtr; // 平行坐标轴

int widthNow, heightNow;
// float windowScaleH = (float) windowHeight;
// float windowScaleW = (float) windowWidth;


// for\s*\((.*?);(.*?);\s*(\w+)\+\+\)
// for($1;$2; ++$3)    for循环 前置自增 全文件替换

int main()
{

    ScreenEyeBaseL = screenAndEyeGo_init(); // 眼睛 屏幕

    AxisTilt = axisXYZ_init(); // Display()函数 必是void (*func)(void) 指针支持全局使用
    ParallelAxis = parallel_axisXYZ_init();
    AxisTiltPtr = AxisTilt.get();
    ParallelAxisPtr = ParallelAxis.get();


    // triaComonInit(&polygonAll, triangle1SpotXYZ,0x827cf0,0x4b808e,/*debug*/true,0,3); // 香叶红 草灰绿 BGR
    // triaComonInit(&polygonAll, triangle2SpotXYZ,0x539422,0x4b808e,true,0,/*objname*/3); // 孔雀绿 草灰绿 BGR
    // loadMainObj(&polygonAll, "../trianglesAll/tiger_template.obj.txt");
    // loadRooTriangles(&polygonAll);

//----------------------------------------------------------------------------------------------
    // rectComonInit(&polygonAll, rect1SpotXYZ,0xd0bb63,0x4b808e,false,0); // 霁青 草灰绿 BGR
    // rectComonInit(&polygonAll, rect2SpotXYZ,0x41dafb,0x227388,false,0); // 油菜花黄 苔绿 BGR
//----------------------------------------------------------------------------------------------
    // sphereInit(&polygonAll, SpherePos001.ltnSet,SpherePos001.rtnSet,SpherePos001.lbnSet,SpherePos001.ltfSet,
    //                0x78962c,0x6ad8f8, 0x7d8870,
    //                 0);
    // sphereImgInit(&polygonAll, SpherePos001.ltnSet,SpherePos001.rtnSet,SpherePos001.lbnSet,SpherePos001.ltfSet,
    //            0x78962c,0x6ad8f8, 0x7d8870,
    //            R"(G:\Saved_Pictures\bottle_3.png)", 0);
    // sphereImgInit(&polygonAll,SpherePos002.ltnSet,SpherePos002.rtnSet,SpherePos002.lbnSet,SpherePos002.ltfSet,
    //             0xff2eff,0xffff2e, 0x7d8870,
    //             R"(G:\Saved_Pictures\Screenshot_2024-04-04-08-23.jpg)", 1); // 亮粉 浅蓝
//----------------------------------------------------------------------------------------------
    // coneInit(&polygonAll, ConePos002, 0x241662/*甘蔗紫*/,0x37d3fc, 0x227388, 0); //  柠檬黄 苔绿
    // coneInit(&polygonAll, ConePos001, 0xefc739,0x1851f8, 0x227388, 0); // 蓝 红
//----------------------------------------------------------------------------------------------
    // 加载图片 ScreenGo模式 不在循环
    // loadImgByFog(&polygonAll, "F:/rarely_document/pvz_cpp/pvz_demo/res/zhiwu/3/10.png",
    //     {-220.0f,240.0f,200.0f});
    // loadImgByFog(&polygonAll, "F:/rarely_document/pvz_cpp/pvz_demo/res/Map/background5.jpg",
    // {-320.0f,340.0f,300.0f});
//----------------------------------------------------------------------------------------------
    // imgRectComonInit(&polygonAll, R"(G:\Saved_Pictures\diffusers_kolors_painted_wall.png)",
    //                  rect4SpotXYZ,0x539422,0x4b808e,false); // 绿 褐黄
    // imgRectComonInit(&polygonAll, R"(G:\Saved_Pictures\fantasy_girl.png)",
    //                  rect5SpotXYZ,NULL,0x4b808e,false); // 绿 褐黄
//----------------------------------------------------------------------------------------------
    // fogObjCustom1Init(&polygonAll, {-320.0f, 35.0f, 250.0f},0xffff67, false);
    // fogObjCustom2Init(&polygonAll, {-320.0f, 35.0f, 250.0f},0xff33cc, false);
//----------------------------------------------------------------------------------------------
    // fogObjCustom3Init(&polygonAll, {-32.0f, 35.0f, 75.0f},0xffe933, false);
    // fogObjCustom4Init(&polygonAll, {72.0f, 35.0f, 75.0f},0x4bf623, false);
    // fogObjInit_roo(&polygonAll, {75.0f, 25.0f, -30.0f},0x4bf623, false);
//----------------------------------------------------------------------------------------------
    Bezier223Init(&polygonAll,0x85cd1e, 0xf9f9fb,0x4b808e,0);
    Bezier223Init2(&polygonAll,0x85cd1e, 0xf9f9fb,0x4b808e,0);
//----------------------------------------------------------------------------------------------
     //BicubicBezierInit(&polygonAll, 0xffff2e, 0xf9f9fb); // 浅蓝 白
    //Bezier3ImgInit(&polygonAll, 0xffff2e, 0xf9f9fb); // 浅蓝 白

     //Bezier3MirrorInit(&polygonAll, rollPart,mirrorMoved1,0x85cd1e, 0xf9f9fb); // 暗灰 灰白
     // Bezier3MirrorInit(&polygonAll, art,mirrorMoved2,0xffff2e, 0xf9f9fb); // 暗灰 灰白

      BicubicBezierInitUtah1(&polygonAll, 0x12dccb, 0xdc1297); // 盖
      BicubicBezierInitUtah2(&polygonAll, 0x12dccb, 0xdc1297); // 嘴
      BicubicBezierInitUtah3(&polygonAll, 0x12dccb, 0x7c5a24);
//----------------------------------------------------------------------------------------------
    // 霁青 玉髓绿 瓦松绿
     // equation2Init(&polygonAll, {-200.0f, 50.0f, -200.0f}, {75.0f, 75.0f, 100.0f}, -0.02f, 0.2f,1.f,
     //               0xd0bb63, 0x49b341, NULL,0);
     // equation2_4Init(&polygonAll, {-200.0f, 50.0f, 300.0f}, {75.0f, 100.0f, 200.0f}, -0.02f, 0.2f,1.f,
     //                 0xd0bb63, 0x49b341, NULL,0); // 慢! 橘色 f6a623 紫色 9941d3
//----------------------------------------------------------------------------------------------
     // equation3Init(&polygonAll, {200.0f, 50.0f, -200.0f}, {75.0f, 75.0f, 80.0f},
     //               -0.002f, 0.02f,0.2,1.f,
     //               0xd0bb63,0x23a6f6, 0xd34199, 0);
     // equation3_9Init(&polygonAll, {200.0f, 50.0f, 450.0f}, {65.0f, 75.0f, 200.0f},
     //                 -0.002f, 0.02f,0.2,1.f,
     //                 0xd0bb63,0x23a6f6, 0xd34199, 0);
//----------------------------------------------------------------------------------------------
     //gammaInit(&polygonAll, {25.0f, 25.0f, 25.0f}, {20.0f, 70.0f, 50.0f},0x23d1f6, 1); // 超 慢

//----------------------------------------------------------------------------------------------
   //  arrow_1_init(&polygonAll); // 箭头1iii
   //  glm::vec3 clockCenter_ = arrow_2_init(&polygonAll); // 箭头2
   //
   // CircleXYZ dialPlate = CircleXYZ({clockCenter_.x-102,clockCenter_.y-102,clockCenter_.z}, // lt
   //           {clockCenter_.x+102,clockCenter_.y-102,clockCenter_.z}, // rt
   //           {clockCenter_.x+102,clockCenter_.y+102,clockCenter_.z}, // rb
   //           {clockCenter_.x-102,clockCenter_.y+102,clockCenter_.z}); // lb
   // circleInit(&polygonAll,&dialPlate,0xe4e0e6/*白*/, 0x7d8870, false, 0);
//----------------------------------------------------------------------------------------------

    firstStart();
    

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    // 在创建GLFW窗口前获取内容缩放比例


    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    struct GLFWwindow*
    window = glfwCreateWindow(windowWidth, windowHeight, "Polygon Display", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    // 才创建窗口，才可以获取OpenGL版本信息
    const GLubyte* renderer = glGetString(GL_RENDERER); // 获取显卡型号
    const GLubyte* version = glGetString(GL_VERSION); // 获取OpenGL版本
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported: %s\n", version);

    glfwSwapInterval(1);


    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glDisable(GL_DEPTH_TEST);  // 关闭深度测试
    glDisable(GL_STENCIL_TEST); // 关闭模板缓存
    glDepthMask(GL_FALSE); // 对于深度测试，可以改用glDepthMask(GL_FALSE)临时禁用写入
//    int key = 0;
    while (!glfwWindowShouldClose(window))
    {
//        float ratio;
        //class std::chrono::time_point<struct std::chrono::steady_clock> start = std::chrono::steady_clock::now(); // 计时开始

        // if(heightNow != windowHeight){
        //     windowScaleH = static_cast<float>(heightNow) / (float) windowHeight; // 高缩比
        // }
        // if(widthNow != windowWidth){
        //     windowScaleW = static_cast<float>(widthNow) / (float) windowWidth; // 宽缩比
        // }

        glfwGetFramebufferSize(window, &widthNow, &heightNow);
//        ratio = widthNow / (float) heightNow;

        //glViewport(x, y, width, height) - 设置视口(绘制区域)，参数指定左下角坐标(x,y)和宽高尺寸
        glViewport(0, 0, widthNow, heightNow);
        glClear(GL_COLOR_BUFFER_BIT);

        //glMatrixMode(mode) - 设置当前矩阵模式，参数可以是：
        //
        //GL_PROJECTION 投影矩阵
        //GL_MODELVIEW 模型视图矩阵
        //GL_TEXTURE 纹理矩阵

        //glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); // - 将当前矩阵重置为单位矩阵


        //- 设置正交投影矩阵，定义了一个立方体裁剪空间
//        glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        glOrtho(0, windowWidth, windowHeight, 0, -1,
                std::numeric_limits<float>::max()); // 注意Y轴是从上到下的

//        glMatrixMode(GL_MODELVIEW);
//        glLoadIdentity();

        //对当前矩阵进行旋转变换，参数是旋转角度和旋转轴向量
//        glTranslatef(screenWidth/2.0f, screenHeight/2.0f, 0.0f); // 移到中心
//        glRotatef((float)glfwGetTime() * 50.f, 1.f, 0.f, 0.f);  // 旋转
//        glTranslatef(-screenWidth/2.0f, -screenHeight/2.0f, 0.0f); // 移回

        MovingTurning();


        // 绘制
        Display();


        if(ScreenEyeBaseL->objBufferFresh){
            switchDebugByClickedXY();
            ScreenEyeBaseL->objBufferFresh = false;
        }

//        println("按键 鼠标 ?");
//        std::this_thread::sleep_for(std::chrono::milliseconds(5000));// 延迟 2000ms
        //处理所有等待中的事件(如键盘、鼠标输入)
        glfwPollEvents();
//        println("按键 鼠标 !");


        ScreenEyeBaseL->flushBatchDraw();
        //交换前后缓冲区，实现双缓冲渲染
        glfwSwapBuffers(window);


        //  class std::chrono::time_point<struct std::chrono::steady_clock> end = std::chrono::steady_clock::now(); // 计时结束
        //  std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // 计算耗时
        // // 帧率控制
        //  if (duration.count() < 16666) { // 60FPS的帧间隔时间（1,000,000μs ÷ 60 ≈ 16,666μs）
        //      std::this_thread::sleep_for(std::chrono::microseconds(16666 - duration.count()));
        //  }
        //
        // else{
        //     std::cout << "frame time over 16.6ms: " << duration.count() << "μs\n";
        // }
    }

    //销毁指定窗口并释放相关资源
    glfwDestroyWindow(window);

    //终止GLFW库，释放所有分配的资源
    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    //const char* keyName = glfwGetKeyName(key, scancode);
    // 添加按键检测和打印
    //if (action == GLFW_PRESS)
    _w = glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS;
    _s = glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS;
    _a = glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS;
    _d = glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS;
    _q = glfwGetKey(window,GLFW_KEY_Q) == GLFW_PRESS;
    _e = glfwGetKey(window,GLFW_KEY_E) == GLFW_PRESS;
    _j = glfwGetKey(window,GLFW_KEY_J) == GLFW_PRESS;
    _l = glfwGetKey(window,GLFW_KEY_L) == GLFW_PRESS;
    _i = glfwGetKey(window,GLFW_KEY_I) == GLFW_PRESS;
    _k = glfwGetKey(window,GLFW_KEY_K) == GLFW_PRESS;
    _o = glfwGetKey(window,GLFW_KEY_O) == GLFW_PRESS;
    _u = glfwGetKey(window,GLFW_KEY_U) == GLFW_PRESS;
    _c = glfwGetKey(window,GLFW_KEY_C) == GLFW_PRESS;
    _v = glfwGetKey(window,GLFW_KEY_V) == GLFW_PRESS;

//    _w = glfwGetKey(window,GLFW_KEY_W) == GLFW_RELEASE;
//    _s = glfwGetKey(window,GLFW_KEY_S) == GLFW_RELEASE;


}

void MovingTurning(){
    if(runningMode==mode._leftView){
        if(_w){
 

            print("前移 ");
            // polygonCollisionInStep('w');

             // if (by_axis) {
                axisMoveXYZ(AxisTiltPtr, 'w', goStep);
                freshPolygonByAxis( 'w'); // 移动了 才刷新
            // }
        }
        if(_s){
//          if (1) {
            print("后移 ");
            // polygonCollisionInStep('s');

            // if (by_axis) {
                axisMoveXYZ(AxisTiltPtr, 's', goStep);
                freshPolygonByAxis( 's');
            // }

        }
        if(_a){

            print("左移 ");
            // polygonCollisionInStep('a');

            // if (by_axis) {
                axisMoveXYZ(AxisTiltPtr, 'a', goStep);
                freshPolygonByAxis( 'a');
            // }

        }
        if(_d){
//        if(1){
            print("右移 ");
            // polygonCollisionInStep('d');

             // if (by_axis) {
                axisMoveXYZ(AxisTiltPtr, 'd', goStep);
                freshPolygonByAxis( 'd');
            // }

        }
        if(_q){

            print("上移 ");
            // polygonCollisionInStep('q');

            // if (by_axis) {
                axisMoveXYZ(AxisTiltPtr, 'q', goStep);
                freshPolygonByAxis( 'q');
            // }

        }
        if(_e) {

            print("下移 ");
            // polygonCollisionInStep('e');

            // if (by_axis) {
                axisMoveXYZ(AxisTiltPtr, 'e', goStep);
                freshPolygonByAxis( 'e');
            // }

        }
        if(_j) {

            print("左转 ");

             // if (by_axis) {
//                axisTurnXYZ_Quaternion(AxisTiltPtr, ScreenEyeBaseL, 'j', goAngle);
                axisTurnXYZ_EulerAngle(AxisTiltPtr, ScreenEyeBaseL.get(), 'j', goAngle);
                freshPolygonByAxis( 'j');
            // }

        }
        if(_l) {

            print("右转 ");

            // if (by_axis) {
                axisTurnXYZ_EulerAngle(AxisTiltPtr, ScreenEyeBaseL.get(), 'l', goAngle);

                freshPolygonByAxis( 'l');
            // }

        }
        if(_i /*###*/) {

            print("上翻 ");

            // if (by_axis) {
                axisTurnXYZ_EulerAngle(AxisTiltPtr, ScreenEyeBaseL.get(), 'i', goAngle);
                freshPolygonByAxis('i');
            // }


        }
        if(_k) {

            print("下翻 ");

            // if (by_axis) {
                axisTurnXYZ_EulerAngle(AxisTiltPtr, ScreenEyeBaseL.get(), 'k', goAngle);

                freshPolygonByAxis('k');
            // }


        }
        if(_o) {

            print("右旋 ");

             // if (by_axis) {
                axisTurnXYZ_EulerAngle(AxisTiltPtr, ScreenEyeBaseL.get(), 'o', goAngle);

                freshPolygonByAxis( 'o');
            // }

        }
        if(_u) {

            print("左旋 ");

             // if (by_axis) {
                axisTurnXYZ_EulerAngle(AxisTiltPtr, ScreenEyeBaseL.get(), 'u', goAngle);

                freshPolygonByAxis('u');
            // }

        }
        if(_c) {

            // if (by_axis) {
                print("转表逆 ");
                //axisTurnXYZ_EulerAngle(AxisTiltPtr, ScreenEyeBaseL60, 'lbSet', goAngle);

                for (auto &i: polygonAll) {
                    if (i->type_ == 3) {
                        //printf("^^^^▲ objNaame:%d\n", ((TriangleDemo *) (polygonAll[i]->flatPtr))->objName);
                        TriangleDemo* triangleNow = dynamic_cast<TriangleDemo *>(i.get());
                        if (triangleNow->objName == 1) {
                            //printf("箭头1\n");
                            triangleTurn_Unchange_XYZ(triangleNow, &bottomCenter,
                                                      'o', 1.5f);

                            fresh2S2M2L_XY_by_axis_Go(triangleNow,AxisTiltPtr, ScreenEyeBaseL.get());

                        } else if (triangleNow->objName == 2) {
                            //printf("箭头2\n");
                            triangleTurn_Unchange_XYZ(triangleNow, &bottomCenter2,
                                                      'o', 0.125f);

                            fresh2S2M2L_XY_by_axis_Go(triangleNow, AxisTiltPtr, ScreenEyeBaseL.get());
                        }
                    }
                }
            // }

        }
        if(_v) {

            // if (by_axis) {
                print("转表顺 ");
                //axisTurnXYZ_EulerAngle(AxisTiltPtr, ScreenEyeBaseL60, 'lbSet', goAngle);

                for (auto &i: polygonAll) {
                    if (i->type_ == 3) {
                        //printf("^^^^▲ objNaame:%d\n", ((TriangleDemo *) (polygonAll[i]->flatPtr))->objName);
                        TriangleDemo* triangleNow = dynamic_cast<TriangleDemo *>(i.get());
                        if (triangleNow->objName == 1) {
                            //printf("箭头1\n");
                            triangleTurn_Unchange_XYZ(triangleNow, &bottomCenter,
                                                      'u', 1.5f);

                            fresh2S2M2L_XY_by_axis_Go(triangleNow, AxisTiltPtr, ScreenEyeBaseL.get());

                        } else if (triangleNow->objName == 2) {
                            //printf("箭头2\n");
                            triangleTurn_Unchange_XYZ(triangleNow, &bottomCenter2,
                                                      'u', 0.125f);

                            fresh2S2M2L_XY_by_axis_Go(triangleNow, AxisTiltPtr, ScreenEyeBaseL.get());
                        }
                    }
                }
            // }

        }
    }

    else if(runningMode==mode._screenGo){
        if(_w){

            print("前移 ");
            //polygonCollisionInStep('w');

            screenMoveXYZ(ScreenEyeBaseL.get(), 'w', goStep); // a 代表前移
            //rectMoveXYZSelf(StandSquarePtr, 'w', goStep);
            freshPolygonAfterScreenGo();

        }
        if(_s){

            print("后移 ");
            //polygonCollisionInStep('s');

            screenMoveXYZ(ScreenEyeBaseL.get(), 's', goStep); // d 代表后移
            //rectMoveXYZSelf(StandSquarePtr, 's', goStep);
            freshPolygonAfterScreenGo();

        }
        if(_a){

            print("左移 ");
            //polygonCollisionInStep('a');

            screenMoveXYZ(ScreenEyeBaseL.get(), 'a', goStep); // w 代表左移
            //rectMoveXYZSelf(StandSquarePtr, 'a', goStep);
            freshPolygonAfterScreenGo();

        }
        if(_d){

            print("右移 ");
            //polygonCollisionInStep('d');

            screenMoveXYZ(ScreenEyeBaseL.get(), 'd', goStep); // s 代表右移
            //rectMoveXYZSelf(StandSquarePtr, 'd', goStep);
            freshPolygonAfterScreenGo();

        }
        if(_q){

            print("上移 ");
            //polygonCollisionInStep('q');

            screenMoveXYZ(ScreenEyeBaseL.get(), 'q', goStep);
            //rectMoveXYZSelf(StandSquarePtr, 'q', goStep);
            freshPolygonAfterScreenGo();

        }
        if(_e) {

            print("下移 ");
            //polygonCollisionInStep('e');

            screenMoveXYZ(ScreenEyeBaseL.get(), 'e', goStep);
            //rectMoveXYZSelf(StandSquarePtr, 'e', goStep);
            freshPolygonAfterScreenGo();

        }
        if(_j) {

            print("左转 ");
            screenTurnXYZ(ScreenEyeBaseL.get(), 'j', goAngle);
            freshPolygonAfterScreenGo();

        }
        if(_l) {

            print("右转 ");
            screenTurnXYZ(ScreenEyeBaseL.get(), 'l', goAngle);
            freshPolygonAfterScreenGo();

        }
        if(_i) {

            print("上翻 ");
            screenTurnXYZ(ScreenEyeBaseL.get(), 'i', goAngle);
            freshPolygonAfterScreenGo();

        }
        if(_k) {

            print("下翻 ");
            screenTurnXYZ(ScreenEyeBaseL.get(), 'k', goAngle);
            freshPolygonAfterScreenGo();

        }
        if(_o) {

            print("右旋 ");
            screenTurnXYZ(ScreenEyeBaseL.get(), 'o', goAngle);
            freshPolygonAfterScreenGo();

        }
        if(_u) {

            print("左旋 ");
            screenTurnXYZ(ScreenEyeBaseL.get(), 'u', goAngle);
            freshPolygonAfterScreenGo();

        }
        if(_c) {

            print("转表逆 ");
            ScreenEyeBaseL->freshInfo(); // 刷新 屏幕信息
            for (auto & i : polygonAll) {
                if (i->type_ == 3) {
                    //printf("^^^^▲ objNaame:%d\n", ((TriangleDemo *) (polygonAll[i]->flatPtr))->objName);
                    TriangleDemo* triangleNow = dynamic_cast<TriangleDemo *>(i.get());
                    if (triangleNow->objName == 1) {
                        //printf("箭头1\n");
                        triangleCenterTurnXYZ(triangleNow, &bottomCenter,
                                              'o',1.5f);

                        fresh2S2M2L_XY_Go(triangleNow, ScreenEyeBaseL.get());

                    } else if (triangleNow->objName == 2) {
                        //printf("箭头2\n");
                        triangleCenterTurnXYZ(triangleNow, &bottomCenter2,
                                              'o',0.125f);

                        fresh2S2M2L_XY_Go(triangleNow, ScreenEyeBaseL.get());
                    }
                }
            }

        }
        if(_v) {

            print("转表顺 ");
            ScreenEyeBaseL->freshInfo(); // 刷新 屏幕信息
            for (auto & i : polygonAll) {

                if (i->type_ == 3) {
                    //print("^^^^▲ objNaame:%d\n", ((TriangleDemo *) (polygonAll[i]->flatPtr))->objName);
                    TriangleDemo* triangleNow = dynamic_cast<TriangleDemo *>(i.get());
                    if (triangleNow->objName == 1) {
                        //printf("箭头1\n");
                        triangleCenterTurnXYZ(triangleNow, &bottomCenter,
                                              'u',1.5f);

                        fresh2S2M2L_XY_Go(triangleNow, ScreenEyeBaseL.get());

                    } else if (triangleNow->objName == 2) {
                        //printf("箭头2\n");
                        triangleCenterTurnXYZ(triangleNow, &bottomCenter2,
                                              'u',0.125f);

                        fresh2S2M2L_XY_Go(triangleNow, ScreenEyeBaseL.get());
                    }
                }

            }

        }
    }

//    std::this_thread::sleep_for(std::chrono::milliseconds(20));// 延迟 20ms
}
// 鼠标点击回调函数
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        println("鼠标点击坐标: ({:.0f}, {:.0f})", xpos, ypos);

        // if(widthNow != windowWidth)
        // {xpos = xpos / windowScaleW;}
        // if(heightNow != windowHeight)
        // {ypos = ypos / windowScaleH;}
        // if(widthNow != windowWidth || heightNow != windowHeight)
        // {printf("鼠标修正坐标: (%.0f, %.0f)\n", xpos, ypos);}

//GLFW_MOUSE_BUTTON_RIGHT
//GLFW_MOUSE_BUTTON_MIDDLE


        if (colorBarShow && xpos >= colorBarLeft && xpos <= colorBarLeft + 255) {
            if (ypos <= windowHeight - colorBarHeight * 2 &&
            ypos >= windowHeight - colorBarHeight * 3) {
                blueI = static_cast<int>(xpos);
            } else if (ypos <= windowHeight - colorBarHeight &&
            ypos >= windowHeight - colorBarHeight * 2) {
                greenI = static_cast<int>(xpos);
            } else if (ypos <= windowHeight &&
            ypos >= windowHeight - colorBarHeight) {
                redI = static_cast<int>(xpos);
            }
            println("color b: {} g: {} r: {}", blueI, greenI, redI);
        }

//        int objBufferIndex = ScreenEyeBaseL->indexOfPixelsVector((int)xpos, (int)ypos);
//        PolygonBase* objThis = ScreenEyeBaseL->objBuffer[objBufferIndex];
//        cout << "objBufferIndex:" << objBufferIndex << endl;
//        cout << "addr:" << std::hex << objThis << endl;

        ScreenEyeBaseL->clickedLast.x = static_cast<int>(xpos);
        ScreenEyeBaseL->clickedLast.y = static_cast<int>(ypos);
        ScreenEyeBaseL->objBufferFresh = true;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));// 延迟 20ms
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        if(colorBarShow)colorBarShow = false;
        else colorBarShow = true;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));// 延迟 20ms
    }
}
void switchDebugByClickedXY(){
    glm::ivec2 clickedPos = ScreenEyeBaseL->clickedLast;

    PolygonBase* objThis = ScreenEyeBaseL->objBuffer(clickedPos.y,clickedPos.x);
    if(objThis == nullptr)return; // 点击在 外面

    if (objThis->type_ == 3) { // 三角形 是否被点击
        // ▲被点击
        dynamic_cast<TriangleDemo *>(objThis)->switchDebug(); // 切换debug模式

    } else if (objThis->type_ == 4) { // 矩形是否被点击

        dynamic_cast<RectDemo *>(objThis)->switchDebug(); // 切换debug模式

    } else if (objThis->type_ == 5) { // 雾点是否被点击

        dynamic_cast<FogObjDemo *>(objThis)->switchDebug(); // 切换debug模式


    } else if (objThis->type_ == 10) { // 圆是否被点击

        dynamic_cast<CircleDemo *>(objThis)->switchDebug(); // 切换debug模式


    } else if (objThis->type_ == 6){

        dynamic_cast<SphereDemo *>(objThis)->switchDebug(); // 切换debug模式


    } else if (objThis->type_ == 13) { // 圆锥是否被点击
        // 圆锥被点击
        dynamic_cast<ConeDemo *>(objThis)->switchDebug(ScreenEyeBaseL.get()); // 切换debug模式

    } else if (objThis->type_ == 23) { // 贝塞尔曲线是否被点击
        dynamic_cast<Bezier33Edge4 *>(objThis)->switchDebug(AxisTiltPtr); // 切换debug模式
        // 延迟 20ms

    } else if (objThis->type_ == 20) { // 二次方程_复曲面_是否被点击
        dynamic_cast<EquationTwo *>(objThis)->switchDebug(); // 切换debug模式
        // 延迟 20ms

    } else if (objThis->type_ == 21) {
        dynamic_cast<EquationTwo4 *>(objThis)->switchDebug();

    } else if (objThis->type_ == 22) { // 贝塞尔 镜面
        dynamic_cast<Bezier33Edge4Mirror *>(objThis)->switchDebug(AxisTiltPtr);

    } else if (objThis->type_ == 26) { // 贝塞尔
        dynamic_cast<Bezier3Img *>(objThis)->switchDebug(AxisTiltPtr);

    } else if (objThis->type_ == 9) {
        dynamic_cast<Bezier22Edge3 *>(objThis)->switchDebug();
    }
    // 延迟 20ms
    std::this_thread::sleep_for(std::chrono::milliseconds(50));

}

void Display(){
    // 坐标轴
    if(runningMode==mode._leftView || runningMode==mode._screenGo){ // 左视机位
        AxisTiltPtr->drawTiltAxis3Color(ScreenEyeBaseL.get()); // 绘制
        ParallelAxisPtr->drawAxis(ScreenEyeBaseL.get()); // 绘制平行坐标轴
        for(auto & i : polygonAll){// 画 几何面 坐标轴
            if(i->type_ == 4){ // 矩形
                dynamic_cast<RectDemo *>(i.get())->drawRectAxis(ScreenEyeBaseL.get());
            }else if(i->type_ == 10){ // 圆面
                dynamic_cast<CircleDemo*>(i.get())->drawCircleAxis(ScreenEyeBaseL.get());
            }else if(i->type_ == 6){ // 球
                dynamic_cast<SphereDemo*>(i.get())->drawSphereAxis(ScreenEyeBaseL.get());
            }else if(i->type_ == 13){
                dynamic_cast<ConeDemo*>(i.get())->drawConeAxis(ScreenEyeBaseL.get());
            }else if(i->type_ == 20){
                dynamic_cast<EquationTwo*>(i.get())->drawTheAxis(ScreenEyeBaseL.get());
            }else if(i->type_ == 21){
                dynamic_cast<EquationTwo4*>(i.get())->drawTheAxis(ScreenEyeBaseL.get());
            }
        }
    }



    // 写入帧缓存
    if(runningMode==mode._leftView){ // 左视机位
        const int numPolys = static_cast<int>(polygonAll.size());
        lock_guard<mutex> lock(cout_mutex);

#pragma omp parallel for schedule(dynamic, 4) num_threads(8)
        for(int idx = 0; idx < numPolys; ++idx) {
            const auto &poly = polygonAll[idx];
            switch (poly->type_) {
                case 4:
                    dynamic_cast<RectDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 3:
                    dynamic_cast<TriangleDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 1:
                    dynamic_cast<RectDemo *>(poly.get())->drawRectOnly(ScreenEyeBaseL.get());
                    break;
                case 5:
                    dynamic_cast<FogObjDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 10:
                    dynamic_cast<CircleDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 6:
                    dynamic_cast<SphereDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 13:
                    dynamic_cast<ConeDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 23:
                    dynamic_cast<Bezier33Edge4 *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get(), AxisTiltPtr);
                    break;
                case 8:
                    dynamic_cast<ImgRect *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 20:
                    dynamic_cast<EquationTwo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 21:
                    dynamic_cast<EquationTwo4 *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 24:
                    dynamic_cast<EquationThree9 *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 25:
                    dynamic_cast<EquationThree *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 28:
                    dynamic_cast<GammaComplex *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 22:
                    dynamic_cast<Bezier33Edge4Mirror *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get(), AxisTiltPtr);
                    break;
                case 26:
                    dynamic_cast<Bezier3Img *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get(), AxisTiltPtr);
                    break;
                case 9: // 贝塞尔 双二次 三边
                    dynamic_cast<Bezier22Edge3 *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
//                default:
//                    break;

            }
        }

    }else if(runningMode==mode._screenGo) { // 自由机位
         // 避免多次调用size()
        const int numPolys = static_cast<int>(polygonAll.size());
        lock_guard<mutex> lock(cout_mutex);

#pragma omp parallel for schedule(dynamic, 4) num_threads(8)
        for(int idx = 0; idx < numPolys; ++idx) {
            const auto &poly = polygonAll[idx];
            switch (poly->type_) {
                case 4:
                    dynamic_cast<RectDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 3:
                    dynamic_cast<TriangleDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 1:
                    dynamic_cast<RectDemo *>(poly.get())->drawRectOnly(ScreenEyeBaseL.get());
                    break;
                case 5:
                    dynamic_cast<FogObjDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 10:
                    dynamic_cast<CircleDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 6:
                    dynamic_cast<SphereDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 13:
                    dynamic_cast<ConeDemo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 23:
                    dynamic_cast<Bezier33Edge4 *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get(), AxisTiltPtr);
                    break;
                case 8:
                    dynamic_cast<ImgRect *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 20:
                    dynamic_cast<EquationTwo *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 21:
                    dynamic_cast<EquationTwo4 *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 24:
                    dynamic_cast<EquationThree9 *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 25:
                    dynamic_cast<EquationThree *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
                case 22:
                    dynamic_cast<Bezier33Edge4Mirror *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get(), AxisTiltPtr);
                    break;
                case 26:
                    dynamic_cast<Bezier3Img *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get(), AxisTiltPtr);
                    break;
                case 9:
                    dynamic_cast<Bezier22Edge3 *>(poly.get())->Draw_Tick(ScreenEyeBaseL.get());
                    break;
//                default:
//                    break;

            }

            //cout << "Thread " << omp_get_thread_num() << " processing " << endl;
        }

    }

    if(colorBarShow)colorBand();


}

void polygonCollisionInStep(char _direction){

    for (unique_ptr<PolygonBase> & i : polygonAll) {
        if (i->type_ == 4) {
            freshRectCollisionClose(dynamic_cast<RectDemo *>(i.get()), StandSquarePtr, _direction,
                                    goStep);
        } else if (i->type_ == 3) {
            freshTriaCollisionClose(dynamic_cast<TriangleDemo *>(i.get()), StandSquarePtr,
                                    _direction, goStep);
        }
    }

}
void firstStart(){
    println("显示初始化");
    //screenMoveXYZ(ScreenEyeBaseL_ptr, 'w', 0.0f); // a 代表前移
    //rectMoveXYZSelf(StandSquarePtr, 'w', 0.0f);

//    blueI = rand()%256; // 初始颜色随机
//    greenI = rand()%256;
//    redI = rand()%256;
    class std::random_device rd;  // 获取一个随机数，作为种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister算法生成随机数

    // 定义一个均匀分布的范围
    class std::uniform_int_distribution<> distr(0, 255);
    blueI = distr(gen);
    greenI = distr(gen);
    redI = distr(gen);


    if(runningMode==mode._leftView) { // 左视机位
        axisMoveXYZ(AxisTiltPtr, 'd', 800.0f);
        //freshPolygonByAxis( 'd'); // 移动了 才刷新
        axisMoveXYZ(AxisTiltPtr, 'e', 500.0f);
        //freshPolygonByAxis( 'e'); // 移动了 才刷新
        axisMoveXYZ(AxisTiltPtr, 's', 500.0f);
        freshPolygonByAxis( 's'); // 移动了 才刷新

    }else if(runningMode==mode._screenGo) {
        // 自由机位
        screenMoveXYZ(ScreenEyeBaseL.get(), 'a', 800.0f); // d 代表后移
        //freshPolygonAfterScreenGo();
        screenMoveXYZ(ScreenEyeBaseL.get(), 'q', 500.0f); // d 代表后移
        //freshPolygonAfterScreenGo();
        screenMoveXYZ(ScreenEyeBaseL.get(), 'w', 500.0f); // d 代表后移
        freshPolygonAfterScreenGo();

    }

    println("显示初始化完成");
}
void freshPolygonAfterScreenGo(){

    ScreenEyeBaseL->freshInfo(); // 刷新 屏幕信息
    freshTBLRXY_axis_Go(AxisTiltPtr, ParallelAxisPtr, ScreenEyeBaseL.get()); // 刷新坐标显示位置

    for (auto & i : polygonAll) {
        switch (i->type_) {
            case 4:
                freshTBLRXY_Go(dynamic_cast<RectDemo *>(i.get()), ScreenEyeBaseL.get());
                break;
            case 3:
                fresh2S2M2L_XY_Go(dynamic_cast<TriangleDemo *>(i.get()), ScreenEyeBaseL.get());
                break;
            case 1:
                freshTBLRXY_SelfL(dynamic_cast<RectDemo *>(i.get()), ScreenEyeBaseL.get());
                break;
            case 5:
                reinterpret_cast<FogObjDemo*>(i.get())->Draw_Tick(ScreenEyeBaseL.get());
                break;
            case 10:
                fresh_oTBLRXY_Go(dynamic_cast<CircleDemo *>(i.get()) , ScreenEyeBaseL.get());
                break;
            case 6:
                fresh_oTBLRXYNF_Go(dynamic_cast<SphereDemo *>(i.get()) , ScreenEyeBaseL.get());
                break;
            case 13:
                fresh_oTBLRDXY_Go(dynamic_cast<ConeDemo*>(i.get()), ScreenEyeBaseL.get());
                break;
            case 23:
                freshBezier334_P_Grid_XY_Go(dynamic_cast<Bezier33Edge4*>(i.get()), ScreenEyeBaseL.get());
                break;
            case 8:
                freshImg_2S2M2L_XY(dynamic_cast<ImgRect*>(i.get()), ScreenEyeBaseL.get());
                break;
            case 20:
                fresh_EquationBox_Go(dynamic_cast<EquationTwo*>(i.get()), ScreenEyeBaseL.get());
                break;
            case 21:
                fresh_Equation4Box_Go(dynamic_cast<EquationTwo4*>(i.get()), ScreenEyeBaseL.get());
                break;
            case 24:
                fresh_Equation9Box_Go(dynamic_cast<EquationThree9*>(i.get()), ScreenEyeBaseL.get());
                break;
            case 25:
                fresh_Equation3Box_Go(dynamic_cast<EquationThree*>(i.get()), ScreenEyeBaseL.get());
                break;
            case 22:
                bezier334Mirror_P_Grid_XY_Go(dynamic_cast<Bezier33Edge4Mirror *>(i.get()), ScreenEyeBaseL.get());
                break;
            case 26:
                bezier3Img_P_Grid_XY_Go(dynamic_cast<Bezier3Img *>(i.get()), ScreenEyeBaseL.get());
                break;
            case 9:
                freshBezier223_P_Grid_XY_Go(dynamic_cast<Bezier22Edge3 *>(i.get()), ScreenEyeBaseL.get());
            default:
                break;
        }

    }
}
void freshPolygonByAxis(char key){
    freshTBLRXY_axis_Go(AxisTiltPtr, ParallelAxisPtr, ScreenEyeBaseL.get());

    for (auto & i : polygonAll) {
        switch (i->type_) {
            case 4:
                freshTBLRXY_by_axis_Go(dynamic_cast<RectDemo *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 3:
                fresh2S2M2L_XY_by_axis_Go(dynamic_cast<TriangleDemo *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 1:
                freshTBLRXY_SelfL(dynamic_cast<RectDemo *>(i.get()), ScreenEyeBaseL.get());
                break;
            case 5:
                freshFogObj_XY_by_axis_L(dynamic_cast<FogObjDemo *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get(), key);
                break;
            case 10:
                freshCircle_by_axis_go(dynamic_cast<CircleDemo *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 6:
                freshSphere_by_axis_go(dynamic_cast<SphereDemo *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 13:
                freshCone_by_axis_go(dynamic_cast<ConeDemo *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 23:
                freshBezier334_by_axis_go(dynamic_cast<Bezier33Edge4 *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 8:
                freshImg_2S2M2L_XY_by_axis(dynamic_cast<ImgRect *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 20:
                freshEquationBox_by_axis_go(dynamic_cast<EquationTwo *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 21:
                freshEquation4Box_by_axis_go(dynamic_cast<EquationTwo4*>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 24:
                freshEquation9Box_by_axis_go(dynamic_cast<EquationThree9*>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 25:
                freshEquation3Box_by_axis_go(dynamic_cast<EquationThree *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 28:
                freshGammaBox_by_axis_go(dynamic_cast<GammaComplex *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 22:
                freshBezier334Mirror_by_axis_go(dynamic_cast<Bezier33Edge4Mirror *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 26:
                freshBezier3Img_by_axis_go(dynamic_cast<Bezier3Img *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
                break;
            case 9:
                freshBezier223_by_axis_go(dynamic_cast<Bezier22Edge3 *>(i.get()), AxisTiltPtr, ScreenEyeBaseL.get());
            default:
                break;
        }

    }

}
void colorBand(){
    float x1=colorBarLeft;

    BGR3f colorNow{};
    for(int i=0x000000;i<=0x0000FF;i+=0x000001) {
            // xl=0 xr=255
            // yt=windowHeight - (colorBarHeight) yb=windowHeight
            // colorl=0,0,0 colorr=1,0,0

        colorNow.setBGR(i,1);

    float _color[3] = {colorNow.r1,colorNow.g1,colorNow.b1};
//        PolygonBase::downLine(x1,windowHeight - (colorBarHeight),
//                          windowHeight,_color);
        ScreenDemo::downLine2ScreenBuffer(ScreenEyeBaseL.get(),static_cast<int>(x1),windowHeight - colorBarHeight,
                                          windowHeight,_color);

        x1++;
    }
    float _color[3] = {1.0f,1.0f,1.0f};
    for(int i=0;i<=widthI; ++i) { // 竖白线 往右宽
        ScreenDemo::downLine2ScreenBuffer(ScreenEyeBaseL.get(),redI+i,windowHeight - colorBarHeight,
                                          windowHeight,_color);
    }
    x1=colorBarLeft;

    for(int i=0x000000;i<=0x00FF00;i+=0x000100) {
        colorNow.setBGR(i,1);

        _color[0] = colorNow.r1;_color[1] = colorNow.g1;_color[2] = colorNow.b1;
        ScreenDemo::downLine2ScreenBuffer(ScreenEyeBaseL.get(),(int)x1,windowHeight - (colorBarHeight * 2),
                                          windowHeight - colorBarHeight,_color);
        x1++;
    }
    _color[0] = 1.f;_color[1] = 1.f;_color[2] = 1.f;
    for(int i=0;i<=widthI; ++i){ // 竖白线 往右宽
        ScreenDemo::downLine2ScreenBuffer(ScreenEyeBaseL.get(),greenI+i,windowHeight - (colorBarHeight * 2),
                                          windowHeight - colorBarHeight,_color);
    }

    x1=colorBarLeft;
    for(int i=0x000000;i<=0xFF0000;i+=0x010000){

        colorNow.setBGR(i,1);

        _color[0] = colorNow.r1;_color[1] = colorNow.g1;_color[2] = colorNow.b1;
        ScreenDemo::downLine2ScreenBuffer(ScreenEyeBaseL.get(),(int)x1,windowHeight - (colorBarHeight * 3),
                                          windowHeight - (colorBarHeight * 2),_color);
        x1++;
    }
    _color[0] = 1.f;_color[1] = 1.f;_color[2] = 1.f;
    for(int i=0;i<=widthI; ++i){ // 竖白线 往右宽
        ScreenDemo::downLine2ScreenBuffer(ScreenEyeBaseL.get(),blueI+i,windowHeight - (colorBarHeight * 3),
                                          windowHeight - (colorBarHeight * 2),_color);
    }

    _color[0]=(float)redI/255.f;_color[1]=(float)greenI/255.f;_color[2]=(float)blueI/255.f;
    for(int _x=255-30;_x<=255; ++_x){
        ScreenDemo::downLine2ScreenBuffer(ScreenEyeBaseL.get(),_x,windowHeight-(colorBarHeight*3)-30,
                                          windowHeight-(colorBarHeight*3),_color);
    }

}

void loadImgByFog(vector<unique_ptr<PolygonBase>>* polygonAll_ptr, string filename,const glm::vec3& _pos){
    Matrix2D<glm::vec3> imgClouds;
    PolygonBase::loadImgRGB01(filename,imgClouds);


//    cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR); // 从文件读取RGB图像
//    if (img.empty()) {
//        std::cerr << "无法读取图像 " << filename << std::endl;
//        return;
//    }
//
    glm::vec3 initPos3D = {0.0f, 0.0f, 0.0f}; // 起始位置
    float PosX = 0,PosY = 0;
    FogObjDemo* FogObj001 = fogObjInit(polygonAll_ptr,false);

    for(int outter=0; outter < imgClouds.outterMax; outter+=1){
        for(int inner=0; inner < imgClouds.innerMax; inner+=1){
            PosX = static_cast<float>(inner)+_pos.x;//*2.0f;
            PosY = static_cast<float>(outter)+_pos.y;//*2.0f;
            initPos3D.x = PosX;
            initPos3D.y = PosY;
            initPos3D.z = _pos.z;

//            cv::Vec3b color = img.at<cv::Vec3b>(i,j); // 读取像素点的BGR值
            glm::vec3 colorNow = imgClouds(outter, inner); // 读取像素点的坐标
            // int b = static_cast<int>(colorNow[2]);
            // int g = static_cast<int>(colorNow[1]);
            // int r = static_cast<int>(colorNow[0]);
            // // 处理像素点的BGR值
            // int colorNow_ = (b<<16) + (g<<8) + r; // 转换为RGB值


            unique_ptr<FogDemo> FogPointCurr = make_unique<FogDemo>(initPos3D,colorNow); // 当下雾点
            FogObj001->fogPoints.push_back(std::move(FogPointCurr)); // 添加到雾点列表
            //if(i%100==0 && j%100==0)cout << "i:" << i << "/" << img.rows << " j:" << j << "/" << img.cols<< endl;
        }
    }
    FogObj001->centerSet(); // 计算中心点
}