#!/bin/bash

TopDir=`pwd`
export X509_USER_PROXY=${TopDir}/x509up_u556800431
voms-proxy-info

RunN=$1
Idx=$2
MaxEvents=$3

echo "`pwd` `hostname` `uname -a`"



Name="LNuLLA"
s1root="s1_${Name}_${RunN}_${Idx}.root"
s21root="s21_${Name}_${RunN}_${Idx}.root"
s22root="s22_${Name}_${RunN}_${Idx}.root"
s3root="s3_${Name}_${RunN}_${Idx}.root"
s4root="s4_${Name}_${RunN}_${Idx}.root"


echo "### start step1 DDD `date` `hostname` `uname -a`"
./runStep1_LNuLLA.sh $s1root $RunN $Idx $MaxEvents
ls -alh
echo "Show me the space"
du -h
echo "Show me the left space"
df -h
s1ROOT=`find . -maxdepth 1 -type f -name "s1_*.root"`

echo "### start step2 DDD `date` `hostname` `uname -a`"
echo " ### Show me the voms ### "
voms-proxy-info
echo " ### ################ ### "
voms-proxy-info

./runStep2_LNuLLA.sh $s1root $s21root $s22root
ls -alh
echo "Show me the space"
du -h
echo "Show me the left space"
df -h
s2ROOT=`find . -maxdepth 1 -type f -name "s2_2_*.root"`

echo "### start step3 DDD `date` `hostname` `uname -a`"
./runStep3_LNuLLA.sh $s22root $s3root
ls -alh
echo "Show me the space"
du -h
echo "Show me the left space"
df -h
s3ROOT=`find . -maxdepth 1 -type f -name "s3_*.root"`

echo "### start step4 DDD `date` `hostname` `uname -a`"
./runStep4_LNuLLA.sh $s3root $s4root
ls -alh
echo "Show me the space"
du -h
echo "Show me the left space"
df -h
s4ROOT=`find . -maxdepth 1 -type f -name "s4_*.root"`

export SCRAM_ARCH=slc7_amd64_gcc700
source /cvmfs/cms.cern.ch/cmsset_default.sh
if [ -r CMSSW_10_6_19/src ] ; then
    echo release CMSSW_10_2_5 already exists
else
    scram p CMSSW CMSSW_10_6_19
fi
cd CMSSW_10_6_19/src
eval `scram runtime -sh`
scram b
cd ../../



mkdir condorOut/
mv *.log *_cfg.py ${s1ROOT} ${s2ROOT} ${s3ROOT} ${s4ROOT}  condorOut/

echo "### Bye! Bye! GoodJob!!!"
cd condorOut/
ls 
pwd

