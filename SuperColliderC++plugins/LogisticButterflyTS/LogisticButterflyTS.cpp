#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;


struct LogisticButterflyTS : public Unit
{
  float currentValue = 0.5; // init value
  float currentValue2 = 0.5; 
  float state = -1.0;
  float previousLambda = 0.0;
  float currentLambda = 0.0;
  float currentSeed = 0.5;
  float previousSeed = 0.5;
  float currentError = 0.000001;
  float previousError = 0.000001;
  float errorplusseed = 0.0;
  float errorplusvalue = 0.0;
};

// declare unit generator functions
static void LogisticButterflyTS_next_a(LogisticButterflyTS *unit, int inNumSamples);
static void LogisticButterflyTS_Ctor(LogisticButterflyTS* unit);





//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void LogisticButterflyTS_Ctor(LogisticButterflyTS* unit)
{
    
  SETCALC(LogisticButterflyTS_next_a);

  unit->currentValue = 0.5; 
  unit->currentValue2 = 0.5; 
  unit->previousLambda = 0.0;
  unit->currentLambda = 0.0;
  unit->state = -1.0;
  unit->currentSeed = 0.5;
  unit->previousSeed = 0.5;
  unit->currentError = 0.0;
  unit->previousError = 0.0;
  unit->errorplusseed = 0.0;
  unit->errorplusvalue = 0.0;

  
  LogisticButterflyTS_next_a(unit, 1);


}


//////////////////////////////////////////////////////////////////


void LogisticButterflyTS_next_a(LogisticButterflyTS *unit, int inNumSamples)
{
    float *out1 = OUT(0);
    float *out2 = OUT(1);
    float *lambda = IN(0);
    float *seed = IN(1);
    float *error = IN(2);

  for (int i=0; i < inNumSamples; ++i)
    {

      unit->state = unit->state + 1.0;
      unit->currentError = error[i];
      unit->currentLambda = lambda[i];
      unit->currentSeed = seed[i];

      ///// clipping lambda
      if (unit->currentLambda > 4.0) {
        unit->currentLambda = 4.0;
      }
      if (unit->currentLambda < 3.5) {
        unit->currentLambda = 3.5;
      }

      ///// clipping seed
      if (unit->currentSeed > 0.999999) {
        unit->currentSeed = 0.999999;
      }
      if (unit->currentSeed < 0.000001) {
        unit->currentSeed = 0.000001;
      }
      
      ////// clip error + seed
      unit->errorplusseed = unit->currentSeed + unit->currentError;
      if (unit->errorplusseed > 0.999999) {
        unit->errorplusseed = 0.999999;
      }
      if (unit->errorplusseed < -0.999999) {
        unit->errorplusseed = -0.999999;
      }
      
      ////// starting value
      if (unit->state==1) {
        unit->currentValue = unit->currentSeed;
        unit->currentValue2 = unit->errorplusseed;
        unit->previousSeed = unit->currentSeed;
      }

      ////// changing seed, restart the calculation
      if ((unit->currentSeed != unit->previousSeed) && (unit->state != 1.0)) {
        unit->currentValue = unit->currentSeed;
        unit->currentValue2 = unit->errorplusseed;
      }

      ////// changing error, use the current seed value and restart the calculation
      if ((unit->currentError != unit->previousError) && (unit->state != 1.0)) {
        unit->currentValue = unit->currentSeed;
        unit->currentValue2 = unit->errorplusseed;
      }

      ///// core function 1
      unit->currentValue = (unit->currentValue * unit->currentLambda) * (1 - unit->currentValue);
      unit->currentValue2 = (unit->currentValue2 * unit->currentLambda) * (1 - unit->currentValue2);

      ///// outputs and assigning variables
      out1[i] = unit->currentValue;
      out2[i] = unit->currentValue2;
      unit->previousLambda = unit->currentLambda;
      unit->previousSeed = unit->currentSeed;
      unit->previousError = unit->currentError;
  }
}



PluginLoad(LogisticButterflyTS)
{

    ft = inTable;

    DefineSimpleUnit(LogisticButterflyTS);
}