#include "SC_PlugIn.h"
#include <cmath>
// https://github-wiki-see.page/m/mtmccrea/supercollider/wiki/Notes-on-writing-UGens
// cmake -DSC_PATH=/Users/macbook/Desktop/SuperCollider-3.12.2-Source/ ..
// cmake -DCMAKE_BUILD_TYPE=RELEASE ..

// InterfaceTable contains pointers to functions in the host (server).
static InterfaceTable *ft;

float arrayIndexes[48000]; //VARIABILE GLOBALE


struct ZCSinesTS : public Unit
{
  int currentIndexStruct = 0;
  int counter1Struct = 0;
  int counter2Struct = 0;
  int phasorStruct = 0;
  int stateStruct = 0;
  int delayStruct = 48000;
  int arrayIndexesStateStruct = -1;

};

// declare unit generator functions
static void ZCSinesTS_next_a(ZCSinesTS *unit, int inNumSamples);
static void ZCSinesTS_Ctor(ZCSinesTS* unit);







//////////////////////////////////////////////////////////////////

// Ctor is called to initialize the unit generator.
// It only executes once.

// A Ctor usually does 3 things.
// 1. set the calculation function.
// 2. initialize the unit generator state variables.
// 3. calculate one sample of output.

void ZCSinesTS_Ctor(ZCSinesTS* unit)
{
    
  SETCALC(ZCSinesTS_next_a);
    
  unit->currentIndexStruct = 0;
  unit->counter1Struct = 0;
  unit->counter2Struct = 0;
  unit->phasorStruct = 0;
  unit->stateStruct = 0;
  unit->delayStruct = 48000;
  unit->arrayIndexesStateStruct = -1;
  
  ZCSinesTS_next_a(unit, 1);


  unit->currentIndexStruct = 0;
  unit->counter1Struct = 0;
  unit->counter2Struct = 0;
  unit->phasorStruct = 0;
  unit->stateStruct = 0;
  unit->delayStruct = 48000;
  unit->arrayIndexesStateStruct = -1;

}


//////////////////////////////////////////////////////////////////





void ZCSinesTS_next_a(ZCSinesTS *unit, int inNumSamples)
{

    float *out = OUT(0);
    float *in = IN(0);
      

    for (int i=0; i < inNumSamples; ++i)
    {
        unit->stateStruct = unit->stateStruct+1;
    if (in[i]==1.0) {
        unit->counter1Struct = unit->counter1Struct + 1;
        if (unit->counter2Struct!=0) {unit->arrayIndexesStateStruct = unit->arrayIndexesStateStruct+1; arrayIndexes[unit->arrayIndexesStateStruct]=unit->counter2Struct;} 
        unit->counter2Struct = 0;
    }
    else {
        unit->counter2Struct = unit->counter2Struct + 1;
        if (unit->counter1Struct!=0) {unit->arrayIndexesStateStruct = unit->arrayIndexesStateStruct+1; arrayIndexes[unit->arrayIndexesStateStruct]=unit->counter1Struct;}
        unit->counter1Struct = 0;
    };

    if (((unit->stateStruct) > (unit->delayStruct)) && (arrayIndexes[unit->currentIndexStruct] != 0.0)) {
        out[i] = sin(unit->phasorStruct * (2 * M_PI) / arrayIndexes[unit->currentIndexStruct]); unit->phasorStruct = unit->phasorStruct + 1;
        }
    else {
        out[i] = 0.0;
        }

    if ((unit->phasorStruct == arrayIndexes[unit->currentIndexStruct]) && (unit->phasorStruct != 0)) {unit->phasorStruct = 0; unit->currentIndexStruct = unit->currentIndexStruct+1;}
  }
}



PluginLoad(ZCSinesTS)
{
    ft = inTable;

    DefineSimpleUnit(ZCSinesTS);
}