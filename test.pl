#!/usr/bin/perl -w
# Use strict syntax
use strict;
# Use our neural network
use NeuralNetwork;
# Set the network instance
NeuralNetwork::getInstance()                # Grab the instance
	->setThreshold(int(rand(99999999999))); # Set the threshold
# Let's generate some neurons and inputs
for my $iNeuron (1 .. 1000) {
	# Add the neuron
	NeuralNetwork::getInstance()->addNeuron($iNeuron);
	# Now let's add the inputs
	for my $iInput (1 .. 100) {
		# Add the input
		NeuralNetwork::getInstance()->addInput($iNeuron, int(rand(999999)), int(rand(1999999)));
	}
}
# Print the neuron map
# NeuralNetwork::getInstance()->dumpNeurons();
# Generate and display the neuron output
print "\n";
print "-------------------------------------\n";
print "--- The Activation Results Is -------\n";
print "-------------------------------------\n";
print NeuralNetwork::getInstance()->getActivation()->{"bActive"};
print " or ", ((NeuralNetwork::getInstance()->getActivation()->{"bActive"} eq 1) ? "True" : "False");
print "\n\n";
print "-------------------------------------\n";
print "--- The Total Outcome Was -----------\n";
print "-------------------------------------\n";
print NeuralNetwork::getInstance()->getActivation()->{"iOutput"};
print "\n\n";