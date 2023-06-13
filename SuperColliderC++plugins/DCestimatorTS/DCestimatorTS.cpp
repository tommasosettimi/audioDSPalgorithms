#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;


struct DCestimatorTS : public Unit
{
  float currentSample = 0.0;
  float previousLambda = 0.0;
  float state = -1.0;
};

// declare unit generator functions
static void DCestimatorTS_next_a(DCestimatorTS *unit, int inNumSamples);
static void DCestimatorTS_Ctor(DCestimatorTS* unit);







//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void DCestimatorTS_Ctor(DCestimatorTS* unit)
{
    
  SETCALC(DCestimatorTS_next_a);

  unit->currentSample = 0.0;
  unit->previousLambda = 0.0;
  unit->state = -1.0;

  
  DCestimatorTS_next_a(unit, 1);

  unit->currentSample = 0.0;
  unit->previousLambda = 0.0;
  unit->state = -1.0;



}


//////////////////////////////////////////////////////////////////


void DCestimatorTS_next_a(DCestimatorTS *unit, int inNumSamples)
{
    float *out = OUT(0);
    float *in = IN(0);


    for (int i=0; i < inNumSamples; ++i)
    {
      unit->state = unit->state + 1; 

      if (unit->state == 0) {
        unit->currentSample = in[i]; out[i] = unit->currentSample; unit->previousSample = unit->currentSample;
      } else if (unit->state == 1) {
        unit->currentSample = (in[i] + unit->previousSample) * 0.5; out[i] = unit->currentSample; unit->previousSample = unit->currentSample;
      } else {
        unit->currentSample = ((unit->state - 1.0) / unit->state) * unit->previousSample + (in[i] / unit->state); out[i] = unit->currentSample; unit->previousSample = unit->currentSample;
      }

  }
}



PluginLoad(DCestimatorTS)
{
    ft = inTable;

    DefineSimpleUnit(DCestimatorTS);
}