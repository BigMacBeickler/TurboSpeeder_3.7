#pragma once
#include <string>
#include <vector>
#include "FileHandler.h"

struct dataPoint
{
public:
	float time;
	float x, y, z;
	float rotMatrix[9];
};

struct configClass
{
public:
	std::string name;
	int movingAverageRange;
	int douglasPeuckerTolerance;
	int vlleinszuviel;
};

class dataContainer
{
	public:
		dataContainer(void);
		bool getData(FileHandler& file);
		bool getConfigFile(FileHandler& file);
		bool getConfigManual();
		bool saveConfig();
		void printCoordinates();
		void printRotMatrix();
		~dataContainer(void);

	private:
		std::vector<dataPoint> dataField;
		std::vector<float> stringToFloatVector(const std::string& str);
		configClass config;
};


