LogisticSyncTS : UGen {
    *ar {|in, delay, threshold|
        ^this.multiNew('audio', in, delay, threshold);
    }
}




