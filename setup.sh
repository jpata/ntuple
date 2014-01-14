#!/bin/bash
CMSSW_VERSION=CMSSW_6_0_1
CMSSW_VERSION_BACKUP=CMSSW_6_0_1_FWLITE
scram project -n CMSSW CMSSW $CMSSW_VERSION || scram project -n CMSSW CMSSW $CMSSW_VERSION_BACKUP   
git checkout CMSSW
git submodule init
git submodule update
