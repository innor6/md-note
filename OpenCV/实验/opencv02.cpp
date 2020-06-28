#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;



// 绘制直方图的函数
void drawHistgram(Mat& img, string title) {
	//统计直方图信息
	vector<int> hist(256, 0);
	MatIterator_<uchar> it, end;
	for (it = img.begin<uchar>(), end = img.end<uchar>(); it != end; ++it)
		hist[*it] = hist[*it] + 1;

	//绘制直方图
	int hist_w = 512, hist_h = 400;				//图的宽、高
	int bin_w = cvRound((double)hist_w / 256); 	//图中每个桶的宽度
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	for (int i = 0; i < 256; i++)
	{
		line(histImage,
			Point(bin_w * (i), hist_h),
			Point(bin_w * (i), hist_h - cvRound(hist[i])),
			Scalar(255, 255, 255), bin_w, 8, 0);
	}
	imshow(title, histImage);
}


int main()
{
	// 1.计算直方图
	string image_path = samples::findFile("lena.jpg");
	Mat img = imread(image_path, IMREAD_GRAYSCALE);
	if (img.empty())
	{
		cout << "Could not read the image: " << image_path << endl;
		return 1;
	}
	imshow("原始图像", img);
	drawHistgram(img,"原始直方图");


	
	// 2.灰度图像的直方图均衡
	// 统计直方图信息
	vector<int> hist(256, 0);
	MatIterator_<uchar> it, end;
	for (it = img.begin<uchar>(), end = img.end<uchar>(); it != end; ++it)
		hist[*it] = hist[*it] + 1;
	// 累积分布函数
	vector<int> cdf(256, 0);
	cdf[0] = hist[0];
	for (int i = 1; i != 256; ++i) {
		cdf[i] = cdf[i - 1] + hist[i];
	}
	// 归一化
	normalize(cdf, cdf, 0, 255, NORM_MINMAX, -1, Mat());
	// 应用变换
	Mat equlized;
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	for (int i = 0; i < 256; ++i)
		p[i] = saturate_cast<uchar>(cdf[i]);
	LUT(img, lookUpTable, equlized);
	imshow("直方图均衡化过的图像", equlized);
	drawHistgram(equlized, "均衡后的直方图");


	// 3.彩色图像的直方图均衡
	Mat img_bgr = imread(image_path, IMREAD_COLOR);
	imshow("彩色原图", img_bgr);
	// 转换为HLS
	Mat img_hls;
	cvtColor(img_bgr, img_hls, COLOR_BGR2HLS);
	vector<Mat> HLS;
	split(img_hls, HLS);
	// 对亮度通道进行直方图均衡
	drawHistgram(HLS[1], "均衡前亮度直方图");
	equalizeHist(HLS[1], HLS[1]);
	drawHistgram(HLS[1], "均衡后亮度直方图");
	// 转换回BGR输出
	merge(HLS, img_hls);
	cvtColor(img_hls, img_bgr, COLOR_HLS2BGR);
	imshow("均衡后的彩色图像", img_bgr);
	


	waitKey();
	return 0;
}

