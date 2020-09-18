import FWCore.ParameterSet.Config as cms

process = cms.Process("GenInfo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery =50  ## --How often you're updated on the progress


process.source = cms.Source("PoolSource",
	# replace 'myfile.root' with the source file you want to use
	fileNames = cms.untracked.vstring(
		'file:/x5/cms/jwkim/gitdir/WVG/Sample_Generation/GenSim/out_pp2lnlall_250evts_step1/SUS-RunIIFall18wmLHEGS-00028.root'
		#'file:/x5/cms/jwkim/gitdir/WVG/Sample_Generation/GenSim/out_pp2lnlaz_step1/SUS-RunIIFall18wmLHEGS-00028.root'
	)
)
	

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleTreeDrawer",
	src = cms.InputTag("genParticles"),                                                                 
	printP4 = cms.untracked.bool(False),
	printPtEtaPhi = cms.untracked.bool(False),
	printVertex = cms.untracked.bool(False),
	printStatus = cms.untracked.bool(False),
	printIndex = cms.untracked.bool(False),
	status = cms.untracked.vint32( 3 )
)


process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleListDrawer",
  maxEventsToPrint = cms.untracked.int32(1),
  printVertex = cms.untracked.bool(False),
  printOnlyHardInteraction = cms.untracked.bool(False), # Print only status=3 particles. This will not work for Pythia8, which does not have any such particles.
  src = cms.InputTag("genParticles")
)




## --> on Developing
process.TFileService = cms.Service("TFileService".
	fileName = cms.string("test_gen_tree.root")
)
## < --

process.GenInfo = cms.EDAnalyzer('GenInfo',

	GenParticles = cms.InputTag("genParticles"),
)


process.p = cms.Path(process.GenInfo
#*process.printTree
)
