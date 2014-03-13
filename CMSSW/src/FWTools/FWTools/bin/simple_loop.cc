#include <TH1F.h>
#include <TTree.h>
#include <TROOT.h>
#include <TFile.h>
#include <TSystem.h>
#include <TStopwatch.h>
#include <TMath.h>

#include <DataFormats/FWLite/interface/Event.h>
#include <DataFormats/Common/interface/Handle.h>
#include <FWCore/FWLite/interface/AutoLibraryLoader.h>

#include <DataFormats/PatCandidates/interface/Muon.h>
#include <PhysicsTools/FWLite/interface/TFileService.h>

using namespace std;

int main(int argc, char *argv[])
{
    // load framework libraries
    gSystem->Load( "libFWCoreFWLite" );
    AutoLibraryLoader::enable();

    std::vector<std::string> inputFiles;
    inputFiles.push_back("input.root");

    std::string outputFile("output.root");

    fwlite::TFileService fs = fwlite::TFileService(outputFile.c_str());

    TFileDirectory dir = fs.mkdir("trees");
    TTree *out_tree = 0;
    out_tree = dir.make<TTree>("Events", "Events");

    // loop over the events
    int ievt = 0;
    long bytes_read = 0;
    TStopwatch *stopwatch = new TStopwatch();
    stopwatch->Start();

    edm::Handle<std::vector<pat::Muon>> muons;
    edm::InputTag muonSource("selectedPatMuons");

    //file loop
    for (unsigned int iFile = 0; iFile < inputFiles.size(); ++iFile)
    {
        // open input file (can be located on castor)
        std::cout << "Opening file " << inputFiles[iFile] << std::endl;
        TFile *in_file = TFile::Open(inputFiles[iFile].c_str());
        if ( in_file )
        {
            std::cout << "File opened successfully" << std::endl;
            double file_time = stopwatch->RealTime();
            stopwatch->Continue();

            fwlite::Event ev(in_file);
            std::cout << "Looping over " << ev.size() << " events" << std::endl;
            //Event loop
            for (ev.toBegin(); !ev.atEnd(); ++ev, ++ievt)
            {
                std::cout << "event " << ievt << std::endl;

                //get the current event
                edm::EventBase const &event = ev;

                event.getByLabel(muonSource, muons);
                for(const pat::Muon& muon : *muons) {
                    std::cout << "muon " << muon.pt() << std::endl;
                }
            }
            
            in_file->Close();
            file_time = stopwatch->RealTime() - file_time;
            stopwatch->Continue();
            bytes_read += in_file->GetBytesRead();
            std::cout << "Closing file " << in_file->GetPath() << " with " << in_file->GetBytesRead() / (1024 * 1024) << " Mb read, "
                    << in_file->GetBytesRead() / (1024 * 1024) / file_time << " Mb/s" << std::endl;
        }
        else
        {
            std::cerr << "Couldn't open an input file: " << inputFiles[iFile] << std::endl;
            continue;
        }
    }

    return 0;
}
