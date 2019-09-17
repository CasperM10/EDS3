#include "RentalAdministration.h"
#include <stdexcept>

using namespace std;

RentalAdministration::RentalAdministration()
{
	
}

RentalAdministration::~RentalAdministration()
{
	for (Car* car : Cars)
	{  
		delete car;
		car = NULL;
	}
}

bool RentalAdministration::Add(Car* car)
{
	if(car == NULL)
	{
		return false;
	}
	Cars.push_back(car);
	return true;
}

bool RentalAdministration::RentCar(string licenceplate)
{
	if(licenceplate.empty())
	{
		throw(invalid_argument("licenceplate is null"));
	}
	Car* car = FindCarWithException(licenceplate);
	return car->Rent();
}

double RentalAdministration::ReturnCar(string licenceplate, int kilometers)
{
	if(licenceplate.empty())
	{
		throw(invalid_argument("Licenceplate is null"));
	}
	Car* car = FindCarWithException(licenceplate);
	if(car->IsAvailable)
	{
		throw(logic_error("Car is not rented"));
	}
	return car->Return(kilometers);
}

void RentalAdministration::CleanCar(string licenceplate)
{
	if(licenceplate.empty())
	{
		throw(invalid_argument("licenceplate is null"));
	}
	Car* car = FindCarWithException(licenceplate);
	car->Clean();
}

vector<Car*> RentalAdministration::GetCars() const
{
	return Cars;
}

Car* RentalAdministration::FindCar(string licenceplate)
{
	for (Car* car : Cars)
	{  
		if (car->LicencePlate == licenceplate)
		{
			return car;
		}
	}	
	return NULL;
}

Car* RentalAdministration::FindCarWithException(string licenceplate)
{
	Car* car = FindCar(licenceplate);
	return car;
}
