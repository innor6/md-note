#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//理想高通滤波器（参数d0为截止频率）
Mat IHPF(Mat src, float d0) {
	Mat filter(src.size(), CV_32FC1);
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			double d = sqrt(pow((i - src.rows / 2), 2) + pow((j - src.cols / 2), 2));
			if (d <= d0)
				filter.at<float>(i, j) = 0;
			else
				filter.at<float>(i, j) = 1;
		}
	}
	return filter;
}

//理想低通滤波器（参数d0为截止频率）
Mat ILPF(Mat src, float d0) {
	Mat filter(src.size(), CV_32FC1);
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			double d = sqrt(pow((i - src.rows / 2), 2) + pow((j - src.cols / 2), 2));
			if (d <= d0)
				filter.at<float>(i, j) = 1;
			else
				filter.at<float>(i, j) = 0;
		}
	}
	return filter;
}

//布特沃斯高通滤波器
Mat BHPF(Mat src, float d0) {
	double n = 2;	//阶数
	Mat filter(src.size(), CV_32FC1);
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			double d = sqrt(pow((i - src.rows / 2), 2) + pow((j - src.cols / 2), 2));
			filter.at<float>(i, j) = 1 / (1 + pow(d0 / d, 2 * n));
		}
	}
	return filter;
}

//布特沃斯低通滤波器
Mat BLPF(Mat src, float d0) {
	double n = 2;	//阶数
	Mat filter(src.size(), CV_32FC1);
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			double d = sqrt(pow((i - src.rows / 2), 2) + pow((j - src.cols / 2), 2));
			filter.at<float>(i, j) = 1 / (1 + pow(d / d0, 2 * n));
		}
	}
	return filter;
}


//将原点移动到图像中心
Mat Centerlize(Mat src) {
	Mat dst = src(Rect(0, 0, src.cols & -2, src.rows & -2));//裁切到奇数
	int cx = dst.cols / 2;
	int cy = dst.rows / 2;
	Mat q0(dst, Rect(0, 0, cx, cy));
	Mat q1(dst, Rect(cx, 0, cx, cy));
	Mat q2(dst, Rect(0, cy, cx, cy));
	Mat q3(dst, Rect(cx, cy, cx, cy));
	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);
	return dst;
}

void on_IHPF(int pos, void* usrdata)
{
	Mat* planes = (Mat*)usrdata;

	// 滤波
	Mat fileter = IHPF(planes[0], pos);
	Mat re, im, dst;
	multiply(planes[0], fileter, re);
	multiply(planes[1], fileter, im);
	Mat plane_F[] = { re, im };

	// idft
	Mat ifft;
	merge(plane_F, 2, ifft);
	idft(ifft, ifft);
	Mat plane_IF[2];
	split(ifft, plane_IF);
	magnitude(plane_IF[0], plane_IF[1], plane_IF[0]);
	normalize(plane_IF[0], plane_IF[0], 1, 0, NORM_MINMAX);
	imshow("2.a理想高通滤波的结果", plane_IF[0]);

	//显示谱图像
	magnitude(re, im, re);
	Mat magI = re;
	magI += Scalar::all(1);	//转换为对数坐标系
	log(magI, magI);
	normalize(magI, magI, 0, 1, NORM_MINMAX); //归一化
	imshow("2.a理想高通滤波器", magI);
}

void on_ILPF(int pos, void* usrdata)
{
	Mat* planes = (Mat*)usrdata;

	// 滤波
	Mat fileter = ILPF(planes[0], pos);
	Mat re, im, dst;
	multiply(planes[0], fileter, re);
	multiply(planes[1], fileter, im);
	Mat plane_F[] = { re, im };
	
	// idft
	Mat ifft;
	merge(plane_F, 2, ifft);
	idft(ifft, ifft);
	Mat plane_IF[2];
	split(ifft, plane_IF);
	magnitude(plane_IF[0], plane_IF[1], plane_IF[0]);
	normalize(plane_IF[0], plane_IF[0], 1, 0, NORM_MINMAX);
	imshow("2.b理想低通滤波的结果", plane_IF[0]);
	
	//显示谱图像
	magnitude(re, im, re);
	Mat magI = re;
	magI += Scalar::all(1);	//转换为对数坐标系
	log(magI, magI);
	normalize(magI, magI, 0, 1, NORM_MINMAX); //归一化
	imshow("2.b理想低通滤波器", magI);
}

