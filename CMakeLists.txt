cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(PolygonDisplay)

# 启用OpenMP (针对MSVC和其他编译器)
if(MSVC)
    # MSVC 使用/openmp 选项
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /openmp")
else()
    # 其他编译器(gcc,clang)使用-fopenmp
    find_package(OpenMP REQUIRED)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(PolygonDisplay PUBLIC OpenMP::OpenMP_CXX)
    endif()
endif()

set(PARENT_CWD E:/ClionProjects)


include_directories(
        ${PARENT_CWD}/OpenCV/build/include
        ${PARENT_CWD}/of_v0.12.1_vs_64_release/libs/glm/include/glm
        ${PARENT_CWD}/eigen-3.4.0
)
# 添加GLFW子模块
add_subdirectory(deps/glfw)

# 查找OpenGL库
find_package(OpenGL REQUIRED)

# 创建可执行文件
add_executable(PolygonDisplay
        src/main.cpp

#        polygonClass/RectDemo.h
        polygonClass/RectDemo.cpp
#        polygonClass/TriangleDemo.h
        polygonClass/TriangleDemo.cpp
#        polygonClass/AxisDemo.h
        polygonClass/AxisDemo.cpp
#        polygonClass/FogDemo.h
        polygonClass/FogDemo.cpp
#        polygonClass/CircleDemo.h
        polygonClass/CircleDemo.cpp
#        polygonClass/source/ScreenDemo.h
        polygonClass/source/ScreenDemo.cpp
#        polygonClass/source/PolygonBase.h
        polygonClass/source/PolygonBase.cpp
#        polygonClass/SphereDemo.h
        polygonClass/SphereDemo.cpp
#        polygonClass/ConeDemo.h
        polygonClass/ConeDemo.cpp
#        polygonClass/BicubicBezier.h
        polygonClass/Bezier22Edge3.cpp
        polygonClass/Bezier33Edge4.cpp
        polygonClass/Bezier33Edge4Mirror.cpp
        polygonClass/Bezier3Img.cpp
#        polygonClass/ImgRect.h
        polygonClass/ImgRect.cpp
#        polygonClass/equation/EquationTwo.h
        polygonClass/equation/EquationTwo.cpp
#        polygonClass/equation/EquationTwo4.h
        polygonClass/equation/EquationTwo4.cpp
#        polygonClass/equation/EquationThree.h
        polygonClass/equation/EquationThree.cpp
#        polygonClass/equation/EquationThree9.h
        polygonClass/equation/EquationThree9.cpp
#        polygonClass/equation/GammaComplex.h
        polygonClass/equation/GammaComplex.cpp


#        src/GlobalSettings.h


#        polygon_init/arrow_1.h
#        polygon_init/axis_1.h
#        polygon_init/fogPoint_1.h
#        polygon_init/rect_1.h
#        polygon_init/triangle_1.h
#        polygon_init/circle_1.h
#        polygon_init/sphere_1.h
#        polygon_init/cone_1.h
#        polygon_init/becubicBezier_1.h
#        polygon_init/imgRect_1.h
#        polygon_init/screen_1.h
#        polygon_init/equation/equation2_1.h
#        polygon_init/equation/equation2_4_1.h
#        polygon_init/equation/equation3_1.h
#        polygon_init/equation/equation3_9_1.h
#        polygon_init/equation/gamma_1.h

        #polygonClass/BezierCurveLength.cpp
)

# 链接库  OpenCV 库

