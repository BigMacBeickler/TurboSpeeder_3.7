// TurboSpeeder_3.7.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.

// TODO:
/*

2. Configfile einlesen / definieren
3. Eingelesene Daten in Struktur speichern (Struct dementsprechend erstellen...)
4. Filter Mittelwert (Einstellbare länge Asymmetrisch) NUR XYZ
5. Filter Approximation NUR XYZ
6. Eulerwinkel
7. AUSGABE in passende Datei

*/

#include <iostream>
#include <ctime>
#include <string>
#include "FileHandler.h"
#include "DataContainer.h"

//_DEBUG gets set by the IDE if the DEBUG config as compile option is selected

/*DATAPRINT define to print data in between*/
//#define DATAPRINT
/*Possible testmode*/
//#define TESTMODE


int main()
{
	clock_t start;
	start = clock();

	ConfigContainer config;
	DataContainer data(config);

/*
Daten einlesen
*/

	std::string dataFileName;
	std::cout << "Enter Datafilename: ";
	std::getline(std::cin, dataFileName);

#ifdef _DEBUG
	//schneller debuggen, einfach enter um test1.csv zu laden
	if (dataFileName == "") dataFileName = "test1.csv";
#endif // DEBUG

	FileHandler dataFile(dataFileName);
	while (!dataFile.exists()) {
		std::cout << "File does not exist.Retry or cancel(c)." << std::endl;
		std::getline(std::cin, dataFileName);
		if (dataFileName == "c") {
			std::cout << "k, bye" << std::endl;
			return 1;
		}
	};
	if (!data.getData(dataFile)) {
		std::cout << "Fetching data failed." << std::endl;
	};

#ifdef DATAPRINT
	data.printCoordinates();
	data.printRotMatrix();
#endif


/*
Config einlesen

*/

	std::cout << "Load Configfile. Type \"man\" for manually setting values: " << std::endl;
	std::string configFileName;
	std::getline(std::cin, configFileName);

#ifdef _DEBUG
	//schneller debuggen, lädt testconfig falls leer
	if (configFileName == "") configFileName = "testconfig.txt";
#endif //DEBUG

	if (configFileName != "man") {
		std::cout << configFileName;
		FileHandler configFile(configFileName);
		while (!dataFile.exists()) {
			std::cout << "File does not exist.Retry or cancel(c)." << std::endl;
			std::getline(std::cin, configFileName);
			if (configFileName == "c") return 1;
		};
		config.getConfigFromFile(configFile);
	}
	else {
		if(config.getConfigManual()) return 1;
	}

#ifdef DATAPRINT
	config.printConfig();
#endif

/*
* Daten bearbeiten, averageFilter,aproximateXYZ, rotationMatrixToEuler, speed
*/

	if(!data.averageFilter(config.getMovingAverageRange())) {
		std::cout << "Filter couldn´t be applied, filter width is bigger than data field." << std::endl;
		return false;
	}
	
#ifdef DATAPRINT
	std::cout << "Daten nach Average-Filter" << std::endl;
	data.printCoordinates();
#endif

	data.approximateXYZ(config.getDouglasPeuckerTolerance());
	data.rotationMatrixToEulerAngels();
	data.GIVEMETHESPEEEEEEEEED();

#ifdef DATAPRINT
	data.printCoordinates();
	data.printRotMatrix();
#endif


/*
* Daten und config speichern
*/


	if (data.saveAsKukaSrc(dataFileName)) {
		std::cout << "Data exported successfully" << std::endl;
	}
	else {
		std::cout << "Error while writing data, engieneer is informed" << std::endl;
	}

 
	if (config.getManConfig() == true) {
		std::cout << "Save configuration in a file?(y/n)" << std::endl;
		std::string save_choice;
		std::getline(std::cin, save_choice);
		if (save_choice == "y" || save_choice == "Y") {
			std::string savename;
			std::cout << "Confignamen eingeben: ";
			std::getline(std::cin, savename);
			config.saveConfig(savename);

		}
		else if (save_choice == "n" || save_choice == "N") {
			std::cout << "=( k, bye" << std::endl;
		}
		else {
			std::cout << "Lern schreiben" << std::endl;
		}
	}

	float elapsed = (float)(clock() - start) / CLOCKS_PER_SEC;
	std::cout << "Elapsed time: " << elapsed << std::endl;

	return 0;
}
