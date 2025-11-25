#pragma once
#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

std::string buildColorString(float, float, float);

cv::Mat applyGrayscaleFilter(const cv::Mat&);
cv::Mat applyInverseFilter(const cv::Mat&);
cv::Mat applyBlurFilter(const cv::Mat&, int);
cv::Mat applyContrastFilter(const cv::Mat&, int);

cv::Mat resizeImage(cv::Mat&, float);

float computeAverageBrightness(const cv::Mat&, int, int, int, int);
void computeAverageRGB(const cv::Mat&, int, int, int, int, float &, float &, float &);
std::string convertToASCII(cv::Mat&, std::string, int, int, bool);
std::string convertToBanner(std::string&);
