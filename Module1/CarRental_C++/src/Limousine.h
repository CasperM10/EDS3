#ifndef LIMOUSINE_H
#define LIMOUSINE_H

#include <string>
#include "Car.h"

class Limousine : public Car
{	
	public:
	bool HasMiniBar;
	
	Limousine(std::string, std::string, int, std::string, bool);
	
	virtual double Return(int);
	virtual void Clean();
};

#endif
