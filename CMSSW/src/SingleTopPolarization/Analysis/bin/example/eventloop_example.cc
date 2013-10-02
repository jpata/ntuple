//This file can be copied as an example for your own loop

//The public interface, which is kept more or less constant
#include "src/headers/stpol.hh" //present in $STPOL_DIR/src/headers/stpol.hh

using namespace stpol::stable;

int main(int argc, char **argv)
{

    //Call the FWLite library loaders
    initialize();

    //Our list of input files
    vector<string> fn;
    fn.push_back("test_edm.root");

    fw_event *events = new fw_event(fn);

    for (unsigned int i = 0; i < events->size(); i++)
    {
        events->to(i);
        
        const event_id evid = get_event_id(events); //defined in fwlite.hh

        float mu_pt = signal::muon.pt(events); //defined in stpol.hh, namespace stpol::stable
        float ele_pt = signal::electron.pt(events);
        
        std::cout << evid.run << ":" << evid.lumi << ":" << evid.event << " " << mu_pt << " | " << ele_pt << std::endl;
    }

    return 0;
}
