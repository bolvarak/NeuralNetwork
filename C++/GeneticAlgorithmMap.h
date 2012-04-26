// Application Definitions
#ifndef GENETICALGORITHMMAP_H
#define GENETICALGORITHMMAP_H
// Application Headers
#include <stdlib.h>
#include <Windows.h>
#include <vector>
#include "Definitions.h"
// Namespace Definition
using namespace std;
// Map class definition
class GeneticAlgorithmMap {
// Private properties
private:
	// Map Storage
	static const int iMap[MAP_HEIGHT][MAP_WIDTH];
	static const int mMapWidth;
	static const int mMapHeight;
	// Starting points
	static const int mStartX;
	static const int mStartY;
	// End points
	static const int mEndX;
	static const int mEndY;
// Public Properties
public:
	// Memory storage
	int iMemory[MAP_HEIGHT][MAP_WIDTH];
	// Constructor Definition
	GeneticAlgorithmMap() {
		// Clear memory
		ResetMemory();
	}
	// Tests the route to see how far the organism can get and returns
	// a fitness score proportional to the distance reached from the exit
	double TestRoute(const std::vector<int> &vPath, GeneticAlgorithmMap &cMemory);
	// Displays the map using Windows GDI
	void Render(const int cxClient, const int cyClient, HDC hdcSurface);
	// Draws the path that is stored in memory
	void RenderFromMemory(const int cxClient, const int cyClient, HDC hdcSurface);
	// Clears memory
	void ResetMemory();
};
#endif
