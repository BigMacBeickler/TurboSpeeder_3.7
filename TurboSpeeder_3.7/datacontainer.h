#pragma once
#include <string>
#include <vector>
#include "FileHandler.h"
#include "configContainer.h"

struct dataPoint
{
public:
	float time;
	double x, y, z;
	double rotMatrix[9];
};

//struct configClass
//{
//public:
//	std::string name;
//	int movingAverageRange;
//	int douglasPeuckerTolerance;
//	int vlleinszuviel;
//};

class DataContainer
{
	public:
		DataContainer(void);
		bool getData(FileHandler& file);
		bool averageFilter(const int n);
		bool deleteEntry(const int n);
		//bool getConfigFile(FileHandler& file);
		//bool getConfigManual();
		//bool saveConfig();
		void printCoordinates() const;
		void printRotMatrix() const;
		void approximateXYZ(float epsilon);
		~DataContainer(void);

	private:
		std::vector<dataPoint> dataField;
		std::vector<float> stringToFloatVector(const std::string& str);
		std::vector<double> stringToDoubleVector(const std::string& str);
		ConfigContainer config;
		template<typename T>
		std::vector<T> stringToNumber(const std::string& str);
};


