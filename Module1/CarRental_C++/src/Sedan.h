#ifndef SEDAN_H
#define SEDAN_H

#include <string>
#include "Car.h"

class Sedan : public Car
{
	private:
	int lastCleanedAtKm;
	
	public:
	bool HasTowbar;
	
	Sedan(std::string, std::string, int, std::string, bool);
	
	virtual void Clean();
	bool GetNeedsCleaning();
};

#endif
