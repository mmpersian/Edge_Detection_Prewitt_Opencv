// Edge_Detection_Prewitt_Opencv.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include<cmath>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include <iostream>

int xSobelGradient(cv::Mat image, int x, int y)
{
    return image.at<uchar>(y - 1, x - 1) +
        2* image.at<uchar>(y, x - 1) +
        image.at<uchar>(y + 1, x - 1) -
        image.at<uchar>(y - 1, x + 1) -
        2* image.at<uchar>(y, x + 1) -
        image.at<uchar>(y + 1, x + 1);
}
int xPrewittGradient(cv::Mat image, int x, int y)
{
    return image.at<uchar>(y - 1, x - 1) +
         image.at<uchar>(y, x - 1) +
        image.at<uchar>(y + 1, x - 1) -
        image.at<uchar>(y - 1, x + 1) -
        image.at<uchar>(y, x + 1) -
        image.at<uchar>(y + 1, x + 1);
}

// Computes the y component of the gradient vector
// at a given point in a image
// returns gradient in the y direction

int ySobelGradient(cv::Mat image, int x, int y)
{
    return image.at<uchar>(y - 1, x - 1) +
        2* image.at<uchar>(y - 1, x) +
        image.at<uchar>(y - 1, x + 1) -
        image.at<uchar>(y + 1, x - 1) -
        2* image.at<uchar>(y + 1, x) -
        image.at<uchar>(y + 1, x + 1);
}

int yPrewittGradient(cv::Mat image, int x, int y)
{
    return image.at<uchar>(y - 1, x - 1) +
         image.at<uchar>(y - 1, x) +
        image.at<uchar>(y - 1, x + 1) -
        image.at<uchar>(y + 1, x - 1) -
        image.at<uchar>(y + 1, x) -
        image.at<uchar>(y + 1, x + 1);
}

int main()
{
    std::cout << "Hello World!\n";
    cv::Mat src, dstSobel,dstPrewitt;
    int gsx, gsy,gpx,gpy ,sums,sump;

    // Load an image
    src = cv::imread("C:\\Users\\Mehdi\\Source\\repos\\Edge_Detection_Prewitt_Opencv\\x64\\Debug\\StivJobs1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
    dstSobel = src.clone();
    dstPrewitt = src.clone();
    if (!src.data)
    {
        return -1;
    }


    for (int y = 0; y < src.rows; y++)
        for (int x = 0; x < src.cols; x++) {
            dstSobel.at<uchar>(y, x) = 0.0;
            dstPrewitt.at<uchar>(y, x) = 0.0;
        }
    for (int y = 1; y < src.rows - 1; y++) {
        for (int x = 1; x < src.cols - 1; x++) {
        	//Sobel 
            gsx = xSobelGradient(src, x, y);
            gsy = ySobelGradient(src, x, y);
            sums = sqrt(powf(gsx,2.0) + powf(gsy,2.0));
            sums = sums > 255 ? 255 : sums;
            sums = sums < 0 ? 0 : sums;
            dstSobel.at<uchar>(y, x) = sums;
        	
            //Prewitt
            gpx = xPrewittGradient(src, x, y);
            gpy = yPrewittGradient(src, x, y);
            sump = sqrt(powf(gpx, 2.0) + powf(gpy, 2.0));
            sump = sump > 255 ? 255 : sump;
            sump = sump < 0 ? 0 : sump;
            dstPrewitt.at<uchar>(y, x) = sump;
        	
        }
    }

    cv::namedWindow("Sobel Filter");
    cv::imshow("Sobel Filter", dstSobel);

    cv::namedWindow("Prewitt Filter");
    cv::imshow("Prewitt Filter", dstPrewitt);
	
    cv::namedWindow("initial");
    cv::imshow("initial", src);

    cv::waitKey();


    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
