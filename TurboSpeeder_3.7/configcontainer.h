#pragma once
#include <string>
#include <array>
#include "FileHandler.h"

#define FLOATINGAVERAGE 4
#define FILTER	5
#define BLOCKSIZE 13



struct ConfigContainer
{

	//(Name), Mittelwertweite, Douglas-Peucker Toleranz, Geschwindigkeitsmodus, manuelle Geschwindigkeit, Orientierungsmodus, manuelle Orientierungswerte,
private:
	std::string sName = "default";
	uint32_t iMovingAverageRange = 1;
	float fDouglasPeuckerTolerance = 1;
	uint32_t iSpeedMode = 0;
	float fManSpeedValue = 1;
	uint32_t iOrientationMode = 0;
	std::array<float, 3> fManOrientationValues{};		//3 datapoints x,y and z, initialized as zeros
	uint32_t iBlockSize = 13;								//blocksize consits of 1x timestamp, 3x space variables, 9x rotational matrix values
	uint32_t iModus = 1;										//Modus 1 = standart; nothing more defined
	uint32_t iManStartValue = 0;								//not used
	uint32_t iManStopValue = 0;								//not used
	
	bool bManConfig;
	//test

	// Private Setters
	void setName(const std::string& name);
	void setMovingAverageRange(int range);
	void setDouglasPeuckerTolerance(float tolerance);
	void setSpeedMode(int mode);
	void setManSpeedValue(float value);
	void setOrientationMode(int mode);
	void setManOrientationValues(float x, float y, float z);
	void setBlockSize(int size);
	void setModus(int modus);
	void setManStartValue(int value);
	void setManStopValue(int value);
	void setManConfig(bool value);


public:
	bool getConfigFromFile(FileHandler& file);
	bool getConfigManual();
	void printConfig() const;
	bool saveConfig(std::string configname);

	std::string getName() const;
	int getMovingAverageRange() const;
	float getDouglasPeuckerTolerance() const;
	int getSpeedMode() const;
	float getManSpeedValue() const;
	int getOrientationMode() const;
	float getManOrientationValues(int n) const;
	int getBlockSize() const;
	int getModus() const;
	int getManStartValue() const;
	int getManStopValue() const;
	bool getManConfig() const;

};


