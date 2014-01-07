#include <TTree.h>
#include <TFile.h>
#include <TLeaf.h>

#include "SingleTopPolarization/FWTools/interface/util.hh"

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

    void tfile_close(TFile *fi)
    {
        fi->Write();
        fi->Close();
    }

    void *tfile_get(TFile *fi, const char *key)
    {
        return fi->Get(key);
    }

    void *tfile_mkdir(TFile *fi, const char *dir)
    {
        return fi->mkdir(dir);
    }

    void *tfile_cd(TFile *fi, const char *dir)
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


}
