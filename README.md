# audioDSPalgorithms

Digital Signal Processing (DSP) algorithms in form of libraries in different programming languages (C++, Faust, SuperCollider).

## Summary

This repository contains various Digital Signal Processing (**DSP**) algorithms that have been useful to me over the years in audio programming, perhaps they will also be useful to someone else. There are various folders, specifically:

- **C++pluginsSC**: a library of UGens (plugins) for SuperCollider, an environment and programming language for real-time audio synthesis and algorithmic composition. For each plug-in there is also the relative non-compiled .cpp original file, to look into the DSP. To use these plugins you should copy and paste this folder in your "Extensions" folder for the SuperCollider environment (typically ~/Library/Application Support/SuperCollider/Extensions/ for Mac users). They range from very simple (see DCdynamicTS) to complex systems (see LogisticButterflyTS).

- **FaustDSPfiles**: a library of DSP algorithms (.dsp files) in Faust, a domain-specific purely functional programming language for implementing signal processing algorithms in the form of libraries, audio plug-ins, or standalone applications. For most of the algorithms you can find also a relative compiled SuperCollider UGen (the folders) in the same folder. Again, to use these plugins in SuperCollider you should copy and paste this folder in your "Extensions" folder for the SuperCollider environment. Alternatively you can also target another programming languages from the Faust IDE through the .dsp files.

- **SuperColliderCodes**: a library of .scd files for SuperCollider (SC), an environment and programming language for real-time audio synthesis and algorithmic composition. Most of them are working in the language part of SC an don't use the audio server and will be implemented soon in C++ as SC Ugens (plugins). 

#

### C++pluginsSC

A library of UGens (plugins) for SuperCollider, an environment and programming language for real-time audio synthesis and algorithmic composition. The full documentation of this library will be uploaded soon. The library include the following audio DSP plugins: DCdynamicTS, DCestimatorTS, HoldedPhasorTS, HyperbolicSaturatorTS, LogisticButterflyTS, LogisticMapTS, LogisticSyncTS, NonLinSaturatorTS, RunnningDerivativeTS, RunningIntegratorTS, SineButterflyTS, SkipZeroCrossingsTS, ZCSinesTS, ZCrateTS, ZeroCrossingDetectorTS, ZeroCrossingToggleTS.



### FaustDSPfiles

A library of DSP algorithms (.dsp files) in Faust, a domain-specific purely functional programming language for implementing signal processing algorithms in the form of libraries, audio plug-ins, or standalone applications. The full documentation of this library will be uploaded soon. The library include the following audio DSP plugins: DifferentOfZeroTS, PhasorSignAlternatorTS, PhasorTS, RMSBlockSumTS, SampleCounterTS, SampleHoldTS, SummingBlockSumTS, ZeroCrossingToggleReverseTS, ZeroCrossingToggleStereoTS, ZeroCrossingToggleX3TS.




### SuperColliderCodes

A library of .scd files for SuperCollider (SC), an environment and programming language for real-time audio synthesis and algorithmic composition. The full documentation of this library will be uploaded soon. The library include the following audio DSP codes: average_function_language.scd, evolvingBitwiseDistortion.scd, median_absolute_deviation.scd, pitchTrack.scd. 







