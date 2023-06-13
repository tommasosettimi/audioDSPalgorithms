import("stdfaust.lib");
process(sig) = ((sig <: _ * _') < 0) + (sig==0);