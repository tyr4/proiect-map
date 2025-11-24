#pragma once
#include <iostream>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

cv::Mat convertToGrayscale(const cv::Mat&);
cv::Mat resizeImage(cv::Mat&, float);
float computeAverageBrightness(const cv::Mat&, int, int, int, int);
std::string convertToASCII(cv::Mat&, std::string, int, int);
