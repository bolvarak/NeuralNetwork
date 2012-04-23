#!/usr/bin/perl -w
# Use strict syntax
use strict;
# Use our neural network
use NeuralNetwork;
# Set the input values
my(@aInputValues) = (1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0);
# Set the network instance
NeuralNetwork::getInstance()               # Grab the instance
	->clearStorage()                       # Clear the DB (optional)
	->setThreshold(int(rand(99999999999))) # Set the threshold
	->addLayer(3, 64, \@aInputValues);     # Add a layer 
# Grab the activation object
my($oActivation) = NeuralNetwork::getInstance()->getActivation();
# Print the neuron map
NeuralNetwork::getInstance()->dumpNetwork();
# Generate and display the neuron output
print "\n";
print "-------------------------------------\n";
print "--- The Activation Results Is -------\n";
print "-------------------------------------\n";
print $oActivation->{"bActive"};
print "\n\n";
print "-------------------------------------\n";
print "--- The Total Outcome Was -----------\n";
print "-------------------------------------\n";
print $oActivation->{"iOutput"};
print "\n\n";
print "-------------------------------------\n";
print "--- The Sigmoid Is ------------------\n";
print "-------------------------------------\n";
print $oActivation->{"iSigmoid"};
print "\n\n";
