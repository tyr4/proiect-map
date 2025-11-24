#include "ascii.hpp"
#include <cxxopts.hpp>

#define CHAR_ASPECT 0.5f

int main(int argc, char *argv[]) {
    cxxopts::Options options("asciiart", "Convert images to ASCII");
    // add command line argument options
    options.add_options()
        ("i,input", "Input a path to the image.", cxxopts::value<std::string>())
        ("o,output", "Output to the specified path.", cxxopts::value<std::string>()->default_value(""))
        ("w,width", "Set the width in characters of the ASCII art.", cxxopts::value<int>()->default_value("120"))
        ("c,charset", "Set the charset to be used. They have to be entered in order of greatest -> lowest"
                      "in terms of fill.", cxxopts::value<std::string>()->default_value("@%#W$8B&M0QDRNHXAqmzpdbkhao*+=;:,.  "))
        ("f,filter", "Set the filter to be applied before processing the image.", cxxopts::value<std::string>()->default_value(""))
        ("l,color", "Enable ANSI color support.")
        ("h,help", "Prints this help command!");

    auto result = options.parse(argc, argv);

    if (result["help"].as<bool>() || argc == 1) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    std::string inputFile = result["input"].as<std::string>();
    std::string outputFile = result["output"].as<std::string>();
    std::string charset = result["charset"].as<std::string>();
    cv::Mat inputImage = cv::imread(inputFile, cv::IMREAD_UNCHANGED), editedImage;

    float aspect = 1.0f * inputImage.rows / inputImage.cols;
    int width = std::min(result["width"].as<int>(), inputImage.cols); // makes sure it doesnt go out of bounds
    int height = width * aspect * CHAR_ASPECT;

    if (inputImage.empty()) {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    // TODO: add switches here for image filters
    editedImage = inputImage;

    printASCII(editedImage, charset, width, height);

    return 0;
}