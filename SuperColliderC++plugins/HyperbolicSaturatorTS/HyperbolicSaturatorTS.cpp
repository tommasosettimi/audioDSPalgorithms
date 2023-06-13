#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;


struct HyperbolicSaturatorTS : public Unit
{
  float currentSample = 0.0;
  float previousSample = 0.0;
  float currentThresold = 0.5;
  float x1 = 0.0;
  float x2 = 0.0;

};

// declare unit generator functions
static void HyperbolicSaturatorTS_next_a(HyperbolicSaturatorTS *unit, int inNumSamples);
static void HyperbolicSaturatorTS_Ctor(HyperbolicSaturatorTS* unit);







//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void HyperbolicSaturatorTS_Ctor(HyperbolicSaturatorTS* unit)
{
    
  SETCALC(HyperbolicSaturatorTS_next_a);

  unit->currentSample = 0.0;
  unit->previousSample = 0.0;
  unit->currentThresold = 0.5;
  unit->x1 = 0.0;
  unit->x2 = 0.0;

  HyperbolicSaturatorTS_next_a(unit, 1);

  unit->currentSample = 0.0;
  unit->previousSample = 0.0;
  unit->currentThresold = 0.5;  
  unit->x1 = 0.0;
  unit->x2 = 0.0;

}


//////////////////////////////////////////////////////////////////


void HyperbolicSaturatorTS_next_a(HyperbolicSaturatorTS *unit, int inNumSamples)
{
    float *out = OUT(0);
    float *in = IN(0);
    float *threshold = IN(1);


    for (int i=0; i < inNumSamples; ++i)
    {
      unit->currentThresold = threshold[i];
      unit->currentSample = in[i];

      //// avoid denominator == 0

      /*
      if (unit->currentThresold == 0.0) {
        unit->currentThresold = 0.0000000000001;
      }
      if (unit->currentThresold < 0.0000000000001 && unit->currentThresold > 0.0) {
        unit->currentThresold = 0.0000000000001;
      }
      if (unit->currentThresold > -0.0000000000001 && unit->currentThresold < 0.0) {
        unit->currentThresold = -0.0000000000001;
      }
      */

      unit->x1 = unit->currentSample / unit->currentThresold;
      unit->x1 = abs(unit->x1);
      unit->x1 = 1.0 + unit->x1;
      unit->x1 = (unit->currentSample / unit->currentThresold) / unit->x1;
      unit->currentSample = unit->x1 * unit->currentThresold;
      out[i] = unit->currentSample;
  }
}



PluginLoad(HyperbolicSaturatorTS)
{
    ft = inTable;

    DefineSimpleUnit(HyperbolicSaturatorTS);
}