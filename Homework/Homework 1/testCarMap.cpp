#include "CarMap.h"
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
	CarMap car;

	car.addCar("222");
	car.addCar("333");
	car.addCar("111");
	car.addCar("111");
	car.addCar("444");
	car.addCar("555");
	car.addCar("666");

	assert(car.fleetSize() == 6);

	car.drive("111", 25.0);
	car.drive("333", 5.0);
	car.drive("444", 523.0);
	car.drive("666", 52.0);

	car.print();
}