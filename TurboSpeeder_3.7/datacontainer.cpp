#include <iostream>
#include <sstream>
#include "DataContainer.h"
#include <iomanip>
#include "aproximation.h"
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
	//std::vector<float> converted = stringToNumber<float>(wholeDataset);
	std::vector<double> converted = stringToDoubleVector(wholeDataset);

	size_t blockSize = timeSIZE + datapointSIZE + rotMatrixSIZE; //Zusammensetzung eines Datensatzes || Zeitwert + 3 Koordinaten + 9 Rotationsmatrixwerte
	

	//dafuq th catch?
	try {
		if (converted.size() % blockSize != 0) {
			throw("Data is incoherent");
		}
	}
	catch(std::string str) {
		std::cout << str << std::endl;
		return false;
	}
	std::cout << std::fixed << std::setprecision(6);
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
			throw("It�s emptyyyyyyyy");
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
		double sumX = 0, sumY = 0, sumZ = 0;
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
		std::cout << std::endl;
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
		std::cout << std::endl;
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



//String in Doublevector umwandeln
std::vector<double> DataContainer::stringToDoubleVector(const std::string& str)
{
	std::vector<double> result;
	std::istringstream iss(str);
	double value;

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
	T value;
	
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

void DataContainer::approximateXYZ(float DouglasPeuckerTolerance) {
	std::vector<Point3D> originalPoints;
	size_t numDatapoints = dataField.size();

	for (size_t i = 0; i < numDatapoints; ++i) {
		originalPoints.push_back({ dataField[i].x, dataField[i].y, dataField[i].z, i });
	}

	std::vector<Point3D> simplified;
	douglasPeuckerRecursive(originalPoints, DouglasPeuckerTolerance, simplified);

	std::vector<dataPoint> newData;
	for (const auto& pt : simplified) {
		newData.push_back(dataField[pt.index]);
	}

	dataField = std::move(newData);

	//Ouput
	std::cout << "\n\n__________________________________________________________________";
	std::cout << "\nAusgabe der Approxiamtion:";
	std::cout << "\n\n-> Verwendete Douglas-Peucker Toleranz = " << DouglasPeuckerTolerance;
	std::cout << "\n-> Verwendete Punkte " << dataField.size() << "/" << numDatapoints << "\n\n";
}

void DataContainer::rotationMatrixToEulerAngels(void)
{

	for (auto& dp : dataField) {
		double r00 = dp.rotMatrix[0];
		double r01 = dp.rotMatrix[1];
		double r02 = dp.rotMatrix[2];
		double r10 = dp.rotMatrix[3];
		double r11 = dp.rotMatrix[4];
		double r12 = dp.rotMatrix[5];
		double r20 = dp.rotMatrix[6];
		double r21 = dp.rotMatrix[7];
		double r22 = dp.rotMatrix[8];


		double yaw, pitch, roll;

		// Pitch (y-Achse)
		if (r20 < 1.0f) {
			if (20 > -1.0f) {
				pitch = std::asin(-r20);
				roll = std::atan2(r21, r22);
				yaw = std::atan2(r10, r00);
			}
			else {
				// r20 == -1
				pitch = static_cast<float>(0.0);
				roll = -std::atan2(-r12, r11);
				yaw = 0.0f;
			}
		}
		else {
			//r20  == 1
			pitch = -static_cast<float>(0.0);
			roll = std::atan2(-r12, r11);
			yaw = 0.0f;
		}

		std::setprecision(8);
		std::cout << "Time: " << dp.time
			<< " Yaw: " << yaw * (180.0 / 3.141592653589793238463)
			<< " Pitch: " << pitch * (180.0 / 3.141592653589793238463)
			<< " Roll: " << roll * (180.0 / 3.141592653589793238463) << std::endl;
	}
}



DataContainer::~DataContainer(void)
{
}
