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

#curl -s --insecure https://cms-pdmv.cern.ch/mcm/public/restapi/requests/get_fragment/SUS-RunIIFall18wmLHEGS-00028 --retry 2 --create-dirs -o Configuration/GenProduction/python/SUS-RunIIFall18wmLHEGS-00028-fragment.py 
#[ -s Configuration/GenProduction/python/SUS-RunIIFall18wmLHEGS-00028-fragment.py ] || exit $?;
#
#scram b
#cd ../../
#seed=$(($(date +%s) % 100 + 1))
#cmsDriver.py Configuration/GenProduction/python/SUS-RunIIFall18wmLHEGS-00028-fragment.py --fileout file:SUS-RunIIFall18wmLHEGS-00028.root --mc --eventcontent RAWSIM,LHE --datatier GEN-SIM,LHE --conditions 102X_upgrade2018_realistic_v11 --beamspot Realistic25ns13TeVEarly2018Collision --step LHE,GEN,SIM --nThreads 8 --geometry DB:Extended --era Run2_2018 --python_filename SUS-RunIIFall18wmLHEGS-00028_1_cfg.py --no_exec --customise Configuration/DataProcessing/Utils.addMonitoring --customise_commands process.RandomNumberGeneratorService.externalLHEProducer.initialSeed="int(${seed})" -n 1047 || exit $? ; 
#
