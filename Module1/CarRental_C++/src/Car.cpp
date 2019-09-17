#include "Car.h"
#include <stdexcept>

using namespace std;

Car::Car(string manufacturer, string model, int buildyear, string licenceplate, double priceperkm)
{
	if(manufacturer.empty() || model.empty() || licenceplate.empty())
	{
		throw(invalid_argument("A input argument is null"));
	}
	if(buildyear < 1890)
	{
		throw(out_of_range("cars cannot be built before 1890!"));
	}
	if(priceperkm < 0)
	{
		throw(out_of_range("cannot be smaller than 0"));
	}
	Manufacturer = manufacturer;
	Model = model;
	BuildYear = buildyear;
	LicencePlate = licenceplate;
	pricePerKm = priceperkm;
	Kilometers = 0;
	IsAvailable = true;
}

Car::~Car(){}

void Car::Clean() 
{
	NeedsCleaning = false;
}

bool Car::Rent()
{
	if(!IsAvailable)
	{
		return false;
	}
	IsAvailable = false;
	return true;
}

double Car::Return(int kilometers)
{
	if(IsAvailable)
	{
		throw(logic_error("Car was not rented"));
	}
	if(kilometers < Kilometers)
	{
		throw(logic_error("Less km than car had"));
	}
	
	double cost = pricePerKm * (kilometers - Kilometers);
	Kilometers = kilometers;
	NeedsCleaning = true;
	IsAvailable = true;
	return cost;
}

string Car::ToString() const
{
	return Manufacturer + " - " + Model + ", " + LicencePlate;
}

string Car::GetManufacturer() const 
{
	return Manufacturer;
}

string Car::GetModel() const
{
	return Model;
}

int Car::GetBuildYear() const
{
	return BuildYear;
}

string Car::GetLicencePlate() const
{
	return LicencePlate;
}

bool Car::GetNeedsCleaning() const
{
	return NeedsCleaning;
}

int Car::GetKilometers() const
{
	return Kilometers;
}

bool Car::GetIsAvailable() const
{
	return IsAvailable;
}

// TODO: implement your class methods here
