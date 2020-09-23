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
#include "TTree.h"

using namespace reco;


class GenInfo : public edm::one::EDAnalyzer<edm::one::SharedResources>{
	public:
		explicit GenInfo(const edm::ParameterSet&);
		~GenInfo();

		static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


	private:
		virtual void beginJob() override;
		virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
		virtual void endJob() override;
	
		edm::EDGetTokenT<reco::GenParticleCollection> genToken_;//--used to access GenParticleCollectio

		int Znum;
		int Ze1,Ze2;
		int Zmu1,Zmu2;
		int Zta1,Zta2;
		int Wme,Wmenu;
		int Wmmu,Wmmunu;
		int Wmta,Wmtanu;
		int Wpe, Wpenu;
		int Wpmu,Wpmunu;
		int Wpta,Wptanu;
		int Pho;
		int cnt;

		TTree* outTree;
	
		std::vector<double> v_Ze1_pt,v_Ze1_eta,v_Ze1_phi,v_Ze1_E;
		std::vector<double> v_Ze2_pt,v_Ze2_eta,v_Ze2_phi,v_Ze2_E;
		std::vector<double> v_Zmu1_pt,v_Zmu1_eta,v_Zmu1_phi,v_Zmu1_E;
		std::vector<double> v_Zmu2_pt,v_Zmu2_eta,v_Zmu2_phi,v_Zmu2_E;
		std::vector<double> v_Zta1_pt,v_Zta1_eta,v_Zta1_phi,v_Zta1_E;
		std::vector<double> v_Zta2_pt,v_Zta2_eta,v_Zta2_phi,v_Zta2_E;

		std::vector<double> v_Wpe_pt,v_Wpe_eta,v_Wpe_phi,v_Wpe_E;        
		std::vector<double> v_Wpmu_pt,v_Wpmu_eta,v_Wpmu_phi,v_Wpmu_E;
		std::vector<double> v_Wpta_pt,v_Wpta_eta,v_Wpta_phi,v_Wpta_E;
		std::vector<double> v_Wpenu_pt,v_Wpenu_et,v_Wpenu_phi,v_Wpenu_E;
		std::vector<double> v_Wpmunu_pt,v_Wpmunu_et,v_Wpmunu_phi,v_Wpmunu_E;
		std::vector<double> v_Wptanu_pt,v_Wptanu_et,v_Wptanu_phi,v_Wptanu_E;
		
		std::vector<double> v_Wme_pt,v_Wme_eta,v_Wme_phi,v_Wme_E;
		std::vector<double> v_Wmmu_pt,v_Wmmu_eta,v_Wmmu_phi,v_Wmmu_E;
		std::vector<double> v_Wmta_pt,v_Wmta_eta,v_Wmta_phi,v_Wmta_E;
		std::vector<double> v_Wmenu_pt,v_Wmenu_et,v_Wmenu_phi,v_Wmenu_E;
		std::vector<double> v_Wmmunu_pt,v_Wmmunu_et,v_Wmmunu_phi,v_Wmmunu_E;
		std::vector<double> v_Wmtanu_pt,v_Wmtanu_et,v_Wmtanu_phi,v_Wmtanu_E;
		std::vector<double> v_Pho_pt,v_Pho_eta,v_Pho_phi,v_Pho_E;
	


		double ze1_pt,ze1_eta,ze1_phi,ze1_E;
		double ze2_pt,ze2_eta,ze2_phi,ze2_E;

		double zmu1_pt,zmu1_eta,zmu1_phi,zmu1_E;
		double zmu2_pt,zmu2_eta,zmu2_phi,zmu2_E;

		double zta1_pt,zta1_eta,zta1_phi,zta1_E;
		double zta2_pt,zta2_eta,zta2_phi,zta2_E;

