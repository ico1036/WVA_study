import FWCore.ParameterSet.Config as cms

process = cms.Process("GenInfo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.MessageLogger.cerr.FwkReport.reportEvery =50  ## --How often you're updated on the progress


process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/x5/cms/jwkim/gitdir/WVG/Sample_Generation/GenSim/out_pp2lnlall_250evts_step1/SUS-RunIIFall18wmLHEGS-00028.root'
    )
)

process.GenInfo = cms.EDAnalyzer('GenInfo',

	GenParticles = cms.InputTag("genParticles"),
)


process.p = cms.Path(process.GenInfo)
