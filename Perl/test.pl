#!/usr/bin/perl -w
# Use strict syntax
use strict;
# Use our neural network
use NeuralNetwork;
# Set the network instance
NeuralNetwork::getInstance()               # Grab the instance
	->setThreshold(int(rand(99999999999))) # Set the threshold
	->addLayer(1);                         # Add a layer 
# Let's generate some neurons and inputs
for my $iNeuron (1 .. 3) {
	# Add the neuron
	NeuralNetwork::getInstance()      # Instantiate the network
		->addNeuron(1, $iNeuron)      # Add a neuron to the layer
		->addInputs(1, $iNeuron, 64); # Give the neuron some inputs
}
# Grab the activation object
my($oActivation) = NeuralNetwork::getInstance()->getActivation();
# Print the neuron map
# NeuralNetwork::getInstance()->dumpNetwork();
# Generate and display the neuron output
print "\n";
print "-------------------------------------\n";
print "--- The Activation Results Is -------\n";
print "-------------------------------------\n";
print $oActivation->{"bActive"};
print " or ", (($oActivation->{"bActive"} eq 1) ? "True" : "False");
print "\n\n";
print "-------------------------------------\n";
print "--- The Total Outcome Was -----------\n";
print "-------------------------------------\n";
print $oActivation->{"iOutput"};
print "\n\n";