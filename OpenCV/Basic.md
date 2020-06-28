[TOC]



## Mat

Mat中存储了一个像素矩阵的指针（M.data?）、以及相关的元数据（M.rows、M.cols、M.type()）

- 像素的坐标：(y,x)==(row,col)，下标从0开始

- RGB中，一个像素中的排列为：BGR

```c++
Vec3b px = img.at<Vec3b>(y, x);
uchar blue = px.val[0];	//RGB的第一个数据是B
```

颜色转换

```c++
cvtColor(src, dst, COLOR_BGR2GRAY);
```



##### 拷贝Mat

1. 浅拷贝：只拷贝指针

```c++
// A,B,C,D,E操作同一个像素矩阵
Mat A = imread("pic.jpg",IMREAD_COLOR);
Mat B(A);	//拷贝构造
Mat C = A;	//浅拷贝

//取图像的一部分
Mat D(A, Rect(10, 10, 100, 100) );
Mat E = A(Range::all(), Range(1,3));
```

2. 深拷贝：复制像素矩阵

```c++
// 操作F、G不会影响A
Mat F = A.clone();
Mat G;
A.copyTo(G);
```

##### 创建Mat

1. 构造函数

   ```c++
   Mat M(2,2, CV_8UC3, Scalar(0,0,255));	//行、列、类型、填充值
   cout <<M << endl;
   ```

   M是一个2*2的像素矩阵：

   CV_8UC3：数组中为8位、usigned char类型的元素，每个像素3个通道。

   Scalar(0,0,255)：每个像素的填充值

2. 方法

   ```c++
   M.create(4,4, CV_8UC(1));
   M.creat(A.size(),A.type());
   M.creat(A.rows, A.clos, A.type())
   ```

   CV_8UC(1)：表示每个像素只有一个通道

3. 特殊矩阵

   ```c++
   Mat E = Mat::eye(4, 4, CV_64F);
   Mat O = Mat::ones(2, 2, CV_32F);
   Mat Z = Mat::zeros(A.size(),A.type());
   ```

4. 手动输入

   ```c++
   Mat C = (Mat_<double>(3,3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
   
   C = (Mat_<double>({0, -1, 0, -1, 5, -1, 0, -1, 0})).reshape(3);
   ```

5. 提取行

   ```c++
   Mat NewRow = C.row(1).clone();	//提取了第2行，注意下标
   ```

6. 填充随机值

   ```c++
   randu(A, Scalar::all(0), Scalar::all(255));	//指定随机值范围
   ```

7. 打印格式

   ```c++
   cout << R << endl << endl;	//默认按照矩阵打印
   cout << format(R, Formatter::FMT_PYTHON) << endl << endl;	//每个像素用[]括起来
   ```

8. 其他类型的数据

   ```c++
   Point2f P(5, 1);
   Point3f P3f(2, 6, 7);
   //用vector构造Mat，注意此时vec和Mat共用同一内存
   Mat(vector<float> vec({(float)CV_PI, 2, 3.01f}));
   ```



##### 计时

```c++
double t = (double)getTickCount();
// do something ...
t = ((double)getTickCount() - t)/getTickFrequency();
cout << "Times passed in seconds: " << t << endl;
```





## 遍历像素矩阵

##### at

用于获取单个像素的信息：

- 只在debug下检查index范围合法性

- 注意坐标：(y,x)==(row,col)

```c++
//单通道
Scalar intensity = img.at<uchar>(y, x);
Scalar intensity = img.at<uchar>(Point(x, y));//转换坐标
img.at<uchar>(y, x) = 128;

//BGR
Vec3b intensity = img.at<Vec3b>(y, x);
uchar blue = intensity.val[0];
uchar green = intensity.val[1];
uchar red = intensity.val[2];
```

遍历图像：（性能相对较差，且不安全）

```c++
Mat H(100, 100, CV_64F);
for(int i = 0; i < H.rows; i++)
    for(int j = 0; j < H.cols; j++)
        H.at<double>(i,j)=1./(i+j+1);
```



##### cvGet2D&cvSet2D

