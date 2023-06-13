(
var path;
~nsec = 2;
~sourceRecBuffer = Buffer.alloc(s, s.sampleRate * ~nsec, numChannels: 1);
~toggleAbuffer = Buffer.alloc(s, s.sampleRate * ~nsec, numChannels: 1);
~toggleBbuffer = Buffer.alloc(s, s.sampleRate * ~nsec, numChannels: 1);
~zcBuffer = Buffer.alloc(s, s.sampleRate * ~nsec, numChannels: 1);
~outBuffer = Buffer.alloc(s, s.sampleRate * ~nsec, numChannels: 1);
//path = "/Users/macbook/Desktop/1969_cut.aiff";
//path = "/Users/macbook/Desktop/Thesis/Soundfiles/Gen_II_concert_beginning.wav";
//path = "/Users/macbook/Desktop/Thesis/Soundfiles/Gen_II_concert.wav";
path = Platform.resourceDir +/+ "sounds/a11wlk01.wav";
~sourceBuf = Buffer.readChannel(s, path, channels: [0]);
)
s.sampleRate/3000

play{SinOsc.ar(3001)}

(
~freq = 3002;
(
~sinGen = {|nsamp|
	Array.fill(
		nsamp, {|x|
		sin(x * 2pi / (nsamp));
	})
}
);
~array =  ~sinGen.((s.sampleRate/~freq).asInteger);
~resArr = Array.newClear;
(~freq.asInteger).do {~resArr = ~resArr ++ ~array};
"fatto".postln
)

~sineSig = Buffer.sendCollection(s, ~resArr.as(Signal), 1, action: {"fatto".postln })

(
~numFrames = 100000;
~buf = Buffer.alloc(s, ~numFrames, 1);
)

(
SynthDef(\test, { |delay = 0.2, buf|

	var source, in, zc, zcTrig, times, sweepTime, ramp, inSig, counter, zcTrigD, counterD, bufWr, rate, wavesets;

	//source = SinOsc.ar(1500);
	source = PlayBuf.ar(1, ~sineSig, loop: 1);


	in = source;

	//zc = HPZ1.ar(in.sign).abs >= 1;
	//zcTrig = ToggleFF.ar(zc);


	zc = ZeroCrossingDetectorTS.ar(source);
	zcTrig = ZeroCrossingToggleTS.ar(zc);


	counter = PulseCount.ar(zcTrig) % BufFrames.ir(~buf);
	#zcTrigD, counterD = DelayN.ar([zcTrig, counter], delay, delay);
	times = Timer.ar(zcTrig);
	bufWr = BufWr.ar(times, ~buf, counter - 1);

	sweepTime = Latch.ar(BufRd.ar(1, ~buf, counterD), zcTrigD);
	rate = Select.ar(counterD > DC.ar(0), [DC.ar(0), 2pi / sweepTime]);
	ramp = Sweep.ar(zcTrigD, rate);

	//RecordBuf.ar(source, ~sourceRecBuffer, loop: 0);
	//RecordBuf.ar(zc, ~zcBuffer, loop: 0);

	Out.ar(1, sin(ramp));
}).play
)

~sourceRecBuffer.loadToFloatArray(action: {|x| ~srcsamplesArray = x});
~srcsamplesArray.copyRange(0, 16);

~zcBuffer.loadToFloatArray(action: {|c| ~zcArray = c});
~zcArray.copyRange(0, 16)

