// TurboSpeeder_3.7.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.

#define TESTMODE

#include <iostream>
#include <ctime>
#include <string>
#include "FileHandler.h"
#include "DataContainer.h"



//Tesmode functions
#ifdef TESTMODE
#include <cassert>
#include <array>
#include <sstream>
#include <cmath>

// --- helpers --------------------------------------------------------------
static bool write_file(const std::string& name, const std::string& content) {
    FileHandler fh(name);
    return fh.write(content);
}

// Build one record line: time, x, y, z, then 3x3 rotation matrix values.
// The code expects whitespace-separated numbers (not CSV commas).
static std::string make_record(double t, double x, double y, double z,
    const std::array<double, 9>& R)
{
    std::ostringstream oss;
    oss.setf(std::ios::fixed); oss.precision(6);
    oss << t << ' ' << x << ' ' << y << ' ' << z << ' '
        << R[0] << ' ' << R[1] << ' ' << R[2] << ' '
        << R[3] << ' ' << R[4] << ' ' << R[5] << ' '
        << R[6] << ' ' << R[7] << ' ' << R[8] << '\n';
    return oss.str();
}

static void run_testmode_asserts() {
    std::cout << "[TESTMODE] running embedded asserts...\n";

    // Identity rotation (Euler A/B/C should be ~0 for ZYX conversion).
    const std::array<double, 9> I = { 1,0,0, 0,1,0, 0,0,1 };

    // === Test 1: Validating reading & field placement ======================
    {
        std::string content;
        content += make_record(0.0, 0.0, 0.0, 0.0, I);
        content += make_record(1.0, 100.0, 0.0, 0.0, I);
        content += make_record(2.0, 100.0, 100.0, 0.0, I);

        const std::string fname = "__t_valid_data.txt";
        assert(write_file(fname, content) && "unable to write test input file");

        ConfigContainer cfg;
        DataContainer   data(cfg);
        FileHandler     fdata(fname);

        bool ok = data.getData(fdata);
        assert(ok && "getData() should succeed on a valid dataset");

        const auto& v = data.__test_data();
        assert(v.size() == 3 && "expected 3 datasets");
        assert(v[0].time == 0.0f);
        assert(v[1].time == 1.0f);
        assert(v[2].time == 2.0f);
        assert(v[1].x == 100.0 && v[1].y == 0.0 && v[1].z == 0.0);
        assert(v[2].x == 100.0 && v[2].y == 100.0 && v[2].z == 0.0);

        // === Test 2: Euler/orientation for identity =======================
        data.rotationMatrixToEulerAngels();
        auto near0 = [](double a) { return std::abs(a) < 1e-6; };
        assert(near0(v[0].A) && near0(v[0].B) && near0(v[0].C) && "identity -> Euler ≈ 0");
        assert(near0(v[1].A) && near0(v[1].B) && near0(v[1].C));
        assert(near0(v[2].A) && near0(v[2].B) && near0(v[2].C));

        // === Test 3: Timestamps strictly increasing =======================
        bool strictly_increasing = true;
        for (size_t i = 1; i < v.size(); ++i)
            strictly_increasing &= (v[i - 1].time < v[i].time);
        assert(strictly_increasing && "timestamps must increase monotonically");
    }

    // === Test 4: Douglas–Peucker endpoints kept, reduction happens =========
    {
        std::string content;
        content += make_record(0.0, 0.0, 0.0, 0.0, I);
        content += make_record(1.0, 1.0, 0.0, 0.0, I);
        content += make_record(2.0, 2.0, 0.0, 0.0, I);
        content += make_record(3.0, 3.0, 0.0, 0.0, I);

        const std::string fname = "__t_dp_line.txt";
        assert(write_file(fname, content));

        ConfigContainer cfg;
        DataContainer   data(cfg);
        FileHandler     fdata(fname);
        assert(data.getData(fdata));

        const auto& v = data.__test_data();
        const auto beforeN = data.__test_data().size();
        data.approximateXYZ(0.01f); // nearly collinear -> can reduce

        assert(v.size() >= 2 && v.size() <= beforeN);
        assert(v.front().time == 0.0f && v.back().time == 3.0f && "endpoints must remain");
    }

    // === Negative Test A: incoherent/malformed dataset must throw ==========
    {
        // One full record + 5 dangling numbers -> size not divisible by 13.
        std::string bad;
        bad += make_record(0.0, 0.0, 0.0, 0.0, I);
        bad += "1 2 3 4 5\n";
        const std::string fname = "__t_bad_incoherent.txt";
        assert(write_file(fname, bad));

        ConfigContainer cfg;
        DataContainer   data(cfg);
        FileHandler     fbad(fname);

        bool threw = false;
        try {
            (void)data.getData(fbad); // current code throws const char* on incoherent size
        }
        catch (const char* msg) {
            threw = true;
            (void)msg; // message is "Data is incoherent" in the current implementation
        }
        assert(threw && "expected getData() to throw on incoherent block size");
    }

    // === Negative Test B: empty file (implementation note) =================
    {
        const std::string fname = "__t_empty.txt";
        assert(write_file(fname, ""));  // empty file

        ConfigContainer cfg;
        DataContainer   data(cfg);
        FileHandler     fempty(fname);

        // Current implementation parses 0 numbers and returns true with 0 datasets.
        bool ok = data.getData(fempty);
        const auto& v = data.__test_data();
        assert(ok && v.empty() && "empty input -> 0 datasets (adjust code if spec requires failure)");
    }

    std::cout << "[TESTMODE] all asserts passed.\n";
}
#endif // TESTMODE


//_DEBUG gets set by the IDE if the DEBUG config as compile option is selected

/*DATAPRINT define to print data in between*/
//#define DATAPRINT
/*Possible testmode*/

int main()
{

#ifdef TESTMODE
    run_testmode_asserts();
#endif


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
		while (!configFile.exists()) {
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
