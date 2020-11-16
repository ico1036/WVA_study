echo  "########################### pp2lnlall 250evt ##############################"
cmsRun ana.py  inputFiles="file:SUS-RunIIFall18wmLHEGS-00028.root" maxEvents=-1 2>&1 | tee pp2lnlall_250evt.log

