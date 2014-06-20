#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

/* int main()
{
    cv::Mat image = cv::imread("D:\\binary.bmp");

    cv::namedWindow("Origin Image");
    cv::imshow("Origin Image", image);


    cv::Mat eroded;    //target image eroded
//    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
//    cv::Mat element(7, 7, CV_8U, cv::Scalar(1));
//    cv::erode(image, eroded, element);
//    cv::erode(image, eroded, cv::Mat());
    cv::erode(image, eroded, cv::Mat(), cv::Point(-1, -1), 3);
    cv::namedWindow("Eroded Image");
    cv::imshow("Eroded Image", eroded);

//    cv::Mat dilated;    // target image dilated
//    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(15, 15));
////    cv::dilate(image, dilated, cv::Mat());
//    cv::dilate(image, dilated, element);
//    cv::namedWindow("Dilated Image");
//    cv::imshow("Dilated Image", dilated);

    cv::waitKey(0);

    return 1;
} */

//-----------------------------------【命名空间声明部分】---------------------------------------
//		描述：包含程序所使用的命名空间
//-----------------------------------------------------------------------------------------------
using namespace std;
using namespace cv;


//-----------------------------------【全局变量声明部分】--------------------------------------
//		描述：全局变量声明
//-----------------------------------------------------------------------------------------------
Mat g_srcImage, g_dstImage;//原始图和效果图
int g_nTrackbarNumer = 0;//0表示腐蚀erode, 1表示膨胀dilate
int g_nStructElementSize = 3; //结构元素(内核矩阵)的尺寸


//-----------------------------------【全局函数声明部分】--------------------------------------
//		描述：全局函数声明
//-----------------------------------------------------------------------------------------------
void Process();//膨胀和腐蚀的处理函数
void on_TrackbarNumChange(int, void *);//回调函数
void on_ElementSizeChange(int, void *);//回调函数


//-----------------------------------【main( )函数】--------------------------------------------
//		描述：控制台应用程序的入口函数，我们的程序从这里开始
//-----------------------------------------------------------------------------------------------
int main( )
{
    //改变console字体颜色
    system("color 5E");

    //载入原图
    g_srcImage = imread("D:\\binary.bmp");
    if( !g_srcImage.data ) { printf("Oh，no，读取srcImage错误~！ \n"); return false; }

    //显示原始图
    namedWindow("srcImage");
    imshow("srcImage", g_srcImage);

    //进行初次腐蚀操作并显示效果图
    namedWindow("result");
    //获取自定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));
    erode(g_srcImage, g_dstImage, element);
    imshow("result", g_dstImage);

    //创建轨迹条
    createTrackbar("Erode/Dilate", "result", &g_nTrackbarNumer, 1, on_TrackbarNumChange);
    createTrackbar("Kernel Size", "result", &g_nStructElementSize, 21, on_ElementSizeChange);

    //输出一些帮助信息
    cout<<endl<<"\t running successfully, please silde the silider to view the result\n\n"
       <<"\tpress key 'q' to quit~!\n"
        <<"\n\n\t\t\t\t by cgf";

    //轮询获取按键信息，若下q键，程序退出
    while(char(waitKey(1)) != 'q') {}

    return 0;
}

//-----------------------------【Process( )函数】------------------------------------
//		描述：进行自定义的腐蚀和膨胀操作
//-----------------------------------------------------------------------------------------
void Process()
{
    //获取自定义核
    Mat element = getStructuringElement(MORPH_RECT, Size(2*g_nStructElementSize+1, 2*g_nStructElementSize+1),Point( g_nStructElementSize, g_nStructElementSize ));

    //进行腐蚀或膨胀操作
    if(g_nTrackbarNumer == 0) {
        erode(g_srcImage, g_dstImage, element);
    }
    else {
        dilate(g_srcImage, g_dstImage, element);
    }

    //显示效果图
    imshow("result", g_dstImage);
}


//-----------------------------【on_TrackbarNumChange( )函数】------------------------------------
//		描述：腐蚀和膨胀之间切换开关的回调函数
//-----------------------------------------------------------------------------------------------------
void on_TrackbarNumChange(int, void *)
{
    //腐蚀和膨胀之间效果已经切换，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
    Process();
}


//-----------------------------【on_ElementSizeChange( )函数】-------------------------------------
//		描述：腐蚀和膨胀操作内核改变时的回调函数
//-----------------------------------------------------------------------------------------------------
void on_ElementSizeChange(int, void *)
{
    //内核尺寸已改变，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
    Process();
}
