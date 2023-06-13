#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;


struct NonLinSaturatorTS : public Unit
{
  float currentSample = 0.0;
  float previousSample = 0.0;
  float state = -1.0;
  float multiplier = 1.0;
  float adder = 0.0;
  float nSamples = 1.0;

};

// declare unit generator functions
static void NonLinSaturatorTS_next_a(NonLinSaturatorTS *unit, int inNumSamples);
static void NonLinSaturatorTS_Ctor(NonLinSaturatorTS* unit);







//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void NonLinSaturatorTS_Ctor(NonLinSaturatorTS* unit)
{
    
  SETCALC(NonLinSaturatorTS_next_a);

  unit->state = -1.0;
  unit->currentSample = 0.0;
  unit->previousSample = 0.0;
  unit->multiplier = 0.0;
  unit->adder = 0.0;
  unit->nSamples = 0.0;

  NonLinSaturatorTS_next_a(unit, 1);

  unit->state = -1.0;
  unit->currentSample = 0.0;
  unit->previousSample = 0.0;
  unit->multiplier = 0.0;
  unit->adder = 0.0;
  unit->nSamples = 0.0;

}


//////////////////////////////////////////////////////////////////


void NonLinSaturatorTS_next_a(NonLinSaturatorTS *unit, int inNumSamples)
{
    float *out = OUT(0);
    float nsamp = IN0(0);
    float mul = IN0(1);
    float add = IN0(2);


    for (int i=0; i < inNumSamples; ++i)
    {
      unit->multiplier = mul;
      unit->adder = add;
      unit->nSamples = nsamp; 


      unit->state = unit->state + 1;
      unit->state = fmod(unit->state, unit->nSamples);
      if (unit->state == 0) {
        unit->currentSample = unit->currentSample + 1;
      }

      out[i] = (unit->currentSample + unit->adder) * unit->multiplier;

  }
}



PluginLoad(NonLinSaturatorTS)
{
    ft = inTable;

    DefineSimpleUnit(NonLinSaturatorTS);
}