TESTFILE=http://phys.hep.kbfi.ee/~joosep/test_100ev.root

.PHONY: setup testfile

all: clean lib

clean:
	cd CMSSW/src; eval `scramv1 runtime -sh`; scram b clean; scram b vclean;

setup:
	./setup.sh

lib:
	cd CMSSW/src; eval `scramv1 runtime -sh`; scram b -j4 SingleTopPolarization/FWTools

plainlib:
	c++ `root-config --cflags --libs` -ICMSSW/src/ CMSSW/src/SingleTopPolarization/FWTools/bin/plain.cc -lTMVA -shared -fPIC -o libplainroot_jl
