#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


//高斯噪声
Mat AddGaussion(Mat src) {
	Mat dst = src.clone();

	Mat noise = Mat::zeros(src.rows, src.cols, src.type());
	RNG rng;
	rng.fill(noise, RNG::NORMAL, 10, 20);
	dst = dst + noise;
	return dst;
}

//椒盐噪声（取决于val==0 or 255）
Mat AddPepperSalt(Mat src,uchar val) {
	Mat dst = src.clone();
	RNG rng(val);
	for (int t = 0; t < 10000; ++t) {
		int i = rng.uniform(0, src.rows);
		int j = rng.uniform(0, src.cols);
		dst.at<uchar>(i, j) = val;
	}
	return dst;
}


//算术均值滤波
Mat ArithmeticMeanFileter(Mat src)
{
	Mat kernel = Mat::ones(5, 5, CV_32F) / (float)(5 * 5);
	Mat dst;
	filter2D(src, dst, -1, kernel);
	return dst;
}

//几何均值滤波
Mat GeometryMeanFilter(Mat src)
{
	Mat dst = Mat::zeros(src.size(),src.type());

	double product;
	int mn;
	int row, col;
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			product = 1;
			mn = 0;
			for (int m = -2; m <= 2; ++m) {
				row = i + m;
				for (int n = -2; n <= 2; ++n) {
					col = j + n;
					if (row >= 0 && row < src.rows && col >= 0 && col < src.cols) {
						product *= (src.at<uchar>(row, col)==0?1: src.at<uchar>(row, col));
						++mn;
					}
				}
			}
			dst.at<uchar>(i, j) = pow(product, 1.0 / mn);
		}
	}
	return dst;
}

//谐波均值滤波
Mat HamonicMeanFilter(Mat src) {
	Mat dst = Mat::zeros(src.size(), src.type());

	double sum;
	int mn;
	int row, col;
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			sum = 0;
			mn = 0;
			for (int m = -2; m <= 2; ++m) {
				row = i + m;
				for (int n = -2; n <= 2; ++n) {
					col = j + n;
					if (row >= 0 && row < src.rows && col >= 0 && col < src.cols) {
						sum += (src.at<uchar>(row, col) == 0 ? 255 : 255.0/src.at<uchar>(row, col));
						++mn;
					}
				}
			}
			dst.at<uchar>(i, j) = mn / sum * 255;
		}
	}
	return dst;
}

//逆谐波均值滤波
Mat InverseHamonicMeanFilter(Mat src, double Q) {
	Mat dst = Mat::zeros(src.size(), src.type());

	double sum1;
	double sum2;
	int row, col;
	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			sum1 = 0;
			sum2 = 0;
			for (int m = -2; m <= 2; ++m) {
				row = i + m;
				for (int n = -2; n <= 2; ++n) {
					col = j + n;
					if (row >= 0 && row < src.rows && col >= 0 && col < src.cols) {
						sum1 += pow(src.at<uchar>(row, col) / 255.0, Q + 1);
						sum2 += pow(src.at<uchar>(row, col) / 255.0, Q);
					}
				}
			}
			dst.at<uchar>(i, j) = sum1 / sum2 * 255;
		}
	}
	return dst;
}


//自适应均值滤波
Mat SelfAdaptMeanFilter(Mat src) {
	Mat mean = ArithmeticMeanFileter(src);	//先求一下局部均值
	Mat dst = Mat::zeros(src.size(), src.type());

	double gxy;			//图像在x、y的像素值
	double ml;			//局部均值
	double Sl;			//局部方差
	double Si = 100;	//全局方差
	int mn;
	int row, col;

	for (int i = 0; i < src.rows; ++i) {
		for (int j = 0; j < src.cols; ++j) {
			gxy = src.at<uchar>(i, j);
			ml = mean.at<uchar>(i, j);
			Sl = 0;
			mn = 0;
			for (int m = -3; m <= 3; ++m) {
				row = i + m;
				for (int n = -3; n <= 3; ++n) {
					col = j + n;
					if (row >= 0 && row < src.rows && col >= 0 && col < src.cols) {
						Sl = Sl + pow(src.at<uchar>(row, col) - ml, 2);
						++mn;
					}
				}
			}
			Sl = Sl / mn;
			dst.at<uchar>(i, j) = gxy - Si / Sl * (gxy - ml);
		}
	}
	return dst;
}

