SineButterflyTS : MultiOutUGen {
    *ar {|lambda, seed, error|
        ^this.multiNew('audio', lambda, seed, error);
    }
	init { arg ... theInputs;
		inputs = theInputs;
		channels = [
			OutputProxy(rate, this, 0),
			OutputProxy(rate, this, 1)
		];
		^channels
	}
	checkInputs { ^this.checkNInputs(1) }
}



/*

Pan2 : MultiOutUGen {
	*ar { arg in, pos = 0.0, level = 1.0;
		^this.multiNew('audio', in, pos, level )
	}
	*kr { arg in, pos = 0.0, level = 1.0;
		^this.multiNew('control', in, pos, level )
	}
	init { arg ... theInputs;
		inputs = theInputs;
		channels = [
			OutputProxy(rate, this, 0),
			OutputProxy(rate, this, 1)
		];
		^channels
	}
	checkInputs { ^this.checkNInputs(1) }
}*/