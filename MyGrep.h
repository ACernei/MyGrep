#ifndef MYGREP_MYGREP_H
#define MYGREP_MYGREP_H

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>


class MyGrep {
    static void process_file(const std::filesystem::directory_entry &dirEntry, const std::string &pattern);

    static void process_directory(const std::filesystem::directory_entry &dirEntry, const std::string &pattern);

    static std::string replace_char(std::string text, char pattern, const std::string &replacement);

    static std::string cleanup_str(std::string text);
public:
    static void process_path(const std::string &path, const std::string &pattern);
};


#endif //MYGREP_MYGREP_H
