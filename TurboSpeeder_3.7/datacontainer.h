/**
 * @file datacontainer.h
 * @brief Defines the DataContainer class and supporting data structures for handling, processing, and analyzing time-series 3D data.
 *
 * The DataContainer class manages a collection of dataPoint structs, each containing timestamp, 3D coordinates, speed, and a rotation matrix.
 * It provides methods for loading data from files, filtering, trajectory simplification (Douglas-Peucker), speed calculation, and conversion of rotation matrices to Euler angles.
 * Utility functions for data parsing and output are also included.
 */

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
	float speed = 0;
	double A = 0.0; // Euler angle: was yaw
	double B = 0.0; // Euler angle: was pitch
	double C = 0.0; // Euler angle: was roll
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
		DataContainer(ConfigContainer& config);
		bool getData(FileHandler& file);
		bool averageFilter(const int n);
		void approximateXYZ(float epsilon);
		void rotationMatrixToEulerAngels(void);
		void GIVEMETHESPEEEEEEEEED(void);

		bool deleteEntry(const int n);
		//bool getConfigFile(FileHandler& file);
		//bool getConfigManual();
		//bool saveConfig();

		bool saveAsKukaSrc(const std::string& dataFileName);

		void printCoordinates() const;
		void printRotMatrix() const;

		~DataContainer(void);

	private:
		std::vector<dataPoint> dataField;
		std::vector<float> stringToFloatVector(const std::string& str);
		std::vector<double> stringToDoubleVector(const std::string& str);
		ConfigContainer *config;
		template<typename T>
		std::vector<T> stringToNumber(const std::string& str);
};


