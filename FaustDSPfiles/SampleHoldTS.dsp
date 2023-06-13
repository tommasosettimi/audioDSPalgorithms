import("stdfaust.lib");
//capture(b) = select2(n)~_;
//process(phasor, nsamples) = capture(phasor==(n-1));

//phaseFunc(nsamp) = 1 : ((_,_ : +), (nsamp) : %)~_;
//process(nsamp) = select2((phaseFunc(nsamp)==(nsamp-1)))~_;


process(selectorSig, in) = in : select2(selectorSig)~_ : abs;