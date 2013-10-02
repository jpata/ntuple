#!/bin/bash
CMSSW_VERSION=CMSSW_5_3_11
CMSSW_VERSION_BACKUP=CMSSW_5_3_11_FWLITE
scram project -n CMSSW CMSSW $CMSSW_VERSION || scram project -n CMSSW CMSSW $CMSSW_VERSION_BACKUP   
git checkout CMSSW
git submodule init
git submodule update
