#include <iostream>
#include <sstream>
#include "datacontainer.h"
#include <iomanip>

dataContainer::dataContainer(void)
{
}


// wie bekomm ich am besten die daten aus dem String in den vektor?
bool dataContainer::getData(FileHandler &file)
{
	std::string wholeDataset;
	wholeDataset = file.read();
	std::vector converted = stringToFloatVector(wholeDataset);

	size_t blockSize = 1 + 3 + 9; //Zusammensetzung eines Datensatzes
	if(converted.size() % blockSize != 0){
		return false;			//throw std::runtime_error?
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
	std::cout << this->dataField.size() << "\n";
	return true;
}

bool dataContainer::getConfigFile(FileHandler& file)
{
	std::cout << "getconfig!\n";
	return true;
}

bool dataContainer::getConfigManual()
{
	std::cout << "Weite des gleitenden Mittelwertes angeben. \n";
	std::string movingAverageString;
	std::getline(std::cin, movingAverageString);
	try {
		this->config.movingAverageRange = std::stoi(movingAverageString);
	}
	catch (std::invalid_argument) {
		std::cout << "Das war keine Zahl";
		return false;
	}
	std::cout << this->config.movingAverageRange << "\n";

	std::cout << "Toleranz des Douglas-Peucker-Filters angeben. \n";
	std::string douglasPeuckerString;
	std::getline(std::cin, douglasPeuckerString);
	try {
		this->config.douglasPeuckerTolerance = std::stoi(douglasPeuckerString);
	}
	catch (std::invalid_argument) {
		std::cout << "Das war keine Zahl";
		return false;
	}
	std::cout << this->config.douglasPeuckerTolerance << "\n";

	std::cout << "Weite des gleitenden Mittelwertes angeben. \n";
	std::string leichtzuersetzen;
	std::getline(std::cin, leichtzuersetzen);
	try {
		this->config.vlleinszuviel = std::stoi(leichtzuersetzen);
	}
	catch (std::invalid_argument) {
		std::cout << "Das war keine Zahl";
		return false;
	}
	std::cout << this->config.vlleinszuviel << "\n";
	return true;
}

bool dataContainer::saveConfig()
{
	return false;
}

void dataContainer::printCoordinates()
{
	std::cout << std::fixed << std::setprecision(6);
	for (size_t i = 0; i < dataField.size(); i++) {
		std::cout << "Time: " << dataField[i].time << " ";
		std::cout << "X: " << dataField[i].x << " ";
		std::cout << "Y: " << dataField[i].y << " ";
		std::cout << "Z: " << dataField[i].z << " ";
	}
}

void dataContainer::printRotMatrix()
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
std::vector<float> dataContainer::stringToFloatVector(const std::string& str) 
{
	std::vector<float> result;
	std::istringstream iss(str);
	float value;

	while (iss >> value) {
		result.push_back(value);
	}
	return result;
}

dataContainer::~dataContainer(void)
{
}
