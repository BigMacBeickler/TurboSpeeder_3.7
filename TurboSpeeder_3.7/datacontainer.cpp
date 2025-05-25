#include <iostream>
#include <sstream>
#include "DataContainer.h"
#include <iomanip>
#define timeSIZE 1
#define datapointSIZE 3
#define rotMatrixSIZE 9




DataContainer::DataContainer(void)
{
}


/**
 * Reads and parses numerical data from a file into the internal data structure.
 *
 * @param [in] file A reference to a FileHandler object used to read the raw data as a string.
 * @return True if data is successfully parsed and loaded; false if the data format is invalid.
 *
 * @details
 * The function performs the following steps:
 * - Reads the entire content of the file into a string.
 * - Converts the string into a vector of floats using `stringToNumber<float>()`.
 * - Verifies that the number of floats is a multiple of the expected block size (13 values per dataset).
 * - Parses each block into a `dataPoint` struct consisting of:
 *   - 1 time value
 *   - 3 position values (x, y, z)
 *   - 9 rotation matrix values
 * - Adds each parsed `dataPoint` to the `dataField` vector.
 * - Outputs the number of datasets successfully read.
 */

// wie bekomm ich am besten die daten aus dem String in den vektor?
bool DataContainer::getData(FileHandler &file)
{
	std::string wholeDataset;
	wholeDataset = file.read();

	//std::vector converted = stringToFloatVector(wholeDataset);
	std::vector converted = stringToNumber<float>(wholeDataset);

	size_t blockSize = timeSIZE + datapointSIZE + rotMatrixSIZE; //Zusammensetzung eines Datensatzes || Zeitwert + 3 Koordinaten + 9 Rotationsmatrixwerte
	
	try {
		if (converted.size() % blockSize != 0) {
			throw("Data is incoherent");
		}
	}
	catch(std::string str) {
		std::cout << str << std::endl;
		return false;
	}

	for (size_t i = 0; i < converted.size(); i += blockSize) {
		dataPoint dp;
		dp.time = converted[i];
		dp.x = converted[i + 1];
		dp.y = converted[i + 2];
		dp.z = converted[i + 3];
		for (int j = 0; j < 9; ++j) {
			dp.rotMatrix[j] = converted[i + 4 + j];
		}
		this->dataField.push_back(dp);
	}
	std::cout << "Read " << this->dataField.size() << " datasets " << std::endl;
	return true;
}

bool DataContainer::deleteEntry(const int n){
	try {
		if (this->dataField.begin() >= this->dataField.end()) {
			throw("It´s emptyyyyyyyy");
		}
	}
	catch (std::string str) {
		std::cout << str << " \n";
		return false;
	}
	
	this->dataField.erase(this->dataField.begin() + n);
	return true;
}

bool DataContainer::averageFilter(const int n)
{
	if (this->dataField.size() < n || n == 0) {
		std::cout << "Entry Invalid.\n";
		return false;
	}
	for (size_t i = 0; i < this->dataField.size() - n; ++i) {
		float sumX = 0, sumY = 0, sumZ = 0;
		for (int j = 0; j < n; ++j) {
			sumX += this->dataField[i + j].x;
			sumY += this->dataField[i + j].y;
			sumZ += this->dataField[i + j].z;
		}
		this->dataField[i].x = sumX / n;
		this->dataField[i].y = sumY / n;
		this->dataField[i].z = sumZ / n;
	}
	return true;
}


//const because only read, no write
void DataContainer::printCoordinates() const
{
	std::cout << std::fixed << std::setprecision(6);
	for (size_t i = 0; i < dataField.size(); i++) {
		std::cout << "Time: " << dataField[i].time << " ";
		std::cout << "X: " << dataField[i].x << " ";
		std::cout << "Y: " << dataField[i].y << " ";
		std::cout << "Z: " << dataField[i].z << " ";
	}
}

//const because only read, no write
// a bit ugly :3
void DataContainer::printRotMatrix() const
{
	std::cout << std::fixed << std::setprecision(6);
	for (size_t i = 0; i < dataField.size(); i++) {
		std::cout << "Rx1: " << dataField[i].rotMatrix[0] << " ";
		std::cout << "Rx2: " << dataField[i].rotMatrix[1] << " ";
		std::cout << "Rx3: " << dataField[i].rotMatrix[2] << " ";
		std::cout << "Ry1: " << dataField[i].rotMatrix[3] << " ";
		std::cout << "Ry2: " << dataField[i].rotMatrix[4] << " ";
		std::cout << "Ry3: " << dataField[i].rotMatrix[5] << " ";
		std::cout << "Rz1: " << dataField[i].rotMatrix[6] << " ";
		std::cout << "Rz2: " << dataField[i].rotMatrix[7] << " ";
		std::cout << "Rz3: " << dataField[i].rotMatrix[8] << " ";
	}
}


//String in Floatvector umwandeln
std::vector<float> DataContainer::stringToFloatVector(const std::string& str) 
{
	std::vector<float> result;
	std::istringstream iss(str);
	float value;

	while (iss >> value) {
		result.push_back(value);
	}
	return result;
}


// Transform String to whatever, muahhaaha!! 
/* @brief Template function to convert whitespace-seperated String to vector of format T
* 
* @Tparam T type of data
* @param [in]	str		const string with data to converse
* @return result verctor with converted data or empty vector if an io error occured
* 
* @detail
* tries to stream string in valie of T, throws failbit if io error occurs (e.g. letter instead of number)
* catches failbit and cancels the operation
* returns result vector
*/

template <typename T>
std::vector<T> DataContainer::stringToNumber(const std::string& str) {
	std::vector<T> result;
	std::istringstream iss(str);
	//bhiss.exceptions(std::istringstream::failbit);
	float value;
	
//	try {
		while (iss >> value) {
			result.push_back(value);
		}
//	}
	//catch (const std::exception& e) {// catches the failbit that was set from the iss stream operation
	//	std::cerr << "Wrong format " << e.what() << std::endl;//e.what() shows the exact error that was set
	//	result.clear();
	//	return result;
	//}
	return result;
}

DataContainer::~DataContainer(void)
{
}
