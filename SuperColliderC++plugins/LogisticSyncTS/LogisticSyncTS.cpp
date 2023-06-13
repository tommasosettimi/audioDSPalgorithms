#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;




struct LogisticSyncTS : public Unit
{
    float previousSample = 0.0;
    float currentSample = 0.0;
    float state = -1.0;
    float maximumDelay = 0.1;
    float derivative = 0.0;
    float syncState;
    float sr;
    float sum = 0.0;
    float res = 0.0;

};

// declare unit generator functions
static void LogisticSyncTS_next_a(LogisticSyncTS *unit, int inNumSamples);
static void LogisticSyncTS_Ctor(LogisticSyncTS* unit);




//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void LogisticSyncTS_Ctor(LogisticSyncTS* unit)
{
    
  SETCALC(LogisticSyncTS_next_a);

  unit->previousSample = 0.0;  
  unit->currentSample = 0.0;  
  unit->state = -1.0;
  unit->sr = (float)SAMPLERATE;
  unit->derivative = 0.0;
  unit->syncState = 0.0;
  unit->sum = 0.0;
  unit->res = 0.0;



  LogisticSyncTS_next_a(unit, 1);


}


//////////////////////////////////////////////////////////////////


void LogisticSyncTS_next_a(LogisticSyncTS *unit, int inNumSamples)
{

    float *out = OUT(0);
    float *in = IN(0);
    float delay = IN0(1);
    float threshold = IN0(2);
      

    for (int i=0; i < inNumSamples; ++i)
    {
        unit->state = fmod(unit->state + 1, delay * unit->sr);
        unit->currentSample = in[i];
        
        if (unit->state != 0.0) {
            unit->derivative = unit->currentSample - unit->previousSample;
            unit->derivative = abs(unit->derivative);
        }
        else {
            unit->derivative = 0.0;
        }

        if (unit->derivative > threshold && unit->syncState == 0.0) { 
            unit->syncState = unit->state;
        }
            
        if (unit->syncState == 0) {
            unit->res = unit->state;
            unit->res = unit->res / unit->sr;
        }
        else {
            unit->res = (delay * unit->sr) - unit->syncState;
            unit->res = unit->res / unit->sr;
        }
        out[i] = unit->res;
        unit->previousSample = unit->currentSample;

        
  }
}



PluginLoad(LogisticSyncTS)
{
    ft = inTable;

    DefineSimpleUnit(LogisticSyncTS);
}