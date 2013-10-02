import sys
import os

#Monkey-patch the system path to import the stpol header
sys.path.append(os.path.join(os.environ["STPOL_DIR"], "src/headers"))
from stpol import stpol, list_methods

from DataFormats.FWLite import Events, Handle, Lumis

#Print what methods are available for an object in a "flat" format for a simple overview
print "Muon properties (stpol.stable.signal.muon):"
list_methods(stpol.stable.signal.muon)
print "Electron properties (stpol.stable.signal.electron):"
list_methods(stpol.stable.signal.electron)


#Open the list of files supplied on the command line
file_list = sys.argv[1:]
events = Events(file_list)


#Very temporary short names for convenience
e = stpol.stable.event
sigmu = stpol.stable.signal.muon
sigele = stpol.stable.signal.electron
#Loop over the events
for event in events:

    print e.id(event)
    mu_pt = sigmu.pt(event)
    ele_pt = sigele.pt(event)
    print "met=", e.met(event), "mu_pt=",mu_pt, "ele_pt=",ele_pt
    print "mu_iso=", sigmu.iso(event), "ele_iso=", sigele.iso(event)
