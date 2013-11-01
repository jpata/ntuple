TESTFILE=http://phys.hep.kbfi.ee/~joosep/test_100ev.root

.PHONY: setup testfile

all: clean lib

clean:
	cd CMSSW/src; eval `scramv1 runtime -sh`; scram b clean; scram b vclean;

setup:
	./setup.sh

lib: clean
	cd CMSSW/src; eval `scramv1 runtime -sh`; scram b SingleTopPolarization/FWTools