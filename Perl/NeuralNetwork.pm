#!/usr/bin/perl -w
# Define the package name
package NeuralNetwork;
# Use strict syntax
use strict;
# Use our database connectors
use DBI;
# Use our debugger
use Data::Dumper;
# Use Perl's trigonometry packages
use Math::Trig;
# Our instance placeholder
my($oInstance);
 #############################################################################
### Singleton #################################################################
 #############################################################################
sub getInstance {
	# Check for an existing instance
	if ($oInstance) {
		# Simply return the existing instance
		return $oInstance;
	} else {
		# Return a new instance
		return new NeuralNetwork();
	}
}
 #############################################################################
### Constructor ###############################################################
 #############################################################################
sub new {
	# Grab the class name
	my($sClass) = shift;
	# Setup the instance
	my($oSelf)  = {
		iBias      => -1.0, 
		oDbc       => DBI->connect("dbi:SQLite:dbname=Db/NeuralNetwork.db", "", "", {
			RaiseError => 1
		}),
		oLayers    => {},
		iThreshold => 0
	};
	# Set the instance
	$oInstance ||= bless($oSelf, $sClass);
	# Return the instance
	return $oInstance;
}

 ############################################################################
### Public ###################################################################
 ############################################################################
sub addInput {
	# Grab the instance
	my($oSelf)   = shift;
	# Grab the layer identifier
	my($iLayer)  = shift;
	# Grab the neuron identifier
	my($iNeuron) = shift;
	# Grab the value
	my($iValue)  = shift;
	# Generate the weight
	my($iWeight) = $oSelf->getWeight();
	# Append the input
	$oSelf->{"oLayers"}{$iLayer}{$iNeuron}{$oSelf->storeInput($iNeuron, $iLayer, $iValue, $iWeight)} = {
		iInput  => $iValue, 
		iWeight => $iWeight
	};
	# Return instance
	return $oSelf;
}
sub addInputs {
	# Grab the instance
	my($oSelf)   = shift;
	# Grab the layer identifier
	my($iLayer)  = shift;
	# Grab the neuron identifier
	my($iNeuron) = shift;
	# Grab the number of inputs
	my($iInputs) = shift;
	# Loop to the inputs
	for (my $iInput = 0; $iInput < $iInputs; $iInput ++) {
		# Append the input to the inputs
		push(@{$oSelf->{"oLayers"}{$iLayer}{$iNeuron}}, {
			iInput  => $iInput,
			iWeight => $oSelf->getWeight()
		});
	}
	# Return instance
	return $oSelf; 
}
sub addLayer {
	# Grab the instance, number of neurons number of inputs and input values
	my($oSelf, $iNeurons, $iInputs, $aInputValues) = @_;
	# Generate the layer id
	my($iLayer)                                    = $oSelf->storeLayer($iNeurons);
	# Add the layer
	$oSelf->{"oLayers"}{$iLayer}                    = {};
	# Check for neuron count
	if ($iNeurons) {
		# Go ahead and add the neurons
		for (my $iNeuron = 0; $iNeuron < $iNeurons; $iNeuron ++) {
			# Add the neuron
			$oSelf->addNeuron($iLayer, $iInputs, $aInputValues);
		}
	}
	# Return instance
	return $oSelf;
}
sub addNeuron {
	# Grab the instance, layer identifier, number of inputs and input values
	my($oSelf, $iLayer, $iInputs, $aInputValues)                         = @_;
	# Generate a neuron id
	my($iNeuron)                                                         = $oSelf->storeNeuron($iLayer, $iInputs);
	# Add the neuron
	$oSelf->{"oLayers"}{$iLayer}{$iNeuron}                               = {};
	# Loop through the inputs and set the values
	for (my $iInput = 1; $iInput < $iInputs; $iInput ++) {
		# Add the input
		$oSelf->addInput($iLayer, $iNeuron, @{$aInputValues}[$iInput]);
	}
	# Return instance
	return $oSelf;
}
sub clearStorage {
	# Grab the instance
	my($oSelf) = shift;
	# Generate layer delete statement
	my($oLayerStatement)  = $oSelf->{"oDbc"}->prepare("DELETE FROM Layers;");
	# Generate neuron delete statement
	my($oNeuronStatement) = $oSelf->{"oDbc"}->prepare("DELETE FROM Neurons;");
	# Generate input delete statement
	my($oInputStatement)  = $oSelf->{"oDbc"}->prepare("DELETE FROM Inputs;");
	# Generate output delete statement
	my($oOutputStatement) = $oSelf->{"oDbc"}->prepare("DELETE FROM Output;");
	# Execute the statements
	$oLayerStatement->execute();
	$oNeuronStatement->execute();
	$oInputStatement->execute();
	$oOutputStatement->execute();
	# Return instance
	return $oSelf;
}
sub dumpNetwork {
	# Grab the instance
	my($oSelf) = shift;
	# Start the map
	print("\n");
	# Loop through the layers
	while (my($iLayer, $oNeurons) = each(%{$oSelf->{"oLayers"}})) {
		# Print the layer id
		print($iLayer, " => ", "\n");
		# Loop through the neurons
		while (my($iNeuron, $oInput) = each(%{$oSelf->{"oLayers"}{$iLayer}})) {
			# Print the neuron id
			print("\t", $iNeuron, " => ", "\n");
			# Loop through the inputs
			while (my($sKey, $oData) = each(%{$oInput})) {
				# Print the input value
				print("\t\t", "iInput => ", $oData->{"iInput"}, "\n");
				# Print the input weight
				print("\t\t", "iWeight => ", $oData->{"iWeight"}, "\n");
				# Print another newline
				print("\n");
			}
		}
	}
	# Space out the map
	print("\n\n");
	# Grab the activation
	my(@aActivations) = $oSelf->getActivation();
	# Start the activation print
	print("aActivations => ", "\n");
	# Loop through the activations
	for my $oActivation (@aActivations) {
		# Print the active status
		print("\t", "bActive => ", $oActivation->{"bActive"}, "\n");
		# Print the layer
		print("\t", "iLayerId => ", $oActivation->{"iLayerId"}, "\n");
		# Print the neuron
		print("\t", "iNeuronId => ", $oActivation->{"iNeuronId"}, "\n");
		# Print the output
		print("\t", "iOutput => ", $oActivation->{"iOutput"}, "\n");
		# Print the sigmoid
		print("\t", "iSigmoid => ", $oActivation->{"iSigmoid"}, "\n\n");
	}
	# Finish the map
	print("\n\n");
	# Return
	return undef;
}
sub storeActivation {
	# Grab the instance and activation object
	my($oSelf, $oActivation) = @_;
	# Return the activation id
	return $oSelf->{"oDbc"}->last_insert_id("", "", "Output", "");
}
sub storeInput {
	# Grab the instance, neuron ID, layer ID, value and weight
	my($oSelf, $iNeuronId, $iLayerId, $iValue, $iWeight) = @_;
	# Generate the statement
	my($oStatement)                                      = $oSelf->{"oDbc"}->prepare("INSERT INTO Inputs (iNeuronId, iLayerId, iValue, iWeight, sCreated) VALUES (?, ?, ?, ?, datetime())");
	# Execute the statement
	$oStatement->execute($iNeuronId, $iLayerId, $iValue, $iWeight);
	# Return the input id
	return $oSelf->{"oDbc"}->last_insert_id("", "", "Inputs", "");
}
sub storeLayer {
	# Grab the instance and neuron count
	my($oSelf, $iNeurons) = @_;
	# Generate the statement
	my($oStatement)       = $oSelf->{"oDbc"}->prepare("INSERT INTO Layers (iNeurons, sCreated) VALUES (?, datetime())");
	# Execute the statement
	$oStatement->execute($iNeurons);
	# Return the layer id
	return $oSelf->{"oDbc"}->last_insert_id("", "", "Layers", "");
}
sub storeNeuron {
	# Grab the instance, layer ID and input count
	my($oSelf, $iLayerId, $iInputs) = @_;
	# Generate the statement
	my($oStatement)                 = $oSelf->{"oDbc"}->prepare("INSERT INTO Neurons (iLayerId, iInputs, sCreated) VALUES (?, ?, datetime())");
	# Execute the statement
	$oStatement->execute($iLayerId, $iInputs);
	# Return the neuron id
	return $oSelf->{"oDbc"}->last_insert_id("", "", "Neurons", "");
}
 #############################################################################
