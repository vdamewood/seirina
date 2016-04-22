#!/bin/sh

./wave $@ | aplay -c2 -fS16_LE -r44100
