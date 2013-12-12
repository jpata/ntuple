#include "SingleTopPolarization/FWTools/interface/fwlite.hh"
#include "SingleTopPolarization/FWTools/interface/util.hh"
#include <sys/utsname.h>
#include <unistd.h>

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

        //int i = 1;
        //for (auto& s : fn) {
        //    std::cout << "fwlevents_jl infile " << i << " " << s << std::endl;
        //    i++;
        //}
        return new fwlite::ChainEvent(fn);
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
    
    long events_eventindex(fwlite::ChainEvent *ev)
    {
        return ev->eventIndex();
    }
    
    const char* events_tfile_path(fwlite::ChainEvent *ev)
    {
        return ev->getTFile()->GetPath();
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
    
    void *new_handle_uint()
    {
        return new_handle<unsigned int>();
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
    
    const void *get_by_label_uint(
        const fwlite::ChainEvent *ev,
        fwlite::Handle<unsigned int> *handle,
        const edm::InputTag *label)
    {
        return get_by_label<unsigned int>(ev, handle, label);
    }

    long get_event_run(fw_event *ev)
    {
        edm::EventID id = ev->id();
        return id.run();
    }
    
    long get_event_lumi(fw_event *ev)
    {
        edm::EventID id = ev->id();
        return id.luminosityBlock();
    }
    
    long get_event_event(fw_event *ev)
    {
        edm::EventID id = ev->id();
        return id.event();
    }
}
