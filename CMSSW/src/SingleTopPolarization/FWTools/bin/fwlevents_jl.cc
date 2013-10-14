#include "SingleTopPolarization/FWTools/interface/fwlite.hh"
#include "SingleTopPolarization/FWTools/interface/util.hh"

#include <DataFormats/Common/interface/MergeableCounter.h>
#include <TFile.h>

extern "C" {

    void *new_inputtag(const char *label, const char *instance, const char *process)
    {
        return new edm::InputTag(label, instance, process);
    }

    void *new_chain_event(const char **fnames, unsigned int n_fnames)
    {
        std::vector<std::string> fn;
        for (unsigned int i = 0; i < n_fnames; i++)
        {
            fn.push_back(fnames[i]);
        }
        return new fwlite::ChainEvent(fn);
    }

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

    bool events_to(fwlite::ChainEvent *ev, long n)
    {
        return ev->to(n);
    }

    long events_size(fwlite::ChainEvent *ev)
    {
        return ev->size();
    }

    long events_fileindex(fwlite::ChainEvent *ev)
    {
        return ev->fileIndex();
    }

    void *new_handle_vfloat()
    {
        return new_handle<std::vector<float>>();
    }

    void *new_handle_double()
    {
        return new_handle<double>();
    }

    void *new_handle_float()
    {
        return new_handle<float>();
    }

    void *new_handle_int()
    {
        return new_handle<int>();
    }

    Array *get_branches(fwlite::ChainEvent *ev)
    {
        std::vector<const char *> *names = new std::vector<const char *>();
        for (auto & e : ev->getBranchDescriptions())
        {
            names->push_back(e.branchName().c_str());
        }
        Array *out = (Array *)malloc(sizeof(Array));
        out->start = names->size() > 0 ? &(names->at(0)) : 0;
        out->size = sizeof(const char *);
        out->n_elems = names->size();
        return out;
    }

    const void *get_by_label_vfloat(
        const fwlite::ChainEvent *ev,
        fwlite::Handle<vector<float>> *handle,
        const edm::InputTag *label)
    {
        return get_by_label<std::vector<float>>(ev, handle, label);
    }

    const void *get_by_label_double(
        const fwlite::ChainEvent *ev,
        fwlite::Handle<double> *handle,
        const edm::InputTag *label)
    {
        return get_by_label<double>(ev, handle, label);
    }

    const void *get_by_label_float(
        const fwlite::ChainEvent *ev,
        fwlite::Handle<float> *handle,
        const edm::InputTag *label)
    {
        return get_by_label<float>(ev, handle, label);
    }

    const void *get_by_label_int(
        const fwlite::ChainEvent *ev,
        fwlite::Handle<int> *handle,
        const edm::InputTag *label)
    {
        return get_by_label<int>(ev, handle, label);
    }
}
