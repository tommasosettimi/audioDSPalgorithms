import("stdfaust.lib");
//needs the phasor 0,0,0,0,(sampleBlock-1),1,0,0,0,0,0 
process(phasor) = (phasor  == (1) : + ~(_%(2)) : _ == (2) : _ * (-2) : _ + phasor) : _;
