#include <iostream>
#include "datacontainer.h"

dataContainer::dataContainer(void)
{
}

void dataPoint::setDatapoints()
{
}


// wie bekomm ich am besten die daten aus dem String in den vektor?
bool dataContainer::getData(FileHandler &file)
{
	std::string wholeDataset;
	wholeDataset = file.read();
	size_t blockSize = 1 + 3 + 9; //Zusammensetzung eines Datensatzes
	std::cout << wholeDataset[wholeDataset.size()-2] << "\n";
	if(wholeDataset.size() % blockSize != 0){
		return false;			//throw std::runtime_error?
	}
	std::cout << "hier 2!\n";
	for (size_t i = 0; i < wholeDataset.size(); i += blockSize) {
		dataPoint dp;
		dp.time = wholeDataset[i];
		dp.x = wholeDataset[i + 1];
		dp.y = wholeDataset[i + 2];
		dp.z = wholeDataset[i + 3];
		for (int j = 0; j < 9; ++j) {
			dp.rotMatrix[j] = wholeDataset[i + 4 + j];
		}
		this->dataField.push_back(dp);
	}
	std::cout << this->dataField.size() << "\n";
	return true;
}

bool dataContainer::getConfigFile(FileHandler file)
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

dataContainer::~dataContainer(void)
{
}
