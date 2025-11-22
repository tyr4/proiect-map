#include <opencv2/opencv.hpp>
#include <iostream>
#include <cxxopts.hpp>

cv::Mat convertToGrayscale(const cv::Mat &input) {
    cv::Mat final;

    if (input.channels() == 4) {
        // split channels: B, G, R, A
        std::vector<cv::Mat> channels;
        cv::split(input, channels);

        // convert to grayscale
        cv::Mat gray;
        cv::cvtColor(input, gray, cv::COLOR_BGRA2GRAY);  // works directly!

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

cv::Mat resizeImage(cv::Mat &input, double factor) {
    cv::Mat resized;

    cv::resize(input, resized, cv::Size(), factor, factor, cv::INTER_AREA);

    return resized;
}

int main() {
    std::string inputFile = "/home/mihai/CLionProjects/MAP-ascii-from-image/input/slide1.jpg";
    std::string outputFile = "/home/mihai/CLionProjects/MAP-ascii-from-image/output/output.png";
    cv::Mat inputImage = cv::imread(inputFile, cv::IMREAD_UNCHANGED); // keeps alpha
    cv::Mat editedImage;

    double scale = 0.5;

    if (inputImage.empty()) {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    // editedImage = convertToGrayscale(inputImage);
    editedImage = resizeImage(inputImage, scale);

    cv::imwrite(outputFile, editedImage);

    for (int y = 0; y < editedImage.rows; y++) {
        for (int x = 0; x < editedImage.cols; x++) {
            cv::Vec3b pixel = editedImage.at<cv::Vec3b>(y, x);

            unsigned char B = pixel[0];
            unsigned char G = pixel[1];
            unsigned char R = pixel[2];

            double brightness = 0.299*R + 0.587*G + 0.114*B;

            std::cout << "Pixel (" << x << ", " << y << "): "
                      << "R=" << (int)R << " "
                      << "G=" << (int)G << " "
                      << "B=" << (int)B;
            std::cout << " Brightness: " << brightness << std::endl;
        }
    }

    // std::cout << "Saved grayscale image witwh alpha to " << output_file << std::endl;
    return 0;
}
