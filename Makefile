all: example test

setup:
	./setup.sh

example:
	cd CMSSW/src; eval `scramv1 runtime -sh`; scram b clean; scram b vclean; scram b SingleTopPolarization/FWTools; scram b -j16; eval `scramv1 runtime -sh`

test:
	edmFileUtil test_edm.root || curl -k http://phys.hep.kbfi.ee/~joosep/test_edm.root -o test_edm.root
	CMSSW/bin/$(SCRAM_ARCH)/stpol_testcode1