		double wpe_pt,wpe_eta,wpe_phi,wpe_E;
		double wpmu_pt,wpmu_eta,wpmu_phi,wpmu_E;
		double wpta_pt,wpta_eta,wpta_phi,wpta_E;
		double wme_pt,wme_eta,wme_phi,wme_E;
		double wmmu_pt,wmmu_eta,wmmu_phi,wmmu_E;
		double wmta_pt,wmta_eta,wmta_phi,wmta_E;

		double wpenu_pt,wpenu_et,wpenu_phi,wpenu_E;
		double wpmunu_pt,wpmunu_et,wpmunu_phi,wpmunu_E;
		double wptanu_pt,wptanu_et,wptanu_phi,wptanu_E;
		double wmenu_pt,wmenu_et,wmenu_phi,wmenu_E;
		double wmmunu_pt,wmmunu_et,wmmunu_phi,wmmunu_E;
		double wmtanu_pt,wmtanu_et,wmtanu_phi,wmtanu_E;
	
		double pho_pt, pho_eta, pho_phi,pho_E;


};


GenInfo::GenInfo(const edm::ParameterSet& iConfig)
{
	edm::Service<TFileService> fs;
	outTree = fs->make<TTree> ("outTree","outTree");

	//now do what ever initialization is needed
	genToken_ = consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("GenParticles")); //-- GenParticle
	

	Znum=0;
	Ze1=0;
	Ze2=0;
	Zmu1=0;
	Zmu2=0;
	Zta1=0;
	Zta2=0;
	Wme=0;
	Wmenu=0;
	Wmmu=0;
	Wmmunu=0;
	Wmta=0;
	Wmtanu=0;
	Wpe=0;
	Wpenu=0;
	Wpmu=0;
	Wpmunu=0;
	Wpta=0;
	Wptanu=0;
	cnt=0;
	Pho=0;


	outTree->Branch("ze1_pt" ,&ze1_pt);
	outTree->Branch("ze1_eta",&ze1_eta);
	outTree->Branch("ze1_phi",&ze1_phi);
	outTree->Branch("ze1_E",&ze1_E);
	outTree->Branch("ze2_pt" ,&ze2_pt);
	outTree->Branch("ze2_eta",&ze2_eta);
	outTree->Branch("ze2_phi",&ze2_phi);
	outTree->Branch("ze2_E",&ze2_E);

	outTree->Branch("zmu1_pt" ,&zmu1_pt);
	outTree->Branch("zmu1_eta",&zmu1_eta);
	outTree->Branch("zmu1_phi",&zmu1_phi);
	outTree->Branch("zmu1_E",&zmu1_E);
	outTree->Branch("zmu2_pt" ,&zmu2_pt);
	outTree->Branch("zmu2_eta",&zmu2_eta);
	outTree->Branch("zmu2_phi",&zmu2_phi);
	outTree->Branch("zmu2_E",&zmu2_E);

	outTree->Branch("zta1_pt" ,&zta1_pt);
	outTree->Branch("zta1_eta",&zta1_eta);
	outTree->Branch("zta1_phi",&zta1_phi);
	outTree->Branch("zta1_E",&zta1_E);
	outTree->Branch("zta2_pt" ,&zta2_pt);
	outTree->Branch("zta2_eta",&zta2_eta);
	outTree->Branch("zta2_phi",&zta2_phi);
	outTree->Branch("zta2_E",&zta2_E);

	outTree->Branch("wpe_pt"  ,&wpe_pt);
	outTree->Branch("wpe_eta" ,&wpe_eta);
	outTree->Branch("wpe_phi" ,&wpe_phi);
	outTree->Branch("wpe_E" ,&wpe_E);
	outTree->Branch("wpmu_pt" ,&wpmu_pt);
	outTree->Branch("wpmu_eta",&wpmu_eta);
	outTree->Branch("wpmu_phi",&wpmu_phi);
	outTree->Branch("wpmu_E",&wpmu_E);
	outTree->Branch("wpta_pt" ,&wpta_pt);
	outTree->Branch("wpta_eta",&wpta_eta);
	outTree->Branch("wpta_phi",&wpta_phi);
	outTree->Branch("wpta_E",&wpta_E);
	
	outTree->Branch("wme_pt"  ,&wme_pt);
	outTree->Branch("wme_eta" ,&wme_eta);
	outTree->Branch("wme_phi" ,&wme_phi);
	outTree->Branch("wme_E" ,&wme_E);
	outTree->Branch("wmmu_pt" ,&wmmu_pt);
	outTree->Branch("wmmu_eta",&wmmu_eta);
	outTree->Branch("wmmu_phi",&wmmu_phi);
	outTree->Branch("wmmu_E",&wmmu_E);
	outTree->Branch("wmta_pt" ,&wmta_pt);
	outTree->Branch("wmta_eta",&wmta_eta);
	outTree->Branch("wmta_phi",&wmta_phi);
	outTree->Branch("wmta_E",&wmta_E);

	outTree->Branch("wpenu_pt"  ,&wpenu_pt);
	outTree->Branch("wpenu_et"  ,&wpenu_et);
	outTree->Branch("wpenu_phi" ,&wpenu_phi);
	outTree->Branch("wpenu_E" ,&wpenu_E);
	outTree->Branch("wpmunu_pt" ,&wpmunu_pt);
	outTree->Branch("wpmunu_et" ,&wpmunu_et);
	outTree->Branch("wpmunu_phi",&wpmunu_phi);
	outTree->Branch("wpmunu_E",&wpmunu_E);
	outTree->Branch("wptanu_pt" ,&wptanu_pt);
	outTree->Branch("wptanu_et" ,&wptanu_et);
	outTree->Branch("wptanu_phi",&wptanu_phi);
	outTree->Branch("wptanu_E",&wptanu_E);
	
	outTree->Branch("wmenu_pt"  ,&wmenu_pt);
	outTree->Branch("wmenu_et"  ,&wmenu_et);
	outTree->Branch("wmenu_phi" ,&wmenu_phi);
	outTree->Branch("wmenu_E" ,&wmenu_E);
	outTree->Branch("wmmunu_pt" ,&wmmunu_pt);
	outTree->Branch("wmmunu_et" ,&wmmunu_et);
	outTree->Branch("wmmunu_phi",&wmmunu_phi);
	outTree->Branch("wmmunu_E",&wmmunu_E);
	outTree->Branch("wmtanu_pt" ,&wmtanu_pt);
	outTree->Branch("wmtanu_et" ,&wmtanu_et);
	outTree->Branch("wmtanu_phi",&wmtanu_phi);
	outTree->Branch("wmtanu_E",&wmtanu_E);

	outTree->Branch("pho_pt",&pho_pt);
	outTree->Branch("pho_eta",&pho_eta);
	outTree->Branch("pho_phi",&pho_phi);
	outTree->Branch("pho_E",&pho_E);

}



