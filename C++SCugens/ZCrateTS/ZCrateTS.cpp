#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;


struct ZCrateTS : public Unit
{

  float state = -1.0;
  float windowSize;
  float sum = 0.0;
  float res = 0.0;

  float previousSample = 0.0;
  float currentSample = 0.0;
  float signChange = 1.0;
  float equalofZero = 1.0;
  int zerocount = 0;
  float outDetector = 0.0;
};

// declare unit generator functions
static void ZCrateTS_next_a(ZCrateTS *unit, int inNumSamples);
static void ZCrateTS_Ctor(ZCrateTS* unit);







//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void ZCrateTS_Ctor(ZCrateTS* unit)
{
    
  SETCALC(ZCrateTS_next_a);


  unit->state = -1.0;
  unit->sum = 0.0;
  unit->res = 0.0;
  unit->windowSize = (float)SAMPLERATE / 100; //10 ms

  unit->previousSample = 0.0;  
  unit->currentSample = 0.0;  
  unit->signChange = 1.0;
  unit->equalofZero = 1.0; 
  unit->zerocount = 0;
  unit->outDetector = 0.0;

  
  ZCrateTS_next_a(unit, 1);

  unit->state = -1.0;
  unit->sum = 0.0;
  unit->res = 0.0;
  unit->windowSize = (float)SAMPLERATE / 100; //10 ms

  unit->previousSample = 0.0;  
  unit->currentSample = 0.0;  
  unit->signChange = 1.0;
  unit->equalofZero = 1.0;
  unit->zerocount = 0;
  unit->outDetector = 0.0;


}


//////////////////////////////////////////////////////////////////


void ZCrateTS_next_a(ZCrateTS *unit, int inNumSamples)
{
    float *out = OUT(0);
    float *in = IN(0);


    for (int i=0; i < inNumSamples; ++i)
    {
      /////////// Detector
      unit->currentSample = in[i];
        if ((unit->currentSample * unit->previousSample) < 0.0) {
            unit->signChange = 1.0;
        }
        else {
            unit->signChange = 0.0;
        }
         if (unit->currentSample == 0.0) {
            unit->zerocount = unit->zerocount + 1;
            if (unit->zerocount > 1) {
                unit->equalofZero = 0.0;
            }
            else {
                unit->equalofZero = 1.0;
            }
        }
        else {
            unit->equalofZero = 0.0;
            unit->zerocount = 0;
        } 

        unit->outDetector = unit->equalofZero + unit->signChange;
        unit->previousSample = unit->currentSample;


      /////////// Rate
      unit->state = unit->state + 1.0;
      unit->sum = unit->sum + unit->outDetector;
      if (unit->state == unit->windowSize) {
        unit->res = unit->sum / unit->windowSize;
        unit->sum = 0.0;
        unit->state = 0.0;
      }
      out[i] = unit->res;
  }
}



PluginLoad(ZCrateTS)
{
    ft = inTable;

    DefineSimpleUnit(ZCrateTS);
}