# 正确示例：根据构建模式选择带d/不带d的库
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(PolygonDisplay
            PRIVATE
            glfw
            ${OPENGL_gl_LIBRARY}
            ${PARENT_CWD}/OpenCV/build/x64/vc16/lib/opencv_world4100d.lib
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(PolygonDisplay
            PRIVATE
            glfw
            ${OPENGL_gl_LIBRARY}
            ${PARENT_CWD}/OpenCV/build/x64/vc16/lib/opencv_world4100.lib
    )
endif()
# 包含头文件
target_include_directories(PolygonDisplay
    PRIVATE
    deps/glfw/include
)

# Windows特殊配置
if(WIN32)
    # 设置入口点为main函数
    target_link_options(PolygonDisplay PRIVATE "/ENTRY:mainCRTStartup")
    
    # 复制GLFW DLL到输出目录
    add_custom_command(TARGET PolygonDisplay POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            I:/PolygonDisplay/deps/glfw-3.4.bin.WIN64/lib-vc2022/glfw3.dll

        $<TARGET_FILE_DIR:PolygonDisplay>
    )
endif()

#set(GLAD D:/ClionProjects/PolygonDisplay/deps/glfw/deps/glad.c)
#add_executable(simple src/simple.cpp ${GLAD})
# 使用导入目标
#target_link_libraries(simple PRIVATE OpenGL::GL)


#include_directories(
#        F:/rarely_document/EasyX_Help/extract/include
#)
#link_directories(
#        F:/rarely_document/EasyX_Help/extract/lib/VC2015/x64
#)



# 添加 OpenCV 的包含目录
include_directories(
        ${PARENT_CWD}/OpenCV/build/include
)
# 添加 OpenCV 的库目录
link_directories(
        ${PARENT_CWD}/OpenCV/build/x64/vc16/lib
)
# 添加你的源文件
#add_executable(RectangleDisplay readImg/ReadPng.cpp)


# 检查构建类型
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "当前构建模式: Debug")
    # 可添加 Debug 模式专属配置，如启用   |调试符号|关闭优化|
    # o0 无优化 最适合调试 o1 轻度优化 基本可以调试 o2 o3高度优化 难以调试
    add_compile_options(-g -O0)
    # 复制 DLL 文件到构建目录 VVV
    add_custom_command(
            TARGET PolygonDisplay POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PARENT_CWD}/OpenCV/build/x64/vc16/bin/opencv_world4100d.dll
            #        C:/Windows/System32/opengl32.dll
            $<TARGET_FILE_DIR:PolygonDisplay>
    )

elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "当前构建模式: Release")
    # 可添加 Release 模式专属配置，如   |开启优化|关闭调试符号|
    # o0 o1 o2 o3 os大小优先 oz极致压缩
    add_compile_options(-O3 -DNDEBUG)
    # 复制 DLL 文件到构建目录 VVV
    add_custom_command(
            TARGET PolygonDisplay POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${PARENT_CWD}/OpenCV/build/x64/vc16/bin/opencv_world4100.dll
            #        C:/Windows/System32/opengl32.dll
            $<TARGET_FILE_DIR:PolygonDisplay>
    )
#elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
#    message(STATUS "当前构建模式: RelWithDebInfo (Release with Debug Info)")
#    # 启用优化，同时保留调试符号（适合发布但需要调试能力）
#    add_compile_options(-g -O2 -DNDEBUG)
#    # RelWithDebInfo 通常使用 Release 版本的 DLL（除非你有专门的带调试信息的 DLL）
#    add_custom_command(
#            TARGET PolygonDisplay POST_BUILD
#            COMMAND ${CMAKE_COMMAND} -E copy
#            ${PARENT_CWD}/OpenCV/build/x64/vc16/bin/opencv_world4100.dll
#            $<TARGET_FILE_DIR:PolygonDisplay>
#    )
else()
    # 处理其他模式（如 RelWithDebInfo、MinSizeRel）
    message(WARNING "未指定构建模式，默认使用 Release")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif()


#对于[av²+bv+c]u² + [dv²+ev+f]u + [gv²+hv+i] = 0
#实际上系数是四层分数式每层多项,由于没有未知量,用一个字母替代
#能否转换为ax⁴+bx³+x²+x+c=0的形式?(需要写为c++函数来表示)
#
#能否将ax⁴+bx³+x²+x+c=0像求根公式和跟判别式那样,写出系数对应的解?(需要写为c++函数来表示)
#
