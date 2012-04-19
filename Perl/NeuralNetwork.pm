#!/usr/bin/perl -w
# Define the package name
package NeuralNetwork;
# Use strict syntax
use strict;
# Our instance placeholder
my($oInstance);
###############################################################################
### Singleton ################################################################
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
###############################################################################
### Constructor ##############################################################
#############################################################################
sub new {
	# Grab the class name
	my($sClass) = shift;
	# Setup the instance
	my($oSelf)  = {
		oLayers    => {},
		oNeurons   => {}, 
		iThreshold => 0
	};
	# Set the instance
	$oInstance ||= bless($oSelf, $sClass);
	# Return the instance
	return $oInstance;
}
###############################################################################
### Public ###################################################################
#############################################################################
sub addInput {
	# Grab the instance
	my($oSelf)   = shift;
	# Grab the layer identifier
	my($iLayer)  = shift;
	# Grab the neuron identifier
	my($iNeuron) = shift;
	# Grab the weight
	my($iWeight) = shift;
	# Grab the value
	my($iValue)  = shift;
	# Append the input to the inputs
	push(@{$oSelf->{"oLayers"}{$iLayer}{$iNeuron}}, {
		iValue  => $iValue,
		iWeight => $iWeight
	});
	# Return instance
	return $oSelf; 
}
sub addLayer {
	# Grab the instance, layer identifier and number of neurons
	my($oSelf, $iLayer, $iNeurons) = @_;
	# Add the layer
	$oSelf->{"oLayers"}{$iLayer}   = {};
	# Check for neuron count
	if ($iNeurons) {
		# Go ahead and add the neurons
		for (my $iNeuron = 0; $iNeuron < $iNeurons; $iNeuron ++) {
			# Add the neuron
			$oSelf->addNeuron($iLayer, $iNeuron);
		}
	}
	# Return instance
	return $oSelf;
}
sub addNeuron {
	# Grab the instance, layer identifier and neuron identifier
	my($oSelf, $iLayer, $iNeuron) = @_;
	# Add the neuron
	$oSelf->{"oLayers"}{$iLayer}{$iNeuron} = [];
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
		while (my($iNeuron, @aInputs) = each(%{$oSelf->{"oLayers"}{$iLayer}})) {
			# Print the neuron id
			print("\t", $iNeuron, " => ", "\n");
			# Loop through the inputs
			for my $oInput (@{$oSelf->{"oLayers"}{$iLayer}{$iNeuron}}) {
				# Print the input
				print("\t\t", "iValue => ", $oInput->{"iValue"}, "\n");
				# Print the weight
				print("\t\t", "iWeight => ", $oInput->{"iWeight"}, "\n\n");
			}
		}
	}
	# Space out the map
	print("\n\n");
	# Grab the activation
	my($oActivation) = $oSelf->getActivation();
	# Start the activation print
	print("Activation => ", "\n");
	# Print the active status
	print("\t", "bActive => ", $oActivation->{"bActive"}, "\n");
	# Print the output
	print("\t", "iOutput => ", $oActivation->{"iOutput"}, "\n");
	# Finish the map
	print("\n\n");
	# Return
	return undef;
}
###############################################################################
### Getters ##################################################################
#############################################################################
sub getActivation {
	# Grab the instance 
	my($oSelf)       = shift;
	# Grab the layer
	my($iLayer)      = shift or undef;
	# Grab the neuron identifier
	my($iNeuron)     = shift or undef;
	# Set the activation placeholder
	my($iActivation) = 0;
	# Check for a neuron
	if ($iLayer and $iNeuron) {
		# Check for the layer and neuron
		if ($oSelf->{"oLayers"}{$iLayer} and $oSelf->{"oLayers"}{$iLayer}{$iNeuron}) {
			# Loop through the inputs
			for my $oInput (@{$oSelf->{"oLayers"}{$iLayer}{$iNeuron}}) {
				# Multiply to get the output
				$iActivation += (int $oInput->{"iWeight"} * int $oInput->{"iValue"});
			}
		} else {
			# The layer or neuron doesn't exist
			return undef;
		}
	} elsif ($iLayer) { # Check for a layer
		# Check for the layer
		if ($oSelf->{"oLayers"}{$iLayer}) {
			# Loop through the neurons in the layer
			while (my($iNeuronId, $oNeuron) = each(%{$oSelf->{"oLayer"}{$iLayer}})) {
				# Loop through the inputs
				for my $oInput (@{$oSelf->{"oLayers"}{$iLayer}{$iNeuronId}}) {
					# Multiply to get the output
					$iActivation += (int $oInput->{"iWeight"} * $oInput->{"iValue"});
				}
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
				# Loop through the inputs
				for my $oInput (@{$oSelf->{"oLayers"}{$iLayerId}{$iNeuronId}}) {
					# Multiply to get the output
					$iActivation += (int $oInput->{"iWeight"} * $oInput->{"iValue"});
				}
			}
		}
	}
	# Check the output
	if ($iActivation ge $oSelf->{"iThreshold"}) {
		# Return the output
		return {
			bActive => 1, 
			iOutput => $iActivation
		};
	} else {
		# Return the output
		return {
			bActive => 0, 
			iOutput => $iActivation
		};
	}
}
sub getThreshold {
	# Grab the instance
	my($oSelf) = shift;
	# Return the threshold
	return $oSelf->{"iThreshold"};
}
###############################################################################
### Setters ##################################################################
#############################################################################
sub setThreshold {
	# Grab the instance and threshold
	my($oSelf, $iThreshold) = @_;
	# Set the threshold into the system
	$oSelf->{"iThreshold"}  = $iThreshold;
	# Return instance
	return $oSelf;
}
###############################################################################
### Destructor ###############################################################
#############################################################################
1;
__END__;