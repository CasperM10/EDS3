#ifndef RENTALADMINISTRATION_H
#define RENTALADMINISTRATION_H

#include "Car.h"
#include <string>
#include <vector>

class RentalAdministration
{
	private:
	Car* FindCar(std::string);
	Car* FindCarWithException(std::string);
	
	public:
	std::vector<Car*> Cars;
	
	RentalAdministration();
	~RentalAdministration();
	
	bool Add(Car*);
	bool RentCar(std::string);
	double ReturnCar(std::string, int);
	void CleanCar(std::string);
	std::vector<Car*> GetCars() const;
};

#endif
