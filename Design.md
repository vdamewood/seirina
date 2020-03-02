# Seirina Design Goals

This is a rought draft for a design document for Seirina.
It may change in the future to clearify existing goals,
and possibly to add additional goals.

Seirina is a library for processing musical concepts into synthesized audio.
This document is meant to establish the goals for the 1.0 release of Seirina.
Before a beta version is released, all required features and interfaces
must be described and implemented.

Seirina will be implemented as a software library, written in C++.
Seirina will allow a program to take input and render audio output
based on the input.

## Supported Concepts

The main concept in Seirina is a project.
A project represents a song or composition.
A project must have a fixed, finite-length form,
and may optionally have an infinite form by looping like video game music.

A project will contain one or more tracks.
There can be potentially muliple types of tracks,
but for now, only a track of synthesized music will be described.
When rendering a project, its tracks will be mixed together.
Tracks that are part of a project will have a spacial orientation.
This spacial orient will be left/right on a continuum at the least.
If feasible, a project should allow a track of move around this space.

Seirina will, include a track type that renders synthesized music.
If possible the track should support multiple notes being played at once,
thus allowing for a single track to represent a single conceptual insrument.
If feasible, additional track types for emulating certain audio chips
should be included as well.

The synthesized music will use ADSR envelopes and pluggable waveforms.
For now, Seirina is targeted to support sine waves, pulse waves,
triangle waves, sawtooth, and absolute-value-of-sine waves.

The user should be able to implement other kinds of tracks and
waveforms.

## Seirina Input Processor

The input processor will take a project file as input, and yeild an
in-memory project object.
A project file will contain information on tracks, their timbres, and
their notes.
The formate will be a Zip (PKZIP) or 7Zip file containing track data in
subfiles.

## Seirina Example Program

The Seirina Example program will take, as input, a project file,
and either play the project described in it,
or render the input to a WAV file.
If possible, this mechanism should allow for plugiable output modules,
and render to FLAC as well.
