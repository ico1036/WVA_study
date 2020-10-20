#!/bin/bash


export SCRAM_ARCH=slc6_amd64_gcc700

source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ -r CMSSW_10_2_5/src ] ; then
  echo release CMSSW_10_2_5 already exists
else
  scram p CMSSW CMSSW_10_2_5
fi
cd CMSSW_10_2_5/src
eval `scram runtime -sh`

scram b
cd ../..


# Maximum validation duration: 28800s
# Margin for validation duration: 20%
# Validation duration with margin: 28800 * (1 - 0.20) = 23040s
# Time per event for each sequence: 0.1800s
# Threads for each sequence: 2
# Time per event for single thread for each sequence: 2 * 0.1800s = 0.3600s
# Which adds up to 0.3600s per event
# Single core events that fit in validation duration: 23040s / 0.3600s = 64000
# Produced events limit in McM is 10000
# According to 1.0000 efficiency, up to 10000 / 1.0000 = 10000 events should run
# Clamp (put value) 64000 within 1 and 10000 -> 10000
# It is estimated that this validation will produce: 10000 * 1.0000 = 10000 events
EVENTS=5


# cmsDriver command
cmsDriver.py  --python_filename SUS-RunIIAutumn18NanoAOD-00004_1_cfg.py --eventcontent NANOEDMAODSIM --customise Configuration/DataProcessing/Utils.addMonitoring --datatier NANOAODSIM --fileout file:SUS-RunIIAutumn18NanoAOD-00004.root --conditions 102X_upgrade2018_realistic_v15 --step NANO --filein file:SUS-RunIIAutumn18MiniAOD-00011.root --era Run2_2018 --no_exec --mc -n $EVENTS || exit $? ;
