#include "MyGrep.h"

void MyGrep::process_path(const std::string &path, const std::string &pattern) {
    std::filesystem::path filePath{path};
    std::filesystem::directory_entry dirEntry{filePath};
    if (dirEntry.is_regular_file()) {
        process_file(dirEntry, pattern);
    } else if (dirEntry.is_directory()) {
        process_directory(dirEntry, pattern);
    }
}

void MyGrep::process_directory(const std::filesystem::directory_entry &dirEntry, const std::string &pattern) {
    for (const std::filesystem::directory_entry &childEntry: std::filesystem::recursive_directory_iterator(
            dirEntry.path())) {
        //process only regular files
        if (!childEntry.is_regular_file())
            continue;
        process_file(childEntry, pattern);
    }
}

void MyGrep::process_file(const std::filesystem::directory_entry &dirEntry, const std::string &pattern) {
    //get text from file
    std::ifstream file(dirEntry.path());
    std::stringstream fileBuffer;
    fileBuffer << file.rdbuf();
    std::string fileText = fileBuffer.str();
    file.close();

    //find prefix and suffix
    int patternPos = (int) fileText.find(pattern);
    if (patternPos == std::string::npos)
        return;

    std::string prefix = fileText.substr(std::max(patternPos - 3, 0), std::min(patternPos, 3));
    std::string suffix = fileText.substr(patternPos + pattern.length(), 3);

    std::cout << dirEntry.path() << "(" << patternPos << "): "
         << cleanup_str(prefix) << "..." << cleanup_str(suffix) << std::endl;
}

std::string MyGrep::cleanup_str(std::string text) {
    text = replace_char(text, '\t', "\\t");
    text = replace_char(text, '\n', "\\n");
    return text;
}

std::string MyGrep::replace_char(std::string text, char pattern, const std::string &replacement) {
    std::string::size_type pos;
    while ((pos = text.find(pattern)) != std::string::npos) {
        text.replace(pos, 1, replacement);
    }
    return text;
}