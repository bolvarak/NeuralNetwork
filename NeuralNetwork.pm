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
	# Grab the neuron identifier
	my($iNeuron) = shift;
	# Grab the weight
	my($iWeight) = shift;
	# Grab the value
	my($iValue)  = shift;
	# Append the input to the inputs
	push(@{$oSelf->{"oNeurons"}{$iNeuron}}, {
		iValue  => $iValue,
		iWeight => $iWeight
	});
	# Return instance
	return $oSelf; 
}
sub addNeuron {
	# Grab the instance and neuron identifier
	my($oSelf, $iNeuron) = @_;
	# Add the neuron
	$oSelf->{"oNeurons"}{$iNeuron} = [];
	# Return instance
	return $oSelf;
}
sub dumpNeurons {
	# Grab the instance
	my($oSelf) = shift;
	# Start the map
	print("\n");
	# Loop through the neurons
	while (my($iNeuron, @aInputs) = each(%{$oSelf->{"oNeurons"}})) {
		# Print the neuron id
		print($iNeuron, " => ", "\n");
		# Loop through the inputs
		for my $oInput (@{$oSelf->{"oNeurons"}{$iNeuron}}) {
			# Print the input
			print("\t", "iValue => ", $oInput->{"iValue"}, "\n");
			# Print the weight
			print("\t", "iWeight => ", $oInput->{"iWeight"}, "\n\n");
		}
	}
	# Finish the map
	print "\n\n";
	# Return
	return undef;
}
###############################################################################
### Getters ##################################################################
#############################################################################
sub getActivation {
	# Grab the instance 
	my($oSelf)       = shift;
	# Grab the neuron identifier
	my($iNeuron)     = shift or undef;
	# Set the activation placeholder
	my($iActivation) = 0;
	# Check for a neuron
	if ($iNeuron) {
		# Check for the neuron
		if ($oSelf->{"oNeurons"}{$iNeuron}) {
			# Loop through the inputs
			for my $oInput (@{$oSelf->{"oNeurons"}{$iNeuron}}) {
				# Multiply to get the output
				$iActivation += (int $oInput->{"iWeight"} * int $oInput->{"iValue"});
			}
		} else {
			# The neuron doesn't exist
			return 0;
		}
	} else {
		# Loop through the neurons
		while (my($iNeuronId, @aInputs) = each(%{$oSelf->{"oNeurons"}})) {
			# Loop through the inputs
			for my $oInput (@{$oSelf->{"oNeurons"}{$iNeuronId}}) {
				# Multiply to get the output
				$iActivation += (int $oInput->{"iWeight"} * $oInput->{"iValue"});
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