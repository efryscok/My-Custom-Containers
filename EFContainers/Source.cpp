#include "eflist.h"
#include "efmap.h"
#include "efvector.h"
#include "CHRTimer.h"

#include <list>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>

template <typename T>
void testMap(T& map) {
	// Timer for container comparisons
	CHRTimer timer;
	
	// Variables for keeping track of timed events
	int timeInt = 0;
	double timeDbl = 0.0;
	double find = 0.0;

	// Timing inserts
	timer.Reset(); timer.Start();
	for (int count = 0; count < 1000000; ++count) {
		map[count] = 0;
		timeDbl += timer.GetElapsedSeconds(true);
		if (static_cast<int>(timeDbl) > timeInt) {
			++timeInt;
			std::cout << ".";
		}
	}
	timer.Stop();

	// Timing find
	timer.Reset(); timer.Start();
	map.find(500000);
	find += timer.GetElapsedSeconds(true);
	timer.Stop();

	// Output results
	std::cout << std::endl << "Insert: " << timeDbl << " Find: " << find * 1000 << std::endl;
}

int main() {
	// Create containers
	ef::map<int, int> efMap;
	std::map<int, int> stdMap;

	// Custom map
	std::cout << "ef::map" << std::endl;
	testMap(efMap);

	// Standard map
	std::cout << std::endl << "std::map" << std::endl;
	testMap(stdMap);
}