// Application Definitions
#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
// Application Headers
#include <vector>
#include <sstream>
#include "Definitions.h"
#include "GeneticAlgorithmMap.h"
#include "Utilities.h"
// Namespace Definition
using namespace std;
// Genome structure
struct Genome {
	std::vector<int> vBits;
	double           dFitness;
	// Fitness structure definition
	Genome() : dFitness(0){}
	// Genome constructor definition
	Genome(const int iNumberOfBits) : dFitness(0) {
		// Create a random bit string
		for (int iBit = 0; iBit < iNumberOfBits; ++iBit) {
			// Append the bit
			vBits.push_back(RandomInteger(0, 1));
		}
	}
};
// Genetic Algorithm Class Definition
class GeneticAlgorithm {
// Private Properties
protected:
	std::vector<Genome> mGenomes;
	int                 mPopulationSize;
	double              mCrossoverRate;
	double              mMutationRate;
	int                 mChromosomeLength;
	int                 mGeneLength;
	int                 mFittestGenome;
	double              mBestFitnessScore;
	double              mTotalFitnessScore;
	int                 mGeneration;
	GeneticAlgorithmMap mMap;
	GeneticAlgorithmMap mBrain;
	bool                mBusy;
	// Mutation Definition
	void Mutate(std::vector<int> &vBits);
	// Crossover Definition
	void Crossover(const std::vector<int> &vMother, const std::vector<int> &vFather, std::vector<int> &vOffspringAlpha, std::vector<int> &vOffspringBeta);
	// Selection Definition
	Genome& Selection();
	// Update Fitness Score Definition
	void UpdateFitnessScores();
	// Decoding Definition
	std::vector<int> Decode(const std::vector<int> &vEncodedBits);
	// Binary to Integer Conversion Definition
	int BinaryToInteger(const std::vector<int> &vBinary);
	// Population Creation Definition
	void CreatePopulation();
// Public Properties
public:
	// GeneticAlgorithm Constructor Definition
	GeneticAlgorithm(
		double dCrossoverRate, 
		double dMutationRate, 
		int iPopulationSize, 
		int iNumberOfBits, 
		int iGeneLength) : mCrossoverRate(dCrossoverRate), mMutationRate(dMutationRate), mPopulationSize(iPopulationSize), mChromosomeLength(iNumberOfBits), mTotalFitnessScore(0.0), mGeneLength(iGeneLength), mBusy(false) {
			// Create a new population
			CreatePopulation();
	};
	// Execution Definition
	void Execute(HWND hWindow);
	// Render Definition
	void Render(int cxClient, int cyClient, HDC hdcSurface);
	// Epoch Definition
	void Epoch();
	// Accessor Method Definitions
	int Generation() {
		// Return the current generation
		return mGeneration;
	};
	int GetFittest() {
		// Return the fittest genome
		return mFittestGenome;
	};
	bool Started() {
		// Return the busy state
		return mBusy;
	};
	// Algorithm Destructor Definition
	void Stop() {
		// Stop the algorithm
		mBusy = false;
	};
};
#endif
