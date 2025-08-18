#include <fstream>
#include <filesystem>
#include <sstream>
#include <valarray>
#include <vector>
#include "FileHandler.h"

//weniger text
namespace fs = std::filesystem;

/********************************************************************
@brief    : Constructor that initializes the FileHandler with a filename.
@param    : fname - The name of the file to be handled.
@return   : None.
*********************************************************************/
FileHandler::FileHandler(const std::string& fname) : filename(fname) {}

/********************************************************************
@brief    : Checks whether the file exists in the filesystem.
@param    : None.
@return   : True if the file exists; false otherwise.
*********************************************************************/
bool FileHandler::exists() const {
    return fs::exists(filename);
}

/********************************************************************
@brief    : Writes the given content to the file, overwriting any existing content.
@param    : content - The string content to write to the file.
@return   : True if the file was successfully written; false otherwise.
*********************************************************************/
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

 /********************************************************************
 @brief    : Reads the entire content of the file.
 @param    : None.
 @return   : A string containing the file content; returns "Fehler" if the file cannot be opened.
 *********************************************************************/
std::string FileHandler::read() const {
    std::ifstream file(filename);
    if (!file.is_open()) return "Fehler";
    std::string content((std::istreambuf_iterator<char>(file)),
                         std::istreambuf_iterator<char>());
    file.close();
    return content;
}

/********************************************************************
@brief    : Retrieves the current filename associated with the FileHandler.
@param    : None.
@return   : The filename as a string.
*********************************************************************/
std::string FileHandler::getFilename() const {
    return filename;
}

/********************************************************************
@brief    : Sets a new filename for the FileHandler.
@param    : newName - The new filename to assign.
@return   : None.
*********************************************************************/
void FileHandler::setFilename(const std::string& newName) {
    filename = newName;
}