```c++
pixel = cvGet2D(img, i, j);
pixel.val[0] = 0;
pixel.val[1] = 0;
pixel.val[2] = 0;
cvSet2D(img, i, j, pixel);
```



以下的例子中，我们用一个数组table[]，将图像中值为x的像素映射为table[x]

##### 数组遍历

（高效）

```c++
CV_Assert(I.depth() == CV_8U);	//检查是uchar类型

int channels = I.channels();	//获取矩阵行列数目
int nRows = I.rows;
int nCols = I.cols * channels;

if (I.isContinuous())	//有时矩阵可能以一行形式存储
{
    nCols *= nRows;
    nRows = 1;
}
    
uchar* p;
for(int i = 0; i < nRows; ++i)
{
	p = I.ptr<uchar>(i);	//获取第i行的指针
    for (int j = 0; j < nCols; ++j)
    {
        p[j] = table[p[j]];	//i行的第j个元素（注意如果通道是3，则要处理连续的三个BGR元素）
    }
}
```

##### 迭代器遍历

（安全）

```c++
CV_Assert(I.depth() == CV_8U);	//检查是uchar类型
const int channels = I.channels();
switch(channels)
{
case 1:		//灰度图像
{
    MatIterator_<uchar> it, end;
    for( it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
    *it = table[*it];
    break;
}
case 3:		//彩色图像，元素类型为Vec3b
{
    MatIterator_<Vec3b> it, end;
    for( it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
    {
        (*it)[0] = table[(*it)[0]];
        (*it)[1] = table[(*it)[1]];
        (*it)[2] = table[(*it)[2]];
    }
}
}
```



##### LUT

（多线程）

```c++
//先将table映射转换为mat
Mat lookUpTable(1, 256, CV_8U);
uchar* p = lookUpTable.ptr();
for( int i = 0; i < 256; ++i)
	p[i] = saturate_cast<uchar>(table[i]);

//处理
LUT(src, lookUpTable, dst);
```





## 读入/显示/写图像

```c++
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    // imread：读取图像，存入到mat
    // 加载方式：
    // IMREAD_COLOR：BGR 8位格式加载图像。默认值。
	// IMREAD_UNCHANGED：照原样加载图像（包括Alpha通道（如果存在））
	// IMREAD_GRAYSCALE：灰度
	string image_path = samples::findFile("starry_night.jpg");
	Mat img = imread(image_path, IMREAD_COLOR);
	if (img.empty()) {
		cout << "Could not read the image: " << image_path << endl;
		return 1;
	}
    
    // 生成窗口
    namedWindow("Output", WINDOW_AUTOSIZE);
    // imshow：显示图像到指定窗口
	imshow("Output", img);
    
    // imwrite：保存图像
    // 参数：在指定时间内等待一次输入
	int k = waitKey(0);
	if (k == 's') {
		imwrite("starry_night.png", img);
	}
	return 0;
}
```



## GUI-trackbar

当多个trackbar调用同一个回调函数时，用全局变量更适合

```c++
#include "opencv2/highgui.hpp"
using namespace cv;

//注意：此处使用static使得on_trackbar可以访问全局变量
const int slider_max = 100;
int slider = 50;
Mat src,dst;
// 回调函数（static不是必须的）
static void on_trackbar( int , void* )
{
    imshow("Output",dst);
}


int main() {
    //创建窗口
    namedWindow("Output", WINDOW_AUTOSIZE); 
    
    //创建trackbar
    //参数：显示的文字、窗口名称、数据被绑定到slider变量、最大值、回调函数
    createTrackbar("Name 100", "Output", &slider, slider_max, on_trackbar);
    
    //调用一次回调函数，进行初始化
    on_trackbar(slider, 0);
    
    waitKey(0);
    return 0;
}
```

##### 传数据给回调函数

不使用全局变量的方法。

 createTrackbar可以有第6个参数，用于传数据给回调函数：如传Mat &img

```c++
namedWindow("winName", WINDOW_AUTOSIZE);	//创建窗口
int slider = 50;
createTrackbar("trackBarName", "winName", &slider, slider_max, callback, &img);
callback(50, &img);	//调用一次回调函数
```

回调函数：

