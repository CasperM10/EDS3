#include "Limousine.h"

using namespace std;

static const double priceperkm = 2.5;

Limousine::Limousine(string manufacturer, string model, int buildyear, string licenceplate, bool hasminibar)
	: Car(manufacturer, model, buildyear, licenceplate, priceperkm)
{
	HasMiniBar = hasminibar;
	NeedsCleaning = false;
}

double Limousine::Return(int kilometers)
{
	double price = Car::Return(kilometers);
	NeedsCleaning = true;
	return price;
}

void Limousine::Clean()
{
	NeedsCleaning = false;
}

// TODO: implement your class methods here
