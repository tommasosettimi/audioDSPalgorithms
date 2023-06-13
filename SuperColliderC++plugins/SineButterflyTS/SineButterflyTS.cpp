#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;


struct SineButterflyTS : public Unit
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
};

// declare unit generator functions
static void SineButterflyTS_next_a(SineButterflyTS *unit, int inNumSamples);
static void SineButterflyTS_Ctor(SineButterflyTS* unit);





//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void SineButterflyTS_Ctor(SineButterflyTS* unit)
{
    
  SETCALC(SineButterflyTS_next_a);

  unit->currentValue = 0.5; 
  unit->currentValue2 = 0.5; 
  unit->previousLambda = 0.0;
  unit->currentLambda = 0.0;
  unit->state = -1.0;
  unit->currentSeed = 0.5;
  unit->previousSeed = 0.5;
  unit->currentError = 0.000001;
  unit->previousError = 0.000001;
  
  SineButterflyTS_next_a(unit, 1);

  unit->currentValue = 0.5; 
  unit->currentValue2 = 0.5; 
  unit->previousLambda = 0.0;
  unit->currentLambda = 0.0;
  unit->state = -1.0;
  unit->currentSeed = 0.5;
  unit->previousSeed = 0.5;
  unit->currentError = 0.000001;
  unit->previousError = 0.000001;

}


//////////////////////////////////////////////////////////////////


void SineButterflyTS_next_a(SineButterflyTS *unit, int inNumSamples)
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

      ///// clipping lambda
      unit->currentLambda = lambda[i];
      if (unit->currentLambda > 0.999999) {
        unit->currentLambda = 0.999999;
      }
      if (unit->currentLambda < 0.000001) {
        unit->currentLambda = 0.000001;
      }

      ///// clipping seed
      unit->currentSeed = seed[i];
      if (unit->currentSeed > 0.999999) {
        unit->currentSeed = 0.999999;
      }
      if (unit->currentSeed < 0.000001) {
        unit->currentSeed = 0.000001;
      }
      
      ///// for substituting seed to current value
      if ((unit->currentSeed != unit->previousSeed) && (unit->state != 0.0)) {
        unit->currentValue = unit->currentSeed;
      }


      ///// core function
      //unit->currentValue = (unit->currentValue * unit->currentLambda) * (1 - unit->currentValue);
      unit->currentValue = unit->currentLambda * (sinf(unit->currentValue * M_PI ));

      ///// clipping output
      if (unit->currentValue > 0.999) {
        unit->currentValue = 0.999;
      }
      if (unit->currentValue < -0.999) {
        unit->currentValue = -0.999;
      }
      
      ///// outputs and assigning variables
      out1[i] = unit->currentValue;
      unit->previousLambda = lambda[i];

      //////////////////////////////////////////////////////////////// 
      /////////////////////////////////////////////// prediction error


      if (unit->state == 0) {
        unit->currentValue2 = unit->currentValue2 + unit->currentError;
      }
      ///// for error change
      if ((unit->currentError != unit->previousError) && (unit->state != 0.0)) {
        unit->currentValue2 = unit->currentValue2 + unit->currentError;
      }

      ///// for substituting seed to current value
      if ((unit->currentSeed != unit->previousSeed) && (unit->state != 0.0)) {
        unit->currentValue2 = unit->currentSeed + unit->currentError;
      }

      ///// core function
      //unit->currentValue2 = (unit->currentValue2 * unit->currentLambda) * (1 - unit->currentValue2);
      unit->currentValue2 = unit->currentLambda * (sinf(unit->currentValue2 * M_PI));

      ///// clipping output
      if (unit->currentValue2 > 0.999) {
        unit->currentValue2 = 0.999;
      }
      if (unit->currentValue2 < -0.999) {
        unit->currentValue2 = -0.999;
      }
      
      ///// output prediction error and assigning variables
      out2[i] = unit->currentValue2 - unit->currentValue;
      unit->previousSeed = unit->currentSeed;
      unit->previousError = unit->currentError;
      
  }
}



PluginLoad(SineButterflyTS)
{

    ft = inTable;

    DefineSimpleUnit(SineButterflyTS);
}