```c++
void callback(int pos, void* usrdata)	//参数pos为trackbar的数值
{
    Mat src =*(Mat*)(usrdata);	//强制类型转换（userdata不能为0！！）
    Mat dst;
    
    // 二值化
    threshold(src, dst, pos, 255, 0);

    imshow(winName, dst);
}
```



##### 摄像机

```c++
void camera() 
{
	Mat frame, frame_gray;
	cout << frame << endl;
	VideoCapture cap(0);
	namedWindow("Video Capture");
	namedWindow("Object Detection");
	while (true) {
		cap >> frame;
		if (frame.empty())
		{
			break;
		}
		// Convert from BGR to HSV colorspace
		cvtColor(frame, frame_gray, COLOR_BGR2GRAY); //将图像转换为灰度

		// Show the frames
		imshow("Video Capture", frame);
		imshow("Object Detection", frame_gray);


		char key = (char)waitKey(30);
		if (key == 'q' || key == 27)
		{
			break;
		}
	}

	return;
}
```





## 图像处理

#### 基本工具

##### **限界**

有时对像素赋值时，可能计算后的值会超出合法范围，可使用`saturate_cast`进行限界。

```c++
for( int c = 0; c < src.channels(); c++ ) {
    dst.at<Vec3b>(y,x)[c] =
    saturate_cast<uchar>( alpha*src.at<Vec3b>(y,x)[c] + beta );
}
```



##### **LUT**

查表法，依次对每个像素，将其值转换为lookUpTable[256]中对应的值。

1. 创建映射表lookUpTable[256]：存储将0~255的灰度值根据具体变换算法映射后的值。

2. LUT函数对src的每一个像素（RGB也有效），查找映射表，将其转换为对应值。

```c++
LUT(src, lookUpTable, dst);
```

（示例代码见：遍历像素矩阵-LUT）



##### **归一化**

将数组中的数据归一化到 [min,max] 范围

```c++
vector<int> arr;
normalize(arr, arr, min, max, NORM_MINMAX, -1, Mat());
```



##### **绝对值**

对每个像素计算：
$$
dst = |src * \alpha + \beta|
$$

```
convertScaleAbs(src, dst, alpha=1.0, beta=0.0);
```

超出部分限界。



##### **随机数**

```
RNG rng;	//可以设定随机数种子rng(seed)
int i = rng.uniform(0, src.rows);
int j = rng.uniform(0, src.cols);
```





##### **色彩空间**

```
cvtColor(src, dst, COLOR_BGR2GRAY);
cvtColor(src, dst, COLOR_BGR2HLS);
```



##### **通道分离**

用Mat数组的写法（推荐）：

```c++
//分离、分别对每个通道处理（可用for循环）、合并
Mat planes[3];
split(src, planes);
filter2D(planes[0], planes[0], -1, kernel);
filter2D(planes[1], planes[1], -1, kernel);
filter2D(planes[2], planes[2], -1, kernel);
merge(planes, 3, dst);	
//merge的第2个参数为合并的通道数
```

vector的写法：

```c++
//色彩空间的转换
cvtColor(bgr, hls, COLOR_BGR2HLS);

//将hls分离为三个通道分量，存储到vector<Mat> HLS
vector<Mat> HLS;
split(hls, HLS);	
//对亮度通道进行直方图均衡
equalizeHist(HLS[1], HLS[1]);
//合并通道
merge(HLS, img_hls);

//色彩空间的转换
cvtColor(img_hls, src, COLOR_HLS2BGR);
```







#### 蒙版运算（核）

```c++
//定义核
Mat kernel = (Mat_<char>(3,3) <<  0, -1,  0,
                                 -1,  5, -1,
                                  0, -1,  0);
//src是读入的图像，dst是输出的图像
Mat dst;
filter2D(src, dst, -1, kernel);


//不要忘记对核进行归一化，如：
Mat kernel = Mat::ones(3, 3, CV_32F) / (float)(3 * 3);
```



#### 线性混合

$$
dst=α⋅src1+β⋅src2+γ
$$

```c++
double alpha = 0.5, beta;
beta = 1 - alpha;
addWeighted( src1, alpha, src2, beta, gama, dst);
```

超出部分限界。

变量名beta会和C++17的std::beta命名冲突。



