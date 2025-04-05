// TurboSpeeder_3.7.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.

// TODO:
/*
1. Filehandler Fertig machen
2. Configfile einlesen / definieren





*/

#include <iostream>
#include <ctime>
#include <string>
#include "Point2D.h"
#include "Point3D.h"
#include "FileHandler.h"
// What about using namespace std; ?!?!?!?!?!?!?!?

std::valarray<float> dataarray;

int main()
{
    clock_t start;
    start = clock();

    std::cout << "Bitte Dateinamen eingeben: ";
    std::string datafile;
    std::getline(std::cin, datafile);
    FileHandler fileHandler(datafile);
	if (!fileHandler.exists()) {
		std::cout << "Datei existiert nicht. Bitte erneut versuchen.\n";
		return 1;
	};
	dataarray = fileHandler.readCSV();


    std::cout << "Configfile laden. Leer lassen falls keine Configfile geladen werden soll: ";   
    std::string configfile;
    std::getline(std::cin, configfile);  

    float elapsed = (float)(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Elapsed time: " << elapsed << "\n";

    return 0;
}
