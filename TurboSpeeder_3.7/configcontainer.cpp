#include <iostream>
#include <sstream>
#include <iomanip>

#include "configcontainer.h"


bool ConfigContainer::getConfigManual()
{
	std::string answer;
	this->setManConfig(true);

	std::string readstring;
	std::cout << "Specify the width of the moving average. Leave blank to skip. \n";
	std::getline(std::cin, readstring);
	try {
		this->iMovingAverageRange = std::stoi(readstring);
	}
	catch (std::invalid_argument const& inv) {
		std::cout << "Invalid argument " << inv.what() << std::endl;
		return 1;
	}

	std::cout << "Specify the tolerance of the Douglas-Peucker filter. Leave blank to skip." << std::endl;
	std::getline(std::cin, readstring);
	try {
		this->fDouglasPeuckerTolerance = std::stof(readstring);
	}
	catch (std::invalid_argument const& inv) {
		std::cout << "Invalid argument " << inv.what() << std::endl;
		return 1;
	}

	std::cout << "Want to set a speed value? (y/n)" << std::endl;
	std::getline(std::cin, answer);
	if (answer == "y" || answer == "Y") {
		this->iSpeedMode = 1;
		std::cout << "Enter the speed value in mm/s" << std::endl;
		std::getline(std::cin, readstring);
		try {
			this->fManSpeedValue = std::stof(readstring);
		}
		catch (std::invalid_argument const& inv) {
			std::cout << "Invalid argument " << inv.what() << std::endl;
			return 1;
		}
	}
	else if (answer == "n" || answer == "N") {
		std::cout << "Speed will get calculated" << std::endl;
	}
	else {
		std::cout << "Please answer with 'y' or 'n'." << std::endl;
	}

	std::cout << "Rigid orientation instead of calculated orientation? (y/n)" << std::endl;
	std::getline(std::cin, answer);
	if (answer == "y" || answer == "Y") {
		this->iOrientationMode = 1;
		std::cout << "Enter the orientation values A" << std::endl;
		std::getline(std::cin, readstring);
		try {
			this->fManOrientationValues[0] = std::stof(readstring);
		}
		catch (std::invalid_argument const& inv) {
			std::cout << "Invalid argument " << inv.what() << std::endl;
			return 1;
		}
		std::cout << "Enter the orientation values B" << std::endl;
		std::getline(std::cin, readstring);
		try {
			this->fManOrientationValues[1] = std::stof(readstring);
		}
		catch (std::invalid_argument const& inv) {
			std::cout << "Invalid argument " << inv.what() << std::endl;
			return 1;
		}
		std::cout << "Enter the orientation values C" << std::endl;
		std::getline(std::cin, readstring);
		try {
			this->fManOrientationValues[2] = std::stof(readstring);
		}
		catch (std::invalid_argument const& inv) {
			std::cout << "Invalid argument " << inv.what() << std::endl;
			return 1;
		}
	}
	else if (answer == "n" || answer == "N") {
		std::cout << "Calculated orientation";
	}
	else {
		std::cout << "Please answer with 'y' or 'n'.\n";
	}


	return 0;
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


//Read config file, arrangement of attributes is 
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
				valueStream >> this->fDouglasPeuckerTolerance;
			}
			else {
				std::cerr << "Unknown key: " << key << std::endl;
			}
		}
	}

	std::cout << "got config!\n";
	return true;
}

/**
 * Saves the current configuration to a file in the same format as testconfig.txt,
 * so that getConfigFromFile can read it back.
 *
 * @param configname The filename to save the configuration to.
 * @return True if the file was written successfully, false otherwise.
 */


bool ConfigContainer::saveConfig(std::string configname)
{
	if (configname.size() < 4 || configname.substr(configname.size() - 4) != ".txt") {
		configname += ".txt";
	}

	FileHandler file(configname);

	// Check if file exists and prompt user
	while (file.exists()) {
		std::cout << "File \"" << configname << "\" already exists. Override? (y/n): ";
		std::string answer;
		std::getline(std::cin, answer);
		if (answer == "y" || answer == "Y") {
			break;
		}
		else if (answer == "n" || answer == "N") {
			std::cout << "Enter new filename (with .txt extension): ";
			std::getline(std::cin, configname);
			file.setFilename(configname);
			if (configname.size() < 4 || configname.substr(configname.size() - 4) != ".txt") {
				configname += ".txt";
			}
		}
		else {
			std::cout << "Please answer with 'y' or 'n'.\n";
		}
	}

	std::ostringstream oss;
	oss << std::fixed << std::setprecision(6);
	oss << "name: " << sName << "\n";
	oss << "geschwindigkeitsmodus: " << iSpeedMode << "\n";
	oss << "geschwindigkeit: " << fManSpeedValue << "\n";
	oss << "orientierung: " << iOrientationMode << "\n";
	oss << "blocksizemode: " << iBlockSize << "\n";
	oss << "startpunkt: " << iManStartValue << "\n";
	oss << "stopppunkt: " << iManStopValue << "\n";
	oss << "betriebsart: " << iModus << "\n";
	oss << "filterbreite: " << iMovingAverageRange << "\n";
	oss << "approximation: " << fDouglasPeuckerTolerance << "\n";
	return file.write(oss.str());
}



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

void ConfigContainer::setManConfig(bool value)
{
	bManConfig = value;
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

float ConfigContainer::getManOrientationValues(int n) const {
	return fManOrientationValues[n];
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

bool ConfigContainer::getManConfig() const
{
	return bManConfig;
}
