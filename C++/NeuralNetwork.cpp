// Load our libraries
#include <iostream>
#include <vector>

struct Neuron {
	// Define the number of inputs
	int iInputs;
	// This holds the weight for each input
	std::vector<double> vWeights;
	// Usage
	Neuron(int iNumberOfInputs);
};

struct Layer {
	// Define the number of neurons
	int iNeurons;
	// This holds each neuron
	std::vector<Neuron> vNeurons;
	// Usage
	Layer(int iNumberOfNeurons, int iInputsPerNeuron);
};

Neuron::Neuron(int iNumberOfInputs) : iInputs(iNumberOfInputs + 1) {
	// Loop through the inputs adding one weight for the bias
	for (int iInput = 0; iInput < (iNumberOfInputs + 1); ++ iInput) {
		// Set the weight
		vWeights.push_back(RandomClamped());
	}
}

class NeuralNetwork {
private:
	// The number of inputs per neuron
	int iInputs;
	// The number of outputs per neuron
	int iOutputs;
	// The number of hidden layers
	int iHiddenLayers;
	// Number of inputs for each hidden layer
	int iNeuronsPerHiddenLayer;
	// Our vector of layers
	std::vector<Layer> vLayers;
public:
	// Our class name
	NeuralNetwork();
	// Our network creation wizard
	void createNetwork();
	// Grabs the weights from the network
	std::vector<double> getWeights() const;
	// Grabs the total number of weights from the network
	int getNumberOfWeights() const;
	// Replaces the weights with new ones
	void setWeights(std::vector<double> &vWeights);
	// Calculates the outputs from a set of inputs
	std::vector<double>getOutputs(std::vector<double> &vInputs);
	// Sigmoid response curve
	inline double getSigmoid(double iActivation, double iResponse);
};

std::vector<double> NeuralNetwork::createNetwork(std::vector<double> &vInputs) {
	// Output placeholder
	std::vector<double> vOutputs;
	// Current weight
	int iCurrentWeight = 0;
	// Make sure we have the proper number of inputs
	if (vInputs.size() != iInputs) {
		// Return an empty vector of outputs
		return vOutputs;
	}
	// Loop through the layers
	for (int iHiddenLayer = 0; iHiddenLayer < (iHiddenLayers + 1); ++ iHiddenLayer) {
		// Make sure the current layer is greater than 0
		if (iHiddenLayer > 0) {
			// Set the inputs to the outputs
			vInputs = vOutputs;
		}
		// Clear the outputs
		vOutputs.clear();
		// Reset the current weight
		iCurrentWeight = 0;
		// Loop through the neurons running the algorithm and sigmoid
		for (int iNeuron = 0; iNeuron < vLayers[iHiddenLayer].iNumberOfNeurons; ++ iNeuron) {
			// Set the net input
			double iNetInput    = 0;
			// Set the number of inputs
			int iNumberOfInputs = vLayers[iHiddenLayer].vNeurons[iNeuron].iInputs;
			// Loop through the inputs adding the weight
			for (int iInput = 0; iInput < (iNumberOfInputs - 1); ++ iInput) {
				// Multiply the weights by the inputs
				iNetInput += vLayers[iHiddenLayer].vNeurons[iNeuron].vWeights[iInput] * vInputs[iCurrentWeight ++];
			}
			// Add the bias
			iNetInput += vLayers[iHiddenLayer].vNeurons[iNeuron].vWeights[(iNumberOfInputs - 1)] * CParams::dBias;
			// Store the output
			vOutputs.pushBack(getSigmoid(iNetInput, CParams::dActivationResponse));
			// Reset the current weight
			iCurrentWeight = 0;
		}
	}
	// Return the outputs
	return vOutputs;
}
