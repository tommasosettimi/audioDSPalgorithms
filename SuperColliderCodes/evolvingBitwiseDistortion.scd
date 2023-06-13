// Bitwise distortion saturator

(
// Add the SynthDef first

SynthDef(\bitwiseDistortion, {
    |in = 0, out = 0, mask = 0xFF|
	var input, distorted;
	input = Saw.ar(300) * 0.1; // Here you can change the source
	//input = In.ar(in, 1); // Alternative source example
    distorted = (input * mask).round / mask; // Actual distortion
	distorted = HPF.ar(distorted, 10); // DC blocker
    Out.ar(out, distorted); // Output playback
}).add;
)

x = Synth(\bitwiseDistortion) // Start the synth
x.free // Stop the synth


///////////////////////////////////////////////////

// Bitwise distortion saturator with evolving distortion

(
// Add the SynthDef first
SynthDef(\evolvingBitwiseDistortion, {
    |in, out = 0, duration = 4, maskRangeMin = 0.1, maskRangeMax = 0.7,
	changingRate = 0.2, // set the changing rate of the distortion behaviour
	regularity = 0 // set regularity between 0.0 (regular distortion behaviour) and 1.0 (irregular distortion behaviour)
	|
	var input, mask1, mask2, mask, distorted;
	input = SinOsc.ar(300) * 0.1; // Here you can change the source
	// var input = In.ar(in, 1); // Alternative source example
    mask1 = LFDNoise3.kr(changingRate).abs.range(maskRangeMin, maskRangeMax) * 0xFF;
	mask2 = SinOsc.kr(changingRate).abs.range(maskRangeMin, maskRangeMax) * 0xFF;
	mask = (mask2 * regularity) + (mask1 * (1-regularity));
    distorted = (input * mask).round / mask; // Actual distortion
	distorted = HPF.ar(distorted, 10); // DC blocker
    Out.ar(out, distorted); // Output playback
}).add;
)

y = Synth(\evolvingBitwiseDistortion, [\in, 0, \out, 0, \duration, 2, \changingRate, 0.1, regularity: 1.0]); // Start the synth
y.free // Stop the synth





