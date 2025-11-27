#include <iostream>
#include "ascii.hpp"
#include <unordered_map>
#include <vector>

#define OUTPUT_PATH "/home/mihai/CLionProjects/MAP-ascii-from-image/output/output.png"

const std::string RESET = "\x1b[0m";

// banner text font thing
std::unordered_map<char, std::vector<std::string>> asciiMap = {
    {'A', { {" █████╗ "}, {"██╔══██╗"}, {"███████║"}, {"██╔══██║"}, {"██║  ██║"}, {"╚═╝  ╚═╝"} }},
    {'B', { {"██████╗ "}, {"██╔══██╗"}, {"██████╔╝"}, {"██╔══██╗"}, {"██████╔╝"}, {"╚═════╝ "} }},
    {'C', { {" ██████╗"}, {"██╔════╝"}, {"██║     "}, {"██║     "}, {"╚██████╗"}, {" ╚═════╝"} }},
    {'D', { {"██████╗ "}, {"██╔══██╗"}, {"██║  ██║"}, {"██║  ██║"}, {"██████╔╝"}, {"╚═════╝ "} }},
    {'E', { {"███████╗"}, {"██╔════╝"}, {"█████╗  "}, {"██╔══╝  "}, {"███████╗"}, {"╚══════╝"} }},
    {'F', { {"███████╗"}, {"██╔════╝"}, {"█████╗  "}, {"██╔══╝  "}, {"██║     "}, {"╚═╝     "} }},
    {'G', { {" ██████╗ "}, {"██╔════╝ "}, {"██║  ███╗"}, {"██║   ██║"}, {"╚██████╔╝"}, {" ╚═════╝ "} }},
    {'H', { {"██╗  ██╗"}, {"██║  ██║"}, {"███████║"}, {"██╔══██║"}, {"██║  ██║"}, {"╚═╝  ╚═╝"} }},
    {'I', { {"██╗"}, {"██║"}, {"██║"}, {"██║"}, {"██║"}, {"╚═╝"} }},
    {'J', { {"     ██╗"}, {"     ██║"}, {"     ██║"}, {"██   ██║"}, {"╚█████╔╝"}, {" ╚════╝ "} }},
    {'K', { {"██╗  ██╗"}, {"██║ ██╔╝"}, {"█████╔╝ "}, {"██╔═██╗ "}, {"██║  ██╗"}, {"╚═╝  ╚═╝"} }},
    {'L', { {"██╗     "}, {"██║     "}, {"██║     "}, {"██║     "}, {"███████╗"}, {"╚══════╝"} }},
    {'M', { {"███╗   ███╗"}, {"████╗ ████║"}, {"██╔████╔██║"}, {"██║╚██╔╝██║"}, {"██║ ╚═╝ ██║"}, {"╚═╝     ╚═╝"} }},
    {'N', { {"███╗   ██╗"}, {"████╗  ██║"}, {"██╔██╗ ██║"}, {"██║╚██╗██║"}, {"██║ ╚████║"}, {"╚═╝  ╚═══╝"} }},
    {'O', { {" ██████╗ "}, {"██╔═══██╗"}, {"██║   ██║"}, {"██║   ██║"}, {"╚██████╔╝"}, {" ╚═════╝ "} }},
    {'P', { {"██████╗ "}, {"██╔══██╗"}, {"██████╔╝"}, {"██╔═══╝ "}, {"██║     "}, {"╚═╝     "} }},
    {'Q', { {" ██████╗ "}, {"██╔═══██╗"}, {"██║   ██║"}, {"██║   ██║"}, {"╚██████╔╝"}, {" ╚════██╗"}, {"      ╚═╝"} }},
    {'R', { {"██████╗ "}, {"██╔══██╗"}, {"██████╔╝"}, {"██╔══██╗"}, {"██║  ██║"}, {"╚═╝  ╚═╝"} }},
    {'S', { {"███████╗"}, {"██╔════╝"}, {"███████╗"}, {"╚════██║"}, {"███████║"}, {"╚══════╝"} }},
    {'T', { {"████████╗"}, {"╚══██╔══╝"}, {"   ██║   "}, {"   ██║   "}, {"   ██║   "}, {"   ╚═╝   "} }},
    {'U', { {"██╗   ██╗"}, {"██║   ██║"}, {"██║   ██║"}, {"██║   ██║"}, {"╚██████╔╝"}, {" ╚═════╝ "} }},
    {'V', { {"██╗   ██╗"}, {"██║   ██║"}, {"██║   ██║"}, {"╚██╗ ██╔╝"}, {" ╚████╔╝ "}, {"  ╚═══╝  "} }},
    {'W', { {"██╗    ██╗"}, {"██║    ██║"}, {"██║ █╗ ██║"}, {"██║███╗██║"}, {"╚███╔███╔╝"}, {" ╚══╝╚══╝ "} }},
    {'X', { {"██╗  ██╗"}, {"╚██╗██╔╝"}, {" ╚███╔╝ "}, {" ██╔██╗ "}, {"██╔╝ ██╗"}, {"╚═╝  ╚═╝"} }},
    {'Y', { {"██╗   ██╗"}, {"╚██╗ ██╔╝"}, {" ╚████╔╝ "}, {"  ╚██╔╝  "}, {"   ██║   "}, {"   ╚═╝   "} }},
    {'Z', { {"███████╗"}, {"╚══███╔╝"}, {"  ███╔╝ "}, {" ███╔╝  "}, {"███████╗"}, {"╚══════╝"} }}
};


