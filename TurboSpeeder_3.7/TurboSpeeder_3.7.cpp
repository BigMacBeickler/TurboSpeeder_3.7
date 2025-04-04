// TurboSpeeder_3.7.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.


#include <iostream>
#include <ctime>
#include "Point2D.h"
#include "Point3D.h"

int main()
{
    clock_t start;
    start = clock();

    //std::cout << "Hello World!\n";

    float elapsed = (float)(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Elapsed time: " << elapsed << "\n";

    return 0;
}

