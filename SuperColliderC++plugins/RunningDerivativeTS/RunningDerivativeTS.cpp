#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;


struct RunningDerivativeTS : public Unit
{
  float previousSample = 0.0;
  float currentSample = 0.0;

};

// declare unit generator functions
static void RunningDerivativeTS_next_a(RunningDerivativeTS *unit, int inNumSamples);
static void RunningDerivativeTS_Ctor(RunningDerivativeTS* unit);







//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void RunningDerivativeTS_Ctor(RunningDerivativeTS* unit)
{
    
  SETCALC(RunningDerivativeTS_next_a);

  unit->previousSample = 0.0;
  unit->currentSample = 0.0;


  
  RunningDerivativeTS_next_a(unit, 1);

  unit->previousSample = 0.0;
  unit->currentSample = 0.0;

}


//////////////////////////////////////////////////////////////////


void RunningDerivativeTS_next_a(RunningDerivativeTS *unit, int inNumSamples)
{
    float *out = OUT(0);
    float *in = IN(0);


    for (int i=0; i < inNumSamples; ++i)
    {
      unit->currentSample = in[i];
      out[i] = unit->currentSample - unit->previousSample;
      unit->previousSample = unit->currentSample;
      
  }
}



PluginLoad(RunningDerivativeTS)
{
    ft = inTable;

    DefineSimpleUnit(RunningDerivativeTS);
}