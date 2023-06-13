import("stdfaust.lib");

//process(input, phasor) = (phasor == (1) : + ~(_%(2)) : _ == (2) : _ * (-2) : _ + phasor) * (input : (+ ~(_)), phasor : * : _);
//process(in, delay) = in : + ~(_@(delay)) : abs;

//process(input, phasor, delay) = (input : (+ ~(_)), phasor : * : _) : _ <: _ , @(delay : abs) : - : abs;

//process(in, delay) = in <: _ , @(delay:abs) : -;


process(input, phasor) = (phasor == (1) : + ~(_%(2)) : _ == (2) : _ * (-2) : _ + phasor) * (input : (+ ~(_)), phasor : * : _) : _;





			