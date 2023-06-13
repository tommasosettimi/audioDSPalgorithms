import("stdfaust.lib");
phaseFunc(nsamp) = 1 : ((_,_ : +), (nsamp) : %)~_;
process(in) = phaseFunc(in);



