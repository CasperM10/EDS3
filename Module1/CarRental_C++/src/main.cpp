//============================================================================
// Name        : menu.cpp
// Author      : Freddy Hurkmans
// Version     :
// Copyright   : copyright Freddy Hurkmans
// Description : Assignment 1 example
//============================================================================
#include "RentalAdministration.h"
#include "Limousine.h"
#include "Sedan.h"

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

void addTestDataToAdministration(RentalAdministration& administration)
{
    string licencePlates[] = {"SD-001", "SD-002", "SD-003", "SD-004", "LM-001", "LM-002"};
	
    for (int i = 0; i < 4; i++)
    {
        Car* sedan = new Sedan("BMW", "535d", 2012 + i, licencePlates[i], false);
        administration.Add(sedan);
    }
    for (int i = 4; i < 6; i++)
    {
        Car *limousine = new Limousine("Rolls Roys", "Phantom Extended Wheelbase", 2015, licencePlates[i], true);
        administration.Add(limousine);
    }
}

static const Car* GetCurrentCar(const RentalAdministration* administration, size_t carNumber)
{
    if (carNumber > administration->Cars.size())
    {
        cout << "\nError: car with car number " << carNumber << " does not exist!\n";
        return NULL;
    }
    
	for(uint i = 0; i < administration->Cars.size(); i++)
	{
		if(i == carNumber)
		{
			return administration->Cars[i];
		}
	}
    return NULL;
}

static void PrintCars(const RentalAdministration& administration)
{
    int i = 1;
    for (Car* car : administration.Cars) 
	{  
		cout << "\n" << i << ": " << car->ToString();
		i++;
	}
}

static size_t selectCar(const RentalAdministration& administration)
{
    size_t carNumber = 0;
    cout << "These cars are currently listed:";
    PrintCars(administration);
    cout << "\nPlease enter a car number: ";
    std::cin >> carNumber;
    std::cin.ignore();
    return carNumber - 1;
}

static void rentCar(RentalAdministration* administration, size_t carNumber)
{
	try
	{
		const Car* curr = GetCurrentCar(administration, carNumber);
		administration->RentCar(curr->LicencePlate);
		cout << "Rented " << curr->ToString();
	}
    catch(invalid_argument)
    {
		cout << "Invalid arg exception thrown";
	}
}

static void returnCar(RentalAdministration* administration, size_t carNumber)
{
	double cost = 0;
	try
	{
		const Car* curr = GetCurrentCar(administration, carNumber);
		if(curr != NULL)
		{
			cout << "New total kilometers:";
			int kilometers;
			cin >> kilometers;
			cost = administration->ReturnCar(curr->LicencePlate, kilometers);
			cout << "Returned " << curr->ToString() << endl;
			cout << "Cost: " << cost;
		}
		else
		{
			cout << "Car is not Rented";
		}
	}
	catch(invalid_argument e)
	{
		cout << "Invalid arg exception thrown";
	}
	catch(logic_error)
	{
		cout << "logic error exception thrown";
	}
}

static void printIfCarNeedsCleaning(const RentalAdministration* administration, size_t carNumber)
{
    const Car* curr = GetCurrentCar(administration, carNumber);
    if(curr->NeedsCleaning)
    {
		cout << curr->ToString();
		cout << " Needs Cleaning";
	}
	else{cout << "Car doesn't need Cleaning";}
}

static void cleanCar(RentalAdministration* administration, size_t carNumber)
{
	try
	{
		const Car* curr = GetCurrentCar(administration, carNumber);
		administration->CleanCar(curr->LicencePlate);
		cout << "Cleaned " << curr->ToString();
	}
	catch(invalid_argument)
	{
		cout << "Invalid arg exception thrown";
	}
}


static void showMenu( void )
{
    cout << ("\n\nCar Rental menu\n");
    cout << ("===============\n");
    cout << ("(1) Show all cars\n");
    cout << ("(2) Select car\n");
    cout << ("(3) Rent selected car\n");
    cout << ("(4) Return selected car\n");
    cout << ("(5) Check if car needs cleaning\n");
    cout << ("(6) Clean car\n");
    cout << ("-----------------------\n");
    cout << ("(9) QUIT\n\n");
    cout << ("Choice : ");
}

int main( void )
{
    bool quit = false;
    size_t carNumber = 0;

    RentalAdministration administration;
    addTestDataToAdministration(administration);

    while (!quit)
    {
        char choice = '\0';
        showMenu();
        cin >> choice;
        cin.ignore();
        
        switch (choice)
        {
        case '1' :
            PrintCars(administration);
            break;
        case '2' :
            carNumber = selectCar(administration);
            break;
        case '3' :
            rentCar(&administration, carNumber);
            break;
        case '4' :
            returnCar(&administration, carNumber);
            break;
        case '5' :
            printIfCarNeedsCleaning(&administration, carNumber);
            break;
        case '6' :
            cleanCar(&administration, carNumber);
            break;

        case '9' :
            quit = true;
            break;
        default:
            cout << "\n\nI did not understand your choice (" << choice << ")" << endl;
            break;
        }
    }

    return 0;
}
