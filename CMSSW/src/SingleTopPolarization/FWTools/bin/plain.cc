#include <TTree.h>
#include <TFile.h>
#include "SingleTopPolarization/FWTools/interface/util.hh"

extern "C" {

    TFile *new_tfile(const char *name, const char *op)
    {
        return TFile::Open(name, op);
    }

    TTree *new_ttree(TFile *fi, const char *name)
    {
        fi->cd();
        return new TTree(name, name);
    }

    void tfile_close(TFile *fi)
    {
        fi->Write();
        fi->Close();
    }

    void *tfile_get(TFile *fi, const char *key)
    {
        return fi->Get(key);
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

    void ttree_set_branch_address(TTree *tree, TBranch *br, const char *name)
    {
        tree->SetBranchAddress(name, br);
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


}