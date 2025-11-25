#include "ascii.hpp"
#include <cxxopts.hpp>
#include <fstream>

constexpr float CHAR_ASPECT = 0.5f;

// enum is for easier switch handling
enum FILTERS {BLUR = 1, GRAYSCALE, INVERSE, CONTRAST};

int main(int argc, char *argv[]) {
    // map is for actually being able to use the switch with a string
    std::unordered_map<std::string, int> filterMap = {
        {"blur", FILTERS::BLUR},
        {"grayscale", FILTERS::GRAYSCALE},
        {"inverse", FILTERS::INVERSE},
        {"contrast", FILTERS::CONTRAST}
    };
    cxxopts::Options options("MAP-ascii-from-image", "Convert images to ASCII");
    // add command line argument options
    options.add_options()
        ("i,input", "Input a path to the image.", cxxopts::value<std::string>())
        ("o,output", "Output to the specified path.", cxxopts::value<std::string>()->default_value(""))
        ("w,width", "Set the width in characters of the ASCII art.", cxxopts::value<int>()->default_value("120"))
        ("c,charset", "Set the charset to be used. They have to be entered in order of greatest -> lowest"
                                    "in terms of fill.", cxxopts::value<std::string>()->default_value("@%#W$8B&M0QDRNHXAqmzpdbkhao*+=;:,.  "))
        ("f,filter", "Set the filter to be applied before processing the image."
                                   " Options: Blur, Grayscale, Inverse, Contrast.", cxxopts::value<std::string>()->default_value(""))
        ("a,amount", "Amount of blur/contrast for the filters.\nBlur amount: e.g. '5' blurs in a 5x5 "
                     "neighbor grid\nContrast amount: e.g. >1 increases contrast and <1 decreases contrast (turns it into pitch black)", cxxopts::value<int>()->default_value("5"))
        ("l,color", "Enable ANSI color support.")
        ("t,terminal", "Enable terminal output.")
        ("h,help", "Prints this help command!");

    // first check if the first argument is a file path, no need for -i or --input
    options.parse_positional({"input"});

    auto result = options.parse(argc, argv);

    // if the help command is invoked or no args are passed, print it and exit
    if (result["help"].as<bool>() || argc == 1) {
        std::cout << options.help() << std::endl;
        return 0;
    }

    // assign the command line arguments to the variables
    std::string inputFile;

    if (result.count("input")) {
        inputFile = result["input"].as<std::string>();
        std::cout << "Input file: " << inputFile << "\n";
    }
    else {
        std::cerr << "No input file specified\n";
        return 0;
    }

    std::string outputFile = result["output"].as<std::string>();
    std::string charset = result["charset"].as<std::string>();
    std::string filter = result["filter"].as<std::string>();
    cv::Mat inputImage = cv::imread(inputFile, cv::IMREAD_UNCHANGED), editedImage;

    float aspect = 1.0f * inputImage.rows / inputImage.cols;
    int width = std::min(result["width"].as<int>(), inputImage.cols); // makes sure it doesnt go out of bounds
    int height = width * aspect * CHAR_ASPECT;
    int amount = result["amount"].as<int>();
    bool terminalOutput = result["terminal"].as<bool>();

    if (inputImage.empty()) {
        std::cerr << "Failed to load image\n";
        return 1;
    }

    // apply filters before processing the image
    switch (filterMap[filter]) {
        case GRAYSCALE:
            editedImage = applyGrayscaleFilter(inputImage);
            break;

        case INVERSE:
            editedImage = applyInverseFilter(inputImage);
            break;

        case BLUR:
            editedImage = applyBlurFilter(inputImage, amount);
            break;

        case CONTRAST:
            editedImage = applyContrastFilter(inputImage, amount);
            break;

        default:
            editedImage = inputImage;
            break;
    }

    // actually process the image
    std::string output = convertToASCII(editedImage, charset, width, height, result["color"].as<bool>());
    if (terminalOutput) {
        std::cout << output;
    }

    // output to file if the user has specified one
    if (!outputFile.empty()) {
        std::ofstream file(outputFile);

        if (!file.is_open()) {
            std::cerr << "Failed to open file " << output << std::endl;
        }
        else {
            file << output;
            std::cout << "Sent output to: " << outputFile << std::endl;
            file.close();
        }
    }

    return 0;
}