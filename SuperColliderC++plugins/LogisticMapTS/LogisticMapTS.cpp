#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;




struct LogisticMapTS : public Unit
{
  float currentValue = 0.5; // init value
  float state = -1.0;
  float previousLambda = 0.0;
  float currentLambda = 0.0;
};

// declare unit generator functions
static void LogisticMapTS_next_a(LogisticMapTS *unit, int inNumSamples);
static void LogisticMapTS_Ctor(LogisticMapTS* unit);







//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void LogisticMapTS_Ctor(LogisticMapTS* unit)
{
    
  SETCALC(LogisticMapTS_next_a);

  unit->currentValue = 0.5; //init
  unit->previousLambda = 0.0;
  unit->currentLambda = 0.0;
  unit->state = -1.0;

  
  LogisticMapTS_next_a(unit, 1);

  unit->currentValue = 0.5; //init
  unit->previousLambda = 0.0;
  unit->currentLambda = 0.0;
  unit->state = -1.0;



}


//////////////////////////////////////////////////////////////////


void LogisticMapTS_next_a(LogisticMapTS *unit, int inNumSamples)
{
    float *out = OUT(0);
    float lambda = IN0(0);


    for (int i=0; i < inNumSamples; ++i)
    {
      unit->state = unit->state + 1.0;

      ///// clipping lambda
      unit->currentLambda = lambda;
      if (unit->currentLambda > 3.999) {
        unit->currentLambda = 3.999;
      }
      if (unit->currentLambda < 3.5) {
        unit->currentLambda = 3.5;
      }
      

      ///// for dynamic lambda
      if ((unit->currentLambda != unit->previousLambda) && (unit->state != 0.0)) {
        unit->currentValue = abs(unit->currentValue);
      }

      ///// core function
      unit->currentValue = (unit->currentValue * unit->currentLambda) * (1 - unit->currentValue);

      ///// clipping
      if (unit->currentValue > 0.999) {
        unit->currentValue = 0.999;
      }
      if (unit->currentValue < -0.999) {
        unit->currentValue = -0.999;
      }
      
      ///// out
      out[i] = unit->currentValue;
      unit->previousLambda = lambda;


  }
}



PluginLoad(LogisticMapTS)
{
    ft = inTable;

    DefineSimpleUnit(LogisticMapTS);
}