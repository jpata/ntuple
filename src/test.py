import sys
import os

#Monkey-patch the system path to import the stpol header
sys.path.append(os.path.join(os.environ["STPOL_DIR"], "src/headers"))
from stpol import stpol, list_methods

from DataFormats.FWLite import Events, Handle, Lumis

#Print what methods are available for an object in a "flat" format for a simple overview
#print "Muon properties (stpol.stable.tchan.muon):"
#list_methods(stpol.stable.tchan.muon)
#print "Electron properties (stpol.stable.tchan.electron):"
#list_methods(stpol.stable.tchan.electron)


#Open the list of files supplied on the command line
file_list = sys.argv[1:]
events = Events(file_list)

for fi in file_list:
    print fi, stpol.stable.file.total_processed(fi), stpol.stable.file.sample_type(fi)

#Very temporary short names for convenience
e = stpol.stable.event
sigmu = stpol.stable.tchan.muon
sigele = stpol.stable.tchan.electron
#Loop over the events


for event in events:
    print e.id(event)
    mu_pt = sigmu.pt(event)
    ele_pt = sigele.pt(event)
    print "met=", e.met(event), "mu_pt=",mu_pt, "ele_pt=",ele_pt
    print "mu_iso=", sigmu.iso(event), "ele_iso=", sigele.iso(event)
    print "njets=", e.njets(event), "ntags=", e.ntags(event)
    print "nmuons=", e.nmuons(event)
    print "nelectrons=", e.nelectrons(event)
    print "bjet_pt=", stpol.stable.tchan.bjet.pt(event)
    print "ljet_pt=", stpol.stable.tchan.specjet1.pt(event)
    print "c=", e.c(event)
    print "costheta=", e.costheta.lj(event)
    print "csv=", stpol.stable.tchan.bjet.bd_csv(event)
    print "tchp=", stpol.stable.tchan.bjet.bd_tchp(event)
