#include <iostream>
#include <sstream>
#include "FileHandler.h"
#include "configcontainer.h"

bool ConfigContainer::getConfigManual()
{
	std::string readstring;

	
	std::cout << "Weite des gleitenden Mittelwertes angeben. Keine Eingabe zum Überspringen \n";
	std::getline(std::cin, readstring);
	try {
		this->iMovingAverageRange = std::stoi(readstring);
	}
	catch (std::invalid_argument const& inv) {
		std::cout << "Das war keine Zahl" << inv.what() << std::endl;
		return false;
	}
	std::cout << this->iMovingAverageRange << std::endl;


	std::cout << "Toleranz des Douglas-Peucker-Filters angeben. Keine Eingabe zum Überspringen" << std::endl;
	std::getline(std::cin, readstring);
	try {
		this->iDouglasPeuckerTolerance = std::stoi(readstring);
	}
	catch (std::invalid_argument const& inv) {
		std::cout << "Das war keine Zahl" << inv.what() << std::endl;
		return false;
	}
	std::cout << this->iDouglasPeuckerTolerance << std::endl;


	//testen!!

	std::cout << "Weite des gleitenden Mittelwertes angeben. Keine Eingabe zum Überspringen" << std::endl;
	std::getline(std::cin, readstring);
	if (!readstring.empty()) {
		try {
			//this->iModus = std::stoi(readstring);
			this->setModus(std::stoi(readstring));
		}
		catch (std::invalid_argument const& inv) {
			std::cout << "Das war keine Zahl " << inv.what() << std::endl;
			return false;
		}
		std::cout << this->getModus() << std::endl;
		return true;
	}
	else {
		this->setModus(1);
	}
}

//Hier weiter machen
//Orientierung verstehen und mit einlesen.
//Todo: Berechnungen für Geschwindigkeit und Orientierung.
//Umwandlung in Euler-Winkel??

void ConfigContainer::printConfig() const
{
	std::cout << "Name " << getName() << "\n" << std::endl;
	std::cout << "SpeedMode " << getSpeedMode() << "\n" << std::endl;
	std::cout << "Speed " << getManSpeedValue() << "\n" << std::endl;
	std::cout << "Orientationmode " << getOrientationMode() << "\n" << std::endl;
	std::cout << "Name " << getName() << "\n" << std::endl;
	std::cout << "Name " << getName() << "\n" << std::endl;
	std::cout << "Name " << getName() << "\n" << std::endl;
	std::cout << "Name " << getName() << "\n" << std::endl;
	std::cout << "Name " << getName() << "\n" << std::endl;
	std::cout << "Name " << getName() << "\n" << std::endl;
	std::cout << "Name " << getName() << "\n" << std::endl;
}


//Needs to be implemented
bool ConfigContainer::getConfigFromFile(FileHandler& file)
{
	std::string wholeConfigset;
	wholeConfigset = file.read();

	// Parse the string line by line
	std::istringstream iss(wholeConfigset);
	std::string line;

	while (std::getline(iss, line)) 
		{
		std::istringstream lineStream(line);
		std::string key, valueStr;

		if (std::getline(lineStream, key, ':') && std::getline(lineStream, valueStr)) {
			// Trim leading whitespace from valueStr
			size_t start = valueStr.find_first_not_of(" \t");
			valueStr = (start != std::string::npos) ? valueStr.substr(start) : "";

			std::istringstream valueStream(valueStr);

			if (key == "name") {
				valueStream >> this->sName;
			}
			else if (key == "geschwindigkeitsmodus") {
				valueStream >> this->iSpeedMode;
			}
			else if (key == "geschwindigkeit") {
				valueStream >> this->fManSpeedValue;
			}
			else if (key == "orientierung") {
				valueStream >> this->iOrientationMode;
			}
			else if (key == "blocksizemode") {
				valueStream >> this->iBlockSize;
			}
			else if (key == "startpunkt") {
				valueStream >> this->iManStartValue;
			}
			else if (key == "stopppunkt") {
				valueStream >> this->iManStopValue;
			}
			else if (key == "betriebsart") {
				valueStream >> this->iModus;
			}
			else if (key == "filterbreite") {
				valueStream >> this->iMovingAverageRange;
			}
			else if (key == "approximation") {
				valueStream >> this->iDouglasPeuckerTolerance;
			}
			else {
				std::cerr << "Unknown key: " << key << std::endl;
			}
		}
	}

	std::cout << "got config!\n";
	return true;
}


//Needs to be implemented
bool ConfigContainer::saveConfig(std::string configname)
{
	return false;
}

// Private Setters
void ConfigContainer::setName(const std::string& name) {
	sName = name;
}

void ConfigContainer::setMovingAverageRange(int range) {
	iMovingAverageRange = range;
}

void ConfigContainer::setDouglasPeuckerTolerance(int tolerance) {
	iDouglasPeuckerTolerance = tolerance;
}

void ConfigContainer::setSpeedMode(int mode) {
	iSpeedMode = mode;
}

void ConfigContainer::setManSpeedValue(float value) {
	fManSpeedValue = value;
}

void ConfigContainer::setOrientationMode(int mode) {
	iOrientationMode = mode;
}

void ConfigContainer::setManOrientationValues(float x, float y, float z) {
	fManOrientationValues = { x, y, z };
}

void ConfigContainer::setBlockSize(int size) {
	iBlockSize = size;
}

void ConfigContainer::setModus(int modus) {
	iModus = modus;
}

void ConfigContainer::setManStartValue(int value) {
	iManStartValue = value;
}

void ConfigContainer::setManStopValue(int value) {
	iManStopValue = value;
}


// Public Getters
std::string ConfigContainer::getName() const {
	return sName;
}

int ConfigContainer::getMovingAverageRange() const {
	return iMovingAverageRange;
}

int ConfigContainer::getDouglasPeuckerTolerance() const {
	return iDouglasPeuckerTolerance;
}

int ConfigContainer::getSpeedMode() const {
	return iSpeedMode;
}

float ConfigContainer::getManSpeedValue() const {
	return fManSpeedValue;
}

int ConfigContainer::getOrientationMode() const {
	return iOrientationMode;
}

std::array<float, 3> ConfigContainer::getManOrientationValues() const {
	return fManOrientationValues;
}

int ConfigContainer::getBlockSize() const {
	return iBlockSize;
}

int ConfigContainer::getModus() const {
	return iModus;
}

int ConfigContainer::getManStartValue() const {
	return iManStartValue;
}

int ConfigContainer::getManStopValue() const {
	return iManStopValue;
}
