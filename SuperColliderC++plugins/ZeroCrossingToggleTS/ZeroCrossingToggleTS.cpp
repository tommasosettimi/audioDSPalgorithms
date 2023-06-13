#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;




struct ZeroCrossingToggleTS : public Unit
{
    float previousSample = 0.0;
    float res = 0.0; 
    
};

// declare unit generator functions
static void ZeroCrossingToggleTS_next_a(ZeroCrossingToggleTS *unit, int inNumSamples);
static void ZeroCrossingToggleTS_Ctor(ZeroCrossingToggleTS* unit);







//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void ZeroCrossingToggleTS_Ctor(ZeroCrossingToggleTS* unit)
{
    
  SETCALC(ZeroCrossingToggleTS_next_a);

  unit->previousSample = 0.0;
  unit->res = 0.0;
  
  
  ZeroCrossingToggleTS_next_a(unit, 1);
  unit->previousSample = 0.0;
  unit->res = 0.0;  
  


}


//////////////////////////////////////////////////////////////////


void ZeroCrossingToggleTS_next_a(ZeroCrossingToggleTS *unit, int inNumSamples)
{
    float *out = OUT(0);
    float *in = IN(0);

    for (int i=0; i < inNumSamples; ++i)
    {
    unit->res = in[i] + unit->res;
    unit->res = fmodf(unit->res, 2.0);
    out[i] = unit->res;
    unit->previousSample = in[i];

  }
}



PluginLoad(ZeroCrossingToggleTS)
{
    ft = inTable;

    DefineSimpleUnit(ZeroCrossingToggleTS);
}