void on_BHPF(int pos, void* usrdata) {
	Mat* planes = (Mat*)usrdata;

	// 滤波
	Mat fileter = BHPF(planes[0], pos);
	Mat re, im, dst;
	multiply(planes[0], fileter, re);
	multiply(planes[1], fileter, im);
	Mat plane_F[] = { re, im };

	// idft
	Mat ifft;
	merge(plane_F, 2, ifft);
	idft(ifft, ifft);
	Mat plane_IF[2];
	split(ifft, plane_IF);
	magnitude(plane_IF[0], plane_IF[1], plane_IF[0]);
	normalize(plane_IF[0], plane_IF[0], 1, 0, NORM_MINMAX);
	imshow("3.a布特沃斯高通滤波的结果", plane_IF[0]);

	//显示谱图像
	magnitude(re, im, re);
	Mat magI = re;
	magI += Scalar::all(1);	//转换为对数坐标系
	log(magI, magI);
	normalize(magI, magI, 0, 1, NORM_MINMAX); //归一化
	imshow("3.a布特沃斯高通滤波器", magI);
}


void on_BLPF(int pos, void* usrdata) {
	Mat* planes = (Mat*)usrdata;

	// 滤波
	Mat fileter = BLPF(planes[0], pos);
	Mat re, im, dst;
	multiply(planes[0], fileter, re);
	multiply(planes[1], fileter, im);
	Mat plane_F[] = { re, im };

	// idft
	Mat ifft;
	merge(plane_F, 2, ifft);
	idft(ifft, ifft);
	Mat plane_IF[2];
	split(ifft, plane_IF);
	magnitude(plane_IF[0], plane_IF[1], plane_IF[0]);
	normalize(plane_IF[0], plane_IF[0], 1, 0, NORM_MINMAX);
	imshow("3.b布特沃斯低通滤波的结果", plane_IF[0]);

	//显示谱图像
	magnitude(re, im, re);
	Mat magI = re;
	magI += Scalar::all(1);	//转换为对数坐标系
	log(magI, magI);
	normalize(magI, magI, 0, 1, NORM_MINMAX); //归一化
	imshow("3.b布特沃斯低通滤波器", magI);
}


int main()
{
	// 读入图像
	string image_path = samples::findFile("lena.jpg");
	Mat I = imread(image_path, IMREAD_GRAYSCALE);
	if (I.empty())
	{
		cout << "Could not read the image: " << image_path << endl;
		return 1;
	}
	imshow("原始图像", I);

	
	/* 1.DFT和IDFT */
	// DFT
	Mat padded; 
	int m = getOptimalDFTSize(I.rows);
	int n = getOptimalDFTSize(I.cols);
	copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0)); //填充边界
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexI;
	merge(planes, 2, complexI);
	dft(complexI, complexI);
	split(complexI, planes); // 分离实部、虚部
	planes[0] = Centerlize(planes[0]); // 移动原点到中心
	planes[1] = Centerlize(planes[1]);

	//显示谱图像
	Mat re = planes[0].clone();
	Mat im = planes[1].clone();
	magnitude(re, im, re);
	Mat magI = re;
	magI += Scalar::all(1);	//转换为对数坐标系
	log(magI, magI);
	normalize(magI, magI, 0, 1, NORM_MINMAX);	//归一化
	imshow("1.谱图像", magI);

	// IDFT
	Mat ifft;
	idft(complexI, ifft, DFT_REAL_OUTPUT);
	normalize(ifft, ifft, 0, 1, NORM_MINMAX);
	imshow("1.IDFT", ifft);



	/* 2-1 理想高通滤波器 */
	namedWindow("2.a理想高通滤波器", WINDOW_AUTOSIZE);
	int d1 = 40;
	createTrackbar("截止频率", "2.a理想高通滤波器", &d1, 400, on_IHPF, planes);
	on_IHPF(40, planes);

	/* 2-2 理想低通滤波器 */
	namedWindow("2.b理想低通滤波器", WINDOW_AUTOSIZE);
	int d2 = 40;
	createTrackbar("截止频率", "2.b理想低通滤波器", &d2, 400, on_ILPF, planes);
	on_ILPF(40, planes);

	/* 3-1 布特沃斯高通滤波器 */
	namedWindow("3.a布特沃斯高通滤波器", WINDOW_AUTOSIZE);
	int d3 = 40;
	createTrackbar("截止频率", "3.a布特沃斯高通滤波器", &d3, 400, on_BHPF, planes);
	on_BHPF(40, planes);


	/* 3-2 布特沃斯低通滤波器 */
	namedWindow("3.b布特沃斯低通滤波器", WINDOW_AUTOSIZE);
	int d4 = 40;
	createTrackbar("截止频率", "3.b布特沃斯低通滤波器", &d4, 400, on_BLPF, planes);
	on_BLPF(40, planes);





	waitKey(0);

	return 0;
}

