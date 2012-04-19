#include <iostream>
#include std::vector;

struct Neuron {
    // The number of inputs into the neuron
    int iInputs;
    // The weights for each of the inputs
    vector<double> vWeight;
    // Define the usage
    Neuron(int iInputs);
}

struct NeuronLayer {
    // The number of neurons in this layer
    int iNeurons;
    // The layer of neurons
    vector<Neuron> vNeurons;
    // Define the usage
    NeuronLayer(int iNeurons, int iInputsPerNeuron);
}

Neuron::Neuron(int iInputs) : iInputs(iInputs + 1) {
    // Loop to the number of inputs
    for (int iInput = 0; iInput < iInputs; iInput ++) {
        // Add the weight for this this input with a random value
        vWeight.push_back(RandomClamped());
    }
}

class NeuralNetwork {
private:
    int iInputs;
    int iOutputs;
    int iHiddenLayers;
    int iNeuronsPerHiddenLayer;
    vector<NeuronLayer>vNeuronLayers;
    
public:
    NeuralNetwork();
    // Network creation method
    void CreateNetwork();
    // Weight retreival method
    vector<double>GetWeights()const;
    // Wieght number retreival method
    int GetNumberOfWeights()const;
    // Weight replacement method
    void SetWeights(vector<double> &vWeights);
    // Output calculator method
    vector<double>Calculate(vector<double> &vInputs);
    // Sigmoid method
    inline double Sigmoid(double iActivation, double iResponse);
};

vector<double> NeuralNetwork::Calculate(vector<double> &vInputs) {
    // Placeholder for all of the output results from each layer
    vector<double> vLayerOutputs;
    int iWeight = 0;
    // Check that we have the correct amount of inputs
    if (vInputs.size() != iInputs) {
        // Return an empty vector
        return vLayerOutputs;
    }
    // Loop through the layers
    for (int iLayer = 0; iLayer < (iHiddenLayers + 1); iLayer ++) {
        // Check the layer
        if (iLayer > 0) {
            vInputs = vLayerOutputs;
        }
        // Clear the outputs
        vLayerOutputs.clear();
        // Reset the weight
        iWeight = 0;
        // Loop throught the nerons and run the formula on the inputs and weights
        for (int iNeuron = 0; iNeuron < vNeuronLayers[iLayer].iNeurons; iNeuron ++) {
            // Input placeholder
            int iNetworkInput = 0;
            // Grab the number of inputs
            int iInputs       = vNeuronLayers[iLayer].vNeurons[iNeuron].iInputs;
            // Loop through the weights
            for (int iNeuronWeight = 0; iNeuronWeight < iInputs; iNeuronWeight ++) {
                // Sum the weight/input multiplicatives
                iNetworkInput += vNeuronLayers[iLayer].vNeurons[iNeuron].vWeights[(iNeuronWeight] * vInputs[iWeight ++];
            }
        }
    }
}