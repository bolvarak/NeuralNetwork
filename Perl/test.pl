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
# Generate and display the neuron output
print "\n";
print "--------------------------------------------------------------------------------\n";
print "--- The Outcome Was ------------------------------------------------------------\n";
print "--------------------------------------------------------------------------------\n";
print "--- Successful Bias -- ", &networkTrainer(-1.00)->{"iSuccessBias"}, " --------------------------------------------------------\n";
print "--------------------------------------------------------------------------------\n";
print "--------------------------------------------------------------------------------\n";
print "\n";
# Define the trainer
sub networkTrainer {
	# Grab the set values and weights
	glob @aInputValues;
	glob @aInputWeights;
	# Grab the new bias
	my($iBias) = shift;
	# Instantiate the neural network
	my($oNetwork) = new NeuralNetwork();
	# Set the bias
	$oNetwork->setBias(-1.00);
	# Add the layer
	$oNetwork->addLayer(1, scalar(@aInputValues), \@aInputValues);
	# Grab the activation objects
	my(@aActivations) = $oNetwork->getActivation();
	# Check the activation
	if (int $aActivations[0]->{"iOutput"} ne 1) {
		# Return this function
		return &networkTrainer($iBias += 0.01);
	}
	# Return success
	return {
		"iSuccessBias" => $iBias
	};
}