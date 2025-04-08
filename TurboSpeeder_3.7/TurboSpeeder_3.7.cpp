// TurboSpeeder_3.7.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.

// TODO:
/*
1. Filehandler Fertig machen
2. Configfile einlesen / definieren
3. Eingelesene Daten in Struktur speichern (Struct dementsprechend erstellen...)
4. Filter Mittelwert (Einstellbare länge Asymmetrisch) NUR XYZ
5. Filter Approximation NUR XYZ
6. Eulerwinkel
7. AUSGABE in passende Datei
8. GUI


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
#include "datacontainer.h"
// What about using namespace std; ?!?!?!?!?!?!?!?

//Bad practice!!

/*

Consider two libraries called Foo and Bar:

using namespace foo;
using namespace bar;

Everything works fine, and you can call Blah() from Foo and Quux() from Bar without problems. But one day you upgrade to a new version of Foo 2.0, which now offers a function called Quux(). Now you've got a conflict: Both Foo 2.0 and Bar import Quux() into your global namespace. This is going to take some effort to fix, especially if the function parameters happen to match.

If you had used foo::Blah() and bar::Quux(), then the introduction of foo::Quux() would have been a non-event.
*/



std::valarray<float> dataarray;


int main()
{
    clock_t start;
    start = clock();

    dataContainer data;

    std::cout << "Bitte Dateinamen eingeben: ";
    std::string dataFileName;
    std::getline(std::cin, dataFileName);

    //schneller debuggen, einfach enter
    if (dataFileName == "") dataFileName = "test1.csv";


    FileHandler dataFile(dataFileName);
	if (!dataFile.exists()) {
		std::cout << "Datei existiert nicht. Bitte erneut versuchen.\n";
		return 1;
	};
    data.getData(dataFile);

    //data.printCoordinates();
    data.printRotMatrix();

    std::cout << "Configfile laden. Leer lassen falls keine Configfile geladen werden soll: ";   
    std::string configFileName;
    std::getline(std::cin, configFileName);
    std::cout << configFileName;
    if (configFileName != "") {
        FileHandler configFile(configFileName);
        if (!configFile.exists()) {
            std::cout << "Datei existiert nicht. Bitte erneut versuchen.\n";
            return 1;
        };

        data.getConfigFile(configFile);
    }
    else {
        data.getConfigManual();
    }

    float elapsed = (float)(clock() - start) / CLOCKS_PER_SEC;
    std::cout << "Elapsed time: " << elapsed << "\n";

    return 0;
}