### Getters ###################################################################
 #############################################################################
sub getActivation {
	# Grab the instance 
	my($oSelf)       = shift;
	# Grab the layer
	my($iLayer)      = shift or undef;
	# Grab the neuron identifier
	my($iNeuron)     = shift or undef;
	# Activations object placeholder
	my(@aActivations);
	# Set the activation placeholder
	my($iActivation) = 0;
	# Check for a neuron
	if ($iLayer and $iNeuron) {
		# Check for the layer and neuron
		if ($oSelf->{"oLayers"}{$iLayer} and $oSelf->{"oLayers"}{$iLayer}{$iNeuron}) {
			# Loop through the inputs
			while (my($sKey, $oInput) = each(%{$oSelf->{"oLayers"}{$iLayer}{$iNeuron}})) {
				# Multiply to get the output
				$iActivation += (int $oInput->{"iWeight"} * int $oInput->{"iInput"});
			}
			# push the activation to the array
			push(@aActivations, {
				"bActive"   => (($iActivation ge $oSelf->{"iThreshold"}) ? 1 : 0), 
				"iLayerId"  => $iLayer, 
				"iNeuronId" => $iNeuron, 
				"iOutput"   => $iActivation, 
				"iSigmoid"  => $oSelf->getSigmoid($iActivation)
			});
		} else {
			# The layer or neuron doesn't exist
			return undef;
		}
	} elsif ($iLayer) { # Check for a layer
		# Check for the layer
		if ($oSelf->{"oLayers"}{$iLayer}) {
			# Loop through the neurons in the layer
			while (my($iNeuronId, $oNeuron) = each(%{$oSelf->{"oLayer"}{$iLayer}})) {
				# Reset the activation
				$iActivation = 0;
				# Loop through the inputs
				while (my($sKey, $oInput) = each(%{$oSelf->{"oLayers"}{$iLayer}{$iNeuronId}})) {
					# Multiply to get the output
					$iActivation += (int $oInput->{"iWeight"} * $oInput->{"iInput"});
				}
				# push the activation to the array
				push(@aActivations, {
					"bActive"   => (($iActivation ge $oSelf->{"iThreshold"}) ? 1 : 0), 
					"iLayerId"  => $iLayer,
					"iNeuronId" => $iNeuronId,
					"iOutput"   => $iActivation, 
					"iSigmoid"  => $oSelf->getSigmoid($iActivation)
				});
			}
		} else {
			# The layer does not exist
			return undef;
		}
	} else {
		# Loop through the layers
		while (my($iLayerId, $oNeurons) = each(%{$oSelf->{"oLayers"}})) {
			# Loop through the neurons
			while (my($iNeuronId, $oNeuron) = each(%{$oSelf->{"oLayers"}{$iLayerId}})) {
				# Reset the activation
				$iActivation = 0;
				# Loop through the inputs
				while (my($sKey, $oInput) = each(%{$oSelf->{"oLayers"}{$iLayerId}{$iNeuronId}})) {
					# Multiply to get the output
					$iActivation += (int $oInput->{"iWeight"} * $oInput->{"iInput"});
				}
				# push the activation to the array
				push(@aActivations, {
					"bActive"   => (($iActivation ge $oSelf->{"iThreshold"}) ? 1 : 0), 
					"iLayerId"  => $iLayerId, 
					"iNeuronId" => $iNeuronId,
					"iOutput"   => $iActivation, 
					"iSigmoid"  => $oSelf->getSigmoid($iActivation)
				});
			}
		}
	}
	# Return the activations
	return @aActivations;
}
sub getSigmoid {
	# Grab the instance and activation
	my($oSelf, $iActivation) = @_;
	# Return the output
	return tanh($iActivation);
}
sub getThreshold {
	# Grab the instance
	my($oSelf) = shift;
	# Return the threshold
	return $oSelf->{"iThreshold"};
}
sub getWeight {
	# Grab the instance
	my($oSelf)    = shift;
	# Generate the random number
	my($iWeight)  = rand(1.0);
	# Now generate a random boolean
	if (int(rand(2))) {
		# Make the weight negative
		$iWeight *= -1;
	}
	# Return a random weight
	return $iWeight;
}
 #############################################################################
### Setters ###################################################################
 #############################################################################
sub setThreshold {
	# Grab the instance and threshold
	my($oSelf, $iThreshold) = @_;
	# Set the threshold into the system
	$oSelf->{"iThreshold"}  = $iThreshold;
	# Return instance
	return $oSelf;
}
 #############################################################################
### Destructor ################################################################
 #############################################################################
1;
__END__;