// map is for actually being able to use the switch with a string
std::unordered_map<std::string, int> filterMap = {
    {"blur", FILTERS::BLUR},
    {"grayscale", FILTERS::GRAYSCALE},
    {"inverse", FILTERS::INVERSE},
    {"contrast", FILTERS::CONTRAST}
};

void applyFilter(cv::Mat &input, const std::string &filter, int amount) {
    switch (filterMap[filter]) {
        case GRAYSCALE:
            input = applyGrayscaleFilter(input);
            break;

        case INVERSE:
            input = applyInverseFilter(input);
            break;

        case BLUR:
            input = applyBlurFilter(input, amount);
            break;

        case CONTRAST:
            input = applyContrastFilter(input, amount);
            break;

        default:
            break;
    }
}

bool isVideo(const std::string &path) {
    cv::VideoCapture cap(path);
    cv::Mat frame1, frame2;

    if (!cap.isOpened())
        return false;

    if (!cap.read(frame1))
        return false; // cannot read the first frame -> not valid

    if (!cap.read(frame2))
        return false; // only one frame -> image

    return true; // at least 2 frames -> video
}

bool isImage(const std::string &path) {
    cv::Mat image = cv::imread(path);

    return !image.empty();
}

// move cursor to top-left
void resetCursor() {
    std::cout << "\033[H" << std::flush;
}

// nice for animation
void hideCursor() {
    std::cout << "\033[?25l" << std::flush;
}

// show cursor again at exit
void showCursor() {
    std::cout << "\033[?25h" << std::flush;
}

// catch ctrl+c if the video animation is stopped
// shows back the cursor and exits alternate terminal
void controlCEvent(int sig) {
    showCursor();
    std::cout << "\033[?1049l";
    exit(1);
}

std::string buildColorString(float R, float G, float B, char character) {
    // make sure the value is in the 0-255 range
    int r = std::clamp(static_cast<int>(R), 0, 255);
    int g = std::clamp(static_cast<int>(G), 0, 255);
    int b = std::clamp(static_cast<int>(B), 0, 255);

    std::ostringstream output;
    output << "\x1b[38;2;" << r << ";" << g << ";" << b << "m" << character << RESET;
    return output.str();
}

cv::Mat applyGrayscaleFilter(const cv::Mat &input) {
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

    // debugging purposes
    if (cv::imwrite(OUTPUT_PATH, final)) {
        std::cout << "Saved image to " << OUTPUT_PATH << std::endl;
    }
    else {
        std::cout << "Failed to save image to " << OUTPUT_PATH << std::endl;
    }

    return final;
}

