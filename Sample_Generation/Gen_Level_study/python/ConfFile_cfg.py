import FWCore.ParameterSet.Config as cms
import glob

maxevent=-1

process = cms.Process("GenInfo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(maxevent) )
process.MessageLogger.cerr.FwkReport.reportEvery =50  ## --How often you're updated on the progress


# ---- Grep file path ----------------------------#

# Scheme 1
infiles = glob.glob("/home/jwkim/SL6_WZG_study/CMSSW_WorkFlow/Scheme1_Large/condorOut/s1*.root") ; outfile_name = "scheme1.root"

# Scheme 2
#infiles = glob.glob("/home/jwkim/SL6_WZG_study/CMSSW_WorkFlow/Scheme2_Large/condorOut/s1*.root") ; outfile_name = "scheme2.root"

# Scheme 3
#infiles = glob.glob("/home/jwkim/SL6_WZG_study/CMSSW_WorkFlow/Scheme3_Large/condorOut/s1*.root") ; outfile_name = "scheme3.root"

# Sheme 4
#infiles1 = glob.glob("/home/jwkim/SL6_WZG_study/CMSSW_WorkFlow/Scheme4_Wm_Large/condorOut/s1*.root") ; outfile_name = "scheme4.root"
#infiles2 = glob.glob("/home/jwkim/SL6_WZG_study/CMSSW_WorkFlow/Scheme4_Wp_Large/condorOut/s1*.root") 
#infiles = infiles1 + infiles2


file_list=[]
for f in infiles:

#->- For Scheme 3 --------------- There is empty file
#	if f == '/home/jwkim/SL6_WZG_study/CMSSW_WorkFlow/Scheme3_Large/condorOut/s1_LNuLLA_41_144.root':
#		continue;
#<---------------------------------

	file_list.append('file:' + f)


# ---------------------------------------------





print("Number of files: ",len(file_list))

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(file_list)
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
    fileName = cms.string(outfile_name)
)

process.GenInfo = cms.EDAnalyzer('GenInfo',

    GenParticles = cms.InputTag("genParticles"),
	Generator = cms.InputTag("generator")
)


process.p = cms.Path(process.GenInfo
#*process.printTree
)

