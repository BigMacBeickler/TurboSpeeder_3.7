#include <fstream>
#include <filesystem>
#include <sstream>
#include <valarray>
#include <vector>
#include "FileHandler.h"

//weniger text
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

/**
 * Reads the entire content of the file specified by the 'filename' member.
 *
 * @return A string containing the full content of the file.
 *         If the file cannot be opened, returns "Fehler".
 */

std::string FileHandler::read() const {
    std::ifstream file(filename);
    if (!file.is_open()) return "Fehler";
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    file.close();
    return content;
}

std::string FileHandler::getFilename() const {
    return filename;
}

void FileHandler::setFilename(const std::string& newName) {
    filename = newName;
}

