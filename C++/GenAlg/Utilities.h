#ifndef UTILITIES_H
	#define UTILITIES_H
	// Application headers
	#include <stdlib.h>
	#include <math.h>
	#include <sstream>
	#include <string>
	// Namespace
	using namespace std;
	// Random integer generator
	inline int RandomInteger(int iNumberX, int iNumberY) {
		// Return the random number
		return (rand() % (iNumberY - iNumberX + 1) + iNumberX);
	}
	// Random float point generator
	inline double RandomFloat() {
		// Return the random floating point
		return (rand() / (RAND_MAX + 1.0));
	}
	// Random boolean generator
	inline bool RandomBoolean() {
		// Generate the random boolean
		if (RandomInteger(0, 1)) {
			// Return the boolean
			return true;
		} else {
			// Return the boolean
			return false;
		}
	}
	// Return a random floating point between -1.0 and 1.0
	inline double RandomClamped() {
		// Generate and return the random floating point
		return (RandomFloat() - RandomFloat());
	}
	// Convert integers to strings
	string IntegerToString(int iNumber);
#endif
