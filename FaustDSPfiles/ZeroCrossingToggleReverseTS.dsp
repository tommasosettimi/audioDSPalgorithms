import("stdfaust.lib");
process(in) = (_ %(2) ~ + (in)) == 0;