all: example test

setup:
	./setup.sh

example:
	cd CMSSW/src; scram b clean; scram b vclean; scram b -j16

test:
	edmFileUtil test_edm.root || curl -k http://phys.hep.kbfi.ee/~joosep/test_edm.root -o test_edm.root
	CMSSW/bin/$(SCRAM_ARCH)/eventloop_example
