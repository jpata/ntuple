#include <TTree.h>
#include <TChain.h>
#include <TFile.h>
#include <TLeaf.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TAxis.h>
#include <TMVA/Reader.h>

#include <iostream>
#include "FWTools/FWTools/interface/util.hh"

struct TreeBranch
{
    char *name;
    char *dtype;
    TBranch *branch;
};

extern "C" {

    TFile *new_tfile(const char *name, const char *op)
    {
        return TFile::Open(name, op, name, 1);
    }

    TTree *new_ttree(TFile *fi, const char *name)
    {
        fi->cd();
        return new TTree(name, name);
    }
    
    TTree *new_tchain(TFile *fi, const char *name)
    {
        fi->cd();
        return new TChain(name, name);
    }

    void tfile_close(TFile *fi)
    {
        //fi->Write();
        fi->Close();
    }

    void tobject_write(TObject* t)
    {
        t->Write("", TObject::kOverwrite);
    }

    void ttree_write(TTree* t)
    {
        tobject_write(t);
    }
    
    void tbranch_write(TBranch* t)
    {
        tobject_write(t);
    }

    void *tfile_get(TFile *fi, const char *key)
    {
        return fi->Get(key);
    }

    bool tchain_add_file(TChain *ch, const char *file)
    {
        return ch->AddFile(file);
    }

    void *tfile_mkdir(TFile *fi, const char *dir)
    {
        return fi->mkdir(dir);
    }

    void tfile_ls(TFile *fi)
    {
        fi->ls();
    }

    bool tfile_cd(TFile *fi, const char *dir)
    {
        return fi->cd(dir);
    }

    TBranch *new_tbranch(TTree *tree, const char *brname, void *braddr, const char *leaflist)
    {
        return new TBranch(tree, brname, braddr, leaflist);
    }

    TBranch *ttree_branch(TTree *tree, const char *brname, void *braddr, const char *leaflist)
    {
        return tree->Branch(brname, braddr, leaflist);
    }

    long ttree_fill(TTree *tree)
    {
        return tree->Fill();
    }
    
    long tbranch_fill(TBranch *branch)
    {
        return branch->Fill();
    }

    int ttree_set_branch_address(TTree *tree, TBranch *br, const char *name)
    {
        return tree->SetBranchAddress(name, br);
    }
    
    void ttree_set_branch_status(TTree *tree, const char *name, bool status)
    {
        tree->SetBranchStatus(name, status);
    }

    long ttree_get_entries(TTree *tree)
    {
        return tree->GetEntries();
    }

    long ttree_get_entry(TTree *tree, long n)
    {
        return tree->GetEntry(n);
    }

    long tbranch_get_entry(TBranch *branch, long n)
    {
        return branch->GetEntry(n);
    }

    void ttree_reset_cache(TTree* tree)
    {
        tree->SetCacheSize(10000000);
    }
    
    void ttree_add_cache(TTree* tree, const char* branches)
    {
        tree->AddBranchToCache(branches);
    }

    Array *ttree_get_branches(TTree *tree)
    {
        TObjArray *brlist = tree->GetListOfBranches();
        unsigned int n_branches = brlist->GetEntries();
        TreeBranch *br_infos = (TreeBranch *)malloc(sizeof(TreeBranch) * n_branches);

        Array *out = (Array *)malloc(sizeof(Array));
        for (unsigned int i = 0; i < n_branches; i++)
        {
            TBranch *br = ((TBranch *)(*brlist)[i]);
            //LogInfo << br->GetName() << std::endl;
            if (br->GetNleaves() != 1)
            {
                //                LogInfo << "Complex branch n=" << i << ": " << br->GetName() << ", skipping" << std::endl;
                continue;
            }

            TObjArray *leaves = br->GetListOfLeaves();
            TLeaf *leaf = br->GetLeaf((*leaves)[0]->GetName());
            //Need to include +1 for terminator
            br_infos[i].name = (char *)malloc(sizeof(char) * (1 + strlen(br->GetName())));
            br_infos[i].dtype = (char *)malloc(sizeof(char) * (1 + strlen(leaf->GetTypeName())));
            br_infos[i].branch = br;
            strcpy(br_infos[i].name, br->GetName());
            strcpy(br_infos[i].dtype, leaf->GetTypeName());
            //LogInfo << br_infos[i].name << ":" << br_infos[i].dtype << std::endl;
        }
        out->start = (void *)br_infos;
        out->size = sizeof(TreeBranch);
        out->n_elems = n_branches;

        return out;
    }

    void* new_th1d(
        const char* name,
        unsigned int nbins, //N 
        double* edges, //N+1 low1, low2, ... ,lowN, highN
        double* bins, //N+2 under, 1, 2, ... , over
        double* errors, //N+2 under, 1, 2, ... , over
        const char** labels=0,  //N+1 under, 1, 2, ... , over
        const double nentries=0.0
    ) {

        TH1D* hi = new TH1D(name, name, nbins-1, edges);
        //0 - underflow, nbins - overflow
        for (unsigned int i=0;i<=nbins;i++) {
            hi->SetBinContent(i, bins[i]);
            hi->SetBinError(i, errors[i]);
            if (labels!=0 && i>0 && i<nbins) {
                hi->GetXaxis()->SetBinLabel(i, labels[i-1]);
            }
        }
        hi->SetEntries(nentries);
        return hi;
    }

    void set_axis_label(TH1* h, int a, const char* label) {
        if (a<1 || a>3) {
            std::cerr << "incorrect axis index " << a << " !in [1,3]." << std::endl;
            return;
        }

        TAxis* ax = 0;
        if (a==1)
            ax = h->GetXaxis();
        if (a==2)
            ax = h->GetYaxis();
        if (a==3)
            ax = h->GetZaxis();

        ax->SetTitle(label);
    }

    void* new_th2d(
        const char* name,
        unsigned int nbins_x, 
        unsigned int nbins_y,

        double* edges_x,
        double* edges_y,

        double** bins,

        double** errors,

        const char** labels_x=0,
        const char** labels_y=0,
        const double nentries=0.0
    ) {
        TH2D* hi = new TH2D(name, name, nbins_x-1, edges_x, nbins_y-1, edges_y);
        for (unsigned int x=0;x<=nbins_x;x++) {
            
            if (labels_x!=0 && x>0 && x<nbins_x) {
                hi->GetXaxis()->SetBinLabel(x, labels_x[x-1]);
            }

            for (unsigned int y=0;y<=nbins_y;y++) {
                hi->SetBinContent(x, y, bins[x][y]);
                hi->SetBinError(x, y, errors[x][y]);

                if (labels_y!=0 && y>0 && y<nbins_y) {
                    hi->GetYaxis()->SetBinLabel(y, labels_y[y-1]);
                }
            }
        }
        hi->SetEntries(nentries);
        return hi;
    }

    double th1d_get_bin_content(TH1D* h, unsigned int n) {
        return h->GetBinContent(n);
    }

    double th1d_get_bin_error(TH1D* h, unsigned int n) {
        return h->GetBinError(n);
    }

    double th2d_get_bin_content(TH2D* h, unsigned int n, unsigned int m) {
        return h->GetBinContent(n, m);
    }

    double th2d_get_bin_error(TH2D* h, unsigned int n, unsigned int m) {
        return h->GetBinError(n, m);
    }

    int th1d_get_n_bins(TH1D* h, unsigned int n) {
        if (n == 1) {
            return h->GetNbinsX();
        }
        else if (n == 2) {
            return h->GetNbinsY();
        }
        else if (n == 3) {
            return h->GetNbinsZ();
        }
        return -1;
    }


    ///
    /// TMVA wrappers
    ///
    void* new_tmva_reader(const char* name) {
        return new TMVA::Reader(name);
    }

    void tmva_reader_add_variable(TMVA::Reader* reader, const char* name, float* p, unsigned int var_type) {
        if (var_type==0) {
            reader->AddVariable(TString(name), p);
        }
        else if (var_type==1) {
            reader->AddSpectator(TString(name), p);
        }
        else {
            throw std::exception();
        }
    }

    void tmva_book_mva(TMVA::Reader* reader, const char* mva_name, const char* weight_file) {
        reader->BookMVA(mva_name, weight_file);
    }

    double tmva_evaluate_mva(TMVA::Reader* reader, const char* mva_name) {
        return (double)(reader->EvaluateMVA(mva_name));
    }
}
