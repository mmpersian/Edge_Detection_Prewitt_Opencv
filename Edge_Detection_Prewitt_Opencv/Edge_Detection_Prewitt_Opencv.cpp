// Edge_Detection_Prewitt_Opencv.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include<cmath>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include <iostream>

int xGradient(cv::Mat image, int x, int y)
{
    return image.at<uchar>(y - 1, x - 1) +
        2 * image.at<uchar>(y, x - 1) +
        image.at<uchar>(y + 1, x - 1) -
        image.at<uchar>(y - 1, x + 1) -
        2 * image.at<uchar>(y, x + 1) -
        image.at<uchar>(y + 1, x + 1);
}

// Computes the y component of the gradient vector
// at a given point in a image
// returns gradient in the y direction

int yGradient(cv::Mat image, int x, int y)
{
    return image.at<uchar>(y - 1, x - 1) +
        2 * image.at<uchar>(y - 1, x) +
        image.at<uchar>(y - 1, x + 1) -
        image.at<uchar>(y + 1, x - 1) -
        2 * image.at<uchar>(y + 1, x) -
        image.at<uchar>(y + 1, x + 1);
}

int main()
{
    std::cout << "Hello World!\n";
    cv::Mat src, dst;
    int gx, gy, sum;

    // Load an image
    src = cv::imread("lena512color.tiff", CV_LOAD_IMAGE_GRAYSCALE);
    dst = src.clone();
    if (!src.data)
    {
        return -1;
    }


    for (int y = 0; y < src.rows; y++)
        for (int x = 0; x < src.cols; x++)
            dst.at<uchar>(y, x) = 0.0;

    for (int y = 1; y < src.rows - 1; y++) {
        for (int x = 1; x < src.cols - 1; x++) {
            gx = xGradient(src, x, y);
            gy = yGradient(src, x, y);
            sum = abs(gx) + abs(gy);
            sum = sum > 255 ? 255 : sum;
            sum = sum < 0 ? 0 : sum;
            dst.at<uchar>(y, x) = sum;
        }
    }

    cv::namedWindow("final");
    cv::imshow("final", dst);

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
