#include <memory>

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "vector"
#include "TTree.h"
#include "TH1F.h"
#include "TLorentzVector.h"

using reco::GenParticleCollection;
using reco::GenParticle;
using reco::Candidate;

inline bool isPDGlepton(int pdgId) {
   int pdgIdA = abs(pdgId);
   if((pdgIdA >= 11) && (pdgIdA <= 16)) return true;
   return false;
}


class GenInfo : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
public:
   explicit GenInfo(const edm::ParameterSet&);
   ~GenInfo();

   static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   size_t GetGenParticleIndex(edm::Handle<GenParticleCollection> genParticles, int _pdgId, int _status, double _pt, double _mass, size_t firstIdx);
   void GetDaughters(edm::Handle<GenParticleCollection> genParticles, size_t mIdx, std::vector<size_t>& dauIndexes);


private:
   virtual void beginJob() override;
   virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
   virtual void endJob() override;

	edm::EDGetTokenT<reco::GenParticleCollection> genToken_;//--used to access GenParticleCollection

   TH1F* h1_typeLL;
   TH1F* h1_typeLN;
   TH1F* h1_typeP ;

   TH1F* h1_phoPt;
   TH1F* h1_phoPt_HAD;
   TH1F* h1_phoPt_FSR;

   TH1F* h1_nDauZ ;
   TH1F* h1_nDauW ;

	TH1F* h1_mZDau   ; 
	TH1F* h1_mZDauLL ; 

	TH1F* h1_mWDau   ; 
	TH1F* h1_mWDauLL ; 

}; // CLASS END


// CONSTRUCTOR
GenInfo::GenInfo(const edm::ParameterSet& iConfig) {
	genToken_ = consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("GenParticles")); //-- GenParticle

   edm::Service<TFileService> fs;
   h1_typeLL = fs->make<TH1F>("h1_typeLL","h1_typeLL", 10, 0, 10);
   h1_typeLN = fs->make<TH1F>("h1_typeLN","h1_typeLN", 10, 0, 10);
   h1_typeP  = fs->make<TH1F>("h1_typeP" ,"h1_typeP" , 10, 0, 10);

   h1_phoPt = fs->make<TH1F>("h1_phoPt","h1_phoPt",1000,0,1000);
   h1_phoPt_HAD = fs->make<TH1F>("h1_phoPt_HAD","h1_phoPt_HAD",1000,0,1000);
   h1_phoPt_FSR = fs->make<TH1F>("h1_phoPt_FSR","h1_phoPt_FSR",1000,0,1000);

   h1_nDauZ = fs->make<TH1F>("h1_nDauZ","h1_nDauZ",10,0,10);
   h1_nDauW = fs->make<TH1F>("h1_nDauW","h1_nDauW",10,0,10);
	
	h1_mZDau   = fs->make<TH1F>("h1_mZDau"  ,"h1_mZDau"  ,200,0,200);
	h1_mZDauLL = fs->make<TH1F>("h1_mZDauLL","h1_mZDauLL",200,0,200);

	h1_mWDau   = fs->make<TH1F>("h1_mWDau"  ,"h1_mWDau"  ,200,0,200);
	h1_mWDauLL = fs->make<TH1F>("h1_mWDauLL","h1_mWDauLL",200,0,200);

} // CONSTRUCTOR END

GenInfo::~GenInfo() {}


// MEHTOD: Find Index of Particle
size_t GenInfo::GetGenParticleIndex(edm::Handle<GenParticleCollection> genParticles, int _pdgId, int _status, double _pt, double _mass, size_t firstIdx = 0) {
   firstIdx++;
   for(size_t i = firstIdx; i < genParticles->size(); ++ i) {
      const GenParticle & p = (*genParticles)[i];
      int id = p.pdgId();
      int st = p.status();
      double pt = p.pt();
      double mass = p.mass();
      if(_pdgId == id && _status == st && _pt == pt && _mass == mass) return i;
   }
   std::cout << "### Error NotFound GenParticle Index " << _pdgId << " " << _status << " " << _pt << " " << _mass << std::endl;
   return 0;
}

