#include "eventQueue/EventManager.h"

#pragma region test
#include <stdio.h>
#include <iostream>
#include <typeinfo>
#include "maths/algorithm/newtonRapson.h"
#pragma endregion

using namespace Phantom;
using namespace std;
int Test() {

#pragma region Test EventManager
	using namespace EventQueue;
	EventHandler eh;
	EventManager::GetInstance().AddEventHandler(0, &eh);
	Event evt(EventId::EVT_TICK);
	EventManager::GetInstance().DispatchEvent(&evt);


	using namespace maths;

	cout.precision(4);
	cout.setf(ios::fixed);
	NewtonRapson<float,double>::nr_f f = [](double x) { return pow(x, 3.0) - x - 11.0; };
	NewtonRapson<float,double>::nr_fprime fprime = [](double x) { return 3 * pow(x, 2.0) - 1.0; };
	auto result = NewtonRapson<float,double>::Solve(2, f, fprime);
	cout << "root of equation x^3 - x - 11 = 0 is: " << result << endl;

#pragma endregion
	return 0;
}