// TurboSpeeder_3.7.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.

// TODO:
/*

2. Configfile einlesen / definieren
3. Eingelesene Daten in Struktur speichern (Struct dementsprechend erstellen...)
4. Filter Mittelwert (Einstellbare länge Asymmetrisch) NUR XYZ
5. Filter Approximation NUR XYZ
6. Eulerwinkel
7. AUSGABE in passende Datei



zu 3.:
struct (Alle Float)
Timestamps
X
Y
Z
A1
A2
B1
B2
C1
C2
 this is test!!!

typdef struct {
 float Datapoint 1;
 float Datapoint 2;
 float Datapoint 3;
 float Datapoint 4;
 float Datapoint 5;
 float Datapoint 6;
} aDataRow;

aDataRow SomeData[numRows];

*/

#include <iostream>
#include <ctime>
#include <string>
#include "FileHandler.h"
#include "DataContainer.h"
#include <conio.h>

//#define DATAPRINT

int main()
{
    clock_t start;
    start = clock();

    ConfigContainer config;
    DataContainer data;

    /*
    Daten einlesen

    */

    std::cout << "Bitte Dateinamen eingeben: ";
    std::string dataFileName;
    std::getline(std::cin, dataFileName);

#ifdef _DEBUG
    //schneller debuggen, einfach enter um test1.csv zu laden
    if (dataFileName == "") dataFileName = "test1.csv";
#endif // DEBUG



    FileHandler dataFile(dataFileName);
	if (!dataFile.exists()) {
		std::cout << "Datei existiert nicht. Bitte erneut versuchen.\n";
		return 1;
	};
    data.getData(dataFile);
    

#ifdef DATAPRINT
   data.printCoordinates();
   data.printRotMatrix();
#endif


    std::cout << "Configfile laden. Leer lassen falls keine Configfile geladen werden soll: ";   
    std::string configFileName;
    std::getline(std::cin, configFileName);
    
#ifdef _DEBUG
    //schneller debuggen, lädt testconfig falls leer
    if (configFileName == "") configFileName = "testconfig.txt";
#endif

    std::cout << configFileName;
    if (configFileName != "") {
        FileHandler configFile(configFileName);
        if (!configFile.exists()) {
            std::cout << "Datei existiert nicht. Bitte erneut versuchen.\n";
            return 1;
        };
        config.getConfigFromFile(configFile);
    }
    else {
        config.getConfigManual();
    }
    config.printConfig();


    data.averageFilter(config.getMovingAverageRange());
    std::cout << "Daten nach Average-Filter" << std::endl;
   // data.printCoordinates();


    data.approximateXYZ(config.getDouglasPeuckerTolerance());
    //data.printCoordinates();
    data.printRotMatrix();
    
    data.rotationMatrixToEulerAngels();


    std::cout << "Konfiguration als Datei speichern?\n" << std::endl;
    std::string save;
    std::cin >> save;
    if (save == "yes") {
        std::string savename;
        std::cout << "Confignamen eingeben: ";
        std::getline(std::cin, savename);
       // config.saveConfig(savename);
        


    }
    else if (save == "no") {

    }
    else {
        std::cout << "Lern schreiben" << std::endl;
    }

    float elapsed = (float)(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Elapsed time: " << elapsed << "\n";

    return 0;
}