cv::Mat applyInverseFilter(const cv::Mat &input) {
    cv::Mat final;

    // inverts all bits on all channels
    cv::bitwise_not(input, final);

    // debugging purposes
    if (cv::imwrite(OUTPUT_PATH, final)) {
        std::cout << "Saved image to " << OUTPUT_PATH << std::endl;
    }
    else {
        std::cout << "Failed to save image to " << OUTPUT_PATH << std::endl;
    }

    return final;
}

cv::Mat applyBlurFilter(const cv::Mat &input, int amount) {
    cv::Mat final;

    // replaces each pixel with the average of its neighbors in a 5x5 neighborhood
    cv::blur(input, final, cv::Size(amount, amount));

    // debugging purposes
    if (cv::imwrite(OUTPUT_PATH, final)) {
        std::cout << "Saved image to " << OUTPUT_PATH << std::endl;
    }
    else {
        std::cout << "Failed to save image to " << OUTPUT_PATH << std::endl;
    }

    return final;
}

cv::Mat applyContrastFilter(const cv::Mat &input, int amount) {
    cv::Mat final;

    input.convertTo(final, -1, amount, 0);

    // debugging purposes
    if (cv::imwrite(OUTPUT_PATH, final)) {
        std::cout << "Saved image to " << OUTPUT_PATH << std::endl;
    }
    else {
        std::cout << "Failed to save image to " << OUTPUT_PATH << std::endl;
    }

    return final;
}

cv::Mat resizeImage(cv::Mat &input, float factor) {
    cv::Mat resized;

    cv::resize(input, resized, cv::Size(), factor, factor, cv::INTER_AREA);

    return resized;
}

void computeAverageRGB(const cv::Mat &input, int startWidth, int startHeight, int width, int height, float &Rval, float &Gval, float &Bval) {
    // first calculate the min range to not jump out of the matrix bounds
    int maxWidth = startWidth + width > input.cols ? input.cols : startWidth + width ;
    int maxHeight = startHeight + height > input.rows ? input.rows : startHeight + height ;
    int imageChannels = input.channels();
    unsigned char B, G, R, A;

    Rval = Gval = Bval = 0;

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
            }

            Rval += R;
            Gval += G;
            Bval += B;
        }
    }

    int count = (maxHeight - startHeight) * (maxWidth - startWidth);

    Rval /= count;
    Gval /= count;
    Bval /= count;
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
                    // averageBrightness += 255;
                    continue;
                }
            }

            // brightness formula
            averageBrightness += 0.299*R + 0.587*G + 0.114*B;
        }
    }

    return averageBrightness / (width * height);
}

std::string convertToASCII(cv::Mat &input, std::string charset, int width, int height, bool wantsColor) {
    // this makes sure no portions of the image get cut off due to rounding
    float blockW = static_cast<float>(input.cols) / width;
    float blockH = static_cast<float>(input.rows) / height;
    float R, G, B;
    std::string buf;
    std::string colorBuf;

    // iterates through the user defined width (and height which is calculated based on the width)
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {

            // makes a rectangular selection of the entire pixel map that is
            // blockW x blockH pixels, and maps a character to it
            int startX = static_cast<int>(col * blockW);
            int endX = static_cast<int>((col + 1) * blockW);

            int startY = static_cast<int>(row * blockH);
            int endY = static_cast<int>((row + 1) * blockH);

            float avg = computeAverageBrightness(input, startX, startY, endX - startX, endY - startY);
            int idx = (avg / 255.0f) * (charset.size() - 1);

            if (wantsColor) {
                // for the color output, the average RGB values per each block are needed
                computeAverageRGB(input, startX, startY, endX - startX, endY - startY, R, G, B);
                // ANSI color output
                colorBuf += buildColorString(R, G, B, charset[idx]);
            }
            else {
                // standard character output
                buf += charset[idx]; // output the char, low -> big index means low -> big screen fill (on the default charset)
            }
        }
        wantsColor? colorBuf += "\n" : buf += "\n";
    }

    return wantsColor ? colorBuf : buf;
}

std::string convertToBanner(std::string &input) {
    std::string output;

    for (int line = 0; line < 6; line++) {
        for (char i : input) {
            output += asciiMap[std::toupper(i)][line] + " ";
        }
        output += "\n";
    }

    return output;
}