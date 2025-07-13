#include <iostream>
#include <sstream>
#include "DataContainer.h"
#include <iomanip>
#include "aproximation.h"


#define timeSIZE 1
#define datapointSIZE 3
#define rotMatrixSIZE 9
#define speedSize 1
#define eulerSize 3

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

	size_t blockSize = timeSIZE + datapointSIZE + rotMatrixSIZE ; //Zusammensetzung eines Datensatzes || Zeitwert + 3 Koordinaten + 9 Rotationsmatrixwerte
	

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
		std::cout << "Speed: " << dataField[i].speed << " ";
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
	T value;
		while (iss >> value) {
			result.push_back(value);
		}
	return result;
}


/**
 * Simplifies the trajectory of data points using the Douglas-Peucker algorithm.
 *
 * @param [in] DouglasPeuckerTolerance The tolerance value that determines the degree of simplification.
 *
 * @details
 * - Converts the (x, y, z) coordinates of each dataPoint in dataField into a vector of Point3D.
 * - Calls the Douglas-Peucker algorithm to reduce the number of points while preserving the overall shape.
 * - The tolerance parameter controls how aggressively points are removed (higher = more simplification).
 * - Rebuilds the dataField vector to contain only the simplified points.
 * - Outputs the number of points before and after simplification, and the tolerance used.
 */

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
	std::cout << "\n Approxiamtionvalues:";
	std::cout << "\n\n-> Using Douglas-Peucker tolerance = " << DouglasPeuckerTolerance;
	std::cout << "\n-> Used points " << dataField.size() << "/" << numDatapoints << "\n\n";
}


/**
 * Converts the 3x3 rotation matrix of each dataPoint in dataField to Euler angles (yaw, pitch, roll).
 *
 * @details
 * - Iterates through all dataPoints and extracts the 3x3 rotation matrix from each.
 * - Calculates the Euler angles (in degrees) using the Tait-Bryan angles (yaw-pitch-roll, ZYX order).
 * - Handles special cases for gimbal lock when the pitch angle is ±90 degrees.
 * - Prints the timestamp and the calculated yaw, pitch, and roll for each dataPoint.
 * - The output angles are in degrees for easier interpretation.
 */

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

		// Store as A, B, C in degrees
		dp.A = yaw * (180.0 / 3.141592653589793238463);
		dp.B = pitch * (180.0 / 3.141592653589793238463);
		dp.C = roll * (180.0 / 3.141592653589793238463);

		std::cout << "Time: " << dp.time
			<< " A: " << dp.A
			<< " B: " << dp.B
			<< " C: " << dp.C << std::endl;
	}
}



/**
 * Calculates the speed for each dataPoint in the dataField vector.
 *
 * @details
 * - Assumes the coordinates (x, y, z) of each dataPoint are given in centimeters.
 * - Computes the Euclidean distance between consecutive points and divides by the time difference (in seconds).
 * - The first dataPoint's speed is calculated using the first and second points.
 * - If the time difference is zero or negative, the speed is set to zero for that point.
 */


void DataContainer::GIVEMETHESPEEEEEEEEED(void)
{
	if (dataField.size() < 2) return;

	// Calculate speed for the first datapoint using the first and second points
	float dt0 = dataField[1].time - dataField[0].time;
	if (dt0 > 0) {
		double dx0 = dataField[1].x - dataField[0].x;
		double dy0 = dataField[1].y - dataField[0].y;
		double dz0 = dataField[1].z - dataField[0].z;
		double distance0 = std::sqrt(dx0 * dx0 + dy0 * dy0 + dz0 * dz0) / 100.0; // convert cm to m
		dataField[0].speed = static_cast<float>(distance0 / dt0);
	}
	else {
		dataField[0].speed = 0;
	}

	for (size_t i = 1; i < dataField.size(); ++i) {
		float dt = dataField[i].time - dataField[i - 1].time;
		if (dt <= 0) {
			dataField[i].speed = 0;
			continue;
		}
		double dx = dataField[i].x - dataField[i - 1].x;
		double dy = dataField[i].y - dataField[i - 1].y;
		double dz = dataField[i].z - dataField[i - 1].z;
		double distance = std::sqrt(dx * dx + dy * dy + dz * dz); 
		dataField[i].speed = static_cast<float>(distance / dt);
	}
}


