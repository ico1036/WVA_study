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
		int ZDau_num;

		TTree* outTree;
	
		std::vector<double> v_Zlep1_pt,v_Zlep1_eta,v_Zlep1_phi;
		std::vector<double> v_Zlep2_pt,v_Zlep2_eta,v_Zlep2_phi;
		
		double zlep1_pt,zlep1_eta,zlep1_phi;
		double zlep2_pt,zlep2_eta,zlep2_phi;
	


};


GenInfo::GenInfo(const edm::ParameterSet& iConfig)
	edm::Service<TFileService> fs;
	outTree = fs->make<TTree> ("outTree","outTree")
{

	//now do what ever initialization is needed
	genToken_ = consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("GenParticles")); //-- GenParticle
	
	Znum=0;
	ZDau_num=0;

	outTree->Branch("zlep1_pt" ,zlep1_pt&);
	outTree->Branch("zlep1_eta",zlep1_eta&);
	outTree->Branch("zlep1_phi",zlep1_phi&);
	outTree->Branch("zlep2_pt" ,zlep2_pt&);
	outTree->Branch("zlep2_eta",zlep2_eta&);
	outTree->Branch("zlep2_phi",zlep2_phi&);
	

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
		if ( id == 23 && n==2 ){

			Znum++;
			

			// --Loop of Daughter processes
			for(size_t j = 0; j < n; ++ j) { 
				const Candidate * d = p.daughter( j );
				int dauId = d->pdgId();
				int daucharge = d->charge();
				double daupt  = d->pt() ;
				double daueta = d->eta();
				double dauphi = d->phi();

				// --lep-
				if ( daucharge == -1 ){
					v_Zlep1_pt.push_back(daupt);
					v_Zlep1_eta.push_back(daueta);
					v_Zlep1_phi.push_back(dauphi);
							
				// --lep+
				}else{
					v_Zlep2_pt.push_back(daupt);
					v_Zlep2_eta.push_back(daueta);
					v_Zlep2_phi.push_back(dauphi);

				}

			}
	 
		}

	}// -- END Particle LOOP

	outTree->Fill();


	cout << "Number of Prompt Z boson: " << " " <<Znum << " " << v_Zlep1_pt.size() << " " << v_Zlep2_pt.size() << endl;

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

outTree->Write();

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
