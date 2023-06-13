import("stdfaust.lib");
phaseFunc(nsamp) = 1 : ((_,_ : +), (nsamp) : %)~_;
summingSigFunc(in, nsamp) = in:+~*(phaseFunc(nsamp)!=0); //block sum 
process(in, nsamp) = summingSigFunc((in^(2)), nsamp) : select2((phaseFunc(nsamp)==(nsamp-1)))~_ : sqrt; //sample and hold and squared root