/**
 * Saves the dataField vector to a KUKA-compatible .src file using the FileHandler's write function.
 *
 * @param [in] dataFileName The original data file name (e.g., "input.csv").
 * @return True if writing was successful, false otherwise.
 *
 * @details
 * - Generates a filename by replacing the .csv extension with .src.
 * - Formats each dataPoint as a KUKA PTP or LIN command: "PTP {X x, Y y, Z z, A a, B b, C c, S 6, T 0} "
 *   (X, Y, Z in mm; A, B, C in degrees; VEL.CP in mm/s ).
 * - Speed is not directly included in the PTP/LIN command, but can be added as a comment or adapted for LIN/VEL if needed.
 * - Writes all lines to the .src file using FileHandler::write.
 */

bool DataContainer::saveAsKukaSrc(const std::string& dataFileName)
{
	// Remove .csv extension and add .src
	std::string outFileName = dataFileName;
	size_t pos = outFileName.rfind(".csv");
	if (pos != std::string::npos)
		outFileName.replace(pos, 4, ".src");
	else
		outFileName += ".src";

	FileHandler outFile(outFileName);

	// Check if file exists and prompt user
	while (outFile.exists()) {
		std::cout << "File \"" << outFileName << "\" already exists. Override? (y/n): ";
		std::string answer;
		std::getline(std::cin, answer);
		if (answer == "y" || answer == "Y") {
			break;
		}
		else if (answer == "n" || answer == "N") {
			std::cout << "Enter new filename (without extension): ";
			std::getline(std::cin, outFileName);
			outFile.setFilename(outFileName);
			outFileName += ".src";
		}
		else {
			std::cout << "Please answer with 'y' or 'n'.\n";
		}
	}

	// Ask user for command type
	std::string kukaCmd;
	while (true) {
		std::cout << "Default is LIN, type \"yes\" to use PTP?";
		std::getline(std::cin, kukaCmd);
		if (kukaCmd == "yes" || kukaCmd == "YES" || kukaCmd == "y") {
			kukaCmd = "PTP";
			break;
		}
		else if (kukaCmd == "") {
			kukaCmd = "LIN";
			break;
		}
		else {
			std::cout << "Enter \"yes\" to use PTP.\n";
		}
	}

	std::ostringstream oss;
	oss << "&ACCESS RVP\n&REL 1\n&PARAM TEMPLATE_NAME = \"" << kukaCmd << "\"\n&PARAM EDITMASK = \"KUKATP\"\n";
	oss << "DEF KUKA_POINTS()\n";
	oss << "   ; X Y Z in mm, A B C in deg, Speed in mm/s\n";
	for (const auto& dp : dataField) {
		if (config.getSpeedMode()==0) {
			oss << "   $VEL.CP = " << std::fixed << std::setprecision(0) << (dp.speed * 1000) << " ; mm/s\n";
		}
		else {
			oss << "   $VEL.CP = " << std::fixed << std::setprecision(0) << config.getManSpeedValue() << " ; mm/s\n";
		}
		oss << "   " << kukaCmd << " {X " << std::fixed << std::setprecision(6) << (dp.x * 10)
			<< ", Y " << (dp.y * 10)
			<< ", Z " << (dp.z * 10)
			<< ", A " << std::setprecision(6) << dp.A
			<< ", B " << dp.B
			<< ", C " << dp.C
			<< "\n";
	}
	oss << "END\n";

	return outFile.write(oss.str());
}



DataContainer::~DataContainer(void)
{
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
