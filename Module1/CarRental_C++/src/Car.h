#ifndef CAR_H
#define CAR_H

#include <string>

class Car
{
private:
	double pricePerKm;
public:
	std::string Manufacturer;
	std::string Model;
	int BuildYear;
	std::string LicencePlate;
	int Kilometers;
	bool IsAvailable;
	bool NeedsCleaning;

	Car(std::string, std::string, int, std::string, double);
	virtual ~Car();
	
	bool Rent();
	double Return(int);
	virtual void Clean();
	std::string ToString() const;
	
	std::string GetManufacturer() const;
	std::string GetModel() const; 
	int GetBuildYear() const;
	std::string GetLicencePlate() const;
	bool GetNeedsCleaning() const;
	int GetKilometers() const;
	bool GetIsAvailable() const; 
};

#endif
