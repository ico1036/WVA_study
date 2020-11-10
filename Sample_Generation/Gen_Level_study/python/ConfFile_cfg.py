import FWCore.ParameterSet.Config as cms
#import glob


maxevent=-1

process = cms.Process("GenInfo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevent) )
process.MessageLogger.cerr.FwkReport.reportEvery =50  ## --How often you're updated on the progress


'''
input_file = glob.glob('../../../../CMSSW_WorkFlow/Scheme1_Large/condorOut/s1_LNuLLA_3775483_*.root')
input_files=[]
for i in input_file:
	j = 'file:' + i
	input_files.append(j)
print(input_files)
'''


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:../../../../CMSSW_WorkFlow/Scheme1_Large/condorOut/s1_LNuLLA_3775483_0.root'
#		 input_files
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
  maxEventsToPrint = cms.untracked.int32(maxevent),
  printVertex = cms.untracked.bool(False),
  printOnlyHardInteraction = cms.untracked.bool(False), # Print only status=3 particles. This will not work for Pythia8, which does not have any such particles.
  src = cms.InputTag("genParticles")
)




process.TFileService = cms.Service("TFileService",
    fileName = cms.string("test_gen_tree.root")
)

process.GenInfo = cms.EDAnalyzer('GenInfo',

    GenParticles = cms.InputTag("genParticles"),
)


process.p = cms.Path(process.GenInfo
#*process.printTree
)

