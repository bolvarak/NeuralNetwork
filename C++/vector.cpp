// Load our headers
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
// Use our standard namespace
using namespace std;
// The main function
int main (void) {
	// Define the vector
	std::vector<double> vNumbers;
	// Loop to the max and append the numbers
	for (int iNumber = 0; iNumber < 100; ++iNumber) {
		// Append the number
		vNumbers.push_back(iNumber * time(NULL));
	}
	// Loop through the vector
	for (int iElement = 0; iElement < vNumbers.size(); ++iElement) {
		// Print the number
		cout << "The number is: " << vNumbers[iElement] << endl;
	}
}
