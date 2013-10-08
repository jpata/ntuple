TESTFILE=http://phys.hep.kbfi.ee/~joosep/test_100ev.root

.PHONY: setup testfile

all: lib example test

clean:
	cd CMSSW/src; eval `scramv1 runtime -sh`; scram b clean; scram b vclean;

setup:
	./setup.sh

lib: clean
	cd CMSSW/src; eval `scramv1 runtime -sh`; scram b SingleTopPolarization/FWTools

example: lib
	cd CMSSW/src; eval `scramv1 runtime -sh`; scram b -j16; eval `scramv1 runtime -sh`

testfile:
	edmFileUtil test_edm.root || curl -k $(TESTFILE) -o test_edm.root && edmFileUtil test_edm.root

test: testc testpy

testc: testfile
	cd CMSSW/src; eval `scramv1 runtime -sh`; cd ../..; CMSSW/bin/$(SCRAM_ARCH)/stpol_testcode1

testpy: testfile
	python src/test.py test_edm.root
