#pragma once
#include <string>
#include <vector>



class dataContainer
{

	public:
		dataContainer(void);


	private:
		std::vector<dataPoints> test;
		configClass config;

};

struct dataPoints
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