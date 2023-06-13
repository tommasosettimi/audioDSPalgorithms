import("stdfaust.lib");

//process(in, phasorSig) = in : +~*(phasorSig!=(0)) : _ ;
process(in) = in, (0) : != : _;