// METHOD: Loop over Daughter particle recursively
// Append final state particle on "dauIndexes"  vector
void GenInfo::GetDaughters(edm::Handle<GenParticleCollection> genParticles, size_t mIdx, std::vector<size_t>& dauIndexes) {
   
	const GenParticle & motherP = (*genParticles)[mIdx];
   if(motherP.numberOfDaughters() == 0) {
    
	  return;
   } else if(motherP.numberOfDaughters() == 1) {
      const Candidate * d = motherP.daughter(0);
      size_t idxD = GetGenParticleIndex(genParticles, (int)d->pdgId(), (int)d->status(), (double)d->pt(), (double)d->mass(), mIdx);
      GetDaughters(genParticles, idxD, dauIndexes);
      return;
   } else {
      for(size_t j=0; j<motherP.numberOfDaughters() ; j++) {
         const Candidate * d = motherP.daughter(j);
         if(isPDGlepton(d->pdgId()) or (d->pdgId() == 22)) {
            size_t idxD = GetGenParticleIndex(genParticles, (int)d->pdgId(), (int)d->status(), (double)d->pt(), (double)d->mass(), mIdx);
            dauIndexes.push_back(idxD);
         } else {
            size_t idxD = GetGenParticleIndex(genParticles, (int)d->pdgId(), (int)d->status(), (double)d->pt(), (double)d->mass(), mIdx);
            GetDaughters(genParticles, idxD, dauIndexes);
         }
      }
      return;
   }
   std::cout << "Something Wrong in GenInfo::GetDaughters() !!!!" << std::endl;
}


// Event Loop Start
void GenInfo::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
   using namespace edm;
	using std::cout;
	using std::endl;

   edm::Handle<GenParticleCollection> genParticles;
   iEvent.getByLabel("genParticles", genParticles);

   bool findZ = false;
   bool findW = false;
   bool findP = false;
   bool findLL = false;
   int numHardLep = 0;
   int numHardZLep = 0;
   int numHardNeu = 0;

   int typeLL = 0;
   int typeLN = 0;
   int typeP  = 0;

   size_t idxZ = 0;
   size_t idxW = 0;
   size_t idxP = 0;

   const GenParticle & pHard2 = (*genParticles)[2];
   const GenParticle & pHard3 = (*genParticles)[3];
   if(pHard2.numberOfDaughters() != pHard3.numberOfDaughters()) {
      cout << "Error DiffProduce from 2 and 3 " << pHard2.numberOfDaughters() << " " << pHard3.numberOfDaughters() << endl;
   }

	// --Loop over Hard2 Daughter paricles
	for(size_t j=0; j<pHard2.numberOfDaughters() ; j++) {
      const Candidate * d = pHard2.daughter(j);
      int dauId = d->pdgId();
      int dauAId = abs(d->pdgId());

		// -- Dau of Hard2 particle == Higgs or Z boson
      if((dauId == 23 or dauId == 25) and !findZ) {
         findZ = true;
         idxZ = GetGenParticleIndex(genParticles, (int)d->pdgId(), (int)d->status(), (double)d->pt(), (double)d->mass());
         typeLL = 1;
      }
		// -- W boosn
      if(abs(dauId) == 24 and !findW) {
         findW = true;
         idxW = GetGenParticleIndex(genParticles, (int)d->pdgId(), (int)d->status(), (double)d->pt(), (double)d->mass());
         typeLN = 1;
      }
		// -- Photon
      if(dauId == 22 and !findP) {
         findP = true;
         idxP = GetGenParticleIndex(genParticles, (int)d->pdgId(), (int)d->status(), (double)d->pt(), (double)d->mass());
         typeP = 1;
      }

		// -- Lepton or Neutrino  
      if(dauAId == 11 or dauAId == 13 or dauAId == 15) { numHardLep++; numHardZLep++; } 
      if(dauAId == 12 or dauAId == 14 or dauAId == 16) { numHardNeu++; numHardZLep--; }
   } // --END Hard2 Daughter particle Loop


	// typeLL:2 No recognized Z or H but final 2 leps
   if(!findZ && numHardZLep == 2) {
      findLL = true;
      typeLL = 2;
   }

	// typeLN:2 No recognized W but final 1 vl & 1 or 3 lep
   if(!findW && numHardNeu == 1 and (numHardLep == 1 or numHardLep==3)) {
      typeLN = 2;
   }

   // Intermediate W -- decya to W Z and un-recognized vectorbosons decay to leptonically 
   if(!findZ && !findLL) {
      if(idxW != 0) { // yes W boson
         std::vector<size_t> wDauIndexes;
         GetDaughters(genParticles, idxW, wDauIndexes);
         int numWLep = 0;
         int numWNeu = 0;
			// Loop over Final state daughters of W boson Idx
         for(std::vector<size_t>::iterator it=wDauIndexes.begin(); it!=wDauIndexes.end(); it++) {
            const GenParticle & pDau = (*genParticles)[*it];
            int dauAId = abs(pDau.pdgId());
            if(dauAId == 11 or dauAId == 13 or dauAId == 15) numWLep++;
            if(dauAId == 12 or dauAId == 14 or dauAId == 16) numWNeu++;
         }
         if(numWNeu == 1 && numWLep > 2) { // Whynot numWlep ==2  ?
            typeLL = 3;
            typeLN = 3;
         }
      }
   }

	// DaughterIndexes from Z and W 
   std::vector<size_t> zDauIndexes;
   std::vector<size_t> wDauIndexes;
   if(typeLL == 1) GetDaughters(genParticles, idxZ, zDauIndexes);
   if(typeLN == 1 or typeLN == 3) GetDaughters(genParticles, idxW, wDauIndexes);
   int numPhotonFromZ = 0;
   int numPhotonFromW = 0;
   size_t fsrMaxPIdx = 0;
   double fsrMaxPPt = 0.0;
   int fsrMaxPType = -1;

    //  Z(orH) daughter Loop STARt
   for(std::vector<size_t>::iterator it=zDauIndexes.begin(); it!=zDauIndexes.end(); it++) {
      const GenParticle& p = (*genParticles)[*it];
		
		// Photon from Z(orH)
	  if(p.pdgId() == 22) {
         numPhotonFromZ++;
         if(p.pt() > fsrMaxPPt) {
            fsrMaxPIdx = *it;
            fsrMaxPPt = p.pt();
            fsrMaxPType = 1;
         }
      }
   } // Z(orH) daughter Loop END

	// W Daughter Loop START
   for(std::vector<size_t>::iterator it=wDauIndexes.begin(); it!=wDauIndexes.end(); it++) {
      const GenParticle& p = (*genParticles)[*it];
    
		// PHoton from W 
	 if(p.pdgId() == 22) {
         numPhotonFromW++;
         if(p.pt() > fsrMaxPPt) {
            fsrMaxPIdx = *it;
            fsrMaxPPt = p.pt();
            fsrMaxPType = 2;
         }
      }
   } // W Daughter Loop END

   if(!findP && fsrMaxPType == 1) typeP = 2;  // Not Hardprocess photon, FSR photon from Z ...
   if(!findP && fsrMaxPType == 2) typeP = 3;  // Not Hardprocess photon, FSR photon from W ... 


