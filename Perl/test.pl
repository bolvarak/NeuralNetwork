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
for my $iNeuron (1 .. 10) {
	# Add the neuron
	NeuralNetwork::getInstance()->addNeuron(1, $iNeuron);
	# Now let's add the inputs
	for my $iInput (1 .. 10) {
		# Add the input
		NeuralNetwork::getInstance()->addInput(1, $iNeuron, int(rand(999999)), int(rand(1999999)));
	}
}
# Grab the activation object
my($oActivation) = NeuralNetwork::getInstance()->getActivation();
# Print the neuron map
NeuralNetwork::getInstance()->dumpNetwork();
# Generate and display the neuron output
# print "\n";
# print "-------------------------------------\n";
# print "--- The Activation Results Is -------\n";
# print "-------------------------------------\n";
# print $oActivation->{"bActive"};
# print " or ", (($oActivation->{"bActive"} eq 1) ? "True" : "False");
# print "\n\n";
# print "-------------------------------------\n";
# print "--- The Total Outcome Was -----------\n";
# print "-------------------------------------\n";
# print $oActivation->{"iOutput"};
# print "\n\n";