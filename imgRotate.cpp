#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include <opencv2/core.hpp>

using namespace std;
using namespace cv;

void imgRotate(const Mat& mat, Mat& transformedMat, const double& angle);

int main()
{

    Mat mat = imread("template.jpg", 0);
    
    Mat rotatedMat;
    imgRotate(mat, rotatedMat, 30);

    namedWindow("Rotated image", 1);
    imshow("Rotated image", rotatedMat);

    waitKey();

    return 0;
}

void imgRotate(const Mat& mat, Mat& transformedMat, const double& angle)
{
    const Point matCenter(mat.cols * 0.5, mat.rows * 0.5);
    const double angleRad = CV_PI * (angle/180);

    // Step 1: Calculate the rotation matrix, the result needs further adjustment in Step 3.
    Mat rotMat = getRotationMatrix2D(matCenter, angle, 1.0);

    // Step 2: Calculate the new image size based on the rotation angle
    const int newHeight = static_cast<int>(fabs((sin(angleRad) * mat.cols)) + fabs((cos(angleRad) * mat.rows)));
    const int newWidth = static_cast<int>(fabs((sin(angleRad) * mat.rows)) + fabs((cos(angleRad) * mat.cols)));

    // Step 3: Adjust the rotation matrix by adding the translation from old center to new center
    rotMat.at<double>(0,2) += round((newWidth - mat.cols) * 0.5);
    rotMat.at<double>(1,2) += round((newHeight - mat.rows) * 0.5);

    warpAffine(mat, transformedMat, rotMat, Size(newWidth, newHeight));

}