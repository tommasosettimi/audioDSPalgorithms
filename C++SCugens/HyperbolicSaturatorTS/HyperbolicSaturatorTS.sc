HyperbolicSaturatorTS : UGen {
    *ar {|in, threshold|
        ^this.multiNew('audio', in, threshold);
    }
}




