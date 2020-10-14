#!/bin/bash

cd /afs/cern.ch/cms/PPD/PdmV/work/McM/submit/SUS-RunIIAutumn18MiniAOD-00011/

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
# Time per event for each sequence: 0.6700s
# Threads for each sequence: 8
# Time per event for single thread for each sequence: 8 * 0.6700s = 5.3600s
# Which adds up to 5.3600s per event
# Single core events that fit in validation duration: 23040s / 5.3600s = 4298
# Produced events limit in McM is 10000
# According to 1.0000 efficiency, up to 10000 / 1.0000 = 10000 events should run
# Clamp (put value) 4298 within 1 and 10000 -> 4298
# It is estimated that this validation will produce: 4298 * 1.0000 = 4298 events
EVENTS=4298


# cmsDriver command
cmsDriver.py  --python_filename SUS-RunIIAutumn18MiniAOD-00011_1_cfg.py --eventcontent MINIAODSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier MINIAODSIM --fileout file:SUS-RunIIAutumn18MiniAOD-00011.root --conditions 102X_upgrade2018_realistic_v15 --step PAT --geometry DB:Extended --filein "dbs:/WZG_TuneCP5_13TeV-amcatnlo-pythia8/RunIIAutumn18DRPremix
