// Application Headers
#include "GeneticAlgorithm.h"
// Selction Method
Genome& GeneticAlgorithm::Selection() {
	double dSlice          = (RandomFloat() * mTotalFitnessScore);
	double dTotal          = 0.0;
	int    iSelectedGenome = 0;
	// Loop through the population
	for (int iGenome = 0; iGenome < mPopulationSize; ++iGenome) {
		// Increment the total fitness
		dTotal += mGenomes[iGenome].dFitness;
		// Is this the Genome we are looking for
		if (dTotal > dSlice) {
			// Set the selected genome
			iSelectedGenome = iGenome;
			// End the loop
			break;
		}
	}
	// Return the selected genome
	return mGenomes[iSelectedGenome];
}
// Mutation Method
void GeneticAlgorithm::Mutate(std::vector<int> &vBits) {
	// Loop through the bits
	for (int iBit = 0; iBit < (int) vBits.size(); ++iBit) {
		// Should this bit be flipped
		if (RandomFloat() < mMutationRate) {
			// Flip the bit
			vBits[iBit] = !vBits[iBit];
		}
	}
}
// Crossover Method
void GeneticAlgorithm::Crossover(const std::vector<int> &vMother, const std::vector<int> &vFather, std::vector<int> &vOffspringAlpha, std::vector<int> &vOffspringBeta) {
	// Just return parents as offspring, dependent on the rate or if the parents are the same
	if ((RandomFloat() > mCrossoverRate) || (vMother == vFather)) {
		// Set the alpha offspring
		vOffspringAlpha = vMother;
		// Set the beta offspring
		vOffspringBeta  = vFather;
		// Return
		return;
	}
	// Determine the crossover point
	int iCrossoverPoint = RandomInteger(0, (mChromosomeLength - 1));
	// Swap the bits
	for (int iGenome = 0; iGenome < iCrossoverPoint; ++iGenome) {
		// Add an alpha offspring
		vOffspringAlpha.push_back(vMother[iGenome]);
		// Add a beta offspring
		vOffspringBeta.push_back(vFather[iGenome]);
	}
	for (int iMotherGenome = 0; iMotherGenome < (int) vMother.size(); ++iMotherGenome) {
		// Add another alpha offspring
		vOffspringAlpha.push_back(vFather[iMotherGenome]);
		// Add another beta offspring
		vOffspringBeta.push_back(vMother[iMotherGenome]);
	}
}
// Execution Method
void GeneticAlgorithm::Execute(HWND hWindow) {
	// Create a random population of genomes
	CreatePopulation();
	// Start the algorithm
	mBusy = true;
}
// Create Population Method
void GeneticAlgorithm::CreatePopulation() {
	// Clear existing population
	mGenomes.clear();
	// Loop through the population
	for (int iGenome = 0; iGenome < mPopulationSize; ++iGenome) {
		// Add the genome
		mGenomes.push_back(Genome(mChromosomeLength));
	}
	// Reset all variables
	mGeneration        = 0;
	mFittestGenome     = 0;
	mBestFitnessScore  = 0;
	mTotalFitnessScore = 0;
}
// Epoch Method
void GeneticAlgorithm::Epoch() {
	// Update the fitness scores
	UpdateFitnessScores();
	// Create a new population
	int iNewOffspring = 0;
	// Create a placeholder for the offspring
	std::vector<Genome> vOffspringGenomes;
	// Loop through the babies
	while (iNewOffspring < mPopulationSize) {
		// Select 2 parents
		Genome vMother = Selection();
		Genome vFather = Selection();
		// Offspring placeholders
		Genome vOffspringAlpha, vOffspringBeta;
		// Crossover
		Crossover(vMother.vBits, vFather.vBits, vOffspringAlpha.vBits, vOffspringBeta.vBits);
		// Mutate
		Mutate(vOffspringAlpha.vBits);
		Mutate(vOffspringBeta.vBits);
		// Add the offspring to the new population
		vOffspringGenomes.push_back(vOffspringAlpha);
		vOffspringGenomes.push_back(vOffspringBeta);
		// Increment the offspring
		iNewOffspring += 2;
	}
	// Copy the offspring back into the initial population
	mGenomes = vOffspringGenomes;
	// Increment the generations
	++mGeneration;
}
// Update Fitness Scores Method
void GeneticAlgorithm::UpdateFitnessScores() {
	// Reset the variables
	mFittestGenome     = 0;
	mBestFitnessScore  = 0;
	mTotalFitnessScore = 0;
	// Setup a temporary brain
	GeneticAlgorithmMap cTemporaryMemory;
	// Update the fitness scores and keep track of the fittest so far
	for (int iGenome = 0; iGenome < mPopulationSize; ++iGenome) {
		// Setup a directions placeholder
		std::vector<int> vDirections = Decode(mGenomes[iGenome].vBits);
		// Decode each genomes chromosome into a vector or directions
		mGenomes[iGenome].dFitness = mMap.TestRoute(vDirections, cTemporaryMemory);
		// Update the total
		mTotalFitnessScore += mGenomes[iGenome].dFitness;
		// Check to see if this genome is the fittest thus far
		if (mGenomes[iGenome].dFitness > mBestFitnessScore) {
			// Store it
			mBestFitnessScore = mGenomes[iGenome].dFitness;
			// Set the fittest genome
			mFittestGenome    = iGenome;
			// Set the temporary brain to the real brain
			mBrain            = cTemporaryMemory;
			// Has the solution been found
			if (mGenomes[iGenome].dFitness == 1) {
				// A solution has been found, stop the algorithm
				mBusy = false;
			}
		}
		// Reset the temporary brain
		cTemporaryMemory.ResetMemory();
	}
}
// Decode Method
std::vector<int> GeneticAlgorithm::Decode(const std::vector<int> &vEncodedBits) {
	// Our directions placeholder
	std::vector<int> vDirections;
	// Loop through the chromosomes
	for (int iGene = 0; iGene < (int) vEncodedBits.size(); iGene += mGeneLength) {
		// Current gene placeholder
		std::vector<int> vCurrentGene;
		// Loop through the bits
		for (int iBit = 0; iBit < mGeneLength; ++iBit) {
			// Add the bit
			vCurrentGene.push_back(vEncodedBits[(iGene + iBit)]);
		}
		// Decode the bit
		vDirections.push_back(BinaryToInteger(vCurrentGene));
	}
	// Return the decoded directions
	return vDirections;
}
// Binary To Integer Method
int GeneticAlgorithm::BinaryToInteger(const std::vector<int> &vBinary) {
	// Set the default value
	int iValue      = 0;
	// Set the default multiplier
	int iMultiplier = 1;
	// Loop through the bits
	for (int iBit = vBinary.size(); iBit > 0; --iBit) {
		// Set the new value
		iValue += (vBinary[(iBit - 1)] * iMultiplier);
		// Set the new multiplier
		iMultiplier *= 2;
	}
	// Return the value
	return iValue;
}
// Render Method
void GeneticAlgorithm::Render(int cxClient, int cyClient, HDC hdcSurface) {
	// Render the map
	mMap.Render(cxClient, cyClient, hdcSurface);
	// Render the best route
	mBrain.RenderFromMemory(cxClient, cyClient, hdcSurface);
	// Render additional information
	// Generation Text
	string sGeneration = "Generation: " + IntegerToString(mGeneration);
	// Render Generation Text
	TextOut(hdcSurface, 5, 0, sGeneration.c_str(), sGeneration.size());
	// Check the busy state
	if (!mBusy) {
		// Start text
		string sStartText = "Press Return to start a new run";
		// Render Start text
		TextOut(hdcSurface, ((cxClient / 2) - (sStartText.size() * 3)), (cyClient - 20), sStartText.c_str(), sStartText.size());
	} else {
		// Stop Text
		string sStopText = "Press Spacebar to stop";
		// Render the stop text
		TextOut(hdcSurface, ((cxClient / 2) - (sStopText.size() * 3)), (cyClient - 20), sStopText.c_str(), sStopText.size());
	}
}
