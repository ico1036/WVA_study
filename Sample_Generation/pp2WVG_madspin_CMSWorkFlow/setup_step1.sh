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

# Download fragment from McM
#curl -s -k https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/SUS-RunIIFall18wmLHEGS-00028 --retry 3 --create-dirs -o Configuration/GenProduction/python/SUS-RunIIFall18wmLHEGS-00028-fragment.py
#[ -s Configuration/GenProduction/python/SUS-RunIIFall18wmLHEGS-00028-fragment.py ] || exit $?;
#scram b
#cd ../..

# PdmV proxy
export X509_USER_PROXY=/afs/cern.ch/user/p/pdmvserv/private/$HOSTNAME/voms_proxy.cert

# Maximum validation duration: 28800s
# Margin for validation duration: 20%
# Validation duration with margin: 28800 * (1 - 0.20) = 23040s
# Time per event for each sequence: 5.4972s
# Threads for each sequence: 8
# Time per event for single thread for each sequence: 8 * 5.4972s = 43.9773s
# Which adds up to 43.9773s per event
# Single core events that fit in validation duration: 23040s / 43.9773s = 523
# Produced events limit in McM is 10000
# According to 1.0000 efficiency, up to 10000 / 1.0000 = 10000 events should run
# Clamp (put value) 523 within 1 and 10000 -> 523
# It is estimated that this validation will produce: 523 * 1.0000 = 523 events
EVENTS=5

# Random seed between 1 and 100 for externalLHEProducer
SEED=$(($(date +%s) % 100 + 1))


# cmsDriver command
cmsDriver.py Configuration/GenProduction/python/SUS-RunIIFall18wmLHEGS-00028-fragment.py --python_filename SUS-RunIIFall18wmLHEGS-00028_1_cfg.py --eventcontent RAWSIM,LHE --customise Configuration/DataProcessing/Utils.addMonitoring --datatier GEN-SIM,LHE --fileout file:SUS-RunIIFall18wmLHEGS-00028.root --conditions 102X_upgrade2018_realistic_v11 --beamspot Realistic25ns13TeVEarly2018Collision --customise_commands process.RandomNumberGeneratorService.externalLHEProducer.initialSeed="int(${SEED})" --step LHE,GEN,SIM --geometry DB:Extended --era Run2_2018 --no_exec --mc -n $EVENTS || exit $? ;
