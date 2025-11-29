#include <iostream>
#include "ascii.hpp"
#include <cxxopts.hpp>
#include <fstream>

void tryPasteToFile(const std::string &output, const cxxopts::ParseResult &result) {
    std::string outputFile = result["output"].as<std::string>();

    if (!outputFile.empty()) {
        std::ofstream file(outputFile);

        if (!file.is_open()) {
            std::cerr << "Failed to open file " << output << std::endl;
            return;
        }

        file << output;
        std::cout << "Sent output to: " << outputFile << "\n" << std::endl;
        file.close();
    }
}

int main(int argc, char *argv[]) {
    bool videoIs; // yoda style naming because the function stole the name
    signal(SIGINT, controlCEvent); // see the ascii.cpp file for explanation

    cxxopts::Options options("MAP-ascii-from-image", "Convert images to ASCII");
    // add command line argument options
    options.add_options()
        ("i,input", "Input a path to the image.", cxxopts::value<std::string>())
        ("o,output", "Output to the specified path.", cxxopts::value<std::string>()->default_value(""))
        ("w,width", "Set the width in characters of the ASCII art.", cxxopts::value<int>()->default_value("120"))
        ("c,charset", "Set the charset to be used. Recommended order is lowest to greatest"
                                    "in terms of fill.", cxxopts::value<std::string>()->default_value("  .,;:=+*oahkbdpzmqAXHNRDQ0M&B8$W#%@"))
        ("f,filter", "Set the filter to be applied before processing the image."
                                   " Options: Blur, Grayscale, Inverse, Contrast.", cxxopts::value<std::string>()->default_value(""))
        ("a,amount", "Amount of blur/contrast for the filters.\nBlur amount: e.g. '5' blurs in a 5x5 "
                     "neighbor grid\nContrast amount: e.g. >1 increases contrast and <1 decreases contrast (turns it into pitch black)", cxxopts::value<int>()->default_value("5"))
        ("l,logo", "Converts the text input into logo art.", cxxopts::value<std::string>()->default_value(""))
        ("r,color", "Enable ANSI color support.")
        ("t,terminal", "Enable terminal output.")
        ("h,help", "Prints this help command!");

    // // first check if the first argument is a file path, no need for -i or --input
    // options.parse_positional({"input"});

    // parse the result of the arguments
    auto result = options.parse(argc, argv);

    // if the help command is invoked / no args are passed, print help and exit
    if (result["help"].as<bool>() || argc == 1) {
        std::cout << options.help() << std::endl;
        return 1;
    }

    // first check if the user wants logo art
    std::string logo = result["logo"].as<std::string>();
    if (logo != "") {
        std::string output = convertToBanner(logo);
        std::cout << output << std::endl;

        tryPasteToFile(output, result);

        return 0;
    }

    // assign the command line arguments to the variables
    std::string inputPath;

    inputPath = result["input"].as<std::string>();

    std::string outputFile = result["output"].as<std::string>();
    std::string charset = result["charset"].as<std::string>();
    std::string filter = result["filter"].as<std::string>();
    int amount = result["amount"].as<int>();
    bool terminalOutput = result["terminal"].as<bool>();
    bool wantsColor = result["color"].as<bool>();

    // check if its a video or image
    cv::Mat inputImage;
    cv::VideoCapture video;

    // first attempt to open as a video
    videoIs = isVideo(inputPath);
    if (videoIs) {
        video = cv::VideoCapture(inputPath);

        // assume the first frame as the input image for the following calcs
        // it gets assigned in the function
        if (!video.read(inputImage)) {
            std::cerr << "Failed to read frame";
            return 1;
        }
    }
    else {
        inputImage = cv::imread(inputPath);

        if (inputImage.empty()) {
            std::cerr << "Failed to load image\n";
            return 1;
        }
    }

    // calculate resolution stuff
    float aspect = 1.0f * inputImage.rows / inputImage.cols;
    int width = std::min(result["width"].as<int>(), inputImage.cols); // makes sure it doesnt go out of bounds
    int height = width * aspect * CHAR_ASPECT;

    // process the video, no extra operations are needed after that
    if (videoIs) {
        playVideoASCII(video, charset, width, height, filter, amount);
        return 0;
    }

    // if no video, process the image
    // apply filters before processing the image
    applyFilter(inputImage, filter, amount);

    // actually process the image
    std::string output = convertToASCII(inputImage, charset, width, height, wantsColor);
    if (terminalOutput) {
        std::cout << output;
    }

    // output to file if the user has specified one
    tryPasteToFile(output, result);

    return 0;
}