//自适应中值滤波
Mat SelfAdaptMedianFilter(Mat src) {
	Mat dst = Mat::zeros(src.size(), src.type());
	int row, col;
	double Zmin, Zmax, Zmed, Zxy, Smax = 7;
	int wsize;
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			wsize = 1;
			while (wsize <= 3) {
				Zmin = 255.0;
				Zmax = 0.0;
				Zmed = 0.0;
				Zxy = src.at<uchar>(i, j);
				int mn = 0;
				for (int m = -wsize; m <= wsize; m++) {
					row = i + m;
					for (int n = -wsize; n <= wsize; n++) {
						col = j + n;
						if (row >= 0 && row < src.rows && col >= 0 && col < src.cols) {
							if (src.at<uchar>(row, col) > Zmax) {
								Zmax = src.at<uchar>(row, col);
							}
							if (src.at<uchar>(row, col) < Zmin) {
								Zmin = src.at<uchar>(row, col);
							}
							Zmed = Zmed + src.at<uchar>(row, col);
							mn++;
						}
					}
				}
				Zmed = Zmed / mn;
				if ((Zmed - Zmin) > 0 && (Zmed - Zmax) < 0) {
					if ((Zxy - Zmin) > 0 && (Zxy - Zmax) < 0) {
						dst.at<uchar>(i,j) = Zxy;
					}
					else {
						dst.at<uchar>(i, j) = Zmed;
					}
					break;
				}
				else {
					wsize++;
					if (wsize > 3) {
						dst.at<uchar>(i, j) = Zmed;
						break;
					}
				}
			}
		}
	}
	return dst;
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
	imshow("原始图像", img);

	//加噪声
	Mat Gaussion_noise = AddGaussion(img);
	Mat Pepper_noise = AddPepperSalt(img, 0);
	Mat Salt_noise = AddPepperSalt(img, 255);
	Mat PepperSalt_noise = AddPepperSalt(Pepper_noise, 255);

	/* 1.均值滤波 */
	/*
	//高斯噪声 + 算术均值滤波、几何均值滤波、谐波均值滤波
	imshow("高斯噪声", Gaussion_noise);
	imshow("高斯噪声+算术均值滤波", ArithmeticMeanFileter(Gaussion_noise));
	imshow("高斯噪声+几何均值滤波", GeometryMeanFilter(Gaussion_noise));
	
	//胡椒噪声 + 谐波均值滤波、逆谐波均值滤波(Q=1)
	imshow("胡椒噪声", Pepper_noise);
	imshow("胡椒噪声+谐波均值滤波", HamonicMeanFilter(Pepper_noise));
	imshow("胡椒噪声+逆谐波均值滤波", InverseHamonicMeanFilter(Pepper_noise, 1));
	
	//盐噪声 + 谐波均值滤波、逆谐波均值滤波(Q=-1)
	
	imshow("盐噪声", Salt_noise);
	imshow("盐噪声+谐波均值滤波", HamonicMeanFilter(Salt_noise));
	imshow("盐噪声+逆谐波均值滤波", InverseHamonicMeanFilter(Salt_noise, -1));
	
	//椒盐噪声 + 谐波均值滤波、逆谐波均值滤波(Q=1)
	imshow("椒盐噪声", PepperSalt_noise);
	imshow("椒盐噪声+谐波均值滤波", HamonicMeanFilter(PepperSalt_noise));
	imshow("椒盐噪声+逆谐波均值滤波", InverseHamonicMeanFilter(PepperSalt_noise, 1));
	*/



	/* 2.中值滤波 */
	/*
	Mat median_dst;
	//胡椒噪声 + 中值滤波
	imshow("胡椒噪声", Pepper_noise);
	medianBlur(Pepper_noise, median_dst, 5);
	imshow("胡椒噪声+中值滤波5*5", median_dst);
	medianBlur(Pepper_noise, median_dst, 9);
	imshow("胡椒噪声+中值滤波9*9", median_dst);

	//盐噪声 + 中值滤波
	imshow("盐噪声", Salt_noise);
	medianBlur(Salt_noise, median_dst, 5);
	imshow("盐噪声+中值滤波5*5", median_dst);
	medianBlur(Salt_noise, median_dst, 9);
	imshow("盐噪声+中值滤波9*9", median_dst);

	//椒盐噪声 + 中值滤波
	imshow("椒盐噪声", PepperSalt_noise);
	medianBlur(PepperSalt_noise, median_dst, 5);
	imshow("椒盐噪声+中值滤波5*5", median_dst);
	medianBlur(PepperSalt_noise, median_dst, 9);
	imshow("椒盐噪声+中值滤波9*9", median_dst);
	*/




	/* 3.自适应均值滤波 */
	/*
	Mat SelfAdaptMean_dst;
	imshow("高斯噪声", Gaussion_noise);
	imshow("高斯噪声+算术均值滤波", ArithmeticMeanFileter(Gaussion_noise));
	imshow("高斯噪声+几何均值滤波", GeometryMeanFilter(Gaussion_noise));
	SelfAdaptMean_dst = SelfAdaptMeanFilter(Gaussion_noise);
	imshow("高斯噪声+自适应均值滤波", SelfAdaptMean_dst);
	*/




	/* 4.自适应中值滤波 */
	/*
	Mat SelfAdaptMedian_dst;
	imshow("椒盐噪声", PepperSalt_noise);
	medianBlur(PepperSalt_noise, SelfAdaptMedian_dst, 5);
	imshow("椒盐噪声+中值滤波5*5", SelfAdaptMedian_dst);
	SelfAdaptMedian_dst = SelfAdaptMedianFilter(PepperSalt_noise);
	imshow("椒盐噪声+自适应中值滤波7*7", SelfAdaptMedian_dst);
	*/




	/* 5.彩色图像均值滤波 */
	/*
	Mat img_color = imread(image_path, IMREAD_COLOR);
	imshow("彩色图像", img_color);
	vector<Mat> BGR;
	split(img_color, BGR);
	for (int i = 0; i < 3; ++i) {
		BGR[i] = AddGaussion(BGR[i]);
	}
	Mat noise_color;
	merge(BGR, noise_color);
	imshow("彩色高斯噪声", noise_color);

	//算术均值滤波
	split(noise_color, BGR);
	for (int i = 0; i < 3; ++i) {
		BGR[i] = ArithmeticMeanFileter(BGR[i]);
	}
	Mat Arith;
	merge(BGR, Arith);
	imshow("彩色高斯噪声+算术均值滤波", Arith);

	//几何均值滤波
	split(noise_color, BGR);
	for (int i = 0; i < 3; ++i) {
		BGR[i] = GeometryMeanFilter(BGR[i]);
	}
	Mat Geo;
	merge(BGR, Geo);
	imshow("彩色高斯噪声+几何均值滤波", Geo);
	*/

	waitKey(0);
	return 0;
}