#### 亮度&饱和度

**线性变换**：
$$
g(x)=αf(x)+β
$$

```c++
src.convertTo(dst, -1, alpha, beta);//第二个参数为-1，则dst和src的type相同
```

alpha<1：直方图被压缩，对比度降低

增大beta：亮度增加，若发生过饱和，对比度会降低（可用alpha进行补偿）

过饱和：线性变换后某些值可能会超出范围而被限界，导致失真，对比度降低。

**伽马变换**：
$$
O=(\frac{I}{255})^γ × 255
$$
![伽马变换.png](https://docs.opencv.org/master/Basic_Linear_Transform_Tutorial_gamma.png)

伽马变换不会像线性变换一样出现过饱和的情况。

```c++
//先根据伽马函数创建映射表
Mat lookUpTable(1, 256, CV_8U);
uchar* p = lookUpTable.ptr();
for( int i = 0; i < 256; ++i)
	p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);

//使用LUT进行伽马变换
LUT(src, lookUpTable, dst);
```





#### 二值化

```c++
// 转换为灰度图
cvtColor( src, src_gray, COLOR_BGR2GRAY );
// 二值化
threshold( src_gray, dst, threshold_value, max_binary_value, threshold_type );
```

二值化的type参数说明：

 0：二进制（常用）

1：二进制反转

2：阈值被截断

3：阈值归零

4：阈值反转为零



#### 直方图

直方图均衡

```c++
// 必须是灰度图的均衡
equalizeHist(img, dst);

// 对于多通道，先split，再均衡
cvtColor(img, src, COLOR_BGR2HLS);
vector<Mat> HLS;
split(src, HLS);	//分离通道，存储到vector<Mat> HLS
equalizeHist(HLS[1], HLS[1]);//对亮度通道L进行直方图均衡
merge(HLS, dst);	//合并通道
```

绘制RGB直方图

```c++
void drawHistgram_BGR(Mat& img, string title) {
	//分解BGR三个通道
	vector<Mat> bgr_planes;
	split(img, bgr_planes);

	//计算三个通道的直方图
	Mat b_hist, g_hist, r_hist;
	//指定参数
	int histSize = 256;					//直方图的桶数
	float range[] = { 0, 256 };
	const float* histRange = { range };	//直方图横坐标的范围（左闭右开）
	bool uniform = true, accumulate = false;
	calcHist( &bgr_planes[0],	//蓝色通道Mat
              1, 0,				//图像数、通道数
              Mat(),			//遮罩，这里用空的
              b_hist,			//dst
              1,				//直方图横坐标维度
              &histSize,		//直方图的桶数
              &histRange,		//直方图横坐标的范围
              uniform, accumulate );	//设为true和false
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histSize, &histRange, uniform, accumulate);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histSize, &histRange, uniform, accumulate);

	//设置绘制参数
	int hist_w = 512, hist_h = 400;						//图的宽、高
	int bin_w = cvRound((double)hist_w / histSize); 	//每个桶的宽度
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	//归一化
	normalize(b_hist, b_hist,	//src、dst
            0, histImage.rows,//归一化后的范围（将直方图数值归一化到图像的高度）
            NORM_MINMAX, -1, Mat());
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	//绘制
	for (int i = 1; i < histSize; i++)
	{
		line(histImage,	//指定绘制线到哪个图像、两个端点、线的颜色
			 Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
			 Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))),
			 Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(g_hist.at<float>(i - 1))),
			 Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))),
			 Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(r_hist.at<float>(i - 1))),
			 Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))),
			 Scalar(0, 0, 255), 2, 8, 0);
	}
	//另一种绘制方法是，每次画竖线，即把线的两端点横坐标设为相同（适合单通道的直方图），见下面的例子

	imshow(title, histImage);
}
```

绘制灰度图像的直方图（自己写的一个函数）

```c++
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
```

#### 平滑

均值滤波

```c++
blur( src, dst, Size( i, i ), Point(-1,-1) );	//指定核的大小、锚点
```

高斯滤波

```c++
GaussianBlur( src, dst, Size( i, i ), 0, 0 );	//最后两个为标准差σx、σy（0表示自动计算）
```

