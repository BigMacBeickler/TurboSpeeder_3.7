// TurboSpeeder_3.7.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.

#include <iostream>
#include <ctime>
#include <string>
#include "Point2D.h"
#include "Point3D.h"
#include "FileHandler.h"

int main()
{
    clock_t start;
    start = clock();

    //std::cout << "Hello World!\n";

    std::cout << "Bitte Dateinamen eingeben: ";
    std::string datafile;
    std::getline(std::cin, datafile);

    std::cout << "Configfile laden. Leer lassen falls keine Configfile geladen werden soll ";   
    std::string configfile;
    std::getline(std::cin, configfile);  

    float elapsed = (float)(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Elapsed time: " << elapsed << "\n";

    return 0;
}