GenInfo::~GenInfo()
{
 
	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event------------
void
GenInfo::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) // -- START EVENT LOOP
{
	using namespace edm;
	using namespace std;	

	Handle<GenParticleCollection> genParticles;
	iEvent.getByLabel("genParticles", genParticles);
	

	v_Ze1_pt.clear();
	v_Ze1_eta.clear();
	v_Ze1_phi.clear();
	v_Ze1_E.clear();
	v_Ze2_pt.clear();
	v_Ze2_eta.clear();
	v_Ze2_phi.clear();
	v_Ze2_E.clear();
	
	v_Zmu1_pt.clear();
	v_Zmu1_eta.clear();
	v_Zmu1_phi.clear();
	v_Zmu1_E.clear();
	v_Zmu2_pt.clear();
	v_Zmu2_eta.clear();
	v_Zmu2_phi.clear();
	v_Zmu2_E.clear();

	v_Zta1_pt.clear();
	v_Zta1_eta.clear();
	v_Zta1_phi.clear();
	v_Zta1_E.clear();
	v_Zta2_pt.clear();
	v_Zta2_eta.clear();
	v_Zta2_phi.clear();
	v_Zta2_E.clear();

	v_Wpe_pt.clear();
	v_Wpe_eta.clear();
	v_Wpe_phi.clear();
	v_Wpe_E.clear();
	v_Wpmu_pt.clear();
	v_Wpmu_eta.clear();
	v_Wpmu_phi.clear();
	v_Wpmu_E.clear();
	v_Wpta_pt.clear();
	v_Wpta_eta.clear();
	v_Wpta_phi.clear();
	v_Wpta_E.clear();
	v_Wpenu_pt.clear();
	v_Wpenu_et.clear();
	v_Wpenu_phi.clear();
	v_Wpenu_E.clear();
	v_Wpmunu_pt.clear();
	v_Wpmunu_et.clear();
	v_Wpmunu_phi.clear();
	v_Wpmunu_E.clear();
	v_Wptanu_pt.clear();
	v_Wptanu_et.clear();
	v_Wptanu_phi.clear();
	v_Wptanu_E.clear();


	v_Wme_pt.clear();
	v_Wme_eta.clear();
	v_Wme_phi.clear();
	v_Wme_E.clear();
	v_Wmmu_pt.clear();
	v_Wmmu_eta.clear();
	v_Wmmu_phi.clear();
	v_Wmmu_E.clear();
	v_Wmta_pt.clear();	
	v_Wmta_eta.clear();
	v_Wmta_phi.clear();
	v_Wmta_E.clear();
	v_Wmenu_pt.clear();
	v_Wmenu_et.clear();
	v_Wmenu_phi.clear();
	v_Wmenu_E.clear();
	v_Wmmunu_pt.clear();
	v_Wmmunu_et.clear();
	v_Wmmunu_phi.clear();
	v_Wmmunu_E.clear();
	v_Wmtanu_pt.clear();
	v_Wmtanu_et.clear();
	v_Wmtanu_phi.clear();
	v_Wmtanu_E.clear();

	v_Pho_pt.clear();
	v_Pho_eta.clear();
	v_Pho_phi.clear();
	v_Pho_E.clear();


//		cout << "PID" << " , " <<"Status" << " , " << "N of Daughter" << " , " << "pt" << " , " << "eta" << " , " << "phi" << " , " << "charge" << endl;
	 
	for(size_t i = 0; i < genParticles->size(); ++ i) { // -- START PARTICLE LOOP
		const GenParticle & p = (*genParticles)[i];
		int id = p.pdgId();
		int st = p.status();
		const Candidate * mom = p.mother();
		double pt = p.pt(), eta = p.eta(), phi = p.phi(), mass = p.mass();
		double vx = p.vx(), vy = p.vy(), vz = p.vz();
		int charge = p.charge();
		size_t n = p.numberOfDaughters();
	

		// -- Find Prompt Z boson 
		if ( id == 23 && n==2 && st == 62 ){

			Znum++;
			

			// --Loop of Daughter processes
			for(size_t j = 0; j < n; ++ j) { 
				const Candidate * d = p.daughter( j );
				int dauId = d->pdgId();
				int daucharge = d->charge();
				double daupt  = d->pt() ;
				double daueta = d->eta();
				double dauphi = d->phi();
				double dauE = d->energy();


				// Electrons
				if ( dauId == 11 ){
					Ze1++;
					v_Ze1_pt.push_back(daupt)  ;
					v_Ze1_eta.push_back(daueta);
					v_Ze1_phi.push_back(dauphi);
					v_Ze1_E.push_back(dauE);

				}else if ( dauId == -11 ){
					Ze2++;
					v_Ze2_pt.push_back(daupt)  ;
					v_Ze2_eta.push_back(daueta);
					v_Ze2_phi.push_back(dauphi);
					v_Ze2_E.push_back(dauE);
				}
	
				// Muons
				if ( dauId == 13 ){
					Zmu1++;	
					v_Zmu1_pt.push_back(daupt)  ;
					v_Zmu1_eta.push_back(daueta);
					v_Zmu1_phi.push_back(dauphi);
					v_Zmu1_E.push_back(dauE);

				}else if ( dauId == -13 ){
					Zmu2++;
					v_Zmu2_pt.push_back(daupt)    ;
					v_Zmu2_eta.push_back(daueta)  ;
					v_Zmu2_phi.push_back(dauphi)  ;
					v_Zmu2_E.push_back(dauE)  ;
				}

				// Taus
				if ( dauId == 15 ){
					Zta1++;
					v_Zta1_pt.push_back(daupt)  ;
					v_Zta1_eta.push_back(daueta);
					v_Zta1_phi.push_back(dauphi);
					v_Zta1_E.push_back(dauE);

				}else if ( dauId == -15 ){
					Zta2++;
					v_Zta2_pt.push_back(daupt)  ;
					v_Zta2_eta.push_back(daueta);
					v_Zta2_phi.push_back(dauphi);
					v_Zta2_E.push_back(dauE);
				}

			}
	 
		}




		// -- Find Prompt W- boson 
		if ( id == -24 && n == 2 && st == 62){

			// --Loop of Daughter processes
			for(size_t j = 0; j < n; ++ j) { 
				const Candidate * d = p.daughter( j );
				int dauId = d->pdgId();
				int daucharge = d->charge();
				double daupt  = d->pt() ;
				double daueta = d->eta();
				double dauet  = d->et();
				double dauphi = d->phi();
				double dauE = d->energy();

				// Electrons
				if ( dauId == 11 ){
					Wme++;
					v_Wme_pt.push_back(daupt)  ;
					v_Wme_eta.push_back(daueta);
					v_Wme_phi.push_back(dauphi);
					v_Wme_E.push_back(dauE);

				}else if ( dauId == -12 ){
					Wmenu++;
					v_Wmenu_pt.push_back(daupt)  ;
					v_Wmenu_et.push_back(dauet);
					v_Wmenu_phi.push_back(dauphi);
					v_Wmenu_E.push_back(dauE);
				}
	
				// Muons
				if ( dauId == 13 ){
					Wmmu++;
					v_Wmmu_pt.push_back(daupt)  ;
					v_Wmmu_eta.push_back(daueta);
					v_Wmmu_phi.push_back(dauphi);
					v_Wmmu_E.push_back(dauE);

				}else if ( dauId == -14 ){
					Wmmunu++;
					v_Wmmunu_pt.push_back(daupt)    ;
					v_Wmmunu_et.push_back(dauet)  ;
					v_Wmmunu_phi.push_back(dauphi)  ;
					v_Wmmunu_E.push_back(dauE)  ;
				}

				// Taus
				if ( dauId == 15 ){
					Wmta++;
					v_Wmta_pt.push_back(daupt)  ;
					v_Wmta_eta.push_back(daueta);
					v_Wmta_phi.push_back(dauphi);
					v_Wmta_E.push_back(dauE);

				}else if ( dauId == -16 ){
					Wmtanu++;
					v_Wmtanu_pt.push_back(daupt)  ;
					v_Wmtanu_et.push_back(dauet);
					v_Wmtanu_phi.push_back(dauphi);
					v_Wmtanu_E.push_back(dauE);
		       }
			}
		}


		// -- Find Prompt W+ boson 
		if ( id == 24 && n == 2 && st == 62){

			

			// --Loop of Daughter processes
			for(size_t j = 0; j < n; ++ j) { 
				const Candidate * d = p.daughter( j );
				int dauId = d->pdgId();
				int daucharge = d->charge();
				double daupt  = d->pt() ;
				double daueta = d->eta();
				double dauet  = d->et();
				double dauphi = d->phi();
				double dauE = d->energy();

				// Electrons
				if ( dauId == -11 ){
					Wpe++;
					v_Wpe_pt.push_back(daupt)  ;
					v_Wpe_eta.push_back(daueta);
					v_Wpe_phi.push_back(dauphi);
					v_Wpe_E.push_back(dauE);

				}else if ( dauId == 12 ){
					Wpenu++;
					v_Wpenu_pt.push_back(daupt)  ;
					v_Wpenu_et.push_back(dauet);
					v_Wpenu_phi.push_back(dauphi);
					v_Wpenu_E.push_back(dauE);
				}
	
				// Muons
				if ( dauId == -13 ){
					Wpmu++;
					v_Wpmu_pt.push_back(daupt)  ;
					v_Wpmu_eta.push_back(daueta);
					v_Wpmu_phi.push_back(dauphi);
					v_Wpmu_E.push_back(dauE);

				}else if ( dauId == 14 ){
					Wpmunu++;
					v_Wpmunu_pt.push_back(daupt)    ;
					v_Wpmunu_et.push_back(dauet)  ;
					v_Wpmunu_phi.push_back(dauphi)  ;
					v_Wpmunu_E.push_back(dauE)  ;
				}

				// Taus
				if ( dauId == -15 ){
					Wpta++;
					v_Wpta_pt.push_back(daupt)  ;
					v_Wpta_eta.push_back(daueta);
					v_Wpta_phi.push_back(dauphi);
					v_Wpta_E.push_back(dauE);

				}else if ( dauId == 16 ){
					Wptanu++;
					v_Wptanu_pt.push_back(daupt)  ;
					v_Wptanu_et.push_back(dauet);
					v_Wptanu_phi.push_back(dauphi);
					v_Wptanu_E.push_back(dauE);
		       }
			}
		}


		// -- Find Prompt Photon
		if ( id == 22 && st == 23){
			
			Pho++;
			// --Loop of Daughter processes
			for(size_t j = 0; j < n; ++ j) { 
				const Candidate * d = p.daughter( j );
				int dauId = d->pdgId();
				int daucharge = d->charge();
				double daupt  = d->pt() ;
				double daueta = d->eta();
				double dauet  = d->et();
				double dauphi = d->phi();
				double dauE   = d->energy();

			v_Pho_pt.push_back(daupt);
			v_Pho_eta.push_back(daueta);
			v_Pho_phi.push_back(dauphi);
			v_Pho_E.push_back(dauE);
			}
		}

	}// -- END Particle LOOP


	// --Fill branches

		//  Z e+e-
		if( v_Ze1_pt.size() !=0 && v_Ze2_pt.size() !=0 ){
			ze1_pt  = v_Ze1_pt[0];
			ze1_eta = v_Ze1_eta[0];
			ze1_phi = v_Ze1_phi[0];
			ze1_E = v_Ze1_E[0];
			ze2_pt  = v_Ze2_pt[0];
			ze2_eta = v_Ze2_eta[0];
			ze2_phi = v_Ze2_phi[0];
			ze2_E = v_Ze2_E[0];
		}
		//  Z mu+mu-
		if( v_Zmu1_pt.size() !=0 && v_Zmu2_pt.size() !=0 ){
			zmu1_pt  = v_Zmu1_pt[0];
			zmu1_eta = v_Zmu1_eta[0];
			zmu1_phi = v_Zmu1_phi[0];
			zmu1_E = v_Zmu1_E[0];
			zmu2_pt  = v_Zmu2_pt[0];
			zmu2_eta = v_Zmu2_eta[0];
			zmu2_phi = v_Zmu2_phi[0];
			zmu2_E = v_Zmu2_E[0];
		}
		//  Z ta+ta-
		if( v_Zta1_pt.size() !=0 && v_Zta2_pt.size() !=0 ){
			zta1_pt  = v_Zta1_pt[0];
			zta1_eta = v_Zta1_eta[0];
			zta1_phi = v_Zta1_phi[0];
			zta1_E = v_Zta1_E[0];
			zta2_pt  = v_Zta2_pt[0];
			zta2_eta = v_Zta2_eta[0];
			zta2_phi = v_Zta2_phi[0];
			zta2_E = v_Zta2_E[0];
		}

		// W- e-ve~
		if( v_Wme_pt.size() !=0 && v_Wmenu_pt.size() !=0 ){
			wme_pt   = v_Wme_pt[0];
			wme_eta  = v_Wme_eta[0];
			wme_phi  = v_Wme_phi[0];
			wme_E  = v_Wme_E[0];
			wmenu_pt = v_Wmenu_pt[0];
			wmenu_et = v_Wmenu_et[0];
			wmenu_phi= v_Wmenu_phi[0];
			wmenu_E= v_Wmenu_E[0];
		}
		// W- mu-vmu~
		if( v_Wmmu_pt.size() !=0 && v_Wmmunu_pt.size() !=0 ){
			wmmu_pt   = v_Wmmu_pt[0];
			wmmu_eta  = v_Wmmu_eta[0];
			wmmu_phi  = v_Wmmu_phi[0];
			wmmu_E  = v_Wmmu_E[0];
			wmmunu_pt = v_Wmmunu_pt[0];
			wmmunu_et = v_Wmmunu_et[0];
			wmmunu_phi= v_Wmmunu_phi[0];
			wmmunu_E= v_Wmmunu_E[0];
		}
		// W- ta-vta~
		if( v_Wmta_pt.size() !=0 && v_Wmtanu_pt.size() !=0 ){
			wmta_pt   = v_Wmta_pt[0];
			wmta_eta  = v_Wmta_eta[0];
			wmta_phi  = v_Wmta_phi[0];
			wmta_E  = v_Wmta_E[0];
			wmtanu_pt = v_Wmtanu_pt[0];
			wmtanu_et = v_Wmtanu_et[0];
			wmtanu_phi= v_Wmtanu_phi[0];
			wmtanu_E= v_Wmtanu_E[0];
		}
		// W+ e+ve
		if( v_Wpe_pt.size() !=0 && v_Wpenu_pt.size() !=0 ){
			wpe_pt   = v_Wpe_pt[0];
			wpe_eta  = v_Wpe_eta[0];
			wpe_phi  = v_Wpe_phi[0];
			wpe_E  = v_Wpe_E[0];
			wpenu_pt = v_Wpenu_pt[0];
			wpenu_et = v_Wpenu_et[0];
			wpenu_phi= v_Wpenu_phi[0];
			wpenu_E= v_Wpenu_E[0];
		}
		// W+ mu+ vmu
		if( v_Wpmu_pt.size() !=0 && v_Wpmunu_pt.size() !=0 ){
			wpmu_pt   = v_Wpmu_pt[0];
			wpmu_eta  = v_Wpmu_eta[0];
			wpmu_phi  = v_Wpmu_phi[0];
			wpmu_E  = v_Wpmu_E[0];
			wpmunu_pt = v_Wpmunu_pt[0];
			wpmunu_et = v_Wpmunu_et[0];
			wpmunu_phi= v_Wpmunu_phi[0];
			wpmunu_E= v_Wpmunu_E[0];
		}
		// W- ta+ vta
		if( v_Wpta_pt.size() !=0 && v_Wptanu_pt.size() !=0 ){
			wpta_pt   = v_Wpta_pt[0];
			wpta_eta  = v_Wpta_eta[0];
			wpta_phi  = v_Wpta_phi[0];
			wpta_E  = v_Wpta_E[0];
			wptanu_pt = v_Wptanu_pt[0];
			wptanu_et = v_Wptanu_et[0];
			wptanu_phi= v_Wptanu_phi[0];
			wptanu_E= v_Wptanu_E[0];
		}

		// Photon
		if( v_Pho_pt.size() > 0 ){
			pho_pt  = v_Pho_pt[0];
			pho_eta = v_Pho_eta[0];
			pho_phi = v_Pho_phi[0];
			pho_E = v_Pho_E[0];
		}
		
if ( v_Ze1_pt.size() !=0 || v_Ze2_pt.size() !=0 || v_Zmu1_pt.size() !=0 || v_Zmu2_pt.size() !=0 || v_Zta1_pt.size() !=0 || v_Zta2_pt.size() !=0 || v_Wme_pt.size() !=0 || v_Wmenu_pt.size() !=0 || v_Wmmu_pt.size() !=0 || v_Wmmunu_pt.size() !=0 || v_Wmta_pt.size() !=0 || v_Wmtanu_pt.size() !=0 || v_Wpe_pt.size() !=0 || v_Wpenu_pt.size() !=0 || v_Wpmu_pt.size() !=0 || v_Wpmunu_pt.size() !=0 || v_Wpta_pt.size() !=0 || v_Wptanu_pt.size() !=0 || v_Pho_pt.size() > 0 ){
	outTree->Fill();
cnt++; 
}

	cout << " ############ Z Boson summary ########" << endl;
	cout << "Number of Daughter(e) of  Z boson  " << " " << Ze1 << " " << Ze2 << endl;
	cout << "Number of Daughter(mu) of  Z boson  " << " " << Zmu1 << " " << Zmu2 << endl;
	cout << "Number of Daughter(ta) of  Z boson  " << " " << Zta1 << " " << Zta2 << endl;
	cout << "Number of Daughter sum of Z boson " << " " << Ze1+Zmu1+Zta1 << " " << Ze2+Zmu2+Zta2 << endl;
	cout << " ############ W Boson summary ########" << endl;
	cout << " ############ W- " << endl;
	cout << "Number of Daughter(e enu) of  W- boson  " << " " << Wme << " " << Wmenu << endl;
	cout << "Number of Daughter(mu munu) of  W- boson  " << " " << Wmmu << " " << Wmmunu << endl;
	cout << "Number of Daughter(ta tanu) of  W- boson  " << " " << Wmta << " " << Wmtanu << endl;
	cout << "Number of Daughter sum of  W- boson  " << " " << Wme+Wmmu+Wmta << " " << Wmenu+Wmmunu+Wmtanu << endl;
	cout << " ############ W+ " << endl;
	cout << "Number of Daughter(e enu) of  W+ boson  " << " " << Wpe << " " << Wpenu << endl;
	cout << "Number of Daughter(mu munu) of  W+ boson  " << " " << Wpmu << " " << Wpmunu << endl;
	cout << "Number of Daughter(ta tanu) of  W+ boson  " << " " << Wpta << " " << Wptanu << endl;
	cout << "Number of Daughter sum of  W+ boson  " << " " << Wpe+Wpmu+Wpta << " " << Wpenu+Wpmunu+Wptanu << endl;
	cout << "Number of Daughter sum of  W boson  " << " " << Wpe+Wpmu+Wpta+Wme+Wmmu+Wmta << " " << Wpenu+Wpmunu+Wptanu+Wmenu+Wmmunu+Wmtanu << endl;
	
	cout << "Number of Photon  " << " " <<  Pho << endl;
	cout << "EVT count: " << " " << cnt << endl;





	//cout << "Number of Prompt W boson: " << " " <<Wnum << " " << v_Wlep_pt.size() << " " << v_Wnu_pt.size() << endl;
	//cout << "Number of Daughter of  W boson: " << " " <<Wd1 << " " << Wd2 << endl;

#ifdef THIS_IS_AN_EVENT_EXAMPLE
	Handle<ExampleData> pIn;
	iEvent.getByLabel("example",pIn);
#endif
	
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
	ESHandle<SetupData> pSetup;
	iSetup.get<SetupRecord>().get(pSetup);
#endif
} // -- END Event LLOP


// ------------ method called once each job just before starting event loop------------
void 
GenInfo::beginJob()
{
}

// ------------ method called once each job just after ending the event loop------------
void 
GenInfo::endJob() 
{
}


// ------------ method fills 'descriptions' with the allowed parameters for the module------------
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
