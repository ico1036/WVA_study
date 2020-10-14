#!/bin/bash

cd /afs/cern.ch/cms/PPD/PdmV/work/McM/submit/SUS-RunIIAutumn18DRPremix-00011/

export SCRAM_ARCH=slc6_amd64_gcc700

source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ -r CMSSW_10_2_6/src ] ; then
  echo release CMSSW_10_2_6 already exists
else
  scram p CMSSW CMSSW_10_2_6
fi
cd CMSSW_10_2_6/src
eval `scram runtime -sh`

scram b
cd ../..

# PdmV proxy
export X509_USER_PROXY=/afs/cern.ch/user/p/pdmvserv/private/$HOSTNAME/voms_proxy.cert

# Maximum validation duration: 28800s
# Margin for validation duration: 20%
# Validation duration with margin: 28800 * (1 - 0.20) = 23040s
# Time per event for each sequence: 0.9940s, 1.1987s
# Threads for each sequence: 8, 8
# Time per event for single thread for each sequence: 8 * 0.9940s = 7.9520s, 8 * 1.1987s = 9.5896s
# Which adds up to 17.5416s per event
# Single core events that fit in validation duration: 23040s / 17.5416s = 1313
# Produced events limit in McM is 10000
# According to 1.0000 efficiency, up to 10000 / 1.0000 = 10000 events should run
# Clamp (put value) 1313 within 1 and 10000 -> 1313
# It is estimated that this validation will produce: 1313 * 1.0000 = 1313 events
EVENTS=1313


# cmsDriver command
cmsDriver.py  --python_filename SUS-RunIIAutumn18DRPremix-00011_1_cfg.py --eventcontent PREMIXRAW --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM-RAW --fileout file:SUS-RunIIAutumn18DRPremix-00011_0.root --pileup_input "dbs:/Neutrino_E-10_gun/RunIISummer17PrePremix-PUAutumn18_102X_upgrade2018_realistic_v15-v1/GEN-SIM-DIGI-RAW" --conditions 102X_upgrade2018_realistic_v15 --step DIGI,DATAMIX,L1,DIGI2RAW,HLT:@relval2018 --procModifiers premix_stage2 --geometry DB:Extended --filein "dbs:/WZG_TuneCP5_13TeV-amcatnlo-pythia8/RunIIFall18wmLHEGS-102X_upgrade2018_realistic_v11-v1/GEN-SIM" --datamix PreMix --era Run2_2018 --no_exec --mc -n $EVENTS || exit $? ;

# cmsDriver command
cmsDriver.py  --python_filename SUS-RunIIAutumn18DRPremix-00011_2_cfg.py --eventcontent AODSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier AODSIM --fileout file:SUS-RunIIAutumn18DRPremix-00011.root --conditions 102X_upgrade2018_realistic_v15 --step RAW2DIGI,L1Reco,RECO,RECOSIM,EI --procModifiers premix_stage2 --filein file:SUS-RunIIAutumn18DRPremix-00011_0.root --era Run2_2018 --runUnscheduled --no_exec --mc -n $EVENTS || exit $? ;
