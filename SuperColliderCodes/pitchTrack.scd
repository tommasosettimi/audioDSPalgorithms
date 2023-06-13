
// CLASSICAL PITCH TRACKING


(
SynthDef(\pitchTrack, { |
	out, freq = 300, amp = 0.1,
	gate = 1, // For envelopes
	peakThresholdTracking = 0.5 // For pitch tracking
	|
	var source, sig,
	envForRelease, envForAttack, // For Envelopes
	pitchTrack, sigToPitchTrack // For pitch tracking
	;

	// SOURCE
	source = Saw.ar(freq + SinOsc.ar(1).range(10.neg, 10));
	source = source + PinkNoise.ar(1);

	// TRACKING
	sigToPitchTrack = source;
	pitchTrack = Pitch.kr(Mix.ar(sigToPitchTrack), initFreq: freq, peakThreshold: peakThresholdTracking)[0];
	pitchTrack = Median.kr(10 /*length*/, pitchTrack); // Delete noise and outliers

	// SET THE PITCH TO AN OSCILLATOR
	sig = SinOsc.ar(pitchTrack);

	envForAttack = EnvGen.kr(Env.new([0.0, 1.0, 1.0], [0.01, 2**8]), gate, doneAction: Done.freeSelf);
	envForRelease = EnvGen.kr(Env.cutoff(1), gate, doneAction: Done.freeSelf);
	Out.ar(out, sig * amp * envForAttack * envForRelease);
}).add;
);

~sine = Synth(\pitchTrack, [\freq, 500, \peakThreshold: 0.7]);

~sine.set(\peakThreshold, 0.9);

~sine.release(0.01);


////////////////////////////////////////////////////////////////////////

// FIXED PITCH AFTER AVERAGE IN A BUFFER
(
// Calculate the median
~calculateMedian = { |list|
    var sortedList = list.sort;
    var medianIndex = sortedList.size.div(2);
    sortedList[medianIndex]
};

// Calculate the median absolute deviation (MAD)
~calculateMAD = { |list, median|
    var absDeviations = list.collect { |x| (x - median).abs };
    ~calculateMedian.(absDeviations)
};

// Calculate the average without outliers
~calculateAverageWithoutOutliers = { |arr, threshold = 3|
    var sortedArr = arr.sort;
    var median = ~calculateMedian.(sortedArr);
    var mad = ~calculateMAD.(sortedArr, median);
    var outliersThreshold = threshold * mad;

    var filteredArr = sortedArr.select { |x| (x - median).abs <= outliersThreshold };
    filteredArr.sum / filteredArr.size
};
)

(
~recordingTimePitch = 4; // Seconds, min 0.6 seconds
~pitchBuf = Buffer.alloc(s, ~recordingTimePitch * s.sampleRate, 1);
~pitchTrackArr = Array.newClear(~recordingTimePitch * s.sampleRate);
)

(
SynthDef(\pitchTrack, {|
	runPitchRec = 0.0, triggerPitchRec = -1.0, peakThresholdTracking = 0.5, freqTracking = 50 // For pitch tracking

	|
	var source,
	pitchTrack, sigToPitchTrack, pitchToBuffer, recBuf, // For pitch tracking
	sineTest
	;

	// SOURCE SIGNAL
	source = SinOsc.ar(300 + LFDNoise3.kr(1, mul: 20));


	// PITCH TRACKING
	sigToPitchTrack = source;
	pitchTrack = Pitch.kr(Mix.ar(sigToPitchTrack), initFreq: 50, peakThreshold: peakThresholdTracking)[0];
	pitchTrack = Median.kr(10 /*length*/, pitchTrack); // Delete noise and outliers
	//pitchTrack.poll;

	// RECORD ON BUFFER
	pitchToBuffer = pitchTrack;
	RecordBuf.ar(pitchTrack, ~pitchBuf, doneAction: 0, run: 1.0, loop: 0.0, trigger: triggerPitchRec);


	// TEST
	sineTest = SinOsc.ar(freqTracking) * 0.1;
	Out.ar([0,1], sineTest);

}).add;
);

~synth = Synth(\pitchTrack)

(
~pitchTask = Task.new({
	~synth.set(\triggerPitchRec, 1.0, \numberDC, 3.0); // Record the pitch
	~recordingTimePitch.wait;
	~pitchTrackArr = Array.newClear;
	~pitchBuf.loadToFloatArray(action: {|x| ~pitchTrackArr = x}); // Load to array
	~pitchTrackArr = ~pitchTrackArr.drop((0.5 * s.sampleRate).asInteger); // Discard first 0.5 seconds
	~selectedArray = Array.newClear();
	~pitchTrackArr.do({|item, index| if (index%(s.options.blockSize)==0) {~selectedArray = ~selectedArray ++ item}});
	~pitchTrackArr = ~selectedArray;
	~fundamental = ~calculateAverageWithoutOutliers.(~pitchTrackArr);
	~fundamental.postln;
	~synth.set(\triggerPitchRec, -1.0, \numberDC, 2.0); // Reset the trigger
}).start
)
~synth.set(\freq, ~fundamental)







