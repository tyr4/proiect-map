#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <signal.h>
#include <thread>

constexpr float CHAR_ASPECT = 0.5f;

// enum is for easier switch handling
enum FILTERS {BLUR = 1, GRAYSCALE, INVERSE, CONTRAST};

std::string buildColorString(float R, float G, float B, char character);

cv::Mat applyGrayscaleFilter(const cv::Mat &input);
cv::Mat applyInverseFilter(const cv::Mat &input);
cv::Mat applyBlurFilter(const cv::Mat &input, int amount);
cv::Mat applyContrastFilter(const cv::Mat &input, int amount);

cv::Mat resizeImage(cv::Mat &input, float factor);

float computeAverageBrightness(const cv::Mat &input, int startWidth, int startHeight, int width, int height);
void computeAverageRGB(const cv::Mat &input, int startWidth, int startHeight, int width, int height, float &Rval, float &Gval, float &Bval);
std::string convertToASCII(cv::Mat &input, std::string charset, int width, int height, bool wantsColor);
void playVideoASCII(cv::VideoCapture video, std::string charset, int width, int height, std::string filter, int amount);
std::string convertToBanner(std::string &input);

void applyFilter(cv::Mat &input, const std::string &filter, int amount);
bool isVideo(const std::string &path);
bool isImage(const std::string &path);
void resetCursor();
void hideCursor();
void showCursor();
void controlCEvent(int sig);