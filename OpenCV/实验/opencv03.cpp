#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//均值模板
void BoxFilter(int pos, void* img)
{
	Mat src = *(Mat*)(img);
	Mat dst;
	int size = 1 + pos * 2;
	Mat kernel = Mat::ones(size, size, CV_32F) / (float)(size * size);
	filter2D(src, dst, -1, kernel);
	imshow("1.均值滤波", dst);
}

//高斯模板
void GaussianFilter(int pos, void* img)
{
	Mat src = *(Mat*)(img);
	Mat dst;
	int size = 1 + pos * 2;
	GaussianBlur(src, dst, Size(size, size), 0, 0);
	imshow("2.高斯滤波", dst);
}

//高提升滤波
void EnhanceFilter(int pos, void* img)
{
	Mat src = *(Mat*)(img);
	Mat blur, mask, dst;
	GaussianBlur(src, blur, Size(3, 3), 0, 0);
	mask = src - blur;
	addWeighted(src, 1, mask, pos, 0.0, dst);
	imshow("4.高提升滤波", dst);
}

//均值模板+彩色图像
void BoxFilter_COLOR(int pos, void* img)
{
	Mat src = *(Mat*)(img);
	Mat dst;
	int size = 1 + pos * 2;
	Mat kernel = Mat::ones(size, size, CV_32F) / (float)(size * size);
	Mat planes[3];
	split(src, planes);
	filter2D(planes[0], planes[0], -1, kernel);
	filter2D(planes[1], planes[1], -1, kernel);
	filter2D(planes[2], planes[2], -1, kernel);
	merge(planes, 3, dst);
	imshow("5.均值滤波+彩色图像", dst);
}

//高斯模板+彩色图像
void GaussianFilter_COLOR(int pos, void* img)
{
	Mat src = *(Mat*)(img);
	Mat dst;
	int size = 1 + pos * 2;
	Mat planes[3];
	split(src, planes);
	GaussianBlur(planes[0], planes[0], Size(size, size), 3, 3);
	GaussianBlur(planes[1], planes[1], Size(size, size), 3, 3);
	GaussianBlur(planes[2], planes[2], Size(size, size), 3, 3);
	merge(planes, 3, dst);
	imshow("6.高斯滤波+彩色图像", dst);
}


