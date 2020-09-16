// -*- C++ -*-
//
// Package:    GenInfo/GenInfo
// Class:      GenInfo
// 
/**\class GenInfo GenInfo.cc GenInfo/GenInfo/plugins/GenInfo.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  
//         Created:  Tue, 15 Sep 2020 14:33:06 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "vector"


using namespace reco;


class GenInfo : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit GenInfo(const edm::ParameterSet&);
      ~GenInfo();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

	  edm::EDGetTokenT<reco::GenParticleCollection> genToken_;  //--used to access GenParticleCollectio

	 // TTree* outTree;

		// PT
	  std::vector<double> v_Zele1_pt;
	  std::vector<double> v_Zele2_pt;
	  std::vector<double> v_Wmele_pt;
	  std::vector<double> v_Wpele_pt;
	  
	  std::vector<double> v_Zmu1_pt;
	  std::vector<double> v_Zmu2_pt;
	  std::vector<double> v_Wmmu_pt;
	  std::vector<double> v_Wpmu_pt;

	  std::vector<double> v_Zta1_pt;
	  std::vector<double> v_Zta2_pt;
	  std::vector<double> v_Wmta_pt;
	  std::vector<double> v_Wpta_pt;

	  std::vector<double> v_Wmnu_pt;
	  std::vector<double> v_Wpnu_pt;
	  std::vector<double> v_pho_pt;
	  
		// Eta
	  std::vector<double> v_Zele1_eta;
	  std::vector<double> v_Zele2_eta;
	  
	  std::vector<double> v_Zmu1_eta;
	  std::vector<double> v_Zmu2_eta;

	  std::vector<double> v_Zta1_eta;
	  std::vector<double> v_Zta2_eta;

	  std::vector<double> v_pho_eta;
	  
		// Phi
      std::vector<double> v_Zele1_phi;
	  std::vector<double> v_Zele2_phi;
	  std::vector<double> v_Wmele_phi;
	  std::vector<double> v_Wpele_phi;
	  
	  std::vector<double> v_Zmu1_phi;
	  std::vector<double> v_Zmu2_phi;
	  std::vector<double> v_Wmmu_phi;
	  std::vector<double> v_Wpmu_phi;

	  std::vector<double> v_Zta1_phi;
	  std::vector<double> v_Zta2_phi;
	  std::vector<double> v_Wmta_phi;
	  std::vector<double> v_Wpta_phi;

	  std::vector<double> v_Wmnu_phi;
	  std::vector<double> v_Wpnu_phi;
	  std::vector<double> v_pho_phi;
	  
		// Et
	  std::vector<double> v_Wmele_et;
	  std::vector<double> v_Wpele_et;
	  std::vector<double> v_Wmmu_et;
	  std::vector<double> v_Wpmu_et;
	  std::vector<double> v_Wmta_et;
	  std::vector<double> v_Wpta_et;
	  std::vector<double> v_Wmnu_et;
	  std::vector<double> v_Wpnu_et;

	  double Zele1_pt;
	  double Zele2_pt;
	  double Wmele_pt;
	  double Wpele_pt;
	  double Zmu1_pt;
	  double Zmu2_pt;
	  double Wmmu_pt;
	  double Wpmu_pt;
	  double Zta1_pt;
	  double Zta2_pt;
	  double Wmta_pt;
	  double Wpta_pt;
	  double Wmnu_pt;
	  double Wpnu_pt;
	  double pho_pt;
	  double Zele1_eta;
	  double Zele2_eta;
	  double Zmu1_eta;
	  double Zmu2_eta;
	  double Zta1_eta;
	  double Zta2_eta;
	  double pho_eta;
	  double Zele1_phi;
	  double Zele2_phi;
	  double Wmele_phi;
	  double Wpele_phi;
	  double Zmu1_phi;
	  double Zmu2_phi;
	  double Wmmu_phi;
	  double Wpmu_phi;
	  double Zta1_phi;
	  double Zta2_phi;
	  double Wmta_phi;
	  double Wpta_phi;
	  double Wmnu_phi;
	  double Wpnu_phi;
	  double pho_phi;
	  double Wmele_et;
	  double Wpele_et;
	  double Wmmu_et;
	  double Wpmu_et;
	  double Wmta_et;
	  double Wpta_et;
	  double Wmnu_et;
	  double Wpnu_et;


};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

// --constructors and destructor

GenInfo::GenInfo(const edm::ParameterSet& iConfig)
	//edm::Service<TFileService> fs;
	//outTree = fs->make<TTree> ("outTree","outTree")
{

   //now do what ever initialization is needed
	genToken_ = consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("GenParticles")); //-- GenParticle


	/*
	//outTree->Branch("pho_pt",phit_pt&);
	outTree->Branch("Zele1_pt",  Zele1_pt&);
    outTree->Branch("Zele2_pt",  Zele2_pt&);
    outTree->Branch("Wmele_pt",  Wmele_pt&);
    outTree->Branch("Wpele_pt",  Wpele_pt&);
    outTree->Branch("Zmu1_pt",   Zmu1_pt&);
    outTree->Branch("Zmu2_pt",   Zmu2_pt&);
    outTree->Branch("Wmmu_pt",   Wmmu_pt&);
    outTree->Branch("Wpmu_pt",   Wpmu_pt&);
    outTree->Branch("Zta1_pt",   Zta1_pt&);
    outTree->Branch("Zta2_pt",   Zta2_pt&);
    outTree->Branch("Wmta_pt",   Wmta_pt&);
    outTree->Branch("Wpta_pt",   Wpta_pt&);
    outTree->Branch("Wmnu_pt",   Wmnu_pt&);
    outTree->Branch("Wpnu_pt",   Wpnu_pt&);
    outTree->Branch("pho_pt",    pho_pt&);
    outTree->Branch("Zele1_eta", Zele1_eta&);
    outTree->Branch("Zele2_eta", Zele2_eta&);
    outTree->Branch("Zmu1_eta",  Zmu1_eta&);
    outTree->Branch("Zmu2_eta",  Zmu2_eta&);
    outTree->Branch("Zta1_eta",  Zta1_eta&);
    outTree->Branch("Zta2_eta",  Zta2_eta&);
    outTree->Branch("pho_eta",   pho_eta&);
    outTree->Branch("Zele1_phi", Zele1_phi&);
    outTree->Branch("Zele2_phi", Zele2_phi&);
    outTree->Branch("Wmele_phi", Wmele_phi&);
    outTree->Branch("Wpele_phi", Wpele_phi&);
    outTree->Branch("Zmu1_phi",  Zmu1_phi&);
    outTree->Branch("Zmu2_phi",  Zmu2_phi&);
    outTree->Branch("Wmmu_phi",  Wmmu_phi&);
    outTree->Branch("Wpmu_phi",  Wpmu_phi&);
    outTree->Branch("Zta1_phi",  Zta1_phi&);
    outTree->Branch("Zta2_phi",  Zta2_phi&);
    outTree->Branch("Wmta_phi",  Wmta_phi&);
    outTree->Branch("Wpta_phi",  Wpta_phi&);
    outTree->Branch("Wmnu_phi",  Wmnu_phi&);
    outTree->Branch("Wpnu_phi",  Wpnu_phi&);
    outTree->Branch("pho_phi",   pho_phi&);
    outTree->Branch("Wmele_et",  Wmele_et&);
    outTree->Branch("Wpele_et",  Wpele_et&);
    outTree->Branch("Wmmu_et",   Wmmu_et&);
    outTree->Branch("Wpmu_et",   Wpmu_et&);
    outTree->Branch("Wmta_et",   Wmta_et&);
    outTree->Branch("Wpta_et",   Wpta_et&);
    outTree->Branch("Wmnu_et",   Wmnu_et&);
    outTree->Branch("Wpnu_et",   Wpnu_et&);
	*/

}


