export SCRAM_ARCH=slc6_amd64_gcc481
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
echo "$VO_CMS_SW_DIR $SCRAM_ARCH"
source ${VO_CMS_SW_DIR}/cmsset_default.sh
#cmsrel CMSSW_7_1_30

cd CMSSW_7_1_30/src
eval `scramv1 runtime -sh`
echo $CMSSW_BASE
cd ../..

