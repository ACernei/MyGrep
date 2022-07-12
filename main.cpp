#include "MyGrep.h"

#include <iostream>
#include <string>
#include <filesystem>

bool is_valid_path(const std::string &path);

bool is_valid_pattern(const std::string &pattern);

bool is_valid(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    if (!is_valid(argc, argv))
        return 1;

    std::string path = argv[1];
    std::string pattern = argv[2];

    std::cout << "PATH    = " << path << std::endl
         << "PATTERN = " << pattern << std::endl;

    MyGrep::process_path(path, pattern);

    return 0;
}

bool is_valid(int argc, char *argv[]) {
    //validate the input arguments
    if (argc != 3) {
        std::cout << "Usage: PATH PATTERN" << std::endl
             << "Incorrect number of arguments. Exiting..." << std::endl;
        return false;
    }

    if (!is_valid_path(argv[1])) {
        std::cout << "Invalid path!" << std::endl;
        return false;
    }

    if (!is_valid_pattern(argv[2])) {
        std::cout << "Invalid pattern!" << std::endl;
        return false;
    }

    return true;
}

bool is_valid_path(const std::string &path) {
    std::filesystem::path filePath{path};
    return std::filesystem::exists(filePath);
}

bool is_valid_pattern(const std::string &pattern) {
    //set pattern constraints
    return pattern.length() > 0 && pattern.length() <= 128;
}