GenInfo::~GenInfo()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
GenInfo::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	using namespace std;	

	Handle<GenParticleCollection> genParticles;
	iEvent.getByLabel("genParticles", genParticles);
	
	v_pho_pt.clear();

//		cout << "PID" << " , " <<  "Status" << " , " << "N of Daughter" << " , " << "pt" << " , " << "eta" << " , " << "phi" << " , " << "charge" << endl;

    for(size_t i = 0; i < genParticles->size(); ++ i) {
        const GenParticle & p = (*genParticles)[i];
        int id = p.pdgId();
        int st = p.status();
        const Candidate * mom = p.mother();
        double pt = p.pt(), eta = p.eta(), phi = p.phi(), mass = p.mass();
        double vx = p.vx(), vy = p.vy(), vz = p.vz();
        int charge = p.charge();
        size_t n = p.numberOfDaughters();
	

//		cout << id << " , " <<  st << " , " << n << " , " << pt << " , " << eta << " , " << phi << " , " << charge << endl;


	/*       
		// --Photon 
		if ( id == 22 ){
			v_pho_pt.push_back(p.pt())	;
			cout << <<p.pt() << endl;
		}
		
		// --Z boson
		// Electron1 
		if ( id == 11 && mom->pdgId() == 23  ){	
			v_Zele1_pt.push_back(p.pt())	;
			v_Zele1_eta.push_back(p.eta()) ;	
			v_Zele1_phi.push_back(p.phi()) ;
		}
		// Electron2 
		if ( id == -11 && mom->pdgId() == 23  ){	
			v_Zele2_pt.push_back(p.pt())	;
			v_Zele2_eta.push_back(p.eta())	;
			v_Zele2_phi.push_back(p.phi())	;
		}
		
		// Muon1 
		if ( id == 13 && mom->pdgId() == 23  ){	
			v_Zmu1_pt.push_back(p.pt())	;
			v_Zmu1_eta.push_back(p.eta()) ;	
			v_Zmu1_phi.push_back(p.phi()) ;
		}
		// Muon2 
		if ( id == -13 && mom->pdgId() == 23  ){	
			v_Zmu2_pt.push_back(p.pt())	;
			v_Zmu2_eta.push_back(p.eta())	;
			v_Zmu2_phi.push_back(p.phi())	;
		}
			
		// tau1 
		if ( id == 15 && mom->pdgId() == 23  ){	
			v_Zta1_pt.push_back(p.pt())	;
			v_Zta1_eta.push_back(p.eta()) ;	
			v_Zta1_phi.push_back(p.phi()) ;
		}
		// tau2 
		if ( id == -15 && mom->pdgId() == 23  ){	
			v_Zta2_pt.push_back(p.pt())	;
			v_Zta2_eta.push_back(p.eta())	;
			v_Zta2_phi.push_back(p.phi())	;
		}
		

		// --W- boson
		// Electron 
		if ( id == 11 && mom->pdgId() == -24  ){	
			v_Wmele_pt.push_back(p.pt())	;
			v_Wmele_phi.push_back(p.phi()) ;
			v_Wmele_et.push_back(p.et())	;
		}
		// Muon 
		if ( id == 13 && mom->pdgId() == -24  ){	
			v_Wmmu_pt.push_back(p.pt())	;
			v_Wmmu_phi.push_back(p.phi()) ;
			v_Wmmu_et.push_back(p.et())	;
		}
		// tau
		if ( id == 15 && mom->pdgId() == -24  ){	
			v_Wmta_pt.push_back(p.pt())	;
			v_Wmta_phi.push_back(p.phi()) ;
			v_Wmta_et.push_back(p.et())	;
		}
		
		// --W+ boson
		// Electron 
		if ( id == -11 && mom->pdgId() == 24  ){	
			v_Wpele_pt.push_back(p.pt())	;
			v_Wpele_phi.push_back(p.phi()) ;
			v_Wpele_et.push_back(p.et())	;
		}
		// Muon 
		if ( id == -13 && mom->pdgId() == 24  ){	
			v_Wpmu_pt.push_back(p.pt())	;
			v_Wpmu_phi.push_back(p.phi()) ;
			v_Wpmu_et.push_back(p.et())	;
		}
		// tau
		if ( id == -15 && mom->pdgId() == 24  ){	
			v_Wpta_pt.push_back(p.pt())	;
			v_Wpta_phi.push_back(p.phi()) ;
			v_Wpta_et.push_back(p.et())	;
		}

	*/


		//std::cout << id << std::endl; // -- Check output 

        for(size_t j = 0; j < n; ++ j) {
            const Candidate * d = p.daughter( j );
            int dauId = d->pdgId();
        }
    }

	



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
GenInfo::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenInfo::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenInfo::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenInfo);
