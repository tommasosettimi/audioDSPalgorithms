NonLinSaturatorTS : UGen {
    *ar {|nsamp, mul, add|
        ^this.multiNew('audio', nsamp, mul, add);
    }
}




