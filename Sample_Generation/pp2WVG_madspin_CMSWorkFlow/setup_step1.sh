#!/bin/bash


export SCRAM_ARCH=slc6_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh

if [ -r CMSSW_10_2_6/src ] ; then
  echo release CMSSW_10_2_6 already exists
else
  scram p CMSSW CMSSW_10_2_6
fi
cd CMSSW_10_2_6/src
eval `scram runtime -sh`


## -------------------- First start this code as setup 
# Download fragment from McM
curl -s -k https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/SUS-RunIIFall18wmLHEGS-00028 --retry 3 --create-dirs -o Configuration/GenProduction/python/SUS-RunIIFall18wmLHEGS-00028-fragment.py
[ -s Configuration/GenProduction/python/SUS-RunIIFall18wmLHEGS-00028-fragment.py ] || exit $?;
scram b
cd ../..


## Number of Gen Events
EVENTS=5

# Random seed between 1 and 100 for externalLHEProducer
SEED=$(($(date +%s) % 100 + 1))

## --------------------Make Config file 
# cmsDriver command
cmsDriver.py Configuration/GenProduction/python/SUS-RunIIFall18wmLHEGS-00028-fragment.py --python_filename SUS-RunIIFall18wmLHEGS-00028_1_cfg.py --eventcontent RAWSIM,LHE --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM,LHE --fileout file:SUS-RunIIFall18wmLHEGS-00028.root --conditions 102X_upgrade2018_realistic_v11 --beamspot Realistic25ns13TeVEarly2018Collision --customise_commands process.RandomNumberGeneratorService.externalLHEProducer.initialSeed="int(${SEED})" --step LHE,GEN,SIM --geometry DB:Extended --era Run2_2018 --no_exec --mc -n $EVENTS || exit $? ;
