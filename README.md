# audioDSPmiscellaneous

Miscellaneous Digital Signal Processing (DSP) algorithms in different programming languages (Faust, SuperCollider, C++, ...).

## Summary

This repository contains various Digital Signal Processing (DSP) algorithms that have been useful to me over the years in audio programming, perhaps they will also be useful to someone else. There are various folders, specifically:

- SuperColliderC++plugins: a library of UGens (plugins) for SuperCollider, an environment and programming language for real-time audio synthesis and algorithmic composition. For each plug-in there is also the relative non-compiled .cpp original file, to look into the DSP. To use these plugins you should copy and paste this folder in your "Extensions" folder for the SuperCollider environment (typically ~/Library/Application Support/SuperCollider/Extensions/ for Mac users). They range from very simple (see DCdynamicTS) to complex systems (see LogisticButterflyTS).

- FaustDSPfiles: different DSP algorithms (.dsp files) in Faust, a domain-specific purely functional programming language for implementing signal processing algorithms in the form of libraries, audio plug-ins, or standalone applications. For most of the algorithms you can find also a relative compiled SuperCollider UGen (the folders) in the same folder. Again, to use these plugins in SuperCollider you should copy and paste this folder in your "Extensions" folder for the SuperCollider environment. Alternatively you can also target another programming languages from the Faust IDE through the .dsp files.


