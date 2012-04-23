#!/usr/bin/perl -w
# Use strict syntax
use strict;
# Use our neural network
use NeuralNetwork;
# Use our debugger
use Data::Dumper;
# Set the input values
my(@aInputValues);
# Set the input weights
my(@aInputWeights);
# File placeholder
my($sData);
# Open the test file
open(my $hTemplate, "<4.html")
	or die("Unable to open file: $!");
# Read the test file
while (<$hTemplate>) {
	# Remove special characters
	chomp;
	# Append the string
	$sData .= $_;
}
# Remove tabs
$sData =~ s/\t+//g;
# Remove newlines
$sData =~ s/\n+//g;
$sData =~ s/\r+\n+//g;
# Remove double spaces
$sData =~ s/\s+/ /g;
# Process the data
while ($sData =~ m/\<td\s*?class=\"([a-zA-Z0-9]+)\"\>&nbsp;\<\/td\>/g) {
	# Check the input
	if ($1 eq "green") {
		# Add the input
		push(@aInputValues,  0);
	} else {
		# Add the input
		push(@aInputValues,  1);

	}
}
# Set the network instance
NeuralNetwork::getInstance()                              # Grab the instance
	->clearStorage()                                      # Clear the DB (optional)
	->setThreshold(int(rand(99999999999)))                # Set the threshold
	->addLayer(3, scalar(@aInputValues), \@aInputValues); # Add a layer 
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
