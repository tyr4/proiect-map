#include "ascii.hpp"
#include <cxxopts.hpp>
#include <fstream>

#define CHAR_ASPECT 0.5f

int main(int argc, char *argv[]) {
    // enum is for easier switch handling
    // map is for actually being able to use the switch with a string
    enum filters {BLUR = 1, GRAYSCALE, INVERSE, CONTRAST};
    std::unordered_map<std::string, int> filterMap = {
        {"blur", 1},
        {"grayscale", 2},
        {"inverse", 3},
        {"contrast", 4}
    };
    cxxopts::Options options("asciiart", "Convert images to ASCII");
    // add command line argument options
    options.add_options()
        ("i,input", "Input a path to the image.", cxxopts::value<std::string>())
        ("o,output", "Output to the specified path.", cxxopts::value<std::string>()->default_value(""))
        ("w,width", "Set the width in characters of the ASCII art.", cxxopts::value<int>()->default_value("120"))
        ("c,charset", "Set the charset to be used. They have to be entered in order of greatest -> lowest"
                                    "in terms of fill.", cxxopts::value<std::string>()->default_value("@%#W$8B&M0QDRNHXAqmzpdbkhao*+=;:,.  "))
        ("f,filter", "Set the filter to be applied before processing the image."
                                   "Options: ", cxxopts::value<std::string>()->default_value(""))
        ("l,color", "Enable ANSI color support.")
        ("h,help", "Prints this help command!");

    auto result = options.parse(argc, argv);

    if (result["help"].as<bool>() || argc == 1) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    // assign the command line arguments to the variables
    std::string inputFile = result["input"].as<std::string>();
    std::string outputFile = result["output"].as<std::string>();
    std::string charset = result["charset"].as<std::string>();
    std::string filter = result["filter"].as<std::string>();
    cv::Mat inputImage = cv::imread(inputFile, cv::IMREAD_UNCHANGED), editedImage;

    float aspect = 1.0f * inputImage.rows / inputImage.cols;
    int width = std::min(result["width"].as<int>(), inputImage.cols); // makes sure it doesnt go out of bounds
    int height = width * aspect * CHAR_ASPECT;

    if (inputImage.empty()) {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    // apply filters before processing the image
    switch (filterMap[filter]) {
        case GRAYSCALE:
            editedImage = convertToGrayscale(inputImage);
            break;

        default:
            editedImage = inputImage;
            break;

    }

    // actually process the image
    std::string output = convertToASCII(editedImage, charset, width, height);
    // std::cout << output;

    // output to file if the user has specified one
    if (!outputFile.empty()) {
        std::ofstream file(outputFile);

        if (!file.is_open()) {
            std::cerr << "Failed to open file " << output << std::endl;
        }

        file << output;
        std::cout << "Sent output to: " << outputFile << std::endl;
        file.close();
    }


    return 0;
}