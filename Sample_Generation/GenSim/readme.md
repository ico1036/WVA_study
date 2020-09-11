## CMSSW workflow 

### Setup and cmsRun
 - [setup.sh](https://github.com/ico1036/WVA_study/tree/master/Sample_Generation/GenSim/out_GenXsec): Code & Env setup  
 - [SUS-RunIIFall18wmLHEGS-00028_1_cfg.py](https://github.com/ico1036/WVA_study/blob/master/Sample_Generation/GenSim/SUS-RunIIFall18wmLHEGS-00028_1_cfg.py) ( step 1 config file )
 - step1 output logfiles: out_pp2lnlall_250evts_step1,out_pp2lnlall_5evts_step1,out_pp2lnlaz_step1  

---
### Cross-section
 - [ana.py](https://github.com/ico1036/WVA_study/blob/master/Sample_Generation/GenSim/ana.py) : source code for "GenXsecAnalyzer"
 - [runGenXsecAnl.sh](https://github.com/ico1036/WVA_study/blob/master/Sample_Generation/GenSim/runGenXsecAnl.sh) "run GenXsecANalyzer"
 - [out_GenXsec](https://github.com/ico1036/WVA_study/tree/master/Sample_Generation/GenSim/out_GenXsec): output files from GenXsecAnalyzer
 
--- 
### Cross-section results

 #### Gridpack  
 1. pp2lnlaz (250 evts) : 6.551e-02 +- 7.0e-05 pb (3h 30min)  
 2. pp2lnlall (5 evts)     : 2.067e-04 +- 1.8e-06 pb (83h)  
 3. pp2lnlall (250 evts) : 5.774e-03 +- 8.4e-06 pb  
  
 #### Gen-SIM using GenXsecAnalyzer ( After filter: final cross section )
 1. pp2lnlall(250 evts): 1.188e-02 +- 1.119e-05 pb  
 2. pp2lnlall(5 evts)  : 1.188e-02 +- 1.119e-05 pb  
 3. pp2lnlaz(250 evts) : 7.619e-02 +- 7.481e-05 pb  

 
 
