#!/bin/bash

echo "`pwd` `hostname` `uname -a`"

echo "### start step1 $1 $2 DDD `date` `hostname` `uname -a`"
./step1_WA_aTGC_NLO_2016.sh $1 $2 $3
ls -alh 
s1ROOT=`find . -maxdepth 1 -type f -name "s1_*.root"`

echo "### start step2 $s1ROOT DDD `date` `hostname` `uname -a`"
./step2_WA_aTGC_NLO_2016.sh ${s1ROOT}
ls -alh 
s2ROOT=`find . -maxdepth 1 -type f -name "s2_2_*.root"`

echo "### start step3 ${s2ROOT} DDD `date` `hostname` `uname -a`"
./step3_WA_aTGC_NLO_2016.sh ${s2ROOT}
ls -alh 
s3ROOT=`find . -maxdepth 1 -type f -name "s3_*.root"`

s3ROOTbasename=`basename $s3ROOT`

export SCRAM_ARCH=slc6_amd64_gcc630
source /cvmfs/cms.cern.ch/cmsset_default.sh
scram p CMSSW CMSSW_9_4_9
cd CMSSW_9_4_9/src
eval `scram runtime -sh`
scram b
cd ../../

xrdcp ${s3ROOT} root://cms-xrdr.sdfarm.kr:1094//xrd/store/user/ycyang/WA_aTGC_NLO_2016/MINIAODSIM/${s3ROOTbasename} 

mkdir condorOut/
mv *.log *_cfg.py ${s1ROOT} ${s3ROOT} condorOut/
echo "### Bye! Bye! GoodJob!!!"

