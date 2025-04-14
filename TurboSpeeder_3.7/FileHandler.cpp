#include <fstream>
#include <filesystem>
#include <sstream>
#include <valarray>
#include <vector>
#include "FileHandler.h"


namespace fs = std::filesystem;

FileHandler::FileHandler(const std::string& fname) : filename(fname) {}

bool FileHandler::exists() const {
    return fs::exists(filename);
}

bool FileHandler::write(const std::string& content) const {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open()) return false;
    file << content;
    file.close();
    return true;
}

//bool FileHandler::append(const std::string& content) const {
//    std::ofstream file(filename, std::ios::out | std::ios::app);
//    if (!file.is_open()) return false;
//    file << content;
//    file.close();
//    return true;
//}

std::string FileHandler::read() const {
    std::ifstream file(filename);
    if (!file.is_open()) return "Fehler";
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    file.close();
    return content;
}

//bool FileHandler::remove() const {
//    if (exists()) {
//        return fs::remove(filename);
//    }
//    return false;
//}

std::string FileHandler::getFilename() const {
    return filename;
}

void FileHandler::setFilename(const std::string& newName) {
    filename = newName;
}

//std::valarray<float> FileHandler::readCSV() const {
//    std::ifstream file(filename);
//    if (!file.is_open()) return std::valarray<float>();
//
//    std::vector<float> values;
//    std::string line;
//    while (std::getline(file, line)) {
//        std::stringstream ss(line);
//        std::string value;
//        while (std::getline(ss, value, ',')) {
//            values.push_back(std::stof(value));
//        }
//    }
//    file.close();
//
//    return std::valarray<float>(values.data(), values.size());
//}