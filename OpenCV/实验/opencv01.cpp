#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

//二值化
void Binarization(int t, void* img)
{
	Mat src = *(Mat*)img;
	Mat dst;
	threshold(src, dst, t, 255, 0);

	imshow("2.二值化", dst);
}


//对数变换
void Log(int c, void* img) {
	Mat src = *(Mat*)img;
	Mat dst;

	//创建映射表
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	for (int i = 0; i < 256; ++i)
		p[i] = saturate_cast<uchar>(log2(1 + i / 255.0) * 255.0 * c / 10.0);

	LUT(src, lookUpTable, dst);
	imshow("3.对数变换", dst);
}


//伽马变换
void Gamma(int gamma, void* img){
	Mat src = *(Mat*)img;
	Mat dst;
	
	//创建映射表
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	for (int i = 0; i < 256; ++i)
		p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma/10.0) * 255.0);

	LUT(src, lookUpTable, dst);
	imshow("4.伽马变换", dst);
}

int main()
{
	// 1.读取图像，以灰度模式打开
	string image_path = samples::findFile("lena.jpg");
	Mat img = imread(image_path, IMREAD_GRAYSCALE);
	if (img.empty())
	{
		cout << "Could not read the image: " << image_path << endl;
		return 1;
	}
	imshow("1.读取图像", img);


	// 2.二值化
	int threshold=128;
	int threshold_max = 255;
	namedWindow("2.二值化", WINDOW_AUTOSIZE);
	createTrackbar("阈值", "2.二值化", &threshold, threshold_max, Binarization, &img);
	Binarization(threshold, &img);


	// 3.对数变换
	int c = 10;
	int c_max = 40;
	namedWindow("3.对数变换", WINDOW_AUTOSIZE);
	createTrackbar("c/10", "3.对数变换", &c, c_max, Log, &img);
	Log(c, &img);


	// 4.伽马变换
	int gamma = 10;
	int gamma_max = 100;
	namedWindow("4.伽马变换", WINDOW_AUTOSIZE);
	createTrackbar("γ/10", "4.伽马变换", &gamma, gamma_max, Gamma, &img);
	Gamma(gamma, &img);


	// 5.彩色图像的补色变换
	Mat color_img = imread(image_path, IMREAD_COLOR);
	Mat revers_img;
	if (color_img.empty())
	{
		cout << "Could not read the image: " << image_path << endl;
		return 1;
	}
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	for (int i = 0; i < 256; ++i)
		p[i] = 255 - i;
	LUT(color_img, lookUpTable, revers_img);
	imshow("5.1 彩色图像", color_img);
	imshow("5.2 彩色图像的补色变换", revers_img);
	
	
	
	int k = waitKey(0);
	return 0;
}