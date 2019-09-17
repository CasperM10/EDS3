#include "Sedan.h"

using namespace std;

static const double priceperkm = 0.29;
static const int maxKmPerClean = 500;

Sedan::Sedan(string manufacturer, string model, int buildyear, string licenceplate, bool hastowbar)
	: Car(manufacturer, model, buildyear, licenceplate, priceperkm)
{
	HasTowbar = hastowbar;
	lastCleanedAtKm = 0;
}

void Sedan::Clean()
{
	lastCleanedAtKm = Kilometers;
	NeedsCleaning = false;
}

bool Sedan::GetNeedsCleaning()
{
	return (Kilometers - lastCleanedAtKm) >= maxKmPerClean;
}
