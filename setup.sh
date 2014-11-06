#!/bin/bash
export SCRAM_ARCH=slc6_amd64_gcc481
CMSSW_VERSION=CMSSW_7_2_0
scram project -n CMSSW CMSSW $CMSSW_VERSION
git checkout CMSSW
git submodule init
git submodule update
