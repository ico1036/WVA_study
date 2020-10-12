

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


//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

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

	edm::EDGetTokenT<reco::GenParticleCollection> genToken_;//--used to access GenParticleCollectio

       // --Counter List
        int Znum;
        int Wpnum;
        int Wp_ele_num;
        int Wp_nu_num;
        int Wmnum;
		int Nphoton;
        int cnt;
	

        int Nelectron;
        int Npositron;
        int Nmuplus;
        int Nmuminus;
        int Ntaplus;
        int Ntaminus;



        // --Tree definition
        TTree* ZTree;
        TTree* WpTree;
        TTree* WmTree;
        TTree* PhoTree;

        // --Vector List
        std::vector<double> v_ZMass;
        std::vector<double> v_WpMT;
        std::vector<double> v_WmMT;
        std::vector<double> v_PhoPT;


        // --Variables for making branches
        double ZMass;
        double WpMT;
        double WmMT;
		double PhoPT;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
GenInfo::GenInfo(const edm::ParameterSet& iConfig)
{

    edm::Service<TFileService> fs;
    ZTree = fs->make<TTree> ("ZTree","ZTree");
    WpTree = fs->make<TTree> ("WpTree","WpTree");
    WmTree = fs->make<TTree> ("WmTree","WmTree");
    PhoTree = fs->make<TTree> ("PhoTree","PhoTree");

    //now do what ever initialization is needed
    genToken_ = consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("GenParticles")); //-- GenParticle


    // -- Initialize counters
    Znum=0;
    cnt=0;
    Nelectron=0;
    Npositron=0;
    Nmuplus=0;
    Nmuminus=0;
    Ntaplus=0;
    Ntaminus=0;
    Wpnum=0;
    Wp_ele_num=0;
    Wp_nu_num=0;
    Wmnum=0;
	Nphoton=0;


    // -- Make branches

    ZTree->Branch("ZMass", &ZMass);
    WpTree->Branch("WpMT", &WpMT);
    WmTree->Branch("WmMT", &WmMT);
    PhoTree->Branch("PhoPT", &PhoPT);


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

	// --Initialize vectors
    v_ZMass.clear();
    v_WpMT.clear();
    v_WmMT.clear();
    v_PhoPT.clear();

	 //// -- Particle Loop start 
    for(size_t i = 0; i < genParticles->size(); ++ i) {
        const GenParticle & p = (*genParticles)[i];
        int id = p.pdgId();
        int st = p.status();
        const Candidate * mom = p.mother();
        double pt = p.pt(), eta = p.eta(), phi = p.phi(), mass = p.mass();
        double vx = p.vx(), vy = p.vy(), vz = p.vz();
        int charge = p.charge();
        size_t n = p.numberOfDaughters();

		// -- Find Prompt Z boson 
		//if ( id == 23 && st == 22 ){
		if ( id == 23  ){
			
			v_ZMass.push_back(mass);
			
			Znum++;
			break;
		} 

		//if ( id == 11 && ( st==1 || st==23 || st==51 )  && p.numberOfMothers() == 1 && ( mom->pdgId() == 23 || mom->pdgId() == 22 ) ){
		//if ( id == 11   && p.numberOfMothers() == 1 && (  mom->pdgId() == 22 ) ){
		if ( id == 11   && p.numberOfMothers() == 1 && (  mom->pdgId() == 22 ) ){
			Nelectron++;
		} 

		if ( id == -11 && p.numberOfMothers() == 1 && (  mom->pdgId() == 22 ) ){
			Npositron++;			
		}
		if ( id == 13   && p.numberOfMothers() == 1 && (  mom->pdgId() == 22 )){
			Nmuminus++;
		} 

		if ( id == -13 && p.numberOfMothers() == 1 && (  mom->pdgId() == 22 )){
			Nmuplus++;			
		}
		if ( id == 15   && p.numberOfMothers() == 1 && (  mom->pdgId() == 22 )){
			Ntaminus++;
		} 

		if ( id == -15 && p.numberOfMothers() == 1 && (  mom->pdgId() == 22 ) ){
			Ntaplus++;			
		}// End Z Boson


		/*
		// -- Find Prompt W+ boson 
        if ( id == 24  ){

            v_WpMT.push_back(p.mt());


            Wpnum++;
            break;
        }



        // -- Find Prompt W- boson 
        if ( id == -24  ){

            v_WmMT.push_back(p.mt());
            Wmnum++;



            break;
        }


			
		// -- Find Prompt Photon
		//if ( id == 22 && st == 23) {
		if ( id == 22) {

			v_PhoPT.push_back(pt);
			Nphoton++;
		
			break;
		}
		*/
			



    }//// -- Particle Loop End


	    // --Fill branches

        //  Step1 ...Z mass
        if( v_ZMass.size() != 0 ){
            ZMass  = v_ZMass[0];
            ZTree->Fill();

        }
        // Step2  W MT
        if( v_WpMT.size() != 0 ){
            WpMT  = v_WpMT[0];
            WpTree->Fill();
        }
        if( v_WmMT.size() != 0 ){
            WmMT  = v_WmMT[0];
            WmTree->Fill();
        }


		// Step3 Photon PT
		if( v_PhoPT.size() != 0 ){
			PhoPT = v_PhoPT[0];
			PhoTree->Fill();
		}



		cnt++;
	
//  cout << " ############ Z Boson summary ########" << endl;
    cout << "Number of Z boson  " << " " << Znum  << endl;
    cout << "Number of e-   " << " " << Nelectron << endl;
    cout << "Number of e+   " << " " << Npositron << endl;
    cout << "Number of mu-   " << " " << Nmuminus << endl;
    cout << "Number of mu+   " << " " << Nmuplus << endl;
    cout << "Number of ta-   " << " " << Ntaminus << endl;
    cout << "Number of ta+   " << " " << Ntaplus << endl;
    cout << " ############ W Boson summary ########" << endl;
    cout << "Number of W+ boson  " << " " << Wpnum << endl;
//  cout << "Number of e+  " << " " << Wp_ele_num << endl;
//  cout << "Number of nu  " << " " << Wp_nu_num << endl;
    cout << "Number of W- boson  " << " " << Wmnum << endl;
    cout << " ############ Photon summary ########" << endl;
    cout << "Number of Photon: " << " " << Nphoton << endl;
    cout << "Number of Event: " << " " << cnt << endl;







#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
} // END event Loop


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

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenInfo);
