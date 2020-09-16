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




};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

// --constructors and destructor

GenInfo::GenInfo(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed
	genToken_ = consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("GenParticles")); //-- GenParticle
	//genToken_(consumes<edm::View<reco::GenParticleCollection> >(iConfig.getParameter<edm::InputTag>("genParticles"))) //-- GenParticle

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

	Handle<GenParticleCollection> genParticles;
	iEvent.getByLabel("genParticles", genParticles);
    for(size_t i = 0; i < genParticles->size(); ++ i) {
        const GenParticle & p = (*genParticles)[i];
        int id = p.pdgId();
        int st = p.status();
        const Candidate * mom = p.mother();
        double pt = p.pt(), eta = p.eta(), phi = p.phi(), mass = p.mass();
        double vx = p.vx(), vy = p.vy(), vz = p.vz();
        int charge = p.charge();
        size_t n = p.numberOfDaughters();
        
		std::cout << id << std::endl; // -- Check output 

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