// ------------Fill histogram

   // Fill particle type
   h1_typeLL->Fill(typeLL);
   h1_typeLN->Fill(typeLN);
   h1_typeP ->Fill(typeP );

   // Photon index FSR or Hardprocess
   if(idxP == 0) idxP = fsrMaxPIdx;  
   if(idxP == 0) { std::cout << "### Error Final Idx for Photon is NULL " << "Type LN " << typeLN << std::endl; return; } // No photon
   const GenParticle& phoGen = (*genParticles)[idxP];
   

	// Fill Photon
	h1_phoPt->Fill(phoGen.pt()); // All photon PT
	if(typeP == 1) h1_phoPt_HAD->Fill(phoGen.pt()); // Hard photon
	if(typeP == 2 or typeP == 3) h1_phoPt_FSR->Fill(phoGen.pt()); // FSR photon

	// Fill Z boson
	if(typeLL == 1) {
		h1_nDauZ->Fill(zDauIndexes.size()); // N of Daughter from ....
		TLorentzVector zDauVec;
		TLorentzVector zDauLLVec;

	   // Z Daughter Loop
	   for(std::vector<size_t>::iterator it=zDauIndexes.begin(); it!=zDauIndexes.end(); it++) {
		    const GenParticle& p = (*genParticles)[*it];
			TLorentzVector dVec; dVec.SetPtEtaPhiE(p.pt(), p.eta(), p.phi(), p.energy());

			// Di lepton
		    if(isPDGlepton(p.pdgId())) {
				zDauLLVec += dVec;
				zDauVec += dVec;
			} else {  // Di lepton + Photon
				zDauVec += dVec;
			}
   	  }
		h1_mZDau->Fill(zDauVec.M());  // ll
		h1_mZDauLL->Fill(zDauLLVec.M()); // lla
	}


	// Fill W boson
	if(typeLN == 1 or typeLN == 3) {
		h1_nDauW->Fill(wDauIndexes.size());
		TLorentzVector wDauVec;
		TLorentzVector wDauLLVec;
	   for(std::vector<size_t>::iterator it=wDauIndexes.begin(); it!=wDauIndexes.end(); it++) {
   	   const GenParticle& p = (*genParticles)[*it];
			TLorentzVector dVec; dVec.SetPtEtaPhiE(p.pt(), p.eta(), p.phi(), p.energy());
   	   if(isPDGlepton(p.pdgId())) {
				wDauLLVec += dVec;
				wDauVec += dVec;
			} else {
				wDauVec += dVec;
			}
   	}
		h1_mWDau->Fill(wDauVec.M());
		h1_mWDauLL->Fill(wDauLLVec.M());
	}




   return;




	



#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


void GenInfo::beginJob() {}
void GenInfo::endJob() {}
void GenInfo::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
DEFINE_FWK_MODULE(GenInfo);
