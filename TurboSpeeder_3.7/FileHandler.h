#pragma once

#include <string>
#include <valarray>
#include "configcontainer.h"

class FileHandler {
private:
    std::string filename;

public:
    FileHandler(const std::string& fname);
    bool exists() const;
    bool writeConfig(const ConfigContainer) const;
    bool append(const std::string& content) const;
    std::string read() const;
    bool remove() const;
    std::string getFilename() const;
    void setFilename(const std::string& newName);
    std::valarray<float> readCSV() const;

};

