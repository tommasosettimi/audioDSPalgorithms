import("stdfaust.lib");
process(in) = in + ((_~ %(2) +(in)) == 2) * -1;