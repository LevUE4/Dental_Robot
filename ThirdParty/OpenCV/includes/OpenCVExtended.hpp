#pragma once  

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <vector>

#define DLL_EXPORT __declspec(dllexport)    //shortens __declspec(dllexport) to DLL_EXPORT


struct FloatPoint2D {
    float x;
    float y;
};

#pragma warning( disable : 4190)

#ifdef __cplusplus      //if C++ is used convert it to C to prevent C++'s name mangling of method names
extern "C"
{
#endif
    FloatPoint2D    DLL_EXPORT findColor(cv::Mat, int p1, int p2, int p3, int p4, int p5, int p6);
    cv::Mat	        DLL_EXPORT getCircleArea(cv::Mat mat1, cv::Mat mat2);

#ifdef __cplusplus
}
#endif


#pragma warning( push ) 

#pragma once

