#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat src, src_gray;
int thresh =90;
int max_thresh = 200;
int apertureSize = 3;
double k = 0.04;
double myHarris_minVal, myHarris_maxVal;
const char* source_window = "Source image";
const char* corners_window = "Corners detected";
void cornerHarris_demo(int, void*);
void My_cornerEigenVals(Mat, Mat&);
int main(int argc, char** argv)
{
    
    src = imread("C:/Users/DEEPIKA/Desktop/openCV/image/google.jpg");
    //  cout << src;
    if (src.empty())
    {
        cout << "Could not open or find the image!\n" << endl;
        cout << "Usage: " << argv[0] << " <Input image>" << endl;
        return -1;
    }
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
  
    namedWindow(source_window);
    createTrackbar("Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo);
    imshow(source_window, src);
    cornerHarris_demo(0, 0);
    waitKey();
    return 0;
}
void cornerHarris_demo(int, void*)
{
   
    
 Mat   dst = Mat::zeros(src.size(), CV_32FC1);
     My_cornerEigenVals(src_gray, dst);

  

   
    // cornerHarris(src_gray, dst, blockSize, apertureSize, k);

   
   
    Mat dst_norm;
    Mat clone = src.clone();
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
   
    for (int i = 0; i < dst_norm.rows; i++)
    {
        for (int j = 0; j < dst_norm.cols; j++)
        {
            if ((int)dst_norm.at<float>(i, j) > thresh)
            {
                circle(clone, Point(j, i), 5, Scalar(0), 2, 8, 0);
            }
        }
    }
    namedWindow(corners_window);
    imshow(corners_window, clone);
    waitKey(0);
}


void  My_cornerEigenVals(Mat src_gray, Mat& dst) {
    
    Mat Dx, Dy;
    
    Sobel(src_gray, Dx, CV_32FC1, 1, 0, 3);
    Sobel(src_gray, Dy, CV_32FC1, 0, 1, 3);
   Mat dxx, dyy, dxy, dxyg, dyyg, dxxg, x2y2, xyg,mtrace;
    pow(Dx, 2.0, dxx);
    pow(Dy, 2.0, dyy);
    multiply(Dx, Dy, dxy);
    GaussianBlur(dxx, dxxg, Size(3, 3), 2.0, 0.0,BORDER_DEFAULT);
    GaussianBlur(dyy, dyyg, Size(3, 3), 0.0, 2.0,BORDER_DEFAULT);
    GaussianBlur(dxy, dxyg, Size(3, 3), 2.0,2.0, BORDER_DEFAULT);
    multiply(dxxg, dyyg, x2y2);
    multiply(dxyg, dxyg, xyg);
    pow((dxxg + dyyg), 2.0, mtrace);
    
    dst = (x2y2 - xyg) - k * (mtrace);
    
   k * mtrace;
  
    imshow("dst", dst);
}