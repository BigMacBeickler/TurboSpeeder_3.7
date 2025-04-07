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

	void setDatapoints();
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
		bool getConfigFile(FileHandler);
		bool getConfigManual();
		bool saveConfig();
		~dataContainer(void);


	private:
		std::vector<dataPoint> dataField;
		configClass config;

};

