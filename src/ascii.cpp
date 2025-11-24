#include "ascii.hpp"

cv::Mat convertToGrayscale(const cv::Mat &input) {
    cv::Mat final;

    if (input.channels() == 4) {
        // split channels: B, G, R, A
        std::vector<cv::Mat> channels;
        cv::split(input, channels);

        // convert to grayscale
        cv::Mat gray;
        cv::cvtColor(input, gray, cv::COLOR_BGRA2GRAY);

        // convert back to bgr, while keeping the transparency
        cv::merge(std::vector<cv::Mat>{gray, gray, gray, channels[3]}, final);
    }
    else {
        // convert to grayscale, 1 channel
        cv::cvtColor(input, final, cv::COLOR_BGR2GRAY);
        // convert the grayscale back into bgr values
        cv::cvtColor(final, final, cv::COLOR_GRAY2BGR);
    }

    return final;
}

cv::Mat resizeImage(cv::Mat &input, float factor) {
    cv::Mat resized;

    cv::resize(input, resized, cv::Size(), factor, factor, cv::INTER_AREA);

    return resized;
}

float computeAverageBrightness(const cv::Mat &input, int startWidth, int startHeight, int width, int height) {
    // first calculate the min range to not jump out of the matrix bounds
    int maxWidth = startWidth + width > input.cols ? input.cols : startWidth + width ;
    int maxHeight = startHeight + height > input.rows ? input.rows : startHeight + height ;
    int imageChannels = input.channels();
    float averageBrightness = 0;
    unsigned char B, G, R, A;

    for (int y = startHeight; y < maxHeight; y++) {
        for (int x = startWidth; x < maxWidth; x++) {
            // normal images
            if (imageChannels == 3) {
                cv::Vec3b pixel = input.at<cv::Vec3b>(y, x);

                B = pixel[0];
                G = pixel[1];
                R = pixel[2];
            }
            // check for transparency layer, mainly pngs
            else {
                cv::Vec4b pixel = input.at<cv::Vec4b>(y, x);
                B = pixel[0];
                G = pixel[1];
                R = pixel[2];
                A = pixel[3];

                // if the pixel is (almost) transparent then ignore it (assume its white -> uses a low fill char)
                if (A < 10) {
                    averageBrightness += 255;
                    continue;
                }
            }

            // brightness formula
            averageBrightness += 0.299*R + 0.587*G + 0.114*B;
        }
    }

    return averageBrightness / (width * height);
}

void printASCII(cv::Mat &input, std::string charset, int width, int height) {
    // iterates through the user defined width (and height which is calculated based on the width)
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {

            int startX = col * (input.cols / width);
            int endX = (col + 1) * (input.cols / width);

            int startY = row * (input.rows / height);
            int endY = (row + 1) * (input.rows / height);

            float avg = computeAverageBrightness(input, startX, startY, endX - startX, endY - startY);

            int idx = (avg / 255.0f) * (charset.size() - 1);
            std::cout << charset[idx];
        }
        std::cout << "\n";
    }
}