#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;


struct DCdynamicTS : public Unit
{
  float currentSample = 0.0;

};

// declare unit generator functions
static void DCdynamicTS_next_a(DCdynamicTS *unit, int inNumSamples);
static void DCdynamicTS_Ctor(DCdynamicTS* unit);







//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void DCdynamicTS_Ctor(DCdynamicTS* unit)
{
    
  SETCALC(DCdynamicTS_next_a);

  unit->currentSample = 0.0;


  
  DCdynamicTS_next_a(unit, 1);

  unit->currentSample = 0.0;

}


//////////////////////////////////////////////////////////////////


void DCdynamicTS_next_a(DCdynamicTS *unit, int inNumSamples)
{
    float *out = OUT(0);
    float in = IN0(0);


    for (int i=0; i < inNumSamples; ++i)
    {
      unit->currentSample = in;
      out[i] = unit->currentSample;
      
  }
}



PluginLoad(DCdynamicTS)
{
    ft = inTable;

    DefineSimpleUnit(DCdynamicTS);
}