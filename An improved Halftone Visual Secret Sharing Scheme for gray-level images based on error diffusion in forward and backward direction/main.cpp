#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <time.h>

using namespace cv;
using namespace std;

/**
It is implemented according to "An improved Halftone Visual Secret Sharing Scheme for gray-level images based on error diffusion in forward and backward direction"
Published: IEEE, Advanced Computing & Communication Technologies (ACCT), 2015 Fifth International Conference
Author: Aman Kamboj, D.K.Gupta
*/

IplImage* getHalfTone(IplImage*);
void encrypProcess(IplImage*, IplImage*, IplImage*);

int main()
{
    // Input image G
    IplImage *img=cvLoadImage("LennaGray.png");
    IplImage *grayImg = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U,1);
    cvCvtColor(img, grayImg, CV_RGB2GRAY);

    // HalfTone image I
    IplImage *halfToneImg = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U,1);

    // Inverse of HalfTone image I'
    IplImage *inv_halfToneImg = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U,1);

    // Secret image
    IplImage *secretImg = cvLoadImage("cameraman.jpg");
    IplImage *gray_secretImg = cvCreateImage(cvSize(secretImg->width, secretImg->height), IPL_DEPTH_8U,1);
    cvCvtColor(secretImg, gray_secretImg, CV_RGB2GRAY);
    IplImage *halfTone_secret = cvCreateImage(cvSize(secretImg->width, secretImg->height), IPL_DEPTH_8U,1);

    // Reconstructed image
    IplImage *superimposed = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U,1);

    // ===== Phase 1: Halftoning process =====

    halfToneImg = getHalfTone(grayImg);

    halfTone_secret = getHalfTone(gray_secretImg);

    // Get inverse of halfTone image
    cvNot(halfToneImg, inv_halfToneImg);

    cvSaveImage("halfTone.png", halfToneImg);

    cvSaveImage("inv_halfTone.png", inv_halfToneImg);

    // ===== Phase 2: Encryption process =====

    encrypProcess(halfTone_secret, halfToneImg, inv_halfToneImg);

    cvSaveImage("Share1.png", halfToneImg);

    cvSaveImage("Share2.png", inv_halfToneImg);

    // ===== Phase 3: Decryption process =====

    cvAnd(halfToneImg,inv_halfToneImg, superimposed);

    cvSaveImage("Superimposed.png", superimposed);

    cvWaitKey(0);
    return 0;
}

void encrypProcess(IplImage *secret, IplImage *halfTone, IplImage *invHalfTone)
{
    // Code books
    int whiteM1[4] = {0,255,0,255};
    int whiteM2[4] = {255,0,255,0};
    int blackM1[4] = {0,255,255,0};
    int blackM2[4] = {255,0,0,255};

    srand(time(NULL));

    for (int i = 0; i < secret->height; ++i)
    {
        for (int j = 0; j < secret->width; ++j)
        {
            int randNum = rand() % 2;

            uchar pixVal = secret->imageData[i*secret->widthStep+j];

            int *selectM;

            if(pixVal == 0)
            {
                if(randNum == 0)
                {
                    selectM = blackM1;
                }
                else
                {
                    selectM = blackM2;
                }
            }
            else
            {
                if(randNum == 0)
                {
                    selectM = whiteM1;
                }
                else
                {
                    selectM = whiteM2;
                }
            }

            // Modify halfTone & rev-halfTone by selected matrix M
            halfTone->imageData[(2*i)*halfTone->widthStep+(2*j)] = selectM[0];
            halfTone->imageData[(2*i+1)*halfTone->widthStep+(2*j+1)] = selectM[1];

            invHalfTone->imageData[(2*i)*invHalfTone->widthStep+(2*j)] = selectM[2];
            invHalfTone->imageData[(2*i+1)*invHalfTone->widthStep+(2*j+1)] = selectM[3];

        }
    }
}


/**
Calculate halfTone image of gray level image
*/
IplImage* getHalfTone(IplImage *grayImg)
{
    IplImage *halfToneImg = cvCreateImage(cvSize(grayImg->width, grayImg->height), IPL_DEPTH_8U,1);

    for (int i=2; i<grayImg->height; ++i)
    {
        for (int j=2; j<grayImg->width; ++j)
        {
            uchar c = grayImg->imageData[i*grayImg->widthStep+j];

            halfToneImg->imageData[i*halfToneImg->widthStep+j] = c >= 127.5 ? 255:0;

            // Calculate error
            int error = grayImg->imageData[i*grayImg->widthStep+j] - halfToneImg->imageData[i*halfToneImg->widthStep+j];

            // Diffuse error to neighboring pixels
            grayImg->imageData[i*grayImg->widthStep+j+1] += (error*0.075);
            grayImg->imageData[i*grayImg->widthStep+j-1] += (error*0.075);
            grayImg->imageData[(i-1)*grayImg->widthStep+j] += (error*0.075);
            grayImg->imageData[(i+1)*grayImg->widthStep+j] += (error*0.075);

            grayImg->imageData[(i+1)*grayImg->widthStep+j+1] += (error*0.05);
            grayImg->imageData[(i+1)*grayImg->widthStep+j-1] += (error*0.05);
            grayImg->imageData[(i-1)*grayImg->widthStep+j+1] += (error*0.05);
            grayImg->imageData[(i-1)*grayImg->widthStep+j-1] += (error*0.05);
            grayImg->imageData[(i-2)*grayImg->widthStep+j] += (error*0.05);
            grayImg->imageData[(i)*grayImg->widthStep+j+2] += (error*0.05);
            grayImg->imageData[(i+2)*grayImg->widthStep+j] += (error*0.05);
            grayImg->imageData[(i)*grayImg->widthStep+j-2] += (error*0.05);

            grayImg->imageData[(i-2)*grayImg->widthStep+j+1] += (error*0.03);
            grayImg->imageData[(i-2)*grayImg->widthStep+j-1] += (error*0.03);
            grayImg->imageData[(i+2)*grayImg->widthStep+j+1] += (error*0.03);
            grayImg->imageData[(i+2)*grayImg->widthStep+j-1] += (error*0.03);
            grayImg->imageData[(i-1)*grayImg->widthStep+j+2] += (error*0.03);
            grayImg->imageData[(i-1)*grayImg->widthStep+j-2] += (error*0.03);
            grayImg->imageData[(i+1)*grayImg->widthStep+j+2] += (error*0.03);
            grayImg->imageData[(i+1)*grayImg->widthStep+j-2] += (error*0.03);

            grayImg->imageData[(i-2)*grayImg->widthStep+j+2] += (error*0.015);
            grayImg->imageData[(i-2)*grayImg->widthStep+j-2] += (error*0.015);
            grayImg->imageData[(i+2)*grayImg->widthStep+j+2] += (error*0.015);
            grayImg->imageData[(i+2)*grayImg->widthStep+j-2] += (error*0.015);

        }

    }

    return halfToneImg;
}

