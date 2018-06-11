# Seirina

Copyrigh 2018 Vincent Damewood
Seirina is licensed under the terms of the Apache License 2.0.

Seirina is a project to develop code to generate audio files of
synthesized music. Currently, it supports generating a single-channel
stream of a single wave form with a fixed ADSR envelop.

Seirina uses Cmake for its build system. Make a directly, called
`build`, `cd` into it, and run `cmake ..`, then `make`, to build
Seirina.

The `genwave` program is the main command-line interface. Use the -i
argument to indicate an input file, -o to select the output file,
and -w to select wave form, one of `sine`, `square`, `triangle`,
`saw`, and `absine` (absolute value of a sinewave). Output is in the
form of a `wav` file.

The input is a text file in a specific format. Each line is a separate
note. The first letter (A-G), represents the pitch class, and it
optionally followed by either a -, +, or space, to represent flat,
sharp, or natural respectively. Following the pitch class,  a
single-digit number, represents the octave in scientific pitch notation.
A440 and middle C are octave 4. A dash separates the octave from the
duration, which is represented either a a single-digit number, or
a fraction of single-digit numbers separated by a /. This duration
is in beats, which is currently hard-coded as 18900 audio samples
(resulting in 140 beats per minute).