int main()
{
	// 读入图像
	string image_path = samples::findFile("lena.jpg");
	Mat img = imread(image_path, IMREAD_GRAYSCALE);
	if (img.empty())
	{
		cout << "Could not read the image: " << image_path << endl;
		return 1;
	}
	imshow("原图像", img);
	Mat img_color = imread(image_path, IMREAD_COLOR);
	

	// 1.均值模板平滑 + 灰度图像
	int pos1 = 0, max_pos1 = 4;
	namedWindow("1.均值滤波", WINDOW_AUTOSIZE);
	createTrackbar("size=1+2*", "1.均值滤波", &pos1, max_pos1, BoxFilter, &img);
	BoxFilter(pos1, &img);
	

	// 2.高斯模板平滑 + 灰度图像
	int pos2 = 0, max_pos2 = 4;
	namedWindow("2.高斯滤波", WINDOW_AUTOSIZE);
	createTrackbar("size=1+2*", "2.高斯滤波", &pos2, max_pos2, GaussianFilter, &img);
	GaussianFilter(pos2, &img);
	

	// 3.Laplacian、Robert、Sobel模板锐化 + 灰度图像
	Mat Laplacian_dst;
	Mat Laplacian_kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
	filter2D(img, Laplacian_dst, CV_16S, Laplacian_kernel);
	Mat L;
	convertScaleAbs(Laplacian_dst, L);
	imshow("3-1 Laplacian滤波结果", L);
	addWeighted(img, 1, Laplacian_dst, -1, 0.0, Laplacian_dst, CV_16S);
	convertScaleAbs(Laplacian_dst, Laplacian_dst);
	imshow("3-1 Laplacian锐化结果", Laplacian_dst);
	
	{
		Mat mag, gx, gy;
		Mat robert_x_kernel = (Mat_<float>(2, 2) << -1, 0, 0, 1);
		Mat robert_y_kernel = (Mat_<float>(2, 2) << 0, -1, 1, 0);
		filter2D(img, gx, CV_16S, robert_x_kernel);
		filter2D(img, gy, CV_16S, robert_y_kernel);
		convertScaleAbs(gx, gx);
		convertScaleAbs(gy, gy);
		addWeighted(gx, 0.5, gy, 0.5, 0.0, mag);
		imshow("3-2 Robert滤波结果", mag);
		addWeighted(img, 1, mag, 1, 0.0, mag);
		imshow("3-2 Robert锐化结果", mag);
	}

	Mat mag, gx, gy;
	Mat sobel_x_kernel = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
	Mat sobel_y_kernel = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	filter2D(img, gx, CV_16S, sobel_x_kernel);
	filter2D(img, gy, CV_16S, sobel_y_kernel);
	convertScaleAbs(gx, gx);
	convertScaleAbs(gy, gy);
	addWeighted(gx, 0.5, gy, 0.5, 0.0, mag);
	imshow("3-3 Sobel滤波结果", mag);
	addWeighted(img, 1, mag, 1, 0.0, mag);
	imshow("3-3 Sobel锐化结果", mag);
	
	
	
	// 4.高提升滤波 + 灰度图像
	int pos4 = 4, max_pos4 = 10;
	namedWindow("4.高提升滤波", WINDOW_AUTOSIZE);
	createTrackbar("k", "4.高提升滤波", &pos4, max_pos4, EnhanceFilter, &img);
	EnhanceFilter(pos4, &img);
	

	// 5.均值模板平滑 + 彩色图像
	int pos5 = 0, max_pos5 = 4;
	namedWindow("5.均值滤波+彩色图像", WINDOW_AUTOSIZE);
	createTrackbar("size=1+2*", "5.均值滤波+彩色图像", &pos5, max_pos5, BoxFilter_COLOR, &img_color);
	BoxFilter_COLOR(pos5, &img_color);


	// 6.高斯模板平滑 + 彩色图像
	int pos6 = 0, max_pos6 = 4;
	namedWindow("6.高斯滤波+彩色图像", WINDOW_AUTOSIZE);
	createTrackbar("size=1+2*", "6.高斯滤波+彩色图像", &pos6, max_pos6, GaussianFilter_COLOR, &img_color);
	GaussianFilter_COLOR(pos6, &img_color);


	// 7.Laplacian、Robert、Sobel模板锐化 + 彩色图像
	imshow("彩色原图像", img_color);

	{
		Mat dst;
		Mat Laplacian_dst[3];
		Mat Laplacian_kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
		Mat planes[3];
		split(img_color, planes);
		for (int i = 0; i < 3; ++i) {
			filter2D(planes[i], Laplacian_dst[i], CV_16S, Laplacian_kernel);
			addWeighted(planes[i], 1, Laplacian_dst[i], -1, 0.0, Laplacian_dst[i], CV_16S);
			convertScaleAbs(Laplacian_dst[i], Laplacian_dst[i]);
		}
		merge(Laplacian_dst, 3, dst);
		imshow("7-1 Laplacian + 彩色图像", dst);
	}

	{
		Mat mag[3], gx[3], gy[3], dst;
		Mat robert_x_kernel = (Mat_<float>(2, 2) << -1, 0, 0, 1);
		Mat robert_y_kernel = (Mat_<float>(2, 2) << 0, -1, 1, 0);
		Mat planes[3];
		split(img_color, planes);
		for (int i = 0; i < 3; ++i) {
			filter2D(planes[i], gx[i], CV_16S, robert_x_kernel);
			filter2D(planes[i], gy[i], CV_16S, robert_y_kernel);
			convertScaleAbs(gx[i], gx[i]);
			convertScaleAbs(gy[i], gy[i]);
			addWeighted(gx[i], 0.5, gy[i], 0.5, 0.0, mag[i]);
			addWeighted(planes[i], 1, mag[i], 1, 0.0, mag[i]);
		}
		merge(mag, 3, dst);
		imshow("7-2 Robert + 彩色图像", dst);
	}

	{
		Mat mag[3], gx[3], gy[3], dst;
		Mat sobel_x_kernel = (Mat_<float>(3, 3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
		Mat sobel_y_kernel = (Mat_<float>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);

		Mat planes[3];
		split(img_color, planes);
		for (int i = 0; i < 3; ++i) {
			filter2D(planes[i], gx[i], CV_16S, sobel_x_kernel);
			filter2D(planes[i], gy[i], CV_16S, sobel_y_kernel);
			convertScaleAbs(gx[i], gx[i]);
			convertScaleAbs(gy[i], gy[i]);
			addWeighted(gx[i], 0.5, gy[i], 0.5, 0.0, mag[i]);
			addWeighted(planes[i], 1, mag[i], 1, 0.0, mag[i]);
		}
		merge(mag, 3, dst);
		imshow("7-3 Sobel + 彩色图像", dst);
	}
	


	waitKey();
	return 0;
}

