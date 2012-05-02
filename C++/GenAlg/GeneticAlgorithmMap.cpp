// Application Header
#include "GeneticAlgorithmMap.h"
// Define our maze
const int GeneticAlgorithmMap::iMap[MAP_HEIGHT][MAP_WIDTH] = 
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
8, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1,
1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1,
1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1,
1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1,
1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5,
1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1,
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
// Define the map dimensions
const int GeneticAlgorithmMap::mMapHeight = MAP_HEIGHT;
const int GeneticAlgorithmMap::mMapWidth  = MAP_WIDTH;
// Define the map start positions
const int GeneticAlgorithmMap::mStartX    = 14;
const int GeneticAlgorithmMap::mStartY    = 7;
// Define the map end positions
const int GeneticAlgorithmMap::mEndX      = 0;
const int GeneticAlgorithmMap::mEndY      = 2;
// Render method
void GeneticAlgorithmMap::Render(const int cxClient, const int cyClient, HDC hdcSurface) {
	// Define the border
	const int iBorder = 20;
	// Define block sizes
	int iBlockSizeX   = ((cxClient - (2 * iBorder)) / mMapWidth);
	int iBlockSizeY   = ((cyClient - (2 * iBorder)) / mMapHeight);
	// Create our brushes
	HBRUSH hbrBlackBrush, hbrRedBrush, hbrOldBrush;
	// Create our pens
	HPEN   penNullPen, penOldPen;
	// Set the null pen so the outline of the cells are visible
	penNullPen    = (HPEN) GetStockObject(NULL_PEN);
	// Set a brush to fill in the cells with
	hbrBlackBrush = (HBRUSH) GetStockObject(BLACK_BRUSH);
	// Set a brush to denote the entrance and exit points
	hbrRedBrush   = (HBRUSH) CreateSolidBrush(RGB(255, 0, 0));
	// Store our objects into the device context
	hbrOldBrush   = (HBRUSH) SelectObject(hdcSurface, hbrBlackBrush);
	penOldPen     = (HPEN) SelectObject(hdcSurface, penNullPen);
	// Loop through the y-axis
	for (int iCoordinateY = 0; iCoordinateY < mMapHeight; ++iCoordinateY) {
		// Loop through the x-axis
		for (int iCoordinateX = 0; iCoordinateX < mMapWidth; ++iCoordinateX) {
			// Calculate the corners of each cell
			int iLeft   = (iBorder + (iBlockSizeX * iCoordinateX));
			int iRight  = (iLeft + iBlockSizeX);
			int iTop    = (iBorder + (iBlockSizeY * iCoordinateY));
			int iBottom = (iTop + iBlockSizeY);
			// Draw a black rectangle if this is a wall cell
			if (iMap[iCoordinateY][iCoordinateX] == 1) {
				// Grab the brush
				SelectObject(hdcSurface, hbrBlackBrush);
				// Draw the cell
				Rectangle(hdcSurface, iLeft, iTop, iRight, iBottom);
			}
			// Draw a red rectangle if this is an entrance or exit cell
			if ((iMap[iCoordinateY][iCoordinateX] == 5) || (iMap[iCoordinateY][iCoordinateX] == 8)) {
				// Grab the brush
				SelectObject(hdcSurface, hbrRedBrush);
				// Draw the cell
				Rectangle(hdcSurface, iLeft, iTop, iRight, iBottom);
			}
		}
	}
	// Grab the original brush
	SelectObject(hdcSurface, hbrOldBrush);
	// Grab the original pen
	SelectObject(hdcSurface, penOldPen);
}
// Render From Memory Method
void GeneticAlgorithmMap::RenderFromMemory(const int cxClient, const int cyClient, HDC hdcSurface) {
	// Set the border
	const int iBorder = 20;
	// Define block sizes
	int iBlockSizeX = ((cxClient - (2 * iBorder)) / mMapWidth);
	int iBlockSizeY = ((cyClient - (2 * iBorder)) / mMapHeight);
	// Create our brushes
	HBRUSH hbrGreyBrush, hbrOldBrush;
	// Create our pens
	HPEN   penNullPen, penOldPen;
	// Set a brush to fill our cells with
	hbrGreyBrush = (HBRUSH) GetStockObject(LTGRAY_BRUSH);
	// Set a pen to draw our cells with
	penNullPen   = (HPEN) GetStockObject(NULL_PEN);
	// Set the brush into the device context
	hbrOldBrush  = (HBRUSH) SelectObject(hdcSurface, hbrGreyBrush);
	// Set the pen into the device context
	penOldPen    = (HPEN) SelectObject(hdcSurface, penNullPen);
	// Loop through the y-axis
	for (int iCoordinateY = 0; iCoordinateY < mMapHeight; ++iCoordinateY) {
		// Loop through the x-axis
		for (int iCoordinateX = 0; iCoordinateX < mMapWidth; ++iCoordinateX) {
			// Calculate the corners of each cell
			int iLeft   = (iBorder + (iBlockSizeX * iCoordinateX));
			int iRight  = (iLeft + iBlockSizeX);
			int iTop    = (iBorder + (iBlockSizeY * iCoordinateY));
			int iBottom = (iTop + iBlockSizeY);
			// Draw a green rectangle if this is a wall
			if (iMemory[iCoordinateY][iCoordinateX] == 1) {
				// Render the cell
				Rectangle(hdcSurface, iLeft, iTop, iRight, iBottom);
			}
		}
	}
	// Restore the original brush
	SelectObject(hdcSurface, hbrOldBrush);
	// Restore the original pen
	SelectObject(hdcSurface, penOldPen);
}
// Test Route Method
double GeneticAlgorithmMap::TestRoute(const vector<int> &vPath, GeneticAlgorithmMap &cMemory) {
	// Define the positions
	int iPositionX = mStartX;
	int iPositionY = mStartY;
	// Loop through the paths
	for (int iDirection = 0; iDirection < vPath.size(); ++iDirection) {
		// Determine the direction
		switch (vPath[iDirection]) {
			// North
			case 0 : 
				// Check the boundaries
				if (((iPositionY - 1) < 0) || (iMap[(iPositionY - 1)][iPositionX] == 1)) {
					// Done
					break;
				} else {
					// Decriment Y-axis
					iPositionY -= 1;
				}
				// Done
				break;
			// South
			case 1 : 
				// Check the boundaries
				if (((iPositionY + 1) >= mMapHeight) || (iMap[(iPositionY + 1)][iPositionX] == 1)) {
					// Done
					break;
				} else {
					// Increment Y-axis
					iPositionY += 1;
				}
				// Done
				break;
			// East
			case 2 : 
				// Check the boundaries
				if (((iPositionX + 1) >= mMapWidth) || (iMap[iPositionY][(iPositionX + 1)] == 1)) {
					// Done
					break;
				} else {
					// Increment X-axis
					iPositionX += 1;
				}
				// Done
				break;
			// West
			case 3 : 
				// Check the boundaries
				if (((iPositionX - 1) < 0) || (iMap[iPositionY][iPositionX - 1] == 1)) {
					// Done
					break;
				} else {
					// Decrement X-axis
					iPositionX -= 1;
				}
				// Done
				break;
		}
		// Set the memory set
		cMemory.iMemory[iPositionY][iPositionX] = 1;
	}
	// Assign fitness score proportional to the organism's distance from the exit
	int iDifferenceX = abs(iPositionX - mEndX);
	int iDifferenceY = abs(iPositionY - mEndY);
	// Run the algorithm
	return (1 / (double)(iDifferenceX + iDifferenceY + 1));
}
// Reset Memory Method
void GeneticAlgorithmMap::ResetMemory() {
	// Loop through the y-axis
	for (int iCoordinateY = 0; iCoordinateY < mMapHeight; ++iCoordinateY) {
		// Loop through the x-axis
		for (int iCoordinateX = 0; iCoordinateX < mMapWidth; ++iCoordinateX) {
			// Reset the coordinates
			iMemory[iCoordinateY][iCoordinateX] = 0;
		}
	}
}
