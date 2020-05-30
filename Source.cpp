#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
Mat src, src_gray;
int thresh = 120;
int max_thresh = 200;
const char* source_window = "Source image";
const char* corners_window = "Corners detected";
void cornerHarris_demo(int, void*);
void my_cornerHarris(Mat, Mat&, int, double);
int main(int argc, char** argv)
{
   
    src = imread("C:/Users/DEEPIKA/Desktop/openCV/image/google.jpg");
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
    int apertureSize = 3;
    double k = 0.04;
    Mat dst = Mat::zeros(src.size(), CV_32FC1);
    //cornerHarris(src_gray, dst, blockSize, apertureSize, k);
    my_cornerHarris(src_gray, dst,  apertureSize, k);
    Mat dst_norm , dst_norm_scaled;
    normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1);
   convertScaleAbs(dst_norm, dst_norm_scaled);
   /* for (int i = 0; i < dst_norm.rows; i++)
    {
        for (int j = 0; j < dst_norm.cols; j++)
        {
            if ((int)dst_norm.at<float>(i, j) > thresh)
            {
                circle(src, Point(j, i), 5, Scalar(0), 2, 8, 0);
            }
        }
    }*/
    for (int i = 1; i < src.rows - 1; i++) {
        for (int j = 1; j < src.cols - 1; j++)
        {
            // looping inside the image and checking if the hook value (mid vlue) of looping window
            //   and if its intensity is greater then threshold then consider it to be a corner and
            //  draw a circle of radius 5 and color black (0,0,0)
            double max1, min1;
            Mat check(dst_norm, Range(i - 1, i + 2), Range(j - 1, j + 2));
            minMaxLoc(check, &min1, &max1);
            if (max1 == dst_norm.at<float>(i, j) && dst_norm.at<float>(i, j) > 85) {
                circle(src, Point(j, i), 5, Scalar(0, 0, 0), 2, 8, 0);
            }
        }
    }
    namedWindow(corners_window);
    imshow(corners_window, src);
   
}
void my_cornerHarris(Mat src_gray, Mat& dst, int apertureSize, double k) {
    Mat Ix;// = Mat::zeros(src_gray.size(), CV_32FC1);
    Mat Iy;// = Mat::zeros(src_gray.size(), CV_32FC1);
    Sobel(src_gray, Ix,  CV_32F, 1, 0, apertureSize);
    Sobel(src_gray, Iy, CV_32F, 0, 1, apertureSize);
    Mat ixx, iyy, ixy,  x2y2, xy, mtrace,ixg, iyg, ixyg;
    pow(Ix, 2.0, ixx);                                
    pow(Iy, 2.0, iyy);                                
    multiply(Ix, Iy, ixy);
    GaussianBlur(ixx, ixg, Size(apertureSize, apertureSize), 2.0, 0.0, BORDER_DEFAULT);    
   GaussianBlur(iyy, iyg, Size(apertureSize, apertureSize), 0.0, 2.0, BORDER_DEFAULT);    
    GaussianBlur(ixy, ixyg, Size(apertureSize, apertureSize), 2.0, 2.0, BORDER_DEFAULT);
    multiply(ixg, iyg, x2y2);
    multiply(ixyg, ixyg, xy);
    pow((ixg + iyg), 2.0, mtrace);
    dst = (x2y2 - xy) - k * mtrace;
  
    imshow("ouput",dst);
  }