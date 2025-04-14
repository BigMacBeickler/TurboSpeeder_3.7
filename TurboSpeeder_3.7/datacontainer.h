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
		bool deleteEntry(const int n);
		bool getConfigFile(FileHandler& file);
		bool getConfigManual();
		bool saveConfig();
		void printCoordinates() const;
		void printRotMatrix() const;
		~dataContainer(void);

	private:
		std::vector<dataPoint> dataField;
		std::vector<float> stringToFloatVector(const std::string& str);
		configClass config;
		template<typename T>
		std::vector<T> stringToNumber(const std::string& str);
};


