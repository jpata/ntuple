#include "FWTools/FWTools/interface/fwlite.hh"

#include <DataFormats/Common/interface/TriggerResults.h>
#include <FWCore/Common/interface/TriggerNames.h>

void initialize()
{
    setvbuf(stdout, (char *)NULL, _IOLBF, 0);
    gSystem->Load("libFWCoreFWLite");
    AutoLibraryLoader::enable();
    gSystem->Load("libDataFormatsFWLite");
    std::cout << "ROOT+FWLite initialized: " << gROOT->GetVersion() << std::endl;
}

const vector<float> *get_vfloat(fwlite::Handle<vector<float>> *h, fwlite::ChainEvent *ev, const label &l);


long get_counter_sum(const char **fnames, unsigned int n_fnames, const char *src)
{
    long ret = 0;
    for (unsigned int i = 0; i < n_fnames; i++)
    {
        TFile *f = new TFile(fnames[i]);
        fwlite::LuminosityBlock ls(f);
        for (ls.toBegin(); !ls.atEnd(); ++ls)
        {
            edm::Handle<edm::MergeableCounter> counter;
            ls.getByLabel(edm::InputTag(src), counter);
            ret += counter->value;
        }
        f->Close();
    }
    return ret;
}

fwlite::Handle<edm::TriggerResults> trig_results;

bool passes_triggers(fw_event *event, const char **trignames, unsigned int n_trignames)
{
    trig_results.getByLabel(*event, "TriggerResults", "", "HLT");

    const edm::TriggerNames &trig_names = event->triggerNames(*trig_results);

    bool passes = false;
    for (unsigned int i = 0; i < n_trignames; i++)
    {
        const char *name = trignames[i];
        unsigned int idx = trig_names.triggerIndex(name);

        //trigger not found, accept will throw out_of_range
        if (idx >= trig_results->size())
        {
            continue;
        }
        passes = passes || trig_results->accept(idx);
    }
    return passes;
}
