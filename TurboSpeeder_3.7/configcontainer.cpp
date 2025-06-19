#include <iostream>
#include <sstream>

#include "configcontainer.h"

bool ConfigContainer::getConfigFromFile(FileHandler& file)
{
	return false;
}

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


	std::cout << "Toleranz des Douglas-Peucker-Filters angeben. Keine Eingabe zum Überspringen" << std::endl;
	std::getline(std::cin, readstring);
	try {
		this->fDouglasPeuckerTolerance = std::stof(readstring);
	}
	catch (std::invalid_argument const& inv) {
		std::cout << "Das war keine Zahl" << inv.what() << std::endl;
		return false;
	}


	//testen!!

	//std::cout << "Weite des gleitenden Mittelwertes angeben. Keine Eingabe zum Überspringen" << std::endl;
	//std::getline(std::cin, readstring);
	//if (!readstring.empty()) {
	//	try {
	//		//this->iModus = std::stoi(readstring);
	//		this->setModus(std::stoi(readstring));
	//	}
	//	catch (std::invalid_argument const& inv) {
	//		std::cout << "Das war keine Zahl " << inv.what() << std::endl;
	//		return false;
	//	}
	//	std::cout << this->getModus() << std::endl;
	//	return true;
	//}
	//else {
	//	this->setModus(1);
	//}
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
	std::cout << "Blocksizemode " << getBlockSize() << "\n" << std::endl;
	std::cout << "Startpunkt " << getManStartValue() << "\n" << std::endl;
	std::cout << "Stopppunkt " << getManStopValue() << "\n" << std::endl;
	std::cout << "Betriebsart " << getModus() << "\n" << std::endl;
	std::cout << "Filterbreite " << getMovingAverageRange() << "\n" << std::endl;
	std::cout << "Approximation " << getDouglasPeuckerTolerance() << "\n" << std::endl;
	//std::cout << "Name " << getName() << "\n" << std::endl;
}


//Needs to be implemented
//bool ConfigContainer::getConfigFromFile(FileHandler& file)
//{
//	std::string wholeConfigset;
//	wholeConfigset = file.read();
//
//	// Parse the string line by line
//	std::istringstream iss(wholeConfigset);
//	std::string line;
//
//	while (std::getline(iss, line)) 
//		{
//		std::istringstream lineStream(line);
//		std::string key, valueStr;
//
//		if (std::getline(lineStream, key, ':') && std::getline(lineStream, valueStr)) {
//			// Trim leading whitespace from valueStr
//			size_t start = valueStr.find_first_not_of(" \t");
//			valueStr = (start != std::string::npos) ? valueStr.substr(start) : "";
//
//			std::istringstream valueStream(valueStr);
//
//			if (key == "name") {
//				valueStream >> this->sName;
//			}
//			else if (key == "geschwindigkeitsmodus") {
//				valueStream >> this->iSpeedMode;
//			}
//			else if (key == "geschwindigkeit") {
//				valueStream >> this->fManSpeedValue;
//			}
//			else if (key == "orientierung") {
//				valueStream >> this->iOrientationMode;
//			}
//			else if (key == "blocksizemode") {
//				valueStream >> this->iBlockSize;
//			}
//			else if (key == "startpunkt") {
//				valueStream >> this->iManStartValue;
//			}
//			else if (key == "stopppunkt") {
//				valueStream >> this->iManStopValue;
//			}
//			else if (key == "betriebsart") {
//				valueStream >> this->iModus;
//			}
//			else if (key == "filterbreite") {
//				valueStream >> this->iMovingAverageRange;
//			}
//			else if (key == "approximation") {
//				valueStream >> this->iDouglasPeuckerTolerance;
//			}
//			else {
//				std::cerr << "Unknown key: " << key << std::endl;
//			}
//		}
//	}
//
//	std::cout << "got config!\n";
//	return true;
//}


//Needs to be implemented
//bool ConfigContainer::saveConfig(std::string configname)
//{
//	setName(configname);
//	std::string datatosave;
//	FileHandler saveFile(getName());
//	std::stringstream ss(datatosave);
//	ss << "geschwindigkeitsmodus: " << getSpeedMode() << "\n";
//	ss << "geschwindigkeit: " << getManSpeedValue() << "\n";
//	ss << "orientierung " << getOrientationMode() << "\n";
//	ss << "blocksizemode " << getBlockSize() << "\n";
//	ss << "startpunkt " << getManStartValue() << "\n";
//	ss << "stopppunkt " << getManStopValue() << "\n";
//	ss << "betriebsart " << getModus() << "\n";
//	ss << "filterbreite " << getMovingAverageRange() << "\n";
//	ss << "approximation " << getDouglasPeuckerTolerance() << "\n";
//	saveFile.write(datatosave);
//
//	//if (saveFile.exists() == true) {
//	//	std::cout << "Datei überschreiben?\n";
//	//	std::string answear;
//	//	std::cin >> answear;
//	//	if (answear == "yes") {
//	//		saveFile.writeConfig(*this);
//	//	}
//	//}
//	return true;
//}

// Private Setters
void ConfigContainer::setName(const std::string& name) {
	sName = name;
}

void ConfigContainer::setMovingAverageRange(int range) {
	iMovingAverageRange = range;
}

void ConfigContainer::setDouglasPeuckerTolerance(float tolerance) {
	fDouglasPeuckerTolerance = tolerance;
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

float ConfigContainer::getDouglasPeuckerTolerance() const {
	return fDouglasPeuckerTolerance;
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
