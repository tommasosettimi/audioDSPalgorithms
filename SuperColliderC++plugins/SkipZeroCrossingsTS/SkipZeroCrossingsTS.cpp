#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;




struct SkipZeroCrossingsTS : public Unit
{
    float previousSample = 0.0;
    float ones = 0.0; 
    
};

// declare unit generator functions
static void SkipZeroCrossingsTS_next_a(SkipZeroCrossingsTS *unit, int inNumSamples);
static void SkipZeroCrossingsTS_Ctor(SkipZeroCrossingsTS* unit);







//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void SkipZeroCrossingsTS_Ctor(SkipZeroCrossingsTS* unit)
{
    
  SETCALC(SkipZeroCrossingsTS_next_a);

  unit->previousSample = 0.0;
  unit->ones = 0.0;
  
  
  SkipZeroCrossingsTS_next_a(unit, 1);
  unit->previousSample = 0.0;
  unit->ones = 0.0;  
  


}


//////////////////////////////////////////////////////////////////


void SkipZeroCrossingsTS_next_a(SkipZeroCrossingsTS *unit, int inNumSamples)
{
    float *out = OUT(0);
    float *in = IN(0);

    for (int i=0; i < inNumSamples; ++i)
    {
    unit->ones = in[i] + unit->ones;
    if (unit->ones == 2.0) {
      out[i] = 0.0; unit->ones = 0.0;} 
    else {out[i] = in[i];}
  }
}



PluginLoad(SkipZeroCrossingsTS)
{
    ft = inTable;

    DefineSimpleUnit(SkipZeroCrossingsTS);
}