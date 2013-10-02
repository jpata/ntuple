all: example test

setup:
	./setup.sh

lib:
	cd CMSSW/src; eval `scramv1 runtime -sh`; scram b clean; scram b vclean; scram b SingleTopPolarization/FWTools

example: lib
	cd CMSSW/src; eval `scramv1 runtime -sh`; scram b -j16; eval `scramv1 runtime -sh`

test: testc testpy
testc:
	edmFileUtil test_edm.root || curl -k http://phys.hep.kbfi.ee/~joosep/test_edm.root -o test_edm.root
	cd CMSSW/src; eval `scramv1 runtime -sh`; cd ../..; CMSSW/bin/$(SCRAM_ARCH)/stpol_testcode1

testpy:
	edmFileUtil test_edm.root || curl -k http://phys.hep.kbfi.ee/~joosep/test_edm.root -o test_edm.root
	python src/test.py test_edm.root
